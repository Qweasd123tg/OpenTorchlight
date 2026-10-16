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
    if (getSingleton() == NULL)
        return NULL;

    std::map<std::wstring, CDataGroup*>::iterator i;
    {
        std::wstring name = STRINGS::StringUpper(skillName);
        i = getSingleton()->m_skills.find(name);
    }
    if (i != getSingleton()->m_skills.end())
        return i->second;
    return NULL;
}

CSkill* CSkillParser::getSkill(CResourceManager* resourceManager, const std::wstring& skillName)
{
    if (getSingleton() == NULL)
        return NULL;

    std::map<std::wstring, CDataGroup*>::iterator it;
    {
        std::wstring upperSkillName = STRINGS::StringUpper(skillName);
        it = getSingleton()->m_skills.find(upperSkillName);
    }

    if (it == getSingleton()->m_skills.end())
        return NULL;

    return new CSkill(resourceManager, it->second);
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
    CSkillParser* parser = getSingleton();
    if (parser != NULL) {
        parser->parseSkills();
    }
}

CSkillParser::CSkillParser(CResourceSettings* resourceSettings)
    : CRunicCore(), m_skills(), m_pResourceSettings(resourceSettings)
{
    g_SkillParser = (long)this;

    parseSkills();
}

void CSkillParser::getSkillNames(TArrayList<std::wstring>& skillNames)
{
    for (std::map<std::wstring, CDataGroup*>::iterator i = getSingleton()->m_skills.begin();
         i != getSingleton()->m_skills.end(); ++i)
        skillNames.add(i->first);
}
