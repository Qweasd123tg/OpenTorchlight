#include "tests/FinishLevelFixture.h"
#include "tests/NativeMenuServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "NativeAutomapFixture.h"
#include "GameVariables.h"
TL_ORIGINAL(void,avOld,(CLevel*,bool),"_ZN6CLevel17setAutomapVisibleEb")
extern "C" void avNew(CLevel*,bool) __asm__("_ZN6CLevel17setAutomapVisibleEb");
TL_FUNCTION(avVisible,"_ZN8CAutomap10setVisibleEb")
namespace {
autotest::Capture*output;CAutomap*map;unsigned calls;
void number(unsigned n){output->add(&n,4);}void visible(CAutomap*p,bool b){++calls;number(p==map);number(b);number(p->m_bVisible);number(gbWasVisible);number(p->m_bFullscreen);number(p->m_bFullMap);p->m_bVisible=b;}
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);output=&out;calls=0;finishlevel::Fixture f;f.level.m_automap=seed&1?map:NULL;map->m_bVisible=(seed&4)!=0;map->m_bFullscreen=(seed&16)!=0;map->m_bFullMap=(seed&32)!=0;gbWasVisible=(seed&8)!=0;detour::Set hooks;TL_REDIRECT(hooks,avVisible,&visible);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef void(*Fn)(CLevel*,bool);Fn fn=ours?avNew:avOld;if(!autotest::beginInvocation(out,fn))return;fn(&f.level,(seed&2)!=0);out.callCompleted=1;number(calls);number(map->m_bVisible);number(gbWasVisible);number(map->m_bFullscreen);number(map->m_bFullMap);hooks.restore();f.level.m_automap=NULL;}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(services.master);CResourceManager resources(services.scene);level_native::Automap native(&resources,services.scene);map=native.map;bool previous=gbWasVisible;autotest::Coverage coverage("level_automap_visible",reinterpret_cast<uintptr_t>(avOld));for(unsigned i=0;i<64;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    automapVisible seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);gbWasVisible=previous;return coverage.completed!=64||coverage.missing||coverage.different;}
}
TL_TEST(complete_level_automap_visible){return systems_fixture::isolated(&worker,host);}
