#include <string>
#include <vector>
#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
TL_ORIGINAL(CCharacter*,laOld,(CLevel*,CCharacter*,const Ogre::Vector3&,bool),"_ZN6CLevel12addCharacterEP10CCharacterRKN4Ogre7Vector3Eb")
extern "C" CCharacter*laNew(CLevel*,CCharacter*,const Ogre::Vector3&,bool) __asm__("_ZN6CLevel12addCharacterEP10CCharacterRKN4Ogre7Vector3Eb");
TL_FUNCTION(laActivate,"_ZN9CBaseUnit19activateUnitInLevelEv")
TL_FUNCTION(laPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(laRoom,"_ZN6CLevel28getRoomIndexThatPositionIsInERKN4Ogre7Vector3E")
TL_FUNCTION(laPath,"_ZN10CCharacter16createPathfinderER6CLevel")
TL_FUNCTION(laDrop,"_ZN10CCharacter12dropToGroundER6CLevelfb")
TL_FUNCTION(laOpacity,"_ZN10CCharacter13updateOpacityEfb")
TL_FUNCTION(laRim,"_ZN10CCharacter11setRimlightESbIwSt11char_traitsIwESaIwEE")
namespace {
autotest::Capture*output;CLevel*level;CCharacter*actor;Ogre::SceneManager*scene;unsigned seed;
void number(unsigned n){output->add(&n,4);}void scalar(float f){output->add(&f,4);}void vector(const Ogre::Vector3&v){output->add(&v,sizeof v);}void text(const std::wstring&s){number(s.size());if(!s.empty())output->add(s.data(),s.size()*sizeof(wchar_t));}
struct Character:CCharacter{Character(CResourceManager*r):CCharacter(r){}virtual void addToAvoidanceMap(CLevel&l){number(6);number(&l==level);number(this==actor);}};
void activate(CBaseUnit*p){number(1);number(p==actor);vector(p->m_vPosition);}
void position(CPositionableObject*p,const Ogre::Vector3&v){number(2);number(p==actor);vector(v);p->m_vPosition=v;}
int room(CLevel*p,const Ogre::Vector3&v){number(3);number(p==level);vector(v);return int(seed%9)-4;}
void path(CCharacter*p,CLevel&l){number(4);number(p==actor);number(&l==level);number(p->m_iRoomIndex);}
void drop(CCharacter*p,CLevel&l,float f,bool b){number(5);number(p==actor);number(&l==level);scalar(f);number(b);}
void opacity(CCharacter*p,float f,bool b){number(7);number(p==actor);scalar(f);number(b);scalar(p->m_currentOpacity);p->m_currentOpacity=.75f;}
void rim(CCharacter*p,std::wstring s){number(8);number(p==actor);text(s);}
void execute(void*raw,autotest::Capture&out,bool ours){output=&out;seed=*static_cast<unsigned*>(raw);finishlevel::Fixture f;f.resources.m_pSceneManager=scene;level=&f.level;Character a(&f.resources),b(&f.resources);actor=&a;a.m_vPosition=Ogre::Vector3(-1,2,-3);a.m_iRoomIndex=-71;a.m_currentOpacity=-.5f;
 void*empty=NULL;std::memcpy(&empty,reinterpret_cast<void*>(0x1495cc8),8);if(!empty)new(reinterpret_cast<void*>(0x1495cc8))std::wstring;CLevelTemplateData data(NULL);data.m_sRimlightTexture=seed%3==0?L"":seed%3==1?L"rim/normal.dds":L"rim/\x041b\x0435\x0441.dds";level->m_pLevelTemplateData=seed%5?&data:NULL;f.resources.m_bFlag3=seed&2;
 for(unsigned i=0;i<seed%4;++i){finishlevel::prepend(level->m_pCharacters,static_cast<CCharacter*>(&b));finishlevel::prepend(level->m_activeCharacters,static_cast<CCharacter*>(i%2?&a:&b));}
 detour::Set hooks;TL_REDIRECT(hooks,laActivate,&activate);TL_REDIRECT(hooks,laPosition,&position);TL_REDIRECT(hooks,laRoom,&room);TL_REDIRECT(hooks,laPath,&path);TL_REDIRECT(hooks,laDrop,&drop);TL_REDIRECT(hooks,laOpacity,&opacity);TL_REDIRECT(hooks,laRim,&rim);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef CCharacter*(*Fn)(CLevel*,CCharacter*,const Ogre::Vector3&,bool);Fn fn=ours?laNew:laOld;Ogre::Vector3 p(float(seed%7),float(seed%11)*.5f,float(seed%13)*-.25f);if(!autotest::beginInvocation(out,fn))return;CCharacter*result=fn(level,seed%7?&a:NULL,p,seed&1);out.callCompleted=1;number(result==&a);number(result==NULL);number(a.m_iRoomIndex);scalar(a.m_currentOpacity);vector(a.m_vPosition);
 std::vector<CCharacter*>ids;ids.push_back(&a);ids.push_back(&b);finishlevel::listState(out,level->m_pCharacters,ids);finishlevel::listState(out,level->m_activeCharacters,ids);level->m_pLevelTemplateData=NULL;
}
void original(void*p,autotest::Capture&o){execute(p,o,false);}void candidate(void*p,autotest::Capture&o){execute(p,o,true);}
}
TL_TEST(all_level_add_character){nativegame::Services services;if(!services.ready())return 1;scene=services.scene;autotest::Coverage coverage("all_level_add_character",(uintptr_t)&laOld);for(unsigned i=0;i<512;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    add character seed%u issue%u/%u exit%d/%d length%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
