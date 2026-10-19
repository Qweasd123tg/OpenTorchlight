#include <cstring>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "Equipment.h"
#include "Inventory.h"
#include "GenericModel.h"
#include "AttackDescription.h"
#include "AIManager.h"
#include "Skill.h"
#include "Particle.h"
#include "DataGroup.h"
#include "TRepository.h"
#include "SoundBank.h"
#undef private
#undef protected
#include "NativeMenuClient.h"
#include "tests/FinishLevelFixture.h"
TL_ORIGINAL(bool,vOldAttack,(CCharacter*),"_ZN10CCharacter6attackEv")
TL_ORIGINAL(void,vOldSpawn,(CCharacter*),"_ZN10CCharacter5spawnEv")
TL_ORIGINAL(CCharacter*,vOldSight,(CCharacter*,EAlignment,bool),"_ZN10CCharacter22calculateTargetInSightE10EAlignmentb")
TL_ORIGINAL(void,vOldAlignment,(CCharacter*,EAlignment),"_ZN10CCharacter12setAlignmentE10EAlignment")
extern "C" bool vNewAttack(CCharacter*) __asm__("_ZN10CCharacter6attackEv");
extern "C" void vNewSpawn(CCharacter*) __asm__("_ZN10CCharacter5spawnEv");
extern "C" CCharacter*vNewSight(CCharacter*,EAlignment,bool) __asm__("_ZN10CCharacter22calculateTargetInSightE10EAlignmentb");
extern "C" void vNewAlignment(CCharacter*,EAlignment) __asm__("_ZN10CCharacter12setAlignmentE10EAlignment");
TL_FUNCTION(vLoad,"_ZN13CGenericModel9loadModelESbIwSt11char_traitsIwESaIwEES3_bbb")
TL_FUNCTION(vSelect,"_ZN10CCharacter12selectAttackE18EATTACK_RANGE_TYPE")
TL_FUNCTION(vRange,"_ZN10CCharacter11attackRangeEv")
TL_FUNCTION(vMelee,"_ZN10CCharacter10meleeRangeEv")
TL_FUNCTION(vRanged,"_ZN10CCharacter11rangedRangeEv")
TL_FUNCTION(vEffect,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(vFlag,"_ZN10CAIManager9hasAIFlagE13EAIFLAG_TYPES")
TL_FUNCTION(vLength,"_ZNK13CGenericModel25getAnimationLengthSecondsEi")
TL_FUNCTION(vClear,"_ZN13CGenericModel21clearQueuedAnimationsEv")
TL_FUNCTION(vBlend,"_ZN10CCharacter14blendAnimationEibfff")
TL_FUNCTION(vQueue,"_ZN13CGenericModel19queueBlendAnimationERKSsbff")
TL_FUNCTION(vTheme,"_ZN9CBaseUnit12hasUnitThemeERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(vPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(vSetPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(vSound,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(vExists,"_ZNK13CGenericModel24animationExistsSubstringERKSs")
TL_FUNCTION(vRandomAnimation,"_ZN13CGenericModel19findRandomAnimationERKSs")
TL_FUNCTION(vPlay,"_ZN13CGenericModel13playAnimationEjbff")
TL_FUNCTION(vInvisible,"_ZN10CCharacter17getSpawnInvisibleEv")
TL_FUNCTION(vOpacity,"_ZN10CCharacter13updateOpacityEfb")
TL_FUNCTION(vBehind,"_ZN10CCharacter15setRenderBehindEb")
TL_FUNCTION(vActive,"_ZN10CCharacter20calculateActiveRangeERKN4Ogre7Vector3E")
TL_FUNCTION(vCamera,"_ZN16CResourceManager16getCameraControlEv")
TL_FUNCTION(vParticle,"_ZN9CParticle5StartEv")
TL_FUNCTION(vOutline,"_ZN13CGenericModel22setRenderBehindTextureERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(vHighlight,"_ZN13CGenericModel19setHighlightTextureERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(vData,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEPKw")
TL_FUNCTION(vISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(vDestination,"_ZN10CCharacter14setDestinationER6CLevelff")
TL_FUNCTION(vFind,"_ZN6CLevel23findCharacterWithinViewERKN4Ogre7Matrix4E10EAlignmentfffbP10CCharacterP6CSkill")
TL_FUNCTION(vSkillAngle,"_ZN6CSkill18getFindTargetAngleEv")

namespace {
struct Case{unsigned op,seed,control;};unsigned seed,findCalls;bool armed;autotest::Capture*out;finishlevel::Fixture*level;menugui::Client*client;CSoundManager*audio;CCharacter*self,*target,*master;CEquipment*equipment[2];CGenericModel*models[3];CAttackDescription*attacks[3];CParticle*particle;CSkill*skill;
void num(unsigned n){if(armed)out->add(&n,4);}void fp(float f){if(armed)out->add(&f,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void narrow(const std::string&s){num(s.size());if(armed)out->add(s.data(),s.size());}void wide(const std::wstring&s){num(s.size());if(armed)out->add(s.data(),s.size()*sizeof(wchar_t));}
unsigned id(const void*p){if(!p)return 0;if(p==self)return 1;if(p==target)return 2;if(p==master)return 3;for(unsigned i=0;i<2;++i)if(p==equipment[i])return 11+i;for(unsigned i=0;i<3;++i){if(p==models[i])return 21+i;if(p==attacks[i])return 31+i;}if(p==particle)return 41;if(p==skill)return 42;return 99;}
void initEmptyGlobals(){
 const uintptr_t a[]={0x14286f0,0x1428720,0x1429ea0,0x1476060,0x14781e0,0x1479460,0x147c340,0x147e8e0,0x147fac0,0x1480a40,0x1482e00,0x1484120,0x14872e0,0x148e500,0x148f960,0x14afec0,0x14b3300,0x14b5868,0x14b58e8,0x14e68b0,0x14ee340,0x14f2668,0x1500740,0x1500820,0x15019a0,0x150b428,0x150c8a0,0x150c980};
 for(unsigned i=0;i<sizeof(a)/sizeof(a[0]);++i){void*p;std::memcpy(&p,(void*)a[i],sizeof(p));if(!p)new((void*)a[i])std::string;}
 const uintptr_t b[]={0x14286f8,0x1428728,0x1429ea8,0x1476068,0x14781e8,0x1479468,0x147c348,0x147e8e8,0x147fac8,0x1480a48,0x1482e08,0x1484128,0x14872e8,0x148e508,0x148f968,0x14afec8,0x14b3308,0x14b5870,0x14b58f0,0x14e68b8,0x14ee348,0x14f2670,0x1500748,0x1500828,0x15019a8,0x150b430,0x150c8a8,0x150c988};
 for(unsigned i=0;i<sizeof(b)/sizeof(b[0]);++i){void*p;std::memcpy(&p,(void*)b[i],sizeof(p));if(!p)new((void*)b[i])std::wstring;}
}

float value(unsigned k){const float v[]={-100,-10,-1,0,.01f,.1f,1,2,5,10,11,100};return v[(seed*13+k*7)%12];}
void load(CGenericModel*,std::wstring,std::wstring,bool,bool,bool){}
void select(CCharacter*p,EATTACK_RANGE_TYPE type){num(101);num(type);p->m_attack=seed%7?attacks[unsigned(type)%3]:NULL;}
float range(CCharacter*){num(103);return value(1);}float melee(CCharacter*){num(107);return value(2);}float ranged(CCharacter*){num(109);return value(3);}
float effect(CCharacter*p,EEFFECT_TYPE type,EDAMAGE_TYPES damage){num(113);num(id(p));num(type);num(damage);return value(unsigned(type));}
bool flag(CAIManager*,EAIFLAG_TYPES type){num(127);num(type);return seed%3==0;}
float length(const CGenericModel*p,int index){num(131);num(id(p));num(index);return float(seed%5)*.75f;}
void clear(CGenericModel*p){num(137);num(id(p));}
void blend(CCharacter*p,int index,bool loop,float a,float b,float c){num(139);num(id(p));num(index);num(loop);fp(a);fp(b);fp(c);}
void queue(CGenericModel*p,const std::string&name,bool loop,float a,float b){num(149);num(id(p));narrow(name);num(loop);fp(a);fp(b);}
bool theme(CBaseUnit*p,const std::wstring&name){num(151);num(id(p));wide(name);return (seed/5)%3==0;}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){num(157);num(id(p));num(absolute);return p->m_vPosition;}
void setPosition(CPositionableObject*p,const Ogre::Vector3&v){num(163);num(id(p));vec(v);p->m_vPosition=v;}
int sound(CSoundBank*,int index,Ogre::SceneNode*node,float a,float b,bool flag){num(167);num(index);num(node!=NULL);fp(a);fp(b);num(flag);return int(seed);}
bool exists(const CGenericModel*p,const std::string&name){num(173);num(id(p));narrow(name);return seed%5!=1;}
int animation(CGenericModel*p,const std::string&name){num(179);num(id(p));narrow(name);return int(seed%7)-2;}
void play(CGenericModel*p,unsigned index,bool loop,float a,float b){num(181);num(id(p));num(index);num(loop);fp(a);fp(b);}
bool invisible(CCharacter*){num(191);return seed&2;}
void opacity(CCharacter*p,float elapsed,bool force){num(193);num(id(p));fp(elapsed);num(force);}
void behind(CCharacter*p,bool value){num(197);num(id(p));num(value);p->m_Padding4A1[0]=value;}
void active(CCharacter*p,const Ogre::Vector3&v){num(199);num(id(p));vec(v);}
CCameraControl*camera(CResourceManager*p){num(211);num(p==&level->resources);return (seed/3)%3?client->camera:NULL;}
void start(CParticle*p){num(223);num(id(p));}
void outline(CGenericModel*p,const std::wstring&name){num(227);num(id(p));wide(name);}
void highlight(CGenericModel*p,const std::wstring&name){num(229);num(id(p));wide(name);}
const std::wstring&data(CDataGroup*,const std::wstring&name,const wchar_t*defaultValue){num(233);wide(name);wide(defaultValue);static std::wstring result;result=seed%2?L"spawn Ж":L"";return result;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){num(239);num(id(p));num(type);if(p==self)return type==28?seed%3==0:type==167?seed%5==0:type==169?seed%7==0:false;if(p==target)return type==167?seed%5==0:false;if(p==equipment[0]||p==equipment[1])return type==8?seed%5!=0:type==35?(seed+(p==equipment[1]))%3==0:false;return false;}
void destination(CCharacter*p,CLevel&l,float x,float z){num(241);num(&l==&level->level);fp(x);fp(z);p->m_isPathing=true;p->m_pathDestination=Ogre::Vector3(x,0,z);}
CCharacter*find(CLevel*p,const Ogre::Matrix4&m,EAlignment alignment,float minimum,float angle,float range,bool attached,CCharacter*exclude,CSkill*skill){num(251);num(p==&level->level);for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j)fp(m[i][j]);num(alignment);fp(minimum);fp(angle);fp(range);num(attached);num(id(exclude));num(id(skill));unsigned call=findCalls++;return (seed/7)%4==call?target:NULL;}
float skillAngle(CSkill*p){num(257);num(id(p));return value(19);}
class Character:public CCharacter{public:Character():CCharacter(NULL){}virtual void setAIState(EAIState state){num(263);num(id(this));num(state);m_eAIState=state;}virtual void reactToDamage(CCharacter*p,bool critical){num(269);num(id(this));num(id(p));num(critical);}virtual const Ogre::Matrix4&getOrientation(){num(271);num(id(this));return m_mOrientation;}};
class Equipment:public CEquipment{public:Equipment():CEquipment(NULL){}virtual void*getUnitModel(){num(277);num(id(this));return m_pUnitModel;}virtual void*getUnitModelSecondary(){num(281);num(id(this));return m_pUnitModelSecondary;}};
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;out=&capture;armed=false;findCalls=0;self=new Character;target=new Character;master=new Character;for(unsigned i=0;i<2;++i)equipment[i]=new Equipment;for(unsigned i=0;i<3;++i){attacks[i]=new CAttackDescription(i?"slash":"attack",seed%2,1,2,3,4,5,6);attacks[i]->m_animationIndex=(seed+i)%7==0?-1:int(i);attacks[i]->m_fAttackSpeed=float(seed%4+1)*.5f;}
 detour::Set setup,patches;TL_REDIRECT(setup,vLoad,&load);for(unsigned i=0;i<3;++i)models[i]=new CGenericModel(NULL,NULL,L"fixture",L"fixture",false);setup.restore();particle=new CParticle(NULL,L"fixture",NULL);skill=new CSkill(NULL,NULL);skill->m_iTargetAlignment=seed%7;
 CInventory*inventory=new CInventory(self,17);self->m_pInventory=seed%11?inventory:NULL;for(unsigned i=0;i<2;++i){equipment[i]->m_pUnitModel=(seed+i)%3?models[i+1]:NULL;equipment[i]->m_pUnitModelSecondary=equipment[i]->m_pUnitModel&&(seed+i)%5?models[i+1]:NULL;for(unsigned j=i;j<12;j+=2)if((seed+j)%4){CEquipmentRef*ref=new CEquipmentRef;ref->m_pEquipment=equipment[i];ref->m_iSlot=j;inventory->m_equipmentRefs.add(ref);}}
 self->m_pResourceManager=&level->resources;self->m_pUnitModel=c.op==0||seed%13?models[0]:NULL;self->m_pDataGroup=new CDataGroup(L"fixture",NULL,2,2,new TRepository<std::wstring>(L""));self->m_targetCharacter.setObject(seed%3?target:NULL);self->m_targetItem.setObject(seed%5?equipment[0]:NULL);self->m_pMaster=seed%3?master:NULL;self->m_activeSkill=seed%7?skill:NULL;self->m_attackItem=seed%5?equipment[0]:NULL;self->m_attack=seed%7?attacks[2]:NULL;if(seed%11)self->m_attacks.push_back(attacks[0]);const float times[]={-.1f,0,.2f};self->m_attackTime=times[(seed/3)%3];self->m_skillTime=times[(seed/7)%3];self->m_skillLooping=(seed/13)%7==0;self->m_skillInterrupted=(seed/17)%2;self->m_attackFlag1F5=seed%17==0;self->m_moveInputHeld=(seed/3)%3==0;self->m_attackRangeScale=value(7);self->m_fidgetTime=value(9);self->m_pAIManager=seed%3?new CAIManager(self):NULL;self->m_alignment=static_cast<EAlignment>(seed%7);self->m_Padding4A1[0]=seed%5!=0;self->m_bEnabled=seed%3!=0;self->m_bVisible=(seed/11)%3!=0;self->m_bInActiveRange=seed%7!=0;self->m_levelSound=seed%5?new CSoundBank(*audio,false):NULL;self->m_equipmentParticles[5]=(seed/3)%3?particle:NULL;self->m_currentOpacity=.6f;self->m_vPosition=Ogre::Vector3(value(5),value(6),value(7));target->m_vPosition=Ogre::Vector3(value(8),-9,value(10));master->m_vPosition=Ogre::Vector3(3,4,5);models[0]->m_vPosition=Ogre::Vector3(7,8,9);self->m_mOrientation=Ogre::Matrix4(Ogre::Quaternion(Ogre::Radian(seed*.1f),Ogre::Vector3::UNIT_Y));master->m_mOrientation=Ogre::Matrix4(Ogre::Quaternion(Ogre::Radian(-float(seed)*.07f),Ogre::Vector3::UNIT_Y));self->m_viewAngle=value(11);self->m_sightRange=value(12);float minimum=value(13);std::memcpy(self->m_Padding36C,&minimum,sizeof(minimum));self->m_fBaseUnitValue194=value(14);target->m_fBaseUnitValue194=value(15);equipment[0]->m_fBaseUnitValue194=value(16);
#define PATCH(n,f) TL_REDIRECT(patches,v##n,&f)
 PATCH(Select,select);PATCH(Range,range);PATCH(Melee,melee);PATCH(Ranged,ranged);PATCH(Effect,effect);PATCH(Flag,flag);PATCH(Length,length);PATCH(Clear,clear);PATCH(Blend,blend);PATCH(Queue,queue);PATCH(Theme,theme);PATCH(Position,position);PATCH(SetPosition,setPosition);PATCH(Sound,sound);PATCH(Exists,exists);PATCH(RandomAnimation,animation);PATCH(Play,play);PATCH(Invisible,invisible);PATCH(Opacity,opacity);PATCH(Behind,behind);PATCH(Active,active);PATCH(Camera,camera);PATCH(Particle,start);PATCH(Outline,outline);PATCH(Highlight,highlight);PATCH(Data,data);PATCH(ISA,isa);PATCH(Destination,destination);PATCH(Find,find);PATCH(SkillAngle,skillAngle);
#undef PATCH
 if(patches.failed())_exit(43);armed=true;
 if(c.op==0){typedef bool(*F)(CCharacter*);F fn=ours?vNewAttack:vOldAttack;if(!autotest::beginInvocation(capture,fn))return;num(fn(self));capture.callCompleted=1;}
 else if(c.op==1){typedef void(*F)(CCharacter*);F fn=ours?vNewSpawn:vOldSpawn;autotest::invoke(capture,fn,self);}
 else if(c.op==2){typedef CCharacter*(*F)(CCharacter*,EAlignment,bool);F fn=ours?vNewSight:vOldSight;if(!autotest::beginInvocation(capture,fn))return;CCharacter*result=fn(self,static_cast<EAlignment>(seed%8),seed&1);if(ours&&c.control)result=result?NULL:target;num(id(result));capture.callCompleted=1;}
 else{typedef void(*F)(CCharacter*,EAlignment);F fn=ours?vNewAlignment:vOldAlignment;autotest::invoke(capture,fn,self,static_cast<EAlignment>(seed%8));}
 if(ours&&c.control){if(c.op==0)self->m_attackEvent=!self->m_attackEvent;else if(c.op==1)self->m_eAIState=static_cast<EAIState>(unsigned(self->m_eAIState)^1);else if(c.op==3)self->m_alignment=static_cast<EAlignment>(unsigned(self->m_alignment)^1);}num(self->m_eAIState);num(self->m_alignment);num(id(self->m_attack));num(self->m_Padding4A1[0]);num(self->m_Padding4D0[0]);num(self->m_attackEvent);fp(self->m_attackTime);fp(self->m_fidgetTime);fp(self->m_currentOpacity);vec(self->m_pathDestination);vec(particle->m_vPosition);armed=false;}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned op){int failures=0;const uintptr_t address[]={(uintptr_t)&vOldAttack,(uintptr_t)&vOldSpawn,(uintptr_t)&vOldSight,(uintptr_t)&vOldAlignment};autotest::Coverage coverage("character_visual_runtime",address[op]);for(unsigned i=0;i<4096;++i){Case c={op,i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    visual op%u seed%u status%d/%d issue%u/%u bytes%lu/%lu\n",op,i,a.status,b.status,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}coverage.report(host);return failures;}}coverage.report(host);Case c={op,19,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    visual op%u negative detected%u\n",op,unsigned(caught));return failures;}
}
TL_TEST(character_visual_runtime){initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;menugui::Audio ownedAudio(native.master);menugui::Client ownedClient(*native.settings,native.master,*native.master->m_pSoundManager);client=&ownedClient;audio=native.master->m_pSoundManager;finishlevel::Fixture ownedLevel;ownedLevel.resources.m_pSceneManager=native.scene;ownedLevel.resources.m_pLevel=&ownedLevel.level;level=&ownedLevel;int failures=0;for(unsigned op=0;op<4;++op){failures+=run(host,op);if(failures)break;}return failures;}
