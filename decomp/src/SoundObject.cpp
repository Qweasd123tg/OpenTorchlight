#include "EmptyStrings.h"
#include "SoundManager.h"
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
    if (!m_pSoundBank || !getEnabled() || !m_bSoundPlaying || m_bSoundPaused)
        return;
    if (!m_pSoundBank->m_soundManager->m_bUnknown6A9 || !m_pSoundBank->m_soundManager->m_bUnknown6A8)
        return;
    m_pSoundBank->update(elapsedTime, m_bEnvironmental ? m_pSceneNode : 0);
    if (m_pSoundBank->m_channels.size() == 0 && !m_bEnvironmental) {
        m_bSoundPlaying = false;
        BroadcastEvent(13);
    }
}

void CSoundObject::editorSelectionChanged(bool selected)
{
    if (m_pResourceManager && m_pResourceManager->getEditorIsRunning()) {
        if (selected)
            sceneNodeAttachEntity(m_pEntity);
        else
            sceneNodeDetachEntity();
    }
}

CSoundObject::~CSoundObject()
{
}

void CSoundObject::reset()
{
    m_pSoundBank->stop();
    play();
}

#include "MasterResourceManager.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"

void CSoundObject::play()
{
    if (!m_pSoundBank)
        return;
    if ((!m_pSoundBank->m_soundManager->m_bUnknown6A9 ||
         !m_pSoundBank->m_soundManager->m_bUnknown6A8) && !m_bEnvironmental)
        return;
    m_pSoundBank->m_dirty = true;
    if (!m_bVisible)
        CSceneNodeObject::setVisible(true);
    m_pSoundBank->stop();
    m_bSoundPlaying = true;
    if (!m_bEnvironmental)
        m_pSoundBank->setRadius(0.0f);
    if (!m_pSoundBank->m_loop || !m_bEnvironmental)
        if (m_pSoundBank->playSample(0, m_bEnvironmental ? m_pSceneNode : 0, 0.0f, 0.0f, false) < 0)
            m_bSoundPlaying = false;
    BroadcastEvent(11);
    if (m_bSoundPaused)
        pause();
}

void CSoundObject::setSoundBankGuid(long long guid)
{
    if (!m_pSoundBank)
        return;
    m_iSoundBankGuid = guid;
    m_pSoundBank->clear();
    if (m_iSoundBankGuid != -1) {
        m_pSoundBank->addSample(0, guid);
        if (m_bSoundPlaying)
            reset();
    }
}

void CSoundObject::setSoundBankNameIndex(unsigned int index)
{
    m_iSoundBankNameIndex = index;
    CSoundBankDataInformation* information = CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
    if (!information)
        return;
    CSoundData* sound = information->getSoundDataObject(
        information->getCategoryNameByID(m_iSoundBankCategory),
        information->getSoundNameByCategoryIndex(m_iSoundBankCategory, index));
    if (sound) {
        setSoundBankGuid(sound->m_iGuid);
        if (m_bSoundPlaying || m_bSoundStartsOnActivated)
            play();
    }
}

CSoundObject::CSoundObject(CResourceManager* resources)
    : CPositionableObject(resources, 0), m_iSoundBankGuid(-1), m_iSoundBankCategory(0),
      m_iSoundBankNameIndex(0), m_pSoundBank(0), m_bSoundStartsOnActivated(true),
      m_bSoundPlaying(false), m_bSoundPaused(false), m_bEnvironmental(true)
{
    if (CMasterResourceManager::getSingleton()->m_pSoundManager) {
        m_pSoundBank = new CSoundBank(*CMasterResourceManager::getSingleton()->m_pSoundManager, true);
        if (m_pSoundBank) {
            m_pSoundBank->setRadius(5.0f);
            setScale(m_pSoundBank->m_radius);
            m_pSoundBank->m_dirty = true;
        }
    }
}
