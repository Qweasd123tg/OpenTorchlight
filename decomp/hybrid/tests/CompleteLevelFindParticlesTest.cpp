#include "tests/FinishLevelFixture.h"
#include "tests/NativeMenuServices.h"
#include "tests/NativeEditorControls.h"
#include "tests/SystemsFixtureWorker.h"
#include "NativeAutomapFixture.h"
#include "ParticleTechWrapper.h"
#include "ParticlePreloader.h"
#include <OgreControllerManager.h>
void fpConfigure(ParticleUniverse::ParticleTechnique*,bool,bool);
unsigned fpFlags(ParticleUniverse::ParticleTechnique*);
TL_ORIGINAL(void,fpOld,(CLevel*),"_ZN6CLevel13findParticlesEv")
extern "C" void fpNew(CLevel*) __asm__("_ZN6CLevel13findParticlesEv");
TL_FUNCTION(fpQuery,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEEP10TArrayListIP17CEditorBaseObjectE")
TL_FUNCTION(fpInit,"_ZN12CEditorScene9InitSceneEP16CResourceManagerj")
namespace {
autotest::Capture*output;unsigned seed;CEditorScene*rooms[3];CLayout*layouts[4];CParticleTechWrapper*wrappers[3];CEditorBaseObject*base;
void number(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){number(s.size());if(s.size())output->add(s.data(),s.size()*4);}
unsigned layoutID(CLayout*p){for(unsigned i=0;i<4;++i)if(p==layouts[i])return i;std::abort();return 99;}
void init(CEditorScene*,CResourceManager*r,unsigned flags){if(r||flags)std::abort();}
void query(CEditorScene*p,const std::wstring&name,TArrayList<CEditorBaseObject*>*out){wide(name);number(out->size());number(out->m_nCapacity);number(out->m_nGrowBy);for(unsigned i=0;i<3;++i)if(p==rooms[i]){number(1);number(i);unsigned count=(seed/3+i*2)%8;for(unsigned j=0;j<count;++j)out->add(layouts[(seed+j+i)%4]);return;}for(unsigned i=0;i<4;++i)if(p==layouts[i]){number(2);number(i);unsigned count=(seed/7+i*3)%9;for(unsigned j=0;j<count;++j){unsigned k=(seed+j+i)%5;out->add(k==0?NULL:k==1?base:static_cast<CEditorBaseObject*>(wrappers[k-2]));}return;}std::abort();}
void side(void*raw,autotest::Capture&out,bool ours){seed=*static_cast<unsigned*>(raw);output=&out;finishlevel::Fixture f;for(unsigned i=0;i<seed%4;++i)f.level.m_RoomScenes.add(rooms[i]);for(unsigned i=0;i<seed/5%13;++i)f.level.m_auxiliaryLayouts.add(layouts[(i+seed)%4]);for(unsigned i=0;i<4;++i)layouts[i]->m_bStartOnLoad=((seed/11+i)%3)!=0;for(unsigned i=0;i<3;++i){if(!wrappers[i]->m_technique)std::abort();fpConfigure(wrappers[i]->m_technique,((seed/13+i)%4)==0,((seed/17+i)%2)!=0);}
 detour::Set hooks;TL_REDIRECT(hooks,fpQuery,&query);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef void(*Fn)(CLevel*);Fn fn=ours?fpNew:fpOld;if(!autotest::beginInvocation(out,fn))return;fn(&f.level);out.callCompleted=1;number(f.level.m_auxiliaryLayouts.size());number(f.level.m_auxiliaryLayouts.m_nCapacity);number(f.level.m_auxiliaryLayouts.m_nGrowBy);for(unsigned i=0;i<f.level.m_auxiliaryLayouts.size();++i)number(layoutID(f.level.m_auxiliaryLayouts[i]));for(unsigned i=0;i<3;++i)number(fpFlags(wrappers[i]->m_technique));hooks.restore();f.level.m_RoomScenes.clear();}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(services.master);nativeeditor::Controls*controls=new nativeeditor::Controls(services);controls->game.game->m_sceneManager=services.scene;if(!services.master->m_pParticlePreloader)services.master->m_pParticlePreloader=new CParticlePreloader(NULL);if(!Ogre::ControllerManager::getSingletonPtr())new Ogre::ControllerManager;if(!services.scene->hasCamera("PlayerCam")){menugui::ProjectionDuringConstruction projection;services.scene->createCamera("PlayerCam");}const char*names[]={"BaseWhite","BaseWhiteNoLighting"};for(unsigned i=0;i<2;++i){Ogre::MaterialPtr m=Ogre::MaterialManager::getSingleton().getByName(names[i]);if(!m.isNull())m->removeAllTechniques();}for(unsigned i=0;i<3;++i)wrappers[i]=new CParticleTechWrapper(controls->resources);for(unsigned i=0;i<3;++i)rooms[i]=new CEditorScene(L"findParticles room");{detour::Set setup;TL_REDIRECT(setup,fpInit,&init);if(setup.failed())return 1;for(unsigned i=0;i<4;++i)layouts[i]=new CLayout(NULL,static_cast<ELAYOUT_TYPES>(0));}base=new CEditorBaseObject;
 autotest::Coverage coverage("level_find_particles",0x950660);int failed=0;for(unsigned i=0;i<384;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    findParticles seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned z=0;z<a.capture.length&&z<b.capture.length;++z)if(a.capture.data[z]!=b.capture.data[z]){host->log("    firstdiff%u old%02x new%02x\n",z,(unsigned char)a.capture.data[z],(unsigned char)b.capture.data[z]);break;}failed=1;break;}}coverage.report(host);{level_native::CameraNotificationDuringCleanup camera;services.scene->destroyCamera("PlayerCam");}return failed||coverage.completed!=384||coverage.missing||coverage.different;}
}
TL_TEST(complete_level_find_particles){return systems_fixture::isolated(&worker,host);}
