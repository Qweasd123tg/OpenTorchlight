#ifndef PLAYER_H
#define PLAYER_H

#include <OgreCamera.h>
#include "Character.h"

// Partial: Player.cpp is not recovered. Virtual overrides follow the original
// vtable; the unexamined player fields retain their original extent.
class CPlayer : public CCharacter
{
public:
    virtual ~CPlayer();
    virtual void unitInit(CDataGroup*, bool);
    virtual void levelResetting();
    virtual void update(Ogre::Camera*, const Ogre::Vector3&, float);
    virtual bool getIsPlayer();
    virtual void levelLoaded(CLevel*);
    virtual bool getIsInGodMode();
    virtual void fillSaveState(CCharacterSaveState&);
    virtual void applySaveState(CCharacterSaveState&);
    virtual void updateAnimation(float);
    virtual void loadModel(std::wstring, std::wstring);
    virtual void levelUp();
    virtual void die(CCharacter*, const Ogre::Vector3*, float, bool);
    virtual void startFishing();
    virtual void catchFish();
    virtual void setAIState(EAIState);
    virtual void fishingAI(float, CLevel&);
    virtual void fishingAICatch(float, CLevel&);
    virtual void openPortal(CLevel&);
    virtual void openMapPortal(std::wstring, CLevel&);
    virtual void applyAchievementsForKilledCharacter(CCharacter*);
    virtual void calculateMaxMana();
    virtual void calculateMaxHP();

private:
    unsigned char m_PlayerData[0xa70 - 0x720];
};

#endif
