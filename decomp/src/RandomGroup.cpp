#include "EmptyStrings.h"
#include "GameEnums.h"
#include "RandomGroup.h"
#include "PositionableObject.h"
#include "ResourceManager.h"

void CRandomGroup::SetRandomType(unsigned int randomType)
{
    if (randomType <= 2) {
        m_iRandomType = randomType;
    }
}

bool CRandomGroup::canGroupBeCreatedBasedOffOfDungeon()
{
    struct ResourceManagerLayout {
        unsigned char padding[0x43];
        bool ignoreRestrictions;
    };

    struct LevelLayout {
        unsigned char padding[0x280];
        std::wstring dungeonName;
    };

    if (m_sDungeonForGroup.empty())
        return true;

    if (m_pResourceManager->getEditorIsRunning())
        return true;

    const ResourceManagerLayout* resourceManager =
        reinterpret_cast<const ResourceManagerLayout*>(m_pResourceManager);

    if (resourceManager->ignoreRestrictions)
        return true;

    const LevelLayout* level =
        reinterpret_cast<const LevelLayout*>(m_pResourceManager->getLevel());

    if (level == NULL)
        return true;

    return level->dungeonName.empty() ||
           level->dungeonName == m_sDungeonForGroup;
}

bool CRandomGroup::getGroupCanBeCreated()
{
    if (reinterpret_cast<const unsigned char*>(m_pResourceManager)[0x43])
        return true;

    return canGroupBeCreatedBasedOffOfPlayerClass() &&
           canGroupBeCreatedBasedOffOfQuests() &&
           canGroupBeCreatedBasedOffOfDungeon() &&
           canGroupBeCreatedBasedOffOfDifficulty();
}

CRandomGroup::CRandomGroup(CResourceManager* resourceManager)
    : CPositionableObject(resourceManager, NULL),
      m_bPropagatePosition(true),
      m_iMinimumChildren(0),
      m_iMaximumChildren(0),
      m_iChildSelectionLimit(0),
      m_iChildSpawnLimit(0),
      m_iRandomType(0),
      m_iRandomWeight(1),
      m_iNumberOfPicks(1),
      m_lastPosition(0.0f, 0.0f, 0.0f),
      m_children(10),
      m_bIsDynamicGroup(true),
      m_sPlayerClassName(EMPTY_WSTRING),
      m_sDungeonForGroup(EMPTY_WSTRING),
      m_iDifficulty(-1)
{
    setVisible(true);
}

CRandomGroup::~CRandomGroup()
{
}

#include "EditorScene.h"
#include "Layout.h"
#include "Randomizer.h"
#include "Utilities.h"

void CRandomGroup::calculateChildren()
{
    if (!getSceneOwner() || !m_pResourceManager || !m_bIsDynamicGroup)
        return;

    TArrayList<CLayout*> layouts(10);
    std::map<long long, CEditorBaseObject*>& objects = getSceneOwner()->getObjects();
    for (std::map<long long, CEditorBaseObject*>::iterator i = objects.begin(); i != objects.end(); ++i) {
        if (!i->second->isChildOfObject(getGuid()))
            continue;
        CPositionableObject* object = dynamic_cast<CPositionableObject*>(i->second);
        if (object) {
            CLayout* layout = dynamic_cast<CLayout*>(object);
            if (layout)
                layouts.add(layout);
            m_children.add(object);
        }
    }

    for (unsigned int i = 0; i < layouts.size(); ++i) {
        for (unsigned int j = 0; j < m_children.size(); ++j) {
            if (layouts[i] && m_children[j]->isChildOfObject(layouts[i]->getGuid())) {
                m_children.removeAt(j);
                --j;
            }
        }
    }

    if (!m_pResourceManager->getEditorIsRunning()) {
        Ogre::Vector3 position = getPosition(false);
        for (unsigned int i = 0; i < m_children.size(); ++i) {
            m_children[i]->CPositionableObject::setPosition(m_children[i]->getPosition(false) - position);
            m_children[i]->setParentPositionableObject(this);
        }
        m_children.clear();
    }
}

