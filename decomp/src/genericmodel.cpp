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

#include <OgreSceneNode.h>
#include "FileSystem.h"
void CGenericModel::setWireframe(bool wireframe)
{
    if (!m_pEntity) return;
    if (wireframe) {
        m_pEntity->setMaterialName("Points");
        m_pEntity->getParentSceneNode()->showBoundingBox(true);
        m_pEntity->setCastShadows(false);
    } else {
        m_pEntity->setMaterialName("");
        m_pEntity->getParentSceneNode()->showBoundingBox(false);
        m_pEntity->setCastShadows(false);
    }
}

#include <OgreTextureManager.h>
#include <OgreResourceGroupManager.h>

void CGenericModel::setTextureOverrideSingle(const std::string& name,const std::wstring& path)
{
    if (path.empty() || !Ogre::TextureManager::getSingletonPtr()) return;
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(path,info,false,true,false);
    if (!info.m_bExists) return;
    Ogre::TexturePtr texture=Ogre::TextureManager::getSingletonPtr()->getByName(info.m_sResourceName);
    if (!texture.isNull() && texture->isLoaded()) {
        m_string128=info.m_sResourceName;
        setTextureOverrideSingle(name,texture);
    } else {
        Ogre::TextureManager::getSingletonPtr()->load(info.m_sResourceName,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,Ogre::TEX_TYPE_2D,-1,1.0f,false,Ogre::PF_UNKNOWN,false);
        Ogre::TexturePtr loaded=Ogre::TextureManager::getSingletonPtr()->getByName(info.m_sResourceName);
        if (!loaded.isNull() && loaded->isLoaded()) {
            m_string128=info.m_sResourceName;
            setTextureOverrideSingle(name,loaded);
        }
    }
}

void CGenericModel::setTextureOverride(const std::wstring& path)
{
    if (path.empty() || !Ogre::TextureManager::getSingletonPtr()) return;
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(path,info,false,true,false);
    if (!info.m_bExists) return;
    Ogre::TexturePtr texture=Ogre::TextureManager::getSingletonPtr()->getByName(info.m_sResourceName);
    if (!texture.isNull() && texture->isLoaded()) {
        m_string128=info.m_sResourceName;
        setTextureOverride(texture,"","");
    } else {
        Ogre::TextureManager::getSingletonPtr()->load(info.m_sResourceName,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,Ogre::TEX_TYPE_2D,-1,1.0f,false,Ogre::PF_UNKNOWN,false);
        Ogre::TexturePtr loaded=Ogre::TextureManager::getSingletonPtr()->getByName(info.m_sResourceName);
        if (!loaded.isNull() && loaded->isLoaded()) {
            m_string128=info.m_sResourceName;
            setTextureOverride(loaded,"","");
        }
    }
}

#include "ResourceManager.h"
#include <OgreSceneManager.h>
#include "GameClient.h"
#include <OgreRenderQueue.h>
#include <OgreMaterialManager.h>
void CGenericModel::setCastsShadows(bool shadows)
{
    for (unsigned int i=0;i<static_cast<unsigned int>(m_renderableStates.size());++i)
        m_renderableStates[i].castsShadows=shadows;
    if (shadows) {
        if (m_pEntity) m_pEntity->setVisibilityFlags(4);
    } else if (m_pEntity) m_pEntity->setVisibilityFlags(1);
}

void CGenericModel::setRenderToLightMap(bool enabled)
{
    m_renderToLightMap=enabled;
    if (m_pEntity) {
        if (enabled) {
            m_pEntity->setRenderQueueGroup(95);
            m_pEntity->setVisibilityFlags(2);
        } else {
            m_pEntity->setRenderQueueGroup(m_pResourceManager->getSceneManager()->getRenderQueue()->getDefaultQueueGroup());
            m_pEntity->setVisibilityFlags(1);
        }
    }
}

void CGenericModel::releaseUniqueMaterials()
{
    if (!m_uniqueMaterials) return;
    for (unsigned int i=0;i<static_cast<unsigned int>(m_renderableStates.size());++i) {
        if (m_renderableStates[i].material && Ogre::MaterialManager::getSingleton().resourceExists(m_renderableStates[i].material->getName())) {
            m_renderableStates[i].material->unload();
            Ogre::MaterialManager::getSingleton().remove(m_renderableStates[i].material->getName());
        }
        if (m_renderableStates[i].material18 && Ogre::MaterialManager::getSingleton().resourceExists(m_renderableStates[i].material18->getName())) {
            m_renderableStates[i].material18->unload();
            Ogre::MaterialManager::getSingleton().remove(m_renderableStates[i].material18->getName());
        }
        if (m_renderableStates[i].material20 && Ogre::MaterialManager::getSingleton().resourceExists(m_renderableStates[i].material20->getName())) {
            m_renderableStates[i].material20->unload();
            Ogre::MaterialManager::getSingleton().remove(m_renderableStates[i].material20->getName());
        }
    }
    if (m_pResourceManager && m_pResourceManager->getGameClient())
        m_pResourceManager->getGameClient()->m_pendingPassClear=true;
}


#include <algorithm>
#include <OgrePass.h>
#include <OgreTextureUnitState.h>
#include <OgreTechnique.h>
void CGenericModel::setLightOverride(float value)
{
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE)==1) return;
    for (unsigned int i=0;i<static_cast<unsigned int>(m_renderableStates.size());++i) {
        CRenderableStates& state=m_renderableStates[i];
        float scale=std::max(0.25f,value);
        Ogre::Pass* original=state.originalMaterial->getBestTechnique()->getPass(0);
        Ogre::ColourValue ambient=original->getAmbient();
        Ogre::ColourValue diffuse=original->getDiffuse();
        Ogre::ColourValue illumination=original->getSelfIllumination();
        ambient.r*=scale;ambient.g*=scale;ambient.b*=scale;ambient.a=1.0f;
        diffuse.r*=scale;diffuse.g*=scale;diffuse.b*=scale;diffuse.a=1.0f;
        illumination.r*=scale;illumination.g*=scale;illumination.b*=scale;illumination.a=1.0f;
        Ogre::Pass* target=state.material->getBestTechnique()->getPass(0);
        target->setAmbient(ambient);
        target->setDiffuse(diffuse);
        target->setSelfIllumination(illumination);
        if (state.material20) {
            value*=value;
            value*=value;
            if (value>0.01f) {
                state.material20->getBestTechnique()->getPass(0)->setSelfIllumination(value,value,value);
                state.m_state0=0;
            } else state.m_state0=1;
        }
    }
}

