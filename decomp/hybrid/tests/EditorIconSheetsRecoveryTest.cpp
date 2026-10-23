#include <Ogre.h>
#include <cstring>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/NativeEditorControls.h"
#include "tests/GameClientOwnedNative.h"
#include "tests/GameClientUiOwner.h"

TL_ORIGINAL(const wchar_t*, iconSheetsOld, (), "_Z19EditorGetIconSheetsv")
extern "C" const wchar_t* iconSheetsNew() __asm__("_Z19EditorGetIconSheetsv");
TL_FUNCTION(iconSheetsClient, "_ZN7CEditor13getGameClientEv")
extern wchar_t sEditorString[1000];
namespace {
struct Case { unsigned seed, mode, guard; bool negative; };
CEditor* editors[2];
iEditorResourceManager* resources;
CGameClient* client;
CGameUI* ui;
autotest::Capture* output;
const Case* input;
unsigned calls;
void number(unsigned n) { output->add(&n, 4); }
CGameClient* getClient(CEditor* editor)
{
    number(101); number(editor == editors[0] ? 1 : editor == editors[1] ? 2 : 99);
    ++calls;
    if (input->mode == 1 && calls == 1) return NULL;
    if ((input->mode == 2 && calls == 2) || (input->mode == 5 && calls == 1)) client->m_pGameUI = NULL;
    if (input->mode == 3 && calls == 1) gEditor = editors[1];
    if (input->mode == 4 && calls == 3) ui->m_itemIconFiles.add(L"late,icon-Ж");
    return client;
}
void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw); input = &c; output = &out; calls = 0;
    gEditor = editors[0];
    for (unsigned i = 0; i < 2; ++i) { editors[i]->m_bDisabled = false; editors[i]->m_pEditorResourceManager = resources; }
    editors[0]->m_bDisabled = (c.guard & 1) != 0;
    if (c.guard & 2) editors[0]->m_pEditorResourceManager = NULL;
    client->m_pGameUI = ui;
    ui->m_itemIconFiles.clear();
    const unsigned counts[] = {0, 1, 2, 5, 24, 28};
    unsigned count = counts[c.seed % 6];
    const wchar_t* names[] = {L"", L"a", L"folder/icon.imageset", L"comma,name", L"Ж中\U0001f642", L"duplicate"};
    for (unsigned i = 0; i < count; ++i) {
        std::wstring name = names[(i + c.seed) % 6];
        if (i == 0 && c.seed >= 6) {
            const unsigned sizes[] = {995, 997, 998, 999, 1000, 1100};
            name = std::wstring(sizes[c.seed % 6], L'x');
        }
        if (i == 1 && c.seed % 3 == 0) name.assign(L"ab\0cd", 5);
        ui->m_itemIconFiles.add(name);
    }
    for (unsigned i = 0; i < 1000; ++i) sEditorString[i] = wchar_t(0x400 + i % 31);
    detour::Set patches; TL_REDIRECT(patches, iconSheetsClient, &getClient);
    if (patches.failed()) _exit(41);
    typedef const wchar_t* (*Function)(); Function function = ours ? iconSheetsNew : iconSheetsOld;
    if (!autotest::beginInvocation(out, function)) return;
    const wchar_t* result = function(); out.callCompleted = 1;
    if (!result) { out.issue = autotest::Capture::InvalidReport; return; }
    if (ours && c.negative) sEditorString[0] ^= 1;
    number(calls); number(gEditor == editors[0] ? 1 : 2); number(client->m_pGameUI == ui);
    number(result == sEditorString); out.addText(std::wstring(result));
    out.add(sEditorString, sizeof(sEditorString));
    number(ui->m_itemIconFiles.size());
    for (unsigned i = 0; i < ui->m_itemIconFiles.size(); ++i) out.addText(ui->m_itemIconFiles[i]);
}
void original(void* p, autotest::Capture& o) { side(p, o, false); }
void recovered(void* p, autotest::Capture& o) { side(p, o, true); }
int worker(const tlhybrid_host* host)
{
    tlheadless::Environment environment; environment.loadGameSkin();
    nativegame::Services native; if (!native.ready()) return 1;
    nativeeditor::Controls editor(native); menugui::Audio audio(native.master);
    menugui::OwnedClient owner(*native.settings, native.master, *native.master->m_pSoundManager);
    client = owner.client;
    gameclient_fixture::UiOwner uiOwner(*native.settings, *client, owner.camera->m_cameras[0],
        owner.scenes[0], owner.scenes[1], owner.scenes[2], owner.resources);
    ui = uiOwner.ui;
    editors[0] = editor.editor; resources = editors[0]->m_pEditorResourceManager;
    editors[1] = static_cast<CEditor*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEditor), 0, 0, 0));
    {
        detour::Set setup;
        TL_REDIRECT(setup, nativeeditor::createDirectory, &nativeeditor::directory);
        TL_REDIRECT(setup, nativeeditor::copyFile, &nativeeditor::copy);
        if (setup.failed()) return 1;
        nativeeditor::editorCtor(editors[1]);
    }
    autotest::Coverage coverage("editor_icon_sheets_recovery", 0x733aa0);
    for (unsigned guard = 0; guard < 4; ++guard) for (unsigned mode = 0; mode < 6; ++mode)
        for (unsigned seed = 0; seed < 18; ++seed) {
            Case c = {seed, mode, guard, false}; autotest::Outcome a, b;
            autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
            if (coverage.observe(host, a, b)) {
                host->log("    icons seed%u mode%u guard%u status%d/%d issue%u/%u bytes%lu/%lu\n", seed, mode, guard, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue, (unsigned long)a.capture.length, (unsigned long)b.capture.length);
                coverage.report(host); return 1;
            }
        }
    coverage.report(host);
    Case c = {11, 0, 0, true}; autotest::Outcome a, b;
    autotest::runChild(original, &c, a); autotest::runChild(recovered, &c, b);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    host->log("    editor icons negative detected %u\n", unsigned(detected));
    gEditor = editors[0];
    return !detected || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus || autotest::incomplete(a) || autotest::incomplete(b);
}
}
TL_TEST(editor_icon_sheets_recovery) { return systems_fixture::isolated(worker, host); }
