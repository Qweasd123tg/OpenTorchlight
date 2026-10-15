#include "EditorScene.h"
#include "LogicGroup.h"
#include "LogicGroupDescriptor.h"

CEditorBaseObject* CLogicGroupDescriptor::CreateObject(CEditorScene* scene)
{
    return new CLogicGroup(scene->getResourceManager());
}

CLogicGroupDescriptor::~CLogicGroupDescriptor()
{
}

#include <map>
#include <string>
#include "ResourceManager.h"

void CLogicGroupDescriptor::levelActivated(CEditorScene* scene)
{
    if (!scene->getResourceManager()->getEditorIsRunning())
        for (unsigned int i = 0; i < m_Objects.size(); ++i)
            m_Objects[i]->BroadcastEvent(115);
}

void CLogicGroupDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* initiator)
{
    if (object)
    {
        CLogicGroup* target = dynamic_cast<CLogicGroup*>(object);
        if (target)
        {
            switch (event)
            {
            case 84: target->BroadcastEvent(118); break;
            case 85: target->BroadcastEvent(119); break;
            case 86: target->BroadcastEvent(120); break;
            case 87: target->BroadcastEvent(121); break;
            case 88: target->BroadcastEvent(122); break;
            case 89: target->BroadcastEvent(123); break;
            case 90: target->BroadcastEvent(124); break;
            case 91: target->BroadcastEvent(125); break;
            }
        }
    }
}

bool CLogicGroupDescriptor::loadAdditionalInfo(CEditorBaseObject* object, COgreReader* reader, CDataGroup* group, CDescriptorLoadConfiguration* configuration)
{
    if (object)
    {
        CLogicGroup* target = dynamic_cast<CLogicGroup*>(object);
        if (target)
        {
            target->loadLogicGroupToDataGroup(group, reader, configuration);
            return true;
        }
    }
    return false;
}

bool CLogicGroupDescriptor::saveAdditionalInfo(CEditorBaseObject* object, std::basic_ofstream<char, std::char_traits<char> >* stream, CDataGroup* group, CDescriptorSaveConfiguration* configuration)
{
    if (object)
    {
        CLogicGroup* target = dynamic_cast<CLogicGroup*>(object);
        if (target)
        {
            target->saveLogicGroupToDataGroup(group, stream, configuration);
            return true;
        }
    }
    return false;
}

CLogicGroupDescriptor::CLogicGroupDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CDescriptor(0)
{
    m_sName = std::wstring(name);
    m_sIcon = std::wstring(description);
    m_sDescription = std::wstring(group);
    m_iFlags &= ~DESCRIPTOR_FLAG_CLONABLE;
    AddInputLogic(INPUT_EVENT_STOP_4);
    AddInputLogic(INPUT_EVENT_START);
    AddInputLogic(INPUT_EVENT_PAUSE_3);
    AddInputLogic(INPUT_EVENT_INPUT1);
    AddInputLogic(INPUT_EVENT_INPUT2);
    AddInputLogic(INPUT_EVENT_INPUT3);
    AddInputLogic(INPUT_EVENT_INPUT4);
    AddInputLogic(INPUT_EVENT_INPUT5);
    AddOutputLogic(OUTPUT_EVENT_STOP);
    AddOutputLogic(OUTPUT_EVENT_START);
    AddOutputLogic(OUTPUT_EVENT_PAUSE);
    AddOutputLogic(OUTPUT_EVENT_OUTPUT_1);
    AddOutputLogic(OUTPUT_EVENT_OUTPUT_2);
    AddOutputLogic(OUTPUT_EVENT_OUTPUT_3);
    AddOutputLogic(OUTPUT_EVENT_OUTPUT_4);
    AddOutputLogic(OUTPUT_EVENT_OUTPUT_5);
    AddOutputLogic(OUTPUT_EVENT_LEVEL_ACTIVATED);
}
