extern unsigned int KSETTINGS_NETBOOK_MODE;
#include "AnimationSet.h"
#include "EmptyStrings.h"
#include "EmptyStrings.h"
#include "GenericModel.h"
#include "Keyframe.h"
#include "MasterResourceManager.h"
#include <OgreEntity.h>
#include <OgreMaterial.h>
#include "Settings.h"
#include "StringUtilities.h"


// Imported source candidates; historical status is not fresh acceptance.
int CGenericModel::findKey(int animation, CKeyframe* key)
{
    for (unsigned int i = 0; i < m_animationSet->m_lAnimationGroups[animation].size(); ++i)
        if (m_animationSet->m_lAnimationGroups[animation][i] == key) return i;
    return -1;
}

TArrayList<int>* CGenericModel::getValueIndexes(int animation, CKeyframe* key)
{
    int index = findKey(animation, key);
    return &m_valueIndexes[animation][index];
}

unsigned int CGenericModel::getAnimationCount() const
{
    return m_animationSet ? m_animationSet->m_nUnknown : 0;
}

const std::string& CGenericModel::getAnimationName(unsigned int animation) const
{
    return m_animationSet ? m_animationSet->m_lUnknown28[animation] : EMPTY_STRING;
}

unsigned int CGenericModel::getKeyCount(unsigned int animation)
{
    unsigned int result = 0;
    if (m_animationSet) {
        result = m_animationSet->m_lAnimationGroups.size();
        if (animation < m_animationSet->m_lAnimationGroups.size()) result = m_animationSet->m_lAnimationGroups[animation].size();
    }
    return result;
}

CKeyframe* CGenericModel::getKeyFrame(unsigned int animation, unsigned int key)
{
    if (!m_animationSet) return NULL;
    if (animation >= m_animationSet->m_lAnimationGroups.size()) return NULL;
    if (key >= m_animationSet->m_lAnimationGroups[animation].size()) return NULL;
    return m_animationSet->m_lAnimationGroups[animation][key];
}

const std::string& CGenericModel::getName()
{
    return m_name;
}

int CGenericModel::getAnimationLength(int animation) const
{
    getAnimationLengthSeconds(animation);
    return 0;
}

unsigned long CGenericModel::activeAnimations() const
{
    return m_activeAnimations.size();
}

bool CGenericModel::animationQueued(const std::string& animation) const
{
    return animationQueued(getAnimationIndex(animation));
}

bool CGenericModel::animationPlaying(const std::string& animation) const
{
    return animationPlaying(getAnimationIndex(animation));
}

void CGenericModel::queueBlendAnimation(const std::string& animation, bool loop, float blend, float speed)
{
    queueBlendAnimation(getAnimationIndex(animation), loop, blend, speed);
}

void CGenericModel::setHighlighted(bool highlighted)
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_renderableStates.size()); ++i) m_renderableStates[i].highlighted = highlighted;
}

void CGenericModel::setRenderBehind(bool behind)
{
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE) == 1) return;
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_renderableStates.size()); ++i) m_renderableStates[i].renderBehind = behind;
}

void CGenericModel::setAmbient(Ogre::ColourValue& colour)
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_renderableStates.size()); ++i) {
        Ogre::Material* material = m_renderableStates[i].material;
        material->setAmbient(colour); material->setDiffuse(colour);
    }
}

#include <OgreAnimationState.h>
#include <OgreTechnique.h>
#include <OgrePass.h>
#include <OgreTextureUnitState.h>
#include "Utilities.h"
#include <algorithm>

void CGenericModel::setQueryMask(OGRE_UTILITIES::EQUERYMASK mask)
{
    m_queryMask = mask;
    if (m_pEntity) m_pEntity->setQueryFlags(mask);
}



std::string CGenericModel::getTexureName()
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_renderableStates.size()); ++i) {
        if (!m_renderableStates[i].material) continue;
        Ogre::Technique* technique = m_renderableStates[i].material->getBestTechnique();
        if (!technique) continue;
        Ogre::Pass* pass = technique->getPass(0);
        if (!pass || !pass->getNumTextureUnitStates()) continue;
        Ogre::TextureUnitState* texture = pass->getTextureUnitState(0);
        if (texture) return texture->getTextureName();
    }
    return EMPTY_STRING;
}

float CGenericModel::getAnimationLengthSeconds(int animation) const
{
    if (animation < 0 || !m_animationSet || animation >= m_animationSet->m_nUnknown) return 0;
    return m_animationStates[animation]->getLength();
}

