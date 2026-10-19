#include <string>
#include <map>
#include <vector>
#include <limits>
#include "tests/FinishLevelFixture.h"
#define private public
#define protected public
#include "SkillManager.h"
#include "Hierarchy.h"
#include "Skill.h"
#include "MissilePreloader.h"
#include "Automap.h"
#include "SoundManager.h"
#include "StringTranslate.h"
#include "iLevelUpdatedCharacter.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#define PAIR(R,N,A,S) TL_ORIGINAL(R,lvOld##N,A,S) extern "C" R lvNew##N A __asm__(S);
PAIR(void,Item,(CLevel*,CItem*),"_ZN6CLevel16notifyOfDeletionEP5CItem")
PAIR(void,Character,(CLevel*,CCharacter*),"_ZN6CLevel16notifyOfDeletionEP10CCharacter")
PAIR(void,Near,(CLevel*,const Ogre::Vector3&),"_ZN6CLevel18updateNearUnitListERKN4Ogre7Vector3E")
PAIR(void,Update,(CLevel*,Ogre::Camera*,const Ogre::Vector3&,float,float),"_ZN6CLevel16updateCharactersEPN4Ogre6CameraERKNS0_7Vector3Eff")
PAIR(long long,Listener,(CLevel*,long long,iUnitObserver*),"_ZN6CLevel17addListenerToUnitExP13iUnitObserver")
PAIR(void,Money,(CLevel*,CCharacter*,CCharacter*,const Ogre::Vector3&,bool),"_ZN6CLevel9rollMoneyEP10CCharacterS1_RKN4Ogre7Vector3Eb")
PAIR(void,Treasure,(CLevel*,CCharacter*,CCharacter*,const Ogre::Vector3&),"_ZN6CLevel12rollTreasureEP10CCharacterS1_RKN4Ogre7Vector3E")
TL_FUNCTION(lvMissile,"_ZN17CMissilePreloader16notifyOfDeletionEP8iMissileP19CPositionableObject")
TL_FUNCTION(lvClientItem,"_ZN11CGameClient16notifyOfDeletionEP5CItem")
TL_FUNCTION(lvClientCharacter,"_ZN11CGameClient16notifyOfDeletionEP10CCharacter")
TL_FUNCTION(lvCharItem,"_ZN10CCharacter16notifyOfDeletionEP5CItem")
TL_FUNCTION(lvCharCharacter,"_ZN10CCharacter16notifyOfDeletionEPS_")
TL_FUNCTION(lvCharRange,"_ZN10CCharacter20calculateActiveRangeERKN4Ogre7Vector3E")
TL_FUNCTION(lvItemRange,"_ZN5CItem20calculateActiveRangeERKN4Ogre7Vector3E")
TL_FUNCTION(lvCharVisible,"_ZN10CCharacter10setVisibleEbb")
TL_FUNCTION(lvHide,"_ZN5CItem12hideItemTextEv")
TL_FUNCTION(lvDelete,"_ZN6CLevel15deleteCharacterEP10CCharacter")
TL_FUNCTION(lvMapPlayer,"_ZN8CAutomap17setPlayerPositionERKN4Ogre7Vector3E")
TL_FUNCTION(lvMapPet,"_ZN8CAutomap14setPetPositionERKN4Ogre7Vector3E")
TL_FUNCTION(lvMapVisible,"_ZN8CAutomap13setPetVisibleEb")
TL_FUNCTION(lvEffect,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(lvRandom,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(lvRandomInt,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(lvGoldModel,"_ZN9CItemGold9loadModelESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(lvParticle,"_ZN16CResourceManager14createParticleEPKw")
TL_FUNCTION(lvOpen,"_ZN6CLevel22randomOpenItemPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(lvAddItem,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(lvDrop,"_ZN9CItemGold13playDropSoundEPN4Ogre9SceneNodeE")
TL_FUNCTION(lvCreate,"_ZN16CResourceManager23createUnitsBySpawnClassERKSbIwSt11char_traitsIwESaIwEER10TArrayListIP9CBaseUnitEjP10CCharacterSC_ii")
TL_FUNCTION(lvAddUnit,"_ZN6CLevel7addUnitEP9CBaseUnitRKN4Ogre7Vector3E")
TL_FUNCTION(lvMoney,"_ZN6CLevel9rollMoneyEP10CCharacterS1_RKN4Ogre7Vector3Eb")
namespace {
struct Case{unsigned mode,seed;};
Ogre::SceneManager*activeScene;autotest::Capture*output;unsigned seed,randomCalls;CLevel*level;CBaseUnit*units[6];CSkill*skills[6];std::vector<CItemGold*>gold;
void word(unsigned n){output->add(&n,4);}void scalar(float n){output->add(&n,4);}void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}
unsigned id(CBaseUnit*p){if(!p)return 0;for(unsigned i=0;i<6;++i)if(units[i]==p)return i+1;for(unsigned i=0;i<gold.size();++i)if(gold[i]==p)return 20+i;return 99;}
void text(const std::wstring&s){word(s.size());for(unsigned i=0;i<s.size();++i)word(s[i]);}
struct Character:CCharacter{Character(CResourceManager*r):CCharacter(r){}virtual void update(Ogre::Camera*camera,const Ogre::Vector3&p,float dt){word(110);word(id(this));word(camera!=NULL);vector(p);scalar(dt);if(seed&32)m_bInActiveRange=!m_bInActiveRange;}};
struct Item:finishlevel::Item{Item(CResourceManager*r):finishlevel::Item(r){}virtual void setVisible(bool a,bool b){word(111);word(id(this));word(a);word(b);m_bVisible=a;}};
struct Observer:iUnitObserver{virtual void unitStateChange(CBaseUnit*,EUNIT_STATES){std::abort();}};
struct Updated:iLevelUpdatedCharacter{unsigned index;Updated(unsigned i):index(i){}virtual void characterUpdatedInLevel(float dt,CCharacter*c){word(112);word(index);word(id(c));scalar(dt);if(seed&16)level->removeCharacterUpdateListener(this);}virtual void itemUpdatedInLevel(float,CItem*){std::abort();}};
struct Audio{CSoundManager*sound,*prior;Audio():sound(static_cast<CSoundManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSoundManager),0,0,0))),prior(CMasterResourceManager::getSingleton()->m_pSoundManager){std::memset(sound,0,sizeof(*sound));::new(sound)CSoundManager(false);CMasterResourceManager::getSingleton()->m_pSoundManager=sound;}~Audio(){CMasterResourceManager::getSingleton()->m_pSoundManager=prior;sound->~CSoundManager();Ogre::NedAllocImpl::deallocBytes(sound);}};
void missile(CMissilePreloader*p,iMissile*s,CPositionableObject*object){word(120);word(p!=NULL);word(id(static_cast<CBaseUnit*>(object)));unsigned n=99;if(!s)n=0;for(unsigned i=0;i<6;++i)if(reinterpret_cast<void*>(s)==skills[i])n=1+i;word(n);}
void clientItem(CGameClient*p,CItem*x){word(121);word(p==level->m_pGameClient);word(id(x));}void clientCharacter(CGameClient*p,CCharacter*x){word(122);word(p==level->m_pGameClient);word(id(x));}
void charItem(CCharacter*a,CItem*b){word(123);word(id(a));word(id(b));}void charCharacter(CCharacter*a,CCharacter*b){word(124);word(id(a));word(id(b));}
void charRange(CCharacter*c,const Ogre::Vector3&p){word(125);word(id(c));vector(p);c->m_bInFadeRange=(seed+id(c))%3!=0;}
void itemRange(CItem*c,const Ogre::Vector3&p){word(126);word(id(c));vector(p);c->m_bInFadeRange=(seed+id(c))%4!=0;}
void charVisible(CCharacter*c,bool a,bool b){word(127);word(id(c));word(a);word(b);c->m_bVisible=a;}
void hide(CItem*c){word(128);word(id(c));}
void deleteCharacter(CLevel*p,CCharacter*c){word(129);word(p==level);word(id(c));}
void mapPlayer(CAutomap*,const Ogre::Vector3&p){word(130);vector(p);}void mapPet(CAutomap*,const Ogre::Vector3&p){word(131);vector(p);}void mapVisible(CAutomap*,bool b){word(132);word(b);}
float randomFloat(float a,float b){word(140);scalar(a);scalar(b);const float values[]={0,.099999f,.1f,.100001f,.5f,1};return a+(b-a)*values[(seed+randomCalls++)%6];}
int randomInt(int a,int b){word(141);word(a);word(b);return a+int(seed%5);}
float effect(CCharacter*p,EEFFECT_TYPE t,EDAMAGE_TYPES d){word(142);word(id(p));word(t);word(d);const float values[]={-150,-100,-.5f,0,17.5f,100,250};return values[seed%7];}
void model(CItemGold*,std::wstring name){word(143);text(name);}CParticle*particle(CResourceManager*,const wchar_t*name){word(144);text(name);return NULL;}
Ogre::Vector3 open(CLevel*p,const Ogre::Vector3&v,float r,bool b){word(145);word(p==level);vector(v);scalar(r);word(b);return Ogre::Vector3(v.x+r,v.y+1.25f,v.z-r);}
void addItem(CLevel*p,CItem*i,const Ogre::Vector3&v,bool b){word(146);word(p==level);vector(v);word(b);CItemGold*g=dynamic_cast<CItemGold*>(i);word(g!=NULL);if(!g)std::abort();gold.push_back(g);word(g->m_goldAmount);word(g->getResourceManager()==level->m_resourceManager);}
void drop(CItemGold*p,Ogre::SceneNode*n){word(147);word(id(p));word(n==p->getSceneNode());}
void create(CResourceManager*r,const std::wstring&name,TArrayList<CBaseUnit*>&list,unsigned count,CCharacter*a,CCharacter*b,int depth,int flags){word(148);word(r==level->m_resourceManager);text(name);word(list.size());word(list.m_nGrowBy);word(count);word(id(a));word(id(b));word(depth);word(flags);for(unsigned i=0;i<seed%13;++i)list.add(units[i%6]);}
void addUnit(CLevel*p,CBaseUnit*u,const Ogre::Vector3&v){word(149);word(p==level);word(id(u));vector(v);}
void money(CLevel*p,CCharacter*a,CCharacter*b,const Ogre::Vector3&v,bool always){word(150);word(p==level);word(id(a));word(id(b));vector(v);word(always);}
void execute(void*raw,autotest::Capture&out,bool ours){
 Case c=*static_cast<Case*>(raw);output=&out;seed=c.seed;randomCalls=0;gold.clear();std::memset(skills,0,sizeof skills);
 finishlevel::Fixture fixture;fixture.resources.m_pSceneManager=activeScene;fixture.resources.m_pHierarchy=CMasterResourceManager::getSingleton()->m_pHierarchy;fixture.resources.m_pHierarchy->m_parentTypes[8].clear();fixture.resources.m_pHierarchy->m_parentTypes[8].push_back(8);fixture.resources.m_pHierarchy->m_parentTypes[28].clear();fixture.resources.m_pHierarchy->m_parentTypes[28].push_back(28);level=&fixture.level;Character a(&fixture.resources),b(&fixture.resources),d(&fixture.resources),e(&fixture.resources);Item item(&fixture.resources),other(&fixture.resources);
 units[0]=&a;units[1]=&b;units[2]=&d;units[3]=&e;units[4]=&item;units[5]=&other;
 for(unsigned i=0;i<6;++i){units[i]->m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>((seed+i)%4?8:28);units[i]->m_vPosition=Ogre::Vector3(float(i),float(seed%3),float(i)*-1.5f);units[i]->m_bInActiveRange=(seed+i)&1;units[i]->m_bBaseUnitFlag190=(seed+i)%5==0;}
 Ogre::Vector3 p(float(seed%11)-5,float(seed%7)*.25f,float(seed%13)-6);
 detour::Set hooks;
 if(c.mode<2){
  // Client is an opaque typed collaborator receiver; all its entry points are
  // observed. This fixture does not claim Client construction or rendering.
  union Client{long double alignment;unsigned char data[sizeof(CGameClient)];}client;
  level->m_pGameClient=reinterpret_cast<CGameClient*>(client.data);
  for(unsigned i=0;i<seed%9;++i)finishlevel::prepend(level->m_pCharacters,static_cast<CCharacter*>(units[i%4]));
  void*q=NULL;std::memcpy(&q,reinterpret_cast<void*>(0x14ee340),8);if(!q)new(reinterpret_cast<void*>(0x14ee340))std::string;std::memcpy(&q,reinterpret_cast<void*>(0x14ee348),8);if(!q)new(reinterpret_cast<void*>(0x14ee348))std::wstring;
  CBaseUnit*target=c.mode?static_cast<CBaseUnit*>(&a):static_cast<CBaseUnit*>(&item);CSkillManager*saved=target->m_pSkillManager;
  CSkillManager manager(&fixture.resources,target);target->m_pSkillManager=seed%5?&manager:NULL;
  TArrayList<CSkill*>*lists[3];for(unsigned i=0;i<3;++i){lists[i]=new TArrayList<CSkill*>(1);manager.m_SkillsByName[std::wstring(1,wchar_t(L'A'+i))]=lists[i];}
  for(unsigned i=0;i<seed%7;++i){skills[i]=new CSkill(&fixture.resources,NULL);lists[i%3]->add(skills[i]);}
  if(seed%4==0)manager.m_SkillsByName[L"NULL"]=NULL;
  TL_REDIRECT(hooks,lvMissile,&missile);TL_REDIRECT(hooks,lvClientItem,&clientItem);TL_REDIRECT(hooks,lvClientCharacter,&clientCharacter);TL_REDIRECT(hooks,lvCharItem,&charItem);TL_REDIRECT(hooks,lvCharCharacter,&charCharacter);
  if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(c.mode){typedef void(*Fn)(CLevel*,CCharacter*);Fn fn=ours?lvNewCharacter:lvOldCharacter;if(!autotest::beginInvocation(out,fn))return;fn(level,&a);out.callCompleted=1;}
  else{typedef void(*Fn)(CLevel*,CItem*);Fn fn=ours?lvNewItem:lvOldItem;if(!autotest::beginInvocation(out,fn))return;fn(level,&item);out.callCompleted=1;}
  manager.m_SkillsByName.erase(L"NULL");target->m_pSkillManager=saved;level->m_pGameClient=NULL;
 }else if(c.mode==2){
  for(unsigned i=0;i<seed%7;++i)finishlevel::prepend(level->m_pCharacters,static_cast<CCharacter*>(units[i%4]));for(unsigned i=0;i<seed%5;++i)finishlevel::prepend(level->m_items,static_cast<CItem*>(units[4+i%2]));
  for(unsigned i=0;i<seed%3;++i){finishlevel::prepend(level->m_activeCharacters,static_cast<CCharacter*>(&a));finishlevel::prepend(level->m_activeItems,static_cast<CItem*>(&item));}
  TLinkedList<CItem*>*saved=level->m_items;if(seed%17==0)level->m_items=NULL;
  TL_REDIRECT(hooks,lvCharRange,&charRange);TL_REDIRECT(hooks,lvItemRange,&itemRange);TL_REDIRECT(hooks,lvCharVisible,&charVisible);TL_REDIRECT(hooks,lvHide,&hide);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(CLevel*,const Ogre::Vector3&);Fn fn=ours?lvNewNear:lvOldNear;if(!autotest::beginInvocation(out,fn))return;fn(level,p);out.callCompleted=1;
  std::vector<CCharacter*>characters;for(unsigned i=0;i<4;++i)characters.push_back(static_cast<CCharacter*>(units[i]));std::vector<CItem*>items;items.push_back(&item);items.push_back(&other);finishlevel::listState(out,level->m_activeCharacters,characters);finishlevel::listState(out,level->m_activeItems,items);for(unsigned i=0;i<6;++i){word(units[i]->m_bInFadeRange);word(units[i]->m_bVisible);}level->m_items=saved;
 }else if(c.mode==3){
  for(unsigned i=0;i<seed%8;++i)finishlevel::prepend(level->m_activeCharacters,static_cast<CCharacter*>(units[i%4]));a.m_pMaster=&b;b.m_Followers.push_back(seed%2?&a:&d);a.m_eAIState=static_cast<EAIState>(seed%3?0:42);
  Updated first(0),second(1);finishlevel::prepend(level->m_characterUpdateListeners,static_cast<iLevelUpdatedCharacter*>(&first));if(seed%2)finishlevel::prepend(level->m_characterUpdateListeners,static_cast<iLevelUpdatedCharacter*>(&second));
  union Map{long double alignment;unsigned char data[sizeof(CAutomap)];}map;level->m_automap=seed%7?reinterpret_cast<CAutomap*>(map.data):NULL;
  TL_REDIRECT(hooks,lvDelete,&deleteCharacter);TL_REDIRECT(hooks,lvMapPlayer,&mapPlayer);TL_REDIRECT(hooks,lvMapPet,&mapPet);TL_REDIRECT(hooks,lvMapVisible,&mapVisible);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(CLevel*,Ogre::Camera*,const Ogre::Vector3&,float,float);Fn fn=ours?lvNewUpdate:lvOldUpdate;if(!autotest::beginInvocation(out,fn))return;fn(level,NULL,p,float(seed%9)*.125f,float(seed%5)*.5f);out.callCompleted=1;word(level->m_updatedCharacterCount);unsigned count=0;for(TLinkedListNode<iLevelUpdatedCharacter*>*n=level->m_characterUpdateListeners->m_pHead;n;n=n->m_pNext){word(static_cast<Updated*>(n->m_Data)->index);++count;}word(count);level->m_automap=NULL;a.m_pMaster=NULL;b.m_Followers.clear();
 }else if(c.mode==4){
  Observer observers[3];const long long values[]={-1,0,1,255,256,0x1234567800000000LL,-0x1234567800000001LL,std::numeric_limits<long long>::max(),std::numeric_limits<long long>::min()};
  typedef long long(*Fn)(CLevel*,long long,iUnitObserver*);Fn fn=ours?lvNewListener:lvOldListener;if(!autotest::beginInvocation(out,fn))return;
  for(unsigned i=0;i<1+seed%79;++i){long long guid=values[(seed+i)%9];long long result=fn(level,guid,seed%5?&observers[(seed+i)%3]:NULL);out.add(&result,8);}out.callCompleted=1;
  word(level->m_unitObservers.size());for(std::map<long long,TArrayList<iUnitObserver*>*>::iterator it=level->m_unitObservers.begin();it!=level->m_unitObservers.end();++it){out.add(&it->first,8);word(it->second->size());word(it->second->m_nCapacity);word(it->second->m_nGrowBy);for(unsigned i=0;i<it->second->size();++i){unsigned n=0;for(unsigned j=0;j<3;++j)if((*it->second)[i]==&observers[j])n=j+1;word(n);}}
 }else{
  CStringTranslate translation(L"");a.m_spawnFlag703=seed%7==0;b.m_spawnFlag703=seed%11==0;level->m_dungeonDepth=int(seed%13)-4;CCharacter*first=seed%3?&a:NULL;CCharacter*second=seed%4?&b:NULL;
  TL_REDIRECT(hooks,lvRandom,&randomFloat);TL_REDIRECT(hooks,lvRandomInt,&randomInt);TL_REDIRECT(hooks,lvEffect,&effect);TL_REDIRECT(hooks,lvGoldModel,&model);TL_REDIRECT(hooks,lvParticle,&particle);TL_REDIRECT(hooks,lvOpen,&open);TL_REDIRECT(hooks,lvAddItem,&addItem);TL_REDIRECT(hooks,lvDrop,&drop);
  if(c.mode==6){TL_REDIRECT(hooks,lvCreate,&create);TL_REDIRECT(hooks,lvAddUnit,&addUnit);TL_REDIRECT(hooks,lvMoney,&money);}
  if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(c.mode==5){typedef void(*Fn)(CLevel*,CCharacter*,CCharacter*,const Ogre::Vector3&,bool);Fn fn=ours?lvNewMoney:lvOldMoney;if(!autotest::beginInvocation(out,fn))return;fn(level,first,second,p,seed%2);out.callCompleted=1;}
  else{typedef void(*Fn)(CLevel*,CCharacter*,CCharacter*,const Ogre::Vector3&);Fn fn=ours?lvNewTreasure:lvOldTreasure;if(!autotest::beginInvocation(out,fn))return;fn(level,first,second,p);out.callCompleted=1;}
  word(gold.size());for(unsigned i=0;i<gold.size();++i){word(gold[i]->m_goldAmount);TSafePointer<CItemGold>weak;weak.setObject(gold[i]);delete gold[i];word(weak.getObject()==NULL);}gold.clear();
 }
}
void original(void*p,autotest::Capture&o){execute(p,o,false);}void candidate(void*p,autotest::Capture&o){execute(p,o,true);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address){nativegame::Services services;if(!services.ready())return 1;activeScene=services.scene;Audio audio;CMissilePreloader*preloader=CMissilePreloader::getSinglelton();bool owns=preloader==NULL;if(owns)preloader=new CMissilePreloader(NULL);autotest::Coverage coverage(name,address);for(unsigned i=0;i<512;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    level mode%u seed%u issue%u/%u status%d/%d length%lu/%lu\n",mode,i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);if(owns)delete preloader;return 1;}}coverage.report(host);if(owns)delete preloader;return 0;}
}
TL_TEST(all_level_notify_item){return run(host,0,"all_level_notify_item",(uintptr_t)&lvOldItem);}
TL_TEST(all_level_notify_character){return run(host,1,"all_level_notify_character",(uintptr_t)&lvOldCharacter);}
TL_TEST(all_level_near){return run(host,2,"all_level_near",(uintptr_t)&lvOldNear);}
TL_TEST(all_level_update_characters){return run(host,3,"all_level_update_characters",(uintptr_t)&lvOldUpdate);}
TL_TEST(all_level_listener_guid){return run(host,4,"all_level_listener_guid",(uintptr_t)&lvOldListener);}
TL_TEST(all_level_roll_money){return run(host,5,"all_level_roll_money",(uintptr_t)&lvOldMoney);}
TL_TEST(all_level_roll_treasure){return run(host,6,"all_level_roll_treasure",(uintptr_t)&lvOldTreasure);}
