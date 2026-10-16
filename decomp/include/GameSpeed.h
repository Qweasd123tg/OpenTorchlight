#ifndef GAMESPEED_H
#define GAMESPEED_H

#include <string>

#include "GameEnums.h"
#include "Graph.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CGameSpeed : public CRunicCore
{
public:
    class CSpeedInstance : public CRunicCore
    {
    public:
        virtual ~CSpeedInstance();
        EGAMESPEED_TYPE m_type;
        float m_duration;
        float m_elapsed;
        CGraph* m_graph;
        float m_scale;
    };

    virtual ~CGameSpeed();

    static CGameSpeed* getSingleton();

    float getGameSpeed();
    void calculateGameSpeed(float fDeltaTime);
    static void addSpeedModifier(EGAMESPEED_TYPE eType, float fSpeed, float fWeight);
    void clear();

    CGameSpeed(std::wstring graphName1, std::wstring graphName2);

    float m_fGameSpeed;
    unsigned char m_abReserved14[4] __attribute__((aligned(4)));

    CGraph* m_pGraph1;
    CGraph* m_pGraph2;

    TArrayList<CSpeedInstance*> m_lSpeedModifiers;
};

#endif