void CGenericModel::addValueIndex(int animation, CKeyframe* key, int value)
{
    int index = findKey(animation, key);
    m_valueIndexes[animation][index].add(value);
}

const std::string& CGenericModel::getAnimationNameByPath(const std::wstring& path) const
{
    if (m_animationSet) {
        for (unsigned int i = 0; i < m_animationSet->m_lUnknown40.size(); ++i)
            if (STRINGS::StringUpper(path) == STRINGS::StringUpper(m_animationSet->m_lUnknown40[i]) &&
                i < m_animationSet->m_lUnknown28.size()) return m_animationSet->m_lUnknown28[i];
    }
    return EMPTY_STRING;
}

bool CGenericModel::animationExists(const std::string& name) const
{
    if (m_animationSet)
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_animationSet->m_nUnknown); ++i)
            if (STRINGS::StringUpper(name) == STRINGS::StringUpper(m_animationSet->m_lUnknown28[i])) return true;
    return false;
}

float CGenericModel::getAnimationLengthSeconds(const std::string& name) const
{
    if (m_animationSet)
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_animationSet->m_nUnknown); ++i)
            if (STRINGS::StringUpper(name) == STRINGS::StringUpper(m_animationSet->m_lUnknown28[i])) return getAnimationLengthSeconds(i);
    return 0;
}

long CGenericModel::getAnimationLength(const std::string& name) const
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_animationSet->m_nUnknown); ++i)
        if (STRINGS::StringUpper(name) == STRINGS::StringUpper(m_animationSet->m_lUnknown28[i])) return static_cast<long>(getAnimationLengthSeconds(i));
    return 0;
}

unsigned int CGenericModel::getAnimationIndex(const std::string& name) const
{
    if (!m_animationSet) return -1;
    std::string upper = STRINGS::StringUpper(name);
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_animationSet->m_nUnknown); ++i)
        if (upper == STRINGS::StringUpper(m_animationSet->m_lUnknown28[i])) return i;
    return -1;
}

bool CGenericModel::animationExistsSubstring(const std::string& name) const
{
    if (m_animationSet) {
        unsigned int length = name.length();
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_animationSet->m_nUnknown); ++i) {
            std::string upper = STRINGS::StringUpper(m_animationSet->m_lUnknown28[i]);
            if (upper.length() >= length && upper.substr(0,length) == name) return true;
        }
    }
    return false;
}

int CGenericModel::findRandomAnimation(const std::string& name)
{
    unsigned int length = name.length();
    int result = -1;
    for (unsigned int i = 0; m_animationSet && i < static_cast<unsigned int>(m_animationSet->m_nUnknown); ++i) {
        std::string upper = STRINGS::StringUpper(m_animationSet->m_lUnknown28[i]);
        if (upper.length() >= length && upper.substr(0,length) == name)
            if (result == -1 || UTILITIES::randomBetweenVolatile(0,1000) < 500.0f) result = i;
    }
    return result;
}

void CGenericModel::setAnimationTime(float time)
{
    for (unsigned int i = 0; i < m_activeAnimations.size(); ++i)
        if (!m_activeAnimations[i]->m_queued)
            m_activeAnimations[i]->m_time = std::min(m_activeAnimations[i]->m_length, std::max(0.0f,time));
}

bool CGenericModel::animationQueued(unsigned int animation) const
{
    for (unsigned int i = 0; i < m_activeAnimations.size(); ++i)
        if (m_activeAnimations[i]->m_queued && m_activeAnimations[i]->m_animation == animation) return true;
    return false;
}

bool CGenericModel::animationPlaying() const
{
    for (unsigned int i = 0; i < m_activeAnimations.size(); ++i)
        if (!m_activeAnimations[i]->m_queued && m_activeAnimations[i]->m_playing) return true;
    return false;
}

bool CGenericModel::animationPlaying(unsigned int animation) const
{
    for (unsigned int i = 0; i < m_activeAnimations.size(); ++i)
        if (!m_activeAnimations[i]->m_queued && m_activeAnimations[i]->m_animation == animation && m_activeAnimations[i]->m_playing) return true;
    return false;
}

bool CGenericModel::loopingAnimationPlaying()
{
    for (unsigned int i = 0; i < m_activeAnimations.size(); ++i)
        if (!m_activeAnimations[i]->m_queued && m_activeAnimations[i]->m_playing && m_activeAnimations[i]->m_loop) return true;
    return false;
}

int CGenericModel::currentAnimation() const
{
    for (unsigned int i = 0; i < m_activeAnimations.size(); ++i)
        if (!m_activeAnimations[i]->m_queued && m_activeAnimations[i]->m_playing) return m_activeAnimations[i]->m_animation;
    return -1;
}

