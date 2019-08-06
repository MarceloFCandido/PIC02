#include <mpi.h>
#include "util.h"
#include "_2DWave.h"

#define SPECS_DIR   "./specs/"
#define VEL_DIR     "./velocity/"
#define SNAPS_DIR   "./snaps/"
#define TRACES_DIR  "./traces/"
#define NUM_THREADS 12
#define MASTER      0

/*
 *    This program aims to solve the bidimensional wave equation
 *    by the finite differences method. This methods will be im-
 *    plemented with the help of Eigen library, that provides the
 *    necessary tools of the Linear Algebra, mainly the vectors
 *    and matrices thats will be used to store and manipulate data,
 *    as well the methods that are necessary to this.
 */

typedef struct kit_t {
    // current iteration
    int *k;
    // the reference for the wave object
    _2DWave *w;
    // the reference for the matrices to be manipulated
    mat *U[3];
    // the limits of manipulation for each thread
    int x_lim_begin,
        x_lim_end;
    // some parameters for calculation
    mat vel;        // velocity matrix
    vec X,          // spatial and temporal vectors
        Y,
        T;
    float dt2   ,   // constants
          dt2dx2,
          dt2dy2;
} KIT_t;

void *eval(void *kit) {
    KIT_t casted_kit = *((KIT_t *) kit);

    // we will copy the arguments to be more didatic
    // but the faster code would use pointers directly
    
    // getting the current time stamp
    int k = *(casted_kit.k);
    // getting the wave object
    _2DWave wv = *(casted_kit.w);
    // getting the matrices's addresses
    mat *U1 = casted_kit.U[0],
        *U2 = casted_kit.U[1],
        *U3 = casted_kit.U[2];
    // the velocity matrix
    mat v = casted_kit.vel;
    // getting the limits of the work
    int x_lim_begin = casted_kit.x_lim_begin,
        x_lim_end   = casted_kit.x_lim_end  ;
    // and the spatial and temporal vectors
    vec X = casted_kit.X,
        Y = casted_kit.Y,
        T = casted_kit.T;
    // and the parameters
    float dt2    = casted_kit.dt2,
          dt2dx2 = casted_kit.dt2dx2,
          dt2dy2 = casted_kit.dt2dy2;

    // TODO: Doing FDM calculations
    for (     int i = x_lim_begin; i <= x_lim_end     ; i++) {
        for ( int j = 1          ; j < wv.getNy() - 1; j++) {
            (*U1)(i,j) =  v(i,j) * ( dt2dx2 * ( (*U2)(i+1,j  ) - 2. *  (*U2)(i,j) + (*U2)(i-1,j  ) ) 
                                   + dt2dy2 * ( (*U2)(i  ,j+1) - 2. *  (*U2)(i,j) + (*U2)(i  ,j-1) ) )
                    + dt2 * wv.evaluateFXYT( X(i), Y(j), T(k) ) + 2. * (*U2)(i,j) - (*U3)(i  ,j  )    ;
        }
    }
}

