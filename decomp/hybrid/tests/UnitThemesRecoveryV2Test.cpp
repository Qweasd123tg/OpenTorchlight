#include <Ogre.h>
#include <string>
#include <vector>
#include <cstdio>
#include <unistd.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#include "UnitThemes.h"
#include "UnitThemeParticle.h"
#undef private
#include "tests/NativeGameServices.h"
#include "FileSystem.h"

TL_ORIGINAL(void, themeCtor, (CUnitThemes*,const wchar_t*), "_ZN11CUnitThemesC1EPKw")
TL_ORIGINAL(void, themeDtor, (CUnitThemes*), "_ZN11CUnitThemesD1Ev")
TL_ORIGINAL(void, themeReloadOld, (CUnitThemes*), "_ZN11CUnitThemes6reloadEv")
extern "C" void themeReloadNew(CUnitThemes*) __asm__("_ZN11CUnitThemes6reloadEv");
extern "C" CUnitThemes* themeSingleton __asm__("_ZL13g_pUnitThemes");
TL_FUNCTION(themeFiles, "_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(themeLoad, "_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TL_FUNCTION(themeSave, "_ZN10CDataGroup10SaveToFileERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(themeGuid, "_ZN9UTILITIES16createUniqueGuidEv")

namespace {
struct Case { unsigned seed; bool nativeData,negative; };
const Case* current; autotest::Capture* capture; CUnitThemes* catalog;
CFileSystem* filesystem; TSafePointer<CUnitTheme>* oldWitness;
std::vector<TSafePointer<CDataGroup>*> loaded;
std::string temporary; std::wstring directory;
unsigned listed,loads,saves,guids; bool armed;
void number(long long value){capture->add(&value,sizeof value);}
void valid(bool yes){if(!yes)std::abort();}
std::wstring path(unsigned index){char name[32];std::sprintf(name,"theme-%u.dat",index);return directory+std::wstring(name,name+std::strlen(name));}
std::string narrow(const std::wstring& text){return std::string(text.begin(),text.end());}

void fill(CDataGroup& group,unsigned index,bool explicitGuid)
{
    unsigned mode=(index+current->seed/6)%6;
    if(mode){const wchar_t* names[]={L"",L"",L"lowerCase",L"\u0416\u4e2d-theme",L"duplicate",L"Mixed"};group.SetDataValue(L"NAME",names[mode],false);}
    if(explicitGuid||index%3)group.SetDataValue(L"GUID",static_cast<long long>(index%2?0x1234567800000000LL+index:0));
    const unsigned counts[]={0,1,2,18};
    for(unsigned i=0;i<counts[(current->seed+index)%4];++i){
        CDataGroup* child=group.AddDataGroup(i%3==0?L"NOT_PARTICLE":L"PARTICLE");
        if(i%2)child->SetDataValue(L"FILE",i%3?L"particles/test.layout":L"\u0416\u4e2d.layout",false);
        if((i+current->seed)%4)child->SetDataValue(L"UNITTYPE",i%2?L"GOLD":L"UNKNOWN-THEME-TYPE",false);
        if(i%2)child->SetDataValue(L"COUNT",int(i)-5);
        if((i+current->seed)%5)child->SetDataValue(L"ATTACHES",bool(i&1));
        if(i%4)child->SetDataValue(L"FOLLOWS",bool(i&2));
        if(i%2)child->SetDataValue(L"BONE",L"Bone-\u0416",false);
    }
}
unsigned files(CFileSystem* owner,const std::wstring& requested,TArrayList<std::wstring>& result,std::wstring pattern,bool recursive,bool strip,bool modsOnly,bool skipMods)
{
    if(!armed)return 0;
    valid(owner==filesystem&&requested==directory&&pattern==L"*.dat"&&!recursive&&strip&&!modsOnly&&!skipMods);
    number(1);number(result.size());number(result.m_nGrowBy);
    for(unsigned i=0;i<3;++i){number(oldWitness[i].getObject()==NULL);valid(!oldWitness[i].getObject());}
    for(unsigned i=0;i<listed;++i)result.add(path(i));
    return listed+77;
}
void load(CDataGroup* group,const std::wstring& file,CTimerStatics* timers)
{
    valid(armed&&loads<listed&&file==path(loads)&&!timers);
    number(2);number(loads);capture->addText(group->GetGroupName());number(group->GetNumberOfDataValues());number(group->GetNumberOfDataGroups());number(group->m_DataValues.m_nGrowBy);number(group->m_DataGroups.m_nGrowBy);
    TSafePointer<CDataGroup>* witness=new TSafePointer<CDataGroup>;witness->setObject(group);loaded.push_back(witness);
    fill(*group,loads++,false);
}
long long guid(){number(3);return 0x3123456700000000LL+current->seed*31+guids++;}
int save(CDataGroup* group,const std::wstring& file)
{
    valid(armed&&loads&&file==path(loads-1));number(4);number(loads-1);number(group->GetDataValue(L"GUID",static_cast<long long>(-1)));capture->addText(group->GetDataValue(L"NAME",L""));++saves;return current->seed%2;
}
void side(void* raw,autotest::Capture& out,bool ours)
{
    current=static_cast<Case*>(raw);capture=&out;armed=false;loads=saves=guids=0;loaded.clear();
    const unsigned counts[]={0,1,2,3,12,26};listed=counts[current->seed%6];
    std::string base=temporary+"/";directory=std::wstring(base.begin(),base.end());
    filesystem=CFileSystem::getSingleton();valid(filesystem!=NULL);
    if(current->nativeData)for(unsigned i=0;i<listed;++i){CDataGroup group(L"UNITTHEME",NULL,20,10,NULL);fill(group,i,true);valid(group.SaveToFile(path(i))!=0);}
    CUnitThemes* previous=themeSingleton;int before=g_iTotalCountOfObjects;
    catalog=static_cast<CUnitThemes*>(Ogre::NedAllocImpl::allocBytes(sizeof(CUnitThemes),0,0,0));
    // Suppress only the constructor's unrelated directory enumeration.
    detour::Set listing;TL_REDIRECT(listing,themeFiles,&files);valid(!listing.failed());themeCtor(catalog,directory.c_str());
    TSafePointer<CUnitTheme> previousThemes[3];oldWitness=previousThemes;
    for(unsigned i=0;i<3;++i){CUnitTheme* theme=new CUnitTheme;theme->m_sName=L"OLD";theme->m_iGuid=i;CUnitThemeParticle* particle=new CUnitThemeParticle;particle->m_iCount=7;theme->m_particles.add(particle);catalog->getThemes().add(theme);previousThemes[i].setObject(theme);}
    armed=true;detour::Set collaborators;
    if(!current->nativeData){TL_REDIRECT(collaborators,themeLoad,&load);TL_REDIRECT(collaborators,themeSave,&save);TL_REDIRECT(collaborators,themeGuid,&guid);}
    valid(!collaborators.failed());typedef void(*Function)(CUnitThemes*);Function fn=ours?themeReloadNew:themeReloadOld;
    if(autotest::beginInvocation(out,fn)){fn(catalog);out.callCompleted=1;}
    if(ours&&current->negative)catalog->m_Themes.setGrowBy(0x1234);
    number(catalog->m_Themes.size());number(catalog->m_Themes.m_nCapacity);number(catalog->m_Themes.m_nGrowBy);number(loads);number(saves);number(guids);
    std::vector<TSafePointer<CRunicCore>*> finalWitness;
    for(unsigned i=0;i<catalog->m_Themes.size();++i){CUnitTheme* theme=catalog->m_Themes[i];capture->addText(theme->getName());number(theme->getGuid());number(theme->m_particles.size());number(theme->m_particles.m_nGrowBy);TSafePointer<CRunicCore>* weak=new TSafePointer<CRunicCore>;weak->setObject(theme);finalWitness.push_back(weak);
        for(unsigned j=0;j<theme->m_particles.size();++j){CUnitThemeParticle* p=theme->m_particles[j];capture->addText(p->m_wstrFile);number(p->m_iCount);number(p->m_iUnitTypeID);number(p->m_bAttaches);number(p->m_bFollows);capture->addText(p->m_wstrBone);weak=new TSafePointer<CRunicCore>;weak->setObject(p);finalWitness.push_back(weak);}}
    for(unsigned i=0;i<loaded.size();++i){number(loaded[i]->getObject()==NULL);valid(!loaded[i]->getObject());delete loaded[i];}loaded.clear();
    collaborators.restore();armed=false;themeDtor(catalog);Ogre::NedAllocImpl::deallocBytes(catalog);themeSingleton=previous;listing.restore();
    for(unsigned i=0;i<finalWitness.size();++i){number(finalWitness[i]->getObject()==NULL);valid(!finalWitness[i]->getObject());delete finalWitness[i];}
    number(g_iTotalCountOfObjects-before);
    if(current->nativeData)for(unsigned i=0;i<listed;++i)unlink(narrow(path(i)).c_str());
}
void original(void* p,autotest::Capture& out){side(p,out,false);}void recovered(void* p,autotest::Capture& out){side(p,out,true);}
bool useNative;
int worker(const tlhybrid_host* host)
{
    nativegame::Services services;valid(services.ready());char path[]="/tmp/otl-theme-proof-XXXXXX";valid(mkdtemp(path)!=NULL);temporary=path;
    const char* label=useNative?"unit_themes_native_data":"unit_themes_observed";unsigned count=useNative?36:144;
    autotest::Coverage coverage(label,reinterpret_cast<uintptr_t>(themeReloadOld));
    for(unsigned seed=0;seed<count;++seed){Case c={seed,useNative,false};autotest::Outcome a,b;autotest::runChild(original,&c,a,10000,20000);autotest::runChild(recovered,&c,b,10000,20000);
        if(coverage.observe(host,a,b)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    themes seed%u native%u valid%u/%u status%d/%d issue%u/%u bytes%lu/%lu first%lu\n",seed,unsigned(useNative),a.reportValid,b.reportValid,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);coverage.report(host);return 1;}}
    coverage.report(host);Case control={5,useNative,true};autotest::Outcome a,b;autotest::runChild(original,&control,a,10000,20000);autotest::runChild(recovered,&control,b,10000,20000);
    bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);bool complete=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);host->log("    %s negative detected%u completed%u\n",label,unsigned(detected),unsigned(complete));rmdir(temporary.c_str());return coverage.completed!=count||!detected||!complete;
}
}
TL_TEST(unit_themes_observed){useNative=false;return systems_fixture::isolated(worker,host,240);}
TL_TEST(unit_themes_native_data){useNative=true;return systems_fixture::isolated(worker,host,240);}
