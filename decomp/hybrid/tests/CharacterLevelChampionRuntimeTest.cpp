#include <cstring>
#include <limits>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "Graph.h"
#include "GraphManager.h"
#include "AttackDescription.h"
#include "DataGroup.h"
#include "TRepository.h"
#include "StringUtilities.h"
#include "EmptyStrings.h"
#undef private
#undef protected
#include "tests/NativeMenuClient.h"
#include "tests/FinishLevelFixture.h"
TL_ORIGINAL(void,lcChampion,(CCharacter*,const std::wstring&,int,std::wstring),"_ZN10CCharacter12makeChampionERKSbIwSt11char_traitsIwESaIwEEiS3_")
TL_ORIGINAL(void,lcLevel,(CCharacter*,unsigned,bool),"_ZN10CCharacter8setLevelEjb")
extern "C" void lcNewChampion(CCharacter*,const std::wstring&,int,std::wstring) __asm__("_ZN10CCharacter12makeChampionERKSbIwSt11char_traitsIwESaIwEEiS3_");
extern "C" void lcNewLevel(CCharacter*,unsigned,bool) __asm__("_ZN10CCharacter8setLevelEjb");
TL_FUNCTION(lcFind,"_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(lcValue,"_ZNK6CGraph8getValueEfj")
TL_FUNCTION(lcRandom,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(lcISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(lcTheme,"_ZN9CBaseUnit12addUnitThemeERKSbIwSt11char_traitsIwESaIwEE")
namespace{
#include "CharacterEmptyGlobals.h"
struct Case{unsigned seed,op,control;};unsigned seed,mode,variant;bool armed;autotest::Capture*out;nativegame::Services*services;finishlevel::Fixture*world;CCharacter*self;CGraph*graph;
void num(unsigned n){if(armed)out->add(&n,4);}void fp(float n){if(armed)out->add(&n,4);}void wide(const std::wstring&s){num(s.size());if(armed)out->add(s.data(),s.size()*4);}
class Actor:public CCharacter{public:Actor():CCharacter(NULL){}virtual void setScale(float scale){num(101);fp(scale);m_vScale=Ogre::Vector3(scale,scale,scale);}virtual void calculateMaxMana(){num(103);m_maxManaBase=32+variant;}};
CGraph*find(CGraphManager*p,const std::wstring&name){num(107);num(p==CGraphManager::getSingleton());wide(name);graph->m_sName=name;return graph;}
float value(const CGraph*p,float x,unsigned line){num(109);num(p==graph);fp(x);num(line);wide(p->m_sName);float base=p->m_sName.find(L"HEALTH")!=std::wstring::npos?120.25f:p->m_sName.find(L"ARMOR")!=std::wstring::npos?40.5f:30.75f;return base+x*.75f;}
float random(float a,float b){num(113);fp(a);fp(b);return variant%3==0?a:variant%3==1?b:a+(b-a)*.5f;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){num(127);num(p==self);num(t);return mode==2||mode==3;}
void theme(CBaseUnit*p,const std::wstring&name){num(131);num(p==self);wide(name);}
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;mode=seed%32;variant=seed/32;out=&capture;armed=false;menugui::Client client(*services->master->m_pSettings,services->master,*services->master->m_pSoundManager);client.client->m_startDifficulty=variant%4;world->resources.m_GameClients.clear();world->resources.m_GameClients.add(client.client);self=new Actor;self->m_pResourceManager=&world->resources;self->m_iUnitLevel=mode==0?11:3;self->m_champion=mode==1;self->m_characterDisplayName=L"old";self->m_bravery=-7;self->m_vScale=Ogre::Vector3(1,2,1.25f);self->m_experienceReward=mode==4?0:5;self->m_maxManaBase=-3;self->m_fameReward=17;self->m_maxHPBase=11;self->m_fHPFloat=12;self->m_fManaFloat=13;self->m_naturalArmor=99;for(unsigned i=0;i<7;++i)self->m_damageDefense[i]=50+i;float range[]={.25f,.75f};std::memcpy(self->m_Padding4D0+4,range,8);self->m_value6D0=99;
 CDataGroup*data=new CDataGroup(L"unit",NULL,32,32,new TRepository<std::wstring>(L""));self->m_pDataGroup=data;data->AddDataValue(L"UNIQUENAME",bool(variant&1));float low=mode==5?0:mode==6?.01f:mode==7?std::numeric_limits<float>::quiet_NaN():mode==8?200:60;float high=mode==5?0:mode==6?.02f:mode==9?std::numeric_limits<float>::quiet_NaN():mode==8?10:140;data->AddDataValue(L"MINHP",low);data->AddDataValue(L"MAXHP",high);data->AddDataValue(L"XP",static_cast<unsigned>(mode==4?0:5));data->AddDataValue(L"ARMOR",static_cast<unsigned>(mode==10?0:50));data->AddDataValue(L"MINDAMAGE",static_cast<unsigned>(20));data->AddDataValue(L"MAXDAMAGE",static_cast<unsigned>(mode==11?0:70));data->AddDataValue(L"NO_UNARMED_ATTACKS",bool(variant&2));data->AddDataValue(L"SET_HP_PCT",mode==12?-.5f:mode==13?2.0f:mode==14?std::numeric_limits<float>::quiet_NaN():.75f);if(mode==15){data->AddDataValue(L"HEALTH_GRAPH",L"health_custom",false);data->AddDataValue(L"ARMOR_GRAPH",L"armor_custom",false);data->AddDataValue(L"DAMAGE_GRAPH",L"damage_custom",false);}
 for(unsigned i=0;i<7;++i){std::wstring name=STRINGS::StringUpper(gDAMAGE_TYPES[i]);if((seed+i)%3){data->AddDataValue(L"ARMOR_"+name,static_cast<unsigned>(20+i));data->AddDataValue(L"DAMAGE_"+name,static_cast<unsigned>(15+i));}}
 if(variant&4){CAttackDescription*a=new CAttackDescription("existing",false,1,2,3,4,5,.75f);int span[]={77,88};std::memcpy(a->m_AttackData5C,span,8);self->m_attacks.push_back(a);}graph=new CGraph(GRAPH_LINEAR,L"probe",1);
 detour::Set patches;TL_REDIRECT(patches,lcFind,&find);TL_REDIRECT(patches,lcValue,&value);TL_REDIRECT(patches,lcRandom,&random);TL_REDIRECT(patches,lcISA,&isa);TL_REDIRECT(patches,lcTheme,&theme);if(patches.failed())_exit(43);armed=true;
 if(c.op==0){typedef void(*F)(CCharacter*,const std::wstring&,int,std::wstring);F f=ours?lcNewChampion:lcChampion;if(!autotest::beginInvocation(capture,f))return;f(self,L"Champion Ж",42,variant&2?L"THEME":L"");}else{typedef void(*F)(CCharacter*,unsigned,bool);F f=ours?lcNewLevel:lcLevel;if(!autotest::beginInvocation(capture,f))return;f(self,11,mode!=3);}capture.callCompleted=1;if(ours&&c.control)self->m_naturalArmor+=1;num(self->m_iUnitLevel);num(self->m_champion);wide(self->m_characterDisplayName);fp(self->m_bravery);fp(self->m_vScale.x);fp(self->m_vScale.y);fp(self->m_vScale.z);num(self->m_experienceReward);num(self->m_fameReward);num(self->m_maxHPBase);fp(self->m_fHPFloat);num(self->m_maxManaBase);fp(self->m_fManaFloat);num(self->m_naturalArmor);for(unsigned i=0;i<7;++i)num(self->m_damageDefense[i]);num(self->m_value6D0);num(self->m_attackFlag1F5);num(self->m_attacks.size());for(unsigned i=0;i<self->m_attacks.size();++i){CAttackDescription*a=self->m_attacks[i];for(unsigned j=0;j<7;++j){num(a->m_DamageMinimums[j]);num(a->m_DamageMaximums[j]);}int values[2];std::memcpy(values,a->m_AttackData5C,8);num(values[0]);num(values[1]);fp(a->m_fRange);fp(a->m_fStrikeRange);}armed=false;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned op){initEmptyGlobals();const wchar_t*labels[]={L"Physical",L"Magical",L"Fire",L"Ice",L"Electric",L"Poison",L"All"};for(unsigned i=0;i<7;++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x147cb00+i*8),8);if(!p)new(reinterpret_cast<void*>(0x147cb00+i*8))std::wstring(labels[i]);}nativegame::Services native;if(!native.ready())return 1;services=&native;menugui::Audio audio(native.master);finishlevel::Fixture level;world=&level;const char*name=op?"character_set_level_runtime":"character_make_champion_runtime";autotest::Coverage coverage(name,op?0x83ead0:0x851590);int failures=0;for(unsigned i=0;i<512;++i){Case c={i,op,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    level/champion op%u seed%u status%d/%d bytes%lu/%lu\n",op,i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j+3<a.capture.length&&j+3<b.capture.length;j+=4){unsigned x,y;std::memcpy(&x,a.capture.data+j,4);std::memcpy(&y,b.capture.data+j,4);if(x!=y){host->log("    word%u %08x/%08x\n",j/4,x,y);if(j>512)break;}}coverage.report(host);return failures;}}coverage.report(host);Case c={31,op,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    level/champion negative detected%u\n",unsigned(caught));return failures;}
}
TL_TEST(character_make_champion_runtime){return run(host,0);}
TL_TEST(character_set_level_runtime){return run(host,1);}
