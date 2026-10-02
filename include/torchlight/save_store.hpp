#pragma once
#include "torchlight/checkpoint.hpp"
#include <filesystem>
#include <functional>

namespace torchlight {
// original-code: CGameUI::canLoad @0xa84d20 -> CMenuManager::canLoad
// @0xc2b700 queries the separate filename-vector count, signed low32 >0.
[[nodiscard]] bool save_list_can_load(std::size_t filename_count) noexcept;
inline constexpr std::uint32_t kCheckpointFormatVersion = 7;
inline constexpr std::size_t kMaximumCheckpointBytes = 32U * 1024U * 1024U;
[[nodiscard]] std::vector<std::uint8_t> encode_checkpoint(const CampaignCheckpoint &);
[[nodiscard]] CampaignCheckpoint decode_checkpoint(const std::vector<std::uint8_t> &);
struct SaveSlotInfo {
    std::string slot, name, error;
    std::int64_t class_guid = 0;
    // resource-derived from our own checkpoint (progression level, hardcore
    // flag). Feeds PlayerNDesc; the exact original Desc composition
    // (difficulty words, playtime, Dead/Retired) stays open.
    int level = 1;
    bool hardcore = false;
    DungeonAddress current;
    std::uint64_t revision = 0;
    std::filesystem::file_time_type modified{};
    // Our decoded PlayerCheckpoint::health. Trailing default preserves existing
    // aggregate fixtures while supplying CContinueGameMenu's health > 0 guard.
    float health = 1.0F;
    [[nodiscard]] bool loadable() const noexcept {
        return error.empty();
    }
};
// original-code: CContinueGameMenu::canContinue @0xc33490 (67 bytes),
// selected-index/count guard then saved float HP > 0. OTC error rows are an
// explicit adapter and cannot supply an original save-state object.
[[nodiscard]] const SaveSlotInfo* selected_continue_save(
    const std::vector<SaveSlotInfo>& saves, std::size_t selected) noexcept;
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
    // original-code: CContinueGameMenu::deleteCharacter @0xc3fd00 deletes the
    // selected save file (DeleteFile) then reloads the list. Idempotent:
    // absent slot removes nothing and reports false; traversal rejected.
    [[nodiscard]] bool remove(const std::string &slot) const;
    // Revision conflict protection. Returns the committed revision. Hook is for
    // failure tests and is run AFTER syncing temp bytes, BEFORE atomic replacement.
    [[nodiscard]] std::uint64_t write(const CampaignCheckpoint &,
                                      const std::function<void()> &before_replace = {}) const;

  private:
    [[nodiscard]] std::filesystem::path path(const std::string &slot) const;
    std::filesystem::path directory_;
};
} // namespace torchlight
