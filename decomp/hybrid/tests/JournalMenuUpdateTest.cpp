
#include <cstring>
#include <string>
#include <limits>
#include <fenv.h>
#define private public
#define protected public
#include <CEGUI.h>
#include <OgreEntity.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include "JournalMenu.h"
#include "GenericModel.h"
#include "Settings.h"
#include "GameUI.h"
#include "GameVariables.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldUpdate,(CJournalMenu*,float),"_ZN12CJournalMenu6updateEf")
extern "C" void newUpdate(CJournalMenu*,float) __asm__("_ZN12CJournalMenu6updateEf");
TL_FUNCTION(settingsFn,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(animationFn,"_ZN13CGenericModel15updateAnimationEfb")
TL_FUNCTION(modelPosFn,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(playingFn,"_ZNK13CGenericModel16animationPlayingERKSs")
TL_FUNCTION(queuedFn,"_ZNK13CGenericModel15animationQueuedERKSs")
TL_FUNCTION(scaledFn,"_ZN7CGameUI7scaledYEf")
extern "C" char positionFn[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char entityFn[] __asm__("_ZN4Ogre6Entity16_updateAnimationEv");
namespace {
struct Case{unsigned state,cached,time,profile,mutate,geometry,serial;};
const Case* cs;autotest::Capture* cap;CJournalMenu* menu;CGenericModel* model;Ogre::Entity* entity;Ogre::SkeletonInstance* skeleton;Ogre::Bone* bones[2];Ogre::Vector3 tags[2];CGameUI* uis[2];CSettings* settings[2];CCharacter* actors[2];CEGUI::Window* windows[4];CEGUI::UVector2 positions[4];unsigned settingsCalls,scaleCalls,positionCalls,layoutCalls;unsigned branches;
void n(int x){cap->add(&x,4);}void f(float x){cap->add(&x,4);}void str(const std::string& x){n(x.size());cap->add(x.data(),x.size());}
int wid(CEGUI::Window* p){for(unsigned i=0;i<4;++i)if(p==windows[i])return i;return p?99:-1;}
int setting(CDynamicPropertyFile* p,unsigned key){n(1);n(p==(CDynamicPropertyFile*)settings[0]?0:p==(CDynamicPropertyFile*)settings[1]?1:99);n(key);++settingsCalls;if(cs->mutate)menu->m_pSettings=settings[1];const int values[]={1920,1080,0,-1,2147483647,(-2147483647-1)};return values[(cs->serial+settingsCalls-1)%6];}
void animation(CGenericModel* p,float dt,bool force){branches|=1;n(2);n(p==model);f(dt);n(force);}
void updateEntity(Ogre::Entity* p){n(3);n(p==entity);}
Ogre::Bone* bone(Ogre::SkeletonInstance* p,const std::string& name){n(4);n(p==skeleton);str(name);if(name=="tag_topskill")return bones[0];if(name=="tag_bottomskill")return bones[1];_exit(66);}
const Ogre::Vector3& derived(Ogre::Bone* p){n(5);unsigned i=p==bones[0]?0:p==bones[1]?1:99;n(i);if(i>1)_exit(67);if(cs->mutate)tags[i].x+=.25f;return tags[i];}
Ogre::Vector3 modelPosition(CPositionableObject* p,bool absolute){n(6);n(p==model);n(absolute);n(++positionCalls);return Ogre::Vector3(cs->mutate?float(positionCalls):3.0f,-7,11);}
float scaled(CGameUI* p,float x){n(7);n(p==uis[0]?0:p==uis[1]?1:99);f(x);n(++scaleCalls);if(cs->mutate)menu->m_pGameUI=menu->m_pGameUI==uis[0]?uis[1]:uis[0];const float scale[]={1,.75f,-1,0,-0.0f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity()};return x*scale[cs->serial%8];}
void position(CEGUI::Window* p,const CEGUI::UVector2& v){n(8);int i=wid(p);n(i);if(i<0||i>3)_exit(68);cap->add(&v,sizeof(v));positions[i]=v;}
void layout(CJournalMenu* p){branches|=2;n(9);n(p==menu);n(p->m_LastPlayedSeconds);++layoutCalls;if(cs->mutate){p->m_bOpen=false;p->m_pOwner=actors[1];}}
bool playing(const CGenericModel* p,const std::string& name){branches|=4;n(10);n(p==model);str(name);return cs->profile&1;}
bool queued(const CGenericModel* p,const std::string& name){branches|=8;n(11);n(p==model);str(name);return cs->profile&2;}
void visible(CGenericModel* p,bool value){branches|=16;n(12);n(p==model);n(value);}
void remove(CEGUI::Window* p,CEGUI::Window* child){branches|=32;n(13);n(wid(p));n(wid(child));child->d_parent=0;}
void canonical(unsigned char* data,unsigned offset,void* a,void* b=0){void* p;std::memcpy(&p,data+offset,8);if(!p||p==a||p==b){uintptr_t v=!p?0:p==a?1:2;std::memcpy(data+offset,&v,8);}}
void side(const Case& c,bool ours,autotest::Capture& output){
 cap=&output;cs=&c;settingsCalls=scaleCalls=positionCalls=layoutCalls=branches=0;
 unsigned long long mm[(sizeof(CJournalMenu)+23)/8],gm[(sizeof(CGenericModel)+7)/8]={0},em[16]={0},sm[16]={0},bm[2][16]={{0}},um[2][16]={{0}},pm[2][16]={{0}},am[2][0x400/8]={{0}},wm[4][(sizeof(CEGUI::Window)+7)/8]={{0}};
 std::memset(mm,c.geometry?0x5a:0xa5,sizeof(mm));menu=(CJournalMenu*)mm;model=(CGenericModel*)gm;entity=(Ogre::Entity*)em;skeleton=(Ogre::SkeletonInstance*)sm;
 void* menuTable[64]={0};menuTable[0x48/8]=(void*)&layout;*(void***)menu=menuTable;
 void* modelTable[64]={0};modelTable[0x50/8]=(void*)&visible;*(void***)model=modelTable;model->m_pEntity=entity;model->m_pSkeleton=skeleton;
 void* skeletonTable[64]={0};skeletonTable[0x1b0/8]=(void*)&bone;*(void***)skeleton=skeletonTable;void* boneTable[80]={0};boneTable[0x200/8]=(void*)&derived;
 const float times[]={0,1.25f,-1.25f,-0.0f,2147483648.0f,4294967296.0f,9223372036854775808.0f,-9223372036854775808.0f,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN(),12345.125f};
 for(unsigned i=0;i<2;++i){uis[i]=(CGameUI*)um[i];settings[i]=(CSettings*)pm[i];actors[i]=(CCharacter*)am[i];std::memcpy((char*)actors[i]+0x388,&times[(c.time+i)%12],4);bones[i]=(Ogre::Bone*)bm[i];*(void***)bones[i]=boneTable;tags[i]=Ogre::Vector3(c.geometry?-1000.0f:float(100+70*i),40+20*i,3);}
 for(unsigned i=0;i<4;++i){windows[i]=(CEGUI::Window*)wm[i];positions[i]=CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0));}windows[1]->d_parent=windows[0];
 menu->m_pParentWindow=windows[0];menu->m_pRoot=windows[1];menu->m_pTopFrame=windows[2];menu->m_pBottomFrame=windows[3];menu->m_pOwner=actors[0];menu->m_pModel=model;menu->m_pSettings=settings[0];menu->m_pGameUI=uis[0];menu->m_bOpen=c.state&1;menu->m_bClosed=c.state&2;menu->m_LastPlayedSeconds=c.cached?0:12345;menu->m_ScreenEdge=-11;menu->m_TopEdge=-12;
 detour::Set d,imports;
#define R(N,F) TL_REDIRECT(d,N,&F)
 R(settingsFn,setting);R(animationFn,animation);R(modelPosFn,modelPosition);R(playingFn,playing);R(queuedFn,queued);R(scaledFn,scaled);
#undef R
 imports.redirect(positionFn,positionFn,&position);imports.redirect(removeFn,removeFn,&remove);imports.redirect(entityFn,entityFn,&updateEntity);if(d.failed()||imports.failed())_exit(69);
 for(unsigned frame=0;frame<2;++frame){n(90);n(frame);float dt=frame?-0.0f:.125f;::feclearexcept(FE_ALL_EXCEPT);if(frame){if(ours)newUpdate(menu,dt);else oldUpdate(menu,dt);}else if(ours)autotest::invoke(output,&newUpdate,menu,dt);else autotest::invoke(output,&oldUpdate,menu,dt);n(::fetestexcept(FE_ALL_EXCEPT));
 unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,menu,sizeof(snapshot));canonical(snapshot,0,menuTable);for(unsigned i=0;i<4;++i)canonical(snapshot,0x10+8*i,windows[i]);canonical(snapshot,0x30,actors[0],actors[1]);canonical(snapshot,0x40,settings[0],settings[1]);canonical(snapshot,0x48,uis[0],uis[1]);canonical(snapshot,0x58,model);cap->add(snapshot,sizeof(snapshot));cap->add(positions,sizeof(positions));n(wid(windows[1]->d_parent));}
 cap->add(am,sizeof(am));n(layoutCalls);n(branches);
}
void a(void* p,autotest::Capture& c){side(*(Case*)p,false,c);}void b(void* p,autotest::Capture& c){side(*(Case*)p,true,c);}
}
TL_TEST(journalmenu_update_differential){autotest::Coverage coverage("journalmenu_update_differential",(uintptr_t)&oldUpdate);unsigned serial=0,all=0;
 for(unsigned state=0;state<4;++state)for(unsigned cached=0;cached<2;++cached)for(unsigned time=0;time<12;++time)for(unsigned profile=0;profile<4;++profile)for(unsigned mutate=0;mutate<2;++mutate)for(unsigned geometry=0;geometry<2;++geometry){Case c={state,cached,time,profile,mutate,geometry,serial++};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(x.capture.length>=4){unsigned flags;std::memcpy(&flags,x.capture.data+x.capture.length-4,4);all|=flags;}if(coverage.observe(host,x,y)||autotest::incomplete(x)||autotest::incomplete(y)||x.childStatus||y.childStatus){coverage.report(host);size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    journal update case %u state %u cache %u time %u profile %u mutate %u geometry %u exits %d/%d first %lu lengths %lu/%lu\n",c.serial,state,cached,time,profile,mutate,geometry,x.childStatus,y.childStatus,(unsigned long)first,(unsigned long)x.capture.length,(unsigned long)y.capture.length);return 1;}}
 coverage.report(host);host->log("    journal update: %u two-frame scenarios, branch mask %u\n",serial,all);return all==63?0:1;
}
