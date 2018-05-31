
#include "velocity.h"

velocity::velocity(double a, double b, double c) {
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

double velocity::getA() {
    return this->a;
}

double velocity::getB() {
    return this->b;
}

double velocity::getC() {
    return this->c;
}

// TODO: document
double velocity::getGradientVelocity(double x, double y) {
    return this->a * x + this->b * y + this->c;
}
