#ifndef ALIGNWRAPPER_H
#define ALIGNWRAPPER_H

#include "AffectorWrapper.h"
#include "ResourceManager.h"

class CAlignWrapper : public CAffectorWrapper
{
public:
    virtual ~CAlignWrapper();
    CAlignWrapper(CResourceManager* resourceManager);

    unsigned char m_unknown11A[6];
};

#endif
