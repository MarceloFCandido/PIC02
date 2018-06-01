#include "medium.h"

medium::medium(double Lx, double Ly, double tMax, double Mx, double Ny) {
    this->Lx = Lx;
    this->Ly = Ly;
    this->tMax = tMax;
    this->Mx = Mx;
    this->Ny = Ny;
}

double medium::getLx() {
    return this->Lx;
}

void medium::setLx(double Lx) {
    this->Lx = Lx;
}

double medium::getLy() {
    return this->Ly;
}

void medium::setLy(double Ly) {
    this->Ly = Ly;
}

double medium::getTMax() {
    return this->tMax;
}

void medium::setTMax(double tMax) {
    this->tMax = tMax;
}

double medium::getMx() {
    return this->Mx;
}

void medium::setMx(double Mx) {
    this->Mx = Mx;
}

double medium::getNy() {
    return this->Ny;
}

void medium::setNy(double Ny) {
    this->Ny = Ny;
}
