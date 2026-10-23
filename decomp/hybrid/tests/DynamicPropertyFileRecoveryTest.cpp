// Native differential coverage for CDynamicPropertyFile::saveSettings and
// loadSettings on real objects, real files and real CFileReader/UTF conversion.
#include "AutoTest.h"
#include "SystemsFixtureWorker.h"
#include <OgreLogManager.h>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <new>
#include <string>
#include <sys/stat.h>
#include <vector>
#define private public
#include "DynamicPropertyFile.h"
#undef private

TL_ORIGINAL(void, dpfCtor, (CDynamicPropertyFile*, std::wstring, std::wstring, std::wstring), "_ZN20CDynamicPropertyFileC1ESbIwSt11char_traitsIwESaIwEES3_S3_")
TL_ORIGINAL(unsigned int, dpfIntIndex, (CDynamicPropertyFile*, const std::wstring&, int, bool), "_ZN20CDynamicPropertyFile19GetIntPropertyIndexERKSbIwSt11char_traitsIwESaIwEEib")
TL_ORIGINAL(unsigned int, dpfFloatIndex, (CDynamicPropertyFile*, const std::wstring&, float, bool), "_ZN20CDynamicPropertyFile21GetFloatPropertyIndexERKSbIwSt11char_traitsIwESaIwEEfb")
TL_ORIGINAL(unsigned int, dpfStringIndex, (CDynamicPropertyFile*, const std::wstring&, std::wstring, bool), "_ZN20CDynamicPropertyFile22GetStringPropertyIndexERKSbIwSt11char_traitsIwESaIwEES3_b")
TL_ORIGINAL(bool, originalSave, (CDynamicPropertyFile*, const std::wstring&, bool), "_ZN20CDynamicPropertyFile12saveSettingsERKSbIwSt11char_traitsIwESaIwEEb")
TL_ORIGINAL(bool, originalLoad, (CDynamicPropertyFile*, const std::wstring&), "_ZN20CDynamicPropertyFile12loadSettingsERKSbIwSt11char_traitsIwESaIwEE")
extern "C" bool recoveredSave(CDynamicPropertyFile*, const std::wstring&, bool) __asm__("_ZN20CDynamicPropertyFile12saveSettingsERKSbIwSt11char_traitsIwESaIwEEb");
extern "C" bool recoveredLoad(CDynamicPropertyFile*, const std::wstring&) __asm__("_ZN20CDynamicPropertyFile12loadSettingsERKSbIwSt11char_traitsIwESaIwEE");

