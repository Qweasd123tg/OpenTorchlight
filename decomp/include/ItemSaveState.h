#ifndef ITEMSAVESTATE_H
#define ITEMSAVESTATE_H
#include "RunicCore.h"
#include <OgreVector3.h>
#include <OgreMatrix4.h>
#include <string>

// Partial: complete layout, fields used by Item are named; other save payload is opaque.
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
    unsigned char m_StateData68[0x80-0x68];
    int m_iRoomIndex;
    Ogre::Vector3 m_vLocalPosition;
    Ogre::Vector3 m_vWorldPosition;
    Ogre::Matrix4 m_mOrientation;
    unsigned char m_StateDataDC[0x170-0xdc];
    long long m_iQuestGuid;
    int m_iQuestState;
    bool m_bItemFlag17C;
};
#endif
