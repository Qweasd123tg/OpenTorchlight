#ifndef SKILLPARSER_H
#define SKILLPARSER_H

#include <map>
#include <string>

#include "DataGroup.h"
#include "ResourceManager.h"
#include "ResourceSettings.h"
#include "RunicCore.h"
#include "Skill.h"
#include "TArrayList.h"

class CSkillParser : public CRunicCore
{
public:
    virtual ~CSkillParser();

    static CSkillParser* getSingleton();
    void clearSkills();
    void getSkillNames(TArrayList<std::wstring>& skillNames);
    CDataGroup* getSkillData(const std::wstring& skillName);
    CSkill* getSkill(CResourceManager* resourceManager, const std::wstring& skillName);
    void parseSkill(const std::wstring& fileName);
    void parseSkills();
    void reloadSkills();

    CSkillParser(CResourceSettings* resourceSettings);

    std::map<std::wstring, CDataGroup*> m_skills;
    CResourceSettings* m_pResourceSettings;
};

#endif
