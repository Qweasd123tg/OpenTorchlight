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

void CSteamStats::statModified(ESTATS stat, UNIONDATA32BIT value)
{
    for (unsigned int i = 0; i < m_pendingStatChanges.size(); ++i) {
        if (m_pendingStatChanges[i].stat == stat) {
            return;
        }
    }

    SStatChange change = { stat, value };
    m_pendingStatChanges.add(change);
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
