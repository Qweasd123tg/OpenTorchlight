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

#include "FileSystem.h"

void CMissilePreloader::clearCachedMissiles()
{
    m_activeMissiles.deleteAll();
    for (std::map<std::wstring,TArrayList<CMissile*>*>::iterator it = m_cachedMissiles.begin(); it != m_cachedMissiles.end(); ++it) {
        if (it->second) {
            it->second->deleteAll();
            if (it->second) {
                delete it->second;
                it->second = NULL;
            }
        }
    }
    m_cachedMissiles.clear();
}

void CMissilePreloader::reloadMissiles()
{
    if (!m_pResourceManager)
        m_pResourceManager = new CResourceManager(NULL);
    clear();
    TArrayList<std::wstring> files(25);
    const std::wstring& directory = m_pResourceSettings->GetString(KRESOURCESETTING_S_MISSILE_FOLDER);
    CFileSystem::getSingleton()->getFileList(directory, files, L"*.layout", true, true, false, false);
    for (unsigned int i = 0; i < files.size(); ++i)
        loadMissile(files[i]);
}

CMissile* CMissilePreloader::createNewMissileRef(CResourceManager* resources, const std::wstring& filename)
{
    if (!getSinglelton())
        return NULL;
    std::wstring name = STRINGS::StringUpper(filename);
    std::map<std::wstring,TArrayList<CMissile*>*>::iterator cached = m_cachedMissiles.find(name);
    if (cached != m_cachedMissiles.end() && cached->second->size()) {
        CMissile* missile = (*cached->second)[0];
        cached->second->removeAt(0);
        missile->setResourceManager(resources);
        m_activeMissiles.add(missile);
        missile->resetMissile();
        return missile;
    }
    std::map<std::wstring,CMissile*>::iterator original = getSinglelton()->m_missilesToLoad.find(name);
    if (original == getSinglelton()->m_missilesToLoad.end())
        return NULL;
    CMissile* missile = new CMissile(resources, original->second);
    if (cached == m_cachedMissiles.end())
        m_cachedMissiles[name] = new TArrayList<CMissile*>(10);
    m_activeMissiles.add(missile);
    return missile;
}

void CMissilePreloader::cacheMissile(CMissile* missile)
{
    if (!missile)
        return;
    missile->setVisible(false);
    std::map<std::wstring,TArrayList<CMissile*>*>::iterator found = m_cachedMissiles.find(std::wstring(missile->m_sMissileName));
    if (found != m_cachedMissiles.end() && found->second) {
        found->second->add(missile);
        return;
    }
    TArrayList<CMissile*>* list = new TArrayList<CMissile*>(10);
    m_cachedMissiles[std::wstring(missile->m_sMissileName)] = list;
    cacheMissile(missile);
}

#include "Layout.h"
#include "Descriptor.h"
#include <OgreLogManager.h>

void CMissilePreloader::loadMissile(const std::wstring& layoutName)
{
    CLayout layout(m_pResourceManager, static_cast<ELAYOUT_TYPES>(0));
    layout.loadLayoutFile(layoutName, true, NULL, false, false, 0);
    TArrayList<CEditorBaseObject*>* objects = layout.GetObjectsCreatedByADescriptor(L"Missile");
    if (objects && objects->size()) {
        for (unsigned int i = 0; i < objects->size(); ++i) {
            CEditorBaseObject* object = (*objects)[i];
            if (!object)
                continue;
            CMissile* missile = dynamic_cast<CMissile*>(object);
            if (!missile)
                continue;
            std::wstring name = missile->m_sMissileName;
            if (name == EMPTY_WSTRING)
                continue;
            if (m_missilesToLoad.find(name) == m_missilesToLoad.end()) {
                missile->getDescriptor()->getSceneOwner()->RemoveObjectInScene(missile);
                m_missilesToLoad[STRINGS::StringUpper(std::wstring(missile->m_sMissileName))] = missile;
            } else {
                std::string message = "The missile with name: " +
                    STRINGS::StringConvertToNarrow(std::wstring(missile->m_sMissileName).c_str()) +
                    "\n is already created. This missile will not load from location : " +
                    STRINGS::StringConvertToNarrow(layoutName.c_str());
                Ogre::LogManager::getSingleton().logMessage(message.c_str(), Ogre::LML_CRITICAL, false);
            }
        }
    }
}
