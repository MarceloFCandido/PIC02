#include <iostream>
#include <stdio.h>
#include <mpi.h>
#include <armadillo>
#include <queue>
#include <pthread.h>

using namespace std;
using namespace arma;

#define MASTER      0
#define NUM_THREADS 6
#define PI          3.14159265359

/** Args
 * @brief 
 *  x_points - number of points in x axis
	x_b      - beggining of the x axis
  	x_t      - end of the x axis
	x_w      - value in axis to begin the wave
	t_t      - end of the t(ime) axis
	t_w      - value of the end of the t axis
	freq     - value of the frequency of the wave
 */

typedef struct kit_t {
    int thread_id;
    mat *A        ;
    int x_pt_start,
        x_pt_end  ,
        i         ;
    float x_j,
          t_i,
          x_ofst;
} KIT_t;

// some global variables to be used in the calculations
float A,
      R,
      t_w/*ave */,
      x_w/*ave */,
      pi2_freq2,
      x_ofst_2,
      t_ofst_2,
      termA;

float fxt(float x, float t) {
	float Dx  = x - x_w;
	float Dx2 = Dx * Dx;
	float Dt  = t - t_w;
	float Dt2 = Dt * Dt;

	float result = ((1. - 2. * pi2_freq2 * Dt2) * exp(-pi2_freq2 * Dt2)) * \
                    ((1. - 2. * pi2_freq2 * Dx2) * exp(-pi2_freq2 * Dx2));

	return result;
}