float CGenericModel::getAnimationTime()
{
    for (unsigned int i = 0; i < m_activeAnimations.size(); ++i)
        if (!m_activeAnimations[i]->m_queued && m_activeAnimations[i]->m_playing) return m_activeAnimations[i]->m_time;
    return 0;
}

void CGenericModel::setAnimationSpeed(const std::string&, float speed)
{
    for (unsigned int i = 0; i < m_activeAnimations.size(); ++i)
        if (!m_activeAnimations[i]->m_queued && m_activeAnimations[i]->m_playing) m_activeAnimations[i]->m_speed = speed;
}

bool CGenericModel::animationQueuedSubstring(const std::string& name) const
{
    unsigned int length = name.length();
    for (unsigned int i = 0; i < m_activeAnimations.size(); ++i) {
        if (m_activeAnimations[i]->m_queued) {
            std::string upper = STRINGS::StringUpper(getAnimationName(m_activeAnimations[i]->m_animation));
            if (length <= upper.length() && upper.substr(0,length) == name) return true;
        }
    }
    return false;
}

bool CGenericModel::animationPlayingSubstring(const std::string& name) const
{
    unsigned int length = name.length();
    for (unsigned int i = 0; i < m_activeAnimations.size(); ++i) {
        if (!m_activeAnimations[i]->m_queued && m_activeAnimations[i]->m_playing) {
            std::string upper = STRINGS::StringUpper(getAnimationName(m_activeAnimations[i]->m_animation));
            if (length <= upper.length() && upper.substr(0,length) == name) return true;
        }
    }
    return false;
}

void CGenericModel::clearQueuedAnimations()
{
    for (int i = 0; i < static_cast<int>(m_activeAnimations.size()); ++i) {
        if (m_activeAnimations[i]->m_queued) {
            if (m_activeAnimations[i]) delete m_activeAnimations[i];
            m_activeAnimations[i] = NULL;
            for (int j = i; j < static_cast<int>(m_activeAnimations.size())-1; ++j) m_activeAnimations[j] = m_activeAnimations[j+1];
            m_activeAnimations.pop_back();
            --i;
        }
    }
}

void CGenericModel::clearAnimations()
{
    for (int i = 0; i < static_cast<int>(m_activeAnimations.size()); ++i) {
        if (m_activeAnimations[i]->m_animation < m_animationStates.size()) m_animationStates[m_activeAnimations[i]->m_animation]->setEnabled(false);
        if (m_activeAnimations[i]) delete m_activeAnimations[i];
        m_activeAnimations[i] = NULL;
    }
    m_activeAnimations.clear();
}

void CGenericModel::playAnimation(const std::string& name, bool loop, float speed, float length)
{
    if (m_animationSet)
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_animationSet->m_nUnknown); ++i)
            if (STRINGS::StringUpper(m_animationSet->m_lUnknown28[i]) == name) { playAnimation(i,loop,speed,length); return; }
}

void CGenericModel::blendAnimation(const std::string& name, bool loop, float blend, float speed, float length)
{
    if (m_animationSet)
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_animationSet->m_nUnknown); ++i)
            if (STRINGS::StringUpper(m_animationSet->m_lUnknown28[i]) == name) blendAnimation(i,loop,blend,speed,length);
}

void CGenericModel::queueBlendAnimation(unsigned int animation, bool loop, float blend, float speed)
{
    if (animation == static_cast<unsigned int>(-1) || !m_animationStates.size()) return;
    if (getAnimationLengthSeconds(animation) == 0) blend = 0;
    m_animationStates[animation]->setLoop(loop);
    float length = m_animationStates[animation]->getLength();
    blend = std::min(blend,length);
    CActiveAnimation* active = new CActiveAnimation;
    active->m_animation = animation;
    active->m_length = length; active->m_duration = length; active->m_time = 0;
    active->m_loop = loop;
    active->m_playing = false; active->m_queued = true;
    active->m_flag27 = active->m_flag28 = active->m_flag29 = active->m_flag2a = false;
    active->m_speed = speed;
    active->m_blendRemaining = active->m_blendDuration = blend <= 0 ? 0.0001f : blend;
    active->m_weight = 1;
    m_activeAnimations.push_front(active);
}

