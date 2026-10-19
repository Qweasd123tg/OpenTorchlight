#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "GameClientNativeSteam.h"
namespace {
int worker(const tlhybrid_host*host){int failures=0;nativegame::Services services;if(!services.ready())return 1;CSteamStats*previous=CSteamStats::getSingleton();TSafePointer<CSteamStats>weak;
 {gameclient_fixture::SteamOwner owner;weak.setObject(owner.stats);TL_CHECK(failures,owner.stats->m_statValues.size()==31);TL_CHECK(failures,!owner.stats->m_bStatsEnabled);owner.stats->forceStatsToSave();host->log("    genuine native SteamStats C1/singleton/forceStatsToSave completed\n");}
 TL_CHECK(failures,weak.getObject()==NULL);TL_CHECK(failures,CSteamStats::getSingleton()==previous);host->log("    genuine native SteamStats D1 completed; weak expired; singleton restored\n");return failures;
}
}
TL_TEST(gameclient_native_steam){return systems_fixture::isolated(&worker,host);}