void CGenericModel::setOpacity(float opacity)
{
    if (m_opacity==opacity) return;
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE)==0) {
        for (unsigned int i=0;i<static_cast<unsigned int>(m_renderableStates.size());++i) {
            CRenderableStates& state=m_renderableStates[i];
            state.m_opacity=opacity;
            Ogre::Material* material=state.material;
            unsigned short count=material->getBestTechnique()->getNumPasses();
            for (int j=0;j<count;++j) {
                Ogre::Pass* pass=material->getBestTechnique()->getPass(j);
                if (!pass->getNumTextureUnitStates()) continue;
                pass->getTextureUnitState(0);
                if (opacity>=1.0f) {
                    if (state.spectral && j==0) pass->setSceneBlending(Ogre::SBT_ADD);
                    else if (state.m_gap2e && j==0) {
                        pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
                        pass->setAlphaRejectSettings(Ogre::CMPF_GREATER,m_gap23B?5:150,false);
                    } else if (j==0) pass->setSceneBlending(Ogre::SBT_REPLACE);
                    else pass->setSeparateSceneBlending(Ogre::SBF_SOURCE_ALPHA,Ogre::SBF_ONE,Ogre::SBF_ZERO,Ogre::SBF_ZERO);
                    if (state.spectral) pass->getTextureUnitState(0)->setColourOperation(Ogre::LBO_MODULATE);
                    else pass->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE,Ogre::LBS_TEXTURE,Ogre::LBS_CURRENT,1.0f,1.0f,0.0f);
                } else if (j==0 && state.spectral) {
                    pass->getTextureUnitState(0)->setColourOperationEx(Ogre::LBX_MODULATE,Ogre::LBS_MANUAL,Ogre::LBS_TEXTURE,Ogre::ColourValue(opacity,opacity,opacity,opacity),Ogre::ColourValue::Black,1.0f);
                } else {
                    pass->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE,Ogre::LBS_TEXTURE,Ogre::LBS_MANUAL,1.0f,opacity,1.0f);
                    if (j==0) {
                        pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
                        pass->setAlphaRejectSettings(Ogre::CMPF_GREATER,5,false);
                    } else pass->setSeparateSceneBlending(Ogre::SBF_SOURCE_ALPHA,Ogre::SBF_ONE,Ogre::SBF_ZERO,Ogre::SBF_ZERO);
                }
            }
        }
    }
    m_opacity=opacity;
}

#include "FileSystem.h"
#include <OgrePass.h>
#include <OgreTechnique.h>
#include <OgreTextureUnitState.h>
#include <OgreGpuProgram.h>

void CGenericModel::clearProjectorPass()
{
    for (unsigned int i=0;i<static_cast<unsigned int>(m_renderableStates.size());++i) {
        if (!m_renderableStates[i].m_flag31) continue;
        Ogre::Material*material=m_renderableStates[i].material;
        Ogre::Pass*pass=material->getBestTechnique()->getPass(0);
        unsigned short count=pass->getNumTextureUnitStates();
        int index=m_renderableStates[i].projectorPass;
        if (count<=index) continue;
        if (m_renderableStates[i].m_flag30 && CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHADOWS_ENABLED)) {
            unsigned short remove=index>1?index-1:count-2;
            pass->removeTextureUnitState(remove);
            pass->removeTextureUnitState(remove);
        } else pass->removeTextureUnitState(index>1?index-1:count-1);
        m_renderableStates[i].projectorTechnique=-1;
        material->compile(true);
    }
}

void CGenericModel::setHighlightTexture(const std::wstring& texture)
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(texture,info,false,true,false);
    if (info.m_bExists) {
    for (unsigned int i=0;i<static_cast<unsigned int>(m_renderableStates.size());++i) {
        Ogre::Pass* pass=m_renderableStates[i].material18->getBestTechnique()->getPass(0);
        unsigned short count=pass->getNumTextureUnitStates();
        if (count>1) {
            pass->getTextureUnitState(count-1)->setCubicTextureName(info.m_sResourceName,true);
            if (m_pResourceManager && m_pResourceManager->getGameClient())
                m_pResourceManager->getGameClient()->m_pendingPassClear=true;
        }
    }
    }
}

void CGenericModel::setRenderBehindTexture(const std::wstring& texture)
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(texture,info,false,true,false);
    if (info.m_bExists) {
    for (unsigned int i=0;i<static_cast<unsigned int>(m_renderableStates.size());++i) {
        if (!m_renderableStates[i].material20) continue;
        Ogre::Pass* pass=m_renderableStates[i].material20->getBestTechnique()->getPass(0);
        if (pass->getNumTextureUnitStates()) {
            pass->getTextureUnitState(0)->setTextureName(info.m_sResourceName,Ogre::TEX_TYPE_2D);
            if (m_pResourceManager && m_pResourceManager->getGameClient())
                m_pResourceManager->getGameClient()->m_pendingPassClear=true;
        }
    }
    }
}

void CGenericModel::setRimLighting(std::wstring texture)
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(texture,info,false,true,false);
    if (!CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_RIMLIGHTS_ENABLED)) return;
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE)==1 || !info.m_bExists) return;
    bool existed=m_flag238;
    for (unsigned int i=0;i<static_cast<unsigned int>(m_renderableStates.size());++i) {
        CRenderableStates& state=m_renderableStates[i];
        if (state.spectral || !state.material) continue;
        Ogre::Pass* pass=state.material->getBestTechnique()->getPass(0);
        if (!pass || !pass->getNumTextureUnitStates()) continue;
        Ogre::TextureUnitState* unit=existed ? pass->getTextureUnitState(pass->getNumTextureUnitStates()-1) : pass->createTextureUnitState();
        unit->setCubicTextureName(info.m_sResourceName,true);
        unit->setTextureCoordSet(1);
        unit->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
        unit->setEnvironmentMap(true,Ogre::TextureUnitState::ENV_NORMAL);
        unit->setColourOperation(Ogre::LBO_ADD);
        if (pass->hasVertexProgram())
            pass->getVertexProgramParameters()->setNamedAutoConstant("texViewProj",static_cast<Ogre::GpuProgramParameters::AutoConstantType>(0x79),0);
    }
    m_flag238=true;
}

