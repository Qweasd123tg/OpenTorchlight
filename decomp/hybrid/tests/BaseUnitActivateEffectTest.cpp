#include <cstring>
#include <cwchar>
#include <limits>
#include <map>
#include <new>
#include <string>
#include <vector>
#include <OgreLogManager.h>
#include "AutoTest.h"
#include "BaseUnit.h"
#include "DataGroup.h"
#include "Effect.h"
#include "SkillManager.h"
#include "Utilities.h"
TL_ORIGINAL(void, originalActivateEffect, (CBaseUnit*,CEffect*), "_ZN9CBaseUnit14activateEffectEP7CEffect")
extern "C" void* activateBaseTable[] __asm__("_ZTV9CBaseUnit");
extern "C" void* activateEffectTable[] __asm__("_ZTV7CEffect");
extern void* activateSkillParser __asm__("_ZL13g_SkillParser");
namespace {
struct Case {unsigned int seed;};
unsigned int modelCalls;
void* noModel(void*) {++modelCalls;return NULL;}
void pointerAt(void* p,size_t offset,void* v) {std::memcpy(static_cast<char*>(p)+offset,&v,sizeof(v));}
void* readPointer(void* p,size_t offset) {void* v;std::memcpy(&v,static_cast<char*>(p)+offset,sizeof(v));return v;}
void uintAt(void* p,size_t offset,unsigned int v) {std::memcpy(static_cast<char*>(p)+offset,&v,4);}
struct Logs : Ogre::LogListener {
    std::vector<Ogre::String> entries;
    virtual void messageLogged(const Ogre::String& message,Ogre::LogMessageLevel,bool,const Ogre::String&) {entries.push_back(message);}
};
void side(Case& c,bool ours,autotest::Capture& out) {
    Ogre::LogManager logger;Ogre::Log* log=logger.createLog("activate-effect-test",true,false,true);Logs logs;log->addListener(&logs);
    CDataGroup data(L"SKILL",NULL,4,4,NULL);data.AddDataValue(L"NAME",std::wstring(L"TEST"),false);data.AddDataValue(L"ACTIVATION_TYPE",std::wstring(L"NORMAL"),false);
    unsigned int levelCount=c.seed>=312?1001:2;
    for(unsigned int i=1;i<=levelCount;++i) {wchar_t levelName[32];swprintf(levelName,32,L"LEVEL%u",i);data.AddDataGroup(levelName);}
    long long base[0x1d8/8],effect[0x138/8],parser[0x80/8],resources[0x48/8],hierarchy[0x100/8];std::memset(base,0,sizeof(base));std::memset(effect,0,sizeof(effect));std::memset(parser,0,sizeof(parser));std::memset(resources,0,sizeof(resources));std::memset(hierarchy,0,sizeof(hierarchy));
    typedef std::map<unsigned int,std::vector<unsigned int> > Relations;Relations* relations=new(reinterpret_cast<char*>(hierarchy)+0x10)Relations;
    pointerAt(resources,0x20,hierarchy);pointerAt(base,0x68,resources);
    void* table[82];std::memcpy(table,activateBaseTable,sizeof(table));table[62]=reinterpret_cast<void*>(&noModel);pointerAt(base,0,table+2);pointerAt(effect,0,activateEffectTable+2);uintAt(base,0x100,7);
    typedef std::map<std::wstring,CDataGroup*> Skills;Skills* skills=new(reinterpret_cast<char*>(parser)+0x10)Skills;(*skills)[L"TEST"]=&data;
    void* savedParser=activateSkillParser;activateSkillParser=c.seed%17?parser:NULL;
    const unsigned int types[]={0,73,74,75,76,77,80,81,82,104,105,106,144};uintAt(effect,0x1c,c.seed>=312?74:types[c.seed%13]);
    const unsigned int levels[]={0,1,2,1000,1001,0xffffffff};uintAt(effect,0x10,c.seed==312?1001:c.seed==313?1000:levels[(c.seed/13)%6]);
    const float values[]={0,0.5f,2.75f,-3,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};float value=values[(c.seed/39)%6];std::memcpy(reinterpret_cast<char*>(effect)+0xc8,&value,4);
    std::wstring* name=new(reinterpret_cast<char*>(effect)+0x80)std::wstring(c.seed%7?L"TEST":L"MISSING");
    if(c.seed&1)pointerAt(base,0x1c8,new CSkillManager(reinterpret_cast<CResourceManager*>(resources),reinterpret_cast<CBaseUnit*>(base)));
    modelCalls=0;UTILITIES::setSeed(c.seed+1);
    CBaseUnit* object=reinterpret_cast<CBaseUnit*>(base);CEffect* target=reinterpret_cast<CEffect*>(effect);
    if(ours)object->activateEffect(target);else originalActivateEffect(object,target);
    out.add(reinterpret_cast<char*>(effect)+0x10,0x70);out.add(reinterpret_cast<char*>(effect)+0xc4,0x20);out.add(&modelCalls,sizeof(modelCalls));
    CSkillManager* manager=static_cast<CSkillManager*>(readPointer(base,0x1c8));bool present=manager!=NULL;out.add(&present,sizeof(present));
    if(manager) {
        TArrayList<void*>* known=reinterpret_cast<TArrayList<void*>*>(reinterpret_cast<char*>(manager)+0x60);unsigned int count=known->size();out.add(&count,sizeof(count));
        for(unsigned int i=0;i<count;++i) {char* skill=static_cast<char*>((*known)[i]);out.add(skill+0xdc,4);out.add(skill+0x10c,4);out.add(skill+0x124,4);}
    }
    size_t n=logs.entries.size();out.add(&n,sizeof(n));for(size_t i=0;i<n;++i){size_t len=logs.entries[i].size();out.add(&len,sizeof(len));out.add(logs.entries[i].data(),len);}
    delete manager;typedef TArrayList<TSafePointer<void*>*> SafeList;delete static_cast<SafeList*>(readPointer(base,8));
    name->~basic_string();activateSkillParser=savedParser;skills->~Skills();relations->~Relations();log->removeListener(&logs);
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(base_unit_activate_skill_effects) {
    int failures=0;
    for(unsigned int seed=0;seed<314;++seed) {Case c={seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok)host->log("    activate effect seed %u status %d/%d bytes %lu/%lu\n",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);}
    return failures;
}
