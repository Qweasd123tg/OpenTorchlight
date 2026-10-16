#ifndef DATAGROUPREPOSITORY_H
#define DATAGROUPREPOSITORY_H

#include "TRepository.h"
#include "EmptyStrings.h"

// Original TU-local interned string repository in DataGroup.cpp.
static TRepository<std::wstring> g_GlobalRepository(EMPTY_WSTRING);

#endif
