// Inlined initializers and final CGameUI::create phase.
// Normal-path evidence aa3ac9..aa402d.
#ifndef OTL_GAMEUI_STARTUP_FINALIZE_H
#define OTL_GAMEUI_STARTUP_FINALIZE_H
#include "startup_menus.h"
#include "EquipmentTooltip.h"
#include "SkillTooltip.h"
#include "SkillFoldout.h"
#include "TextEvent.h"
#include "TLinkedList.h"
#include "Console.h"
#include "MenuManager.h"
// These convenience constructor signatures represent inlined source operations;
// no external ABI/import is inferred for the unsymbolized initializer bodies.
inline __attribute__((always_inline)) CEquipmentTooltip::CEquipmentTooltip(CEGUI::Window* parent)
    :m_iCachedItemGuid(-1),m_pParent(parent){}
inline __attribute__((always_inline)) CSkillTooltip::CSkillTooltip(CGameUI* ui,CEGUI::Window* root)
    :m_pGameUI(ui),m_sText(EMPTY_WSTRING),m_iIndex(-1),m_pRoot(root){}
inline __attribute__((always_inline)) CSkillFoldout::CSkillFoldout(CGameUI* ui,CEGUI::Window* parent)
    :m_iSelection(0),m_pGameUI(ui),m_pParent(parent),m_bFlagCB1(false) {
    for(int i=0;i<100;++i)m_SkillIndices[i]=i;
}
inline __attribute__((always_inline)) CTextEvent::CTextEvent(const std::string& text,const CEGUI::colour& first,const CEGUI::colour& second)
    :m_Value10(0.f),m_Value14(0.f),m_Value18(0.f),m_Text(text),m_Colour28(first),m_Colour40(second),
     m_Value60(1.f),m_Value64(1.f),m_Value68(1.f),m_Value70(0.1f),m_pWindow(NULL),m_Flag80(true),m_Flag81(true),m_Flag82(false){}
namespace gameui_create_detail {
// Exact inlined one-pointer list shell. Do not expand the shared partial list
// declaration or initialize bytes the original leaves untouched.
struct TextEventList : Ogre::GeneralAllocatedObject {
    TLinkedListNode<CTextEvent*>* head;
    TextEventList():head(NULL){}
    inline __attribute__((always_inline)) void prepend(CTextEvent* event) {
        TLinkedListNode<CTextEvent*>* node=new TLinkedListNode<CTextEvent*>;
        node->m_Data=event;node->m_pNext=NULL;node->m_pPrevious=NULL;
        if(!head) {head=node;node->m_pNext=NULL;head->m_pPrevious=NULL;}
        else {node->m_pNext=head;head->m_pPrevious=node;head=node;}
    }
};
typedef char event_list_size[sizeof(TextEventList)==8?1:-1];
typedef char event_node_size[sizeof(TLinkedListNode<CTextEvent*>)==0x18?1:-1];
struct FinalState {
    char prefix[0x4a0];
    CEquipmentTooltip* equipment;
    CEquipmentTooltip* compareFirst;
    CEquipmentTooltip* compareSecond;
    CSkillTooltip* skill;
    CSkillFoldout* foldout;
    char gap4C8[0x588-0x4c8];
    CMenuManager* menuManager;
    char gap590[0x1690-0x590];
    CConsole* console;
    TextEventList* freeEvents;
    TextEventList* activeEvents;
};
#define STARTUP_FINAL_OFFSET(NAME,OFFSET) typedef char startup_final_##NAME[__builtin_offsetof(FinalState,NAME)==OFFSET?1:-1]
STARTUP_FINAL_OFFSET(equipment,0x4a0);STARTUP_FINAL_OFFSET(compareFirst,0x4a8);STARTUP_FINAL_OFFSET(compareSecond,0x4b0);
STARTUP_FINAL_OFFSET(skill,0x4b8);STARTUP_FINAL_OFFSET(foldout,0x4c0);STARTUP_FINAL_OFFSET(menuManager,0x588);
STARTUP_FINAL_OFFSET(console,0x1690);STARTUP_FINAL_OFFSET(freeEvents,0x1698);STARTUP_FINAL_OFFSET(activeEvents,0x16a0);
#undef STARTUP_FINAL_OFFSET
struct MasterConsoleState {char prefix[0xa0];CConsole* console;};
typedef char master_console_offset[__builtin_offsetof(MasterConsoleState,console)==0xa0?1:-1];
inline __attribute__((always_inline)) void finalize(CGameUI* self,PrefixState& ui,SceneState& scenes,SheetState& sheets,MenuState& menus,FinalState& out) {
    out.equipment=new CEquipmentTooltip(sheets.top);
    out.equipment->load(self,L"media/UI/tooltip.layout");
    out.compareFirst=new CEquipmentTooltip(sheets.top);
    out.compareFirst->load(self,L"media/UI/tooltipcompare.layout");
    out.compareSecond=new CEquipmentTooltip(sheets.top);
    out.compareSecond->load(self,L"media/UI/tooltipcompare.layout");
    out.skill=new CSkillTooltip(self,sheets.top);
    out.skill->load(self,L"media/UI/skilltooltip.layout");
    out.foldout=new CSkillFoldout(self,sheets.top);
    out.foldout->load(self,L"media/UI/skillfoldout.layout");
    CEGUI::Window* consoleRoot=CEGUI::System::getSingleton().getGUISheet();
    CConsole* console=new CConsole(self,menus.resources,consoleRoot);
    out.console=console;
    reinterpret_cast<MasterConsoleState*>(CMasterResourceManager::getSingleton())->console=console;
    if(ui.settings->GetInt(KSETTINGS_DISPLAY_STATS))self->toggleFPS();
    out.activeEvents=new TextEventList;
    out.freeEvents=new TextEventList;
    for(unsigned i=0;i<100;++i) {
        CTextEvent* event;
        {
            std::string text("");
            CEGUI::colour first(1.f,1.f,1.f,1.f);
            CEGUI::colour second(1.f,1.f,1.f,1.f);
            event=new CTextEvent(text,first,second);
        }
        event->createText(self,sheets.ingame);
        out.freeEvents->prepend(event);
    }
    out.menuManager=new CMenuManager(*self,*ui.settings,scenes.camera,ui.scene,sheets.sheet,menus.resources);
}
}
#endif
