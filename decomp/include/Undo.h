#ifndef UNDO_H
#define UNDO_H

#include "RunicCore.h"
#include "TArrayList.h"

class CEditorBaseObject;
union UNIONDATA32BIT;

class CUndo : public CRunicCore
{
public:
    class CUndoData : public CRunicCore
    {
    public:
        virtual ~CUndoData();
        CEditorBaseObject* m_object;              // 0x10
        int m_action;                            // 0x18
        unsigned int m_property;                 // 0x1c
        unsigned int m_sceneID;                  // 0x20
        unsigned char m_padding24[4];
        long long m_parentGuid;                  // 0x28
        long long m_objectGuid;                  // 0x30
        UNIONDATA32BIT* m_data;                  // 0x38
        unsigned int m_count;                    // 0x40
        unsigned char m_padding44[4];
    };

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
