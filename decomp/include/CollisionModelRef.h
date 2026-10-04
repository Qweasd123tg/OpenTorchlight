#ifndef COLLISIONMODELREF_H
#define COLLISIONMODELREF_H

#ifndef _GLIBCXX_USE_CXX11_ABI
#define _GLIBCXX_USE_CXX11_ABI 0
#endif

#include <string>
#include "RunicCore.h"

class CollisionModel;

class CollisionModelRef : public CRunicCore
{
public:
    virtual ~CollisionModelRef();
    CollisionModelRef();

    CollisionModel* m_pCollisionModel;
    unsigned char m_Padding18[8] __attribute__((aligned(8)));
    std::wstring m_sUnknown20;
};

#endif
