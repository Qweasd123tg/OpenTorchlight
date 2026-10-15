
#include "Descriptor.h"
#include "EditorScene.h"
#include "LogicLink.h"
#include "LogicObject.h"

CEditorBaseObject* CLogicObject::GetObject()
{
    if (getSceneOwner())
        return getSceneOwner()->GetObjectInScene(m_iObjectID);
    return NULL;
}

CLogicLink* CLogicObject::GetLogicLinkByIndex(unsigned int index)
{
    if (index < m_Links.size())
        return m_Links[index];
    return NULL;
}

void CLogicObject::setObjectID(long long objectID)
{
    m_iObjectID = objectID;
    CEditorBaseObject* object = GetObject();
    if (object)
    {
        m_pLinkedDescriptor = object->getDescriptor();
        if (m_pLinkedDescriptor)
            m_pLinkedDescriptor->OutputLogicObjectAdd(object, this);
    }
}

bool CLogicObject::RemoveLinkByIndex(unsigned int index)
{
    if (index >= m_Links.size())
        return false;
    if (m_Links[index])
    {
        if (m_Links[index])
        {
            delete m_Links[index];
            m_Links[index] = NULL;
        }
        m_Links[index] = NULL;
    }
    return true;
}

CLogicObject::CLogicObject(CEditorScene* scene, long long objectID, unsigned int id)
    : CEditorBaseObject(), m_iID(id), m_iObjectID(objectID), m_pLinkedDescriptor(NULL),
      m_fLeft(0.0f), m_fTop(0.0f), m_fRight(0.0f), m_fBottom(0.0f), m_Links(10)
{
    CEditorBaseObject::SetSceneOwner(scene);
    if (objectID != -1)
        setObjectID(objectID);
}

bool CLogicObject::RemoveLinksToLogicObject(CLogicObject* object)
{
    if (!object)
        return false;
    for (unsigned int i = 0; i < m_Links.size(); ++i)
        if (m_Links[i] && object == m_Links[i]->m_pLinkingToLogicObject)
            RemoveLinkByIndex(i);
    return true;
}
bool CLogicObject::RemoveLogicLinksRefingObjectID(long long objectID)
{
    if (objectID == -1)
        return false;
    for (unsigned int i = 0; i < m_Links.size(); ++i)
        if (m_Links[i])
        {
            CLogicObject* object = m_Links[i]->m_pLinkingToLogicObject;
            if (object && objectID == object->m_iObjectID)
                RemoveLinkByIndex(i);
        }
    return true;
}
void CLogicObject::SetXPosition(int position)
{
    m_fRight = m_fRight - m_fLeft + position;
    m_fLeft = position;
}
void CLogicObject::SetYPosition(int position)
{
    m_fBottom = m_fBottom - m_fTop + position;
    m_fTop = position;
}
