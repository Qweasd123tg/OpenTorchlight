#ifndef DESCRIPTORREGISTRY_H
#define DESCRIPTORREGISTRY_H
#include <map>
#include <string>
#include <vector>
#include "TArrayList.h"
class CEditorBaseObject;
// Original DescriptorController.cpp globals: factory map and ordered type names.
typedef void* (*DescriptorFactoryFunction)();
typedef std::map<std::wstring, DescriptorFactoryFunction> DescriptorFactoryMap;
extern DescriptorFactoryMap g_Descriptors;
extern std::vector<std::wstring> g_DescriptorNameOrder;
extern std::map<std::wstring, TArrayList<CEditorBaseObject*>*> g_CachedObjects;
#endif
