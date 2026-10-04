#ifndef LOGICNODESTATE_H
#define LOGICNODESTATE_H

#include <stdio.h>
#include <string>

#include "RunicCore.h"
#include "TArrayList.h"

class CLogicObject;

class CLogicNodeState : public CRunicCore
{
public:
    virtual ~CLogicNodeState();

    void save(_IO_FILE *pFile);
    void load(_IO_FILE *pFile, unsigned int nVersion);

    bool m_bActive;
    bool m_bEnabled;
    bool m_bFinished;
    bool m_bFailed;
    bool m_bPersistent;
    unsigned int m_nStateVersion;
    unsigned int m_nNodeId;
    unsigned int m_nParentNodeId;
    unsigned int m_nStateFlags;
    std::wstring m_wstrName;
    unsigned int m_nCurrentState;
    TArrayList<CLogicObject *> m_apLinkedObjects;
    CLogicObject *m_pOwnerObject;
};

#endif
