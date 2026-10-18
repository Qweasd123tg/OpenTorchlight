#include "LayoutDescriptor.h"

CLayoutDescriptor::~CLayoutDescriptor()
{
}

#include "Layout.h"

void CLayoutDescriptor::update(float elapsed)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i)
        static_cast<CLayout*>(m_Objects[i])->update(elapsed);
}

void CLayoutDescriptor::descriptorSceneDeactivated(CEditorScene*)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CLayout* layout = dynamic_cast<CLayout*>(m_Objects[i]);
        if (layout)
            layout->setActivated(false);
    }
}

void CLayoutDescriptor::descriptorSceneActivated(CEditorScene*)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CLayout* layout = dynamic_cast<CLayout*>(m_Objects[i]);
        if (layout) {
            layout->setActivated(true);
            if (layout->m_bStartOnLoad)
                layout->start();
            else
                layout->stop(false);
            layout->deleteUnusedDescriptors();
        }
    }
}

CEditorBaseObject* CLayoutDescriptor::CreateObject(CEditorScene* scene)
{
    return new CLayout(scene->getResourceManager(), m_LayoutType);
}

#include "Level.h"

void CLayoutDescriptor::descriptorSceneLoaded(CEditorScene* scene)
{
    CLevel* level = scene->getResourceManager()->getLevel();
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CLayout* layout = dynamic_cast<CLayout*>(m_Objects[i]);
        if (layout) {
            layout->initOnLoad();
            if (level && layout->m_Unknown1B8 == static_cast<ELAYOUT_TYPES>(2) &&
                level->m_flag258 && layout->getNumberOfTimelinesThatDoLoop() == 0)
                continue;
            if (layout->m_bStartOnLoad)
                layout->start();
            else
                layout->stop(false);
        }
    }
}

void CLayoutDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* sender)
{
    CLayout* layout = object ? dynamic_cast<CLayout*>(object) : NULL;
    if (!layout) return;
    switch (event) {
    case 2: layout->setEnabled(true); return;
    case 3: layout->setEnabled(false); return;
    case 4: layout->setEnabled(true); layout->setVisible(true); return;
    case 5: layout->setEnabled(false); layout->setVisible(false); return;
    case 16:
        layout->getSceneNode()->_update(true, true);
        layout->start();
        object->BroadcastEvent(31);
        break;
    case 17: layout->stop(false); object->BroadcastEvent(32); break;
    case 18: layout->stop(true); object->BroadcastEvent(32); break;
    case 21: layout->getSceneNode()->_update(true, true); layout->start(); break;
    case 22: layout->startBackwards(); break;
    case 23:
    case 24: layout->stop(false); break;
    case 25: layout->pause(); break;
    case 27: break;
    default: if (layout->processInputs(event, sender)) return;
    }
    CPositionableObjectDescriptor::InputLogicEvent(object, event, sender);
}
