#include <cstring>
#include <cstdlib>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "ResourceSettings.h"
TL_ORIGINAL(void,original0,(void*),"_ZN17CModelViewerSceneC1Ev")
extern "C" void candidate0(void*) __asm__("_ZN17CModelViewerSceneC1Ev");
TL_ORIGINAL(void,original1,(void*),"_ZN17CModelViewerScene17createDescriptorsEv")
extern "C" void candidate1(void*) __asm__("_ZN17CModelViewerScene17createDescriptorsEv");
TL_ORIGINAL(void,original2,(void*),"_ZN17CResourceSettingsC1Ev")
extern "C" void candidate2(void*) __asm__("_ZN17CResourceSettingsC1Ev");
TL_ORIGINAL(std::wstring,original3,(std::wstring),"_ZN9UTILITIES17GetEnvironmentVarESbIwSt11char_traitsIwESaIwEE")
extern "C" std::wstring candidate3(std::wstring) __asm__("_ZN9UTILITIES17GetEnvironmentVarESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(target_sceneBase,"_ZN12CEditorSceneC1EPKw")
TL_FUNCTION(target_editorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(target_addDescriptor,"_ZN12CEditorScene13AddDescriptorEPKw")
TL_FUNCTION(target_settingsBase,"_ZN20CDynamicPropertyFileC1ESbIwSt11char_traitsIwESaIwEES3_S3_")
TL_FUNCTION(target_stringIndex,"_ZN20CDynamicPropertyFile22GetStringPropertyIndexERKSbIwSt11char_traitsIwESaIwEES3_b")
TL_FUNCTION(target_appPath,"_ZN10FILESYSTEM14GetAppDataPathEv")
TL_FUNCTION(target_home,"_ZN10LinuxUtils10GetHomeDirEv")
namespace {
unsigned* indices[]={&KRESOURCESETTING_S_MASTERRESOURCEFILE,&KRESOURCESETTING_S_PARTICLE_SYSTEMS,&KRESOURCESETTING_S_PARTICLE_MATERIALS,&KRESOURCESETTING_S_PARTICLE_IMAGES,&KRESOURCESETTING_S_ROOM_DATA_FOLDER,&KRESOURCESETTING_S_SOUND_DATA_FOLDER,&KRESOURCESETTING_S_SKILL_FOLDER,&KRESOURCESETTING_S_MISSILE_FOLDER,&KRESOURCESETTING_S_AFFIXES_FOLDER,&KRESOURCESETTING_S_GRAPH_MANAGER,&KRESOURCESETTING_S_TRANSLATE_FILE};

struct Case{unsigned op,seed;};Case* input;autotest::Capture* output;void* active;unsigned calls;
void num(unsigned n){output->add(&n,4);}void ptr(void*p){output->add(&p,8);}void indicesState(){for(unsigned i=0;i<11;++i)num(*indices[i]);}
void sceneBase(void*p,const wchar_t*name){num(1);ptr(p);output->addText(std::wstring(name));output->add(p,0x190);std::memset(p,(input->seed*33+7)&255,0x190);}
bool editorRunning(void*p){num(2);ptr(p);return input->seed&1;}
void addDescriptor(void*p,const wchar_t*name){num(3);ptr(p);output->addText(std::wstring(name));if(input->seed%3==0)std::memset(static_cast<char*>(p)+0x18,0x7b,8);}
void settingsBase(void*p,std::wstring dir,std::wstring file,std::wstring section){num(4);ptr(p);output->addText(dir);output->addText(file);output->addText(section);output->add(p,0x140);std::memset(p,(input->seed*33+7)&255,0x140);}
unsigned stringIndex(void*p,const std::wstring&name,std::wstring value,bool flag){num(5);ptr(p);output->addText(name);output->addText(value);num(flag);indicesState();output->add(p,0x140);++calls;return input->seed*0x11234567u+calls*31;}
std::wstring appPath(){num(6);return input->seed%3==0?L"":input->seed%3==1?L"/tmp/editor settings":L"/tmp/\u0418\u0433\u0440\u0430/";}
std::wstring home(){num(7);return input->seed%3==0?L"":input->seed%3==1?L"/tmp/game-home":L"/tmp/\u0418\u0433\u0440\u0430";}
void side(Case&c,bool ours,autotest::Capture&out){input=&c;output=&out;calls=0;unsigned long long bytes[64],resource[32]={0};std::memset(bytes,(c.seed*13+11)&255,sizeof(bytes));active=bytes;void*p=resource;std::memcpy(reinterpret_cast<char*>(bytes)+0x40,&p,8);for(unsigned i=0;i<11;++i)*indices[i]=0xabcdef00u+i;
 detour::Set patches;
 TL_REDIRECT(patches,target_sceneBase,&sceneBase);
 TL_REDIRECT(patches,target_editorRunning,&editorRunning);
 TL_REDIRECT(patches,target_addDescriptor,&addDescriptor);
 TL_REDIRECT(patches,target_settingsBase,&settingsBase);
 TL_REDIRECT(patches,target_stringIndex,&stringIndex);
 TL_REDIRECT(patches,target_appPath,&appPath);

 TL_REDIRECT(patches,target_home,&home);
 if(patches.failed())_exit(41);
 switch(c.op){case 0:autotest::invoke(out,ours?candidate0:original0,active);break;case 1:autotest::invoke(out,ours?candidate1:original1,active);break;case 2:autotest::invoke(out,ours?candidate2:original2,active);break;
 case 3:{const wchar_t*names[]={L"APPDATA",L"appdata",L"APPDATA/",L"",L"HOME",L"XAPPDATA",L"APPDATA"};std::wstring name=names[c.seed%7];
  std::wstring(*fn)(std::wstring)=ours?candidate3:original3;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(name);out.callCompleted=1;out.addText(result);break;}
 }
 num(calls);indicesState();out.add(bytes,sizeof(bytes));out.add(resource,sizeof(resource));patches.restore();
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
int run(const tlhybrid_host*host,unsigned first,unsigned last,const char*name){const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2,(uint64_t)(uintptr_t)original3};
 for(unsigned op=first;op<last;++op){autotest::Coverage coverage(name,addresses[op]);for(unsigned n=0;n<128;++n){Case c={op,n};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    small observed %u/%u status %d/%d bytes %lu/%lu\n",op,n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);}return 0;}
}
TL_TEST(small_model_viewer_observed){return run(host,0,2,"small_model_viewer_observed");}
TL_TEST(small_resource_settings_observed){return run(host,2,3,"small_resource_settings_observed");}
TL_TEST(small_environment_observed){return run(host,3,4,"small_environment_observed");}
