#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "FileSystem.h"
TL_ORIGINAL(void,mlOld,(CLevel*,const std::wstring&,CLayout*),"_ZN6CLevel24mergeLayoutsForRoomPieceERKSbIwSt11char_traitsIwESaIwEEP7CLayout")
extern "C" void mlNew(CLevel*,const std::wstring&,CLayout*) __asm__("_ZN6CLevel24mergeLayoutsForRoomPieceERKSbIwSt11char_traitsIwESaIwEEP7CLayout");
TL_ORIGINAL(void,mlLayoutCtor,(CLayout*,CResourceManager*,ELAYOUT_TYPES),"_ZN7CLayoutC1EP16CResourceManager13ELAYOUT_TYPES")
TL_ORIGINAL(void,mlLayoutDtor,(CLayout*),"_ZN7CLayoutD1Ev")
TL_FUNCTION(mlInit,"_ZN12CEditorScene9InitSceneEP16CResourceManagerj")
TL_FUNCTION(mlEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(mlFiles,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(mlCreate,"_ZN12CEditorScene24CreateObjectByDescriptorERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(mlLoad,"_ZN7CLayout14loadLayoutFileERKSbIwSt11char_traitsIwESaIwEEbP13CTimerStaticsbbj")
namespace {
autotest::Capture*output;unsigned seed,calls;CLevel*level;CResourceManager*resources;CLayout*layouts[3];TArrayList<std::wstring>*fileList;
void number(unsigned n){output->add(&n,4);}void scalar(float v){output->add(&v,4);}void text(const std::wstring&s){number(s.size());if(s.size())output->add(s.data(),s.size()*sizeof(wchar_t));}unsigned id(CLayout*p){for(unsigned i=0;i<3;++i)if(p==layouts[i])return i;return 99;}
void init(CEditorScene*p,CResourceManager*r,unsigned flags){if(r||flags)std::abort();}
bool editor(CResourceManager*p){number(1);number(p==resources);return seed%3==0;}
const wchar_t*names[]={L"a.layout",L"folder/b.layout",L"",L"\x041b\x0435\x0441.layout",L"a.layout"};
unsigned files(CFileSystem*p,const std::wstring&directory,TArrayList<std::wstring>&out,std::wstring pattern,bool a,bool b,bool c,bool d){number(2);number(p==g_pFileSystem);text(directory);text(pattern);number(a);number(b);number(c);number(d);number(out.m_nGrowBy);number(out.size());fileList=&out;for(unsigned i=0;i<seed/3%6;++i)out.add(names[i%5]);return out.size()+19;}
CEditorBaseObject*create(CEditorScene*p,const std::wstring&name,bool load){number(3);number(p==layouts[0]);text(name);number(load);unsigned index=1+(calls++%2);number(index);return layouts[index];}
void load(CLayout*p,const std::wstring&path,bool a,CTimerStatics*t,bool b,bool c,unsigned n){number(4);number(id(p));text(path);number(a);number(t==NULL);number(b);number(c);number(n);if((seed&32)&&calls==1)fileList->add(std::wstring(L"added-during-load.layout"));}
struct Layout:CLayout{Layout():CLayout(NULL,static_cast<ELAYOUT_TYPES>(0)){}virtual void setPosition(float x,float y,float z){number(5);number(id(this));scalar(x);scalar(y);scalar(z);m_vPosition=Ogre::Vector3(x,y,z);}virtual void setVisible(bool v){number(6);number(id(this));number(v);m_bVisible=v;}};
void initialized(uintptr_t a,bool wide){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(a),8);if(!p){if(wide)new(reinterpret_cast<void*>(a))std::wstring;else new(reinterpret_cast<void*>(a))std::string;}}
void execute(void*raw,autotest::Capture&out,bool ours){output=&out;seed=*static_cast<unsigned*>(raw);calls=0;fileList=NULL;initialized(0x14a4320,false);initialized(0x14a4328,true);initialized(0x1528e40,false);initialized(0x1528e48,true);
 finishlevel::Fixture f;level=&f.level;resources=&f.resources;
 // Exercise the native constructor's existing-singleton branch: all member
 // owners are constructed, while archive scanning is outside this fixture.
 CFileSystem*previous=g_pFileSystem;void*memory=Ogre::NedAllocImpl::allocBytes(sizeof(CFileSystem),0,0,0);g_pFileSystem=static_cast<CFileSystem*>(memory);CFileSystem*fs=new(memory)CFileSystem(false);
 {detour::Set setup;TL_REDIRECT(setup,mlInit,&init);if(setup.failed()){out.issue=autotest::Capture::InvalidReport;return;}for(unsigned i=0;i<3;++i)layouts[i]=new Layout;}
 detour::Set hooks;TL_REDIRECT(hooks,mlEditor,&editor);TL_REDIRECT(hooks,mlFiles,&files);TL_REDIRECT(hooks,mlCreate,&create);TL_REDIRECT(hooks,mlLoad,&load);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 const wchar_t*paths[]={L"room.layout",L"media/rooms/room.layout",L"media\\rooms\\room.layout",L"/tmp/\x041b\x0435\x0441/room.layout",L"/root.layout",L"dir.with.dot/a"};std::wstring path=paths[seed/7%6];typedef void(*Fn)(CLevel*,const std::wstring&,CLayout*);Fn fn=ours?mlNew:mlOld;if(!autotest::beginInvocation(out,fn))return;fn(level,path,seed%5?layouts[0]:NULL);out.callCompleted=1;number(calls);for(unsigned i=0;i<3;++i){number(layouts[i]->m_bVisible);out.add(&layouts[i]->m_vPosition,sizeof(Ogre::Vector3));}
 hooks.restore();for(unsigned i=0;i<3;++i)delete layouts[i];fs->~CFileSystem();Ogre::NedAllocImpl::deallocBytes(fs);g_pFileSystem=previous;
}
void original(void*p,autotest::Capture&o){execute(p,o,false);}void candidate(void*p,autotest::Capture&o){execute(p,o,true);}
int run(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;autotest::Coverage coverage("level_merge_layouts",(uintptr_t)&mlOld);for(unsigned i=0;i<336;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    merge layouts seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(level_merge_layouts){return systems_fixture::isolated(&run,host);}
