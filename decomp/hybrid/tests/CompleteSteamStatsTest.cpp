#include <map>
#include <string>
#include <cstring>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#define private public
#include "SteamStats.h"
#undef private
#include "iStatListener.h"
#include "GameVariables.h"
TL_ORIGINAL(void, systemsStatsCtor, (CSteamStats*), "_ZN11CSteamStatsC1Ev")
TL_ORIGINAL(void, systemsStatsDtor, (CSteamStats*), "_ZN11CSteamStatsD1Ev")
TL_ORIGINAL(void, systemsStatsReload, (CSteamStats*, CPlayer*), "_ZN11CSteamStats16reloadPlayerDataEP7CPlayer")
extern "C" void newStatsReload(CSteamStats*, CPlayer*) __asm__("_ZN11CSteamStats16reloadPlayerDataEP7CPlayer");
TL_ORIGINAL(void, systemsStatsListeners, (CSteamStats*), "_ZN11CSteamStats19updateStatListenersEv")
extern "C" void newStatsCtor(CSteamStats*) __asm__("_ZN11CSteamStatsC1Ev");
extern "C" void newStatsListeners(CSteamStats*) __asm__("_ZN11CSteamStats19updateStatListenersEv");
namespace {
struct Case { unsigned mode, count, mutation; };
autotest::Capture* capture;
CSteamStats* currentStats;
unsigned callbacks;
void word(autotest::Capture& out, unsigned x) { out.add(&x,sizeof(x)); }
struct Listener : iStatListener {
    unsigned identity, mutation;
    Listener(unsigned id, unsigned m) : identity(id), mutation(m) {}
    ~Listener() {}
    void statChanged(unsigned key, UNIONDATA32BIT old, UNIONDATA32BIT value) {
        word(*capture, identity);word(*capture,key);word(*capture,old.m_uValue);word(*capture,value.m_uValue);
        ++callbacks;
        if (mutation==1) currentStats->m_statValues[key] += 7;
        if (mutation==2 && callbacks==1) {
            CSteamStats::SStatChange change;change.stat=static_cast<ESTATS>(30);change.value.m_uValue=0x12345678;
            currentStats->m_pendingStatChanges.add(change);
        }
    }
};
void side(void* raw, autotest::Capture& out, bool ours) {
    const Case& c=*static_cast<Case*>(raw);
    union Storage { long double alignment; unsigned char data[sizeof(CSteamStats)]; } storage;
    std::memset(storage.data,0xa5,sizeof(storage.data));
    CSteamStats* self=reinterpret_cast<CSteamStats*>(storage.data);
    long previous=m_gStatsObject;
    capture=&out;currentStats=self;callbacks=0;
    if(c.mode==0) {
        if(ours)autotest::invoke(out,newStatsCtor,self);else autotest::invoke(out,systemsStatsCtor,self);
        word(out,m_gStatsObject==reinterpret_cast<long>(self));
        out.add(&self->m_bStatsEnabled,2);out.add(&self->m_fStatsUpdateInterval,8);
        word(out,self->m_bStatsDirty);word(out,self->m_pStatsFile==NULL);word(out,self->m_bLocalUpdatesEnabled);
        word(out,self->m_statValues.size());word(out,self->m_statValues.m_nCapacity);word(out,self->m_statValues.m_nGrowBy);
        for(unsigned i=0;i<self->m_statValues.size();++i)word(out,self->m_statValues[i]);
        word(out,self->m_statListeners.size());
        for(CSteamStats::TStatListenerMap::iterator it=self->m_statListeners.begin();it!=self->m_statListeners.end();++it) {
            word(out,it->first);word(out,it->second->size());word(out,it->second->m_nCapacity);word(out,it->second->m_nGrowBy);
        }
        word(out,self->m_pendingStatChanges.size());word(out,self->m_pendingStatChanges.m_nCapacity);word(out,self->m_pendingStatChanges.m_nGrowBy);
        word(out,self->m_game==NULL);word(out,self->m_pPlayer==NULL);
    } else if(c.mode==9) {
        systemsStatsCtor(self);
        for(unsigned i=0;i<31;++i)self->m_statValues[i]=0x20000000+i;
        union PlayerStorage { long double alignment; unsigned char data[sizeof(CPlayer)]; } playerStorage;
        std::memset(playerStorage.data,0,sizeof(playerStorage.data));
        CPlayer* player=reinterpret_cast<CPlayer*>(playerStorage.data);
        int gold=static_cast<int>(0x80001234u+c.count), level=static_cast<int>(0x40001234u+c.count);
        std::memcpy(playerStorage.data+0x444,&gold,4);std::memcpy(playerStorage.data+0x7f0,&level,4);
        unsigned char* definitions=reinterpret_cast<unsigned char*>(0x153a860);
        int saved[31][2];
        for(unsigned i=0;i<31;++i) {
            std::memcpy(saved[i],definitions+i*24,8);
            int changed[2]={ ((i+c.count)%3==0)?-1:static_cast<int>(i), static_cast<int>((i+c.count)%3) };
            if(i==28||i==29){changed[0]=-1;changed[1]=0;}
            std::memcpy(definitions+i*24,changed,8);
        }
        self->m_statValues.m_nCapacity=c.mutation==1?1:31;
        CPlayer* selected=c.mutation==2?NULL:player;
        if(ours)autotest::invoke(out,newStatsReload,self,selected);else autotest::invoke(out,systemsStatsReload,self,selected);
        word(out,self->m_pPlayer==selected);
        for(unsigned i=0;i<31;++i)word(out,self->m_statValues.m_pData[i]);
        for(unsigned i=0;i<31;++i)std::memcpy(definitions+i*24,saved[i],8);
    } else {
        systemsStatsCtor(self);
        Listener a(1,c.mutation),b(2,c.mutation),d(3,0);
        self->m_statListeners[static_cast<ESTATS>(0)]->add(&a);
        if(c.mode&1)self->m_statListeners[static_cast<ESTATS>(0)]->add(&b);
        self->m_statListeners[static_cast<ESTATS>(30)]->add(&d);
        if(c.mode&2) { delete self->m_statListeners[static_cast<ESTATS>(15)];self->m_statListeners.erase(static_cast<ESTATS>(15)); }
        for(unsigned i=0;i<31;++i)self->m_statValues[i]=0x1000+i;
        const int keys[]={0,15,30,31,0,-1};
        for(unsigned i=0;i<c.count;++i) {
            CSteamStats::SStatChange change;change.stat=static_cast<ESTATS>(keys[i%6]);change.value.m_uValue=0x80001234u+i;
            self->m_pendingStatChanges.add(change);
        }
        if(ours)autotest::invoke(out,newStatsListeners,self);else autotest::invoke(out,systemsStatsListeners,self);
        word(out,callbacks);word(out,self->m_pendingStatChanges.size());word(out,self->m_pendingStatChanges.m_nCapacity);word(out,self->m_pendingStatChanges.m_pData==NULL);
        for(unsigned i=0;i<31;++i)word(out,self->m_statValues[i]);
    }
    systemsStatsDtor(self);m_gStatsObject=previous;
}
void original(void* p,autotest::Capture& out){side(p,out,false);}
void candidate(void* p,autotest::Capture& out){side(p,out,true);}
int compare(const tlhybrid_host* host,unsigned mode) {
    autotest::Stats stats={0,0,0};unsigned cases=0;int failures=0;
    autotest::Coverage coverage(mode?"complete_stats_listeners":"complete_stats_constructor",reinterpret_cast<uintptr_t>(mode?&systemsStatsListeners:&systemsStatsCtor));
    for(unsigned shape=0;shape<(mode?4u:1u);++shape)for(unsigned n=0;n<(mode?8u:1u);++n)for(unsigned m=0;m<(mode?3u:1u);++m) {
        Case c={mode?shape+1:0,n,m};
        bool ok=autotest::compareCase(original,candidate,&c,stats,host,mode?"complete_stats_listeners":"complete_stats_constructor",cases++,&coverage);
        TL_CHECK(failures,ok);
    }
    coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);
}
}
TL_TEST(complete_stats_constructor){return compare(host,0);}
TL_TEST(complete_stats_listeners){return compare(host,1);}
TL_TEST(complete_stats_reload_player) {
    autotest::Stats stats={0,0,0};unsigned cases=0;int failures=0;
    autotest::Coverage coverage("complete_stats_reload_player",reinterpret_cast<uintptr_t>(&systemsStatsReload));
    for(unsigned n=0;n<7;++n)for(unsigned m=0;m<3;++m) {
        Case c={9,n,m};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_stats_reload_player",cases++,&coverage);TL_CHECK(failures,ok);
    }
    coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);
}
