#include "MasterResourceManager.h"
#include "Hierarchy.h"
#include "UnitResourceList.h"
#include "EmptyStrings.h"
#include "AnimationPlayerDescriptor.h"
#include "GameVariables.h"
#include "AnimationPlayer.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"

CAnimationPlayerDescriptor::CAnimationPlayerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, false, false, false, false, false)
{
    AddProperty(L"PROPERTIES", L"START ON LOAD", L"If true the animation starts on load.", (void*)Set_setStartOnLoad, (void*)Get_getStartOnLoad, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"BLEND TIME", L"The time which the animation will blend.", (void*)Set_setBlendTime, (void*)Get_getBlendTime, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"BLEND OUT TIME", L"The time which the animation will blend out.", (void*)Set_setBlendOutTime, (void*)Get_getBlendOutTime, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"DURATION OVERRIDE", L"Forces the animation to play this long.", (void*)Set_setForceDuration, (void*)Get_getForceDuration, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"PLAY IDLE", L"When the animation stops it'll blend into an idle.", (void*)Set_setPlayIdle, (void*)Get_getPlayIdle, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"ANIMATION", L"ANIMATION", L"The name of the animation you want the unit to play.", (void*)Set_setAnimationName, (void*)Get_getAnimationName, VARIABLE_TYPE_STRING, 0);
    unsigned int groupProperty = AddPropertyWithInterpreterFunctions(L"UNIT", L"GROUP", L"The group to choose from.", (void*)Set_setCategory, (void*)Get_getCategory, GetGroupIDByString, GetGroupStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    unsigned int unitProperty = AddPropertyWithInterpreterFunctions(L"UNIT", L"UNIT", L"The unit to make path.", (void*)Set_setUnitString, (void*)Get_getUnitString, GetResourceIDByString, GetResourceStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    LinkProperty(unitProperty, groupProperty);
    AddInputLogic(INPUT_EVENT_PLAY_3);
    AddInputLogic(INPUT_EVENT_PLAY_LOOPING);
    AddInputLogic(INPUT_EVENT_STOP_3);
    AddInputLogic(INPUT_EVENT_STOP_AND_IDLE);
    AddOutputLogic(OUTPUT_EVENT_ANIMATION_STOPPED);
    AddOutputLogic(OUTPUT_EVENT_ANIMATION_PLAYING);
}
void CAnimationPlayerDescriptor::descriptorSceneActivated(CEditorScene* scene)
{
    if (scene->getResourceManager()->getEditorIsRunning())
        return;
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CAnimationPlayer* player = dynamic_cast<CAnimationPlayer*>(m_Objects[i]);
        if (player && player->m_bStartOnLoad)
            player->playAnimation(true);
    }
}



CAnimationPlayerDescriptor::~CAnimationPlayerDescriptor()
{
}

unsigned int CAnimationPlayerDescriptor::GetResourceIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring&, void*)
{
    return 0;
}

std::wstring CAnimationPlayerDescriptor::GetGroupStringByID(CEditorScene*, CEditorBaseObject*, unsigned int index, void*)
{
    if (index <= 3)
        return reinterpret_cast<const std::wstring*>(gANIMATIONPLAYER_TYPE_NAMES)[index];

    return reinterpret_cast<const std::wstring*>(gANIMATIONPLAYER_TYPE_NAMES)[0];
}

void CAnimationPlayerDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int eventType, CEditorBaseObject* sender)
{
    CAnimationPlayer* player = dynamic_cast<CAnimationPlayer*>(object);
    if (!player)
        return;

    switch (eventType) {
    case 0x42:
        player->playAnimation(false);
        player->BroadcastEvent(OUTPUT_EVENT_ANIMATION_PLAYING);
        break;
    case 0x43:
        player->playAnimation(true);
        player->BroadcastEvent(OUTPUT_EVENT_ANIMATION_PLAYING);
        break;
    case 0x44:
        player->stopAnimation(false);
        break;
    case 0x45:
        player->stopAnimation(true);
        break;
    }
}

void CAnimationPlayerDescriptor::update(float timeSlice)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CAnimationPlayer* player =
            dynamic_cast<CAnimationPlayer*>(m_Objects[i]);

        if (player != 0) {
            player->update(timeSlice);
        }
    }
}

CEditorBaseObject* CAnimationPlayerDescriptor::CreateObject(CEditorScene* scene)
{
    return new CAnimationPlayer(scene->getResourceManager());
}

unsigned int CAnimationPlayerDescriptor::GetGroupIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring& value, void*)
{
    for (unsigned int index = 0; index < 4; ++index) {
        if (value == gANIMATIONPLAYER_TYPE_NAMES[index])
            return index;
    }
    return 0;
}

std::wstring CAnimationPlayerDescriptor::GetResourceStringByID(CEditorScene*, CEditorBaseObject* object, unsigned int index, void*)
{
    CAnimationPlayer* player = dynamic_cast<CAnimationPlayer*>(object);
    if (player == NULL)
        return EMPTY_WSTRING;
    const std::wstring& category = player->m_sCategory;
    CResourceManager* resources = player->m_pResourceManager;
    if (category == gANIMATIONPLAYER_TYPE_NAMES[0])
        return L"PLAYER";
    const std::map<long long, CDataGroup*>* group;
    if (category == gANIMATIONPLAYER_TYPE_NAMES[1])
        group = resources->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[1]);
    else if (category == gANIMATIONPLAYER_TYPE_NAMES[3]) {
        if (category == gANIMATIONPLAYER_TYPE_NAMES[1])
            group = resources->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[1]);
        else
            group = resources->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[3]);
    }
    else if (category == gANIMATIONPLAYER_TYPE_NAMES[2]) {
        CHierarchy* hierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
        unsigned int type = static_cast<unsigned int>(-1);
        if (index < hierarchy->m_types.size())
            type = hierarchy->m_types[index];
        return CMasterResourceManager::getSingleton()->m_pHierarchy->getTypeName(type);
    }
    else
        return EMPTY_WSTRING;
    for (std::map<long long, CDataGroup*>::const_iterator it = group->begin(); it != group->end(); ++it) {
        if (index == 0)
            return it->second->GetDataValue(L"NAME", EMPTY_WSTRING);
        --index;
    }
    return EMPTY_WSTRING;
}
