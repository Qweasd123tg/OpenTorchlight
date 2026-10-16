#include <string>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#include "PathController.h"
#include "PathNode.h"
#include "GameClient.h"
TL_ORIGINAL(Ogre::Vector3, frontOriginal,(void*,CBaseUnit*),"_ZN15CPathController28caculatePointInFrontOfPlayerEP9CBaseUnit")
extern "C" Ogre::Vector3 frontCandidate(void*,CBaseUnit*) __asm__("_ZN15CPathController28caculatePointInFrontOfPlayerEP9CBaseUnit");
TL_ORIGINAL(Ogre::Vector3, nextOriginal,(void*,float,CBaseUnit*,bool),"_ZN15CPathController21getNextPointAtPercentEfP9CBaseUnitb")
extern "C" Ogre::Vector3 nextCandidate(void*,float,CBaseUnit*,bool) __asm__("_ZN15CPathController21getNextPointAtPercentEfP9CBaseUnitb");
TL_ORIGINAL(float*, arrayOriginal,(void*,unsigned&),"_ZN15CPathController17getArrayOfVectorsERj")
extern "C" float* arrayCandidate(void*,unsigned&) __asm__("_ZN15CPathController17getArrayOfVectorsERj");
TL_ORIGINAL(void, setArrayOriginal,(void*,const float*,unsigned),"_ZN15CPathController17setArrayOfVectorsEPKfj")
extern "C" void setArrayCandidate(void*,const float*,unsigned) __asm__("_ZN15CPathController17setArrayOfVectorsEPKfj");
TL_FUNCTION(positionTarget,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(editorTarget,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(countTarget,"_ZN15CPathController21setNumberOfPathPointsEj")
TL_FUNCTION(frontTarget,"_ZN15CPathController28caculatePointInFrontOfPlayerEP9CBaseUnit")
TL_ORIGINAL(void, childOriginal,(void*),"_ZN15CPathController14childNodeMovedEv")
extern "C" void childCandidate(void*) __asm__("_ZN15CPathController14childNodeMovedEv");
TL_ORIGINAL(void, positionOriginal,(void*,const Ogre::Vector3&),"_ZN15CPathController15positionUpdatedERKN4Ogre7Vector3E")
extern "C" void positionCandidate(void*,const Ogre::Vector3&) __asm__("_ZN15CPathController15positionUpdatedERKN4Ogre7Vector3E");
TL_ORIGINAL(void, splineOriginal,(void*),"_ZN15CPathController14caculateSplineEv")
extern "C" void splineCandidate(void*) __asm__("_ZN15CPathController14caculateSplineEv");
TL_FUNCTION(setPositionTarget,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
namespace {
struct Case{unsigned op,index;};Case* input;autotest::Capture* output;void* self;void* resources;void* parent;void* parentPositionable;void* player;void* unit;void* nodes[5];Ogre::Vector3 positions[5];unsigned calls;bool editor;
template<class T>T& field(void* p,unsigned offset){return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);}void invalid(){output->issue=autotest::Capture::InvalidReport;}void number(unsigned n){output->add(&n,sizeof(n));}void vector(const Ogre::Vector3& v){output->add(&v,sizeof(v));}
Ogre::Vector3 getPosition(void* p,bool absolute){number(1);number(p==self?0:p==parent?1:p==player?2:3);number(absolute);++calls;if(p==self)return Ogre::Vector3(float(input->index%5)-2,41,float(input->index%7)-3);if(p==parent)return Ogre::Vector3(3,-4,9);if(p==parentPositionable)return Ogre::Vector3(-19,6,-31);if(p==player)return Ogre::Vector3(float(input->index%3)-1,-7,float(input->index%4)-2);for(unsigned i=0;i<5;++i)if(p==nodes[i]){Ogre::Vector3 v=positions[i];if(input->op==2&&input->index%3==0)v.y+=calls*0.25f;return v;}invalid();return Ogre::Vector3::ZERO;}
bool isEditor(void* p){number(2);if(p!=resources)invalid();return editor;}
void setCount(void* p,unsigned n){number(3);number(n);if(p!=self)invalid();}
void nodePosition(void* p,float x,float y,float z){number(4);vector(Ogre::Vector3(x,y,z));if(field<void*>(p,0x100))invalid();for(unsigned i=0;i<5;++i)if(p==nodes[i]){positions[i]=Ogre::Vector3(x,y,z);return;}invalid();}
void setPosition(void* p,const Ogre::Vector3& v){number(7);vector(v);++calls;if(p==self)return;for(unsigned i=0;i<5;++i)if(p==nodes[i]){if(field<void*>(p,0x100))invalid();positions[i]=v;return;}invalid();}
void visible(void* p,bool value){number(5);number(value);if(p!=self)invalid();}
Ogre::Vector3 front(void* p,CBaseUnit* u){number(6);if(p!=self||u!=unit)invalid();return Ogre::Vector3(-17,input->index*0.5f,25);}
void body(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;self=autotest::allocate(sizeof(CPathController));resources=autotest::allocate(256);parent=autotest::allocate(512);parentPositionable=autotest::allocate(512);player=autotest::allocate(2048);unit=autotest::allocate(2048);field<void*>(self,0x68)=resources;field<void*>(self,0x48)=parent;field<void*>(self,0x50)=c.index%2?parentPositionable:NULL;field<bool>(self,0x130)=c.index%2;
 TArrayList<CGameClient*>* clients=new(static_cast<char*>(resources)+0x28)TArrayList<CGameClient*>;void* client=autotest::allocate(512);field<void*>(client,0x58)=c.index%9==0?0:player;if(c.index%11)clients->add(static_cast<CGameClient*>(client));
 field<float>(player,0x194)=c.index%8*0.125f;field<float>(unit,0x194)=c.index%5*0.25f;
 TArrayList<CPathNode*>* nodeList=new(static_cast<char*>(self)+0x138)TArrayList<CPathNode*>;TArrayList<float>* coordinates=new(static_cast<char*>(self)+0x150)TArrayList<float>;TArrayList<float>* distances=new(static_cast<char*>(self)+0x168)TArrayList<float>;
 void** selfTable=static_cast<void**>(autotest::allocate(0x200));selfTable[0x50/8]=reinterpret_cast<void*>(&visible);field<void*>(self,0)=selfTable;
 void** nodeTable=static_cast<void**>(autotest::allocate(0x200));nodeTable[0x58/8]=reinterpret_cast<void*>(&nodePosition);
 unsigned n=c.index%5;for(unsigned i=0;i<5;++i){nodes[i]=autotest::allocate(0x128);field<void*>(nodes[i],0)=nodeTable;field<void*>(nodes[i],0x100)=self;positions[i]=Ogre::Vector3(i*1.25f,-float(i),float(i*i));if(i<n)nodeList->add(static_cast<CPathNode*>(nodes[i]));}
 editor=c.index%3!=0;for(unsigned i=0;i<9;++i)coordinates->add(float(i)*0.5f-2);
 detour::Set patches;TL_REDIRECT(patches,positionTarget,&getPosition);TL_REDIRECT(patches,editorTarget,&isEditor);TL_REDIRECT(patches,countTarget,&setCount);TL_REDIRECT(patches,setPositionTarget,&setPosition);if(c.op==1)TL_REDIRECT(patches,frontTarget,&front);if(patches.failed()){std::fprintf(stderr,"    Path fixture detour failure seed %u side %u code %u site %p\n",c.index,ours,unsigned(patches.failure()),patches.failureSite());invalid();return;}
 if(c.op==0){Ogre::Vector3(*fn)(void*,CBaseUnit*)=ours?frontCandidate:frontOriginal;if(!autotest::beginInvocation(out,fn))return;Ogre::Vector3 v=fn(self,static_cast<CBaseUnit*>(unit));out.callCompleted=1;vector(v);number(calls);}
 else if(c.op==1){field<bool>(self,0x135)=c.index%13==0;distances->add(0);distances->add(0.5f);distances->add(1);field<float>(self,0x180)=c.index%7==0?0.0f:1.0f;const float percents[]={-1,0,0.25f,0.5f,0.75f,1,2};float percent=percents[c.index%7];if(c.index%17==0){unsigned bits=0x7fc12345;std::memcpy(&percent,&bits,4);}Ogre::Vector3(*fn)(void*,float,CBaseUnit*,bool)=ours?nextCandidate:nextOriginal;if(!autotest::beginInvocation(out,fn))return;Ogre::Vector3 v=fn(self,percent,static_cast<CBaseUnit*>(unit),c.index%2);out.callCompleted=1;vector(v);number(calls);}
 else if(c.op==2){unsigned count=123;float*(*fn)(void*,unsigned&)=ours?arrayCandidate:arrayOriginal;if(!autotest::beginInvocation(out,fn))return;float* values=fn(self,count);out.callCompleted=1;number(count);number(values==0);if(count)out.add(values,count*4);number(calls);}
 else if(c.op==3){unsigned count=n*3+c.index%3;float values[18];for(unsigned i=0;i<18;++i)values[i]=float(i)-4.25f;if(c.index%7==0){count=0;}if(c.index%5==0)field<void*>(self,0x48)=0;void(*fn)(void*,const float*,unsigned)=ours?setArrayCandidate:setArrayOriginal;if(!autotest::beginInvocation(out,fn))return;fn(self,count?values:0,count);out.callCompleted=1;number(coordinates->size());for(unsigned i=0;i<coordinates->size();++i)out.add(&(*coordinates)[i],4);for(unsigned i=0;i<n;++i){vector(positions[i]);number(field<void*>(nodes[i],0x100)==self);}number(calls);}
 else if(c.op==4){if(n&&c.index%7==0)(*nodeList)[0]=0;void(*fn)(void*)=ours?childCandidate:childOriginal;if(!autotest::beginInvocation(out,fn))return;fn(self);out.callCompleted=1;number(calls);}
 else if(c.op==5){Ogre::Vector3 value=positions[0];if(c.index%3)value.x+=0.5f;if(c.index%7==0){unsigned bits=0x7fc12345;std::memcpy(&value.z,&bits,4);}void(*fn)(void*,const Ogre::Vector3&)=ours?positionCandidate:positionOriginal;if(!autotest::beginInvocation(out,fn))return;fn(self,value);out.callCompleted=1;number(calls);if(n){vector(positions[0]);number(field<void*>(nodes[0],0x100)==self);}}
 else{coordinates->clear();for(unsigned i=0;i<n;++i){coordinates->add(float(i)*0.125f);coordinates->add(float(i*i)*0.5f);coordinates->add(float(i%2)*3);}distances->add(77.0f);distances->add(88.0f);field<float>(self,0x180)=99.0f;field<bool>(self,0x135)=c.index%7==0;if(c.index%11==0)field<void*>(self,0x48)=0;void(*fn)(void*)=ours?splineCandidate:splineOriginal;if(!autotest::beginInvocation(out,fn))return;fn(self);out.callCompleted=1;out.add(static_cast<char*>(self)+0x180,4);number(distances->size());for(unsigned i=0;i<distances->size();++i)out.add(&(*distances)[i],4);}
 patches.restore();coordinates->~TArrayList();distances->~TArrayList();nodeList->~TArrayList();clients->~TArrayList();}
void original(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),false,out);}void recovered(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned op,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned i=0;i<96;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    world path op %u seed %u child %d/%d issue %u/%u started %u/%u completed %u/%u bytes %lu/%lu\n",op,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length); for(unsigned j=0;j<a.capture.length||j<b.capture.length;++j) if(j>=a.capture.length||j>=b.capture.length||a.capture.data[j]!=b.capture.data[j]) {host->log("    first differing byte %u old %02x new %02x\n",j,j<a.capture.length?(unsigned char)a.capture.data[j]:0,j<b.capture.length?(unsigned char)b.capture.data[j]:0);break;}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=96||coverage.different||coverage.missing;}
}
TL_TEST(world_path_front_point){return run(host,0,"world_path_front_point",(uintptr_t)&frontOriginal);}
TL_TEST(world_path_next_point){return run(host,1,"world_path_next_point",(uintptr_t)&nextOriginal);}
TL_TEST(world_path_get_array){return run(host,2,"world_path_get_array",(uintptr_t)&arrayOriginal);}
TL_TEST(world_path_set_array){return run(host,3,"world_path_set_array",(uintptr_t)&setArrayOriginal);}

TL_TEST(world_path_child_moved){return run(host,4,"world_path_child_moved",(uintptr_t)&childOriginal);}
TL_TEST(world_path_position_updated){return run(host,5,"world_path_position_updated",(uintptr_t)&positionOriginal);}
TL_TEST(world_path_spline){return run(host,6,"world_path_spline",(uintptr_t)&splineOriginal);}
