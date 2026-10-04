#ifndef BATCHMODELREF_H
#define BATCHMODELREF_H

#include <string>
#include "RunicCore.h"

class BatchModel;

class BatchModelRef : public CRunicCore
{
public:
    virtual ~BatchModelRef();
    BatchModelRef();

    BatchModel* m_pBatchModel;
    unsigned char m_gap18[0x8] __attribute__((aligned(8)));
    std::wstring m_sBatchModelName;
};

#endif
