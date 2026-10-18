#include "FinishLevelFixture.h"
#include "DataGroup.h"
#include "TimerStatics.h"
#include "StringTranslate.h"
TL_ORIGINAL(std::wstring,serviceOld0,(CLevel*),"_ZN6CLevel26getLevelChampionSpawnClassEv")
extern "C" std::wstring serviceNew0(CLevel*) __asm__("_ZN6CLevel26getLevelChampionSpawnClassEv");
TL_ORIGINAL(std::wstring,serviceOld1,(CLevel*),"_ZN6CLevel25getLevelMonsterSpawnClassEv")
extern "C" std::wstring serviceNew1(CLevel*) __asm__("_ZN6CLevel25getLevelMonsterSpawnClassEv");
TL_ORIGINAL(std::wstring,serviceOld2,(CLevel*),"_ZN6CLevel7getNameEv")
extern "C" std::wstring serviceNew2(CLevel*) __asm__("_ZN6CLevel7getNameEv");
TL_ORIGINAL(void,serviceOld3,(CLevel*),"_ZN6CLevel8pushTimeEv")
extern "C" void serviceNew3(CLevel*) __asm__("_ZN6CLevel8pushTimeEv");
TL_ORIGINAL(void,serviceOld4,(CLevel*,const wchar_t*),"_ZN6CLevel7popTimeEPKw")
extern "C" void serviceNew4(CLevel*,const wchar_t*) __asm__("_ZN6CLevel7popTimeEPKw");
TL_ORIGINAL(void,serviceOld5,(CLevel*,bool),"_ZN6CLevel9setInitedEb")
extern "C" void serviceNew5(CLevel*,bool) __asm__("_ZN6CLevel9setInitedEb");
TL_ORIGINAL(Ogre::Vector3,serviceOld6,(CLevel*,const Ogre::Vector3&,float,float,bool),"_ZN6CLevel27randomOpenItemPositionRangeERKN4Ogre7Vector3Effb")
extern "C" Ogre::Vector3 serviceNew6(CLevel*,const Ogre::Vector3&,float,float,bool) __asm__("_ZN6CLevel27randomOpenItemPositionRangeERKN4Ogre7Vector3Effb");
TL_ORIGINAL(Ogre::Vector3,serviceOld7,(CLevel*,const Ogre::Vector3&,float,float,bool),"_ZN6CLevel23randomOpenPositionRangeERKN4Ogre7Vector3Effb")
extern "C" Ogre::Vector3 serviceNew7(CLevel*,const Ogre::Vector3&,float,float,bool) __asm__("_ZN6CLevel23randomOpenPositionRangeERKN4Ogre7Vector3Effb");
TL_ORIGINAL(bool,serviceOld8,(CLevel*,Ogre::Vector3,const Ogre::Vector3&,bool),"_ZN6CLevel15passableBetweenEN4Ogre7Vector3ERKS1_b")
extern "C" bool serviceNew8(CLevel*,Ogre::Vector3,const Ogre::Vector3&,bool) __asm__("_ZN6CLevel15passableBetweenEN4Ogre7Vector3ERKS1_b");
TL_ORIGINAL(const std::wstring&,serviceOld9,(CDataGroup*,std::wstring&,const std::wstring&),"_Z22getStringFromDataGroupP10CDataGroupRSbIwSt11char_traitsIwESaIwEERKS4_")
extern "C" const std::wstring& serviceNew9(CDataGroup*,std::wstring&,const std::wstring&) __asm__("_Z22getStringFromDataGroupP10CDataGroupRSbIwSt11char_traitsIwESaIwEERKS4_");
TL_ORIGINAL(void,serviceOld10,(CDataGroup*,FILE*),"_Z26parseDataGroupForRoomPieceP10CDataGroupP8_IO_FILE")
extern "C" void serviceNew10(CDataGroup*,FILE*) __asm__("_Z26parseDataGroupForRoomPieceP10CDataGroupP8_IO_FILE");
TL_FUNCTION(serviceTemplateLoad,"_ZN18CLevelTemplateData4loadEPKw")
TL_FUNCTION(serviceTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
extern "C" char serviceTimer_original[] __asm__("_ZN4Ogre5Timer15getMicrosecondsEv");extern "C" char serviceTimer_linked[] __asm__("_ZN4Ogre5Timer15getMicrosecondsEv");
TL_FUNCTION(serviceRandom,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(serviceMap,"_ZN6CLevel11mapPassableERKN4Ogre7Vector3E")
TL_FUNCTION(servicePass,"_ZN6CLevel16positionPassableERKN4Ogre7Vector3E")
TL_FUNCTION(serviceNoSpawn,"_ZN6CLevel17isInNoSpawnRegionERKN4Ogre7Vector3Ef")
TL_FUNCTION(serviceStatics,"_ZN13CTimerStatics10getStaticsEb")
TL_FUNCTION(serviceGroups,"_ZN10CDataGroup18GetDataGroupByNameERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(serviceValues,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
namespace finishservice {
struct Case{unsigned target,variant;};static unsigned variant,target,clockCalls,randomCalls,mapCalls,passCalls,spawnCalls;static std::vector<unsigned> trace;static bool record;static detour::Set *groupsPatch,*valuesPatch;
static void n(unsigned x){if(record)trace.push_back(x);}static void f(float x){unsigned b;std::memcpy(&b,&x,4);n(b);}static void v(const Ogre::Vector3&p){f(p.x);f(p.y);f(p.z);}
static void templateLoad(CLevelTemplateData*,const wchar_t*){}
static std::wstring translate(CStringTranslate*,const wchar_t*p){n(10);n(p&&std::wstring(p)==L"Floor");return variant%3?L"Этаж":L"";}
static unsigned long timer(Ogre::Timer*){++clockCalls;return static_cast<unsigned long>(variant)*1100ul+clockCalls*37ul;}
static float random(float a,float b){n(20);f(a);f(b);float ratio=float((randomCalls++*17+variant)%31)/30.0f;return a+(b-a)*ratio;}
static bool map(CLevel*,const Ogre::Vector3&p){n(30);v(p);++mapCalls;unsigned shape=variant%8;return shape==0 || (shape==1&&mapCalls>=2) || (shape==2&&mapCalls>=7) || (shape==3&&mapCalls>=99) || (shape==4&&mapCalls>=100) || (shape==5&&mapCalls%2==0);}
static bool pass(CLevel*,const Ogre::Vector3&p){n(40);v(p);++passCalls;return variant%5!=1 || passCalls%3==0;}
static bool noSpawn(CLevel*,const Ogre::Vector3&p,float radius){n(50);v(p);f(radius);++spawnCalls;return variant%5==2 || (variant%5==3&&spawnCalls<3);}
static std::wstring statics(CTimerStatics*,bool full){n(60);n(full);return L"fixture timers";}
struct Timer:CTimerStatics{~Timer(){n(70);}};
struct Character:CCharacter{unsigned id;Character(unsigned x):CCharacter(NULL),id(x){}virtual void levelLoaded(CLevel* p){n(80+id);n(p!=NULL);}};
static CDataGroup* groups(CDataGroup*p,const std::wstring& name,bool create){n(90);n(unsigned(p->GetNumberOfDataGroups()));n(name==L"PROPERTIES"?1:name==L"CHILDREN"?2:name==L"branch"?3:4);n(create);groupsPatch->restore();CDataGroup*r=reinterpret_cast<CDataGroup*(*)(CDataGroup*,const std::wstring&,bool)>(serviceGroups_original)(p,name,create);TL_REDIRECT(*groupsPatch,serviceGroups,&groups);return r;}
static const std::wstring& values(CDataGroup*p,const std::wstring& name,const std::wstring& def){n(100);n(name==L"VALUE"?1:name==L"DESCRIPTOR"?2:3);valuesPatch->restore();const std::wstring&r=reinterpret_cast<const std::wstring&(*)(CDataGroup*,const std::wstring&,const std::wstring&)>(serviceValues_original)(p,name,def);TL_REDIRECT(*valuesPatch,serviceValues,&values);return r;}
static void initializeWide(uintptr_t address){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),sizeof p);if(!p)new(reinterpret_cast<void*>(address))std::wstring;}
static void side(void*input,autotest::Capture&out,bool candidate){
 Case c=*static_cast<Case*>(input);record=false;target=c.target;variant=c.variant;clockCalls=randomCalls=mapCalls=passCalls=spawnCalls=0;trace.clear();finishlevel::Fixture f;initializeWide(0x1492210);initializeWide(0x1495cc8);
 detour::Set bounds,groupBoundary,valueBoundary;TL_REDIRECT(bounds,serviceTemplateLoad,&templateLoad);TL_REDIRECT(bounds,serviceTranslate,&translate);TL_REDIRECT(bounds,serviceTimer,&timer);TL_REDIRECT(bounds,serviceStatics,&statics);
 if(c.target>=6&&c.target<=8){TL_REDIRECT(bounds,serviceRandom,&random);TL_REDIRECT(bounds,serviceMap,&map);TL_REDIRECT(bounds,servicePass,&pass);TL_REDIRECT(bounds,serviceNoSpawn,&noSpawn);}
 groupsPatch=&groupBoundary;valuesPatch=&valueBoundary;
 CLevelTemplateData*data=new CLevelTemplateData(NULL);data->m_selectedUnitSpawners[0]=c.variant%2?L"monsters/Ω":L"";data->m_selectedUnitSpawners[1]=c.variant%2?L"champions/К":L"";data->m_showFloorNumber=c.variant%2;data->m_levelName=c.variant%3==0?L"":c.variant%3==1?L"Mines":L"洞穴";f.level.m_iLevelDepth=int(c.variant%9)-4;f.level.m_pLevelTemplateData=c.variant%4?data:NULL;
 Timer*t=new Timer;t->m_startMicroseconds=123;t->m_name=L"fixture";for(unsigned i=0;i<c.variant%5;++i)t->m_times.add(variant*1000+i*17);if(c.variant%3==0)t->m_statistics[L"named"]=std::make_pair(13u,2u);f.level.m_timerStatics=c.variant%4?t:NULL;TSafePointer<CTimerStatics>witness;witness.setObject(t);
 Character c0(0),c1(1);if(c.variant%3){finishlevel::prepend<CCharacter*>(f.level.m_pCharacters,&c0);if(c.variant%2)finishlevel::prepend<CCharacter*>(f.level.m_pCharacters,&c1);if(c.variant%4==1)finishlevel::prepend<CCharacter*>(f.level.m_pCharacters,NULL);}
 CDataGroup root(L"root",NULL,2,2,NULL);std::wstring childName=c.variant%2?L"branch":L"missing",fallback=c.variant%3?L"fallback/Ω":L"";
 if(c.variant%4){CDataGroup*branch=root.AddDataGroup(L"branch");if(c.variant%3)branch->SetDataValue(L"VALUE",c.variant%2?L"stored":L"",false);}
 if(c.target==10){for(unsigned i=0;i<c.variant%5;++i){CDataGroup*node=root.AddDataGroup(L"node");if((i+c.variant)%3){CDataGroup*properties=node->AddDataGroup(L"PROPERTIES");properties->SetDataValue(L"DESCRIPTOR",i%2?L"Room Piece":L"Other",false);CDataGroup*children=node->AddDataGroup(L"CHILDREN");if(i%2){CDataGroup*inner=children->AddDataGroup(L"nested");inner->AddDataGroup(L"PROPERTIES")->SetDataValue(L"DESCRIPTOR",L"Room Piece",false);}}}}
 TL_REDIRECT(groupBoundary,serviceGroups,&groups);TL_REDIRECT(valueBoundary,serviceValues,&values);if(bounds.failed()||groupBoundary.failed()||valueBoundary.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 const wchar_t*timeName=c.variant%3==0?NULL:c.variant%3==1?L"":L"named";Ogre::Vector3 point(float(c.variant%7)-3,4,float(c.variant%11)-5),end=point+Ogre::Vector3(float(c.variant%9)*0.15f,9,float(c.variant%5)*0.2f);float minimum=float(c.variant%5)*0.2f,maximum=minimum+float(c.variant%3)*0.4f;FILE*file=c.variant%2?tmpfile():NULL;
 record=true;
 switch(c.target){
 case 0:if(candidate)autotest::invoke<std::wstring(*)(CLevel*),CLevel*>(out,serviceNew0,&f.level);else autotest::invoke<std::wstring(*)(CLevel*),CLevel*>(out,serviceOld0,&f.level);break;
 case 1:if(candidate)autotest::invoke<std::wstring(*)(CLevel*),CLevel*>(out,serviceNew1,&f.level);else autotest::invoke<std::wstring(*)(CLevel*),CLevel*>(out,serviceOld1,&f.level);break;
 case 2:if(candidate)autotest::invoke<std::wstring(*)(CLevel*),CLevel*>(out,serviceNew2,&f.level);else autotest::invoke<std::wstring(*)(CLevel*),CLevel*>(out,serviceOld2,&f.level);break;
 case 3:if(candidate)autotest::invoke<void(*)(CLevel*),CLevel*>(out,serviceNew3,&f.level);else autotest::invoke<void(*)(CLevel*),CLevel*>(out,serviceOld3,&f.level);break;
 case 4:if(candidate)autotest::invoke<void(*)(CLevel*,const wchar_t*),CLevel*,const wchar_t*>(out,serviceNew4,&f.level,timeName);else autotest::invoke<void(*)(CLevel*,const wchar_t*),CLevel*,const wchar_t*>(out,serviceOld4,&f.level,timeName);break;
 case 5:if(candidate)autotest::invoke<void(*)(CLevel*,bool),CLevel*,bool>(out,serviceNew5,&f.level,bool(c.variant%2));else autotest::invoke<void(*)(CLevel*,bool),CLevel*,bool>(out,serviceOld5,&f.level,bool(c.variant%2));break;
 case 6:if(candidate)autotest::invoke<Ogre::Vector3(*)(CLevel*,const Ogre::Vector3&,float,float,bool),CLevel*,const Ogre::Vector3&,float,float,bool>(out,serviceNew6,&f.level,point,minimum,maximum,bool(c.variant%2));else autotest::invoke<Ogre::Vector3(*)(CLevel*,const Ogre::Vector3&,float,float,bool),CLevel*,const Ogre::Vector3&,float,float,bool>(out,serviceOld6,&f.level,point,minimum,maximum,bool(c.variant%2));break;
 case 7:if(candidate)autotest::invoke<Ogre::Vector3(*)(CLevel*,const Ogre::Vector3&,float,float,bool),CLevel*,const Ogre::Vector3&,float,float,bool>(out,serviceNew7,&f.level,point,minimum,maximum,bool(c.variant%2));else autotest::invoke<Ogre::Vector3(*)(CLevel*,const Ogre::Vector3&,float,float,bool),CLevel*,const Ogre::Vector3&,float,float,bool>(out,serviceOld7,&f.level,point,minimum,maximum,bool(c.variant%2));break;
 case 8:if(candidate)autotest::invoke<bool(*)(CLevel*,Ogre::Vector3,const Ogre::Vector3&,bool),CLevel*,Ogre::Vector3,const Ogre::Vector3&,bool>(out,serviceNew8,&f.level,point,end,bool(c.variant%2));else autotest::invoke<bool(*)(CLevel*,Ogre::Vector3,const Ogre::Vector3&,bool),CLevel*,Ogre::Vector3,const Ogre::Vector3&,bool>(out,serviceOld8,&f.level,point,end,bool(c.variant%2));break;
 case 9:{typedef const std::wstring&(*Fn)(CDataGroup*,std::wstring&,const std::wstring&);Fn fn=candidate?&serviceNew9:&serviceOld9;if(!autotest::beginInvocation(out,fn))return;const std::wstring& result=fn(&root,childName,fallback);out.callCompleted=1;out.addText(result);finishlevel::number(out,&result==&fallback);break;}
 case 10:if(candidate)autotest::invoke<void(*)(CDataGroup*,FILE*),CDataGroup*,FILE*>(out,serviceNew10,c.variant%7?&root:NULL,file);else autotest::invoke<void(*)(CDataGroup*,FILE*),CDataGroup*,FILE*>(out,serviceOld10,c.variant%7?&root:NULL,file);break;
 }
 record=false;finishlevel::number(out,trace.size());for(unsigned i=0;i<trace.size();++i)finishlevel::number(out,trace[i]);finishlevel::number(out,clockCalls);finishlevel::number(out,randomCalls);finishlevel::number(out,mapCalls);finishlevel::number(out,passCalls);finishlevel::number(out,spawnCalls);finishlevel::number(out,f.level.m_automapRoomPieces);finishlevel::number(out,f.level.m_timerStatics!=NULL);finishlevel::number(out,witness.getObject()!=NULL);
 if(witness.getObject()){finishlevel::number(out,t->m_times.size());for(unsigned i=0;i<t->m_times.size();++i)finishlevel::number(out,t->m_times[i]);finishlevel::number(out,t->m_statistics.size());for(std::map<std::wstring,std::pair<unsigned,unsigned> >::iterator p=t->m_statistics.begin();p!=t->m_statistics.end();++p){out.addText(p->first);finishlevel::number(out,p->second.first);finishlevel::number(out,p->second.second);}delete t;}
 if(file){finishlevel::number(out,ftell(file));fclose(file);}f.level.m_timerStatics=NULL;f.level.m_pLevelTemplateData=NULL;delete data;
}
static void original(void*p,autotest::Capture&o){side(p,o,false);}static void ours(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(finish_level_service_9366f0){autotest::Coverage coverage("finish_level_service_9366f0",0x9366f0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<48;++n){finishservice::Case c={0,n};autotest::compareCase(finishservice::original,finishservice::ours,&c,stats,host,"service",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=48;}
TL_TEST(finish_level_service_936740){autotest::Coverage coverage("finish_level_service_936740",0x936740);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<48;++n){finishservice::Case c={1,n};autotest::compareCase(finishservice::original,finishservice::ours,&c,stats,host,"service",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=48;}
TL_TEST(finish_level_service_95a790){autotest::Coverage coverage("finish_level_service_95a790",0x95a790);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<48;++n){finishservice::Case c={2,n};autotest::compareCase(finishservice::original,finishservice::ours,&c,stats,host,"service",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=48;}
TL_TEST(finish_level_service_94a570){autotest::Coverage coverage("finish_level_service_94a570",0x94a570);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<48;++n){finishservice::Case c={3,n};autotest::compareCase(finishservice::original,finishservice::ours,&c,stats,host,"service",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=48;}
TL_TEST(finish_level_service_95ee30){autotest::Coverage coverage("finish_level_service_95ee30",0x95ee30);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<48;++n){finishservice::Case c={4,n};autotest::compareCase(finishservice::original,finishservice::ours,&c,stats,host,"service",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=48;}
TL_TEST(finish_level_service_95e8b0){autotest::Coverage coverage("finish_level_service_95e8b0",0x95e8b0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<48;++n){finishservice::Case c={5,n};autotest::compareCase(finishservice::original,finishservice::ours,&c,stats,host,"service",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=48;}
TL_TEST(finish_level_service_9455e0){autotest::Coverage coverage("finish_level_service_9455e0",0x9455e0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<48;++n){finishservice::Case c={6,n};autotest::compareCase(finishservice::original,finishservice::ours,&c,stats,host,"service",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=48;}
TL_TEST(finish_level_service_945770){autotest::Coverage coverage("finish_level_service_945770",0x945770);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<48;++n){finishservice::Case c={7,n};autotest::compareCase(finishservice::original,finishservice::ours,&c,stats,host,"service",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=48;}
TL_TEST(finish_level_service_948240){autotest::Coverage coverage("finish_level_service_948240",0x948240);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<48;++n){finishservice::Case c={8,n};autotest::compareCase(finishservice::original,finishservice::ours,&c,stats,host,"service",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=48;}
TL_TEST(finish_level_service_95a6d0){autotest::Coverage coverage("finish_level_service_95a6d0",0x95a6d0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<48;++n){finishservice::Case c={9,n};autotest::compareCase(finishservice::original,finishservice::ours,&c,stats,host,"service",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=48;}
TL_TEST(finish_level_service_94f4f0){autotest::Coverage coverage("finish_level_service_94f4f0",0x94f4f0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<48;++n){finishservice::Case c={10,n};autotest::compareCase(finishservice::original,finishservice::ours,&c,stats,host,"service",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=48;}