#include "ResourceManager.h"
#include <cstring>
CGenericModel::CGenericModel(CResourceManager* resources,Ogre::SceneManager* manager,OGRE_UTILITIES::EPRIMITIVES primitive)
    :CPositionableObject(resources,manager),m_sModelPath(L""),m_modelGroup(L""),m_name(""),m_string128(""),
     m_pSkeleton(NULL),m_modelSceneManager(manager),m_animationStates(10),m_animationSet(NULL),m_animationPaused(false),m_flag1e9(false),
     m_queryMask(static_cast<OGRE_UTILITIES::EQUERYMASK>(8)),m_randomWeight(1),m_uniqueMaterials(false),m_opacity(1.0f),m_entity230(NULL),
     m_flag238(false),m_renderToLightMap(false),m_renderFlag23A(false),m_gap23B(0),m_animationLoop(true),m_animationSpeed(1.0f),m_animationPlaying(0),m_animationStep(1.0f/65.0f)
{
    std::memset(m_gap138,0,sizeof(m_gap138));
    std::memset(m_ModelData248,0,sizeof(m_ModelData248));
    m_bEnabled=true;
    if (resources) {
        if (!m_modelSceneManager) m_modelSceneManager=m_pResourceManager->getSceneManager();
        loadPrefabType(primitive);
    }
}
CGenericModel::CGenericModel(CResourceManager* resources,Ogre::SceneManager* manager,std::wstring path,std::wstring group,bool flag)
    :CPositionableObject(resources,manager),m_sModelPath(L""),m_modelGroup(L""),m_name(""),
     m_pSkeleton(NULL),m_modelSceneManager(manager),m_animationStates(10),m_animationSet(NULL),m_animationPaused(false),m_flag1e9(flag),
     m_boundsMinimum(0.0f,0.0f,0.0f),m_boundsMaximum(0.0f,0.0f,0.0f),m_queryMask(static_cast<OGRE_UTILITIES::EQUERYMASK>(2)),
     m_randomWeight(1),m_uniqueMaterials(false),m_opacity(1.0f),m_entity230(NULL),m_flag238(false),m_renderToLightMap(false),m_gap23B(0),
     m_animationLoop(true),m_animationSpeed(1.0f),m_animationPlaying(0),m_animationStep(1.0f/65.0f)
{
    std::memset(m_gap138,0,sizeof(m_gap138));
    std::memset(m_ModelData248,0,sizeof(m_ModelData248));
    if (resources) {
        m_bEnabled=true;
        if (!m_modelSceneManager) m_modelSceneManager=m_pResourceManager->getSceneManager();
        if (path!=EMPTY_WSTRING) loadModel(path,group,false,false,false);
    }
}

#include "ResourceManager.h"
#include "OgreUtilities.h"
void CGenericModel::unloadModel()
{
    if (m_animationSet) CMasterResourceManager::getSingleton()->removeAnimationSet(m_animationSet);
    m_animationSet=NULL;
    m_pSkeleton=NULL;
    m_AnimationEvents.clear();
    if (m_entity230) m_pEntity=m_entity230;
    if (m_pEntity) {
        OGRE_UTILITIES::detachEntityFromParent(m_pEntity);
        m_pResourceManager->getSceneManager()->destroyEntity(m_pEntity);
        m_pEntity=NULL;
    }
    m_sModelPath=L"";
    m_modelGroup=L"";
}

#include "OgreUtilities.h"
#include "ResourceManager.h"
#include <OgreEntity.h>
void CGenericModel::loadPrefabType(OGRE_UTILITIES::EPRIMITIVES primitive)
{
    unloadModel();
    m_sModelPath=OGRE_UTILITIES::gPRIMITIVE_NAMES[primitive];
    try {
        m_pEntity=OGRE_UTILITIES::createEntity(m_modelSceneManager,primitive,m_queryMask,"gm");
        m_name=m_pEntity->getName();
    } catch (Ogre::Exception&) {
        Ogre::LogManager::getSingleton().logMessage("[Genericmodel] Error creating entity");
    }
    m_pEntity->setCastShadows(false);
    setQueryMask(static_cast<OGRE_UTILITIES::EQUERYMASK>(8));
    sceneNodeAttachEntity(m_pEntity);
    updateOrientation();
    setRenderToLightMap(m_renderToLightMap);
}

#include <OgreEntity.h>
#include <OgreSubEntity.h>
#include <OgreSubMesh.h>
void CGenericModel::generateExtremes(unsigned long count,bool reverse)
{
    unsigned int subCount=m_pEntity->getNumSubEntities();
    std::vector<std::vector<Ogre::Vector3> > points;
    points.resize(subCount);
    for (unsigned int i=0;i<subCount;++i) {
        Ogre::SubEntity*sub=m_pEntity->getSubEntity(i);
        sub->getSubMesh()->generateExtremes(count);
        for (int j=static_cast<int>(sub->getSubMesh()->extremityPoints.size())-1;j>=0;--j)
            points[subCount-1-i].push_back(sub->getSubMesh()->extremityPoints[j]);
    }
    if (reverse) {
        for (unsigned int i=0;i<subCount;++i) {
            Ogre::SubEntity*sub=m_pEntity->getSubEntity(i);
            sub->getSubMesh()->generateExtremes(count);
            sub->getSubMesh()->extremityPoints.clear();
            for (unsigned int j=0;j<points[i].size();++j)
                sub->getSubMesh()->extremityPoints.push_back(points[i][j]);
        }
    }
}

