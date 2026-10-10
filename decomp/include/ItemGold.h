#ifndef ITEM_GOLD_H
#define ITEM_GOLD_H
#include "Item.h"
class CGenericModel;
class CParticle;
// Full 0x288-byte extent; derived state reuses CItem's tail padding at 0x22c.
class CItemGold : public CItem
{
public:
    virtual ~CItemGold();
    virtual void setActiveInLevel(bool);
    virtual CGenericModel* getUnitModel();
    virtual void* getUnitCollisionModel();
    virtual void unitInit(CDataGroup*,bool);
    virtual void update(Ogre::Camera*,const Ogre::Vector3&,float);
    virtual void fillSaveState(CItemSaveState&,int,bool);
    virtual void applySaveState(CItemSaveState&);
    void unloadModel();
    void loadModel(std::wstring name);
    void playDropSound(Ogre::SceneNode* node);
    void playTakeSound(Ogre::SceneNode* node);
private:
    int m_goldAmount;
    float m_goldScale;
    float m_scaleTime;
    CGenericModel* m_goldModel;
    unsigned char m_unrecovered240[0x40];
    CParticle* m_goldParticle;
};
#endif
