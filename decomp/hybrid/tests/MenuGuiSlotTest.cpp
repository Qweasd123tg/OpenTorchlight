#include "MenuGuiFixture.h"
#include "DataGroup.h"
#include "GameVariables.h"
TL_ORIGINAL(void,mgOldDialogCreate,(CQuestDialogMenu*),"_ZN16CQuestDialogMenu11createMenusEv")
extern "C" void mgNewDialogCreate(CQuestDialogMenu*) __asm__("_ZN16CQuestDialogMenu11createMenusEv");
TL_ORIGINAL(void,mgOldQuestSlot,(CQuestMenu*,int,CEquipment*),"_ZN10CQuestMenu11setSlotIconEiP10CEquipment")
extern "C" void mgNewQuestSlot(CQuestMenu*,int,CEquipment*) __asm__("_ZN10CQuestMenu11setSlotIconEiP10CEquipment");
TL_ORIGINAL(void,mgOldDialogSlot,(CQuestDialogMenu*,int,CEquipment*),"_ZN16CQuestDialogMenu11setSlotIconEiP10CEquipment")
extern "C" void mgNewDialogSlot(CQuestDialogMenu*,int,CEquipment*) __asm__("_ZN16CQuestDialogMenu11setSlotIconEiP10CEquipment");
TL_ORIGINAL(void,mgEquipmentCtor,(CEquipment*,CResourceManager*),"_ZN10CEquipmentC1EP16CResourceManager")
TL_ORIGINAL(void,mgEquipmentDtor,(CEquipment*),"_ZN10CEquipmentD1Ev")
namespace {
CSettings*settings;Ogre::SceneManager*scene;bool dumpLayout,dumpCandidate;
CEGUI::Window*window(const char*type,const char*name,CEGUI::Window*parent){CEGUI::Window*w=CEGUI::WindowManager::getSingleton().createWindow(type,name);if(parent)parent->addChildWindow(w);w->setSize(CEGUI::UVector2(CEGUI::UDim(.1f,32),CEGUI::UDim(.2f,48)));return w;}
void snapshot(autotest::Capture&out,CEGUI::Window*w){std::string s=tlheadless::snapshot(*w);unsigned n=s.size();out.add(&n,4);out.add(s.data(),n);if(dumpLayout){std::FILE*f=std::fopen(dumpCandidate?"/tmp/otl-menu-layout-candidate.txt":"/tmp/otl-menu-layout-original.txt","wb");if(!f)std::abort();std::fwrite(s.data(),1,s.size(),f);std::fclose(f);}}
struct Items {
    std::vector<CEquipment*>all;
    CEquipment*create(CResourceManager*r){CEquipment*p=static_cast<CEquipment*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEquipment),0,0,0));mgEquipmentCtor(p,r);all.push_back(p);return p;}
    ~Items(){for(unsigned i=0;i<all.size();++i)all[i]->m_SocketedEquipment.clear();for(unsigned i=all.size();i;--i){mgEquipmentDtor(all[i-1]);Ogre::NedAllocImpl::deallocBytes(all[i-1]);}}
};
template<class M>void slots(M*m,CEGUI::Window*root){
    m->m_uiImages=CEGUI::ImagesetManager::getSingleton().getImageset("UIIcons");
    for(unsigned i=0;i<3;++i){char n[40];std::sprintf(n,"slot-background-%u",i);m->m_rewardBackgrounds[i]=window("DefaultWindow",n,root);std::sprintf(n,"slot-%u",i);m->m_rewardSlots[i]=window("GuiLook/StaticImage",n,m->m_rewardBackgrounds[i]);std::sprintf(n,"slot-count-%u",i);m->m_rewardCounts[i]=window("GuiLook/StaticText",n,m->m_rewardBackgrounds[i]);std::sprintf(n,"slot-icon-%u",i);m->m_rewardIcons[i]=window("GuiLook/StaticImage",n,root);std::sprintf(n,"slot-rarity-%u",i);m->m_rewardRarity[i]=window("GuiLook/StaticImage",n,root);}
}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
#ifdef OTL_MENU_SLOT_DEBUG_FIRST6
    if(c.op)c.index+=6;
