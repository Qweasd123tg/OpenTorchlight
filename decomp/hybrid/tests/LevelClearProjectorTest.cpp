#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "SettingsVariables.h"
#include <OgreMaterialManager.h>
#include <OgreTechnique.h>
#include <OgrePass.h>
#include <OgreTextureUnitState.h>
TL_ORIGINAL(void,cpOld,(CLevel*,CGenericModel*,CGenericModel*),"_ZN6CLevel18clearProjectorPassEP13CGenericModelS1_")
extern "C" void cpNew(CLevel*,CGenericModel*,CGenericModel*) __asm__("_ZN6CLevel18clearProjectorPassEP13CGenericModelS1_");
TL_ORIGINAL(void,cpModelCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,cpModelDtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
TL_FUNCTION(cpClear,"_ZN13CGenericModel18clearProjectorPassEv")
extern "C" char cpCompile[] __asm__("_ZN4Ogre8Material7compileEb");
namespace {
autotest::Capture*output;CLevel*level;CGenericModel*models[3];CSettings*settings;Ogre::SceneManager*scene;unsigned seed;
void number(unsigned n){output->add(&n,4);}void text(const std::string&s){number(s.size());if(s.size())output->add(s.data(),s.size());}
void clear(CGenericModel*p){number(1);unsigned id=99;for(unsigned i=0;i<3;++i)if(p==models[i])id=i;number(id);if(id==99)std::abort();}
void compile(Ogre::Material*p,bool automatic){number(2);number(automatic);unsigned id=99;for(unsigned i=0;i<level->m_renderableStates.size();++i)if(p==level->m_renderableStates[i].material)id=i;number(id);if(id==99)std::abort();number(level->m_renderableStates[id].projectorTechnique);}
struct Item:finishlevel::Item{unsigned index;Item(CResourceManager*r,unsigned i):finishlevel::Item(r),index(i){}virtual void*getUnitModel(){number(3);number(index);return models[index%3];}};
void execute(void*raw,autotest::Capture&out,bool ours){
 output=&out;seed=*static_cast<unsigned*>(raw);finishlevel::Fixture f;level=&f.level;f.resources.m_pSceneManager=scene;settings->SetInt(KSETTINGS_SHADOWS_ENABLED,seed%2);
 for(unsigned i=0;i<3;++i){models[i]=static_cast<CGenericModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0));cpModelCtor(models[i],NULL,NULL,OGRE_UTILITIES::PRIMITIVE_SPHERE);}
 const wchar_t*paths[]={L"LIGHT",L"lightmesh",L"other/LIGHT",L"",L"\x041b\x0435\x0441",L"light"};models[0]->m_sModelPath=paths[seed/4%6];
 Item*items[3];for(unsigned i=0;i<3;++i){items[i]=new Item(&f.resources,i);items[i]->m_bLevelLighting=(seed/7+i)%2;}
 for(unsigned i=0;i<seed/11%6;++i)finishlevel::prepend(level->m_items,static_cast<CItem*>(items[i%3]));
 Ogre::MaterialPtr materials[4];unsigned entries=seed/3%5;level->m_renderableStates.resize(entries);
 for(unsigned i=0;i<entries;++i){std::string name="level-clear-projector-";name+=char('0'+i);materials[i]=Ogre::MaterialManager::getSingleton().create(name,"General");Ogre::Pass*pass=materials[i]->getTechnique(0)->getPass(0);unsigned count=(seed/13+i)%8;for(unsigned j=0;j<count;++j){Ogre::TextureUnitState*t=pass->createTextureUnitState();std::string n="unit-";n+=char('0'+j);t->setName(n);}
 CRenderableStates&s=level->m_renderableStates[i];std::memset(&s,0,0x38);s.material=materials[i].get();s.m_flag30=(seed/17+i)%2;s.m_flag31=(seed/19+i)%2;s.projectorTechnique=short(13+i);s.projectorPass=short(int((seed/23+i)%(count+3))-1);
 // A pass with no texture units cannot own a removable projector unit.
 if(count==0 || (s.m_flag30&&(seed%2)&&count<2))s.projectorPass=short(count);
 }
 detour::Set hooks;TL_REDIRECT(hooks,cpClear,&clear);hooks.redirect(cpCompile,cpCompile,&compile);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Fn)(CLevel*,CGenericModel*,CGenericModel*);Fn fn=ours?cpNew:cpOld;if(!autotest::beginInvocation(out,fn))return;fn(level,seed&1?models[0]:NULL,seed&2?models[1]:NULL);out.callCompleted=1;
 number(level->m_renderableStates.size());for(unsigned i=0;i<entries;++i){CRenderableStates&s=level->m_renderableStates[i];number(s.projectorTechnique);number(s.projectorPass);number(s.m_flag30);number(s.m_flag31);Ogre::Pass*pass=materials[i]->getTechnique(0)->getPass(0);number(pass->getNumTextureUnitStates());for(unsigned j=0;j<pass->getNumTextureUnitStates();++j)text(pass->getTextureUnitState(j)->getName());}
 hooks.restore();level->m_renderableStates.clear();for(unsigned i=0;i<entries;++i){Ogre::MaterialManager::getSingleton().remove(materials[i]->getHandle());materials[i].setNull();}
 for(unsigned i=0;i<3;++i){delete items[i];cpModelDtor(models[i]);Ogre::NedAllocImpl::deallocBytes(models[i]);}
}
void original(void*p,autotest::Capture&o){execute(p,o,false);}void candidate(void*p,autotest::Capture&o){execute(p,o,true);}
int run(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;autotest::Coverage coverage("level_clear_projector",(uintptr_t)&cpOld);for(unsigned i=0;i<1536;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    clear projector seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(level_clear_projector){return systems_fixture::isolated(&run,host);}
