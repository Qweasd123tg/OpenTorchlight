#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

#include "EditorBaseObject.h"
#include "EditorDefines.h"
#include "DescriptorProp.h"
#include "OutputEvents.h"
#include "InputEvents.h"

class CDataGroup;
class CDescriptorLoadConfiguration;
class CDescriptorSaveConfiguration;
class CEditorScene;
class CLogicObject;
class CLogicWrapper;
class COgreReader;

// Base of every editor object descriptor: the type's properties, its logic
// inputs and outputs, the objects created from it and their save/load.
class CDescriptor : public CEditorBaseObject
{
    friend class CEditorScene;
public:
    // m_iFlags bits; names are ours (the serialized ones from SerializeDescriptor).
    enum
    {
        DESCRIPTOR_FLAG_CLONABLE = 0x8,
        DESCRIPTOR_FLAG_CHILDREN = 0x20,
        DESCRIPTOR_FLAG_DRAGGABLE = 0x40,
        DESCRIPTOR_FLAG_NOT_SAVED = 0x80,
        DESCRIPTOR_FLAG_100 = 0x100,
        DESCRIPTOR_FLAG_POSITIONABLE = 0x400,
        DESCRIPTOR_FLAG_ROTATEABLE = 0x800,
        DESCRIPTOR_FLAG_4000 = 0x4000,
        DESCRIPTOR_FLAGS_DEFAULT =
            DESCRIPTOR_FLAG_CLONABLE | DESCRIPTOR_FLAG_DRAGGABLE | DESCRIPTOR_FLAG_100 | DESCRIPTOR_FLAG_4000
    };

    CDescriptor(int flags);
    virtual ~CDescriptor();

    virtual void update(float elapsed) {}
    virtual void deleteNotification() {}
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene) = 0;
    virtual void DescriptorObjectCreatedInEditor(CEditorBaseObject* object) {}
    virtual bool DescriptorObjectBeingDeleted(CEditorBaseObject* object) { return true; }
    virtual void DescriptorObjectHasBeenInited(CEditorBaseObject* object) {}
    virtual void descriptorSceneLoaded(CEditorScene* scene) {}
    virtual void descriptorSceneActivated(CEditorScene* scene) {}
    virtual void descriptorSceneDeactivated(CEditorScene* scene) {}
    virtual void saveObject(CEditorBaseObject* object, CDataGroup* group,
                            CDescriptorSaveConfiguration* configuration);
    virtual bool saveAdditionalInfo(CEditorBaseObject* object, std::ofstream* file, CDataGroup* group,
                                    CDescriptorSaveConfiguration* configuration)
    {
        return false;
    }
    virtual bool loadAdditionalInfo(CEditorBaseObject* object, COgreReader* reader, CDataGroup* group,
                                    CDescriptorLoadConfiguration* configuration)
    {
        return true;
    }
    virtual void InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* sender) {}

    unsigned int AddProperty(std::wstring category, std::wstring name, std::wstring description, void* setFunction,
                             void* getFunction, EVARIABLE_TYPES type, int flags);
    unsigned int AddPropertyWithInterpreterFunctions(std::wstring category, std::wstring name,
                                                     std::wstring description, void* setFunction,
                                                     void* getFunction,
                                                     PropertyStringToIndexFunction stringToIndex,
                                                     PropertyIndexToStringFunction indexToString, void* userData,
                                                     EVARIABLE_TYPES type, int flags);
    void LinkProperty(unsigned int property, unsigned int linkedProperty);
    CDescriptorProp* GetProperty(unsigned int index);
    CDescriptorProp* GetPropertyByIndex(unsigned int index);
    CDescriptorProp* GetPropertyByName(const std::wstring& name);
    unsigned int GetPropertyID(const std::wstring& name);
    bool HasProperty(const std::wstring& name);
    void SetProperty(CEditorBaseObject* object, unsigned int index, const void* data, unsigned int count);
    void* GetPropertyValue(CEditorBaseObject* object, unsigned int index, unsigned int& count);
    void GetPropertyListOfValues(CEditorBaseObject* object, unsigned int index, std::vector<std::wstring>& values);
    void calculateDefaultValues(CEditorBaseObject* object);
    long long getUniqueNumericValueRepresentation();

    unsigned int AddInputLogic(std::wstring name, unsigned int id);
    unsigned int AddInputLogic(EINPUT_EVENTS event);
    unsigned int AddOutputLogic(std::wstring name, unsigned int id);
    unsigned int AddOutputLogic(EOUTPUT_EVENTS event);
    CLogicWrapper* GetInputLogicWrapper(unsigned int index);
    CLogicWrapper* GetOutputLogicWrapper(unsigned int index);
    unsigned int GetInputLogicWrapperIndex(std::wstring name);
    unsigned int GetOutputLogicWrapperIndex(std::wstring name);
    unsigned int GetInputLogicFuncIndexByWrapper(CLogicWrapper* wrapper);
    unsigned int GetOutputLogicFuncIndexByWrapper(CLogicWrapper* wrapper);
    void OutputLogicObjectAdd(CEditorBaseObject* object, CLogicObject* logicObject);
    void OutputLogicObjectRemove(CEditorBaseObject* object, CLogicObject* logicObject);
    void BroadcastEventFromObject(CEditorBaseObject* object, unsigned int event);

    void EditorSceneCreatedObject(CEditorBaseObject* object);
    void EditorSceneRemovingObject(CEditorBaseObject* object);
    void deleteAllObjects();
    void cleanForQuickShutDown();
    bool Clone(CEditorBaseObject* object, CEditorBaseObject* source, CEditorBaseObject* parent);

    void SerializeDescriptor(CDataGroup* group, unsigned int id);
    unsigned int saveObjects(CDataGroup* group, CDescriptorSaveConfiguration* configuration);
    bool saveObjectInBinaryFile(std::ofstream& file, CEditorBaseObject* object,
                                CDescriptorSaveConfiguration* configuration);
    CEditorBaseObject* loadObject(CDataGroup* group, CDescriptorLoadConfiguration* configuration);
    int loadObjects(CDataGroup* group, CDescriptorLoadConfiguration* configuration);
    bool loadObjectFromBinaryFile(COgreReader& reader, CEditorBaseObject* object,
                                  CDescriptorLoadConfiguration& configuration);
    CEditorBaseObject* postProcessObject(CDataGroup* group, CDescriptorLoadConfiguration* configuration);
    void postProcessObjects(CDataGroup* group, CDescriptorLoadConfiguration* configuration);

    unsigned int getObjectCount() const { return m_Objects.size(); }
    CEditorBaseObject* getObject(unsigned int index) { return m_Objects[index]; }

protected:
    std::wstring m_sName;
    std::wstring m_sDescription;
    std::wstring m_sIcon;
    std::wstring m_sMenuCategory;
    unsigned int m_iFlags;
    unsigned int m_iID;
    std::map<std::wstring, unsigned int> m_PropertyIDs;
    TArrayList<CDescriptorProp*> m_Properties;
    TArrayList<CDescriptorProp*> m_DefaultProperties;
    TArrayList<CEditorBaseObject*> m_Objects;
    TArrayList<std::wstring> m_ParentFilters;
    TArrayList<CLogicWrapper*> m_InputLogicWrappers;
    TArrayList<CLogicWrapper*> m_OutputLogicWrappers;
    std::map<CEditorBaseObject*, TArrayList<CLogicObject*>*> m_OutputLogicObjects;
};

#endif
