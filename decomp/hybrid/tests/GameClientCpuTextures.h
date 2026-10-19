#ifndef GAMECLIENT_CPU_TEXTURES_H
#define GAMECLIENT_CPU_TEXTURES_H
#include <OgreTextureManager.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreRenderTexture.h>
#include <OgreResourceManager.h>
#include <OgreRoot.h>
#include <OgreException.h>
#include <cstdlib>
#include <cstring>
#include <vector>
// Real SDK resource classes and their native base C1/D1. Only the rendering
// backend's virtual allocation/readback boundary is supplied in this fixture.
namespace gameclient_cpu {
struct Events {
    unsigned buffers,bufferDestructors,textures,textureDestructors,targets,targetDestructors;
    std::vector<unsigned> calls;
    Events():buffers(0),bufferDestructors(0),textures(0),textureDestructors(0),targets(0),targetDestructors(0){}
};
inline Events&events(){static Events value;return value;}
struct Target:Ogre::RenderTexture {
    Target(Ogre::HardwarePixelBuffer*buffer):Ogre::RenderTexture(buffer,0){++events().targets;}
    ~Target(){++events().targetDestructors;}
    bool requiresTextureFlipping()const{return false;}
    unsigned listenerCount()const{return mListeners.size();}
};
struct Buffer:Ogre::HardwarePixelBuffer {
    Target*target;
    std::vector<unsigned char> bytes;
    Buffer(size_t width,size_t height,Ogre::PixelFormat format):Ogre::HardwarePixelBuffer(width,height,1,format,Ogre::HardwareBuffer::HBU_STATIC,true,false),target(NULL),bytes(width*height*4,0){++events().buffers;target=new Target(this);}
    ~Buffer(){delete target;++events().bufferDestructors;}
    Ogre::PixelBox lockImpl(const Ogre::Image::Box box,Ogre::HardwareBuffer::LockOptions){events().calls.push_back(101);if(box.front||box.back!=1||box.left||box.top||box.right!=mWidth||box.bottom!=mHeight)std::abort();return Ogre::PixelBox(mWidth,mHeight,1,mFormat,&bytes[0]);}
    void unlockImpl(){events().calls.push_back(103);}
    void blitFromMemory(const Ogre::PixelBox&,const Ogre::Image::Box&){std::abort();}
    void blitToMemory(const Ogre::Image::Box&,const Ogre::PixelBox&){std::abort();}
    Ogre::RenderTexture*getRenderTarget(size_t slice){events().calls.push_back(107);events().calls.push_back(slice);if(slice)std::abort();return target;}
};
struct Texture:Ogre::Texture {
    Ogre::HardwarePixelBufferSharedPtr buffer;
    Texture(Ogre::ResourceManager*creator,const Ogre::String&name,Ogre::ResourceHandle handle,const Ogre::String&group,bool manual,Ogre::ManualResourceLoader*loader):Ogre::Texture(creator,name,handle,group,manual,loader){++events().textures;}
    ~Texture(){freeInternalResources();++events().textureDestructors;}
    void loadImpl(){createInternalResources();}
    void createInternalResourcesImpl(){events().calls.push_back(109);events().calls.push_back(mWidth);events().calls.push_back(mHeight);events().calls.push_back(mFormat);events().calls.push_back(mUsage);buffer=Ogre::HardwarePixelBufferSharedPtr(new Buffer(mWidth,mHeight,mFormat));}
    void freeInternalResourcesImpl(){events().calls.push_back(113);buffer.setNull();}
    Ogre::HardwarePixelBufferSharedPtr getBuffer(size_t face,size_t mipmap){events().calls.push_back(127);events().calls.push_back(face);events().calls.push_back(mipmap);if(face||mipmap||buffer.isNull())std::abort();return buffer;}
};
struct Textures:Ogre::TextureManager {
    Textures(){if(Ogre::Root::getSingleton().getRenderSystem())std::abort();}
    ~Textures(){removeAll();}
    Ogre::Resource*createImpl(const Ogre::String&name,Ogre::ResourceHandle handle,const Ogre::String&group,bool manual,Ogre::ManualResourceLoader*loader,const Ogre::NameValuePairList*){return new Texture(this,name,handle,group,manual,loader);}
    Ogre::PixelFormat getNativeFormat(Ogre::TextureType,Ogre::PixelFormat format,int){return format;}
    bool isHardwareFilteringSupported(Ogre::TextureType,Ogre::PixelFormat,int,bool){return true;}
};
}
#endif
