#include "SmallMassCompare.h"
#include "UnitThemeParticle.h"
#include "Dungeon.h"
#include "LevelTemplateData.h"

TL_ORIGINAL(void, themeOriginal,(void*,void*),"_ZN18CUnitThemeParticle4loadEP10CDataGroup")
extern "C" void themeCandidate(void*,void*) __asm__("_ZN18CUnitThemeParticle4loadEP10CDataGroup");
TL_FUNCTION(themeString,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(themeWide,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEPKw")
TL_FUNCTION(themeInteger,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(themeBoolean,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(themeMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(themeType,"_ZN10CHierarchy15getTypeIDByNameERKSbIwSt11char_traitsIwESaIwEE")

namespace theme_test {
using namespace smallmass;
struct World {
    char master[0x190],hierarchy[8],group[8];
    std::wstring file,bone,type;
    World():file(L"particle/тест"),bone(L"hand"),type(L"MONSTERS"){}
};
World* world;
const std::wstring& stringValue(void* group,const std::wstring& key,const std::wstring& fallback) {
    event(1,group);text(key);text(fallback);
    return input->index&1?(key==L"FILE"?world->file:world->bone):fallback;
}
const std::wstring& wideValue(void* group,const std::wstring& key,const wchar_t* fallback) {
    event(2,group);text(key);text(std::wstring(fallback));
    if(input->index&2)world->type=fallback;
    return world->type;
}
int intValue(void* group,const std::wstring& key,int fallback) {
    event(3,group);text(key);number(fallback);
    return input->index&16?fallback:int(input->index%7)-3;
}
bool boolValue(void* group,const std::wstring& key,bool fallback) {
    event(4,group);text(key);number(fallback);
    return input->index&(key==L"ATTACHES"?4:8)?fallback:!fallback;
}
void* master(){number(5);return world->master;}
int type(void* hierarchy,const std::wstring& name){event(6,hierarchy);text(name);return int(input->index)*13+name.size();}
void execute(Case& c,bool ours,autotest::Capture& out) {
    input=&c;output=&out;autotest::g_arenaUsed=0;
    World storage;world=&storage;
    field<void*>(storage.master,0x80)=storage.hierarchy;
    unsigned char* self=static_cast<unsigned char*>(object(sizeof(CUnitThemeParticle)));
    std::memset(self,0xa5,sizeof(CUnitThemeParticle));
    std::wstring* file=new(self+0x10)std::wstring(L"old file");
    std::wstring* bone=new(self+0x28)std::wstring(L"old bone");
    detour::Set redirects;
    TL_REDIRECT(redirects,themeString,&stringValue);TL_REDIRECT(redirects,themeWide,&wideValue);
    TL_REDIRECT(redirects,themeInteger,&intValue);TL_REDIRECT(redirects,themeBoolean,&boolValue);
    TL_REDIRECT(redirects,themeMaster,&master);TL_REDIRECT(redirects,themeType,&type);
    if(redirects.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    autotest::invoke(out,ours?themeCandidate:themeOriginal,self,static_cast<void*>(storage.group));
    text(*file);text(*bone);out.add(self+0x18,0x10);
    text(storage.file);text(storage.bone);text(storage.type);
    file->~basic_string();bone->~basic_string();
}
}
TL_TEST(advance_theme_load){return smallmass::run(host,0,"advance_theme_load",(uintptr_t)themeOriginal,theme_test::execute,64);}

TL_ORIGINAL(void*,depthOriginal,(void*,void*,unsigned),"_ZN8CDungeon28getLevelTemplateDataForDepthEP11CGameClientj")
extern "C" void* depthCandidate(void*,void*,unsigned) __asm__("_ZN8CDungeon28getLevelTemplateDataForDepthEP11CGameClientj");
TL_FUNCTION(depthStrata,"_ZN8CDungeon17getStrataTemplateEj")
TL_FUNCTION(depthManager,"_ZN15CDungeonManager12getSingletonEv")
TL_FUNCTION(depthFind,"_ZN15CDungeonManager16getDungeonByNameESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(depthRandom,"_ZN8CDungeon26getRandomLevelTemplateDataEv")
namespace depth_test {
using namespace smallmass;
void *level,*manager,*fallback,*randomLevel;
void* strata(void* dungeon,unsigned depth){event(1,dungeon);number(depth);return input->index%5?level:NULL;}
void* singleton(){number(2);return manager;}
void* find(void* self,std::wstring name){event(3,self);text(name);return input->index%7?fallback:NULL;}
void* random(void* self){event(4,self);return input->index%11?randomLevel:NULL;}
void execute(Case& c,bool ours,autotest::Capture& out) {
    input=&c;output=&out;autotest::g_arenaUsed=0;
    void* dungeon=object(sizeof(CDungeon));level=object(sizeof(CLevelTemplateData));
    manager=object(16);fallback=object(sizeof(CDungeon));randomLevel=object(sizeof(CLevelTemplateData));
    std::wstring* name=new(static_cast<char*>(level)+0x60)std::wstring(c.index&1?L"FALLBACK":L"");
    unsigned count=c.index%7;
    field<unsigned>(dungeon,0x18)=count;
    unsigned depths[]={0,count?count-1:0,count,count+1,~0u};
    detour::Set redirects;
    TL_REDIRECT(redirects,depthStrata,&strata);TL_REDIRECT(redirects,depthManager,&singleton);
    TL_REDIRECT(redirects,depthFind,&find);TL_REDIRECT(redirects,depthRandom,&random);
    if(redirects.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    void* (*fn)(void*,void*,unsigned)=ours?depthCandidate:depthOriginal;
    if(!autotest::beginInvocation(out,fn))return;
    void* result=fn(dungeon,c.index&2?fallback:NULL,depths[(c.index/7)%5]);
    out.callCompleted=1;pointer(result);text(*name);number(field<unsigned>(dungeon,0x18));
    name->~basic_string();
}
}
TL_TEST(advance_dungeon_depth){return smallmass::run(host,0,"advance_dungeon_depth",(uintptr_t)depthOriginal,depth_test::execute,140);}
