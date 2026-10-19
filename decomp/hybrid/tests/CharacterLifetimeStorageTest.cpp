#include <execinfo.h>
#include <fcntl.h>
#include <ucontext.h>
#include <cstring>
#include <vector>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "CharacterSaveState.h"
#include "ItemSaveState.h"
#include "Equipment.h"
#include "Inventory.h"
#include "Effect.h"
#include "EffectManager.h"
#include "AIManager.h"
#include "GenericModel.h"
#include "Path.h"
#include "PathController.h"
#include "AstarPathfinder.h"
#include "Particle.h"
#include "SoundManager.h"
#include "SoundBank.h"
#include "Wardrobe.h"
#include "WeaponTrail.h"
#include "CollisionModel.h"
#include "FileSystem.h"
#include "Skill.h"
#include "SkillManager.h"
#include "AttackDescription.h"
#undef protected
#undef private
#include "NativeMenuServices.h"
#include "tests/FinishLevelFixture.h"
#include <OgreMeshManager.h>
#include <OgreMesh.h>
#include <OgreEntity.h>
TL_ORIGINAL(void,lifeOldFill,(CCharacter*,CCharacterSaveState&),"_ZN10CCharacter13fillSaveStateER19CCharacterSaveState")
TL_ORIGINAL(void,lifeOldClean,(CCharacter*),"_ZN10CCharacter22deleteUnitSpecificDataEv")
TL_ORIGINAL(void,lifeOldDtor,(CCharacter*),"_ZN10CCharacterD1Ev")
TL_ORIGINAL(void,lifeNativeSave,(CCharacterSaveState*,FILE*),"_ZN19CCharacterSaveState4saveEP8_IO_FILE")
extern "C" void lifeNewFill(CCharacter*,CCharacterSaveState&) __asm__("_ZN10CCharacter13fillSaveStateER19CCharacterSaveState");
extern "C" void lifeNewClean(CCharacter*) __asm__("_ZN10CCharacter22deleteUnitSpecificDataEv");
extern "C" void lifeNewDtor(CCharacter*) __asm__("_ZN10CCharacterD1Ev");
TL_FUNCTION(lifeModelLoad,"_ZN13CGenericModel9loadModelESbIwSt11char_traitsIwESaIwEES3_bbb")
TL_FUNCTION(lifeWardrobeUpdate,"_ZN9CWardrobe6updateEP10CInventory")
TL_FUNCTION(lifeFileInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(lifeCollision,"_ZN22CMasterResourceManager20removeCollisionModelEP15CCollisionModel")
TL_FUNCTION(lifeRoom,"_ZN6CLevel28getRoomIndexThatPositionIsInERKN4Ogre7Vector3E")
TL_FUNCTION(lifeItemSave,"_ZN14CItemSaveState4saveEP8_IO_FILE")
TL_FUNCTION(lifeCalculate,"_ZN7CEffect18calculateBaseValueENS_15ECALCULATETYPESE")
namespace {
struct Case{unsigned op,seed,control;};autotest::Capture*out;bool armed;unsigned seed;CCharacter*self;CCollisionModel*collision;nativegame::Services*sharedServices;finishlevel::Fixture*sharedLevel;
unsigned diagnosticPhase,diagnosticOperation;bool diagnosticOurs;
void signalTrace(int signal,siginfo_t*info,void*context){
 int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/character/character-life-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);
 if(fd>=0){char line[220];ucontext_t*uc=static_cast<ucontext_t*>(context);int n=std::snprintf(line,sizeof(line),"signal=%d side=%u op=%u seed=%u phase=%u rip=%llx addr=%p\n",signal,unsigned(diagnosticOurs),diagnosticOperation,seed,diagnosticPhase,(unsigned long long)uc->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,line,n);void*stack[48];int count=backtrace(stack,48);backtrace_symbols_fd(stack,count,fd);close(fd);}raise(signal);
}
void installSignalTrace(){struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_sigaction=&signalTrace;sigemptyset(&action.sa_mask);action.sa_flags=SA_SIGINFO|SA_RESETHAND;sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);}

