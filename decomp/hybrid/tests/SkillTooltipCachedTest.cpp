// Cached-name/level path of the complete entry; paired with content coverage.
#include <string>
#include <cstring>
#include <new>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include "GameUI.h"
#include "SkillTooltip.h"
#include "Skill.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldTooltip,(CSkillTooltip*,CBaseUnit*,CSkill*,float,float),"_ZN13CSkillTooltip11showTooltipEP9CBaseUnitP6CSkillff")
extern "C" void newTooltip(CSkillTooltip*,CBaseUnit*,CSkill*,float,float) __asm__("_ZN13CSkillTooltip11showTooltipEP9CBaseUnitP6CSkillff");
TL_FUNCTION(nameFn,"_ZN6CSkill7getNameEv")
TL_FUNCTION(levelFn,"_ZN6CSkill28calculateEffectiveSkillLevelEv")
TL_FUNCTION(widthFn,"_ZN7CGameUI14getWindowWidthEv")
TL_FUNCTION(heightFn,"_ZN7CGameUI15getWindowHeightEv")
#define IMPORT(N,S) extern "C" char N[] __asm__(S)
IMPORT(getWidthFn,"_ZNK5CEGUI6Window8getWidthEv");
IMPORT(getHeightFn,"_ZNK5CEGUI6Window9getHeightEv");
IMPORT(setPositionFn,"_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
IMPORT(addFn,"_ZN5CEGUI6Window14addChildWindowEPS0_");
IMPORT(frontFn,"_ZN5CEGUI6Window11moveToFrontEv");
#undef IMPORT
namespace {
struct Case {unsigned profile,position,attached,mutate;};
autotest::Capture* cap;const Case* input;CSkillTooltip* tip;CSkill* skill;CGameUI* ui[2];CEGUI::Window* windows[3];CEGUI::UVector2 sizes[3],positions[3];std::wstring name;unsigned calls;
const uintptr_t caches[]={0x14b9d08,0x14b9d00,0x14b9cf8,0x14b9cf0,0x14b9ce8,0x14b9ce0,0x14b9cd8,0x14b9cd0,0x14b9cc8};
const uintptr_t guards[]={0x14b9c80,0x14b9c88,0x14b9c90,0x14b9c98,0x14b9ca0,0x14b9ca8,0x14b9cb0,0x14b9cb8,0x14b9cc0};
template<class T>T& at(void* p,size_t off){return *(T*)((char*)p+off);}
CGameUI*& globalUI(){return *(CGameUI**)0x14b9c68;}
void n(int x){cap->add(&x,4);}void f(float x){cap->add(&x,4);}
int id(const CEGUI::Window* p){for(int i=0;i<3;++i)if(p==windows[i])return i;return p?-2:-1;}
const std::wstring& getName(CSkill* p){n(1);n(p==skill);return name;}
void level(CSkill* p){n(2);n(p==skill);if(input->mutate&1)tip->m_iIndex=99;at<unsigned>(p,0xe0)=5;}
float width(CGameUI* p){n(3);n(p==ui[0]?0:p==ui[1]?1:-1);const float v[]={1920,0,-1,100,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN(),-2147483648.0f,2147483648.0f};if(input->mutate&1)globalUI()=ui[1];return v[input->profile%8];}
float height(CGameUI* p){n(4);n(p==ui[0]?0:p==ui[1]?1:-1);return input->profile%5==0?60.0f:1080.0f;}
CEGUI::UDim getWidth(const CEGUI::Window* p){n(5);n(id(p));++calls;if(input->mutate&2)tip->m_pWindow=windows[2];return sizes[id(p)].d_x;}
CEGUI::UDim getHeight(const CEGUI::Window* p){n(6);n(id(p));++calls;if(input->mutate&2)tip->m_pWindow=windows[0];return sizes[id(p)].d_y;}
void setPosition(CEGUI::Window* p,const CEGUI::UVector2& v){n(7);n(id(p));cap->add(&v,sizeof(v));positions[id(p)]=v;}
void add(CEGUI::Window* p,CEGUI::Window* child){n(8);n(id(p));n(id(child));child->d_parent=p;}
void front(CEGUI::Window* p){n(9);n(id(p));}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;cap=&out;calls=0;unsigned long long um[2][900]={0},sm[44]={0},tm[47]={0},wm[3][(sizeof(CEGUI::Window)+7)/8];memset(wm,0,sizeof(wm));ui[0]=(CGameUI*)um[0];ui[1]=(CGameUI*)um[1];skill=(CSkill*)sm;tip=(CSkillTooltip*)tm;name=L"cachedSkill";new((char*)tip+0x18)std::wstring(name);tip->m_iIndex=5;at<unsigned>(skill,0xe0)=5;
 for(int i=0;i<3;++i){windows[i]=(CEGUI::Window*)wm[i];positions[i]=CEGUI::UVector2(CEGUI::UDim(.25f,123+i),CEGUI::UDim(-.5f,234+i));sizes[i]=CEGUI::UVector2(CEGUI::UDim(.25f,100+i*31),CEGUI::UDim(-.5f,60+i*17));}
 const float v[]={0,-0.0f,.5f,-.5f,2.2f,-2.2f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};sizes[0].d_x.d_scale=v[c.profile%8];sizes[0].d_y.d_scale=v[(c.profile/4)%8];sizes[0].d_x.d_offset=c.profile%3==0?-400:c.profile%3==1?140:2400;
 const float mx[]={25,1800,-200,4000,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),52};const float my[]={5,1200,1000,-500,2500,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),52};
 tip->m_pGameUI=ui[1];globalUI()=ui[0];tip->m_pRoot=windows[1];tip->m_pWindow=windows[0];windows[0]->d_parent=c.attached?windows[1]:0;
 for(unsigned i=0;i<9;++i){new((void*)caches[i])std::wstring(L"cached");*(unsigned char*)guards[i]=1;}
 detour::Set d;TL_REDIRECT(d,nameFn,&getName);TL_REDIRECT(d,levelFn,&level);TL_REDIRECT(d,widthFn,&width);TL_REDIRECT(d,heightFn,&height);
