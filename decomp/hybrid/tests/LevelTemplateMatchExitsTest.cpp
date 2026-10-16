// Differential mutation oracle for CLevelTemplateData::matchExits, 0x972e90.
// Prepared from tu-pipbn9ai. Owning objects have real C++ lifetimes.
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <new>
#include <fenv.h>
#include <OgreVector3.h>
#define private public
#include "LevelTemplateData.h"
#undef private
#include "AutoTest.h"

TL_ORIGINAL(void, matchOwnerConstruct, (void*, const wchar_t*), "_ZN18CLevelTemplateDataC1EPKw")
TL_ORIGINAL(void, matchOwnerDestroy, (void*), "_ZN18CLevelTemplateDataD1Ev")
TL_ORIGINAL(void, originalMatchExits, (CLevelTemplateData*, CChunkInstance*, std::vector<CChunkInstance*>&), "_ZN18CLevelTemplateData10matchExitsEP14CChunkInstanceRSt6vectorIS1_SaIS1_EE")
extern "C" void candidateMatchExits(CLevelTemplateData*, CChunkInstance*, std::vector<CChunkInstance*>&) __asm__("_ZN18CLevelTemplateData10matchExitsEP14CChunkInstanceRSt6vectorIS1_SaIS1_EE");

namespace level_template_match_exits_fixture {
typedef char OwnerABI[sizeof(CLevelTemplateData) == 0x778 ? 1 : -1];
struct Case { unsigned index; };

float bits(unsigned value)
{
    float result;
    std::memcpy(&result, &value, sizeof(result));
    return result;
}

unsigned next(unsigned& seed)
{
    seed = seed * 1664525u + 1013904223u;
    return seed;
}

float coordinate(unsigned& seed)
{
    return static_cast<float>(static_cast<int>(next(seed) % 81u) - 40) * 0.25f;
}

void initialize(CChunkInstance& instance, unsigned id, unsigned capacity)
{
    instance.m_chunkTypeIndex = static_cast<int>(id);
    instance.m_x = instance.m_y = instance.m_z = 0.0f;
    instance.m_name = L"match exit instance \u03a9";
    instance.m_name += static_cast<wchar_t>(L'A' + id);
    if (capacity == 2) instance.m_usedExits.reserve(128);
    if (capacity == 3) instance.m_usedExits.reserve(3);
    if (capacity != 0) {
        instance.m_usedExits.push_back(7);
        instance.m_usedExits.push_back(-1);
    }
}

void add(CChunkType* type, float x, float y, float z, unsigned count = 1)
{
    for (unsigned i = 0; i < count; ++i)
        type->m_exits.add(Ogre::Vector3(x, y, z));
}

void captureInstance(autotest::Capture& out, const CChunkInstance& instance)
{
    out.add(&instance.m_chunkTypeIndex, sizeof(instance.m_chunkTypeIndex));
    out.add(&instance.m_x, 12);
    out.addText(instance.m_name);
    unsigned count = instance.m_usedExits.size();
    out.add(&count, sizeof(count));
    for (unsigned i = 0; i < count; ++i)
        out.add(&instance.m_usedExits[i], sizeof(int));
}

// Returns 1/2 for independently specified multiplicity/self-alias expectations.
unsigned setup(unsigned index, CLevelTemplateData* owner, CChunkType** types,
               CChunkInstance* objects, std::vector<CChunkInstance*>& peers)
{
    CChunkInstance& current = objects[0];
    CChunkInstance& first = objects[1];
    CChunkInstance& second = objects[2];
    if (index < 8) {
        if (index != 0) add(types[0], 0, 0, 2);
        if (index != 1) peers.push_back(&first);
        if (index != 2) add(types[1], index == 4 ? 20.0f : 0.0f, 0, 2);
        if (index == 3) first.m_x = 50;
        if (index == 5) first.m_y = 2001;
        if (index == 6) first.m_z = 30;
        if (index == 7) { peers.clear(); peers.push_back(&current); }
    } else if (index < 24) {
        // Offset the peer exit further outward so omitting the 1.5 shift fails.
        const float exits[8][2] = {{0,6},{0,-2},{4,2},{-4,2},{2,4},{-2,0},{0,2},{0,0}};
        unsigned direction = (index - 8) % 8;
        float x = exits[direction][0], z = exits[direction][1];
        if (index >= 16 && direction >= 4 && direction < 6)
            x = ::nextafterf(x, x > 0 ? HUGE_VALF : -HUGE_VALF);
        add(types[0], x, 0, z);
        // Explicit expected shifts for the four cardinal cases only.
        float shiftedX = x, shiftedZ = z;
        float extraX = 0, extraZ = 0;
        if (direction == 0) { shiftedZ += 1.5f; extraZ = 1.5f; }
        if (direction == 1 || direction == 7) { shiftedZ -= 1.5f; extraZ = -1.5f; }
        if (direction == 2) { shiftedX += 1.5f; extraX = 1.5f; }
        if (direction == 3) { shiftedX -= 1.5f; extraX = -1.5f; }
        if (direction == 4) { extraX = -1.25f; extraZ = -1.25f; }
        if (direction == 5) { extraX = 1.25f; extraZ = 1.25f; }
        owner->m_chunkWidthBasis = 4;
        first.m_x = shiftedX; first.m_z = shiftedZ - 2;
        types[1]->m_height = 9;
        add(types[1], extraX, 0, 2 + extraZ);
        peers.push_back(&first);
    } else if (index < 36) {
        add(types[0], 0, 0, 2, 2);
        add(types[1], 0, 0, 2, 3);
        add(types[2], 0, 0, 2, 2);
        peers.push_back(&first); peers.push_back(&second); peers.push_back(&first);
        return 1;
    } else if (index < 48) {
        add(types[0], 0, 0, 2); add(types[0], 1, 0, 2);
        peers.push_back(&current);
        return 2;
    } else if (index < 66) {
        unsigned face = (index - 48) / 3, nudge = (index - 48) % 3;
        float pitch = owner->m_chunkWidthBasis * owner->m_tileBasis - 0.1f;
        float boundary = 0;
        switch (face) {
            case 0: boundary = 0.5f * pitch; break;
            case 1: boundary = -(0.5f * pitch + 3.0f * pitch); break;
            case 2: boundary = 1000; break;
            case 3: boundary = -1000; break;
            case 4: boundary = 2; break;
            default: boundary = 2 - (4.0f * owner->m_chunkHeightBasis * owner->m_tileBasis - 0.1f); break;
        }
        if (nudge) boundary = ::nextafterf(boundary, nudge == 1 ? -HUGE_VALF : HUGE_VALF);
        if (face < 2) first.m_x = boundary;
        else if (face < 4) first.m_y = boundary;
        else first.m_z = boundary;
        types[1]->m_height = 11; // Z containment uses width, not height.
        add(types[0], 0, 0, 2);
        add(types[1], -first.m_x, -first.m_y, 2 - first.m_z);
        peers.push_back(&first);
    } else if (index < 84) {
        unsigned axis = (index - 66) / 6, variant = (index - 66) % 6;
        float distance = 2;
        if (variant % 3) distance = ::nextafterf(distance, variant % 3 == 1 ? 0.0f : HUGE_VALF);
        if (variant >= 3) distance = -distance;
        // World candidate point is zero on every axis; preserve one-ULP nudges.
        current.m_z = -2;
        first.m_z = -4;
        add(types[0], 0, 0, 2);
        add(types[1], axis == 0 ? distance : 0, axis == 1 ? distance : 0, 4);
        if (axis == 2) {
            first.m_z = -distance;
            types[1]->m_exits.clear();
            add(types[1], 0, 0, 2 * distance);
            if (distance < 0) { first.m_z = distance; types[1]->m_exits.clear(); add(types[1], 0, 0, 0); }
        }
        peers.push_back(&first);
    } else if (index < 96) {
        add(types[0], 0, 0, 2);
        add(types[1], 0, 0, 2);
        second.m_x = 40;
        add(types[2], -40, 0, 2);
        switch ((index - 84) % 4) {
            case 0: peers.push_back(&second); peers.push_back(&first); break;
            case 1: peers.push_back(&first); peers.push_back(&second); peers.push_back(&first); break;
            case 2: second.m_x = 0; types[2]->m_exits.clear(); peers.push_back(&second); peers.push_back(&first); break;
            default: peers.push_back(&first); peers.push_back(&current); peers.push_back(&first); break;
        }
    } else if (index < 144) {
        const unsigned special[] = {0x7fc01234u,0x7f800000u,0xff800000u,0x80000000u,0x7f7fffffu,0x00000001u};
        float value = bits(special[(index - 96) / 8]);
        add(types[0], 0, 0, 2); add(types[1], 0, 0, 2);
        peers.push_back(&first);
        switch ((index - 96) % 8) {
            case 0: current.m_x = value; break;
            case 1: current.m_y = value; break;
            case 2: current.m_z = value; break;
            case 3: first.m_x = value; break;
            case 4: first.m_y = value; break;
            case 5: first.m_z = value; break;
            case 6: owner->m_tileBasis = value; break;
            default: types[1]->m_exits[0].x = value; break;
        }
    } else if (index < 160) {
        const int typeIndex[] = {-1,0x7fffffff,10,1};
        for (unsigned i = 0; i < 4; ++i) add(types[i], 0, 0, 2, i + 1);
        current.m_chunkTypeIndex = typeIndex[(index - 144) % 4];
        first.m_chunkTypeIndex = typeIndex[(index - 144) / 4];
        peers.push_back(&first);
    } else if (index < 192) {
        const float basis[] = {0.0f,-0.0f,0.1f,0.5f,1.0f,2.0f,-1.0f,6.5f};
        unsigned variant = index - 160;
        owner->m_tileBasis = basis[variant % 8];
        owner->m_chunkWidthBasis = variant < 16 ? 2.0f : -2.0f;
        owner->m_chunkHeightBasis = variant % 4 == 0 ? -2.0f : 2.0f;
        types[0]->m_height = static_cast<int>(variant / 8) - 1;
        types[1]->m_width = static_cast<int>(variant / 8) - 1;
        add(types[0], 0, 0, 0); add(types[1], 0, 0, 0);
        add(types[1], 0.25f, 0.25f, 0.25f);
        peers.push_back(&first); peers.push_back(&current);
    } else {
        unsigned seed = index * 7919u + 17u;
        const int dimensions[] = {-2,0,1,2,4,7};
        const float basis[] = {0.0f,-0.0f,0.1f,0.5f,1.0f,2.0f,-1.0f,6.5f};
        owner->m_tileBasis = basis[(index / 32) % 8];
        owner->m_chunkWidthBasis = basis[(index / 7) % 8];
        owner->m_chunkHeightBasis = basis[(index / 13) % 8];
        for (unsigned i = 0; i < 4; ++i) {
            types[i]->m_width = dimensions[next(seed) % 6];
            types[i]->m_height = dimensions[next(seed) % 6];
            unsigned count = next(seed) % 5;
            for (unsigned j = 0; j < count; ++j) {
                float x = coordinate(seed), y = coordinate(seed), z = coordinate(seed);
                add(types[i], x, y, z);
            }
            objects[i].m_x = coordinate(seed);
            objects[i].m_y = coordinate(seed);
            objects[i].m_z = coordinate(seed);
        }
        unsigned count = next(seed) % 5;
        for (unsigned i = 0; i < count; ++i) peers.push_back(&objects[next(seed) % 4]);
        unsigned mode = index % 32;
        if (mode == 0) current.m_chunkTypeIndex = -1;
        if (mode == 1) first.m_chunkTypeIndex = 0x7fffffff;
        if (mode == 2) { first.m_x = current.m_x; first.m_y = current.m_y; first.m_z = current.m_z; }
        if (mode == 3) { peers.push_back(&first); peers.push_back(&first); }
        if (mode == 4) peers.push_back(&current);
        if (mode >= 24) {
            const unsigned special[] = {0x7fc01234u,0x7f800000u,0xff800000u,0x80000000u};
            float value = bits(special[(index / 32) % 4]);
            switch (mode) {
                case 24: current.m_x = value; break;
                case 25: current.m_y = value; break;
                case 26: current.m_z = value; break;
                case 27: first.m_x = value; break;
                case 28: first.m_y = value; break;
                case 29: first.m_z = value; break;
                case 30: if (types[0]->m_exits.size()) types[0]->m_exits[0].x = value; break;
                default: if (types[1]->m_exits.size()) types[1]->m_exits[0].z = value; break;
            }
        }
    }
    return 0;
}

bool appended(const std::vector<int>& value, unsigned prefix, const int* suffix, unsigned count)
{
    if (value.size() != prefix + count) return false;
    for (unsigned i = 0; i < count; ++i) if (value[prefix + i] != suffix[i]) return false;
    return true;
}

void side(Case& c, bool ours, autotest::Capture& out)
{
    union Storage { long double align; unsigned char bytes[0x778]; } storage;
    std::memset(storage.bytes, 0xa5, sizeof(storage.bytes));
    matchOwnerConstruct(storage.bytes, NULL);
    CLevelTemplateData* owner = reinterpret_cast<CLevelTemplateData*>(storage.bytes);
    CChunkType* types[4];
    for (unsigned i = 0; i < 4; ++i) {
        types[i] = new CChunkType;
        types[i]->m_entranceChunk = i == 0; types[i]->m_exitChunk = i == 3;
        types[i]->m_registeredWithRandomizers = false; types[i]->m_mustPlace = false;
        types[i]->m_width = 4; types[i]->m_height = 2; types[i]->m_maxAppearance = 3;
        types[i]->m_folder = L"match/fixture"; types[i]->m_name = L"type";
        types[i]->m_inclusiveFiles.add(L"piece.layout");
        owner->m_chunkTypes.add(types[i]);
    }
    owner->m_tileBasis = 1; owner->m_chunkWidthBasis = 2; owner->m_chunkHeightBasis = 2;
    CChunkInstance objects[4];
    for (unsigned i = 0; i < 4; ++i) initialize(objects[i], i, c.index % 4);
    std::vector<CChunkInstance*> peers;
    unsigned oracle = setup(c.index, owner, types, objects, peers);
    // Seed already matched vectors with a real prior original call on both sides.
    if (c.index >= 24 && c.index < 48 && c.index % 12 >= 8)
        originalMatchExits(owner, &objects[0], peers);
    std::vector<int> prefixes[4];
    unsigned char scalarsBefore[4][16];
    std::wstring namesBefore[4];
    for (unsigned i = 0; i < 4; ++i) {
        prefixes[i] = objects[i].m_usedExits;
        std::memcpy(scalarsBefore[i], &objects[i].m_chunkTypeIndex, 4);
        std::memcpy(scalarsBefore[i] + 4, &objects[i].m_x, 12);
        namesBefore[i] = objects[i].m_name;
    }
    std::vector<CChunkInstance*> peersBefore(peers);
    unsigned char ownerBefore[sizeof(storage.bytes)];
    std::memcpy(ownerBefore, storage.bytes, sizeof(ownerBefore));
    typedef void (*Function)(CLevelTemplateData*, CChunkInstance*, std::vector<CChunkInstance*>&);
    Function fn = ours ? candidateMatchExits : originalMatchExits;
    feclearexcept(FE_ALL_EXCEPT);
    if (!autotest::beginInvocation(out, fn)) { matchOwnerDestroy(owner); return; }
    fn(owner, &objects[0], peers);
    out.callCompleted = 1;
    int exceptions = fetestexcept(FE_ALL_EXCEPT);
    out.add(&exceptions, sizeof(exceptions));
    unsigned errors = std::memcmp(ownerBefore, storage.bytes, sizeof(ownerBefore)) != 0;
    if (peers != peersBefore) ++errors;
    for (unsigned i = 0; i < 4; ++i) {
        if (std::memcmp(scalarsBefore[i], &objects[i].m_chunkTypeIndex, 4) ||
            std::memcmp(scalarsBefore[i] + 4, &objects[i].m_x, 12) || namesBefore[i] != objects[i].m_name) ++errors;
        if (objects[i].m_usedExits.size() < prefixes[i].size()) ++errors;
        else for (unsigned j = 0; j < prefixes[i].size(); ++j)
            if (objects[i].m_usedExits[j] != prefixes[i][j]) ++errors;
        captureInstance(out, objects[i]);
    }
    if (oracle == 1) {
        const int candidateSuffix[] = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
        const int firstSuffix[] = {0,1,2,0,1,2,0,1,2,0,1,2};
        const int secondSuffix[] = {0,1,0,1};
        if (!appended(objects[0].m_usedExits, prefixes[0].size(), candidateSuffix, 16) ||
            !appended(objects[1].m_usedExits, prefixes[1].size(), firstSuffix, 12) ||
            !appended(objects[2].m_usedExits, prefixes[2].size(), secondSuffix, 4) ||
            objects[3].m_usedExits != prefixes[3]) ++errors;
    } else if (oracle == 2) {
        const int suffix[] = {0,0,1,0,1,1};
        if (!appended(objects[0].m_usedExits, prefixes[0].size(), suffix, 6)) ++errors;
        for (unsigned i = 1; i < 4; ++i) if (objects[i].m_usedExits != prefixes[i]) ++errors;
    }
    for (unsigned i = 0; i < 4; ++i) {
        out.add(&types[i]->m_entranceChunk, 16);
        out.addText(types[i]->m_folder); out.addText(types[i]->m_name);
        unsigned count = types[i]->m_inclusiveFiles.size(); out.add(&count, sizeof(count));
        for (unsigned j = 0; j < count; ++j) out.addText(types[i]->m_inclusiveFiles[j]);
        count = types[i]->m_exits.size(); out.add(&count, sizeof(count));
        for (unsigned j = 0; j < count; ++j) out.add(&types[i]->m_exits[j], 12);
    }
    unsigned count = peers.size(); out.add(&count, sizeof(count));
    for (unsigned i = 0; i < count; ++i) {
        unsigned id = 4;
        for (unsigned j = 0; j < 4; ++j) if (peers[i] == &objects[j]) id = j;
        out.add(&id, sizeof(id));
    }
    out.add(&errors, sizeof(errors));
    // Semantic differences remain complete comparison reports, including mutants.
    matchOwnerDestroy(owner);
}

void original(void* data, autotest::Capture& out) { side(*static_cast<Case*>(data), false, out); }
void recovered(void* data, autotest::Capture& out) { side(*static_cast<Case*>(data), true, out); }
}

