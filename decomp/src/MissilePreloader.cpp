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
    if (g_MissilePreloader == 0)
        return 0;

    std::wstring upperMissileName = STRINGS::StringUpper(missileName);
    std::map<std::wstring, CMissile*>::iterator it =
        this->m_missilesToLoad.lower_bound(upperMissileName);

    if (it != this->m_missilesToLoad.end())
        return it->second;

    return 0;
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
