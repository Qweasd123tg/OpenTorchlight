#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "GameSpeed.h"
#include "Graph.h"
#include "RunicCore.h"

CGameSpeed* CGameSpeed::getSingleton()
{
    return static_cast<CGameSpeed*>(g_pGameSpeed);
}

void CGameSpeed::clear()
{
    CGameSpeed* pGameSpeed = static_cast<CGameSpeed*>(g_pGameSpeed);
    if (pGameSpeed) {
        for (unsigned int i = 0; i < pGameSpeed->m_lSpeedModifiers.size(); ++i) {
            CGameSpeedModifier* modifier =
                static_cast<CGameSpeedModifier*>(pGameSpeed->m_lSpeedModifiers[i]);
            delete modifier;
        }
        pGameSpeed->m_lSpeedModifiers.clear();
    }
}

CGameSpeed::CGameSpeed(std::wstring graphName1, std::wstring graphName2)
    : CRunicCore(),
      m_fGameSpeed(1.0f),
      m_lSpeedModifiers(10)
{
    if (g_pGameSpeed == NULL)
    {
        g_pGameSpeed = this;
        m_pGraph1 = new CGraph(graphName1);
        m_pGraph2 = new CGraph(graphName2);
    }
}
