#include <Ogre.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "ParticleTechWrapper.h"
#include "GenericModel.h"
#include <ParticleUniverseSystem.h>
#undef protected
#undef private
#include "tests/ParticleNativeOwners.h"

TL_ORIGINAL(void,pathCtor,(CParticleTechWrapper*,CResourceManager*),"_ZN20CParticleTechWrapperC1EP16CResourceManager")
TL_ORIGINAL(void,pathDtor,(CParticleTechWrapper*),"_ZN20CParticleTechWrapperD1Ev")
TL_ORIGINAL(void,oldModelPath,(CParticleTechWrapper*,const std::wstring&),"_ZN20CParticleTechWrapper12setModelPathERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,oldTexturePath,(CParticleTechWrapper*,const std::wstring&),"_ZN20CParticleTechWrapper14setTexturePathERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void newModelPath(CParticleTechWrapper*,const std::wstring&) __asm__("_ZN20CParticleTechWrapper12setModelPathERKSbIwSt11char_traitsIwESaIwEE");
extern "C" void newTexturePath(CParticleTechWrapper*,const std::wstring&) __asm__("_ZN20CParticleTechWrapper14setTexturePathERKSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(pathMaterial,"_ZN20CParticleTechWrapper21createTextureMaterialEv")
TL_FUNCTION(pathRender,"_ZN20CParticleTechWrapper13setRenderTypeEjb")
namespace {
ParticleNativeOwners owners;
struct Case{unsigned seed;bool model,negative;};
autotest::Capture* output;
void number(long long value){output->add(&value,sizeof(value));}
void material(CParticleTechWrapper* w){number(1);output->addText(w->m_pTexturePath);}
void render(CParticleTechWrapper*w,unsigned type,bool force){number(2);number(type);number(force);number(w->m_pUnknown1A8!=NULL);output->addText(w->m_pModelPath);}
class Texture:public Ogre::Texture{
public:
 bool loaded,reloadable;unsigned reloads;
 Texture(Ogre::ResourceManager*m,const Ogre::String&n,Ogre::ResourceHandle h,const Ogre::String&g,bool manual,Ogre::ManualResourceLoader*l):Ogre::Texture(m,n,h,g,manual,l),loaded(false),reloadable(false),reloads(0){}
 bool isLoaded()const{number(3);return loaded;}
 bool isReloadable()const{number(4);return reloadable;}
 void reload(){number(5);++reloads;}
 Ogre::HardwarePixelBufferSharedPtr getBuffer(size_t,size_t){std::abort();return Ogre::HardwarePixelBufferSharedPtr();}
protected:
 void loadImpl(){}
 void createInternalResourcesImpl(){}
 void freeInternalResourcesImpl(){}
};
class Textures:public Ogre::TextureManager{
public:
 Ogre::PixelFormat getNativeFormat(Ogre::TextureType,Ogre::PixelFormat format,int){return format;}
 bool isHardwareFilteringSupported(Ogre::TextureType,Ogre::PixelFormat,int,bool){return false;}
protected:
 Ogre::Resource*createImpl(const Ogre::String&n,Ogre::ResourceHandle h,const Ogre::String&g,bool manual,Ogre::ManualResourceLoader*l,const Ogre::NameValuePairList*){return new Texture(this,n,h,g,manual,l);}
};
void side(void*raw,autotest::Capture&out,bool ours){
 const Case&c=*static_cast<Case*>(raw);output=&out;
 particleNativeSetEditorMode(owners,true);
 CParticleTechWrapper*w=static_cast<CParticleTechWrapper*>(Ogre::NedAllocImpl::allocBytes(sizeof(CParticleTechWrapper),0,0,0));pathCtor(w,owners.resources);
 const wchar_t*paths[]={L"",L"media/particles/Recover.dds",L"Recover.dds",L"dir/subdir/Recover.dds",L"dir/Other.dds"};
 std::wstring value=paths[c.seed%5];
 w->m_pTexturePath=(c.seed/5%2)?value:L"old.dds";w->m_pModelPath=(c.seed/5%2)?value:L"old.mesh";
 if(c.model&&c.seed/10%2)w->m_pUnknown1A8=new CGenericModel(owners.resources,NULL,L"",L"",false);
 Textures textures;Ogre::TexturePtr texture=textures.create("Recover.dds","General",true,NULL);
 Texture*t=static_cast<Texture*>(texture.getPointer());t->loaded=bool(c.seed/20%2);t->reloadable=bool(c.seed/40%2);
 unsigned renderType=w->m_renderType;if(c.model)w->m_renderType=c.seed%13;
 particleNativeSetEditorMode(owners,c.seed/80%2==0);
 detour::Set hooks;TL_REDIRECT(hooks,pathMaterial,&material);TL_REDIRECT(hooks,pathRender,&render);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Function)(CParticleTechWrapper*,const std::wstring&);
 Function function=c.model?(ours?newModelPath:oldModelPath):(ours?newTexturePath:oldTexturePath);
 const std::wstring&argument=c.seed%11==0?(c.model?w->m_pModelPath:w->m_pTexturePath):value;
 int before=g_iTotalCountOfObjects;
 if(!autotest::beginInvocation(out,function))return;function(w,argument);out.callCompleted=1;
 if(ours&&c.negative)(c.model?w->m_pModelPath:w->m_pTexturePath)+=L" negative";
 number(6);out.addText(w->m_pModelPath);out.addText(w->m_pTexturePath);number(t->reloads);number(w->m_pUnknown1A8!=NULL);number(g_iTotalCountOfObjects-before);
 if(w->m_pUnknown1A8)number(w->m_pUnknown1A8->m_pResourceManager==owners.resources);
 w->m_renderType=renderType;hooks.restore();particleNativeSetEditorMode(owners,true);pathDtor(w);Ogre::NedAllocImpl::deallocBytes(w);
}
void a(void*p,autotest::Capture&out){side(p,out,false);}void b(void*p,autotest::Capture&out){side(p,out,true);}
int worker(const tlhybrid_host*host,bool model){
 owners=particleNativeOwners(2);autotest::Coverage coverage(model?"technique_model_path_recovery":"technique_texture_path_recovery",model?0xa460e0:0xa45200);
 for(unsigned i=0;i<160;++i){Case c={i,model,false};autotest::Outcome before,after;autotest::runChild(a,&c,before,2000,10000);autotest::runChild(b,&c,after,2000,10000);
  if(coverage.observe(host,before,after)){host->log("    technique path case%u status%d/%d issue%u/%u bytes%lu/%lu\n",i,before.childStatus,after.childStatus,before.capture.issue,after.capture.issue,(unsigned long)before.capture.length,(unsigned long)after.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);Case c={67,model,true};autotest::Outcome before,after;autotest::runChild(a,&c,before,2000,10000);autotest::runChild(b,&c,after,2000,10000);
 bool detected=before.capture.length!=after.capture.length||std::memcmp(before.capture.data,after.capture.data,before.capture.length);
 host->log("    technique path negative control detected%u\n",detected?1u:0u);
 return !detected||autotest::incomplete(before)||autotest::incomplete(after)||!before.reportValid||!after.reportValid||before.childStatus||after.childStatus;
}
int modelWorker(const tlhybrid_host*h){return worker(h,true);}int textureWorker(const tlhybrid_host*h){return worker(h,false);}
}
TL_TEST(technique_model_path_recovery){return systems_fixture::isolated(modelWorker,host);}
TL_TEST(technique_texture_path_recovery){return systems_fixture::isolated(textureWorker,host);}
