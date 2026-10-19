#include <cstring>
#include <clocale>
#include <execinfo.h>
#include <fcntl.h>
#include <ucontext.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "Equipment.h"
#include "Skill.h"
#include "SkillManager.h"
#include "EffectManager.h"
#include "Inventory.h"
#include "GenericModel.h"
#include "Wardrobe.h"
#include "WeaponTrail.h"
#include "DataGroup.h"
#include "TRepository.h"
#include "FileSystem.h"
#undef private
#undef protected
#include "NativeMenuServices.h"
namespace {
#include "CharacterEmptyGlobals.h"
}
TL_ORIGINAL(void,ceOldOff,(CCharacter*,CEquipment*),"_ZN10CCharacter19equipmentUnequippedEP10CEquipment")
TL_ORIGINAL(void,ceOldOn,(CCharacter*,CEquipment*),"_ZN10CCharacter17equipmentEquippedEP10CEquipment")
extern "C" void ceNewOff(CCharacter*,CEquipment*) __asm__("_ZN10CCharacter19equipmentUnequippedEP10CEquipment");
extern "C" void ceNewOn(CCharacter*,CEquipment*) __asm__("_ZN10CCharacter17equipmentEquippedEP10CEquipment");
TL_FUNCTION(ceFiles,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(ceWardrobe,"_ZN9CWardrobe6updateEP10CInventory")
TL_FUNCTION(ceISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(ceWardrobed,"_ZN10CEquipment11isWardrobedESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ceBones,"_ZN10CCharacter8getBonesEv")
TL_FUNCTION(ceGet,"_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(ceDelete,"_ZN13CSkillManager19deleteSpecificSkillEP6CSkill")
TL_FUNCTION(ceLevel,"_ZN13CSkillManager13setSkillLevelEP6CSkillj")
TL_FUNCTION(cePassive,"_ZN13CSkillManager18startPassiveSkillsEP9CBaseUnitRKN4Ogre7Vector3ERKNS2_10QuaternionES5_")
TL_FUNCTION(ceAdd,"_ZN9CBaseUnit14addSkillByNameERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(ceEffects,"_ZN14CEffectManager21calculateEffectValuesEv")
TL_FUNCTION(ceOpacity,"_ZN10CCharacter13updateOpacityEfb")
TL_FUNCTION(ceBehind,"_ZN10CCharacter15setRenderBehindEb")
TL_FUNCTION(ceAlignment,"_ZN10CCharacter9alignmentEv")
TL_FUNCTION(ceSetAlignment,"_ZN10CCharacter12setAlignmentE10EAlignment")
TL_FUNCTION(ceTrailActive,"_ZN12CWeaponTrail9setActiveEb")
TL_FUNCTION(ceTrailVisible,"_ZN12CWeaponTrail10setVisibleEb")
namespace {
struct Case{unsigned op,seed,control;};unsigned op,seed,phase,calls;bool armed,oursSide;autotest::Capture*out;nativegame::Services*services;CCharacter*self;CEquipment*equipment,*other;CSkillManager*manager;CSkill*skills[4];CWeaponTrail*trails[2];
void fault(int signal,siginfo_t*info,void*context){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/character/character-equipment-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);if(fd>=0){char line[200];ucontext_t*uc=static_cast<ucontext_t*>(context);int n=std::snprintf(line,sizeof(line),"signal%d side%u op%u seed%u phase%u rip%llx address%p\n",signal,unsigned(oursSide),op,seed,phase,(unsigned long long)uc->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,line,n);void*stack[40];int count=backtrace(stack,40);backtrace_symbols_fd(stack,count,fd);close(fd);}raise(signal);}
void num(unsigned x){if(armed)out->add(&x,4);}void fp(float x){if(armed)out->add(&x,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void wide(const std::wstring&s){num(s.size());if(armed)out->add(s.data(),s.size()*sizeof(wchar_t));}unsigned id(const void*p){if(!p)return 0;if(p==self)return 1;if(p==equipment)return 2;if(p==other)return 3;if(p==manager)return 4;for(unsigned i=0;i<4;++i)if(p==skills[i])return 10+i;return 99;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){num(101);num(id(p));num(type);if(type==static_cast<UNITTYPES::EUNITTYPES>(8))return(seed/3)%2;if(type==static_cast<UNITTYPES::EUNITTYPES>(12))return(seed/5)%2;return(seed/7)%2;}
bool wardrobed(CEquipment*p,std::wstring name){num(103);num(id(p));wide(name);return seed%3==0;}
void wardrobe(CWardrobe*p,CInventory*i){num(107);num(p==self->m_wardrobe);num(i==self->m_pInventory);}
bool file(CFileSystem*,const std::wstring&,CFileInfo&info,bool,bool,bool){info.m_bExists=false;return false;}
void bones(CCharacter*p){num(109);num(id(p));}
CSkill*get(CSkillManager*p,const std::wstring&name,int level){num(113);num(id(p));wide(name);num(level);return(seed+calls++)%3==0?NULL:skills[(calls-1)%4];}
CSkill*add(CBaseUnit*p,const std::wstring&name,bool flag){num(127);num(id(p));wide(name);num(flag);return(seed+calls++)%3==0?NULL:skills[(calls-1)%4];}
void deleted(CSkillManager*p,CSkill*s){num(131);num(id(p));num(id(s));}
void level(CSkillManager*p,CSkill*s,unsigned value){num(137);num(id(p));num(id(s));num(value);s->m_skillLevel=value;}
void passive(CSkillManager*p,CBaseUnit*unit,const Ogre::Vector3&position,const Ogre::Quaternion&orientation,const Ogre::Vector3&target){num(139);num(id(p));num(id(unit));vec(position);fp(orientation.w);fp(orientation.x);fp(orientation.y);fp(orientation.z);vec(target);}
void effects(CEffectManager*p){num(149);num(p==self->m_pEffectManager);}
void opacity(CCharacter*p,float elapsed,bool force){num(151);num(id(p));fp(elapsed);num(force);}
void behind(CCharacter*p,bool flag){num(157);num(id(p));num(flag);}
EAlignment alignment(CCharacter*p){num(163);num(id(p));return static_cast<EAlignment>(seed%7);}
void setAlignment(CCharacter*p,EAlignment value){num(167);num(id(p));num(value);p->m_alignment=value;}
void trailActive(CWeaponTrail*p,bool value){num(173);num(p==trails[0]?1:p==trails[1]?2:99);num(value);p->m_active=value;}
void trailVisible(CWeaponTrail*p,bool value){num(179);num(p==trails[0]?1:p==trails[1]?2:99);num(value);}
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);op=c.op;seed=c.seed;phase=1;oursSide=ours;armed=false;out=&capture;calls=0;struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_sigaction=&fault;action.sa_flags=SA_SIGINFO|SA_RESETHAND;sigemptyset(&action.sa_mask);sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);
 self=new CCharacter(NULL);equipment=new CEquipment(NULL);other=new CEquipment(NULL);self->m_vPosition=Ogre::Vector3(seed*.25f,-2,3);self->m_vRight=Ogre::Vector3::UNIT_X;self->m_vUp=Ogre::Vector3::UNIT_Y;self->m_vForward=Ogre::Vector3::UNIT_Z;self->m_Padding4A1[0]=seed&1;self->m_attackItem=seed%3==0?equipment:seed%3==1?other:NULL;self->m_pInventory=seed&2?new CInventory(self,17):NULL;
 manager=new CSkillManager(NULL,self);self->m_pSkillManager=manager;for(unsigned i=0;i<4;++i){skills[i]=new CSkill(NULL,NULL);skills[i]->m_Guid=100+i;skills[i]->m_iColumn=7;skills[i]->m_iCharges=19;skills[i]->m_skillLevel=13;}
 self->m_activeSkill=seed&4?skills[0]:NULL;self->m_previousSkill=seed&8?skills[1]:NULL;self->m_activeSkillGuid=100+seed%5;self->m_leftSkillGuid=100+(seed/3)%5;self->m_leftMouseSkillGuid=100+(seed/7)%5;self->m_pEffectManager=seed&16?new CEffectManager(self):NULL;
 CDataGroup*group=new CDataGroup(L"equipment",NULL,4,4,new TRepository<std::wstring>(L""));equipment->m_pDataGroup=group;group->AddDataValue(L"LEVEL",int(seed%7)-2);group->AddDataValue(L"CHARGES",static_cast<unsigned int>(seed%9-4));for(unsigned i=0;i<seed%5;++i){CDataGroup*g=group->AddDataGroup(L"SKILL_TO_GIVE");if((seed+i)%3)g->AddDataValue(L"NAME",i%2?L"spell Ж":L"",false);if((seed+i)%2)g->AddDataValue(L"LEVEL",int(i)-2);if((seed+i)%4)g->AddDataValue(L"CHARGES",static_cast<int>(i)-2);}
 if(seed&32){CGenericModel*model=new CGenericModel(NULL,services->scene,static_cast<OGRE_UTILITIES::EPRIMITIVES>(0));detour::Set setup;TL_REDIRECT(setup,ceFiles,&file);TL_REDIRECT(setup,ceWardrobe,&wardrobe);if(setup.failed())_exit(43);self->m_wardrobe=new CWardrobe(self,services->scene,services->scene,model,NULL,L"missing.dds",L"",L"",L"",L"",L"");}
 for(unsigned i=0;i<2;++i){trails[i]=NULL;if((seed>>(6+i))&1){trails[i]=new CWeaponTrail(services->scene,i?"callbacktrail1":"callbacktrail0",3,.5f);self->m_weaponTrails[i]=trails[i];}}
 if(seed%5==0)self->m_pSkillManager=NULL;
 detour::Set patches;
#define P(name,fn) TL_REDIRECT(patches,ce##name,&fn)
 P(ISA,isa);P(Wardrobed,wardrobed);P(Wardrobe,wardrobe);P(Bones,bones);P(Get,get);P(Delete,deleted);P(Add,add);P(Level,level);P(Passive,passive);P(Effects,effects);P(Opacity,opacity);P(Behind,behind);P(Alignment,alignment);P(SetAlignment,setAlignment);P(TrailActive,trailActive);P(TrailVisible,trailVisible);
#undef P
 if(patches.failed())_exit(44);phase=100;armed=true;typedef void(*F)(CCharacter*,CEquipment*);F fn=op?(ours?ceNewOn:ceOldOn):(ours?ceNewOff:ceOldOff);if(!autotest::beginInvocation(capture,fn))return;fn(self,seed%13?equipment:NULL);capture.callCompleted=1;phase=101;if(ours&&c.control)self->m_activeSkillGuid^=1;num(id(self->m_attackItem));num(id(self->m_activeSkill));num(id(self->m_previousSkill));if(armed){out->add(&self->m_activeSkillGuid,8);out->add(&self->m_leftSkillGuid,8);out->add(&self->m_leftMouseSkillGuid,8);}num(self->m_alignment);for(unsigned i=0;i<4;++i){num(skills[i]->m_iColumn);num(skills[i]->m_iCharges);num(skills[i]->m_skillLevel);}for(unsigned i=0;i<2;++i)if(trails[i])num(trails[i]->m_active);armed=false;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(character_equipment_callbacks_runtime){std::setlocale(LC_CTYPE,"C.UTF-8");initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;services=&native;int failures=0;uintptr_t addresses[]={(uintptr_t)&ceOldOff,(uintptr_t)&ceOldOn};for(unsigned op=0;op<2;++op){autotest::Coverage coverage("character_equipment_callbacks_runtime",addresses[op]);for(unsigned i=0;i<512;++i){Case c={op,i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    equipment op%u seed%u status%d/%d bytes%lu/%lu\n",op,i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}for(unsigned j=0;j+3<a.capture.length&&j+3<b.capture.length&&j<400;j+=4){unsigned x,y;std::memcpy(&x,a.capture.data+j,4);std::memcpy(&y,b.capture.data+j,4);host->log("    word%u %u/%u\n",j/4,x,y);}coverage.report(host);return failures;}}coverage.report(host);Case c={op,31,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    equipment op%u negative detected%u\n",op,unsigned(caught));}return failures;}
