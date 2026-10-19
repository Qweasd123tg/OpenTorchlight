

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
    camera->m_cameraShakes.add(reference);
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

static void __attribute__((used)) SetPetsEnabled(CCharacter* character, bool enabled)
{
    if (!character)
        return;
    unsigned int count = character->getFollowerCount();
    for (unsigned int i = 0; i < count; ++i)
    {
        character->getFollower(i)->setEnabled(enabled);
        SetPetsEnabled(character->getFollower(i), enabled);
    }
}

#include "FileSystem.h"
#include "MasterResourceManager.h"
#include "GameVariables.h"
#include <elements/CEGUIEditbox.h>
#include <elements/CEGUIFrameWindow.h>

CConsole::CConsole(CGameUI* ui, CResourceManager* resources, CEGUI::Window* parent)
    : m_parentWindow(parent), m_window(NULL), m_inputWindow(NULL), m_historyWindow(NULL),
      m_historyIndex(0), m_history(10), m_resources(resources), m_gameClient(NULL),
      m_gameUI(NULL), m_logConsole(false)
{
    if (!parent) return;
    m_gameUI = ui;
    m_gameClient = resources->getGameClient(0);
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/console.layout", info, false, true, false);
    m_window = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName), true);
    if (m_window) {
        parent->addChildWindow(m_window);
        m_window->setAlwaysOnTop(true);
        m_window->setDestroyedByParent(false);
        m_window->subscribeEvent(CEGUI::Window::EventKeyDown,
            CEGUI::Event::Subscriber(&CConsole::handleKeyDown, this));
        m_window->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
            CEGUI::Event::Subscriber(&CConsole::handleClose, this));
        m_inputWindow = m_window->getChild(1u);
        m_historyWindow = m_window->getChild(2u);
        CEGUI::Window* submit = m_window->getChild(3u);
        static_cast<CEGUI::Editbox*>(m_inputWindow)->setReadOnly(false);
        m_inputWindow->setEnabled(true);
        m_inputWindow->setAutoRepeatDelay(0.0f);
        m_inputWindow->subscribeEvent(CEGUI::Editbox::EventTextAccepted,
            CEGUI::Event::Subscriber(&CConsole::handleSubmit, this));
        submit->subscribeEvent(CEGUI::Window::EventActivated,
            CEGUI::Event::Subscriber(&CConsole::handleSubmit, this));
        setVisible(false);
        m_logConsole = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_LOG_CONSOLE) > 0;
    }
}

#include "LinuxUtils.h"
#include <CEGUIInputEvent.h>
void CConsole::update(float)
{
    if (!m_inputWindow) return;
    m_inputWindow->moveToFront();
    while (!m_inputWindow->getText().empty()
           && static_cast<signed char>(m_inputWindow->getText().c_str()[0]) <= 32) {
        CEGUI::String tail = m_inputWindow->getText().substr(1);
        m_inputWindow->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(tail.c_str())));
    }
}

bool CConsole::handleKeyDown(const CEGUI::EventArgs& event)
{
    if (!m_inputWindow) return true;
    CEGUI::Key::Scan key = static_cast<const CEGUI::KeyEventArgs&>(event).scancode;
    if (key == CEGUI::Key::ArrowUp) {
        --m_historyIndex;
        if (m_historyIndex < -1) m_historyIndex = -1;
        if (m_historyIndex < 0) m_inputWindow->setText("");
        else {
            std::string text = STRINGS::StringConvertToUTF8(m_history[m_historyIndex]);
            m_inputWindow->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(text.c_str())));
            static_cast<CEGUI::Editbox*>(m_inputWindow)->setCaratIndex(CEGUI::String::npos);
        }
    } else if (key == CEGUI::Key::ArrowDown) {
        ++m_historyIndex;
        if (m_historyIndex > static_cast<int>(m_history.size())) m_historyIndex = m_history.size();
        if (m_historyIndex >= static_cast<int>(m_history.size())) m_inputWindow->setText("");
        else {
            std::string text = STRINGS::StringConvertToUTF8(m_history[m_historyIndex]);
            m_inputWindow->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(text.c_str())));
            static_cast<CEGUI::Editbox*>(m_inputWindow)->setCaratIndex(CEGUI::String::npos);
        }
    } else return key == CEGUI::Key::Tab;
    m_inputWindow->activate();
    return true;
}

bool CConsole::handleSubmit(const CEGUI::EventArgs&)
{
    if (GetAsyncKeyState(9) < 0) return false;
    if (m_inputWindow) {
        std::wstring text = STRINGS::StringConvertToWide(m_inputWindow->getText().c_str(), 5000);
        if (!text.empty()) {
            text += L'\n';
            addText(text);
        }
        m_inputWindow->activate();
        m_inputWindow->setText("");
    }
    return true;
}

#include <queue>
#include <OgreLogManager.h>
#include <elements/CEGUIMultiLineEditbox.h>

void CConsole::addTextNoHistory(std::wstring text)
{
    if (!m_historyWindow) return;
    if (m_logConsole)
        Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToNarrow(text.c_str()), Ogre::LML_CRITICAL, false);
    std::queue<std::wstring> lines;
    STRINGS::TokenizeString(&lines, text, L"\n");
    if (lines.empty()) lines.push(text);
    while (!lines.empty()) {
        std::wstring line = lines.front();
        std::string previous(m_historyWindow->getText().c_str());
        int excess = static_cast<int>(previous.size() + line.size() - 5000);
        previous = previous.substr(excess < 0 ? 0 : excess);
        std::string combined = previous + STRINGS::StringConvertToUTF8(line);
        m_historyWindow->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(combined.c_str())));
        lines.pop();
    }
    static_cast<CEGUI::MultiLineEditbox*>(m_historyWindow)->setCaratIndex(CEGUI::String::npos);
}

void CConsole::addText(std::wstring text)
{
    if (!m_historyWindow) return;
    if (m_logConsole)
        Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToNarrow(text.c_str()), Ogre::LML_CRITICAL, false);
    std::queue<std::wstring> lines;
    STRINGS::TokenizeString(&lines, text, L"\n");
    if (lines.empty()) lines.push(text);
    while (!lines.empty()) {
        std::wstring line = lines.front();
        static_cast<CEGUI::MultiLineEditbox*>(m_historyWindow)->setCaratIndex(CEGUI::String::npos);
        std::string previous(m_historyWindow->getText().c_str());
        int excess = static_cast<int>(previous.size() + text.size() - 5000);
        previous = previous.substr(excess < 0 ? 0 : excess);
        std::string combined = previous + STRINGS::StringConvertToUTF8(line);
        m_historyWindow->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(combined.c_str())));
        m_history.add(line);
        m_historyIndex = m_history.size();
        executeCommandLine(line);
        lines.pop();
    }
}