void num(unsigned n){if(armed)out->add(&n,4);}void fp(float v){if(armed)out->add(&v,4);}
void initEmptyGlobals(){
 const uintptr_t a[]={0x14286f0,0x1428720,0x1429ea0,0x1476060,0x14781e0,0x1479460,0x147c340,0x147e8e0,0x147fac0,0x1480a40,0x1482e00,0x1484120,0x14872e0,0x148e500,0x148f960,0x14afec0,0x14b3300,0x14b5868,0x14b58e8,0x14e68b0,0x14ee340,0x14f2668,0x1500740,0x1500820,0x15019a0,0x150b428,0x150c8a0,0x150c980};
 for(unsigned i=0;i<sizeof(a)/sizeof(a[0]);++i){void*p;std::memcpy(&p,(void*)a[i],sizeof(p));if(!p)new((void*)a[i])std::string;}
 const uintptr_t b[]={0x14286f8,0x1428728,0x1429ea8,0x1476068,0x14781e8,0x1479468,0x147c348,0x147e8e8,0x147fac8,0x1480a48,0x1482e08,0x1484128,0x14872e8,0x148e508,0x148f968,0x14afec8,0x14b3308,0x14b5870,0x14b58f0,0x14e68b8,0x14ee348,0x14f2670,0x1500748,0x1500828,0x15019a8,0x150b430,0x150c8a8,0x150c988};
 for(unsigned i=0;i<sizeof(b)/sizeof(b[0]);++i){void*p;std::memcpy(&p,(void*)b[i],sizeof(p));if(!p)new((void*)b[i])std::wstring;}
}
void modelLoad(CGenericModel*,std::wstring,std::wstring,bool,bool,bool){}
void wardrobeUpdate(CWardrobe*,CInventory*){}
bool fileInfo(CFileSystem*,const std::wstring&,CFileInfo&info,bool,bool,bool){info.m_bExists=false;return false;}
void removeCollision(CMasterResourceManager*,CCollisionModel*p){num(101);num(p==collision?1:p?99:0);}
int room(CLevel*,const Ogre::Vector3&v){num(103);fp(v.x);fp(v.y);fp(v.z);return int(seed)-17;}
void itemSave(CItemSaveState*p,FILE*f){num(107);num(p->m_iIndex);num(p->m_iStackSize);fwrite(&p->m_iIndex,4,1,f);fwrite(&p->m_iStackSize,4,1,f);}
float calculate(CEffect*p,CEffect::ECALCULATETYPES mode){num(109);num(mode);for(unsigned i=0;i<4;++i)fp(p->m_values[i]);p->m_fValueC0=p->m_values[0]+7;return p->m_fValueC0;}
struct Equipment: CEquipment {Equipment():CEquipment(NULL){}virtual void fillSaveState(CItemSaveState&s,int index,bool flag){num(113);num(index);num(flag);s.m_iIndex=index;s.m_iStackSize=seed+index;s.m_sItemName=L"fixture equipment";}};
struct Witness{TSafePointer<CRunicCore>*pointer;bool cleanup;};std::vector<Witness>witnesses;
void witness(CRunicCore*p,bool cleanup){Witness w={new TSafePointer<CRunicCore>,cleanup};w.pointer->setObject(p);witnesses.push_back(w);}
CEffect*effect(unsigned index){CEffect*p=new CEffect(static_cast<EEFFECT_TYPE>(0),false,static_cast<EEFFECT_ACTIVATION>(index%3),1.5f,2.25f,3,false);p->m_eDamageType=static_cast<EDAMAGE_TYPES>(0);p->m_sName=L"saved-effect";p->m_name88=L"second";p->m_name90=L"";p->m_particleName=L"";p->m_flag33=(seed+index)%3!=0;p->m_modifierFlag32=false;p->m_flag31=0;p->m_fValueC0=index+19.25f;return p;}
void state(CCharacterSaveState*p){FILE*f=tmpfile();if(!f)_exit(45);lifeNativeSave(p,f);long size=ftell(f);num(size);rewind(f);char bytes[4096];while(size_t n=fread(bytes,1,sizeof(bytes),f))out->add(bytes,n);fclose(f);}
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);out=&capture;armed=false;seed=c.seed;diagnosticOurs=ours;diagnosticOperation=c.op;diagnosticPhase=1;installSignalTrace();witnesses.clear();nativegame::Services&services=*sharedServices;services.master->m_pSceneManager=services.scene;finishlevel::Fixture&level=*sharedLevel;level.level.m_iLevelDepth=int(seed)-3;
 detour::Set constructors,boundaries;TL_REDIRECT(constructors,lifeModelLoad,&modelLoad);TL_REDIRECT(constructors,lifeWardrobeUpdate,&wardrobeUpdate);TL_REDIRECT(constructors,lifeFileInfo,&fileInfo);TL_REDIRECT(boundaries,lifeCollision,&removeCollision);TL_REDIRECT(boundaries,lifeRoom,&room);TL_REDIRECT(boundaries,lifeItemSave,&itemSave);TL_REDIRECT(boundaries,lifeCalculate,&calculate);if(constructors.failed()||boundaries.failed())_exit(43);
 self=new CCharacter(&level.resources);self->m_pSceneManager=services.scene;self->m_pSceneNode=services.scene->getRootSceneNode()->createChildSceneNode();CCharacter*master=new CCharacter(NULL);self->m_pMaster=seed&1?master:NULL;if(self->m_pMaster){master->m_Followers.push_back(self);master->m_followerFlags.push_back(true);}witness(self,false);
 self->m_vPosition=Ogre::Vector3(seed*.25f,-5,seed*.5f);self->m_iRoomIndex=seed%3==0?-1:int(seed)+29;self->m_iUnitLevel=seed+7;self->m_fameLevel=int(seed)-5;self->m_iUnitValue1A0=0x1122334400000000LL+seed;self->setGuid(0x1122000000000000LL+seed);self->setOriginalGuid(0x2211000000000000LL+seed);master->setOriginalGuid(0x3322000000000000LL+seed);self->m_originalUnitGuid=0x5566778800000000LL+seed;self->m_iSpawnerGuid=0x3344556600000000LL+seed;self->m_iQuestGuid=seed+111;self->m_iQuestState=seed+9;self->m_forcedHidden=seed&1;self->m_bSaveFlag191=seed&2;self->m_alignment=static_cast<EAlignment>(seed%7);self->m_transformationTime=seed*.5f;self->m_townTravelTime=-float(seed);self->m_champion=seed%3==0;self->m_petMode=seed%5;self->m_bSecondaryWeaponSet=seed%3==1;self->m_playTime=seed*2.25f;self->m_vScale=Ogre::Vector3(seed*.25f,3,7);self->m_bravery=-float(seed)*.125f;self->m_experience=seed*17;self->m_fame=seed*19;self->m_fHPFloat=seed*.75f;self->m_maxHPBase=seed+41;self->m_maxHPBonus=-int(seed)-31;self->m_fManaFloat=seed*1.25f;self->m_maxManaBase=seed+71;self->m_maxManaBonus=seed*.75f-2.5f;self->m_defenseStat=seed+13;self->m_magicStat=seed+17;self->m_rangedStat=seed+19;self->m_iMeleeStat=seed+23;self->m_experienceReward=seed+31;self->m_fameReward=seed+43;self->m_bEnabled=seed&1;self->m_iUnusedStatPoints=seed+47;self->m_iUnusedSkillPoints=seed+53;self->m_iUnusedPerkPoints=seed+59;self->m_iGold=seed*71;self->m_characterDisplayName=L"fixture character Ж";self->m_activeSkillGuid=0x1234500012345678LL;self->m_leftSkillGuid=0x98765432123LL;self->m_leftMouseSkillGuid=-171;for(unsigned i=0;i<7;++i)self->m_damageDefense[i]=int(i*17)-seed;for(unsigned i=0;i<4;++i){self->m_knownSpells[i]=i%2?L"fire Ж":L"";self->m_knownSpellLevels[i]=seed+i;}
 CPathController*borrowed=new CPathController(NULL);self->m_pathToFollow.setObject(borrowed);TSafePointer<CPathController>borrowedWeak;borrowedWeak.setObject(borrowed);
 if(c.op==0){if(seed%4){self->m_pSkillManager=new CSkillManager(NULL,self);for(unsigned i=0;i<seed%5;++i){CSkill*p=new CSkill(NULL,NULL);p->m_skillLevel=seed+i*7;self->m_pSkillManager->m_OtherSkills.add(p);}}
  if(seed%3){self->m_pInventory=new CInventory(self,17);for(unsigned i=0;i<seed%4;++i){CEquipmentRef*p=new CEquipmentRef;p->m_pEquipment=new Equipment;p->m_iSlot=int(i)-3;p->m_flag20=(seed+i)%2;self->m_pInventory->m_equipmentRefs.add(p);}}
  if(seed%5){self->m_pEffectManager=new CEffectManager(self);for(unsigned g=0;g<3;++g)for(unsigned i=0;i<(seed+g)%4;++i)self->m_pEffectManager->getActiveEffects(g).add(effect(i+g));}
 }
 else{
  if(seed&1){self->m_pAIManager=new CAIManager(self);witness(self->m_pAIManager,false);}if(seed&2){self->m_deathPath=new CPath("death",false,Ogre::Vector3(0,0,0));witness(self->m_deathPath,false);}if(seed&4){self->m_movementPath=new CPath("move",true,Ogre::Vector3(1,2,3));witness(self->m_movementPath,false);}if(seed&8){self->m_pathfinder=new CAstarPathfinder(0,0,0,0,NULL,NULL,1);witness(self->m_pathfinder,false);}if(seed&16){self->m_pInventory=new CInventory(self,17);witness(self->m_pInventory,false);}
  for(unsigned i=0;i<4;++i)if((seed>>i)&1){self->m_weaponTrails[i]=new CWeaponTrail(services.scene,std::string("lifetime-trail-")+char('0'+i),3,.5f);witness(self->m_weaponTrails[i],false);}
  for(unsigned i=0;i<seed%4;++i){CCharacter::CParticleAnimationTrigger*p=new CCharacter::CParticleAnimationTrigger;p->m_resources=NULL;p->m_particle=NULL;p->m_node=NULL;p->m_nodeOwner=NULL;self->m_particleTriggers.add(p);witness(p,true);}for(unsigned i=0;i<seed%4;++i){CParticle*p=i%2?NULL:new CParticle(NULL,L"fixture",&level.resources);self->m_equipmentParticles.add(p);if(p)witness(p,true);}
  if(seed&1){self->m_pPaperdollModel=new CGenericModel(NULL,NULL,L"fixture",L"fixture",false);witness(self->m_pPaperdollModel,true);}if(seed&2){self->m_pUnitModel=new CGenericModel(NULL,NULL,L"fixture",L"fixture",false);witness(self->m_pUnitModel,false);}
  for(unsigned i=0;i<seed%4;++i){CAttackDescription*p=i%2?NULL:new CAttackDescription("attack",false,1,2,3,4,5,6);self->m_attacks.push_back(p);if(p)witness(p,true);}self->m_attack=self->m_attacks.size()?self->m_attacks[0]:NULL;
  if(seed&4){self->m_levelSound=new CSoundBank(*services.master->m_pSoundManager,false);witness(self->m_levelSound,true);}if(seed&8){self->m_secondarySound=new CSoundBank(*services.master->m_pSoundManager,true);witness(self->m_secondarySound,true);}
  Ogre::SceneNode**nodes[]={&self->m_pRightHandNode,&self->m_fishingNode,&self->m_pLeftHandNode,&self->m_pShieldNode,&self->m_pRightShoulderNode,&self->m_pLeftShoulderNode,&self->m_pHeadNode};for(unsigned i=0;i<7;++i)if((seed+i)%3==0){*nodes[i]=self->m_pSceneNode->createChildSceneNode();(*nodes[i])->createChildSceneNode();}
  if(seed&16){CGenericModel*model=self->m_pUnitModel?self->m_pUnitModel:self->m_pPaperdollModel;if(model){self->m_wardrobe=new CWardrobe(self,services.scene,services.scene,model,model,L"missing-base.dds",L"",L"",L"",L"",L"");witness(self->m_wardrobe,true);}}
  if(seed%3){diagnosticPhase=50;unsigned i=(seed/2)%12;Ogre::MeshPtr mesh=Ogre::MeshManager::getSingleton().createManual("character-lifetime-mesh","General");mesh->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1));Ogre::Entity*entity=services.scene->createEntity("character-lifetime-entity",mesh->getName());if(seed&1)self->m_pSceneNode->attachObject(entity);if(seed&2)self->m_PaperdollItemsSecondary[i]=entity;else self->m_PaperdollItems[i]=entity;}
 }
 diagnosticPhase=60;collision=seed&32?new CCollisionModel(services.scene,L""):NULL;self->m_collisionModel=collision;constructors.restore();diagnosticPhase=90;armed=true;
 if(c.op==0){CCharacterSaveState*p=new CCharacterSaveState;p->m_values.push_back(999);p->m_strings.add(L"preexisting mod");if(seed&1){CItemSaveState*q=new CItemSaveState;q->m_iIndex=-3;q->m_iStackSize=7;p->m_pets.push_back(q);p->m_items[1].push_back(effect(9));}typedef void(*F)(CCharacter*,CCharacterSaveState&);F fn=ours?lifeNewFill:lifeOldFill;if(!autotest::beginInvocation(capture,fn))return;fn(self,*p);capture.callCompleted=1;if(ours&&c.control)p->m_guid50^=1;state(p);num(self->m_iRoomIndex);std::vector<TSafePointer<CRunicCore>*>owned;for(unsigned i=0;i<p->m_pets.size();++i){TSafePointer<CRunicCore>*w=new TSafePointer<CRunicCore>;w->setObject(p->m_pets[i]);owned.push_back(w);}for(unsigned g=0;g<3;++g)for(unsigned i=0;i<p->m_items[g].size();++i){TSafePointer<CRunicCore>*w=new TSafePointer<CRunicCore>;w->setObject(p->m_items[g][i]);owned.push_back(w);}delete p;for(unsigned i=0;i<owned.size();++i){num(owned[i]->getObject()==NULL);if(owned[i]->getObject())capture.issue=autotest::Capture::InvalidReport;delete owned[i];}}
 else{typedef void(*F)(CCharacter*);F fn=c.op==1?(ours?lifeNewClean:lifeOldClean):(ours?lifeNewDtor:lifeOldDtor);diagnosticPhase=100;autotest::invoke(capture,fn,self);diagnosticPhase=101;if(ours&&c.control)borrowedWeak.setObject(NULL);if(c.op==1){num(self->m_particleTriggers.size());num(self->m_equipmentParticles.size());for(unsigned i=0;i<self->m_equipmentParticles.size();++i)num(self->m_equipmentParticles[i]==NULL);num(self->m_attacks.size());num(self->m_attack==NULL);num(self->m_pPaperdollModel==NULL);num(self->m_wardrobe==NULL);num(self->m_levelSound==NULL);num(self->m_secondarySound==NULL);num(self->m_pRightHandNode==NULL);num(self->m_fishingNode==NULL);num(self->m_pLeftHandNode==NULL);num(self->m_pShieldNode==NULL);num(self->m_pRightShoulderNode==NULL);num(self->m_pLeftShoulderNode==NULL);num(self->m_pHeadNode==NULL);}
  for(unsigned i=0;i<witnesses.size();++i){bool invalid=witnesses[i].pointer->getObject()==NULL;num(invalid);if((c.op==2||witnesses[i].cleanup)&&!invalid)capture.issue=autotest::Capture::InvalidReport;}num(master->m_Followers.size());num(borrowedWeak.getObject()==borrowed);}
 armed=false;if(c.op!=2)lifeOldDtor(self);Ogre::NedAllocImpl::deallocBytes(self);delete collision;delete borrowed;for(unsigned i=0;i<witnesses.size();++i)delete witnesses[i].pointer;witnesses.clear();
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned op,unsigned count){int failures=0;uintptr_t addresses[]={(uintptr_t)&lifeOldFill,(uintptr_t)&lifeOldClean,(uintptr_t)&lifeOldDtor};autotest::Coverage coverage("character_lifetime_storage",addresses[op]);for(unsigned i=0;i<count;++i){Case c={op,i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    life op%u seed%u status%d/%d issue%u/%u bytes%lu/%lu\n",op,i,a.status,b.status,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}for(unsigned k=0;k<80&&k<a.capture.length&&k<b.capture.length;++k)host->log("    raw%u %02x/%02x\n",k,(unsigned char)a.capture.data[k],(unsigned char)b.capture.data[k]);coverage.report(host);return failures;}}coverage.report(host);Case c={op,19,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||memcmp(a.capture.data,b.capture.data,a.capture.length)!=0;TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    life op%u negative detected %u\n",op,unsigned(caught));return failures;}
}
TL_TEST(character_lifetime_storage){initEmptyGlobals();nativegame::Services services;if(!services.ready())return 1;finishlevel::Fixture level;level.resources.m_pSceneManager=services.scene;level.resources.m_pLevel=&level.level;menugui::Audio audio(services.master);sharedServices=&services;sharedLevel=&level;int failures=0;for(unsigned op=0;op<3;++op){failures+=run(host,op,op==0?32:64);if(failures)return failures;}return failures;}
