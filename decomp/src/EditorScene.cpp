#include "EditorScene.h"

void CEditorScene::fireEvent(EEDITOR_EVENTS event, long long guid)
{
}

#include <map>
#include <string>
#include "DescriptorManager.h"

void CEditorScene::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    if (m_pDescriptorManager)
    {
        if (enabled)
            BroadcastEvent(6);
        else
            BroadcastEvent(7);
    }
}

void CEditorScene::update(float elapsed)
{
    if (m_bVisible && getEnabled() && m_pDescriptorManager)
        m_pDescriptorManager->update(elapsed);
}

CEditorBaseObject* CEditorScene::GetObjectInScene(long long guid)
{
    if (guid == -1)
        return NULL;
    std::map<long long, CEditorBaseObject*>::iterator object = m_Objects.find(guid);
    if (object != m_Objects.end())
        return object->second;
    return NULL;
}
