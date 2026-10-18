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
