#include <Ogre.h>
#include <OgreUTFString.h>
#include <cstring>
#include <string>
#include <new>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Editor.h"
#undef protected
#undef private
#include "iEditorResourceManager.h"

#define GETTER(n, symbol) TL_ORIGINAL(wchar_t*,old##n,(),symbol) extern "C" wchar_t* next##n() __asm__(symbol);
GETTER(0,"_Z19EditorGetSkillTypesv")
GETTER(1,"_Z25EditorGetSkillTargetTypesv")
GETTER(2,"_Z24EditorGetSkillEventTypesv")
GETTER(3,"_Z39EditorGetSkillEffectAndAffixTargetTypesv")
GETTER(4,"_Z29EditorGetSkillActivationTypesv")
TL_ORIGINAL(void,skillEditorCtor,(CEditor*),"_ZN7CEditorC1Ev")
TL_ORIGINAL(void,skillEditorDtor,(CEditor*),"_ZN7CEditorD1Ev")
TL_FUNCTION(skillDirectory,"_ZN10FILESYSTEM22CreateAppDataDirectoryERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(skillCopy,"_Z10copyFileToRKSbIwSt11char_traitsIwESaIwEES4_")
extern char sEditorTmpMemory[4000];

namespace {
struct Manager: iEditorResourceManager {
    void editorUpdateSceneOnce(int){} void* getWindowHandle(){return NULL;}
    CSettings* getSettings(){return NULL;} Ogre::SceneManager* getSceneManager(){return NULL;}
    CSoundManager* getSoundManager(){return NULL;} Ogre::RenderWindow* getRenderWindow(){return NULL;}
    Ogre::Camera* getGameCamera(){return NULL;} void updateAspectRatio(float,float){}
    CGameClient* getGameClient(){return NULL;}
};
struct Case { unsigned operation,seed; bool observed,negative; };
const Case* current; autotest::Capture* capture; CEditor* editor;
std::wstring inputs[12];
typedef wchar_t*(*Getter)();
Getter originalGetters[]={old0,old1,old2,old3,old4};
Getter candidateGetters[]={next0,next1,next2,next3,next4};
const unsigned counts[]={4,12,11,5,5};
const uintptr_t nativeTables[]={0x14624a0,0x1462400,0x14623a0,0x1462560,0x1462460};
const uintptr_t targets[]={0x736260,0x739e90,0x73acd0,0x73bb20,0x73c730};
void number(unsigned value){capture->add(&value,sizeof value);}
bool directory(const std::wstring&){return true;}
void copy(const std::wstring&,const std::wstring&){}
std::wstring name(unsigned profile,unsigned i)
{
    const wchar_t* canonical[5][12]={
        {L"SKILL",L"OFFENSIVE",L"DEFENSIVE",L"CHARM"},
        {L"NONE",L"POSITION",L"TARGET",L"SELF",L"EVERYBODY",L"POSITIONRANDOM",L"POSITIONFLEE",L"ITEM",L"UNIDENTIFIEDITEM",L"PETS",L"SELFANDPETS",L"TARGET_POS"},
        {L"EVENT_START",L"EVENT_END",L"EVENT_TRIGGER",L"EVENT_TRIGGER_TWO",L"EVENT_UNITHIT",L"EVENT_UNITDIE",L"EVENT_MISSILEHIT",L"EVENT_MISSILEDIE",L"EVENT_DIEBYEFFECT",L"EVENT_CASTERDIE",L"EVENT_UNIT_CREATE"},
        {L"ENEMY",L"SELF",L"PET",L"EVERYBODY",L"FRIEND"},
        {L"ANY",L"PROC",L"WEAPON",L"NORMAL",L"PASSIVE"}
    };
    if(!current->observed||profile==0)return canonical[current->operation][i];
    switch(profile){
    case 1:return L"";
    case 2:return L"\u00e9\u03a9\u0416\u4e2d";
    case 3:return std::wstring(L"A\0B",3);
    case 4:return L"\U0001f600\U0010ffff";
    case 5:return std::wstring(31,static_cast<wchar_t>('A'+i));
    case 6:return std::wstring(64,static_cast<wchar_t>('a'+i));
    case 7:return std::wstring(150,static_cast<wchar_t>('Z'-i));
    case 8:{unsigned n=counts[current->operation],total=1998-n;return std::wstring(total/n+(i<total%n?1:0),':');}
    case 9:return std::wstring(500000,L'q');
    case 10:return L"\u0800\ud7ff\ue000\uffff";
    default:{std::wstring r;r+=static_cast<wchar_t>(0xd800);r+=static_cast<wchar_t>(0xdc00);r+=static_cast<wchar_t>(0xdfff);r+=static_cast<wchar_t>(0xd800);return r;}
    }
}
void initializeOriginalStrings()
{
    // All tables are actual writable ELF BSS objects. hybrid.py redirects the
    // TU-local STT_OBJECT references in the candidate to these same slots.
    for(unsigned i=0;i<counts[current->operation];++i){
        inputs[i]=name(current->seed/4%12,i);
        std::wstring* slot=reinterpret_cast<std::wstring*>(nativeTables[current->operation])+i;
        void* data=NULL;std::memcpy(&data,slot,sizeof data);
        if(!data)new(slot)std::wstring(inputs[i]);else *slot=inputs[i];
    }
    std::wstring* empty=reinterpret_cast<std::wstring*>(0x1460598);
    void* data=NULL;std::memcpy(&data,empty,sizeof data);
    if(!data)new(empty)std::wstring;else empty->clear();
}
void side(void* argument,autotest::Capture& out,bool ours)
{
    current=static_cast<Case*>(argument);capture=&out;
    initializeOriginalStrings();int liveBefore=g_iTotalCountOfObjects;CEditor* previous=gEditor;
    editor=static_cast<CEditor*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEditor),0,0,0));
    {detour::Set setup;TL_REDIRECT(setup,skillDirectory,&directory);TL_REDIRECT(setup,skillCopy,&copy);if(setup.failed()){out.issue=autotest::Capture::InvalidReport;return;}skillEditorCtor(editor);}
    Manager manager;gEditor=editor;
    unsigned guard=current->seed%4;
    editor->m_bDisabled=(guard&1)!=0;editor->m_pEditorResourceManager=guard&2?NULL:&manager;
    char initial[4000];for(unsigned i=0;i<sizeof initial;++i)initial[i]=static_cast<char>((i*37+current->seed*19+0x53)&255);
    std::memcpy(sEditorTmpMemory,initial,sizeof initial);
    Getter function=ours?candidateGetters[current->operation]:originalGetters[current->operation];
    if(!autotest::beginInvocation(out,function))return;
    wchar_t* result=function();out.callCompleted=1;
    if(ours&&current->negative)sEditorTmpMemory[12]^=0x20;
    number(result==NULL);number(result==reinterpret_cast<wchar_t*>(sEditorTmpMemory));
    number(gEditor==editor);number(editor->m_bDisabled);number(editor->m_pEditorResourceManager==&manager);
    out.add(sEditorTmpMemory,sizeof sEditorTmpMemory);
    for(unsigned i=0;i<counts[current->operation];++i){const std::wstring& item=reinterpret_cast<std::wstring*>(nativeTables[current->operation])[i];number(item.size());unsigned hash=2166136261u;for(unsigned j=0;j<item.size();++j)hash=(hash^static_cast<unsigned>(item[j]))*16777619u;number(hash);}

    // Independent expected bytes expose the original's 2-byte copy multiplier
    // on Linux wchar_t=4, including truncated code units and the four-byte NUL.
    char expected[4000];std::memcpy(expected,initial,sizeof expected);std::memset(expected,0,4);
    if(guard==0){
        std::wstring text;Ogre::UTFString comma(",");
        for(unsigned i=0;i<counts[current->operation];++i)text+=static_cast<std::wstring>(Ogre::UTFString(inputs[i])+comma);
        if(text.size()<2000000){size_t bytes=text.size()*2;if(bytes+4>sizeof expected){out.issue=autotest::Capture::InvalidReport;return;}std::memcpy(expected,text.c_str(),bytes);std::memset(expected+bytes,0,4);}
    }
    number(std::memcmp(expected,sEditorTmpMemory,sizeof expected)==0);
    if(std::memcmp(expected,sEditorTmpMemory,sizeof expected)!=0&&!current->negative)out.issue=autotest::Capture::InvalidReport;
    editor->m_bDisabled=false;editor->m_pEditorResourceManager=NULL;
    skillEditorDtor(editor);Ogre::NedAllocImpl::deallocBytes(editor);gEditor=previous;
    number(g_iTotalCountOfObjects==liveBefore);
}
void original(void*p,autotest::Capture&out){side(p,out,false);}
void candidate(void*p,autotest::Capture&out){side(p,out,true);}
int run(const tlhybrid_host*host,unsigned operation,bool observed,const char*label)
{
    autotest::Coverage coverage(label,targets[operation]);unsigned count=observed?96:32;
    for(unsigned i=0;i<count;++i){Case c={operation,i,observed,false};autotest::Outcome a,b;autotest::runChild(original,&c,a,2000,20000);autotest::runChild(candidate,&c,b,2000,20000);
        if(coverage.observe(host,a,b)){size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;
            host->log("    skill getter%u observed%u seed%u status%d/%d issue%u/%u completed%u/%u bytes%lu/%lu first%lu\n",operation,observed,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)first);coverage.report(host);return 1;}}
    coverage.report(host);Case c={operation,8,observed,true};autotest::Outcome a,b;autotest::runChild(original,&c,a,2000,20000);autotest::runChild(candidate,&c,b,2000,20000);
    bool different=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    bool completed=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);
    host->log("    skill getter%u observed%u negative detected%u completed%u\n",operation,observed,unsigned(different),unsigned(completed));return !different||!completed;
}
}
TL_TEST(editor_skill_types_native){return run(host,0,false,"editor_skill_types_native");}
TL_TEST(editor_skill_types_observed){return run(host,0,true,"editor_skill_types_observed");}
TL_TEST(editor_skill_targets_native){return run(host,1,false,"editor_skill_targets_native");}
TL_TEST(editor_skill_targets_observed){return run(host,1,true,"editor_skill_targets_observed");}
TL_TEST(editor_skill_events_native){return run(host,2,false,"editor_skill_events_native");}
TL_TEST(editor_skill_events_observed){return run(host,2,true,"editor_skill_events_observed");}
TL_TEST(editor_skill_affix_targets_native){return run(host,3,false,"editor_skill_affix_targets_native");}
TL_TEST(editor_skill_affix_targets_observed){return run(host,3,true,"editor_skill_affix_targets_observed");}
TL_TEST(editor_skill_activation_native){return run(host,4,false,"editor_skill_activation_native");}
TL_TEST(editor_skill_activation_observed){return run(host,4,true,"editor_skill_activation_observed");}
