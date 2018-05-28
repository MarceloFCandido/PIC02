#include "velocity.h"

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

        // TODO: document
        double getGradientVelocity(double x, double y) {
            return this->a * x + this->b * y + this->c;
        }

};
