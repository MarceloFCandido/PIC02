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


        // TODO: Create getters for the entries

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

};
