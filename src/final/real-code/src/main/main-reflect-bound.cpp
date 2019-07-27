#include "util.h"
#include "_2DWave.h"

#define SPECS_DIR  "./specs/"
#define VEL_DIR    "./velocity/"
#define SNAPS_DIR  "./snaps/"
#define TRACES_DIR "./traces/"
#define NUM_THREADS 6

/*
 *    This program aims to solve the bidimensional wave equation
 *    by the finite differences method. This methods will be im-
 *    plemented with the help of Eigen library, that provides the
 *    necessary tools of the Linear Algebra, mainly the vectors
 *    and matrices thats will be used to store and manipulate data,
 *    as well the methods that are necessary to this.
 */

typedef struct kit_t {
    // the reference for the wave object
    // the reference for the queue matrices to be manipulated
    // the limits of manipulation for each thread
    // some parameters for calculation
} KIT_t;

void *eval(void *kit) {
    KIT_t casted_kit = (KIT_t *) kit;


}

int main () {
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
    X.save( SPECS_DIR "X.dat", raw_ascii);
    Y.save( SPECS_DIR "Y.dat", raw_ascii);
    T.save( SPECS_DIR "T.dat", raw_ascii);

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

    double dt2    =         wv.getDt() * wv.getDt();
    double dt2dx2 = dt2 / ( wv.getDx() * wv.getDx() );
    double dt2dy2 = dt2 / ( wv.getDy() * wv.getDy() );

    // creating kits for threads
    KIT_t kits[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        
    }

    // for (int k = 1; k < wv.getOt() - 1; k++) {
    //     // Getting the matrices from the queue
    //     U1 = U.front(); U.pop(); // t + 1
    //     U2 = U.front(); U.pop(); // t
    //     U3 = U.front(); U.pop(); // t - 1

    //     // Doing FDM calculations
    //     for (     int i = 1; i < wv.getMx() - 1; i++) {
    //         for ( int j = 1; j < wv.getNy() - 1; j++) {
    //             U1(i,j) =  v(i,j) * ( dt2dx2 * ( U2(i+1,j) - 2.0*U2(i,j) + U2(i-1,j) ) 
    //                                 + dt2dy2 * ( U2(i,j+1) - 2.0*U2(i,j) + U2(i,j-1) ) )
    //                     + dt2 * wv.evaluateFXYT( X(i), Y(j), T(k) ) 
    //                     + 2.0 * U2(i,j) - U3(i,j);
    //         }
    //     }

    //     // Registering traces
    //     for (int ii = 1; ii * offset_Recv_int < size(U1)(0) && ii < nRecv; ii++) {
    //         traces(k, ii) = U1(ii * offset_Recv_int, 1);
    //     }

    //     // if frame k is one of the required for the snaps
    //     if (N > 0 && k == numSnaps.front()) {
    //         ostringstream oss;
    //         int save = numSnaps.front();
    //         oss << SNAPS_DIR << setfill('0') << setw(5) << save << ".dat";
    //         numSnaps.pop(); numSnaps.push(save);
    //         U1.save(oss.str(), raw_ascii);
    //     }

    //     // Putting the matrices again in the queue
    //     U.push(U3); U.push(U1); U.push(U2);
    // }

    vec d(7);
    d(0) = (int) wv.getMx();
    d(1) = (int) wv.getNy();
    d(2) = (int) wv.getOt();
    d(3) = N;
    d(4) = wv.getLx();
    d(5) = wv.getLy();
    d(6) = nRecv;

    d.save( SPECS_DIR "output.dat", raw_ascii);

    traces.save( TRACES_DIR "traces.dat", raw_ascii);

    return 0;

}
