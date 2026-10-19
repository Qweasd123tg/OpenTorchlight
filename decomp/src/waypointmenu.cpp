#include <CEGUIInputEvent.h>
#include "WaypointMenu.h"
#include "GameClient.h"
#include "Character.h"
#include "Item.h"

void CWaypointMenu::update(float)
{
    if (!m_bUnknown30 && !m_bUnknown31) {
        m_bUnknown31 = true;
        CGameClient* client = m_pGameUI->m_gameClient;
        client->m_selectedItem.setObject(NULL);
        client->m_targetItem.setObject(NULL);
        client->m_selectedCharacter.setObject(NULL);
        client->m_targetCharacter.setObject(NULL);
    }
}

bool CWaypointMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    CGameUI* ui = m_pGameUI;
    ui->m_bExitButtonPressed = true;
    ui->closeAll();
    return true;
}

bool CWaypointMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button != CEGUI::LeftButton) return true;
    return CDropdownMenu::handle_CloseButton(event);
}

#include "Player.h"
#include "DungeonTracker.h"
#include "DungeonManager.h"
#include "Dungeon.h"
#include "LevelTemplateData.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
#include "FileSystem.h"
#include "EmptyStrings.h"
#include <CEGUIWindowManager.h>

bool CWaypointMenu::onClick(ELayoutFunction function, std::wstring)
{
    if (m_bUnknown30) {
        if (static_cast<unsigned int>(function) == 8) {
            m_bUnknown32 = true;
        } else if (static_cast<unsigned int>(function) >= 14 && static_cast<unsigned int>(function) <= 63) {
            int index = static_cast<unsigned int>(function) - 14;
            if (index < static_cast<int>(m_destinations.size()))
                m_pGameUI->getGameClient()->warpLevels(m_destinations[index],0,m_floors[index],true,EMPTY_WSTRING,false);
        }
        setOpen(false);
    }
    return true;
}

void CWaypointMenu::setOpen(bool open)
{
    if (m_bUnknown30 != open) m_pGameUI->setInteractiveMenuVisible(open);
    if (m_bUnknown30 && !open) {
        static_cast<CEGUI::Window*>(m_pUnknown10)->removeChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
        m_bUnknown31 = false;
    } else if (!m_bUnknown30 && open) {
        m_bUnknown31 = false;
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
        static_cast<CEGUI::Window*>(m_pUnknown20)->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
        static_cast<CEGUI::Window*>(m_pUnknown10)->addChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
        static_cast<CEGUI::Window*>(m_pUnknown18)->moveToBack();
    }
    m_bUnknown30 = open;
    if (!open) {
        CGameClient* client = m_pGameUI->getGameClient();
        client->getMouseClickUnit(3).setObject(NULL);
        client->getMouseClickUnit(2).setObject(NULL);
        client->getMouseClickUnit(0).setObject(NULL);
        client->getMouseClickUnit(1).setObject(NULL);
        return;
    }
    static std::wstring g_Waypoints;
    if (g_Waypoints.empty()) g_Waypoints = CStringTranslate::getSinglton()->getTranslateString(L"Waypoints");
    static std::wstring g_Floor;
    if (g_Floor.empty()) g_Floor = CStringTranslate::getSinglton()->getTranslateString(L"Floor");
    setTitle(g_Waypoints);
    CPlayer* player = m_pGameUI->getGameClient()->getPlayer();
    int count = player->m_dungeonTrackers.size();
    for (unsigned int i = 0; i < 50; ++i) {
        if (m_destinationWindows[i]) {
            m_destinationWindows[i]->setVisible(false);
            m_floorWindows[i]->setVisible(false);
        }
    }
    m_destinations.clear();
    m_floors.clear();
    int index = 0;
    for (int i = 0; i < count; ++i) {
        CDungeonTracker* tracker = player->m_dungeonTrackers[i];
        for (unsigned int j = 0; j < tracker->m_levels.size(); ++j) {
            if (index > 48 || !m_destinationWindows[index]) continue;
            int depth = tracker->m_levels[j];
            CDungeon* dungeon = CDungeonManager::getSingleton()->getDungeonByName(tracker->m_name);
            if (!dungeon) continue;
            CLevelTemplateData* data = dungeon->getLevelTemplateDataForDepth(m_pGameUI->getGameClient(),depth);
            std::wstring label = EMPTY_WSTRING;
            if (data->m_showFloorNumber)
                label = data->m_levelName + L" - " + g_Floor + L" " + STRINGS::GetValueAsWString(static_cast<int>(static_cast<unsigned int>(depth)+1u));
            else label = data->m_levelName;
            m_destinationWindows[index]->setVisible(true);
            m_floorWindows[index]->setVisible(true);
            std::string text = STRINGS::StringConvertToUTF8(label);
            m_floorWindows[index]->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(text.c_str())));
            m_destinations.push_back(tracker->m_name);
            m_floors.push_back(depth);
            ++index;
        }
    }
}

void CWaypointMenu::createMenus()
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/waypointmenu.layout",info,false,true,false);
    CEGUI::Window* layout = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName),true);
    m_pGameUI->convertToScreenScale(layout,false);
    m_pGameUI->mapToFunctions(layout);
    mapEventHandlers(layout);
    for (unsigned int i = 0; i < 50; ++i) {
        m_destinationWindows[i] = layout->recursiveChildSearch(CEGUI::String("Button"+STRINGS::GetValueAsString(i+1)));
        m_floorWindows[i] = layout->recursiveChildSearch(CEGUI::String("Choice"+STRINGS::GetValueAsString(i+1)));
    }
    static_cast<CEGUI::Window*>(m_pUnknown20)->addChildWindow(layout);
    m_iUnknown50 = layout->recursiveChildSearch("Title");
}

CWaypointMenu::CWaypointMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui,settings,scene,parent,resources,0), m_bUnknownC0(false), m_bUnknownC1(false), m_destinations(), m_floors()
{
    createMenus();
    static std::wstring g_Waypoints;
    if (g_Waypoints.empty()) g_Waypoints = CStringTranslate::getSinglton()->getTranslateString(L"Waypoints");
    setTitle(g_Waypoints);
}
