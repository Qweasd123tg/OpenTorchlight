#include <Ogre.h>
#include <typeinfo>
#include <dlfcn.h>
#include <sys/mman.h>
#include <execinfo.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "Editor.h"
#include "EditorScene.h"
#include "ResourceManager.h"
#include "GameClient.h"
#include "Level.h"
#include "DataGroup.h"
#include "ParticleTechWrapper.h"
#include "POV.h"
#include "MouseHandler.h"
#include "ParticlePreloader.h"
#include "Undo.h"
#undef protected
#undef private
#include "tests/NativeEditorControls.h"
#include "tests/NativeMenuClient.h"
#include "CharacterLibraryBoundary.h"
TL_ORIGINAL(void,esRelease,(CEditor*),"_ZN7CEditor16releaseResourcesEv")
TL_ORIGINAL(void,esReinit,(CEditor*),"_ZN7CEditor11reinitSceneEv")
TL_ORIGINAL(void,esRecreate,(CEditor*,unsigned),"_ZN7CEditor13recreateSceneEj")
TL_ORIGINAL(bool,esDump,(CEditor*,const std::wstring&),"_ZN7CEditor36EditorDumpDescriptionOfObjectsToFileERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,esParticles,(CEditor*,float,float),"_ZN7CEditor21updateParticleSystemsEff")
extern "C" void esNewRelease(CEditor*) __asm__("_ZN7CEditor16releaseResourcesEv");
extern "C" void esNewReinit(CEditor*) __asm__("_ZN7CEditor11reinitSceneEv");
extern "C" void esNewRecreate(CEditor*,unsigned) __asm__("_ZN7CEditor13recreateSceneEj");
extern "C" bool esNewDump(CEditor*,const std::wstring&) __asm__("_ZN7CEditor36EditorDumpDescriptionOfObjectsToFileERKSbIwSt11char_traitsIwESaIwEE");
extern "C" void esNewParticles(CEditor*,float,float) __asm__("_ZN7CEditor21updateParticleSystemsEff");
TL_FUNCTION(esSceneInit,"_ZN12CEditorScene9InitSceneEP16CResourceManagerj")
TL_FUNCTION(esSceneDescribe,"_ZN12CEditorScene36SaveDescriptionOfSceneAndDescriptorsEP10CDataGroupj")
TL_FUNCTION(esDataSave,"_ZN10CDataGroup10SaveToFileERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(esObjects,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case{unsigned op,profile,negative;};const Case*current;autotest::Capture*cap;nativegame::Services*services;CEditor*editor;CResourceManager*resources;CEditorScene*expectedScene;TArrayList<CEditorBaseObject*>*objectList;
const tlhybrid_host*debugHost;void fault(int s){void*p[28];int n=backtrace(p,28);if(debugHost)for(int i=0;i<n;++i)debugHost->log("    Editor scene signal%d frame%d %p\n",s,i,p[i]);_exit(128+s);}
void word(unsigned x){cap->add(&x,4);}void real(float x){cap->add(&x,4);}
void globals(){void*p;std::memcpy(&p,reinterpret_cast<void*>(0x145c6f0),8);if(!p)new(reinterpret_cast<void*>(0x145c6f0))std::wstring;const uintptr_t arrays[]={0x145c700,0x145c780,0x145c820};const std::wstring*values[]={gEDITOR_EVENT_NAMES,gEDITOR_FLAG_NAMES,gEDITOR_UPDATE_MASKS};const unsigned sizes[]={14,17,4};for(unsigned a=0;a<3;++a)for(unsigned i=0;i<sizes[a];++i){void*at=reinterpret_cast<void*>(arrays[a]+8*i);std::memcpy(&p,at,8);if(!p)new(at)std::wstring(values[a][i]);}}
void init(CEditorScene*p,CResourceManager*r,unsigned flags){word(10);word(r==resources);word(flags);cap->addText(p->getName());cap->addText(std::string(typeid(*p).name()));word(editor->m_EditorScenes.size());for(unsigned i=0;i<editor->m_EditorScenes.size();++i)word(editor->m_EditorScenes[i]==p);}
void describe(CEditorScene*p,CDataGroup*g,unsigned index){word(11);word(index);cap->addText(p->getName());CDataGroup*child=g->AddDataGroup(p->getName());child->AddDataValue(L"profile",current->profile);child->AddDataValue(L"index",index);}
void data(CDataGroup*g){cap->addText(g->GetGroupName());word(g->GetNumberOfDataValues());for(unsigned i=0;i<g->GetNumberOfDataValues();++i){CDataValue*v=g->GetDataValue(i);cap->addText(v->GetDataValueName());word(v->GetValueType());cap->addText(v->GetValueAsString());}word(g->GetNumberOfDataGroups());for(unsigned i=0;i<g->GetNumberOfDataGroups();++i)data(g->GetDataGroup(i));}
int save(CDataGroup*g,const std::wstring&path){word(12);cap->addText(path);data(g);return current->profile&1?-5:1;}
TArrayList<CEditorBaseObject*>*objects(CEditorScene*p,const std::wstring&name){word(13);word(p==expectedScene);cap->addText(name);return objectList;}
void recordScenes(CEditor*p){word(p->m_EditorScenes.size());for(unsigned i=0;i<p->m_EditorScenes.size();++i){CEditorScene*s=p->m_EditorScenes[i];word(s!=NULL);if(s){cap->addText(s->getName());cap->addText(std::string(typeid(*s).name()));}}word(p->m_EditorSceneIDs.size());for(std::map<std::wstring,unsigned>::iterator i=p->m_EditorSceneIDs.begin();i!=p->m_EditorSceneIDs.end();++i){cap->addText(i->first);word(i->second);}}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);current=&c;cap=&out;signal(SIGSEGV,fault);signal(SIGABRT,fault);globals();nativeeditor::Controls*fixture=new nativeeditor::Controls(*services);editor=fixture->editor;resources=fixture->resources;fixture->game.game->m_sceneManager=services->scene;out.length=0;if(!services->master->m_pParticlePreloader)services->master->m_pParticlePreloader=new CParticlePreloader(NULL);
 if(c.op==0){
  unsigned mask=c.profile;editor->m_iFlags=int(mask*37);for(unsigned i=0;i<c.profile%4;++i){CUndo*u=new CUndo;editor->m_Undos.push_back(u);u=new CUndo;editor->m_Redos.push_back(u);}if(mask&1)editor->m_pCameraController=new CPOV(*services->settings);if(mask&2)editor->m_pUnknownB0=new CMouseHandler(NULL);for(unsigned i=0;i<(mask>>2)%4;++i){editor->m_EditorScenes.add(i&1?NULL:new CEditorScene(L"release owner"));editor->m_EditorSceneIDs[L"release"]=i;}if(mask&4){editor->m_pUnknown130=services->scene->getRootSceneNode()->createChildSceneNode();editor->m_pUnknown130->createChildSceneNode();}if(mask&8)editor->m_pUnknown168=new CLevel(L"release",services->settings,NULL,resources,services->scene,NULL,int(c.profile),int(c.profile));TSafePointer<CEditorObjectManager>manager;manager.setObject(editor->m_pObjectManager);TSafePointer<CResourceManager>resource;resource.setObject(resources);TSafePointer<CPOV>pov;pov.setObject(editor->m_pCameraController);int before=g_iTotalCountOfObjects;
  typedef void(*F)(CEditor*);F f=ours?esNewRelease:esRelease;if(autotest::beginInvocation(out,f)){f(editor);out.callCompleted=1;if(ours&&c.negative)editor->m_iFlags=1;}
  word(before-g_iTotalCountOfObjects);word(manager.getObject()==NULL);word(resource.getObject()==NULL);word(pov.getObject()==NULL);word(editor->m_pUnknown130==NULL);word(editor->m_pUnknown138==NULL);word(editor->m_pUnknownB0==NULL);word(editor->m_pCameraController==NULL);word(editor->m_pObjectManager==NULL);word(editor->m_pUnknown168==NULL);word(editor->m_pUnknown128==NULL);word(editor->m_iFlags);word(editor->m_Undos.size());word(editor->m_Redos.size());for(std::list<CUndo*>::iterator i=editor->m_Undos.begin();i!=editor->m_Undos.end();++i)word(*i==NULL);for(std::list<CUndo*>::iterator i=editor->m_Redos.begin();i!=editor->m_Redos.end();++i)word(*i==NULL);recordScenes(editor);return;
 }
 if(c.op==1){
  services->settings->SetInt(KSETTINGS_AI_FREEZE,int(c.profile)-13);if(c.profile&1)editor->m_pUnknown168=new CLevel(L"previous",services->settings,NULL,resources,services->scene,NULL,int(c.profile),-int(c.profile));TSafePointer<CLevel>previous;previous.setObject(editor->m_pUnknown168);int before=g_iTotalCountOfObjects;typedef void(*F)(CEditor*);F f=ours?esNewReinit:esReinit;if(autotest::beginInvocation(out,f)){f(editor);out.callCompleted=1;if(ours&&c.negative)editor->m_iFlags^=1;}
  CLevel*p=editor->m_pUnknown168;word(p!=NULL);word(resources->m_pLevel==p);word(previous.getObject()==NULL);word(g_iTotalCountOfObjects-before);cap->addText(p->m_sDungeonName);word(p->m_resourceManager==resources);word(p->m_sceneManager==services->scene);word(p->m_iLevelDepth);word(editor->m_iFlags);return;
 }
 if(c.op==2){
  unsigned index=c.profile%5,count=c.profile/5;for(unsigned i=0;i<count;++i)editor->m_EditorScenes.add((i+c.profile)%3?new CEditorScene(L"old scene"):NULL);editor->m_EditorSceneIDs[L"Mesh Viewer"]=17;editor->m_EditorSceneIDs[L"Layout"]=18;editor->m_EditorSceneIDs[L"Particle Creator"]=19;detour::Set d;TL_REDIRECT(d,esSceneInit,init);if(d.failed())std::abort();typedef void(*F)(CEditor*,unsigned);F f=ours?esNewRecreate:esRecreate;if(autotest::beginInvocation(out,f)){f(editor,index);out.callCompleted=1;if(ours&&c.negative)editor->m_EditorSceneIDs[L"Layout"]^=1;}recordScenes(editor);return;
 }
 if(c.op==3){
  for(unsigned i=0;i<c.profile%5;++i){std::wstring name=L"scene-";name+=wchar_t(L'A'+i+c.profile);if(c.profile&4)name+=L"/задача";editor->m_EditorScenes.add(new CEditorScene(name.c_str()));}std::wstring path=c.profile&1?L"output/objects.dat":L"";path+=wchar_t(L'A'+c.profile);if(c.profile&8)path+=std::wstring(L"\0ignored",8);detour::Set d;TL_REDIRECT(d,esSceneDescribe,describe);TL_REDIRECT(d,esDataSave,save);if(d.failed())std::abort();typedef bool(*F)(CEditor*,const std::wstring&);F f=ours?esNewDump:esDump;if(autotest::beginInvocation(out,f)){bool result=f(editor,path);out.callCompleted=1;if(ours&&c.negative)result=!result;word(result);}return;
 }
 expectedScene=new CEditorScene(L"Particle Creator");editor->m_EditorScenes.add(c.profile%8==1?NULL:expectedScene);if(c.profile%8!=0)editor->m_EditorSceneIDs[L"Particle Creator"]=0;
 TArrayList<CEditorBaseObject*> list(2);objectList=c.profile%8==2?NULL:&list;CEditorBaseObject base;if(c.profile%8>=3)list.add(NULL);if(c.profile%8>=4)list.add(&base);CParticleTechWrapper*particle=NULL;
 if(c.profile%8>=5){if(!Ogre::ControllerManager::getSingletonPtr())new Ogre::ControllerManager;if(!services->scene->hasCamera("PlayerCam")){menugui::ProjectionDuringConstruction boundary;services->scene->createCamera("PlayerCam");}const char*names[]={"BaseWhite","BaseWhiteNoLighting"};for(unsigned n=0;n<2;++n){Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().getByName(names[n]);if(!material.isNull())material->removeAllTechniques();}particle=new CParticleTechWrapper(resources);list.add(particle);}
 editor->m_fParticleMovementA=c.profile&8?2.5f:5.0f;editor->m_fParticleMovementB=c.profile&16?0.0f:10.0f-float(c.profile%4)*4.0f;float elapsed=(float(c.profile%7)-2.0f)*.75f,height=c.profile&16?0.0f:c.profile&8?-1.5f:1.0f;detour::Set d;TL_REDIRECT(d,esObjects,objects);if(d.failed())std::abort();typedef void(*F)(CEditor*,float,float);F f=ours?esNewParticles:esParticles;if(autotest::beginInvocation(out,f)){for(unsigned j=0;j<3;++j){f(editor,elapsed+float(j)*1.25f,height);if(particle){Ogre::Vector3 position=particle->getPosition(false);out.add(&position,12);out.add(&particle->getOrientation()[0][0],64);}}out.callCompleted=1;if(ours&&c.negative)word(9);}
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uintptr_t address,unsigned count){debugHost=host;nativegame::Services native;services=&native;int failures=0;autotest::Coverage cov(name,address);for(unsigned i=0;i<count;++i){Case c={op,i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a,1200,6000);autotest::runChild(after,&c,b,1200,6000);int bad=cov.observe(host,a,b);TL_CHECK(failures,!bad);if(bad){host->log("    Editor scenes op%u profile%u status%d/%d issue%u/%u bytes%lu/%lu\n",op,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first difference%u values%u/%u\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}cov.report(host);return failures;}}cov.report(host);Case c={op,17,1};autotest::Outcome a,b;autotest::runChild(before,&c,a,1200,6000);autotest::runChild(after,&c,b,1200,6000);bool detected=a.capture.length!=b.capture.length||memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,detected&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    Editor scenes negative op%u detected%u\n",op,unsigned(detected));return failures;}
int releaseWorker(const tlhybrid_host*h){return run(h,0,"editor_complete_release",0x715820,32);}int reinitWorker(const tlhybrid_host*h){return run(h,1,"editor_complete_reinit",0x716cb0,32);}int recreateWorker(const tlhybrid_host*h){return run(h,2,"editor_complete_recreate",0x717b20,30);}int dumpWorker(const tlhybrid_host*h){return run(h,3,"editor_complete_dump",0x7163a0,32);}int particleWorker(const tlhybrid_host*h){return run(h,4,"editor_complete_particles",0x717020,32);}
}
TL_TEST(editor_complete_release){return systems_fixture::isolated(releaseWorker,host);}
TL_TEST(editor_complete_reinit){return systems_fixture::isolated(reinitWorker,host);}
TL_TEST(editor_complete_recreate){return systems_fixture::isolated(recreateWorker,host);}
TL_TEST(editor_complete_dump){return systems_fixture::isolated(dumpWorker,host);}
TL_TEST(editor_complete_particles){return systems_fixture::isolated(particleWorker,host);}
