#ifndef NATIVE_REINITIALIZE_PROGRAMS_H
#define NATIVE_REINITIALIZE_PROGRAMS_H
#include <OgreGpuProgram.h>
#include <OgreGpuProgramManager.h>
namespace nativeprogram {
class Program:public Ogre::GpuProgram {
protected:
 virtual void loadFromSource(){}
 virtual void loadImpl(){}
 virtual void unloadImpl(){}
public:
 Program(Ogre::ResourceManager*manager,const std::string&name,Ogre::ResourceHandle handle,const std::string&group,bool manual,Ogre::ManualResourceLoader*loader):Ogre::GpuProgram(manager,name,handle,group,manual,loader){
  Ogre::GpuNamedConstants named;named.floatBufferSize=16;named.intBufferSize=0;Ogre::GpuConstantDefinition def;def.constType=Ogre::GCT_MATRIX_4X4;def.physicalIndex=0;def.logicalIndex=0;def.elementSize=16;def.arraySize=1;named.map["texViewProj"]=def;setManualNamedConstants(named);setSkeletalAnimationIncluded(true);setMorphAnimationIncluded(false);setPoseAnimationIncluded(0);
 }
 virtual bool isSupported()const{return true;}
};
class Manager:public Ogre::GpuProgramManager {
protected:
 virtual Ogre::Resource*createImpl(const std::string&name,Ogre::ResourceHandle handle,const std::string&group,bool manual,Ogre::ManualResourceLoader*loader,Ogre::GpuProgramType,const std::string&){return new Program(this,name,handle,group,manual,loader);}
 virtual Ogre::Resource*createImpl(const std::string&name,Ogre::ResourceHandle handle,const std::string&group,bool manual,Ogre::ManualResourceLoader*loader,const Ogre::NameValuePairList*){return new Program(this,name,handle,group,manual,loader);}
};
}
#endif
