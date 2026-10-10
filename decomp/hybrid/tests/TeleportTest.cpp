// Differential protocol test for CTeleport::activate.
// UI/physics collaborators are spies on both sides; no live teleport simulation.
// Original primary vtables retain RTTI prefixes; only verified slots are redirected.
// Each case rejects crashes and compares callback order, arguments and state.
#include <cstdio>
#include <cstring>
#include <limits>
#include <new>
#include <vector>
#include <unistd.h>
#include "AutoTest.h"
#include "Detour.h"
#include "Teleport.h"
#include "GameClient.h"
#include "Player.h"
#include "Level.h"

class CLevel;

TL_ORIGINAL(void, originalActivate, (CTeleport *, Ogre::Vector3, Ogre::Vector3),
            "_ZN9CTeleport8activateEN4Ogre7Vector3ES1_")

// Nonvirtual collaborator spies.
TL_FUNCTION(tpStopPathing, "_ZN10CCharacter11stopPathingEv")
TL_FUNCTION(tpSetPosition, "_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(tpDropToGround, "_ZN10CCharacter12dropToGroundER6CLevelfb")
TL_FUNCTION(tpTeleportToMaster, "_ZN10CCharacter16teleportToMasterEf")

extern "C" void *teleportTable[] __asm__("_ZTV9CTeleport");
extern "C" void *playerTable[] __asm__("_ZTV7CPlayer");

namespace {

// ---------------------------------------------------------------- constants

const unsigned int kClients = 3;      // fake CGameClient objects
const unsigned int kPlayers = 3;      // fake CPlayer objects
const unsigned int kMaxFollowers = 6; // followers preloaded per player
const unsigned int kTeleportSlots = 58;   // virtual slots covered on CTeleport
const unsigned int kPlayerSlots = 132;     // covers verified slot 77
const unsigned int kSetDirectionSlot = 36;    // offset 0x120
const unsigned int kRemoveAvoidanceSlot = 77; // offset 0x268
const unsigned int kControllerEventSlot = 6;  // offset 0x30

// Call-trace opcodes (fixed, so traces are comparable across children).
enum TraceOp
{
    kOpStopPathing = 1,
    kOpRemoveAvoidance = 2,
    kOpSetPosition = 3,
    kOpSetDirection = 4,
    kOpDropToGround = 5,
    kOpFollowerTeleport = 6,
    kOpBroadcastEvent = 7,
    kOpPlayerBroadcast = 8
};

// ---------------------------------------------------------------- case input

struct Case
{
    bool nullResource;
    bool enabled;             // CTeleport::m_bEnabled (+0x100), activate ignores it
    unsigned char clients;    // entries present in resourceManager 0's list
    unsigned char nullMask;   // bit i: client i has a null player
    unsigned char sharedMask; // bit i: client i points at players[0]
    unsigned char followers[kPlayers];
    unsigned char growBy;         // TArrayList growBy for both resource managers
    unsigned char mutate;         // callback mutation bits, see kMut*
    float p[3];
    float d[3];
};

// Callback mutation bits. All of them are performed at most once per activate so
// that list/vector growth stays bounded and the run terminates.
const unsigned char kMutSwapInStopPathing = 1;
const unsigned char kMutSwapInSetDirection = 2;
const unsigned char kMutGrowFollowers = 4;
const unsigned char kMutAppendClient = 8;
const unsigned char kMutSwapInDropToGround = 16;
const unsigned char kMutSwapEveryCall = 32;

// ---------------------------------------------------------------- child state

typedef std::vector<CCharacter *> FollowerList;

std::vector<unsigned int> trace;

void *gTeleport;
void *gResources[2];
void *gLevels[2];
void *gClients[kClients];
void *gPlayers[kPlayers];
void *gFollowers[kPlayers][kMaxFollowers];
void *gExtraFollower;
unsigned int gMutate;
unsigned int gSwapTurn;
unsigned int gGrowthOps;
unsigned int gAppendOps;
unsigned int gSwapOps;
unsigned int gDropOps;
unsigned int gTraceOverflow;

std::vector<CCharacter *> *gFollowerLists[kPlayers];
TArrayList<CGameClient *> *gGameClientLists[2];
void pointerAt(void *p, size_t at, void *v)
{
    std::memcpy(static_cast<char *>(p) + at, &v, sizeof(v));
}

void *pointerGet(void *p, size_t at)
{
    void *v = 0;
    std::memcpy(&v, static_cast<char *>(p) + at, sizeof(v));
    return v;
}

unsigned int bits(float f)
{
    unsigned int u = 0;
    std::memcpy(&u, &f, sizeof(u));
    return u;
}

// Stable integer identity: never a process address.
unsigned int who(void *p)
{
    if (p == 0)
        return 0;
    if (p == gTeleport)
        return 1;
    for (unsigned int i = 0; i < 2; ++i)
    {
        if (p == gLevels[i])
            return 40 + i;
        if (p == gResources[i])
            return 30 + i;
    }
    for (unsigned int i = 0; i < kClients; ++i)
        if (p == gClients[i])
            return 20 + i;
    for (unsigned int i = 0; i < kPlayers; ++i)
        if (p == gPlayers[i])
            return 10 + i;
    if (p == gExtraFollower)
        return 200;
    for (unsigned int p2 = 0; p2 < kPlayers; ++p2)
        for (unsigned int f = 0; f < kMaxFollowers; ++f)
            if (p == gFollowers[p2][f])
                return 60 + p2 * 8 + f;
    return 99;
}

void record(unsigned int op, void *receiver, unsigned int a = 0, unsigned int b = 0,
            unsigned int c = 0, unsigned int e = 0)
{
    if (trace.size() + 6 > 4096)
    {
        if (gTraceOverflow != std::numeric_limits<unsigned int>::max())
            ++gTraceOverflow;
        return;
    }
    trace.push_back(op);
    trace.push_back(who(receiver));
    trace.push_back(a);
    trace.push_back(b);
    trace.push_back(c);
    trace.push_back(e);
}

void resetTrace()
{
    gTraceOverflow = 0;
    trace.clear();
}

void captureTrace(autotest::Capture& out)
{
    size_t n = trace.size();
    out.add(&n, sizeof(n));
    for (size_t i = 0; i < n; ++i)
        out.add(&trace[i], 4);
    out.add(&gTraceOverflow, sizeof(gTraceOverflow));
    // Equal discarded counts cannot establish equality of the missing events.
    if (gTraceOverflow && out.issue == autotest::Capture::Complete)
        out.issue = autotest::Capture::Overflow;
}

unsigned int playerIndex(void *p)
{
    for (unsigned int i = 0; i < kPlayers; ++i)
        if (p == gPlayers[i])
            return i;
    return kPlayers;
}

// Switches the player's resource manager between the two fakes. getLevel() must
// be re-read after such a switch, so the level argument of the next level-taking
// call has to change too.
void maybeSwapResource(void *player, unsigned char trigger)
{
    if (!(gMutate & (trigger | kMutSwapEveryCall)))
        return;
    if ((gMutate & kMutSwapEveryCall) == 0 && gSwapOps != 0)
        return;
    ++gSwapOps;
    gSwapTurn = (gSwapTurn + 1) & 1;
    pointerAt(player, 0x68, gResources[gSwapTurn]);
}

void growFollowersOnce(void *follower)
{
    if (!(gMutate & kMutGrowFollowers) || gGrowthOps != 0)
        return;
    for (unsigned int p = 0; p < kPlayers; ++p)
        for (unsigned int f = 0; f < kMaxFollowers; ++f)
            if (follower == gFollowers[p][f])
            {
                ++gGrowthOps;
                // Mutates the list while activate is iterating it: the follower
                // count must be re-read, not cached.
                gFollowerLists[p]->push_back(static_cast<CCharacter *>(gExtraFollower));
                return;
            }
}

void appendClientOnce(void *)
{
    if (!(gMutate & kMutAppendClient) || gAppendOps != 0)
        return;
    if (gGameClientLists[0]->size() >= 8)
        return;
    ++gAppendOps;
    // Appends a client while the outer loop is running: the client count must be
    // re-read, not cached.
    gGameClientLists[0]->add(static_cast<CGameClient *>(gClients[kClients - 1]));
}

// ---------------------------------------------------------------- redirect fakes

void stopPathingSpy(void *self)
{
    record(kOpStopPathing, self);
    maybeSwapResource(self, kMutSwapInStopPathing);
}

void setPositionSpy(void *self, const Ogre::Vector3 &v)
{
    record(kOpSetPosition, self, bits(v.x), bits(v.y), bits(v.z));
    // Fixture-only scratch location, not a recovered position offset.
    std::memcpy(static_cast<char *>(self) + 0x5f0, &v.x, 12);
}

void dropToGroundSpy(void *self, CLevel *level, float height, bool snap)
{
    record(kOpDropToGround, self, who(level), bits(height), snap ? 1u : 0u);
    ++gDropOps;
    maybeSwapResource(self, kMutSwapInDropToGround);
}

void teleportToMasterSpy(void *self, float f)
{
    record(kOpFollowerTeleport, self, bits(f));
    growFollowersOnce(self);
}

// Virtual stubs. Signatures follow the verified slots; a stub is only ever
// entered through the copied vtable, never by name.
void teleportEventStub(void *self, unsigned int eventId)
{
    record(kOpBroadcastEvent, self, eventId);
    appendClientOnce(self);
}

void setDirectionStub(void *self, Ogre::Vector3 direction)
{
    record(kOpSetDirection, self, bits(direction.x), bits(direction.y), bits(direction.z));
    std::memcpy(static_cast<char *>(self) + 0x610, &direction.x, 12);
    maybeSwapResource(self, kMutSwapInSetDirection);
}

void removeFromAvoidanceMapStub(void *self, CLevel *level)
{
    record(kOpRemoveAvoidance, self, who(level));
}

void playerBroadcastStub(void *self, unsigned int eventId)
{
    record(kOpPlayerBroadcast, self, eventId);
}

// ---------------------------------------------------------------- one side

void side(const Case &c, bool ours, autotest::Capture &out)
{
    __attribute__((aligned(16))) char self[0x110];
    __attribute__((aligned(16))) char resources[2][0x48];
    __attribute__((aligned(16))) char clients[kClients][0x3910];
    __attribute__((aligned(16))) char players[kPlayers][0xa70];
    __attribute__((aligned(16))) char levels[2][sizeof(CLevel)];
    __attribute__((aligned(16))) char followers[kPlayers][kMaxFollowers][0x720];
    __attribute__((aligned(16))) char extraFollower[0x720];

    std::memset(self, 0, sizeof(self));
    std::memset(resources, 0, sizeof(resources));
    std::memset(clients, 0, sizeof(clients));
    std::memset(players, 0, sizeof(players));
    std::memset(levels, 0, sizeof(levels));
    std::memset(followers, 0, sizeof(followers));
    std::memset(extraFollower, 0, sizeof(extraFollower));

    gTeleport = self;
    gExtraFollower = extraFollower;
    gMutate = c.mutate;
    gSwapTurn = 0;
    gGrowthOps = 0;
    gAppendOps = 0;
    gSwapOps = 0;
    gDropOps = 0;
    resetTrace();

    for (unsigned int r = 0; r < 2; ++r)
    {
        gResources[r] = resources[r];
        gLevels[r] = levels[r];
        pointerAt(resources[r], 0x18, levels[r]);
    }
    for (unsigned int i = 0; i < kClients; ++i)
        gClients[i] = clients[i];
    for (unsigned int p = 0; p < kPlayers; ++p)
    {
        gPlayers[p] = players[p];
        pointerAt(players[p], 0x68, c.nullResource ? NULL : resources[0]);
        for (unsigned int f = 0; f < kMaxFollowers; ++f)
            gFollowers[p][f] = followers[p][f];
    }

    // CTeleport vtable: RTTI prefix preserved, only BroadcastEvent slot routed to the recorder.
    void *ttable[2 + kTeleportSlots];
    std::memcpy(ttable, teleportTable, sizeof(ttable));
    ttable[2 + kControllerEventSlot] = reinterpret_cast<void *>(&teleportEventStub);
    pointerAt(self, 0, ttable + 2);
    pointerAt(self, 0x108, resources[0]);
    self[0x100] = c.enabled ? 1 : 0;

    // CPlayer vtable: RTTI prefix preserved, verified slots routed to recorders.
    void *ptable[2 + kPlayerSlots];
    std::memcpy(ptable, playerTable, sizeof(ptable));
    ptable[2 + kSetDirectionSlot] = reinterpret_cast<void *>(&setDirectionStub);
    ptable[2 + kRemoveAvoidanceSlot] = reinterpret_cast<void *>(&removeFromAvoidanceMapStub);
    ptable[2 + kControllerEventSlot] = reinterpret_cast<void *>(&playerBroadcastStub);
    for (unsigned int p = 0; p < kPlayers; ++p)
        pointerAt(players[p], 0, ptable + 2);

    // Client -> player wiring (null players and shared players included).
    for (unsigned int i = 0; i < kClients; ++i)
    {
        void *target = (c.sharedMask & (1u << i)) ? players[0] : players[i];
        if (c.nullMask & (1u << i))
            target = 0;
        pointerAt(clients[i], 0x58, target);
    }

    // Placement-construct the two GameClients lists and the follower vectors.
    for (unsigned int r = 0; r < 2; ++r)
    {
        gGameClientLists[r] = new (static_cast<char *>(resources[r]) + 0x28)
            TArrayList<CGameClient *>(c.growBy);
    }
    for (unsigned int i = 0; i < c.clients; ++i)
        gGameClientLists[0]->add(reinterpret_cast<CGameClient *>(clients[i]));
    for (unsigned int p = 0; p < kPlayers; ++p)
    {
        gFollowerLists[p] = new (static_cast<char *>(players[p]) + 0x648) FollowerList();
        unsigned int count = c.followers[p];
        if (count > kMaxFollowers)
            count = kMaxFollowers;
        for (unsigned int f = 0; f < count; ++f)
            gFollowerLists[p]->push_back(
                reinterpret_cast<CCharacter *>(followers[p][f]));
    }

    detour::Set patches;
    TL_REDIRECT(patches, tpStopPathing, &stopPathingSpy);
    TL_REDIRECT(patches, tpSetPosition, &setPositionSpy);
    TL_REDIRECT(patches, tpDropToGround, &dropToGroundSpy);
    TL_REDIRECT(patches, tpTeleportToMaster, &teleportToMasterSpy);
    bool failed = patches.failed();
    out.add(&failed, sizeof(failed));
    if (failed)
        _exit(17);

    CTeleport *object = reinterpret_cast<CTeleport *>(self);
    Ogre::Vector3 position(c.p[0], c.p[1], c.p[2]);
    Ogre::Vector3 direction(c.d[0], c.d[1], c.d[2]);
    if (ours)
        object->activate(position, direction);
    else
        originalActivate(object, position, direction);

    captureTrace(out);
    // Object state after the call.
    out.add(&self[0x100], 1);
    unsigned int resourceId = who(pointerGet(self, 0x108));
    out.add(&resourceId, sizeof(resourceId));
    for (unsigned int i = 0; i < kClients; ++i)
    {
        unsigned int id = who(pointerGet(clients[i], 0x58));
        out.add(&id, sizeof(id));
    }
    for (unsigned int p = 0; p < kPlayers; ++p)
    {
        unsigned int rm = who(pointerGet(players[p], 0x68));
        out.add(&rm, sizeof(rm));
        out.add(players[p] + 0x5f0, 12); // position handed to setPosition
        out.add(players[p] + 0x610, 12); // direction handed to setDirection
        unsigned int fs = gFollowerLists[p]->size();
        out.add(&fs, sizeof(fs));
    }
    for (unsigned int r = 0; r < 2; ++r)
    {
        unsigned int cs = gGameClientLists[r]->size();
        out.add(&cs, sizeof(cs));
    }
    out.add(&gGrowthOps, sizeof(gGrowthOps));
    out.add(&gAppendOps, sizeof(gAppendOps));
    out.add(&gSwapOps, sizeof(gSwapOps));
    out.add(&gDropOps, sizeof(gDropOps));

    // No patch or object-state leak between children.
    patches.restore();
    for (unsigned int p = 0; p < kPlayers; ++p)
        gFollowerLists[p]->~FollowerList();
    for (unsigned int r = 0; r < 2; ++r)
        gGameClientLists[r]->~TArrayList<CGameClient *>();
}

void original(void *p, autotest::Capture &out)
{
    side(*static_cast<const Case *>(p), false, out);
}

void recovered(void *p, autotest::Capture &out)
{
    side(*static_cast<const Case *>(p), true, out);
}

// ---------------------------------------------------------------- case table

Case makeCase(bool enabled, unsigned int clients, unsigned int nullMask,
              unsigned int sharedMask, unsigned int f0, unsigned int f1, unsigned int f2,
              unsigned int growBy, unsigned int mutate, float px, float py, float pz,
              float dx, float dy, float dz)
{
    Case c;
    c.nullResource = false;
    c.enabled = enabled;
    c.clients = static_cast<unsigned char>(clients);
    c.nullMask = static_cast<unsigned char>(nullMask);
    c.sharedMask = static_cast<unsigned char>(sharedMask);
    c.followers[0] = static_cast<unsigned char>(f0);
    c.followers[1] = static_cast<unsigned char>(f1);
    c.followers[2] = static_cast<unsigned char>(f2);
    c.growBy = static_cast<unsigned char>(growBy);
    c.mutate = static_cast<unsigned char>(mutate);
    c.p[0] = px;
    c.p[1] = py;
    c.p[2] = pz;
    c.d[0] = dx;
    c.d[1] = dy;
    c.d[2] = dz;
    return c;
}

const float kPool[13] = {
    0.0f,
    -0.0f,
    1.0f,
    -1.0f,
    0.5f,
    -0.25f,
    std::numeric_limits<float>::quiet_NaN(),
    std::numeric_limits<float>::infinity(),
    -std::numeric_limits<float>::infinity(),
    1e30f,
    -1e-30f,
    3.4e38f,
    1.0e-45f};

void buildCases(std::vector<Case> &cases)
{
    // Branch and argument cases.
    Case missingLevel = makeCase(true, 1, 0, 0, 2, 0, 0, 2, 0, 1, 2, 3, 4, 5, 6);
    missingLevel.nullResource = true;
    cases.push_back(missingLevel);
    cases.push_back(makeCase(true, 0, 0, 0, 0, 0, 0, 2, 0, 1, 2, 3, 0, 0, 1));
    cases.push_back(makeCase(false, 0, 0, 0, 0, 0, 0, 2, 0, 1, 2, 3, 0, 0, 1));
    cases.push_back(makeCase(true, 1, 1, 0, 0, 0, 0, 2, 0, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 1, 0, 0, 0, 0, 0, 2, 0, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(false, 1, 0, 0, 3, 0, 0, 2, 0, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 1, 0, 0, 6, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0));
    cases.push_back(makeCase(true, 2, 1, 0, 1, 2, 0, 2, 0, 5, -5, 5, -5, 5, -5));
    cases.push_back(makeCase(true, 2, 2, 0, 1, 1, 0, 2, 0, 5, -5, 5, -5, 5, -5));
    cases.push_back(makeCase(true, 2, 3, 0, 2, 2, 2, 2, 0, 7, 7, 7, -7, -7, -7));
    cases.push_back(makeCase(true, 3, 0, 0, 0, 1, 2, 2, 0, 1, 1, 1, 2, 2, 2));
    cases.push_back(makeCase(true, 3, 1, 0, 4, 0, 2, 2, 0, 1, 1, 1, 2, 2, 2));
    cases.push_back(makeCase(true, 3, 5, 0, 1, 3, 2, 3, 0, 1, 1, 1, 2, 2, 2));
    cases.push_back(makeCase(true, 3, 7, 0, 2, 2, 2, 1, 0, 1, 1, 1, 2, 2, 2));
    // Two clients sharing one player: the whole sequence must happen twice.
    cases.push_back(makeCase(true, 2, 0, 1, 2, 1, 0, 2, 0, 9, 8, 7, 6, 5, 4));
    cases.push_back(makeCase(true, 3, 0, 3, 2, 1, 1, 2, 0, 9, 8, 7, 6, 5, 4));
    cases.push_back(makeCase(true, 3, 4, 3, 2, 1, 1, 2, 0, 9, 8, 7, 6, 5, 4));
    // Enabled flag is ignored by activate.
    cases.push_back(makeCase(false, 3, 1, 1, 2, 2, 2, 2, 0, 1, 2, 3, 4, 5, 6));
    // Non-finite and extreme components.
    cases.push_back(makeCase(true, 2, 0, 0, 1, 2, 0, 2, 0, kPool[6], kPool[7], kPool[8],
                             kPool[6], kPool[7], kPool[8]));
    cases.push_back(makeCase(true, 2, 0, 0, 1, 2, 0, 2, 0, kPool[1], kPool[1], kPool[1],
                             kPool[1], kPool[1], kPool[1]));
    cases.push_back(makeCase(true, 2, 0, 0, 1, 2, 0, 2, 0, kPool[11], kPool[12], kPool[10],
                             kPool[9], kPool[9], kPool[9]));
    // Callback mutations: level switching, follower list growth, client append.
    cases.push_back(makeCase(true, 1, 0, 0, 1, 0, 0, 2, kMutSwapInStopPathing, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 1, 0, 0, 1, 0, 0, 2, kMutSwapInSetDirection, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 1, 0, 0, 1, 0, 0, 2, kMutSwapInDropToGround, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 2, 0, 0, 2, 2, 0, 2,
                             kMutSwapInStopPathing | kMutSwapInSetDirection, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 2, 0, 0, 1, 1, 0, 2,
                             kMutSwapInSetDirection | kMutSwapInDropToGround, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 2, 0, 0, 1, 1, 0, 2, kMutSwapEveryCall, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 1, 0, 0, 2, 0, 0, 2, kMutGrowFollowers, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 2, 0, 0, 3, 1, 0, 2, kMutGrowFollowers, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 2, 1, 0, 2, 3, 0, 2,
                             kMutGrowFollowers | kMutSwapInSetDirection, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 3, 0, 0, 2, 2, 2, 2, kMutAppendClient, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 3, 1, 0, 1, 2, 3, 2, kMutAppendClient, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 2, 0, 1, 1, 2, 0, 2,
                             kMutAppendClient | kMutGrowFollowers, 1, 2, 3, 4, 5, 6));
    cases.push_back(makeCase(true, 2, 0, 0, 2, 1, 0, 2,
                             kMutAppendClient | kMutGrowFollowers | kMutSwapInStopPathing |
                                 kMutSwapInSetDirection,
                             kPool[6], 1, 2, 3, kPool[7], 4));
    // TArrayList growth shapes (growBy 1..4) around the client count boundary.
    for (unsigned int g = 1; g <= 4; ++g)
    {
        cases.push_back(makeCase(true, 1, 0, 0, 1, 0, 0, g, 0, 1, 2, 3, 4, 5, 6));
        cases.push_back(makeCase(true, 2, 0, 0, 1, 1, 0, g, 0, 1, 2, 3, 4, 5, 6));
        cases.push_back(makeCase(true, 3, 0, 0, 1, 1, 1, g, 0, 1, 2, 3, 4, 5, 6));
        cases.push_back(makeCase(true, 3, 0, 0, 1, 1, 1, g, kMutAppendClient, 1, 2, 3, 4, 5, 6));
    }

    // Deterministic sweep over the remaining shape combinations.
    for (unsigned int s = 0; s < 96; ++s)
    {
        unsigned int clients = s % 4;
        unsigned int nullMask = 0;
        unsigned int sharedMask = 0;
        if (clients == 3 && (s % 5) == 0)
            nullMask = 1u << (s % 3);
        if (clients == 2 && (s % 4) == 1)
            nullMask = 1u << ((s >> 1) % 2);
        if (clients == 1 && (s % 6) == 5)
            nullMask = 1;
        if (clients >= 2 && (s % 7) == 3)
            sharedMask = (s % 14) == 3 ? 1u : 3u;
        unsigned int fold = (s >> 2) % 3;
        unsigned int f0 = fold == 0 ? 0 : (fold == 1 ? 1 : (s % kMaxFollowers));
        unsigned int f1 = ((s >> 3) % 3 == 0) ? 0 : ((s >> 3) % 4);
        unsigned int f2 = ((s >> 4) % 2 == 0) ? 0 : ((s >> 5) % kMaxFollowers);
        unsigned int growBy = 1 + (s % 4);
        unsigned int mutate = (unsigned int)(s % 6);
        if (s % 11 == 0)
            mutate |= kMutSwapInSetDirection;
        if (s % 13 == 0)
            mutate |= kMutGrowFollowers;
        if (s % 17 == 0)
            mutate |= kMutAppendClient;
        if (s % 19 == 0)
            mutate |= kMutSwapInDropToGround;
        if (s % 23 == 0)
            mutate |= kMutSwapEveryCall;
        bool enabled = (s % 3) != 0;
        cases.push_back(makeCase(enabled, clients, nullMask, sharedMask, f0, f1, f2,
                                 growBy, mutate, kPool[s % 13], kPool[(s / 13) % 13],
                                 kPool[(s / 5) % 13], kPool[(s / 7) % 13],
                                 kPool[(s / 11) % 13], kPool[(s / 3) % 13]));
    }
}

void describe(const Case &c, char *buffer, size_t size)
{
    std::snprintf(buffer, size,                  "enabled=%d clients=%u null=%u shared=%u fol=%u/%u/%u growBy=%u "
                  "mutate=%u p=(%a,%a,%a) d=(%a,%a,%a)",
                  c.enabled ? 1 : 0, (unsigned int)c.clients, (unsigned int)c.nullMask,
                  (unsigned int)c.sharedMask, (unsigned int)c.followers[0],
                  (unsigned int)c.followers[1], (unsigned int)c.followers[2],
                  (unsigned int)c.growBy, (unsigned int)c.mutate, (double)c.p[0],
                  (double)c.p[1], (double)c.p[2], (double)c.d[0], (double)c.d[1],
                  (double)c.d[2]);
}

bool sameTraceObservation(const autotest::Outcome& a, const autotest::Outcome& b)
{
    return a.reportValid && b.reportValid &&
           !autotest::incomplete(a) && !autotest::incomplete(b) &&
           WIFEXITED(a.status) && WEXITSTATUS(a.status) == 0 &&
           WIFEXITED(b.status) && WEXITSTATUS(b.status) == 0 &&
           a.capture.length == b.capture.length &&
           a.capture.length < autotest::Capture::kSize &&
           std::memcmp(a.capture.data, b.capture.data, a.capture.length) == 0;
}

int run(const tlhybrid_host *host)
{
    std::vector<Case> cases;
    buildCases(cases);
    host->log("    teleport cases: %lu\n", (unsigned long)cases.size());
    int failures = 0;
    for (size_t i = 0; i < cases.size(); ++i)
    {
        autotest::Outcome a, b;
        autotest::runChild(original, &cases[i], a);
        autotest::runChild(recovered, &cases[i], b);
        bool ok = sameTraceObservation(a, b);
        if (!ok)
        {
            char text[512];
            describe(cases[i], text, sizeof(text));
            host->log("    teleport case %lu: %s\n", (unsigned long)i, text);
            host->log("    statuses %d/%d bytes %lu/%lu issues %u/%u\n", a.status, b.status,
                      (unsigned long)a.capture.length, (unsigned long)b.capture.length,
                      a.capture.issue, b.capture.issue);
            if (WIFEXITED(a.status) && WIFEXITED(b.status) &&
                a.capture.length == b.capture.length &&
                a.capture.length < autotest::Capture::kSize)
            {
                for (unsigned long k = 0; k + 4 <= a.capture.length; k += 4)
                {
                    unsigned int x, y;
                    std::memcpy(&x, a.capture.data + k, 4);
                    std::memcpy(&y, b.capture.data + k, 4);
                    if (x != y)
                    {
                        host->log("    first difference at byte %lu: %u vs %u\n", k, x, y);
                        break;
                    }
                }
            }
        }
        TL_CHECK(failures, ok);
    }
    return failures;
}

} // namespace

TL_TEST(teleport_activate_differential)
{
    return run(host);
}
