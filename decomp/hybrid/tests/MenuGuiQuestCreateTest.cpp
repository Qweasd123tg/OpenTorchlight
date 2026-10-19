#include "MenuGuiFixture.h"
#include "GenericModel.h"
#include "MenuModelGpuBoundary.h"
#include "GameVariables.h"
#include "SoundData.h"
#include "SoundBankDataInformation.h"
TL_ORIGINAL(void,mgOldQuestCreate,(CQuestMenu*),"_ZN10CQuestMenu11createMenusEv")
extern "C" void mgNewQuestCreate(CQuestMenu*) __asm__("_ZN10CQuestMenu11createMenusEv");
extern "C" void mgNewQuestCtor(CQuestMenu*,CGameUI&,CSettings&,Ogre::RenderWindow*,Ogre::SceneManager*,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*) __asm__("_ZN10CQuestMenuC1ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerES8_PN5CEGUI6WindowEP16CResourceManager");
TL_FUNCTION(mgCtorSoundLookup,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(mgCtorSoundAdd,"_ZN10CSoundBank9addSampleEix")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;CQuestMenu*menu;CSoundData*samples;unsigned presence;
void n(unsigned value){output->add(&value,4);}
CSoundData*soundLookup(CSoundBankDataInformation*p,const std::wstring&name){
    n(10);n(p==CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation);const wchar_t*names[]={L"INVENTORYOPEN",L"INVENTORYCLOSE",L"LOWMANA"};unsigned id=0;for(;id<3&&name!=names[id];++id){}n(id);n(name.size());output->add(name.data(),name.size()*4);return id<3&&(presence&(1u<<id))?samples+id:NULL;
}
void soundAdd(CSoundBank*p,int id,long long guid){n(11);n(p==menu->m_soundBank);n(id);output->add(&guid,8);}

void snapshot(autotest::Capture&out,CEGUI::Window*w){std::string s=tlheadless::snapshot(*w);unsigned n=s.size();out.add(&n,4);out.add(s.data(),n);}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
    const int widths[]={800,1600,320,1280,1920,2560};const int heights[]={600,900,480,720,1080,1440};const float ratios[]={1,1.5f,.5f,.75f,2,3};unsigned profile=c.index/8;settings->SetInt(KSETTINGS_RES_WIDTH,widths[profile*2+(c.index&1)]);settings->SetInt(KSETTINGS_RES_HEIGHT,heights[profile*2+((c.index&2)!=0)]);settings->SetFloat(KSETTINGS_YRATIO,ratios[profile*2+((c.index&4)!=0)]);
    CStringTranslate translate(L"");menugui::ModelGpuBoundary gpu;menugui::Fixture f(*settings,scene);output=&out;
    CSoundData soundData[3];for(unsigned i=0;i<3;++i){soundData[i].m_group=NULL;soundData[i].m_iGuid=0x123456789abcdefLL+i;}samples=soundData;presence=c.index%8;
    if(c.op==0){typedef void(*Fn)(CQuestMenu*);Fn fn=ours?mgNewQuestCreate:mgOldQuestCreate;if(!autotest::beginInvocation(out,fn))return;fn(f.quest);}
    else{
        mgQuestDtor(f.quest);Ogre::NedAllocImpl::deallocBytes(f.quest);f.quest=static_cast<CQuestMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CQuestMenu),0,0,0));
        typedef void(*Fn)(CQuestMenu*,CGameUI&,CSettings&,Ogre::RenderWindow*,Ogre::SceneManager*,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*);Fn fn=ours?mgNewQuestCtor:mgQuestCtor;if(!autotest::beginInvocation(out,fn))return;
        menu=f.quest;detour::Set sound;TL_REDIRECT(sound,mgCtorSoundLookup,&soundLookup);TL_REDIRECT(sound,mgCtorSoundAdd,&soundAdd);if(sound.failed())std::abort();
        fn(f.quest,*f.ui,*settings,NULL,f.nativeClient.scenes[0],f.nativeClient.scenes[1],f.root,&f.resources);
    }
    out.callCompleted=1;
    unsigned state[]={f.quest->m_parentWindow==f.root,f.quest->m_hoveredReward==NULL,f.quest->m_mouseThrough,f.quest->m_owner==NULL,f.quest->m_allowAbandon,f.quest->m_closed,f.quest->m_requestClose,f.quest->m_selectedQuestChanged,f.quest->m_selectedQuestID,unsigned(f.quest->m_selectedQuestIndex),f.quest->m_settings==settings,f.quest->m_gameUI==f.ui,f.quest->m_scene==f.nativeClient.scenes[0],f.quest->m_resources==&f.resources,f.quest->m_soundBank!=NULL,f.quest->m_questWindows.size()};out.add(state,sizeof(state));
    unsigned gpuCalls[]={menugui::materialPreparationCalls(),menugui::materialLoadCalls(),menugui::texturePreparationCalls(),menugui::automaticHardwareChecks(),menugui::textureLoadCalls()};out.add(gpuCalls,sizeof(gpuCalls));
    for(unsigned i=0;i<100;++i)out.add(&f.quest->m_questIDs[i],4);
    for(unsigned i=0;i<4;++i)out.add(&f.quest->m_rewardIDs[i],4);
    for(unsigned i=0;i<3;++i){unsigned ok=f.quest->m_rewardSlots[i]->getUserData()==&f.quest->m_rewardIDs[i];out.add(&ok,4);if(!ok)std::abort();}
    out.add(&f.quest->m_screenEdge,4);out.add(&f.quest->m_modelAnchor,4);
    snapshot(out,f.quest->m_rootWindow);
    // Native model geometry and genuine bones remain available for later
    // update/closing tests. No projection method is consumed here.
    Ogre::Vector3 position=f.quest->m_model->getPosition(false);out.add(&position,sizeof(position));
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address){tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,op,name,address,&side,24);}
}
TL_TEST(complete_menu_quest_create_real_cegui){return run(host,0,"complete_menu_quest_create_real_cegui",0xbc6b90);}
TL_TEST(complete_menu_quest_ctor_real_cegui){return run(host,1,"complete_menu_quest_ctor_real_cegui",0xbcc6d0);}
