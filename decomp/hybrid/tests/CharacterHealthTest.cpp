#include <string>
#include <vector>
#include <map>
#include <new>
#include <limits>
#include <CEGUIcolour.h>
#include "SoundBank.h"
#define private public
#define protected public
#include "Character.h"
#include "Effect.h"
#include "EffectManager.h"
#include "Level.h"
#include "LevelTemplateData.h"
#include "GameClient.h"
#include "GameUI.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldDisplay,(CCharacter*,float),"_ZN10CCharacter21displayDamageAbsorbedEf")
extern "C" void newDisplay(CCharacter*,float) __asm__("_ZN10CCharacter21displayDamageAbsorbedEf");
TL_ORIGINAL(void,oldHealth,(CCharacter*,float),"_ZN10CCharacter8modifyHPEf")
extern "C" void newHealth(CCharacter*,float) __asm__("_ZN10CCharacter8modifyHPEf");
TL_ORIGINAL(bool,oldValid,(CCharacter*,CCharacter*,CBaseUnit*,CEffect*),"_ZN10CCharacter20isEffectValidForUnitEPS_P9CBaseUnitP7CEffect")
extern "C" bool newValid(CCharacter*,CCharacter*,CBaseUnit*,CEffect*) __asm__("_ZN10CCharacter20isEffectValidForUnitEPS_P9CBaseUnitP7CEffect");
TL_FUNCTION(ch_isa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(ch_isplayer,"_ZN9CBaseUnit8isPlayerEv")
TL_FUNCTION(ch_alignment,"_ZN10CCharacter9alignmentEv")
TL_FUNCTION(ch_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(ch_text,"_ZN7CGameUI12addTextEventERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_")
TL_FUNCTION(ch_theme,"_ZN9CBaseUnit12hasUnitThemeEP10CUnitTheme")
TL_FUNCTION(ch_maxhp,"_ZN10CCharacter5maxHPEv")
TL_FUNCTION(ch_hp,"_ZN10CCharacter2HPEv")
TL_FUNCTION(ch_mana,"_ZN10CCharacter4manaEv")
TL_FUNCTION(ch_maxmana,"_ZN10CCharacter7maxManaEv")
TL_FUNCTION(ch_threshold,"_ZN9CBaseUnit27broadcastHPThreshholdEventsEffff")
TL_FUNCTION(ch_force,"_ZN10CCharacter28forceDisplayOfDamageAbsorbedEv")
TL_FUNCTION(ch_value,"_ZN7CEffect5valueE14EEFFECT_VALUES")
TL_FUNCTION(ch_full,"_ZN9CBaseUnit13dontUseOnFullEv")
TL_FUNCTION(ch_learn,"_ZN10CCharacter13canLearnSpellESbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(ch_stat,"_ZN10CCharacter25incrementJournalStatisticE17EJournalStatistici")
TL_FUNCTION(ch_sound,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(ch_has,"_ZN14CEffectManager9hasEffectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ch_remove,"_ZN14CEffectManager12removeEffectERKSbIwSt11char_traitsIwESaIwEEb")
namespace {
struct Case{unsigned op,index;};struct State{Case c;autotest::Capture*out;CCharacter*self,*master;CBaseUnit*target;CEffect*effect;CLevel*level;CGameUI*ui;CSoundBank*sound,*masterSound;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned v){active->out->add(&v,4);}void fp(float v){active->out->add(&v,4);}void wide(const std::wstring&s){num(s.size());active->out->add(s.data(),s.size()*4);}unsigned id(CBaseUnit*p){return p==active->self?1:p==active->master?2:p==active->target?3:p==NULL?0:99;}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}float val(unsigned n){const float vs[]={-100,-1,-0.0f,0,.125f,.2f,.5f,1,2,20,21,100,101,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity()};return vs[hash(n)%16];}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){num(1);num(id(p));num(type);return (hash(10+id(p)+unsigned(type))&1)!=0;}bool player(CBaseUnit*p){num(2);num(id(p));return hash(20+id(p))&1;}EAlignment alignment(CCharacter*){num(3);return static_cast<EAlignment>(hash(21)%4);}Ogre::Vector3 position(CPositionableObject*,bool absolute){num(4);num(absolute);return Ogre::Vector3(3.5f,-2.f,.25f);}void text(CGameUI*p,const Ogre::Vector3&v,const std::string&t,float a,float b,CEGUI::colour first,CEGUI::colour second){num(5);num(p==active->ui);vec(v);num(t.size());active->out->add(t.data(),t.size());fp(a);fp(b);fp(first.getRed());fp(first.getGreen());fp(first.getBlue());fp(first.getAlpha());fp(second.getRed());fp(second.getGreen());fp(second.getBlue());fp(second.getAlpha());}
bool theme(CBaseUnit*p,const std::wstring&s){num(6);num(id(p));wide(s);return hash(22)%3==0;}int maxHP(CCharacter*){num(7);return int(hash(23)%8)*20-20;}int hp(CCharacter*){num(8);return int(hash(24)%8)*20-20;}int mana(CCharacter*){num(9);return int(hash(25)%8)*20-20;}int maxMana(CCharacter*){num(10);return int(hash(26)%8)*20-20;}void threshold(CBaseUnit*,float a,float b,float c,float d){num(11);fp(a);fp(b);fp(c);fp(d);}void force(CCharacter*p){num(12);p->m_damageDisplayTime=-10000;}float value(CEffect*p,EEFFECT_VALUES n){num(13);num(p==active->effect);num(n);return val(27);}bool full(CBaseUnit*p){num(14);num(id(p));return hash(28)&1;}bool learn(CCharacter*,std::wstring s,int v){num(15);wide(s);num(v);return hash(29)&1;}void journal(CCharacter*,EJournalStatistic n,int v){num(16);num(n);num(v);}void sound(CSoundBank*p,int index,float a,float b){num(17);num(p==active->sound?1:p==active->masterSound?2:99);num(index);fp(a);fp(b);}bool has(CEffectManager*,const std::wstring&s){num(18);wide(s);return hash(30)&1;}bool removeEffect(CEffectManager*,const std::wstring&s,bool b){num(19);wide(s);num(b);return true;}bool god(CCharacter*){num(20);return hash(31)%4==0;}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;std::memset(&s,0,sizeof s);active=&s;s.c=c;s.out=&out;s.self=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.master=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.target=static_cast<CBaseUnit*>(autotest::allocate(sizeof(CBaseUnit)));s.effect=static_cast<CEffect*>(autotest::allocate(sizeof(CEffect)));s.level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));s.ui=static_cast<CGameUI*>(autotest::allocate(sizeof(CGameUI)));s.sound=static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank)));s.masterSound=static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank)));CResourceManager*r=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));CGameClient*g=static_cast<CGameClient*>(autotest::allocate(sizeof(CGameClient)));CLevelTemplateData*t=static_cast<CLevelTemplateData*>(autotest::allocate(sizeof(CLevelTemplateData)));r->m_pLevel=s.level;s.level->m_pGameClient=g;g->m_pGameUI=s.ui;s.level->m_pLevelTemplateData=hash(32)%4?t:NULL;t->m_permitsPortal=hash(33)&1;t->m_isTown=hash(34)&1;s.self->m_pResourceManager=r;s.self->m_pMaster=hash(35)%3?s.master:NULL;s.self->m_levelSound=hash(36)&1?s.sound:NULL;s.master->m_levelSound=hash(37)&1?s.masterSound:NULL;new(&s.master->m_Followers)std::vector<CCharacter*>;if(hash(38)%3)s.master->m_Followers.push_back(hash(39)&1?s.self:s.master);s.self->m_pEffectManager=hash(40)%3?static_cast<CEffectManager*>(autotest::allocate(sizeof(CEffectManager))):NULL;s.self->m_eAIState=static_cast<EAIState>(hash(41)%8);s.self->m_alignment=static_cast<EAlignment>(hash(42)%4);s.self->m_characterFlag52F=hash(43)&1;s.self->m_bInvulnerable=hash(44)&1;s.self->m_damageDisplayEnabled=hash(45)&1;s.self->m_damageDisplayTime=val(46);s.self->m_damageOverTimeTaken=val(47);s.self->m_fHPFloat=val(48);s.self->m_maxHPBase=int(hash(49)%300)-50;s.self->m_previousThresholdHP=val(50);s.self->m_experienceReward=123;new(&s.effect->m_sName)std::wstring(hash(51)&1?L"Effect Ж":L"");s.effect->m_eType=static_cast<EEFFECT_TYPE>(c.index%147);s.effect->m_activation=static_cast<EEFFECT_ACTIVATION>(hash(52)%5);void**v=static_cast<void**>(autotest::allocate(0x300));v[0x290/8]=reinterpret_cast<void*>(&god);*reinterpret_cast<void***>(s.self)=v;
if(c.op==0){typedef void(*F)(CCharacter*,float);F f=ours?newDisplay:oldDisplay;if(!autotest::beginInvocation(out,f))return;f(s.self,val(53));out.callCompleted=1;fp(s.self->m_damageDisplayTime);fp(s.self->m_damageOverTimeTaken);}
else if(c.op==1){typedef void(*F)(CCharacter*,float);F f=ours?newHealth:oldHealth;if(!autotest::beginInvocation(out,f))return;f(s.self,val(54));out.callCompleted=1;fp(s.self->m_fHPFloat);fp(s.self->m_previousThresholdHP);fp(s.self->m_damageDisplayTime);num(s.self->m_experienceReward);}
else{if(hash(55)%5==0)r->m_pLevel=NULL;typedef bool(*F)(CCharacter*,CCharacter*,CBaseUnit*,CEffect*);F f=ours?newValid:oldValid;if(!autotest::beginInvocation(out,f))return;num(f(s.self,s.master,hash(56)%3?s.target:NULL,hash(57)%11?s.effect:NULL));out.callCompleted=1;}
s.effect->m_sName.~basic_string();s.master->m_Followers.~vector();}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
int run(const tlhybrid_host*host,unsigned op,unsigned count,const char*name,unsigned address){detour::Set h;TL_REDIRECT(h,ch_isa,&isa);TL_REDIRECT(h,ch_isplayer,&player);TL_REDIRECT(h,ch_alignment,&alignment);TL_REDIRECT(h,ch_position,&position);TL_REDIRECT(h,ch_text,&text);TL_REDIRECT(h,ch_theme,&theme);TL_REDIRECT(h,ch_maxhp,&maxHP);TL_REDIRECT(h,ch_hp,&hp);TL_REDIRECT(h,ch_mana,&mana);TL_REDIRECT(h,ch_maxmana,&maxMana);TL_REDIRECT(h,ch_threshold,&threshold);TL_REDIRECT(h,ch_force,&force);TL_REDIRECT(h,ch_value,&value);TL_REDIRECT(h,ch_full,&full);TL_REDIRECT(h,ch_learn,&learn);TL_REDIRECT(h,ch_stat,&journal);TL_REDIRECT(h,ch_sound,&sound);TL_REDIRECT(h,ch_has,&has);TL_REDIRECT(h,ch_remove,&removeEffect);if(h.failed())return 1;autotest::Coverage coverage(name,address);for(unsigned i=0;i<count;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    health op%u seed%u status%d/%d bytes%lu/%lu started%u/%u done%u/%u\n",op,i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length,a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+4*k,4);std::memcpy(&y,b.capture.data+4*k,4);if(x!=y){host->log("    word%u %08x/%08x\n",k,x,y);for(unsigned z=0;z*4<a.capture.length&&z*4<b.capture.length&&z<36;++z){unsigned aa,bb;std::memcpy(&aa,a.capture.data+4*z,4);std::memcpy(&bb,b.capture.data+4*z,4);host->log("    dump%u %08x/%08x\n",z,aa,bb);}break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=count||coverage.different||coverage.missing;}
}
TL_TEST(character_combat_damage_display){return run(host,0,4096,"character_combat_damage_display",0x810370);}
TL_TEST(character_combat_modify_hp){return run(host,1,8192,"character_combat_modify_hp",0x838a50);}
TL_TEST(character_combat_valid_effect){return run(host,2,16384,"character_combat_valid_effect",0x813f20);}