#include "RoomPieceDataInformation.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
static bool __attribute__((used)) fixRoomPieces(CDataGroup* root)
{
    if (!root || root->GetNumberOfDataGroups() == 0) return false;
    bool modified = false;
    for (unsigned int i = 0; i < root->GetNumberOfDataGroups(); ++i) {
        CDataGroup* object = root->GetDataGroup(i);
        CDataGroup* properties = object->GetDataGroupByName(L"PROPERTIES",false);
        if (properties) {
            const std::wstring& descriptor = properties->GetDataValue(L"DESCRIPTOR",EMPTY_WSTRING);
            if (descriptor == L"Room Piece") {
                CDataGroup* guid = properties->GetDataGroupByName(L"GUID",false);
                if (guid) {
                    std::wstring text = guid->GetDataValue(L"VALUE",EMPTY_WSTRING);
                    if (!text.empty()) {
                        long long requested = STRINGS::GetInt64(text);
                        CRoomPieceDataInformation::CRoomPieceCoreData* room = CMasterResourceManager::getSingleton()->m_pRoomPieceInformation->_GetRoomPieceCoreDataByGuidByClosestGuid(requested);
                        if (room) {
                            guid->SetDataValue(L"VALUE",STRINGS::GetValueAsWString(room->m_guid),false);
                            modified = true;
                        }
                    }
                }
            } else if (descriptor == L"Sound") {
                CDataGroup* guid = properties->GetDataGroupByName(L"GUID",false);
                if (guid) {
                    std::wstring text = guid->GetDataValue(L"VALUE",EMPTY_WSTRING);
                    if (!text.empty()) {
                        long long requested = STRINGS::GetInt64(text);
                        CSoundData* sound = CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation->getSoundDataObjectByGuidThatIsClosest(requested);
                        if (sound) {
                            guid->SetDataValue(L"VALUE",STRINGS::GetValueAsWString(sound->m_iGuid),false);
                            modified = true;
                        }
                    }
                }
            }
        }
        CDataGroup* children = object->GetDataGroupByName(L"CHILDREN",false);
        if (children) modified = fixRoomPieces(children) || modified;
    }
    return modified;
}

#include "Level.h"
#include "UnitResourceList.h"
void CConsole::spawnUnit(std::wstring name, std::wstring count)
{
    if (!m_resources->getLevel() || !m_gameClient->getPlayer()) return;
    CPlayer* player = m_gameClient->getPlayer();
    Ogre::Vector3 position = player->getPosition(true);
    Ogre::Vector3 forward = player->getForward();
    Ogre::Vector3 right = player->getRight();
    unsigned int quantity = STRINGS::GetInt(count);
    if (quantity >= 10001) quantity = 1;
    unsigned int group = 0;
    for (; group < 4; ++group)
        if (m_resources->getMasterResourceList()->getDataGroupByObjectName(gRESOURCE_GROUP_NAMES[group], name))
            break;
    unsigned int index = 0;
    for (unsigned int i = 0; i < quantity; ++i) {
        CBaseUnit* unit = m_resources->createUnit(gRESOURCE_GROUP_NAMES[group].c_str(), name.c_str(),
                                                m_resources->getLevel()->getDungeonDepth(), false);
        if (!unit) return;
        Ogre::Vector3 base(position.x + forward.x, position.y + forward.y, position.z + forward.z);
        unsigned int end = index + 5;
        Ogre::Vector3 open(0,0,0);
        bool different;
        do {
            unsigned int row = index / 10;
            float spread = float(row) * (row & 1 ? -1.0f : 1.0f);
            float column = float(index % 10);
            Ogre::Vector3 candidate(right.x*spread + (forward.x*column + base.x),
                                    right.y*spread + (forward.y*column + base.y),
                                    right.z*spread + (forward.z*column + base.z));
            ++index;
            open = m_resources->getLevel()->randomOpenItemPosition(candidate, .25f, false);
            different = open != candidate;
        } while (index != end && !different);
        if (index == end) delete unit;
        else m_resources->getLevel()->addUnit(unit, open);
    }
}

#include "Level.h"
#include "Monster.h"
#include "Item.h"
#include "RandomNames.h"
void CConsole::spawnMonster(std::wstring name, std::wstring count, bool champion, int monsterLevel)
{
    if (!m_resources->getLevel() || !m_gameClient->getPlayer()) return;
    CPlayer* player = m_gameClient->getPlayer();
    Ogre::Vector3 position = player->getPosition(true);
    Ogre::Vector3 forward = player->getForward();
    Ogre::Vector3 right = player->getRight();
    unsigned int quantity = STRINGS::GetInt(count);
    if (quantity > 1000) quantity = 1;
    unsigned int index = 0;
    for (unsigned int i = 0; i < quantity; ++i) {
        CMonster* unit = m_resources->createMonster(name.c_str(), monsterLevel, false);
        if (!unit) return;
        Ogre::Vector3 base(position.x + forward.x, position.y + forward.y, position.z + forward.z);
        unsigned int end = index + 5;
        Ogre::Vector3 open(0,0,0);
        bool different;
        do {
            unsigned int row = index / 10;
            float spread = float(row) * (row & 1 ? -1.0f : 1.0f);
            float column = float(index % 10);
            Ogre::Vector3 candidate(right.x*spread + (forward.x*column + base.x),
                                    right.y*spread + (forward.y*column + base.y),
                                    right.z*spread + (forward.z*column + base.z));
            ++index;
            open = m_resources->getLevel()->randomOpenPosition(candidate, 2.0f, false);
            different = open != candidate;
        } while (index != end && !different);
        if (index == end) delete unit;
        else {
            if (champion)
                unit->makeChampion(CRandomNames::getSingleton()->generateName(true),m_resources->getLevel()->getDungeonDepth(),L"CHAMPION");
            m_resources->getLevel()->addCharacter(unit,open,false);
        }
    }
}

void CConsole::spawnItem(std::wstring name, long long guid, std::wstring count)
{
    if (!m_resources->getLevel() || !m_gameClient->getPlayer()) return;
    CPlayer* player = m_gameClient->getPlayer();
    Ogre::Vector3 position = player->getPosition(true);
    Ogre::Vector3 forward = player->getForward();
    Ogre::Vector3 right = player->getRight();
    unsigned int quantity = STRINGS::GetInt(count);
    if (quantity > 1000) quantity = 1;
    unsigned int index = 0;
    for (unsigned int i = 0; i < quantity; ++i) {
        CItem* unit = guid == -1 ? m_resources->createItem(name.c_str(),false,true)
                                : m_resources->createItem(guid,false,true,false);
        if (!unit) return;
        Ogre::Vector3 base(position.x + forward.x, position.y + forward.y, position.z + forward.z);
        unsigned int end = index + 5;
        Ogre::Vector3 open(0,0,0);
        bool different;
        do {
            unsigned int row = index / 10;
            float spread = float(row) * (row & 1 ? -1.0f : 1.0f);
            float column = float(index % 10);
            Ogre::Vector3 candidate(right.x*spread + (forward.x*column + base.x),
                                    right.y*spread + (forward.y*column + base.y),
                                    right.z*spread + (forward.z*column + base.z));
            ++index;
            open = m_resources->getLevel()->randomOpenItemPosition(candidate, .25f, false);
            different = open != candidate;
        } while (index != end && !different);
        if (index == end) delete unit;
        else {
            m_resources->getLevel()->addItem(unit,open,true);
            m_resources->getGameClient(0)->getPlayer()->setCheater();
        }
    }
}

