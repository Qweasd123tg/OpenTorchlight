#include "SmallMassCompare.h"
#include <OgreHardwareBufferManager.h>
#include <OgreDefaultHardwareBufferManager.h>
#include <OgreVertexIndexData.h>
TL_ORIGINAL(void,dynamicInitOld,(void*,int,bool),"_ZN18CDynamicRenderable10initializeEN4Ogre15RenderOperation13OperationTypeEb")
TL_ORIGINAL(void,dynamicBuffersOld,(void*,size_t,size_t),"_ZN18CDynamicRenderable22prepareHardwareBuffersEmm")
extern "C" void dynamicInitNew(void*,int,bool) __asm__("_ZN18CDynamicRenderable10initializeEN4Ogre15RenderOperation13OperationTypeEb");
extern "C" void dynamicBuffersNew(void*,size_t,size_t) __asm__("_ZN18CDynamicRenderable22prepareHardwareBuffersEmm");
extern "C" char dynamicVertexCtor[] __asm__("_ZN4Ogre10VertexDataC1Ev");
extern "C" char dynamicIndexCtor[] __asm__("_ZN4Ogre9IndexDataC1Ev");
namespace {
using namespace smallmass;void* token;unsigned calls;
void record(unsigned tag,void* p){event(tag,p);++calls;}
void vertexCtor(void* p){record(1,p);std::memset(p,0,0x60);}
void indexCtor(void* p){record(2,p);std::memset(p,0,0x30);new(p)Ogre::HardwareIndexBufferSharedPtr();}
void declaration(void* p){record(3,p);number(field<unsigned>(p,0x150));number(field<bool>(p,0x154));number(field<void*>(p,0x148)!=0);number(field<void*>(p,0x158)!=0);number(field<size_t>(p,0x208));number(field<size_t>(p,0x210));}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;void* self=object(0x218);token=object(0x30);void** selfTable=static_cast<void**>(object(0x210));selfTable[0x208/8]=reinterpret_cast<void*>(&declaration);field<void*>(self,0)=selfTable;field<bool>(self,0x154)=c.index&1;
 detour::Set d;if(c.op==0){d.redirect(dynamicVertexCtor,dynamicVertexCtor,&vertexCtor);d.redirect(dynamicIndexCtor,dynamicIndexCtor,&indexCtor);}if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==0){field<void*>(self,0x158)=c.index&2?token:0;autotest::invoke(out,ours?dynamicInitNew:dynamicInitOld,self,int(c.index%7),bool(c.index&1));number(field<unsigned>(self,0x150));number(field<bool>(self,0x154));number(field<size_t>(self,0x208));number(field<size_t>(self,0x210));number(field<void*>(self,0x148)!=0);number(field<void*>(self,0x158)!=0);}
 else{
 Ogre::DefaultHardwareBufferManager buffers;
 Ogre::VertexData vertex;Ogre::IndexData indices;
 vertex.vertexDeclaration->addElement(0,0,Ogre::VET_FLOAT3,Ogre::VES_POSITION);
 if(c.index&4)vertex.vertexDeclaration->addElement(0,12,Ogre::VET_FLOAT1,Ogre::VES_TEXTURE_COORDINATES);
 field<void*>(self,0x148)=&vertex;field<void*>(self,0x158)=&indices;
 static size_t capacities[]={0,1,2,8,16,64};static size_t requested[]={0,1,2,3,4,7,8,9,15,16,17,65};
 size_t oldV=capacities[(c.index/2)%6],oldI=capacities[(c.index/7)%6];field<size_t>(self,0x208)=oldV;field<size_t>(self,0x210)=oldI;
 Ogre::HardwareVertexBufferSharedPtr oldVB;Ogre::HardwareIndexBufferSharedPtr oldIB;
 if(oldV){oldVB=buffers.createVertexBuffer(vertex.vertexDeclaration->getVertexSize(0),oldV,Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY,false);vertex.vertexBufferBinding->setBinding(0,oldVB);}
 if(oldI){oldIB=buffers.createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT,oldI,Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY,false);indices.indexBuffer=oldIB;}
 void* previousV=oldVB.getPointer();void* previousI=oldIB.getPointer();if(c.index&8){oldVB.setNull();oldIB.setNull();}
 size_t v=requested[c.index%12],i=requested[(c.index/3)%12];autotest::invoke(out,ours?dynamicBuffersNew:dynamicBuffersOld,self,v,i);
 number(field<size_t>(self,0x208));number(field<size_t>(self,0x210));number(vertex.vertexCount);number(indices.indexCount);
 Ogre::HardwareVertexBufferSharedPtr result=vertex.vertexBufferBinding->getBuffer(0);number(result->getNumVertices());number(result->getVertexSize());number(result->getUsage());number(result.getPointer()==previousV);
 if(!indices.indexBuffer.isNull()){number(indices.indexBuffer->getNumIndexes());number(indices.indexBuffer->getType());number(indices.indexBuffer.getPointer()==previousI);}else number(0);
 }

 number(calls);
}
}
TL_TEST(advance_runtime_dynamic_initialize){return smallmass::run(host,0,"advance_runtime_dynamic_initialize",(uintptr_t)dynamicInitOld,execute,48);}
TL_TEST(advance_runtime_dynamic_buffers){return smallmass::run(host,1,"advance_runtime_dynamic_buffers",(uintptr_t)dynamicBuffersOld,execute,144);}
