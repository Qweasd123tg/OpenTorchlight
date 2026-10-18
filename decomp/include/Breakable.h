#ifndef BREAKABLE_H
#define BREAKABLE_H
#include "Item.h"
class CGenericModel;
class CCollisionModel;
class CParticle;
class CBreakable : public CItem
{
public:
    CBreakable(CResourceManager* resources);
    virtual ~CBreakable();
    virtual void setActiveInLevel(bool active);
    virtual void* getUnitModel() { return m_pUnitModel; }
    virtual void* getUnitCollisionModel() { return m_collisionModel; }
    virtual void unitInit(CDataGroup* data, bool initialize);
    virtual void update(Ogre::Camera* camera, const Ogre::Vector3& position, float elapsed);
    virtual bool interact(CCharacter* character);
    virtual void setRimlight(std::wstring texture);
private:
    bool m_interacted; // +0x22c, reused CItem tail padding
    CGenericModel* m_pUnitModel; // +0x230
    CCollisionModel* m_collisionModel; // +0x238
    CParticle* m_particle; // +0x240
};
#endif
