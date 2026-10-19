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
#include "ItemGold.h"
#include "Equipment.h"
#include "Inventory.h"
#include "GameUI.h"
#include "SoundBank.h"
#undef private
#undef protected
#include "MenuGuiFixture.h"
#include "tests/FinishLevelFixture.h"
namespace {
#include "CharacterEmptyGlobals.h"
}
TL_ORIGINAL(void,giOld,(CCharacter*,CItem*,CLevel&),"_ZN10CCharacter7getItemEP5CItemR6CLevel")
extern "C" void giNew(CCharacter*,CItem*,CLevel&) __asm__("_ZN10CCharacter7getItemEP5CItemR6CLevel");
TL_FUNCTION(giISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(giGoldTake,"_ZN9CItemGold13playTakeSoundEPN4Ogre9SceneNodeE")
TL_FUNCTION(giTake,"_ZN10CEquipment13playTakeSoundEPN4Ogre9SceneNodeE")
TL_FUNCTION(giGold,"_ZN10CCharacter8giveGoldEi")
TL_FUNCTION(giTarget,"_ZN10CCharacter13setTargetItemEP5CItem")
TL_FUNCTION(giTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(giText,"_ZN7CGameUI12addTextEventERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_")
TL_FUNCTION(giDelete,"_ZN6CLevel10deleteItemEP5CItem")
TL_FUNCTION(giRemove,"_ZN6CLevel10removeItemEP5CItemb")
TL_FUNCTION(giPickup,"_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
TL_FUNCTION(giEquip,"_ZN10CInventory35equipEquipmentIntoFirstFreeLocationEP10CEquipment")
TL_FUNCTION(giCanEquip,"_ZN10CInventory8canEquipEP10CEquipmentb")
TL_FUNCTION(giPlayer,"_ZN9CBaseUnit8isPlayerEv")
TL_FUNCTION(giUI,"_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(giTip,"_ZN7CGameUI8queueTipE11EContextTip")
TL_FUNCTION(giSound,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(giAdd,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(giPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(giBehind,"_ZN10CCharacter15setRenderBehindEb")
TL_FUNCTION(giModelLoad,"_ZN9CItemGold9loadModelESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(giSampleLoad,"_ZN10CSoundBank9addSampleEix")
namespace {
struct Case{unsigned seed,control;};unsigned seed,phase;bool armed,oursSide;autotest::Capture*out;nativegame::Services*services;menugui::Fixture*menu;finishlevel::Fixture*world;CCharacter*self,*master;CEquipment*equipment[2];CItemGold*coins[2];CItem*other;
void fault(int signal,siginfo_t*info,void*context){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/character/character-get-item-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);if(fd>=0){char line[200];ucontext_t*uc=static_cast<ucontext_t*>(context);int n=std::snprintf(line,sizeof(line),"signal%d side%u seed%u phase%u rip%llx address%p\n",signal,unsigned(oursSide),seed,phase,(unsigned long long)uc->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,line,n);void*stack[40];int count=backtrace(stack,40);backtrace_symbols_fd(stack,count,fd);close(fd);}raise(signal);}
void num(unsigned x){if(armed)out->add(&x,4);}void fp(float x){if(armed)out->add(&x,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void wide(const std::wstring&s){num(s.size());if(armed)out->add(s.data(),s.size()*sizeof(wchar_t));}void narrow(const std::string&s){num(s.size());if(armed)out->add(s.data(),s.size());}unsigned id(const void*p){if(!p)return 0;if(p==self)return 1;if(p==master)return 2;if(p==other)return 3;for(unsigned i=0;i<2;++i){if(p==equipment[i])return 10+i;if(p==coins[i])return 20+i;}return 99;}
class Other:public CItem{public:Other():CItem(NULL){}virtual void setActiveInLevel(bool value){m_bEnabled=value;}virtual void*getUnitModel(){return NULL;}virtual void*getUnitCollisionModel(){return NULL;}};
class Equipment:public CEquipment{public:Equipment():CEquipment(NULL){}virtual void drop(){num(101);num(id(this));vec(m_vPosition);}};
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){num(103);num(id(p));num(type);if(type==static_cast<UNITTYPES::EUNITTYPES>(34))return p==coins[0]||p==coins[1];if(type==static_cast<UNITTYPES::EUNITTYPES>(28))return (seed/3)%2;return type==static_cast<UNITTYPES::EUNITTYPES>(120)?(seed/5+id(p))%3==0:type==static_cast<UNITTYPES::EUNITTYPES>(129)&&(seed/7+id(p))%3==0;}
void setupGoldModel(CItemGold*,std::wstring){}
void setupSample(CSoundBank*,int,long long){}
void goldTake(CItemGold*p,Ogre::SceneNode*node){num(107);num(id(p));num(node==NULL);}
void take(CEquipment*p,Ogre::SceneNode*node){num(109);num(id(p));num(node==NULL);}
void gold(CCharacter*p,int amount){num(113);num(id(p));num(amount);p->m_iGold+=amount;}
void target(CCharacter*p,CItem*item){num(127);num(id(p));num(id(item));p->m_targetItem.setObject(item);}
std::wstring translate(CStringTranslate*,const wchar_t*text){num(131);wide(text);return seed%3?L"gold Ж":L"";}
void text(CGameUI*p,const Ogre::Vector3&position,const std::string&value,float duration,float size,CEGUI::colour a,CEGUI::colour b){num(137);num(p==menu->ui);vec(position);narrow(value);fp(duration);fp(size);fp(a.getRed());fp(a.getGreen());fp(a.getBlue());fp(a.getAlpha());fp(b.getRed());fp(b.getGreen());fp(b.getBlue());fp(b.getAlpha());}
void deleted(CLevel*p,CItem*item){num(139);num(p==&world->level);num(id(item));}
bool remove(CLevel*p,CItem*item,bool flag){num(149);num(p==&world->level);num(id(item));num(flag);return(seed/5)%3!=0;}
CEquipment*pickup(CInventory*p,CEquipment*item,bool flag){num(151);num(p==self->m_pInventory);num(id(item));num(flag);return(seed/7)%3==0?NULL:equipment[(seed/11)%2];}
bool equip(CInventory*p,CEquipment*item){num(157);num(p==self->m_pInventory);num(id(item));return(seed/13)%2;}
bool canEquip(CInventory*p,CEquipment*item,bool flag){num(163);num(p==self->m_pInventory);num(id(item));num(flag);return(seed/17)%3!=0;}
bool player(CBaseUnit*p){num(167);num(id(p));return p==self?(seed/19)%2:(seed/23)%2;}
CGameUI*ui(CResourceManager*p){num(173);num(p==&world->resources);return menu->ui;}
void tip(CGameUI*p,EContextTip kind){num(179);num(p==menu->ui);num(kind);}
void sound(CSoundBank*p,int sample,float a,float b){num(181);num(p==self->m_levelSound?1:p==master->m_levelSound?2:99);num(sample);fp(a);fp(b);}
void add(CLevel*p,CItem*item,const Ogre::Vector3&position,bool flag){num(191);num(p==&world->level);num(id(item));vec(position);num(flag);}
void position(CPositionableObject*p,const Ogre::Vector3&value){num(193);num(id(p));vec(value);p->m_vPosition=value;}
void behind(CCharacter*p,bool flag){num(197);num(id(p));num(flag);p->m_Padding4A1[0]=flag;}
void side(void*input,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(input);seed=c.seed;phase=1;oursSide=ours;armed=false;out=&capture;struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_sigaction=&fault;action.sa_flags=SA_SIGINFO|SA_RESETHAND;sigemptyset(&action.sa_mask);sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);self=new CCharacter(NULL);master=new CCharacter(NULL);for(unsigned i=0;i<2;++i){equipment[i]=new Equipment;equipment[i]->m_bUnknown348=(seed/3+i)%2;coins[i]=NULL;}other=new Other;self->m_pResourceManager=&world->resources;self->m_pInventory=new CInventory(self,17);self->m_pMaster=(seed/11)%3?master:NULL;self->m_iGold=31;self->m_vPosition=Ogre::Vector3(seed*.1f,-2,5);self->m_Padding4A1[0]=seed%2;self->m_levelSound=seed&32?new CSoundBank(*services->master->m_pSoundManager,false):NULL;master->m_levelSound=seed&64?new CSoundBank(*services->master->m_pSoundManager,false):NULL;self->m_targetItem.setObject(other);world->level.m_pGameClient=menu->nativeClient.client;menu->nativeClient.client->m_pGameUI=menu->ui;CItem*item=seed%13?seed%4==0?static_cast<CItem*>(coins[0]):seed%4==1?other:equipment[0]:NULL;
 if(seed%4==0){detour::Set construction;TL_REDIRECT(construction,giModelLoad,&setupGoldModel);TL_REDIRECT(construction,giSampleLoad,&setupSample);if(construction.failed())_exit(44);for(unsigned i=0;i<2;++i){coins[i]=new CItemGold(&world->resources,int(seed*7+i*31)-113);coins[i]->m_vPosition=Ogre::Vector3(seed*.25f,i*3.0f,-4);}if(seed%13)item=coins[0];}
 detour::Set patches;
#define P(name,fn) TL_REDIRECT(patches,gi##name,&fn)
 P(ISA,isa);P(GoldTake,goldTake);P(Take,take);P(Gold,gold);P(Target,target);P(Translate,translate);P(Text,text);P(Delete,deleted);P(Remove,remove);P(Pickup,pickup);P(Equip,equip);P(CanEquip,canEquip);P(Player,player);P(UI,ui);P(Tip,tip);P(Sound,sound);P(Add,add);P(Position,position);P(Behind,behind);
#undef P
 if(patches.failed())_exit(43);phase=100;armed=true;typedef void(*F)(CCharacter*,CItem*,CLevel&);F fn=ours?giNew:giOld;if(!autotest::beginInvocation(capture,fn))return;fn(self,item,world->level);if(seed%4==0&&item)fn(self,coins[1],world->level);capture.callCompleted=1;phase=101;if(ours&&c.control)++self->m_iGold;num(self->m_iGold);num(id(self->m_targetItem.getObject()));num(self->m_Padding4A1[0]);for(unsigned i=0;i<2;++i)vec(equipment[i]->m_vPosition);armed=false;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(character_get_item_runtime){std::setlocale(LC_CTYPE,"C.UTF-8");initEmptyGlobals();tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services native;if(!native.ready())return 1;menugui::Audio audio(native.master);CStringTranslate translate(L"");services=&native;menugui::Fixture gui(*native.settings,native.scene);menu=&gui;finishlevel::Fixture level;world=&level;world->resources.m_pLevel=&world->level;world->resources.m_pSceneManager=native.scene;int failures=0;autotest::Coverage coverage("character_get_item_runtime",(uintptr_t)&giOld);for(unsigned i=0;i<768;++i){Case c={i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    getItem seed%u status%d/%d bytes%lu/%lu\n",i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}coverage.report(host);return failures;}}coverage.report(host);Case c={44,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    getItem negative detected%u\n",unsigned(caught));return failures;}
