#ifndef AIFLAGMANAGER_H
#define AIFLAGMANAGER_H

#include "RunicCore.h"
#include "AIDefines.h"
#include "TArrayList.h"

class CAIFlag;
class CAIManager;
class CCharacter;

// Owns one timed CAIFlag per EAIFLAG_TYPES value of a character's AI and
// applies the side effects of flags being set and cleared.
class CAIFlagManager : public CRunicCore
{
public:
    CAIFlagManager(CAIManager* aiManager, CCharacter* character);
    virtual ~CAIFlagManager();

    bool hasAIFlag(EAIFLAG_TYPES type);
    void updateAIFlag(EAIFLAG_TYPES type, float elapsed);
    void flagRemoved(EAIFLAG_TYPES type);
    void removeAIFlag(EAIFLAG_TYPES type);
    void flagSet(EAIFLAG_TYPES type);
    // Extends the flag to at least the given time; returns the flag.
    CAIFlag* addAIFlag(EAIFLAG_TYPES type, float time);
    void updateAIFlags(float elapsed);

private:
    TArrayList<CAIFlag*> m_Flags;
    CCharacter* m_pCharacter;
    CAIManager* m_pAIManager;
};

#endif
