#ifndef ITEM_H
#define ITEM_H
#include "BaseUnit.h"
namespace CEGUI { class Window; }
class CItemSaveState;
class CSoundBank;

class CItem : public CBaseUnit
{
public:
    CItem(CResourceManager* resourceManager);
    virtual ~CItem();
    virtual void setVisible(bool visible);
    virtual void unitInit(CDataGroup* data, bool initialize);
    virtual void update(Ogre::Camera* camera, const Ogre::Vector3& cameraPosition, float elapsed);
    virtual void setHighlighted(bool highlighted);
    virtual bool interact(CCharacter* character);
    virtual void updateAnimation(float elapsed);
    virtual void fillSaveState(CItemSaveState& state, int index, bool flag);
    virtual void applySaveState(CItemSaveState& state);
    virtual const std::wstring& getItemName() { return m_sItemName; }
    virtual void setItemTextHighlighted(bool highlighted);
    virtual bool isMagical() { return false; }
    virtual void setRimlight(std::wstring texture);
    virtual void setVisible(bool visible, bool immediate);
    void calculateActiveRange(const Ogre::Vector3& position);
    void snapToGround();
    void hideItemText();
    void showItemText();
    void updateOpacity(float elapsed, bool force);
    void destroyItemText();
    bool isUseable() { return ISA(UNITTYPES::CONSUMABLE) || ISA(UNITTYPES::INTERACTABLE); }

protected:
    CSoundBank* m_pSoundBank;
    float m_fForcedActiveTime;
    CEGUI::Window* m_pItemText;
    bool m_bItemFlag1F0;
    bool m_bNonSelectable;
    bool m_bItemFlag1F2;
    CEGUI::Window* m_pItemTextParent;
    bool m_bItemTextAttached;
    float m_fOpacity;
    bool m_bRequestedVisible;
    bool m_bLevelLighting;
    bool m_bItemFlag20A;
    std::wstring m_sItemName;
    bool m_bItemFlag218;
    // Opaque trailing state. Derived ItemGold/Breakable members start at 0x22c;
    // Equipment has its secondary iMissile base at 0x230 (original RTTI).
    unsigned char m_ItemData219[0x22c-0x219];
};
#endif