#include "GameClient.h"
#include "ResourceManager.h"
#include <OgrePass.h>
#include <OgreTechnique.h>
#include <OgreTextureUnitState.h>
void CGenericModel::setProjectorPass(Ogre::Frustum* shadow,Ogre::Frustum* projector,const std::string& shadowTexture,const std::string& projectorTexture)
{
    for (unsigned int i=0;i<static_cast<unsigned int>(m_renderableStates.size());++i) {
        CRenderableStates& state=m_renderableStates[i];
        if (state.projectorTechnique!=-1 || !state.m_flag31) continue;
        Ogre::Pass* pass=state.material->getBestTechnique()->getPass(0);
        int index=state.projectorPass;
        bool shadows=state.m_flag30 && CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHADOWS_ENABLED);
        if (index+(shadows?2:1)<=pass->getNumTextureUnitStates()) continue;
        if (state.material18) {
            Ogre::Pass* highlight=state.material18->getBestTechnique()->getPass(0);
            if (highlight->getNumTextureUnitStates()) {
                state.material18->setLightingEnabled(false);
                state.material18->getBestTechnique()->getPass(0)->getTextureUnitState(0)->setColourOperationEx(Ogre::LBX_MODULATE_X2,Ogre::LBS_TEXTURE,Ogre::LBS_CURRENT,Ogre::ColourValue::White,Ogre::ColourValue::White,0.0f);
            }
        }
        Ogre::TextureUnitState* first=NULL;
        Ogre::TextureUnitState* second=NULL;
        if (index>1) {
            if (shadows) pass->createTextureUnitState();
            Ogre::TextureUnitState* copy=pass->createTextureUnitState();
            *copy=*pass->getTextureUnitState(index-1);
            copy->setName("");
            if (shadows) {
                first=pass->getTextureUnitState(index-1);
                second=pass->getTextureUnitState(index);
                first->setBlank();
                second->setBlank();
            } else {
                second=pass->getTextureUnitState(index-1);
                second->setBlank();
            }
        } else {
            if (shadows) first=pass->createTextureUnitState(shadowTexture,0);
            second=pass->createTextureUnitState(projectorTexture,0);
        }
        if (shadows) {
            first->setProjectiveTexturing(true,shadow);
            first->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
            first->setTextureFiltering(Ogre::FO_POINT,Ogre::FO_LINEAR,Ogre::FO_NONE);
            first->setColourOperationEx(Ogre::LBX_MODULATE_X2,Ogre::LBS_CURRENT,Ogre::LBS_TEXTURE,Ogre::ColourValue::White,Ogre::ColourValue::White,0.0f);
            if (index>1) first->setTextureName(shadowTexture,Ogre::TEX_TYPE_2D);
            first->setName("LIGHTPASS");
        }
        second->setProjectiveTexturing(true,projector);
        second->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
        second->setTextureFiltering(Ogre::FO_POINT,Ogre::FO_LINEAR,Ogre::FO_NONE);
        second->setColourOperationEx(Ogre::LBX_MODULATE_X4,shadows?Ogre::LBS_CURRENT:Ogre::LBS_TEXTURE,shadows?Ogre::LBS_TEXTURE:Ogre::LBS_CURRENT,Ogre::ColourValue::White,Ogre::ColourValue::White,0.0f);
        if (index>1) second->setTextureName(projectorTexture,Ogre::TEX_TYPE_2D);
        second->setName("LIGHTPASS");
        if (shadows) state.projectorTechnique=state.projectorPass;
        if (m_pResourceManager && m_pResourceManager->getGameClient()) m_pResourceManager->getGameClient()->m_pendingPassClear=true;
    }
}

#include <OgreSkeletonInstance.h>
#include <OgreMeshManager.h>
#include "OgreUtilities.h"
#include "StringUtilities.h"
void CGenericModel::reloadAnimations()
{
    clearAnimations();
    if (!m_animationSet) return;
    std::wstring path=m_sModelPath;
    std::wstring group=m_modelGroup;
    m_pEntity->getMesh()->unload();
    Ogre::SkeletonInstance*skeleton=m_pEntity->getSkeleton();
    if (skeleton) {
        skeleton->getNumAnimations();
        for (unsigned int i=0;i<static_cast<unsigned int>(m_animationSet->m_nUnknown);++i) {
            if (STRINGS::StringUpper(m_animationSet->m_lUnknown28[i])!="BIND")
                skeleton->removeAnimation(m_animationSet->m_lUnknown28[i]);
        }
        skeleton->unload();
    }
    if (m_pEntity) {
        OGRE_UTILITIES::detachEntityFromParent(m_pEntity);
        Ogre::MeshManager::getSingleton().remove(m_pEntity->getMesh()->getHandle());
        m_modelSceneManager->destroyEntity(m_pEntity);
    }
    m_pEntity=NULL;
    m_entity230=NULL;
    unloadModel();
    loadModel(path,group,false,false,true);
    setEnabled(true);
}

