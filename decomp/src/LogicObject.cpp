#include "DescriptorLoadConfiguration.h"
#include "OgreReader.h"

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

void CLogicObject::SetPosition(int x, int y)
{
    float width = m_fRight - m_fLeft;
    float height = m_fBottom - m_fTop;
    width = 25.0f < width ? width : 25.0f;
    height = 25.0f < height ? height : 25.0f;
    m_fRight = width + x;
    m_fLeft = x;
    m_fBottom = height + y;
    m_fTop = y;
}
void CLogicObject::SetSize(int width, int height)
{
    if (width < 25) width = 25;
    if (height < 25) height = 25;
    m_fRight = width + m_fLeft;
    m_fBottom = height + m_fTop;
}
void CLogicObject::saveLogicObjectLinksToBinaryFile(std::ofstream* stream)
{
    unsigned int count = 0;
    for (unsigned int i = 0; i < m_Links.size(); ++i)
        if (m_Links[i]) ++count;
    stream->write(reinterpret_cast<const char*>(&count), 4);
    for (unsigned int i = 0; i < m_Links.size(); ++i)
        if (m_Links[i]) m_Links[i]->saveLogicLinksToBinaryFile(stream);
}
unsigned int CLogicObject::AddLogicLink(CLogicWrapper* output, CLogicObject* input, CLogicWrapper* function)
{
    if (!input || !output || !function) return ~0u;
    CLogicLink* link = new CLogicLink(getSceneOwner(), this, output, input, function);
    unsigned int index = m_Links.size();
    m_Links.add(link);
    return index;
}
unsigned int CLogicObject::AddLogicLink(unsigned int output, CLogicObject* input, unsigned int function)
{
    if (!input) return ~0u;
    CDescriptor* inputDescriptor = input->m_pLinkedDescriptor;
    CDescriptor* descriptor = m_pLinkedDescriptor;
    if (!inputDescriptor || !descriptor) return ~0u;
    CLogicWrapper* outputWrapper = descriptor->GetOutputLogicWrapper(output);
    CLogicWrapper* inputWrapper = inputDescriptor->GetInputLogicWrapper(function);
    if (!inputWrapper || !outputWrapper) return ~0u;
    return AddLogicLink(outputWrapper, input, inputWrapper);
}
void CLogicObject::saveLogicObjectToBinaryFile(std::ofstream* stream)
{
    stream->write(reinterpret_cast<const char*>(&m_iID), 4);
    long long guid = -1;
    if (GetObject()) guid = GetObject()->getOriginalGuid();
    stream->write(reinterpret_cast<const char*>(&guid), 8);
    stream->write(reinterpret_cast<const char*>(&m_fLeft), 4);
    stream->write(reinterpret_cast<const char*>(&m_fTop), 4);
}
void CLogicObject::loadLogicObjectByBinaryFile(CLogicGroup* group, COgreReader* reader,
 CDescriptorLoadConfiguration* configuration, std::map<int,int>& remappedIDs)
{
    if (!reader || !group) return;
    int oldID = 0;
    reader->read(&oldID, 4);
    long long objectID = -1;
    reader->read(&objectID, 8);
    reader->read(&m_fLeft, 4);
    reader->read(&m_fTop, 4);
    objectID = configuration->getRemappedID(objectID);
    if (objectID == -1) return;
    setObjectID(objectID);
    remappedIDs[oldID] = m_iID;
}
CLogicObject::~CLogicObject()
{
    CEditorBaseObject* object = GetObject();
    if (object) m_pLinkedDescriptor->OutputLogicObjectRemove(object, this);
    m_Links.deleteAll();
    m_pLinkedDescriptor = NULL;
    m_iObjectID = -1;
    m_iID = ~0u;
}
