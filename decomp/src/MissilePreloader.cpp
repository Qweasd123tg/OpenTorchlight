#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "MissilePreloader.h"
#include "Missile.h"
#include "PositionableObject.h"
#include "ResourceSettings.h"
#include "RunicCore.h"
#include "StringUtilities.h"
#include "TArrayList.h"
#include "iMissile.h"

CMissilePreloader* CMissilePreloader::getSinglelton()
{
    return (CMissilePreloader*)g_MissilePreloader;
}

void CMissilePreloader::notifyOfDeletion(iMissile* pMissile, CPositionableObject* pObject)
{
    for (unsigned int i = 0; i < m_activeMissiles.size(); i++)
    {
        CMissile* pActiveMissile = m_activeMissiles[i];

        CPositionableObject** ppTarget = reinterpret_cast<CPositionableObject**>(
            reinterpret_cast<char*>(pActiveMissile) + 0x230);
        if (*ppTarget == pObject)
            pActiveMissile->setTarget(NULL);

        if (pMissile != NULL)
        {
            TArrayList<iMissile*>* pMissiles = reinterpret_cast<TArrayList<iMissile*>*>(
                reinterpret_cast<char*>(pActiveMissile) + 0x1c8);
            pMissiles->remove(pMissile);
        }
    }
}

CMissilePreloader::CMissilePreloader(CResourceSettings* pResourceSettings)
    : CRunicCore(),
      m_pResourceSettings(pResourceSettings),
      m_pResourceManager(NULL),
      m_activeMissiles(10)
{
    g_MissilePreloader = (long)this;
}

void CMissilePreloader::clear()
{
    clearCachedMissiles();
    for (std::map<std::wstring, CMissile*>::iterator i = m_missilesToLoad.begin(); i != m_missilesToLoad.end(); ++i)
    {
        if (i->second)
        {
            delete i->second;
            i->second = NULL;
        }
    }
    m_missilesToLoad.clear();
}

CMissilePreloader::~CMissilePreloader()
{
    clear();
    if (m_pResourceManager != NULL)
    {
        delete m_pResourceManager;
        m_pResourceManager = NULL;
    }
    g_MissilePreloader = NULL;
}

CMissile* CMissilePreloader::getMissileRef(const std::wstring& missileName)
{
    if (getSinglelton() == NULL)
        return NULL;

    std::map<std::wstring, CMissile*>::iterator i;
    {
        std::wstring name = STRINGS::StringUpper(missileName);
        i = getSinglelton()->m_missilesToLoad.find(name);
    }
    if (i != getSinglelton()->m_missilesToLoad.end())
        return i->second;
    return NULL;
}

void CMissilePreloader::updateMissiles(float deltaTime)
{
    for (unsigned int i = 0; i < m_activeMissiles.size(); ++i) {
        CMissile* pMissile = m_activeMissiles[i];
        if (!pMissile->update(deltaTime)) {
            m_activeMissiles.removeAt(i);
            cacheMissile(pMissile);
            --i;
        }
    }
}

void CMissilePreloader::getMissileNames(TArrayList<std::wstring>& missileNames)
{
    for (std::map<std::wstring, CMissile*>::iterator i = m_missilesToLoad.begin();
         i != m_missilesToLoad.end(); ++i)
        missileNames.add(i->first);
}