#include "FileSystem.h"
#include "FileUtilities.h"
#include "DataGroup.h"
#include <OgreSkeletonInstance.h>
#include <OgreSkeletonManager.h>
#include <OgreAnimation.h>
#include <OgreLogManager.h>
void CGenericModel::loadAnimations(Ogre::Entity* entity, std::wstring path, std::wstring group, bool merge)
{
    CFileInfo file;
    CFileSystem::getSingleton()->getFileInfo(group+path,file,false,true,false);
    if (!file.m_bExists) return;
    CDataGroup* data=new CDataGroup(L"ANIMATION",NULL,20,10,NULL);
    data->LoadFile(group+path,NULL);
    std::vector<std::string> processed;
    Ogre::SkeletonInstance* skeleton=entity->getSkeleton();
    std::vector<CDataGroup*> animations;
    unsigned int count=data->GetDataGroupsMatchingName(L"ANIMATION",&animations);
    std::wstring modelName=FILESYSTEM::GetFileName(m_sModelPath);
    for (unsigned int i=0;i<count;++i) {
        CDataGroup* animation=animations[i];
        std::wstring animationPath=animation->GetDataValue(L"FILE",L"");
        CFileInfo animationFile;
        CFileSystem::getSingleton()->getFileInfo(group+animationPath,animationFile,false,true,false);
        if (!animationFile.m_bExists) continue;
        Ogre::SkeletonPtr source=Ogre::SkeletonManager::getSingleton().load(animationFile.m_sResourceName,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,false,NULL,NULL);
        int index=m_animationSet->m_lUnknown28.size();
        std::string name=source->getAnimation(0)->getName();
        bool sameModel=modelName.substr(0,modelName.size()-5)==STRINGS::StringUpper(animationPath.substr(0,animationPath.size()-9));
        unsigned int selected=0;
        if (sameModel) {
            for (unsigned int j=0;j<source->getNumAnimations();++j) {
                if (STRINGS::StringUpper(source->getAnimation(j)->getName())=="BIND") {
                    name=source->getAnimation(j)->getName();
                    selected=j;
                }
            }
        }
        bool duplicate=false;
        if (m_pSkeleton->hasAnimation(name)) {
            for (unsigned int j=0;j<processed.size();++j) {
                if (processed[j]==name) {
                    Ogre::LogManager::getSingleton().logMessage(std::string("Animation duplicate named: ")+name+" in file "+STRINGS::StringConvertToNarrow(animationPath.c_str()),Ogre::LML_CRITICAL,false);
                    duplicate=true;
                }
            }
        }
        processed.push_back(name);
        bool bind=false;
        if (STRINGS::StringUpper(name)=="BIND") {
            for (unsigned int j=0;j<static_cast<unsigned int>(m_animationSet->m_nUnknown);++j)
                if (m_animationSet->m_lUnknown28[j]==name) {index=j;break;}
            bind=true;
        } else if (m_pSkeleton->hasAnimation(name)) {
            if (duplicate) continue;
            for (unsigned int j=0;j<static_cast<unsigned int>(m_animationSet->m_nUnknown);++j)
                if (m_animationSet->m_lUnknown28[j]==name) {index=j;break;}
            merge=false;
        }
        if (duplicate) continue;
        if (merge && !bind) {
            Ogre::Skeleton::BoneHandleMap map;
            source->_buildMapBoneByHandle(source.getPointer(),map);
            Ogre::StringVector names;
            skeleton->_mergeSkeletonAnimations(source.getPointer(),map,names);
        }
        std::string sourceName=source->getAnimation(selected)->getName();
        if (index==static_cast<int>(m_animationSet->m_lUnknown28.size())) {
            m_animationSet->m_lUnknown28.push_back(sourceName);
            m_animationSet->m_lUnknown40.push_back(animationPath);
        }
        Ogre::SkeletonManager::getSingleton().remove(STRINGS::StringConvertToUTF8(animationPath));
        if (m_animationSet->m_nUnknown>m_animationSet->m_lAnimationGroups.size())
            m_animationSet->m_lAnimationGroups.resize(m_animationSet->m_nUnknown);
        std::vector<CDataGroup*> keys;
        unsigned int keyCount=animation->GetDataGroupsMatchingName(L"KEY",&keys);
        for (unsigned int j=0;j<keyCount;++j) AddKey(index,keys[j]);
        if (merge && !bind) ++m_animationSet->m_nUnknown;
    }
    if (merge) skeleton->_refreshAnimationState(entity->getAllAnimationStates());
    delete data;
}

#include "ResourceManager.h"
#include "OgreUtilities.h"
#include "FileUtilities.h"
#include "GameUIOgreUTFString.h"
#include <OgreSkeletonInstance.h>
#include <OgreAnimation.h>
#include <OgreLogManager.h>
void CGenericModel::loadModel(std::wstring path,std::wstring group,bool animationsOnly,bool unique,bool reload)
{
    CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE);
    std::memset(m_ModelData248,0,sizeof(m_ModelData248));
    clearAnimations();
    path=STRINGS::StringUpper(path);
    group=STRINGS::StringUpper(group);
    if (path==m_sModelPath) return;
    m_uniqueMaterials=unique;
    unloadModel();
    m_sModelPath=path;
    m_modelGroup=group;
    path=FILESYSTEM::CleanPath(path);
    std::wstring directory=FILESYSTEM::RemoveFileName(path);
    std::string error;
    m_pEntity=OGRE_UTILITIES::createEntity(m_modelSceneManager,path,m_queryMask,"gm");
    if (!m_pEntity) {
        error=std::string("Unable to find file : ")+STRINGS::StringConvertToUTF8(path);
        Ogre::LogManager::getSingleton().logMessage(std::string("[Genericmodel] Error creating entity\n")+error,Ogre::LML_CRITICAL,false);
        m_sModelPath=L"";
        m_modelGroup=L"";
        m_pEntity=NULL;
        m_name="";
        return;
    }
    m_name=m_pEntity->getName();
    m_pEntity->setCastShadows(false);
    std::wstring animationBase=group;
    if (animationBase.empty()) {
        animationBase=FILESYSTEM::GetFileName(path);
        animationBase=animationBase.substr(0,animationBase.size()-5);
    } else animationBase=FILESYSTEM::GetFileName(group);
    if (m_pEntity->getSkeleton()) {
        m_pSkeleton=m_pEntity->getSkeleton();
        unsigned int animationCount=m_pSkeleton->getNumAnimations();
        std::wstring animationPath=directory+animationBase+L".animation";
        CAnimationSet* previous=m_animationSet;
        m_animationSet=CMasterResourceManager::getSingleton()->getAnimationSet(animationPath);
        if (!previous && m_animationSet) ++m_animationSet->m_nAnimationCount;
        if (reload && m_animationSet) m_animationSet->clear();
        bool initialize=m_animationSet==NULL;
        if (initialize) {
            m_animationSet=new CAnimationSet;
            CMasterResourceManager::getSingleton()->addAnimationSet(m_animationSet);
        }
        if (initialize || reload) {
            m_animationSet->m_wsName=animationPath;
            m_animationSet->m_nUnknown=animationCount;
            for (unsigned int i=0;i<static_cast<unsigned int>(m_animationSet->m_nUnknown);++i) {
                std::string name=m_pSkeleton->getAnimation(i)->getName();
                m_animationSet->m_lUnknown28.push_back(name);
                if (STRINGS::StringUpper(name)=="BIND")
                    m_animationSet->m_lUnknown40.push_back(animationBase+L".SKELETON");
                else m_animationSet->m_lUnknown40.push_back((Ogre::UTFString(name)+Ogre::UTFString(L".SKELETON")).asWStr());
            }
            loadAnimations(m_pEntity,animationBase+L".animation",directory,true);
            m_animationSet->m_lAnimationGroups.resize(m_animationSet->m_nUnknown);
        }
    }
    for (unsigned int i=0;i<m_valueIndexes.size();++i) {
        for (unsigned int j=0;j<m_valueIndexes[i].size();++j) m_valueIndexes[i][j].clear();
        m_valueIndexes[i].clear();
    }
    m_valueIndexes.clear();
    if (m_animationSet) {
        m_valueIndexes.resize(m_animationSet->m_lAnimationGroups.size());
        for (unsigned int i=0;i<m_animationSet->m_lAnimationGroups.size();++i)
            m_valueIndexes[i].resize(m_animationSet->m_lAnimationGroups[i].size());
    }
    if (m_pSkeleton && animationsOnly) return;
    reInitialize(m_pEntity,true);
    updateOrientation();
    Ogre::AxisAlignedBox box=m_pEntity->getBoundingBox();
    m_boundsMinimum=box.getMinimum();
    m_boundsMaximum=box.getMaximum();
    setRenderToLightMap(m_renderToLightMap);
}

