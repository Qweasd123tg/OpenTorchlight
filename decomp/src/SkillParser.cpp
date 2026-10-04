#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "SkillParser.h"
#include "DataGroup.h"
#include "FileSystem.h"
#include "ResourceManager.h"
#include "ResourceSettings.h"
#include "RunicCore.h"
#include "Skill.h"
#include "StringUtilities.h"
#include "TArrayList.h"

CSkillParser* CSkillParser::getSingleton()
{
    return reinterpret_cast<CSkillParser*>(g_SkillParser);
}

void CSkillParser::clearSkills()
{
    for (std::map<std::wstring, CDataGroup*>::iterator i = m_skills.begin(); i != m_skills.end(); ++i)
    {
        if (i->second != NULL)
        {
            delete i->second;
        }
    }
    m_skills.clear();
}

CSkillParser::~CSkillParser()
{
    clearSkills();
    g_SkillParser = NULL;
}

CDataGroup *CSkillParser::getSkillData(const std::wstring &skillName)
{
    CSkillParser *parser = getSingleton();
    if (parser == NULL)
        return NULL;

    std::wstring name = STRINGS::StringUpper(skillName);
    std::map<std::wstring, CDataGroup *>::iterator it = parser->m_skills.find(name);
    if (it != parser->m_skills.end())
        return it->second;

    return NULL;
}

CSkill* CSkillParser::getSkill(CResourceManager* resourceManager, const std::wstring& skillName)
{
    if (getSingleton() == NULL)
        return NULL;

    std::wstring upperSkillName = STRINGS::StringUpper(skillName);
    std::map<std::wstring, CDataGroup*>::iterator it =
        getSingleton()->m_skills.find(upperSkillName);

    if (it == getSingleton()->m_skills.end())
        return NULL;

    return new CSkill(reinterpret_cast<CResourceManager*>(this), it->second);
}

void CSkillParser::parseSkills()
{
    if (m_pResourceSettings != 0)
    {
        clearSkills();

        std::wstring skillFolder =
            m_pResourceSettings->GetString(KRESOURCESETTING_S_SKILL_FOLDER);
        TArrayList<std::wstring> files;

        CFileSystem::getSingleton()->getFileList(
            skillFolder, files, L"*.dat", true, true, false, false);

        for (unsigned int i = 0; i < files.size(); ++i)
            parseSkill(files[i]);
    }
}

void CSkillParser::reloadSkills()
{
    if (g_SkillParser != NULL) {
        parseSkills();
    }
}

CSkillParser::CSkillParser(CResourceSettings* resourceSettings)
    : CRunicCore(), m_skills(), m_pResourceSettings(resourceSettings)
{
    g_SkillParser = (long)this;

    parseSkills();
}
