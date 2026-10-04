#ifndef RANDOMGROUP_H
#define RANDOMGROUP_H

#include <OgreVector3.h>
#include <string>

#include "EditorBaseObject.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "TArrayList.h"
#include "iRandomWeight.h"

class CRandomGroup : public CPositionableObject, public iRandomWeight
{
public:
    virtual ~CRandomGroup();

    virtual void setVisible(bool visible);
    virtual void positionUpdated(const Ogre::Vector3& position);

    virtual unsigned int GetRandomWeight()
    {
        return m_iRandomWeight;
    }

    virtual void SetRandomWeight(unsigned int randomWeight)
    {
        m_iRandomWeight = randomWeight;
    }

    void SetRandomType(unsigned int randomType);
    bool canGroupBeCreatedBasedOffOfPlayerClass();
    bool canGroupBeCreatedBasedOffOfQuests();
    bool canGroupBeCreatedBasedOffOfDifficulty();
    bool canGroupBeCreatedBasedOffOfDungeon();
    bool getGroupCanBeCreated();
    void calculateChildren();

    CRandomGroup(CResourceManager* resourceManager);

    void chooseChildrenByRandomChoice(
        TArrayList<CRandomGroup*>& randomGroups,
        TArrayList<CEditorBaseObject*>& editorObjects);

    bool m_bPropagatePosition;
    unsigned char m_gap109[3];

    int m_iMinimumChildren;
    int m_iMaximumChildren;
    int m_iChildSelectionLimit;
    int m_iChildSpawnLimit;

    unsigned int m_iRandomType;
    unsigned int m_iRandomWeight;
    int m_iNumberOfPicks;

    Ogre::Vector3 m_lastPosition;

    TArrayList<CPositionableObject*> m_children;

    bool m_bIsDynamicGroup;
    unsigned char m_gap151[7];

    std::wstring m_sQuestHasToBeComplete;
    std::wstring m_sQuestHasToBeActive;
    std::wstring m_sQuestCannotBeActiveOrComplete;
    std::wstring m_sQuestHasToBeActiveOrComplete;
    std::wstring m_sQuestNotComplete;

    std::wstring m_sPlayerClassName;
    std::wstring m_sDungeonForGroup;
    int m_iDifficulty;

public:
    // Inline accessors behind the descriptors' property functions.
    void setIsDynamicGroup(bool value) { m_bIsDynamicGroup = value; }
    void SetNumberOfPicks(int value) { m_iNumberOfPicks = value; }
    void setDifficulty(int value) { m_iDifficulty = value; }
    int getDifficulty() const { return m_iDifficulty; }
    unsigned int GetRandomType() const { return m_iRandomType; }
    int GetNumberOfPicks() const { return m_iNumberOfPicks; }
    bool getIsDynamicGroup() const { return m_bIsDynamicGroup; }
};

#endif
