#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*,void*,bool), "_ZN10CCharacter14setActiveSkillEP6CSkillb")
extern "C" void candidate0(void*,void*,bool) __asm__("_ZN10CCharacter14setActiveSkillEP6CSkillb");
TL_ORIGINAL(void, original1, (void*,int), "_ZN10CCharacter10cycleSkillEi")
extern "C" void candidate1(void*,int) __asm__("_ZN10CCharacter10cycleSkillEi");
TL_ORIGINAL(void*, original2, (void*,unsigned), "_ZN10CCharacter13getKnownSpellEj")
extern "C" void* candidate2(void*,unsigned) __asm__("_ZN10CCharacter13getKnownSpellEj");
TL_ORIGINAL(void, original3, (void*,std::wstring,int), "_ZN10CCharacter12unLearnSpellESbIwSt11char_traitsIwESaIwEEi")
extern "C" void candidate3(void*,std::wstring,int) __asm__("_ZN10CCharacter12unLearnSpellESbIwSt11char_traitsIwESaIwEEi");
TL_ORIGINAL(void, original4, (void*,void*), "_ZN10CCharacter16deactivateEffectEP7CEffect")
extern "C" void candidate4(void*,void*) __asm__("_ZN10CCharacter16deactivateEffectEP7CEffect");
TL_ORIGINAL(void, original5, (void*,float), "_ZN10CCharacter23handInteractiveSequenceEf")
extern "C" void candidate5(void*,float) __asm__("_ZN10CCharacter23handInteractiveSequenceEf");
TL_ORIGINAL(void, original6, (void*,void*,void*), "_ZN10CCharacter13doWeaponProcsEP10CEquipmentP9CBaseUnit")
extern "C" void candidate6(void*,void*,void*) __asm__("_ZN10CCharacter13doWeaponProcsEP10CEquipmentP9CBaseUnit");
#include <OgreQuaternion.h>
#include <vector>
TL_FUNCTION(dep_known, "_ZN13CSkillManager11knownSkillsE22ESKILL_ACTIVATION_TYPE")
TL_FUNCTION(dep_calculate, "_ZN6CSkill28calculateEffectiveSkillLevelEv")
TL_FUNCTION(dep_getSkill, "_ZN13CSkillManager8getSkillERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(dep_deleteSkill, "_ZN13CSkillManager19deleteSpecificSkillEP6CSkill")
TL_FUNCTION(dep_stop, "_ZN10CCharacter24attemptStopOfActiveSkillEv")
TL_FUNCTION(dep_position, "_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(dep_executeSkill, "_ZN13CSkillManager12executeSkillEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ERKNS5_10QuaternionES8_S3_")
namespace {
using namespace smallmass;
void* self;void* manager;void* skills[4];void* other;void* path;Ogre::Quaternion orientationValue;
unsigned positionCalls;std::vector<std::wstring*> strings;
std::wstring& makeText(void* p,unsigned offset,const wchar_t* v) { std::wstring* s=new(static_cast<char*>(p)+offset)std::wstring(v);strings.push_back(s);return *s; }
int known(void* p,int type) { event(1,p);number(type);return field<unsigned>(p,0x68); }
void calculate(void* p) { event(2,p);field<unsigned>(p,0xe0)=(input->index/7+field<unsigned>(p,0x118))%4; }
void* getSkill(void* p,const std::wstring& name,int level) { event(3,p);text(name);number(level);return input->index%7==0?NULL:skills[input->index%4]; }
void deleteSkill(void* p,void* skill) { event(4,p);pointer(skill); }
bool stop(void* p) { event(5,p);if(input->index%5==0)field<void*>(p,0x750)=NULL;return input->index&8; }
Ogre::Vector3 position(void* p,bool absolute) { event(6,p);number(absolute);++positionCalls;return field<Ogre::Vector3>(p,0x84); }
const Ogre::Quaternion& orientation(void* p) { event(7,p);return orientationValue; }
void* executeSkill(void* p,void* skill,void* caster,int activation,const Ogre::Vector3& from,const Ogre::Quaternion& orientation,const Ogre::Vector3& to,void* target) {
 event(8,p);pointer(skill);pointer(caster);number(activation);vector(from);output->add(&orientation,sizeof(orientation));vector(to);pointer(target);return skill;
}
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;strings.clear();positionCalls=0;
 self=object(0x778);manager=object(0x98);other=object(0x480);path=object(0x198);void* effect=object(0x138);
 void** listData=static_cast<void**>(object(4*8));
 for(unsigned i=0;i<4;++i) {
  skills[i]=object(0x160);listData[i]=skills[i];
  field<unsigned>(skills[i],0x118)=i;field<int>(skills[i],0xec)=c.index&1?-1:13;
  field<bool>(skills[i],0x64)=c.index&2;field<bool>(skills[i],0x6b)=(c.index/3+i)%4==0;
  field<bool>(skills[i],0x6d)=(c.index/5+i)%5!=0;field<int>(skills[i],0x60)=(c.index/9+i)%5;
  field<long long>(skills[i],0x150)=0x1234567890000LL+i*131;
 }
 unsigned count=c.index%11==0?0:4;list(manager,0x60,listData,count,c.index%7==0?1:4);
 field<void*>(self,0x1c8)=c.index%17==0?NULL:manager;
 field<void*>(other,0x1c8)=c.index%13==0?NULL:manager;
 field<void*>(self,0x398)=skills[0];
 if(c.op!=1&&c.index%7==0)field<void*>(self,0x398)=NULL;
 field<void*>(self,0x3a0)=c.index&16?skills[c.index%4]:NULL;
 const float times[]={0,0.25f,-1,1};field<float>(self,0x380)=c.index%19==0?bits(0x7fc01234):times[(c.index/4)%4];field<bool>(self,0x267)=c.index&4;
 long long guid=field<long long>(skills[c.index%4],0x150);
 field<long long>(self,0x3b0)=c.index&1?guid:-1;field<long long>(self,0x3b8)=c.index&2?guid:71;field<long long>(self,0x3c0)=c.index&4?guid:83;
 if(c.op==3||c.op==4)field<void*>(self,0x398)=c.index&8?skills[c.index%4]:skills[(c.index+1)%4];
 const wchar_t* names[]={L"",L"FIRE",L"ice",L"SPELL"};
 for(unsigned i=0;i<4;++i){makeText(self,0x3c8+i*8,names[(c.index/4+i)%4]);field<int>(self,0x3e8+i*4)=int(i)-1;}
 const int types[]={0x4a,0x4c,0x51,0x69,0x4b,0,1,0x50};field<int>(effect,0x1c)=types[(c.index/4)%8];field<int>(effect,0x10)=int(c.index%7)-2;
 makeText(effect,0x80,names[c.index%4]);
 field<void*>(self,0x750)=c.index&16?path:NULL;field<bool>(self,0x264)=c.index&32;field<float>(self,0x278)=2.5f;
 Ogre::Vector3 source(float(int(c.index%7)-3),7,float(int(c.index%11)-5));
 Ogre::Vector3 target=c.index%9==0?source:Ogre::Vector3(-2,-3,5);
 field<Ogre::Vector3>(self,0x84)=source;field<Ogre::Vector3>(other,0x84)=target;field<float>(other,0x194)=float(int(c.index%13)-3)*0.25f;
 void* node=object(32);void** table=static_cast<void**>(object(0x100));table[0xc8/8]=reinterpret_cast<void*>(&orientation);field<void*>(node,0)=table;field<void*>(self,0x58)=node;
 orientationValue=Ogre::Quaternion(0.5f,0.5f,-0.5f,0.5f);
 detour::Set patches;
 TL_REDIRECT(patches,dep_known,&known);
 TL_REDIRECT(patches,dep_calculate,&calculate);
 TL_REDIRECT(patches,dep_getSkill,&getSkill);
 TL_REDIRECT(patches,dep_deleteSkill,&deleteSkill);
 TL_REDIRECT(patches,dep_stop,&stop);
 TL_REDIRECT(patches,dep_position,&position);
 TL_REDIRECT(patches,dep_executeSkill,&executeSkill);
 if(patches.failed())_exit(41);
 switch(c.op) {
 case 0:autotest::invoke(out,ours?candidate0:original0,self,c.index%5==0?NULL:c.index%5==1?effect:skills[c.index%4],bool(c.index&1));break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,int(c.index%3)-1);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,c.index%8==7?0xffffffffu:c.index%7);break;
 case 3:{std::wstring name=c.index%3==0?L"missing":field<std::wstring>(self,0x3c8+(c.index%4)*8);int level=c.index%5==0?11:field<int>(self,0x3e8+(c.index%4)*4);void(*fn)(void*,std::wstring,int)=ours?candidate3:original3;if(!autotest::beginInvocation(out,fn))return;fn(self,name,level);out.callCompleted=1;break;}
 case 4:autotest::invoke(out,ours?candidate4:original4,self,effect);break;
 case 5:autotest::invoke(out,ours?candidate5:original5,self,0.125f);break;
 case 6:autotest::invoke(out,ours?candidate6:original6,self,c.index%7==0?NULL:other,c.index%5==0?NULL:other);break;
 }
 for(unsigned i=0;i<strings.size();++i){text(*strings[i]);strings[i]->~basic_string();std::memset(strings[i],0,sizeof(std::wstring));}
 number(positionCalls);out.add(autotest::g_arena,autotest::g_arenaUsed);
}
}
TL_TEST(restore69_80f410) { return smallmass::run(host,0,"restore69_80f410",(uint64_t)(uintptr_t)original0,execute,192); }
TL_TEST(restore69_80f500) { return smallmass::run(host,1,"restore69_80f500",(uint64_t)(uintptr_t)original1,execute,192); }
TL_TEST(restore69_80f800) { return smallmass::run(host,2,"restore69_80f800",(uint64_t)(uintptr_t)original2,execute,192); }
TL_TEST(restore69_823bf0) { return smallmass::run(host,3,"restore69_823bf0",(uint64_t)(uintptr_t)original3,execute,192); }
TL_TEST(restore69_837060) { return smallmass::run(host,4,"restore69_837060",(uint64_t)(uintptr_t)original4,execute,192); }
TL_TEST(restore69_83c670) { return smallmass::run(host,5,"restore69_83c670",(uint64_t)(uintptr_t)original5,execute,192); }
TL_TEST(restore69_827010) { return smallmass::run(host,6,"restore69_827010",(uint64_t)(uintptr_t)original6,execute,192); }
