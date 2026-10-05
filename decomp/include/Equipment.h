#ifndef EQUIPMENT_H
#define EQUIPMENT_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>
#include <string>
#include <vector>
#include "BaseUnit.h"
#include "Character.h"
#include "Constants.h"
#include "DataGroup.h"
#include "Effect.h"
#include "EffectDefines.h"
#include "GameUI.h"
#include "GameEnums.h"
#include "GenericModel.h"
#include "Item.h"
#include "ItemSaveState.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "iMissile.h"
class CAttackDescription;
class CInventory;
class CMissile;
class CParticle;
class CPath;

class CEquipment : public CItem, public iMissile
{
public:
    virtual ~CEquipment();
    virtual void setActiveInLevel(bool);
    virtual void* getUnitModel();
    virtual void* getUnitCollisionModel();
    virtual void unitInit(CDataGroup*, bool);
    virtual void update(Ogre::Camera*, const Ogre::Vector3&, float);
    virtual void setHighlighted(bool);
    virtual bool isEffectValidForUnit(CCharacter*, CBaseUnit*, CEffect*);
    virtual void applyEffectOnUnit(CCharacter*, CBaseUnit*, CEffect*);
    virtual void fillSaveState(CItemSaveState&, int, bool);
    virtual void applySaveState(CItemSaveState&);
    virtual const std::wstring& getItemName();
    virtual void setItemTextHighlighted(bool);
    virtual bool isMagical();
    virtual void setRimlight(std::wstring);
    virtual void missileBeingFired(CMissile*);
    virtual void missileDieing(CMissile*);
    virtual void missileApplyingEffects(CMissile*, CCharacter*, const Ogre::Vector3*, float, float);
    virtual bool getCharacterCanBeHarmedByMissile(CMissile*, CCharacter*);
    virtual bool missileValidateTargetBeforeLaunch(CMissile*, CPositionableObject*, Ogre::Vector3&);
    virtual void* getUnitModelSecondary();
    virtual bool canEquip(CCharacter*, bool);
    virtual long long canPickup(CCharacter*);
    virtual long long canDrop(CCharacter*);
    virtual void addedToInventory(CInventory*, CCharacter*);
    virtual void removedFromInventory(CInventory*, CCharacter*);
    virtual void equipped(CInventory*, CCharacter*, EEQUIP_LOCATIONS);
    virtual void unequipped(CInventory*, CCharacter*, EEQUIP_LOCATIONS);
    virtual void useEquipment(CCharacter*, CCharacter*);
    virtual void incrementStackBy(int);
    virtual CCharacter* getEquippedTo();
    virtual void equip();
    virtual void unequip();
    virtual void useEquipment();
    virtual void drop();
    virtual void activateDropParticles();
    long long hasEffects();
    void unloadModel();
    int minimumDamage();
    int maximumDamage();
    int getDamageBonus(EDAMAGE_TYPES);
    void removeDamageBonus(EDAMAGE_TYPES, int);
    void resetVisualLayout();
    void updateVisualLayout(float);
    int getDefenseRequirement(CCharacter*);
    int getMagicRequirement(CCharacter*);
    int getDexterityRequirement(CCharacter*);
    int getStrengthRequirement(CCharacter*);
    int getLevelRequirement(CCharacter*);
    long long canEnchant();
    // unresolved: CEquipment::removeAffixesThatDontSupportUnitType(UNITTYPES::EUNITTYPES)
    void addContainerItem(CEquipment*);
    bool canUseOnTarget(CCharacter*, CBaseUnit*);
    void useOnTarget(CCharacter*, CBaseUnit*);
    void playDropSound(Ogre::SceneNode*);
    void playTakeSound(Ogre::SceneNode*);
    void setRenderBehind(bool);
    void setElementalParticlesEnabled(bool);
    void detachFromLocation();
    long DPS();
    void executeProcs(CCharacter*, EEFFECT_TYPE, CBaseUnit*);
    void destroyIcon();
    std::wstring getAttackSpeedString(EWeaponSpeed);
    int sellPrice();
    int buyPrice();
    CEquipment(CResourceManager*);
    void addInherentDamage(EDAMAGE_TYPES, int);
    void addDamageBonus(EDAMAGE_TYPES, int);
    void updateDrop(float);
    CEquipment* getFlavorDescription();
    std::wstring getSet();
    void convertEquipment(std::wstring);
    void createNewEquipment(std::wstring);
    void setGraphDamage(unsigned int);
    void setGraphAC(unsigned int);
    int enchantPrice();
    std::wstring skillDescription();
    bool fireMissiles(CCharacter*, CCharacter*);
    unsigned long getMaxSockets();
    void addSockets();
    bool isWardrobed(std::wstring);
    void setRequirements();
    void calculateCombatStats(bool);
    void improveHeirloom();
    void createIcon(CGameUI&, bool);
    void recalculatePrice();
    void enchant(bool);
    std::wstring getFullItemName(bool);
    void createParticles();
    void createElementalDamages();
    void clearDamageBonuses();
    void addEnchant(int, int, int);
    void attachToGivenLocation(CCharacter*, EEQUIP_LOCATIONS);
    void loadModel(std::wstring, std::wstring);
    void reskinByClass(std::wstring);
    std::wstring effectsDescription(EEFFECT_ACTIVATION, bool, bool);
    std::wstring getEquipmentEffects();
    std::wstring getEquipmentType(bool);
    std::wstring getEquipmentDescription(bool, bool);
    std::wstring getEquipmentStats();

