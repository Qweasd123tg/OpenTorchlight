#ifndef SINEFORCEWRAPPER_H
#define SINEFORCEWRAPPER_H

#include "ForceWrapper.h"
#include "ResourceManager.h"

class CSineForceWrapper : public CForceWrapper
{
public:
    virtual ~CSineForceWrapper();
    CSineForceWrapper(CResourceManager*);
};

#endif
