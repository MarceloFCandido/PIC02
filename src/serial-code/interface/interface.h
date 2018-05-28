#include <fstream>
#include <vector>
#include <Eigen/Dense>

class interface {
    /**
     * Defines an interface as a linear function
     */

    private:
        double a, b;

    public:
        interface(double a, double b);

        // Getters
        // (setters are not made because it's not
        // supposed that 'a' and 'b' change after defined by
        // the constructor)
        double getA();

        double getB();

        // The interface was imaginated like a linear function:
        //                      y = ax + b
        // So, to get a the height of an point (the y coordinate)
        // in the interface, we just give a point x to it
        double getY(double x);

        /** Function for serialization of interface objects
         *  Receives:       ofstrem object - file that will receive the data
         *                                   of the this interface object
         */
        void serialize(ofstream *file);

        /** Function for deserialization of interface objects
         *  Receives:       ifstrem object - file that will supply the data
         *                                   for the this interface object
         */
        void deserialize(ifstream *file);
};
