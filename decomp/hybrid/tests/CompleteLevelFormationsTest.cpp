#include "tests/FinishLevelFixture.h"
#include "tests/NativeMenuServices.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "FormationNode.h"
#include "DataGroup.h"
#include "Utilities.h"
#undef protected
#undef private
#include <limits>
#include <ucontext.h>
#include <signal.h>
TL_ORIGINAL(unsigned,pfOld,(CLevel*,CRandomizer&,TArrayList<Ogre::AxisAlignedBox>&),"_ZN6CLevel18populateFormationsER11CRandomizerR10TArrayListIN4Ogre14AxisAlignedBoxEE")
extern "C" unsigned pfNew(CLevel*,CRandomizer&,TArrayList<Ogre::AxisAlignedBox>&) __asm__("_ZN6CLevel18populateFormationsER11CRandomizerR10TArrayListIN4Ogre14AxisAlignedBoxEE");
TL_FUNCTION(pfLoad,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TL_FUNCTION(pfTemplateLoad,"_ZN18CLevelTemplateData4loadEPKw")
TL_FUNCTION(pfCount,"_ZN18CLevelTemplateData24getNumberOfUnitsToCreateE21ELEVELLAYOUT_CREATIONj")
TL_FUNCTION(pfRandom,"_ZN11CRandomizer9getRandomEv")
TL_FUNCTION(pfBetween,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(pfOpen,"_ZN6CLevel18randomOpenPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(pfNoSpawn,"_ZN6CLevel17isInNoSpawnRegionERKN4Ogre7Vector3Ef")
TL_FUNCTION(pfLayout,"_ZN14CFormationNode13setLayoutFileERKSbIwSt11char_traitsIwESaIwEEP16CResourceManager")
namespace {
const tlhybrid_host*logger;volatile sig_atomic_t phase;
void fault(int signal,siginfo_t*info,void*raw){ucontext_t*u=static_cast<ucontext_t*>(raw);logger->log("    formations signal%d phase%d rip%lx addr%lx\n",signal,int(phase),(unsigned long)u->uc_mcontext.gregs[REG_RIP],(unsigned long)info->si_addr);struct sigaction a;std::memset(&a,0,sizeof a);a.sa_handler=SIG_DFL;sigemptyset(&a.sa_mask);sigaction(signal,&a,NULL);raise(signal);}
nativegame::Services*services;autotest::Capture*output;CLevel*level;CLevelTemplateData*data;CResourceManager*resources;CRandomizer*regions;unsigned seed,randomCalls,betweenCalls,openCalls,noSpawnCalls;std::vector<CFormationNode*>created;
void number(unsigned n){output->add(&n,4);}void scalar(float f){output->add(&f,4);}void vec(const Ogre::Vector3&v){output->add(&v,sizeof v);}void wide(const std::wstring&s){number(s.size());if(s.size())output->add(s.data(),s.size()*4);}
void templateLoad(CLevelTemplateData*,const wchar_t*){}
void load(CDataGroup*p,const std::wstring&name,CTimerStatics*t){number(1);wide(name);number(t==NULL);number(p->m_DataValues.m_nGrowBy);number(p->m_DataGroups.m_nGrowBy);unsigned count=seed/3%5;for(unsigned i=0;i<count;++i){CDataGroup*g=p->AddDataGroup(L"FORMATION");if(seed/17%5!=i)g->AddDataValue(L"FILE",i%2?L"path/\x041b\x0435\x0441.layout":L"formation.layout",false);g->AddDataValue(L"WEIGHT",int((seed+i)%9)-3);}}
unsigned count(CLevelTemplateData*p,ELEVELLAYOUT_CREATION kind,unsigned area){number(2);number(p==data);number(kind);number(area);return seed/3%5?seed/5%5:0;}
int random(CRandomizer*p){number(3);number(p==regions);number(p->getChoiceCount());for(unsigned i=0;i<p->getChoiceCount();++i){number(p->getChoice(i));scalar(p->m_Odds[i]);}unsigned n=++randomCalls;unsigned choice=p->getChoiceCount()?(seed+n*3)%p->getChoiceCount():0;number(choice);return choice;}
float between(float a,float b){number(4);scalar(a);scalar(b);unsigned n=++betweenCalls;float value=a+(b-a)*float((seed+n*7)%17)/16.0f;scalar(value);return value;}
Ogre::Vector3 open(CLevel*p,const Ogre::Vector3&v,float radius,bool flag){number(5);number(p==level);vec(v);scalar(radius);number(flag);unsigned n=++openCalls;Ogre::Vector3 result=v;switch(seed/7%5){case 0:break;case 1:result.y-=1;break;case 2:if(n%5>1)result.y=-2;break;case 3:result=Ogre::Vector3(0,0,0);break;default:result.x=std::numeric_limits<float>::quiet_NaN();break;}vec(result);return result;}
bool noSpawn(CLevel*p,const Ogre::Vector3&v,float radius){number(6);number(p==level);vec(v);scalar(radius);unsigned n=++noSpawnCalls;bool value=seed/11%4==0||(seed/11%4==1&&n%3!=0);number(value);return value;}
void layout(CFormationNode*p,const std::wstring&name,CResourceManager*r){number(7);number(r==resources);wide(name);number(p->m_bActivationStarted);number(p->m_pEditorScene==NULL);created.push_back(p);}
void side(void*raw,autotest::Capture&out,bool ours){seed=*static_cast<unsigned*>(raw);output=&out;randomCalls=betweenCalls=openCalls=noSpawnCalls=0;created.clear();phase=1;finishlevel::Fixture f;level=&f.level;resources=&f.resources;resources->m_pSceneManager=services->scene;level->m_openCellCount=seed*3+1;
 phase=2;CLevelTemplateData owner(L"formations-no-io");data=&owner;data->m_selectedUnitSpawners[7]=seed%7==1?L"":L"formations.dat";level->m_pLevelTemplateData=seed%7==0?NULL:data;unsigned prior=seed/13%4;for(unsigned i=0;i<prior;++i){CFormationNode*p=new CFormationNode(resources,NULL);phase=3;p->setPosition(Ogre::Vector3(float(i)*20.f,0,float(seed%3)*10.f));level->m_formations.add(p);}
 CRandomizer randomizer(RANDOMIZER_NORMAL);regions=&randomizer;TArrayList<Ogre::AxisAlignedBox>boxes(3);for(unsigned i=0;i<3;++i){Ogre::Vector3 lo(float(int(seed%5)-2)+i*30.f,-9,-float(i)*40.f),hi=lo+Ogre::Vector3(15,17,25);boxes.add(Ogre::AxisAlignedBox(lo,hi));randomizer.addChoice(i,i+1);}
 detour::Set hooks;TL_REDIRECT(hooks,pfLoad,&load);TL_REDIRECT(hooks,pfCount,&count);TL_REDIRECT(hooks,pfRandom,&random);TL_REDIRECT(hooks,pfBetween,&between);TL_REDIRECT(hooks,pfOpen,&open);TL_REDIRECT(hooks,pfNoSpawn,&noSpawn);TL_REDIRECT(hooks,pfLayout,&layout);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 phase=100;typedef unsigned(*Fn)(CLevel*,CRandomizer&,TArrayList<Ogre::AxisAlignedBox>&);Fn fn=ours?pfNew:pfOld;if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(level,randomizer,boxes);out.callCompleted=1;phase=200;number(result);number(randomCalls);number(betweenCalls);number(openCalls);number(noSpawnCalls);number(created.size());number(level->m_formations.size());number(level->m_formations.m_nCapacity);number(level->m_formations.m_nGrowBy);for(unsigned i=0;i<level->m_formations.size();++i){CFormationNode*p=level->m_formations[i];number(p!=NULL);vec(p->getPosition(false));number(p->m_bActivationStarted);number(p->m_pEditorScene==NULL);}hooks.restore();level->m_pLevelTemplateData=NULL;level->m_formations.deleteAll();}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){logger=host;struct sigaction sa;std::memset(&sa,0,sizeof sa);sa.sa_sigaction=&fault;sa.sa_flags=SA_SIGINFO;sigemptyset(&sa.sa_mask);sigaction(SIGSEGV,&sa,NULL);sigaction(SIGABRT,&sa,NULL);nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(native.master);void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1495cc8),8);if(!p)new(reinterpret_cast<void*>(0x1495cc8))std::wstring;detour::Set setup;TL_REDIRECT(setup,pfTemplateLoad,&templateLoad);if(setup.failed())return 1;if(std::getenv("OTL_FORMATION_DIRECT")){unsigned i=13;autotest::Capture capture;side(&i,capture,false);return !capture.callCompleted;}autotest::Coverage coverage("level_formations",0x95dc40);for(unsigned i=0;i<512;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    formations seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned z=0;z<a.capture.length&&z<b.capture.length;++z)if(a.capture.data[z]!=b.capture.data[z]){host->log("    firstdiff%u old%02x new%02x\n",z,(unsigned char)a.capture.data[z],(unsigned char)b.capture.data[z]);break;}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=512||coverage.missing||coverage.different;}
}
TL_TEST(complete_level_formations){return systems_fixture::isolated(&worker,host);}
