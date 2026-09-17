#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vorbis/vorbisfile.h>

// Assets check: every shipped music track must be a decodable OGG stream.
// No playback, no game logic; proves the real files feed the backend.
int main(int argc, char **argv) {
    try {
        if (argc != 2) throw std::runtime_error("usage: music_tracks_probe music-dir");
        static const char *const tracks[] = {
            "TITLE.OGG", "TOWN.OGG", "TOWNFIGHT.OGG", "MINES.OGG", "CAVERN.OGG",
            "CRYPT.OGG", "FORTRESS.OGG", "LAVA.OGG", "PALACE.OGG", "RUINS.OGG",
            "BOSSANTICIPATION.OGG", "BOSSFIGHT.OGG", "BOSSRESOLUTION.OGG",
            "ORDRAAKFIGHT.OGG", "ORDRAAKRESOLUTION.OGG",
        };
        int decoded = 0;
        for (const char *track : tracks) {
            const std::string path = std::string(argv[1]) + "/" + track;
            OggVorbis_File vorbis{};
            if (ov_fopen(path.c_str(), &vorbis) != 0)
                throw std::runtime_error(std::string("cannot open ") + track);
            const vorbis_info *info = ov_info(&vorbis, -1);
            if (info == nullptr || info->rate <= 0 || info->channels <= 0 ||
                ov_time_total(&vorbis, -1) <= 0) {
                ov_clear(&vorbis);
                throw std::runtime_error(std::string("not a music stream: ") + track);
            }
            std::printf("%s rate=%ld channels=%d seconds=%.1f\n", track, info->rate,
                        info->channels, ov_time_total(&vorbis, -1));
            ov_clear(&vorbis);
            ++decoded;
        }
        std::printf("PASS: %d original music tracks decode; file names only, no mapping claim\n",
                    decoded);
        return 0;
    } catch (const std::exception &e) {
        std::fprintf(stderr, "FAIL: %s\n", e.what());
        return 1;
    }
}
