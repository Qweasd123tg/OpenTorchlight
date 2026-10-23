#include "tests/FinishLevelFixture.h"
#include "tests/NativeMenuServices.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/MenuGuiFixture.h"
#include "UtilitiesMath.h"
#include <limits>
TL_ORIGINAL(CCharacter*,lsCharacterOld,(CLevel*,const Ogre::Matrix4&,const Ogre::Matrix4&,float,float,CCharacter*),"_ZN6CLevel32findCharacterAtScreenCoordinatesERKN4Ogre7Matrix4ES3_ffP10CCharacter")
TL_ORIGINAL(CItem*,lsItemOld,(CLevel*,const Ogre::Matrix4&,const Ogre::Matrix4&,float,float),"_ZN6CLevel27findItemAtScreenCoordinatesERKN4Ogre7Matrix4ES3_ff")
TL_ORIGINAL(void,lsOnscreenOld,(CLevel*,Ogre::Camera*),"_ZN6CLevel17findItemsOnscreenEPN4Ogre6CameraE")
extern "C" CCharacter*lsCharacterNew(CLevel*,const Ogre::Matrix4&,const Ogre::Matrix4&,float,float,CCharacter*) __asm__("_ZN6CLevel32findCharacterAtScreenCoordinatesERKN4Ogre7Matrix4ES3_ffP10CCharacter");
extern "C" CItem*lsItemNew(CLevel*,const Ogre::Matrix4&,const Ogre::Matrix4&,float,float) __asm__("_ZN6CLevel27findItemAtScreenCoordinatesERKN4Ogre7Matrix4ES3_ff");
extern "C" void lsOnscreenNew(CLevel*,Ogre::Camera*) __asm__("_ZN6CLevel17findItemsOnscreenEPN4Ogre6CameraE");
TL_FUNCTION(lsAlive,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(lsAlignment,"_ZN10CCharacter9alignmentEv")
TL_FUNCTION(lsISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(lsTheme,"_ZN9CBaseUnit12hasUnitThemeERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(lsPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(lsHideItem,"_ZN5CItem12hideItemTextEv")
TL_FUNCTION(lsHideActor,"_ZN10CCharacter17hideCharacterTextEv")
namespace {
autotest::Capture*output;Ogre::SceneManager*scene;CLevel*level;CCharacter*actors[5];CItem*items[5];unsigned seed,mode;
void word(unsigned n){output->add(&n,4);}void vec(const Ogre::Vector3&v){output->add(&v,sizeof v);}
unsigned id(const void*p){if(!p)return 0;for(unsigned i=0;i<5;++i){if(p==actors[i])return i+1;if(p==items[i])return i+11;}return 99;}
struct Actor:CCharacter{Ogre::Vector3 minimum,maximum;explicit Actor(CResourceManager*r):CCharacter(r){}virtual bool getEnabled(){word(1);word(id(this));word(m_bEnabled);return m_bEnabled;}virtual const Ogre::Vector3&getLocalMinBounds(){word(2);word(id(this));vec(minimum);return minimum;}virtual const Ogre::Vector3&getLocalMaxBounds(){word(3);word(id(this));vec(maximum);return maximum;}};
struct Item:finishlevel::Item{Ogre::Vector3 minimum,maximum;explicit Item(CResourceManager*r):finishlevel::Item(r){}virtual bool getEnabled(){word(1);word(id(this));word(m_bEnabled);return m_bEnabled;}virtual const Ogre::Vector3&getLocalMinBounds(){word(2);word(id(this));vec(minimum);return minimum;}virtual const Ogre::Vector3&getLocalMaxBounds(){word(3);word(id(this));vec(maximum);return maximum;}};
struct Camera:Ogre::Camera{Ogre::Matrix4 projection;explicit Camera(Ogre::SceneManager*s):Ogre::Camera("level-screen-camera",s),projection(Ogre::Matrix4::IDENTITY){}virtual const Ogre::Matrix4&getProjectionMatrix()const{word(4);return projection;}};
bool alive(CCharacter*p){word(5);unsigned n=id(p);word(n);bool v=mode==0||(seed/3+n)%5!=0;word(v);return v;}
EAlignment alignment(CCharacter*p){word(6);unsigned n=id(p);word(n);unsigned v=(seed/13+n)%5;word(v);return static_cast<EAlignment>(v);}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){word(7);unsigned n=id(p);word(n);word(t);bool v=mode==0||(seed/7+n)%3!=0;word(v);return v;}
bool theme(CBaseUnit*p,const std::wstring&s){word(8);unsigned n=id(p);word(n);word(s.size());if(!s.empty())output->add(s.data(),s.size()*4);bool v=mode==0||(seed/11+n)%4!=0;word(v);return v;}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){word(9);word(id(p));word(absolute);vec(p->m_vPosition);return p->m_vPosition;}
void hideItem(CItem*p){word(10);word(id(p));}
void hideActor(CCharacter*p){word(11);word(id(p));}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;mode=seed/512;finishlevel::Fixture f;level=&f.level;f.resources.m_pSceneManager=scene;CMasterResourceManager::getSingleton()->m_pSceneManager=scene;
 Actor*as[5];Item*is[5];for(unsigned i=0;i<5;++i){as[i]=new Actor(&f.resources);actors[i]=as[i];is[i]=new Item(&f.resources);items[i]=is[i];}
 const float extents[]={-.01f,-.25f,-.55f,-.8f,-1.2f,.15f,-3.f};
 for(unsigned i=0;i<5;++i){Actor*a=as[i];Item*b=is[i];Ogre::Vector3 p(float(int((seed/17+i)%11)-5)*.2f,float(int((seed/7+i)%9)-4)*.2f,.25f+float((seed+i)%9)*.375f);if(seed&64)p.z=-p.z;if(seed%47==0)p.x=std::numeric_limits<float>::quiet_NaN();if(seed%53==0)p.x=1.1000001f;
  a->m_vPosition=p;b->m_vPosition=p;a->m_lastWorldPosition[0]=p.x;a->m_lastWorldPosition[1]=p.y;a->m_lastWorldPosition[2]=p.z+.125f;
  a->minimum=Ogre::Vector3(extents[(seed/5+i)%7],-.15f,extents[(seed/9+i)%7]);a->maximum=Ogre::Vector3(.8f,.2f+float((seed/19+i)%5)*.5f,.6f);b->minimum=Ogre::Vector3(extents[(seed/3+i)%7],-.2f,extents[(seed/11+i)%7]);b->maximum=Ogre::Vector3(.6f,.3f+float((seed/23+i)%3)*.25f,.5f);
  a->m_bInActiveRange=mode==0||(seed/5+i)%5!=0;a->m_damageShapeEnabled=mode==0||(seed/7+i)%5!=0;a->m_bEnabled=mode==0||(seed/11+i)%4!=0;a->m_bVisible=mode==0||(seed/13+i)%4!=0;
  b->m_bInActiveRange=mode==0||(seed/17+i)%4!=0;b->m_bItemFlag1F0=mode==0||(seed/19+i)%4!=0;b->m_bNonSelectable=mode!=0&&(seed/23+i)%5==0;b->m_bVisible=mode==0||(seed/29+i)%4!=0;b->m_bEnabled=mode==0||(seed/31+i)%4!=0;
  a->m_pMaster=seed%7?actors[(seed/19+i)%5]:NULL;a->m_Followers.clear();if((seed+i)%3==0)a->m_Followers.push_back(actors[(seed/23+i+1)%5]);
 }
 for(unsigned i=0;i<seed%9;++i){finishlevel::prepend(level->m_activeCharacters,actors[(i+seed/9)%5]);finishlevel::prepend(level->m_activeItems,items[(i+seed/11)%5]);finishlevel::prepend(level->m_pendingItems,items[(i+seed/13)%5]);finishlevel::prepend(level->m_pendingCharacters,actors[(i+seed/17)%5]);}
 Ogre::Matrix4 view=Ogre::Matrix4::IDENTITY,projection=Ogre::Matrix4::IDENTITY;float phase=float(seed%7)*.05f,co=::cosf(phase),si=::sinf(phase);view[0][0]=co;view[0][2]=si;view[2][0]=-si;view[2][2]=co;view[0][3]=float(int(seed/3%5)-2)*.125f;view[1][3]=float(int(seed/5%5)-2)*.125f;
 projection[0][0]=.5f+float(seed/7%3)*.5f;projection[1][1]=.5f+float(seed/11%3)*.5f;projection[0][1]=seed&8?.125f:0;projection[2][3]=seed&16?.25f:0;if(seed&32){projection[3][2]=.25f;projection[3][0]=.03125f;}
 Camera*camera=NULL;if(c.op==2){menugui::ProjectionDuringConstruction setup;camera=new Camera(scene);camera->projection=projection;camera->setPosition(Ogre::Vector3(float(int(seed%5)-2)*.125f,float(seed%3)*.25f,float(seed%7)*-.125f));camera->setOrientation(Ogre::Quaternion(Ogre::Radian(phase),Ogre::Vector3::UNIT_Y));}
 TLinkedList<CItem*>*savedItems=level->m_pendingItems;TLinkedList<CCharacter*>*savedActors=level->m_pendingCharacters;if(c.op==2&&seed%29==0)level->m_pendingItems=NULL;if(c.op==2&&seed%31==0)level->m_pendingCharacters=NULL;
 detour::Set hooks;TL_REDIRECT(hooks,lsAlive,&alive);TL_REDIRECT(hooks,lsAlignment,&alignment);TL_REDIRECT(hooks,lsISA,&isa);TL_REDIRECT(hooks,lsTheme,&theme);TL_REDIRECT(hooks,lsPosition,&position);TL_REDIRECT(hooks,lsHideItem,&hideItem);TL_REDIRECT(hooks,lsHideActor,&hideActor);if(hooks.failed())std::abort();
 const float coords[]={0,-.25f,.25f,-.55f,.55f,-1,1,-1.1f,1.1f,.01f};float x=coords[seed/3%10],y=coords[seed/13%10];const void*result=NULL;
 if(c.op==0){typedef CCharacter*(*Fn)(CLevel*,const Ogre::Matrix4&,const Ogre::Matrix4&,float,float,CCharacter*);Fn fn=ours?lsCharacterNew:lsCharacterOld;if(!autotest::beginInvocation(out,fn))return;result=fn(level,view,projection,x,y,seed%5?actors[seed/23%5]:NULL);}
 else if(c.op==1){typedef CItem*(*Fn)(CLevel*,const Ogre::Matrix4&,const Ogre::Matrix4&,float,float);Fn fn=ours?lsItemNew:lsItemOld;if(!autotest::beginInvocation(out,fn))return;result=fn(level,view,projection,x,y);}
 else{typedef void(*Fn)(CLevel*,Ogre::Camera*);Fn fn=ours?lsOnscreenNew:lsOnscreenOld;if(!autotest::beginInvocation(out,fn))return;fn(level,camera);}
 out.callCompleted=1;word(id(result));std::vector<CItem*>itemIds;std::vector<CCharacter*>actorIds;for(unsigned i=0;i<5;++i){itemIds.push_back(items[i]);actorIds.push_back(actors[i]);}finishlevel::listState(out,level->m_pendingItems,itemIds);finishlevel::listState(out,level->m_pendingCharacters,actorIds);finishlevel::listState(out,level->m_activeItems,itemIds);finishlevel::listState(out,level->m_activeCharacters,actorIds);
 hooks.restore();level->m_pendingItems=savedItems;level->m_pendingCharacters=savedActors;for(unsigned i=0;i<5;++i){as[i]->m_Followers.clear();as[i]->m_pMaster=NULL;delete as[i];delete is[i];}delete camera;
}
int worker(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;scene=services.scene;menugui::Audio audio(CMasterResourceManager::getSingleton());const char*names[]={"level_screen_character","level_screen_item","level_screen_onscreen"};const unsigned addresses[]={0x94b440,0x94c730,0x94f730};for(unsigned i=0;i<3;++i)if(smallmass::run(host,i,names[i],addresses[i],&side,1024))return 1;return 0;}
}
TL_TEST(complete_level_screen){return systems_fixture::isolated(&worker,host,180);}
