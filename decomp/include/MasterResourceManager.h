#ifndef MASTERRESOURCEMANAGER_H
#define MASTERRESOURCEMANAGER_H

#include "RunicCore.h"

class CSettings;

// Partial: declarations from MasterResourceManager.cpp used by recovered TUs;
// only the settings pointer is placed (the object is 400 bytes).
class CMasterResourceManager : public CRunicCore
{
public:
    virtual ~CMasterResourceManager();

    static CMasterResourceManager* getSingleton();

private:
    unsigned char m_Unrecovered10[0x80];

public:
    CSettings* m_pSettings;
};

#endif
