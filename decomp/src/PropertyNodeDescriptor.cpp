#include "EmptyStrings.h"
#include "PropertyNodeDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "PropertyNode.h"

CPropertyNodeDescriptor::CPropertyNodeDescriptor()
    : CPositionableObjectDescriptor(L"Property Node", L"Property node for spawns and logic", L"gear", true, true, true, true, true)
{
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddPropertyWithInterpreterFunctions(L"PROPERTY", L"TYPE", L"Property Type", (void*)Set_setPropertyNodeType, (void*)Get_getPropertyNodeType, getPropertyNodeTypeByString, getPropertyNodeTypeString, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 68);
    AddProperty(L"PROPERTY", L"RADIUS", L"The radius of the shape", (void*)Set_setRadius, (void*)Get_getRadius, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTY", L"BOX WIDTH", L"The box width", (void*)Set_setScaleX, (void*)Get_getScaleX, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTY", L"BOX LENGTH", L"The box length", (void*)Set_setScaleZ, (void*)Get_getScaleZ, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTY", L"ENABLED", L"Property node enabled", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
}

CPropertyNodeDescriptor::~CPropertyNodeDescriptor()
{
}

unsigned int CPropertyNodeDescriptor::getPropertyNodeTypeByString(
    CEditorScene* scene,
    CEditorBaseObject* object,
    const std::wstring& value,
    void* userData)
{
    const std::wstring* names =
        reinterpret_cast<const std::wstring*>(&gPROPERTY_NODE_TYPE_NAMES);

    for (unsigned int i = 0; i < 16; ++i)
    {
        if (value == names[i])
            return i;
    }

    return 0;
}

CEditorBaseObject* CPropertyNodeDescriptor::CreateObject(CEditorScene* scene)
{
    return new CPropertyNode(scene->getResourceManager());
}

void CPropertyNodeDescriptor::descriptorSceneActivated(CEditorScene*)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i)
    {
        if (m_Objects[i] != NULL)
        {
            CPropertyNode *propertyNode =
                dynamic_cast<CPropertyNode *>(m_Objects[i]);

            if (propertyNode != NULL)
                propertyNode->activate();
        }
    }
}
