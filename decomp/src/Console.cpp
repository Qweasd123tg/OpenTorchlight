
#include "GameClient.h"
#include "Player.h"
#include "CameraShake.h"
#include "CameraControl.h"
#include "SpawnClassParser.h"

#include "EmptyStrings.h"
#include "Console.h"
#include "StringUtilities.h"
#include "CEGUIWindowManager.h"


bool CConsole::getVisible()
{
    return m_window ? m_window->isVisible(false) : false;
}

bool CConsole::handleClose(const CEGUI::EventArgs&)
{
    setVisible(false);
    return true;
}

std::wstring CConsole::getHistoryText()
{
    std::wstring text = EMPTY_WSTRING;
    if (m_historyWindow)
        text = STRINGS::StringConvertToWide(m_historyWindow->getText().c_str(), 5000);
    return text;
}

CConsole::~CConsole()
{
    CEGUI::WindowManager::getSingleton().destroyWindow(m_window);
    m_window = NULL;
    m_inputWindow = NULL;
}

template TArrayList<std::wstring>::~TArrayList();

void CConsole::keyEvent(unsigned int, unsigned int, long)
{
}

void CConsole::cameraShake(std::wstring name)
{
    name = STRINGS::StringUpper(name);
    CCameraShake* shake = new CCameraShake(name, Ogre::Vector3(0.0f, 1.0f, 0.0f), 1.0f);
    CCameraControl* camera = m_resources->getCameraControl();
    TSafePointer<CCameraShake>* reference =
        OGRE_NEW_T(TSafePointer<CCameraShake>, Ogre::MEMCATEGORY_GENERAL)();
    reference->setObject(shake);
    reinterpret_cast<TArrayList<TSafePointer<CCameraShake>*>*>(camera->m_Unknown58)->add(reference);
}

void CConsole::spawnClassCreate(std::wstring name, std::wstring count, std::wstring level)
{
    if (!m_resources->getLevel() || !m_gameClient->getPlayer()) return;
    CSpawnClass* spawn = CSpawnClassParser::getSingleton()->getSpawnClass(name);
    if (!spawn) return;
    unsigned int quantity = STRINGS::GetInt(count);
    int parsedLevel = STRINGS::GetInt(level);
    unsigned int unitLevel = level.empty() ? static_cast<unsigned int>(-1) : parsedLevel;
    std::wstring checkedCount = STRINGS::GetValueAsWString(quantity);
    std::wstring checkedLevel = STRINGS::GetValueAsWString(unitLevel);
    if (checkedCount == count && checkedLevel == level) {
        CPlayer* player = m_gameClient->getPlayer();
        CLevel* currentLevel = m_resources->getLevel();
        Ogre::Vector3 position = player->getPosition(true);
        m_resources->createUnitsBySpawnClassAtPositionInLevel(spawn, quantity, position,
                                                             currentLevel, player, player, unitLevel);
    }
}

void CConsole::equipSkillToPlayer(std::wstring name)
{
    CPlayer* player = m_gameClient->getPlayer();
    if (player) {
        player->addSkillByName(name, false);
        player->setActiveSkillByName(name);
    }
    addTextNoHistory(L"\tAdded skill: " + name);
}

void CConsole::addSpeedToPlayer()
{
    CPlayer* player = m_gameClient->getPlayer();
    if (!player) return;
    if (player->removeAffix(L"PLAYER_SPEED_UP")) {
        addTextNoHistory(L"\tRemoved speed boost from player.");
    } else {
        player->addAffix(L"PLAYER_SPEED_UP", 1, player, -1.0f);
        addTextNoHistory(L"\tAdded speed boost to player.");
    }
}

void CConsole::setVisible(bool visible)
{
    if (m_window) {
        if (visible) {
            m_window->setVisible(true);
            m_window->activate();
            m_window->moveToFront();
            m_inputWindow->setText("");
        } else m_window->setVisible(false);
    }
}
