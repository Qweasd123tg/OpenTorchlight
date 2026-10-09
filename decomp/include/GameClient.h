#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <string>
#include <OgreRenderTargetListener.h>
#include <OgreRenderQueue.h>
#include <string>

#include "RunicCore.h"
#include "QuestEventTypes.h"

class CBaseUnit;
class CCharacter;
class CPlayer;
class CGameUI;

// Partial: player and UI fields. Preserve all three base
// subobjects and the original 0x3910-byte allocation from GameClient.cpp.
class CGameClient : public CRunicCore, public Ogre::RenderTargetListener,
                    public Ogre::RenderQueue::RenderableListener
{
public:
    void clearMouseClickUnits();
    void warpLevels(std::wstring dungeon, int delta, int depth, bool waypoint, std::wstring warpName, bool flag);
    virtual ~CGameClient();
    virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent&);
    virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent&);
    virtual bool renderableQueued(Ogre::Renderable*, unsigned char, unsigned short,
                                  Ogre::Technique**, Ogre::RenderQueue*);

    void setStateControlFlag(bool value) { m_bStateControl10BC = value; }
    bool getPlayerIsCheat();
    void questEventFire(EQUEST_EVENTS event, CCharacter* character, CBaseUnit* target);
    CPlayer* getPlayer() { return m_pPlayer; }
    CGameUI* getGameUI() { return m_pGameUI; }

private:
    unsigned char m_ClientData20[0x58 - 0x20];
    CPlayer* m_pPlayer;
    unsigned char m_ClientData60[0x78 - 0x60];
    CGameUI* m_pGameUI;
    unsigned char m_ClientData80[0x10bc - 0x80];
    bool m_bStateControl10BC;
    unsigned char m_ClientData10BD[0x3910 - 0x10bd];
};

#endif
