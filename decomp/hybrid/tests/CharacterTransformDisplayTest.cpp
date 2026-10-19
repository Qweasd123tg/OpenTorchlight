#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "Equipment.h"
#include "Inventory.h"
#include "SkillManager.h"
#include "Skill.h"
#include "DataGroup.h"
#include "TRepository.h"
#include "UnitResourceList.h"
#include "Particle.h"
#include "AttackDescription.h"
#include "GameClient.h"
#undef private
#undef protected
#include "NativeMenuClient.h"
#include "tests/FinishLevelFixture.h"
#include "CharacterEmptyGlobals.h"

TL_ORIGINAL(void,tNativeCtor,(CCharacter*,CResourceManager*),"_ZN10CCharacterC1EP16CResourceManager")
TL_ORIGINAL(void,tOldRevert,(CCharacter*),"_ZN10CCharacter20revertTransformationEv")
TL_ORIGINAL(void,tOldConvert,(CCharacter*,std::wstring,bool),"_ZN10CCharacter16convertCharacterESbIwSt11char_traitsIwESaIwEEb")
TL_ORIGINAL(int,tOldDisplay,(CCharacter*,bool,bool,bool),"_ZN10CCharacter23maximumDamageForDisplayEbbb")
extern "C" void tNewRevert(CCharacter*) __asm__("_ZN10CCharacter20revertTransformationEv");
extern "C" void tNewConvert(CCharacter*,std::wstring,bool) __asm__("_ZN10CCharacter16convertCharacterESbIwSt11char_traitsIwESaIwEEb");
extern "C" int tNewDisplay(CCharacter*,bool,bool,bool) __asm__("_ZN10CCharacter23maximumDamageForDisplayEbbb");
TL_FUNCTION(tMasterList,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(tByGuid,"_ZN17CUnitResourceList18getDataGroupByGuidEx")
TL_FUNCTION(tByName,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(tGroups,"_ZN10CDataGroup25GetDataGroupsMatchingNameERKSbIwSt11char_traitsIwESaIwEEPSt6vectorIPS_SaIS7_EE")
TL_FUNCTION(tWide,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(tInt,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(tSkill,"_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(tDeleteSkill,"_ZN13CSkillManager19deleteSpecificSkillEP6CSkill")
TL_FUNCTION(tCleanup,"_ZN10CCharacter22deleteUnitSpecificDataEv")
TL_FUNCTION(tUnitInit,"_ZN10CCharacter8unitInitEP10CDataGroupb")
TL_FUNCTION(tAlignment,"_ZN10CCharacter9alignmentEv")
TL_FUNCTION(tSetAlignment,"_ZN10CCharacter12setAlignmentE10EAlignment")
TL_FUNCTION(tVisible,"_ZN10CCharacter10setVisibleEbb")
TL_FUNCTION(tPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(tSetPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(tStart,"_ZN9CParticle5StartEv")
TL_FUNCTION(tEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(tStored,"_ZN11CGameClient16storedUnitExistsEx")
TL_FUNCTION(tRight,"_ZN10CCharacter20getWeaponInRightHandEv")
TL_FUNCTION(tLeft,"_ZN10CCharacter19getWeaponInLeftHandEv")
TL_FUNCTION(tRemove,"_ZN10CInventory15removeEquipmentEP10CEquipment")
TL_FUNCTION(tSelect,"_ZN10CCharacter12selectAttackE18EATTACK_RANGE_TYPE")
TL_FUNCTION(tEquipped,"_ZN10CInventory22getEquipmentEquippedAtE16EEQUIP_LOCATIONS")
TL_FUNCTION(tISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(tEffect,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(tStrength,"_ZN10CCharacter8strengthEv")
TL_FUNCTION(tDexterity,"_ZN10CCharacter9dexterityEv")
TL_FUNCTION(tMagic,"_ZN10CCharacter5magicEv")
TL_FUNCTION(tDamage,"_ZN10CEquipment13maximumDamageEv")

namespace {
struct Case { unsigned op,seed,control; };
unsigned seed,operation,skillCalls,deleted;
bool armed;
autotest::Capture* output;
finishlevel::Fixture* world;
CUnitResourceList* resourceList;
menugui::Client* client;
CCharacter* self;
CCharacter* master;
CEquipment* equipment[2];
CSkill* skills[3];
CDataGroup* groups[5];
CParticle* particle;
CAttackDescription* attack;

void number(unsigned value){if(armed)output->add(&value,sizeof(value));}
void integer(long long value){if(armed)output->add(&value,sizeof(value));}
void real(float value){if(armed)output->add(&value,sizeof(value));}
void wide(const std::wstring& value){number(value.size());if(armed)output->add(value.data(),value.size()*sizeof(wchar_t));}
void vector(const Ogre::Vector3& value){real(value.x);real(value.y);real(value.z);}
unsigned id(const void* p){if(!p)return 0;if(p==self)return 1;if(p==master)return 2;if(p==particle)return 3;if(p==attack)return 4;for(unsigned i=0;i<2;++i)if(p==equipment[i])return 10+i;for(unsigned i=0;i<3;++i)if(p==skills[i])return 20+i;for(unsigned i=0;i<5;++i)if(p==groups[i])return 30+i;return 99;}
void references(){integer(self->m_activeSkillGuid);integer(self->m_leftSkillGuid);integer(self->m_leftMouseSkillGuid);number(id(self->m_activeSkill));number(id(self->m_previousSkill));}
void loadState(){real(self->m_transformationTime);integer(self->m_originalUnitGuid);wide(self->m_characterDisplayName);number(self->m_alignment);references();}
CCharacter* character(){CCharacter*p=static_cast<CCharacter*>(Ogre::NedAllocImpl::allocBytes(sizeof(CCharacter),0,0,0));tNativeCtor(p,NULL);return p;}
CUnitResourceList* list(CResourceManager*p){number(101);number(p==&world->resources);return resourceList;}
CDataGroup* byGuid(CUnitResourceList*p,long long guid){number(103);number(p==resourceList);integer(guid);return seed%5?groups[1]:NULL;}
CDataGroup* byName(CUnitResourceList*p,const std::wstring& category,const std::wstring& name){number(107);number(p==resourceList);wide(category);wide(name);return category==L"MONSTERS"?(seed%3==0?groups[1]:NULL):(seed%3==1?groups[1]:NULL);}
unsigned matching(CDataGroup*p,const std::wstring&name,std::vector<CDataGroup*>* result){number(109);number(id(p));wide(name);unsigned n=(seed/5)%4;for(unsigned i=0;i<n;++i)result->push_back(groups[2+i]);return n;}
const std::wstring& text(CDataGroup*p,const std::wstring&name,const std::wstring& fallback){number(113);number(id(p));wide(name);wide(fallback);static std::wstring result;result=(id(p)%2)?L"skill Ж":L"";return result;}
int dataInt(CDataGroup*p,const std::wstring&name,int fallback){number(127);number(id(p));wide(name);number(fallback);return p==groups[0]?int(seed%9)-3:int((seed+id(p))%7)-2;}
CSkill* getSkill(CSkillManager*p,const std::wstring&name,int level){number(131);number(p==self->m_pSkillManager);wide(name);number(level);unsigned i=skillCalls++%3;return (seed+i)%5?skills[i]:NULL;}
void deleteSkill(CSkillManager*p,CSkill*s){number(137);number(p==self->m_pSkillManager);number(id(s));references();++deleted;}
void cleanup(CCharacter*p){number(139);number(id(p));loadState();p->m_pUnitModel=NULL;}
void unitInit(CCharacter*p,CDataGroup*group,bool initialize){number(149);number(id(p));number(id(group));number(initialize);p->m_pDataGroup=group;p->m_characterDisplayName=L"reinitialized";p->m_alignment=static_cast<EAlignment>(0);}
EAlignment alignment(CCharacter*p){number(151);number(id(p));return static_cast<EAlignment>((seed/3)%8);}
void setAlignment(CCharacter*p,EAlignment value){number(157);number(id(p));number(value);p->m_alignment=value;}
void visible(CCharacter*p,bool value,bool recursive){number(163);number(id(p));number(value);number(recursive);loadState();p->m_bVisible=value;}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){number(167);number(id(p));number(absolute);return p->m_vPosition;}
void setPosition(CPositionableObject*p,const Ogre::Vector3&value){number(173);number(id(p));vector(value);p->m_vPosition=value;}
void start(CParticle*p){number(179);number(id(p));}
bool editor(CResourceManager*p){number(181);number(p==&world->resources);return (seed/7)%3==0;}
bool stored(CGameClient*p,long long guid){number(191);number(p==client->client);integer(guid);return (seed/11)%2;}
CEquipment* right(CCharacter*p){number(193);number(id(p));return seed%3?equipment[0]:NULL;}
CEquipment* left(CCharacter*p){number(197);number(id(p));return (seed/3)%3?equipment[1]:NULL;}
long long remove(CInventory*p,CEquipment*e){number(199);number(p==self->m_pInventory);number(id(e));return 0;}
class Equipment : public CEquipment {
public: Equipment():CEquipment(NULL){} virtual ~Equipment(){number(211);number(id(this));}
};
void select(CCharacter*p,EATTACK_RANGE_TYPE type){number(223);number(id(p));number(type);p->m_attack=seed%7?attack:NULL;}
CEquipment* equipped(CInventory*p,EEQUIP_LOCATIONS slot){number(227);number(p==self->m_pInventory);number(slot);return (seed/(unsigned(slot)+2))%3?equipment[unsigned(slot)%2]:NULL;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){number(229);number(id(p));number(type);unsigned k=p==equipment[1]?1:0;switch(unsigned(type)){case 35:return (seed/3+k)%2;case 8:return (seed/5+k)%3!=0;case 21:return (seed/7+k)%3==0;case 162:return (seed/11+k)%4==0;case 163:return (seed/13+k)%4==0;case 164:return (seed/17+k)%4==0;default:return false;}}
float effect(CCharacter*p,EEFFECT_TYPE type,EDAMAGE_TYPES damage){number(233);number(id(p));number(type);number(damage);const float values[]={-120.25f,-100,-10,-.01f,0,.001f,.1f,.9f,1,2.25f,13.4f,101};return values[(seed*7+unsigned(type)*3+unsigned(damage)*5+(p==master?9:0))%12];}
int strength(CCharacter*p){number(239);number(id(p));return int(seed%43)-20;}
int dexterity(CCharacter*p){number(241);number(id(p));return int(seed%67)-30;}
int magic(CCharacter*p){number(251);number(id(p));return int(seed%97)-45;}
int damage(CEquipment*p){number(257);number(id(p));return int((seed*7+id(p))%37)-15;}

void side(void* input,autotest::Capture& capture,bool ours)
{
    Case c=*static_cast<Case*>(input);seed=c.seed;operation=c.op;output=&capture;armed=false;skillCalls=deleted=0;
    self=character();master=character();attack=new CAttackDescription("attack",false,1,2,3,4,5,6);
    for(unsigned i=0;i<2;++i)equipment[i]=new Equipment;
    for(unsigned i=0;i<3;++i){skills[i]=new CSkill(NULL,NULL);skills[i]->m_Guid=100+i;}
    for(unsigned i=0;i<5;++i)groups[i]=new CDataGroup(L"fixture",NULL,2,2,new TRepository<std::wstring>(L""));
    particle=new CParticle(NULL,L"fixture",NULL);resourceList=new CUnitResourceList;
    CSkillManager* manager=new CSkillManager(NULL,self);
    self->m_pResourceManager=&world->resources;self->m_pDataGroup=seed%7?groups[0]:NULL;self->m_pSkillManager=(seed/7)%5?manager:NULL;
    self->m_pInventory=new CInventory(self,17);self->m_pMaster=seed%3?master:NULL;
    self->m_characterDisplayName=seed%2?L"original Ж":L"";self->m_originalUnitGuid=17+seed;self->m_transformationTime=float(seed%11)-3.0f;
    self->m_activeSkillGuid=100+seed%4;self->m_leftSkillGuid=100+(seed/3)%4;self->m_leftMouseSkillGuid=100+(seed/7)%4;
    self->m_activeSkill=seed%4?skills[seed%3]:NULL;self->m_previousSkill=(seed/3)%4?skills[(seed/5)%3]:NULL;
    self->m_alignment=static_cast<EAlignment>(seed%8);self->m_vPosition=Ogre::Vector3(float(int(seed%17)-8),-2.25f,float(seed%7));
    self->m_equipmentParticles[8]=particle;self->m_iUnitLevel=seed%21;self->setGuid(900+seed);self->setOriginalGuid(1900+seed);
    world->level.m_flag258=(seed/3)%3==0;
    self->m_attack=(seed/7)%3?attack:NULL;self->m_attackItem=seed%5?equipment[0]:NULL;
    unsigned originalLevel=(seed/5)%21;std::memcpy(self->m_Padding66C,&originalLevel,sizeof(originalLevel));self->m_iMeleeStat=int(seed%101)-50;
    for(unsigned i=0;i<(seed/11)%3;++i)self->m_attacks.push_back(attack);
    for(unsigned i=0;i<7;++i)attack->m_DamageMaximums[i]=(seed*(i+1))%31;
    for(unsigned i=0;i<2;++i)for(unsigned j=0;j<(seed/3+i)%9;++j){equipment[i]->m_ElementalDamageTypes.push_back(static_cast<EDAMAGE_TYPES>(j%7));equipment[i]->m_ElementalDamageBonuses.push_back(int((seed+j*5)%37)-18);equipment[i]->m_InherentElementalDamage.push_back(int((seed+j*7)%43)-20);}
    detour::Set patches;
#define PATCH(name,fn) TL_REDIRECT(patches,t##name,&fn)
    if(c.op<2){PATCH(MasterList,list);PATCH(ByGuid,byGuid);PATCH(ByName,byName);PATCH(Groups,matching);PATCH(Wide,text);PATCH(Int,dataInt);PATCH(Skill,getSkill);PATCH(DeleteSkill,deleteSkill);PATCH(Cleanup,cleanup);PATCH(UnitInit,unitInit);PATCH(Alignment,alignment);PATCH(SetAlignment,setAlignment);PATCH(Visible,visible);PATCH(Position,position);PATCH(SetPosition,setPosition);PATCH(Start,start);PATCH(Editor,editor);PATCH(Stored,stored);PATCH(Right,right);PATCH(Left,left);PATCH(Remove,remove);}
    else{PATCH(Select,select);PATCH(Equipped,equipped);PATCH(ISA,isa);PATCH(Effect,effect);PATCH(Strength,strength);PATCH(Dexterity,dexterity);PATCH(Magic,magic);PATCH(Damage,damage);}
#undef PATCH
    if(patches.failed())_exit(43);armed=true;
    if(c.op==0){typedef void(*F)(CCharacter*);autotest::invoke(capture,ours?tNewRevert:tOldRevert,self);if(ours&&c.control)self->m_originalUnitGuid=17;}
    else if(c.op==1){typedef void(*F)(CCharacter*,std::wstring,bool);F fn=ours?tNewConvert:tOldConvert;if(!autotest::beginInvocation(capture,fn))return;fn(self,seed%2?L"monster Ж":L"",(seed/3)%2);capture.callCompleted=1;if(ours&&c.control)self->m_characterDisplayName=L"incorrect";}
    else{typedef int(*F)(CCharacter*,bool,bool,bool);F fn=ours?tNewDisplay:tOldDisplay;if(!autotest::beginInvocation(capture,fn))return;int result=fn(self,seed&1,seed&2,seed&4);capture.callCompleted=1;number(result+(ours&&c.control));}
    loadState();number(deleted);number(self->m_bVisible);number(id(self->m_pDataGroup));vector(particle->m_vPosition);armed=false;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned op)
{
    int failures=0;const uintptr_t addresses[]={(uintptr_t)&tOldRevert,(uintptr_t)&tOldConvert,(uintptr_t)&tOldDisplay};autotest::Coverage coverage("character_transform_display",addresses[op]);
    for(unsigned i=0;i<4096;++i){Case c={op,i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    transform op%u seed%u status%d/%d bytes%lu/%lu\n",op,i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}for(unsigned j=640;j<a.capture.length&&j<b.capture.length&&j<760;j+=4){unsigned x,y;std::memcpy(&x,a.capture.data+j,4);std::memcpy(&y,b.capture.data+j,4);host->log("    word%u %08x/%08x\n",j,x,y);}coverage.report(host);return failures;}}
    coverage.report(host);Case c={op,19,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    transform op%u negative detected%u\n",op,unsigned(caught));return failures;
}
}
TL_TEST(character_transform_display)
{
    initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;menugui::Audio ownedAudio(native.master);menugui::Client ownedClient(*native.settings,native.master,*native.master->m_pSoundManager);client=&ownedClient;finishlevel::Fixture ownedLevel;ownedLevel.resources.m_pSceneManager=native.scene;ownedLevel.resources.m_pLevel=&ownedLevel.level;world=&ownedLevel;world->resources.getGameClients()->add(client->client);int failures=0;const char*debug=std::getenv("OTL_CHARACTER_TRANSFORM_OP");for(unsigned op=debug?std::atoi(debug):0;op<3;++op){failures+=run(host,op);if(failures)break;}return failures;
}
