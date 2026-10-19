#include "AutoTest.h"
#include <Ogre.h>
#include <string>
#include <vector>
#include <map>
#include <limits>
#define private public
#include "Keyframe.h"
#include "CameraShake.h"
#include "UnitThemes.h"
#include "GraphManager.h"
#include "DataGroup.h"
#undef private
#include "tests/NativeGameServices.h"
TL_ORIGINAL(void,kfOldCtor,(CKeyframe*,int,CDataGroup*),"_ZN9CKeyframeC1EiP10CDataGroup")
TL_ORIGINAL(void,kfOldDtor,(CKeyframe*),"_ZN9CKeyframeD1Ev")
TL_ORIGINAL(void,kfOldInitializer,(),"_GLOBAL__I__ZN9CKeyframeC2EiP10CDataGroup")
TL_ORIGINAL(void,kfThemeCtor,(CUnitThemes*,const wchar_t*),"_ZN11CUnitThemesC1EPKw")
TL_ORIGINAL(void,kfThemeDtor,(CUnitThemes*),"_ZN11CUnitThemesD1Ev")
extern "C" void kfNewCtor(CKeyframe*,int,CDataGroup*) __asm__("_ZN9CKeyframeC1EiP10CDataGroup");
namespace {
struct Case{unsigned event,profile;};
const wchar_t* events[]={L"HIT",L"BLENDIN",L"BLENDOUT",L"PLAYSOUND",L"SPAWNPARTICLE",L"SPAWNPARTICLE_STOP_ON_DEATH",L"FOOTSTEP",L"SHOWWEAPONTRAIL",L"HIDEWEAPONTRAIL",L"ATTACKSOUND",L"ENABLECOLLISION",L"DISABLECOLLISION",L"REMOVEPARTICLES",L"REMOVEANIMATIONPARTICLES",L"CAMERASHAKE",L"ATTACKEND",L"UNTARGETABLE",L"TARGETABLE",L"DAMPVELOCITY",L"UNDAMPVELOCITY",L"SHOWWEAPONS",L"HIDEWEAPONS",L"HIDEMESH",L"SHOWMESH",L"FADEOUTMESH",L"FADEINMESH",L"CAMERASHAKE_NO_FALLOFF",L"PLAYSOUND_NO_FALLOFF",L"HITTWO",L"",L"UNKNOWN",L"HIT"};
CUnitThemes* themes;CUnitTheme*theme[3];CGraph*graph;
void number(autotest::Capture& out,int value){out.add(&value,sizeof value);}
void real(autotest::Capture& out,float value){out.add(&value,sizeof value);}
void side(void* raw,autotest::Capture& out,bool ours){
 Case c=*static_cast<Case*>(raw);int before=g_iTotalCountOfObjects;unsigned p=c.profile;
 CDataGroup data(L"KEYFRAME",NULL,4,3,NULL);
 std::wstring event=c.event==31?std::wstring(L"HIT\0X",5):std::wstring(events[c.event]);
 if(p&1)for(unsigned i=0;i<event.size();++i)if(event[i]>=L'A'&&event[i]<=L'Z')event[i]+=L'a'-L'A';
 if(c.event!=29)data.AddDataValue(L"NAME",event,false);
 const wchar_t* names[]={L"",L"keyframe-theme",L"KEYFRAME-THEME",L"MISSING",L"OTHER-THEME",L"",L"keyframe-theme",L"UNKNOWN"};
 if(p)data.AddDataValue(L"UNITTHEME",names[p],false);
 float values[]={0,-1,.005f,.01f,.125f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN(),-std::numeric_limits<float>::infinity()};
 if(p)data.AddDataValue(L"FRAME",values[p]);
 if(p&1)data.AddDataValue(L"SOUND",L"graph/test",false);
 if(p&2)data.AddDataValue(L"LAYOUT",p&1?L"GRAPH\\TEST":L"OTHER/RESOURCE",false);
 if(p&4)data.AddDataValue(L"CAMERASHAKE",p==4?L"":L"GRAPH/TEST",false);
 if(p%3)data.AddDataValue(L"PARTICLEATTACHES",bool(p&1));
 if(p)data.AddDataValue(L"BONE",p&1?L"Bone0":L"Кость",false);
 const int counts[]={1,-3,0,2,11,-2147483647-1,2147483647,1};
 if(p)data.AddDataValue(L"PARTICLECOUNT",counts[p]);
 data.AddDataValue(L"CAMERASHAKEDURATION",values[p]);
 for(unsigned i=0;i<p%3;++i){CDataGroup*offset=data.AddDataGroup(L"BONEOFFSET");offset->AddDataValue(L"X",float(i)+.25f*p);if(p&1)offset->AddDataValue(L"Y",-.5f*p);if(p&2)offset->AddDataValue(L"Z",3.75f+i);}
 CKeyframe*key=static_cast<CKeyframe*>(Ogre::NedAllocImpl::allocBytes(sizeof(CKeyframe),0,0,0));std::memset(key,0xa5,sizeof(CKeyframe));
 void(*function)(CKeyframe*,int,CDataGroup*)=ours?kfNewCtor:kfOldCtor;
 int animation=p%3==0?-1:p%3==1?0:2147483647;
 if(autotest::beginInvocation(out,function)){function(key,animation,&data);out.callCompleted=1;}
 real(out,key->m_frame);out.addText(key->m_text);out.addText(key->m_name);number(out,key->m_animationIndex);out.add(&key->m_offset,sizeof(key->m_offset));out.addText(key->m_themeName);
 int themeID=key->m_theme==NULL?-1:key->m_theme==theme[0]?0:key->m_theme==theme[1]?1:key->m_theme==theme[2]?2:-2;number(out,themeID);
 number(out,key->m_mode);number(out,key->m_flag4C);number(out,key->m_iEventCode);number(out,key->m_cameraShake!=NULL);number(out,g_iTotalCountOfObjects-before);
 TSafePointer<CKeyframe>weak;weak.setObject(key);TSafePointer<CCameraShake>shake;
 if(key->m_cameraShake){CCameraShake*s=key->m_cameraShake;shake.setObject(s);real(out,s->m_fDuration);real(out,s->m_fElapsedTime);real(out,s->m_fMagnitudeMultiplier);real(out,s->m_fDirectionX);real(out,s->m_fDirectionY);real(out,s->m_fDirectionZ);number(out,s->m_graph.getObject()==graph?1:s->m_graph.getObject()==NULL?0:-1);out.addText(s->m_strCameraShakeName);number(out,s->m_nDirectionOrientation);real(out,s->m_fCameraPositionX);real(out,s->m_fCameraPositionY);real(out,s->m_fCameraPositionZ);number(out,s->m_bCameraShakeActive);number(out,s->m_bCameraFallsOffWithDistance);}
 kfOldDtor(key);Ogre::NedAllocImpl::deallocBytes(key);number(out,weak.getObject()==NULL);number(out,shake.getObject()==NULL);number(out,g_iTotalCountOfObjects-before);out.addHeapInUse();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void recovered(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(keyframe_constructor_native){
 void*first=NULL;std::memcpy(&first,reinterpret_cast<void*>(0x14884e0),sizeof first);if(!first)kfOldInitializer();
 nativegame::Services services;if(!services.ready())return 1;
 themes=CUnitThemes::getSingleton();bool own=themes==NULL;
 if(own){themes=static_cast<CUnitThemes*>(Ogre::NedAllocImpl::allocBytes(sizeof(CUnitThemes),0,0,0));kfThemeCtor(themes,L"__keyframe_fixture_absent__.dat");}
 if(CUnitThemes::getSingleton()!=themes)return 1;
 for(unsigned i=0;i<3;++i){theme[i]=new CUnitTheme;theme[i]->m_sName=i==2?L"OTHER-THEME":L"KEYFRAME-THEME";theme[i]->m_iGuid=100+i;themes->getThemes().add(theme[i]);}
 CGraphManager*manager=CGraphManager::getSingleton();graph=new CGraph(GRAPH_LINEAR,L"GRAPH/TEST",1);manager->m_GraphsByName[L"GRAPH/TEST"]=graph;
 autotest::Coverage coverage("keyframe_constructor_native",0x8d3eb0);int failures=0;
 for(unsigned event=0;event<32&&!failures;++event)for(unsigned profile=0;profile<8;++profile){Case c={event,profile};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    Keyframe event%u profile%u exits%d/%d issue%u/%u bytes%lu/%lu\n",event,profile,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);failures=1;break;}}
 coverage.report(host);manager->m_GraphsByName.erase(L"GRAPH/TEST");delete graph;
 for(unsigned i=0;i<3;++i){themes->getThemes().remove(theme[i]);delete theme[i];}
 if(own){kfThemeDtor(themes);Ogre::NedAllocImpl::deallocBytes(themes);}
 return failures||coverage.completed!=256||coverage.different||coverage.missing;
}
