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
    this->dx = Lx / (Mx - 1); // x axis's interval
    this->dy = this->dx;            // y axis's interval
    this->dt = this->dy / 2.;
    // Number of instants in the time
    this->Ot = (int) ceil(tMax / this->dt);
    this->R = PI * PI + w * w;  // TODO: explain
}

double _2DWave::getLx() {
    return this->Lx;
}

void _2DWave::setLx(double Lx) {
    this->Lx = Lx;
}

double _2DWave::getLy() {
    return this->Ly;
}

void _2DWave::setLy(double Ly) {
    this->Ly = Ly;
}

double _2DWave::getTMax() {
    return this->tMax;
}

void _2DWave::setTMax(double tMax) {
    this->tMax = tMax;
}

double _2DWave::getMx() {
    return this->Mx;
}

void _2DWave::setMx(double Mx) {
    this->Mx = Mx;
}

double _2DWave::getNy() {
    return this->Ny;
}

void _2DWave::setNy(double Ny) {
    this->Ny = Ny;
}

double _2DWave::getW() {
    return this->w;
}

void _2DWave::setW(double w) {
    this->w = w;
}

double _2DWave::getA() {
    return this->A;
}

void _2DWave::setA(double A) {
    this->A = A;
}

double _2DWave::getXp() {
    return this->Xp;
}

void _2DWave::setXp(double Xp) {
    this->Xp = Xp;
}

double _2DWave::getYp() {
    return this->Yp;
}

void _2DWave::setYp(double Yp) {
    this->Yp = Yp;
}

double _2DWave::getTp() {
    return this->Tp;
}

void _2DWave::setTp(double Tp) {
    this->Tp = Tp;
}

double _2DWave::getOt() {
    return this->Ot;
}

void _2DWave::setOt(double Ot) {
    this->Ot = Ot;
}

double _2DWave::getDx() {
    return this->dx;
}

void _2DWave::setDx(double dx) {
    this->dx = dx;
}

double _2DWave::evaluateFXYT(double x, double y, double t) {
    // TODO: Refactor
    /**
     * Function that returns a bidimensional velocities array.
     * TODO: redocument
    */

    // Defining Tterm
    double tTerm = t - this->Tp;
    tTerm *= tTerm;
    tTerm *= this->R;

    // Defining Xterm
    double xTerm = x - this->Xp;
    xTerm *= xTerm;

    // Defining Yterm
    double yTerm = y - this->Yp;
    yTerm *= yTerm;

    // Defining Dterm
    double dTerm = xTerm + yTerm;
    dTerm *= this->R;

    // CAUTION: the minus in front of Tterm and Dterm
    return this->A * exp(-tTerm) * ((1 - 2 * dTerm) * exp(-dTerm));

}

mat _2DWave::getVelocitiesMatrix(vector<interface> interfaces,
    vector<velocity> velocities) {
    // TODO: Refactor
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

    // Instatiating matrix for velocities
    mat v((int) this->Mx, (int) this->Ny);
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

/** Function for serialization of velocity objects
 *  Receives:       ofstream object - file that will receive the data
 *                                   of the this velocity object
 */
void _2DWave::serialize(ofstream *file) {
    if((*file).is_open()) {
        double data[10]; // for writing attributes of the class
                        // in the file
        data[0] = this->Lx;
        data[1] = this->Ly;
        data[2] = this->tMax;
        data[3] = this->Mx;
        data[4] = this->Ny;
        data[5] = this->w;
        data[6] = this->A;
        data[7] = this->Xp;
        data[8] = this->Yp;
        data[9] = this->Tp;
        (*file).write((char *) &data, sizeof(data));
    } else {
        printf("Error: The file isn't open.\nAborting...");
        // exit(1);
    }
}

/** Function for deserialization of velocity objects
 *  Receives:       ifstream object - file that will supply the data
 *                                   for the this velocity object
 */
void _2DWave::deserialize(ifstream *file) {
    if((*file).is_open()) {
        double data[10]; // for writing attributes of the class
                        // in the file
        (*file).read((char *) &data, sizeof(data));
        this->Lx = data[0];
        this->Ly = data[1];
        this->tMax = data[2];
        this->Mx = data[3];
        this->Ny = data[4];
        this->w = data[5];
        this->A = data[6];
        this->Xp = data[7];
        this->Yp = data[8];
        this->Tp = data[9];
        // Redoing the atributions that depend of the data deserialize above
        this->dx = this->Lx / (this->Mx - 1); // x axis's interval
        this->dy = this->dx;            // y axis's interval
        this->dt = this->dy / 2.;
        // Number of instants in the time
        this->Ot = (int) ceil(this->tMax / this->dt);
        this->R = PI * PI + this->w * this->w;  // TODO: explain
    } else {
        printf("Error: The file isn't open.\nAborting...");
        // exit(1);
    }
}
