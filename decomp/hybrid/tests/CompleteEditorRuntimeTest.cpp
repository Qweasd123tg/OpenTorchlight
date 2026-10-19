#include <Ogre.h>
#include <SDL.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <execinfo.h>
#include <typeinfo>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "Editor.h"
#include "EditorScene.h"
#include "LayoutScene.h"
#include "ResourceManager.h"
#include "GameClient.h"
#include "Game.h"
#include "Level.h"
#include "POV.h"
#include "RoomPiece.h"
#include "Quest.h"
#include "ParticlePreloader.h"
#include "ObjectControl3D.h"
#undef protected
#undef private
#include "tests/NativeEditorControls.h"
#include "tests/MenuGuiFixture.h"
#include "OgreUtilities.h"
#include <ParticleUniverseSystemManager.h>
#include "CharacterLibraryBoundary.h"
#include "EditorRuntimeEntries.h"
TL_FUNCTION(erAsyncKey,"_Z16GetAsyncKeyStatej")
extern "C" SDL_Window*SDL_CreateWindow(const char*,int,int,int,int,Uint32);
extern "C" void SDL_DestroyWindow(SDL_Window*);
namespace {
struct Case{unsigned op,profile,negative;};const Case*current;autotest::Capture*cap;nativegame::Services*services;CEditor*editor;CGame*game;CPOV*pov;Ogre::Camera*camera;CGameClient*client;CGameUI*ui;CLevel*level;CEditorObjectManager*manager;CEditorScene*layout;CQuestManager*quests;CQuest*questValues[3];TArrayList<CEditorBaseObject*>*list;Ogre::Entity*grid;bool oursSide;const tlhybrid_host*debugHost;
void fault(int signal){void*p[32];int n=backtrace(p,32);if(debugHost)for(int i=0;i<n;++i)debugHost->log("    Editor runtime signal%d op%u profile%u side%u frame%d %p\n",signal,current->op,current->profile,oursSide,i,p[i]);_exit(128+signal);}
void word(unsigned x){cap->add(&x,4);}void real(float x){cap->add(&x,4);}void vec(const Ogre::Vector3&v){cap->add(&v,12);}
void strings(){void*p;std::memcpy(&p,reinterpret_cast<void*>(0x145c6f0),8);if(!p)new(reinterpret_cast<void*>(0x145c6f0))std::wstring;}
bool directory(const std::wstring&path){word(40);cap->addText(path);return current->profile&1;}
void copy(const std::wstring&a,const std::wstring&b){word(41);cap->addText(a);cap->addText(b);}
std::wstring app(){return L"application/";}std::wstring appdata(){return L"user/данные/";}
void mouse(CPOV*p,void*w,float delta){word(1);word(p==pov);word(w==game->m_windowHandle);real(delta);p->m_viewAxis120=.5f+float(current->profile%3);p->m_fUnknown124=-.25f;p->m_viewAxis128=1.25f;}
void deactivate(CPOV*p){word(2);word(p==pov);word(p->m_bUnknown148);word(p->m_bUnknown149);word(p->m_bUnknown14A);word(p->m_bUnknown14B);word(p->m_bUnknown14C);word(p->m_bUnknown14D);}
short key(unsigned value){word(3);word(value);if(current->op==0){unsigned group=99,which=0;const unsigned first[]={4,3,5,6,0x22,0x21},second[]={10,9,11,12,2,1},third[]={0,0,0,0,8,7};for(unsigned i=0;i<6;++i){if(value==first[i]){group=i;which=1;}if(value==second[i]){group=i;which=2;}if(value==third[i]&&third[i]){group=i;which=3;}}if(group!=99){unsigned choice=(current->profile/4+group)%4;return choice==which?short(0x8000|value):short(current->profile&1?1:0);}return 0;}return value==0x52&&(current->profile&16)?short(0x8000):0;}
void updatePov(CPOV*p,float elapsed,float scale){word(4);word(p==pov);real(elapsed);real(scale);real(p->m_fUnknownD8);real(p->m_fUnknownDC);real(p->m_fUnknownE0);p->m_fUnknownD8+=.25f;p->m_fUnknownDC-=.5f;p->m_fUnknownE0+=.75f;}
void resetPov(CPOV*p,bool reset,float pitch,float yaw){word(5);word(p==pov);word(reset);real(pitch);real(yaw);}
void updateEditor(CEditor*p,float elapsed){word(6);word(p==editor);real(elapsed);if(current->op==1&&(current->profile&16)){typedef void(*F)(CEditor*,Ogre::Vector3);F f=oursSide?erNewReset:erOldReset;f(p,Ogre::Vector3(999,998,997));}}
void input(CEditor*p,float elapsed){word(7);word(p==editor);real(elapsed);}
void particles(CEditor*p,float elapsed,float height){word(8);word(p==editor);real(elapsed);real(height);real(p->m_fParticleMovementB);}
void resetCamera(CEditor*p,Ogre::Vector3 position){word(9);word(p==editor);vec(position);}
void managerUpdate(CEditorObjectManager*p,float elapsed){word(10);word(p==manager);real(elapsed);if(current->profile&32)gEditor->m_iFlags^=2;}
Ogre::Vector3 pivot(CEditorObjectManager*p){word(11);word(p==manager);return Ogre::Vector3(float(current->profile)+2,-3.5f,4.25f);}
struct Scene:CEditorScene{unsigned id;Scene(unsigned n):CEditorScene(L"runtime scene"),id(n){}void update(float elapsed){word(12);word(id);real(elapsed);}};
void levelUpdate(CLevel*p,Ogre::Camera*c,const Ogre::Vector3&v,float elapsed,float scale,CPlayer*player){word(13);word(p==level);word(c==camera);vec(v);real(elapsed);real(scale);word(player==NULL);}
void layouts(CLevel*p,float elapsed){word(14);word(p==level);real(elapsed);}void animation(CLevel*p,float elapsed,float scale,CPlayer*player){word(15);word(p==level);real(elapsed);real(scale);word(player==NULL);}
void items(CLevel*p,Ogre::Camera*c,const Ogre::Vector3&v,float elapsed){word(16);word(p==level);word(c==camera);vec(v);real(elapsed);}void updatedObjects(CLevel*p,Ogre::Camera*c,const Ogre::Vector3&v,float elapsed){word(17);word(p==level);word(c==camera);vec(v);real(elapsed);}
void closeAll(CGameUI*p){word(18);word(p==ui);}void closeCinematic(CGameUI*p){word(19);word(p==ui);}void closeLeft(CGameUI*p){word(20);word(p==ui);}void closeRight(CGameUI*p){word(21);word(p==ui);}void closeMenus(CGameUI*p){word(22);word(p==ui);}void fps(CGameUI*p){word(23);word(p==ui);}
struct Layout:CLayoutScene {void setVisible(bool v){word(24);word(v);word(editor->m_iFlags);CSceneNodeObject::setVisible(v);}void setEnabled(bool v){word(25);word(v);word(editor->m_iFlags);CSceneNodeObject::setEnabled(v);}};
TArrayList<CEditorBaseObject*>*objects(CEditorScene*p,const std::wstring&name){word(26);word(p==layout);cap->addText(name);return list;}
int save(CEditorScene*p,std::wstring path,TArrayList<CEditorBaseObject*>*selected){word(27);word(p==layout);cap->addText(path);word(selected==NULL);return -1;}
void clear(CEditorScene*p){word(28);word(p==layout);}
void refresh(CGameClient*p){word(29);word(p==client);}bool unload(CGameClient*p,bool value){word(30);word(p==client);word(value);return false;}
void load(CGameClient*p,std::wstring dungeon,std::wstring rules,bool flag,int depth,ELevelEntryType entry,std::wstring start){word(31);word(p==client);cap->addText(dungeon);cap->addText(rules);word(flag);word(depth);word(entry);cap->addText(start);word(p->m_gameSeed);}
void projector(CLevel*p,CGenericModel*a,CGenericModel*b){word(32);word(p==level);word(a==NULL);word(b==NULL);}
int randomValue(int a,int b){word(33);word(a);word(b);return 1009+current->profile;}
void location(CMasterResourceManager*p,const std::wstring&path,const std::string&group,bool reload){word(34);word(p==services->master);cap->addText(path);cap->addText(group);word(reload);}
void groupUnload(Ogre::ResourceGroupManager*,const std::string&group,bool reload){word(35);cap->addText(group);word(reload);}
void questReset(CQuestManager*p,bool v){word(36);word(p==quests);word(v);}
long long questFind(CQuestManager*p,const std::wstring&name){word(37);word(p==quests);cap->addText(name);if(name==L"missing")return 0;unsigned i=name==L"accepted"?0:name==L"active"?1:2;return reinterpret_cast<uintptr_t>(questValues[i]);}
long long questGive(CQuestManager*p,CQuest*q,CBaseUnit*unit,bool v){word(38);word(p==quests);word(q==questValues[1]);word(unit==NULL);word(v);q->m_questAccepted=true;return 0;}
long long questComplete(CQuestManager*p,CQuest*q){word(39);word(p==quests);word(q==questValues[2]);return 0;}void questAccept(CQuest*q,bool v){word(42);word(q==questValues[1]);word(v);}
void recreate(CEditor*p,unsigned i){word(43);word(p==editor);word(i);word(p->m_pUnknown128!=NULL);}
bool dump(CEditor*p,const std::wstring&path){word(44);word(p==editor);cap->addText(path);return current->profile&1;}
void initControls(CObjectControl3D*p){word(45);word(p->m_resources!=NULL);word(p->m_controlsNode!=NULL);}
Ogre::Entity*entity(Ogre::SceneManager*p,const std::wstring&name,OGRE_UTILITIES::EQUERYMASK mask,const char*text){word(46);word(p==services->scene);cap->addText(name);word(mask);cap->addText(std::string(text));return grid;}
class Window:public Ogre::RenderWindow{public:Window(){mWidth=640;mHeight=480;}void create(const Ogre::String&,unsigned,unsigned,bool,const Ogre::NameValuePairList*){std::abort();}void destroy(){}void resize(unsigned w,unsigned h){mWidth=w;mHeight=h;}void reposition(int,int){std::abort();}bool isClosed()const{return false;}void copyContentsToMemory(const Ogre::PixelBox&,Ogre::RenderTarget::FrameBuffer){std::abort();}bool requiresTextureFlipping()const{return false;}};
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);current=&c;oursSide=ours;cap=&out;signal(SIGSEGV,fault);signal(SIGABRT,fault);strings();client=NULL;ui=NULL;level=NULL;quests=NULL;grid=NULL;layout=NULL;
 nativeeditor::Controls*controls=NULL;
 if(c.op==5){SystemsNativeGame*n=new SystemsNativeGame(Ogre::Root::getSingletonPtr(),services->settings);game=n->game;editor=static_cast<CEditor*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEditor),0,0,0));{detour::Set d;TL_REDIRECT(d,erDirectory,directory);TL_REDIRECT(d,erCopy,copy);if(d.failed())std::abort();nativeeditor::editorCtor(editor);}gEditor=editor;manager=NULL;}
 else {controls=new nativeeditor::Controls(*services);editor=controls->editor;game=controls->game.game;manager=controls->manager;}
 game->m_sceneManager=services->scene;game->m_soundManager=services->master->m_pSoundManager;
 services->master->m_pParticleSystemManager->m_paused=bool(c.profile&1);services->master->m_pParticleSystemManager->m_particleFalloff=123.25f+c.profile;services->master->m_pParticleSystemManager->m_cameraPosition=Ogre::Vector3(c.profile+1,-2.25f,3.5f);
 {menugui::ProjectionDuringConstruction boundary;char name[50];std::sprintf(name,"editor-camera-%u",c.profile);camera=services->scene->createCamera(name);}camera->setPosition(float(c.profile)*.125f,-2,3.5f);
 game->m_cameraControl=new CCameraControl(camera,camera,camera,camera,camera);
 pov=c.op==5?NULL:new CPOV(*services->settings);editor->m_pCameraController=pov;if(pov){pov->m_fUnknownD8=float(c.profile)+.5f;pov->m_fUnknownDC=-3.25f;pov->m_fUnknownE0=7.5f;pov->m_viewAxis120=1;pov->m_fUnknown124=0;pov->m_viewAxis128=0;pov->m_bUnknown148=pov->m_bUnknown149=pov->m_bUnknown14A=pov->m_bUnknown14B=pov->m_bUnknown14C=pov->m_bUnknown14D=true;}
 editor->m_pUnknown88=c.op==5?NULL:camera;for(unsigned i=0;i<6;++i)editor->m_iUnknown98[i]=float(c.profile+i)*.25f;editor->m_fParticleMovementB=8.5f;editor->m_iMouseWheelDelta=int(c.profile/12%3)-1;
 if(SDL_VideoInit("dummy"))std::abort();SDL_Window*sdl=SDL_CreateWindow("editor native comparisons",0,0,320+int(c.profile)*2,240+int(c.profile)*2,8);if(!sdl)std::abort();game->m_windowHandle=reinterpret_cast<void*>(static_cast<size_t>(SDL_GetWindowID(sdl)));
 CSettings*settings=services->settings;
 if(c.op==0){for(unsigned i=0;i<14;++i){std::wstring keyName=L"test-binding-";keyName+=wchar_t(L'A'+i);editor->m_keyPropertyIndices[i]=settings->GetIntPropertyIndex(keyName,i+1,false);}if(c.profile%4==0)editor->m_pEditorResourceManager=NULL;if(c.profile%4==1)editor->m_bRenderWindowHasFocus=false;if(c.profile%4==2)editor->m_pCameraController=NULL;}
 if(c.op==1){if(c.profile%4==0)editor->m_pUnknown88=NULL;if(c.profile%4==1)editor->m_pCameraController=NULL;}
 TArrayList<CEditorBaseObject*> selectedObjects;
 if(c.op==2){editor->m_bUnknown4A=c.profile%8!=0;if(c.profile%8==1)editor->m_pSettings=NULL;editor->m_iFlags=c.profile&1?2:0;if(c.profile&4)editor->m_iFlags|=1u<<15;editor->m_bRenderWindowHasFocus=!(c.profile&8);if(c.profile%8==2)editor->m_pCameraController=NULL;for(unsigned i=0;i<3;++i)editor->m_EditorScenes.add((i+c.profile)%3?new Scene(i):NULL);if(c.profile&16){CEditorBaseObject*object=new CEditorBaseObject;manager->getSelectedObjects()->add(object);}if(c.profile&8){level=new CLevel(L"update",settings,NULL,controls->resources,services->scene,NULL,0,0);editor->m_pUnknown168=level;}if(c.profile&4){menugui::Client*n=new menugui::Client(*settings,services->master,*services->master->m_pSoundManager);client=n->client;controls->resources->getGameClients()->add(client);}settings->SetFloat(KSETTINGS_F_PARTICLE_FALLOFF,float(c.profile)*7.25f-10);}
 if(c.op==3||c.op==4){menugui::Fixture*f=new menugui::Fixture(*settings,services->scene);client=f->nativeClient.client;ui=f->ui;quests=client->m_questManager;game->m_gameClient=client;client->m_pGameUI=c.profile&1?ui:NULL;editor->m_iFlags=c.profile&2?0xffff:0;editor->m_iLevelDepth=int(c.profile)-17;editor->m_bRenderWindowHasFocus=c.profile&4;editor->m_bUnknown4B=c.profile&8;editor->m_bUseTempStartPos=true;for(unsigned i=0;i<3;++i)editor->m_iUnknown78[i]=float(c.profile+i)*-2.25f;layout=new Layout;editor->m_EditorScenes.add(layout);editor->m_EditorSceneIDs[L"Layout"]=0;list=&selectedObjects;CEditorBaseObject*base=new CEditorBaseObject;if(c.profile%6>=1)list->add(NULL);if(c.profile%6>=2)list->add(base);if(c.profile%6>=3){CRoomPiece*piece=new CRoomPiece(controls->resources);piece->CSceneNodeObject::setEnabled(c.profile%6>=5);piece->CSceneNodeObject::setVisible(c.profile%6>=4);list->add(piece);}if(c.profile&16){level=new CLevel(L"flags",settings,client,controls->resources,services->scene,NULL,0,0);client->m_level=level;}for(unsigned i=0;i<3;++i){questValues[i]=new CQuest(controls->resources,quests);questValues[i]->m_questAccepted=i==0;}const wchar_t*names[]={L"missing",L"accepted",L"active"};for(unsigned i=0;i<c.profile%4;++i)editor->m_ActiveQuests.add(names[i]);if(c.profile&8){editor->m_CompletedQuests.add(L"missing");editor->m_CompletedQuests.add(L"completed");}}
 if((c.op==3||c.op==4)&&c.profile>=80){switch(c.profile%8){case 0:editor->m_pEditorResourceManager=NULL;break;case 1:game->m_gameClient=NULL;break;case 2:if(c.op==3)editor->m_EditorScenes[0]=NULL;break;case 3:if(c.op==3)list=NULL;break;}}
 Window*window=NULL;Ogre::Viewport*viewport=NULL;
 if(c.op==5){window=new Window;viewport=window->addViewport(c.profile%8==2?NULL:camera);if(c.profile%8==1)editor->m_bUnknown4A=true;if(c.profile%8==3)game->m_settings=NULL;if(c.profile%8==4)game->m_sceneManager=NULL;services->master->m_pDefaultSceneManager=services->scene;Ogre::MeshPtr mesh=Ogre::MeshManager::getSingleton().createManual("editor-grid","General");mesh->_setBounds(Ogre::AxisAlignedBox(Ogre::Vector3(-1,-1,-1),Ogre::Vector3(1,1,1)),false);grid=services->scene->createEntity("editor-grid-entity",mesh->getName());Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("Wireframe","General");material->removeAllTechniques();}
 out.length=0;detour::Set d;CharacterLibraryBoundary unloadGroup(characterLibraryEntry("libOgreMain-1.6.5.so","_ZN4Ogre20ResourceGroupManager19unloadResourceGroupERKSsb"),groupUnload);
 if(c.op==0||c.op==1){TL_REDIRECT(d,erMouse,mouse);TL_REDIRECT(d,erDeactivate,deactivate);}TL_REDIRECT(d,erAsyncKey,key);
 if(c.op==1||c.op==3||c.op==4||c.op==5){TL_REDIRECT(d,erEditorUpdate,updateEditor);TL_REDIRECT(d,erPovUpdate,updatePov);}
 if(c.op==1){TL_REDIRECT(d,erResetPov,resetPov);}
 if(c.op==2){TL_REDIRECT(d,erEditorInput,input);TL_REDIRECT(d,erParticles,particles);TL_REDIRECT(d,erResetCamera,resetCamera);TL_REDIRECT(d,erPovUpdate,updatePov);TL_REDIRECT(d,erManagerUpdate,managerUpdate);TL_REDIRECT(d,erPivot,pivot);TL_REDIRECT(d,erLevelUpdate,levelUpdate);TL_REDIRECT(d,erLayouts,layouts);TL_REDIRECT(d,erAnimation,animation);TL_REDIRECT(d,erItems,items);TL_REDIRECT(d,erObjectsUpdate,updatedObjects);}
 if(c.op==3||c.op==4){TL_REDIRECT(d,erParticles,particles);TL_REDIRECT(d,erCloseAll,closeAll);TL_REDIRECT(d,erCloseCinematic,closeCinematic);TL_REDIRECT(d,erCloseLeft,closeLeft);TL_REDIRECT(d,erCloseRight,closeRight);TL_REDIRECT(d,erCloseMenus,closeMenus);TL_REDIRECT(d,erFps,fps);TL_REDIRECT(d,erObjects,objects);TL_REDIRECT(d,erSceneSave,save);TL_REDIRECT(d,erClearObjects,clear);TL_REDIRECT(d,erRefresh,refresh);TL_REDIRECT(d,erUnload,unload);TL_REDIRECT(d,erLoad,load);TL_REDIRECT(d,erProjector,projector);TL_REDIRECT(d,erRandom,randomValue);TL_REDIRECT(d,erQuestReset,questReset);TL_REDIRECT(d,erQuestFind,questFind);TL_REDIRECT(d,erQuestGive,questGive);TL_REDIRECT(d,erQuestComplete,questComplete);TL_REDIRECT(d,erQuestAccept,questAccept);TL_REDIRECT(d,erLocation,location);TL_REDIRECT(d,erDirectory,directory);TL_REDIRECT(d,erCopy,copy);TL_REDIRECT(d,erAppPath,app);TL_REDIRECT(d,erAppData,appdata);}
 if(c.op==5){TL_REDIRECT(d,erResetCamera,resetCamera);TL_REDIRECT(d,erRecreate,recreate);TL_REDIRECT(d,erDump,dump);TL_REDIRECT(d,erInitControls,initControls);TL_REDIRECT(d,erCreateEntity,entity);TL_REDIRECT(d,erAppData,appdata);}
 if(d.failed()||unloadGroup.failed())std::abort();
 const float deltas[]={0,.016f,.25f,-.125f,1,5};float delta=deltas[c.profile%6];
 if(c.op==0){typedef void(*F)(CEditor*,float);F f=ours?erNewInput:erOldInput;if(autotest::beginInvocation(out,f)){f(editor,delta);out.callCompleted=1;}}
 else if(c.op==1){typedef void(*F)(CEditor*,Ogre::Vector3);F f=ours?erNewReset:erOldReset;if(autotest::beginInvocation(out,f)){f(editor,Ogre::Vector3(float(c.profile)*.125f,-5.25f,7.75f));editor->m_pUnknown88=camera;editor->m_pCameraController=pov;f(editor,Ogre::Vector3(21,22,23));out.callCompleted=1;}}
 else if(c.op==2){typedef void(*F)(CEditor*,float);F f=ours?erNewUpdate:erOldUpdate;if(autotest::beginInvocation(out,f)){f(editor,delta);out.callCompleted=1;}}
 else if(c.op==3||c.op==4){const EEDITOR_FLAGS values[]={EDITOR_FLAG_INGAME_MODE,EDITOR_FLAG_SHOW_STATS,EDITOR_FLAG_UPDATE_PARTICLES_CIRCLE,EDITOR_FLAG_LOGIC_ENABLED,EDITOR_FLAG_SHOW_GRID,EDITOR_FLAG_COUNT};EEDITOR_FLAGS flag=c.profile>=48?EDITOR_FLAG_INGAME_MODE:values[c.profile/8%6];typedef void(*F)(CEditor*,EEDITOR_FLAGS);F f=c.op==3?(ours?erNewSet:erOldSet):(ours?erNewRemove:erOldRemove);if(autotest::beginInvocation(out,f)){f(editor,flag);out.callCompleted=1;}}
 else {typedef void(*F)(CEditor*,iEditorResourceManager*,Ogre::Viewport*);F f=ours?erNewInit:erOldInit;if(autotest::beginInvocation(out,f)){f(editor,c.profile%8==0?NULL:static_cast<iEditorResourceManager*>(game),viewport);out.callCompleted=1;}}
 if(ours&&c.negative)editor->m_iMouseWheelDelta^=1;
 word(editor->m_iFlags);word(editor->m_iMouseWheelDelta);word(editor->m_bRenderWindowHasFocus);word(editor->m_bUnknown4A);word(editor->m_bUnknown4B);word(editor->m_bUseTempStartPos);real(editor->m_fParticleMovementB);if(pov){real(pov->m_fUnknownD8);real(pov->m_fUnknownDC);real(pov->m_fUnknownE0);word(pov->m_bUnknown148);word(pov->m_bUnknown149);word(pov->m_bUnknown14A);word(pov->m_bUnknown14B);word(pov->m_bUnknown14C);word(pov->m_bUnknown14D);word(pov->m_bUnknown178);}vec(camera->getPosition());out.add(&camera->getOrientation(),16);real(camera->getNearClipDistance());real(camera->getFarClipDistance());word(settings->GetInt(KSETTINGS_WIN_WIDTH));word(settings->GetInt(KSETTINGS_WIN_HEIGHT));real(services->master->m_pParticleSystemManager->m_particleFalloff);vec(services->master->m_pParticleSystemManager->m_cameraPosition);word(services->master->m_pParticleSystemManager->m_paused);if(client){word(client->m_gameSeed);vec(client->m_audioListenerPosition);}if(c.op==5){word(editor->m_pEditorResourceManager==static_cast<iEditorResourceManager*>(game));word(editor->m_pSettings==game->m_settings);word(editor->m_pUnknown90==viewport);word(editor->m_pUnknown88==camera);word(editor->m_pUnknown128!=NULL);word(editor->m_pObjectManager!=NULL);word(editor->m_pCameraController!=NULL);word(editor->m_pUnknownB0!=NULL);word(editor->m_pUnknown168!=NULL);if(editor->m_pUnknown168)word(editor->m_pUnknown128->getLevel()==editor->m_pUnknown168);word(editor->m_pUnknown130!=NULL);word(editor->m_pUnknown138==grid);if(editor->m_pUnknown130){vec(editor->m_pUnknown130->getScale());vec(editor->m_pUnknown130->getPosition());word(grid->getParentSceneNode()==editor->m_pUnknown130);}if(editor->m_pCameraController)for(unsigned i=0;i<14;++i)word(settings->GetInt(editor->m_keyPropertyIndices[i]));}
 d.restore();SDL_DestroyWindow(sdl);SDL_VideoQuit();
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uintptr_t address,unsigned count){debugHost=host;tlheadless::Environment*env=NULL;if(op==3||op==4){env=new tlheadless::Environment;env->loadGameSkin();}nativegame::Services native;services=&native;menugui::Audio audio(services->master);int failures=0;autotest::Coverage cov(name,address);for(unsigned i=0;i<count;++i){Case c={op,i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a,1500,10000);autotest::runChild(after,&c,b,1500,10000);int bad=cov.observe(host,a,b);TL_CHECK(failures,!bad);if(bad){host->log("    Editor runtime op%u profile%u status%d/%d issue%u/%u bytes%lu/%lu\n",op,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first difference%u values%u/%u\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}for(unsigned j=0;j<a.capture.length&&j<b.capture.length;j+=4){unsigned av=0,bv=0;std::memcpy(&av,a.capture.data+j,std::min(4u,unsigned(a.capture.length-j)));std::memcpy(&bv,b.capture.data+j,std::min(4u,unsigned(b.capture.length-j)));if(av!=bv)host->log("    word%u %08x/%08x\n",j,av,bv);}cov.report(host);return failures;}}cov.report(host);Case c={op,7,1};autotest::Outcome a,b;autotest::runChild(before,&c,a,1500,10000);autotest::runChild(after,&c,b,1500,10000);bool detected=a.capture.length!=b.capture.length||memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,detected&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    Editor runtime negative op%u detected%u\n",op,unsigned(detected));return failures;}
int inputWorker(const tlhybrid_host*h){return run(h,0,"editor_complete_input",0x70d980,96);}int resetWorker(const tlhybrid_host*h){return run(h,1,"editor_complete_reset",0x71c4a0,32);}int updateWorker(const tlhybrid_host*h){return run(h,2,"editor_complete_update",0x71b8a0,64);}int setWorker(const tlhybrid_host*h){return run(h,3,"editor_complete_set",0x71a120,88);}int removeWorker(const tlhybrid_host*h){return run(h,4,"editor_complete_remove",0x71bd70,88);}int initWorker(const tlhybrid_host*h){return run(h,5,"editor_complete_init",0x71c650,32);}
}
TL_TEST(editor_complete_input){return systems_fixture::isolated(inputWorker,host);}
TL_TEST(editor_complete_reset){return systems_fixture::isolated(resetWorker,host);}
TL_TEST(editor_complete_update){return systems_fixture::isolated(updateWorker,host);}
TL_TEST(editor_complete_set){return systems_fixture::isolated(setWorker,host);}
TL_TEST(editor_complete_remove){return systems_fixture::isolated(removeWorker,host);}
TL_TEST(editor_complete_init){return systems_fixture::isolated(initWorker,host);}
