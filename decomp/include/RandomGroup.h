#ifndef RANDOMGROUP_H
#define RANDOMGROUP_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

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
    virtual void setVisible(bool);
    virtual void positionUpdated(const Ogre::Vector3&);
    virtual unsigned int GetRandomWeight();
    virtual void SetRandomWeight(unsigned int);
    void SetRandomType(unsigned int);
    long long canGroupBeCreatedBasedOffOfPlayerClass();
    unsigned int canGroupBeCreatedBasedOffOfQuests();
    int canGroupBeCreatedBasedOffOfDifficulty();
    long long canGroupBeCreatedBasedOffOfDungeon();
    long long getGroupCanBeCreated();
    void calculateChildren();
    CRandomGroup(CResourceManager*);
    void chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&);

    // fields
    bool m_bUnknown108;
    unsigned char m_gap109[0x3];
    int m_iUnknown10C;
    int m_iUnknown110;
    int m_iUnknown114;
    int m_iUnknown118;
    unsigned int m_iGetRandomType;
    unsigned int m_iRandomWeight;
    int m_iSetNumberOfPicks;
    int m_iUnknown128;
    int m_iUnknown12C;
    int m_iUnknown130;
    unsigned char m_gap134[0x4] __attribute__((aligned(4)));
    unsigned char m_Unknown138[0x18] __attribute__((aligned(8)));
    bool m_bIsDynamicGroup;
    unsigned char m_gap151[0x7];
    std::wstring m_sQuestHasToBeComplete;
    std::wstring m_sQuestHasToBeActive;
    std::wstring m_sQuestCannotBeActiveOrComplete;
    std::wstring m_sQuestHasToBeActiveOrComplete;
    std::wstring m_sQuestNotComplete;
    void* m_pPlayerClassName;
    void* m_pDungeonForGroup;
    int m_iDifficulty;
};

#endif
