#include "AutoTest.h"
#include <string>
#include <vector>
#include <map>
#include <list>
#include <deque>
#define private public
#define protected public
#include <OgrePass.h>
#include <OgreGpuProgramUsage.h>
#include "GenericModel.h"
#include "ResourceManager.h"
#include "GameClient.h"
#undef protected
#undef private
#include <Ogre.h>
#include "FileSystem.h"
#include "SettingsVariables.h"
#include "tests/NativeGameServices.h"
#include "tests/NativeMenuClient.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,gtOldClear,(CGenericModel*),"_ZN13CGenericModel18clearProjectorPassEv")
TL_ORIGINAL(void,gtOldHigh,(CGenericModel*,const std::wstring&),"_ZN13CGenericModel19setHighlightTextureERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,gtOldBehind,(CGenericModel*,const std::wstring&),"_ZN13CGenericModel22setRenderBehindTextureERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,gtOldRim,(CGenericModel*,std::wstring),"_ZN13CGenericModel14setRimLightingESbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,gtCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,gtDtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
TL_ORIGINAL(void,gtResourceCtor,(CResourceManager*,Ogre::SceneManager*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,gtResourceDtor,(CResourceManager*),"_ZN16CResourceManagerD1Ev")
TL_FUNCTION(gtFiles,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
extern "C" void gtNewClear(CGenericModel*) __asm__("_ZN13CGenericModel18clearProjectorPassEv");
extern "C" void gtNewHigh(CGenericModel*,const std::wstring&) __asm__("_ZN13CGenericModel19setHighlightTextureERKSbIwSt11char_traitsIwESaIwEE");
extern "C" void gtNewBehind(CGenericModel*,const std::wstring&) __asm__("_ZN13CGenericModel22setRenderBehindTextureERKSbIwSt11char_traitsIwESaIwEE");
extern "C" void gtNewRim(CGenericModel*,std::wstring) __asm__("_ZN13CGenericModel14setRimLightingESbIwSt11char_traitsIwESaIwEE");
extern "C" char gtBest[] __asm__("_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE");
extern "C" char gtCompile[] __asm__("_ZN4Ogre8Material7compileEb");
extern "C" char gtConstant[] __asm__("_ZN4Ogre20GpuProgramParameters20setNamedAutoConstantERKSsNS0_16AutoConstantTypeEm");
namespace {
typedef char usageSize[sizeof(Ogre::GpuProgramUsage)==0x48?1:-1];typedef char paramsSize[sizeof(Ogre::GpuProgramParameters)==0x70?1:-1];typedef char usageOffset[offsetof(Ogre::Pass,mVertexProgramUsage)==0x100?1:-1];
nativegame::Services*services;CGameClient*client;autotest::Capture*output;unsigned seed;std::vector<Ogre::MaterialPtr>*known;std::vector<Ogre::GpuProgramParametersSharedPtr>*params;
struct Case{unsigned op,seed;};
void number(unsigned n){output->add(&n,4);}void text(const std::string&s){number(s.size());if(s.size())output->add(s.data(),s.size());}
unsigned materialId(Ogre::Material*p){for(unsigned i=0;i<known->size();++i)if((*known)[i].getPointer()==p)return i;std::abort();return 99;}
Ogre::Technique*best(Ogre::Material*p,unsigned short lod,const Ogre::Renderable*r){materialId(p);if(lod||r)std::abort();return p->getTechnique(0);}
void compile(Ogre::Material*p,bool automatic){number(10);number(materialId(p));number(automatic);}
void constant(Ogre::GpuProgramParameters*p,const std::string&name,Ogre::GpuProgramParameters::AutoConstantType type,size_t extra){unsigned id=99;for(unsigned i=0;i<params->size();++i)if((*params)[i].getPointer()==p)id=i;if(id==99)std::abort();number(11);number(id);text(name);number(type);number(extra);}
void files(CFileSystem*p,const std::wstring&path,CFileInfo&info,bool a,bool b,bool c){if(p!=g_pFileSystem)std::abort();number(12);number(a);number(b);number(c);number(path.size());if(path.size())output->add(path.data(),path.size()*sizeof(wchar_t));info.m_bExists=(seed%3)!=0;info.m_sResourceName="rim/texture-"+Ogre::StringConverter::toString(seed%7)+".png";}
void initialized(uintptr_t address,bool wide){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p){if(wide)new(reinterpret_cast<void*>(address))std::wstring;else new(reinterpret_cast<void*>(address))std::string;}}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;output=&out;services->settings->SetInt(KSETTINGS_SHADOWS_ENABLED,seed%2);services->settings->SetInt(KSETTINGS_RIMLIGHTS_ENABLED,seed/3%2);services->settings->SetInt(KSETTINGS_NETBOOK_MODE,seed/6%3);
 CResourceManager*resources=static_cast<CResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CResourceManager),0,0,0));gtResourceCtor(resources,services->scene);unsigned mode=seed/18%3;if(mode==2)resources->m_GameClients.add(client);client->m_pendingPassClear=false;
 CGenericModel*model=static_cast<CGenericModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0));gtCtor(model,NULL,NULL,OGRE_UTILITIES::PRIMITIVE_SPHERE);if(mode)model->setResourceManager(resources);model->m_flag238=(seed/54)%2;
 std::vector<Ogre::MaterialPtr>materials;known=&materials;std::vector<Ogre::GpuProgramParametersSharedPtr>parameters;params=&parameters;unsigned count=seed/2%5;
 for(unsigned i=0;i<count;++i){CRenderableStates state=CRenderableStates();state.spectral=(seed/27+i)%2;state.m_flag30=(seed/9+i)%2;state.m_flag31=(seed/5+i)%2;state.projectorTechnique=13+i;
  for(unsigned k=0;k<3;++k){std::string name="generic-texture-"+Ogre::StringConverter::toString(i*3+k);Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create(name,"General");materials.push_back(material);Ogre::Pass*pass=material->getTechnique(0)->getPass(0);unsigned units=(seed/7+i+k)%6;for(unsigned u=0;u<units;++u){Ogre::TextureUnitState*t=pass->createTextureUnitState();t->setName("unit-"+Ogre::StringConverter::toString(u));t->setTextureName("original-"+Ogre::StringConverter::toString(u)+".png");}
   if(c.op==3&&k==0&&(seed/11+i)%2){Ogre::GpuProgramParametersSharedPtr p(new Ogre::GpuProgramParameters);parameters.push_back(p);Ogre::GpuProgramUsage*usage=new Ogre::GpuProgramUsage(Ogre::GPT_VERTEX_PROGRAM);usage->setParameters(p);pass->mVertexProgramUsage=usage;}
   if(k==0){state.material=c.op==3&&(seed/13+i)%3==0?NULL:material.getPointer();int index=int((seed/17+i)%(units+3))-1;if(units==0||(state.m_flag30&&seed%2&&units<2))index=units;state.projectorPass=index;}else if(k==1)state.material18=material.getPointer();else state.material20=(seed/23+i)%3?material.getPointer():NULL;
  }model->m_renderableStates.push_back(state);
 }
 detour::Set hooks;hooks.redirect(gtBest,gtBest,&best);hooks.redirect(gtCompile,gtCompile,&compile);hooks.redirect(gtConstant,gtConstant,&constant);TL_REDIRECT(hooks,gtFiles,&files);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}const wchar_t*names[]={L"",L"media/rim.png",L"\\folder\\rim.png",L"\x041b\x0435\x0441.png"};std::wstring name=names[seed/4%4];
 if(c.op==0){void(*fn)(CGenericModel*)=ours?gtNewClear:gtOldClear;if(autotest::beginInvocation(out,fn)){fn(model);out.callCompleted=1;}}
 else if(c.op==3){void(*fn)(CGenericModel*,std::wstring)=ours?gtNewRim:gtOldRim;if(autotest::beginInvocation(out,fn)){fn(model,name);out.callCompleted=1;}}
 else{void(*fn)(CGenericModel*,const std::wstring&)=c.op==1?(ours?gtNewHigh:gtOldHigh):(ours?gtNewBehind:gtOldBehind);if(autotest::beginInvocation(out,fn)){fn(model,name);out.callCompleted=1;}}
 number(model->m_flag238);number(client->m_pendingPassClear);for(unsigned i=0;i<count;++i){CRenderableStates&s=model->m_renderableStates[i];number(s.projectorTechnique);number(s.projectorPass);number(s.m_flag30);number(s.m_flag31);}
 for(unsigned i=0;i<materials.size();++i){Ogre::Pass*p=materials[i]->getTechnique(0)->getPass(0);number(p->getNumTextureUnitStates());for(unsigned j=0;j<p->getNumTextureUnitStates();++j){Ogre::TextureUnitState*t=p->getTextureUnitState(j);text(t->getName());text(t->getTextureName());number(t->getTextureType());number(t->getNumFrames());number(t->getTextureCoordSet());const Ogre::TextureUnitState::UVWAddressingMode&a=t->getTextureAddressingMode();number(a.u);number(a.v);number(a.w);const Ogre::LayerBlendModeEx&b=t->getColourBlendMode();number(b.operation);number(b.source1);number(b.source2);number(t->getEffects().size());for(Ogre::TextureUnitState::EffectMap::const_iterator it=t->getEffects().begin();it!=t->getEffects().end();++it){number(it->first);number(it->second.subtype);}}}
 hooks.restore();gtDtor(model);Ogre::NedAllocImpl::deallocBytes(model);resources->m_GameClients.clear();gtResourceDtor(resources);Ogre::NedAllocImpl::deallocBytes(resources);for(unsigned i=0;i<materials.size();++i)Ogre::MaterialManager::getSingleton().remove(materials[i]->getHandle());
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(native.master);menugui::Client actualClient(*native.settings,native.master,*native.master->m_pSoundManager);client=actualClient.client;initialized(0x1482e00,false);initialized(0x1482e08,true);initialized(0x1528e40,false);initialized(0x1528e48,true);CFileSystem*previous=g_pFileSystem;void*memory=Ogre::NedAllocImpl::allocBytes(sizeof(CFileSystem),0,0,0);g_pFileSystem=static_cast<CFileSystem*>(memory);CFileSystem*fs=new(memory)CFileSystem(false);
 const char*names[]={"generic_clear_projector","generic_highlight_texture","generic_behind_texture","generic_rim_lighting"};uintptr_t addresses[]={reinterpret_cast<uintptr_t>(gtOldClear),reinterpret_cast<uintptr_t>(gtOldHigh),reinterpret_cast<uintptr_t>(gtOldBehind),reinterpret_cast<uintptr_t>(gtOldRim)};int failures=0;
 for(unsigned op=0;op<4;++op){autotest::Coverage coverage(names[op],addresses[op]);for(unsigned seed=0;seed<432;++seed){Case c={op,seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    texture op%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",op,seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);failures+=coverage.completed!=432||coverage.missing||coverage.different;}
 fs->~CFileSystem();Ogre::NedAllocImpl::deallocBytes(fs);g_pFileSystem=previous;return failures;
}
}
TL_TEST(complete_generic_texture){return systems_fixture::isolated(&worker,host);}
