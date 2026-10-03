#ifndef UTILITIES_H
#define UTILITIES_H

// Partial: declarations from utilities.cpp used by recovered TUs.
namespace UTILITIES
{
    float randomBetween(float minimum, float maximum);
    float randomBetweenVolatile(float minimum, float maximum);
    int randomIntegerBetweenVolatile(int minimum, int maximum);
    long long createUniqueGuid();
    void setSeed(int seed);
}

#endif
