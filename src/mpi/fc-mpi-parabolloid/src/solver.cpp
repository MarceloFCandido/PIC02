#include <armadillo>
#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <string>

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
  int task_id,   // task NUM - the identification of a task
      num_tasks, // number of tasks
      rc,        // for returning code
      i;

  // initiating MPI, starting tasks and identifying them
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &task_id);

  int x_points, y_points;
  float x_b, y_b;
  float x_e, y_e;

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

  // determining the space between points in x and y
  float x_ofst = (x_e - x_b) / x_points;
  float y_ofst = (y_e - y_b) / y_points;
  // determining the beggining and the end of the domain based on task_id
  x_b = x_b + task_id * x_ofst * x_points;
  x_e = x_b + x_ofst * x_points;

  printf("Task %d: X points = %d      \n", task_id, x_points);
  printf("Task %d: X beggining = %.1f \n", task_id, x_b);
  printf("Task %d: X ending = %.1f    \n", task_id, x_e);
  printf("Task %d: Y points = %d      \n", task_id, y_points);
  printf("Task %d: Y beggining = %.1f \n", task_id, y_b);
  printf("Task %d: Y ending = %.1f    \n", task_id, y_e);

  mat A(x_points, y_points);
  rowvec parameters(6);

  // Storing parameters in a vector for a file
  parameters(0) = x_points;
  parameters(1) = x_ofst;
  parameters(2) = x_b;
  parameters(3) = y_points;
  parameters(4) = y_ofst;
  parameters(5) = y_b;

  // Calculating function
  float x_i = x_b;
  float y_i = y_b;

  printf("\nTask %d: calculation is beggining!\n", task_id);

  for (int i = 0; i < x_points; i++) {
    for (int j = 0; j < y_points; j++) {
      A(i, j) = 2. * x_i * x_i + y_i * y_i;
      y_i += y_ofst;
    }
    x_i += x_ofst;
    y_i = y_b;
  }

  printf("\nTask %d: calculation is over!\n", task_id);

  if (task_id != MASTER) { // if it's not the master
    // sending matrix's beggining pointer to master
    printf("\nTask %d: sending!\n", task_id);
    MPI_Send(A.begin(), A.size(), MPI_DOUBLE, MASTER, 0, MPI_COMM_WORLD);
  } else { // if it's the master
    mat B(num_tasks * x_points, y_points);
    B.rows(0, x_points - 1) = A;
    for (int i = 1; i < num_tasks; i++) {
      printf("\nMaster: receiving from task %d!\n", i);
      MPI_Recv(A.begin(), A.size(), MPI_DOUBLE, i, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      B.rows(i * x_points, (i + 1) * x_points - 1) = A;
    }
    B.save("data/outputs/A.dat", raw_binary);
    parameters(0) *= num_tasks;
    parameters.save("data/outputs/pmts.dat", raw_ascii);
  }

  MPI_Finalize();

  return 0;
}
