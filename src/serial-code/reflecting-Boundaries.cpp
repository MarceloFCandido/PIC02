# include <iostream>
# include <cmath>
# include <Eigen/Dense>
# include <list>
# include <map>

using namespace std;

# define PI 3.141592653589793238463

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

};

class Onda2D {
    private:
        double Lx, Ly, tMax, Mx, Ny, w, A, Xp, Yp, Tp; // Entries by the user
        double dx, dy, dt, Ot, R; // Method's internal variables

    public:
        Onda2D (double Lx, 
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

        double evaluateFXYT() {

        }
};

// Defining my own Array type object
// TODO: citar fonte
typedef Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RowArrayIJ;

/*
 *    This program aims to solve the bidimensional wave equation 
 *    by the finite differences method. This methods will be im-
 *    plemented with the help of Eigen library, that provides the
 *    necessary tools of the Linear Algebra, mainly the vectors 
 *    and matrices thats will be used to store and manipulate data, 
 *    as well the methods that are necessary to this.
 */

int main () {

    RowArrayIJ a(10, 10);

    cout << a;

    return 0;

}