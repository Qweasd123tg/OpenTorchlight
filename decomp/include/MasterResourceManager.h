#ifndef MASTERRESOURCEMANAGER_H
#define MASTERRESOURCEMANAGER_H

#include "RunicCore.h"

namespace Ogre { class SceneManager; }
class CHierarchy;
class CSettings;
class CSoundManager;
class CSoundBankDataInformation;

// Partial: declarations from MasterResourceManager.cpp used by recovered TUs;
// hierarchy, settings, audio and paperdoll-scene pointers are placed (the original object is 400 bytes).
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
    unsigned char m_UnrecoveredA0[0xd0-0xa0];
public:
    Ogre::SceneManager* m_pSceneManager;
private:
    unsigned char m_UnrecoveredD8[0x100-0xd8];
public:
    CSoundBankDataInformation* m_pSoundBankDataInformation;
};

#endif
