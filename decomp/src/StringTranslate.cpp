#include "EmptyStrings.h"
#include "StringTranslate.h"
#include "DataGroup.h"

CStringTranslate* m_gStringTranslate = NULL;

CStringTranslate* CStringTranslate::getSinglton()
{
    if (m_gStringTranslate && !m_gStringTranslate->m_bLoaded)
        return NULL;
    return m_gStringTranslate;
}

const std::wstring& CStringTranslate::getTranslateString(const std::wstring& text)
{
    std::map<std::wstring, std::wstring>::iterator it = m_Translations.find(text);
    if (it != m_Translations.end() && !it->second.empty())
        return it->second;
    return text;
}

std::wstring CStringTranslate::getTranslateString(const wchar_t* text)
{
    std::wstring key(text);
    return getTranslateString(key);
}

CStringTranslate::~CStringTranslate()
{
    m_Translations.clear();
    m_gStringTranslate = NULL;
}

void CStringTranslate::reload()
{
    m_bLoaded = false;
    m_Translations.clear();
    if (m_sFileName.find(L".") == std::wstring::npos)
    {
        m_bLoaded = true;
        return;
    }

    TRepository<std::wstring>* repository = new TRepository<std::wstring>(EMPTY_WSTRING);
    CDataGroup dataGroup(EMPTY_WSTRING, NULL, 20, 10, repository);
    dataGroup.LoadFile(m_sFileName, NULL);
    if (dataGroup.GetNumberOfDataGroups() == 0)
    {
        m_bLoaded = true;
        return;
    }

    for (unsigned int i = 0; i < dataGroup.GetNumberOfDataGroups(); i++)
    {
        m_Translations[dataGroup.GetDataGroup(i)->GetDataValue(L"ORIGINAL", EMPTY_WSTRING)] =
            dataGroup.GetDataGroup(i)->GetDataValue(L"TRANSLATION", EMPTY_WSTRING);
    }
    dataGroup.getRepository()->clear();
    m_bLoaded = true;
}

CStringTranslate::CStringTranslate(const std::wstring& fileName)
    : m_sFileName(fileName), m_bLoaded(false)
{
    reload();
    if (m_gStringTranslate == NULL)
        m_gStringTranslate = this;
}
