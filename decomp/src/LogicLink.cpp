#include "UTFConversion.h"

#include "Descriptor.h"
#include "EditorScene.h"
#include "LogicLink.h"
#include "LogicObject.h"

CEditorBaseObject* CLogicLink::GetObjectLinkingTo()
{
    if (m_pEditorScene && m_pLinkingToLogicObject)
        return m_pLinkingToLogicObject->GetObject();
    return NULL;
}

CEditorBaseObject* CLogicLink::GetObjectInitiatingLink()
{
    if (m_pInitiatingLogicObject)
        return m_pInitiatingLogicObject->GetObject();
    return NULL;
}

long long CLogicLink::GetObjectIDInitiatingLink()
{
    if (m_pInitiatingLogicObject)
        return m_pInitiatingLogicObject->m_iObjectID;
    return 0;
}

unsigned int CLogicLink::GetEventIDForOutput()
{
    if (m_pOutputLogicWrapper)
        return m_pOutputLogicWrapper->m_iID;
    return static_cast<unsigned int>(-1);
}

unsigned int CLogicLink::GetInputFuncID()
{
    if (m_pLinkingToDescriptor && m_pInputLogicWrapper)
        return m_pLinkingToDescriptor->GetInputLogicFuncIndexByWrapper(m_pInputLogicWrapper);
    return static_cast<unsigned int>(-1);
}

unsigned int CLogicLink::GetOutputFuncID()
{
    if (m_pInitiatingLogicObject && m_pInitiatingLogicObject->m_pLinkedDescriptor && m_pOutputLogicWrapper)
        return m_pInitiatingLogicObject->m_pLinkedDescriptor->GetOutputLogicFuncIndexByWrapper(m_pOutputLogicWrapper);
    return static_cast<unsigned int>(-1);
}

CLogicLink::~CLogicLink()
{
    m_pOutputLogicWrapper = NULL;
    m_pInputLogicWrapper = NULL;
    m_pInitiatingLogicObject = NULL;
    m_pLinkingToDescriptor = NULL;
    m_pEditorScene = NULL;
}

CLogicLink::CLogicLink(CEditorScene* scene, CLogicObject* initiating, CLogicWrapper* output, CLogicObject* destination, CLogicWrapper* input)
    : CRunicCore(), m_pEditorScene(scene), m_pLinkingToDescriptor(NULL),
      m_pInitiatingLogicObject(initiating), m_pLinkingToLogicObject(destination),
      m_pInputLogicWrapper(input), m_pOutputLogicWrapper(output)
{
    if (!scene) return;
    if (!initiating) return;
    if (!input) return;
    if (!destination) return;
    if (!output) return;
    if (!destination->m_pLinkedDescriptor) return;
    m_pLinkingToDescriptor = destination->m_pLinkedDescriptor;
    initiating->GetObject();
}

void CLogicLink::saveLogicLinksToBinaryFile(std::ofstream* file)
{
    unsigned int id = m_pLinkingToLogicObject->m_iID;
    file->write(reinterpret_cast<const char*>(&id), 4);
    unsigned int length = m_pOutputLogicWrapper->m_sName.length();
    file->write(reinterpret_cast<const char*>(&length), 4);
    utf16string name = UTF32ToUTF16(m_pOutputLogicWrapper->m_sName);
    file->write(reinterpret_cast<const char*>(name.c_str()), length * 2);
    length = m_pInputLogicWrapper->m_sName.length();
    file->write(reinterpret_cast<const char*>(&length), 4);
    name = UTF32ToUTF16(m_pInputLogicWrapper->m_sName);
    file->write(reinterpret_cast<const char*>(name.c_str()), length * 2);
}

void CLogicLink::saveLogicLinksToDataGroup(CDataGroup* dataGroup)
{
    CDataGroup* group = dataGroup->AddDataGroup(L"LOGICLINK");
    group->AddDataValue(L"LINKINGTO", static_cast<int>(m_pLinkingToLogicObject->m_iID));
    group->AddDataValue(L"OUTPUTNAME", m_pOutputLogicWrapper->m_sName, false);
    group->AddDataValue(L"INPUTNAME", m_pInputLogicWrapper->m_sName, false);
}