void CGenericModel::playAnimation(unsigned int animation, bool loop, float speed, float length)
{
    if (!m_animationStates.size()) return;
    clearAnimations();
    m_animationStates[animation]->setLoop(loop);
    float actualLength = m_animationStates[animation]->getLength();
    CActiveAnimation* active = new CActiveAnimation;
    active->m_animation = animation;
    active->m_length = actualLength; active->m_duration = actualLength; active->m_time = 0;
    active->m_loop = loop;
    active->m_playing = false; active->m_queued = false;
    active->m_flag27 = active->m_flag28 = active->m_flag29 = active->m_flag2a = false;
    active->m_blendRemaining = active->m_blendDuration = active->m_weight = 0;
    active->m_speed = speed;
    if (length != -1) active->m_length = length;
    active->m_playing = true; active->m_queued = false; active->m_weight = 0;
    m_animationStates[animation]->setEnabled(true);
    m_activeAnimations.push_front(active);
}

void CGenericModel::blendAnimation(unsigned int animation, bool loop, float blend, float speed, float length)
{
    if (!m_animationStates.size()) return;
    if (getAnimationLengthSeconds(animation) == 0 || blend == 0) { playAnimation(animation,loop,speed,length); return; }
    m_animationStates[animation]->setLoop(loop);
    float actualLength = m_animationStates[animation]->getLength();
    blend = std::min(blend,actualLength);
    clearQueuedAnimations();
    CActiveAnimation* active = new CActiveAnimation;
    active->m_animation = animation;
    active->m_length = actualLength; active->m_duration = actualLength; active->m_time = 0;
    active->m_loop = loop;
    active->m_playing = false; active->m_queued = false;
    active->m_flag27 = active->m_flag28 = active->m_flag29 = active->m_flag2a = false;
    active->m_blendRemaining = active->m_blendDuration = active->m_weight = 0;
    active->m_speed = speed;
    if (length != -1) { active->m_length = length; blend = std::min(blend,length); }
    active->m_playing = true; active->m_queued = false; active->m_weight = 0;
    if (active->m_length != 0) {
        active->m_blendRemaining = active->m_blendDuration = blend;
        active->m_weight = blend != 0 ? 1 : 0;
    }
    m_animationStates[animation]->setEnabled(true);
    m_activeAnimations.push_front(active);
    for (int i = 1; i < static_cast<int>(m_activeAnimations.size()); ++i)
        if (m_activeAnimations[i]->m_animation == animation) return;
    m_animationStates[animation]->setWeight(0);
}




void CGenericModel::AddKey(unsigned int animation, CDataGroup* group)
{
    if (m_animationSet) {
        if (animation >= m_animationSet->m_lAnimationGroups.size()) m_animationSet->m_lAnimationGroups.resize(animation+1);
        CKeyframe* key=new CKeyframe(animation,group);
        m_animationSet->m_lAnimationGroups[animation].push_back(key);
    }
}



CGenericModel::~CGenericModel()
{
    m_animationStates.clear();
    unloadModel();
    clearAnimations();
    releaseUniqueMaterials();
}




void CGenericModel::setTextureOverride(Ogre::TexturePtr texture, std::string exclude, std::string excludeOther)
{
    for (unsigned int i=0;i<static_cast<unsigned int>(m_renderableStates.size());++i) {
        Ogre::Material* material=m_renderableStates[i].material;
        if (exclude!="" && STRINGS::StringUpper(m_renderableStates[i].name).find(exclude)!=std::string::npos) continue;
        if (excludeOther!="" && STRINGS::StringUpper(m_renderableStates[i].name).find(excludeOther)!=std::string::npos) continue;
        Ogre::Pass* pass=material->getBestTechnique()->getPass(0);
        if (pass->getNumTextureUnitStates()) pass->getTextureUnitState(0)->_setTexturePtr(texture);
        if (m_renderableStates[i].material18) {
            pass=m_renderableStates[i].material18->getBestTechnique()->getPass(0);
            if (pass->getNumTextureUnitStates()) pass->getTextureUnitState(0)->_setTexturePtr(texture);
        }
    }
}

void CGenericModel::setTextureOverrideSingle(std::string name, Ogre::TexturePtr texture)
{
    name=STRINGS::StringUpper(name);
    for (unsigned int i=0;i<static_cast<unsigned int>(m_renderableStates.size());++i) {
        Ogre::Material* material=m_renderableStates[i].material;
        std::string upper=STRINGS::StringUpper(m_renderableStates[i].name);
        if (upper.length()>=name.length() && upper.substr(upper.length()-name.length(),name.length())==name) {
            material->getBestTechnique()->getPass(0)->getTextureUnitState(0)->_setTexturePtr(texture);
            if (m_renderableStates[i].material18) m_renderableStates[i].material18->getBestTechnique()->getPass(0)->getTextureUnitState(0)->_setTexturePtr(texture);
        }
    }
}
