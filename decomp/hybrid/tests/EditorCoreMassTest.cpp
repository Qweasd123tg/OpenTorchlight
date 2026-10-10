// Editor ownership, service routing, history and scene counters compared with
// the original. History tests include retained null redo nodes, trimming and
// callback mutations; singleton tests observe allocation and exceptional cleanup.
#include <cstring>
#include <new>
#include <list>
#include <string>
#include <OgreQuaternion.h>
#include "AutoTest.h"
#include "Detour.h"
#include "Settings.h"
extern "C" void* editorGlobal __asm__("gEditor");
extern "C" void* logicDescriptorTable[] __asm__("_ZTV21CLogicGroupDescriptor");
extern "C" void* descriptorTable[] __asm__("_ZTV11CDescriptor");
extern "C" char allocFn[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char freeFn[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
TL_ORIGINAL(void*,original0,(void*),"_ZN7CEditor9getCameraEv")
extern "C" void* candidate0(void*) __asm__("_ZN7CEditor9getCameraEv");
TL_ORIGINAL(void,original1,(void*,int,int,int),"_ZN7CEditor19setDirectionalColorEiii")
extern "C" void candidate1(void*,int,int,int) __asm__("_ZN7CEditor19setDirectionalColorEiii");
TL_ORIGINAL(void,original2,(void*,int,int,int),"_ZN7CEditor23setMaterialAmbientColorEiii")
extern "C" void candidate2(void*,int,int,int) __asm__("_ZN7CEditor23setMaterialAmbientColorEiii");
TL_ORIGINAL(void,original3,(void*,int,int,int),"_ZN7CEditor15setAmbientColorEiii")
extern "C" void candidate3(void*,int,int,int) __asm__("_ZN7CEditor15setAmbientColorEiii");
TL_ORIGINAL(void,original4,(void*,float),"_ZN7CEditor23setDirectionalIntensityEf")
extern "C" void candidate4(void*,float) __asm__("_ZN7CEditor23setDirectionalIntensityEf");
TL_ORIGINAL(void,original5,(void*,void*,bool),"_ZN7CEditor7addUndoEP5CUndob")
extern "C" void candidate5(void*,void*,bool) __asm__("_ZN7CEditor7addUndoEP5CUndob");
TL_ORIGINAL(void,original6,(void*,void*),"_ZN7CEditor7addRedoEP5CUndo")
extern "C" void candidate6(void*,void*) __asm__("_ZN7CEditor7addRedoEP5CUndo");
TL_ORIGINAL(void*,original7,(),"_ZN7CEditor12getSingletonEv")
extern "C" void* candidate7() __asm__("_ZN7CEditor12getSingletonEv");
TL_ORIGINAL(unsigned,original8,(void*),"_ZN12CEditorScene28getNumberOfParticlesUpdatingEv")
extern "C" unsigned candidate8(void*) __asm__("_ZN12CEditorScene28getNumberOfParticlesUpdatingEv");
TL_ORIGINAL(unsigned,original9,(void*,bool),"_ZN12CEditorScene28getNumberOfTimelinesUpdatingEb")
extern "C" unsigned candidate9(void*,bool) __asm__("_ZN12CEditorScene28getNumberOfTimelinesUpdatingEb");
TL_ORIGINAL(unsigned,original10,(void*),"_ZN12CEditorScene30getNumberOfTimelinesThatDoLoopEv")
extern "C" unsigned candidate10(void*) __asm__("_ZN12CEditorScene30getNumberOfTimelinesThatDoLoopEv");
TL_ORIGINAL(void,original11,(void*,bool),"_ZN12CEditorScene12setActivatedEb")
extern "C" void candidate11(void*,bool) __asm__("_ZN12CEditorScene12setActivatedEb");
TL_ORIGINAL(Ogre::Quaternion,original12,(void*),"_ZN16CObjectControl3D23GetSelectionOrientationEv")
extern "C" Ogre::Quaternion candidate12(void*) __asm__("_ZN16CObjectControl3D23GetSelectionOrientationEv");
TL_FUNCTION(target_setInt,"_ZN20CDynamicPropertyFile6SetIntEji")
TL_FUNCTION(target_setFloat,"_ZN20CDynamicPropertyFile8SetFloatEjf")
TL_FUNCTION(target_refresh,"_ZN11CGameClient15refreshLightingEv")
TL_FUNCTION(target_constructor,"_ZN7CEditorC1Ev")
TL_FUNCTION(target_descriptor,"_ZN18CDescriptorManager13GetDescriptorEPKwb")
TL_FUNCTION(target_activate,"_ZN18CDescriptorManager19activateDescriptorsEP12CEditorScene")
TL_FUNCTION(target_deactivate,"_ZN18CDescriptorManager21deactivateDescriptorsEP12CEditorScene")
TL_FUNCTION(target_levelActivated,"_ZN21CLogicGroupDescriptor14levelActivatedEP12CEditorScene")

namespace {
struct Case{unsigned operation,mode,seed,count,limit;int a,b,d;float amount;bool flag,clear;};
const Case* input;autotest::Capture* capture;
void* editors[3];void* editor;void* settings[2];void* resources[2];void* clients[2];void* cameras[2];void* undos[10];void* scene;void* manager;void* descriptors[2];void* particles[8];
std::list<void*>* undoList;std::list<void*>* redoList;
unsigned setCalls,deleteCalls,lookupCalls,allocationCalls,freeCalls;
void number(unsigned n){capture->add(&n,4);}
unsigned identity(void*p){if(!p)return 0;for(unsigned i=0;i<3;++i)if(p==editors[i])return 1+i;
 for(unsigned i=0;i<2;++i){if(p==settings[i])return 10+i;if(p==resources[i])return 20+i;if(p==clients[i])return 30+i;if(p==cameras[i])return 40+i;if(p==descriptors[i])return 50+i;}
 for(unsigned i=0;i<10;++i)if(p==undos[i])return 60+i;for(unsigned i=0;i<8;++i)if(p==particles[i])return 80+i;
 if(p==scene)return 90;if(p==manager)return 91;return 999;}
void event(unsigned code,void*p){number(code);number(identity(p));}
void pointerAt(void*p,unsigned at,void*v){std::memcpy(static_cast<char*>(p)+at,&v,8);}
void integerAt(void*p,unsigned at,unsigned v){std::memcpy(static_cast<char*>(p)+at,&v,4);}
void changedSettings(){++setCalls;if(input->mode==3){pointerAt(editor,0x50,settings[setCalls%2]);pointerAt(editor,0x128,resources[setCalls%2]);}}
void setInt(void*p,unsigned key,int value){event(1,p);number(key);capture->add(&value,4);changedSettings();}
void setFloat(void*p,unsigned key,float value){event(2,p);number(key);capture->add(&value,4);changedSettings();}
void refresh(void*p){event(3,p);}
void* camera(void*p){event(4,p);return input->flag?NULL:cameras[1];}
void destroy(void*p){event(5,p);++deleteCalls;if(input->mode==5&&deleteCalls==1&&input->operation!=7){
 if(input->operation==5)undoList->push_front(undos[9]);else redoList->push_front(undos[9]);}
 if(input->mode==6)integerAt(editor,0x160,2);}
void* allocate(size_t bytes,const char*file,int line,const char*function){number(6);number(bytes);number(file==NULL);number(line);number(function==NULL);++allocationCalls;if(input->mode==8)throw std::bad_alloc();return editors[2];}
void release(void*p){event(7,p);++freeCalls;}
void constructor(void*p){event(8,p);std::memset(p,0x42,0x1f8);if(input->mode==9)throw 417;
 if(input->mode==1)editorGlobal=p;else if(input->mode==2)editorGlobal=editors[1];}
void* descriptor(void*p,const wchar_t*name,bool create){event(9,p);capture->addText(std::wstring(name));number(create);++lookupCalls;
 if(input->mode==1||input->mode==7)return NULL;
 if(std::wstring(name)==L"Particle"&&input->mode==2)return NULL;
 return std::wstring(name)==L"Layout Link Particle"?descriptors[1]:descriptors[0];}
void activate(void*p,void*s){event(10,p);number(identity(s));number(static_cast<unsigned char*>(s)[0x18c]);if(input->mode==6)static_cast<unsigned char*>(s)[0x18c]=0;}
void deactivate(void*p,void*s){event(11,p);number(identity(s));number(static_cast<unsigned char*>(s)[0x18c]);}
void levelActivated(void*p,void*s){event(12,p);number(identity(s));}
bool playing(void*p){event(13,p);return (identity(p)+input->seed)%2;}
unsigned nestedParticles(void*p){event(14,p);return (identity(p)+input->seed)%3?input->seed:0xffffffffu;}
void side(Case&c,bool ours,autotest::Capture&out){
 input=&c;capture=&out;setCalls=deleteCalls=lookupCalls=allocationCalls=freeCalls=0;
 unsigned long long editorBytes[3][0x1f8/8]={{0}},settingBytes[2][16]={{0}},resourceBytes[2][16]={{0}},clientBytes[2][8]={{0}},cameraBytes[2][8]={{0}},undoBytes[10][8]={{0}},sceneBytes[0x190/8]={0},managerBytes[16]={0},descriptorBytes[2][0x200/8]={{0}},particleBytes[8][0x200/8]={{0}};
 void* vtable[10]={0};vtable[1]=reinterpret_cast<void*>(&destroy);vtable[8]=reinterpret_cast<void*>(&camera);
 void* particleTable[70]={0};particleTable[0x210/8]=reinterpret_cast<void*>(&playing);particleTable[0x220/8]=reinterpret_cast<void*>(&nestedParticles);
 for(unsigned i=0;i<3;++i){editors[i]=editorBytes[i];pointerAt(editors[i],0,vtable);}editor=editors[0];
 for(unsigned i=0;i<2;++i){settings[i]=settingBytes[i];resources[i]=resourceBytes[i];clients[i]=clientBytes[i];cameras[i]=cameraBytes[i];descriptors[i]=descriptorBytes[i];}
 for(unsigned i=0;i<10;++i){undos[i]=undoBytes[i];pointerAt(undos[i],0,vtable);}
 scene=sceneBytes;manager=managerBytes;pointerAt(scene,0x100,c.mode==0?NULL:manager);reinterpret_cast<unsigned char*>(scene)[0x18c]=c.clear;
 pointerAt(descriptors[0],0,(c.mode==4?descriptorTable:logicDescriptorTable)+2);
 void* clientPointers[2]={c.mode==5?NULL:clients[0],clients[1]};
 for(unsigned i=0;i<2;++i){pointerAt(resources[i],0x28,clientPointers+i);integerAt(resources[i],0x30,c.mode==0?0:1);integerAt(resources[i],0x34,1);}
 pointerAt(editor,0x50,settings[0]);pointerAt(editor,0x128,c.mode==4?reinterpret_cast<void*>(-40LL):resources[0]);
 pointerAt(editor,0x58,c.mode==0?NULL:resources[0]);pointerAt(resources[0],0,vtable);
 pointerAt(editor,0x88,c.mode==1?NULL:cameras[0]);integerAt(editor,0x64,c.seed);integerAt(editor,0x160,c.limit);
 unsigned* keys[]={&KSETTINGS_AMBIENT_LIGHT_RED,&KSETTINGS_AMBIENT_LIGHT_GREEN,&KSETTINGS_AMBIENT_LIGHT_BLUE,&KSETTINGS_DIRECTIONAL_LIGHT_RED,&KSETTINGS_DIRECTIONAL_LIGHT_GREEN,&KSETTINGS_DIRECTIONAL_LIGHT_BLUE,&KSETTINGS_MATERIAL_AMBIENT_LIGHT_RED,&KSETTINGS_MATERIAL_AMBIENT_LIGHT_GREEN,&KSETTINGS_MATERIAL_AMBIENT_LIGHT_BLUE,&KSETTINGS_F_DIRECTIONAL_INTENSITY};
 for(unsigned i=0;i<10;++i)*keys[i]=17*i+c.seed;
 typedef std::list<void*> History;undoList=::new(static_cast<char*>(editor)+0x140)History;redoList=::new(static_cast<char*>(editor)+0x150)History;
 for(unsigned i=0;i<c.count;++i){undoList->push_back(i%3?undos[i]:NULL);redoList->push_back(i%2?undos[7-i]:NULL);}
 void* particlePointers[8];
 for(unsigned i=0;i<8;++i){particles[i]=particleBytes[i];particlePointers[i]=particles[i];pointerAt(particles[i],0,particleTable);
  static_cast<unsigned char*>(particles[i])[0xa1]=(i+c.seed)%2;static_cast<unsigned char*>(particles[i])[0x89]=(i+c.seed)%3!=0;}
 for(unsigned i=0;i<2;++i){pointerAt(descriptors[i],0xe0,particlePointers);integerAt(descriptors[i],0xe8,c.count);integerAt(descriptors[i],0xec,c.mode==6?2:8);}
 editorGlobal=c.operation==7?(c.mode==7?editors[0]:NULL):editors[0];
 detour::Set patches;
 TL_REDIRECT(patches,target_setInt,&setInt);
 TL_REDIRECT(patches,target_setFloat,&setFloat);
 TL_REDIRECT(patches,target_refresh,&refresh);
 TL_REDIRECT(patches,target_constructor,&constructor);
 TL_REDIRECT(patches,target_descriptor,&descriptor);
 TL_REDIRECT(patches,target_activate,&activate);
 TL_REDIRECT(patches,target_deactivate,&deactivate);
 TL_REDIRECT(patches,target_levelActivated,&levelActivated);
 if(c.operation==7){patches.redirect(allocFn,allocFn,&allocate);patches.redirect(freeFn,freeFn,&release);}
 if(patches.failed())_exit(41);
 switch(c.operation){
 case 0:{void*(*fn)(void*)=ours?&candidate0:&original0;if(!autotest::beginInvocation(out,fn))return;void* result=fn(editor);out.callCompleted=1;number(identity(result));break;}
 case 1:autotest::invoke(out,ours?&candidate1:&original1,editor,c.a,c.b,c.d);break;
 case 2:autotest::invoke(out,ours?&candidate2:&original2,editor,c.a,c.b,c.d);break;
 case 3:autotest::invoke(out,ours?&candidate3:&original3,editor,c.a,c.b,c.d);break;
 case 4:autotest::invoke(out,ours?&candidate4:&original4,editor,c.amount);break;
 case 5:autotest::invoke(out,ours?&candidate5:&original5,editor,c.flag?NULL:undos[8],c.clear);break;
 case 6:autotest::invoke(out,ours?&candidate6:&original6,editor,c.flag?NULL:undos[8]);break;
 case 7:{void*(*fn)()=ours?&candidate7:&original7;if(!autotest::beginInvocation(out,fn))return;void* result=NULL;int fault=0;
  try{result=fn();out.callCompleted=1;}catch(const std::bad_alloc&){fault=1;}catch(int n){fault=n;}
  const bool expectedException=c.mode==8||c.mode==9;
  const int expectedFault=c.mode==8?1:c.mode==9?417:0;
  if(fault!=expectedFault || out.callCompleted!=(expectedException?0u:1u) ||
     (expectedException && (allocationCalls!=1 || freeCalls!=(c.mode==9?1u:0u) || editorGlobal!=NULL || result!=NULL)))
   out.issue=autotest::Capture::InvalidReport;
  number(identity(result));number(fault);break;}
 case 8:autotest::invoke(out,ours?&candidate8:&original8,scene);break;
 case 9:autotest::invoke(out,ours?&candidate9:&original9,scene,c.flag);break;
 case 10:autotest::invoke(out,ours?&candidate10:&original10,scene);break;
 case 11:autotest::invoke(out,ours?&candidate11:&original11,scene,c.flag);break;
 case 12:{Ogre::Quaternion(*fn)(void*)=ours?&candidate12:&original12;if(!autotest::beginInvocation(out,fn))return;Ogre::Quaternion result=fn(editor);out.callCompleted=1;out.add(&result.w,4);out.add(&result.x,4);out.add(&result.y,4);out.add(&result.z,4);break;}

 }
 number(setCalls);number(deleteCalls);number(lookupCalls);number(allocationCalls);number(freeCalls);number(identity(editorGlobal));
 number(undoList->size());for(History::iterator i=undoList->begin();i!=undoList->end();++i)number(identity(*i));
 number(redoList->size());for(History::iterator i=redoList->begin();i!=redoList->end();++i)number(identity(*i));
 unsigned char snapshot[0x1f8];std::memcpy(snapshot,editor,0x1f8);std::memset(snapshot+0x140,0,0x20);out.add(snapshot,sizeof(snapshot));
 out.add(editorBytes[1],sizeof(editorBytes[1]));out.add(editorBytes[2],sizeof(editorBytes[2]));out.add(sceneBytes,sizeof(sceneBytes));out.add(particleBytes,sizeof(particleBytes));
 patches.restore();undoList->~History();redoList->~History();
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(editor_core_mass_differential){
 const uint64_t addresses[]={
(uint64_t)(uintptr_t)&original0,(uint64_t)(uintptr_t)&original1,(uint64_t)(uintptr_t)&original2,(uint64_t)(uintptr_t)&original3,(uint64_t)(uintptr_t)&original4,(uint64_t)(uintptr_t)&original5,(uint64_t)(uintptr_t)&original6,(uint64_t)(uintptr_t)&original7,(uint64_t)(uintptr_t)&original8,(uint64_t)(uintptr_t)&original9,(uint64_t)(uintptr_t)&original10,(uint64_t)(uintptr_t)&original11,(uint64_t)(uintptr_t)&original12};

 const unsigned limits[]={0,1,2,5,8,0xffffffffu};const int values[]={0,1,-1,255,256,2147483647,(-2147483647-1)};
 for(unsigned operation=0;operation<13;++operation){autotest::Coverage coverage("editor_core_mass_differential",addresses[operation]);
  unsigned expectedExceptions=0,allocationExceptions=0,constructorExceptions=0;
  for(unsigned n=0;n<420;++n){Case c={operation,n%10,n/10,(n/10)%8,limits[(n/20)%6],values[(n/10)%7],values[(n/20)%7],values[(n/30)%7],n%2?-0.0f:0.3333333f,((n/10)%2)!=0,((n/20)%2)!=0};
   autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
   const bool expectedException=operation==7&&(c.mode==8||c.mode==9);
   int result=0;
   if(expectedException){
    const bool valid=a.childStatus==0&&b.childStatus==0&&a.reportValid&&b.reportValid&&
     !autotest::incomplete(a)&&!autotest::incomplete(b)&&
     a.capture.issue==autotest::Capture::Complete&&b.capture.issue==autotest::Capture::Complete&&
     a.capture.callStarted==1&&b.capture.callStarted==1&&
     a.capture.callCompleted==0&&b.capture.callCompleted==0&&
     a.capture.callTarget==addresses[operation]&&host&&host->abi_version==TLHYBRID_ABI_VERSION&&
     host->comparison_pair&&host->comparison_pair(addresses[operation],b.capture.callTarget);
    if(!valid)result=2;
    else if(a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length))result=1;
    else{++expectedExceptions;if(c.mode==8)++allocationExceptions;else ++constructorExceptions;}
   }else result=coverage.observe(host,a,b);
   if(result){host->log("    editor core operation %u case %u pair %d status %d/%d bytes %lu/%lu\n",operation,n,result,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}
  }coverage.report(host);
  const unsigned normalExpected=operation==7?336u:420u;
  if(coverage.completed!=normalExpected||coverage.different||coverage.missing||
     expectedExceptions!=(operation==7?84u:0u)||allocationExceptions!=(operation==7?42u:0u)||
     constructorExceptions!=(operation==7?42u:0u))return 1;
  if(operation==7)host->log("    editor core expected exceptions: %u allocation, %u constructor; %u matching fault/cleanup witnesses excluded from normal coverage\n",allocationExceptions,constructorExceptions,expectedExceptions);
 }return 0;
}
