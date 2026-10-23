#include <Ogre.h>
#include "AutoTest.h"
#include "SafePointer.h"
#include "SystemsFixtureWorker.h"
#define private public
#define protected public
#include "Player.h"
#include "Equipment.h"
#include "SharedStash.h"
#include "Inventory.h"
#undef protected
#undef private
#include "NativeGameServices.h"
#include "ParticleNativeOwners.h"

TL_ORIGINAL(void, stashOldSetPlayer, (CSharedStash*, CPlayer*), "_ZN12CSharedStash9setPlayerEP7CPlayer")
TL_ORIGINAL(void, stashOldCtor, (CSharedStash*,const wchar_t*,const wchar_t*), "_ZN12CSharedStashC1EPKwS1_")
extern "C" void stashNewSetPlayer(CSharedStash*,CPlayer*) __asm__("_ZN12CSharedStash9setPlayerEP7CPlayer");
extern "C" void* nativeSharedStash __asm__("_ZL14g_pSharedStash");

namespace {
struct Case { unsigned seed; bool negative; };
ParticleNativeOwners owners;
CPlayer* players[2];

template<class T> void value(autotest::Capture& out, const T& v) { out.add(&v,sizeof v); }

void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case c = *static_cast<Case*>(raw);
    union Storage { long double alignment; char bytes[sizeof(CSharedStash)]; } storage;
    std::memset(storage.bytes,0x5a,sizeof storage.bytes);
    CSharedStash* stash = reinterpret_cast<CSharedStash*>(storage.bytes);
    nativeSharedStash = NULL;
    stashOldCtor(stash,L"missing-stash.bin",L"missing-alternate-stash.bin");
    CPlayer* player = c.seed%8 == 1 ? NULL : players[c.seed%2];
    players[0]->m_saveOnDeath = bool(c.seed&2);
    players[1]->m_saveOnDeath = bool(c.seed&2);
    stash->m_bUseAlternateStash = bool(c.seed&4);
    CInventory* initial = stash->m_pInventory;
    initial->m_pPositionableObject = players[1-c.seed%2];
    TSafePointer<CRunicCore> weak[40];
    unsigned weakCount = 0;
    weak[weakCount++].setObject(initial);
    unsigned count = (c.seed/8)%8;
    for (unsigned i=0; i<count; ++i) {
        CEquipmentRef* ref = new CEquipmentRef;
        ref->m_pEquipment = NULL;
        ref->m_iSlot = i;
        ref->m_originalSlot = i+10;
        ref->m_flag20 = false;
        ref->m_effectsEnabled = false;
        weak[weakCount++].setObject(ref);
        if ((c.seed+i)%3) {
            ref->m_pEquipment = new CEquipment((c.seed+i)&1 ? NULL : owners.resources);
            ref->m_pEquipment->setParentGuid(7654321+i);
            weak[weakCount++].setObject(ref->m_pEquipment);
        }
        initial->m_equipmentRefs.add(ref);
    }
    if (c.seed%8==0) {
        delete stash->m_pInventory;
        stash->m_pInventory = NULL;
    }
    typedef void (*Call)(CSharedStash*,CPlayer*);
    Call call = ours ? stashNewSetPlayer : stashOldSetPlayer;
    if (!autotest::beginInvocation(out,call)) return;
    call(stash,player);
    out.callCompleted = 1;
    if (ours && c.negative) stash->m_bUseAlternateStash = !stash->m_bUseAlternateStash;
    value(out,stash->m_bUseAlternateStash);
    bool hasInventory = stash->m_pInventory != NULL;
    value(out,hasInventory);
    if (hasInventory) {
        CInventory* inventory = stash->m_pInventory;
        unsigned owner = inventory->m_pPositionableObject==players[0] ? 1 : inventory->m_pPositionableObject==players[1] ? 2 : 0;
        value(out,owner);
        unsigned items = inventory->m_equipmentRefs.size();
        value(out,items);
        for (unsigned i=0; i<items; ++i) {
            CEquipmentRef* ref = inventory->m_equipmentRefs[i];
            bool hasEquipment = ref->m_pEquipment != NULL;
            value(out,hasEquipment);
            value(out,ref->m_iSlot);
            if (hasEquipment) {
                value(out,ref->m_pEquipment->getParentGuid());
                bool resources = ref->m_pEquipment->getResourceManager()==owners.resources;
                bool node = ref->m_pEquipment->getSceneNode()!=NULL;
                value(out,resources); value(out,node);
            }
        }
    }
    for (unsigned i=0; i<weakCount; ++i) {
        bool alive = weak[i].getObject()!=NULL;
        value(out,alive);
    }
}
void before(void* p,autotest::Capture& out) { side(p,out,false); }
void after(void* p,autotest::Capture& out) { side(p,out,true); }
int worker(const tlhybrid_host* host)
{
    owners = particleNativeOwners(0);
    players[0] = nativegame::createPlayer(owners.resources);
    players[1] = nativegame::createPlayer(owners.resources);
    players[0]->setGuid(1234567);
    players[1]->setGuid(9876543);
    autotest::Coverage coverage("shared_stash_player_recovery",0xe16880);
    for (unsigned i=0; i<64; ++i) {
        Case c = {i,false}; autotest::Outcome a,b;
        autotest::runChild(before,&c,a,2000,10000);
        autotest::runChild(after,&c,b,2000,10000);
        if (coverage.observe(host,a,b)) {
            host->log("    stash seed %u status %d/%d issue %u/%u bytes %lu/%lu\n",i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host);
    Case c = {19,true}; autotest::Outcome a,b;
    autotest::runChild(before,&c,a,2000,10000);
    autotest::runChild(after,&c,b,2000,10000);
    bool detected = a.capture.length!=b.capture.length || std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    return !detected || autotest::incomplete(a) || autotest::incomplete(b) || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus;
}
}
TL_TEST(shared_stash_player_recovery) { return systems_fixture::isolated(worker,host); }