#endif
    dumpLayout=c.op==0&&c.index==0;dumpCandidate=ours;
    const int widths[]={800,1600,320,1280,1920,2560};const int heights[]={600,900,480,720,1080,1440};const float ratios[]={1,1.5f,.5f,.75f,2,3};unsigned profileSettings=c.op==0?c.index/8:0;settings->SetInt(KSETTINGS_RES_WIDTH,widths[profileSettings*2+(c.index&1)]);settings->SetInt(KSETTINGS_RES_HEIGHT,heights[profileSettings*2+((c.index&2)!=0)]);settings->SetFloat(KSETTINGS_YRATIO,ratios[profileSettings*2+((c.index&4)!=0)]);
    CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);
    if(c.op==0){
        f.dialog->m_pUnknown20=f.root;
        typedef void(*Fn)(CQuestDialogMenu*);Fn fn=ours?mgNewDialogCreate:mgOldDialogCreate;if(!autotest::beginInvocation(out,fn))return;fn(f.dialog);out.callCompleted=1;
        for(unsigned i=0;i<4;++i)out.add(&f.dialog->m_rewardIDs[i],4);
        for(unsigned i=0;i<3;++i){unsigned ok=f.dialog->m_rewardSlots[i]->getUserData()==&f.dialog->m_rewardIDs[i];out.add(&ok,4);if(!ok)std::abort();}
        snapshot(out,f.root);return;
    }
    bool dialog=c.op==2;
    if(dialog){slots(f.dialog,f.root);f.dialog->m_overlayWindow=window("DefaultWindow","overlay",f.root);f.dialog->m_rewardContainer=window("DefaultWindow","sockets",f.root);}
    else{slots(f.quest,f.root);f.quest->m_listContent=window("DefaultWindow","sockets",f.root);}
    f.ui->m_itemImagesets.add(CEGUI::ImagesetManager::getSingleton().getImageset("UIIcons"));
    CDataGroup group(L"ITEM",NULL,4,4,NULL);group.AddDataValue(L"ICON",std::wstring(L"iconhelm"),false);
    Items items;unsigned slot=c.index%3,profile=c.index/3;CEquipment*item=NULL;
    if(profile==0){if(dialog)f.dialog->m_rewardSlots[slot]=NULL;else f.quest->m_rewardSlots[slot]=NULL;}
    if(profile>=2){
        profile-=2;item=items.create(&f.resources);item->m_iSocketCount=profile/4%3;item->m_bUnknown348=(profile&2)!=0;item->m_iUnknown238=(profile/12%3==0)?-1:(profile/12%3==1)?1:37;
        unsigned iconMode=profile/3%3;if(iconMode!=0)item->m_pDataGroup=&group;
        if(iconMode==1){item->m_pIconWindow=window("GuiLook/StaticImage","equipment-icon",f.root);window("GuiLook/StaticImage","equipment-image",item->m_pIconWindow);}
        unsigned types[]={0,54,55,120};item->m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>(types[profile/7%4]);
        if(profile&1)(dialog?f.dialog->m_rewardBackgrounds[slot]:f.quest->m_rewardBackgrounds[slot])->hide();
        for(unsigned i=0;i<profile/5%3;++i){CEquipment*child=items.create(&f.resources);child->m_pDataGroup=iconMode?&group:NULL;if(iconMode==1){char n[40];std::sprintf(n,"child-icon-%u",i);child->m_pIconWindow=window("GuiLook/StaticImage",n,f.root);std::sprintf(n,"child-image-%u",i);window("GuiLook/StaticImage",n,child->m_pIconWindow);}item->m_SocketedEquipment.add(child);}
        if(profile%7==0){if(dialog)f.dialog->m_rewardCounts[slot]=NULL;else f.quest->m_rewardCounts[slot]=NULL;}
    }
    if(dialog){typedef void(*Fn)(CQuestDialogMenu*,int,CEquipment*);Fn fn=ours?mgNewDialogSlot:mgOldDialogSlot;if(!autotest::beginInvocation(out,fn))return;fn(f.dialog,slot,item);}
    else{typedef void(*Fn)(CQuestMenu*,int,CEquipment*);Fn fn=ours?mgNewQuestSlot:mgOldQuestSlot;if(!autotest::beginInvocation(out,fn))return;fn(f.quest,slot,item);}
    out.callCompleted=1;snapshot(out,f.root);
    for(unsigned i=0;i<items.all.size();++i){unsigned has=items.all[i]->m_pIconWindow!=NULL;out.add(&has,4);}
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,op,name,address,&side,count);}
}
TL_TEST(complete_menu_dialog_create_real_cegui){return run(host,0,"complete_menu_dialog_create_real_cegui",0xbb08f0,24);}
TL_TEST(complete_menu_quest_slots_real_cegui){return run(host,1,"complete_menu_quest_slots_real_cegui",0xbc2d50,102);}
TL_TEST(complete_menu_dialog_slots_real_cegui){return run(host,2,"complete_menu_dialog_slots_real_cegui",0xbb56d0,102);}
