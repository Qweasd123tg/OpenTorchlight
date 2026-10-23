#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/CharacterEmptyGlobals.h"
#include <Ogre.h>
#include <map>
#define private public
#include "UnitThemes.h"
#include "UnitTheme.h"
#include "UnitThemeParticle.h"
#undef private
#include "tests/NativeGameServices.h"
#include "StringUtilities.h"
TL_ORIGINAL(void,utCtorOld,(CUnitThemes*,const wchar_t*),"_ZN11CUnitThemesC1EPKw")
extern "C" void utCtorNew(CUnitThemes*,const wchar_t*) __asm__("_ZN11CUnitThemesC1EPKw");
TL_ORIGINAL(void,utDtorOld,(CUnitThemes*),"_ZN11CUnitThemesD1Ev")
TL_FUNCTION(utReloadEntry,"_ZN11CUnitThemes6reloadEv")
namespace {
struct Case{unsigned seed,observed,negative;};const Case*input;autotest::Capture*output;TSafePointer<CUnitTheme>*weak;unsigned created,reloads;std::wstring requested,directory;unsigned observed;
void word(unsigned x){output->add(&x,sizeof x);}void*&singleton(){return *reinterpret_cast<void**>(0x14b5860);}
void reload(CUnitThemes*self){++reloads;output->addText(self->m_sFilename);word(self->m_Themes.m_nGrowBy);word(self->m_Themes.size());word(singleton()!=NULL);unsigned count=input->seed%5;for(unsigned i=0;i<count;++i){CUnitTheme*theme=new CUnitTheme;theme->m_sName=i&1?L"Жёлтый":L"ALPHA";theme->m_iGuid=9000+i;theme->m_particles.setGrowBy(10);for(unsigned j=0;j<(input->seed+i)%3;++j){CUnitThemeParticle*p=new CUnitThemeParticle;p->m_wstrFile=L"fixture.layout";p->m_wstrBone=L"BONE";p->m_iCount=j;p->m_iUnitTypeID=0;p->m_bAttaches=j&1;p->m_bFollows=!(j&1);theme->m_particles.add(p);}weak[created++].setObject(theme);self->m_Themes.add(theme);}}
void side(void*raw,autotest::Capture&out,bool ours){input=static_cast<Case*>(raw);output=&out;created=reloads=0;TSafePointer<CUnitTheme>tokens[8];weak=tokens;void*previous=singleton();if(!(input->seed&1))singleton()=NULL;requested=directory+L"/";if(input->observed){if(input->seed%7==0)requested=L"";if(input->seed%11==0)requested+=std::wstring(1024,L'W');if(input->seed%13==0)requested+=L"Жёлтый/";}CUnitThemes*self=static_cast<CUnitThemes*>(Ogre::NedAllocImpl::allocBytes(sizeof(CUnitThemes),0,0,0));std::memset(self,0x40+input->seed%50,sizeof(CUnitThemes));detour::Set setup;if(input->observed)TL_REDIRECT(setup,utReloadEntry,&reload);if(setup.failed())std::abort();typedef void(*Fn)(CUnitThemes*,const wchar_t*);Fn fn=ours?utCtorNew:utCtorOld;if(autotest::beginInvocation(out,fn)){fn(self,requested.c_str());out.callCompleted=1;}setup.restore();if(ours&&input->negative)self->m_sFilename+=L"NEGATIVE";output->addText(self->m_sFilename);word(self->m_Themes.m_nGrowBy);word(self->m_Themes.size());word(self->m_Themes.m_nCapacity);word(singleton()==self);word(singleton()==previous);word(reloads);for(unsigned i=0;i<self->m_Themes.size();++i){CUnitTheme*t=self->m_Themes[i];output->addText(t->m_sName);out.add(&t->m_iGuid,sizeof t->m_iGuid);word(t->m_particles.size());}word(self->m_sFilename==requested);if(!input->negative&&self->m_sFilename!=requested)out.issue=autotest::Capture::InvalidReport;utDtorOld(self);Ogre::NedAllocImpl::deallocBytes(self);word(singleton()==NULL);for(unsigned i=0;i<created;++i){word(weak[i].getObject()==NULL);if(weak[i].getObject())out.issue=autotest::Capture::InvalidReport;}singleton()=previous;}
void oldSide(void*p,autotest::Capture&o){side(p,o,false);}void newSide(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){initEmptyGlobals();nativegame::Services services;if(!services.ready())return 1;directory=STRINGS::StringConvertToWide(services.base+"unit-themes");std::string narrow=services.base+"unit-themes";mkdir(narrow.c_str(),0700);const char*name=observed?"unit_themes_ctor_owned_native":"unit_themes_ctor_files_native";autotest::Coverage coverage(name,(uintptr_t)utCtorOld);int bad=0;for(unsigned seed=0;seed<64;++seed){Case c={seed,observed,0};autotest::Outcome a,b;autotest::runChild(oldSide,&c,a,8000,32000);autotest::runChild(newSide,&c,b,8000,32000);if(coverage.observe(host,a,b)){host->log("    unit-themes seed%u valid%u/%u status%d/%d issue%u/%u bytes%lu/%lu\n",seed,a.reportValid,b.reportValid,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);bad=1;break;}}coverage.report(host);Case c={27,observed,1};autotest::Outcome a,b;autotest::runChild(oldSide,&c,a,8000,32000);autotest::runChild(newSide,&c,b,8000,32000);bool complete=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);host->log("    %s negative detected%u completed%u\n",name,unsigned(detected),unsigned(complete));rmdir(narrow.c_str());return bad||coverage.completed!=64||!complete||!detected;}
}
TL_TEST(unit_themes_ctor_files_native){observed=0;return systems_fixture::isolated(worker,host,180);}
TL_TEST(unit_themes_ctor_owned_native){observed=1;return systems_fixture::isolated(worker,host,180);}
