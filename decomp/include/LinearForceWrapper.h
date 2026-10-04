#ifndef LINEARFORCEWRAPPER_H
#define LINEARFORCEWRAPPER_H

#include "ForceWrapper.h"
#include "ResourceManager.h"

class CLinearForceWrapper : public CForceWrapper
{
public:
    virtual ~CLinearForceWrapper();
    CLinearForceWrapper(CResourceManager *resourceManager);
};

#endif
