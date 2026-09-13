#pragma once

#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace torchlight {

class PakError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class PakArchive {
public:
    struct Entry {
        std::string name;
        std::uint32_t crc32 = 0;
        std::uint32_t compressed_size = 0;
        std::uint32_t uncompressed_size = 0;
        std::uint32_t local_header_offset = 0;
        std::uint16_t compression_method = 0;
        std::uint16_t flags = 0;

        [[nodiscard]] bool is_directory() const noexcept {
            return !name.empty() && name.back() == '/';
        }
    };

    explicit PakArchive(const std::filesystem::path& path);

    [[nodiscard]] const std::filesystem::path& path() const noexcept { return path_; }
    [[nodiscard]] const std::vector<Entry>& entries() const noexcept { return entries_; }
    [[nodiscard]] const Entry* find(std::string_view name) const noexcept;
    [[nodiscard]] const Entry* find_normalized(std::string_view name) const noexcept;
    [[nodiscard]] bool contains(std::string_view name) const noexcept { return find(name) != nullptr; }
    [[nodiscard]] bool contains_normalized(std::string_view name) const noexcept {
        return find_normalized(name) != nullptr;
    }
    [[nodiscard]] std::vector<std::uint8_t> read(std::string_view name) const;
    [[nodiscard]] std::vector<std::uint8_t> read_normalized(std::string_view name) const;
    [[nodiscard]] std::vector<std::uint8_t> read(const Entry& entry) const;

private:
    std::filesystem::path path_;
    std::uint64_t file_size_ = 0;
    std::vector<Entry> entries_;
    std::unordered_map<std::string, std::size_t> index_;
    std::unordered_map<std::string, std::size_t> normalized_index_;
};

} // namespace torchlight
