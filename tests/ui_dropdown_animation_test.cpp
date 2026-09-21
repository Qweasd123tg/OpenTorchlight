#include "torchlight/pak_archive.hpp"
#include "torchlight/ui_dropdown_animation.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

bool near(float left, float right, float tolerance = 0.00001F) {
    return std::abs(left - right) <= tolerance;
}

} // namespace

int main(int argc, char** argv) {
    try {
        require(argc == 2, "usage: ui_dropdown_animation_test original-pak.zip");
        const torchlight::PakArchive archive(argv[1]);
        torchlight::DropdownAnimation dropdown(archive);
        require(!dropdown.open() && dropdown.closed() && !dropdown.visible(),
                "model-enabled dropdown has the wrong initial lifecycle");

        dropdown.set_open(true);
        require(dropdown.open() && dropdown.closed() && dropdown.visible(),
                "opening did not preserve original closed field ordering");
        const auto open_sound = dropdown.consume_sound_requests();
        require(open_sound.size() == 1U &&
                    open_sound.front() == torchlight::DropdownSoundRequest::open,
                "opening did not request original sound 22");
        auto layers = dropdown.layers();
        require(layers.size() == 2U &&
                    layers[0].clip == torchlight::DropdownAnimationClip::idle &&
                    layers[0].queued && !layers[0].active &&
                    layers[1].clip == torchlight::DropdownAnimationClip::open &&
                    layers[1].active && !layers[1].queued,
                "OPEN/IDLE were not pushed newest-first");
        require(near(layers[0].length, 0.0333333015F, 0.0000001F) &&
                    near(layers[1].length, 0.966666996F, 0.0000001F) &&
                    near(layers[1].speed, 2.0F),
                "original dropdown clip lengths/speeds changed");

        const auto batches768 = dropdown.draws(1024, 768);
        require(batches768.size() == 1U && batches768[0].vertices.size() == 12U,
                "dropdown mesh is not its original four indexed triangles");
        require(batches768[0].texture.size() >= std::string("dropdown.dds").size() &&
                    batches768[0].texture.compare(
                        batches768[0].texture.size() - std::string("dropdown.dds").size(),
                        std::string("dropdown.dds").size(), "dropdown.dds") == 0 &&
                    batches768[0].scene_blend == torchlight::OgreSceneBlend::alpha &&
                    batches768[0].alpha_compare == torchlight::OgreAlphaCompare::greater &&
                    batches768[0].alpha_rejection == 5U && !batches768[0].depth_write &&
                    !batches768[0].depth_check,
                "Dropdown_ material contract changed");
        require(dropdown.pose().geometries.size() == 1U &&
                    dropdown.pose().geometries[0].positions.size() == 6U,
                "dropdown CPU skin pose has the wrong geometry");
        const auto tag = std::find_if(dropdown.pose().bones.begin(), dropdown.pose().bones.end(),
                                      [](const auto& bone) {
                                          return bone.name == "tag_dropdowntop";
                                      });
        require(tag != dropdown.pose().bones.end(), "tag_dropdowntop was not sampled");
        const auto content = dropdown.content_position(1024, 768);
        require(near(content[0], 512.0F + tag->position[0]) &&
                    near(content[1], 384.0F - tag->position[1]),
                "content did not consume the sampled derived tag pose");
        const auto batches384 = dropdown.draws(512, 384);
        require(near(batches384[0].vertices[0].x - 256.0F,
                     (batches768[0].vertices[0].x - 512.0F) * 0.5F) &&
                    near(batches384[0].vertices[0].y - 192.0F,
                         (batches768[0].vertices[0].y - 384.0F) * 0.5F),
                "UI orthographic height/768 projection changed");

        dropdown.advance(0.1F);
        layers = dropdown.layers();
        require(layers[0].queued && near(layers[1].time, 0.2F),
                "IDLE activated before the predecessor threshold");

        dropdown.set_open(false);
        const auto close_sound = dropdown.consume_sound_requests();
        require(close_sound.size() == 1U &&
                    close_sound.front() == torchlight::DropdownSoundRequest::close,
                "closing did not request original sound 66");
        require(!dropdown.open() && !dropdown.closed() && dropdown.visible(),
                "closing detached the dropdown before CLOSE completion");
        layers = dropdown.layers();
        require(!layers.empty() && layers.front().clip ==
                    torchlight::DropdownAnimationClip::close &&
                    layers.front().active && near(layers.front().speed, 2.0F) &&
                    near(layers.front().length, 0.333332986F, 0.0000001F),
                "CLOSE blend did not use the original clip/speed");
        dropdown.advance(0.02F);
        require(dropdown.visible() && !dropdown.close_transition_complete(),
                "CLOSE blend completed too early");

        dropdown.set_open(true); // interrupted CLOSE -> blended OPEN + queued IDLE
        layers = dropdown.layers();
        require(layers.size() >= 3U && layers.front().queued &&
                    layers[1].clip == torchlight::DropdownAnimationClip::open &&
                    layers[2].clip == torchlight::DropdownAnimationClip::close,
                "rapid reopen lost the interrupted shared-state chain");
        dropdown.advance(0.01F);
        for (const auto& batch : dropdown.draws(1024, 768)) {
            for (const auto& vertex : batch.vertices) {
                require(std::isfinite(vertex.x) && std::isfinite(vertex.y),
                        "interrupted N-layer pose produced invalid geometry");
            }
        }
        dropdown.advance(1.0F);
        require(dropdown.open() && dropdown.visible(),
                "rapid reopen was hidden by the interrupted CLOSE");

        dropdown.set_open(false);
        dropdown.advance(0.05F);
        require(dropdown.visible() && !dropdown.closed(),
                "root detached while CLOSE was still playing");
        dropdown.advance(0.2F);
        require(!dropdown.visible() && dropdown.closed() &&
                    dropdown.close_transition_complete() && dropdown.draws(1024, 768).empty(),
                "completed CLOSE did not hide and detach the model branch");

        std::cout << "PASS: original dropdown resources, CGenericModel queue/interruption, "
                     "tag consumer and UI orthographic mesh projection\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
