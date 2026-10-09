#include <cstring>
#include <string>
#include <new>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include <OgreUTFString.h>
#include "JournalMenu.h"
#include "Player.h"
#include "GameUI.h"
#include "ResourceManager.h"
#include "GameClient.h"
#include "StringTranslate.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldLayout,(CJournalMenu*),"_ZN12CJournalMenu12updateLayoutEv")
extern "C" void newLayout(CJournalMenu*) __asm__("_ZN12CJournalMenu12updateLayoutEv");
extern "C" void* playerTable[] __asm__("_ZTV7CPlayer");
extern "C" void* characterTable[] __asm__("_ZTV10CCharacter");
TL_FUNCTION(scaledFn,"_ZN7CGameUI7scaledYEf")
TL_FUNCTION(uniqueFn,"_ZN7STRINGS10uniqueNameERKSs")
TL_FUNCTION(convertFn,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(valueFn,"_ZN7STRINGS17GetValueAsWStringEi")
TL_FUNCTION(intFn,"_ZN7STRINGS16GetValueAsStringEi")
TL_FUNCTION(unsignedFn,"_ZN7STRINGS16GetValueAsStringEj")
TL_FUNCTION(translateSingletonFn,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateFn,"_ZN16CStringTranslate18getTranslateStringEPKw")
#define IMPORT(N,S) extern "C" char N[] __asm__(S)
IMPORT(createFn,"_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_");
IMPORT(destroyFn,"_ZN5CEGUI13WindowManager13destroyWindowEPNS_6WindowE");
IMPORT(addFn,"_ZN5CEGUI6Window14addChildWindowEPS0_");
IMPORT(removeFn,"_ZN5CEGUI6Window17removeChildWindowEPS0_");
IMPORT(sizeFn,"_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
IMPORT(positionFn,"_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
IMPORT(propertyFn,"_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
IMPORT(frontFn,"_ZN5CEGUI6Window11moveToFrontEv");
IMPORT(backFn,"_ZN5CEGUI6Window10moveToBackEv");
IMPORT(topFn,"_ZN5CEGUI6Window14setAlwaysOnTopEb");
IMPORT(textFn,"_ZN5CEGUI6Window7setTextERKNS_6StringE");
#undef IMPORT
namespace {
struct Case{unsigned type,hardcore,difficulty,cache,scale,initial,time,mutate;};
autotest::Capture* cap;const Case* input;CJournalMenu* menu;CGameUI* ui[2];CEGUI::WindowManager* manager;CStringTranslate* translator;
CEGUI::Window* windows[128];unsigned long long windowMemory[128][(sizeof(CEGUI::Window)+7)/8];unsigned count,uniqueCount,scaleCount;bool destroyed[128];
const uintptr_t cacheAddresses[]={0x15278e0,0x15278d8,0x15278d0,0x15278c8,0x15278c0,0x15278b8,0x15278b0,0x15278a8,0x1527818,0x1527810,0x1527808,0x1527828,0x1527830,0x1527838,0x1527840,0x1527848,0x1527850,0x1527858,0x1527860,0x1527868,0x1527870,0x1527878,0x1527880,0x1527888,0x1527890,0x1527898,0x15278a0,0x1527820};
const uintptr_t guards[]={0x1527728,0x1527730,0x1527738,0x1527740,0x1527748,0x1527750,0x1527758,0x1527760,0x15277f0,0x15277f8,0x1527800,0x15277e0,0x15277d8,0x15277d0,0x15277c8,0x15277c0,0x15277b8,0x15277b0,0x15277a8,0x15277a0,0x1527798,0x1527790,0x1527788,0x1527780,0x1527778,0x1527770,0x1527768,0x15277e8};

template<class T>T& at(void* p,size_t offset){return *(T*)((char*)p+offset);}
void n(int x){cap->add(&x,4);}void f(float x){cap->add(&x,4);}void str(const CEGUI::String& s){n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
int id(const CEGUI::Window* p){for(unsigned i=0;i<count;++i)if(p==windows[i])return i;return p?-2:-1;}
CEGUI::Window* window(){if(count==128)_exit(40);CEGUI::Window* p=(CEGUI::Window*)windowMemory[count];windows[count++]=p;new(&p->d_text)CEGUI::String();return p;}
CEGUI::Window* create(CEGUI::WindowManager* p,const CEGUI::String& type,const CEGUI::String& name,const CEGUI::String& prefix){n(1);n(p==manager);str(type);str(name);str(prefix);CEGUI::Window* q=window();n(id(q));return q;}
void destroy(CEGUI::WindowManager* p,CEGUI::Window* q){n(2);n(p==manager);n(id(q));destroyed[id(q)]=true;}
void add(CEGUI::Window* p,CEGUI::Window* q){n(3);n(id(p));n(id(q));q->d_parent=p;}
void remove(CEGUI::Window* p,CEGUI::Window* q){n(4);n(id(p));n(id(q));q->d_parent=0;}
void size(CEGUI::Window* p,const CEGUI::UVector2& v){n(5);n(id(p));cap->add(&v,sizeof(v));}
void position(CEGUI::Window* p,const CEGUI::UVector2& v){n(6);n(id(p));cap->add(&v,sizeof(v));}
void property(CEGUI::PropertySet* p,const CEGUI::String& k,const CEGUI::String& v){n(7);n(id(static_cast<CEGUI::Window*>(p)));str(k);str(v);}
void front(CEGUI::Window* p){n(8);n(id(p));}void back(CEGUI::Window* p){n(9);n(id(p));}
void top(CEGUI::Window* p,bool b){n(10);n(id(p));n(b);p->d_alwaysOnTop=b;}
void text(CEGUI::Window* p,const CEGUI::String& s){n(11);n(id(p));str(s);p->d_text=s;}
float scaled(CGameUI* p,float x){n(12);n(p==ui[0]?0:p==ui[1]?1:-1);f(x);++scaleCount;const float scales[]={1.0f,-.5f,-0.0f,std::numeric_limits<float>::quiet_NaN()};float value=x*scales[input->scale];if(input->mutate){value+=float(scaleCount)*.03125f;menu->m_pGameUI=p==ui[0]?ui[1]:ui[0];}return value;}
std::string unique(const std::string& s){n(13);cap->addText(s);char b[32];std::sprintf(b,"%u",uniqueCount++);return s+b;}
std::string convert(const std::wstring& s){n(14);cap->addText(s);return Ogre::UTFString(s).asUTF8();}
std::wstring value(int x){n(15);n(x);char b[32];std::sprintf(b,"%d",x);return std::wstring(b,b+std::strlen(b));}
std::string ivalue(int x){n(16);n(x);char b[32];std::sprintf(b,"%d",x);return b;}
std::string uvalue(unsigned x){n(17);n(x);char b[32];std::sprintf(b,"%u",x);return b;}
CStringTranslate* singleton(){n(18);return translator;}
std::wstring translate(CStringTranslate* p,const wchar_t* s){n(19);n(p==translator);cap->addText(std::wstring(s));return input->cache==1?L"":input->cache==2?std::wstring(s)+L" \u03a9\u4e2d":std::wstring(s);}
void side(const Case& c,bool ours,autotest::Capture& out){cap=&out;input=&c;count=uniqueCount=scaleCount=0;memset(windowMemory,0,sizeof(windowMemory));memset(destroyed,0,sizeof(destroyed));
 unsigned long long mm[32]={0},pm[400]={0},um[2][16]={0},rm[40]={0},cm[1900]={0},wm[32]={0},tm[16]={0};menu=(CJournalMenu*)mm;CCharacter* actor=(CCharacter*)pm;ui[0]=(CGameUI*)um[0];ui[1]=(CGameUI*)um[1];CResourceManager* resources=(CResourceManager*)rm;CGameClient* client=(CGameClient*)cm;manager=(CEGUI::WindowManager*)wm;translator=(CStringTranslate*)tm;
 *(void***)actor=c.type==1?characterTable+2:playerTable+2;menu->m_pOwner=c.type?actor:0;menu->m_pGameUI=ui[0];menu->m_pResourceManager=resources;menu->m_pRoot=window();menu->m_pContent=window();CEGUI::Window* other=window();new(&menu->m_Children)TArrayList<CEGUI::Window*>(3);for(unsigned i=0;i<c.initial*3;++i){CEGUI::Window* p=window();p->d_parent=i==0?menu->m_pContent:i==1?other:0;menu->m_Children.add(p);}
 new(&resources->m_GameClients)TArrayList<CGameClient*>(1);resources->m_GameClients.add(client);at<int>(client,0x38ec)=int(c.difficulty)-1;at<bool>(actor,0xa15)=c.hardcore;at<int>(actor,0xa10)=c.time==4?-7:c.time==5?2147483647:3;
 const float times[]={0.0f,.01f,59.1f,60,3599.2f,3600,3661.5f,-.1f,-61,86400,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};at<float>(actor,0x388)=times[c.time];for(unsigned i=0;i<18;++i)at<int>(actor,0x7dc+i*4)=c.time==4?-int(i+1):c.time==5?2147483647:int(i*137+13);
 for(unsigned i=0;i<sizeof(cacheAddresses)/sizeof(*cacheAddresses);++i){new((void*)cacheAddresses[i])std::wstring(c.cache==3?L"cached":L"");*(unsigned char*)guards[i]=c.cache==3;}
 CEGUI::WindowManager::ms_Singleton=manager;detour::Set d;
#define R(N,F) TL_REDIRECT(d,N,&F)
 R(scaledFn,scaled);R(uniqueFn,unique);R(convertFn,convert);R(valueFn,value);R(intFn,ivalue);R(unsignedFn,uvalue);R(translateSingletonFn,singleton);R(translateFn,translate);
#undef R
#define I(N,F) d.redirect(N,N,&F)
 I(createFn,create);I(destroyFn,destroy);I(addFn,add);I(removeFn,remove);I(sizeFn,size);I(positionFn,position);I(propertyFn,property);I(frontFn,front);I(backFn,back);I(topFn,top);I(textFn,text);
#undef I
 if(d.failed())_exit(43);
 for(unsigned frame=0;frame<2;++frame){n(90);n(frame);if(frame){if(ours)newLayout(menu);else oldLayout(menu);}else{if(ours)autotest::invoke(out,&newLayout,menu);else autotest::invoke(out,&oldLayout,menu);}n(91);n(menu->m_Children.size());n(menu->m_Children.m_nCapacity);for(unsigned i=0;i<menu->m_Children.size();++i)n(id(menu->m_Children[i]));for(unsigned i=0;i<count;++i){n(id(windows[i]->d_parent));n(destroyed[i]);n(windows[i]->d_alwaysOnTop);n(windows[i]->d_mousePassThroughEnabled);str(windows[i]->d_text);}}
 for(unsigned i=0;i<sizeof(cacheAddresses)/sizeof(*cacheAddresses);++i){cap->addText(*(std::wstring*)cacheAddresses[i]);n(*(unsigned char*)guards[i]);}
}
void a(void* p,autotest::Capture& o){side(*(Case*)p,false,o);}void b(void* p,autotest::Capture& o){side(*(Case*)p,true,o);}
}
TL_TEST(journal_layout_differential){autotest::Coverage cv("journal_layout_differential",(uint64_t)(uintptr_t)&oldLayout);unsigned k=0;for(unsigned type=0;type<3;++type)for(unsigned hardcore=0;hardcore<2;++hardcore)for(unsigned difficulty=0;difficulty<6;++difficulty)for(unsigned cache=0;cache<4;++cache)for(unsigned scale=0;scale<4;++scale)for(unsigned initial=0;initial<2;++initial){Case c={type,hardcore,difficulty,cache,scale,initial,(k/2)%12,(k/3)%2};++k;autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(cv.observe(host,x,y)){size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    case %u type %u hardcore %u difficulty %u cache %u scale %u initial %u time %u mutate %u status %d/%d bytes %lu/%lu first %lu\n",k,type,hardcore,difficulty,cache,scale,initial,c.time,c.mutate,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t i=first>40?first-40:0;i<first+100&&i+4<=x.capture.length&&i+4<=y.capture.length;i+=4){int u,v;memcpy(&u,x.capture.data+i,4);memcpy(&v,y.capture.data+i,4);host->log("      %lu %d/%d\n",(unsigned long)i,u,v);}return 1;}}cv.report(host);return 0;}
