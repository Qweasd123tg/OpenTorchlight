#ifndef MASTERRESOURCEMANAGER_H
#define MASTERRESOURCEMANAGER_H

#include "RunicCore.h"

class CHierarchy;
class CSettings;
class CSoundManager;
class CSoundBankDataInformation;

// Partial: declarations from MasterResourceManager.cpp used by recovered TUs;
// hierarchy, settings and audio pointers are placed (the original object is 400 bytes).
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
    CSoundManager* m_pSoundManager;
private:
    unsigned char m_UnrecoveredA0[0x100-0xa0];
public:
    CSoundBankDataInformation* m_pSoundBankDataInformation;
};

#endif
