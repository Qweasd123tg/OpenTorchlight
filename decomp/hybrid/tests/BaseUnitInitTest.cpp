#include <cstring>
#include <map>
#include <new>
#include <string>
#include <vector>
#include <OgreSceneNode.h>
#include <OgreLogManager.h>
#include "AutoTest.h"
#include "BaseUnit.h"
#include "DataGroup.h"
#include "EffectManager.h"
#include "SkillManager.h"
#include "GameClient.h"
#include "GraphManager.h"
#include "MasterResourceManager.h"
#include "StringTranslate.h"
#include "UnitThemes.h"
#include "Utilities.h"
TL_ORIGINAL(void, originalUnitInit, (CBaseUnit*,CDataGroup*,bool), "_ZN9CBaseUnit8unitInitEP10CDataGroupb")
extern "C" void unitInitAddFloat(CDataGroup*,const std::wstring&,float) __asm__("_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEf");
extern "C" void* initBaseTable[] __asm__("_ZTV9CBaseUnit");
extern void* initSkillParser __asm__("_ZL13g_SkillParser");
extern CUnitThemes* initThemes __asm__("_ZL13g_pUnitThemes");
extern CGraphManager* initGraphs __asm__("_ZL15g_pGraphManager");
extern CMasterResourceManager* m_pMasterResourceManager;
namespace {
struct Case {unsigned int seed;};
unsigned int modelCalls;
void* noModel(void*) {++modelCalls;return NULL;}
void pointerAt(void* p,size_t offset,void* v) {std::memcpy(static_cast<char*>(p)+offset,&v,sizeof(v));}
void* readPointer(void* p,size_t offset) {void* v;std::memcpy(&v,static_cast<char*>(p)+offset,sizeof(v));return v;}
void uintAt(void* p,size_t offset,unsigned int v) {std::memcpy(static_cast<char*>(p)+offset,&v,4);}
void dumpText(const std::wstring& s,autotest::Capture& out) {size_t n=s.size();out.add(&n,sizeof(n));out.add(s.data(),n*sizeof(wchar_t));}
struct Entry {Ogre::String text;int level;bool debug;};
struct Logs : Ogre::LogListener {
    std::vector<Entry> entries;
    virtual void messageLogged(const Ogre::String& text,Ogre::LogMessageLevel level,bool debug,const Ogre::String&) {Entry e={text,static_cast<int>(level),debug};entries.push_back(e);}
};
void side(Case& c,bool ours,autotest::Capture& out) {
    Ogre::LogManager logger;Ogre::Log* log=logger.createLog("base-unit-init-test",true,false,true);Logs logs;log->addListener(&logs);
    CDataGroup data(L"UNIT",NULL,4,4,NULL),oldData(L"OLD",NULL,4,4,NULL),skillA(L"SKILL",NULL,4,4,NULL),skillB(L"SKILL",NULL,4,4,NULL);
    skillA.AddDataValue(L"NAME",std::wstring(L"TEST"),false);skillA.AddDataValue(L"ACTIVATION_TYPE",std::wstring(L"NORMAL"),false);skillA.AddDataGroup(L"LEVEL1");skillA.AddDataGroup(L"LEVEL2");skillA.AddDataGroup(L"LEVEL3");
    skillB.AddDataValue(L"NAME",std::wstring(L"SECOND"),false);skillB.AddDataValue(L"ACTIVATION_TYPE",std::wstring(L"NORMAL"),false);skillB.AddDataGroup(L"LEVEL1");skillB.AddDataGroup(L"LEVEL2");
    const wchar_t* typeNames[]={L"monster",L"socketable",L"sharedstash",L"CHILD",L"UNKNOWN",L""};
    if(c.seed%7)data.AddDataValue(L"UNITTYPE",std::wstring(typeNames[c.seed%6]),false);
    if(c.seed%5)data.AddDataValue(L"UNIT_GUID",std::wstring(c.seed&2?L"1234567890123":L"-42"),false);
    data.AddDataValue(L"NAME",std::wstring(L"UNIT NAME"),false);
    const float scales[]={0,1,2.5f,-1},variations[]={0,0.25f,-0.5f,1};
    if(c.seed%4)unitInitAddFloat(&data,L"SCALE",scales[(c.seed/4)%4]);
    if(c.seed%3)unitInitAddFloat(&data,L"SCALE_VARIATION",variations[(c.seed/3)%4]);
    if(c.seed&2)data.AddDataValue(L"SHADOWS",(c.seed&4)!=0);
    if(c.seed&4)data.AddDataValue(L"BLOCK",(c.seed&8)!=0);
    if(c.seed&8)data.AddDataValue(L"OCCUPIESNODES",(c.seed&16)!=0);
    if(c.seed&16)data.AddDataValue(L"COLLIDEABLE",(c.seed&32)!=0);
    if(c.seed&4)data.AddDataValue(L"LEVEL",2u);
    if(c.seed&8)data.AddDataValue(L"CHARGES",3u);
    if(c.seed&2)data.AddDataValue(L"ENABLED",false);
    if(c.seed%4)for(unsigned int i=0;i<3;++i) {
        CDataGroup* g=data.AddDataGroup(L"SKILL");g->AddDataValue(L"NAME",std::wstring(i==0?L"TEST":i==1?L"SECOND":L"MISSING"),false);
        if(i==0) {
            if(c.seed&16)g->AddDataValue(L"LEVEL",1u);
            g->AddDataValue(L"LEVEL_REQUIRED",4u);g->AddDataValue(L"SKILL_REQUIRED",std::wstring(L"PREVIOUS"),false);
            if(c.seed&8) {g->AddDataValue(L"COLUMN",2u);g->AddDataValue(L"ROW",3u);g->AddDataValue(L"PANE",4u);}
            g->AddDataValue(L"CHANCE",66u);g->AddDataValue(L"CANCEL_CHANCE",9u);
            if(c.seed&4)g->AddDataValue(L"ENABLED",true);
            if(c.seed&32)g->AddDataValue(L"CHARGES",17u);
            g->AddDataValue(L"ANIMATION_OVERRIDE",std::wstring(L"RUN"),false);
            g->AddDataValue(L"ANIMATION_OVERRIDEDW",std::wstring(L"RUN_DW"),false);
            g->AddDataValue(L"ANIMATION_OVERRIDELOOP",std::wstring(L"LOOP"),false);
            g->AddDataValue(L"ANIMATION_OVERRIDELOOPDW",std::wstring(L"LOOP_DW"),false);
        }
    }
    if(c.seed%3==0) {CDataGroup* affixes=data.AddDataGroup(L"AFFIXES");affixes->AddDataValue(L"A",std::wstring(L"alpha"),false);}
    if(c.seed%4!=0) {CDataGroup* container=c.seed&2?data.AddDataGroup(L"EFFECTS"):&data;CDataGroup* effect=container->AddDataGroup(L"EFFECT");effect->AddDataValue(L"NAME",std::wstring(L"UNITBUFF"),false);effect->AddDataValue(L"TYPE",std::wstring(L"DAMAGE"),false);effect->AddDataValue(L"ACTIVATION",std::wstring(L"PASSIVE"),false);unitInitAddFloat(effect,L"VALUE",13);}
    long long base[0x1d8/8],resources[0x48/8],hierarchy[0x100/8],client[0x3910/8],player[0xa70/8],parser[0x80/8],themes[0x30/8],graphs[0x90/8],master[0x190/8],catalog[0x60/8],affix[0xc8/8];
    std::memset(base,0,sizeof(base));std::memset(resources,0,sizeof(resources));std::memset(hierarchy,0,sizeof(hierarchy));std::memset(client,0,sizeof(client));std::memset(player,0,sizeof(player));std::memset(parser,0,sizeof(parser));std::memset(themes,0,sizeof(themes));std::memset(graphs,0,sizeof(graphs));std::memset(master,0,sizeof(master));std::memset(catalog,0,sizeof(catalog));std::memset(affix,0,sizeof(affix));
    void* table[82];std::memcpy(table,initBaseTable,sizeof(table));table[62]=reinterpret_cast<void*>(&noModel);pointerAt(base,0,table+2);pointerAt(base,0x68,resources);pointerAt(base,0x1b0,&oldData);
    uintAt(base,0x100,7);uintAt(base,0x1ac,c.seed&4?120:170);long long previousGuid=-77;std::memcpy(reinterpret_cast<char*>(base)+0x1a0,&previousGuid,8);
    char* self=reinterpret_cast<char*>(base);self[0x18d]=1;self[0x18e]=1;self[0x18f]=0;self[0x190]=(c.seed&32)!=0;self[0x19c]=1;self[0x1a9]=0;
    Ogre::SceneNode node(NULL);pointerAt(base,0x58,&node);Ogre::Vector3 initialScale(9,8,7);std::memcpy(self+0x90,&initialScale,sizeof(initialScale));node.setScale(initialScale);
    typedef std::map<unsigned int,std::vector<unsigned int> > Relations;Relations* relations=new(reinterpret_cast<char*>(hierarchy)+0x10)Relations;(*relations)[777].push_back(120);
    typedef std::map<std::wstring,unsigned int> Types;Types* types=new(reinterpret_cast<char*>(hierarchy)+0x40)Types;(*types)[L"MONSTER"]=27;(*types)[L"SOCKETABLE"]=120;(*types)[L"SHAREDSTASH"]=170;(*types)[L"CHILD"]=777;pointerAt(resources,0x20,hierarchy);
    TArrayList<CGameClient*>* clients=new(reinterpret_cast<char*>(resources)+0x28)TArrayList<CGameClient*>(1);clients->add(reinterpret_cast<CGameClient*>(client));if(c.seed%5)pointerAt(client,0x58,player);reinterpret_cast<char*>(player)[0x791]=c.seed&2?static_cast<char>(0xd6):c.seed&4?1:0;
    typedef std::map<std::wstring,CDataGroup*> Skills;Skills* skills=new(reinterpret_cast<char*>(parser)+0x10)Skills;(*skills)[L"TEST"]=&skillA;(*skills)[L"SECOND"]=&skillB;void* savedParser=initSkillParser;initSkillParser=parser;
    TArrayList<CUnitTheme*>* themeList=new(reinterpret_cast<char*>(themes)+0x18)TArrayList<CUnitTheme*>(1);CUnitThemes* savedThemes=initThemes;initThemes=reinterpret_cast<CUnitThemes*>(themes);
    typedef std::map<std::wstring,CGraph*> Graphs;Graphs* byName=new(reinterpret_cast<char*>(graphs)+0x18)Graphs;Graphs* byFile=new(reinterpret_cast<char*>(graphs)+0x48)Graphs;CGraphManager* savedGraphs=initGraphs;initGraphs=reinterpret_cast<CGraphManager*>(graphs);
    typedef std::map<std::wstring,void*> Affixes;Affixes* entries=new(reinterpret_cast<char*>(catalog)+0x18)Affixes;
    char* templateAffix=reinterpret_cast<char*>(affix);for(unsigned int offset=0x48;offset<=0x60;offset+=8)new(templateAffix+offset)std::wstring;
    *reinterpret_cast<std::wstring*>(templateAffix+0x50)=L"ALPHA";templateAffix[0xa0]=1;uintAt(affix,0x6c,100);float one=1;std::memcpy(templateAffix+0xa4,&one,4);(*entries)[L"ALPHA"]=affix;
    pointerAt(master,0x58,catalog);CMasterResourceManager* savedMaster=m_pMasterResourceManager;m_pMasterResourceManager=reinterpret_cast<CMasterResourceManager*>(master);
    CBaseUnit* object=reinterpret_cast<CBaseUnit*>(base);if(c.seed&64)pointerAt(base,0x1c8,new CSkillManager(reinterpret_cast<CResourceManager*>(resources),object));if(c.seed&128)pointerAt(base,0x1b8,new CEffectManager(NULL));
    CDataGroup* input=c.seed%23?&data:NULL;modelCalls=0;
    for(unsigned int step=0;step<2;++step) {
        if(ours)object->CBaseUnit::unitInit(input,(c.seed&1)!=0);else originalUnitInit(object,input,(c.seed&1)!=0);
        int dataId=readPointer(base,0x1b0)==&data?1:readPointer(base,0x1b0)==&oldData?2:0;out.add(&dataId,4);
        out.add(self+0x100,4);out.add(self+0x18d,4);out.add(self+0x19c,1);out.add(self+0x1a0,8);out.add(self+0x1a9,1);out.add(self+0x1ac,4);out.add(self+0x90,12);out.add(&node.getScale(),sizeof(Ogre::Vector3));out.add(&modelCalls,4);
        CSkillManager* skillManager=static_cast<CSkillManager*>(readPointer(base,0x1c8));bool present=skillManager!=NULL;out.add(&present,1);
        if(skillManager) {TArrayList<void*>* known=reinterpret_cast<TArrayList<void*>*>(reinterpret_cast<char*>(skillManager)+0x60);unsigned int count=known->size();out.add(&count,4);for(unsigned int i=0;i<count;++i){char* skill=static_cast<char*>((*known)[i]);out.add(skill+0x6d,1);out.add(skill+0xd8,8);out.add(skill+0x10c,20);out.add(skill+0x124,4);dumpText(*reinterpret_cast<std::wstring*>(skill+0xd0),out);for(unsigned int offset=0x128;offset<=0x140;offset+=8)dumpText(*reinterpret_cast<std::wstring*>(skill+offset),out);}}
        CEffectManager* effectManager=static_cast<CEffectManager*>(readPointer(base,0x1b8));present=effectManager!=NULL;out.add(&present,1);
        if(effectManager) {char* manager=reinterpret_cast<char*>(effectManager);out.add(manager+0x80,0x248);TArrayList<void*>* applied=reinterpret_cast<TArrayList<void*>*>(manager+0x10);unsigned int n=applied->size();out.add(&n,4);for(unsigned int i=0;i<n;++i){char* value=static_cast<char*>((*applied)[i]);dumpText(*reinterpret_cast<std::wstring*>(value+0x50),out);out.add(value+0x7c,4);}for(unsigned int activation=0;activation<3;++activation){TArrayList<void*>* effects=reinterpret_cast<TArrayList<void*>*>(manager+0x28+activation*0x18);n=effects->size();out.add(&n,4);for(unsigned int i=0;i<n;++i){char* effect=static_cast<char*>((*effects)[i]);out.add(effect+0x10,4);out.add(effect+0x1c,8);dumpText(*reinterpret_cast<std::wstring*>(effect+0x80),out);}}}
        float next=UTILITIES::randomBetweenVolatile(-1,1);out.add(&next,4);
    }
    size_t n=logs.entries.size();out.add(&n,sizeof(n));for(size_t i=0;i<n;++i){size_t len=logs.entries[i].text.size();out.add(&len,sizeof(len));out.add(logs.entries[i].text.data(),len);out.add(&logs.entries[i].level,4);out.add(&logs.entries[i].debug,1);}
    delete static_cast<CSkillManager*>(readPointer(base,0x1c8));delete static_cast<CEffectManager*>(readPointer(base,0x1b8));typedef TArrayList<TSafePointer<void*>*> SafeList;delete static_cast<SafeList*>(readPointer(base,8));
    initSkillParser=savedParser;initThemes=savedThemes;initGraphs=savedGraphs;m_pMasterResourceManager=savedMaster;skills->~Skills();themeList->~TArrayList<CUnitTheme*>();byName->~Graphs();byFile->~Graphs();entries->~Affixes();for(unsigned int offset=0x48;offset<=0x60;offset+=8)reinterpret_cast<std::wstring*>(templateAffix+offset)->~basic_string();clients->~TArrayList<CGameClient*>();types->~Types();relations->~Relations();log->removeListener(&logs);
}
void original(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(base_unit_full_initialization) {
    int failures=0;
    for(unsigned int seed=0;seed<192;++seed) {Case c={seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok) {size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    unit init seed %u status %d/%d bytes %lu/%lu difference %lu\n",seed,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);}TL_CHECK(failures,ok);}
    return failures;
}
