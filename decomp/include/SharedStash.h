#ifndef SHAREDSTASH_H
#define SHAREDSTASH_H

#include "RunicCore.h"

#include <string>

class CCharacter;
class CInventory;
class CPlayer;
class CResourceManager;

class CSharedStash : public CRunicCore
{
public:
    virtual ~CSharedStash();

    static CSharedStash* getSingleton();

    CSharedStash(const wchar_t* stashFileName,
                 const wchar_t* alternateStashFileName);

    void loadSharedStash(CResourceManager* resourceManager,
                         CCharacter* character);
    void setPlayer(CPlayer* player);
    void saveSharedStash();

    CInventory* m_pInventory;
    std::wstring m_stashFileName;
    std::wstring m_alternateStashFileName;
    bool m_bUseAlternateStash;
};

#endif