    // fields
    int m_iUnknown238;
    int m_iUnknown23C;
    CInventory* m_pInventory;
    int m_iUnknown248;
    unsigned char m_gap24C[0x4] __attribute__((aligned(4)));
    CPath* m_pPath;
    float m_fUnknown258;
    bool m_bUnknown25C;
    bool m_bGamblerIcon;
    bool m_bUnknown25E;
    bool m_bUnknown25F;
    int m_iUnknown260;
    int m_iUnknown264;
    int m_iUnknown268;
    int m_iUnknown26C;
    int m_iUnknown270;
    int m_iUnknown274;
    int m_iUnknown278;
    int m_iUnknown27C;
    int m_iUnknown280;
    int m_iUnknown284;
    int m_iUnknown288;
    int m_iUnknown28C;
    CCharacter* m_pEquippedTo;
    int m_iUnknown298;
    unsigned char m_gap29C[0x4] __attribute__((aligned(4)));
    CAttackDescription* m_pAttackDescription;
    // Second attack slot: also holds LSLASH/LPISTOL/LWAND or the sole BOW attack.
    CAttackDescription* m_pAttackDescriptionOverride;
    CGenericModel* m_pUnitModel;
    CGenericModel* m_pUnitModelSecondary;
    long long m_iUnitCollisionModel;
    CEGUI::Window* m_pIconWindow;
    std::wstring m_sUnidentifiedName;
    std::wstring m_sDisplayName;
    std::wstring m_sPrefix;
    std::wstring m_sSuffix;
    Ogre::Matrix4 m_mDropOrientation;
    int m_iMinimumDamage;
    int m_iMaximumDamage;
    int m_iUnknown338;
    int m_iUnknown33C;
    int m_iUnknown340;
    int m_iUnknown344;
    bool m_bUnknown348;
    unsigned char m_gap349[0x7];
    std::vector<EDAMAGE_TYPES> m_ElementalDamageTypes;
    std::vector<int> m_ElementalDamageBonuses;
    std::vector<int> m_InherentElementalDamage;
    // Trivial vector buffers verified in ctor/dtor. Exact element types remain
    // unknown; byte elements preserve those observed storage/lifetime operations.
    std::vector<unsigned char> m_UnknownPOD398;
    std::vector<unsigned char> m_UnknownPOD3B0;
    CParticle* m_pParticle;
    CParticle* m_pParticle_3D0;
    std::wstring m_sUnknown3D8;
    unsigned int m_iSocketCount;
    unsigned char m_gap3E4[0x4] __attribute__((aligned(4)));
    TArrayList<CEquipment*> m_SocketedEquipment;
    std::wstring m_sUnknown400;
    float m_fUnknown408;
    unsigned char m_gap40C[0x4] __attribute__((aligned(4)));
    TArrayList<TSafePointer<CMissile>*> m_ActiveMissileRefs;
    CPositionableObject* m_pPositionableObject;
    bool m_bUnknown430;
};

#endif