namespace {
struct Case { unsigned index; bool load; bool negative; };
std::string fixtureRoot;
autotest::Capture* output;

std::wstring widen(const std::string& text) { return std::wstring(text.begin(), text.end()); }
void number(long long value) { output->add(&value, sizeof(value)); }
void wide(const std::wstring& text)
{
    number(text.size());
    for (unsigned i = 0; i < text.size(); ++i) number(text[i]);
}

void collect(const std::string& root, std::vector<std::string>& names)
{
    DIR* dir = opendir(root.c_str());
    if (!dir) return;
    while (dirent* entry = readdir(dir))
        if (std::strcmp(entry->d_name, ".") && std::strcmp(entry->d_name, ".."))
            names.push_back(entry->d_name);
    closedir(dir);
    std::sort(names.begin(), names.end());
}

void cleanup(const std::string& root)
{
    std::vector<std::string> names;
    collect(root, names);
    for (unsigned i = 0; i < names.size(); ++i) unlink((root + "/" + names[i]).c_str());
    rmdir(root.c_str());
}

void dumpDirectory(const std::string& root)
{
    std::vector<std::string> names;
    collect(root, names);
    number(names.size());
    for (unsigned i = 0; i < names.size(); ++i) {
        output->add(names[i].c_str(), names[i].size() + 1);
        FILE* file = std::fopen((root + "/" + names[i]).c_str(), "rb");
        std::vector<unsigned char> bytes;
        if (file) {
            int ch;
            while ((ch = std::fgetc(file)) != EOF) bytes.push_back(static_cast<unsigned char>(ch));
            std::fclose(file);
        }
        number(bytes.size());
        if (!bytes.empty()) output->add(&bytes[0], bytes.size());
    }
}

void writeFile(const std::string& path, const std::wstring& text, bool utf16)
{
    FILE* file = std::fopen(path.c_str(), "wb");
    if (!file) return;
    if (utf16) {
        unsigned short bom = 0xfeff;
        std::fwrite(&bom, 2, 1, file);
        for (unsigned i = 0; i < text.size(); ++i) {
            unsigned long c = text[i];
            if (c >= 0x10000) {
                c -= 0x10000;
                unsigned short high = 0xd800 + (c >> 10), low = 0xdc00 + (c & 0x3ff);
                std::fwrite(&high, 2, 1, file); std::fwrite(&low, 2, 1, file);
            } else {
                unsigned short unit = static_cast<unsigned short>(c);
                std::fwrite(&unit, 2, 1, file);
            }
        }
    } else {
        for (unsigned i = 0; i < text.size(); ++i) std::fputc(static_cast<int>(text[i] & 0x7f), file);
    }
    std::fclose(file);
}

std::vector<unsigned> callbackLog;
void callbackA(unsigned property) { callbackLog.push_back(1000 + property); }
void callbackB(unsigned property) { callbackLog.push_back(2000 + property); }

void dumpObject(CDynamicPropertyFile* file)
{
    number(file->m_intValues.size());
    for (unsigned i = 0; i < file->m_intValues.size(); ++i) number(file->m_intValues[i]);
    number(file->m_floatValues.size());
    for (unsigned i = 0; i < file->m_floatValues.size(); ++i) {
        unsigned bits; std::memcpy(&bits, &file->m_floatValues[i], 4); number(bits);
    }
    number(file->m_stringValues.size());
    for (unsigned i = 0; i < file->m_stringValues.size(); ++i) wide(file->m_stringValues[i]);
    number(file->m_intIndices.size()); number(file->m_floatIndices.size()); number(file->m_stringIndices.size());
    number(file->m_nonLocalVariables.size());
    number(file->m_callbacks.size());
    for (unsigned i = 0; i < file->m_callbacks.size(); ++i) {
        number(file->m_callbacks[i].size());
        for (unsigned j = 0; j < file->m_callbacks[i].size(); ++j)
            number(file->m_callbacks[i][j] == &callbackA ? 1 : file->m_callbacks[i][j] == &callbackB ? 2 : 999);
    }
    number(file->m_Unrecovered130[0]);
    number(file->m_lastFileError);
    number(callbackLog.size());
    for (unsigned i = 0; i < callbackLog.size(); ++i) number(callbackLog[i]);
}

// Properties registered in a name order different from their index order, so the
// writer's restart-from-begin search and the reader's name lookup both matter.
void populate(CDynamicPropertyFile* file, unsigned index)
{
    const wchar_t* intNames[] = {L"zeta", L"alpha", L"Mid", L"beta_count", L"\x43c\x438\x440", L"a"};
    const wchar_t* floatNames[] = {L"volume", L"gamma", L"Brightness", L"x", L"\x3c0"};
    const wchar_t* stringNames[] = {L"profile", L"name", L"Path", L"empty", L"emoji"};
    const int ints[] = {0, -1, 2147483647, (int)0x80000000, 42, 7};
    const float floats[] = {0.5f, -3.25f, 1e-7f, 123456.789f, 0.0f};
    const wchar_t* strings[] = {L"hello world", L"\x43c\x438\x440 :colon", L"/tmp/a b/c", L"", L"smile \U0001F600 end"};
    unsigned intCount = index % 7 > 5 ? 6 : index % 7;
    unsigned floatCount = (index / 2) % 6;
    unsigned stringCount = (index / 3) % 6;
    for (unsigned i = 0; i < intCount; ++i)
        dpfIntIndex(file, intNames[(i + index) % 6], ints[(i + index) % 6], ((i + index) % 3) == 0);
    for (unsigned i = 0; i < floatCount; ++i)
        dpfFloatIndex(file, floatNames[(i + index) % 5], floats[(i + index) % 5], ((i + index) % 4) == 1);
    for (unsigned i = 0; i < stringCount; ++i)
        dpfStringIndex(file, stringNames[(i + index) % 5], strings[(i + index) % 5], ((i + index) % 2) == 1);
}

CDynamicPropertyFile* construct(const std::wstring& directory, const std::wstring& name, const std::wstring& secondary)
{
    void* memory = operator new(sizeof(CDynamicPropertyFile));
    std::memset(memory, 0, sizeof(CDynamicPropertyFile));
    CDynamicPropertyFile* file = static_cast<CDynamicPropertyFile*>(memory);
    dpfCtor(file, directory, name, secondary);
    return file;
}

void saveSide(const Case& c, bool ours)
{
    std::string root = fixtureRoot;
    mkdir(root.c_str(), 0700);
    std::wstring directory = widen(root);
    const wchar_t* primaries[] = {L"settings.txt", L"local file.cfg", L"\x43c\x438\x440.txt"};
    const wchar_t* secondaries[] = {L"shared.txt", L"global.cfg"};
    CDynamicPropertyFile* file = construct(directory, primaries[c.index % 3], secondaries[(c.index / 3) % 2]);
    populate(file, c.index);
    // A previous file is overwritten, not appended.
    if (c.index % 5 == 2) writeFile(root + "/settings.txt", L"stale :1\n", false);
    std::wstring argument = c.index % 4 == 3 ? std::wstring(L"explicit.txt") : std::wstring();
    bool nonLocal = (c.index / 2) % 2 == 1;
    callbackLog.clear();
    typedef bool (*Call)(CDynamicPropertyFile*, const std::wstring&, bool);
    Call call = ours ? recoveredSave : originalSave;
    if (!autotest::beginInvocation(*output, call)) { cleanup(root); return; }
    bool returned = call(file, argument, nonLocal);
    output->callCompleted = 1;
    if (ours && c.negative) returned = !returned;
    number(returned);
    dumpObject(file);
    dumpDirectory(root);
    cleanup(root);
}

void loadSide(const Case& c, bool ours)
{
    std::string root = fixtureRoot;
    mkdir(root.c_str(), 0700);
    std::wstring directory = widen(root);
    CDynamicPropertyFile* file = construct(directory, L"settings.txt", L"shared.txt");
    populate(file, c.index * 7 + 5);
    // Existing callback rows are kept or trimmed and new rows appended by the resize.
    unsigned rows = c.index % 4;
    file->m_callbacks.resize(rows);
    for (unsigned i = 0; i < rows; ++i) {
        file->m_callbacks[i].push_back(&callbackA);
        if (i % 2) file->m_callbacks[i].push_back(&callbackB);
    }
    const wchar_t* lines[] = {
        L"zeta :12", L"alpha :-7", L"volume :0.75", L"gamma : 2.5", L"profile :player one", L"name :a :b :c",
        L"unknown :5", L"noseparator", L"space split value", L"Path :/tmp/a b/c", L"", L"x :",
        L" :leading", L"Mid :  33", L"Brightness :1e3", L"emoji :smile \U0001F600", L"\x43c\x438\x440 :9",
        L"a :b :", L"a b", L"beta_count :0x10", L"trailing space ", L"empty :", L"\x3c0 :3.14159",
        L"zeta :99", L"two  spaces", L"name : spaced"};
    const unsigned lineCount = sizeof(lines) / sizeof(lines[0]);
    std::wstring text;
    unsigned count = 3 + c.index % 11;
    for (unsigned i = 0; i < count; ++i) {
        text += lines[(i * 5 + c.index * 3) % lineCount];
        text += (c.index % 3 == 1) ? L"\r\n" : L"\n";
    }
    // Exercise the deque's 64-element boundary in both tokenization paths,
    // trailing delimiters, duplicate settings, callback shrinking/growth and
    // a valid file containing only empty lines. These cases remain UTF-16.
    if (c.index >= 72) {
        switch ((c.index - 72) % 8) {
        case 0: text = L"\n\r\n\n"; break;
        case 1:
            text = L"profile";
            for (unsigned i = 0; i < 90; ++i) text += L" :value";
            text += L"\n";
            break;
        case 2:
            text = L"";
            for (unsigned i = 0; i < 100; ++i) text += L"word ";
            text += L"\n";
            break;
        case 3: text = L"alpha :1\nalpha :2\nalpha :3\nalpha :4\n"; break;
        case 4: text = L"singleword\nx :\n :\n : :\n"; break;
        case 5: text = L"volume :0.25\nvolume :0.5\nvolume :0.75\n"; break;
        case 6: text = L"name :\x43c\x438\x440 \U0001F600\nname :last\n"; break;
        case 7:
            text = L"profile :" + std::wstring(1800, L'X') + L"\n";
            for (unsigned i = 0; i < 80; ++i) text += L"unknown :5\n";
            break;
        }
    }
    bool missing = c.index % 9 == 4;
    bool utf16 = c.index % 2 == 0;
    std::wstring argument;
    std::string target = root + "/settings.txt";
    if (c.index % 5 == 3) { argument = L"other name.txt"; target = root + "/other name.txt"; }
    if (!missing) writeFile(target, text, utf16 || c.index % 7 == 1 || c.index >= 72);
    // Failure must reset an already-loaded object, not merely return its
    // constructor's false flag.
    file->m_loaded = c.index % 3 != 0;
    callbackLog.clear();
    typedef bool (*Call)(CDynamicPropertyFile*, const std::wstring&);
    Call call = ours ? recoveredLoad : originalLoad;
    if (!autotest::beginInvocation(*output, call)) { cleanup(root); return; }
    bool returned = call(file, argument);
    output->callCompleted = 1;
    if (ours && c.negative) file->m_intValues.push_back(1);
    number(returned);
    dumpObject(file);
    cleanup(root);
}

void side(void* raw, autotest::Capture& out, bool ours)
{
    output = &out;
    const Case& c = *static_cast<Case*>(raw);
    if (c.load) loadSide(c, ours); else saveSide(c, ours);
}
void before(void* p, autotest::Capture& out) { side(p, out, false); }
void after(void* p, autotest::Capture& out) { side(p, out, true); }

int worker(const tlhybrid_host* host, bool load)
{
    // CFileReader's native loose-file fallback is valid without a filesystem
    // singleton. Its unsupported-encoding branch does require a real logger;
    // absent that owner, the old seed 3 crashed before returning on both sides.
    Ogre::LogManager logs;
    logs.createLog("dynamic-file-recovery", true, false, true);
    char pattern[] = "/tmp/opencode/otl-dynamic-file-XXXXXX";
    char* created = mkdtemp(pattern);
    if (!created) return 1;
    fixtureRoot = std::string(created) + "/dir";
    autotest::Coverage coverage(load ? "dynamic_file_load" : "dynamic_file_save", load ? 0xc70800 : 0xc6ea60);
    unsigned count = load ? 104 : 48;
    unsigned successful = 0, rejected = 0;
    for (unsigned i = 0; i < count; ++i) {
        Case c = {i, load, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) {
            host->log("    dynamic file seed%u load%d status%d/%d issue%u/%u bytes%lu/%lu\n", i, load, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue, (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            unsigned limit = std::min(a.capture.length, b.capture.length);
            for (unsigned offset = 0; offset < limit; ++offset) {
                if (a.capture.data[offset] != b.capture.data[offset]) {
                    host->log("    first differing byte %u original%u candidate%u\n", offset,
                        static_cast<unsigned char>(a.capture.data[offset]), static_cast<unsigned char>(b.capture.data[offset]));
                    break;
                }
            }
            coverage.report(host); rmdir(created); return 1;
        }
        long long returned = -1;
        if (a.capture.length >= sizeof(returned)) std::memcpy(&returned, a.capture.data, sizeof(returned));
        if (returned == 1) ++successful;
        else if (returned == 0) ++rejected;
        else { rmdir(created); return 1; }
    }
    coverage.report(host);
    host->log("    dynamic file load%d successful%u rejected%u\n", load, successful, rejected);
    Case c = {6, load, true};
    autotest::Outcome a, b;
    autotest::runChild(before, &c, a, 2000, 10000);
    autotest::runChild(after, &c, b, 2000, 10000);
    rmdir(created);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    host->log("    dynamic file negative control load%d detected%d\n", load, detected);
    return !detected || autotest::incomplete(a) || autotest::incomplete(b) || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus;
}
int saveWorker(const tlhybrid_host* host) { return worker(host, false); }
int loadWorker(const tlhybrid_host* host) { return worker(host, true); }
}

TL_TEST(dynamic_file_save_recovery) { return systems_fixture::isolated(saveWorker, host); }
TL_TEST(dynamic_file_load_recovery) { return systems_fixture::isolated(loadWorker, host); }
