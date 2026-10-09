#include <cstring>
#include <cstdio>
#include <string>
#define protected public
#define private public
#include <CEGUI.h>
#include <CEGUIMemberFunctionSlot.h>
#include "SkillFoldout.h"
#include "GameUI.h"
#include "FileSystem.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalLoad, (CSkillFoldout*,CGameUI*,std::wstring), "_ZN13CSkillFoldout4loadEP7CGameUISbIwSt11char_traitsIwESaIwEE")
extern "C" void candidateLoad(CSkillFoldout*,CGameUI*,std::wstring) __asm__("_ZN13CSkillFoldout4loadEP7CGameUISbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(fileSingleton,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(fileInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(uniqueFn,"_ZN7STRINGS10uniqueNameERKSs")
TL_FUNCTION(valueFn,"_ZN7STRINGS16GetValueAsStringEi")
TL_FUNCTION(scaleFn,"_ZN7CGameUI20convertToScreenScaleEPN5CEGUI6WindowEb")
TL_FUNCTION(overFn,"_ZN7CGameUI27handle_SkillSelectMouseOverERKN5CEGUI9EventArgsE")
TL_FUNCTION(outFn,"_ZN7CGameUI26handle_SkillSelectMouseOutERKN5CEGUI9EventArgsE")
TL_FUNCTION(clickFn,"_ZN7CGameUI23handle_SkillSelectClickERKN5CEGUI9EventArgsE")
extern "C" char layoutFn[] __asm__("_ZN5CEGUI13WindowManager16loadWindowLayoutERKNS_6StringES3_S3_PFbPNS_6WindowERS1_S6_PvES7_");
extern "C" char topFn[] __asm__("_ZN5CEGUI6Window14setAlwaysOnTopEb");
extern "C" char searchFn[] __asm__("_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE");
namespace {
struct Stop {};
struct Case {unsigned pattern;bool change,alias;unsigned connection,fault;};
const Case* cs;autotest::Capture* cap;CSkillFoldout* fold;CGameUI* ui[3];CFileSystem* fs;CEGUI::WindowManager* wm;
unsigned long long pool[204][(sizeof(CEGUI::Window)+7)/8];void* eventTable[8];unsigned searches,subscriptions,events,valueCalls;unsigned refs[300];unsigned long long bound[300][4];
std::string* resource;std::wstring* resolvedPath;
CEGUI::Window* win(unsigned i){return reinterpret_cast<CEGUI::Window*>(pool[i]);}
int wid(const CEGUI::Window* w){for(unsigned i=0;i<204;++i)if(w==win(i))return i;return w?999:-1;}
int uid(CGameUI* p){for(unsigned i=0;i<3;++i)if(p==ui[i])return i;return p?999:-1;}
void number(int n){cap->add(&n,4);}
void bytes(const std::string& s){number(s.size());cap->add(s.data(),s.size());}
void wide(const std::wstring& s){number(s.size());cap->add(s.data(),s.size()*sizeof(wchar_t));}
void text(const CEGUI::String& s){number(s.length());for(unsigned i=0;i<s.length();++i){unsigned u=s[i];cap->add(&u,4);}}
void event(int n){number(n);++events;if(cs->fault==events)throw Stop();}
CFileSystem* singleton(){event(1);return fs;}
void info(CFileSystem* f,const std::wstring& name,CFileInfo& i,bool a,bool b,bool c){event(2);number(f==fs);wide(name);bytes(i.m_sModName);bytes(i.m_sResourceName);wide(i.m_sPath);number(i.m_eFormat);number(i.m_eLocation);bytes(i.m_sResourceGroup);number(i.m_bExists);number(a);number(b);number(c);i.m_sResourceName=*resource;i.m_sPath=*resolvedPath;i.m_sModName="mod";i.m_sResourceGroup="group";}
std::string unique(const std::string& s){event(3);bytes(s);return *resource+std::string("_unique\0tail",12);}
std::string value(int n){event(10);number(n);number(++valueCalls);char s[32];std::sprintf(s,"%d",n);std::string r=s;if(cs->pattern==1)r+=std::string(33,'x');if(cs->pattern==2)r+=std::string("\0end",4);if(cs->pattern==3)r+="\xc3\xa9";return r;}
CEGUI::Window* layout(CEGUI::WindowManager* m,const CEGUI::String& a,const CEGUI::String& b,const CEGUI::String& c,bool(*fn)(CEGUI::Window*,CEGUI::String&,CEGUI::String&,void*),void* data){event(4);number(m==wm);text(a);text(b);text(c);number(fn==0);number(data==0);return win(0);}
void top(CEGUI::Window* w,bool on){event(5);number(wid(w));number(on);w->d_alwaysOnTop=on;if(cs->change)fold->m_pWindow=win(1);}
void scale(CGameUI* u,CEGUI::Window* w,bool recurse){event(6);number(uid(u));number(wid(w));number(recurse);number(w->d_mousePassThroughEnabled);if(cs->change)fold->m_pWindow=win(2);}
CEGUI::Window* search(const CEGUI::Window* w,const CEGUI::String& name){event(7);number(wid(w));text(name);unsigned i=3+(searches++%(cs->alias?7:200));if(cs->change){fold->m_pWindow=win(searches%3);fold->m_pGameUI=ui[searches%3];}return win(i);}
CEGUI::Event::Connection subscribe(CEGUI::EventSet* e,const CEGUI::String& name,CEGUI::Event::Subscriber sub){
 event(8);number(wid(static_cast<CEGUI::Window*>(e)));text(name);CEGUI::MemberFunctionSlot<CGameUI>* f=static_cast<CEGUI::MemberFunctionSlot<CGameUI>*>(sub.d_functor_impl);
 intptr_t words[2];typedef char check_member_pointer[sizeof(f->d_function)==sizeof(words)?1:-1];std::memcpy(words,&f->d_function,sizeof(words));char* pairs[][2]={{overFn_original,overFn_linked},{outFn_original,outFn_linked},{clickFn_original,clickFn_linked}};
 for(unsigned i=0;i<3;++i)if(words[0]==(intptr_t)pairs[i][0]||words[0]==(intptr_t)pairs[i][1]){words[0]=(intptr_t)pairs[i][0];break;}cap->add(words,sizeof(words));number(uid(f->d_object));number(subscriptions?refs[subscriptions-1]:0);
 unsigned k=subscriptions++;if(k>=300)_exit(64);if(cs->change){fold->m_pGameUI=ui[(k+1)%3];unsigned cell=k/3;fold->m_Icons[cell/10][cell%10]=win(3+(k%200));}
 CEGUI::Event::Connection r;if(cs->connection){refs[k]=cs->connection+1;r.d_object=(CEGUI::BoundSlot*)bound[k];r.d_count=&refs[k];}return r;
}
void canonical(unsigned char* s,unsigned off,int n){uintptr_t x=n;std::memcpy(s+off,&x,8);}
void side(const Case& c,bool ours,autotest::Capture& out){
 cs=&c;cap=&out;searches=subscriptions=events=valueCalls=0;std::memset(refs,0,sizeof(refs));
 unsigned long long fm[(sizeof(CSkillFoldout)+7)/8],um[3][(sizeof(CGameUI)+7)/8]={{0}},fsMem[64]={0},wmMem[64]={0};
 std::memset(fm,0x5a,sizeof(fm));fold=(CSkillFoldout*)fm;for(unsigned i=0;i<3;++i)ui[i]=(CGameUI*)um[i];fold->m_pGameUI=ui[1];fs=(CFileSystem*)fsMem;wm=(CEGUI::WindowManager*)wmMem;CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton=wm;
 std::memset(pool,0,sizeof(pool));eventTable[2]=(void*)&subscribe;for(unsigned i=0;i<204;++i){*(void***)(static_cast<CEGUI::EventSet*>(win(i)))=eventTable;win(i)->d_alwaysOnTop=c.alias;win(i)->d_mousePassThroughEnabled=!c.alias;}
 std::string r=c.pattern==0?std::string("layout"):c.pattern==1?std::string(80,'x'):c.pattern==2?std::string("abc\0tail",8):std::string("layout_\xc3\xa9");std::wstring p=L"resolved/path",arg=c.pattern==2?std::wstring(L"input\0tail",10):std::wstring(L"media/Ω中.layout");resource=&r;resolvedPath=&p;
 detour::Set redirects;TL_REDIRECT(redirects,fileSingleton,&singleton);TL_REDIRECT(redirects,fileInfo,&info);TL_REDIRECT(redirects,uniqueFn,&unique);TL_REDIRECT(redirects,valueFn,&value);TL_REDIRECT(redirects,scaleFn,&scale);redirects.redirect(layoutFn,layoutFn,&layout);redirects.redirect(topFn,topFn,&top);redirects.redirect(searchFn,searchFn,&search);if(redirects.failed())_exit(65);
 bool threw=false;try{if(ours)autotest::invoke(out,&candidateLoad,fold,ui[0],arg);else autotest::invoke(out,&originalLoad,fold,ui[0],arg);}catch(const Stop&){threw=true;}catch(...){_exit(66);}
 number(threw);number(events);number(searches);number(subscriptions);number(valueCalls);int rr,pr;std::memcpy(&rr,reinterpret_cast<const char*>(r.data())-8,4);std::memcpy(&pr,reinterpret_cast<const char*>(p.data())-8,4);number(rr);number(pr);if(rr||pr)_exit(67);
 unsigned char snapshot[sizeof(CSkillFoldout)];std::memcpy(snapshot,fold,sizeof(snapshot));canonical(snapshot,0x338,uid(fold->m_pGameUI));for(unsigned off=0x348;off<0x990;off+=8){CEGUI::Window* w;std::memcpy(&w,snapshot+off,8);if(wid(w)!=999)canonical(snapshot,off,wid(w));}cap->add(snapshot,sizeof(snapshot));for(unsigned i=0;i<204;++i){number(win(i)->d_alwaysOnTop);number(win(i)->d_mousePassThroughEnabled);}for(unsigned i=0;i<subscriptions;++i)number(refs[i]);
}
void a(void* c,autotest::Capture& o){side(*(Case*)c,false,o);}void b(void* c,autotest::Capture& o){side(*(Case*)c,true,o);}
bool equal(const autotest::Outcome& u,const autotest::Outcome& v){return u.reportValid&&v.reportValid&&u.childStatus==0&&v.childStatus==0&&u.capture.issue==0&&v.capture.issue==0&&u.capture.length>100&&u.capture.length==v.capture.length&&!std::memcmp(u.capture.data,v.capture.data,u.capture.length);}
}
TL_TEST(skill_foldout_load_differential){autotest::Coverage coverage("skill_foldout_load_differential",(uint64_t)(uintptr_t)&originalLoad);unsigned total=0;for(unsigned pattern=0;pattern<4;++pattern)for(unsigned change=0;change<2;++change)for(unsigned alias=0;alias<2;++alias)for(unsigned conn=0;conn<3;++conn){Case c={pattern,bool(change),bool(alias),conn,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);++total;if(pair||!equal(u,v)||!u.capture.callCompleted||!v.capture.callCompleted){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    MISMATCH %u/%u/%u/%u first %lu exits %d/%d lengths %lu/%lu\n",pattern,change,alias,conn,(unsigned long)f,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length);coverage.report(host);return 1;}}coverage.report(host);host->log("    FULL BODY: %u cases, 200 cells and 300 subscriptions per case; ordered callback identities/receivers, COW and connection lifetimes\n",total);return 0;}
TL_TEST(skill_foldout_load_expected_exceptions){unsigned total=0;const unsigned faults[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,95,96,97,98,99,450,451,452,453,454,455,899,900,901,902,903,904,905,906};for(unsigned f=0;f<sizeof(faults)/sizeof(faults[0]);++f)for(unsigned change=0;change<2;++change){Case c={2,bool(change),false,1,faults[f]};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);++total;if(!equal(u,v)||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.callTarget!=(uint64_t)(uintptr_t)&originalLoad||!host->comparison_pair||!host->comparison_pair(u.capture.callTarget,v.capture.callTarget)){host->log("    UNWIND MISMATCH fault %u change %u exits %d/%d lengths %lu/%lu\n",faults[f],change,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length);return 1;}}host->log("    EXPECTED EXCEPTIONS: %u matching partial-state and lifetime observations, excluded from normal coverage\n",total);return 0;}
