#include "tests/SmallMassCompare.h"
#include "TArrayList.h"
#include <utility>
#include <OgreMemoryAllocatorConfig.h>
#define DECL(ret,id,args,sym) TL_ORIGINAL(ret,id##Old,args,sym) extern "C" ret id##New args __asm__(sym);
DECL(bool,deepDamageUpdate,(void*,float,void*,const Ogre::Vector3&),"_ZN12CDamageShape17updateLevelObjectEfPN4Ogre6CameraERKNS0_7Vector3E")
DECL(void,deepDamageItem,(void*,float,void*,float),"_ZN12CDamageShape14doDamageToItemEfP5CItemf")
DECL(void,deepDamageCharacter,(void*,float,void*,float),"_ZN12CDamageShape19doDamageToCharacterEfP10CCharacterf")
TL_FUNCTION(deepDamagePosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(deepDamageSetPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(deepDamageEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(deepDamageSnap,"_ZN6CLevel17snapToValidGroundERN4Ogre7Vector3Ef")
TL_FUNCTION(deepDamageVisual,"_ZN6CShape12updateVisualEbf")
TL_FUNCTION(deepDamageMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(deepDamageSettings,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(deepDamageISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(deepDamageShape,"_ZN6CShape29getPositionIsInShapeAtPercentEfRKN4Ogre7Vector3Ef")
TL_FUNCTION(deepDamageUI,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(deepDamageConsole,"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(deepDamageAlignment,"_ZN10CCharacter9alignmentEv")
TL_FUNCTION(deepDamageAlive,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(deepDamageGraph,"_ZNK6CGraph8getValueEfj")
TL_FUNCTION(deepDamageRandom,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(deepDamageEffectCtor,"_ZN7CEffectC1E12EEFFECT_TYPEb18EEFFECT_ACTIVATIONfffb")
TL_FUNCTION(deepDamageEffectCtor2,"_ZN7CEffectC2E12EEFFECT_TYPEb18EEFFECT_ACTIVATIONfffb")
TL_FUNCTION(deepDamageApply,"_ZN10CCharacter11applyDamageER6CLevelRKN4Ogre7Vector3EfS5_fPS_bbbbj")
namespace {
using namespace smallmass;unsigned calls;void* self;void* unit;void* master;void* ui;void* token;void* level;void** effectTable;
void record(unsigned tag,void* p){event(tag,p);++calls;}
bool enabled(void* p){record(1,p);return field<bool>(p,0x82);}
void setEnabled(void* p,bool value){record(2,p);number(value);field<bool>(p,0x82)=value;}
Ogre::Vector3 position(void* p,bool absolute){record(3,p);number(absolute);return field<Ogre::Vector3>(p,0x84);}
void setPosition(void* p,const Ogre::Vector3& v){record(4,p);vector(v);field<Ogre::Vector3>(p,0x84)=v;}
bool editor(void* p){record(5,p);return input->index&1;}
bool snap(void* p,Ogre::Vector3& v,float height){record(6,p);vector(v);floating(height);v.y+=2.25f;return input->index%3;}
void visual(void* p,bool value,float percent){record(7,p);number(value);floating(percent);}
void* getMaster(){record(8,master);return master;}
int setting(void* p,unsigned id){record(9,p);number(id);return (input->index/7)&1;}
bool isa(void* p,int type){record(10,p);number(type);return type==29?(input->index&4)!=0:input->index%11!=0;}
std::pair<bool,float> shape(void* p,float percent,const Ogre::Vector3& v,float radius){record(11,p);floating(percent);vector(v);floating(radius);return std::make_pair(input->index%5!=0,0.625f);}
void* getUI(){record(12,ui);return ui;}
void console(void* p,std::wstring message){record(13,p);text(message);}
bool itemAffected(void* p,void* shape,void* target){record(14,p);pointer(shape);pointer(target);return (input->index+field<unsigned>(p,8))%3!=0;}
bool interact(void* p,void* source){record(15,p);pointer(source);return true;}
int alignment(void* p){record(16,p);return (input->index/2)%3;}
bool alive(void* p){record(17,p);return (input->index&2)!=0;}
bool canAffect(void* p,void* shape,void* target){record(18,p);pointer(shape);pointer(target);return (input->index+field<unsigned>(p,8))%4!=0;}
bool affected(void* p,void* shape,void* target,Ogre::Vector3* direction){record(19,p);pointer(shape);pointer(target);vector(*direction);direction->x+=float(field<unsigned>(p,8))*0.125f;return (input->index+field<unsigned>(p,8))%5==0;}
float graph(void* p,float level,unsigned group){record(20,p);floating(level);number(group);return level*0.5f+7.0f;}
float random(float a,float b){number(21);++calls;floating(a);floating(b);return (b-a)*0.25f+a;}
bool canDamage(void* p,void* target,float damage,const Ogre::Vector3& contact){record(22,p);pointer(target);floating(damage);vector(contact);return input->index%7!=0;}
void effectCtor(void* p,int type,bool flag,int activation,float a,float b,float c,bool d){number(23);++calls;number(type);number(flag);number(activation);floating(a);floating(b);floating(c);number(d);std::memset(p,0,0x138);field<void*>(p,0)=effectTable;field<float>(p,0x24)=b;}
void effectDelete(void* p){number(24);++calls;number(field<unsigned>(p,0x14));vector(field<Ogre::Vector3>(p,0x98));Ogre::GeneralAllocPolicy::deallocateBytes(p);}
bool effectApply(void* p,void* source,void* target,void* effect){record(25,p);pointer(source);pointer(target);number(field<unsigned>(effect,0x14));floating(field<float>(effect,0x24));vector(field<Ogre::Vector3>(effect,0x98));return true;}
void apply(void* p,void* l,const Ogre::Vector3& origin,float damage,const Ogre::Vector3& direction,float scale,void* source,bool a,bool b,bool c,bool d,unsigned kind){record(26,p);pointer(l);vector(origin);floating(damage);vector(direction);floating(scale);pointer(source);number(a);number(b);number(c);number(d);number(kind);}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;self=object(0x200);unit=object(0x1148);master=object(0x190);ui=object(0x1698);token=object(8);level=object(0x2f0);void* resources=object(0x48);field<void*>(resources,0x18)=c.index%6?level:0;field<void*>(self,0x68)=resources;field<void*>(master,0x90)=token;field<void*>(ui,0x1690)=token;field<int>(level,0x1a8)=int(c.index%13)-2;
void** table=static_cast<void**>(object(0x350));table[0x40/8]=reinterpret_cast<void*>(&setEnabled);table[0x48/8]=reinterpret_cast<void*>(&enabled);table[0x1f0/8]=reinterpret_cast<void*>(&canDamage);field<void*>(self,0)=table;void** unitTable=static_cast<void**>(object(0x350));unitTable[0x280/8]=reinterpret_cast<void*>(&interact);unitTable[0x240/8]=reinterpret_cast<void*>(&effectApply);field<void*>(unit,0)=unitTable;effectTable=static_cast<void**>(object(16));effectTable[1]=reinterpret_cast<void*>(&effectDelete);
field<bool>(self,0x82)=c.op==0?(c.index&2)!=0:true;field<Ogre::Vector3>(self,0x84)=Ogre::Vector3(float(c.index%3),2,-4);field<Ogre::Vector3>(unit,0x84)=Ogre::Vector3(3,-1,float(c.index%5));field<float>(unit,0x194)=c.index&16?0.0f:1.25f;field<void*>(self,0x178)=c.index%8?token:0;field<bool>(self,0x180)=c.index&4;field<int>(self,0x184)=c.index%4;field<int>(self,0x188)=7;field<int>(self,0x18c)=c.index%4;field<float>(self,0x190)=0.4f;field<float>(self,0x194)=float(int(c.index%5)-2)*0.125f;field<float>(self,0x198)=float(int(c.index%7)-3)*0.1f;field<float>(self,0x19c)=float(int(c.index%5)-2)*0.25f;field<float>(self,0x1a0)=0.375f;field<bool>(self,0x1a4)=c.index&8;field<bool>(self,0x1a5)=c.index&16;field<bool>(self,0x1a6)=c.index&32;field<bool>(self,0x1a7)=c.index&4;field<bool>(self,0x1a8)=c.index&8;field<int>(self,0x1ac)=int(c.index%5)-1;field<int>(self,0x1b0)=int(c.index%4);field<float>(self,0x1b4)=c.index&32?15:30;field<float>(self,0x1b8)=30;Ogre::Vector3 last=field<Ogre::Vector3>(self,0x84);if(c.index&64)last.y-=1;field<Ogre::Vector3>(self,0x1bc)=last;
TArrayList<void*>& listeners=*new(static_cast<char*>(self)+0x1c8)TArrayList<void*>(1+c.index%3);TArrayList<void*>& targets=*new(static_cast<char*>(self)+0x1e0)TArrayList<void*>(1+c.index%2);for(unsigned i=0;i<c.index%4;++i){void* listener=object(16);void** lt=static_cast<void**>(object(40));lt[2]=reinterpret_cast<void*>(&canAffect);lt[3]=reinterpret_cast<void*>(&affected);lt[4]=reinterpret_cast<void*>(&itemAffected);field<void*>(listener,0)=lt;field<unsigned>(listener,8)=i;listeners.add(listener);}for(unsigned i=0;i<(c.index/4)%4;++i)targets.add(c.index&128&&i==1?unit:token);field<int>(self,0x1f8)=int((c.index/9)%5)-1;
detour::Set d;TL_REDIRECT(d,deepDamagePosition,&position);TL_REDIRECT(d,deepDamageSetPosition,&setPosition);TL_REDIRECT(d,deepDamageEditor,&editor);TL_REDIRECT(d,deepDamageSnap,&snap);TL_REDIRECT(d,deepDamageVisual,&visual);TL_REDIRECT(d,deepDamageMaster,&getMaster);TL_REDIRECT(d,deepDamageSettings,&setting);TL_REDIRECT(d,deepDamageISA,&isa);TL_REDIRECT(d,deepDamageShape,&shape);TL_REDIRECT(d,deepDamageUI,&getUI);TL_REDIRECT(d,deepDamageConsole,&console);TL_REDIRECT(d,deepDamageAlignment,&alignment);TL_REDIRECT(d,deepDamageAlive,&alive);TL_REDIRECT(d,deepDamageGraph,&graph);TL_REDIRECT(d,deepDamageRandom,&random);TL_REDIRECT(d,deepDamageEffectCtor,&effectCtor);TL_REDIRECT(d,deepDamageEffectCtor2,&effectCtor);TL_REDIRECT(d,deepDamageApply,&apply);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
if(c.op==0){Ogre::Vector3 camera(1,2,3);typedef bool(*Fn)(void*,float,void*,const Ogre::Vector3&);autotest::invoke<Fn,void*,float,void*,const Ogre::Vector3&>(out,ours?deepDamageUpdateNew:deepDamageUpdateOld,self,c.index&1?0.2f:-0.15f,token,camera);}else if(c.op==1)autotest::invoke(out,ours?deepDamageItemNew:deepDamageItemOld,self,0.2f,unit,0.75f);else autotest::invoke(out,ours?deepDamageCharacterNew:deepDamageCharacterOld,self,0.2f,unit,0.75f);
number(calls);out.add(static_cast<char*>(self)+0x180,0x48);vector(field<Ogre::Vector3>(self,0x84));number(targets.size());for(unsigned i=0;i<targets.size();++i)pointer(targets[i]);targets.~TArrayList();listeners.~TArrayList();}
}
TL_TEST(deep_runtime_damage_update){return smallmass::run(host,0,"deep_runtime_damage_update",(uintptr_t)deepDamageUpdateOld,execute,256);}
TL_TEST(deep_runtime_damage_item){return smallmass::run(host,1,"deep_runtime_damage_item",(uintptr_t)deepDamageItemOld,execute,256);}
TL_TEST(deep_runtime_damage_character){return smallmass::run(host,2,"deep_runtime_damage_character",(uintptr_t)deepDamageCharacterOld,execute,512);}