void CRandomGroup::chooseChildrenByRandomChoice(
    TArrayList<CRandomGroup*>& randomGroups,
    TArrayList<CEditorBaseObject*>& editorObjects)
{
    if (randomGroups.size() == 0 || !getGroupCanBeCreated())
        return;

    unsigned int type = m_iRandomType;
    if (type != 0 && !m_pResourceManager->m_bFlag3) {
        CRandomizer randomizer(RANDOMIZER_NORMAL);
        int picks = m_iNumberOfPicks;
        for (unsigned int i = 0; i < randomGroups.size(); ++i) {
            CRandomGroup* group = randomGroups[i];
            if (group) {
                int weight = group->GetRandomWeight();
                if (type == 1) {
                    if (weight > 0)
                        randomizer.addChoice(i, weight);
                    else
                        editorObjects.add(group);
                } else {
                    if (weight > 0 && weight < 100) {
                        if (weight >= UTILITIES::randomBetween(1.0f, 100.0f)) {
                            editorObjects.add(group);
                            if (--picks == 0)
                                break;
                        }
                    } else {
                        editorObjects.add(group);
                    }
                }
            }
        }

        if (type == 1) {
            for (unsigned int i = 0; i < static_cast<unsigned int>(picks); ++i) {
                int choice = randomizer.getRandom();
                editorObjects.add(randomGroups[choice]);
                randomizer.removeChoice(choice);
                if (randomizer.getChoiceCount() == 0)
                    break;
            }
        }
    } else {
        for (unsigned int i = 0; i < randomGroups.size(); ++i)
            editorObjects.add(randomGroups[i]);
    }
}

void CRandomGroup::setVisible(bool visible)
{
    if (getVisible() != visible) {
        CSceneNodeObject::setVisible(visible);
        if (getSceneOwner() && getSceneOwner()->getEnabled() && m_bIsDynamicGroup)
            static_cast<CEditorScene*>(getSceneOwner())->setChildrenVisible(getGuid(), visible);
    }
}

#include "GameClient.h"
#include "QuestManager.h"
#include "Level.h"
bool CRandomGroup::canGroupBeCreatedBasedOffOfPlayerClass()
{
    if (m_pResourceManager->m_bFlag3 || m_sPlayerClassName.empty()) return true;
    if (!m_pResourceManager->getGameClient()) return false;
    return m_pResourceManager->getGameClient()->getPlayerClassName()==m_sPlayerClassName;
}
bool CRandomGroup::canGroupBeCreatedBasedOffOfDifficulty()
{
    if (static_cast<unsigned int>(m_iDifficulty)>3) return true;
    if (m_pResourceManager->getEditorIsRunning() || m_pResourceManager->m_bFlag3) return true;
    if (!m_pResourceManager->getGameClient()) return true;
    return m_pResourceManager->getGameClient()->m_startDifficulty==m_iDifficulty;
}
bool CRandomGroup::canGroupBeCreatedBasedOffOfQuests()
{
    if (m_pResourceManager->m_bFlag3) return true;
    if (!m_sQuestHasToBeComplete.empty() && !CQuestManager::getSingleton()->getQuestComplete(m_sQuestHasToBeComplete)) return false;
    if (!m_sQuestNotComplete.empty() && CQuestManager::getSingleton()->getQuestComplete(m_sQuestNotComplete)) return false;
    if (!m_sQuestHasToBeActive.empty() && !CQuestManager::getSingleton()->getQuestIsActive(m_sQuestHasToBeActive)) return false;
    if (!m_sQuestHasToBeActiveOrComplete.empty() && !CQuestManager::getSingleton()->getQuestIsActive(m_sQuestHasToBeActiveOrComplete) && !CQuestManager::getSingleton()->getQuestComplete(m_sQuestHasToBeActiveOrComplete)) return false;
    if (!m_sQuestCannotBeActiveOrComplete.empty()) {
        if (CQuestManager::getSingleton()->getQuestIsActive(m_sQuestCannotBeActiveOrComplete)) return false;
        return !CQuestManager::getSingleton()->getQuestComplete(m_sQuestCannotBeActiveOrComplete);
    }
    return true;
}
void CRandomGroup::positionUpdated(const Ogre::Vector3& position)
{
    if (!m_pResourceManager->getEditorIsRunning()) return;
    if (!m_bIsDynamicGroup) {
        if (position!=Ogre::Vector3::ZERO) CPositionableObject::setPosition(Ogre::Vector3::ZERO);
        return;
    }
    Ogre::Vector3 delta=position-m_lastPosition;
    if (delta!=Ogre::Vector3::ZERO && m_bPropagatePosition) {
        if (m_pResourceManager->getEditorIsRunning()) m_children.clear();
        if (m_pResourceManager->getEditorIsRunning() || (m_pResourceManager->getLevel() && m_pResourceManager->getLevel()->m_automapRoomPieces)) {
            if (m_children.size()==0) calculateChildren();
            for (unsigned int i=0;i<m_children.size();++i) {
                CRandomGroup* child=NULL;
                if (m_children[i]->getDescriptor()==getDescriptor()) {
                    child=dynamic_cast<CRandomGroup*>(m_children[i]);
                    if (child) child->m_bPropagatePosition=false;
                }
                m_children[i]->CPositionableObject::setPosition(m_children[i]->getPosition(false)+delta);
                if (child) child->m_bPropagatePosition=true;
            }
        }
    }
    m_lastPosition=position;
}
