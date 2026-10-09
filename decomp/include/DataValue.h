#ifndef DATAVALUE_H
#define DATAVALUE_H
#include <string>
#include "RunicCore.h"
template <class T> class TRepository;
// Partial: allocation size 0x38; scalar union verified from original typed uses.
class CDataValue : public CRunicCore
{
public:
    enum EDATAVALUETYPES { DATAVALUE_STRING=5,DATAVALUE_TRANSLATE=8 };
    CDataValue(const wchar_t* name, TRepository<std::wstring>* repository);
    virtual ~CDataValue();
    void SetValueString(const wchar_t* value);
    void SetValueTranslate(const wchar_t* value);
    bool GetValueBool();
    void SetValueBool(bool value);
    long long GetValueInt64();
    void SetValueInt64(long long value);
    int GetValueInt32();
    void SetValueInt32(int value);
    unsigned int GetValueUInt32();
    void SetValueUInt32(unsigned int value);
    float GetValueFloat32();
    void SetValueFloat32(float value);
    double GetValueFloat64();
    void SetValueFloat64(double value);
    void SetValueIsTranslate();
    std::wstring GetValueTypeAsString();
    std::wstring GetValueAsString();
    const std::wstring& GetValueString(bool translate);
    EDATAVALUETYPES GetValueType() const { return m_eType; }
private:
    friend struct SmallmatchDataProbe; // compile-only layout/type assertions
    bool m_bStringValue;
    unsigned char m_Data11[7];
    // Six views confirmed by original typed formatting calls and setter parameters.
    union ScalarValue
    {
        bool boolean;
        long long signed64;
        int signed32;
        unsigned int unsigned32;
        float float32;
        double float64;
    } m_Value;
    unsigned int m_iNameID;
    TRepository<std::wstring>* m_pRepository;
    EDATAVALUETYPES m_eType;
};
#endif
