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
    CLogicObject(CEditorScene* scene, long long objectID, unsigned int id);
    virtual ~CLogicObject();

    void Invoke(unsigned int event);

private:
    unsigned int m_iID;
    long long m_iObjectID;
    CEditorBaseObject* m_pObject;
    int m_iX;
    int m_iY;
    int m_iWidth;
    int m_iHeight;
    TArrayList<CLogicLink*> m_Links;
};

#endif
