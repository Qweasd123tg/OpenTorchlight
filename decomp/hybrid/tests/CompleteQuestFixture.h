#ifndef COMPLETE_QUEST_FIXTURE_H
#define COMPLETE_QUEST_FIXTURE_H
#include <climits>
#include <string>
#include <vector>
#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/SmallMassCompare.h"
#define private public
#define protected public
#include "Quest.h"
#include "QuestManager.h"
#include "QuestRequirements.h"
#include "QuestRewards.h"
#include "QuestDialog.h"
#include "QuestUnitData.h"
#undef protected
#undef private
TL_ORIGINAL(void,cqNativeCtor,(CQuest*,CResourceManager*,CQuestManager*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,cqNativeDtor,(CQuest*),"_ZN6CQuestD1Ev")
TL_ORIGINAL(void,cqManagerCtor,(CQuestManager*,CResourceManager*),"_ZN13CQuestManagerC1EP16CResourceManager")
TL_ORIGINAL(void,cqManagerDtor,(CQuestManager*),"_ZN13CQuestManagerD1Ev")
namespace completequest {
inline void init(){new(reinterpret_cast<void*>(0x14f9fe8))std::wstring;new(reinterpret_cast<void*>(0x151d408))std::wstring;const wchar_t*types[]={L"",L"FIND",L"KILL NUM",L"KILL BOSS"};const wchar_t*dialogs[]={L"ERROR",L"INTRO",L"RETURN",L"COMPLETE",L"PASSIVE",L"DETAILS"};const wchar_t*complete[]={L"COMPLETE_ON_QUEST_ACCEPT",L"COMPLETE_ON_QUEST_COMPLETE"};for(unsigned i=0;i<4;++i)new(reinterpret_cast<void*>(0x14fa000+8*i))std::wstring(types[i]);for(unsigned i=0;i<6;++i)new(reinterpret_cast<void*>(0x14fa020+8*i))std::wstring(dialogs[i]);for(unsigned i=0;i<2;++i)new(reinterpret_cast<void*>(0x14fa050+8*i))std::wstring(complete[i]);}
struct Manager {CQuestManager*p;CQuestManager*previous;explicit Manager(CResourceManager*r){p=static_cast<CQuestManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(*p),0,0,0));previous=*reinterpret_cast<CQuestManager**>(0x14fc6e0);*reinterpret_cast<CQuestManager**>(0x14fc6e0)=p;cqManagerCtor(p,r);*reinterpret_cast<CQuestManager**>(0x14fc6e0)=previous;p->m_pSoundBank=NULL;}~Manager(){cqManagerDtor(p);Ogre::NedAllocImpl::deallocBytes(p);*reinterpret_cast<CQuestManager**>(0x14fc6e0)=previous;}};
struct Quest {CQuest*p;Quest(CResourceManager*r,CQuestManager*m){p=static_cast<CQuest*>(Ogre::NedAllocImpl::allocBytes(sizeof(*p),0,0,0));cqNativeCtor(p,r,m);}~Quest(){cqNativeDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}};
}
#endif
