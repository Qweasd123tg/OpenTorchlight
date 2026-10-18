#ifndef LOGICOBJECT_H
#define LOGICOBJECT_H

#include <fstream>
#include <map>

#include "EditorBaseObject.h"
#include "TArrayList.h"

class CDataGroup;
class CLogicLink;
class CLogicWrapper;
class CLogicGroup;
class COgreReader;
class CDescriptorLoadConfiguration;

// Partial: LogicObject.cpp. Node of a logic graph that wraps an editor object
// and forwards its output events along the logic links. Layout from the
// constructor; field names are provisional.
class CLogicObject : public CEditorBaseObject
{
public:
    void SetPosition(int x, int y);
    void SetSize(int width, int height);
    void saveLogicObjectLinksToBinaryFile(std::basic_ofstream<char, std::char_traits<char> >* stream);
    unsigned int AddLogicLink(CLogicWrapper* output, CLogicObject* input, CLogicWrapper* function);
    void saveLogicObjectToBinaryFile(std::basic_ofstream<char, std::char_traits<char> >* stream);
    void saveLogicObjectToDataGroup(CDataGroup* group);
    void loadLogicObjectByBinaryFile(CLogicGroup* group, COgreReader* reader,
                                    CDescriptorLoadConfiguration* configuration,
                                    std::map<int, int>& remappedIDs);
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
    friend class CLogicGroup;
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
