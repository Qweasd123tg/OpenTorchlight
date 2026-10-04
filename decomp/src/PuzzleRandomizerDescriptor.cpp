#include "EmptyStrings.h"
#include "PuzzleRandomizerDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "PuzzleRandomizer.h"

CPuzzleRandomizerDescriptor::CPuzzleRandomizerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the puzzle input enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"NUMBER OF INPUTS", L"This is how many active inputs you want to use.", (void*)Set_setActiveInputs, (void*)Get_getActiveInputs, VARIABLE_TYPE_INTEGER, 0);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddInputLogic(INPUT_EVENT_RESET);
    AddInputLogic(INPUT_EVENT_INPUT_1);
    AddInputLogic(INPUT_EVENT_INPUT_2);
    AddInputLogic(INPUT_EVENT_INPUT_3);
    AddInputLogic(INPUT_EVENT_INPUT_4);
    AddInputLogic(INPUT_EVENT_INPUT_5);
    AddInputLogic(INPUT_EVENT_INPUT_6);
    AddOutputLogic(OUTPUT_EVENT_RESET);
    AddOutputLogic(OUTPUT_EVENT_SUCCESS);
    AddOutputLogic(OUTPUT_EVENT_FAILED);
}

CPuzzleRandomizerDescriptor::~CPuzzleRandomizerDescriptor()
{
}

void CPuzzleRandomizerDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* sender)
{
    if (object != NULL) {
        CPuzzleRandomizer* puzzleRandomizer = dynamic_cast<CPuzzleRandomizer*>(object);
        if (puzzleRandomizer != NULL) {
            switch (event) {
                case 2:
                    puzzleRandomizer->m_bEnabled = true;
                    break;
                case 3:
                    puzzleRandomizer->m_bEnabled = false;
                    break;
                case 6:
                    puzzleRandomizer->reset();
                    puzzleRandomizer->setActiveInputs(puzzleRandomizer->m_iActiveInputs);
                    return;
                case 0x28:
                    puzzleRandomizer->trigger(static_cast<EPUZZLE_INPUTS>(0));
                    return;
                case 0x29:
                    puzzleRandomizer->trigger(static_cast<EPUZZLE_INPUTS>(1));
                    return;
                case 0x2a:
                    puzzleRandomizer->trigger(static_cast<EPUZZLE_INPUTS>(2));
                    return;
                case 0x2b:
                    puzzleRandomizer->trigger(static_cast<EPUZZLE_INPUTS>(3));
                    return;
                case 0x2c:
                    puzzleRandomizer->trigger(static_cast<EPUZZLE_INPUTS>(4));
                    return;
                case 0x2d:
                    puzzleRandomizer->trigger(static_cast<EPUZZLE_INPUTS>(5));
                    return;
            }
        }
    }
}

CEditorBaseObject* CPuzzleRandomizerDescriptor::CreateObject(CEditorScene* scene)
{
    return new CPuzzleRandomizer(scene->getResourceManager());
}
