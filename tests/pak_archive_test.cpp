#include "torchlight/pak_archive.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <zlib.h>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void check_original(const std::filesystem::path& path) {
    const torchlight::PakArchive archive(path);
    require(archive.entries().size() == 24876, "unexpected original entry count");
    require(archive.contains("media/GLOBALS.DAT.adm"), "GLOBALS is missing");
    require(!archive.contains("media/globals.dat.adm"), "lookup unexpectedly changed case");
    const auto globals = archive.read("media/GLOBALS.DAT.adm");
    require(globals.size() == 38078, "unexpected GLOBALS size");
    require(globals.size() >= 8 && globals[0] == 1 && globals[1] == 0 &&
            globals[2] == 0 && globals[3] == 0, "unexpected GLOBALS header");
    const auto master = archive.read("media/MASTERRESOURCEUNITS.DAT.ADM");
    require(master.size() == 2987320, "unexpected master resource size");
    const auto root = archive.read("media/");
    require(root.empty(), "directory entry should be empty");
    std::cout << "PASS: indexed 24876 original resources and read stored/Deflate data\n";
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: pak_archive_test --original /path/to/pak.zip\n";
            return 2;
        }
        check_original(argv[2]);
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
