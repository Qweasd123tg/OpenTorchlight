#include "tests/MenuGuiFixture.h"
#include "tests/FinishLevelFixture.h"
#include "tests/SystemsFixtureWorker.h"
#include "CharacterSaveState.h"
#include <clocale>
TL_ORIGINAL(void,gcaOld,(CGameClient*,CCharacterSaveState*,std::wstring&,CCharacterSaveState*),"_ZN11CGameClient19applyCharacterStateEP19CCharacterSaveStateRSbIwSt11char_traitsIwESaIwEES1_")
extern "C" void gcaNew(CGameClient*,CCharacterSaveState*,std::wstring&,CCharacterSaveState*) __asm__("_ZN11CGameClient19applyCharacterStateEP19CCharacterSaveStateRSbIwSt11char_traitsIwESaIwEES1_");
TL_FUNCTION(gcaPlayer,"_ZN16CResourceManager12createPlayerEPKwb")
TL_FUNCTION(gcaUnit,"_ZN16CResourceManager10createUnitExibb")
TL_FUNCTION(gcaApply,"_ZN7CPlayer14applySaveStateER19CCharacterSaveState")
TL_FUNCTION(gcaRemove,"_ZN6CLevel15removeCharacterEP10CCharacterb")
TL_FUNCTION(gcaAdd,"_ZN6CLevel12addCharacterEP10CCharacterRKN4Ogre7Vector3Eb")
TL_FUNCTION(gcaToward,"_ZN10CCharacter9setTowardERKN4Ogre7Vector3E")
TL_FUNCTION(gcaAlignment,"_ZN10CCharacter12setAlignmentE10EAlignment")
TL_FUNCTION(gcaUIPlayer,"_ZN7CGameUI9setPlayerEP10CCharacter")
namespace {
#include "tests/CharacterEmptyGlobals.h"
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*cap;bool armed;CGameClient*client;CGameUI*ui;CLevel*level;CResourceManager*resources;CPlayer*actors[4];CCharacterSaveState*states[2];
void num(unsigned n){if(armed)cap->add(&n,4);}void fp(float n){if(armed)cap->add(&n,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void wide(const std::wstring&s){num(s.size());if(armed)cap->add(s.data(),s.size()*4);}unsigned id(const void*p){if(!p)return 0;for(unsigned i=0;i<4;++i)if(p==actors[i])return i+1;return 99;}
CPlayer*create(CResourceManager*p,const wchar_t*name,bool flag){num(101);num(p==resources);wide(name);num(flag);return actors[2];}
CBaseUnit*unit(CResourceManager*p,long long guid,int rank,bool a,bool b){num(103);num(p==client->m_gameResources);if(armed)cap->add(&guid,8);num(rank);num(a);num(b);return actors[3];}
void apply(CPlayer*p,CCharacterSaveState&s){num(107);num(id(p));num(&s==states[0]?1:&s==states[1]?2:99);p->SetName(s.m_name);p->m_characterDisplayName=L"applied-override";}
bool remove(CLevel*p,CCharacter*c,bool flag){num(109);num(p==level);num(id(c));num(flag);return true;}
void add(CLevel*p,CCharacter*c,const Ogre::Vector3&v,bool flag){num(113);num(p==level);num(id(c));vec(v);num(flag);}
void toward(CCharacter*p,const Ogre::Vector3&v){num(127);num(id(p));vec(v);}
void alignment(CCharacter*p,EAlignment a){num(131);num(id(p));num(a);p->m_alignment=a;}
void setPlayer(CGameUI*p,CCharacter*c){num(137);num(p==ui);num(id(c));}
struct Case{unsigned seed;};
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);unsigned seed=c.seed;cap=&out;armed=false;menugui::Fixture menu(*settings,scene);finishlevel::Fixture world;client=menu.nativeClient.client;ui=menu.ui;level=&world.level;resources=&world.resources;client->m_pGameUI=ui;client->m_level=level;level->m_playerStart=Ogre::Vector3(seed*.25f,3,-7);level->m_startDirection=Ogre::Vector3(-1,seed*.125f,2);level->m_secondaryStart=Ogre::Vector3(7,-3,seed*.5f);level->m_secondaryStartDirection=Ogre::Vector3(2,1,-float(seed));ui->m_name16B8=seed&1?L"pet-ui":L"Питомец";client->m_editorCreationClass=L"before-class";client->m_editorCreationPet=L"before-pet";client->m_deferredFrames=int(seed%11)-3;
 TSafePointer<CCharacter> weak[4];for(unsigned i=0;i<4;++i){actors[i]=nativegame::createPlayer(client->m_gameResources);actors[i]->m_petMode=17+i;actors[i]->m_characterDisplayName=L"before";weak[i].setObject(actors[i]);}
 client->m_pPlayer=seed%5?actors[0]:NULL;client->m_creationPet=seed&2?actors[1]:NULL;CCharacterSaveState saved,pet;states[0]=&saved;states[1]=&pet;saved.m_name=seed&1?L"Restored":L"Восстановлен";pet.m_name=seed&4?L"PetType":L"Кошка";pet.m_guid20=0x123456780000LL+seed*103;pet.m_valueD0=int(seed%9)-3;std::wstring className=seed&8?L"Destroyer":L"Алхимик";
 detour::Set patch;TL_REDIRECT(patch,gcaPlayer,&create);TL_REDIRECT(patch,gcaUnit,&unit);TL_REDIRECT(patch,gcaApply,&apply);TL_REDIRECT(patch,gcaRemove,&remove);TL_REDIRECT(patch,gcaAdd,&add);TL_REDIRECT(patch,gcaToward,&toward);TL_REDIRECT(patch,gcaAlignment,&alignment);TL_REDIRECT(patch,gcaUIPlayer,&setPlayer);if(patch.failed())_exit(64);
 armed=true;typedef void(*F)(CGameClient*,CCharacterSaveState*,std::wstring&,CCharacterSaveState*);F fn=ours?gcaNew:gcaOld;autotest::invoke(out,fn,client,seed%3?&saved:NULL,className,seed&16?&pet:NULL);num(id(client->m_pPlayer));num(id(client->m_creationPet));num(client->m_deferredFrames);wide(client->m_editorCreationClass);wide(client->m_editorCreationPet);for(unsigned i=0;i<4;++i){num(weak[i].getObject()!=NULL);if(weak[i].getObject()){wide(actors[i]->m_characterDisplayName);num(actors[i]->m_petMode);num(actors[i]->m_alignment);}}
 armed=false;client->m_pPlayer=NULL;client->m_creationPet=NULL;client->m_pGameUI=NULL;client->m_level=NULL;patch.restore();for(unsigned i=0;i<4;++i)if(weak[i].getObject())nativegame::destroyPlayer(actors[i]);
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){initEmptyGlobals();tlheadless::Environment env;env.loadGameSkin();nativegame::Services native;if(!native.ready())return 1;menugui::Audio audio(native.master);settings=native.settings;scene=native.scene;autotest::Stats stats={0,0,0};autotest::Coverage coverage("gameclient_apply_state",(uintptr_t)gcaOld);int failures=0;for(unsigned i=0;i<160;++i){Case c={i};bool ok=autotest::compareCase(before,after,&c,stats,host,"gameclient_apply_state",i,&coverage);TL_CHECK(failures,ok);if(!ok)break;}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=160);}
}
TL_TEST(gameclient_apply_state){if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;return systems_fixture::isolated(&worker,host);}
