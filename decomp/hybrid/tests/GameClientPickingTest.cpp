#include "tests/FinishLevelFixture.h"
#include "tests/MenuGuiFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "LinuxUtils.h"
#include <OgreCamera.h>
#include "tests/GameCpuRenderer.h"
TL_ORIGINAL(bool,gcpWorldOld,(CGameClient*,Ogre::Vector3&,bool),"_ZN11CGameClient17findWorldLocationERN4Ogre7Vector3Eb")
TL_ORIGINAL(void,gcpHoverOld,(CGameClient*),"_ZN11CGameClient18mouseOverCharacterEv")
extern "C" bool gcpWorldNew(CGameClient*,Ogre::Vector3&,bool) __asm__("_ZN11CGameClient17findWorldLocationERN4Ogre7Vector3Eb");
extern "C" void gcpHoverNew(CGameClient*) __asm__("_ZN11CGameClient18mouseOverCharacterEv");
TL_FUNCTION(gcpCursor,"_Z12GetCursorPosP5POINT")
TL_FUNCTION(gcpKey,"_Z16GetAsyncKeyStatej")
TL_FUNCTION(gcpMouse,"_ZN11CGameClient10mouseEventEjj")
TL_FUNCTION(gcpPanel,"_ZN7CGameUI14mouseOverPanelEii")
TL_FUNCTION(gcpRight,"_ZN7CGameUI12rightCoveredEv")
TL_FUNCTION(gcpLeft,"_ZN7CGameUI11leftCoveredEv")
TL_FUNCTION(gcpRightEdge,"_ZN7CGameUI15rightScreenEdgeEv")
TL_FUNCTION(gcpLeftEdge,"_ZN7CGameUI14leftScreenEdgeEv")
TL_FUNCTION(gcpRay,"_ZN6CLevel12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_RjS4_b")
TL_FUNCTION(gcpChar,"_ZN6CLevel32findCharacterAtScreenCoordinatesERKN4Ogre7Matrix4ES3_ffP10CCharacter")
TL_FUNCTION(gcpItem,"_ZN6CLevel27findItemAtScreenCoordinatesERKN4Ogre7Matrix4ES3_ff")
namespace {
#include "tests/CharacterEmptyGlobals.h"
CGameClient*client;CGameUI*ui;CLevel*level;CPlayer*player;CPlayer*hover;CItem*item;unsigned seed,rayCalls,op;autotest::Capture*cap;
void num(unsigned n){cap->add(&n,4);}void fp(float f){cap->add(&f,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void matrix(const Ogre::Matrix4&m){for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j)fp(m[i][j]);}
int cursor(POINT*p){num(101);const long xs[]={-200,0,127,512,1024,1350,2000};const long ys[]={-10,0,100,384,768,900};p->x=xs[seed%7];p->y=ys[seed/7%6];return 1;}
short key(unsigned n){num(103);num(n);return ((seed>>n)&1)?short(-32768):0;}
void mouse(CGameClient*p,unsigned event,unsigned value){num(107);num(p==client);num(event);num(value);}
bool panel(CGameUI*p,int x,int y){num(109);num(p==ui);num(x);num(y);return seed%5==1;}
bool right(CGameUI*p){num(113);num(p==ui);return seed/7%3==1;}
bool left(CGameUI*p){num(127);num(p==ui);return seed/7%3==2;}
float rightEdge(CGameUI*p){num(131);num(p==ui);return seed&1?768:1024;}
float leftEdge(CGameUI*p){num(137);num(p==ui);return seed&1?256:512;}
bool ray(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,Ogre::Vector3&hit,Ogre::Vector3&normal,unsigned&index,Ogre::Vector3&other,bool flag){num(139);num(p==level);vec(a);vec(b);num(flag);unsigned n=rayCalls++;num(n);index=seed/3%5==1?100:17;other=Ogre::Vector3(7,-2,9);
 if(!n){hit=a+Ogre::Vector3(seed/9%2?10.001f:10,0,0);normal=Ogre::Vector3(0,1,0);}else{const float heights[]={-14,-13.999f,0,13.999f,14};hit=Ogre::Vector3(3,player->m_lastWorldPosition[1]+heights[seed/11%5],-5);normal=Ogre::Vector3(0,seed/5%2?.201f:.2f,0);}return seed/2%5!=n;
}
CCharacter*pickChar(CLevel*p,const Ogre::Matrix4&view,const Ogre::Matrix4&projection,float x,float y,CCharacter*c){num(149);num(p==level);matrix(view);matrix(projection);fp(x);fp(y);num(c==player);return seed%4?hover:NULL;}
CItem*pickItem(CLevel*p,const Ogre::Matrix4&view,const Ogre::Matrix4&projection,float x,float y){num(151);num(p==level);matrix(view);matrix(projection);fp(x);fp(y);return seed&1?item:NULL;}
struct PickingRenderer:Ogre::GameCpuRenderer {
 void _convertProjectionMatrix(const Ogre::Matrix4&input,Ogre::Matrix4&output,bool gpu){num(157);num(gpu);matrix(input);output=input;}
 Ogre::Real getMinimumDepthInputValue(){return -1;}
 Ogre::Real getMaximumDepthInputValue(){return 1;}
};
struct Case{unsigned seed;};
void side(void*raw,autotest::Capture&out,bool ours){seed=static_cast<Case*>(raw)->seed;cap=&out;rayCalls=0;client->m_width=seed&1?1024:1920;client->m_height=seed&2?768:1080;client->m_leftHeld=seed&1;client->m_rightHeld=seed&2;
 client->m_pPlayer=player;client->m_level=level;client->m_gameResources->m_pLevel=level;client->m_pGameUI=ui;client->m_targetCharacter.setObject(hover);client->m_targetItem.setObject(item);player->m_lastWorldPosition[0]=seed*.125f;player->m_lastWorldPosition[1]=float(int(seed%13)-6);player->m_lastWorldPosition[2]=-seed*.25f;player->m_isPathing=seed%4==2;hover->m_bVisible=seed%4!=1;hover->m_bEnabled=seed%4!=2;
 PickingRenderer renderer;Ogre::Root::getSingleton().setRenderSystem(&renderer);
 Ogre::Camera*camera=client->m_cameraControl->m_pUnknown10;camera->setPosition(float(seed%5)-2,20,float(seed%9)-4);camera->lookAt(0,0,0);camera->setNearClipDistance(.1f);camera->setFarClipDistance(1000);Ogre::Matrix4 projection=Ogre::Matrix4::IDENTITY;projection[0][0]=1.2f;projection[1][1]=1.6f;projection[2][2]=-1;projection[3][2]=-1;projection[3][3]=0;camera->setCustomProjectionMatrix(true,projection);
 detour::Set hooks;TL_REDIRECT(hooks,gcpCursor,&cursor);TL_REDIRECT(hooks,gcpKey,&key);TL_REDIRECT(hooks,gcpMouse,&mouse);TL_REDIRECT(hooks,gcpPanel,&panel);TL_REDIRECT(hooks,gcpRight,&right);TL_REDIRECT(hooks,gcpLeft,&left);TL_REDIRECT(hooks,gcpRightEdge,&rightEdge);TL_REDIRECT(hooks,gcpLeftEdge,&leftEdge);TL_REDIRECT(hooks,gcpRay,&ray);TL_REDIRECT(hooks,gcpChar,&pickChar);TL_REDIRECT(hooks,gcpItem,&pickItem);if(hooks.failed())_exit(64);
 if(!op){Ogre::Vector3 result(-97,13,41);typedef bool(*F)(CGameClient*,Ogre::Vector3&,bool);F fn=ours?gcpWorldNew:gcpWorldOld;if(autotest::beginInvocation(out,fn)){num(fn(client,result,(seed&4)!=0));out.callCompleted=1;}vec(result);num(rayCalls);}else{typedef void(*F)(CGameClient*);F fn=ours?gcpHoverNew:gcpHoverOld;autotest::invoke(out,fn,client);}
 num(client->m_targetCharacter.getObject()==hover);num(client->m_targetItem.getObject()==item);Ogre::Root::getSingleton().setRenderSystem(NULL);
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
const char*testName;uintptr_t address;unsigned count;
int worker(const tlhybrid_host*host){initEmptyGlobals();tlheadless::Environment env;env.loadGameSkin();nativegame::Services native;if(!native.ready())return 1;menugui::Audio audio(native.master);menugui::Fixture menu(*native.settings,native.scene);finishlevel::Fixture world;client=menu.nativeClient.client;ui=menu.ui;level=&world.level;player=nativegame::createPlayer(client->m_gameResources);hover=nativegame::createPlayer(client->m_gameResources);item=new finishlevel::Item(client->m_gameResources);native.settings->SetInt(KSETTINGS_RES_WIDTH,1024);native.settings->SetInt(KSETTINGS_RES_HEIGHT,768);
 autotest::Stats stats={0,0,0};autotest::Coverage coverage(testName,address);int failures=0;for(unsigned i=0;i<count;++i){Case c={i};bool ok=autotest::compareCase(before,after,&c,stats,host,testName,i,&coverage);TL_CHECK(failures,ok);if(!ok)break;}coverage.report(host);delete item;nativegame::destroyPlayer(hover);nativegame::destroyPlayer(player);return failures+stats.incomplete+(coverage.completed!=count);}
int run(const tlhybrid_host*h,unsigned operation,const char*name,uintptr_t a,unsigned n){op=operation;testName=name;address=a;count=n;return systems_fixture::isolated(&worker,h);}
}
TL_TEST(gameclient_world){return run(host,0,"gameclient_world",(uintptr_t)gcpWorldOld,420);}
TL_TEST(gameclient_hover){return run(host,1,"gameclient_hover",(uintptr_t)gcpHoverOld,168);}
