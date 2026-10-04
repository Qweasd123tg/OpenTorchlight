#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <OgreRenderTargetListener.h>
#include <OgreRenderQueue.h>
#include <string>

#include "RunicCore.h"

class CPlayer;

// Partial: only the player field is named here. Preserve all three base
// subobjects and the original 0x3910-byte allocation from GameClient.cpp.
class CGameClient : public CRunicCore, public Ogre::RenderTargetListener,
                    public Ogre::RenderQueue::RenderableListener
{
public:
    virtual ~CGameClient();
    virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent&);
    virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent&);
    virtual bool renderableQueued(Ogre::Renderable*, unsigned char, unsigned short,
                                  Ogre::Technique**, Ogre::RenderQueue*);

    CPlayer* getPlayer() { return m_pPlayer; }

    void warpLevels(std::wstring dungeon, int levelDelta, int levelDepth, bool waypoint,
                    std::wstring warpName, bool flag);

private:
    unsigned char m_ClientData20[0x58 - 0x20];
    CPlayer* m_pPlayer;
    unsigned char m_ClientData60[0x3910 - 0x60];
};

#endif
