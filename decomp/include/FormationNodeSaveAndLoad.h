#ifndef FORMATIONNODESAVEANDLOAD_H
#define FORMATIONNODESAVEANDLOAD_H

#include <stdio.h>
#include <string>

#include "RunicCore.h"

class CFormationNode;

class CFormationNodeSaveAndLoad : public CRunicCore
{
public:
    virtual ~CFormationNodeSaveAndLoad();

    void saveFormationNode(FILE* pFile);
    void loadFormationNode(FILE* pFile);

    CFormationNodeSaveAndLoad(CFormationNode* pFormationNode);

    bool m_bSavePosition;
    unsigned char m_pad11[7];
    std::wstring m_sFileLoaded;
    unsigned char m_pad20[12] __attribute__((aligned(4)));
    float m_fPositionX;
    float m_fPositionY;
    float m_fPositionZ;
};

#endif
