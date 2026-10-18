#include "FinishLevelFixture.h"
#include "Equipment.h"
#include "EditorScene.h"
TL_ORIGINAL(void,dispatchOld0,(CLevel*,CCharacter*,CCharacter*),"_ZN6CLevel17reactToAreaDamageEP10CCharacterS1_")
extern "C" void dispatchNew0(CLevel*,CCharacter*,CCharacter*) __asm__("_ZN6CLevel17reactToAreaDamageEP10CCharacterS1_");
TL_ORIGINAL(void,dispatchOld1,(CLevel*),"_ZN6CLevel29populateNewMerchantsInventoryEv")
extern "C" void dispatchNew1(CLevel*) __asm__("_ZN6CLevel29populateNewMerchantsInventoryEv");
TL_ORIGINAL(void,dispatchOld2,(CLevel*,float),"_ZN6CLevel19updateDroppingItemsEf")
extern "C" void dispatchNew2(CLevel*,float) __asm__("_ZN6CLevel19updateDroppingItemsEf");
TL_ORIGINAL(float,dispatchOld3,(CLevel*,Ogre::Vector3),"_ZN6CLevel11floorHeightEN4Ogre7Vector3E")
extern "C" float dispatchNew3(CLevel*,Ogre::Vector3) __asm__("_ZN6CLevel11floorHeightEN4Ogre7Vector3E");
TL_ORIGINAL(void,dispatchOld4,(CLevel*),"_ZN6CLevel8activateEv")
extern "C" void dispatchNew4(CLevel*) __asm__("_ZN6CLevel8activateEv");
TL_ORIGINAL(CBaseUnit*,dispatchOld5,(CLevel*,CBaseUnit*,const Ogre::Vector3&),"_ZN6CLevel7addUnitEP9CBaseUnitRKN4Ogre7Vector3E")
extern "C" CBaseUnit* dispatchNew5(CLevel*,CBaseUnit*,const Ogre::Vector3&) __asm__("_ZN6CLevel7addUnitEP9CBaseUnitRKN4Ogre7Vector3E");
TL_FUNCTION(dispatchFriend,"_ZN10CCharacter8isFriendEPS_")
TL_FUNCTION(dispatchRange,"_ZN10CCharacter18inDamageReactRangeEPS_")
TL_FUNCTION(dispatchISA,"_ZN16CResourceManager3ISAEN9UNITTYPES10EUNITTYPESES1_")
TL_FUNCTION(dispatchPane,"_ZN10CInventory11itemsInPaneE16EINVENTORY_PANES")
TL_FUNCTION(dispatchMerchant,"_ZN10CCharacter25generateMerchantInventoryEv")
TL_FUNCTION(dispatchDrop,"_ZN10CEquipment10updateDropEf")
TL_FUNCTION(dispatchRay,"_ZN6CLevel12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_RjS4_b")
TL_FUNCTION(dispatchClear,"_ZN6CLevel18clearOutRoomPiecesEv")
TL_FUNCTION(dispatchParticles,"_ZN6CLevel13findParticlesEv")
TL_FUNCTION(dispatchAddChar,"_ZN6CLevel12addCharacterEP10CCharacterRKN4Ogre7Vector3Eb")
TL_FUNCTION(dispatchAddItem,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
namespace finishdispatch {
struct Case{unsigned target,variant;};static unsigned variant;static bool record;static std::vector<unsigned>trace;static CLevel*level;
static void n(unsigned x){if(record)trace.push_back(x);}static void scalar(float x){unsigned b;std::memcpy(&b,&x,4);n(b);}static void vector(const Ogre::Vector3&x){scalar(x.x);scalar(x.y);scalar(x.z);}
struct Character:CCharacter{Character():CCharacter(NULL){}virtual void reactToDamage(CCharacter*attacker,bool critical){n(10+unsigned(getGuid()));n(attacker?unsigned(attacker->getGuid()):0);n(critical);}};
struct Scene:CEditorScene{unsigned id;Scene(unsigned n):CEditorScene(L"fixture room"),id(n){}virtual void setEnabled(bool value){n(100+id);n(value);m_bEnabled=value;}virtual void setActivated(bool value){n(200+id);n(value);}};
struct Other:CBaseUnit{Other():CBaseUnit(NULL,static_cast<EBASEUNIT_TYPE>(9)){}virtual void setActiveInLevel(bool){}virtual void*getUnitModel(){return NULL;}virtual void*getUnitCollisionModel(){return NULL;}};
static bool friends(CCharacter*a,CCharacter*b){n(300+unsigned(a->getGuid()));n(unsigned(b->getGuid()));return (unsigned(a->getGuid())+variant)%3!=0;}
static bool range(CCharacter*a,CCharacter*b){n(400+unsigned(a->getGuid()));n(unsigned(b->getGuid()));return (unsigned(a->getGuid())+variant)%2!=0;}
static int isa(CResourceManager*,UNITTYPES::EUNITTYPES a,UNITTYPES::EUNITTYPES b){n(500+unsigned(b));return a==b;}
static unsigned pane(CInventory*o,EINVENTORY_PANES p){n(600+unsigned(o->m_pPositionableObject->getGuid()));n(unsigned(p));return ((variant+unsigned(p))%7==0)?1:0;}
static void merchant(CCharacter*a){n(700+unsigned(a->getGuid()));}
static void drop(CEquipment*a,float value){n(800+unsigned(a->getGuid()));scalar(value);if(variant%5==0){for(TLinkedListNode<CItem*>*p=level->m_activeItems->m_pHead;p;p=p->m_pNext)if(p->m_Data==a){if(p->m_pPrevious)p->m_pPrevious->m_pNext=p->m_pNext;else level->m_activeItems->m_pHead=p->m_pNext;if(p->m_pNext)p->m_pNext->m_pPrevious=p->m_pPrevious;delete p;break;}}}
static bool ray(CLevel*,const Ogre::Vector3&a,const Ogre::Vector3&b,Ogre::Vector3&h,Ogre::Vector3&normal,unsigned&material,Ogre::Vector3&face,bool flag){n(900);vector(a);vector(b);n(flag);h=Ogre::Vector3(a.x,float(int(variant%9)-4)*0.5f,a.z);normal=Ogre::Vector3(1,0,0);face=Ogre::Vector3(0,1,0);material=88;return variant%3!=0;}
static void clear(CLevel*){n(1000);}static void particles(CLevel*){n(1100);}
static CCharacter*addChar(CLevel*,CCharacter*p,const Ogre::Vector3&position,bool activate){n(1200);n(unsigned(p->getGuid()));vector(position);n(activate);p->m_vPosition=position;return variant%7?p:NULL;}
static CItem*addItem(CLevel*,CItem*p,const Ogre::Vector3&position,bool activate){n(1300);n(unsigned(p->getGuid()));vector(position);n(activate);p->m_vPosition=position;return variant%7?p:NULL;}
static void side(void*input,autotest::Capture&out,bool candidate){
 Case c=*static_cast<Case*>(input);variant=c.variant;record=false;trace.clear();finishlevel::Fixture f;level=&f.level;
 Character ch0,ch1,ch2;CCharacter*characters[]={&ch0,&ch1,&ch2};
 for(unsigned i=0;i<3;++i){characters[i]->setGuid(10+i);characters[i]->m_eAIState=static_cast<EAIState>((variant+i)%5==0?5:(variant+i)%5==1?6:0);characters[i]->m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>(i==0?0x29:i==1?0x7f:0x1d);characters[i]->m_pResourceManager=&f.resources;if(i<c.variant%4){finishlevel::prepend(f.level.m_activeCharacters,characters[i]);finishlevel::prepend(f.level.m_pCharacters,characters[i]);}}
 CInventory*inventory=NULL;if(c.target==1){inventory=new CInventory(&ch0,10);ch0.m_pInventory=inventory;if(c.variant%3)ch1.m_pInventory=inventory;}
 CEquipment*equipment0=NULL;CEquipment*equipment1=NULL;finishlevel::Item ordinary(NULL);ordinary.setGuid(30);
 if(c.target==2){equipment0=new CEquipment(NULL);equipment1=new CEquipment(NULL);equipment0->setGuid(20);equipment1->setGuid(21);equipment0->m_bInActiveRange=c.variant%2;equipment1->m_bInActiveRange=c.variant%3;ordinary.m_bInActiveRange=true;finishlevel::prepend<CItem*>(f.level.m_activeItems,equipment0);finishlevel::prepend<CItem*>(f.level.m_activeItems,&ordinary);if(c.variant%4)finishlevel::prepend<CItem*>(f.level.m_activeItems,equipment1);}
 Scene scene0(0),scene1(1),scene2(2);Scene*scenes[]={&scene0,&scene1,&scene2};for(unsigned i=0;i<c.variant%4;++i)f.level.m_RoomScenes.add(scenes[i]);
 Other other;other.setGuid(40);CBaseUnit*unit=c.variant%4==0?NULL:c.variant%4==1?static_cast<CBaseUnit*>(&ch0):c.variant%4==2?static_cast<CBaseUnit*>(&ordinary):static_cast<CBaseUnit*>(&other);
 detour::Set boundary;TL_REDIRECT(boundary,dispatchFriend,&friends);TL_REDIRECT(boundary,dispatchRange,&range);TL_REDIRECT(boundary,dispatchISA,&isa);TL_REDIRECT(boundary,dispatchPane,&pane);TL_REDIRECT(boundary,dispatchMerchant,&merchant);TL_REDIRECT(boundary,dispatchDrop,&drop);TL_REDIRECT(boundary,dispatchRay,&ray);TL_REDIRECT(boundary,dispatchClear,&clear);TL_REDIRECT(boundary,dispatchParticles,&particles);TL_REDIRECT(boundary,dispatchAddChar,&addChar);TL_REDIRECT(boundary,dispatchAddItem,&addItem);if(boundary.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 Ogre::Vector3 point(float(int(variant%13)-6),float(variant%7),float(int(variant%11)-5));float elapsed=variant%2?0.125f:-0.5f;record=true;
 switch(c.target){
 case 0:if(candidate)autotest::invoke<void(*)(CLevel*,CCharacter*,CCharacter*),CLevel*,CCharacter*,CCharacter*>(out,dispatchNew0,&f.level,c.variant%2?characters[(c.variant+1)%3]:NULL,characters[c.variant%3]);else autotest::invoke<void(*)(CLevel*,CCharacter*,CCharacter*),CLevel*,CCharacter*,CCharacter*>(out,dispatchOld0,&f.level,c.variant%2?characters[(c.variant+1)%3]:NULL,characters[c.variant%3]);break;
 case 1:if(candidate)autotest::invoke<void(*)(CLevel*),CLevel*>(out,dispatchNew1,&f.level);else autotest::invoke<void(*)(CLevel*),CLevel*>(out,dispatchOld1,&f.level);break;
 case 2:if(candidate)autotest::invoke<void(*)(CLevel*,float),CLevel*,float>(out,dispatchNew2,&f.level,elapsed);else autotest::invoke<void(*)(CLevel*,float),CLevel*,float>(out,dispatchOld2,&f.level,elapsed);break;
 case 3:if(candidate)autotest::invoke<float(*)(CLevel*,Ogre::Vector3),CLevel*,Ogre::Vector3>(out,dispatchNew3,&f.level,point);else autotest::invoke<float(*)(CLevel*,Ogre::Vector3),CLevel*,Ogre::Vector3>(out,dispatchOld3,&f.level,point);break;
 case 4:if(candidate)autotest::invoke<void(*)(CLevel*),CLevel*>(out,dispatchNew4,&f.level);else autotest::invoke<void(*)(CLevel*),CLevel*>(out,dispatchOld4,&f.level);break;
 case 5:{typedef CBaseUnit*(*Fn)(CLevel*,CBaseUnit*,const Ogre::Vector3&);Fn fn=candidate?&dispatchNew5:&dispatchOld5;if(!autotest::beginInvocation(out,fn))return;CBaseUnit*result=fn(&f.level,unit,point);out.callCompleted=1;n(result?unsigned(result->getGuid()):0);break;}
 }
 record=false;finishlevel::number(out,trace.size());for(unsigned i=0;i<trace.size();++i)finishlevel::number(out,trace[i]);std::vector<CItem*>ids;ids.push_back(equipment0);ids.push_back(&ordinary);ids.push_back(equipment1);finishlevel::listState(out,f.level.m_activeItems,ids);out.add(&ch0.m_vPosition,sizeof ch0.m_vPosition);out.add(&ordinary.m_vPosition,sizeof ordinary.m_vPosition);for(unsigned i=0;i<3;++i)finishlevel::number(out,scenes[i]->m_bEnabled);
 ch0.m_pInventory=ch1.m_pInventory=NULL;if(inventory)delete inventory;for(unsigned i=0;i<3;++i)characters[i]->m_pResourceManager=NULL;delete equipment0;delete equipment1;
}
static void original(void*p,autotest::Capture&o){side(p,o,false);}static void ours(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(finish_level_dispatch_936cf0){autotest::Coverage coverage("finish_level_dispatch_936cf0",0x936cf0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<72;++n){finishdispatch::Case c={0,n};autotest::compareCase(finishdispatch::original,finishdispatch::ours,&c,stats,host,"dispatch",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=72;}
TL_TEST(finish_level_dispatch_936630){autotest::Coverage coverage("finish_level_dispatch_936630",0x936630);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<72;++n){finishdispatch::Case c={1,n};autotest::compareCase(finishdispatch::original,finishdispatch::ours,&c,stats,host,"dispatch",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=72;}
TL_TEST(finish_level_dispatch_936c80){autotest::Coverage coverage("finish_level_dispatch_936c80",0x936c80);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<72;++n){finishdispatch::Case c={2,n};autotest::compareCase(finishdispatch::original,finishdispatch::ours,&c,stats,host,"dispatch",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=72;}
TL_TEST(finish_level_dispatch_94e970){autotest::Coverage coverage("finish_level_dispatch_94e970",0x94e970);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<72;++n){finishdispatch::Case c={3,n};autotest::compareCase(finishdispatch::original,finishdispatch::ours,&c,stats,host,"dispatch",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=72;}
TL_TEST(finish_level_dispatch_95a5d0){autotest::Coverage coverage("finish_level_dispatch_95a5d0",0x95a5d0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<72;++n){finishdispatch::Case c={4,n};autotest::compareCase(finishdispatch::original,finishdispatch::ours,&c,stats,host,"dispatch",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=72;}
TL_TEST(finish_level_dispatch_95cdb0){autotest::Coverage coverage("finish_level_dispatch_95cdb0",0x95cdb0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<72;++n){finishdispatch::Case c={5,n};autotest::compareCase(finishdispatch::original,finishdispatch::ours,&c,stats,host,"dispatch",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=72;}
