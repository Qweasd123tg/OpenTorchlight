#include <cstring>
#include <string>
#include <CEGUI.h>
#include "SkillMenu.h"
#include "Skill.h"
#include "Character.h"
#include "SkillManager.h"
#include "SoundBank.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,originalSet,(CSkillMenu*,const CEGUI::EventArgs*),"_ZN10CSkillMenu15handle_SetSkillERKN5CEGUI9EventArgsE")
extern "C" bool candidateSet(CSkillMenu*,const CEGUI::EventArgs*) __asm__("_ZN10CSkillMenu15handle_SetSkillERKN5CEGUI9EventArgsE");
TL_FUNCTION(lookupFn,"_ZN13CSkillManager14getSkillByGuidEx")
TL_FUNCTION(effectiveFn,"_ZN6CSkill28calculateEffectiveSkillLevelEv")
TL_FUNCTION(nameFn,"_ZN6CSkill7getNameEv")
TL_FUNCTION(selectFn,"_ZN10CCharacter20setActiveSkillByNameESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(soundFn,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
namespace {
struct Stop{};struct Case{unsigned present,found,level,activation,flags,profile,mutation,fault;};
const Case* cs;autotest::Capture* cap;CSkillMenu* menu;CSkill* skill;CCharacter* actors[2];CSkillManager* managers[2];CSoundBank* banks[2];std::wstring* skillName;unsigned counts[5];
void n(int x){cap->add(&x,4);}template<class T>T& at(void* p,size_t o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
int actor(CCharacter* p){return p==actors[0]?1:p==actors[1]?2:99;}
void event(unsigned i){n(i);++counts[i-1];if(cs->fault==i)throw Stop();}
CSkill* lookup(CSkillManager* p,long long guid){event(1);n(p==managers[0]?1:p==managers[1]?2:99);cap->add(&guid,8);if(cs->mutation)menu->m_pOwner=actors[1];return cs->found?skill:0;}
void effective(CSkill* p){event(2);n(p==skill);unsigned levels[]={0,1,0xffffffffu};int types[]={0,4,5};at<unsigned>(p,0xe0)=levels[cs->level];at<int>(p,0x60)=types[cs->activation];at<bool>(p,0x6b)=cs->flags&1;at<bool>(p,0x6d)=cs->flags&2;if(cs->mutation==2)menu->m_pOwner=actors[0];}
const std::wstring& name(CSkill* p){event(3);n(p==skill);if(cs->mutation)menu->m_pOwner=actors[1];return *skillName;}
void select(CCharacter* p,std::wstring value){n(4);++counts[3];n(actor(p));cap->addText(value);n(value.data()==skillName->data());if(!value.empty())value[0]=L'X';cap->addText(value);cap->addText(*skillName);if(cs->mutation)menu->m_pSoundBank=banks[1];if(cs->fault==4)throw Stop();}
void sound(CSoundBank* p,int id,Ogre::SceneNode* node,float a,float b,bool v){event(5);n(p==banks[0]?1:p==banks[1]?2:99);n(id);n(node==0);cap->add(&a,4);cap->add(&b,4);n(v);}
void ptr(unsigned char* b,unsigned offset,unsigned value){uintptr_t v=value;std::memcpy(b+offset,&v,sizeof(v));}
void side(const Case& c,bool ours,autotest::Capture& out){
 unsigned long long mm[(sizeof(CSkillMenu)+16+7)/8],am[2][0x800/8],gm[2][0x100/8],bm[2][0xd0/8],sk[0x180/8],wm[0x200/8];std::memset(mm,c.profile==1?0x5a:0xa5,sizeof(mm));std::memset(am,0x31,sizeof(am));std::memset(gm,0x42,sizeof(gm));std::memset(bm,0x53,sizeof(bm));std::memset(sk,0x64,sizeof(sk));std::memset(wm,0x75,sizeof(wm));menu=(CSkillMenu*)mm;skill=(CSkill*)sk;cs=&c;cap=&out;std::memset(counts,0,sizeof(counts));
 for(unsigned i=0;i<2;++i){actors[i]=(CCharacter*)am[i];managers[i]=(CSkillManager*)gm[i];banks[i]=(CSoundBank*)bm[i];at<CSkillManager*>(actors[i],0x1c8)=managers[i];}menu->m_pOwner=actors[0];menu->m_pSoundBank=banks[0];
 std::wstring text=c.profile==0?L"":c.profile==1?std::wstring(L"\u03a9\0tail",6):L"SKILL_LONG_NAME_REQUIRING_A_COPY_AND_DETACH";std::wstring shared=text;skillName=&text;
 long long guids[]={0,-1,(-9223372036854775807LL-1)};long long guid=guids[c.profile];at<void*>(wm,0x1d8)=&guid;CEGUI::WindowEventArgs e(c.present?(CEGUI::Window*)wm:0);
 detour::Set d;TL_REDIRECT(d,lookupFn,&lookup);TL_REDIRECT(d,effectiveFn,&effective);TL_REDIRECT(d,nameFn,&name);TL_REDIRECT(d,selectFn,&select);TL_REDIRECT(d,soundFn,&sound);if(d.failed())_exit(60);
 bool threw=false;try{if(ours)autotest::invoke(out,&candidateSet,menu,static_cast<const CEGUI::EventArgs*>(&e));else autotest::invoke(out,&originalSet,menu,static_cast<const CEGUI::EventArgs*>(&e));}catch(const Stop&){threw=true;}catch(...){_exit(61);}
 n(threw);for(unsigned i=0;i<5;++i)n(counts[i]);cap->addText(text);cap->addText(shared);n(text.data()==shared.data());n(*(reinterpret_cast<const int*>(text.data())-2));unsigned char snapshot[sizeof(mm)];std::memcpy(snapshot,mm,sizeof(snapshot));ptr(snapshot,0x30,actor(menu->m_pOwner));ptr(snapshot,0xe8,menu->m_pSoundBank==banks[0]?1:menu->m_pSoundBank==banks[1]?2:99);cap->add(snapshot,sizeof(snapshot));cap->add(sk,sizeof(sk));
}
void a(void* p,autotest::Capture& o){side(*(Case*)p,false,o);}void b(void* p,autotest::Capture& o){side(*(Case*)p,true,o);}
}
TL_TEST(skillmenu_set_skill){autotest::Coverage coverage("skillmenu_set_skill",(uint64_t)(uintptr_t)&originalSet);
 for(unsigned present=0;present<2;++present)for(unsigned found=0;found<2;++found)for(unsigned level=0;level<3;++level)for(unsigned activation=0;activation<3;++activation)for(unsigned flags=0;flags<4;++flags)for(unsigned profile=0;profile<3;++profile)for(unsigned mutation=0;mutation<3;++mutation){Case c={present,found,level,activation,flags,profile,mutation,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||autotest::incomplete(u)||autotest::incomplete(v)||u.childStatus||v.childStatus||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    set skill mismatch %u/%u/%u/%u/%u/%u/%u exits %d/%d first %lu lengths %lu/%lu\n",present,found,level,activation,flags,profile,mutation,u.childStatus,v.childStatus,(unsigned long)f,(unsigned long)u.capture.length,(unsigned long)v.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
TL_TEST(skillmenu_set_skill_expected_exceptions){unsigned count=0;for(unsigned fault=1;fault<=5;++fault)for(unsigned profile=0;profile<3;++profile)for(unsigned mutation=0;mutation<3;++mutation){Case c={1,1,1,0,2,profile,mutation,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    set skill unwind mismatch %u/%u/%u exits %d/%d\n",fault,profile,mutation,u.childStatus,v.childStatus);return 1;}++count;}host->log("    EXPECTED SET SKILL EXCEPTIONS: %u matching unwinds; excluded from normal completion coverage\n",count);return 0;}
