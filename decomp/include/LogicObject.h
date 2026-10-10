#ifndef LOGICOBJECT_H
#define LOGICOBJECT_H

#include "EditorBaseObject.h"
#include "TArrayList.h"

class CLogicLink;

// Partial: LogicObject.cpp. Node of a logic graph that wraps an editor object
// and forwards its output events along the logic links. Layout from the
// constructor; field names are provisional.
class CLogicObject : public CEditorBaseObject
{
public:
    unsigned int AddLogicLink(unsigned int output, CLogicObject* input, unsigned int function);

    void SetXPosition(int position);
    void SetYPosition(int position);

    CLogicObject(CEditorScene* scene, long long objectID, unsigned int id);
    virtual ~CLogicObject();

    CEditorBaseObject* GetObject();
    CLogicLink* GetLogicLinkByIndex(unsigned int index);
    void setObjectID(long long objectID);
    bool RemoveLinksToLogicObject(CLogicObject* object);
    bool RemoveLogicLinksRefingObjectID(long long objectID);
    void Invoke(unsigned int event);
    bool RemoveLinkByIndex(unsigned int linkIndex);

private:
    friend int EditorGetCountOfLogicLinksInLogicObject(long long, unsigned int);
    friend long long EditorGetObjectIDRefedInLogicObject(long long, unsigned int);
    friend void EditorGetLogicObjectPosition(long long, unsigned int, int&, int&);
    friend class CLogicLink;
    friend struct SmallmatchPass7Probe;
    unsigned int m_iID;
    long long m_iObjectID;
    CDescriptor* m_pLinkedDescriptor;
    float m_fLeft;
    float m_fTop;
    float m_fRight;
    float m_fBottom;
    TArrayList<CLogicLink*> m_Links;
};

#endif
