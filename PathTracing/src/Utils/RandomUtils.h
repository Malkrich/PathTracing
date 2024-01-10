#ifndef RANDOMUTILS_H
#define RANDOMUTILS_H

#include <cstdlib>

namespace PathTracing
{

double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

}

#endif // RANDOMUTILS_H
