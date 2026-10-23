#include <Ogre.h>
#include <map>
#include <vector>
#include <cstring>
#include <climits>
#include <ucontext.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "LogicObject.h"
#include "LogicLink.h"
#include "LogicGroup.h"
#include "LogicGroupDescriptor.h"
#include "EditorScene.h"
#include "Settings.h"
#include "Editor.h"
#undef protected
#undef private
#include "tests/CharacterEmptyGlobals.h"
#include "tests/SystemsFixtureWorker.h"

TL_ORIGINAL(bool, invokeOld, (CLogicObject*,unsigned), "_ZN12CLogicObject6InvokeEj")
extern "C" bool invokeNew(CLogicObject*,unsigned) __asm__("_ZN12CLogicObject6InvokeEj");
TL_ORIGINAL(void, invokeSceneCtor, (CEditorScene*,const wchar_t*), "_ZN12CEditorSceneC1EPKw")
TL_ORIGINAL(void, invokeSceneDtor, (CEditorScene*), "_ZN12CEditorSceneD1Ev")
TL_ORIGINAL(void, invokeNodeCtor, (CLogicObject*,CEditorScene*,long long,unsigned), "_ZN12CLogicObjectC1EP12CEditorScenexj")
TL_ORIGINAL(void, invokeNodeDtor, (CLogicObject*), "_ZN12CLogicObjectD1Ev")
TL_ORIGINAL(void, invokeGroupCtor, (CLogicGroup*,CResourceManager*), "_ZN11CLogicGroupC1EP16CResourceManager")
TL_ORIGINAL(void, invokeGroupDtor, (CLogicGroup*), "_ZN11CLogicGroupD1Ev")
TL_ORIGINAL(void, invokeDescriptorCtor, (CLogicGroupDescriptor*,const wchar_t*,const wchar_t*,const wchar_t*), "_ZN21CLogicGroupDescriptorC1EPKwS1_S1_")
TL_ORIGINAL(void, invokeDescriptorDtor, (CLogicGroupDescriptor*), "_ZN21CLogicGroupDescriptorD1Ev")
TL_ORIGINAL(void, invokeLinkCtor, (CLogicLink*,CEditorScene*,CLogicObject*,CLogicWrapper*,CLogicObject*,CLogicWrapper*), "_ZN10CLogicLinkC1EP12CEditorSceneP12CLogicObjectP13CLogicWrapperS3_S5_")
TL_ORIGINAL(void, invokeLinkDtor, (CLogicLink*), "_ZN10CLogicLinkD1Ev")
TL_ORIGINAL(void, invokeLinkOld, (CLogicLink*,unsigned,CEditorBaseObject*), "_ZN10CLogicLink18InitiateInputEventEjP17CEditorBaseObject")
TL_ORIGINAL(int, invokeIntOld, (CDynamicPropertyFile*,unsigned), "_ZN20CDynamicPropertyFile6GetIntEj")
TL_ORIGINAL(void, invokeSettingsCtor, (CSettings*,std::wstring,std::wstring,std::wstring,std::wstring), "_ZN9CSettingsC1ESbIwSt11char_traitsIwESaIwEES3_S3_S3_")
TL_ORIGINAL(void, invokeSettingsDtor, (CSettings*), "_ZN9CSettingsD1Ev")
TL_ORIGINAL(void, invokeEditorCtor, (CEditor*), "_ZN7CEditorC1Ev")
TL_ORIGINAL(void, invokeEditorDtor, (CEditor*), "_ZN7CEditorD1Ev")
TL_FUNCTION(invokeDirectory, "_ZN10FILESYSTEM22CreateAppDataDirectoryERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(invokeCopy, "_Z10copyFileToRKSbIwSt11char_traitsIwESaIwEES4_")
TL_FUNCTION(invokeInt, "_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(invokeLink, "_ZN10CLogicLink18InitiateInputEventEjP17CEditorBaseObject")

namespace {
struct Case { unsigned seed,mode; bool negative; };
const Case* current;
autotest::Capture* output;
CSettings* settings[2];
CEditorScene* scene;
CLogicObject* self;
CLogicObject* nodes[4];
CLogicGroup* objects[4];
CLogicGroupDescriptor* descriptors[2];
std::vector<CLogicLink*> ownedLinks;
unsigned settingsCalls,linkCalls,logCalls;
detour::Set intHook,linkHook;
bool invoking,insideLink;
const tlhybrid_host* diagnosticHost;
void fault(int signal,siginfo_t* info,void* context) {
    ucontext_t* machine=static_cast<ucontext_t*>(context);
    diagnosticHost->log("    invoke signal%d seed%u mode%u links%u settings%u rip%p address%p\n",
        signal,current->seed,current->mode,linkCalls,settingsCalls,
        reinterpret_cast<void*>(machine->uc_mcontext.gregs[REG_RIP]),info->si_addr);
    autotest::crashed(signal);
}


void number(long long n) { output->add(&n,sizeof n); }
void invalid() { output->issue=autotest::Capture::InvalidReport; }
bool directory(const std::wstring&) { return true; }
void copy(const std::wstring&,const std::wstring&) {}
template<class T> T* storage() { return static_cast<T*>(Ogre::NedAllocImpl::allocBytes(sizeof(T),0,0,0)); }
unsigned objectIndex(CEditorBaseObject* p) {
    if(!p)return 98;
    for(unsigned i=0;i<4;++i)if(p==objects[i])return i;
    return 99;
}
unsigned linkIndex(CLogicLink* p) {
    for(unsigned i=0;i<ownedLinks.size();++i)if(ownedLinks[i]==p)return i;
    return 99;
}
int getInt(CDynamicPropertyFile* p,unsigned index) {
    intHook.restore();
    int value=invokeIntOld(p,index);
    TL_REDIRECT(intHook,invokeInt,&getInt);
    if(intHook.failed())invalid();
    if(invoking && !insideLink) {
        number(1);number(p==settings[0]?0:p==settings[1]?1:99);
        number(index==KSETTINGS_DEBUG_LOGIC);number(value);++settingsCalls;
        if(current->mode==1 && current->seed%7==2 && settingsCalls==1)
            scene->m_pUnknown170=settings[1];
    }
    return value;
}
void link(CLogicLink* p,unsigned event,CEditorBaseObject* sender) {
    number(2);number(linkIndex(p));number(event);number(objectIndex(sender));++linkCalls;
    if(current->mode==0) {
        linkHook.restore();insideLink=true;invokeLinkOld(p,event,sender);insideLink=false;
        TL_REDIRECT(linkHook,invokeLink,&link);
        if(linkHook.failed())invalid();
    } else if(linkCalls==1) {
        switch(current->seed%7) {
        case 0: self->m_Links.add(ownedLinks.back());break;
        case 1: if(self->m_Links.size()>1)self->m_Links[1]=NULL;break;
        case 2: scene->m_Objects[self->m_iObjectID]=objects[3];break;
        case 3: self->m_Links.clear();break;
        case 4: if(self->m_Links.size()>1)self->m_Links[1]=ownedLinks.back();break;
        default: break;
        }
    }
}
struct Listener : Ogre::LogListener {
    void messageLogged(const Ogre::String& message,Ogre::LogMessageLevel level,
                       bool maskDebug,const Ogre::String&) {
        if(!invoking)return;
        number(3);output->addText(message);number(level);number(maskDebug);++logCalls;
        // Invalid invocations in the original log the error then continue. A
        // listener can switch logging off before the unsafe second diagnostic.
        if(current->mode==1 && current->seed/7%5!=0 && logCalls==1) {
            settings[0]->SetInt(KSETTINGS_DEBUG_LOGIC,0);
            settings[1]->SetInt(KSETTINGS_DEBUG_LOGIC,0);
        }
    }
};

void side(void* raw,autotest::Capture& out,bool ours) {
    current=static_cast<Case*>(raw);output=&out;invoking=false;insideLink=false;
    settingsCalls=linkCalls=logCalls=0;ownedLinks.clear();
    const unsigned seed=current->seed;
    int before=g_iTotalCountOfObjects;
    scene=storage<CEditorScene>();invokeSceneCtor(scene,L"Invoke fixture");
    scene->m_pUnknown170=settings[0];
    settings[0]->SetInt(KSETTINGS_DEBUG_LOGIC,0);
    settings[1]->SetInt(KSETTINGS_DEBUG_LOGIC,0);
    for(unsigned i=0;i<2;++i) {
        descriptors[i]=storage<CLogicGroupDescriptor>();
        invokeDescriptorCtor(descriptors[i],i?L"Destination \u03a9":L"Source \u0416",L"Test",L"");
    }
    for(unsigned i=0;i<4;++i) {
        objects[i]=storage<CLogicGroup>();invokeGroupCtor(objects[i],NULL);
        objects[i]->m_iGuid=100+i;objects[i]->m_pDescriptor=descriptors[i?1:0];
        objects[i]->SetName(seed%3?L"object \U0001f642":L"");
        objects[i]->SetSceneOwner(scene);scene->m_Objects[100+i]=objects[i];
        nodes[i]=storage<CLogicObject>();invokeNodeCtor(nodes[i],scene,-1,10+i);
        nodes[i]->m_iObjectID=100+i;nodes[i]->m_pLinkedDescriptor=descriptors[i?1:0];
    }
    self=nodes[0];
    const unsigned counts[]={0,1,2,9,10,11,24};
    unsigned count=counts[seed%7];
    unsigned event=seed%9;
    CLogicWrapper* first=descriptors[0]->GetOutputLogicWrapper(event);
    if(!first)invalid();
    unsigned nativeEvent=first?first->m_iID:0;
    for(unsigned i=0;i<count+1;++i) {
        CLogicLink* p=storage<CLogicLink>();
        CLogicWrapper* from=descriptors[0]->GetOutputLogicWrapper(i%9);
        CLogicWrapper* to=descriptors[1]->GetInputLogicWrapper(i%8);
        invokeLinkCtor(p,scene,self,from,nodes[1+i%3],to);ownedLinks.push_back(p);
        if(i<count)self->m_Links.add((seed/7+i)%5==0?NULL:p);
    }
    unsigned condition=current->mode==1?seed/7%5:0;
    if(condition==1 || condition==4)scene->m_Objects.erase(100);
    if(condition==2 || condition==4)self->m_pLinkedDescriptor=NULL;
    if(condition==3)nativeEvent=~0u;
    bool debug=current->mode==1 && (condition!=0 || seed/35%2!=0);
    settings[0]->SetInt(KSETTINGS_DEBUG_LOGIC,debug?1:0);
    settings[1]->SetInt(KSETTINGS_DEBUG_LOGIC,seed%7==2?0:debug?1:0);
    Listener listener;
    Ogre::Log* log=Ogre::LogManager::getSingleton().getDefaultLog();
    log->addListener(&listener);
    TL_REDIRECT(intHook,invokeInt,&getInt);TL_REDIRECT(linkHook,invokeLink,&link);
    if(intHook.failed()||linkHook.failed())invalid();
    struct sigaction action;std::memset(&action,0,sizeof action);
    action.sa_sigaction=&fault;action.sa_flags=SA_SIGINFO;sigemptyset(&action.sa_mask);
    sigaction(SIGSEGV,&action,NULL);sigaction(SIGBUS,&action,NULL);sigaction(SIGABRT,&action,NULL);
    invoking=true;
    bool result=false;
    if(autotest::beginInvocation(out,ours?invokeNew:invokeOld)) {
        result=(ours?invokeNew:invokeOld)(self,nativeEvent);out.callCompleted=1;
    }
    invoking=false;intHook.restore();linkHook.restore();log->removeListener(&listener);
    if(ours && current->negative)self->m_Links.add(NULL);
    number(result);number(settingsCalls);number(linkCalls);number(logCalls);
    number(self->m_Links.size());number(self->m_Links.m_nCapacity);number(self->m_Links.m_nGrowBy);
    for(unsigned i=0;i<self->m_Links.size();++i)number(self->m_Links[i]?linkIndex(self->m_Links[i]):98);
    number(scene->m_pUnknown170==settings[0]?0:1);
    number(scene->m_Objects.count(100)?objectIndex(scene->m_Objects[100]):98);
    number(settings[0]->GetInt(KSETTINGS_DEBUG_LOGIC));number(settings[1]->GetInt(KSETTINGS_DEBUG_LOGIC));
    for(unsigned i=0;i<4;++i)number(objects[i]->m_fEnabled==1.0f);
    if(!result || settingsCalls!=(condition==0?1u:2u))invalid();
    if(condition && !logCalls)invalid();
    self->m_Links.clear();scene->m_Objects.clear();
    for(unsigned i=0;i<ownedLinks.size();++i) { invokeLinkDtor(ownedLinks[i]);Ogre::NedAllocImpl::deallocBytes(ownedLinks[i]); }
    for(unsigned i=0;i<4;++i) {
        invokeNodeDtor(nodes[i]);Ogre::NedAllocImpl::deallocBytes(nodes[i]);
        invokeGroupDtor(objects[i]);Ogre::NedAllocImpl::deallocBytes(objects[i]);
    }
    for(unsigned i=0;i<2;++i) { invokeDescriptorDtor(descriptors[i]);Ogre::NedAllocImpl::deallocBytes(descriptors[i]); }
    invokeSceneDtor(scene);Ogre::NedAllocImpl::deallocBytes(scene);
    number(g_iTotalCountOfObjects-before);
}
void original(void* p,autotest::Capture& out){side(p,out,false);}
void candidate(void* p,autotest::Capture& out){side(p,out,true);}
int worker(const tlhybrid_host* host,unsigned mode) {
    diagnosticHost=host;
    initEmptyGlobals();
    // The standalone headless loader has not run the original TU initializer.
    for(unsigned i=0;i<sizeof(gOUTPUT_EVENTS_NAMES)/sizeof(*gOUTPUT_EVENTS_NAMES);++i) {
        std::wstring* native=reinterpret_cast<std::wstring*>(0x146fde0)+i;
        void* bytes=NULL;std::memcpy(&bytes,native,sizeof bytes);
        if(!bytes)new(native)std::wstring(gOUTPUT_EVENTS_NAMES[i]);
    }
    bool ownLog=!Ogre::LogManager::getSingletonPtr();
    Ogre::LogManager* manager=ownLog?OGRE_NEW Ogre::LogManager:Ogre::LogManager::getSingletonPtr();
    Ogre::Log* previous=NULL;
    try{previous=manager->getDefaultLog();}catch(...){previous=NULL;}
    Ogre::Log* log=manager->createLog("invoke-recovery",true,false,true);
    for(unsigned i=0;i<2;++i) {settings[i]=storage<CSettings>();invokeSettingsCtor(settings[i],L"",L"",L"",L"");}
    CEditor* previousEditor=gEditor;
    CEditor* editor=storage<CEditor>();
    {detour::Set setup;TL_REDIRECT(setup,invokeDirectory,&directory);TL_REDIRECT(setup,invokeCopy,&copy);
     if(setup.failed())return 1;invokeEditorCtor(editor);}
    gEditor=editor;editor->m_iFlags=0;
    const char* name=mode?"logic_invoke_observed":"logic_invoke_native";
    autotest::Coverage coverage(name,reinterpret_cast<uintptr_t>(&invokeOld));
    int failure=0;
    for(unsigned seed=0;seed<350;++seed) {
        Case c={seed,mode,false};autotest::Outcome a,b;
        autotest::runChild(&original,&c,a);autotest::runChild(&candidate,&c,b);
        if(coverage.observe(host,a,b)) {
            host->log("    invoke mode%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",mode,seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
            failure=1;break;
        }
    }
    coverage.report(host);
    if(!failure) {
        Case c={11,mode,true};autotest::Outcome a,b;
        autotest::runChild(&original,&c,a);autotest::runChild(&candidate,&c,b);
        autotest::Coverage negative("logic_invoke_negative",reinterpret_cast<uintptr_t>(&invokeOld));
        unsigned delta=negative.observe(host,a,b);
        if(!delta || negative.completed!=1 || negative.different!=1 || negative.missing!=0)failure=1;
        host->log("    invoke negative mode%u completed=%u different=%u incomplete=%u\n",mode,negative.completed,negative.different,negative.missing);
    }
    invokeEditorDtor(editor);Ogre::NedAllocImpl::deallocBytes(editor);gEditor=previousEditor;
    for(unsigned i=0;i<2;++i) {invokeSettingsDtor(settings[i]);Ogre::NedAllocImpl::deallocBytes(settings[i]);}
    if(previous)manager->setDefaultLog(previous);
    manager->destroyLog(log);
    if(ownLog)OGRE_DELETE manager;
    return failure;
}
int nativeWorker(const tlhybrid_host* h){return worker(h,0);}
int observedWorker(const tlhybrid_host* h){return worker(h,1);}
}
TL_TEST(logic_invoke_native){return systems_fixture::isolated(&nativeWorker,host,120);}
TL_TEST(logic_invoke_observed){return systems_fixture::isolated(&observedWorker,host,120);}
