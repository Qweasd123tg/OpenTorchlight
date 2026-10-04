#ifndef UNITTHEMEPARTICLE_H
#define UNITTHEMEPARTICLE_H

#include <string>

#include "DataGroup.h"
#include "RunicCore.h"

class CUnitThemeParticle : public CRunicCore
{
public:
    virtual ~CUnitThemeParticle();

    void load(CDataGroup *pDataGroup);

    std::wstring m_wstrFile;
    int m_iUnitTypeID;
    int m_iCount;
    bool m_bAttaches;
    bool m_bFollows;
    std::wstring m_wstrBone;
};

#endif
