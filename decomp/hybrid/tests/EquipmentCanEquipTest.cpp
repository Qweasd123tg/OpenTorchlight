#include <cstring>
#include <climits>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Character.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool, originalCanEquip, (CEquipment*, CCharacter*, bool), "_ZN10CEquipment8canEquipEP10CCharacterb")
TL_FUNCTION(ceIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(ceLevel,"_ZN10CEquipment19getLevelRequirementEP10CCharacter")
TL_FUNCTION(ceStrength,"_ZN10CCharacter8strengthEv")
TL_FUNCTION(ceDexterity,"_ZN10CCharacter9dexterityEv")
TL_FUNCTION(ceMagic,"_ZN10CCharacter5magicEv")
TL_FUNCTION(ceDefense,"_ZN10CCharacter7defenseEv")
TL_FUNCTION(ceStrengthReq,"_ZN10CEquipment22getStrengthRequirementEP10CCharacter")
TL_FUNCTION(ceDexterityReq,"_ZN10CEquipment23getDexterityRequirementEP10CCharacter")
TL_FUNCTION(ceMagicReq,"_ZN10CEquipment19getMagicRequirementEP10CCharacter")
TL_FUNCTION(ceDefenseReq,"_ZN10CEquipment21getDefenseRequirementEP10CCharacter")
namespace {
typedef char character_size[sizeof(CCharacter)==0x720?1:-1];
typedef char flag_offset[__builtin_offsetof(CCharacter,m_bCharacterFlag4A0)==0x4a0?1:-1];
typedef char level_offset[__builtin_offsetof(CBaseUnit,m_iUnitLevel)==0x100?1:-1];
template<class T> struct Raw { unsigned long long data[(sizeof(T)+7)/8]; Raw(){std::memset(data,0,sizeof(data));} T* get(){return reinterpret_cast<T*>(data);} };
struct Case { unsigned flags, types, trigger, mutation; int level, levelReq[2], stats[4], reqs[4]; };
const Case* input;
CEquipment* item; CCharacter* actor; CCharacter* master;
autotest::Capture* capture; unsigned eventCount, levelCalls;
void number(int n) { capture->add(&n,sizeof(n)); }
void event(int id) {
 number(id); ++eventCount;
 if(eventCount==input->trigger) {
  if(input->mutation==1)actor->m_bCharacterFlag4A0=false;
  if(input->mutation==2)actor->m_bCharacterFlag4A0=true;
  if(input->mutation==3)actor->m_iUnitLevel=static_cast<unsigned>(INT_MIN);
  if(input->mutation==4)item->m_bUnknown348=!item->m_bUnknown348;
 }
}
bool isa(CBaseUnit* p, UNITTYPES::EUNITTYPES type) {
 event(10); number(p==item?0:p==actor?1:p==master?2:3); number(type);
 if(p==actor) return type==UNITTYPES::MERCHANT ? (input->flags&1)!=0 : type==UNITTYPES::STASH && (input->flags&2)!=0;
 if(p==master) return type==UNITTYPES::PLAYER && (input->flags&8)!=0;
 if(p==item) return type==UNITTYPES::WEAPON ? (input->types&1)!=0 : type==UNITTYPES::ARMOR ? (input->types&2)!=0 : type==UNITTYPES::SPELL ? (input->types&4)!=0 : type==UNITTYPES::TRINKET && (input->types&8)!=0;
 return false;
}
int level(CEquipment* p,CCharacter* c) { event(20);number(p==item);number(c==actor); return input->levelReq[(levelCalls++)%2]; }
int stat(CCharacter* c,unsigned k) {event(30+k);number(c==actor);return input->stats[k];}
int req(CEquipment* p,CCharacter* c,unsigned k) {event(40+k);number(p==item);number(c==actor);return input->reqs[k];}
int strength(CCharacter*c){return stat(c,0);} int dexterity(CCharacter*c){return stat(c,1);}
int magic(CCharacter*c){return stat(c,2);} int defense(CCharacter*c){return stat(c,3);}
int strengthReq(CEquipment*p,CCharacter*c){return req(p,c,0);} int dexterityReq(CEquipment*p,CCharacter*c){return req(p,c,1);}
int magicReq(CEquipment*p,CCharacter*c){return req(p,c,2);} int defenseReq(CEquipment*p,CCharacter*c){return req(p,c,3);}
void side(const Case& c,bool ours,autotest::Capture& out) {
 Raw<CEquipment> a; Raw<CCharacter> b,d;item=a.get();actor=b.get();master=d.get();input=&c;capture=&out;eventCount=levelCalls=0;
 actor->m_pMaster=c.flags&4?master:NULL;actor->m_bCharacterFlag4A0=(c.flags&16)!=0;
 item->m_bUnknown348=(c.flags&32)!=0;actor->m_iUnitLevel=static_cast<unsigned>(c.level);
 detour::Set patches;
 TL_REDIRECT(patches,ceIsa,&isa);TL_REDIRECT(patches,ceLevel,&level);
 TL_REDIRECT(patches,ceStrength,&strength);TL_REDIRECT(patches,ceDexterity,&dexterity);TL_REDIRECT(patches,ceMagic,&magic);TL_REDIRECT(patches,ceDefense,&defense);
 TL_REDIRECT(patches,ceStrengthReq,&strengthReq);TL_REDIRECT(patches,ceDexterityReq,&dexterityReq);TL_REDIRECT(patches,ceMagicReq,&magicReq);TL_REDIRECT(patches,ceDefenseReq,&defenseReq);
 if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat) {
  bool result=ours?item->CEquipment::canEquip(actor,(c.flags&64)!=0):originalCanEquip(item,actor,(c.flags&64)!=0);
  number(result);number(actor->m_bCharacterFlag4A0);number(actor->m_iUnitLevel);number(item->m_bUnknown348);number(levelCalls);
 }
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}
void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
Case make(unsigned n) {
 Case c;std::memset(&c,0,sizeof(c));c.flags=n%128;c.types=(n/128)%16;c.level=10;c.levelReq[0]=c.levelReq[1]=10;
 for(unsigned k=0;k<4;++k)c.stats[k]=c.reqs[k]=10;
 if(n>=2048) {
  unsigned q=n-2048; c.flags=16|32|64;c.types=1;
  static const int values[]={INT_MIN,-1,0,9,10,11,INT_MAX};
  if(q<343) {c.level=values[q%7];c.levelReq[0]=values[(q/7)%7];c.levelReq[1]=values[(q/49)%7];}
  else if(q<539) {q-=343;unsigned k=q/49;c.stats[k]=values[q%7];c.reqs[k]=values[(q/7)%7];}
  else {q-=539;c.trigger=1+q%17;c.mutation=1+(q/17)%4;c.flags=32|((q/68)%2?16:0)|((q/136)%2?64:0);c.types=(q/272)%16;}
 }
 return c;
}
}
TL_TEST(equipment_canequip_differential) {
 int failures=0;
 for(unsigned n=0;n<6939;++n) {
  Case c=make(n);autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
  bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
  if(!ok)host->log("    canEquip case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
  TL_CHECK(failures,ok);if(!ok)return failures;
 }
 host->log("    canEquip: 6939 cases, two calls per side\n");return failures;
}
