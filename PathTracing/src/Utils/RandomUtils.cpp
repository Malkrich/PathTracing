#include "RandomUtils.h"

namespace PathTracing
{

namespace Utils
{

double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

int random_int(double min,double max)
{ // Returns a random int in [min,max].
    double random = random_double(min,max+1);
    int res = static_cast<int>(random);
    return res;
}

}

}
