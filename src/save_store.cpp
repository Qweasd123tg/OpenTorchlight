#include "torchlight/save_store.hpp"
#include <algorithm>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <fstream>
#include <iomanip>
#include <random>
#include <sstream>
#include <system_error>
#if defined(__unix__) || defined(__APPLE__)
#include <fcntl.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#endif
namespace torchlight {
namespace {
void valid_slot(const std::string &s) {
    if (s.empty() || s.size() > 64)
        throw CheckpointError("invalid save slot");
    for (const auto c : s)
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-'))
            throw CheckpointError("unsafe save slot");
}
std::vector<std::uint8_t> file_bytes(const std::filesystem::path &p) {
    if (std::filesystem::is_symlink(std::filesystem::symlink_status(p)) ||
        !std::filesystem::is_regular_file(p))
        throw CheckpointError("save slot is missing, not regular, or a symlink");
    const auto size = std::filesystem::file_size(p);
    if (size < 20 || size > kMaximumCheckpointBytes + 20)
        throw CheckpointError("save file size outside limit");
    std::ifstream in(p, std::ios::binary);
    if (!in)
        throw CheckpointError("cannot open save slot");
    std::vector<std::uint8_t> b(static_cast<std::size_t>(size));
    in.read(reinterpret_cast<char *>(b.data()), static_cast<std::streamsize>(b.size()));
    if (!in || in.peek() != std::char_traits<char>::eof())
        throw CheckpointError("save changed or was truncated while reading");
    return b;
}
#if defined(__unix__) || defined(__APPLE__)
struct Fd {
    int value = -1;
    explicit Fd(int n) : value(n) {
    }
    ~Fd() {
        if (value >= 0)
            ::close(value);
    }
    Fd(const Fd &) = delete;
    Fd &operator=(const Fd &) = delete;
};
void checked(bool ok, const char *operation) {
    if (!ok)
        throw CheckpointError(std::string(operation) + ": " + std::strerror(errno));
}
#endif
} // namespace
SaveStore::SaveStore(std::filesystem::path p) : directory_(std::move(p)) {
    if (directory_.empty())
        throw CheckpointError("empty save directory");
}
std::filesystem::path SaveStore::default_directory() {
    if (const char *x = std::getenv("XDG_DATA_HOME");
        x && *x && std::filesystem::path(x).is_absolute())
        return std::filesystem::path(x) / "opentorchlight" / "saves";
    if (const char *h = std::getenv("HOME"); h && *h && std::filesystem::path(h).is_absolute())
        return std::filesystem::path(h) / ".local" / "share" / "opentorchlight" / "saves";
    throw CheckpointError("set HOME or XDG_DATA_HOME, or pass --save-dir");
}
std::filesystem::path SaveStore::path(const std::string &slot) const {
    valid_slot(slot);
    return directory_ / (slot + ".otc");
}
std::string SaveStore::allocate_slot() const {
    std::random_device entropy;
    for (int attempt = 0; attempt < 32; ++attempt) {
        std::ostringstream s;
        s << "hero-" << std::hex << std::setfill('0');
        for (int i = 0; i < 4; ++i)
            s << std::setw(8) << static_cast<std::uint32_t>(entropy());
        if (!std::filesystem::exists(path(s.str())))
            return s.str();
    }
    throw CheckpointError("could not allocate a unique save slot");
}
CampaignCheckpoint SaveStore::read(const std::string &slot, std::uint64_t identity) const {
    auto c = decode_checkpoint(file_bytes(path(slot)));
    if (c.slot != slot)
        throw CheckpointError("save slot identity mismatch");
    if (identity && c.resource_identity != identity)
        throw CheckpointError("save belongs to different game resources");
    return c;
}
bool SaveStore::remove(const std::string &slot) const {
    const auto file = path(slot);
    std::error_code status_error;
    const auto status = std::filesystem::symlink_status(file, status_error);
    if (status_error) {
        if (status_error == std::errc::no_such_file_or_directory)
            return false;
        throw CheckpointError("cannot inspect save slot");
    }
    if (!std::filesystem::exists(status))
        return false;
    if (status.type() != std::filesystem::file_type::regular)
        throw CheckpointError("save slot is not a regular file");
    std::error_code remove_error;
    const bool removed = std::filesystem::remove(file, remove_error);
    if (remove_error)
        throw CheckpointError("cannot delete save slot");
    return removed;
}
std::vector<SaveSlotInfo> SaveStore::list(std::uint64_t identity) const {
    std::vector<SaveSlotInfo> result;
    if (!std::filesystem::exists(directory_))
        return result;
    for (const auto &e : std::filesystem::directory_iterator(directory_)) {
        if (e.path().extension() != ".otc")
            continue;
        if (result.size() >= 128)
            throw CheckpointError("more than 128 save slots");
        SaveSlotInfo row;
        row.slot = e.path().stem().string();
        std::error_code ec;
        row.modified = e.last_write_time(ec);
        try {
            auto c = read(row.slot, identity);
            row.name = c.character_name;
            row.class_guid = c.class_guid;
            row.current = c.current;
            row.revision = c.revision;
            row.hardcore = c.player.hardcore;
            row.health = c.player.health;
            // Same sanity range as validate_progression; garbage stays at 1.
            if (c.player.progression && c.player.progression->level >= 1)
                row.level = c.player.progression->level;
        } catch (const std::exception &error) {
            row.error = error.what();
            row.name = row.slot;
        }
        result.push_back(std::move(row));
    }
    std::sort(result.begin(), result.end(), [](const auto &a, const auto &b) {
        return a.modified == b.modified ? a.slot < b.slot : a.modified > b.modified;
    });
    return result;
}
std::uint64_t SaveStore::write(const CampaignCheckpoint &input,
                               const std::function<void()> &before_replace) const {
    valid_slot(input.slot);
    auto c = input;
    if (c.revision == std::numeric_limits<std::uint64_t>::max())
        throw CheckpointError("save revision exhausted");
    ++c.revision;
    const auto data = encode_checkpoint(c);
    std::filesystem::create_directories(directory_);
    if (std::filesystem::is_symlink(std::filesystem::symlink_status(directory_)))
        throw CheckpointError("save directory cannot be a symlink");
#if defined(__unix__) || defined(__APPLE__)
    Fd directory(::open(directory_.c_str(), O_RDONLY | O_DIRECTORY | O_CLOEXEC | O_NOFOLLOW));
    checked(directory.value >= 0, "open save directory");
    Fd lock(
        ::openat(directory.value, ".write-lock", O_RDWR | O_CREAT | O_CLOEXEC | O_NOFOLLOW, 0600));
    checked(lock.value >= 0, "open save lock");
    checked(::flock(lock.value, LOCK_EX) == 0, "lock save directory");
    const auto target = path(c.slot);
    if (std::filesystem::exists(target)) {
        if (read(c.slot).revision != input.revision)
            throw CheckpointError("save changed in another process; reload before overwriting");
    } else if (input.revision != 0)
        throw CheckpointError("existing save slot disappeared; not overwriting silently");
    std::string temp = (directory_ / ".checkpoint-XXXXXX").string();
    std::vector<char> name(temp.begin(), temp.end());
    name.push_back(0);
    Fd fd(::mkstemp(name.data()));
    checked(fd.value >= 0, "create temporary save");
    bool renamed = false;
    try {
        std::size_t done = 0;
        while (done < data.size()) {
            const auto n = ::write(fd.value, data.data() + done, data.size() - done);
            if (n < 0 && errno == EINTR)
                continue;
            checked(n > 0, "write temporary save");
            done += static_cast<std::size_t>(n);
        }
        checked(::fsync(fd.value) == 0, "sync temporary save");
        if (before_replace)
            before_replace();
        checked(::rename(name.data(), target.c_str()) == 0, "replace save");
        renamed = true;
        checked(::fsync(directory.value) == 0,
                "sync save directory (file committed; reload revision on failure)");
    } catch (...) {
        if (!renamed)
            ::unlink(name.data());
        throw;
    }
    return c.revision;
#else
    (void)before_replace;
    throw CheckpointError("atomic save writer is implemented for POSIX platforms only");
#endif
}
} // namespace torchlight
