#include <cstring>
#include <string>
#include <limits>
#include <cwchar>
#define private public
#define protected public
#include <CEGUI.h>
#include "StatsMenuFill.h"
#include "Player.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldVisuals,(CStatsMenuFill*),"_ZN14CStatsMenuFill13updateVisualsEv")
extern "C" void newVisuals(CStatsMenuFill*) __asm__("_ZN14CStatsMenuFill13updateVisualsEv");
TL_FUNCTION(totalFn,"_ZN14CStatsMenuFill21getStatBarTotalAmountE16ESTATSMENU_STATS")
TL_FUNCTION(mouseFn,"_ZN14CStatsMenuFill18calculateMouseOverEv")
TL_FUNCTION(intFn,"_ZN7STRINGS17GetValueAsWStringEi")
TL_FUNCTION(floatFn,"_ZN7STRINGS17GetValueAsWStringEf")
TL_FUNCTION(convertFn,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(scaleFn,"_ZN7CGameUI7scaledYEf")
extern "C" char textFn[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
extern "C" char visibleFn[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" char sizeFn[] __asm__("_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
namespace {
struct Case {unsigned profile,capacity,mutation,strings;};
autotest::Capture* cap;const Case* input;CStatsMenuFill* menu;CPlayer* players[2];CGameUI* uis[2];CEGUI::Window* windows[16];unsigned totalCalls,scaleCalls,mouseCalls;bool shown[16];CEGUI::UVector2 sizes[16];
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
void n(int x){cap->add(&x,4);}void f(float x){cap->add(&x,4);}int wid(const CEGUI::Window* p){for(int i=0;i<16;++i)if(p==windows[i])return i;return -1;}
float total(CStatsMenuFill* p,ESTATSMENU_STATS s){n(1);n(p==menu);n(s);++totalCalls;const float values[]={100.0f,0.0f,-0.0f,-100.0f,1.0f,1000000.0f,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN(),0.25f,3.0f,2147483648.0f};if(input->mutation)menu->m_pPlayer=input->mutation==2?0:players[totalCalls&1];return values[(input->profile+unsigned(s))%12];}
void mouse(CStatsMenuFill* p){n(2);n(p==menu);++mouseCalls;}
std::wstring integer(int value){n(3);n(value);wchar_t text[48];std::swprintf(text,48,L"I%d",value);std::wstring s(text);if(input->strings)s+=std::wstring(L"\0tail\u03a9",6);return s;}
std::wstring floating(float value){n(4);f(value);unsigned bits;std::memcpy(&bits,&value,4);wchar_t text[48];std::swprintf(text,48,L"F%08x",bits);std::wstring s(text);if(input->strings)s+=L" long float \u03a9";return s;}
std::string convert(const std::wstring& s){n(5);cap->addText(s);std::string r;for(size_t i=0;i<s.size();++i){unsigned c=s[i];if(c<128)r+=char(c);else{r+=char(0xc0|(c>>6));r+=char(0x80|(c&63));}}return r;}
float scaled(CGameUI* p,float value){n(6);n(p==uis[0]?0:p==uis[1]?1:-1);f(value);++scaleCalls;if(input->mutation)menu->m_pGameUI=uis[scaleCalls&1];return value*(input->profile&1?-0.75f:1.25f);}
void text(CEGUI::Window* p,const CEGUI::String& s){n(7);n(wid(p));n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
void visible(CEGUI::Window* p,bool b){n(8);n(wid(p));n(b);shown[wid(p)]=b;}
void size(CEGUI::Window* p,const CEGUI::UVector2& v){n(9);n(wid(p));cap->add(&v,sizeof(v));sizes[wid(p)]=v;}
void side(const Case& c,bool ours,autotest::Capture& out){
 cap=&out;input=&c;totalCalls=scaleCalls=mouseCalls=0;std::memset(shown,1,sizeof(shown));std::memset(sizes,0,sizeof(sizes));
 unsigned long long mm[(sizeof(CStatsMenuFill)+7)/8]={0},pm[2][0xa80/8]={0},um[2][0x1a10/8]={0},wm[16][(sizeof(CEGUI::Window)+7)/8]={0};menu=(CStatsMenuFill*)mm;
 const int values[]={0,1,-1,37,2147483647,(-2147483647-1),100,200};
 for(int p=0;p<2;++p){players[p]=(CPlayer*)pm[p];uis[p]=(CGameUI*)um[p];const unsigned offsets[]={0x42c,0x428,0x434,0x430,0x870,0x874,0x87c,0x878,0x448,0x880};for(unsigned i=0;i<10;++i)at<int>(players[p],offsets[i])=values[(c.profile+i+p)%8];}
 for(unsigned i=0;i<16;++i)windows[i]=(CEGUI::Window*)wm[i];CEGUI::Window* bars[4];CEGUI::Window* amounts[4];CEGUI::Window* stats[4];for(unsigned i=0;i<4;++i){bars[i]=windows[i];amounts[i]=windows[i+4];stats[i]=windows[i+8];}
 menu->m_pPlayer=c.profile==12?0:players[0];menu->m_pGameUI=uis[0];menu->m_pExperienceText=windows[12];
 menu->m_Bars.m_pData=bars;menu->m_Bars.m_nCount=4;menu->m_Bars.m_nCapacity=c.capacity;
 menu->m_AmountTexts.m_pData=amounts;menu->m_AmountTexts.m_nCount=4;menu->m_AmountTexts.m_nCapacity=c.capacity;
 menu->m_PercentTexts.m_pData=stats;menu->m_PercentTexts.m_nCount=4;menu->m_PercentTexts.m_nCapacity=c.capacity;
 detour::Set d;TL_REDIRECT(d,totalFn,&total);TL_REDIRECT(d,mouseFn,&mouse);TL_REDIRECT(d,intFn,&integer);TL_REDIRECT(d,floatFn,&floating);TL_REDIRECT(d,convertFn,&convert);TL_REDIRECT(d,scaleFn,&scaled);d.redirect(textFn,textFn,&text);d.redirect(visibleFn,visibleFn,&visible);d.redirect(sizeFn,sizeFn,&size);if(d.failed())_exit(42);
 if(ours)autotest::invoke(out,&newVisuals,menu);else autotest::invoke(out,&oldVisuals,menu);
 n(99);cap->add(mm,sizeof(mm));cap->add(pm,sizeof(pm));cap->add(um,sizeof(um));cap->add(wm,sizeof(wm));cap->add(bars,sizeof(bars));cap->add(amounts,sizeof(amounts));cap->add(stats,sizeof(stats));cap->add(shown,sizeof(shown));cap->add(sizes,sizeof(sizes));n(totalCalls);n(scaleCalls);n(mouseCalls);
}
void a(void* p,autotest::Capture& o){side(*(Case*)p,false,o);}void b(void* p,autotest::Capture& o){side(*(Case*)p,true,o);}
}
TL_TEST(stats_fill_update_differential){autotest::Coverage coverage("stats_fill_update_differential",(uint64_t)(uintptr_t)&oldVisuals);unsigned count=0;for(unsigned profile=0;profile<13;++profile)for(unsigned capacity=0;capacity<=4;++capacity)for(unsigned mutation=0;mutation<3;++mutation)for(unsigned strings=0;strings<2;++strings){Case c={profile,capacity,mutation,strings};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);++count;int pair=coverage.observe(host,x,y);if(pair||autotest::incomplete(x)||autotest::incomplete(y)||!x.reportValid||!y.reportValid||x.childStatus||y.childStatus||x.capture.length!=y.capture.length||std::memcmp(x.capture.data,y.capture.data,x.capture.length)){size_t i=0;while(i<x.capture.length&&i<y.capture.length&&x.capture.data[i]==y.capture.data[i])++i;host->log("    stats fill update case %u/%u/%u/%u exits %d/%d bytes %lu/%lu first %lu\n",profile,capacity,mutation,strings,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)i);coverage.report(host);return 1;}}coverage.report(host);host->log("    stats fill update: %u complete cases\n",count);return 0;}
