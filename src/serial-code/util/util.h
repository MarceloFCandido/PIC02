#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <limits>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

#define PI 3.141592653589793238463

// Defining my own Array type object
// TODO: citar fonte
typedef Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic,
    Eigen::RowMajor> RowArrayIJ;
