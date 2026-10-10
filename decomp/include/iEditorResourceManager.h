#ifndef IEDITORRESOURCEMANAGER_H
#define IEDITORRESOURCEMANAGER_H
class CSettings;
class CSoundManager;
class CGameClient;
namespace Ogre { class SceneManager; class RenderWindow; class Camera; }

// Pure interface at CGame+0x20. Slot names come from CGame's adjustment thunks.
class iEditorResourceManager
{
public:
    virtual ~iEditorResourceManager();
    virtual void editorUpdateSceneOnce(int elapsed) = 0;
    virtual void* getWindowHandle() = 0;
    virtual CSettings* getSettings() = 0;
    virtual Ogre::SceneManager* getSceneManager() = 0;
    virtual CSoundManager* getSoundManager() = 0;
    virtual Ogre::RenderWindow* getRenderWindow() = 0;
    virtual Ogre::Camera* getGameCamera() = 0;
    virtual void updateAspectRatio(float width, float height) = 0;
    virtual CGameClient* getGameClient() = 0;
};
#endif
