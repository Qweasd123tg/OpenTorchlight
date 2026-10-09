#include <cstring>
#include <string>
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
TL_ORIGINAL(void,oldHover,(CStatsMenuFill*),"_ZN14CStatsMenuFill18calculateMouseOverEv")
extern "C" void newHover(CStatsMenuFill*) __asm__("_ZN14CStatsMenuFill18calculateMouseOverEv");
TL_FUNCTION(intFn,"_ZN7STRINGS17GetValueAsWStringEi")
TL_FUNCTION(convertFn,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
extern "C" char tooltipFn[] __asm__("_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE");
namespace {
struct Case {unsigned profile,capacity,mutation,strings;};
autotest::Capture* cap;const Case* input;CStatsMenuFill* menu;CPlayer* players[2];CEGUI::Window* windows[8];CEGUI::Window** lists[2];unsigned intCalls,textCalls;
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
void n(int x){cap->add(&x,4);}int wid(const CEGUI::Window* p){for(int i=0;i<8;++i)if(p==windows[i])return i;return -1;}
std::wstring integer(int value){n(1);n(value);++intCalls;if(input->mutation==1)menu->m_pPlayer=players[intCalls&1];if(input->mutation==2)menu->m_pPlayer=(intCalls&1)?0:players[1];if(input->mutation==3){menu->m_StatSlots.m_pData=lists[intCalls&1];menu->m_StatSlots.m_nCapacity=(input->capacity+intCalls)%5;}wchar_t text[48];std::swprintf(text,48,L"%d",value);std::wstring s(text);if(input->strings==1)s+=L" extra \u03a9";if(input->strings==2)s+=std::wstring(L"\0tail",5);return s;}
std::string convert(const std::wstring& s){n(2);cap->addText(s);std::string r;for(size_t i=0;i<s.size();++i){unsigned c=s[i];if(c<128)r+=char(c);else{r+=char(0xc0|(c>>6));r+=char(0x80|(c&63));}}return r;}
void tooltip(CEGUI::Window* p,const CEGUI::String& s){n(3);n(wid(p));n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);++textCalls;if(input->mutation==3)menu->m_pPlayer=players[textCalls&1];}
void side(const Case& c,bool ours,autotest::Capture& out){
 cap=&out;input=&c;intCalls=textCalls=0;
 unsigned long long mm[(sizeof(CStatsMenuFill)+7)/8]={0},pm[2][0xa80/8]={0},wm[8][(sizeof(CEGUI::Window)+7)/8]={0};menu=(CStatsMenuFill*)mm;
 const int values[]={0,1,-1,37,2147483646,(-2147483647-1),100,200};
 for(int p=0;p<2;++p){players[p]=(CPlayer*)pm[p];const unsigned offsets[]={0x42c,0x428,0x434,0x430};for(unsigned i=0;i<4;++i)at<int>(players[p],offsets[i])=values[(c.profile+i+p)%8];}
 for(unsigned i=0;i<8;++i)windows[i]=(CEGUI::Window*)wm[i];CEGUI::Window* first[4];CEGUI::Window* second[4];for(unsigned i=0;i<4;++i){first[i]=windows[i];second[i]=windows[7-i];}lists[0]=first;lists[1]=second;
 menu->m_pPlayer=c.profile==8?0:players[0];menu->m_StatSlots.m_pData=first;menu->m_StatSlots.m_nCount=c.profile%5;menu->m_StatSlots.m_nCapacity=c.capacity;
 detour::Set d;TL_REDIRECT(d,intFn,&integer);TL_REDIRECT(d,convertFn,&convert);d.redirect(tooltipFn,tooltipFn,&tooltip);if(d.failed())_exit(42);
 if(ours)autotest::invoke(out,&newHover,menu);else autotest::invoke(out,&oldHover,menu);
 n(99);cap->add(mm,sizeof(mm));cap->add(pm,sizeof(pm));cap->add(wm,sizeof(wm));cap->add(first,sizeof(first));cap->add(second,sizeof(second));n(intCalls);n(textCalls);
}
void a(void* p,autotest::Capture& o){side(*(Case*)p,false,o);}void b(void* p,autotest::Capture& o){side(*(Case*)p,true,o);}
}
TL_TEST(stats_fill_hover_differential){autotest::Coverage coverage("stats_fill_hover_differential",(uint64_t)(uintptr_t)&oldHover);unsigned count=0;for(unsigned profile=0;profile<9;++profile)for(unsigned capacity=0;capacity<=4;++capacity)for(unsigned mutation=0;mutation<4;++mutation)for(unsigned strings=0;strings<3;++strings){Case c={profile,capacity,mutation,strings};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);++count;int pair=coverage.observe(host,x,y);if(pair||autotest::incomplete(x)||autotest::incomplete(y)||!x.reportValid||!y.reportValid||x.childStatus||y.childStatus){host->log("    stats hover case %u/%u/%u/%u exits %d/%d bytes %lu/%lu\n",profile,capacity,mutation,strings,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length);coverage.report(host);return 1;}}coverage.report(host);host->log("    stats hover: %u complete cases\n",count);return 0;}
