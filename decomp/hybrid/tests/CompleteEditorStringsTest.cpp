#include <Ogre.h>
#include <OgreUTFString.h>
#include <ctime>
#include <fstream>
#include <iterator>
#include <sys/stat.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "Editor.h"
#undef protected
#undef private
#include "LinuxUtils.h"
#include "iEditorResourceManager.h"
#include "RunicCore.h"
#include "CharacterLibraryBoundary.h"
TL_ORIGINAL(void,editorStringCtor,(CEditor*),"_ZN7CEditorC1Ev")
TL_ORIGINAL(void,editorStringDtor,(CEditor*),"_ZN7CEditorD1Ev")
TL_ORIGINAL(void,editorStringActive,(CEditor*,const std::wstring&),"_ZN7CEditor15setActiveQuestsERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,editorStringCompleted,(CEditor*,const std::wstring&),"_ZN7CEditor18setCompletedQuestsERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,editorStringCopy,(const std::wstring&,const std::wstring&),"_Z10copyFileToRKSbIwSt11char_traitsIwESaIwEES4_")
extern "C" void editorStringNewCtor(CEditor*) __asm__("_ZN7CEditorC1Ev");
extern "C" void editorStringNewDtor(CEditor*) __asm__("_ZN7CEditorD1Ev");
extern "C" void editorStringNewActive(CEditor*,const std::wstring&) __asm__("_ZN7CEditor15setActiveQuestsERKSbIwSt11char_traitsIwESaIwEE");
extern "C" void editorStringNewCompleted(CEditor*,const std::wstring&) __asm__("_ZN7CEditor18setCompletedQuestsERKSbIwSt11char_traitsIwESaIwEE");
extern "C" void editorStringNewCopy(const std::wstring&,const std::wstring&) __asm__("_Z10copyFileToRKSbIwSt11char_traitsIwESaIwEES4_");
TL_FUNCTION(editorStringCopyBoundary,"_Z10copyFileToRKSbIwSt11char_traitsIwESaIwEES4_")
TL_FUNCTION(editorStringDirectory,"_ZN10FILESYSTEM22CreateAppDataDirectoryERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct Manager: iEditorResourceManager { void editorUpdateSceneOnce(int){} void*getWindowHandle(){return NULL;} CSettings*getSettings(){return NULL;} Ogre::SceneManager*getSceneManager(){return NULL;} CSoundManager*getSoundManager(){return NULL;} Ogre::RenderWindow*getRenderWindow(){return NULL;} Ogre::Camera*getGameCamera(){return NULL;} void updateAspectRatio(float,float){} CGameClient*getGameClient(){return NULL;} };
struct Case{unsigned operation,profile,negative;};
autotest::Capture* cap;const Case*current;std::string base;
void word(unsigned v){cap->add(&v,4);}void real(float v){cap->add(&v,4);}
void editorStringGlobals(){const uintptr_t words[]={0x145c6f0};for(unsigned i=0;i<1;++i){void*p;std::memcpy(&p,reinterpret_cast<void*>(words[i]),sizeof p);if(!p)new(reinterpret_cast<void*>(words[i]))std::wstring;}}
bool directory(const std::wstring&path){word(1);cap->addText(path);return !(current->profile&1);}
void copyBoundary(const std::wstring&from,const std::wstring&to){word(2);cap->addText(from);cap->addText(to);}
void reset(Ogre::Timer*){word(3);}time_t clock(time_t*p){time_t t=1700000000+current->profile*17;if(p)*p=t;word(4);word(t);return t;}void seed(unsigned value){word(5);word(value);}
std::wstring text(unsigned p){const wchar_t* fixed[]={L"",L"single",L",",L",,",L"one,two",L",one,",L"one,,two",L"one,one",L"  spaced , second ",L"задача,任務,\U0001f600",L"\t,\n,\r",L"a;b:c"};if(p<12)return fixed[p];std::wstring s;unsigned counts[]={9,10,11,19,20,21,63,64};unsigned count=counts[(p-12)%8];for(unsigned i=0;i<count;++i){if(i)s+=L",";s+=static_cast<wchar_t>(L'A'+(i+p)%26);}if(p>=20)s+=L",,,";if(p>=28)s.insert(s.begin(),L',');return s;}
void state(CEditor*p){
 word(p->m_bRenderWindowHasFocus);word(p->m_bDisabled);word(p->m_bUnknown4A);word(p->m_bUnknown4B);word(p->m_pSettings==NULL);word(p->m_pEditorResourceManager==NULL);real(p->m_fUnknown60);word(p->m_iFlags);word(p->m_iUnknown68);word(p->m_pCameraController==NULL);for(unsigned i=0;i<3;++i)real(p->m_iUnknown78[i]);word(p->m_pUnknown88==NULL);word(p->m_pUnknown90==NULL);for(unsigned i=0;i<6;++i)real(p->m_iUnknown98[i]);word(p->m_pUnknownB0==NULL);word(p->m_iMouseWheelDelta);word(p->m_EditorScenes.size());word(p->m_EditorSceneIDs.size());word(p->m_pObjectManager==NULL);word(p->m_pUnknown128==NULL);word(p->m_pUnknown130==NULL);word(p->m_pUnknown138==NULL);word(p->m_Undos.size());word(p->m_Redos.size());word(p->m_iMaxUndos);word(p->m_bUnknown164);word(p->m_pUnknown168==NULL);word(p->m_iCharacterLevel);word(p->m_iLevelDepth);word(p->m_bLevelPopulate);cap->addText(p->m_sUnknown180);word(p->m_bLevelPopulateChampions);word(p->m_bLevelCreatePet);word(p->m_bRunGodded);word(p->m_bAiFreeze);cap->addText(p->m_sUnknown190);cap->addText(p->m_sUnknown198);cap->addText(p->m_sUnknown1A0);cap->addText(p->m_sUnknown1A8);word(p->m_bUseTempStartPos);cap->add(&p->m_vTempStartPos,12);real(p->m_fParticleMovementA);real(p->m_fParticleMovementB);
 word(p->m_ActiveQuests.size());for(unsigned i=0;i<p->m_ActiveQuests.size();++i)cap->addText(p->m_ActiveQuests[i]);word(p->m_CompletedQuests.size());for(unsigned i=0;i<p->m_CompletedQuests.size();++i)cap->addText(p->m_CompletedQuests[i]);
}
void put(const std::string&p,const std::string&data){FILE*f=fopen(p.c_str(),"wb");if(!f)std::abort();if(fwrite(data.data(),1,data.size(),f)!=data.size()||fclose(f))std::abort();}
void file(const std::string&p){FILE*f=fopen(p.c_str(),"rb");word(f!=NULL);if(!f)return;std::string bytes;char buf[257];size_t n;while((n=fread(buf,1,sizeof buf,f)))bytes.append(buf,n);fclose(f);cap->addText(bytes);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;current=&c;editorStringGlobals();LinuxUtils::gameHomePath=std::wstring(base.begin(),base.end());
 if(c.operation==4){
  const char*names[]={"plain","space name","данные","\xf0\x9f\x98\x80"};std::string source=base+names[c.profile%4]+"-source",destination=base+names[(c.profile/4)%4]+"-destination";std::string data;unsigned n=c.profile<8?c.profile:1u<<((c.profile-8)%12);for(unsigned i=0;i<n;++i)data+=char((i*37+c.profile)%256);unlink(source.c_str());unlink(destination.c_str());if(c.profile%8!=6)put(source,data);if(c.profile%8==5)put(destination,"existing content\n");if(c.profile%8==7)destination=source;std::wstring from=Ogre::UTFString(source).asWStr(),to=Ogre::UTFString(destination).asWStr();typedef void(*F)(const std::wstring&,const std::wstring&);F f=ours?editorStringNewCopy:editorStringCopy;if(autotest::beginInvocation(out,f)){f(from,to);out.callCompleted=1;if(ours&&c.negative)put(destination,"mutation");}file(source);file(destination);unlink(source.c_str());unlink(destination.c_str());return;
 }
 CEditor*p=static_cast<CEditor*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEditor),0,0,0));std::memset(p,(c.profile*7+0x35)&255,sizeof(CEditor));
 detour::Set setup;TL_REDIRECT(setup,editorStringDirectory,directory);TL_REDIRECT(setup,editorStringCopyBoundary,copyBoundary);setup.redirect(reinterpret_cast<char*>(&std::time),reinterpret_cast<char*>(&std::time),clock);setup.redirect(reinterpret_cast<char*>(&std::srand),reinterpret_cast<char*>(&std::srand),seed);CharacterLibraryBoundary timer(characterLibraryEntry("libOgreMain-1.6.5.so","_ZN4Ogre5Timer5resetEv"),reset);if(setup.failed()||timer.failed())std::abort();
 if(c.operation==0){typedef void(*F)(CEditor*);F f=ours?editorStringNewCtor:editorStringCtor;int before=g_iTotalCountOfObjects;if(autotest::beginInvocation(out,f)){f(p);out.callCompleted=1;if(ours&&c.negative)p->m_iFlags^=1;}word(g_iTotalCountOfObjects-before);out.add(p->m_keyPropertyIndices,sizeof p->m_keyPropertyIndices);state(p);editorStringDtor(p);Ogre::NedAllocImpl::deallocBytes(p);return;}
 editorStringCtor(p);gEditor=p;out.length=0;for(unsigned i=0;i<c.profile%13;++i){p->m_ActiveQuests.add(L"old-active");p->m_CompletedQuests.add(L"old-completed");}p->m_sUnknown180=text(c.profile);p->m_sUnknown190=L"monster";p->m_sUnknown198=L"player";p->m_sUnknown1A0=L"command";p->m_sUnknown1A8=L"name";
 if(c.operation==1){Manager manager;p->m_pEditorResourceManager=&manager;p->m_iFlags=c.profile*67;typedef void(*F)(CEditor*);F f=ours?editorStringNewDtor:editorStringDtor;int before=g_iTotalCountOfObjects;if(autotest::beginInvocation(out,f)){f(p);out.callCompleted=1;}word(before-g_iTotalCountOfObjects);void*link;std::memcpy(&link,reinterpret_cast<char*>(p)+0x58,sizeof link);word(link==NULL);int flags;std::memcpy(&flags,reinterpret_cast<char*>(p)+0x64,4);word(flags);if(ours&&c.negative)word(9);Ogre::NedAllocImpl::deallocBytes(p);return;}
 typedef void(*F)(CEditor*,const std::wstring&);F f=c.operation==2?(ours?editorStringNewActive:editorStringActive):(ours?editorStringNewCompleted:editorStringCompleted);std::wstring value=text(c.profile);if(autotest::beginInvocation(out,f)){f(p,value);out.callCompleted=1;if(ours&&c.negative)p->m_iFlags^=1;}state(p);editorStringDtor(p);Ogre::NedAllocImpl::deallocBytes(p);
}
void before(void*p,autotest::Capture&c){side(p,c,false);}void after(void*p,autotest::Capture&c){side(p,c,true);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uintptr_t address){char path[]="/tmp/otl-editor-strings-XXXXXX";if(!mkdtemp(path))return 1;base=std::string(path)+"/";int failures=0;autotest::Coverage cov(name,address);for(unsigned i=0;i<32;++i){Case c={op,i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int bad=cov.observe(host,a,b);TL_CHECK(failures,!bad);if(bad){host->log("    Editor string op%u profile%u status%d/%d issue%u/%u bytes%lu/%lu\n",op,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first difference%u values%u/%u\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}cov.report(host);return failures;}}cov.report(host);Case c={op,17,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool detected=a.capture.length!=b.capture.length||memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,detected&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    Editor strings negative op%u detected%u\n",op,unsigned(detected));rmdir(path);return failures;}
int ctorWorker(const tlhybrid_host*h){return run(h,0,"editor_complete_ctor",0x71ae10);}int dtorWorker(const tlhybrid_host*h){return run(h,1,"editor_complete_dtor",0x717660);}int activeWorker(const tlhybrid_host*h){return run(h,2,"editor_complete_active",0x71d430);}int completedWorker(const tlhybrid_host*h){return run(h,3,"editor_complete_completed",0x718560);}int copyWorker(const tlhybrid_host*h){return run(h,4,"editor_complete_copy",0x7192b0);}
}
TL_TEST(editor_complete_ctor){return systems_fixture::isolated(ctorWorker,host);}
TL_TEST(editor_complete_dtor){return systems_fixture::isolated(dtorWorker,host);}
TL_TEST(editor_complete_active){return systems_fixture::isolated(activeWorker,host);}
TL_TEST(editor_complete_completed){return systems_fixture::isolated(completedWorker,host);}
TL_TEST(editor_complete_copy){return systems_fixture::isolated(copyWorker,host);}
