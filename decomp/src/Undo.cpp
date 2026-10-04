#include "EmptyStrings.h"
#include "Undo.h"
#include "EditorBaseObject.h"
#include "RunicCore.h"
#include "GameVariables.h"

CUndo::CUndo()
    : CRunicCore(), m_undoData(10)
{
}

CUndo::CUndo(CEditorBaseObject* pObject, unsigned int uiProperty)
    : CRunicCore(), m_undoData(10)
{
    AddUndoProperty(pObject, uiProperty);
}

CUndo::~CUndo()
{
    m_undoData.deleteAll();
}

void CUndo::resetPropertiesOnObject(CUndo* pUndo)
{
    for (unsigned int i = 0; i < m_undoData.size(); ++i) {
        switch (*reinterpret_cast<int*>(
                    reinterpret_cast<char*>(m_undoData[i]) + 0x18)) {
        case 0:
            DoUndoOnProperty(m_undoData[i], pUndo);
            break;
        case 1:
            DoUndoUndelete(m_undoData[i], pUndo);
            break;
        case 2:
            DoUndoCreate(m_undoData[i], pUndo);
            break;
        }
    }
}
