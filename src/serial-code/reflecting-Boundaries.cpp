# include <iostream>
# include <cmath>
# include <Eigen/Dense>
# include <iterator>
# include <vector>

using namespace std;

/*
 *    This program aims to solve the bidimensional wave equation 
 *    by the finite differences method. This methods will be im-
 *    plemented with the help of Eigen library, that provides the
 *    necessary tools of the Linear Algebra, mainly the vectors 
 *    and matrices thats will be used to store and manipulate data, 
 *    as well the methods that are necessary to this.
 */

# define PI 3.141592653589793238463

// Defining my own Array type object
// TODO: citar fonte
typedef Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RowArrayIJ;

class interface {
    /**
     * Defines an interface as a linear function
     */

    private:
        double a, b;

    public:
        interface(double a, double b) {
            /**
             * Constructor
             * Receives:    a - angular coefficient
             *              b - independent term
             */ 
            this->a = a;
            this->b = b;
        }

        // Getters 
        // (setters are not made because it's not
        // supposed that 'a' and 'b' change after defined by
        // the constructor)

        double getA() {
            return this->a;
        };

        double getB() {
            return this->b;
        };

        // The interface was imaginated like a linear function: 
        //                      y = ax + b
        // So, to get a the height of an point (the y coordinate) 
        // in the interface, we just give a point x to it
        double getY(double x) {
            /**
             * Function definition
             * Receives:    x - point's coordinate in the abscissas
             * Returns:     y - point's coordinate in the ordinates
             */ 
            return this->a * x + this->b;
        };

};

class velocity {
    /**
     * Defines velocity as a quadractic function of the form
     *                  v(x, y) = ax + by + c
     */ 
    private:
        double a, b, c;
    
    public:
        velocity(double a, double b, double c) {
            /**
             * Constructor
             * Receives:    a - term 'a' of the velocity function
             *              b - term 'b' of the velocity function
             *              c - term 'c' of the velocity function
             */ 
            this->a = a;
            this->b = b;
            this->c = c;
        }

        // Getters 
        // (setters are not made because it's not
        // supposed that 'a' and 'b' change after defined by
        // the constructor)

        double getA() {
            return this->a;
        }

        double getB() {
            return this->b;
        }

        double getC() {
            return this->c;
        }

        double getGradientVelocity(double x, double y) {
            // TODO: document
            return this->a * x + this->b * y + this->c;
        }

};

class _2DWave {
    /**
     * TODO: document
     */ 
    private:
        double Lx, Ly, tMax, Mx, Ny, w, A, Xp, Yp, Tp; // Entries by the user
        double dx, dy, dt, Ot, R; // Method's internal variables

    public:
        _2DWave (double Lx, 
                double Ly, 
                double tMax, 
                double Mx, 
                double Ny, 
                double w, 
                double A, 
                double Xp, 
                double Yp, 
                double Tp) {
            // TODO: document
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

        RowArrayIJ evaluateFXYT(RowArrayIJ X, RowArrayIJ Y, RowArrayIJ T) {
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
            return this->A * -Tterm.array().exp() * ((1 - 2 * Dterm) * -Dterm.array().exp());

        }

        RowArrayIJ getVelocitiesMatrix(vector<interface> interfaces, vector<velocity> velocities) {
            /** Function that returns the bidimensional velocities matrix of the medium.
             *  For each medium's point that the wave propagates, we calculate a velocity based
             *  on which layer of the medium this point is found.
             * 
             *  Receives:       interfaces - a vector of interface objects
             *                  velocities - a vector of velocity objects, where each object 
             *                               represents the velocity function of its respective layer
             */ 
            // Creating iterators
            vector<interface> :: iterator ifs;
            vector<velocity> :: iterator vls;

            // Instatiating matrix for velocities
            RowArrayIJ v((int) this->Mx, (int) this->Ny);

            double x, y;
            int k = 0;
            // Putting the values on the velocities matrix
            for (int i = 0; i < this->Mx; i++) {
                x = i * this->dx;   // An step in the abscissas
                for (int j = 0; j < this->Ny; j++) {
                    y = j * this->dy;   // An step in the ordinates
                    while (y > interfaces[k].getY(x) && k < interfaces.size() - 1) {
                            k += 1; // Looking for on which layer the point is 
                    }
                    // Calculating the velocity in the point
                    v(i, j) = velocities[k].getGradientVelocity(x, y);
                }
            }

            return v;

        }
};

int main () {

    double Lx = 5.;
    double Ly = 5.;
    double tMax = 30.;
    int Mx = 50;
    int Ny = 50;
    _2DWave w();

    return 0;

}