#include "ResourceManager.h"
#include <OgreAnimationState.h>
void CGenericModel::updateAnimation(float elapsed,bool force)
{
    if (!m_pEntity) return;
    if (!getEnabled() && elapsed!=1000.f) {m_AnimationEvents.clear();return;}
    if (m_animationPaused) elapsed=0.f;
    if (m_activeAnimations.empty()) {m_AnimationEvents.clear();return;}
    if (m_pResourceManager->m_bFlag0) force=true;
    else if (!force && m_activeAnimations.size()==1 && m_activeAnimations[0]->m_flag28) {m_AnimationEvents.clear();return;}
    m_AnimationEvents.clear();
    std::vector<float> weights;
    std::vector<int> indexes;
    float total=0.f;
    bool stopWeights=false,stopFollowing=false,updated=false;
    for (int i=0;i<static_cast<int>(m_activeAnimations.size());++i) {
        CActiveAnimation* active=m_activeAnimations[i];
        unsigned int animation=active->m_animation;
        bool skip=false;
        if (active->m_queued && elapsed!=0.f && (i==static_cast<int>(m_activeAnimations.size())-1 || !m_activeAnimations[i+1]->m_queued)) {
            bool start=i==static_cast<int>(m_activeAnimations.size())-1 || !m_activeAnimations[i+1]->m_playing;
            if (!start) {
                CActiveAnimation* next=m_activeAnimations[i+1];
                float remaining=next->m_flag27?0.f:next->m_length-next->m_time;
                remaining/=next->m_speed;
                start=active->m_blendDuration>=remaining-elapsed;
                skip=!start;
            }
            if (start) {
                active->m_playing=true;
                active->m_queued=false;
                active->m_weight=0.f;
                m_animationStates[animation]->setEnabled(true);
                m_animationStates[animation]->setTimePosition(active->m_time);
            }
        }
        if (skip && elapsed!=0.f) continue;
        if (i>0 && elapsed!=0.f) active->m_flag2a=true;
        float previousTime=active->m_time;
        bool playing=active->m_playing;
        active->m_flag27=false;
        float target=1.f;
        if (active->m_playing) {
            if (active->m_blendRemaining>0.f) {
                active->m_blendRemaining-=elapsed;
                active->m_weight=1.f;
                if (active->m_blendDuration!=0.f && active->m_blendRemaining>0.f)
                    active->m_weight=std::min(active->m_blendRemaining/active->m_blendDuration,1.f);
                if (active->m_blendRemaining<=0.f) {
                    active->m_flag29=true;
                    active->m_weight=0.f;
                    active->m_blendRemaining=0.f;
                }
            }
            active->m_time+=elapsed*active->m_speed;
            if (active->m_length==0.f) {
                active->m_time=0.f;
                if (active->m_loop) active->m_flag27=true;
                else {active->m_playing=false;active->m_flag28=true;active->m_flag29=true;}
            } else if (active->m_time>active->m_length) {
                do {
                    active->m_time-=active->m_length;
                    if (!active->m_loop) {
                        active->m_time=active->m_length;
                        active->m_playing=false;
                        active->m_flag28=true;
                        active->m_flag29=true;
                        break;
                    }
                } while (active->m_time>active->m_length);
                if (active->m_loop) active->m_flag27=true;
            }
        }
        float time=active->m_time;
        float weight=target-active->m_weight;
        if (weight!=0.f && (active->m_playing || playing || force || previousTime!=time)) {
            m_animationStates[animation]->setTimePosition(time);
            updated=true;
        }
        weight-=total;
        total+=weight;
        if (!stopWeights && weight!=0.f) {
            if (force || previousTime!=time) {weights.push_back(weight);indexes.push_back(animation);}
        } else if (weight!=0.f && active->m_playing && (force || previousTime!=time)) m_animationStates[animation]->setWeight(weight);
        if (weight==target) stopWeights=stopWeights||active->m_flag2a;
        if (playing && animation!=static_cast<unsigned int>(-1) && elapsed!=0.f && m_animationSet) {
            for (int j=0;j<static_cast<int>(m_animationSet->m_lAnimationGroups[animation].size());++j) {
                float key=m_animationSet->m_lAnimationGroups[animation][j]->m_frame/30.f;
                if ((key>=previousTime && key<=time) || (previousTime>time && (key>=previousTime || key<=time)))
                    m_AnimationEvents.push_back(getKeyFrame(animation,j));
            }
        }
        if (stopFollowing && elapsed!=0.f) active->m_flag28=true;
        if (active->m_flag29) stopFollowing=stopFollowing || elapsed!=0.f;
    }
    float factor=2.f;
    if (total<1.f && total!=0.f) factor=1.f-total;
    for (unsigned int i=0;i<indexes.size();++i) m_animationStates[indexes[i]]->setWeight(weights[i]*factor);
    if (elapsed!=0.f) {
        for (int i=1;i<static_cast<int>(m_activeAnimations.size());++i) {
            CActiveAnimation* active=m_activeAnimations[i];
            if (!active->m_flag28) continue;
            bool found=false;
            for (int j=0;j<i;++j) if (m_activeAnimations[j]->m_animation==active->m_animation) {found=true;break;}
            if (!found) m_animationStates[active->m_animation]->setEnabled(false);
            if (active->m_length>active->m_time && m_animationSet) {
                unsigned int animation=active->m_animation;
                for (int j=0;j<static_cast<int>(m_animationSet->m_lAnimationGroups[animation].size());++j) {
                    CKeyframe* key=getKeyFrame(animation,j);
                    if (key->m_frame/30.f>active->m_time) {
                        int event=key->getEventCode();
                        if (event==13 || event==12 || event==23 || event==25 || event==17 || event==19 || event==20 || event==8 || event==10)
                            m_AnimationEvents.push_back(key);
                    }
                }
            }
            delete active;
            m_activeAnimations[i]=NULL;
            m_activeAnimations[i]=m_activeAnimations.back();
            m_activeAnimations.pop_back();
            --i;
            updated=true;
        }
    }
    if (updated || force || (!m_activeAnimations.empty() && (m_activeAnimations.size()!=1 || !m_activeAnimations[0]->m_flag28))) m_pEntity->_updateAnimation();
}

