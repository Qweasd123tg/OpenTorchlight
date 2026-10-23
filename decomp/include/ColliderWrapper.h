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

    bool m_bCollider11A;
} __attribute__((aligned(8)));

#endif
