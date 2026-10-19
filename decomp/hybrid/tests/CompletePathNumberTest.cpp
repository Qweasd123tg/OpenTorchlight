#include "AutoTest.h"
#include "tests/NativeEditorControls.h"
#include "tests/MenuGuiFixture.h"
#include "tests/SystemsFixtureWorker.h"
#include "PathController.h"
#include "PathNode.h"
#include "EditorScene.h"
#include "OgreUtilities.h"
#include <OgreSubMesh.h>
TL_ORIGINAL(void,pnOld,(CPathController*,unsigned),"_ZN15CPathController21setNumberOfPathPointsEj")
extern "C" void pnNew(CPathController*,unsigned) __asm__("_ZN15CPathController21setNumberOfPathPointsEj");
TL_ORIGINAL(void,pnCtor,(CPathController*,CResourceManager*),"_ZN15CPathControllerC1EP16CResourceManager")
TL_ORIGINAL(void,pnDtor,(CPathController*),"_ZN15CPathControllerD1Ev")
TL_ORIGINAL(void,pnNodeCtor,(CPathNode*,CPathController*,CResourceManager*),"_ZN9CPathNodeC1EP15CPathControllerP16CResourceManager")
TL_FUNCTION(pnEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(pnCreate,"_ZN12CEditorScene24CreateObjectByDescriptorERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(pnCreated,"_ZN20CEditorObjectManager19EditorObjectCreatedEP17CEditorBaseObject")
TL_FUNCTION(pnDeleted,"_ZN20CEditorObjectManager19EditorObjectDeletedEP17CEditorBaseObject")
TL_FUNCTION(pnSelected,"_ZN20CEditorObjectManager20EditorObjectSelectedEP17CEditorBaseObject")
TL_FUNCTION(pnEntity,"_ZN14OGRE_UTILITIES12createEntityEPN4Ogre12SceneManagerENS_11EPRIMITIVESENS_10EQUERYMASKEPKc")
TL_FUNCTION(pnText,"_ZN7CGameUI18getTextEventObjectERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_b")
TL_FUNCTION(pnReturnText,"_ZN7CGameUI21returnTextEventObjectEP10CTextEvent")
namespace {
nativeeditor::Controls*editor;CGameUI*ui;CEditorScene*scene;CPathController*path;autotest::Capture*output;bool invoking,editorFlag;unsigned attempts,factoryMode,entityCount;Ogre::MeshPtr mesh;CEditorBaseObject*wrong;
std::vector<CPathNode*>nodes;std::vector<TSafePointer<CPathNode>*>observers;
void word(unsigned n){if(invoking)output->add(&n,4);}unsigned identity(CEditorBaseObject*p){for(unsigned i=0;i<nodes.size();++i)if(nodes[i]==p)return i;return 0xffffffff;}
bool running(CResourceManager*p){if(p!=editor->resources)std::abort();word(1);return editorFlag;}
Ogre::Entity*entity(Ogre::SceneManager*p,OGRE_UTILITIES::EPRIMITIVES primitive,OGRE_UTILITIES::EQUERYMASK mask,const char*prefix){if(p!=editor->resources->getSceneManager()||primitive!=3||mask!=8||std::string(prefix)!="gm")std::abort();word(8);char name[50];std::sprintf(name,"path-number-native-entity-%u",entityCount++);return p->createEntity(name,mesh->getName());}
CTextEvent*text(CGameUI*p,const Ogre::Vector3&,const std::string&value,float,float,CEGUI::colour,CEGUI::colour,bool flag){if(p!=ui||!value.empty()||flag)std::abort();word(9);return NULL;}
void returnText(CGameUI*p,CTextEvent*event){if(p!=ui||event)std::abort();word(10);}
CPathNode*newNode(){CPathNode*p=static_cast<CPathNode*>(Ogre::NedAllocImpl::allocBytes(sizeof(CPathNode),0,0,0));std::memset(p,0,sizeof(CPathNode));pnNodeCtor(p,NULL,editor->resources);nodes.push_back(p);TSafePointer<CPathNode>*observer=new TSafePointer<CPathNode>;observer->setObject(p);observers.push_back(observer);return p;}
CEditorBaseObject*create(CEditorScene*p,const std::wstring&name,bool load){if(p!=scene||name!=L"Path Node"||!load)std::abort();word(2);++attempts;if(attempts==1&&factoryMode==1)return NULL;if(attempts==1&&factoryMode==2)return wrong;return newNode();}
void created(CEditorObjectManager*p,CEditorBaseObject*object){if(p!=editor->manager)std::abort();word(3);word(identity(object));}
void deleted(CEditorObjectManager*p,CEditorBaseObject*object){if(p!=editor->manager)std::abort();word(4);word(identity(object));}
void selected(CEditorObjectManager*p,CEditorBaseObject*object){if(p!=editor->manager)std::abort();word(5);word(identity(object));}
void initialized(uintptr_t address,const wchar_t*value=L""){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p)new(reinterpret_cast<void*>(address))std::wstring(value);}
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);output=&out;invoking=false;attempts=0;entityCount=0;factoryMode=seed/12%3;editorFlag=seed/3%2;nodes.clear();observers.clear();CEditorScene owner(L"path-number-scene");scene=&owner;CEditorBaseObject other;wrong=&other;path=static_cast<CPathController*>(Ogre::NedAllocImpl::allocBytes(sizeof(CPathController),0,0,0));pnCtor(path,editor->resources);path->SetSceneOwner(scene);path->setPosition(Ogre::Vector3(1.f+seed%7,-2.f,3.f));path->m_pathName=seed%2?L"\u0422\u0440\u043e\u043f\u0430":L"";
 detour::Set hooks;TL_REDIRECT(hooks,pnEditor,&running);TL_REDIRECT(hooks,pnEntity,&entity);TL_REDIRECT(hooks,pnText,&text);TL_REDIRECT(hooks,pnReturnText,&returnText);TL_REDIRECT(hooks,pnCreate,&create);TL_REDIRECT(hooks,pnCreated,&created);TL_REDIRECT(hooks,pnDeleted,&deleted);TL_REDIRECT(hooks,pnSelected,&selected);if(hooks.failed())std::abort();unsigned initial[]={0,1,3,5,12};unsigned n=initial[seed/6%5];for(unsigned i=0;i<n;++i){CPathNode*node=newNode();node->setPosition(float(i),float(i)*.5f,-float(i));node->m_pPathController=path;path->m_pathNodes.add(node);}const unsigned values[]={0,1,3,6,100,101,0xffffffff};unsigned requested=values[seed%7];path->m_iNumberOfPathPoints=seed/42%2?static_cast<int>(requested>100?100:requested):static_cast<int>(n);unsigned oldObjects=g_iTotalCountOfObjects;
 invoking=true;void(*fn)(CPathController*,unsigned)=ours?pnNew:pnOld;if(autotest::beginInvocation(out,fn)){fn(path,requested);out.callCompleted=1;}word(path->m_iNumberOfPathPoints);word(path->m_pathNodes.size());word(attempts);word(g_iTotalCountOfObjects-oldObjects);for(unsigned i=0;i<path->m_pathNodes.size();++i){CPathNode*node=path->m_pathNodes[i];word(identity(node));word(node->m_pPathController==path);out.addText(node->m_sText);Ogre::Vector3 position=node->getPosition(false);out.add(position.ptr(),12);}for(unsigned i=0;i<observers.size();++i)word(observers[i]->getObject()!=NULL);invoking=false;path->m_pathNodes.clear();for(unsigned i=0;i<observers.size();++i){CPathNode*node=observers[i]->getObject();if(node){node->m_pPathController=NULL;delete node;}delete observers[i];}pnDtor(path);Ogre::NedAllocImpl::deallocBytes(path);hooks.restore();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());CStringTranslate translate(L"");menugui::Fixture gui(*CMasterResourceManager::getSingleton()->m_pSettings,services.scene);ui=gui.ui;nativeeditor::Controls actual(services);editor=&actual;initialized(0x1428728);initialized(0x1428748,L"MONSTERS");initialized(0x1429ea8);Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().getByName("lightYellow");if(material.isNull())material=Ogre::MaterialManager::getSingleton().create("lightYellow","General");material->removeAllTechniques();mesh=Ogre::MeshManager::getSingleton().createManual("path-number-native-mesh","General");mesh->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);mesh->createSubMesh()->setMaterialName("lightYellow");autotest::Coverage coverage("path_number",reinterpret_cast<uintptr_t>(pnOld));for(unsigned seed=0;seed<252;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    path number seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);mesh.setNull();return coverage.completed!=252||coverage.missing||coverage.different;}
}
TL_TEST(complete_path_number){return systems_fixture::isolated(&worker,host);}
