#include "SmallMassCompare.h"
TL_ORIGINAL(bool, playerOriginal,(void*),"_ZN12CRandomGroup38canGroupBeCreatedBasedOffOfPlayerClassEv")
extern "C" bool playerCandidate(void*) __asm__("_ZN12CRandomGroup38canGroupBeCreatedBasedOffOfPlayerClassEv");
TL_ORIGINAL(bool, questOriginal,(void*),"_ZN12CRandomGroup33canGroupBeCreatedBasedOffOfQuestsEv")
extern "C" bool questCandidate(void*) __asm__("_ZN12CRandomGroup33canGroupBeCreatedBasedOffOfQuestsEv");
TL_ORIGINAL(bool, difficultyOriginal,(void*),"_ZN12CRandomGroup37canGroupBeCreatedBasedOffOfDifficultyEv")
extern "C" bool difficultyCandidate(void*) __asm__("_ZN12CRandomGroup37canGroupBeCreatedBasedOffOfDifficultyEv");
TL_FUNCTION(playerClass,"_ZN11CGameClient18getPlayerClassNameEv")
TL_FUNCTION(questSingleton,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(questComplete,"_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(questActive,"_ZN13CQuestManager16getQuestIsActiveERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(editorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
namespace {
using namespace smallmass;unsigned calls;void* manager;void* self;
std::wstring player(void* p){event(1,p);++calls;return input->index%3?L"VANQUISHER":L"DESTROYER";}
void* singleton(){event(2,manager);++calls;return manager;}
bool complete(void* p,const std::wstring& name){event(3,p);text(name);++calls;return ((input->index>>(name.empty()?0:name[0]-L'a'))&1)!=0;}
bool active(void* p,const std::wstring& name){event(4,p);text(name);++calls;return ((input->index>>(name.empty()?0:name[0]-L'a'+1))&1)!=0;}
bool editor(void* p){event(5,p);++calls;return input->index%9==0;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;self=object(0x200);manager=object(0x20);void* resources=object(0x50);void* client=object(0x3910);field<void*>(self,0x68)=resources;void* clients[]={c.index%7?client:0};list(resources,0x28,clients,c.index%11?1:0,1);field<bool>(resources,0x43)=c.index%13==0;
 detour::Set p;TL_REDIRECT(p,playerClass,&player);TL_REDIRECT(p,questSingleton,&singleton);TL_REDIRECT(p,questComplete,&complete);TL_REDIRECT(p,questActive,&active);TL_REDIRECT(p,editorRunning,&editor);if(p.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==0){new(static_cast<char*>(self)+0x180)std::wstring(c.index%5?L"VANQUISHER":L"");autotest::invoke(out,ours?playerCandidate:playerOriginal,self);number(calls);field<std::wstring>(self,0x180).~basic_string();}
 else if(c.op==1){for(unsigned i=0;i<5;++i)new(static_cast<char*>(self)+0x158+i*8)std::wstring(c.index%8==i?L"":std::wstring(1,L'a'+i));autotest::invoke(out,ours?questCandidate:questOriginal,self);number(calls);for(unsigned i=0;i<5;++i)field<std::wstring>(self,0x158+i*8).~basic_string();}
 else if(c.op==2){const int values[]={-1,0,1,2,3,4,2147483647};field<int>(self,0x190)=values[(c.index/2)%7];field<int>(client,0x38ec)=c.index%4;autotest::invoke(out,ours?difficultyCandidate:difficultyOriginal,self);number(calls);}

}
}
TL_TEST(scene_random_player_class){return smallmass::run(host,0,"scene_random_player_class",(uintptr_t)playerOriginal,execute,48);}
TL_TEST(scene_random_quests){return smallmass::run(host,1,"scene_random_quests",(uintptr_t)questOriginal,execute,64);}
TL_TEST(scene_random_difficulty){return smallmass::run(host,2,"scene_random_difficulty",(uintptr_t)difficultyOriginal,execute,56);}
