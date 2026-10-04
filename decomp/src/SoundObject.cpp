#include "EmptyStrings.h"
#include "SoundObject.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "BaseUnit.h"
#include "CollisionList.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "UtilitiesMath.h"

void CSoundObject::positionUpdated(const Ogre::Vector3& position)
{
    if (m_pSoundBank != NULL) {
        *reinterpret_cast<bool*>(reinterpret_cast<unsigned char*>(m_pSoundBank) + 0xa8) = true;
    }
}

bool CSoundObject::isLooping()
{
    return m_pSoundBank != 0 &&
           *reinterpret_cast<const bool *>(
               reinterpret_cast<const unsigned char *>(m_pSoundBank) + 0xc8);
}

void CSoundObject::stop()
{
    extern void csoundbank_stop(CSoundBank*) asm("_ZN10CSoundBank4stopEv");

    if (m_pSoundBank) {
        csoundbank_stop(m_pSoundBank);
        BroadcastEvent(0x0c);
        m_bSoundPlaying = false;
    }
}

extern "C" void CallCSoundBankResume(CSoundBank*)
    __asm__("_ZN10CSoundBank6resumeEv");

void CSoundObject::resume()
{
    if (m_pSoundBank != 0) {
        CallCSoundBankResume(m_pSoundBank);
        m_bSoundPaused = false;
        reinterpret_cast<unsigned char*>(m_pSoundBank)[0xa8] = 1;
    }
}

extern void CSoundBank_pause(CSoundBank*) asm("_ZN10CSoundBank5pauseEv");

void CSoundObject::pause()
{
    if (m_pSoundBank != 0) {
        CSoundBank_pause(m_pSoundBank);
        m_bSoundPaused = true;
    }
}

void CSoundObject::setVisible(bool visible)
{
    CSceneNodeObject::setVisible(visible);
    if (m_pSoundBank != NULL)
    {
        *reinterpret_cast<bool *>(reinterpret_cast<char *>(m_pSoundBank) + 0xa8) = true;
    }
}

void CSoundObject::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    if (m_pSoundBank != NULL && enabled && m_bSoundStartsOnActivated)
    {
        play();
        *reinterpret_cast<bool*>(
            reinterpret_cast<unsigned char*>(m_pSoundBank) + 0xa8) = true;
    }
}

void CSoundObject::updateSounds(float elapsedTime)
{
    struct CSoundManagerAccess
    {
        unsigned char padding[0x6a8];
        unsigned char m_bSoundEnabled;
        unsigned char m_bSoundPlaybackEnabled;
    };

    struct CSoundBankAccess
    {
        unsigned char padding0[0x10];
        CSoundManagerAccess* m_pSoundManager;
        unsigned char padding1[0x10];
        int m_iSoundCount;

        void update(float, Ogre::SceneNode*)
            __asm__("_ZN10CSoundBank6updateEfPN4Ogre9SceneNodeE");
    };

    struct CVirtualAccess
    {
        virtual void v0() = 0;
        virtual void v1() = 0;
        virtual void v2() = 0;
        virtual void v3() = 0;
        virtual void v4() = 0;
        virtual void v5() = 0;
        virtual void broadcastEvent(int) = 0;
        virtual void v7() = 0;
        virtual void v8() = 0;
        virtual bool getEnabled() const = 0;
    };

    CSoundBankAccess* soundBank =
        reinterpret_cast<CSoundBankAccess*>(m_pSoundBank);

    if (soundBank == NULL)
        return;

    CVirtualAccess* object = reinterpret_cast<CVirtualAccess*>(this);

    if (!object->getEnabled() || !m_bSoundPlaying || m_bSoundPaused)
        return;

    if (!soundBank->m_pSoundManager->m_bSoundPlaybackEnabled ||
        !soundBank->m_pSoundManager->m_bSoundEnabled)
        return;

    soundBank->update(elapsedTime,
                      m_bEnvironmental ? m_pSceneNode : NULL);

    if (soundBank->m_iSoundCount == 0 && !m_bEnvironmental) {
        m_bSoundPlaying = false;
        object->broadcastEvent(13);
    }
}

void CSoundObject::editorSelectionChanged(bool selected)
{
}

CSoundObject::~CSoundObject()
{
}
