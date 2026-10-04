#ifndef SOUNDOBJECT_H
#define SOUNDOBJECT_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreVector3.h>
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "SoundBank.h"
#include "iSelected.h"

class CSoundObject : public CPositionableObject, public iSelected
{
public:
    virtual ~CSoundObject();
    virtual void setEnabled(bool);
    virtual void setVisible(bool);
    virtual void positionUpdated(const Ogre::Vector3&);
    virtual void editorSelectionChanged(bool);
    char isLooping();
    void stop();
    void resume();
    void pause();
    void play();
    void reset();
    void updateSounds(float);
    void setSoundBankGuid(long long);
    CSoundObject(CResourceManager*);
    void setSoundBankNameIndex(unsigned int);

    // fields
    long long m_iSoundBankGuidAsString;
    int m_iSoundBankCategory;
    unsigned int m_iSoundBankNameIndex;
    CSoundBank* m_pVolume;
    bool m_bSoundStartsOnActivated;
    bool m_bUnknown121;
    bool m_bUnknown122;
    bool m_bEnvironmental;
};

#endif
