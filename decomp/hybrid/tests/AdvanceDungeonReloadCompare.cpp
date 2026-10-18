#include "SmallMassCompare.h"
#include "Dungeon.h"
#include "DungeonManager.h"
#include <climits>

TL_ORIGINAL(void,reloadOriginal,(void*),"_ZN15CDungeonManager6reloadEv")
extern "C" void reloadCandidate(void*) __asm__("_ZN15CDungeonManager6reloadEv");
TL_FUNCTION(reloadFS,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(reloadFiles,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(reloadSeed,"_ZN9UTILITIES7setSeedEi")
TL_FUNCTION(reloadRandom,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(reloadLoad,"_ZN8CDungeon11loadDungeonEPKw")
namespace {
using namespace smallmass;
CDungeonManager* manager;
void* filesystem;
unsigned randomCalls,loaded;
void seed(int value){number(1);number(value);number(manager->m_lDungeons.size());}
void* singleton(){number(2);return filesystem;}
unsigned files(void* self,const std::wstring& path,TArrayList<std::wstring>& result,
               std::wstring pattern,bool recursive,bool strip,bool mods,bool skip) {
    event(3,self);text(path);text(pattern);number(recursive);number(strip);number(mods);number(skip);
    number(result.size());
    for(unsigned i=0;i<input->index%6;++i) {
        std::wstring name=i&1?L"synthetic/Ж":L"synthetic/dungeon";
        name+=wchar_t(L'0'+i);name+=L".dat";result.add(name);
    }
    return result.size();
}
int random(int low,int high) {
    number(4);number(low);number(high);number(manager->m_lDungeons.size());
    unsigned index=randomCalls++;
    return index%3==0?0:index%3==1?INT_MAX:int(input->index*31+index);
}
bool load(CDungeon* dungeon,const wchar_t* name) {
    number(5);text(std::wstring(name));number(dungeon->m_iDungeonIndex);
    number(dungeon->m_levelTemplateData.size());number(dungeon->m_mustBeCompleted.size());
    dungeon->m_sName=name;++loaded;
    return (input->index+loaded)%3!=0;
}
void execute(Case& c,bool ours,autotest::Capture& out) {
    input=&c;output=&out;autotest::g_arenaUsed=0;loaded=randomCalls=0;
    manager=static_cast<CDungeonManager*>(object(sizeof(CDungeonManager)));
    filesystem=object(16);
    new(&manager->m_szDungeonPath)std::wstring(c.index&1?L"TEST/DUNGEONS/":L"");
    typedef TArrayList<CDungeon*> List;
    new(&manager->m_lDungeons)List(10);
    for(unsigned i=0;i<c.index%4;++i)manager->m_lDungeons.add(new CDungeon);
    detour::Set redirects;TL_REDIRECT(redirects,reloadFS,&singleton);TL_REDIRECT(redirects,reloadFiles,&files);
    TL_REDIRECT(redirects,reloadSeed,&seed);TL_REDIRECT(redirects,reloadRandom,&random);TL_REDIRECT(redirects,reloadLoad,&load);
    if(redirects.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    autotest::invoke(out,ours?reloadCandidate:reloadOriginal,static_cast<void*>(manager));
    number(loaded);number(randomCalls);text(manager->m_szDungeonPath);number(manager->m_lDungeons.size());
    for(unsigned i=0;i<manager->m_lDungeons.size();++i) {
        CDungeon* dungeon=manager->m_lDungeons[i];text(dungeon->m_sName);number(dungeon->m_iDungeonIndex);
    }
    manager->m_lDungeons.deleteAll();manager->m_lDungeons.~List();manager->m_szDungeonPath.~basic_string();
}
}
TL_TEST(advance_dungeon_reload){return smallmass::run(host,0,"advance_dungeon_reload",(uintptr_t)reloadOriginal,execute,48);}
