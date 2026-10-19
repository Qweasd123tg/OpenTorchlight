#include "tests/FinishLevelFixture.h"
#include "NativeMenuClient.h"
#include "tests/SystemsFixtureWorker.h"
#include "SettingsVariables.h"
#include "Hierarchy.h"
#include <OgreColourValue.h>
TL_ORIGINAL(CItem*,aiOld,(CLevel*,CItem*,const Ogre::Vector3&,bool),"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
extern "C" CItem*aiNew(CLevel*,CItem*,const Ogre::Vector3&,bool) __asm__("_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb");
TL_ORIGINAL(void,aiModelCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,aiModelDtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
TL_FUNCTION(aiPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(aiActivate,"_ZN9CBaseUnit19activateUnitInLevelEv")
TL_FUNCTION(aiOpacity,"_ZN5CItem13updateOpacityEfb")
TL_FUNCTION(aiRoom,"_ZN6CLevel28getRoomIndexThatPositionIsInERKN4Ogre7Vector3E")
TL_FUNCTION(aiDropSound,"_ZN9CItemGold13playDropSoundEPN4Ogre9SceneNodeE")
TL_FUNCTION(aiAmbient,"_ZN13CGenericModel10setAmbientERN4Ogre11ColourValueE")
TL_FUNCTION(aiProjector,"_ZN13CGenericModel16setProjectorPassEPN4Ogre7FrustumES2_RKSsS4_")
TL_FUNCTION(aiGoldModel,"_ZN9CItemGold9loadModelESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(aiGoldParticle,"_ZN16CResourceManager14createParticleEPKw")
TL_FUNCTION(aiGoldRandom,"_ZN9UTILITIES21randomBetweenVolatileEff")
namespace {
autotest::Capture*output;unsigned seed;CItem*item;CLevel*level;CGenericModel*model;menugui::Client*client;CSettings*settings;
void number(unsigned x){output->add(&x,4);}void scalar(float x){output->add(&x,4);}void vector(const Ogre::Vector3&x){output->add(&x,sizeof x);}
void text(const std::wstring&s){number(s.size());if(s.size())output->add(s.data(),s.size()*sizeof(wchar_t));}
void text(const std::string&s){number(s.size());if(s.size())output->add(s.data(),s.size());}
void rim(CItem*p,std::wstring s){number(7);number(p==item);text(s);p->m_bLevelLighting=(seed/24)%2;}
void*unitModel(CItem*p){number(8);number(p==item);return model;}
struct Item:finishlevel::Item{Item(CResourceManager*r):finishlevel::Item(r){}virtual void setRimlight(std::wstring s){rim(this,s);}virtual void*getUnitModel(){return unitModel(this);}};
struct Equipment:CEquipment{Equipment(CResourceManager*r):CEquipment(r){}virtual void setRimlight(std::wstring s){rim(this,s);}virtual void*getUnitModel(){return unitModel(this);}virtual void drop(){number(5);number(this==item);}virtual void activateDropParticles(){number(6);number(this==item);}};
struct Gold:CItemGold{Gold(CResourceManager*r):CItemGold(r,19){}virtual void setRimlight(std::wstring s){rim(this,s);}virtual CGenericModel*getUnitModel(){return static_cast<CGenericModel*>(unitModel(this));}};
void goldModel(CItemGold*,std::wstring){}CParticle*goldParticle(CResourceManager*,const wchar_t*){return NULL;}float goldRandom(float a,float b){return a+(b-a)*.375f;}
void position(CPositionableObject*p,const Ogre::Vector3&v){number(1);number(p==item);vector(v);p->m_vPosition=v;}
void activate(CBaseUnit*p){number(2);number(p==item);vector(p->m_vPosition);}
void opacity(CItem*p,float t,bool force){number(3);number(p==item);scalar(t);number(force);scalar(p->m_fOpacity);p->m_fOpacity=.75f;}
int room(CLevel*p,const Ogre::Vector3&v){number(4);number(p==level);vector(v);return int(seed%9)-4;}
void dropSound(CItemGold*p,Ogre::SceneNode*n){number(9);number(p==item);number(n==item->getSceneNode());}
void ambient(CGenericModel*p,Ogre::ColourValue&c){number(10);number(p==model);scalar(c.r);scalar(c.g);scalar(c.b);scalar(c.a);}
void projector(CGenericModel*p,Ogre::Frustum*a,Ogre::Frustum*b,const std::string&c,const std::string&d){number(11);number(p==model);number(a==client->camera->m_pUnknown30);number(b==client->camera->m_pUnknown28);number(a!=b);text(c);text(d);}
void execute(void*raw,autotest::Capture&out,bool ours){
 output=&out;seed=*static_cast<unsigned*>(raw);finishlevel::Fixture f;level=&f.level;level->m_pGameClient=client->client;f.resources.m_pSceneManager=client->scenes[0];f.resources.m_pHierarchy=CMasterResourceManager::getSingleton()->m_pHierarchy;
 settings->SetInt(KSETTINGS_LIGHTING_ENABLED,int(seed/48%3));settings->SetInt(KSETTINGS_OVERRIDE_LIGHTING,int(seed/144%3)-1);
 settings->SetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_RED,int(seed%6)*77-40);settings->SetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_GREEN,int(seed%7)*53-20);settings->SetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_BLUE,int(seed%8)*39-10);
 client->client->m_projectorTexture=seed&1?"projector/a.dds":"";client->client->m_projectorFalloffTexture=seed&2?"falloff/b.dds":"falloff\0suffix";
 CStringTranslate translation(L"");
 detour::Set assets;TL_REDIRECT(assets,aiGoldModel,&goldModel);TL_REDIRECT(assets,aiGoldParticle,&goldParticle);TL_REDIRECT(assets,aiGoldRandom,&goldRandom);if(assets.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 unsigned kind=seed%3;item=kind==0?static_cast<CItem*>(new Item(&f.resources)):kind==1?static_cast<CItem*>(new Equipment(&f.resources)):static_cast<CItem*>(new Gold(&f.resources));
 model=static_cast<CGenericModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0));aiModelCtor(model,NULL,NULL,OGRE_UTILITIES::PRIMITIVE_SPHERE);
 item->m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>(kind==2?34:31);item->m_bLevelLighting=(seed/12)%2;item->m_vPosition=Ogre::Vector3(-3,7,-11);item->m_fOpacity=-.25f;item->m_iRoomIndex=-71;f.resources.m_bFlag3=(seed/3)%2;
 void*empty=NULL;std::memcpy(&empty,reinterpret_cast<void*>(0x1495cc8),8);if(!empty)new(reinterpret_cast<void*>(0x1495cc8))std::wstring;
 CLevelTemplateData data(NULL);data.m_sRimlightTexture=seed%5==0?L"":seed%5==1?L"rim/\x041b\x0435\x0441.dds":L"rim/texture.dds";
 data.m_materialAmbientColorR=float(seed%17)*.125f;data.m_materialAmbientColorG=float(seed%13)*-.25f;data.m_materialAmbientColorB=float(seed%11)*.0625f;data.m_materialAmbientColorA=float(seed%7)*.375f;level->m_pLevelTemplateData=seed/432%2?&data:NULL;
 for(unsigned i=0;i<seed%4;++i){finishlevel::prepend(level->m_items,static_cast<CItem*>(i%2?item:NULL));finishlevel::prepend(level->m_activeItems,static_cast<CItem*>(i%2?NULL:item));}
 detour::Set hooks;TL_REDIRECT(hooks,aiPosition,&position);TL_REDIRECT(hooks,aiActivate,&activate);TL_REDIRECT(hooks,aiOpacity,&opacity);TL_REDIRECT(hooks,aiRoom,&room);TL_REDIRECT(hooks,aiDropSound,&dropSound);TL_REDIRECT(hooks,aiAmbient,&ambient);TL_REDIRECT(hooks,aiProjector,&projector);
 if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef CItem*(*Fn)(CLevel*,CItem*,const Ogre::Vector3&,bool);Fn fn=ours?aiNew:aiOld;Ogre::Vector3 p(float(seed%17),float(seed%11)*.5f,float(seed%13)*-.25f);
 if(!autotest::beginInvocation(out,fn))return;CItem*result=fn(level,item,p,(seed/6)%2);out.callCompleted=1;
 number(result==item);number(item->m_iRoomIndex);scalar(item->m_fOpacity);number(item->m_bLevelLighting);vector(item->m_vPosition);
 std::vector<CItem*>ids;ids.push_back(item);finishlevel::listState(out,level->m_items,ids);finishlevel::listState(out,level->m_activeItems,ids);
 level->m_pLevelTemplateData=NULL;level->m_pGameClient=NULL;aiModelDtor(model);Ogre::NedAllocImpl::deallocBytes(model);delete item;
}
void original(void*p,autotest::Capture&o){execute(p,o,false);}void candidate(void*p,autotest::Capture&o){execute(p,o,true);}
int run(const tlhybrid_host*host){
 nativegame::Services services;if(!services.ready())return 1;CMasterResourceManager*master=CMasterResourceManager::getSingleton();settings=master->m_pSettings;menugui::Audio audio(master);menugui::Client native(*settings,master,*master->m_pSoundManager);client=&native;
 for(unsigned t=31;t<=34;t+=3){master->m_pHierarchy->m_parentTypes[t].clear();master->m_pHierarchy->m_parentTypes[t].push_back(t);}
 autotest::Coverage coverage("all_level_add_item",(uintptr_t)&aiOld);
 for(unsigned i=0;i<864;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    addItem seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);return 0;
}
}
TL_TEST(all_level_add_item){return systems_fixture::isolated(&run,host);}
