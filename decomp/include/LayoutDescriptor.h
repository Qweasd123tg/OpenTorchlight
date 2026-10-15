#ifndef LAYOUTDESCRIPTOR_H
#define LAYOUTDESCRIPTOR_H
#include "PositionableObjectDescriptor.h"
#include "GameEnums.h"
class CLayoutDescriptor : public CPositionableObjectDescriptor
{
public:
    CLayoutDescriptor(std::wstring name, ELAYOUT_TYPES type);
    virtual ~CLayoutDescriptor();
    virtual void update(float elapsed);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneLoaded(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene* scene);
    virtual void descriptorSceneDeactivated(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* sender);
private:
    ELAYOUT_TYPES m_LayoutType;
};
#endif
