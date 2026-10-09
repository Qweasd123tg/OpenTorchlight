#include "EmptyStrings.h"
#include "ResourceManager.h"

CResourceManager::~CResourceManager()
{
    m_pSceneManager = NULL;
    m_pLevel = NULL;
    m_pHierarchy = NULL;
}

#include "Editor.h"
#include "MissilePreloader.h"
#include "OgreTextureManager.h"
#include "UnitResourceList.h"
#include <map>
#include <string>
#include "CameraControl.h"
#include "DungeonManager.h"
#include "GameUI.h"
#include "Hierarchy.h"

bool CResourceManager::ISA(UNITTYPES::EUNITTYPES type, UNITTYPES::EUNITTYPES parent)
{
    if (m_pHierarchy)
        return m_pHierarchy->ISA(type, parent);
    return false;
}

UNITTYPES::EUNITTYPES CResourceManager::getUnitTypeByName(const std::wstring& name)
{
    if (m_pHierarchy)
    {
        UNITTYPES::EUNITTYPES type = m_pHierarchy->getTypeIDByName(name);
        if (type != static_cast<UNITTYPES::EUNITTYPES>(-1))
            return type;
    }
    return static_cast<UNITTYPES::EUNITTYPES>(22);
}

CDungeonManager* CResourceManager::getDungeonManager()
{
    return CDungeonManager::getSingleton();
}

CUnitResourceList* CResourceManager::getMasterResourceList()
{
    return CUnitResourceList::getSingleton();
}

CGameUI* CResourceManager::getGameUI()
{
    return CGameUI::getSingleton();
}

CCameraControl* CResourceManager::getCameraControl()
{
    return CCameraControl::getSingleton();
}

CMissilePreloader* CResourceManager::getMissilePreloader()
{
    return CMissilePreloader::getSinglelton();
}

CMissile* CResourceManager::createMissile(const std::wstring& name)
{
    return CMissilePreloader::getSinglelton()->createNewMissileRef(this, name);
}

std::map<long long, CDataGroup*>* CResourceManager::getGroupByName(const std::wstring& name)
{
    if (CUnitResourceList::getSingleton())
        return CUnitResourceList::getSingleton()->getGroupByName(name);
    return NULL;
}

Ogre::TextureManager* CResourceManager::getTextureManager()
{
    return Ogre::TextureManager::getSingletonPtr();
}
