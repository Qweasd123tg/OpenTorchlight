#pragma once
#include "torchlight/checkpoint.hpp"
#include <filesystem>
#include <functional>

namespace torchlight {
inline constexpr std::uint32_t kCheckpointFormatVersion = 1;
inline constexpr std::size_t kMaximumCheckpointBytes = 32U * 1024U * 1024U;
[[nodiscard]] std::vector<std::uint8_t> encode_checkpoint(const CampaignCheckpoint &);
[[nodiscard]] CampaignCheckpoint decode_checkpoint(const std::vector<std::uint8_t> &);
struct SaveSlotInfo {
    std::string slot, name, error;
    std::int64_t class_guid = 0;
    DungeonAddress current;
    std::uint64_t revision = 0;
    std::filesystem::file_time_type modified{};
    [[nodiscard]] bool loadable() const noexcept {
        return error.empty();
    }
};
// OpenTorchlight-owned files only; never imports or modifies original saves.
class SaveStore {
  public:
    explicit SaveStore(std::filesystem::path directory);
    [[nodiscard]] static std::filesystem::path default_directory();
    [[nodiscard]] const std::filesystem::path &directory() const noexcept {
        return directory_;
    }
    [[nodiscard]] std::string allocate_slot() const;
    [[nodiscard]] std::vector<SaveSlotInfo> list(std::uint64_t resource_identity = 0) const;
    [[nodiscard]] CampaignCheckpoint read(const std::string &slot,
                                          std::uint64_t resource_identity = 0) const;
    // Revision conflict protection. Returns the committed revision. Hook is for
    // failure tests and is run AFTER syncing temp bytes, BEFORE atomic replacement.
    [[nodiscard]] std::uint64_t write(const CampaignCheckpoint &,
                                      const std::function<void()> &before_replace = {}) const;

  private:
    [[nodiscard]] std::filesystem::path path(const std::string &slot) const;
    std::filesystem::path directory_;
};
} // namespace torchlight
