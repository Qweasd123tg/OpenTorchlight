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
