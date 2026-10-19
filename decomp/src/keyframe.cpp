#include "Keyframe.h"
#include "DataGroup.h"
#include "UnitThemes.h"
#include "CameraShake.h"
#include "AnimationDefines.h"
#include "StringUtilities.h"
#include "FileUtilities.h"
#include "EmptyStrings.h"
#include <vector>

CKeyframe::~CKeyframe()
{
    if (m_cameraShake) {
        delete m_cameraShake;
        m_cameraShake = NULL;
    }
}

CKeyframe::CKeyframe(int animation, CDataGroup* group)
    : m_animationIndex(animation), m_offset(0, 0, 0), m_theme(NULL),
      m_mode(1), m_flag4C(true), m_cameraShake(NULL)
{
    m_iEventCode = STRINGS::getStringIndex(STRINGS::StringUpper(group->GetDataValue(L"NAME", EMPTY_WSTRING)),
                                         gKEYFRAME_TYPES, 29, 0, false);
    m_themeName = STRINGS::StringUpper(group->GetDataValue(L"UNITTHEME", EMPTY_WSTRING));
    if (m_themeName != EMPTY_WSTRING)
        m_theme = CUnitThemes::getSingleton()->getTheme(m_themeName);
    m_frame = group->GetDataValue(L"FRAME", 0.0f);
    m_text = group->GetDataValue(L"SOUND", EMPTY_WSTRING);
    m_text = group->GetDataValue(L"LAYOUT", m_text);
    m_text = group->GetDataValue(L"CAMERASHAKE", m_text);
    m_text = FILESYSTEM::CleanPath(m_text);
    m_flag4C = group->GetDataValue(L"PARTICLEATTACHES", true);
    STRINGS::StringConvertToNarrow(group->GetDataValue(L"BONE", EMPTY_WSTRING), m_name);
    m_mode = group->GetDataValue(L"PARTICLECOUNT", 1);
    if (m_mode < 1)
        m_mode = 1;
    std::vector<CDataGroup*> offsets;
    if (group->GetDataGroupsMatchingName(L"BONEOFFSET", &offsets)) {
        CDataGroup* offset = offsets[0];
        m_offset.x = offset->GetDataValue(L"X", 0.0f);
        m_offset.y = offset->GetDataValue(L"Y", 0.0f);
        m_offset.z = offset->GetDataValue(L"Z", 0.0f);
    }
    if ((m_iEventCode == 26 || m_iEventCode == 14) && m_text != EMPTY_WSTRING) {
        float duration = group->GetDataValue(L"CAMERASHAKEDURATION", 0.0f);
        duration = 0.01f < duration ? duration : 0.01f;
        m_cameraShake = new CCameraShake(m_text, Ogre::Vector3(0, 1, 0), duration);
    }
}
