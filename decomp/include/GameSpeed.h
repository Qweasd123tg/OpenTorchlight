#ifndef GAMESPEED_H
#define GAMESPEED_H

#include <string>

#include "GameEnums.h"
#include "Graph.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CGameSpeedModifier;

class CGameSpeed : public CRunicCore
{
public:
    virtual ~CGameSpeed();

    static CGameSpeed* getSingleton();

    float getGameSpeed() const;
    void calculateGameSpeed(float fDeltaTime);
    void addSpeedModifier(EGAMESPEED_TYPE eType, float fSpeed, float fWeight);
    void clear();

    CGameSpeed(std::wstring graphName1, std::wstring graphName2);

    float m_fGameSpeed;
    unsigned char m_abReserved14[4] __attribute__((aligned(4)));

    CGraph* m_pGraph1;
    CGraph* m_pGraph2;

    TArrayList<CGameSpeedModifier*> m_lSpeedModifiers;
};

#endif
