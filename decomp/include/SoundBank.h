#ifndef SOUNDBANK_H
#define SOUNDBANK_H
#include "RunicCore.h"
#include "TArrayList.h"
#include <vector>
#include <string>
#include <OgreVector3.h>
class CSoundInstance;
namespace Ogre { class SceneNode; }
class CSoundManager;
// Partial: complete size/vtable; Item uses destruction and update (its return is ignored).
class CSoundBank : public CRunicCore
{
public:
    CSoundBank(CSoundManager&,bool);
    virtual ~CSoundBank();
    CSoundInstance* addSample(int sound, const std::wstring& name, bool flag1, bool flag2,
                   float value1, float value2, float value3, float value4, int value5);
    void addSample(int sound,long long guid);
    int playSample(int sound,Ogre::SceneNode*,float,float,bool);
    void queueGlobalSample(int,float,float);
    void update(float elapsed, Ogre::SceneNode* node);
    void stop(int sound);
    void stop();
    void setRadius(float);
    bool bankPlaying(int);
    void pause();
    void resume();
    float configureVolumeScale(float, const Ogre::Vector3&);
    void clear();
private:
    friend class CSoundObject;
    CSoundManager* m_soundManager; // +0x10
    TArrayList<int> m_channels; // +0x18
    TArrayList<int> m_sampleIDs; // +0x30
    std::vector<std::vector<CSoundInstance*> > m_samples; // +0x48
    std::vector<float> m_radii; // +0x60
    std::vector<float> m_volumes; // +0x78
    std::vector<int> m_probabilities; // +0x90
    bool m_dirty; // +0xa8
    float m_volumeScale; // +0xac
    float m_radius; // +0xb0
    bool m_is3D; // +0xb4
    Ogre::Vector3 m_lastPosition; // +0xb8
    float m_lastVolume; // +0xc4
    bool m_loop; // +0xc8
};
#endif