int main (int argc, char *argv[]) {

    // Variables for working with MPI
    int task_id,   // task NUM - the identification of a task
        num_tasks, // number of tasks
        rc,        // for returning code
        i;

    // initiating MPI, starting tasks and identifying them
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &task_id);

    // Getting external data
    ifstream wf ( SPECS_DIR "wOut.dat", ios::in | ios::binary);
    ifstream vf ( SPECS_DIR "vOut.dat", ios::in | ios::binary);
    ifstream ifl( SPECS_DIR "iOut.dat", ios::in | ios::binary);

    vector<interface> it;
    vector<velocity> vl;
    ifstream nInt( SPECS_DIR "nInt.dat", ios::in);
    int N;
    nInt >> N;
    for (int i = 0; i < N; i++) {
        interface auxI(0., 0.);
        velocity auxV(0., 0., 0.);
        auxI.deserialize(&ifl);
        auxV.deserialize(&vf);
        it.push_back(auxI);
        vl.push_back(auxV);
    }
    velocity auxV(0., 0., 0.);
    auxV.deserialize(&vf);
    vl.push_back(auxV);

    _2DWave wv(0., 0., 0., 0., 0., 0., 0., 0., 0., 0.);

    wv.deserialize(&wf);
    wf.close(); vf.close(); ifl.close();

    // Creating velocities matrix
    mat v;
    v.load( VEL_DIR "velocity.dat", raw_ascii);

    // Compute 1/v^2 only once for all steps
    for (int i = 1; i < wv.getMx() - 1; i++) {
        for (int j = 1; j < wv.getNy() - 1; j++) {
	        v(i,j) = 1.0 / ( v(i,j) * v(i,j) );
	    }
    }

    // Creating arrays for space dimensions X e Y and for time
    vec X = linspace<vec>(0., wv.getLx(),   wv.getMx());
    vec Y = linspace<vec>(0., wv.getLy(),   wv.getNy());
    vec T = linspace<vec>(0., wv.getTMax(), wv.getOt());

    // Saving arrays of dimensions in space
    if (task_id == MASTER) {
        X.save( SPECS_DIR "X.dat", raw_ascii);
        Y.save( SPECS_DIR "Y.dat", raw_ascii);
        T.save( SPECS_DIR "T.dat", raw_ascii);
    }

    nInt >> N; // reusing N
    queue <int> numSnaps;
    if (N > 0) { // get the frames's numbers that must be saved as 
                 // snapshots
        int h = (int) wv.getOt() / N;
        for (int i = 1; h * i < wv.getOt(); i++) { numSnaps.push(h * i); }
    }

    // Receiving data about receivers
    int nRecv;
    double offset_Recv;
    nInt >> nRecv;
    nInt >> offset_Recv;
    nInt.close();

    // Matrix to armazenate traces
    mat traces((int) wv.getOt(), nRecv);
    traces.fill(0.);
    // the number of points between receivers
    // the receivers will be equidistant between itselves
    int offset_Recv_int = wv.getMx() / nRecv;

    // Creating 3 matrices for application of the Finite Difference Method (FDM)
    mat U1((int) wv.getMx(), (int) wv.getNy());
    mat U2((int) wv.getMx(), (int) wv.getNy());
    mat U3((int) wv.getMx(), (int) wv.getNy());

    // Filling the matrices with zeros
    U1.fill(0.);
    U2.fill(0.);
    U3.fill(0.);

    // Creating a queue for administrating the arrays of FDM
    queue <mat> U;
    U.push(U1); U.push(U2); U.push(U3);

    double dt2    =         wv.getDt() * wv.getDt()  ;
    double dt2dx2 = dt2 / ( wv.getDx() * wv.getDx() );
    double dt2dy2 = dt2 / ( wv.getDy() * wv.getDy() );

    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // creating kits for threads
    KIT_t kits[NUM_THREADS];
    int k;
    for (int i = 0; i < NUM_THREADS - 1; i++) {
        kits[i].k              = &k                                                  ;
        kits[i].w              = &wv                                                 ;
        kits[i].x_lim_begin    =  i      * ((int) (wv.getMx() - 2) / NUM_THREADS) + 1;
        kits[i].x_lim_end      = (i + 1) * ((int) (wv.getMx() - 2) / NUM_THREADS)    ;
        kits[i].vel            = v                                                   ;
        kits[i].X              = X                                                   ;
        kits[i].Y              = Y                                                   ;
        kits[i].T              = T                                                   ;
        kits[i].dt2            = dt2                                                 ;
        kits[i].dt2dx2         = dt2dx2                                              ;
        kits[i].dt2dy2         = dt2dy2                                              ;
    }
    // the last kit get all the rest of the points
    kits[NUM_THREADS - 1].k           = &k                                                            ;
    kits[NUM_THREADS - 1].w           = &wv                                                           ;
    kits[NUM_THREADS - 1].x_lim_begin = (NUM_THREADS - 1) * ((int) (wv.getMx() - 2) / NUM_THREADS) + 1;
    kits[NUM_THREADS - 1].x_lim_end   =                      (int)  wv.getMx() - 2                    ;
    kits[NUM_THREADS - 1].vel         = v                                                             ;
    kits[NUM_THREADS - 1].X           = X                                                             ;
    kits[NUM_THREADS - 1].Y           = Y                                                             ;
    kits[NUM_THREADS - 1].T           = T                                                             ;
    kits[NUM_THREADS - 1].dt2         = dt2                                                           ;
    kits[NUM_THREADS - 1].dt2dx2      = dt2dx2                                                        ;
    kits[NUM_THREADS - 1].dt2dy2      = dt2dy2                                                        ;

    for (k = 1; k < wv.getOt() - 1; k++) {
        // Getting the matrices from the queue
        U1 = U.front(); U.pop(); // t + 1
        U2 = U.front(); U.pop(); // t
        U3 = U.front(); U.pop(); // t - 1

        // giving the addresses of the matrices to the threads's kits
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < NUM_THREADS; j++) {
                if (i == 0) kits[j].U[i] = &U1;
                else if (i == 1) kits[j].U[i] = &U2;
                else kits[j].U[i] = &U3;
            }
        }

        // launching threads
        for (int i = 0; i < NUM_THREADS; i++) {
            if (pthread_create(&threads[i], &attr, eval, (void *) &kits[i]) != 0) {
                printf("Error at creating thread %d at iteration %d.\n Aborting...", i, k);
                exit(1);
            }
        }

        // joining threads
        for (int i = 0; i < NUM_THREADS; i++) {
            if (pthread_join(threads[i], NULL) != 0) {
                printf("Error at joining thread %d at iteration %d.\n Aborting...", i, k);
                exit(1);
            }
        }

        // Registering traces
        for (int ii = 1; ii * offset_Recv_int < size(U1)(0) && ii < nRecv; ii++) {
            traces(k, ii) = U1(ii * offset_Recv_int, 1);
        }

        // if frame k is one of the required for the snaps
        if (N > 0 && k == numSnaps.front() && task_id == MASTER) {
            ostringstream oss;
            float save = numSnaps.front() * wv.getDt();
            oss << SNAPS_DIR << "th" << task_id << "-" << save << ".dat";
            numSnaps.pop(); numSnaps.push(save);
            U1.save(oss.str(), raw_ascii);
        }

        // Putting the matrices again in the queue
        U.push(U3); U.push(U1); U.push(U2);
    }

    vec d(7);
    d(0) = (int) wv.getMx();
    d(1) = (int) wv.getNy();
    d(2) = (int) wv.getOt();
    d(3) = N;
    d(4) = wv.getLx();
    d(5) = wv.getLy();
    d(6) = nRecv;

    if (task_id == MASTER) {
        d.save( SPECS_DIR "output.dat", raw_ascii);
        traces.save( TRACES_DIR "traces.dat", raw_ascii);
    }

    MPI_Finalize();

    return 0;

}