void *eval(void *void_kit) {
    KIT_t *kit = (KIT_t *) void_kit;

    int thread_id  = kit->thread_id ;
    mat *A         = kit->A         ;
    int x_pt_start = kit->x_pt_start;
    int x_pt_end   = kit->x_pt_end  ;
    float x_j      = kit->x_j       ;
    float t_i      = kit->t_i       ;

    float x_ofst   = kit->x_ofst    ;
    int i          = 1              ;

    for (int j = x_pt_start; j <= x_pt_end; j++) {
        (*A)(i + 1, j) = termA * ((*A)(i, j - 1) - 2. * (*A)(i, j) + \
            (*A)(i, j + 1)) - (*A)(i - 1, j) + 2. * (*A)(i, j) + t_ofst_2 * \
            fxt(x_j, t_i);
        x_j += x_ofst;
    }

    pthread_exit(NULL);
}

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

    int   x_points   , t_points   ;
	float x_ofst     , t_ofst, x_t/*otal*/;
	float x_b/*egin*/, t_t/*otal*/;

    // auxiliary variables
    float freq,
          freq2,
          pi2 = PI * PI;

	// Creating objects for conversion of arguments
	stringstream convert0(argv[1]);
	stringstream convert1(argv[2]);
	stringstream convert2(argv[3]);
	stringstream convert3(argv[4]);
	stringstream convert4(argv[5]);
	stringstream convert5(argv[6]);
	stringstream convert6(argv[7]);

    // Putting arguments on variables
  	convert0 >> x_points;
	convert1 >> x_b;
  	convert2 >> x_t;
	convert3 >> x_w;
	convert4 >> t_t;
	convert5 >> t_w;
	convert6 >> freq;

    // finding some different place to begin the wave (if this task is not MASTER)
    if (task_id != MASTER) {
        if (x_w + .5 * task_id >= x_b || x_w + .5 * task_id <= x_t) {
            x_w += .5 * task_id;
        } else {
            float x_w_temp;
            do {
                x_w_temp = x_w + rand() / rand();
            } while (x_w_temp < x_b || x_w_temp > x_t);
            x_w = x_w_temp;
        }
    }

	x_ofst    = (x_t - x_b) / x_points;
	t_ofst    = .5 * x_ofst;    // respecting Nyquist theorem
	t_points  = (int) t_t / t_ofst;
	freq2     = freq * freq;
	pi2_freq2 = pi2 * freq2;

    printf("Task %d's specs report\n"
            "X points    : \t%d   \n"
            "T points    : \t%d   \n"
            "X offset    : \t%f   \n"
            "T offset    : \t%f   \n"
            "X total     : \t%f   \n"
            "X total     : \t%f   \n"
            "X wave's pic: \t%f   \n"
            "X wave's pic: \t%f   \n",
        task_id                      , 
        x_points                     , 
        t_points                     , 
        x_ofst                       , 
        t_ofst                       , 
        x_points * x_ofst            , 
        t_t                          , 
        x_w                          , 
        t_w                          );

    // creating the matrix for calculations and a row vector for saving
    // parameters
    mat B(t_points, x_points);
    B.fill(0.);
    mat A(3, x_points);
	A.fill(0.);
  	rowvec parameters(5);

  	// Storing parameters in a vector for a file
  	parameters(0) = x_points;
	parameters(1) = x_ofst;
	parameters(2) = x_b;
  	parameters(3) = t_t;
	parameters(4) = t_points;

  	// Calculating function
	float x_j = x_b;
	float t_i = 0.;

    // setting some calculation variables
	x_ofst_2 = x_ofst * x_ofst;
	t_ofst_2 = t_ofst * t_ofst;
	termA = t_ofst_2 / x_ofst_2;

    // creating threads
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;

    // creating kits for the threads
    KIT_t kits[NUM_THREADS];

    // initializing ptheads attribute and setting threads as joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // determining how many points each thread will have to take care of
    int x_pts_per_thread = (x_points - 2) / NUM_THREADS;

    // distributing information for kits
    for(int i = 0; i < NUM_THREADS - 1; i++) {
        kits[i].thread_id  = i                                      ;
        kits[i].A          = &A                                     ;
        kits[i].x_pt_start = i * x_pts_per_thread + 1               ;
        kits[i].x_pt_end   = i * x_pts_per_thread + x_pts_per_thread;
        kits[i].x_j        = x_ofst * x_pts_per_thread * i          ;
        kits[i].t_i        = t_ofst                                 ;
        kits[i].x_ofst     = x_ofst                                 ;
    }
    kits[NUM_THREADS - 1].thread_id  = NUM_THREADS - 1                         ;
    kits[NUM_THREADS - 1].A          = &A                                      ;
    kits[NUM_THREADS - 1].x_pt_start = (NUM_THREADS - 1) * x_pts_per_thread + 1;
    kits[NUM_THREADS - 1].x_pt_end   = x_points - 2                            ;
    kits[NUM_THREADS - 1].x_j        = x_ofst * x_pts_per_thread * \
        (NUM_THREADS - 1);
    kits[NUM_THREADS - 1].t_i        = t_ofst                                  ;
    kits[NUM_THREADS - 1].x_ofst     = x_ofst                                  ;

    // Iterating in the time
    printf("Task %d: calculation is beggining!\n", task_id);
    for (int i = 1; i < t_points - 1; i++) {
        // creating threads
        for (long j = 0; j < NUM_THREADS; j++) {
            kits[j].t_i = t_ofst * i;
            if (pthread_create(&threads[j], &attr, eval, (void *) &kits[j])) {
                printf("Error on creating thread %ld\n", j);
                exit(1);
            }
        }

        // joining threads
        void *status;
        for (long j = 0; j < NUM_THREADS; j++) {
            int returnCode;
            returnCode = pthread_join(threads[j], &status);
            if (returnCode) {
                printf("Error on joining thread %ld\nThread returned %d", j,
                    returnCode);
            }
        }

        // we need always to save the last line of B before 'deleting' it
        B.row(i - 1) = A.row(0);
        A.rows(0, 1) = A.rows(1, 2);
        A.row(2).zeros();
    }
    printf("Task %d: calculation is over!\n", task_id);

    if (task_id != MASTER) { // if it's not the master
        // sending matrix's beggining pointer to master
        printf("\nTask %d: sending!\n", task_id);
        MPI_Send(B.begin(), B.size(), MPI_DOUBLE, MASTER, 0, MPI_COMM_WORLD); 
    } else { // if it's MASTER
        // saving parameters
        parameters(0) *= num_tasks;
        parameters.save("data/outputs/pmts.dat", raw_ascii);
        // creating auxiliary matrix for MPI_Recv()
        mat C(size(B));
        // resizing B for receiving data from the other tasks
        B.resize(t_points, num_tasks * x_points);
        // receiving data from other tasks
        for (int i = 1; i < num_tasks; i++) {
            printf("Master: receiving from task %d!\n", i);
            MPI_Recv(C.begin(), C.size(), MPI_DOUBLE, i, 0, MPI_COMM_WORLD, 
                     MPI_STATUS_IGNORE);
            B.cols(i * x_points, (i + 1) * x_points - 1) = C;
        }
        B.save("data/outputs/A.dat", raw_binary);
    }

    MPI_Finalize();

    return 0;
}
