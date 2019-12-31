#include "velocity.h"

/** velocity.cpp
 * Layers' velocity's class
 */

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

/** Function for serialization of velocity objects
 *  Receives:       ofstream object - file that will receive the data
 *                                   of the this velocity object
 */
void velocity::serialize(ofstream *file) {
    if((*file).is_open()) {
        double data[3]; // for writing attributes of the class
                        // in the file
        data[0] = this->a; data[1] = this->b; data[2] = this->c;
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
void velocity::deserialize(ifstream *file) {
    if((*file).is_open()) {
        double data[3];
        (*file).read((char *) &data, sizeof(data));
        this->a = data[0]; this->b = data[1]; this->c = data[2];
    } else {
        printf("The file isn't open.\nAborting...");
        // exit(1);
    }
}
