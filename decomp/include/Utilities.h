#ifndef UTILITIES_H
#define UTILITIES_H

#include <queue>
#include <string>

namespace UTILITIES
{
    int GetDesktopBPP(void* window);
    int getRandState();
    float randomBetween(float minimum, float maximum);
    int randomIntegerBetween(int minimum, int maximum);
    float randomBetweenVolatile(float minimum, float maximum);
    int randomIntegerBetweenVolatile(int minimum, int maximum);
    void setSeedVolatile(int seed);
    void setSeed(int seed);
    int getAvailableRAM();
    int getProcessorSpeed();
    std::wstring GetEnvironmentVar(std::wstring name);
    double doubleRand();
    double VerifyDouble(double value, double fallback);
    float VerifyFloat(float value, float fallback);
    float DecompressNormal(int theta, int phi, unsigned int axis);
    void SetClipBoardText(std::wstring text);
    void ClearQueue(std::queue<std::wstring>& queue);
    void ClearQueue(std::queue<std::string>& queue);
    long long createUniqueGuid();
}

#endif
