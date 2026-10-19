#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "TriggerUnit.h"
#include "Level.h"
#include "SoundBank.h"
#include "SoundData.h"
#include "SoundBankDataInformation.h"
#include "UnitResourceList.h"
#include "Editor.h"
#include "SpawnClass.h"
#include "StringUtilities.h"
#undef protected
#undef private
#include "NativeTriggerLevelFixture.h"
#include "tests/NativeMenuServices.h"
#include "tests/NativeEditorControls.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,tiSoundOld,(CTriggerUnit*,ETRIGGER_STATES,const wchar_t*),"_ZN12CTriggerUnit16addSoundsToStateE15ETRIGGER_STATESPKw")
TL_ORIGINAL(void,tiNameOld,(CTriggerUnit*,std::wstring),"_ZN12CTriggerUnit16setUnitModelNameESbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,tiSpawnOld,(CTriggerUnit*,CCharacter*,const std::wstring&,unsigned),"_ZN12CTriggerUnit18spawnTreasureClassEP10CCharacterRKSbIwSt11char_traitsIwESaIwEEj")
extern "C" void tiSoundNew(CTriggerUnit*,ETRIGGER_STATES,const wchar_t*) __asm__("_ZN12CTriggerUnit16addSoundsToStateE15ETRIGGER_STATESPKw");
extern "C" void tiNameNew(CTriggerUnit*,std::wstring) __asm__("_ZN12CTriggerUnit16setUnitModelNameESbIwSt11char_traitsIwESaIwEE");
extern "C" void tiSpawnNew(CTriggerUnit*,CCharacter*,const std::wstring&,unsigned) __asm__("_ZN12CTriggerUnit18spawnTreasureClassEP10CCharacterRKSbIwSt11char_traitsIwESaIwEEj");
TL_FUNCTION(tiSample,"_ZN10CSoundBank9addSampleEix")
TL_FUNCTION(tiRemove,"_ZN6CLevel10removeItemEP5CItemb")
TL_FUNCTION(tiAdd,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(tiLookup,"_ZN16CResourceManager19getSpawnClassByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(tiCreate,"_ZN16CResourceManager40createUnitsBySpawnClassAtPositionInLevelEP11CSpawnClassjRKN4Ogre7Vector3EP6CLevelP10CCharacterS9_i")
namespace {
nativegame::Services*services;autotest::Capture*output;CTriggerUnit*unit;CDataGroup*group;CLevel*level;CCharacter*actor;CSpawnClass*spawn;unsigned seed;
void n(unsigned x){output->add(&x,4);}void text(const std::wstring&s){output->addText(s);}
void sample(CSoundBank*p,int state,long long guid){n(1);n(p==unit->m_pSoundBank);n(state);output->add(&guid,8);}
void remove(CLevel*p,CItem*i,bool flag){n(2);n(p==level);n(i==unit);n(flag);}
void add(CLevel*p,CItem*i,const Ogre::Vector3&position,bool flag){n(3);n(p==level);n(i==unit);output->add(&position,sizeof position);n(flag);}
CSpawnClass* lookup(CResourceManager*r,const std::wstring&s){n(4);n(r==unit->m_pResourceManager);text(s);return seed%3?spawn:NULL;}
void create(CResourceManager*r,CSpawnClass*s,unsigned count,const Ogre::Vector3&position,CLevel*l,CCharacter*a,CCharacter*b,int depth){n(5);n(r==unit->m_pResourceManager);n(s==spawn);n(s==NULL);n(count);output->add(&position,sizeof position);n(l==level);n(a==actor);n(b==NULL);n(depth);}
struct Trigger:CTriggerUnit{explicit Trigger(CResourceManager*r):CTriggerUnit(r){}virtual void unitInit(CDataGroup*d,bool flag){n(6);n(d==group);n(flag);m_bBlocksPath=seed/5%2;}};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;nativetrigger::LevelFixture fixture(*services);fixture.resources.m_pSceneManager=services->scene;fixture.resources.m_pLevel=&fixture.level;level=&fixture.level;
 int previousFlags=gEditor->m_iFlags;gEditor->m_iFlags=seed/7%2?2:0;
 Trigger u(&fixture.resources);unit=&u;u.sceneNodeSetParent(services->scene->getRootSceneNode(),false);u.setPosition(float(int(seed%5)-2),float(seed%7)*.25f,-3.5f);u.m_pSoundBank=new CSoundBank(*services->master->m_pSoundManager,false);u.m_bItemFlag1F0=seed%2;u.m_bPathingFlag19C=seed/3%2;
 CDataGroup data(L"fixture-prop",NULL,10,10,NULL);group=&data;u.m_pDataGroup=&data;
 CSoundBankDataInformation info(NULL);CSoundBankDataInformation*previousInfo=services->master->m_pSoundBankDataInformation;services->master->m_pSoundBankDataInformation=&info;
 const wchar_t*soundNames[]={L"PRIMARY",L"FALLBACK",L"",L"MIXED",L"\x0417\x0412\x0423\x041a"};
 for(unsigned i=0;i<5;++i){CDataGroup sd(L"sound",NULL,10,10,NULL);sd.SetDataValue(L"GUID",static_cast<long long>(1001+i));sd.SetDataValue(L"NAME",soundNames[i],false);sd.SetDataValue(L"CATEGORY",L"FIXTURE",false);CDataGroup*files=sd.GetDataGroupByName(L"FILES",true);files->SetDataValue(L"FILE",L"fixture.wav",false);CSoundData*s=info.createSoundData(&sd);if(!s)std::abort();info.m_sounds.add(s);info.m_soundsByGuid[s->m_iGuid]=s;info.m_soundsByCategoryIndex[0][s->m_name]=s;}
 info.m_categoryNames.add(L"FIXTURE");
 const wchar_t*values[]={L"",L"primary",L"FaLlBaCk",L"mixed",L"unknown",L"\x0437\x0432\x0443\x043a"};data.SetDataValue(L"STATE_SOUND",values[seed%6],false);data.SetDataValue(L"INTERACT_SOUND",values[seed/3%6],false);if(c.op==0&&seed%11==0)u.m_pDataGroup=NULL;
 CUnitResourceList*previousList=m_pGlobalUnitResourceList;CUnitResourceList resources;m_pGlobalUnitResourceList=&resources;
 const wchar_t*names[]={L"",L"same",L"prop",L"MiXeD",L"\x0431\x0440\x0430\x043c\x0430",L"missing"};std::wstring name=names[seed%6];u.m_modelName=seed/5%2?name:L"same";if(seed%3)resources.m_dataGroupsByResourceGroupAndName[L"PROPS"][STRINGS::StringUpper(name)]=&data;
 CSpawnClass actualSpawn(L"fixture-spawn");spawn=&actualSpawn;actor=NULL;if(c.op==2&&seed/2%2)actor=nativegame::createPlayer(&fixture.resources);
 CResourceManager*saved=u.m_pResourceManager;CLevel*savedLevel=saved->m_pLevel;if(c.op==2&&seed/11%3==1)u.m_pResourceManager=NULL;else if(seed/11%3==2)saved->m_pLevel=NULL;u.m_flag2E0=seed/5%2;
 detour::Set hooks;TL_REDIRECT(hooks,tiSample,&sample);TL_REDIRECT(hooks,tiRemove,&remove);TL_REDIRECT(hooks,tiAdd,&add);TL_REDIRECT(hooks,tiLookup,&lookup);TL_REDIRECT(hooks,tiCreate,&create);if(hooks.failed())std::abort();
 if(c.op==0)autotest::invoke(out,ours?tiSoundNew:tiSoundOld,&u,static_cast<ETRIGGER_STATES>(int(seed/7%5)-1),seed/13%2?L"STATE_SOUND":L"absent");
 else if(c.op==1)autotest::invoke(out,ours?tiNameNew:tiNameOld,&u,name);
 else autotest::invoke(out,ours?tiSpawnNew:tiSpawnOld,&u,actor,name,seed%17==0?~0u:seed/3%8);
 hooks.restore();text(u.m_modelName);n(u.m_bItemFlag1F0);n(u.m_bBlocksPath);n(u.m_bPathingFlag19C);output->add(&u.m_vPosition,sizeof u.m_vPosition);u.m_pResourceManager=saved;saved->m_pLevel=savedLevel;m_pGlobalUnitResourceList=previousList;services->master->m_pSoundBankDataInformation=previousInfo;gEditor->m_iFlags=previousFlags;if(actor)nativegame::destroyPlayer(static_cast<CPlayer*>(actor));
}
int worker(const tlhybrid_host*host){
 initEmptyGlobals();void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x148c4e8),8);if(!p)new(reinterpret_cast<void*>(0x148c4e8))std::wstring;
 nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(native.master);nativeeditor::Controls editor(native);
 const char*names[]={"trigger_sound_native","trigger_model_name_native","trigger_treasure_native"};const unsigned addresses[]={0x909a70,0x909d10,0x8fccd0};for(unsigned i=0;i<3;++i)if(smallmass::run(host,i,names[i],addresses[i],&side,192))return 1;return 0;
}
}
TL_TEST(complete_trigger_io){return systems_fixture::isolated(&worker,host);}
