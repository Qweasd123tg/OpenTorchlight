#include <cstring>
#include <map>
#include <new>
#include <string>
#include "AutoTest.h"
#include "BaseUnit.h"
#include "DataGroup.h"
#include "EffectManager.h"
#include "MasterResourceManager.h"
#include "StringTranslate.h"
TL_ORIGINAL(void, originalReapplyAffixes, (CBaseUnit*,bool), "_ZN9CBaseUnit14reapplyAffixesEb")
extern "C" void* affixBaseTable[] __asm__("_ZTV9CBaseUnit");
extern CMasterResourceManager* m_pMasterResourceManager;
namespace {
struct Case {unsigned int seed;};
void pointerAt(void* p,size_t offset,void* v) {std::memcpy(static_cast<char*>(p)+offset,&v,sizeof(v));}
void* readPointer(void* p,size_t offset) {void* v;std::memcpy(&v,static_cast<char*>(p)+offset,sizeof(v));return v;}
void uintAt(void* p,size_t offset,unsigned int v) {std::memcpy(static_cast<char*>(p)+offset,&v,4);}
void dumpText(const std::wstring& s,autotest::Capture& out) {size_t n=s.size();out.add(&n,sizeof(n));out.add(s.data(),n*sizeof(wchar_t));}
void side(Case& c,bool ours,autotest::Capture& out) {
    CDataGroup data(L"UNIT",NULL,4,4,NULL);
    unsigned int levels[]={0,7,25,0xffffffff};if(c.seed&4)data.AddDataValue(L"LEVEL",levels[(c.seed/8)%4]);
    CDataGroup* affixes=data.AddDataGroup(c.seed%11?L"AFFIXES":L"OTHER");
    if(c.seed%7) {affixes->AddDataValue(L"A",std::wstring(L"alpha"),false);affixes->AddDataValue(L"B",std::wstring(L"alpha"),true);affixes->AddDataValue(L"C",std::wstring(c.seed&8?L"alpha":L"beta"),false);affixes->AddDataValue(L"D",std::wstring(L"missing"),false);}
    long long base[0x1d8/8],resources[0x48/8],master[0x190/8],catalog[0x60/8],templates[2][0xc8/8],translator[0x50/8];
    std::memset(base,0,sizeof(base));std::memset(resources,0,sizeof(resources));std::memset(master,0,sizeof(master));std::memset(catalog,0,sizeof(catalog));std::memset(templates,0,sizeof(templates));std::memset(translator,0,sizeof(translator));
    pointerAt(base,0,affixBaseTable+2);uintAt(base,0x100,9);
    typedef std::map<std::wstring,void*> Catalog;Catalog* entries=new(reinterpret_cast<char*>(catalog)+0x18)Catalog;
    const wchar_t* names[]={L"ALPHA",L"BETA"};
    for(unsigned int i=0;i<2;++i) {
        char* t=reinterpret_cast<char*>(templates[i]);for(unsigned int offset=0x48;offset<=0x60;offset+=8)new(t+offset)std::wstring;
        *reinterpret_cast<std::wstring*>(t+0x50)=names[i];t[0xa0]=1;uintAt(t,0x68,0);uintAt(t,0x6c,100);
        float scale=1;std::memcpy(t+0xa4,&scale,4);(*entries)[names[i]]=templates[i];
    }
    pointerAt(master,0x58,catalog);CMasterResourceManager* savedMaster=m_pMasterResourceManager;m_pMasterResourceManager=reinterpret_cast<CMasterResourceManager*>(master);
    typedef std::map<std::wstring,std::wstring> Translations;Translations* translations=new(reinterpret_cast<char*>(translator)+0x10)Translations;(*translations)[L"alpha"]=L"BETA";
    new(reinterpret_cast<char*>(translator)+0x40)std::wstring;reinterpret_cast<char*>(translator)[0x48]=1;
    CStringTranslate* savedTranslator=m_gStringTranslate;m_gStringTranslate=reinterpret_cast<CStringTranslate*>(translator);
    if(c.seed%13)pointerAt(base,0x1b0,&data);if(c.seed%17)pointerAt(base,0x68,resources);
    CBaseUnit* object=reinterpret_cast<CBaseUnit*>(base);
    if(c.seed&1) {pointerAt(base,0x1b8,new CEffectManager(NULL));object->addAffix(std::wstring(L"ALPHA"),3,object,-1.0f);}
    for(unsigned int step=0;step<2;++step) {
        if(ours)object->reapplyAffixes((c.seed&2)!=0);else originalReapplyAffixes(object,(c.seed&2)!=0);
        CEffectManager* manager=static_cast<CEffectManager*>(readPointer(base,0x1b8));bool present=manager!=NULL;out.add(&present,sizeof(present));
        if(manager) {
            TArrayList<void*>* list=reinterpret_cast<TArrayList<void*>*>(reinterpret_cast<char*>(manager)+0x10);
            unsigned int count=list->size();out.add(&count,sizeof(count));
            for(unsigned int i=0;i<count;++i) {char* affix=static_cast<char*>((*list)[i]);dumpText(*reinterpret_cast<std::wstring*>(affix+0x50),out);out.add(affix+0x7c,4);out.add(affix+0xa4,4);bool owner=readPointer(affix,0x28)==base;out.add(&owner,sizeof(owner));}
        }
        unsigned int groups=data.GetNumberOfDataGroups();out.add(&groups,sizeof(groups));
    }
    delete static_cast<CEffectManager*>(readPointer(base,0x1b8));typedef TArrayList<TSafePointer<void*>*> SafeList;delete static_cast<SafeList*>(readPointer(base,8));
    m_pMasterResourceManager=savedMaster;m_gStringTranslate=savedTranslator;translations->~Translations();reinterpret_cast<std::wstring*>(reinterpret_cast<char*>(translator)+0x40)->~basic_string();
    entries->~Catalog();for(unsigned int i=0;i<2;++i)for(unsigned int offset=0x48;offset<=0x60;offset+=8)reinterpret_cast<std::wstring*>(reinterpret_cast<char*>(templates[i])+offset)->~basic_string();
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(base_unit_reapply_affix_data) {
    int failures=0;
    for(unsigned int seed=0;seed<96;++seed) {Case c={seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok)host->log("    reapply affixes seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);}
    return failures;
}
