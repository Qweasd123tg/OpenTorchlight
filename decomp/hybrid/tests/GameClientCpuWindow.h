#ifndef GAMECLIENT_CPU_WINDOW_H
#define GAMECLIENT_CPU_WINDOW_H
#include <OgreRenderWindow.h>
#include "AutoTest.h"
#include "tests/GameCpuRenderer.h"
namespace gameclient_fixture {
class Window:public Ogre::RenderWindow {
public:
    Window(){mWidth=640;mHeight=480;mActive=true;mAutoUpdate=false;}
    void create(const Ogre::String&,unsigned,unsigned,bool,const Ogre::NameValuePairList*){std::abort();}
    void destroy(){}
    void resize(unsigned w,unsigned h){mWidth=w;mHeight=h;}
    void reposition(int,int){std::abort();}
    bool isClosed()const{return false;}
    void getCustomAttribute(const Ogre::String&,void*){std::abort();}
    void copyContentsToMemory(const Ogre::PixelBox&,Ogre::RenderTarget::FrameBuffer){std::abort();}
    bool requiresTextureFlipping()const{return false;}
};
class ProjectionRenderer:public Ogre::GameCpuRenderer {
public:
    autotest::Capture*capture;
    explicit ProjectionRenderer(autotest::Capture*observer=NULL):capture(observer){}
    void _convertProjectionMatrix(const Ogre::Matrix4&input,Ogre::Matrix4&output,bool gpu){if(capture){unsigned tag=181,value=gpu;capture->add(&tag,4);capture->add(&value,4);for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j)capture->add(&input[i][j],4);}output=input;}
    Ogre::Real getMinimumDepthInputValue(){return -1;}
    Ogre::Real getMaximumDepthInputValue(){return 1;}
};
}
#endif
