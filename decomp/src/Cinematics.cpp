#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "Cinematics.h"
#include "DataGroup.h"
#include "RunicCore.h"

CCinematics* CCinematics::getSingleton()
{
    return reinterpret_cast<CCinematics*>(g_pCinematics);
}

class CCinematic
{
public:
    std::wstring m_sName;
    std::wstring m_sText;
    std::wstring m_sImage;
    std::wstring m_sSound;

    void load(CDataGroup* data);
};

void CCinematic::load(CDataGroup* data)
{
    m_sName = data->GetDataValue(L"NAME", L"");
    m_sText = data->GetDataValue(L"TEXT", L"");
    m_sImage = data->GetDataValue(L"IMAGE", L"");
    m_sSound = data->GetDataValue(L"SOUND", L"");
}

CCinematics::CCinematics(const wchar_t* path)
    : CRunicCore(), m_sPath(path), m_lCinematics(10)
{
    if (g_pCinematics == NULL) {
        g_pCinematics = this;
        reload();
    }
}
