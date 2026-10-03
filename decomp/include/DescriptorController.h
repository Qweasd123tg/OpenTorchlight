#ifndef DESCRIPTORCONTROLLER_H
#define DESCRIPTORCONTROLLER_H

#include <string>

class CDescriptor;
class CDescriptorProp;

// Partial: DescriptorController.cpp. Only the static members used by recovered
// TUs are declared; the instance layout is not recovered yet.
class CDescriptorController
{
public:
    static CDescriptorProp* getDescriptorPropertyByName(CDescriptor* descriptor, const std::wstring& name,
                                                        bool defaults);
    static void addDescriptorProperty(CDescriptor* descriptor, CDescriptorProp* property, bool defaults);
};

#endif
