#ifndef ITEMSAVESTATE_H
#define ITEMSAVESTATE_H
#include "RunicCore.h"
#include <OgreVector3.h>
#include <OgreMatrix4.h>
#include <string>
#include <vector>
#include "Constants.h"
class CEffect;

// Partial: complete layout; Item and Equipment save payload fields are named.
class CItemSaveState : public CRunicCore
{
public:
    CItemSaveState();
    virtual ~CItemSaveState();
    std::wstring m_sItemName;
    std::wstring m_sStateString18;
    std::wstring m_sStateString20;
    int m_iStateValue28;
    long long m_iOriginalGuid;
    long long m_iStateValue38;
    long long m_iParentHierarchyHash;
    bool m_bSaveFlag48;
    long long m_iSpawnerGuid;
    int m_iIndex;
    bool m_bSaveFlag5C;
    bool m_bEnabled;
    bool m_bBlocksPath;
    long long m_iUnitValue60;
    int m_iStackSize;
    int m_iStateValue6C;
    unsigned int m_iSocketCount;
    unsigned char m_StateByte74;
    bool m_bIdentified;
    unsigned char m_StateData76[2];
    int m_iBaseDamage;
    int m_iBaseArmor;
    int m_iRoomIndex;
    Ogre::Vector3 m_vLocalPosition;
    Ogre::Vector3 m_vWorldPosition;
    Ogre::Matrix4 m_mOrientation;
    unsigned char m_StateDataDC[4];
    std::vector<CEffect*> m_Effects[3];
    std::vector<CItemSaveState*> m_SocketedItems;
    std::vector<EDAMAGE_TYPES> m_DamageTypes;
    std::vector<int> m_DamageBonuses;
    long long m_iQuestGuid;
    int m_iQuestState;
    bool m_bItemFlag17C;
};
#endif
