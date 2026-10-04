#include "EmptyStrings.h"
#include "CollisionShapeDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "CollisionShape.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"

CCollisionShapeDescriptor::CCollisionShapeDescriptor()
    : CShapeDescriptor(L"Collision Shape", L"Occupies collision path nodes", L"spawn", false, false, false)
{
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddProperty(L"PROPERTIES", L"ENABLED", L"If true the collision shape will occupy path nodes", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
}

CCollisionShapeDescriptor::~CCollisionShapeDescriptor()
{
}

void CCollisionShapeDescriptor::InputLogicEvent(CEditorBaseObject* object,
                                                  unsigned int event,
                                                  CEditorBaseObject* data)
{
    CCollisionShape* shape = dynamic_cast<CCollisionShape*>(object);
    if (shape != NULL) {
        if (event == 2 || event == 3)
            shape->setEnabled(event == 2);
    }
}

void CCollisionShapeDescriptor::update(float delta)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CCollisionShape *shape =
            dynamic_cast<CCollisionShape *>(m_Objects[i]);
        if (shape != NULL) {
            shape->update(delta);
        }
    }
}

CEditorBaseObject* CCollisionShapeDescriptor::CreateObject(CEditorScene* scene)
{
    return new CCollisionShape(scene->getResourceManager());
}
