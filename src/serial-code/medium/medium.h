
class medium {
private:
    double Lx, Ly, tMax, Mx, Ny;

public:
    medium(double Lx, double Ly, double tMax, double Mx, double Ny);
    virtual ~medium();

    // Getters and setters
    void setLx(double Lx);
    double getLx();

    void setLy(double Ly);
    double getLy();

    void setTMax(double tMax);
    double getTMax();

    void setMx(double Mx);
    double getMx();

    void setNy(double Ny);
    double getNy();

};
