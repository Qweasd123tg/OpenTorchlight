#include <cstring>
#include <cmath>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "Equipment.h"
#include "Inventory.h"
#include "GenericModel.h"
#include "AttackDescription.h"
#include "WeaponTrail.h"
#include "ResourceManager.h"
#undef private
#undef protected
#include "tests/NativeGameServices.h"
TL_ORIGINAL(void,oldSelect,(CCharacter*,EATTACK_RANGE_TYPE),"_ZN10CCharacter12selectAttackE18EATTACK_RANGE_TYPE")
TL_ORIGINAL(void,oldTurn,(CCharacter*,const Ogre::Vector3&,float),"_ZN10CCharacter10turnTowardERKN4Ogre7Vector3Ef")
extern "C" void newSelect(CCharacter*,EATTACK_RANGE_TYPE) __asm__("_ZN10CCharacter12selectAttackE18EATTACK_RANGE_TYPE");
extern "C" void newTurn(CCharacter*,const Ogre::Vector3&,float) __asm__("_ZN10CCharacter10turnTowardERKN4Ogre7Vector3Ef");
TL_FUNCTION(selectModelLoad,"_ZN13CGenericModel9loadModelESbIwSt11char_traitsIwESaIwEES3_bbb")
TL_FUNCTION(selectAnimation,"_ZN13CGenericModel19findRandomAnimationERKSs")
TL_FUNCTION(selectISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(selectMaterial,"_ZN12CWeaponTrail15setMaterialNameERKSs")
TL_FUNCTION(selectEntity,"_ZN12CWeaponTrail15setWeaponEntityEPN4Ogre6EntityE")
TL_FUNCTION(selectRandom,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(selectEffect,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
namespace {
struct Case{unsigned op,seed,control;};unsigned seed;bool armed;autotest::Capture*out;nativegame::Services*services;CCharacter*self,*master;CEquipment*equipment[2];CAttackDescription*attacks[4];
void num(unsigned n){if(armed)out->add(&n,4);}void fp(float f){if(armed)out->add(&f,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void text(const std::string&s){num(s.size());if(armed)out->add(s.data(),s.size());}
unsigned identity(const void*p){if(!p)return 0;for(unsigned i=0;i<2;++i)if(p==equipment[i])return i+1;for(unsigned i=0;i<4;++i)if(p==attacks[i])return i+11;return 99;}
void initEmptyGlobals(){
 const uintptr_t a[]={0x14286f0,0x1428720,0x1429ea0,0x1476060,0x14781e0,0x1479460,0x147c340,0x147e8e0,0x147fac0,0x1480a40,0x1482e00,0x1484120,0x14872e0,0x148e500,0x148f960,0x14afec0,0x14b3300,0x14b5868,0x14b58e8,0x14e68b0,0x14ee340,0x14f2668,0x1500740,0x1500820,0x15019a0,0x150b428,0x150c8a0,0x150c980};
 for(unsigned i=0;i<sizeof(a)/sizeof(a[0]);++i){void*p;std::memcpy(&p,(void*)a[i],sizeof(p));if(!p)new((void*)a[i])std::string;}
 const uintptr_t b[]={0x14286f8,0x1428728,0x1429ea8,0x1476068,0x14781e8,0x1479468,0x147c348,0x147e8e8,0x147fac8,0x1480a48,0x1482e08,0x1484128,0x14872e8,0x148e508,0x148f968,0x14afec8,0x14b3308,0x14b5870,0x14b58f0,0x14e68b8,0x14ee348,0x14f2670,0x1500748,0x1500828,0x15019a8,0x150b430,0x150c8a8,0x150c988};
 for(unsigned i=0;i<sizeof(b)/sizeof(b[0]);++i){void*p;std::memcpy(&p,(void*)b[i],sizeof(p));if(!p)new((void*)b[i])std::wstring;}
}

void load(CGenericModel*,std::wstring,std::wstring,bool,bool,bool){}
int animation(CGenericModel*,const std::string&name){num(101);text(name);return int(seed%19)-7;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){num(103);num(identity(p));num(type);unsigned kind=(seed/5)%8;return type==8?kind!=0:type==35?kind==1||kind==3:type==60?kind==2||kind==3:type==102?kind==4:false;}
void material(CWeaponTrail*p,const std::string&name){num(107);text(name);p->m_material=name;}
void entity(CWeaponTrail*p,Ogre::Entity*value){num(109);num(value!=NULL);p->m_weaponEntity=value;}
int random(int minimum,int maximum){num(113);num(minimum);num(maximum);return minimum+int(seed%unsigned(maximum-minimum+1));}
float effect(CCharacter*p,EEFFECT_TYPE type,EDAMAGE_TYPES damage){num(127);num(p==self?1:p==master?2:99);num(type);num(damage);const float values[]={-200,-100,-11,-10,-1,0,1,9.99f,10,10.01f,100,200};if(type==21)return values[(seed/7)%12];if(type==140)return values[(seed/13)%12];return values[(seed/17)%12];}
class Character:public CCharacter{public:Character():CCharacter(NULL){}virtual void setOrientation(const Ogre::Matrix4&m,bool translate){num(131);num(translate);CPositionableObject::setOrientation(m,translate);}virtual void extractOrientationVectors(){num(137);CPositionableObject::extractOrientationVectors();}};
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;out=&capture;armed=false;self=new Character;master=new Character;equipment[0]=new CEquipment(NULL);equipment[1]=new CEquipment(NULL);for(unsigned i=0;i<4;++i)attacks[i]=new CAttackDescription(i%2?"slash":"attack",false,1,2,3,4,5,6);
 detour::Set setup,patches;TL_REDIRECT(setup,selectModelLoad,&load);CGenericModel*model=new CGenericModel(NULL,NULL,L"fixture",L"fixture",false);CGenericModel*weaponModel=new CGenericModel(NULL,NULL,L"fixture",L"fixture",false);setup.restore();CResourceManager resources(NULL);resources.m_pSceneManager=services->scene;self->m_pResourceManager=&resources;CInventory*inventory=new CInventory(self,17);self->m_pInventory=seed%9?inventory:NULL;self->m_pUnitModel=seed%11?model:NULL;self->m_attackItem=equipment[1];self->m_attack=seed%3?attacks[3]:NULL;const float times[]={-1,0,.01f,1};self->m_attackTime=times[(seed/3)%4];self->m_attackFlag37E=seed&1;self->m_alignment=static_cast<EAlignment>((seed/7)%3);
 for(unsigned i=0;i<2;++i){equipment[i]->m_pAttackDescription=(seed+i)%5?attacks[2*i]:NULL;equipment[i]->m_pAttackDescriptionOverride=(seed+i)%7?attacks[2*i+1]:NULL;equipment[i]->m_pUnitModel=weaponModel;if((seed/(i?33:11))%3){CEquipmentRef*ref=new CEquipmentRef;ref->m_pEquipment=equipment[i];ref->m_iSlot=i;inventory->m_equipmentRefs.add(ref);}}
 if(seed%4){self->m_attacks.push_back(seed%7?attacks[0]:NULL);if(seed%2)self->m_attacks.push_back(attacks[1]);}
 for(unsigned i=0;i<2;++i)if((seed>>i)&1)self->m_weaponTrails[i]=new CWeaponTrail(services->scene,std::string("selection-trail-")+char('0'+i),20,1);
 TL_REDIRECT(patches,selectAnimation,&animation);TL_REDIRECT(patches,selectISA,&isa);TL_REDIRECT(patches,selectMaterial,&material);TL_REDIRECT(patches,selectEntity,&entity);TL_REDIRECT(patches,selectRandom,&random);TL_REDIRECT(patches,selectEffect,&effect);if(patches.failed())_exit(43);
 if(c.op==0){armed=true;typedef void(*F)(CCharacter*,EATTACK_RANGE_TYPE);F fn=ours?newSelect:oldSelect;autotest::invoke(capture,fn,self,static_cast<EATTACK_RANGE_TYPE>(seed%5));if(ours&&c.control)self->m_attack=attacks[2];num(identity(self->m_attack));num(identity(self->m_attackItem));for(unsigned i=0;i<4;++i)num(attacks[i]->m_animationIndex);for(unsigned i=0;i<2;++i){num(self->m_weaponTrails[i]!=NULL);if(self->m_weaponTrails[i])text(self->m_weaponTrails[i]->m_material);}}
 else{const float rates[]={-3,0,.01f,.5f,1,3,1000};const float elapsed[]={0,.0001f,.016f,.1f,1,5};float a=float(int(seed%41)-20)*.173f;self->m_mOrientation=Ogre::Matrix4(Ogre::Quaternion(Ogre::Radian(a),Ogre::Vector3::UNIT_Y));self->CPositionableObject::extractOrientationVectors();self->m_eAIState=static_cast<EAIState>((seed/5)%42);self->m_turnRate288=rates[(seed/3)%7];self->m_Padding730[0]=(seed/11)%2;self->m_turnFlag265=seed%3==0;self->m_pMaster=seed&1?master:NULL;Ogre::Vector3 direction(float(int((seed*13)%29)-14),5,float(int((seed*17)%31)-15));armed=true;typedef void(*F)(CCharacter*,const Ogre::Vector3&,float);F fn=ours?newTurn:oldTurn;if(!autotest::beginInvocation(capture,fn))return;fn(self,direction,elapsed[(seed/7)%6]);capture.callCompleted=1;if(ours&&c.control)self->m_turnFlag265=!self->m_turnFlag265;for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j)fp(self->m_mOrientation[i][j]);vec(self->m_targetDirection);vec(self->m_vForward);vec(self->m_vRight);vec(self->m_vUp);num(self->m_turnFlag265);}
 armed=false;self->m_pResourceManager=NULL;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned op){int failures=0;const uintptr_t addr[]={(uintptr_t)&oldSelect,(uintptr_t)&oldTurn};autotest::Coverage coverage("character_selection_turn",addr[op]);for(unsigned i=0;i<4096;++i){Case c={op,i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    selection op%u seed%u status%d/%d issue%u/%u bytes%lu/%lu\n",op,i,a.status,b.status,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}coverage.report(host);return failures;}}coverage.report(host);Case c={op,19,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    selection op%u negative detected %u\n",op,unsigned(caught));return failures;}
}
TL_TEST(character_selection_turn){initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;services=&native;int failures=run(host,0);if(!failures)failures+=run(host,1);return failures;}
