#ifndef AIFLAG_H
#define AIFLAG_H

#include "RunicCore.h"
#include "AIDefines.h"

class CAIFlagManager;

// Timed AI flag owned by a CAIFlagManager.
class CAIFlag : public CRunicCore
{
public:
    CAIFlag(EAIFLAG_TYPES type, CAIFlagManager* manager);
    virtual ~CAIFlag();

    // Counts the remaining time down; false once it has run out.
    bool update(float elapsed);

    bool isActive() { return m_fTimeRemaining > 0.0f; }
    float getTimeRemaining() { return m_fTimeRemaining; }
    void setTimeRemaining(float time) { m_fTimeRemaining = time; }

private:
    float m_fTimeRemaining;
    CAIFlagManager* m_pManager;
    EAIFLAG_TYPES m_eType;
};

#endif
