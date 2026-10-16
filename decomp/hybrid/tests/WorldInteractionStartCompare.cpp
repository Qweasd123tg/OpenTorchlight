#include <string>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#include "Interact.h"
#include "CameraControl.h"
TL_ORIGINAL(void, configureOriginal,(void*,EINTERACTABLE_UNITS),"_ZN9CInteract26configureSpecificUnitIndexE19EINTERACTABLE_UNITS")
extern "C" void configureCandidate(void*,EINTERACTABLE_UNITS) __asm__("_ZN9CInteract26configureSpecificUnitIndexE19EINTERACTABLE_UNITS");
TL_ORIGINAL(void, startOriginal,(void*,EINTERACTABLE_UNITS),"_ZN9CInteract16interactWithUnitE19EINTERACTABLE_UNITS")
extern "C" void startCandidate(void*,EINTERACTABLE_UNITS) __asm__("_ZN9CInteract16interactWithUnitE19EINTERACTABLE_UNITS");
TL_ORIGINAL(void, interactCtorOriginal,(void*,CResourceManager*),"_ZN9CInteractC1EP16CResourceManager")
TL_ORIGINAL(void, interactDtorOriginal,(void*),"_ZN9CInteractD1Ev")
TL_FUNCTION(baseUnitTarget,"_ZN6CLevel22getBaseUnitByDataGroupEP10CDataGroup")
TL_FUNCTION(cameraTarget,"_ZN14CCameraControl12getSingletonEv")
TL_FUNCTION(positionTarget,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(clearTarget,"_ZN6CGraph5clearEj")
TL_FUNCTION(addTarget,"_ZN6CGraph8addValueEffj")
TL_FUNCTION(processTarget,"_ZN6CGraph13processPointsEv")
TL_FUNCTION(uiTarget,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(closeTarget,"_ZN7CGameUI8closeAllEv")
TL_FUNCTION(stopPathTarget,"_ZN10CCharacter11stopPathingEv")
TL_FUNCTION(broadcastTarget,"_ZN17CEditorBaseObject14BroadcastEventEj")
namespace {
struct Case{unsigned op,index;};Case* input;autotest::Capture* output;void* self;void* level;void* player;CRunicCore* oldUnit;CRunicCore* newUnit;CCameraControl* camera;char dataGroup,ui;unsigned calls;
template<class T>T& field(void* p,unsigned offset){return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);}void invalid(){std::fprintf(stderr,"    interaction invalid op %u seed %u collaborators %u started %u completed %u payload %u\n",input->op,input->index,calls,output->callStarted,output->callCompleted,unsigned(output->length));output->issue=autotest::Capture::InvalidReport;}void number(unsigned n){output->add(&n,sizeof(n));}void vector(const Ogre::Vector3& v){output->add(&v,sizeof(v));}
void* baseUnit(void* p,void* data){number(1);number(data==&dataGroup);++calls;if(p!=level||data!=&dataGroup)invalid();return input->index%5==0?0:input->index%3==0?oldUnit:newUnit;}
void* cameraSingleton(){number(2);++calls;return camera;}
Ogre::Vector3 position(void* p,bool absolute){number(3);number(absolute);++calls;if((p!=oldUnit&&p!=newUnit)||absolute)invalid();return Ogre::Vector3(input->index*0.25f,-3,9);}
void graphClear(void* p,unsigned line){number(4);number(line);++calls;if(p!=static_cast<char*>(self)+0xc8||line)invalid();}
void graphAdd(void* p,float x,float y,unsigned line){number(5);output->add(&x,4);output->add(&y,4);number(line);++calls;if(p!=static_cast<char*>(self)+0xc8||line)invalid();}
void graphProcess(void* p){number(6);++calls;if(p!=static_cast<char*>(self)+0xc8)invalid();}
void* uiSingleton(){number(7);++calls;return &ui;}
void close(void* p){number(8);++calls;if(p!=&ui)invalid();}
void stopPath(void* p){number(9);++calls;if(p!=player)invalid();}
void setAI(void* p,int state){number(10);number(state);++calls;if(p!=player||state!=44)invalid();field<int>(p,0x330)=state;}
void broadcast(void* p,unsigned event){number(11);number(event);++calls;if(p!=self||(event!=87&&event!=91))invalid();}
void bind(void* weak,CRunicCore* referent){field<void*>(weak,0)=referent;field<unsigned>(weak,8)=referent->addSafePointer(reinterpret_cast<TSafePointer<void*>*>(weak));}
void body(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;int before=g_iTotalCountOfObjects;int constructed=before;TSafePointer<CRunicCore> oldLifetime,newLifetime;{
 CRunicCore oldObject,newObject;oldUnit=&oldObject;newUnit=&newObject;oldLifetime.setObject(oldUnit);newLifetime.setObject(newUnit);self=autotest::allocate(sizeof(CInteract));void* resources=autotest::allocate(256);level=autotest::allocate(1024);field<void*>(resources,0x18)=level;void* client=autotest::allocate(0x3910);player=autotest::allocate(0x1000);field<void*>(client,0x58)=player;TArrayList<void*>* clients=new(static_cast<char*>(resources)+0x28)TArrayList<void*>;clients->add(client);void** table=static_cast<void**>(autotest::allocate(0x400));table[0x348/8]=reinterpret_cast<void*>(&setAI);field<void*>(player,0)=table;
 interactCtorOriginal(self,static_cast<CResourceManager*>(resources));CInteract* p=static_cast<CInteract*>(self);constructed=g_iTotalCountOfObjects;if(constructed!=before+4)invalid();TSafePointer<CInteract> interactionLifetime;interactionLifetime.setObject(p);p->m_pUnitDataGroup=reinterpret_cast<CDataGroup*>(&dataGroup);if(c.index%4)bind(&p->m_unit,oldUnit);TSafePointer<CRunicCore> witnessOld,witnessNew;witnessOld.setObject(oldUnit);witnessNew.setObject(newUnit);camera=static_cast<CCameraControl*>(autotest::allocate(sizeof(CCameraControl)));camera->m_fUnknown4C=2;camera->m_fUnknown50=-4;camera->m_fUnknown54=6;p->m_fUnknownB0=c.index*0.125f;p->m_fUnknownB8=0.2f;p->m_fUnknownBC=0.75f;
 detour::Set patches;TL_REDIRECT(patches,baseUnitTarget,&baseUnit);TL_REDIRECT(patches,cameraTarget,&cameraSingleton);TL_REDIRECT(patches,positionTarget,&position);TL_REDIRECT(patches,clearTarget,&graphClear);TL_REDIRECT(patches,addTarget,&graphAdd);TL_REDIRECT(patches,processTarget,&graphProcess);TL_REDIRECT(patches,uiTarget,&uiSingleton);TL_REDIRECT(patches,closeTarget,&close);TL_REDIRECT(patches,stopPathTarget,&stopPath);TL_REDIRECT(patches,broadcastTarget,&broadcast);if(patches.failed()){invalid();return;}
 if(c.op==0){void(*fn)(void*,EINTERACTABLE_UNITS)=ours?configureCandidate:configureOriginal;if(!autotest::beginInvocation(out,fn))return;fn(self,static_cast<EINTERACTABLE_UNITS>(0));out.callCompleted=1;}
 else{void(*fn)(void*,EINTERACTABLE_UNITS)=ours?startCandidate:startOriginal;if(!autotest::beginInvocation(out,fn))return;fn(self,static_cast<EINTERACTABLE_UNITS>(0));out.callCompleted=1;out.add(static_cast<char*>(self)+0x98,0xc4-0x98);number(field<bool>(player,0x52e));number(field<int>(player,0x330));number(field<bool>(client,0x10bb));}
 number(p->m_unit.getObject()==oldUnit?1:p->m_unit.getObject()==newUnit?2:0);number(field<unsigned>(&witnessOld,8));number(field<unsigned>(&witnessNew,8));number(witnessOld.getObject()==oldUnit);number(witnessNew.getObject()==newUnit);number(calls);patches.restore();interactDtorOriginal(p);number(interactionLifetime.getObject()==NULL);if(interactionLifetime.getObject())invalid();clients->~TArrayList();
 }number(g_iTotalCountOfObjects-before);number(oldLifetime.getObject()==NULL);number(newLifetime.getObject()==NULL);if(g_iTotalCountOfObjects!=constructed||oldLifetime.getObject()||newLifetime.getObject())invalid();}
void original(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),false,out);}void recovered(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned op,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned i=0;i<80;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    world interaction start op %u case %u child %d/%d issue %u/%u calls %u:%u/%u:%u payload %u/%u tail %u/%u\n",op,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,a.capture.callStarted,a.capture.callCompleted,b.capture.callStarted,b.capture.callCompleted,unsigned(a.capture.length),unsigned(b.capture.length),a.capture.length>=4?*reinterpret_cast<const unsigned*>(a.capture.data+a.capture.length-4):0,b.capture.length>=4?*reinterpret_cast<const unsigned*>(b.capture.data+b.capture.length-4):0);coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=80||coverage.different||coverage.missing;}
}
TL_TEST(world_interact_configure){return run(host,0,"world_interact_configure",(uintptr_t)&configureOriginal);}
TL_TEST(world_interact_start){return run(host,1,"world_interact_start",(uintptr_t)&startOriginal);}
