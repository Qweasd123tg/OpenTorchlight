#ifndef STEAMSTATS_H
#define STEAMSTATS_H

#include "DescriptorProp.h"
#include "GameEnums.h"
#include "Player.h"
#include "RunicCore.h"
#include "TArrayList.h"

#include <map>
#include <string>

class iStatListener;

class CSteamStats : public CRunicCore
{
public:
	struct SStatChange
	{
		ESTATS stat;
		UNIONDATA32BIT value;
	};

	typedef std::map<ESTATS, TArrayList<iStatListener*> > TStatListenerMap;

	virtual ~CSteamStats();

	void reloadPlayerData(CPlayer* player);
	void update(float elapsedTime);
	void forceStatsToSave();
	void setStatInt(ESTATS stat, unsigned int value);
	void incrementStat(ESTATS stat, int amount);
	void setStatFloat(ESTATS stat, float value);

	int getStatInt(ESTATS stat) const;
	float getStatFloat(ESTATS stat) const;
	int getPlayerStatInt(ESTATS stat) const;
	float getPlayerStatFloat(ESTATS stat) const;

	static CSteamStats* getSingleton();

	bool StoreStats();
	void statModified(ESTATS stat, UNIONDATA32BIT value);
	void updateStatListeners();
	void checkForLocalUpdates(float elapsedTime);
	void addStatListener(ESTATS stat, iStatListener* listener);

	CSteamStats();

	bool m_bStatsEnabled;
	bool m_bStatsInitialized;
	unsigned char m_gap12[2];

	float m_fStatsUpdateInterval;
	float m_fLocalUpdateTimer;

	bool m_bStatsDirty;
	unsigned char m_gap1D[3];

	union
	{
		std::wstring* m_pStatsFile;
		std::wstring* stat;
		long long value;
	};

	bool m_bLocalUpdatesEnabled;
	unsigned char m_gap29[7];

	TArrayList<int> m_statValues;
	TStatListenerMap m_statListeners;
	TArrayList<SStatChange> m_pendingStatChanges;

	long long m_llLastStoreTime;
	CPlayer* m_pPlayer;
};

#endif
