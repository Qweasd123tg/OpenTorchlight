#include "EmptyStrings.h"
#include "EditorButtonDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorButton.h"
#include "EditorImage.h"
#include "EditorScene.h"

CEditorButtonDescriptor::CEditorButtonDescriptor()
    : CBaseObjectDescriptor(L"Button", L"An bitmap", L"button")
{
    m_iFlags |= DESCRIPTOR_FLAG_CHILDREN;
    AddProperty(L"PROPERTIES", L"VISIBLE", L"If the image is visible or not", (void*)Set_setVisible, (void*)Get_getVisible, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"ENABLED", L"If disabled you won't get any mouse overs or clicks", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"SIZE AND SHAPE", L"PCT X", L"Number between 0-1 that represents the screen pos", (void*)Set_setPosXPCT, (void*)Get_getPosXPCT, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SIZE AND SHAPE", L"PCT Y", L"Number between 0-1 that represents the screen pos", (void*)Set_setPosYPCT, (void*)Get_getPosYPCT, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SIZE AND SHAPE", L"PCT WIDTH", L"Number between 0-1 that represents the screen width", (void*)Set_setWidthPCT, (void*)Get_getWidthPCT, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SIZE AND SHAPE", L"PCT HEIGHT", L"Number between 0-1 that represents the screen height", (void*)Set_setHeightPCT, (void*)Get_getHeightPCT, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SIZE AND SHAPE", L"X", L"Position of the image X", (void*)Set_setPosX, (void*)Get_getPosX, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SIZE AND SHAPE", L"Y", L"Position of the image Y", (void*)Set_setPosY, (void*)Get_getPosY, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SIZE AND SHAPE", L"WIDTH", L"The width of the image", (void*)Set_setWidth, (void*)Get_getWidth, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SIZE AND SHAPE", L"HEIGHT", L"The height of the image", (void*)Set_setHeight, (void*)Get_getHeight, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"OFFSETS", L"X OFFSET", L"Offset of the image X", (void*)Set_setOffsetX, (void*)Get_getOffsetX, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"OFFSETS", L"Y OFFSET", L"Offset of the image Y", (void*)Set_setOffsetY, (void*)Get_getOffsetY, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"OFFSETS", L"PCT X OFFSET", L"Offset of the image by pct", (void*)Set_setOffsetXPct, (void*)Get_getOffsetXPct, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"OFFSETS", L"PCT Y OFFSET", L"Offset of the image by pct", (void*)Set_setOffsetYPct, (void*)Get_getOffsetYPct, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"IMAGE FILES", L"NORMAL", L"The relative path to an image to show. NOTE - you can also just type in the name of the image if it was loaded via an imageset", (void*)Set_setNormalImage, (void*)Get_getNormalImage, VARIABLE_TYPE_STRING, 0);
    AddProperty(L"IMAGE FILES", L"ROLLOVER", L"The relative path to an image to show. NOTE - you can also just type in the name of the image if it was loaded via an imageset", (void*)Set_setRolloverImage, (void*)Get_getRolloverImage, VARIABLE_TYPE_STRING, 0);
    AddProperty(L"IMAGE FILES", L"CLICKED", L"The relative path to an image to show. NOTE - you can also just type in the name of the image if it was loaded via an imageset", (void*)Set_setClickedImage, (void*)Get_getClickedImage, VARIABLE_TYPE_STRING, 0);
    AddProperty(L"IMAGE FILES", L"DISABLED", L"The relative path to an image to show. NOTE - you can also just type in the name of the image if it was loaded via an imageset", (void*)Set_setDisabledImage, (void*)Get_getDisabledImage, VARIABLE_TYPE_STRING, 0);
    AddInputLogic(INPUT_EVENT_SHOW);
    AddInputLogic(INPUT_EVENT_HIDE);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddOutputLogic(OUTPUT_EVENT_ON_VISIBLE);
    AddOutputLogic(OUTPUT_EVENT_ON_INVISIBLE);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddOutputLogic(OUTPUT_EVENT_CLICKED);
}

CEditorButtonDescriptor::~CEditorButtonDescriptor()
{
}

void CEditorButtonDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* param)
{
    CEditorImage* image = dynamic_cast<CEditorImage*>(object);

    if (image != NULL) {
        switch (event) {
        case 1:
            image->setVisible(false);
            break;
        case 0:
            image->setVisible(true);
            break;
        case 2:
            image->setEnabled(true);
            break;
        case 3:
            image->setEnabled(false);
            break;
        }
    }
}

CEditorBaseObject* CEditorButtonDescriptor::CreateObject(CEditorScene* scene)
{
    return new CEditorButton(scene->getResourceManager());
}
