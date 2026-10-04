#ifndef SOUNDBANK_H
#define SOUNDBANK_H
#include "RunicCore.h"
namespace Ogre { class SceneNode; }
// Partial: complete size/vtable; Item uses destruction and update (its return is ignored).
class CSoundBank : public CRunicCore
{
public:
    virtual ~CSoundBank();
    void update(float elapsed, Ogre::SceneNode* node);
private:
    unsigned char m_SoundBankData[0xd0-0x10];
};
#endif
