#ifndef COLLIDERWRAPPER_H
#define COLLIDERWRAPPER_H

#include <string>

#include "AffectorWrapper.h"

class CResourceManager;

class CColliderWrapper : public CAffectorWrapper
{
public:
    virtual ~CColliderWrapper();
    CColliderWrapper(CResourceManager*, std::string);

    unsigned char m_padding11A[6];
};

#endif
