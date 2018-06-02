#include "../util/util.h"
#include "../interface/interface.h"
#include "../velocity/velocity.h"

class _2DWave {
    /**
     * TODO: document
     */
    private:
        double Lx, Ly, tMax, Mx, Ny, w, A, Xp, Yp, Tp; // Entries by the user
        double dx, dy, dt, Ot, R; // Method's internal variables

    public:
        // TODO: document
        _2DWave (double Lx,
                double Ly,
                double tMax,
                double Mx,
                double Ny,
                double w,
                double A,
                double Xp,
                double Yp,
                double Tp);

        double getLx();
        void setLx(double Lx);
        double getLy();
        void setLy(double Ly);
        double getTMax();
        void setTMax(double tMax);
        double getMx();
        void setMx(double Mx);
        double getNy();
        void setNy(double Ny);
        double getW();
        void setW(double w);
        double getA();
        void setA(double A);
        double getXp();
        void setXp(double Xp);
        double getYp();
        void setYp(double Yp);
        double getTp();
        void setTp(double Tp);

        /**
         * Function that returns a bidimensional velocities array.
         * TODO: document
        */
        RowArrayIJ evaluateFXYT(RowArrayIJ X, RowArrayIJ Y, RowArrayIJ T);

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
        RowArrayIJ getVelocitiesMatrix(vector<interface> interfaces,
            vector<velocity> velocities);

        void serialize(ofstream *file);

        void deserialize(ifstream *file);
};
