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
    CGameSpeed* speed = static_cast<CGameSpeed*>(g_pGameSpeed);
    if (speed)
        speed->m_lSpeedModifiers.deleteAll();
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

float CGameSpeed::getGameSpeed()
{
    CGameSpeed* speed = static_cast<CGameSpeed*>(g_pGameSpeed);
    if (speed)
        return speed->m_fGameSpeed;
    return 1.0f;
}

void CGameSpeed::calculateGameSpeed(float delta)
{
    if (!g_pGameSpeed)
        return;
    static_cast<CGameSpeed*>(g_pGameSpeed)->m_fGameSpeed = 1.0f;
    float count = 1.0f;
    for (unsigned int i = 0; i < static_cast<CGameSpeed*>(g_pGameSpeed)->m_lSpeedModifiers.size(); ++i)
    {
        CSpeedInstance* speed = static_cast<CGameSpeed*>(g_pGameSpeed)->m_lSpeedModifiers[i];
        speed->m_elapsed += delta;
        if (speed->m_elapsed >= speed->m_duration)
        {
            static_cast<CGameSpeed*>(g_pGameSpeed)->m_lSpeedModifiers.removeAt(i);
            delete speed;
        }
        else
        {
            count += 1.0f;
            if (speed->m_type == 0)
                static_cast<CGameSpeed*>(g_pGameSpeed)->m_fGameSpeed += std::max(0.0f, 1.0f - speed->m_graph->getValue(speed->m_elapsed / speed->m_duration, 0) * speed->m_scale);
            else if (speed->m_type == 1)
                static_cast<CGameSpeed*>(g_pGameSpeed)->m_fGameSpeed += 1.0f + std::max(0.0f, speed->m_graph->getValue(speed->m_elapsed / speed->m_duration, 0) * speed->m_scale);
        }
    }
    static_cast<CGameSpeed*>(g_pGameSpeed)->m_fGameSpeed /= count;
}

void CGameSpeed::addSpeedModifier(EGAMESPEED_TYPE type, float duration, float scale)
{
    if (g_pGameSpeed)
    {
        CSpeedInstance* speed = new CSpeedInstance();
        speed->m_type = type;
        speed->m_duration = duration;
        speed->m_elapsed = 0.0f;
        speed->m_scale = scale;
        if (type == 0)
            speed->m_graph = static_cast<CGameSpeed*>(g_pGameSpeed)->m_pGraph1;
        else if (type == 1)
            speed->m_graph = static_cast<CGameSpeed*>(g_pGameSpeed)->m_pGraph2;
        static_cast<CGameSpeed*>(g_pGameSpeed)->m_lSpeedModifiers.add(speed);
    }
}

CGameSpeed::~CGameSpeed()
{
    if (m_pGraph1) { delete m_pGraph1; m_pGraph1 = 0; }
    if (m_pGraph2) { delete m_pGraph2; m_pGraph2 = 0; }
    m_lSpeedModifiers.deleteAll();
    g_pGameSpeed = 0;
}
