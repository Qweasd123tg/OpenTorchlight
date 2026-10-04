#ifndef SOUNDOBJECT_H
#define SOUNDOBJECT_H

#include <OgreVector3.h>
#include "PositionableObject.h"
#include "iSelected.h"

class CResourceManager;
class CSoundBank;

class CSoundObject : public CPositionableObject, public iSelected
{
public:
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
    void updateSounds(float elapsedTime);
    void setSoundBankGuid(long long soundBankGuid);
    void setSoundBankNameIndex(unsigned int soundBankNameIndex);

    CSoundObject(CResourceManager* resourceManager);

    long long m_iSoundBankGuid;
    int m_iSoundBankCategory;
    unsigned int m_iSoundBankNameIndex;
    CSoundBank* m_pSoundBank;
    bool m_bSoundStartsOnActivated;
    bool m_bSoundPlaying;
    bool m_bSoundPaused;
    bool m_bEnvironmental;

public:
    // Inline accessors behind the descriptors' property functions.
    void setSoundBankCategory(int value) { m_iSoundBankCategory = value; }
    unsigned int getSoundBankNameIndex() const { return m_iSoundBankNameIndex; }
    int getSoundBankCategory() const { return m_iSoundBankCategory; }
    bool getEnvironmental() const { return m_bEnvironmental; }
    bool getSoundStartsOnActivated() const { return m_bSoundStartsOnActivated; }
};

#endif
