#ifndef UNITTHEMES_H
#define UNITTHEMES_H
#include "RunicCore.h"
#include "TArrayList.h"
#include "UnitTheme.h"
#include <string>
class CUnitThemes : public CRunicCore
{
public:
    void reload();
    CUnitThemes(const wchar_t* filename);
    virtual ~CUnitThemes();
    static CUnitThemes* getSingleton();
    TArrayList<CUnitTheme*>& getThemes() { return m_Themes; }
    CUnitTheme* getTheme(long long guid) {
        for(unsigned int i=0;i<m_Themes.size();++i)
            if(m_Themes[i]->getGuid()==guid)return m_Themes[i];
        return NULL;
    }
    CUnitTheme* getTheme(const std::wstring& name) {
        for(unsigned int i=0;i<m_Themes.size();++i)
            if(m_Themes[i]->getName()==name)return m_Themes[i];
        return NULL;
    }
private:
    std::wstring m_sFilename;
    TArrayList<CUnitTheme*> m_Themes;
};
#endif
