#include <Ogre.h>
#include <map>
#include <string>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/NativeGameServices.h"
#include "RefManagerInterpreterFunc.h"
#include "FileSystem.h"
#include "FileUtilities.h"
#include "StringUtilities.h"

TL_ORIGINAL(unsigned, modelIDOld, (CEditorScene*,const std::wstring&,void*), "_ZN26CRefManagerInterpreterFunc26GetModelResourceIDByStringEP12CEditorSceneRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned modelIDNew(CEditorScene*,const std::wstring&,void*) __asm__("_ZN26CRefManagerInterpreterFunc26GetModelResourceIDByStringEP12CEditorSceneRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(void, modelInfoOld, (CFileSystem*,const std::wstring&,CFileInfo&,bool,bool,bool), "_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_ORIGINAL(void, modelSceneCtor, (CEditorScene*,const wchar_t*), "_ZN12CEditorSceneC1EPKw")
TL_ORIGINAL(void, modelSceneDtor, (CEditorScene*), "_ZN12CEditorSceneD1Ev")
TL_ORIGINAL(void, modelFsCtor, (CFileSystem*,bool), "_ZN11CFileSystemC1Eb")
TL_ORIGINAL(void, modelFsDtor, (CFileSystem*), "_ZN11CFileSystemD1Ev")
TL_FUNCTION(modelInfoEntry,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
namespace {
typedef std::map<std::wstring,unsigned> Names;
typedef std::map<unsigned,std::wstring> Indices;
struct Case {unsigned seed,observed;bool negative;};
const Case* current;
autotest::Capture* output;
Names* names=reinterpret_cast<Names*>(0x146b940);
Indices* indices=reinterpret_cast<Indices*>(0x146b980);
CFileSystem* fs;
unsigned infoCalls;
detour::Set infoHook;
std::string directory;
void number(long long value){output->add(&value,sizeof value);}
void invalid(){output->issue=autotest::Capture::InvalidReport;}
void info(CFileSystem* self,const std::wstring& path,CFileInfo& file,bool compiled,bool binary,bool modsOnly)
{
    number(1);number(++infoCalls);number(self==fs);output->addText(path);
    number(compiled);number(binary);number(modsOnly);
    if(self!=fs || compiled || !binary || modsOnly)invalid();
    if(current->observed) {
        file.m_bExists=(current->seed/6%2)!=0;
        switch(current->seed/12%5) {
        case 0:(*names)[path]=0xf1234567u;break;
        case 1:names->erase(path);break;
        case 2:(*names)[L"inserted by callback"]=77;break;
        case 3:names->clear();break;
        case 4:const_cast<std::wstring&>(path)=L"mutated/path.mesh";break;
        }
    } else {
        infoHook.restore();modelInfoOld(self,path,file,compiled,binary,modsOnly);
        TL_REDIRECT(infoHook,modelInfoEntry,&info);if(infoHook.failed())invalid();
    }
    number(file.m_bExists);number(file.m_eFormat);number(file.m_eLocation);
    output->addText(file.m_sPath);output->addText(file.m_sResourceGroup);
}
void snapshot()
{
    number(names->size());
    for(Names::const_iterator i=names->begin();i!=names->end();++i){output->addText(i->first);number(i->second);}
    number(indices->size());
    for(Indices::const_iterator i=indices->begin();i!=indices->end();++i){number(i->first);output->addText(i->second);}
}
void touch(const std::string& path)
{
    FILE* file=std::fopen(path.c_str(),"wb");if(!file)std::abort();std::fputs("synthetic model identity",file);std::fclose(file);
}
void side(void* raw,autotest::Capture& out,bool ours)
{
    current=static_cast<Case*>(raw);output=&out;infoCalls=0;
    unsigned seed=current->seed;
    Names savedNames;Indices savedIndices;savedNames.swap(*names);savedIndices.swap(*indices);
    const unsigned sizes[]={0,1,2,7,30,99};
    for(unsigned i=0;i<sizes[seed/6%6];++i) {
        std::wstring key=L"prior/"+std::wstring(i+1,wchar_t(L'A'+i%20));
        (*names)[key]=i*17u;(*indices)[i*17u]=key;
    }
    std::wstring path=seed%3==0?L"./nested//model.mesh":seed%3==1?L".\\nested\\model.mesh":L"./nested/\u0416\u03a9.mesh";
    std::wstring clean=FILESYSTEM::CleanPath(path);
    const unsigned condition=seed%6;
    if(condition==3)(*names)[clean]=0x87654321u;
    if(condition==4)(*indices)[names->size()]=L"overwritten by new registration";
    if(condition==1)path=L"";
    std::string fileName=condition==5?"./nested/\xd0\x96\xce\xa9.mesh":"./nested/model.mesh";
    if(seed%3==2)fileName="./nested/\xd0\x96\xce\xa9.mesh";
    unlink("./nested/model.mesh");unlink("./nested/\xd0\x96\xce\xa9.mesh");
    if(condition!=2)touch(fileName);
    int before=g_iTotalCountOfObjects;
    CEditorScene* scene=static_cast<CEditorScene*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEditorScene),0,0,0));
    modelSceneCtor(scene,L"Model references");
    CFileSystem* previous=g_pFileSystem;
    fs=static_cast<CFileSystem*>(Ogre::NedAllocImpl::allocBytes(sizeof(CFileSystem),0,0,0));
    g_pFileSystem=fs;modelFsCtor(fs,false);
    CEditorScene* argument=condition==0?NULL:scene;
    unsigned first=~0u,second=~0u;
    TL_REDIRECT(infoHook,modelInfoEntry,&info);if(infoHook.failed())invalid();
    if(autotest::beginInvocation(out,ours?modelIDNew:modelIDOld)) {
        first=(ours?modelIDNew:modelIDOld)(argument,path,seed%2?static_cast<void*>(scene):NULL);
        if(seed/36%2)unlink(fileName.c_str());
        second=(ours?modelIDNew:modelIDOld)(argument,path,NULL);
        out.callCompleted=1;
    }
    infoHook.restore();
    if(ours&&current->negative)(*indices)[0xfedcba98u]=L"negative state mutation";
    number(first);number(second);number(infoCalls);snapshot();output->addText(path);
    if((condition==0 || condition==1) && infoCalls)invalid();
    if(condition!=0 && condition!=1 && infoCalls!=2)invalid();
    modelFsDtor(fs);Ogre::NedAllocImpl::deallocBytes(fs);g_pFileSystem=previous;
    modelSceneDtor(scene);Ogre::NedAllocImpl::deallocBytes(scene);
    number(g_iTotalCountOfObjects-before);
    names->clear();indices->clear();savedNames.swap(*names);savedIndices.swap(*indices);
    unlink("./nested/model.mesh");unlink("./nested/\xd0\x96\xce\xa9.mesh");
}
void original(void* p,autotest::Capture& out){side(p,out,false);}
void candidate(void* p,autotest::Capture& out){side(p,out,true);}
int worker(const tlhybrid_host* host,unsigned observed)
{
    initEmptyGlobals();
    void* empty=NULL;std::memcpy(&empty,reinterpret_cast<void*>(0x146b760),8);
    if(!empty)new(reinterpret_cast<void*>(0x146b760))std::string;
    std::memcpy(&empty,reinterpret_cast<void*>(0x146b768),8);
    if(!empty)new(reinterpret_cast<void*>(0x146b768))std::wstring;
    std::memcpy(&empty,reinterpret_cast<char*>(names)+24,8);if(!empty)new(names)Names;
    std::memcpy(&empty,reinterpret_cast<char*>(indices)+24,8);if(!empty)new(indices)Indices;
    nativegame::Services services;if(!services.ready())return 1;
    char temp[]="/tmp/otl-model-ref-XXXXXX";char* made=mkdtemp(temp);if(!made)return 1;
    directory=made;char previous[4096];if(!getcwd(previous,sizeof previous)||chdir(directory.c_str()))return 1;
    if(mkdir("nested",0700))return 1;
    const char* label=observed?"model_registration_observed":"model_registration_native_files";
    autotest::Coverage coverage(label,reinterpret_cast<uintptr_t>(&modelIDOld));
    unsigned total=observed?432:216;int failed=0;
    for(unsigned seed=0;seed<total;++seed) {
        Case c={seed,observed,false};autotest::Outcome a,b;
        autotest::runChild(&original,&c,a,6000,15000);autotest::runChild(&candidate,&c,b,6000,15000);
        if(coverage.observe(host,a,b)) {
            host->log("    model registration observed%u seed%u valid%u/%u issue%u/%u exit%d/%d bytes%lu/%lu\n",observed,seed,a.reportValid,b.reportValid,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
            failed=1;break;
        }
    }
    coverage.report(host);
    if(!failed) {
        Case c={23,observed,true};autotest::Outcome a,b;
        autotest::runChild(&original,&c,a,6000,15000);autotest::runChild(&candidate,&c,b,6000,15000);
        autotest::Coverage negative(label,reinterpret_cast<uintptr_t>(&modelIDOld));
        int delta=negative.observe(host,a,b);
        host->log("    model negative observed%u detected%u completed%u incomplete%u\n",observed,unsigned(delta==1),negative.completed,negative.missing);
        if(delta!=1 || negative.completed!=1 || negative.missing)failed=1;
    }
    unlink("./nested/model.mesh");unlink("./nested/\xd0\x96\xce\xa9.mesh");rmdir("nested");
    if(chdir(previous))return 1;rmdir(directory.c_str());return failed;
}
int nativeWorker(const tlhybrid_host* h){return worker(h,0);}
int observedWorker(const tlhybrid_host* h){return worker(h,1);}
}
TL_TEST(model_registration_native_files){return systems_fixture::isolated(nativeWorker,host,180);}
TL_TEST(model_registration_observed){return systems_fixture::isolated(observedWorker,host,180);}
