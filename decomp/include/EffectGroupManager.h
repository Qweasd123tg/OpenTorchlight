#ifndef EFFECTGROUPMANAGER_H
#define EFFECTGROUPMANAGER_H

#include <map>
#include <string>

#include "Affix.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CEffectGroupManager : public CRunicCore
{
public:
	virtual ~CEffectGroupManager();

	void getAffixNames(TArrayList<std::wstring>& affixNames);
	void clean();
	CAffix* getAffix(const std::wstring& name);
	void rollAndCreateRandomAffixes(
		unsigned int unitType,
		unsigned int affixLevel,
		unsigned int effectCost,
		TArrayList<CAffix*>& result);
	void reload();

	explicit CEffectGroupManager(const wchar_t* path);

	std::wstring m_sPath;
	std::map<std::wstring, CAffix*> m_mapAffixes;
	std::map<unsigned int, TArrayList<CAffix*>*> m_mapAffixesByUnitType;
};

#endif
