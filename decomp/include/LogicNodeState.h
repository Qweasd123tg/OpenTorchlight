#ifndef LOGICNODESTATE_H
#define LOGICNODESTATE_H

#include <stdio.h>
#include <string>

#include "RunicCore.h"
#include <OgreVector3.h>

class CLogicObject;

class CLogicNodeState : public CRunicCore
{
public:
    virtual ~CLogicNodeState() {}

    void save(_IO_FILE *pFile);
    void load(_IO_FILE *pFile, unsigned int nVersion);

    bool m_bActive;
    bool m_bEnabled;
    bool m_bFinished;
    bool m_bFailed;
    bool m_bPersistent;
    unsigned int m_nStateVersion;
    unsigned int m_nNodeId;
    union { unsigned int m_nParentNodeId; float m_value20; };
    unsigned int m_nStateFlags;
    std::wstring m_wstrName;
    unsigned int m_nCurrentState;
    unsigned char m_padding34[4];
    long long m_parentGuid; // +0x38
    long long m_parentHierarchyHash; // +0x40
    long long m_guid; // +0x48
    Ogre::Vector3 m_position; // +0x50; implicit tail padding +0x5c..+0x5f
};

typedef char check_logic_node_state_size[sizeof(CLogicNodeState) == 0x60 ? 1 : -1];

#endif
