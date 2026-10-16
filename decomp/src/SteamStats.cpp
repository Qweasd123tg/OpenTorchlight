#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "SteamStats.h"
#include "iStatListener.h"
#include "Player.h"

void CSteamStats::update(float elapsedTime)
{
}

void CSteamStats::forceStatsToSave()
{
}

void CSteamStats::setStatInt(ESTATS stat, unsigned int value)
{
}

void CSteamStats::incrementStat(ESTATS stat, int amount)
{
}

void CSteamStats::setStatFloat(ESTATS stat, float value)
{
}

bool CSteamStats::StoreStats()
{
    return false;
}

float CSteamStats::getPlayerStatFloat(ESTATS stat)
{
    return -1.0f;
}

void CSteamStats::addStatListener(ESTATS stat, iStatListener* listener)
{
    TStatListenerMap::iterator i = m_statListeners.find(stat);
    if (i != m_statListeners.end())
        i->second->add(listener);
}

void CSteamStats::reloadPlayerData(CPlayer* player)
{
    m_pPlayer = player;
    if (player == NULL)
        return;

    for (unsigned int i = 0; i < 31; ++i)
    {
        const unsigned char* definition = g_strStatDefines + i * 24;
        if (*reinterpret_cast<const int*>(definition) == -1)
        {
            if (*reinterpret_cast<const int*>(definition + 4) == 0)
            {
                m_statValues[i] = -1;
                if (m_pPlayer != NULL)
                {
                    if (i == 28)
                        m_statValues[i] = static_cast<int>(
                            reinterpret_cast<unsigned long>(m_pPlayer->getLevel()));
                    else if (i == 29)
                        m_statValues[i] = m_pPlayer->getGold();
                }
            }
            else if (*reinterpret_cast<const int*>(definition + 4) == 1)
                m_statValues[i] = -1.0f;
        }
    }
}

CSteamStats* CSteamStats::getSingleton()
{
    return (CSteamStats*)m_gStatsObject;
}

void CSteamStats::checkForLocalUpdates(float elapsedTime)
{
    m_fLocalUpdateTimer -= elapsedTime;
    if (m_bLocalUpdatesEnabled && !m_bStatsEnabled && m_pPlayer != NULL &&
        m_pendingStatChanges.size() == 0 && m_fLocalUpdateTimer <= 0.0f) {
        m_fLocalUpdateTimer = 0.5f;
        for (unsigned int i = 0; i < 31; ++i) {
            const unsigned char* definition = g_strStatDefines + i * 24;
            if (*reinterpret_cast<const int*>(definition) != -1)
                continue;
            if (*reinterpret_cast<const int*>(definition + 4) == 0) {
                if (m_statValues[i] != getPlayerStatInt(static_cast<ESTATS>(i))) {
                    UNIONDATA32BIT old;
                    old.m_iValue = m_statValues[i];
                    m_statValues[i] = getPlayerStatInt(static_cast<ESTATS>(i));
                    statModified(static_cast<ESTATS>(i), old);
                }
            } else if (*reinterpret_cast<const int*>(definition + 4) == 1) {
                UNIONDATA32BIT current;
                current.m_iValue = m_statValues[i];
                if (current.m_fValue != getPlayerStatFloat(static_cast<ESTATS>(i))) {
                    UNIONDATA32BIT old;
                    old.m_iValue = m_statValues[i];
                    current.m_fValue = getPlayerStatFloat(static_cast<ESTATS>(i));
                    m_statValues[i] = current.m_iValue;
                    statModified(static_cast<ESTATS>(i), old);
                }
            }
        }
        if (m_pendingStatChanges.size() != 0)
            updateStatListeners();
    }
}

struct StatDefinition
{
    int serviceID;
    int type;
    unsigned char rest[16];
};

int CSteamStats::getStatInt(ESTATS stat)
{
    if (static_cast<unsigned int>(stat) <= 30 &&
        reinterpret_cast<const StatDefinition*>(g_strStatDefines)[stat].type == 0)
        return m_statValues[stat];
    return -1;
}

float CSteamStats::getStatFloat(ESTATS stat)
{
    if (static_cast<unsigned int>(stat) < m_statValues.size() &&
        reinterpret_cast<const StatDefinition*>(g_strStatDefines)[stat].type == 1)
    {
        UNIONDATA32BIT value;
        value.m_iValue = m_statValues[stat];
        return value.m_fValue;
    }
    return -1.0f;
}

int CSteamStats::getPlayerStatInt(ESTATS stat)
{
    int value = -1;
    if (m_pPlayer != NULL)
    {
        if (stat == static_cast<ESTATS>(28))
            value = m_pPlayer->m_journalStats[5];
        else if (stat == static_cast<ESTATS>(29))
            value = m_pPlayer->getGold();
    }
    return value;
}

void CSteamStats::statModified(ESTATS stat, UNIONDATA32BIT value)
{
    for (unsigned int i = 0; i < m_pendingStatChanges.size(); ++i) {
        if (m_pendingStatChanges[i].stat == stat) {
            return;
        }
    }

    SStatChange change;
    change.stat = stat;
    change.value = value;
    m_pendingStatChanges.add(change);
}
