#include <cstring>
#include <map>
#include <new>
#include <string>
#include "AutoTest.h"
#include "BaseUnit.h"
#include "DataGroup.h"
#include "EffectManager.h"
#include "GraphManager.h"
#include "UnitThemes.h"
TL_ORIGINAL(void, originalReapplyEffects, (CBaseUnit*,bool), "_ZN9CBaseUnit14reapplyEffectsEb")
extern "C" void* reapplyBaseTable[] __asm__("_ZTV9CBaseUnit");
extern CUnitThemes* reapplyThemes __asm__("_ZL13g_pUnitThemes");
extern CGraphManager* reapplyGraphs __asm__("_ZL15g_pGraphManager");
namespace {
struct Case {unsigned int seed;};
void pointerAt(void* p,size_t offset,void* v) {std::memcpy(static_cast<char*>(p)+offset,&v,sizeof(v));}
void* readPointer(void* p,size_t offset) {void* v;std::memcpy(&v,static_cast<char*>(p)+offset,sizeof(v));return v;}
void dumpText(const std::wstring& s,autotest::Capture& out) {size_t n=s.size();out.add(&n,sizeof(n));out.add(s.data(),n*sizeof(wchar_t));}
void side(Case& c,bool ours,autotest::Capture& out) {
    CDataGroup data(L"UNIT",NULL,4,4,NULL);
    unsigned int shape=(c.seed/4)%6;CDataGroup* container=&data;
    if(shape>=2)container=data.AddDataGroup(L"EFFECTS");
    unsigned int count=shape==0||shape==2?0:shape==1||shape==3?1:2;
    for(unsigned int i=0;i<count;++i) {
        CDataGroup* effect=container->AddDataGroup(L"EFFECT");
        effect->AddDataValue(L"NAME",std::wstring(i&&shape==5?L"SECOND":L"TEST"),false);
        effect->AddDataValue(L"TYPE",std::wstring(L"DAMAGE"),false);
        effect->AddDataValue(L"LEVEL",1u);
    }
    if(shape==5) {CDataGroup* ignored=data.AddDataGroup(L"EFFECT");ignored->AddDataValue(L"NAME",std::wstring(L"ROOT"),false);}
    long long base[0x1d8/8],catalog[0x30/8],graphs[0x90/8];std::memset(base,0,sizeof(base));std::memset(catalog,0,sizeof(catalog));std::memset(graphs,0,sizeof(graphs));
    pointerAt(base,0,reapplyBaseTable+2);unsigned int level=7;std::memcpy(reinterpret_cast<char*>(base)+0x100,&level,4);
    TArrayList<CUnitTheme*>* themes=new(reinterpret_cast<char*>(catalog)+0x18)TArrayList<CUnitTheme*>(1);
    CUnitThemes* savedThemes=reapplyThemes;reapplyThemes=reinterpret_cast<CUnitThemes*>(catalog);
    typedef std::map<std::wstring,CGraph*> Graphs;
    Graphs* byName=new(reinterpret_cast<char*>(graphs)+0x18)Graphs;Graphs* byFile=new(reinterpret_cast<char*>(graphs)+0x48)Graphs;
    CGraphManager* savedGraphs=reapplyGraphs;reapplyGraphs=reinterpret_cast<CGraphManager*>(graphs);
    if(c.seed%13)pointerAt(base,0x1b0,&data);
    if(c.seed&1)pointerAt(base,0x1b8,new CEffectManager(NULL));
    CBaseUnit* object=reinterpret_cast<CBaseUnit*>(base);
    for(unsigned int step=0;step<2;++step) {
        if(ours)object->reapplyEffects((c.seed&2)!=0);else originalReapplyEffects(object,(c.seed&2)!=0);
        CEffectManager* manager=static_cast<CEffectManager*>(readPointer(base,0x1b8));bool present=manager!=NULL;out.add(&present,sizeof(present));
        if(manager)for(unsigned int activation=0;activation<3;++activation) {
            TArrayList<void*>* list=reinterpret_cast<TArrayList<void*>*>(reinterpret_cast<char*>(manager)+0x28+activation*0x18);
            unsigned int n=list->size();out.add(&n,sizeof(n));
            for(unsigned int i=0;i<n;++i) {char* effect=static_cast<char*>((*list)[i]);out.add(effect+0x10,4);out.add(effect+0x1c,8);dumpText(*reinterpret_cast<std::wstring*>(effect+0x80),out);}
        }
        unsigned int groups=data.GetNumberOfDataGroups();out.add(&groups,sizeof(groups));
    }
    CEffectManager* manager=static_cast<CEffectManager*>(readPointer(base,0x1b8));delete manager;
    typedef TArrayList<TSafePointer<void*>*> SafeList;delete static_cast<SafeList*>(readPointer(base,8));
    reapplyGraphs=savedGraphs;byName->~Graphs();byFile->~Graphs();reapplyThemes=savedThemes;themes->~TArrayList<CUnitTheme*>();
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(base_unit_reapply_effect_data) {
    int failures=0;
    for(unsigned int seed=0;seed<96;++seed) {Case c={seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok)host->log("    reapply effects seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);}
    return failures;
}
