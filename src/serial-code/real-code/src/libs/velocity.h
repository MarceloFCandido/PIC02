#include <fstream>

using namespace std;

/** velocity.h
 * 

class velocity {
    /**
     * Defines velocity as a quadractic function of the form
     *                  v(x, y) = ax + by + c
     */
    private:
        double a, b, c;

    public:
        velocity(double a, double b, double c);

        // Getters
        // (setters are not made because it's not
        // supposed that 'a' and 'b' change after defined by
        // the constructor)
        double getA();

        double getB();

        double getC();

        // TODO: document
        double getGradientVelocity(double x, double y);

        void serialize(ofstream *file);

        void deserialize(ifstream *file);

};
