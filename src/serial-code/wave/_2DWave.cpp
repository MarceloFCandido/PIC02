#include "_2DWave.h"

// TODO: document
_2DWave::_2DWave (double Lx,
        double Ly,
        double tMax,
        double Mx,
        double Ny,
        double w,
        double A,
        double Xp,
        double Yp,
        double Tp) {
    this->Lx = Lx;       // Extension of medium in x
    this->Ly = Ly;       // Depth of the medium in y
    this->tMax = tMax;   // Maximum simulation time
    this->Mx = (int) Mx; // Number of points in the x axis
    this->Ny = (int) Ny; // Number of points in the y axis
    this->w  = w;        // Domminant frequency omega
    this->A  = A;        // Wave's amplitude
    this->Xp = Xp;       // X coordinate of the peak of the pulse
    this->Yp = Yp;       // Y coordinate of the peak of the pulse
    this->Tp = Tp;       // Instant of the peak of the pulse
    this->dx = (int) Lx / (Mx - 1); // x axis's interval
    this->dy = this->dx;            // y axis's interval
    this->dt = this->dy / 2.;
    // Number of instants in the time
    this->Ot = (int) ceil(tMax / this->dt);
    this->R = PI * PI + w * w;  // TODO: explain
}

// TODO: Create getters for the entries

RowArrayIJ _2DWave::evaluateFXYT(RowArrayIJ X, RowArrayIJ Y, RowArrayIJ T) {
    /**
     * Function that returns a bidimensional velocities array.
     * TODO: document
    */

    // Defining Tterm
    RowArrayIJ Tterm(1, T.size());
    Tterm = T - this->Tp;
    Tterm = Tterm.array().square();
    Tterm *= this->R;

    // Defining Xterm
    RowArrayIJ Xterm(1, X.size());
    Xterm = X - this->Xp;
    Xterm = Xterm.array().square();

    // Defining Yterm
    RowArrayIJ Yterm(1, Y.size());
    Yterm = Y - this->Yp;
    Yterm = Yterm.array().square();

    // Defining Dterm
    RowArrayIJ Dterm(1, Xterm.size());
    Dterm = Xterm + Yterm;
    Dterm *= this->R;

    // CAUTION: the minus in front of Tterm and Dterm
    return this->A * -Tterm.array().exp() * ((1 - 2 * Dterm) *
        -Dterm.array().exp());

}

RowArrayIJ _2DWave::getVelocitiesMatrix(vector<interface> interfaces,
    vector<velocity> velocities) {
    /** Function that returns the bidimensional velocities matrix
     *  of the medium.
     *  For each medium's point that the wave propagates, we calculate
     *  a velocity based on which layer of the medium this point is
     * found.
     *
     *  Receives:       interfaces - a vector of interface objects
     *                  velocities - a vector of velocity objects,
     *                               where each object represents the
     *                               velocity function of its
     *                               respective layer
     */
    // Creating iterators
    vector<interface> :: iterator ifs;
    vector<velocity> :: iterator vls;

    // Instatiating matrix for velocities
    RowArrayIJ v((int) this->Mx, (int) this->Ny);

    int k = 0;
    // Putting the values on the velocities matrix
    for (int i = 0; i < this->Mx; i++) {
        double x;
        x = i * this->dx;   // An step in the abscissas
        for (int j = 0; j < this->Ny; j++) {
            double y;
            y = j * this->dy;   // An step in the ordinates
            while (y > interfaces[k].getY(x) && k < interfaces.size()
                    - 1) {
                    k += 1; // Looking for on which layer the point is
            }
            // Calculating the velocity in the point
            v(i, j) = velocities[k].getGradientVelocity(x, y);
        }
    }

    return v;

}