#include "FileSystem.h"
#include <OgreMaterialManager.h>
#include <OgreSubEntity.h>
#include <OgrePass.h>
#include <OgreTechnique.h>
#include <OgreGpuProgram.h>
#include <OgreTextureUnitState.h>
#include <OgreMesh.h>
#include <OgreAnimationState.h>

void CGenericModel::reInitialize(Ogre::Entity* entity, bool initializeMaterials)
{
    unsigned int count = entity->getNumSubEntities();
    if (initializeMaterials)
    {
        m_flag238 = false;
        releaseUniqueMaterials();
        m_renderableStates.clear();
        CRenderableStates initial = CRenderableStates();
        initial.m_state0 = 1;
        initial.projectorTechnique = -1;
        initial.projectorPass = 1;
        initial.m_flag31 = true;
        initial.m_opacity = 1;
        m_renderableStates.resize(count, initial);
        for (unsigned int i = 0; i < count; ++i)
        {
            Ogre::SubEntity* sub = entity->getSubEntity(i);
            CRenderableStates& state = m_renderableStates[i];
            sub->setUserAny(Ogre::Any(&state));
            state.material = sub->getMaterial().getPointer();
            Ogre::Pass* pass = state.material->getBestTechnique()->getPass(0);
            int textureCount = pass->getNumTextureUnitStates();
            int regularTextures = textureCount;
            for (int j = 1; j < textureCount; ++j)
                if (pass->getTextureUnitState(j)->getName() == "LIGHTPASS") --regularTextures;
            state.projectorPass = regularTextures;
            state.name = state.material->getName();
            std::string highlight;
            bool newHighlight = false;
            if (m_uniqueMaterials)
            {
                highlight = STRINGS::uniqueName("highlightmat_");
                if (Ogre::MaterialManager::getSingleton().resourceExists(highlight))
                    state.material18 = static_cast<Ogre::Material*>(Ogre::MaterialManager::getSingleton().getByName(highlight).getPointer());
                else
                {
                    state.material18 = state.material->clone(highlight).getPointer();
                    pass = state.material18->getBestTechnique()->getPass(0);
                    if (pass->getNumTextureUnitStates())
                    {
                        pass = state.material18->getBestTechnique()->getPass(0);
                        if (pass->hasVertexProgram()) pass->setVertexProgram("");
                        if (state.spectral)
                            state.material18->getBestTechnique()->getPass(0)->getTextureUnitState(0)->setColourOperationEx(
                                Ogre::LBX_MODULATE_X4, Ogre::LBS_TEXTURE, Ogre::LBS_CURRENT, Ogre::ColourValue::White, Ogre::ColourValue::White, 0);
                        else
                        {
                            if (m_flag238)
                            {
                                int remaining = std::max(regularTextures - 1, 1);
                                while (state.material18->getBestTechnique()->getPass(0)->getNumTextureUnitStates() > remaining)
                                {
                                    unsigned short last = state.material18->getBestTechnique()->getPass(0)->getNumTextureUnitStates() - 1;
                                    state.material18->getBestTechnique()->getPass(0)->removeTextureUnitState(last);
                                }
                            }
                            Ogre::TextureUnitState* texture = state.material18->getBestTechnique()->getPass(0)->createTextureUnitState();
                            CFileInfo file;
                            CFileSystem::getSingleton()->getFileInfo(L"media/sharedtextures/highlight.dds", file, false, true, false);
                            texture->setCubicTextureName(file.m_sResourceName, true);
                            texture->setTextureCoordSet(1);
                            texture->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
                            texture->setEnvironmentMap(true, Ogre::TextureUnitState::ENV_NORMAL);
                            texture->setColourOperation(Ogre::LBO_ADD);
                        }
                    }
                    newHighlight = true;
                }
            }
            else
            {
                highlight = "highlightmat_" + state.material->getName();
                if (Ogre::MaterialManager::getSingleton().resourceExists(highlight))
                    state.material18 = static_cast<Ogre::Material*>(Ogre::MaterialManager::getSingleton().getByName(highlight).getPointer());
                else
                {
                    state.material18 = state.material->clone(highlight).getPointer();
                    state.material18->setLightingEnabled(false);
                    pass = state.material18->getBestTechnique()->getPass(0);
                    if (pass->getNumTextureUnitStates())
                        state.material18->getBestTechnique()->getPass(0)->getTextureUnitState(0)->setColourOperationEx(
                            Ogre::LBX_MODULATE_X2, Ogre::LBS_TEXTURE, Ogre::LBS_CURRENT, Ogre::ColourValue::White, Ogre::ColourValue::White, 0);
                    newHighlight = true;
                }
            }
            if (state.material->getBestTechnique())
            {
                if (STRINGS::StringUpper(state.name.c_str()).find("SPECTRAL") != std::string::npos)
                {
                    state.spectral = true;
                    m_renderFlag23A = true;
                }
                if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_ALLOW_HWSKINNING) == 1)
                {
                    pass = state.material->getBestTechnique()->getPass(0);
                    bool oldSkinning = state.m_state2;
                    if (pass->hasVertexProgram() && pass->getVertexProgram()->isSkeletalAnimationIncluded())
                    {
                        state.m_state2 = true;
                        state.m_value2c = entity->getMesh()->getMaxBoneAssignments();
                    }
                    else if (m_pSkeleton && m_flag1e9 && !oldSkinning)
                    {
                        state.m_value2c = entity->getMesh()->getMaxBoneAssignments();
                        if (state.m_value2c)
                        {
                            const char* names[] = {"Ogre/HardwareSkinning", "Ogre/HardwareSkinningOne", "Ogre/HardwareSkinningTwo", "Ogre/HardwareSkinningThree"};
                            const char* secondary[] = {"Ogre/HardwareSkinningSecondary", "Ogre/HardwareSkinningOneSecondary", "Ogre/HardwareSkinningTwoSecondary", "Ogre/HardwareSkinningThreeSecondary"};
                            unsigned int bones = state.m_value2c < 4 ? state.m_value2c : 0;
                            pass->setVertexProgram(regularTextures > 1 ? secondary[bones] : names[bones]);
                            pass->getVertexProgramParameters()->setNamedAutoConstant("texViewProj",
                                static_cast<Ogre::GpuProgramParameters::AutoConstantType>(0x79), 0);
                            state.material->compile(true);
                            pass = state.material->getBestTechnique()->getPass(0);
                            if (pass->hasVertexProgram() && pass->getVertexProgram()->isSkeletalAnimationIncluded()) state.m_state2 = true;
                        }
                    }
                    if (state.m_state2 && newHighlight && state.m_value2c && !oldSkinning)
                    {
                        const char* names[] = {"Ogre/HardwareSkinning", "Ogre/HardwareSkinningOne", "Ogre/HardwareSkinningTwo", "Ogre/HardwareSkinningThree"};
                        const char* secondary[] = {"Ogre/HardwareSkinningSecondary", "Ogre/HardwareSkinningOneSecondary", "Ogre/HardwareSkinningTwoSecondary", "Ogre/HardwareSkinningThreeSecondary"};
                        unsigned int bones = state.m_value2c < 4 ? state.m_value2c : 0;
                        state.material18->getBestTechnique()->getPass(0)->setVertexProgram(regularTextures > 1 ? secondary[bones] : names[bones]);
                        state.material18->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedAutoConstant("texViewProj",
                            static_cast<Ogre::GpuProgramParameters::AutoConstantType>(0x79), 0);
                        state.material18->compile(true);
                    }
                }
            }
            if (m_uniqueMaterials)
            {
                state.castsShadows = true;
                if (entity) entity->setVisibilityFlags(4);
            }
            else
            {
                std::string name = state.material->getName();
                if (name.find("shadow") != std::string::npos) state.m_flag30 = true;
                if (name.find("nolight") != std::string::npos) state.m_flag31 = false;
            }
            state.originalMaterial = state.material;
            if (m_uniqueMaterials)
            {
                std::string name = STRINGS::uniqueName(state.material->getName() + "litmat_");
                state.material = state.material->clone(name).getPointer();
                sub->setMaterialName(name);
                if (state.material->getBestTechnique()) state.m_gap2e = state.material->isTransparent();
                name = STRINGS::uniqueName("rbmat_");
                Ogre::MaterialPtr behind = Ogre::MaterialManager::getSingleton().create(name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
                state.material20 = behind.getPointer();
                state.material20->setReceiveShadows(false);
                pass = state.material20->getTechnique(0)->getPass(0);
                pass->setSelfIllumination(0, 0, 0);
                pass->setAmbient(Ogre::ColourValue(0, 0, 0, 1));
                pass->setDiffuse(Ogre::ColourValue(0, 0, 0, 1));
                pass->setDepthWriteEnabled(false);
                CFileInfo file;
                CFileSystem::getSingleton()->getFileInfo(L"media/sharedTextures/outlineblue.dds", file, false, true, false);
                pass->createTextureUnitState(file.m_sResourceName, 0);
                pass->setMaxSimultaneousLights(0);
                pass->setFog(true, Ogre::FOG_NONE, Ogre::ColourValue::White, .001f, 0, 1);
                pass->getTextureUnitState(0)->setEnvironmentMap(true, Ogre::TextureUnitState::ENV_CURVED);
                state.material20->getTechnique(0)->setDepthFunction(Ogre::CMPF_GREATER);
                state.material20->getTechnique(0)->setDepthWriteEnabled(false);
                state.material20->setSceneBlending(Ogre::SBT_ADD);
                if (state.m_state2 && state.m_value2c)
                {
                    const char* names[] = {"Ogre/HardwareSkinningBehind", "Ogre/HardwareSkinningBehindOne", "Ogre/HardwareSkinningBehindTwo", "Ogre/HardwareSkinningBehindThree"};
                    pass->setVertexProgram(names[state.m_value2c < 4 ? state.m_value2c : 0]);
                }
                state.material20->compile(true);
            }
        }
    }
    if (getEntity() != entity)
    {
        if (!m_entity230) m_entity230 = getEntity();
        m_pEntity = NULL;
    }
    sceneNodeAttachEntity(entity);
    if (!m_pSkeleton) return;
    m_pSkeleton = entity->getSkeleton();
    if (!m_animationStates.size())
    {
        if (m_animationSet)
        {
            for (unsigned int i = 0; i < static_cast<unsigned int>(m_animationSet->m_nUnknown); ++i)
                m_animationStates.add(entity->getAnimationState(m_animationSet->m_lUnknown28[i]));
            playAnimation("IDLE", true, 1, -1);
        }
        return;
    }
    if (!m_animationSet) return;
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_animationSet->m_nUnknown); ++i)
        m_animationStates[i] = entity->getAnimationState(m_animationSet->m_lUnknown28[i]);
    for (int i = 0; i < static_cast<int>(m_activeAnimations.size()); ++i)
    {
        CActiveAnimation* animation = m_activeAnimations[i];
        if (!animation->m_flag28)
        {
            m_animationStates[animation->m_animation]->setEnabled(true);
            m_animationStates[animation->m_animation]->setTimePosition(animation->m_time);
        }
    }
    updateAnimation(0, true);
}
