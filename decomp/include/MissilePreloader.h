#ifndef MISSILEPRELOADER_H
#define MISSILEPRELOADER_H

#include <map>
#include <string>

#include "RunicCore.h"
#include "TArrayList.h"

class CMissile;
class CPositionableObject;
class CResourceManager;
class CResourceSettings;
class iMissile;

class CMissilePreloader : public CRunicCore
{
public:
    virtual ~CMissilePreloader();

    CMissilePreloader* getSinglelton();
    void notifyOfDeletion(iMissile* pMissile, CPositionableObject* pObject);

    CMissilePreloader(CResourceSettings* pResourceSettings);

    void clearCachedMissiles();
    void clear();
    void getMissileNames(TArrayList<std::wstring>& missileNames);
    CMissile* getMissileRef(const std::wstring& missileName);
    void loadMissile(const std::wstring& layoutName);
    void reloadMissiles();
    CMissile* createNewMissileRef(CResourceManager* pResourceManager,
                                   const std::wstring& missileName);
    void cacheMissile(CMissile* pMissile);
    void updateMissiles(float deltaTime);

    CResourceSettings* m_pResourceSettings;
    std::map<std::wstring, CMissile*> m_missilesToLoad;
    std::map<std::wstring, TArrayList<CMissile*>*> m_cachedMissiles;
    CResourceManager* m_pResourceManager;
    TArrayList<CMissile*> m_activeMissiles;
};

#endif
