#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*,float), "_ZN7CPlayer15updateAnimationEf")
extern "C" void candidate0(void*,float) __asm__("_ZN7CPlayer15updateAnimationEf");
TL_ORIGINAL(void, original1, (void*,std::wstring,std::wstring), "_ZN7CPlayer9loadModelESbIwSt11char_traitsIwESaIwEES3_")
extern "C" void candidate1(void*,std::wstring,std::wstring) __asm__("_ZN7CPlayer9loadModelESbIwSt11char_traitsIwESaIwEES3_");
TL_ORIGINAL(void, original2, (void*), "_ZN7CPlayer14levelResettingEv")
extern "C" void candidate2(void*) __asm__("_ZN7CPlayer14levelResettingEv");
TL_FUNCTION(dep_animation, "_ZN10CCharacter15updateAnimationEf")
TL_FUNCTION(dep_line, "_ZN7CPlayer17updateFishingLineEf")
TL_FUNCTION(dep_modelAnimation, "_ZN13CGenericModel15updateAnimationEfb")
TL_FUNCTION(dep_hp, "_ZN10CCharacter2HPEv")
TL_FUNCTION(dep_playing, "_ZNK13CGenericModel25animationPlayingSubstringERKSs")
TL_FUNCTION(dep_load, "_ZN10CCharacter9loadModelESbIwSt11char_traitsIwESaIwEES3_")
TL_FUNCTION(dep_create, "_ZN16CResourceManager18createGenericModelEPN4Ogre12SceneManagerEPKwS4_bbb")
TL_FUNCTION(dep_play, "_ZN13CGenericModel13playAnimationERKSsbff")
TL_FUNCTION(dep_behind, "_ZN13CGenericModel15setRenderBehindEb")
TL_FUNCTION(dep_reset, "_ZN10CCharacter14levelResettingEv")
TL_FUNCTION(dep_maxHP, "_ZN10CCharacter5maxHPEv")
TL_FUNCTION(dep_modifyHP, "_ZN10CCharacter8modifyHPEf")
TL_FUNCTION(dep_maxMana, "_ZN10CCharacter7maxManaEv")
TL_FUNCTION(dep_modifyMana, "_ZN10CCharacter10modifyManaEf")
TL_FUNCTION(dep_gameUI, "_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(dep_position, "_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(dep_ground, "_ZN10CCharacter12dropToGroundER6CLevelfb")
TL_FUNCTION(dep_toward, "_ZN10CCharacter9setTowardERKN4Ogre7Vector3E")
TL_FUNCTION(dep_teleport, "_ZN10CCharacter16teleportToMasterEf")
TL_FUNCTION(dep_deleteAffix, "_ZN14CEffectManager11deleteAffixERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dep_removeEffects, "_ZN14CEffectManager21removeNonSavedEffectsEv")

extern "C" char parentEntry[] __asm__("_ZNK4Ogre9SceneNode18getParentSceneNodeEv");
namespace {
using namespace smallmass;
void *self,*models[4],*nodes[6],*ui;unsigned creates;
void animation(void* p,float elapsed){event(1,p);floating(elapsed);}
void line(void* p,float elapsed){event(2,p);floating(elapsed);if(input->index%7==0)field<bool>(models[1],0x81)=true;}
void modelAnimation(void* p,float elapsed,bool flag){event(3,p);floating(elapsed);number(flag);}
int hp(void* p){event(4,p);return int(input->index%5)-2;}
bool playing(void* p,const std::string& name){event(5,p);text(name);return input->index&8;}
void load(void* p,std::wstring model,std::wstring skeleton){event(6,p);text(model);text(skeleton);}
void* create(void* p,void* scene,const wchar_t* mesh,const wchar_t* skeleton,bool a,bool b,bool c){event(7,p);pointer(scene);text(std::wstring(mesh));text(std::wstring(skeleton));number(a);number(b);number(c);return models[2+creates++];}
void play(void* p,const std::string& name,bool loop,float speed,float start){event(8,p);text(name);number(loop);floating(speed);floating(start);}
void behind(void* p,bool flag){event(9,p);number(flag);}
void reset(void* p){event(10,p);}
int maxHP(void* p){event(11,p);return 250;}
void modifyHP(void* p,float value){event(12,p);floating(value);field<float>(p,0x414)+=value;}
int maxMana(void* p){event(13,p);return 90;}
void modifyMana(void* p,float value){event(14,p);floating(value);field<float>(p,0x438)+=value;}
void* gameUI(void* p){event(15,p);return ui;}
void position(void* p,const Ogre::Vector3& value){event(16,p);vector(value);field<Ogre::Vector3>(p,0x84)=value;}
void ground(void* p,void* level,float height,bool flag){event(17,p);pointer(level);floating(height);number(flag);}
void toward(void* p,const Ogre::Vector3& value){event(18,p);vector(value);}
void teleport(void* p,float distance){event(19,p);floating(distance);}
bool deleteAffix(void* p,const std::wstring& name){event(20,p);text(name);if(name==L"DAMAGEEFFECTPOISONED"&&input->index%7==0)field<void*>(self,0x1b8)=0;return true;}
void removeEffects(void* p){event(21,p);}
bool enabled(void* p){event(22,p);return input->index&1;}
void setEnabled(void* p,bool value){event(23,p);number(value);field<bool>(p,0x82)=value;}
void* getModel(void* p){event(24,p);return models[0];}
void visible(void* p,bool value){event(25,p);number(value);field<bool>(p,0x81)=value;}
void nodeVisible(void* p,bool value,bool cascade){event(26,p);number(value);number(cascade);}
void state(void* p,int value){event(27,p);number(value);field<int>(p,0x330)=value;}
void* parent(void* node){event(28,node);return input->index%3==0?0:nodes[5];}
void* removeChild(void* p,void* child){event(29,p);pointer(child);return child;}
void addChild(void* p,void* child){event(30,p);pointer(child);}
void renderQueue(void* p,unsigned char queue){event(31,p);number(queue);}
void destroy(void* p){event(32,p);}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;creates=0;self=object(0xa70);ui=object(0x1930);
 void* resources=object(0x48);void* level=object(0x2f0);void* effects=object(0x110);void* entity=object(0x300);
 void** table=static_cast<void**>(object(0x430));table[0x40/8]=reinterpret_cast<void*>(&setEnabled);table[0x48/8]=reinterpret_cast<void*>(&enabled);table[0x1e0/8]=reinterpret_cast<void*>(&getModel);table[0x348/8]=reinterpret_cast<void*>(&state);field<void*>(self,0)=table;
 void** modelTable=static_cast<void**>(object(0x260));modelTable[1]=reinterpret_cast<void*>(&destroy);modelTable[0x50/8]=reinterpret_cast<void*>(&visible);
 void** nodeTable=static_cast<void**>(object(0x380));nodeTable[0x378/8]=reinterpret_cast<void*>(&nodeVisible);nodeTable[0x1e0/8]=reinterpret_cast<void*>(&removeChild);nodeTable[0x1a8/8]=reinterpret_cast<void*>(&addChild);
 for(unsigned i=0;i<6;++i){nodes[i]=object(0x200);field<void*>(nodes[i],0)=nodeTable;}
 void** entityTable=static_cast<void**>(object(0x148));entityTable[0x140/8]=reinterpret_cast<void*>(&renderQueue);field<void*>(entity,0)=entityTable;
 for(unsigned i=0;i<4;++i){models[i]=object(0x258);field<void*>(models[i],0)=modelTable;field<void*>(models[i],0x58)=nodes[i];field<void*>(models[i],0x60)=entity;field<bool>(models[i],0x81)=c.index&4;}
 field<void*>(self,0x200)=c.op==0&&c.index%13==0?0:models[0];field<void*>(self,0x828)=c.index%5?models[0]:0;field<void*>(self,0x830)=c.index%7?models[1]:0;
 field<void*>(self,0x848)=c.index%3?nodes[4]:0;field<void*>(self,0x2f0)=c.index%4?nodes[4]:0;field<bool>(self,0xa16)=c.index&2;field<float>(self,0x884)=9;
 const int states[]={0,0x1f,0x20,0x21,0x22,0x23,5,6};field<int>(self,0x330)=states[(c.index/2)%8];
 field<void*>(self,0x68)=c.op==2&&c.index%7==0?0:resources;field<void*>(resources,0x18)=c.index%5?level:0;field<int>(ui,0x1928)=c.index%3;
 field<Ogre::Vector3>(level,0x140)=Ogre::Vector3(5,2,-8);field<Ogre::Vector3>(level,0x164)=Ogre::Vector3(.5f,0,1);
 field<void*>(self,0x1b8)=c.index%11?effects:0;
 void** pets=static_cast<void**>(object(4*8));for(unsigned i=0;i<4;++i){pets[i]=object(0x778);field<void*>(pets[i],0)=table;if(c.op==0&&(c.index+i)%5==0)pets[i]=0;}
 field<void*>(self,0x648)=pets;field<void*>(self,0x650)=pets+c.index%5;field<void*>(self,0x658)=pets+4;
 detour::Set patches;
 TL_REDIRECT(patches,dep_animation,&animation);
 TL_REDIRECT(patches,dep_line,&line);
 TL_REDIRECT(patches,dep_modelAnimation,&modelAnimation);
 TL_REDIRECT(patches,dep_hp,&hp);
 TL_REDIRECT(patches,dep_playing,&playing);
 TL_REDIRECT(patches,dep_load,&load);
 TL_REDIRECT(patches,dep_create,&create);
 TL_REDIRECT(patches,dep_play,&play);
 TL_REDIRECT(patches,dep_behind,&behind);
 TL_REDIRECT(patches,dep_reset,&reset);
 TL_REDIRECT(patches,dep_maxHP,&maxHP);
 TL_REDIRECT(patches,dep_modifyHP,&modifyHP);
 TL_REDIRECT(patches,dep_maxMana,&maxMana);
 TL_REDIRECT(patches,dep_modifyMana,&modifyMana);
 TL_REDIRECT(patches,dep_gameUI,&gameUI);
 TL_REDIRECT(patches,dep_position,&position);
 TL_REDIRECT(patches,dep_ground,&ground);
 TL_REDIRECT(patches,dep_toward,&toward);
 TL_REDIRECT(patches,dep_teleport,&teleport);
 TL_REDIRECT(patches,dep_deleteAffix,&deleteAffix);
 TL_REDIRECT(patches,dep_removeEffects,&removeEffects);

 patches.redirect(parentEntry,parentEntry,&parent);
 if(patches.failed())_exit(41);
 switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,self,float(c.index%4)*.125f);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,std::wstring(c.index&1?L"model.mesh":L""),std::wstring(c.index&2?L"skeleton.skeleton":L""));break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self);break;
 }
 number(creates);number(field<bool>(self,0xa16));floating(field<float>(self,0x884));number(field<int>(self,0x330));number(field<bool>(self,0x82));pointer(field<void*>(self,0x828));pointer(field<void*>(self,0x830));floating(field<float>(self,0x414));floating(field<float>(self,0x438));vector(field<Ogre::Vector3>(self,0x84));
}
}
TL_TEST(mass3_8f0d10) { return smallmass::run(host,0,"mass3_8f0d10",(uint64_t)(uintptr_t)original0,execute,256); }
TL_TEST(mass3_8f4780) { return smallmass::run(host,1,"mass3_8f4780",(uint64_t)(uintptr_t)original1,execute,128); }
TL_TEST(mass3_8f5810) { return smallmass::run(host,2,"mass3_8f5810",(uint64_t)(uintptr_t)original2,execute,128); }
