#ifndef GRAVITYWRAPPER_H
#define GRAVITYWRAPPER_H

#include "AffectorWrapper.h"

class CResourceManager;

class CGravityWrapper : public CAffectorWrapper
{
public:
    virtual ~CGravityWrapper();
    CGravityWrapper(CResourceManager *pResourceManager);

    unsigned char m_trailingPadding[6];
};

#endif
