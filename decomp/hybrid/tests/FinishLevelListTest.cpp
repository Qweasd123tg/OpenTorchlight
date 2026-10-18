#include "FinishLevelFixture.h"
#include "EditorScene.h"
#include <OgreBillboard.h>
TL_ORIGINAL(bool,listOld0,(CLevel*,iLevelUpdate*),"_ZN6CLevel18removeUpdateObjectEP12iLevelUpdate")
extern "C" bool listNew0(CLevel*,iLevelUpdate*) __asm__("_ZN6CLevel18removeUpdateObjectEP12iLevelUpdate");
TL_ORIGINAL(void,listOld1,(CLevel*,iLevelUpdate*),"_ZN6CLevel15addUpdateObjectEP12iLevelUpdate")
extern "C" void listNew1(CLevel*,iLevelUpdate*) __asm__("_ZN6CLevel15addUpdateObjectEP12iLevelUpdate");
TL_ORIGINAL(void,listOld2,(CLevel*,Ogre::Camera*,const Ogre::Vector3&,float),"_ZN6CLevel24updateLevelUpdateObjectsEPN4Ogre6CameraERKNS0_7Vector3Ef")
extern "C" void listNew2(CLevel*,Ogre::Camera*,const Ogre::Vector3&,float) __asm__("_ZN6CLevel24updateLevelUpdateObjectsEPN4Ogre6CameraERKNS0_7Vector3Ef");
TL_ORIGINAL(void,listOld3,(CLevel*,iLevelUpdatedCharacter*),"_ZN6CLevel29removeCharacterUpdateListenerEP22iLevelUpdatedCharacter")
extern "C" void listNew3(CLevel*,iLevelUpdatedCharacter*) __asm__("_ZN6CLevel29removeCharacterUpdateListenerEP22iLevelUpdatedCharacter");
TL_ORIGINAL(void,listOld4,(CLevel*),"_ZN6CLevel29flushCharacterUpdateListenersEv")
extern "C" void listNew4(CLevel*) __asm__("_ZN6CLevel29flushCharacterUpdateListenersEv");
TL_ORIGINAL(void,listOld5,(CLevel*,iLevelUpdatedCharacter*),"_ZN6CLevel26addCharacterUpdateListenerEP22iLevelUpdatedCharacter")
extern "C" void listNew5(CLevel*,iLevelUpdatedCharacter*) __asm__("_ZN6CLevel26addCharacterUpdateListenerEP22iLevelUpdatedCharacter");
TL_ORIGINAL(void,listOld6,(CLevel*,CBaseUnit*,EUNIT_STATES),"_ZN6CLevel20unitBroadcastMessageEP9CBaseUnit12EUNIT_STATES")
extern "C" void listNew6(CLevel*,CBaseUnit*,EUNIT_STATES) __asm__("_ZN6CLevel20unitBroadcastMessageEP9CBaseUnit12EUNIT_STATES");
TL_ORIGINAL(void,listOld7,(CLevel*,CCharacter*,bool),"_ZN6CLevel15removeCharacterEP10CCharacterb")
extern "C" void listNew7(CLevel*,CCharacter*,bool) __asm__("_ZN6CLevel15removeCharacterEP10CCharacterb");
TL_ORIGINAL(bool,listOld8,(CLevel*,CItem*,bool),"_ZN6CLevel10removeItemEP5CItemb")
extern "C" bool listNew8(CLevel*,CItem*,bool) __asm__("_ZN6CLevel10removeItemEP5CItemb");
TL_ORIGINAL(void,listOld9,(CLevel*,CCharacter*),"_ZN6CLevel15deleteCharacterEP10CCharacter")
extern "C" void listNew9(CLevel*,CCharacter*) __asm__("_ZN6CLevel15deleteCharacterEP10CCharacter");
TL_ORIGINAL(void,listOld10,(CLevel*,CItem*),"_ZN6CLevel10deleteItemEP5CItem")
extern "C" void listNew10(CLevel*,CItem*) __asm__("_ZN6CLevel10deleteItemEP5CItem");
TL_ORIGINAL(void,listOld11,(CLevel*,Ogre::Camera*,const Ogre::Vector3&,float),"_ZN6CLevel11updateItemsEPN4Ogre6CameraERKNS0_7Vector3Ef")
extern "C" void listNew11(CLevel*,Ogre::Camera*,const Ogre::Vector3&,float) __asm__("_ZN6CLevel11updateItemsEPN4Ogre6CameraERKNS0_7Vector3Ef");
TL_FUNCTION(listClearRefs,"_ZN10CCharacter22clearAllUnitReferencesEv")
TL_FUNCTION(listSetTarget,"_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(listSetTargetItem,"_ZN10CCharacter13setTargetItemEP5CItem")
TL_FUNCTION(listDeactivate,"_ZN9CBaseUnit21deactivateUnitInLevelEv")
TL_FUNCTION(listNotifyCharacter,"_ZN6CLevel16notifyOfDeletionEP10CCharacter")
TL_FUNCTION(listNotifyItem,"_ZN6CLevel16notifyOfDeletionEP5CItem")
TL_FUNCTION(listISA,"_ZN16CResourceManager3ISAEN9UNITTYPES10EUNITTYPESES1_")
namespace finishlist {
struct Case{unsigned target,variant;};static std::vector<unsigned> trace;static bool recording;static unsigned variant;static CLevel* level;
static void event(unsigned n){if(recording)trace.push_back(n);}
struct Character:CCharacter {unsigned id;Character(unsigned n):CCharacter(NULL),id(n){}~Character(){event(100+id);}virtual void setAIState(EAIState state){event(200+id);m_eAIState=state;}};
struct Item:finishlevel::Item {unsigned id;Item(unsigned n):finishlevel::Item(NULL),id(n){}~Item(){event(300+id);}virtual void update(Ogre::Camera*,const Ogre::Vector3&,float value){event(400+id);if(variant%9==0)m_bInActiveRange=!m_bInActiveRange;if(value<0)m_bBaseUnitFlag190=true;}};
struct Scene:CEditorScene {Scene():CEditorScene(L"fixture scene"){}virtual void DeleteObjectInScene(CEditorBaseObject* o){event(500+unsigned(o->getGuid()));if(variant%2)delete o;}};
struct Listener:iLevelUpdatedCharacter {unsigned id;Listener(unsigned n):id(n){}virtual void characterUpdatedInLevel(float,CCharacter*){event(600+id);}virtual void itemUpdatedInLevel(float,CItem*o){event(700+id+unsigned(o->getGuid()));if(variant%7==0)level->removeCharacterUpdateListener(this);}};
struct Update:iLevelUpdate {unsigned id,calls;Update(unsigned n):id(n),calls(0){}virtual bool updateLevelObject(float elapsed,Ogre::Camera*,const Ogre::Vector3& point){event(800+id);event(unsigned(elapsed*4));event(unsigned(point.x*4));++calls;unsigned mode=(variant+id)%6;
 if(mode==2){int index=level->m_updateObjects.find(this);if(index>=0)level->m_updateObjects.removeAt(index);return false;}
 if(mode==3 && level->m_updateObjects.size()>1){level->m_updateObjects.removeAt(level->m_updateObjects.size()-1);return false;}
 return mode!=1;}};
struct Observer:iUnitObserver {unsigned id;Observer(unsigned n):id(n){}virtual void unitStateChange(CBaseUnit*o,EUNIT_STATES st){event(900+id);event(unsigned(o->getGuid()));event(unsigned(st));}};
static void clearRefs(CCharacter*o){event(1000+unsigned(o->getGuid()));}
static void setTarget(CCharacter*o,CCharacter*t){event(1100+unsigned(o->getGuid()));event(t!=NULL);}
static void setTargetItem(CCharacter*o,CItem*t){event(1200+unsigned(o->getGuid()));event(t!=NULL);}
static void deactivate(CBaseUnit*o){event(1300+unsigned(o->getGuid()));o->m_bInActiveRange=false;}
static void notifyCharacter(CLevel*,CCharacter*o){event(1400+unsigned(o->getGuid()));}
static void notifyItem(CLevel*,CItem*o){event(1500+unsigned(o->getGuid()));}
static int isa(CResourceManager*,UNITTYPES::EUNITTYPES a,UNITTYPES::EUNITTYPES b){return a==b;}
static unsigned id(const void*p,const std::vector<const void*>& ids){if(!p)return 0;for(unsigned i=0;i<ids.size();++i)if(ids[i]==p)return i+1;return ~0u;}
static void side(void*input,autotest::Capture& out,bool candidate){
 Case c=*static_cast<Case*>(input);recording=false;variant=c.variant;trace.clear();finishlevel::Fixture f;level=&f.level;
 Scene scene;Ogre::Billboard billboard;Character*characters[3];Item*items[3];TSafePointer<CCharacter>cw[3];TSafePointer<CItem>iw[3];
 std::vector<CCharacter*>charIDs;std::vector<CItem*>itemIDs;std::vector<const void*>identities;
 for(unsigned i=0;i<3;++i){characters[i]=new Character(i);items[i]=new Item(i);characters[i]->setGuid(10+i);items[i]->setGuid(20+i);cw[i].setObject(characters[i]);iw[i].setObject(items[i]);charIDs.push_back(characters[i]);itemIDs.push_back(items[i]);identities.push_back(characters[i]);identities.push_back(items[i]);
 characters[i]->m_eAIState=static_cast<EAIState>(c.variant%3==0?0x2a:0);characters[i]->m_automapBillboard=c.variant%3==1?&billboard:NULL;
 characters[i]->m_bSaveFlag191=(c.variant+i)%2;items[i]->m_bSaveFlag191=(c.variant+i)%2;characters[i]->m_pSceneOwner=c.variant%3?&scene:NULL;items[i]->m_pSceneOwner=c.variant%3?&scene:NULL;
 characters[i]->m_bBaseUnitFlag190=false;items[i]->m_bBaseUnitFlag190=(c.variant+i)%5==0;items[i]->m_bInActiveRange=(c.variant+i)%2;items[i]->m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>(i%2?0x1d:0x22);items[i]->m_pResourceManager=&f.resources;
 if(i<c.variant%4){finishlevel::prepend(f.level.m_pCharacters,static_cast<CCharacter*>(characters[i]));finishlevel::prepend(f.level.m_items,static_cast<CItem*>(items[i]));}
 if((i+c.variant)%3){finishlevel::prepend(f.level.m_activeCharacters,static_cast<CCharacter*>(characters[i]));finishlevel::prepend(f.level.m_activeItems,static_cast<CItem*>(items[i]));}
 if((i+c.variant)%2){finishlevel::prepend(f.level.m_pendingCharacters,static_cast<CCharacter*>(characters[i]));finishlevel::prepend(f.level.m_pendingItems,static_cast<CItem*>(items[i]));}
 }
 Update u0(0),u1(1),u2(2);Update*updates[]={&u0,&u1,&u2};std::vector<const void*>updateIDs;for(unsigned i=0;i<3;++i){updateIDs.push_back(updates[i]);if(i<c.variant%4)f.level.m_updateObjects.add(updates[i]);}if(c.variant%5==0)f.level.m_updateObjects.add(NULL);
 Listener l0(0),l1(1),l2(2);iLevelUpdatedCharacter*listeners[]={&l0,&l1,&l2};std::vector<iLevelUpdatedCharacter*>listenerIDs;
 for(unsigned i=0;i<3;++i){listenerIDs.push_back(listeners[i]);if((i+c.variant)%3)finishlevel::prepend(f.level.m_characterUpdateListeners,listeners[i]);}
 if(c.variant%4==0&&c.target<6)finishlevel::prepend<iLevelUpdatedCharacter*>(f.level.m_characterUpdateListeners,NULL);
 for(TLinkedListNode<iLevelUpdatedCharacter*>*p=f.level.m_characterUpdateListeners->m_pHead;p;p=p->m_pNext)if(c.variant%3==0 || (p->m_Data==&l1&&c.variant%2))f.level.m_pendingCharacterUpdateRemovals.add(p);
 Observer o0(0),o1(1),o2(2);iUnitObserver*observers[]={&o0,&o1,&o2};
 if(c.variant%4){TArrayList<iUnitObserver*>*list=new TArrayList<iUnitObserver*>;for(unsigned i=0;i<c.variant%4;++i)list->add(observers[i]);f.level.m_unitObservers[characters[0]->getGuid()]=list;}
 detour::Set boundaries;TL_REDIRECT(boundaries,listClearRefs,&clearRefs);TL_REDIRECT(boundaries,listSetTarget,&setTarget);TL_REDIRECT(boundaries,listSetTargetItem,&setTargetItem);TL_REDIRECT(boundaries,listDeactivate,&deactivate);TL_REDIRECT(boundaries,listNotifyCharacter,&notifyCharacter);TL_REDIRECT(boundaries,listNotifyItem,&notifyItem);TL_REDIRECT(boundaries,listISA,&isa);if(boundaries.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 CCharacter*charArg=c.variant%4?characters[c.variant%3]:NULL;CItem*itemArg=c.variant%4?items[c.variant%3]:NULL;iLevelUpdate*updateArg=c.variant%4?updates[c.variant%3]:NULL;iLevelUpdatedCharacter*listenerArg=c.variant%4?listeners[c.variant%3]:NULL;
 Ogre::Vector3 point(float(c.variant%7),2,3);float elapsed=c.variant%2?0.25f:-0.5f;
 recording=true;
 switch(c.target){
 case 0:if(candidate)autotest::invoke<bool(*)(CLevel*,iLevelUpdate*),CLevel*,iLevelUpdate*>(out,listNew0,&f.level,updateArg);else autotest::invoke<bool(*)(CLevel*,iLevelUpdate*),CLevel*,iLevelUpdate*>(out,listOld0,&f.level,updateArg);break;
 case 1:if(candidate)autotest::invoke<void(*)(CLevel*,iLevelUpdate*),CLevel*,iLevelUpdate*>(out,listNew1,&f.level,updateArg);else autotest::invoke<void(*)(CLevel*,iLevelUpdate*),CLevel*,iLevelUpdate*>(out,listOld1,&f.level,updateArg);break;
 case 2:if(candidate)autotest::invoke<void(*)(CLevel*,Ogre::Camera*,const Ogre::Vector3&,float),CLevel*,Ogre::Camera*,const Ogre::Vector3&,float>(out,listNew2,&f.level,static_cast<Ogre::Camera*>(NULL),point,elapsed);else autotest::invoke<void(*)(CLevel*,Ogre::Camera*,const Ogre::Vector3&,float),CLevel*,Ogre::Camera*,const Ogre::Vector3&,float>(out,listOld2,&f.level,static_cast<Ogre::Camera*>(NULL),point,elapsed);break;
 case 3:if(candidate)autotest::invoke<void(*)(CLevel*,iLevelUpdatedCharacter*),CLevel*,iLevelUpdatedCharacter*>(out,listNew3,&f.level,listenerArg);else autotest::invoke<void(*)(CLevel*,iLevelUpdatedCharacter*),CLevel*,iLevelUpdatedCharacter*>(out,listOld3,&f.level,listenerArg);break;
 case 4:if(candidate)autotest::invoke<void(*)(CLevel*),CLevel*>(out,listNew4,&f.level);else autotest::invoke<void(*)(CLevel*),CLevel*>(out,listOld4,&f.level);break;
 case 5:if(candidate)autotest::invoke<void(*)(CLevel*,iLevelUpdatedCharacter*),CLevel*,iLevelUpdatedCharacter*>(out,listNew5,&f.level,listenerArg);else autotest::invoke<void(*)(CLevel*,iLevelUpdatedCharacter*),CLevel*,iLevelUpdatedCharacter*>(out,listOld5,&f.level,listenerArg);break;
 case 6:if(candidate)autotest::invoke<void(*)(CLevel*,CBaseUnit*,EUNIT_STATES),CLevel*,CBaseUnit*,EUNIT_STATES>(out,listNew6,&f.level,static_cast<CBaseUnit*>(characters[0]),static_cast<EUNIT_STATES>(c.variant%3));else autotest::invoke<void(*)(CLevel*,CBaseUnit*,EUNIT_STATES),CLevel*,CBaseUnit*,EUNIT_STATES>(out,listOld6,&f.level,static_cast<CBaseUnit*>(characters[0]),static_cast<EUNIT_STATES>(c.variant%3));break;
 case 7:if(candidate)autotest::invoke<void(*)(CLevel*,CCharacter*,bool),CLevel*,CCharacter*,bool>(out,listNew7,&f.level,charArg,bool(c.variant%2));else autotest::invoke<void(*)(CLevel*,CCharacter*,bool),CLevel*,CCharacter*,bool>(out,listOld7,&f.level,charArg,bool(c.variant%2));break;
 case 8:if(candidate)autotest::invoke<bool(*)(CLevel*,CItem*,bool),CLevel*,CItem*,bool>(out,listNew8,&f.level,itemArg,bool(c.variant%2));else autotest::invoke<bool(*)(CLevel*,CItem*,bool),CLevel*,CItem*,bool>(out,listOld8,&f.level,itemArg,bool(c.variant%2));break;
 case 9:if(candidate)autotest::invoke<void(*)(CLevel*,CCharacter*),CLevel*,CCharacter*>(out,listNew9,&f.level,charArg);else autotest::invoke<void(*)(CLevel*,CCharacter*),CLevel*,CCharacter*>(out,listOld9,&f.level,charArg);break;
 case 10:if(candidate)autotest::invoke<void(*)(CLevel*,CItem*),CLevel*,CItem*>(out,listNew10,&f.level,itemArg);else autotest::invoke<void(*)(CLevel*,CItem*),CLevel*,CItem*>(out,listOld10,&f.level,itemArg);break;
 case 11:if(candidate)autotest::invoke<void(*)(CLevel*,Ogre::Camera*,const Ogre::Vector3&,float),CLevel*,Ogre::Camera*,const Ogre::Vector3&,float>(out,listNew11,&f.level,static_cast<Ogre::Camera*>(NULL),point,elapsed);else autotest::invoke<void(*)(CLevel*,Ogre::Camera*,const Ogre::Vector3&,float),CLevel*,Ogre::Camera*,const Ogre::Vector3&,float>(out,listOld11,&f.level,static_cast<Ogre::Camera*>(NULL),point,elapsed);break;
 }
 finishlevel::number(out,f.level.m_npcIconsDirty);
 finishlevel::listState(out,f.level.m_pCharacters,charIDs);finishlevel::listState(out,f.level.m_activeCharacters,charIDs);finishlevel::listState(out,f.level.m_pendingCharacters,charIDs);
 finishlevel::listState(out,f.level.m_items,itemIDs);finishlevel::listState(out,f.level.m_activeItems,itemIDs);finishlevel::listState(out,f.level.m_pendingItems,itemIDs);finishlevel::listState(out,f.level.m_characterUpdateListeners,listenerIDs);
 finishlevel::number(out,f.level.m_updateObjects.size());for(unsigned i=0;i<f.level.m_updateObjects.size();++i)finishlevel::number(out,id(f.level.m_updateObjects[i],updateIDs));
 finishlevel::number(out,f.level.m_pendingCharacterUpdateRemovals.size());for(unsigned i=0;i<f.level.m_pendingCharacterUpdateRemovals.size();++i){iLevelUpdatedCharacter*p=f.level.m_pendingCharacterUpdateRemovals[i]->m_Data;unsigned n=0;for(unsigned j=0;j<3;++j)if(listeners[j]==p)n=j+1;finishlevel::number(out,n);}
 finishlevel::number(out,f.level.m_unitObservers.size());for(std::map<long long,TArrayList<iUnitObserver*>*>::iterator p=f.level.m_unitObservers.begin();p!=f.level.m_unitObservers.end();++p){finishlevel::number(out,unsigned(p->first));finishlevel::number(out,p->second->size());}
 for(unsigned i=0;i<3;++i){finishlevel::number(out,cw[i].getObject()!=NULL);finishlevel::number(out,iw[i].getObject()!=NULL);if(cw[i].getObject()){finishlevel::number(out,characters[i]->m_eAIState);finishlevel::number(out,characters[i]->m_automapBillboard!=NULL);}if(iw[i].getObject()){finishlevel::number(out,items[i]->m_bInActiveRange);finishlevel::number(out,items[i]->m_bBaseUnitFlag190);}}
 recording=false;finishlevel::number(out,trace.size());for(unsigned i=0;i<trace.size();++i)finishlevel::number(out,trace[i]);
 for(unsigned i=0;i<3;++i){if(cw[i].getObject()){characters[i]->m_pSceneOwner=NULL;delete characters[i];}if(iw[i].getObject()){items[i]->m_pResourceManager=NULL;items[i]->m_pSceneOwner=NULL;delete items[i];}}
}
static void original(void*p,autotest::Capture&o){side(p,o,false);}static void ours(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(finish_level_list_9360e0){autotest::Coverage coverage("finish_level_list_9360e0",0x9360e0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishlist::Case c={0,n};autotest::compareCase(finishlist::original,finishlist::ours,&c,stats,host,"list",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_list_936790){autotest::Coverage coverage("finish_level_list_936790",0x936790);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishlist::Case c={1,n};autotest::compareCase(finishlist::original,finishlist::ours,&c,stats,host,"list",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_list_9363b0){autotest::Coverage coverage("finish_level_list_9363b0",0x9363b0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishlist::Case c={2,n};autotest::compareCase(finishlist::original,finishlist::ours,&c,stats,host,"list",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_list_9368e0){autotest::Coverage coverage("finish_level_list_9368e0",0x9368e0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishlist::Case c={3,n};autotest::compareCase(finishlist::original,finishlist::ours,&c,stats,host,"list",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_list_936a80){autotest::Coverage coverage("finish_level_list_936a80",0x936a80);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishlist::Case c={4,n};autotest::compareCase(finishlist::original,finishlist::ours,&c,stats,host,"list",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_list_949430){autotest::Coverage coverage("finish_level_list_949430",0x949430);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishlist::Case c={5,n};autotest::compareCase(finishlist::original,finishlist::ours,&c,stats,host,"list",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_list_938940){autotest::Coverage coverage("finish_level_list_938940",0x938940);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishlist::Case c={6,n};autotest::compareCase(finishlist::original,finishlist::ours,&c,stats,host,"list",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_list_949770){autotest::Coverage coverage("finish_level_list_949770",0x949770);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishlist::Case c={7,n};autotest::compareCase(finishlist::original,finishlist::ours,&c,stats,host,"list",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_list_94a2a0){autotest::Coverage coverage("finish_level_list_94a2a0",0x94a2a0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishlist::Case c={8,n};autotest::compareCase(finishlist::original,finishlist::ours,&c,stats,host,"list",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_list_949a10){autotest::Coverage coverage("finish_level_list_949a10",0x949a10);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishlist::Case c={9,n};autotest::compareCase(finishlist::original,finishlist::ours,&c,stats,host,"list",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_list_949f10){autotest::Coverage coverage("finish_level_list_949f10",0x949f10);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishlist::Case c={10,n};autotest::compareCase(finishlist::original,finishlist::ours,&c,stats,host,"list",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_list_94a1a0){autotest::Coverage coverage("finish_level_list_94a1a0",0x94a1a0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishlist::Case c={11,n};autotest::compareCase(finishlist::original,finishlist::ours,&c,stats,host,"list",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
