#include "AutoTest.h"
#include "SystemsFixtureWorker.h"
#include "FileUtilities.h"
#include <OgreUTFString.h>
#include <algorithm>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <utime.h>
#include <vector>

TL_ORIGINAL(void, originalSetTime, (const std::wstring&, long long, long long, long long), "_ZN10FILESYSTEM11setFileTimeERKSbIwSt11char_traitsIwESaIwEExxx")
TL_ORIGINAL(bool, originalCreateDirectory, (const std::wstring&), "_ZN10FILESYSTEM22CreateAppDataDirectoryERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void recoveredSetTime(const std::wstring&, long long, long long, long long) __asm__("_ZN10FILESYSTEM11setFileTimeERKSbIwSt11char_traitsIwESaIwEExxx");
extern "C" bool recoveredCreateDirectory(const std::wstring&) __asm__("_ZN10FILESYSTEM22CreateAppDataDirectoryERKSbIwSt11char_traitsIwESaIwEE");
namespace LinuxUtils {
extern std::wstring gameHomePath __asm__("_ZN10LinuxUtilsL12gameHomePathE");
}

namespace {
struct Case { unsigned index; bool time; bool negative; };
std::string fixtureRoot;

void touch(const std::string& path)
{
    int fd = open(path.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd >= 0) { write(fd, "fixture", 7); close(fd); }
}

void collect(const std::string& root, const std::string& relative, std::vector<std::string>& result)
{
    std::string path = root + relative;
    DIR* dir = opendir(path.c_str());
    if (!dir) return;
    while (dirent* entry = readdir(dir)) {
        if (!std::strcmp(entry->d_name, ".") || !std::strcmp(entry->d_name, "..")) continue;
        std::string child = relative + "/" + entry->d_name;
        struct stat data;
        if (lstat((root + child).c_str(), &data)) continue;
        result.push_back(child + (S_ISDIR(data.st_mode) ? "/" : ""));
        if (S_ISDIR(data.st_mode)) collect(root, child, result);
    }
    closedir(dir);
}

void cleanup(const std::string& root)
{
    std::vector<std::string> paths;
    collect(root, "", paths);
    std::sort(paths.rbegin(), paths.rend());
    for (unsigned i = 0; i < paths.size(); ++i) {
        std::string path = root + paths[i];
        if (paths[i][paths[i].size() - 1] == '/') rmdir(path.c_str());
        else unlink(path.c_str());
    }
    rmdir(root.c_str());
}

void side(void* raw, autotest::Capture& out, bool ours)
{
    const Case& c = *static_cast<Case*>(raw);
    std::string root = fixtureRoot;
    if (mkdir(root.c_str(), 0700) && errno != EEXIST) {
        out.issue = autotest::Capture::InvalidReport; return;
    }
    if (c.time) {
        const char* names[] = {"data.bin", "spaces here.txt", "\xd0\xbc\xd0\xb8\xd1\x80.dat", "missing.file", "directory"};
        std::string path = root + "/" + names[c.index % 5];
        if (c.index % 5 == 4) mkdir(path.c_str(), 0700);
        else if (c.index % 5 != 3) touch(path);
        struct utimbuf fixed = {946684800, 978307200};
        utime(path.c_str(), &fixed);
        long long times[] = {0, 1, 0xffffffffLL, 0x100000000LL, 0x1122334455667788LL, -1, 132537600000000000LL, 1234567890};
        long long creation = times[c.index % 8];
        long long access = c.index & 1 ? 0 : times[(c.index + 3) % 8];
        long long writeTime = c.index & 2 ? 0 : times[(c.index + 5) % 8];
        std::wstring wide = Ogre::UTFString(path).asWStr();
        typedef void (*Call)(const std::wstring&, long long, long long, long long);
        Call call = ours ? recoveredSetTime : originalSetTime;
        if (!autotest::beginInvocation(out, call)) { cleanup(root); return; }
        call(wide, creation, access, writeTime);
        out.callCompleted = 1;
        struct stat data;
        int error = stat(path.c_str(), &data);
        out.add(&error, sizeof(error));
        if (!error) {
            long long atime = data.st_atime, mtime = data.st_mtime;
            if (ours && c.negative) ++mtime;
            out.add(&atime, sizeof(atime)); out.add(&mtime, sizeof(mtime));
            unsigned mode = data.st_mode;
            out.add(&mode, sizeof(mode));
        }
    } else {
        std::string base = root + "/appdata";
        mkdir(base.c_str(), 0700);
        mkdir((base + "/existing").c_str(), 0700);
        touch(base + "/blocked");
        LinuxUtils::gameHomePath = Ogre::UTFString(base + "/").asWStr();
        const wchar_t* suffixes[] = {L"", L"/", L"/one", L"/one/two", L"/one/two/file.txt", L"/.hidden", L"/one.dir/two", L"/a//b///c", L"/one\\two\\data.dat", L"/spaces here/мир", L"/existing/deep", L"/blocked/deep", L"/.config/leaf", L"/a/./b", L"/a/b.", L"/a/b../c", L"/trailing\\", L"/a/file.ext/x"};
        std::wstring path = Ogre::UTFString(base).asWStr() + suffixes[c.index % 18];
        if (c.index >= 18) std::replace(path.begin(), path.end(), L'/', L'\\');
        typedef bool (*Call)(const std::wstring&);
        Call call = ours ? recoveredCreateDirectory : originalCreateDirectory;
        if (!autotest::beginInvocation(out, call)) { cleanup(root); return; }
        bool returned = call(path);
        out.callCompleted = 1;
        if (ours && c.negative) returned = !returned;
        out.add(&returned, sizeof(returned));
        std::vector<std::string> tree;
        collect(root, "", tree);
        std::sort(tree.begin(), tree.end());
        for (unsigned i = 0; i < tree.size(); ++i) out.add(tree[i].c_str(), tree[i].size() + 1);
    }
    cleanup(root);
}

void before(void* p, autotest::Capture& out) { side(p, out, false); }
void after(void* p, autotest::Capture& out) { side(p, out, true); }
int worker(const tlhybrid_host* host, bool time)
{
    char pattern[] = "/tmp/opencode/otl-file-recovery-XXXXXX";
    char* created = mkdtemp(pattern);
    if (!created) return 1;
    fixtureRoot = created;
    autotest::Coverage coverage(time ? "file_recovery_set_time" : "file_recovery_app_directory", time ? 0xc74490 : 0xc76860);
    unsigned count = time ? 40 : 36;
    for (unsigned i = 0; i < count; ++i) {
        Case c = {i, time, false};
        autotest::Outcome a, b;
        autotest::runChild(before, &c, a, 2000, 10000);
        autotest::runChild(after, &c, b, 2000, 10000);
        if (coverage.observe(host, a, b)) {
            host->log("    file recovery seed%u time%d status%d/%d issue%u/%u bytes%lu/%lu\n", i, time, a.childStatus, b.childStatus, a.capture.issue, b.capture.issue, (unsigned long)a.capture.length, (unsigned long)b.capture.length);
            coverage.report(host); return 1;
        }
    }
    coverage.report(host);
    Case c = {7, time, true};
    autotest::Outcome a, b;
    autotest::runChild(before, &c, a, 2000, 10000);
    autotest::runChild(after, &c, b, 2000, 10000);
    bool detected = a.capture.length != b.capture.length || std::memcmp(a.capture.data, b.capture.data, a.capture.length);
    return !detected || autotest::incomplete(a) || autotest::incomplete(b) || !a.reportValid || !b.reportValid || a.childStatus || b.childStatus;
}
int timeWorker(const tlhybrid_host* host) { return worker(host, true); }
int directoryWorker(const tlhybrid_host* host) { return worker(host, false); }
}

TL_TEST(file_recovery_set_time) { return systems_fixture::isolated(timeWorker, host); }
TL_TEST(file_recovery_app_directory) { return systems_fixture::isolated(directoryWorker, host); }
