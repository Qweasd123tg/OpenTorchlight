#include <cstring>
#include <new>
#include <string>
#include "StatsMenu.h"
#include "GenericModel.h"
#include "SoundBank.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalDtor, (CStatsMenu*), "_ZN10CStatsMenuD1Ev")
TL_ORIGINAL(void, originalDelete, (CStatsMenu*), "_ZN10CStatsMenuD0Ev")
extern "C" void candidateDtor(CStatsMenu*) __asm__("_ZN10CStatsMenuD1Ev");
extern "C" void candidateDelete(CStatsMenu*) __asm__("_ZN10CStatsMenuD0Ev");
TL_FUNCTION(coreDtorFn,"_ZN10CRunicCoreD1Ev")
extern "C" char freeFn[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
namespace {
struct Stop {};
struct Case {unsigned mask,pattern;bool replace,deleting;unsigned fault;};
const Case* cs;autotest::Capture* cap;CStatsMenu* menu;void* objects[3];unsigned destroyed[3],coreCalls,freeCalls;
void n(int value){cap->add(&value,4);}
int id(void* p){if(!p)return 0;for(unsigned i=0;i<3;++i)if(p==objects[i])return i+1;return 99;}
void destroy(void* p){unsigned i=id(p)-1;n(1);n(i);if(i>=3)_exit(64);++destroyed[i];n(id(menu->m_pModel));n(id(menu->m_pSoundBank));if(cs->fault==(i==0?1u:2u))throw Stop();if(cs->replace&&i==0){menu->m_pModel=(CGenericModel*)objects[2];menu->m_pSoundBank=(CSoundBank*)objects[2];}}
void core(CRunicCore* p){n(2);n(p==static_cast<CRunicCore*>(menu));++coreCalls;n(id(menu->m_pModel));n(id(menu->m_pSoundBank));}
void release(void* p){n(3);n(p==menu);++freeCalls;}
void ptr(unsigned char* bytes,unsigned offset,unsigned value){uintptr_t v=value;std::memcpy(bytes+offset,&v,sizeof(v));}
void side(const Case& c,bool ours,autotest::Capture& out){
 unsigned long long mem[(sizeof(CStatsMenu)+7)/8],fake[3][4];void* table[2]={0,(void*)&destroy};std::memset(mem,c.replace?0x5a:0xa5,sizeof(mem));std::memset(fake,0x67,sizeof(fake));for(unsigned i=0;i<3;++i){objects[i]=fake[i];*(void***)objects[i]=table;destroyed[i]=0;}menu=(CStatsMenu*)mem;cs=&c;cap=&out;coreCalls=freeCalls=0;
 menu->m_pModel=c.mask&1?(CGenericModel*)objects[0]:0;menu->m_pSoundBank=c.mask&2?(CSoundBank*)objects[1]:0;
 typedef std::wstring Wide;Wide aliases[4];Wide* fields[]={&menu->m_TextA0,&menu->m_DamageDescription,&menu->m_TextB0,&menu->m_ArmorDescription};
 for(unsigned i=0;i<4;++i){if(c.pattern==1)aliases[i]=Wide(i+1,L'A'+i);if(c.pattern==2)aliases[i]=Wide(512+i*17,L'a'+i);if(c.pattern==3){aliases[i]=L"\u00e9\u4e2d";aliases[i]+=wchar_t('0'+i);}new(fields[i])Wide(aliases[i]);}
 detour::Set redirects;TL_REDIRECT(redirects,coreDtorFn,&core);redirects.redirect(freeFn,freeFn,&release);if(redirects.failed())_exit(65);
 bool threw=false;try{if(ours)autotest::invoke(out,c.deleting?&candidateDelete:&candidateDtor,menu);else autotest::invoke(out,c.deleting?&originalDelete:&originalDtor,menu);}catch(const Stop&){threw=true;}catch(...){_exit(66);}
 n(threw);n(coreCalls);n(freeCalls);for(unsigned i=0;i<3;++i)n(destroyed[i]);unsigned char snapshot[sizeof(CStatsMenu)];std::memcpy(snapshot,menu,sizeof(snapshot));ptr(snapshot,0x1a0,id(menu->m_pModel));ptr(snapshot,0x1b8,id(menu->m_pSoundBank));
 for(unsigned i=0;i<4;++i){int refs;std::memcpy(&refs,(const char*)aliases[i].data()-8,4);n(refs);cap->addText(aliases[i]);ptr(snapshot,0xa0+8*i,0);}
 cap->add(snapshot,sizeof(snapshot));
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
int normal(const tlhybrid_host* host,bool deleting,const char* name){
 autotest::Coverage coverage(name,(uint64_t)(uintptr_t)(deleting?&originalDelete:&originalDtor));
 for(unsigned mask=0;mask<4;++mask)for(unsigned pattern=0;pattern<4;++pattern)for(unsigned change=0;change<2;++change){Case c={mask,pattern,bool(change),deleting,0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);if(pair||!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callCompleted||!v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    dtor mismatch mask %u pattern %u replace %u exits %d/%d lengths %lu/%lu first %lu\n",mask,pattern,change,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length,(unsigned long)f);coverage.report(host);return 1;}}
 coverage.report(host);return 0;
}
}
TL_TEST(statsmenu_destructor_differential){return normal(host,false,"statsmenu_destructor_differential");}
TL_TEST(statsmenu_deleting_destructor_differential){return normal(host,true,"statsmenu_deleting_destructor_differential");}
TL_TEST(statsmenu_destructor_expected_exceptions){
 unsigned total=0;for(unsigned fault=1;fault<=2;++fault)for(unsigned pattern=0;pattern<4;++pattern)for(unsigned change=0;change<2;++change){Case c={3,pattern,bool(change),false,fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);++total;if(!u.reportValid||!v.reportValid||u.childStatus||v.childStatus||!u.capture.callStarted||!v.capture.callStarted||u.capture.callCompleted||v.capture.callCompleted||u.capture.issue||v.capture.issue||u.capture.length!=v.capture.length||std::memcmp(u.capture.data,v.capture.data,u.capture.length)){host->log("    dtor unwind mismatch %u/%u/%u exits %d/%d lengths %lu/%lu\n",fault,pattern,change,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length);return 1;}}
 host->log("    EXPECTED DESTRUCTOR EXCEPTIONS: %u matching unwinds; not normal completion coverage\n",total);return 0;
}