#define I(N,F) d.redirect(N,N,&F)
 I(getWidthFn,getWidth);I(getHeightFn,getHeight);I(setPositionFn,setPosition);I(addFn,add);I(frontFn,front);
#undef I
 if(d.failed())_exit(43);
 if(ours)autotest::invoke(out,&newTooltip,tip,(CBaseUnit*)0,skill,mx[c.position],my[c.position]);else autotest::invoke(out,&oldTooltip,tip,(CBaseUnit*)0,skill,mx[c.position],my[c.position]);
 n(99);n(id(windows[0]->d_parent));n(id(tip->m_pWindow));n(tip->m_iIndex);n(globalUI()==ui[0]?0:1);n(calls);cap->add(positions,sizeof(positions));
}
void a(void* p,autotest::Capture& c){side(*(Case*)p,false,c);}void b(void* p,autotest::Capture& c){side(*(Case*)p,true,c);}
}
TL_TEST(skill_tooltip_cached_differential){autotest::Coverage cv("skill_tooltip_cached_differential",(uint64_t)(uintptr_t)&oldTooltip);unsigned count=0;for(unsigned profile=0;profile<32;++profile)for(unsigned position=0;position<8;++position)for(unsigned attached=0;attached<2;++attached)for(unsigned mutate=0;mutate<4;++mutate){Case c={profile,position,attached,mutate};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);++count;if(cv.observe(host,x,y)){size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    profile %u position %u attached %u mutate %u status %d/%d bytes %lu/%lu first %lu\n",profile,position,attached,mutate,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t i=0;i<x.capture.length&&i+4<=y.capture.length;i+=4){int u,v;memcpy(&u,x.capture.data+i,4);memcpy(&v,y.capture.data+i,4);host->log("      %lu %d/%d\n",(unsigned long)i,u,v);}return 1;}}cv.report(host);host->log("    cached skill-tooltip placement: %u completed comparisons\n",count);return 0;}
