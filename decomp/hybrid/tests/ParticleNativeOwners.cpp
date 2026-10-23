#include <Ogre.h>
#include "tests/NativeEditorControls.h"
#include "tests/NativeMenuClient.h"
#include <ParticleUniverseSystemManager.h>
#include "ParticleNativeOwners.h"
namespace {
class Window:public Ogre::RenderWindow {
public:
    Window(unsigned profile){mWidth=320+profile*3;mHeight=240+profile*2;}
    void create(const Ogre::String&,unsigned,unsigned,bool,const Ogre::NameValuePairList*){std::abort();}
    void destroy(){}
    void resize(unsigned w,unsigned h){mWidth=w;mHeight=h;}
    void reposition(int,int){std::abort();}
    bool isClosed()const{return false;}
    void copyContentsToMemory(const Ogre::PixelBox&,Ogre::RenderTarget::FrameBuffer){std::abort();}
    bool requiresTextureFlipping()const{return false;}
};
struct SceneAccess:Ogre::SceneManager {
    static Ogre::Viewport* Ogre::SceneManager::* viewport(){return &SceneAccess::mCurrentViewport;}
};
struct Owners {
    nativegame::Services services;
    menugui::Audio audio;
    nativeeditor::Controls controls;
    Owners(unsigned profile):audio(services.master),controls(services){
        controls.editor->m_iFlags=profile&1?0:2;
        services.master->m_pParticleSystemManager->m_paused=bool(profile&4);
        if(!Ogre::ControllerManager::getSingletonPtr())new Ogre::ControllerManager;
        const char* names[]={"BaseWhite","BaseWhiteNoLighting","WireframeBlue"};
        for(unsigned i=0;i<3;++i){Ogre::MaterialPtr m=Ogre::MaterialManager::getSingleton().getByName(names[i]);if(m.isNull())m=Ogre::MaterialManager::getSingleton().create(names[i],"General");m->removeAllTechniques();}
        Ogre::Camera* camera;
        {menugui::ProjectionDuringConstruction boundary;camera=services.scene->createCamera("PlayerCam");}
        camera->setPosition(float(profile)-3.5f,2.25f,-9.5f);
        if(profile&2){Window*w=new Window(profile);services.scene->*SceneAccess::viewport()=w->addViewport(camera);}
    }
};
}
ParticleNativeOwners particleNativeOwners(unsigned profile){
    Owners* p=new Owners(profile);
    ParticleNativeOwners result={p->controls.resources,p->services.scene,p->services.scene->getCamera("PlayerCam"),p};
    return result;
}
void particleNativeSetEditorMode(const ParticleNativeOwners& owners, bool editor){
    static_cast<Owners*>(owners.owner)->controls.editor->m_iFlags=editor?2:0;
}
