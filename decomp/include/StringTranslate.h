#ifndef STRINGTRANSLATE_H
#define STRINGTRANSLATE_H

#include <map>
#include <string>

#include "RunicCore.h"

// Translation table loaded from a .dat file: every child group maps its
// ORIGINAL text to its TRANSLATION.
class CStringTranslate : public CRunicCore
{
public:
    CStringTranslate(const std::wstring& fileName);
    virtual ~CStringTranslate();

    static CStringTranslate* getSinglton();

    const std::wstring& getTranslateString(const std::wstring& text);
    std::wstring getTranslateString(const wchar_t* text);
    void reload();

private:
    std::map<std::wstring, std::wstring> m_Translations;
    std::wstring m_sFileName;
    bool m_bLoaded;
};

extern CStringTranslate* m_gStringTranslate;

#endif
