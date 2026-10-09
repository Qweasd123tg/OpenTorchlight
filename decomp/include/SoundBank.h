#ifndef SOUNDBANK_H
#define SOUNDBANK_H
#include "RunicCore.h"
namespace Ogre { class SceneNode; }
class CSoundManager;
// Partial: complete size/vtable; Item uses destruction and update (its return is ignored).
class CSoundBank : public CRunicCore
{
public:
    CSoundBank(CSoundManager&,bool);
    virtual ~CSoundBank();
    void addSample(int sound,long long guid);
    void playSample(int sound,Ogre::SceneNode*,float,float,bool);
    void queueGlobalSample(int,float,float);
    void update(float elapsed, Ogre::SceneNode* node);
    void stop(int sound);
private:
    unsigned char m_SoundBankData[0xd0-0x10];
};
#endif
