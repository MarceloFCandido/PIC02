# include <iostream>
# include <Eigen/Dense>
# include <list>
# include <map>

using namespace std;

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

// typedef Eigen::Matrix<int, Eigen::Dynamic, 
//     Eigen::Dynamic, Eigen::RowMajor> RowMatrixXi;

/*
 *    This program aims to solve the bidimensional wave equation 
 *    by the finite differences method. This methods will be im-
 *    plemented with the help of Eigen library, that provides the
 *    necessary tools of the Linear Algebra, mainly the vectors 
 *    and matrices thats will be used to store and manipulate data, 
 *    as well the methods that are necessary to this.
 */

int main () {

    interface i1(1.0, 1.0);
    velocity v1(1.0, 1.0, 1.0);

    cout << i1.getA() << endl;
    cout << i1.getB() << endl;
    cout << v1.getA() << endl;
    cout << v1.getB() << endl;
    cout << v1.getC() << endl;

    return 0;

}