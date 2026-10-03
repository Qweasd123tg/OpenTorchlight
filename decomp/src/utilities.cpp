#include "EmptyStrings.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "LinuxUtils.h"
#include "MersenneTwister.h"
#include "StringUtilities.h"
#include "Utilities.h"

extern "C" int SDL_SetClipboardText(const char* text);

static MTRand randGen;
static unsigned long g_Rand = GetTickCount();
static unsigned long g_RandVolatile = GetTickCount();

// Multiply-with-carry step: the low half of the state is the value, the high
// half is the carry.
static inline unsigned int nextRandom(unsigned long& state)
{
    state = (state & 0xffffffff) * 0x29777b41 + (state >> 32);
    return (unsigned int)state;
}

// Uniform double in [0, 1): 52 random mantissa bits under the exponent of 1.0.
static inline double randomUnit(unsigned long& state)
{
    unsigned long high = nextRandom(state);
    unsigned long bits = (high << 32) + nextRandom(state);
    bits = (bits & 0x000fffffffffffffUL) | 0x3ff0000000000000UL;
    return *(double*)&bits - 1.0;
}

namespace UTILITIES
{

long long createUniqueGuid()
{
    long long guid;
    do
    {
        guid = ((long long)(unsigned int)randGen.randInt() << 32) +
               ((long long)(unsigned short)randGen.randExc(65536.0) << 16) +
               (unsigned short)randGen.randExc(65536.0);
    } while (guid == -1);
    return guid;
}

int GetDesktopBPP(void* window)
{
    return 32;
}

int getRandState()
{
    return g_Rand;
}

float randomBetween(float minimum, float maximum)
{
    if (maximum == minimum)
        return minimum;
    return minimum + (float)((maximum - minimum) * randomUnit(g_Rand));
}

int randomIntegerBetween(int minimum, int maximum)
{
    if (maximum <= minimum)
        return minimum;
    int value = minimum + nextRandom(g_Rand) % (maximum - minimum + 1);
    if (value > maximum)
        value = maximum;
    return value;
}

float randomBetweenVolatile(float minimum, float maximum)
{
    if (maximum == minimum)
        return minimum;
    return minimum + (float)((maximum - minimum) * randomUnit(g_RandVolatile));
}

int randomIntegerBetweenVolatile(int minimum, int maximum)
{
    if (maximum <= minimum)
        return minimum;
    int value = minimum + nextRandom(g_RandVolatile) % (maximum - minimum + 1);
    if (value > maximum)
        value = maximum;
    return value;
}

void setSeedVolatile(int seed)
{
    g_RandVolatile = seed == 0 ? GetTickCount() : seed;
}

void setSeed(int seed)
{
    g_Rand = seed == 0 ? GetTickCount() : seed;
}

int getAvailableRAM()
{
    return LinuxUtils::GetPhysicalRAMSize();
}

int getProcessorSpeed()
{
    return LinuxUtils::GetCPUFrequency();
}

std::wstring GetEnvironmentVar(std::wstring name)
{
    if (name == L"APPDATA")
        return LinuxUtils::GetHomeDir();
    return L"";
}

double doubleRand()
{
    const double scale = 1.0 / 2147483648.0;
    double value;
    do
    {
        value = ((rand() * scale + rand()) * scale + rand()) * scale;
    } while (value >= 1.0);
    return value;
}

double VerifyDouble(double value, double fallback)
{
    if (isnan(value))
        return 0.0;
    if (finite(value))
        return value;
    return fallback;
}

float VerifyFloat(float value, float fallback)
{
    if (isnan(value))
        return 0.0f;
    if (finite(value))
        return value;
    return fallback;
}

float DecompressNormal(int theta, int phi, unsigned int axis)
{
    double thetaAngle = theta * 2.0 * (3.14159 / 255.0);
    double phiAngle = phi * 2.0 * (3.14159 / 255.0);
    switch (axis)
    {
    case 0:
        return cos(phiAngle) * sin(thetaAngle);
    case 1:
        return sin(phiAngle) * sin(thetaAngle);
    case 2:
        return cos(thetaAngle);
    }
    return 0.0f;
}

void SetClipBoardText(std::wstring text)
{
    SDL_SetClipboardText(STRINGS::StringConvertToUTF8(text).c_str());
}

void ClearQueue(std::queue<std::wstring>& queue)
{
    while (!queue.empty())
        queue.pop();
}

void ClearQueue(std::queue<std::string>& queue)
{
    while (!queue.empty())
        queue.pop();
}

}
