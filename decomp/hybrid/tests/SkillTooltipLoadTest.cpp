// Full-body differential loader fixture. Expected exceptions are separate evidence.
#include <cstring>
#include <limits>
#include <string>
#define protected public
#define private public
#include <CEGUI.h>
#include "SkillTooltip.h"
#include "GameUI.h"
#include "FileSystem.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalLoad, (CSkillTooltip*,CGameUI*,std::wstring), "_ZN13CSkillTooltip4loadEP7CGameUISbIwSt11char_traitsIwESaIwEE")
extern "C" void candidateLoad(CSkillTooltip*,CGameUI*,std::wstring) __asm__("_ZN13CSkillTooltip4loadEP7CGameUISbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(fileSingleton,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(fileInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(uniqueFn,"_ZN7STRINGS10uniqueNameERKSs")
TL_FUNCTION(scaleFn,"_ZN7CGameUI20convertToScreenScaleEPN5CEGUI6WindowEb")
extern "C" char layoutFn[] __asm__("_ZN5CEGUI13WindowManager16loadWindowLayoutERKNS_6StringES3_S3_PFbPNS_6WindowERS1_S6_PvES7_");
extern "C" char topFn[] __asm__("_ZN5CEGUI6Window14setAlwaysOnTopEb");
extern "C" char muteFn[] __asm__("_ZN5CEGUI8EventSet13setMutedStateEb");
extern "C" char searchFn[] __asm__("_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE");
extern "C" char yFn[] __asm__("_ZNK5CEGUI6Window12getYPositionEv");
namespace {
struct Stop {};
struct Case {unsigned profile,pattern;bool change,alias;unsigned fault;};
const Case* cs;autotest::Capture* cap;CSkillTooltip* tip;CGameUI* ui;CFileSystem* fs;CEGUI::WindowManager* wm;
unsigned long long pool[36][(sizeof(CEGUI::Window)+7)/8];CEGUI::UDim ys[36];unsigned searches,reads,events;
std::string* resource;std::wstring* resolvedPath;
CEGUI::Window* win(unsigned i){return reinterpret_cast<CEGUI::Window*>(pool[i]);}
int wid(const CEGUI::Window* w){for(unsigned i=0;i<36;++i)if(w==win(i))return i;return w?999:-1;}
void number(int n){cap->add(&n,4);}
void bytes(const std::string& s){number(s.size());cap->add(s.data(),s.size());}
void wide(const std::wstring& s){number(s.size());cap->add(s.data(),s.size()*sizeof(wchar_t));}
void text(const CEGUI::String& s){number(s.length());for(unsigned i=0;i<s.length();++i){unsigned u=s[i];cap->add(&u,4);}}
void event(int n){number(n);++events;if(cs->fault==events)throw Stop();}
CFileSystem* singleton(){event(1);return fs;}
void info(CFileSystem* f,const std::wstring& name,CFileInfo& i,bool a,bool b,bool c){
 event(2);number(f==fs);wide(name);bytes(i.m_sModName);bytes(i.m_sResourceName);wide(i.m_sPath);number(i.m_eFormat);number(i.m_eLocation);bytes(i.m_sResourceGroup);number(i.m_bExists);number(a);number(b);number(c);
 i.m_sResourceName=*resource;i.m_sPath=*resolvedPath;i.m_sModName="mod";i.m_sResourceGroup="group";i.m_bExists=true;
}
std::string unique(const std::string& s){event(3);bytes(s);return *resource+std::string("_unique\0tail",12);}
CEGUI::Window* layout(CEGUI::WindowManager* manager,const CEGUI::String& a,const CEGUI::String& b,const CEGUI::String& c,bool(*fn)(CEGUI::Window*,CEGUI::String&,CEGUI::String&,void*),void* data){
 event(4);number(manager==wm);text(a);text(b);text(c);number(fn==0);number(data==0);return win(0);
}
void top(CEGUI::Window* w,bool on){event(5);number(wid(w));number(on);w->d_alwaysOnTop=on;if(cs->change)tip->m_pWindow=win(1);}
void mute(CEGUI::EventSet* e,bool on){event(6);CEGUI::Window* w=static_cast<CEGUI::Window*>(e);number(wid(w));number(on);e->d_muted=on;if(cs->change)tip->m_pWindow=win(2);}
void scale(CGameUI* u,CEGUI::Window* w,bool recursive){event(7);number(u==ui);number(wid(w));number(recursive);number(w->d_mousePassThroughEnabled);if(cs->change)tip->m_pWindow=win(0);}
CEGUI::Window* search(const CEGUI::Window* w,const CEGUI::String& name){event(8);number(wid(w));text(name);unsigned i=3+(searches++%(cs->alias?7:32));if(cs->change)tip->m_pWindow=win(searches%3);return win(i);}
const CEGUI::UDim& y(const CEGUI::Window* w){event(9);int i=wid(w);number(i);if(i<0||i>=36)_exit(61);++reads;
 if(cs->change){for(unsigned j=0;j<36;++j)ys[j].d_offset+=float((reads+j)%3)-1.0f;if(reads%2==0){tip->m_pStatIcons[0]=win(3+(reads%4));tip->m_pNextStatIcons[0]=win(20+(reads%4));}}
 cap->add(&ys[i],sizeof(CEGUI::UDim));return ys[i];
}
void canonical(unsigned char* s,unsigned off,int n){uintptr_t x=n;std::memcpy(s+off,&x,sizeof(x));}
void side(const Case& c,bool ours,autotest::Capture& out){
 cs=&c;cap=&out;searches=reads=events=0;
 unsigned long long tm[(sizeof(CSkillTooltip)+7)/8],um[(sizeof(CGameUI)+7)/8]={0},fm[64]={0},mm[64]={0};
 std::memset(tm,0x5a,sizeof(tm));tip=(CSkillTooltip*)tm;ui=(CGameUI*)um;fs=(CFileSystem*)fm;wm=(CEGUI::WindowManager*)mm;
 std::memset(pool,0,sizeof(pool));CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton=wm;
 const float values[]={0.0f,-0.0f,0.49f,0.5f,-0.49f,-0.5f,2.75f,-2.75f,1000.25f,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};
 for(unsigned i=0;i<36;++i){ys[i]=CEGUI::UDim(values[(c.profile+i)%12],float(int(i)*13-150));win(i)->d_muted=c.alias;win(i)->d_alwaysOnTop=c.alias;win(i)->d_mousePassThroughEnabled=c.alias;}
 std::string r=c.pattern==0?std::string("layout"):c.pattern==1?std::string(80,'x'):c.pattern==2?std::string("abc\0tail",8):std::string("layout_\xc3\xa9");
 std::wstring p=L"resolved/path";std::wstring arg=c.pattern==2?std::wstring(L"input\0tail",10):std::wstring(L"media/Ω中.layout");resource=&r;resolvedPath=&p;
 detour::Set redirects;TL_REDIRECT(redirects,fileSingleton,&singleton);TL_REDIRECT(redirects,fileInfo,&info);TL_REDIRECT(redirects,uniqueFn,&unique);TL_REDIRECT(redirects,scaleFn,&scale);
 redirects.redirect(layoutFn,layoutFn,&layout);redirects.redirect(topFn,topFn,&top);redirects.redirect(muteFn,muteFn,&mute);redirects.redirect(searchFn,searchFn,&search);redirects.redirect(yFn,yFn,&y);
 if(redirects.failed())_exit(62);
 bool threw=false;try{if(ours)autotest::invoke(out,&candidateLoad,tip,ui,arg);else autotest::invoke(out,&originalLoad,tip,ui,arg);}catch(const Stop&){threw=true;}catch(...){_exit(63);}
 number(threw);number(events);number(searches);number(reads);
 int rr=99,pr=99;std::memcpy(&rr,reinterpret_cast<const char*>(r.data())-8,4);std::memcpy(&pr,reinterpret_cast<const char*>(p.data())-8,4);number(rr);number(pr);if(rr||pr)_exit(64);
 unsigned char snapshot[sizeof(CSkillTooltip)];std::memcpy(snapshot,tip,sizeof(snapshot));
 for(unsigned off=0x30;off<0xf8;off+=8){CEGUI::Window* w;std::memcpy(&w,snapshot+off,8);if(wid(w)!=999)canonical(snapshot,off,wid(w));}
 for(unsigned off=0x118;off<0x158;off+=8){CEGUI::Window* w;std::memcpy(&w,snapshot+off,8);if(wid(w)!=999)canonical(snapshot,off,wid(w));}
 cap->add(snapshot,sizeof(snapshot));for(unsigned i=0;i<36;++i){number(win(i)->d_alwaysOnTop);number(win(i)->d_muted);number(win(i)->d_mousePassThroughEnabled);cap->add(&ys[i],sizeof(CEGUI::UDim));}
}
void a(void* c,autotest::Capture& o){side(*(Case*)c,false,o);}void b(void* c,autotest::Capture& o){side(*(Case*)c,true,o);}
bool equal(const autotest::Outcome& u,const autotest::Outcome& v){return u.reportValid&&v.reportValid&&u.childStatus==0&&v.childStatus==0&&u.capture.issue==0&&v.capture.issue==0&&u.capture.length>100&&u.capture.length==v.capture.length&&!std::memcmp(u.capture.data,v.capture.data,u.capture.length);}
}
TL_TEST(skill_tooltip_load_differential){
 autotest::Coverage coverage("skill_tooltip_load_differential",(uint64_t)(uintptr_t)&originalLoad);unsigned total=0;
 for(unsigned profile=0;profile<12;++profile)for(unsigned pattern=0;pattern<4;++pattern)for(unsigned change=0;change<2;++change)for(unsigned alias=0;alias<2;++alias){Case c={profile,pattern,bool(change),bool(alias),0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);++total;
 if(pair||!equal(u,v)||!u.capture.callCompleted||!v.capture.callCompleted){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    MISMATCH %u/%u/%u/%u first %lu exits %d/%d lengths %lu/%lu\n",profile,pattern,change,alias,(unsigned long)f,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);host->log("    FULL BODY: %u completed; ordered strings/receivers, full tooltip bytes, window flags, offsets and COW lifetimes\n",total);return 0;
}
TL_TEST(skill_tooltip_load_expected_exceptions){
 unsigned total=0;for(unsigned fault=1;fault<=67;++fault)for(unsigned change=0;change<2;++change){Case c={6,2,bool(change),false,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);++total;
 if(!equal(u,v)||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.callTarget!=(uint64_t)(uintptr_t)&originalLoad||!host->comparison_pair||!host->comparison_pair(u.capture.callTarget,v.capture.callTarget)){host->log("    UNWIND MISMATCH fault %u change %u exits %d/%d lengths %lu/%lu\n",fault,change,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length);return 1;}}
 host->log("    EXPECTED EXCEPTIONS: %u matching collaborator fault sites and restored COW lifetimes, excluded from normal coverage\n",total);return 0;
}
