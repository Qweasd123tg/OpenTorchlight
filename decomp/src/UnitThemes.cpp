#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "UnitThemeParticle.h"
#include "UnitThemes.h"
#include "TArrayList.h"

CUnitThemes* CUnitThemes::getSingleton()
{
    return reinterpret_cast<CUnitThemes*>(g_pUnitThemes);
}

CUnitThemes::~CUnitThemes()
{
    m_Themes.deleteAll();
    g_pUnitThemes = NULL;
}

CUnitThemes::CUnitThemes(const wchar_t *fileName)
{
    typedef TArrayList<int> TUnitThemesList;

    std::wstring *file = new (reinterpret_cast<void *>(
        reinterpret_cast<char *>(this) + 0x10)) std::wstring(fileName);

    TUnitThemesList *unitThemes;
    try
    {
        unitThemes = new (reinterpret_cast<void *>(
            reinterpret_cast<char *>(this) + 0x18)) TUnitThemesList(10);
    }
    catch (...)
    {
        file->~basic_string();
        throw;
    }

    class Cleanup
    {
    public:
        Cleanup(TUnitThemesList *unitThemes_, std::wstring *file_)
            : m_unitThemes(unitThemes_), m_file(file_)
        {
        }

        ~Cleanup()
        {
            m_unitThemes->~TUnitThemesList();
            m_file->~basic_string();
        }

    private:
        TUnitThemesList *m_unitThemes;
        std::wstring *m_file;
    };

    Cleanup cleanup(unitThemes, file);

    extern void reloadUnitThemes(CUnitThemes *) __asm__(
        "_ZN11CUnitThemes6reloadEv");

    reloadUnitThemes(this);
    if (g_pUnitThemes == NULL)
        g_pUnitThemes = this;
}