TL_TEST(level_template_match_exits)
{
    using namespace level_template_match_exits_fixture;
    uint64_t address = static_cast<uint64_t>(reinterpret_cast<uintptr_t>(originalMatchExits));
    autotest::Coverage coverage("level_template_match_exits", address);
    for (unsigned i = 0; i < 1280; ++i) {
        Case c = { i };
        autotest::Outcome a, b;
        autotest::runChild(original, &c, a);
        autotest::runChild(recovered, &c, b);
        unsigned errorsA=1, errorsB=1;
        if (a.capture.length >= 4) std::memcpy(&errorsA, a.capture.data+a.capture.length-4, 4);
        if (b.capture.length >= 4) std::memcpy(&errorsB, b.capture.data+b.capture.length-4, 4);
        if (coverage.observe(host, a, b) || errorsA || errorsB) {
            host->log("    matchExits case %u status %d/%d issue %u/%u bytes %lu/%lu\n", i,
                      a.status, b.status, a.capture.issue, b.capture.issue,
                      (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            for (unsigned j = 0; j < a.capture.length && j < b.capture.length; ++j)
                if (a.capture.data[j] != b.capture.data[j]) {
                    host->log("    first byte %u: %u/%u\n", j,
                              (unsigned char)a.capture.data[j], (unsigned char)b.capture.data[j]);
                    break;
                }
            coverage.report(host);
            return 1;
        }
    }
    coverage.report(host);
    return 0;
}
