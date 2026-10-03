#ifndef DESCRIPTORSAVECONFIGURATION_H
#define DESCRIPTORSAVECONFIGURATION_H

#include <string>

#include "RunicCore.h"

// Options passed through the descriptor save routines. CEditorScene fills the
// paths directly (saveCompressedLayout), so the members are public.
class CDescriptorSaveConfiguration : public CRunicCore
{
public:
    CDescriptorSaveConfiguration();
    virtual ~CDescriptorSaveConfiguration();

    int m_iSaveID;
    int m_iSaveFlags;
    std::wstring m_sFilePath;
    std::wstring m_sFileName;
};

#endif