#include "Level.h"
#include "Layout.h"
#include "DescriptorManager.h"
#include "EmptyStrings.h"
#include "GenericModel.h"
void CConsole::createObjectByName(std::wstring name, std::wstring count)
{
    if (!m_resources->getLevel() || !m_gameClient->getPlayer()) return;
    unsigned int quantity = STRINGS::GetInt(count);
    if (quantity >= 100001) quantity = 1;
    CLayout layout(m_resources,static_cast<ELAYOUT_TYPES>(0));
    CDescriptor* descriptor = layout.GetDescriptorInSceneByName(name.c_str(),true);
    if (descriptor) {
        for (unsigned int i = 0; i < quantity; ++i) {
            CEditorBaseObject* object = layout.CEditorScene::CreateObjectByDescriptor(descriptor,NULL,NULL,true);
            if (name == L"Generic Model") {
                CGenericModel* model = dynamic_cast<CGenericModel*>(object);
                model->loadModel(L"media/models/skeleton/skeleton.MESH",EMPTY_WSTRING,false,false,false);
            }
        }
        addTextNoHistory(L" Created " + STRINGS::GetValueAsWString(quantity) + L" " + name + L"(s).");
    } else {
        addTextNoHistory(L"Unknown object type. Valid types follow..");
        std::vector<CDescriptor*>& descriptors = layout.getDescriptorManager()->getDescriptorVector();
        for (unsigned int i = 0; i < descriptors.size(); ++i)
            addTextNoHistory(STRINGS::GetValueAsWString(i) + L" ) " + descriptors[i]->m_sName);
    }
}
#include "ConsoleData.h"
#include "GameUI.h"
#include "Monster.h"
#include "TRepository.h"
#include "Achievements.h"
#include "Achievement.h"
#include "UnitResourceList.h"
#include "DungeonManager.h"
#include "Dungeon.h"
#include "Inventory.h"
#include "QuestManager.h"
#include "Quest.h"
#include "SkillParser.h"
#include "ParticlePreloader.h"
#include "SoundManager.h"
#include "EditorScene.h"
#include "Layout.h"
#include "FileUtilities.h"
#include "LinuxUtils.h"
#include "Settings.h"
#include <OgreMeshManager.h>
#include <OgreLogManager.h>
#include <OgreUTFString.h>
#include <elements/CEGUIMultiLineEditbox.h>
#include <queue>
#include <cstdlib>

extern unsigned int KSETTINGS_AI_FREEZE;
extern unsigned int KSETTINGS_DISPLAY_PATHING;
extern unsigned int KSETTINGS_F_ANIMATION_FPS;
extern unsigned int KSETTINGS_F_PARTICLEFPS;
extern unsigned int KSETTINGS_SHOW_MISSILE_TRAILS;
extern unsigned int KSETTINGS_SOUND_DEBUG;
extern bool m_gAllowSkillTesting;
#include <ParticleUniverseSystemManager.h>

