#ifndef COLLISIONMODELREF_H
#define COLLISIONMODELREF_H

#ifndef _GLIBCXX_USE_CXX11_ABI
#define _GLIBCXX_USE_CXX11_ABI 0
#endif

#include <string>
#include "RunicCore.h"

class CCollisionModel;

class CollisionModelRef : public CRunicCore
{
public:
    virtual ~CollisionModelRef();
    CollisionModelRef();

    CCollisionModel* m_pCollisionModel;
    int m_referenceCount;
    unsigned char m_gap1c[4];
    std::wstring m_sUnknown20;
};

#endif
