
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
