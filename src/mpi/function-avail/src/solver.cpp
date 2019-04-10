#include <iostream>
#include <stdio.h>
#include <string>
#include <armadillo>
#include <mpi.h>

using namespace std;
using namespace arma;

// Based on https://computing.llnl.gov/tutorials/mpi/samples/C/mpi_pi_reduce.c

#define MASTER 0

/* Args
 * x_points - number of points of the domain in the x axis
 * x_b      - beggining of the domain in x
 * x_e      - end of the domain in x
 * y_points - number of points of the domain in the y axis
 * y_b      - beggining of the domain in y
 * y_e      - end of the domain in y
**/

int main(int argc, char *argv[]) {

    // Variables for working with MPI
    int	task_id,        // task NUM - the identification of a task
	    num_tasks,       // number of tasks
	    rc,              // for returning code
	    i;
    MPI_Status status;

    // initiating MPI, starting tasks and identifying them
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &task_id);

    int   x_points, y_points;
    float x_b     , y_b     ;
    float x_e     , y_e     ;

    // Creating objects for conversion of arguments
    stringstream convert0(argv[1]);
    stringstream convert1(argv[2]);
    stringstream convert2(argv[3]);
    stringstream convert3(argv[4]);
    stringstream convert4(argv[5]);
    stringstream convert5(argv[6]);

    // Putting arguments on variables
    convert0 >> x_points;
    convert1 >> x_b;
    convert2 >> x_e;
    convert3 >> y_points;
    convert4 >> y_b;
    convert5 >> y_e;

    cout << "Task: " << task_id << " X points: "    << x_points << "\n";
    cout << "Task: " << task_id << " X beggining: " << x_b      << "\n";
    cout << "Task: " << task_id << " X end: "       << x_e      << "\n";
    cout << "Task: " << task_id << " Y points: "    << y_points << "\n";
    cout << "Task: " << task_id << " Y beggining: " << y_b      << "\n";
    cout << "Task: " << task_id << " X end: "       << x_e      << "\n";

    mat A(x_points, y_points);
    rowvec parameters(6);

    // determining the space between points in x and y
    float x_ofst = (x_e - x_b) / x_points;
    float y_ofst = (y_e - y_b) / y_points;

    // Storing parameters in a vector for a file
    parameters(0) = x_points; parameters(1) = x_ofst; parameters(2) = x_b;
    parameters(3) = y_points; parameters(4) = y_ofst; parameters(5) = y_b;

    // Calculating function
    float x_i = x_b;
    float y_i = y_b;

    for (int i = 0; i < x_points; i++) {
        for (int j = 0; j < y_points; j++) {
	        A(i, j) = 2. * x_i * x_i + y_i * y_i;
            y_i += y_ofst;
        }
        x_i += x_ofst;
        y_i = y_b;
    }

    if (task_id != MASTER) { // if it's not the master
        // sending matrix's beggining pointer to master
        printf("Task %d: sending!", task_id);
        MPI_Send(A.begin(), A.size(), MPI_DOUBLE, MASTER, 0, MPI_COMM_WORLD);
    } else { // if it's the master
        A.save("data/outputs/A0.dat", raw_binary);
        // FIXME: maybe A should be deleted before continuing
        for (int i = 0; i < num_tasks; i++) {
            printf("Master: receiving from task %d!", i);
            MPI_Recv(A.begin(), A.size(), MPI_DOUBLE, i, 0, MPI_COMM_WORLD,
                MPI_STATUS_IGNORE);
            string path = "data/outputs/A" + to_string(i) + ".dat";
            A.save(path, raw_binary);
        }
    }

    // parameters.save("data/outputs/pmts.dat", raw_ascii);

    MPI_Finalize();

    return 0;
}
