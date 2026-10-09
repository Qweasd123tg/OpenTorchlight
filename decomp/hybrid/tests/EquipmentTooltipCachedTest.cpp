// Original-versus-compiled comparison of the cached-item placement path.
#include <string>
#include <cstring>
#include <new>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include "GameUI.h"
#include "EquipmentTooltip.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(void,oldTooltip,(CGameUI*,CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*),"_ZN7CGameUI20showEquipmentTooltipEP10CCharacterP10CEquipmentP17CEquipmentTooltipS5_S5_")
extern "C" void newTooltip(CGameUI*,CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*) __asm__("_ZN7CGameUI20showEquipmentTooltipEP10CCharacterP10CEquipmentP17CEquipmentTooltipS5_S5_");
TL_FUNCTION(keyFn,"_Z16GetAsyncKeyStatej")
TL_FUNCTION(widthFn,"_ZN7CGameUI14getWindowWidthEv")
TL_FUNCTION(heightFn,"_ZN7CGameUI15getWindowHeightEv")
#define IMPORT(N,S) extern "C" char N[] __asm__(S)
IMPORT(getWidthFn,"_ZNK5CEGUI6Window8getWidthEv");
IMPORT(getHeightFn,"_ZNK5CEGUI6Window9getHeightEv");
IMPORT(getPositionFn,"_ZNK5CEGUI6Window11getPositionEv");
IMPORT(setPositionFn,"_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
IMPORT(addFn,"_ZN5CEGUI6Window14addChildWindowEPS0_");
IMPORT(removeFn,"_ZN5CEGUI6Window17removeChildWindowEPS0_");
IMPORT(frontFn,"_ZN5CEGUI6Window11moveToFrontEv");
#undef IMPORT
namespace {
struct Case {unsigned profile,peers,position,key,attached,mutate;};
autotest::Capture* cap;const Case* input;CGameUI* ui;CEquipmentTooltip* tips[3];CEGUI::Window* windows[4];CEGUI::UVector2 positions[4],sizes[4];unsigned calls;
const uintptr_t caches[]={0x14b9b60,0x14b9b58,0x14b9b50,0x14b9b48,0x14b9b40,0x14b9b38,0x14b9b30,0x14b9b28,0x14b9b20,0x14b9b18,0x14b9b10,0x14b9b08,0x14b9b00,0x14b9af8,0x14b9af0,0x14b9ae8};
const uintptr_t guards[]={0x14b9a68,0x14b9a70,0x14b9a78,0x14b9a80,0x14b9a88,0x14b9a90,0x14b9a98,0x14b9aa0,0x14b9aa8,0x14b9ab0,0x14b9ab8,0x14b9ac0,0x14b9ac8,0x14b9ad0,0x14b9ad8,0x14b9ae0};

template<class T>T& at(void* p,size_t off){return *(T*)((char*)p+off);}
void n(int v){cap->add(&v,4);}void f(float v){cap->add(&v,4);}int id(const CEGUI::Window* p){for(int i=0;i<4;++i)if(p==windows[i])return i;return p?-2:-1;}
void change(){++calls;if(input->mutate){positions[2].d_x.d_offset+=11;positions[3].d_x.d_offset-=7;positions[3].d_y.d_offset+=13;at<long>(ui,0x12d0)+=3;at<long>(ui,0x12d8)-=2;}}
float width(CGameUI* p){n(1);n(p==ui);const float v[]={1920,0,-1,100,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN(),-2147483648.0f,2147483648.0f};return v[input->profile%8];}
float height(CGameUI* p){n(2);n(p==ui);return input->profile%5==0?60.0f:1080.0f;}
CEGUI::UDim getWidth(const CEGUI::Window* p){n(3);n(id(p));change();return sizes[id(p)].d_x;}
CEGUI::UDim getHeight(const CEGUI::Window* p){n(4);n(id(p));change();return sizes[id(p)].d_y;}
const CEGUI::UVector2& getPosition(const CEGUI::Window* p){n(5);n(id(p));change();return positions[id(p)];}
void setPosition(CEGUI::Window* p,const CEGUI::UVector2& v){n(6);n(id(p));cap->add(&v,sizeof(v));positions[id(p)]=v;}
void add(CEGUI::Window* p,CEGUI::Window* child){n(7);n(id(p));n(id(child));child->d_parent=p;}void remove(CEGUI::Window* p,CEGUI::Window* child){n(8);n(id(p));n(id(child));child->d_parent=0;}void front(CEGUI::Window* p){n(9);n(id(p));}
short key(unsigned k){n(10);n(k);const short values[]={0,1,32767,-32768};return values[input->key];}
void side(const Case& c,bool ours,autotest::Capture& out){input=&c;cap=&out;calls=0;unsigned long long um[900]={0},em[160]={0},am[200]={0},tm[3][24]={0},wm[4][(sizeof(CEGUI::Window)+7)/8];memset(wm,0,sizeof(wm));ui=(CGameUI*)um;CEquipment* eq=(CEquipment*)em;CCharacter* owner=(CCharacter*)am;
 for(int i=0;i<4;++i){windows[i]=(CEGUI::Window*)wm[i];sizes[i]=CEGUI::UVector2(CEGUI::UDim(.25f,100+i*31),CEGUI::UDim(-.5f,60+i*17));positions[i]=CEGUI::UVector2(CEGUI::UDim(.3f,400+i*150),CEGUI::UDim(-.7f,300+i*80));}
 const float scalars[]={0,-0.0f,.5f,-.5f,2.2f,-2.2f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};sizes[0].d_x.d_scale=scalars[c.profile%8];sizes[0].d_y.d_scale=scalars[(c.profile/4)%8];sizes[0].d_x.d_offset=c.profile%3==0?-400:c.profile%3==1?140:2400;
 positions[2].d_x.d_offset=c.position%2?100:900;positions[3].d_x.d_offset=c.position%2?600:300;positions[3].d_y.d_offset=c.position>=2?1000:30;
 for(int i=0;i<3;++i){tips[i]=(CEquipmentTooltip*)tm[i];tips[i]->m_pParent=windows[1];tips[i]->m_pRoot=windows[i==0?0:i+1];tips[i]->m_iCachedItemGuid=77;}
 windows[0]->d_parent=c.attached?windows[1]:0;at<long long>(eq,0x10)=77;at<long>(ui,0x12d0)=c.position%2?25:1800;at<long>(ui,0x12d8)=c.position>=2?1200:5;
 for(unsigned i=0;i<sizeof(caches)/sizeof(*caches);++i){new((void*)caches[i])std::wstring(L"cached");*(unsigned char*)guards[i]=1;}
 detour::Set d;TL_REDIRECT(d,widthFn,&width);TL_REDIRECT(d,heightFn,&height);TL_REDIRECT(d,keyFn,&key);
#define I(N,F) d.redirect(N,N,&F)
 I(getWidthFn,getWidth);I(getHeightFn,getHeight);I(getPositionFn,getPosition);I(setPositionFn,setPosition);I(addFn,add);I(removeFn,remove);I(frontFn,front);
#undef I
 if(d.failed())_exit(43);
 if(ours)autotest::invoke(out,&newTooltip,ui,owner,eq,tips[0],c.peers?tips[1]:(CEquipmentTooltip*)0,c.peers==2?tips[2]:(CEquipmentTooltip*)0);else autotest::invoke(out,&oldTooltip,ui,owner,eq,tips[0],c.peers?tips[1]:(CEquipmentTooltip*)0,c.peers==2?tips[2]:(CEquipmentTooltip*)0);
 n(99);n(id(windows[0]->d_parent));cap->add(positions,sizeof(positions));n(calls);
}
void a(void* p,autotest::Capture& c){side(*(Case*)p,false,c);}void b(void* p,autotest::Capture& c){side(*(Case*)p,true,c);}
}
TL_TEST(equipment_tooltip_cached_differential){autotest::Coverage cv("equipment_tooltip_cached_differential",(uint64_t)(uintptr_t)&oldTooltip);unsigned count=0;for(unsigned profile=0;profile<16;++profile)for(unsigned peers=0;peers<3;++peers)for(unsigned position=0;position<4;++position)for(unsigned key=0;key<4;++key)for(unsigned attached=0;attached<2;++attached)for(unsigned mutate=0;mutate<2;++mutate){Case c={profile,peers,position,key,attached,mutate};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);++count;if(cv.observe(host,x,y)){size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    profile %u peers %u position %u key %u attached %u mutate %u status %d/%d bytes %lu/%lu first %lu\n",profile,peers,position,key,attached,mutate,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t i=first>32?first-32:0;i<first+64&&i+4<=x.capture.length&&i+4<=y.capture.length;i+=4){int u,v;memcpy(&u,x.capture.data+i,4);memcpy(&v,y.capture.data+i,4);host->log("      %lu %d/%d\n",(unsigned long)i,u,v);}return 1;}}cv.report(host);host->log("    cached tooltip placement: %u completed entry comparisons\n",count);return 0;}