void CConsole::executeCommandLine(std::wstring input)
{
    std::wstring originalCase = STRINGS::replaceWString(std::wstring(input.c_str()), L"\n", L"");
    std::wstring command = STRINGS::StringUpper(originalCase);
    while (!command.empty() && command[0] <= 0x40)
        command = command.substr(1, command.size() - 1);
    if (command == L"HELP" || command == L"?") {
        addTextNoHistory(gTEXT_HELP);
        static_cast<CEGUI::MultiLineEditbox*>(m_historyWindow)->setCaratIndex(std::wstring::npos);
        return;
    }
    if (command == L"CLS") { m_historyWindow->setText(""); return; }
    if (command == L"ACHIEVEMENTS") {
        addTextNoHistory(CAchievements::getSingleton()->getAchievementStatus());
        std::wstring status = CAchievements::getSingleton()->getAchievementStatus();
        Ogre::LogManager::getSingleton().logMessage(
            STRINGS::StringConvertToUTF8(std::wstring(status.c_str())), Ogre::LML_CRITICAL, false);
        return;
    }
    if (command == L"DEBUGLOGIC") {
        bool enabled = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_DEBUG_LOGIC) == 0;
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_DEBUG_LOGIC, enabled);
        addTextNoHistory(enabled ? L"Logic Debug turned on" : L"Logic Debug turned off");
        return;
    }
    if (command == L"HIDEUI" || command == L"SHOWUI") {
        m_gameClient->getGameUI()->setIngameUIVisible(command == L"SHOWUI");
        addTextNoHistory(command == L"SHOWUI" ? L"UI shown" : L"UI hidden"); return;
    }
    if (command == L"DOICHEAT") {
        if (!m_gameClient->getPlayer()) return;
        addTextNoHistory(m_gameClient->getPlayer() && m_gameClient->getPlayer()->m_cheatMarker == 214
                         ? L"Yes, you do cheat." : L"No, you don't cheat."); return;
    }
    if (command == L"MODS") {
        TArrayList<std::wstring> mods(10);
        CFileSystem::getSingleton()->getEnabledModNames(&mods);
        for (unsigned int i = 0; i < mods.size(); ++i) addTextNoHistory(mods[i]);
    }
    if (command == L"ROOM") {
        Ogre::Vector3 position = m_gameClient->getPlayer()->getPosition(true);
        CEditorScene* room = m_resources->getLevel()->getRoomThatPositionIsIn(position);
        addTextNoHistory(room ? L"Player is in room file : " + room->getLoadedFilename()
                             : L"Unable to determine the room the player is in."); return;
    }
    if (command == L"MEMTEST") {
        MessageBox(NULL, L"Creating 1000 monsters", L"Here goes nothing", 0);
        for (int i = 0; i != 1000; ++i) delete m_resources->createMonster(L"Goblin Stabber", 0, false);
        MessageBox(NULL, L"DONE Creating 1000 monsters", L"Good?", 0);
        MessageBox(NULL, L"Creating 1000 players", L"Here goes nothing", 0);
        for (int i = 0; i != 1000; ++i) delete m_resources->createPlayer(L"DESTROYER", false);
        MessageBox(NULL, L"DONE Creating 1000 players", L"Good?", 0); return;
    }
    if (command == L"FIXGUIDS") {
        std::vector<std::wstring> paths;
        paths.push_back(L"MEDIA/layouts/crypt/1x1_NE_JD_A.layout");
        paths.push_back(L"MEDIA/layouts/crypt/1x1_W_JD_A.layout");
        for (unsigned int i = 0; i < paths.size(); ++i) {
            CDataGroup root(L"", NULL, 20, 10, NULL);
            root.LoadFile(paths[i], NULL);
            CDataGroup* objects = root.GetDataGroupByName(L"OBJECTS", false);
            if (objects && fixRoomPieces(objects)) {
                std::wstring filename(paths[i]);
                _WIN32_FIND_DATA data = FILESYSTEM::GetFileData(filename);
                if (data.attributes & 1) {
                    std::string path = STRINGS::StringConvertToNarrow(filename.c_str());
                    path = STRINGS::replaceString(path, "/", "\\");
                    std::string shell = "TortoiseProc /command:lock /path:\"" + path + "\" /closeonend:1";
                    std::system(shell.c_str());
                }
                root.SaveToFile(paths[i]);
            }
        }
        return;
    }
    if (command == L"SAVEME") m_resources->getGameClient(0)->saveCharacter(false, false);
    if (command == L"WATCHPLAYER" || command == L"WATCH" || command == L"WATCH PLAYER") {
        m_resources->getGameClient(0)->m_cameraWatchTarget = NULL; return;
    }
    if (command == L"WATCHPET") {
        CGameClient* client = m_resources->getGameClient(0);
        client->m_cameraWatchTarget = client->getPlayer()->getFollower(0); return;
    }
    if (command == L"DISABLEPET") {
        CPlayer* player = m_resources->getGameClient(0)->getPlayer();
        bool enabled = !player->getFollower(0)->getEnabled();
        SetPetsEnabled(player, enabled);
        addTextNoHistory(enabled ? L"\tPets Enabled." : L"\tPets Disabled."); return;
    }
    if (command == L"FIXPET") {
        CGameClient* client = m_resources->getGameClient(0);
        CLevel* level = client->m_level;
        CPlayer* player = client->getPlayer();
        if (level && player) {
            player->removePets();
            CMonster* pet = level->m_resourceManager->createMonster(L"Dog", 0, false);
            if (!pet) return;
            pet->setAlignment(static_cast<EAlignment>(1));
            Ogre::Vector3 position = player->getPosition(false);
            Ogre::Vector3 open = level->randomOpenPosition(position, 5.0f, false);
            CCharacter* added = level->addCharacter(pet, open, false);
            added->setMaximumTreeDepth(800);
            added->m_bInvulnerable = true;
            added->m_petMode = 2;
            added->m_characterDisplayName = m_gameUI->m_name16B8;
            player->addPet(added);
        }
    }
    if (command == L"SHOWBLOOD") {
        bool enabled = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHOW_BLOOD) != 1;
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHOW_BLOOD, enabled);
        addTextNoHistory(enabled ? L"\tBlood Enabled." : L"\tBlood Disabled."); return;
    }
    if (command == L"ALWAYSCRIT") {
        CPlayer* player = m_resources->getGameClient(0)->getPlayer();
        bool old = player->m_flag700;
        player->m_flag700 = !old;
        addTextNoHistory(old ? L"\tAlways Crit Disabled." : L"\tAlways Crit Enabled.");
        if (!old) m_resources->getGameClient(0)->getPlayer()->setCheater();
    }
    if (command == L"NOXP") {
        CPlayer* player = m_resources->getGameClient(0)->getPlayer();
        bool disabled = !player->m_experienceDisabled;
        player->m_experienceDisabled = disabled;
        m_resources->getGameClient(0)->getPlayer()->getFollower(0)->m_experienceDisabled = disabled;
        addTextNoHistory(disabled ? L"\tNo Xp Enabled." : L"\tNo Xp Disabled.");
    }
    if (command == L"HOWHARD" || command == L"DIFFICULTY") {
        switch (m_resources->getGameClient(0)->m_startDifficulty) {
        case 0: addTextNoHistory(L"EASY"); break;
        case 1: addTextNoHistory(L"NORMAL"); break;
        case 2: addTextNoHistory(L"HARD"); break;
        case 3: addTextNoHistory(L"VERYHARD"); break;
        }
    }
    if (command == L"IDENTIFYALL" || command == L"IDALL") {
        CPlayer* player = m_resources->getGameClient(0)->getPlayer();
        if (player) {
            player->getInventory()->identifyAll();
            CCharacter* pet = player->getFollower(0);
            if (pet) pet->getInventory()->identifyAll();
            m_resources->getGameClient(0)->getPlayer()->setCheater();
        }
        addTextNoHistory(L"All items identified."); return;
    }
    if (command == L"RESETPLAYER") {
        CPlayer* player = m_resources->getGameClient(0)->getPlayer();
        player->resetLevel(); addTextNoHistory(L"Player Level reset");
        CCharacter* pet = player->getFollower(0);
        if (pet) { pet->setLevel(1, false); addTextNoHistory(L"Player Level reset"); }
        player->resetStatPoints(); addTextNoHistory(L"Stat points reset");
        player->resetSkills(); addTextNoHistory(L"Skills reset");
        m_resources->getGameClient(0)->getPlayer()->setCheater(); return;
    }
    if (command == L"RESETSTATS" || command == L"RESETSKILLS" || command == L"RESETPLAYERLEVEL") {
        CPlayer* player = m_resources->getGameClient(0)->getPlayer();
        if (command == L"RESETSTATS") { player->resetStatPoints(); addTextNoHistory(L"Stat points reset"); }
        else if (command == L"RESETSKILLS") { player->resetSkills(); addTextNoHistory(L"Skills reset"); }
        else { player->resetLevel(); addTextNoHistory(L"Player Level reset"); }
        m_resources->getGameClient(0)->getPlayer()->setCheater(); return;
    }
    if (command == L"CLEARSTRINGS") {
        CDataGroup root(L"", NULL, 20, 10, NULL);
        root.getRepository()->clear(); addTextNoHistory(L"Clear String"); return;
    }
    if (command == L"RESETPETLEVEL") {
        CCharacter* pet = m_resources->getGameClient(0)->getPlayer()->getFollower(0);
        if (!pet) return;
        pet->setLevel(1, false); addTextNoHistory(L"Pet Level reset");
        m_resources->getGameClient(0)->getPlayer()->setCheater(); return;
    }
    if (command == L"PLAYERNOTARGET") {
        int old = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_PLAYER_UNTARGETABLE);
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_PLAYER_UNTARGETABLE, old == 0);
        if (!CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_PLAYER_UNTARGETABLE)) {
            addTextNoHistory(L"Player can be targeted"); return;
        }
        addTextNoHistory(L"Player IS NOT TARGETABLE");
        m_resources->getGameClient(0)->getPlayer()->setCheater(); return;
    }
    if (command == L"WATCHRANDOM") {
        CCharacter* monster = m_resources->getLevel()->getRandomMonster();
        m_resources->getGameClient(0)->m_cameraWatchTarget = monster; return;
    }
    if (command == L"MISSILETRAILS" || command == L"MISSILE TRAILS") {
        int old = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHOW_MISSILE_TRAILS);
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHOW_MISSILE_TRAILS, old == 0);
        addTextNoHistory(L"\tMissile Trails."); return;
    }
    if (command == L"DAMAGE SHAPES") {
        bool enabled = !CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHOW_DAMAGE_SHAPES);
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHOW_DAMAGE_SHAPES, enabled);
        addTextNoHistory(enabled ? L"\tDamage Shapes Enabled." : L"\tDamage Shapes Disabled."); return;
    }
    if (command == L"KILLALL") {
        m_resources->getLevel()->killAll(); addTextNoHistory(L"\tKilled all monsters.");
        m_resources->getGameClient(0)->getPlayer()->setCheater(); return;
    }
    if (command == L"QUESTS") {
        TArrayList<std::wstring> names(10);
        m_gameClient->getPlayer()->getQuestManager()->getQuestNames(names);
        for (unsigned int i = 0; i < names.size(); ++i)
            addTextNoHistory((Ogre::UTFString(STRINGS::GetValueAsWString(i)) + Ogre::UTFString(") ") + Ogre::UTFString(names[i])).asWStr());
    }
    if (command.find(L"QUESTSTRATA") == 0) {
        if (command == L"QUESTSTRATA1") {
            if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater();
            executeCommandLine(L"QUESTCOMPLETE IntroQuest");
            executeCommandLine(L"QUESTCOMPLETE IntroGreets");
            executeCommandLine(L"QUESTCOMPLETE MeetHenchmenGreets");
            executeCommandLine(L"QUESTCOMPLETE KeepLookingForMercs");
            executeCommandLine(L"QUESTCOMPLETE DefeatFirstBoss");
            executeCommandLine(L"QUESTACTIVE ContinueToLookForNicola");
        }
        if (command == L"QUESTSTRATA2") {
            if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater();
            executeCommandLine(L"QUESTSTRATA1");
            executeCommandLine(L"QUESTCOMPLETE ContinueToLookForNicola");
            executeCommandLine(L"QUESTCOMPLETE CryptQuestPt1_1");
            executeCommandLine(L"QUESTCOMPLETE GhostSisters");
            executeCommandLine(L"QUESTCOMPLETE CryptQuestPt2");
            executeCommandLine(L"QUESTCOMPLETE CRYPTQUESTPT2");
            executeCommandLine(L"QUESTACTIVE ruinsPt1");
        }
        if (command == L"QUESTSTRATA3") {
            if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater();
            executeCommandLine(L"QUESTSTRATA2");
            executeCommandLine(L"QUESTCOMPLETE ruinsPt1");
            executeCommandLine(L"QUESTCOMPLETE glyph1");
            executeCommandLine(L"QUESTCOMPLETE glyph2");
            executeCommandLine(L"QUESTCOMPLETE glyph3");
            executeCommandLine(L"QUESTCOMPLETE ruinsPt2");
            executeCommandLine(L"QUESTCOMPLETE beatBoss3");
            executeCommandLine(L"QUESTACTIVE CavePt1");
            executeCommandLine(L"QUESTACTIVE CaveRandomShakes");
        }
        if (command == L"QUESTSTRATA4") {
            if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater();
            executeCommandLine(L"QUESTSTRATA3");
            executeCommandLine(L"QUESTCOMPLETE CaveRandomShakes");
            executeCommandLine(L"QUESTCOMPLETE CavePt1");
            executeCommandLine(L"QUESTCOMPLETE CaveDefeatBoss");
            executeCommandLine(L"QUESTACTIVE LavaPt1");
        }
        if (command == L"QUESTSTRATA5") {
            if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater();
            executeCommandLine(L"QUESTSTRATA4");
            executeCommandLine(L"QUESTCOMPLETE LavaPt1");
            executeCommandLine(L"QUESTCOMPLETE LavaPt2");
            executeCommandLine(L"QUESTCOMPLETE LavaDefeatBoss");
            executeCommandLine(L"QUESTACTIVE fortressPt1");
        }
    }
    if (command == L"FPS") { m_gameUI->toggleFPS(); return; }
    if (command == L"RELOAD") {
        Ogre::MeshManager::getSingleton().reloadAll(true); addTextNoHistory(L"\tReloaded"); return;
    }
    if (command == L"RESTARTLEVEL") {
        if (!m_gameClient->m_currentDungeon || !m_gameClient->m_level) return;
        std::wstring dungeon = m_gameClient->m_currentDungeon->m_sName;
        int depth = m_gameClient->m_level->getLevelDepth();
        addTextNoHistory(L"Restarting current level...");
        m_gameClient->warpLevels(dungeon, 0, depth, false, EMPTY_WSTRING, true); return;
    }
    if (command == L"SKILLTEST") {
        if (m_gAllowSkillTesting) {
            m_gAllowSkillTesting = false; addTextNoHistory(L"Disabling use of all Skills."); return;
        }
        m_gAllowSkillTesting = true; addTextNoHistory(L"Allowing use of all skills for Testing");
        m_resources->getGameClient(0)->getPlayer()->setCheater(); return;
    }
    if (command == L"SKILL" || command == L"SKILLS") {
        TArrayList<std::wstring> names(10); CSkillParser::getSkillNames(names);
        for (unsigned int i = 0; i < names.size(); ++i)
            addTextNoHistory(STRINGS::GetValueAsWString(i) + L") " + names[i]);
        return;
    }
    if (command == L"PATHING" || command == L"SOUNDDEBUG" || command == L"COMBATLOG") {
        unsigned int key = command == L"PATHING" ? KSETTINGS_DISPLAY_PATHING :
                           command == L"SOUNDDEBUG" ? KSETTINGS_SOUND_DEBUG : KSETTINGS_COMBAT_LOG;
        bool enabled = !CMasterResourceManager::getSingleton()->m_pSettings->GetInt(key);
        if (command == L"PATHING") addTextNoHistory(enabled ? L"\tPathing debug enabled" : L"\tPathing debug disabled");
        else if (command == L"SOUNDDEBUG") addTextNoHistory(enabled ? L"\tSound debug enabled" : L"\tSound debug disabled");
        else addTextNoHistory(enabled ? L"\tCombat log enabled" : L"\tCombat log disabled");
        key = command == L"PATHING" ? KSETTINGS_DISPLAY_PATHING :
              command == L"SOUNDDEBUG" ? KSETTINGS_SOUND_DEBUG : KSETTINGS_COMBAT_LOG;
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(key, enabled); return;
    }
    if (command == L"LEVELUP") {
        if (!m_gameClient->getPlayer()) return;
        int gate = CMasterResourceManager::getSingleton()->experienceGate(m_gameClient->getPlayer()->m_iUnitLevel);
        CCharacter* player = m_gameClient->getPlayer();
        player->awardExperience(*m_gameClient->m_level, NULL, gate - player->m_experience, false);
        m_gameClient->getPlayer()->setCheater(); return;
    }
    if (command == L"GOD" || command == L"GODSPEED") {
        if (m_gameClient->getPlayer()) {
            m_gameClient->getPlayer()->m_godMode = !m_gameClient->getPlayer()->getIsInGodMode();
            if (m_gameClient->getPlayer()->getIsInGodMode()) {
                addTextNoHistory(L"\tGod mode turned on"); m_gameClient->getPlayer()->setCheater();
            } else addTextNoHistory(L"\tGod mode turned off");
        }
        if (command != L"GODSPEED") return;
    }
    if (command == L"SPEED" || command == L"GODSPEED") {
        addSpeedToPlayer(); m_gameClient->getPlayer()->setCheater(); return;
    }
    if (command == L"ASCEND") {
        m_gameClient->warpLevels(L"", -1, 0, false, EMPTY_WSTRING, true);
        addTextNoHistory(L"\tAscending"); return;
    }
    if (command == L"DESCEND") {
        std::wstring dungeon = STRINGS::StringUpper(m_gameClient->m_currentDungeon->m_sName);
        int depth;
        if (dungeon == L"TOWN") { dungeon = L"MAIN"; depth = 0; }
        else depth = m_gameClient->m_level->getLevelDepth() + 1;
        m_gameClient->warpLevels(dungeon, 1, depth, false, EMPTY_WSTRING, true);
        addTextNoHistory(L"\tDescending in dungeon " + dungeon);
        m_gameClient->getPlayer()->setCheater(); return;
    }
    if (command == L"PARTICLEFLUSH") {
        CMasterResourceManager::getSingleton()->m_pParticlePreloader->aggressiveUnloadParticles(); return;
    }
    if (command == L"SOUNDDUMP") {
        CMasterResourceManager::getSingleton()->m_pSoundManager->dumpSounds(); return;
    }
    if (command == L"PARTICLES") {
        std::wstring names;
        CMasterResourceManager::getSingleton()->m_pParticlePreloader->getFileNames(names);
        addTextNoHistory(names);
        Ogre::LogManager::getSingleton().logMessage(
            STRINGS::StringConvertToUTF8(std::wstring(names.c_str())), Ogre::LML_CRITICAL, false); return;
    }
    if (command == L"PARTICLESOFF") {
        CMasterResourceManager::getSingleton()->m_pParticleSystemManager->setParticleFPS(.0001f);
        addTextNoHistory(L"Particles Paused"); return;
    }
    if (command == L"PARTICLESON") {
        CMasterResourceManager::getSingleton()->m_pParticleSystemManager->setParticleFPS(
            static_cast<float>(CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_F_PARTICLEFPS)));
        addTextNoHistory(L"Particles Resumed"); return;
    }
    if (command == L"AIFREEZE") {
        if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_AI_FREEZE)) {
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_AI_FREEZE, 0);
            addTextNoHistory(L"\tAI UNFROZEN"); return;
        }
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_AI_FREEZE, 1);
        addTextNoHistory(L"\tAI FROZE");
        if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater(); return;
    }
    if (command == L"ALLITEMS") {
        std::map<long long, CDataGroup*>* group = m_resources->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[0]);
        for (std::map<long long, CDataGroup*>::iterator i = group->begin(); i != group->end(); ++i)
            spawnItem(L"", i->first, L"1");
        if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater(); return;
    }
    if (command == L"ALLMONSTERS") {
        std::map<long long, CDataGroup*>* group = m_resources->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[1]);
        for (std::map<long long, CDataGroup*>::iterator i = group->begin(); i != group->end(); ++i) {
            Ogre::Vector3 pos = m_resources->getGameClient(0)->getPlayer()->getPosition(true);
            Ogre::Vector3 open = m_resources->getLevel()->randomOpenPosition(pos, 100.0f, false);
            CBaseUnit* unit = m_resources->createUnit(i->second, m_resources->getLevel()->getDungeonDepth(), false, false);
            m_resources->getLevel()->addUnit(unit, open);
        }
        if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater(); return;
    }
    if (command == L"CLEARHISTORY") {
        if (!m_gameClient->getPlayer()) return;
        m_gameClient->getPlayer()->clearLevelHistory(); m_gameClient->getPlayer()->setCheater();
        addTextNoHistory(L"Level save history cleared");
        m_gameClient->getPlayer()->setCheater(); return;
    }
    CDataGroup* data = CUnitResourceList::getSingleton()->getDataGroupByObjectName(command);
    if (data) {
        CBaseUnit* unit = m_resources->createUnit(data, m_resources->getLevel()->getDungeonDepth(), false, false);
        Ogre::Vector3 forward = m_gameClient->getPlayer()->getForward() * 3.0f;
        Ogre::Vector3 position = m_gameClient->getPlayer()->getPosition(false);
        Ogre::Vector3 desired = forward + position;
        Ogre::Vector3 open = m_resources->getLevel()->randomOpenItemPosition(desired, 5.0f, false);
        m_resources->getLevel()->addUnit(unit, open); addTextNoHistory(L"Created " + command); return;
    }
    std::wstring::size_type firstSpace = originalCase.find(L" ");
    if (command == L"SPAWNCLASS") {
        CSpawnClassParser* parser = CSpawnClassParser::getSingleton();
        unsigned int index = 0;
        for (std::map<std::wstring, CSpawnClass*>::iterator i = parser->m_spawnClasses.begin(); i != parser->m_spawnClasses.end(); ++i, ++index)
            addTextNoHistory(STRINGS::GetValueAsWString(index) + L") " + i->first);
        if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater(); return;
    }
    unsigned int type;
    if (command == L"CHAMPION") type = m_resources->getUnitTypeByName(L"MONSTER");
    else type = m_resources->getUnitTypeByName(STRINGS::replaceWString(originalCase, L"_", L" "));
    if (type != 22) {
        TArrayList<CDataGroup*> groups(10);
        m_resources->getMasterResourceList()->getDataGroupsByUnitType(type, groups);
        for (unsigned int i = 0; i < groups.size(); ++i)
            addTextNoHistory(STRINGS::GetValueAsWString(i) + L") " + groups[i]->GetDataValue(L"NAME", EMPTY_WSTRING));
        return;
    }
    if (originalCase.size() < 2 || firstSpace == std::wstring::npos) return;
    std::wstring verb = originalCase.substr(0, firstSpace);
    std::wstring rest = originalCase.substr(firstSpace + 1, originalCase.size() - firstSpace);
    std::queue<std::wstring> tokens;
    TArrayList<std::wstring> args(10);
    STRINGS::TokenizeString(&tokens, std::wstring(rest.c_str()), L",");
    while (!tokens.empty()) { args.add(tokens.front()); tokens.pop(); }
    if (rest != L"" && !args.size()) args.add(rest);
    verb = STRINGS::StringUpper(verb);
    if (verb == L"CAMERADISTANCE") {
        float multiplier = static_cast<float>(STRINGS::GetFloat(args[0]));
        CCameraControl* camera = m_resources->getCameraControl();
        camera->m_fUnknown8C = multiplier;
        camera->m_fUnknown38 = camera->getDefaultDistanceToDolly();
        addTextNoHistory(L"Camera was distance from the player was multiplied by: " + args[0]); return;
    }
    if (verb == L"CHEATACHIEVEMENT") {
        CAchievement* achievement = CAchievements::getSingleton()->getAchievement(STRINGS::StringConvertToNarrow(args[0].c_str()));
        if (!achievement) addTextNoHistory(L"Faile to cheat achievement " + args[0]);
        else {
            achievement->cheat();
            addTextNoHistory(L"Cheated achievement " + STRINGS::StringConvertToWide(achievement->m_strName));
        }
        return;
    }
    if (verb == L"WATCH") {
        CDataGroup* group = m_resources->getMasterResourceList()->getDataGroupByObjectName(args[0]);
        if (group) {
            CBaseUnit* unit = m_resources->getLevel()->getBaseUnitByDataGroup(group);
            if (unit) {
                m_resources->getGameClient(0)->m_cameraWatchTarget = unit;
                addTextNoHistory(L"Watching unit : " + args[0]);
            } else {
                m_resources->getGameClient(0)->m_cameraWatchTarget = NULL;
                addTextNoHistory(L"Watching unit player");
            }
        }
        return;
    }
    if (verb == L"LAYOUT") {
        unsigned int count = 10000;
        if (args.size() > 1) { count = STRINGS::GetInt(args[1]); if (count > 10000) count = 10000; }
        for (unsigned int i = 0; i < count; ++i) {
            CLayout* layout = new CLayout(m_resources, static_cast<ELAYOUT_TYPES>(0));
            layout->loadLayoutFile(args[0], false, NULL, false, false, 0); delete layout;
        }
        return;
    }
    if (verb == L"DUNGEON") {
        std::wstring name(args[0]);
        CDungeon* dungeon = CDungeonManager::getSingleton()->getDungeonByName(name);
        if (!dungeon) {
            CDungeonManager* manager = CDungeonManager::getSingleton();
            for (unsigned int i = 0; i < manager->m_lDungeons.size(); ++i)
                addTextNoHistory(manager->m_lDungeons[i]->m_sName);
        } else {
            m_gameClient->setCurrentDungeon(name);
            addTextNoHistory(L"Current dungeon is now: " + name);
            int depth = m_gameClient->m_level ? m_gameClient->m_level->getLevelDepth() : 0;
            m_gameClient->warpLevels(name, 1, depth, false, EMPTY_WSTRING, true);
            if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater();
        }
    }
    if (verb == L"LEVELUP") {
        if (m_gameClient->getPlayer()) {
            unsigned int count = STRINGS::GetInt(args[0]);
            if (static_cast<int>(count) >= 50) count = 50;
            for (unsigned int i = 0; i < count; ++i) {
                int gate = CMasterResourceManager::getSingleton()->experienceGate(m_gameClient->getPlayer()->m_iUnitLevel);
                CCharacter* player = m_gameClient->getPlayer();
                player->awardExperience(*m_gameClient->m_level, NULL, gate - player->m_experience, false);
            }
            m_gameClient->getPlayer()->setCheater();
        }
        return;
    }
    if (verb == L"SETPETLEVEL") {
        unsigned int level = STRINGS::GetInt(args[0]);
        if (m_gameClient->getPlayer() && m_gameClient->getPlayer()->getFollower(0)) {
            m_gameClient->getPlayer()->getFollower(0)->setLevel(level, false);
            addTextNoHistory(L"Pet Level is now: " + args[0]);
            if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater();
        }
    }
    if (verb == L"HURTME") {
        CCharacter* player = m_gameClient->getPlayer();
        if (player) {
            unsigned int percentage = STRINGS::GetInt(args[0]);
            if (static_cast<int>(percentage) > 99) percentage = 100;
            int hp = player->maxHP();
            float damage = -((static_cast<float>(percentage) / 100.0f) * static_cast<float>(hp));
            player->modifyHP(damage);
            if (player->getFollower(0)) {
                player->getFollower(0)->maxHP();
                player->getFollower(0)->modifyHP(damage);
            }
            addTextNoHistory(L"Ouch."); m_gameClient->getPlayer()->setCheater();
        }
        return;
    }
    if (verb == L"SETDIFFICULTY") {
        if (!args.size()) return;
        unsigned int difficulty = STRINGS::GetInt(args[0]);
        if (difficulty > 3) { addTextNoHistory(L"Invalid difficulty Level:" + args[0]); return; }
        m_resources->getGameClient(0)->m_startDifficulty = difficulty;
        if (m_gameClient->getPlayer()->m_saveOnDeath) m_gameClient->getPlayer()->setCheater();
        switch (m_resources->getGameClient(0)->m_startDifficulty) {
        case 0: addTextNoHistory(L"Difficulty is now: EASY"); break;
        case 1: addTextNoHistory(L"Difficulty is now: NORMAL"); break;
        case 2: addTextNoHistory(L"Difficulty is now: HARD"); break;
        case 3: addTextNoHistory(L"Difficulty is now: VERYHARD"); break;
        }
    }
    if (verb == L"STATPOINTS") {
        if (m_gameClient->getPlayer()) {
            m_gameClient->getPlayer()->giveUnusedStatPoints(STRINGS::GetInt(args[0]));
            addTextNoHistory(L"Stat points given: " + args[0]); m_gameClient->getPlayer()->setCheater();
        }
        return;
    }
    if (verb == L"ALLSTATS") {
        int points = STRINGS::GetInt(args[0]);
        m_gameClient->getPlayer()->giveUnusedStatPoints(points);
        for (int i = 0; i < points; ++i) m_gameClient->getPlayer()->spendMeleePoint();
        m_gameClient->getPlayer()->giveUnusedStatPoints(points);
        for (int i = 0; i < points; ++i) m_gameClient->getPlayer()->spendRangedPoint();
        m_gameClient->getPlayer()->giveUnusedStatPoints(points);
        for (int i = 0; i < points; ++i) m_gameClient->getPlayer()->spendMagicPoint();
        m_gameClient->getPlayer()->giveUnusedStatPoints(points);
        for (int i = 0; i < points; ++i) m_gameClient->getPlayer()->spendDefensePoint();
        addTextNoHistory(L"Gave all stats: " + args[0]); m_gameClient->getPlayer()->setCheater();
    }
    if (verb == L"STRENGTH" || verb == L"DEXTERITY" || verb == L"MAGIC" || verb == L"DEFENSE") {
        if (m_gameClient->getPlayer()) {
            int points = STRINGS::GetInt(args[0]);
            m_gameClient->getPlayer()->giveUnusedStatPoints(points);
            for (int i = 0; i < points; ++i) {
                if (verb == L"STRENGTH") m_gameClient->getPlayer()->spendMeleePoint();
                else if (verb == L"DEXTERITY") m_gameClient->getPlayer()->spendRangedPoint();
                else if (verb == L"MAGIC") m_gameClient->getPlayer()->spendMagicPoint();
                else m_gameClient->getPlayer()->spendDefensePoint();
            }
            const wchar_t* text = verb == L"STRENGTH" ? L"Strength points given: " :
                verb == L"DEXTERITY" ? L"Dexterity points given: " :
                verb == L"MAGIC" ? L"Magic points given: " : L"Defense points given: ";
            addTextNoHistory(text + args[0]); m_gameClient->getPlayer()->setCheater();
        }
        return;
    }
    if (verb == L"FAME") {
        if (m_gameClient->getPlayer()) {
            m_gameClient->getPlayer()->addFame(STRINGS::GetInt(args[0]));
            addTextNoHistory(L"Fame points given: " + args[0]); m_gameClient->getPlayer()->setCheater();
        }
        return;
    }
    if (verb == L"ANIMATIONSPEED") {
        int speed = STRINGS::GetInt(args[0]);
        CMasterResourceManager::getSingleton()->m_pSettings->SetFloat(KSETTINGS_F_ANIMATION_FPS, static_cast<float>(speed));
        addTextNoHistory(L"Changing animation speed to: " + args[0]); return;
    }
    if (verb == L"SKILLPOINTS") {
        if (m_gameClient->getPlayer()) {
            m_gameClient->getPlayer()->giveUnusedSkillPoints(STRINGS::GetInt(args[0]));
            addTextNoHistory(L"Skill points given: " + args[0]); m_gameClient->getPlayer()->setCheater();
        }
        return;
    }
    if (verb == L"ASCEND") {
        int count = STRINGS::GetInt(args[0]);
        if (count < 1) count = 0; if (count > 49) count = 50;
        m_gameClient->warpLevels(L"", -count, 0, false, EMPTY_WSTRING, true);
        addTextNoHistory(L"\tAscending"); return;
    }
    if (verb == L"DESCEND") {
        std::wstring dungeon = STRINGS::StringUpper(m_gameClient->m_currentDungeon->m_sName);
        int count = 1;
        if (args.size()) {
            count = STRINGS::GetInt(args[0]); if (count < 1) count = 0; if (count > 999) count = 1000;
        }
        int depth;
        if (dungeon == L"TOWN") { dungeon = L"MAIN"; depth = count > 0 ? -1 : 0; }
        else depth = m_gameClient->m_level->getLevelDepth();
        m_gameClient->warpLevels(dungeon, 1, static_cast<unsigned int>(count) + depth, false, EMPTY_WSTRING, true);
        addTextNoHistory(L"\tDescending in dungeon " + dungeon); m_gameClient->getPlayer()->setCheater(); return;
    }
    if (verb == L"MONEY") {
        int amount = STRINGS::GetInt(args[0]);
        if (m_gameClient->getPlayer()) {
            m_gameClient->getPlayer()->giveGold(amount); addTextNoHistory(L"\tGave gold.");
            m_gameClient->getPlayer()->setCheater();
        }
        return;
    }
    if (verb == L"CAMERASHAKE") { cameraShake(args[0]); return; }
    if (verb == L"UNIT") {
        if (!args.size()) return;
        spawnUnit(args[0], args.size() == 1 ? L"1" : args[1]);
        if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater(); return;
    }
    if (verb == L"EDITOROBJECT") {
        if (!args.size()) return;
        createObjectByName(args[0], args.size() == 1 ? L"1" : args[1]);
        if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater(); return;
    }
    if (verb == L"SPAWNCLASS") {
        spawnClassCreate(args[0], args.size() == 1 ? L"1" : args[1], args.size() < 3 ? L"" : args[2]);
        if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater(); return;
    }
    if (!args.size()) return;
    unsigned int index = STRINGS::GetInt(args[0]);
    std::wstring normalized = STRINGS::GetValueAsWString(index);
    bool isIndex = args[0] == normalized;
    if (verb == L"SKILL") {
        std::wstring name = args[0];
        if (isIndex) {
            TArrayList<std::wstring> skills(10); CSkillParser::getSkillNames(skills);
            if (index >= skills.size()) { addTextNoHistory(L"\tINVALID SKILL CHOICE"); return; }
            name = skills[index];
        }
        equipSkillToPlayer(name); m_gameClient->getPlayer()->setCheater(); return;
    }
    if (normalized == args[0] && index != static_cast<unsigned int>(-1)) {
        bool champion = verb == L"CHAMPION";
        unsigned int type = m_resources->getUnitTypeByName(STRINGS::replaceWString(verb, L"_", L" "));
        if (champion) type = m_resources->getUnitTypeByName(L"MONSTER");
        if (type != 22) {
            TArrayList<CDataGroup*> groups(10);
            m_resources->getMasterResourceList()->getDataGroupsByUnitType(type, groups);
            if (index >= groups.size()) return;
            if (champion || type != 27 || args.size() >= 2) {
                std::wstring count = args.size() == 1 ? L"1" : args[1];
                std::wstring name = groups[index]->GetDataValue(L"NAME", EMPTY_WSTRING);
                if (champion) spawnMonster(name, count, true, 0);
                else if (type != 27) spawnUnit(name, count);
                else if (args.size() == 2) spawnMonster(name, args[1], false, 0);
                else spawnMonster(name, count, false, STRINGS::GetInt(args[2]));
                if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater();
            }
        }
    }
    // Native numeric selections continue through the named-command handlers.
    if (verb == L"MONSTER" || verb == L"CHAMPION") {
        bool champion = verb == L"CHAMPION";
        if (args.size() == 1) {
            spawnMonster(args[0], L"1", champion, 0);
            if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater();
        }
        if (args.size() == 2) spawnMonster(args[0], args[1], champion, 0);
        else if (args.size() < 3) return;
        else spawnMonster(args[0], args[1], champion, STRINGS::GetInt(args[2]));
        if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater(); return;
    }
    if (verb == L"ITEM") {
        spawnItem(args[0], -1, args.size() == 1 ? L"1" : args[1]);
        if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater();
    }
    if (verb == L"ITEMGUID") {
        spawnItem(L"", STRINGS::GetInt64(args[0]), args.size() == 1 ? L"1" : args[1]);
        if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater();
    }
    if (verb == L"QUESTCOMPLETE" || verb == L"QUESTACTIVE" || verb == L"QUESTRESET") {
        TArrayList<std::wstring> names(10);
        m_gameClient->getPlayer()->getQuestManager()->getQuestNames(names);
        std::wstring name = verb == L"QUESTRESET" ? args[0] : STRINGS::StringUpper(args[0]);
        if (isIndex) name = STRINGS::StringUpper(names[index]);
        CQuest* quest = reinterpret_cast<CQuest*>(CQuestManager::getSingleton()->getQuestByName(name));
        if (!quest) {
            for (unsigned int i = 0; i < names.size(); ++i)
                addTextNoHistory((Ogre::UTFString(STRINGS::GetValueAsWString(i)) + Ogre::UTFString(") ") + Ogre::UTFString(names[i])).asWStr());
            addTextNoHistory(L"Quest name invalid: " + name);
        } else {
            CQuestManager* manager = m_gameClient->getPlayer()->getQuestManager();
            if (verb == L"QUESTCOMPLETE") {
                manager->giveQuest(quest, NULL, false);
                quest->setIsComplete(true); quest->setQuestAcceptDialogInteracted(true);
                m_gameClient->getPlayer()->getQuestManager()->completeQuest(quest);
            } else if (verb == L"QUESTACTIVE") {
                manager->giveQuest(quest, NULL, true);
                quest->setQuestAccepted(true); quest->setQuestAcceptDialogInteracted(true);
            } else manager->resetQuest(quest);
            m_gameClient->getPlayer()->getQuestManager()->update(.01f);
            addTextNoHistory((verb == L"QUESTCOMPLETE" ? L"Quest set to complete: " :
                verb == L"QUESTACTIVE" ? L"Quest set to active: " : L"Quest reset: ") + name);
        }
        if (m_gameClient->getPlayer()) m_gameClient->getPlayer()->setCheater();
    }
}
