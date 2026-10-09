#include <cstring>
#include <string>
#include <map>
#include <new>
#define private public
#define protected public
#include "EnchantMenu.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Character.h"
#include "GameGlobals.h"
#include "StringTranslate.h"
#include "GameClient.h"
#include "SoundBank.h"
#include "EffectManager.h"
#include "Level.h"
#include "ResourceManager.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldInteraction,(CEnchantMenu*),"_ZN12CEnchantMenu18performInteractionEv")
extern "C" void newInteraction(CEnchantMenu*) __asm__("_ZN12CEnchantMenu18performInteractionEv");
TL_FUNCTION(queryFn,"_ZN10CInventory18getEquipmentInSlotEj")
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(globalsFn,"_ZN12CGameGlobals12getSingletonEv")
TL_FUNCTION(singletonFn,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateFn,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(priceFn,"_ZN10CEquipment12enchantPriceEv")
TL_FUNCTION(randomIntFn,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(randomFloatFn,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(playFn,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(speakFn,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(giveGoldFn,"_ZN10CCharacter8giveGoldEi")
TL_FUNCTION(maxSocketsFn,"_ZN10CEquipment13getMaxSocketsEv")
TL_FUNCTION(addSocketsFn,"_ZN10CEquipment10addSocketsEv")
TL_FUNCTION(addEnchantFn,"_ZN10CEquipment10addEnchantEiii")
TL_FUNCTION(clearAffixFn,"_ZN14CEffectManager20clearOutAffixEffectsEv")
TL_FUNCTION(clearEffectsFn,"_ZN14CEffectManager12clearEffectsEb")
TL_FUNCTION(clearDamageFn,"_ZN10CEquipment18clearDamageBonusesEv")
TL_FUNCTION(destroyTextFn,"_ZN5CItem15destroyItemTextEv")
TL_FUNCTION(removeFn,"_ZN10CInventory15removeEquipmentEP10CEquipment")
TL_FUNCTION(pickupFn,"_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
TL_FUNCTION(positionFn,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(addItemFn,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(targetFn,"_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(clearMouseFn,"_ZN11CGameClient20clearMouseClickUnitsEv")
TL_FUNCTION(modalFn,"_ZN7CGameUI15openModalDialogESbIwSt11char_traitsIwESaIwEES3_b")
TL_FUNCTION(clearOversFn,"_ZN7CGameUI19clearMenuMouseOversEv")
TL_FUNCTION(journalFn,"_ZN10CCharacter25incrementJournalStatisticE17EJournalStatistici")
TL_FUNCTION(statsFn,"_ZN11CSteamStats12getSingletonEv")
TL_FUNCTION(incrementFn,"_ZN11CSteamStats13incrementStatE6ESTATSi")
TL_FUNCTION(achievementsFn,"_ZN13CAchievements12getSingletonEv")
TL_FUNCTION(achievementFn,"_ZN13CAchievements14getAchievementE13EACHIEVEMENTS")
TL_FUNCTION(forceFn,"_ZN12CAchievement13forceCompleteEv")
TL_FUNCTION(improveFn,"_ZN10CEquipment15improveHeirloomEv")
TL_FUNCTION(effectsFn,"_ZN9CBaseUnit14reapplyEffectsEb")
TL_FUNCTION(affixesFn,"_ZN9CBaseUnit14reapplyAffixesEb")
TL_FUNCTION(safeFn,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(closeFn,"_ZN7CGameUI10closeRightEv")
namespace {
struct Case {int mode,type,outcome,funds,effect,sockets,count,drop,translation,speech,retire,safe,roll,probability;};
autotest::Capture* cap;const Case* input;CEnchantMenu* menu;CCharacter* actor;CGameUI* ui;CGameClient* client;CInventory* inventory;CEquipment* items[3];CGameGlobals* globals;CSoundBank* sounds;CSoundBank* voice;CEffectManager* effects;CLevel* level;std::map<std::wstring,int>* translations;int rolls;int deleted[3];
void n(int x){cap->add(&x,sizeof(x));}void f(float x){cap->add(&x,sizeof(x));}int id(CEquipment* p){for(int i=0;i<3;++i)if(p==items[i])return i;return -1;}
template<class T>T& at(void* p,size_t o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
long query(CInventory* p,unsigned slot){n(1);n(p==inventory);n(slot);return input->type<0?0:(long)items[0];}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){n(2);n(id((CEquipment*)p));n(t);const int kinds[]={0,8,13,17,24};return p==items[0]?int(t)==kinds[input->type]:int(t)==(input->type==4?0xa0:8);}
CGameGlobals* getGlobals(){n(3);return globals;}
CStringTranslate* singleton(){n(4);return (CStringTranslate*)ui;}
std::wstring translate(CStringTranslate* p,const wchar_t* key){n(5);n(p==(CStringTranslate*)ui);std::wstring text(key);cap->addText(text);int seen=(*translations)[text]++;if(input->translation==1||(input->translation==2&&!seen))return L"";return text+(input->translation==3?L" \\n \u03a9":L" translated");}
int price(CEquipment* p){n(6);n(id(p));return 10;}
int randomInt(int lo,int hi){n(7);n(lo);n(hi);return input->retire&1;}
float randomFloat(float lo,float hi){n(8);f(lo);f(hi);++rolls;float r=input->roll==1?500.0f:input->roll==2?0.0f:501.0f;if(input->roll==3){unsigned bits=0x7fc12345;std::memcpy(&r,&bits,4);}return r;}
void play(CSoundBank* p,int sound,Ogre::SceneNode* node,float a,float b,bool c){n(9);n(p==sounds);n(node==(Ogre::SceneNode*)ui);n(sound);f(a);f(b);n(c);}
void speak(CSoundBank* p,int sound,float a,float b){n(10);n(p==voice);n(sound);f(a);f(b);}
void giveGold(CCharacter* p,int amount){n(11);n(p==actor);n(amount);p->m_iGold+=amount;}
int maxSockets(CEquipment* p){n(12);n(id(p));return input->sockets?3:0;}
void addSockets(CEquipment* p){n(13);n(id(p));++p->m_iSocketCount;}
void addEnchant(CEquipment* p,int a,int b,int c){n(14);n(id(p));n(a);n(b);n(c);}
void clearAffix(CEffectManager* p){n(15);n(p==effects);}
void clearEffects(CEffectManager* p,bool x){n(16);n(p==effects);n(x);}
void clearDamage(CEquipment* p){n(17);n(id(p));}
void destroyText(CItem* p){n(18);n(id((CEquipment*)p));}
long remove(CInventory* p,CEquipment* item){n(19);n(p==inventory);n(id(item));return 0;}
long pickup(CInventory* p,CEquipment* item,bool x){n(20);n(p==inventory);n(id(item));n(x);return input->drop?0:1;}
Ogre::Vector3 position(CPositionableObject* p,bool x){n(21);n(p==actor);n(x);return Ogre::Vector3(1.25f,-2.5f,3.75f);}
void addItem(CLevel* p,CItem* item,const Ogre::Vector3& v,bool x){n(22);n(p==level);n(id((CEquipment*)item));f(v.x);f(v.y);f(v.z);n(x);}
void target(CCharacter* p,CCharacter* q){n(23);n(p==actor);n(q==NULL);}
void clearMouse(CGameClient* p){n(24);n(p==client);}
void modal(CGameUI* p,std::wstring title,std::wstring text,bool x){n(25);n(p==ui);cap->addText(title);cap->addText(text);n(x);}
void clearOvers(CGameUI* p){n(26);n(p==ui);}
void journal(CCharacter* p,EJournalStatistic s,int amount){n(27);n(p==actor);n(s);n(amount);}
void* stats(){n(28);return ui;}
void increment(void* p,int s,int amount){n(29);n(p==ui);n(s);n(amount);}
void* achievements(){n(30);return ui;}
void* achievement(void* p,int a){n(31);n(p==ui);n(a);return client;}
void force(void* p){n(32);n(p==client);}
void improve(CEquipment* p){n(33);n(id(p));}
void reapplyEffects(CBaseUnit* p,bool x){n(34);n(id((CEquipment*)p));n(x);}
void affixes(CBaseUnit* p,bool x){n(35);n(id((CEquipment*)p));n(x);}
void safe(void* p,void* ref,unsigned index){n(36);n(p==inventory);n((char*)ref-(char*)client);n(index);}
void close(CGameUI* p){n(37);n(p==ui);}
const std::wstring& name(CEquipment* p){n(38);n(id(p));return p->m_sItemName;}
void drop(CEquipment* p){n(39);n(id(p));}
void destroy(CEquipment* p){n(40);n(id(p));deleted[id(p)]++;}
void update(CEnchantMenu* p){n(41);n(p==menu);}
bool interact(CItem* p,CCharacter* q){n(42);n(p==(CItem*)items[2]);n(q==actor);return true;}
void side(const Case& c,bool ours,autotest::Capture& out){
 cap=&out;input=&c;rolls=0;memset(deleted,0,sizeof(deleted));
 unsigned long long mm[40]={0},am[0xa80/8]={0},um[0x1a10/8]={0},cm[0x3910/8]={0},im[256]={0},em[3][0x440/8]={0},gm[0x2d0/8]={0},rm[0x40/8]={0},fx[128]={0};
 menu=(CEnchantMenu*)mm;actor=(CCharacter*)am;ui=(CGameUI*)um;client=(CGameClient*)cm;inventory=(CInventory*)im;globals=(CGameGlobals*)gm;effects=(CEffectManager*)fx;level=(CLevel*)rm;sounds=(CSoundBank*)rm;voice=(CSoundBank*)fx;
 for(int i=0;i<3;++i){items[i]=(CEquipment*)em[i];new(&items[i]->m_sItemName)std::wstring(i==0?L"Test sword \u03a9":i==1?L"gem one":L"gem two");items[i]->m_iUnknown28C=c.retire;}
 std::map<std::wstring,int> translationMap;translations=&translationMap;
 new(&at<std::wstring>(actor,0x4c0))std::wstring(L"Hero");
 menu->m_iMode=c.mode;menu->m_pCharacter=actor;menu->m_pGameUI=ui;menu->m_pSoundBank=sounds;menu->m_pOwnerItem=c.speech?(CItem*)items[2]:NULL;
 actor->m_pInventory=inventory;actor->m_iGold=c.funds?10:9;actor->m_iUnitLevel=c.retire?2:7;actor->m_pSceneNode=(Ogre::SceneNode*)ui;actor->m_pResourceManager=(CResourceManager*)rm;at<CLevel*>(rm,0x18)=level;
 at<CSoundBank*>(actor,0x298)=c.speech?voice:NULL;at<int>(actor,0xa10)=c.retire;ui->m_pCharacter=actor;at<CGameClient*>(ui,0x1920)=client;
 for(int i=0;i<4;++i){size_t off=0x1c8+i*16;at<void*>(client,off)=(c.safe&(1<<i))?inventory:NULL;at<unsigned>(client,off+8)=100+i;}
 items[0]->m_iUnknown344=c.count;items[0]->m_iUnknown274=c.retire?2:9;items[0]->m_iSocketCount=c.sockets?1:0;items[0]->m_pEffectManager=c.effect?effects:NULL;
 items[0]->m_SocketedEquipment.m_pData=new CEquipment*[3];items[0]->m_SocketedEquipment.m_pData[0]=items[1];items[0]->m_SocketedEquipment.m_pData[1]=items[2];items[0]->m_SocketedEquipment.m_nCount=c.sockets==2?2:0;items[0]->m_SocketedEquipment.m_nCapacity=3;
 globals->m_fEnchanterDisenchantBase=globals->m_fShrineDisenchantBase=c.outcome==0?60.0f:0.0f;
 globals->m_fEnchanterDisenchantMax=globals->m_fShrineDisenchantMax=80.0f;
 globals->m_fEnchanterSocketChance=globals->m_fShrineSocketChance=c.outcome==1?60.0f:0.0f;
 globals->m_fEnchanterEnchantChance=globals->m_fShrineEnchantChance=c.outcome==2?60.0f:0.0f;

 float nan;unsigned nanBits=0x7fc54321;std::memcpy(&nan,&nanBits,4);
 float inf;unsigned infBits=0x7f800000;std::memcpy(&inf,&infBits,4);
 if(c.probability==1){globals->m_fEnchanterDisenchantBase=globals->m_fShrineDisenchantBase=50.0f;globals->m_fEnchanterSocketChance=globals->m_fShrineSocketChance=50.0f;globals->m_fEnchanterEnchantChance=globals->m_fShrineEnchantChance=50.0f;}
 if(c.probability==2)globals->m_fEnchanterDisenchantBase=globals->m_fShrineDisenchantBase=nan;
 if(c.probability==3)globals->m_fEnchanterDisenchantMax=globals->m_fShrineDisenchantMax=nan;
 if(c.probability==4)globals->m_fEnchanterDisenchantPerEnchant=globals->m_fShrineDisenchantPerEnchant=nan;
 if(c.probability==5)globals->m_fEnchanterDisenchantBase=globals->m_fShrineDisenchantBase=-0.0f;
 if(c.probability==6)globals->m_fEnchanterDisenchantBase=globals->m_fShrineDisenchantBase=inf;
 if(c.probability==7)globals->m_fEnchanterDisenchantMax=globals->m_fShrineDisenchantMax=-inf;
 if(c.probability==8){globals->m_fEnchanterDisenchantPerEnchant=globals->m_fShrineDisenchantPerEnchant=1.0f;}
 if(c.probability==9){globals->m_fShrineDisenchantBase=25.0f;globals->m_fEnchanterDisenchantBase=75.0f;globals->m_fShrineSocketChance=25.0f;globals->m_fEnchanterSocketChance=75.0f;globals->m_fShrineEnchantChance=25.0f;globals->m_fEnchanterEnchantChance=75.0f;}
 if(c.probability==10){globals->m_fEnchanterSocketChance=globals->m_fShrineSocketChance=nan;globals->m_fEnchanterEnchantChance=globals->m_fShrineEnchantChance=nan;}
 void* vt[128]={0};vt[1]=(void*)&destroy;vt[0x2a0/8]=(void*)&name;vt[0x360/8]=(void*)&drop;vt[0x280/8]=(void*)&interact;for(int i=0;i<3;++i)*(void***)items[i]=vt;
 void* mv[16]={0};mv[9]=(void*)&update;*(void***)menu=mv;
 detour::Set d,d2;
#define R(N,F) TL_REDIRECT(d,N##Fn,&F)
 R(query,query);R(isa,isa);R(globals,getGlobals);R(singleton,singleton);R(translate,translate);R(price,price);R(randomInt,randomInt);R(randomFloat,randomFloat);R(play,play);R(speak,speak);R(giveGold,giveGold);R(maxSockets,maxSockets);R(addSockets,addSockets);R(addEnchant,addEnchant);R(clearAffix,clearAffix);R(clearEffects,clearEffects);R(clearDamage,clearDamage);R(destroyText,destroyText);R(remove,remove);R(pickup,pickup);
#undef R
#define R(N,F) TL_REDIRECT(d2,N##Fn,&F)
 R(position,position);R(addItem,addItem);R(target,target);R(clearMouse,clearMouse);R(modal,modal);R(clearOvers,clearOvers);R(journal,journal);R(stats,stats);R(increment,increment);R(achievements,achievements);R(achievement,achievement);R(force,force);R(improve,improve);R(effects,reapplyEffects);R(affixes,affixes);R(safe,safe);R(close,close);
#undef R
 if(d.failed()||d2.failed())_exit(42);
 if(c.translation==2){int mode=menu->m_iMode;menu->m_iMode=0;if(ours)newInteraction(menu);else oldInteraction(menu);menu->m_iMode=mode;}
 if(ours)autotest::invoke(out,&newInteraction,menu);else autotest::invoke(out,&oldInteraction,menu);
 n(99);n(menu->m_bInteractionComplete);n(menu->m_bRetirementComplete);n(actor->m_iGold);n(at<bool>(actor,0xa14));n(at<int>(client,0x3908));n(id(at<CEquipment*>(client,0x3900)));n(rolls);
 for(int i=0;i<3;++i){n(items[i]->m_iUnknown344);n(items[i]->m_iUnknown28C);n(items[i]->m_iSocketCount);n(items[i]->m_SocketedEquipment.size());n(items[i]->m_bUnknown348);n(deleted[i]);cap->addText(items[i]->m_sItemName);}
 for(int i=0;i<4;++i){n(at<void*>(client,0x1c8+i*16)!=NULL);n(at<unsigned>(client,0x1d0+i*16));}
}
void a(void* p,autotest::Capture& o){side(*(Case*)p,false,o);}void b(void* p,autotest::Capture& o){side(*(Case*)p,true,o);}
}
TL_TEST(enchant_interaction_differential){
 autotest::Coverage coverage("enchant_interaction_differential",(uint64_t)(uintptr_t)&oldInteraction);int total=0;
 const int modes[]={0,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c};
 for(int mi=0;mi<9;++mi)for(int type=-1;type<5;++type)for(int outcome=0;outcome<4;++outcome)for(int variant=0;variant<8;++variant){
  if((modes[mi]!=0x15&&modes[mi]!=0x16)&&outcome)continue;
  Case c={modes[mi],type,outcome,variant&1,1,(variant%3),variant%2?4:9,variant&2,(variant/2)%4,variant&4,variant%2,variant*2,0};
  autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);int pair=coverage.observe(host,x,y);++total;
  bool ok=pair==0&&!autotest::incomplete(x)&&!autotest::incomplete(y)&&x.reportValid&&y.reportValid&&x.childStatus==0&&y.childStatus==0&&x.capture.length==y.capture.length&&std::memcmp(x.capture.data,y.capture.data,x.capture.length)==0;
  if(!ok){size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    mode %d type %d outcome %d variant %d: status %d/%d bytes %lu/%lu first %lu\n",c.mode,type,outcome,variant,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t i=first>32?first-32:0;i<first+64&&i+4<=x.capture.length&&i+4<=y.capture.length;i+=4){int v,z;memcpy(&v,x.capture.data+i,4);memcpy(&z,y.capture.data+i,4);host->log("      %lu %d %d\n",(unsigned long)i,v,z);}return 1;}
 }coverage.report(host);host->log("    enchant interaction: %d cases\n",total);return 0;
}
