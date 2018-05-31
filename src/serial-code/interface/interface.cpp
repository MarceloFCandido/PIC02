
#include "interface.h"

interface::interface(double a, double b) {
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
double interface::getA() {
    return this->a;
};

double interface::getB() {
    return this->b;
};

// The interface was imaginated like a linear function:
//                      y = ax + b
// So, to get a the height of an point (the y coordinate)
// in the interface, we just give a point x to it
double interface::getY(double x) {
    /**
     * Function definition
     * Receives:    x - point's coordinate in the abscissas
     * Returns:     y - point's coordinate in the ordinates
     */
    return this->a * x + this->b;
}

/** Function for serialization of interface objects
 *  Receives:       ofstrem object - file that will receive the data
 *                                   of the this interface object
 */
void interface::serialize(/*std::*/ofstream *file) {
    if((*file).is_open()) {
        // RowArrayIJ data(1, 2);  // for put the data for the file
        // data(0, 0) = this->a; data(0, 1) = this->b;
        double data[2]; // for writing attributes of the class
                        // in the file
        data[0] = this->a; data[1] = this->b;
        (*file).write((char *) &data, sizeof(data));
    } else {
        printf("Error: The file isn't open.\nAborting...");
        // exit(1);
    }
}

/** Function for deserialization of interface objects
 *  Receives:       ifstrem object - file that will supply the data
 *                                   for the this interface object
 */
void interface::deserialize(/*std::*/ifstream *file) {
    if((*file).is_open()) {
        double data[2];
        (*file).read((char *) &data, sizeof(data));
        this->a = data[0]; this->b = data[1];
    } else {
        printf("The file isn't open.\nAborting...");
        // exit(1);
    }
}
