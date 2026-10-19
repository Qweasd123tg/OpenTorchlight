#include "tests/FinishLevelFixture.h"
#include "tests/NativeMenuServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "SpawnClass.h"
#include "RandomNames.h"
#include "DataGroup.h"
#include "PropertyNode.h"
TL_ORIGINAL(int,psOld,(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,const std::wstring&,bool,bool),"_ZN6CLevel22populateSectionOfLevelERKN4Ogre7Vector3ES3_RKSbIwSt11char_traitsIwESaIwEEbb")
extern "C" int psNew(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,const std::wstring&,bool,bool) __asm__("_ZN6CLevel22populateSectionOfLevelERKN4Ogre7Vector3ES3_RKSbIwSt11char_traitsIwESaIwEEbb");
TL_FUNCTION(psFind,"_ZN16CResourceManager19getSpawnClassByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(psRoll,"_ZN11CSpawnClass14rollSpawnClassER10TArrayListIP10CDataGroupEPS0_IbEP10CCharacterS8_ijiiii")
TL_FUNCTION(psCreate,"_ZN16CResourceManager10createUnitEP10CDataGroupibb")
TL_FUNCTION(psRandomInt,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(psRandomFloat,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(psOpen,"_ZN6CLevel18randomOpenPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(psNoSpawn,"_ZN6CLevel17isInNoSpawnRegionERKN4Ogre7Vector3Ef")
TL_FUNCTION(psPass,"_ZN6CLevel15passableBetweenEN4Ogre7Vector3ERKS1_b")
TL_FUNCTION(psISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(psChampion,"_ZN10CCharacter12makeChampionERKSbIwSt11char_traitsIwESaIwEEiS3_")
TL_FUNCTION(psName,"_ZN12CRandomNames12generateNameEb")
TL_FUNCTION(psNameLoad,"_ZN12CRandomNames4loadEPKw")
TL_FUNCTION(psAddActor,"_ZN6CLevel12addCharacterEP10CCharacterRKN4Ogre7Vector3Eb")
TL_FUNCTION(psAddItem,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
namespace {
autotest::Capture*output;CLevel*level;CResourceManager*resources;CSpawnClass*spawn;CDataGroup*data[3];CRandomNames*names;CBaseUnit*units[8];TSafePointer<CRunicCore>*weak;CPropertyNode*nodes[4];unsigned seed,created,intCalls,floatCalls,openCalls,noSpawnCalls,passCalls;Ogre::SceneManager*scene;
void number(unsigned n){output->add(&n,4);}void vec(const Ogre::Vector3&v){output->add(&v,sizeof v);}void quat(const Ogre::Quaternion&q){output->add(&q,sizeof q);}void scalar(float f){output->add(&f,4);}void wide(const std::wstring&s){number(s.size());if(s.size())output->add(s.data(),s.size()*4);}unsigned id(CBaseUnit*p){for(unsigned i=0;i<created;++i)if(units[i]==p)return i;std::abort();return 99;}void orientation(CBaseUnit*p,const Ogre::Quaternion&q){number(20);number(id(p));quat(q);}void direction(CBaseUnit*p,Ogre::Vector3 v){number(21);number(id(p));vec(v);}
struct Actor:CCharacter{explicit Actor(CResourceManager*r):CCharacter(r){}virtual void setOrientation(const Ogre::Quaternion&q){orientation(this,q);}virtual void setDirection(Ogre::Vector3 v){direction(this,v);}};
struct Item:finishlevel::Item{explicit Item(CResourceManager*r):finishlevel::Item(r){}virtual void setOrientation(const Ogre::Quaternion&q){orientation(this,q);}virtual void setDirection(Ogre::Vector3 v){direction(this,v);}};
struct Foreign:CBaseUnit{explicit Foreign(CResourceManager*r):CBaseUnit(r,static_cast<EBASEUNIT_TYPE>(0)){}virtual void setActiveInLevel(bool){}virtual void*getUnitModel(){return NULL;}virtual void*getUnitCollisionModel(){return NULL;}virtual void setOrientation(const Ogre::Quaternion&q){orientation(this,q);}virtual void setDirection(Ogre::Vector3 v){direction(this,v);}};
struct Node:CPropertyNode{unsigned index;Ogre::Quaternion q;Node(CResourceManager*r,unsigned i):CPropertyNode(r),index(i),q(1,0,0,0){}virtual Ogre::Quaternion getOrientationQuaternion(){number(22);number(index);quat(q);return q;}};
CSpawnClass*find(CResourceManager*p,const std::wstring&name){number(1);number(p==resources);wide(name);bool present=seed%11!=0;number(present);return present?spawn:NULL;}
int roll(CSpawnClass*p,TArrayList<CDataGroup*>&out,TArrayList<bool>*b,CCharacter*a,CCharacter*c,int depth,unsigned count,int x,int y,int z,int w){number(2);number(p==spawn);number(b==NULL);number(a==NULL);number(c==NULL);number(depth);number(count);number(x);number(y);number(z);number(w);number(out.size());number(out.m_nCapacity);number(out.m_nGrowBy);for(unsigned i=0;i<seed%7;++i)out.add(data[(i+seed)%3]);return 53;}
CBaseUnit*create(CResourceManager*p,CDataGroup*g,int depth,bool a,bool b){number(3);number(p==resources);unsigned n=0;while(n<3&&data[n]!=g)++n;number(n);if(n==3||created>=8)std::abort();number(depth);number(a);number(b);unsigned kind=(seed+created)%3;CBaseUnit*u=kind==0?static_cast<CBaseUnit*>(new Actor(resources)):kind==1?static_cast<CBaseUnit*>(new Item(resources)):static_cast<CBaseUnit*>(new Foreign(resources));u->m_bBlocksPath=(seed/5+created)%2;u->m_bPathingFlag19C=(seed/7+created)%2;units[created]=u;weak[created].setObject(u);++created;passCalls=0;number(kind);return u;}
int randomInt(int a,int b){number(4);number(a);number(b);if(b<a)std::abort();int v=a+int((seed+intCalls++)%unsigned(b-a+1));number(v);return v;}
float randomFloat(float a,float b){number(5);scalar(a);scalar(b);float v=a+(b-a)*float((seed+floatCalls++)%5)*.25f;scalar(v);return v;}
Ogre::Vector3 open(CLevel*p,const Ogre::Vector3&v,float radius,bool f){number(6);number(p==level);vec(v);scalar(radius);number(f);++openCalls;Ogre::Vector3 result=v;if((seed/7)%7 && openCalls>seed%4)result+=Ogre::Vector3(.25f,-1,.75f);vec(result);return result;}
bool noSpawn(CLevel*p,const Ogre::Vector3&v,float radius){number(7);number(p==level);vec(v);scalar(radius);bool value=(seed+noSpawnCalls++)%13==0;number(value);return value;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){number(8);number(id(p));number(type);bool value=(seed+id(p))%3!=0;number(value);return value;}
bool pass(CLevel*p,Ogre::Vector3 a,const Ogre::Vector3&b,bool mapOnly){number(9);number(p==level);vec(a);vec(b);number(mapOnly);++passCalls;bool value=(seed/11)%5!=passCalls;number(value);return value;}
std::wstring name(CRandomNames*p,bool title){number(10);number(p==names);number(title);std::wstring s=seed&1?L"Champion \x041a\x4e2d":L"";wide(s);return s;}
void champion(CCharacter*p,const std::wstring&s,int depth,std::wstring type){number(11);number(id(p));wide(s);number(depth);wide(type);}
CCharacter*addActor(CLevel*p,CCharacter*a,const Ogre::Vector3&v,bool f){number(12);number(p==level);number(id(a));vec(v);number(f);return a;}
CItem*addItem(CLevel*p,CItem*a,const Ogre::Vector3&v,bool f){number(13);number(p==level);number(id(a));vec(v);number(f);return a;}
void namesLoad(CRandomNames*p,const wchar_t*){p->m_nWeight=0;}
void side(void*raw,autotest::Capture&out,bool ours){seed=*static_cast<unsigned*>(raw);output=&out;created=intCalls=floatCalls=openCalls=noSpawnCalls=passCalls=0;TSafePointer<CRunicCore>witness[8];weak=witness;finishlevel::Fixture f;level=&f.level;resources=&f.resources;resources->m_pSceneManager=scene;level->m_dungeonDepth=int(seed%17)-5;CSpawnClass actualSpawn(L"populate-section");spawn=&actualSpawn;for(unsigned i=0;i<3;++i)data[i]=new CDataGroup(L"UNIT",NULL,20,10,NULL);
 for(unsigned i=0;i<4;++i){Node*n=new Node(resources,i);nodes[i]=n;n->m_vPosition=Ogre::Vector3(float(i)-2,float(seed%3),float(i*3)-4);n->q=Ogre::Quaternion(float(i+1),float(i)*.125f,-float(i)*.25f,float(seed%5)*.125f);n->m_iUnknown114=(seed/13+i)%3?0:1;}for(unsigned i=0;i<seed/3%5;++i)level->m_propertyNodesF0.add(nodes[i]);
 detour::Set hooks;TL_REDIRECT(hooks,psFind,&find);TL_REDIRECT(hooks,psRoll,&roll);TL_REDIRECT(hooks,psCreate,&create);TL_REDIRECT(hooks,psRandomInt,&randomInt);TL_REDIRECT(hooks,psRandomFloat,&randomFloat);TL_REDIRECT(hooks,psOpen,&open);TL_REDIRECT(hooks,psNoSpawn,&noSpawn);TL_REDIRECT(hooks,psPass,&pass);TL_REDIRECT(hooks,psISA,&isa);TL_REDIRECT(hooks,psChampion,&champion);TL_REDIRECT(hooks,psName,&name);TL_REDIRECT(hooks,psAddActor,&addActor);TL_REDIRECT(hooks,psAddItem,&addItem);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 Ogre::Vector3 minimum(-float(seed%7),-3,-float(seed%11)),maximum(float(seed%13),9,float(seed%17));std::wstring spawnName=seed&1?L"spawn/\x041a\x4e2d":L"";typedef int(*Fn)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,const std::wstring&,bool,bool);Fn fn=ours?psNew:psOld;if(!autotest::beginInvocation(out,fn))return;int result=fn(level,minimum,maximum,spawnName,(seed/17)%2,(seed/2)%2);out.callCompleted=1;number(result);number(created);number(intCalls);number(floatCalls);number(openCalls);number(noSpawnCalls);for(unsigned i=0;i<4;++i)number(nodes[i]->m_iUnknown114);for(unsigned i=0;i<created;++i)number(weak[i].getObject()!=NULL);
 hooks.restore();for(unsigned i=0;i<created;++i)if(weak[i].getObject())delete units[i];for(unsigned i=0;i<created;++i)number(weak[i].getObject()==NULL);level->m_propertyNodesF0.clear();for(unsigned i=0;i<4;++i)delete nodes[i];for(unsigned i=0;i<3;++i)delete data[i];
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;scene=services.scene;menugui::Audio audio(services.master);CRandomNames**singleton=reinterpret_cast<CRandomNames**>(0x151f860);CRandomNames*previous=*singleton;*singleton=NULL;{detour::Set setup;TL_REDIRECT(setup,psNameLoad,&namesLoad);if(setup.failed())return 1;names=new CRandomNames(L"fixture-no-name-io");}if(*singleton!=names||names->m_pRandomizer||names->m_prefixes.size()||names->m_center.size()||names->m_suffixes.size())return 1;
 autotest::Coverage coverage("level_populate_section",reinterpret_cast<uintptr_t>(psOld));for(unsigned i=0;i<768;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    populateSection seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned z=0;z<a.capture.length&&z<b.capture.length;++z)if(a.capture.data[z]!=b.capture.data[z]){host->log("    firstdiff%u old%02x new%02x\n",z,(unsigned char)a.capture.data[z],(unsigned char)b.capture.data[z]);break;}coverage.report(host);return 1;}}coverage.report(host);delete names;*singleton=previous;return coverage.completed!=768||coverage.missing||coverage.different;}
}
TL_TEST(complete_level_populate_section){return systems_fixture::isolated(&worker,host);}
