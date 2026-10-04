#ifndef UNITTHEME_H
#define UNITTHEME_H
#include "RunicCore.h"
#include <string>
// Partial: the manager owns these 0x38-byte objects.
class CUnitTheme : public CRunicCore
{
public:
    virtual ~CUnitTheme();
    const std::wstring& getName() const { return m_sName; }
    long long getGuid() const { return m_iGuid; }
private:
    unsigned char m_ThemeData10[0x28-0x10];
    std::wstring m_sName;
    long long m_iGuid;
};
#endif
