#ifndef MASTERRESOURCEMANAGER_H
#define MASTERRESOURCEMANAGER_H

#include "RunicCore.h"

class CHierarchy;
class CSettings;

// Partial: declarations from MasterResourceManager.cpp used by recovered TUs;
// only the unit type hierarchy and the settings pointer are placed (the object is 400 bytes).
class CMasterResourceManager : public CRunicCore
{
public:
    virtual ~CMasterResourceManager();

    static CMasterResourceManager* getSingleton();

private:
    unsigned char m_Unrecovered10[0x70];

public:
    CHierarchy* m_pHierarchy;

private:
    unsigned char m_Unrecovered88[0x8];

public:
    CSettings* m_pSettings;
};

#endif
