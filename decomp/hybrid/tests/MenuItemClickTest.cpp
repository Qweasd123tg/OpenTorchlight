#include "MenuItemClickSpies.h"
#include "MenuItemClickDependencies.h"
TL_ORIGINAL(bool,originalClick,(CGameUI*,CCharacter*,CSubMenu*,int,bool),"_ZN7CGameUI13menuItemClickEP10CCharacterP8CSubMenuib")
extern "C" bool candidateClick(CGameUI*,CCharacter*,CSubMenu*,int,bool) __asm__("_ZN7CGameUI13menuItemClickEP10CCharacterP8CSubMenuib");
namespace menu_click_fixture {
static CCharacter* owner;
static CSubMenu* clickedMenu;
static void safeInit(void* ref,void* item) {
    field<void*>(ref,0)=item;
    if(!item){field<unsigned>(ref,8)=~0U;return;}
    int i=objectIndex(item);if(i<0)_exit(63);
    field<unsigned>(ref,8)=registered[i].size();registered[i].push_back(reinterpret_cast<TSafePointer<void*>*>(ref));
}
static void tag(unsigned item,unsigned value){if(itemTagCounts[item]>=8)_exit(64);itemTags[item][itemTagCounts[item]++]=value;}
static void setup(Case& c,autotest::Capture& out) {
    std::memset(storage,0,sizeof(storage));std::memset(inventorySlots,0,sizeof(inventorySlots));
    std::memset(itemTagCounts,0,sizeof(itemTagCounts));std::memset(itemTags,0,sizeof(itemTags));
    for(unsigned i=0;i<48;++i)registered[i].clear();
    for(unsigned i=0;i<48;++i){recordedPosition[i]=CEGUI::UVector2(CEGUI::UDim(0.1f,3),CEGUI::UDim(0.2f,4));recordedSize[i]=CEGUI::UVector2(CEGUI::UDim(0.3f,5),CEGUI::UDim(0.4f,6));}
    current=&c;capture=&out;keyCalls=pickupCalls=equipCalls=scaledCalls=0;openMask=1;
    gameUI=object<CGameUI>(1);ui=reinterpret_cast<UIState*>(gameUI);
    ui->player=object<CPlayer>(2);ui->level=object<CLevel>(41);ui->selectedSkill=-1;ui->dragSlot=-1;
    ui->mouseX=(c.variant&1)?(1LL<<33)+117:-77;ui->mouseY=(c.variant&2)?-(1LL<<33)+119:81;
    ui->inventoryMenu=object<CInventoryMenu>(12);ui->petMenu=object<CPetMenu>(13);ui->merchantMenu=object<CMerchantMenu>(14);
    ui->enchantMenu=object<CEnchantMenu>(15);ui->combineMenu=object<CCombineMenu>(16);ui->stashMenu=object<CStashMenu>(17);
    ui->tooltip=object<CEquipmentTooltip>(22);ui->comparisonTooltip1=object<CEquipmentTooltip>(23);ui->comparisonTooltip2=object<CEquipmentTooltip>(24);
    ui->resourceManager=object<CResourceManager>(25);ui->soundBank=object<CSoundBank>(26);
    ui->rootWindow=object<CEGUI::Window>(32);ui->dragWindow=object<CEGUI::Window>(33);
    for(int i=2;i<=6;++i){actor(object<CCharacter>(i)).inventory=object<CInventory>(i+5);field<int>(storage[i],0x444)=100;field<Ogre::SceneNode*>(storage[i],0x58)=object<Ogre::SceneNode>(i==2?42:44);actor(object<CCharacter>(i)).soundBank=(c.variant&2)?NULL:object<CSoundBank>(27);}
    followerStorage[0]=object<CCharacter>(3);followerStorage[1]=NULL;
    field<CCharacter**>(storage[2],0x648)=followerStorage;field<CCharacter**>(storage[2],0x650)=followerStorage+1;field<CCharacter**>(storage[2],0x658)=followerStorage+1;
    object<CSharedStash>(28)->m_pInventory=object<CInventory>(11);
    menuTable[2]=reinterpret_cast<void*>(&menuOwner);menuTable[4]=reinterpret_cast<void*>(&menuOpen);menuTable[8]=reinterpret_cast<void*>(&menuSetOpen);menuTable[9]=reinterpret_cast<void*>(&menuLayout);
    for(unsigned i=0;i<6;++i){field<void**>(storage[12+i],0)=menuTable;menuOwners[i]=object<CCharacter>(i==1?3:i==2?4:i==5?5:2);}
    itemTable[1]=reinterpret_cast<void*>(&deleteItem);itemTable[0x2f8/8]=reinterpret_cast<void*>(&itemCanEquip);itemTable[0x338/8]=reinterpret_cast<void*>(&stack);itemTable[0x360/8]=reinterpret_cast<void*>(&drop);
    for(unsigned i=0;i<4;++i){CEquipment* item=object<CEquipment>(18+i);field<void**>(item,0)=itemTable;field<long long>(item,0x1a0)=100+i;field<CDataGroup*>(item,0x1b0)=object<CDataGroup>(43);item->m_iUnknown238=2;item->m_iUnknown23C=10;item->m_iUnknown248=1;item->m_pIconWindow=object<CEGUI::Window>(34+i);field<CEGUI::Window*>(item->m_pIconWindow,0xb0)=ui->rootWindow;item->m_bUnknown348=true;item->m_iSocketCount=2;}
    const unsigned hover[]={0x1020,0x1370,0x3438,0xf0,0x190,0x3408};
    for(unsigned i=0;i<6;++i)field<CEquipment*>(storage[12+i],hover[i])=object<CEquipment>(20);
    for(unsigned i=22;i<=24;++i)object<CEquipmentTooltip>(i)->m_iCachedItemGuid=400+i;
    owner=object<CCharacter>(2);clickedMenu=object<CSubMenu>(12);c.slot=12;c.requiredPane=c.actualPane=0;c.shiftMask=0;c.canEquip=true;c.useAllowed=true;c.pickupFailures=0;c.equipResults=0;c.returnValue=(c.variant&1)!=0;
    const unsigned weakOffsets[]={0x80,0x90,0xa0,0xb8,0xc8};for(unsigned i=0;i<5;++i)safeInit(reinterpret_cast<char*>(gameUI)+weakOffsets[i],NULL);
    bool clicked=false,dragged=false;unsigned dragOwner=2;
    switch(c.scenario){
      case 0: break;
      case 1: clicked=true;break;
      case 2: clicked=true;ui->selectedSkill=0x123456789LL;break;
      case 3: case 4: clicked=true;c.useAllowed=c.scenario==3;safeInit(&ui->targetedItem,object<CEquipment>(20));safeInit(&ui->itemUser,object<CCharacter>(2));safeInit(&ui->targetCharacter,object<CCharacter>(3));object<CEquipment>(20)->m_iUnknown238=(c.variant&4)?2:1;object<CEquipment>(20)->m_iUnknown248=(c.variant&8)?-9999:0;object<CEquipment>(20)->m_pInventory=object<CInventory>(7);break;
      case 5: case 6: case 7: clicked=true;owner=object<CCharacter>(4);clickedMenu=object<CSubMenu>(14);openMask=5;c.shiftMask=7;if(c.scenario==6)field<int>(storage[2],0x444)=0;if(c.scenario==7){object<CEquipment>(19)->m_iUnknown238=1;object<CEquipment>(19)->m_bUnknown25F=true;}tag(1,54);break;
      case 8: clicked=true;openMask=3;c.shiftMask=7;break;
      case 9: clicked=true;openMask=9;c.shiftMask=7;c.slot=(c.variant&4)?14:0;break;
      case 10: clicked=true;openMask=17;c.shiftMask=7;c.slot=(c.variant&4)?15:12;for(unsigned k=15;k<15+(c.variant%5);++k)inventorySlots[0][k]=object<CEquipment>(20);break;
      case 11: dragged=true;owner=object<CCharacter>(5);clickedMenu=object<CSubMenu>(17);openMask=33;tag(0,103);break;
      case 12: dragged=true;owner=object<CCharacter>(4);clickedMenu=object<CSubMenu>(14);openMask=5;if(c.variant&4)dragOwner=4;break;
      case 13: clicked=true;openMask=5;c.shiftMask=7;if(c.variant&4)tag(1,103);break;
      case 14: clicked=dragged=true;break;
      case 15: clicked=dragged=true;field<long long>(storage[19],0x1a0)=100;object<CEquipment>(19)->m_iUnknown238=(c.variant&4)?9:3;break;
      case 16: clicked=dragged=true;tag(0,120);object<CEquipment>(19)->m_bUnknown348=(c.variant&4)==0;if(c.variant&8)field<unsigned>(storage[19],0x3f0)=2;break;
      case 17: dragged=true;break;
      case 18: dragged=true;c.slot=999;c.equipResults=1;break;
      case 19: dragged=true;c.slot=999;c.equipResults=(c.variant&4)?4:0;break;
      case 20: dragged=true;dragOwner=4;tag(0,54);object<CEquipment>(18)->m_iUnknown238=(c.variant&4)?1:2;object<CEquipment>(18)->m_bUnknown25F=true;break;
      case 21: clicked=dragged=true;c.slot=c.variant&1;tag(0,10);if(c.variant&4)tag(0,37);if(c.variant&8)tag(0,38);inventorySlots[0][0]=object<CEquipment>(19);inventorySlots[0][1]=object<CEquipment>(20);break;
      case 22: clicked=true;owner=object<CCharacter>(6);clickedMenu=object<CSubMenu>(17);menuOwners[5]=owner;openMask=33;c.shiftMask=7;break;
      case 23: clicked=true;owner=object<CCharacter>(3);clickedMenu=object<CSubMenu>(13);openMask=2;c.shiftMask=7;break;
      case 24: clicked=true;c.shiftMask=7;if(c.variant&4)actor(object<CCharacter>(3)).aiState=42;else field<CCharacter**>(storage[2],0x650)=followerStorage;break;
      case 25: dragged=true;c.slot=999;c.equipResults=4;c.pickupFailures=~0U;tag(0,10);break;
      case 27: clicked=true;openMask=33;c.shiftMask=7;if(c.variant&4)tag(1,103);break;
      case 28: clicked=true;openMask=33;c.shiftMask=7;menuOwners[5]=object<CCharacter>(6);if(c.variant&4)tag(1,103);break;
      case 29: clicked=dragged=true;dragOwner=4;tag(0,120);tag(0,54);break;
      case 30: clicked=dragged=true;dragOwner=4;field<long long>(storage[19],0x1a0)=100;object<CEquipment>(18)->m_iUnknown238=(c.variant&4)?1:2;object<CEquipment>(18)->m_bUnknown25F=true;object<CEquipment>(19)->m_iUnknown238=(c.variant&8)?9:3;break;
      case 31: dragged=true;c.slot=(c.variant&4)?0:999;c.canEquip=false;break;
      case 32: dragged=true;c.slot=0;c.canEquip=(c.variant&4)!=0;tag(0,120);break;
      case 26: dragged=true;owner=object<CCharacter>(3);clickedMenu=object<CSubMenu>(13);openMask=(c.variant&4)?33:((c.variant&8)?5:3);c.requiredPane=4;c.actualPane=0;break;
    }
    if(clicked){unsigned inv=objectIndex(actor(owner).inventory)-7;if(c.slot>=0&&c.slot<100)inventorySlots[inv][c.slot]=object<CEquipment>(19);}
    if(dragged){safeInit(&ui->draggedItem,object<CEquipment>(18));safeInit(&ui->dragOwner,object<CCharacter>(dragOwner));ui->dragSlot=31;field<CEGUI::Window*>(storage[34],0xb0)=(c.variant&2)?ui->rootWindow:ui->dragWindow;}
    if(c.scenario==14 || c.scenario==5 || c.scenario==7 || c.scenario==8 || c.scenario==9 || c.scenario==10 || c.scenario==12 || c.scenario==17)c.pickupFailures=(c.variant&8)?1:0;
    if(c.scenario==0){const int slots[]={-1,0,12,82,83,999};c.slot=slots[c.variant%6];}
    if(c.failureMode){const unsigned masks[]={0,1,2,3,6,~0U};c.pickupFailures=masks[c.failureMode];}
    for(unsigned i=7;i<=11;++i)object<CInventory>(i)->m_pPositionableObject=object<CCharacter>(i-5);
}
static void snapshot() {
    number(900);pointer(ui->draggedItem.getObject());pointer(ui->dragOwner.getObject());number(ui->dragSlot);
    pointer(ui->targetedItem.getObject());pointer(ui->itemUser.getObject());pointer(ui->targetCharacter.getObject());capture->add(&ui->selectedSkill,8);
    const unsigned weakOffsets[]={0x80,0x90,0xa0,0xb8,0xc8};for(unsigned i=0;i<5;++i)number(field<unsigned>(gameUI,weakOffsets[i]+8));
    const unsigned hover[]={0x1020,0x1370,0x3438,0xf0,0x190,0x3408};for(unsigned i=0;i<6;++i)pointer(field<CEquipment*>(storage[12+i],hover[i]));
    for(unsigned i=22;i<=24;++i)capture->add(&object<CEquipmentTooltip>(i)->m_iCachedItemGuid,8);
    for(unsigned i=18;i<22;++i){CEquipment* item=object<CEquipment>(i);number(item->m_iUnknown238);number(item->m_iUnknown248);number(item->m_iSocketCount);number(field<unsigned>(item,0x3f0));pointer(field<CEGUI::Window*>(item->m_pIconWindow,0xb0));}
    for(unsigned i=34;i<=37;++i){scalar(recordedPosition[i].d_x.d_scale);scalar(recordedPosition[i].d_x.d_offset);scalar(recordedPosition[i].d_y.d_scale);scalar(recordedPosition[i].d_y.d_offset);scalar(recordedSize[i].d_x.d_scale);scalar(recordedSize[i].d_x.d_offset);scalar(recordedSize[i].d_y.d_scale);scalar(recordedSize[i].d_y.d_offset);}
    number(field<int>(storage[2],0x444));number(openMask);number(keyCalls);number(pickupCalls);number(equipCalls);
    for(unsigned i=0;i<5;++i)for(unsigned k=0;k<100;++k)pointer(inventorySlots[i][k]);
}
static void side(const Case& input,bool ours,autotest::Capture& out) {
    Case c=input;setup(c,out);
    detour::Set redirect0;
    detour::Set redirect1;
    detour::Set redirect2;
    TL_REDIRECT(redirect0,dependency00,&unitIs);
    TL_REDIRECT(redirect0,dependency01,&slotItem);
    TL_REDIRECT(redirect0,dependency02,&targetItem);
    TL_REDIRECT(redirect0,dependency03,&castSkill);
    TL_REDIRECT(redirect0,dependency04,&mouseOver);
    TL_REDIRECT(redirect0,dependency05,&cursorState);
    TL_REDIRECT(redirect0,dependency06,&hardwareCursor);
    redirect0.redirect(dependency07,dependency07,&systemSingleton);
    redirect0.redirect(dependency08,dependency08,&mouseMove);
    TL_REDIRECT(redirect0,dependency09,&requiredPane);
    TL_REDIRECT(redirect0,dependency10,&itemPane);
    TL_REDIRECT(redirect0,dependency11,&shared);
    TL_REDIRECT(redirect0,dependency12,&canUse);
    TL_REDIRECT(redirect0,dependency13,&use);
    TL_REDIRECT(redirect0,dependency16,&playSample);
    TL_REDIRECT(redirect0,dependency17,&queueSample);
    TL_REDIRECT(redirect0,dependency18,&findSlot);
    TL_REDIRECT(redirect0,dependency19,&removeEquipment);
    TL_REDIRECT(redirect0,dependency20,&pickupAt);
    TL_REDIRECT(redirect0,dependency21,&dropSound);
    TL_REDIRECT(redirect1,dependency22,&sellPrice);
    TL_REDIRECT(redirect1,dependency23,&giveGold);
    TL_REDIRECT(redirect1,dependency24,&soldItem);
    TL_REDIRECT(redirect1,dependency25,&pickupAny);
    TL_REDIRECT(redirect1,dependency26,&buyPrice);
    TL_REDIRECT(redirect1,dependency27,&addContainer);
    TL_REDIRECT(redirect1,dependency28,&elemental);
    TL_REDIRECT(redirect1,dependency29,&bonuses);
    TL_REDIRECT(redirect1,dependency30,&effectValues);
    TL_REDIRECT(redirect1,dependency31,&refreshEquipped);
    TL_REDIRECT(redirect1,dependency32,&key);
    TL_REDIRECT(redirect1,dependency33,&setTab);
    TL_REDIRECT(redirect1,dependency34,&takeSound);
    redirect1.redirect(dependency35,dependency35,&addWindow);
    TL_REDIRECT(redirect1,dependency36,&scaledY);
    redirect1.redirect(dependency37,dependency37,&windowPosition);
    redirect1.redirect(dependency38,dependency38,&windowSize);
    TL_REDIRECT(redirect1,dependency39,&position);
    TL_REDIRECT(redirect1,dependency40,&addItem);
    TL_REDIRECT(redirect1,dependency41,&setPetTab);
    TL_REDIRECT(redirect2,dependency42,&setPetTab);
    TL_REDIRECT(redirect2,dependency43,&setTab);
    TL_REDIRECT(redirect2,dependency44,&setTab);
    TL_REDIRECT(redirect2,dependency45,&returnDragged);
    TL_REDIRECT(redirect2,dependency46,&inventoryCanEquip);
    TL_REDIRECT(redirect2,dependency47,&firstFree);
    TL_REDIRECT(redirect2,dependency48,&renderBehind);
    TL_REDIRECT(redirect2,dependency49,&create);
    TL_REDIRECT(redirect2,dependency50,&journal);
    TL_REDIRECT(redirect2,dependency51,&achievements);
    TL_REDIRECT(redirect2,dependency52,&achievement);
    TL_REDIRECT(redirect2,dependency53,&forceComplete);
    redirect2.redirect(dependency54,dependency54,&removeWindow);
    TL_REDIRECT(redirect2,dependency55,&closeLeft);
    TL_REDIRECT(redirect2,dependency56,&closeRight);
    TL_REDIRECT(redirect2,dependency57,&comparisonItems);
    TL_REDIRECT(redirect2,dependency59,&removeSafe);
    TL_REDIRECT(redirect2,dependency60,&addSafe);
    if(redirect0.failed() || redirect1.failed() || redirect2.failed())_exit(60);
    if(ours)autotest::invoke(out,&candidateClick,gameUI,owner,clickedMenu,c.slot,c.returnValue);
    else autotest::invoke(out,&originalClick,gameUI,owner,clickedMenu,c.slot,c.returnValue);
    snapshot();
}
static void a(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}
static void b(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(menu_item_click_differential) {
    using namespace menu_click_fixture;
    autotest::Coverage coverage("menu_item_click_differential",reinterpret_cast<uintptr_t>(&originalClick));
    unsigned total=0;
    for(unsigned scenario=0;scenario<33;++scenario)for(unsigned variant=0;variant<16;++variant)for(unsigned failure=0;failure<6;++failure){
        Case c={};c.scenario=scenario;c.variant=variant;c.failureMode=failure;autotest::Outcome left,right;
        autotest::runChild(a,&c,left);autotest::runChild(b,&c,right);
        int difference=coverage.observe(host,left,right);++total;
        if(difference || left.childStatus || right.childStatus || !left.reportValid || !right.reportValid || !left.capture.callCompleted || !right.capture.callCompleted){
            host->log("    case %u variant %u failure %u differs; exits %d/%d lengths %lu/%lu\n",scenario,variant,failure,left.childStatus,right.childStatus,(unsigned long)left.capture.length,(unsigned long)right.capture.length);
            size_t offset=0;while(offset<left.capture.length && offset<right.capture.length && left.capture.data[offset]==right.capture.data[offset])++offset;
            host->log("    first byte %lu\n",(unsigned long)offset);
            for(size_t i=offset/4>8?offset/4-8:0;i<offset/4+24;++i){unsigned l=0,r=0;if(i*4+4<=left.capture.length)std::memcpy(&l,left.capture.data+i*4,4);if(i*4+4<=right.capture.length)std::memcpy(&r,right.capture.data+i*4,4);host->log("    word %lu: %u / %u\n",(unsigned long)i,l,r);}
            return 1;
        }
    }
    coverage.report(host);host->log("    menuItemClick: %u completed branch comparisons\n",total);return 0;
}
