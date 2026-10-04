#ifndef DATAVALUE_H
#define DATAVALUE_H
#include <string>
#include "RunicCore.h"
template <class T> class TRepository;
// Partial: complete allocation size 0x38, union value bytes remain opaque.
class CDataValue : public CRunicCore
{
public:
    enum EDATAVALUETYPES { DATAVALUE_STRING=5,DATAVALUE_TRANSLATE=8 };
    virtual ~CDataValue();
    std::wstring GetValueAsString();
    const std::wstring& GetValueString(bool translate);
    EDATAVALUETYPES GetValueType() const { return m_eType; }
private:
    bool m_bStringValue;
    unsigned char m_Data11[7];
    unsigned char m_ValueData18[8];
    unsigned int m_iNameID;
    TRepository<std::wstring>* m_pRepository;
    EDATAVALUETYPES m_eType;
};
#endif
