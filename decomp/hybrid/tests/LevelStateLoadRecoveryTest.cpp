#include <cstdio>
#include <cstring>
#include <vector>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "LevelState.h"
#include "CharacterSaveState.h"
#include "ItemSaveState.h"
#include "LogicNodeState.h"
#include "FormationNodeSaveAndLoad.h"

TL_ORIGINAL(void, levelLoadOld, (CLevelState*, FILE*, unsigned), "_ZN11CLevelState4loadEP8_IO_FILEj")
TL_ORIGINAL(void, levelLoadCtor, (CLevelState*, int), "_ZN11CLevelStateC1Ei")
TL_ORIGINAL(void, levelLoadDtor, (CLevelState*), "_ZN11CLevelStateD1Ev")
extern "C" void levelLoadNew(CLevelState*, FILE*, unsigned) __asm__("_ZN11CLevelState4loadEP8_IO_FILEj");
TL_FUNCTION(levelCharacterLoad, "_ZN19CCharacterSaveState4loadEP8_IO_FILEj")
TL_FUNCTION(levelItemLoad, "_ZN14CItemSaveState4loadEP8_IO_FILEj")

namespace {
struct Case { unsigned version, seed, shortTail; bool negative; };
autotest::Capture* capture;
CLevelState* current;
const Case* input;
unsigned characterCalls, itemCalls;
void number(unsigned n) { capture->add(&n, sizeof(n)); }
void characterLoad(CCharacterSaveState* state, FILE* file, unsigned version)
{
    unsigned marker = 0;
    fread(&marker, 4, 1, file);
    number(101); number(version); number(marker); number(current->m_lCharacters.size());
    state->m_name = L"character-Ж";
    state->m_value38 = marker;
    state->m_guid50 = 0x123400000000LL + marker;
    state->m_hp = marker * 0.125f;
    if (input->seed % 5 == 2 && characterCalls == 0) {
        CCharacterSaveState* extra = new CCharacterSaveState;
        extra->m_name = L"callback-owned";
        extra->m_value38 = -19;
        extra->m_guid50 = -3;
        extra->m_hp = -1.0f;
        current->m_lCharacters.push_back(extra);
    }
    ++characterCalls;
}
void itemLoad(CItemSaveState* state, FILE* file, unsigned version)
{
    unsigned marker = 0;
    fread(&marker, 4, 1, file);
    number(103); number(version); number(marker); number(current->m_lItems.size());
    state->m_sItemName = L"item-中";
    state->m_iIndex = marker;
    state->m_iStackSize = marker + 7;
    if (input->seed % 7 == 3 && itemCalls == 0) {
        CItemSaveState* extra = new CItemSaveState;
        extra->m_sItemName = L"callback-owned";
        extra->m_iIndex = -23;
        extra->m_iStackSize = -11;
        current->m_lItems.push_back(extra);
    }
    ++itemCalls;
}
void value(FILE* file, unsigned n) { fwrite(&n, 4, 1, file); }
void utf(FILE* file, unsigned seed, bool wideLength = false)
{
    const unsigned short texts[][6] = {
        {0}, {'A'}, {0x416, 0x4e2d}, {'a', 0, 'z'},
        {0xd83d, 0xde42, 'b', 0x20ac}, {'x', 0xd83d, 0xde42, 0x416, 'y'}
    };
    unsigned length = seed % 6;
    if (wideLength) value(file, length);
    else { unsigned short shortLength = length; fwrite(&shortLength, 2, 1, file); }
    fwrite(texts[length], 2, length, file);
}
void logic(FILE* file, unsigned version, unsigned seed)
{
    const wchar_t* names[] = {L"Timeline", L"timeline", L"", L"other"};
    const wchar_t* name = names[seed % 4];
    unsigned short length = wcslen(name);
    fwrite(&length, 2, 1, file);
    for (unsigned i = 0; i < length; ++i) { unsigned short c = name[i]; fwrite(&c, 2, 1, file); }
    unsigned char flags[] = {0x80, 0, 0xff, 1};
    fwrite(flags, 1, 4, file);
    for (unsigned i = 0; i < 4; ++i) value(file, seed * 13 + i);
    unsigned long long guid = 0x123400000000ULL + seed;
    fwrite(&guid, 8, 1, file); ++guid; fwrite(&guid, 8, 1, file);
    if (version > 16) { ++guid; fwrite(&guid, 8, 1, file); }
    else if (version == 16) value(file, seed * 11 + 3);
    float position[] = {float(seed), -0.25f, seed * 0.5f};
    fwrite(position, 12, 1, file);
    unsigned char persistent = seed % 3 == 0 ? 0 : 0x80;
    fwrite(&persistent, 1, 1, file); value(file, seed + 9);
}
void stateView(CLevelState* state)
{
    capture->add(&state->m_iLevelId, 4); capture->add(&state->m_iStateVersion, 4);
    capture->addText(state->m_sLevelName);
    capture->add(&state->m_bUnknownB0, 1); capture->add(&state->m_bUnknownB1, 1);
    number(state->m_iAutomapWidth); number(state->m_iAutomapHeight);
    if (state->m_iAutomapWidth > 0 && state->m_iAutomapHeight > 0)
        capture->add(state->m_pAutomapData, state->m_iAutomapWidth * state->m_iAutomapHeight * 4);
    number(state->m_lCharacters.size()); number(state->m_lCharacters.capacity());
    for (unsigned i = 0; i < state->m_lCharacters.size(); ++i) {
        CCharacterSaveState* s = state->m_lCharacters[i];
        capture->addText(s->m_name); capture->add(&s->m_value38, 4);
        capture->add(&s->m_guid50, 8); capture->add(&s->m_hp, 4);
    }
    number(state->m_lItems.size()); number(state->m_lItems.capacity());
    for (unsigned i = 0; i < state->m_lItems.size(); ++i) {
        CItemSaveState* s = state->m_lItems[i];
        capture->addText(s->m_sItemName); number(s->m_iIndex); number(s->m_iStackSize);
    }
    number(state->m_lLogicStates.size()); number(state->m_lLogicStates.capacity());
    for (unsigned i = 0; i < state->m_lLogicStates.size(); ++i) {
        CLogicNodeState* s = state->m_lLogicStates[i];
        capture->add(reinterpret_cast<char*>(s) + 0x10, 0x18);
        capture->addText(s->m_wstrName);
        capture->add(reinterpret_cast<char*>(s) + 0x30, 0x30);
    }
    number(state->m_lLevelStrings.size()); number(state->m_lLevelStrings.capacity());
    for (unsigned i = 0; i < state->m_lLevelStrings.size(); ++i) capture->addText(state->m_lLevelStrings[i]);
    number(state->m_lFormations.size());
    for (unsigned i = 0; i < state->m_lFormations.size(); ++i) {
        CFormationNodeSaveAndLoad* f = state->m_lFormations[i];
        capture->add(&f->m_bSavePosition, 1); capture->addText(f->m_sFileLoaded);
        capture->add(&f->m_fPositionX, 12);
    }
}
void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    input = &c; capture = &out; characterCalls = itemCalls = 0;
    detour::Set patches;
    TL_REDIRECT(patches, levelCharacterLoad, &characterLoad);
    TL_REDIRECT(patches, levelItemLoad, &itemLoad);
    if (patches.failed()) _exit(41);
    union Storage { long double align; char bytes[sizeof(CLevelState)]; } storage;
    CLevelState* state = reinterpret_cast<CLevelState*>(storage.bytes);
    levelLoadCtor(state, -91); current = state;
    state->m_sLevelName = L"previous level";
    state->m_bUnknownB0 = false; state->m_bUnknownB1 = c.seed % 2;
    state->m_iAutomapWidth = c.shortTail ? 0 : c.seed % 3 == 0 ? 2 : c.seed % 3 == 1 ? -2 : 0;
    state->m_iAutomapHeight = c.seed % 4 == 1 ? -2 : 3;
    int oldCount = state->m_iAutomapWidth * state->m_iAutomapHeight;
    float* oldMap = new float[oldCount > 0 ? oldCount : 1];
    for (int i = 0; i < (oldCount > 0 ? oldCount : 1); ++i) oldMap[i] = -17.0f;
    state->m_pAutomapData = oldMap;
    if (!c.shortTail && c.seed % 2) {
        CCharacterSaveState* ch = new CCharacterSaveState;
        ch->m_name = L"existing character"; ch->m_value38 = -7; ch->m_guid50 = -5; ch->m_hp = -2.0f;
        state->m_lCharacters.push_back(ch);
        CItemSaveState* item = new CItemSaveState;
        item->m_sItemName = L"existing item"; item->m_iIndex = -7; item->m_iStackSize = -3;
        state->m_lItems.push_back(item);
        state->m_lLevelStrings.push_back(L"existing string");
    }
    FILE* file = tmpfile(); if (!file) _exit(42);
    value(file, c.seed * 31 - 17); value(file, 0x3f800000 + c.seed);
    for (int i = 0; i < oldCount; ++i) { unsigned char flag = i % 3 == 0 ? 0 : i % 3 == 1 ? 0x80 : 0xff; fwrite(&flag, 1, 1, file); }
    utf(file, c.seed);
    unsigned char flag = c.seed % 4 == 0 ? 0 : c.seed % 4 == 1 ? 1 : c.seed % 4 == 2 ? 0x80 : 0xff;
    fwrite(&flag, 1, 1, file);
    if (c.version > 21) fwrite(&flag, 1, 1, file);
    int width = c.shortTail ? 0 : c.seed % 4 == 0 ? 0 : c.seed % 4 == 1 ? -2 : 2;
    int height = c.seed % 5 == 0 ? 0 : 3;
    fwrite(&width, 4, 1, file); fwrite(&height, 4, 1, file);
    if (width > 0) for (int i = 0; i < width * height; ++i) value(file, 0x80000000u + c.seed * 0x100 + i);
    unsigned count = c.shortTail ? 0 : c.seed % 4;
    value(file, count); for (unsigned i = 0; i < count; ++i) value(file, c.seed * 13 + i);
    count = c.shortTail ? 0 : c.seed / 2 % 4;
    value(file, count); for (unsigned i = 0; i < count; ++i) value(file, c.seed * 17 + i);
    count = c.shortTail ? 0 : c.seed / 3 % 5;
    value(file, count); for (unsigned i = 0; i < count; ++i) logic(file, c.version, c.seed + i);
    count = c.shortTail ? 0 : c.seed / 2 % 5;
    value(file, count); for (unsigned i = 0; i < count; ++i) utf(file, c.seed + i);
    count = c.shortTail ? 0 : c.seed / 2 % 13;
    if (c.shortTail) fwrite(&count, 1, c.shortTail - 1, file);
    else {
        value(file, count);
        for (unsigned i = 0; i < count; ++i) {
            utf(file, c.seed + i, true);
            float pos[] = {float(i), c.seed * 0.5f, -float(i)}; fwrite(pos, 12, 1, file);
        }
        value(file, 0xdeadbeef);
    }
    rewind(file);
    autotest::invoke(out, ours ? levelLoadNew : levelLoadOld, state, file, c.version);
    if (ours && c.negative) state->m_iLevelId ^= 1;
    stateView(state);
    number(characterCalls); number(itemCalls);
    number(state->m_pAutomapData == oldMap);
    capture->add(oldMap, (oldCount > 0 ? oldCount : 1) * 4);
    long offset = ftell(file); out.add(&offset, sizeof(offset)); number(feof(file)); number(ferror(file));
    unsigned char rest[32]; size_t remain = fread(rest, 1, sizeof(rest), file); number(remain); out.add(rest, remain);
    std::vector<TSafePointer<CRunicCore>*> lives;
    TSafePointer<CLevelState> stateLife; stateLife.setObject(state);
    for (unsigned i = 0; i < state->m_lCharacters.size(); ++i) { TSafePointer<CRunicCore>* p = new TSafePointer<CRunicCore>; p->setObject(state->m_lCharacters[i]); lives.push_back(p); }
    for (unsigned i = 0; i < state->m_lItems.size(); ++i) { TSafePointer<CRunicCore>* p = new TSafePointer<CRunicCore>; p->setObject(state->m_lItems[i]); lives.push_back(p); }
    for (unsigned i = 0; i < state->m_lLogicStates.size(); ++i) { TSafePointer<CRunicCore>* p = new TSafePointer<CRunicCore>; p->setObject(state->m_lLogicStates[i]); lives.push_back(p); }
    for (unsigned i = 0; i < state->m_lFormations.size(); ++i) { TSafePointer<CRunicCore>* p = new TSafePointer<CRunicCore>; p->setObject(state->m_lFormations[i]); lives.push_back(p); }
    bool retained = state->m_pAutomapData == oldMap;
    levelLoadDtor(state);
    if (!retained) delete[] oldMap;
    number(stateLife.getObject() == NULL); if (stateLife.getObject()) out.issue = autotest::Capture::InvalidReport;
    for (unsigned i = 0; i < lives.size(); ++i) { number(lives[i]->getObject() == NULL); if (lives[i]->getObject()) out.issue = autotest::Capture::InvalidReport; delete lives[i]; }
    fclose(file);
}
void original(void* p, autotest::Capture& o) { side(p, o, false); }
void recovered(void* p, autotest::Capture& o) { side(p, o, true); }
}
TL_TEST(level_state_load_recovery)
{
    autotest::Coverage coverage("level_state_load_recovery", 0x970670);
    const unsigned versions[] = {0, 14, 15, 16, 17, 21, 22, 23, 0xffffffffu};
    for (unsigned v = 0; v < 9; ++v) for (unsigned seed = 0; seed < 24; ++seed) {
        Case c = {versions[v], seed, 0, false}; autotest::Outcome a, b;
        autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
        if (coverage.observe(host, a, b)) {
            host->log("    level load version%u seed%u status%d/%d issue%u/%u bytes%lu/%lu\n", c.version, c.seed, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue, (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            for (unsigned i = 0; i < a.capture.length && i < b.capture.length; ++i) if (a.capture.data[i] != b.capture.data[i]) { host->log("    first diff%u %02x/%02x\n", i, a.capture.data[i], b.capture.data[i]); break; }
            coverage.report(host); return 1;
        }
    }
    for (unsigned tail = 1; tail <= 5; ++tail) {
        Case c = {23, 0, tail, false}; autotest::Outcome a, b;
        autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
        if (coverage.observe(host, a, b)) { coverage.report(host); return 1; }
    }
    coverage.report(host);
    Case negative = {14, 11, 0, true}; autotest::Outcome a, b;
    autotest::runChild(original, &negative, a); autotest::runChild(recovered, &negative, b);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    host->log("    level load negative control detected %u\n", unsigned(detected));
    return !detected || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus || autotest::incomplete(a) || autotest::incomplete(b);
}
