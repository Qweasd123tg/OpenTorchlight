#ifndef BATCHMODELREF_H
#define BATCHMODELREF_H

#include <string>
#include "RunicCore.h"

class CGenericModel;

class BatchModelRef : public CRunicCore
{
public:
    virtual ~BatchModelRef();
    BatchModelRef();

    CGenericModel* m_pBatchModel;
    int m_referenceCount;
    unsigned char m_gap1c[4];
    std::wstring m_sBatchModelName;
};

#endif
