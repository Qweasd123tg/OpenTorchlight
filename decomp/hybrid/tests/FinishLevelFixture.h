#ifndef FINISH_LEVEL_FIXTURE_H
#define FINISH_LEVEL_FIXTURE_H
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <new>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Level.h"
#include "Character.h"
#include "Item.h"
#include "ItemGold.h"
#include "Inventory.h"
#include "ResourceManager.h"
#include "LevelTemplateData.h"
#include "GenericModel.h"
#include "RoomPiece.h"
#include "Layout.h"
#include "MasterResourceManager.h"
#include "PropertyNode.h"
#include "CollisionList.h"
#include "GameClient.h"
#include "Player.h"
#include "Dungeon.h"
#include "iLevelUpdate.h"
#include "iLevelUpdatedCharacter.h"
#undef protected
#undef private
TL_FUNCTION(levelFixtureRemoveCollision,"_ZN22CMasterResourceManager20removeCollisionModelEP15CCollisionModel")
TL_FUNCTION(levelFixtureEditorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(levelFixtureNodeBounds,"_ZN13CPropertyNode17updateBoundingBoxEv")
namespace finishlevel {
inline void rendererFreeBounds(CPropertyNode*){}
inline bool editorNotRunning(CResourceManager*){return false;}
inline void removeNullCollisionModel(void*,void* model){if(model)std::abort();}

// Character.cpp EMPTY_STRING/EMPTY_WSTRING are read by the native constructor
// before this headless test process has run executable static initializers.
inline void initializeCharacterText() {
 void* a=reinterpret_cast<void*>(0x147c340);void* b=reinterpret_cast<void*>(0x147c348);
 void* p=NULL;std::memcpy(&p,a,sizeof p);if(!p)new(a)std::string;
 std::memcpy(&p,b,sizeof p);if(!p)new(b)std::wstring;
}

template<class T> void clearNodes(TLinkedList<T>* list) {
 if (!list) return;
 while(list->m_pHead) {TLinkedListNode<T>*n=list->m_pHead;list->m_pHead=n->m_pNext;delete n;}
}
template<class T> void prepend(TLinkedList<T>* list,T value) {
 TLinkedListNode<T>*n=new TLinkedListNode<T>;n->m_Data=value;n->m_pPrevious=NULL;n->m_pNext=list->m_pHead;
 if(n->m_pNext)n->m_pNext->m_pPrevious=n;list->m_pHead=n;
}
template<class T> void endMember(T& member){member.~T();}
struct Fixture {
 detour::Set rendererFreeBoundary;
 CResourceManager resources;
 CLevel& level;
 Fixture():resources(NULL),level(*::new(Ogre::NedAllocImpl::allocBytes(sizeof(CLevel),0,0,0)) CLevel(L"fixture",NULL,NULL,&resources,NULL,NULL,17,3)) {
  TL_REDIRECT(rendererFreeBoundary,levelFixtureRemoveCollision,&removeNullCollisionModel);TL_REDIRECT(rendererFreeBoundary,levelFixtureEditorRunning,&editorNotRunning);TL_REDIRECT(rendererFreeBoundary,levelFixtureNodeBounds,&rendererFreeBounds);if(rendererFreeBoundary.failed())std::abort();
  resources.m_pHierarchy=NULL;resources.m_bFlag2=false;resources.m_bFlag3=false;
  level.m_noSpawnRegions.clear();initializeCharacterText();
 }
 ~Fixture() {
  clearNodes(level.m_activeCharacters);clearNodes(level.m_activeItems);
  clearNodes(level.m_pCharacters);clearNodes(level.m_items);
  clearNodes(level.m_pendingCharacters);clearNodes(level.m_pendingItems);
  level.m_pendingCharacterUpdateRemovals.clear();clearNodes(level.m_characterUpdateListeners);
  // The real constructor owns typed containers. End their lifetimes locally:
  // the native Level destructor also shuts down global particle/missile pools,
  // which do not exist at this pre-main boundary and are outside these cases.
  for(unsigned x=0;x<level.m_passWidth;++x){if(level.m_mapPassability)delete[]level.m_mapPassability[x];if(level.m_objectPassability)delete[]level.m_objectPassability[x];}
  delete[]level.m_mapPassability;delete[]level.m_objectPassability;
  delete level.m_activeCharacters;delete level.m_activeItems;delete level.m_pCharacters;delete level.m_items;
  delete level.m_pendingCharacters;delete level.m_pendingItems;delete level.m_characterUpdateListeners;
  for(std::map<long long,TArrayList<iUnitObserver*>*>::iterator p=level.m_unitObservers.begin();p!=level.m_unitObservers.end();++p)delete p->second;
  endMember(level.m_RoomScenes);endMember(level.m_roomBounds);endMember(level.m_collisionIndices);endMember(level.m_updateObjects);
  endMember(level.m_noSpawnRegions);endMember(level.m_propertyNodesF0);endMember(level.m_propertyNodes108);endMember(level.m_collisionBounds);
  endMember(level.m_chunks);endMember(level.m_formations);endMember(level.m_timer);endMember(level.m_auxiliaryLayouts);endMember(level.m_sDungeonName);
  endMember(level.m_renderableStates);endMember(level.m_unitObservers);endMember(level.m_pendingCharacterUpdateRemovals);
  level.CRunicCore::~CRunicCore();Ogre::NedAllocImpl::deallocBytes(&level);resources.m_pLevel=NULL;
 }
};
struct Item: CItem {
 explicit Item(CResourceManager*r):CItem(r) {}
 virtual void setActiveInLevel(bool a) {m_bInActiveRange=a;}
 virtual void* getUnitModel(){return NULL;}
 virtual void* getUnitCollisionModel(){return NULL;}
};
inline void number(autotest::Capture&o,unsigned n){o.add(&n,4);}
inline void scalar(autotest::Capture&o,float n){o.add(&n,4);}
template<class T> void listState(autotest::Capture&o,TLinkedList<T>*l,const std::vector<T>& identities) {
 number(o,l!=NULL);if(!l)return;unsigned count=0;TLinkedListNode<T>*prior=NULL;
 for(TLinkedListNode<T>*p=l->m_pHead;p;p=p->m_pNext){if(++count>100){o.issue=autotest::Capture::InvalidReport;return;}number(o,p->m_pPrevious==prior);unsigned id=0;if(p->m_Data){id=~0u;for(unsigned i=0;i<identities.size();++i)if(p->m_Data==identities[i])id=i+1;}number(o,id);prior=p;}
 number(o,count);
}
}
#endif
