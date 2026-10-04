#ifndef COLORWRAPPER_H
#define COLORWRAPPER_H

#include "AffectorWrapper.h"
#include "TArrayList.h"

class CResourceManager;

class CColorWrapper : public CAffectorWrapper
{
public:
    virtual ~CColorWrapper();

    void setColors(const float* colors, unsigned int numberOfColors);
    float* getColors(unsigned int& numberOfColors);

    explicit CColorWrapper(CResourceManager* resourceManager);

    unsigned char m_reserved11A[0x6];
    TArrayList<float> m_colors;
};

#endif
