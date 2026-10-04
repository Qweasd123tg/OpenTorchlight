#ifndef UNDO_H
#define UNDO_H

#include "RunicCore.h"
#include "TArrayList.h"

class CEditorBaseObject;

class CUndo : public CRunicCore
{
public:
	class CUndoData;

	CUndo();
	CUndo(CEditorBaseObject* pObject, unsigned int uiProperty);
	virtual ~CUndo();

	void AddUndoProperty(CEditorBaseObject* pObject, unsigned int uiProperty);
	void AddUndoProperty(CEditorBaseObject* pObject, const wchar_t* pPropertyName);

	void AddNewObject(CEditorBaseObject* pObject);
	void AddObjectDeleted(CEditorBaseObject* pObject);

	void DoAsUndo();
	void DoAsRedo();

	void DoUndoOnProperty(CUndoData* pUndoData, CUndo* pUndo);
	void DoUndoUndelete(CUndoData* pUndoData, CUndo* pUndo);
	void DoUndoCreate(CUndoData* pUndoData, CUndo* pUndo);
	void resetPropertiesOnObject(CUndo* pUndo);

	TArrayList<CUndoData*> m_undoData;
};

#endif
