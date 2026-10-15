#ifndef DESCRIPTORCONTROLLER_H
#define DESCRIPTORCONTROLLER_H

#include <string>
#include <map>
#include "TArrayList.h"

class CDescriptor;
class CDescriptorProp;
class CEditorBaseObject;

// DescriptorController.cpp: two property caches, each an original GCC map.
class CDescriptorController
{
public:
    CDescriptorController();
    static void addDescriptorFunction(const wchar_t* name, void* (*)());
    static CDescriptor* getNewDescriptorByName(const std::wstring& name);

    static unsigned int getDescriptionVersion();

    static CDescriptorProp* getDescriptorPropertyByName(CDescriptor* descriptor, const std::wstring& name,
                                                        bool defaults);
    static void addDescriptorProperty(CDescriptor* descriptor, CDescriptorProp* property, bool defaults);
private:
    std::map<std::wstring, TArrayList<CDescriptorProp*>*> m_Properties;
    std::map<std::wstring, TArrayList<CDescriptorProp*>*> m_DefaultProperties;
};

#endif
