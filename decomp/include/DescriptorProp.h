#ifndef DESCRIPTORPROP_H
#define DESCRIPTORPROP_H

#include <cstring>
#include <string>

#include "RunicCore.h"
#include "TArrayList.h"

class CDataGroup;
class CDescriptorPropertyInterpreter;
class CEditorBaseObject;
class CEditorScene;

// Types of the values a descriptor property exposes; the names are
// KEditorObjectPropertyTypeNames. Enumerator names are ours.
enum EVARIABLE_TYPES
{
    VARIABLE_TYPE_NOT_VALID,
    VARIABLE_TYPE_NOT_SET,
    VARIABLE_TYPE_INTEGER,
    VARIABLE_TYPE_FLOAT,
    VARIABLE_TYPE_UNSIGNED_INTEGER,
    VARIABLE_TYPE_STRING,
    VARIABLE_TYPE_BOOL,
    VARIABLE_TYPE_VECTOR2,
    VARIABLE_TYPE_VECTOR3,
    VARIABLE_TYPE_VECTOR4,
    VARIABLE_TYPE_COUNT
};

union UNIONDATA8BIT
{
    bool m_bValue;
    char m_cValue;
    unsigned char m_ucValue;
};

// String property values travel as 16-bit units.
union UNIONDATA16BIT
{
    short m_sValue;
    unsigned short m_usValue;
};

// One element of a property value; new[] zero-fills every element.
union UNIONDATA32BIT
{
    UNIONDATA32BIT() : m_iValue(0) {}

    int m_iValue;
    unsigned int m_uValue;
    float m_fValue;
    bool m_bValue;
};

// Scratch buffer the generated property getters return.
static UNIONDATA32BIT gUnionOf32BitData[3];

// String property values travel through this buffer (EditorDLL.cpp).
extern char sEditorTmpMemory[4000];

static const std::wstring KEditorObjectPropertyTypeNames[] =
{
    L"NOT VALID",
    L"NOT SET",
    L"INTEGER",
    L"FLOAT",
    L"UNSIGNED INTEGER",
    L"STRING",
    L"BOOL",
    L"VECTOR2",
    L"VECTOR3",
    L"VECTOR4",
};

typedef unsigned int (*PropertyStringToIndexFunction)(CEditorScene*, CEditorBaseObject*, const std::wstring&, void*);
typedef std::wstring (*PropertyIndexToStringFunction)(CEditorScene*, CEditorBaseObject*, unsigned int, void*);

// Partial: DescriptorProp.cpp. A property of a CDescriptor: name, value type and
// the generated accessors that read and write it on an editor object.
class CDescriptorProp : public CRunicCore
{
public:
    // m_iFlags bits read by CDescriptor; names are ours.
    enum
    {
        FLAG_HAS_LIST_OF_VALUES = 0x4,
        FLAG_NOT_SAVED_IN_BINARY = 0x100
    };

    CDescriptorProp(std::wstring category, std::wstring name, std::wstring description, void* setFunction,
                    void* getFunction, EVARIABLE_TYPES type, int flags);
    CDescriptorProp(CDescriptorProp* source, CEditorBaseObject* object);
    virtual ~CDescriptorProp();
    virtual void saveProperty(CEditorBaseObject* object, CDataGroup* group);
    virtual void loadProperty(CEditorBaseObject* object, CDataGroup* group, unsigned int version);

    EVARIABLE_TYPES getVariableType();
    UNIONDATA32BIT* getData(unsigned int& count, CEditorBaseObject* object);
    void setData(const UNIONDATA32BIT* data, unsigned int count, CEditorBaseObject* object);
    std::wstring getListValueByIndex(CEditorScene* scene, CEditorBaseObject* object, unsigned int index);
    void setPropertyInterpreterFunctions(PropertyStringToIndexFunction stringToIndex,
                                         PropertyIndexToStringFunction indexToString, void* userData);
    void cloneValue(CEditorBaseObject* object, CEditorBaseObject* source);
    void serializeProperty(CDataGroup* group, unsigned int index);

    std::wstring m_sName;
    std::wstring m_sDescription;
    CDescriptorPropertyInterpreter* m_pInterpreter;
    void* m_pSetFunction;
    void* m_pGetFunction;
    EVARIABLE_TYPES m_eType;
    int m_iFlags;
    std::wstring m_sCategory;
    TArrayList<UNIONDATA32BIT> m_DefaultValue;
    TArrayList<CDescriptorProp*> m_LinkedProperties;
    void* m_pValueBuffer;
};

#endif
