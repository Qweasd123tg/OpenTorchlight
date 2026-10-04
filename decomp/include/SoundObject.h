#ifndef SOUNDOBJECT_H
#define SOUNDOBJECT_H

// Partial: layout and virtual order of SoundObject.cpp; only the methods used so far.

#include <OgreVector3.h>

#include "PositionableObject.h"
#include "iSelected.h"

class CResourceManager;
class CSoundBank;

class CSoundObject : public CPositionableObject, public iSelected
{
public:
    CSoundObject(CResourceManager* resourceManager);
    virtual ~CSoundObject();
    virtual void setEnabled(bool enabled);
    virtual void setVisible(bool visible);
    virtual void positionUpdated(const Ogre::Vector3& position);
    virtual void editorSelectionChanged(bool selected);

    bool isLooping();
    void stop();
    void resume();
    void pause();
    void play();
    void reset();
    void updateSounds(float elapsed);
    void setSoundBankGuid(long long guid);
    void setSoundBankNameIndex(unsigned int index);

protected:
    long long m_iSoundBankGuid;
    int m_iSoundBankCategory;
    unsigned int m_iSoundBankNameIndex;
    CSoundBank* m_pSoundBank;
    bool m_bStartsOnActivated;
    bool m_bPlaying;
    bool m_bPaused;
    bool m_bEnvironmental;
};

#endif
