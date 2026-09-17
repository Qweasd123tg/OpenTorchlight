// Diagnostic only: reads the current project's actual layout/HUD implementation.
// Does not patch gameplay or claim original pixel geometry.
#include "torchlight/ui_hud.hpp"
#include <array>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace torchlight;
int main(int argc, char** argv) {
    try {
        if (argc != 2) throw std::runtime_error("usage: probe_port_ui original_pak.zip");
        PakArchive archive(argv[1]); UiResources resources(archive); UiHud hud(resources);
        std::cout << std::setprecision(9);
        std::cout << "viewport_w\tviewport_h\tlayout\twidget\tx\ty\tw\th\tvisible\tcallback\n";
        for (const auto size : {std::array<int,2>{1024,768}, {1280,720}, {1920,1080}, {2560,1440}}) {
            for (const auto* path : {"media/UI/inventorymenu.layout", "media/UI/bottomhud.layout"}) {
                const auto* layout = resources.layout(path);
                if (!layout) throw std::runtime_error(std::string("missing layout ") + path);
                for (const auto& w : layout->resolve(size[0],size[1])) {
                    if (w.name != "TopFrame" && w.name != "InventoryButton" && w.name != "PlayButton") continue;
                    std::cout << size[0] << '\t' << size[1] << '\t' << path << '\t' << w.name << '\t'
                              << w.rect.x << '\t' << w.rect.y << '\t' << w.rect.width << '\t' << w.rect.height << '\t'
                              << w.visible << '\t' << w.callback << '\n';
                }
            }
            const auto frame=hud.frame(size[0],size[1],UiHudValues{});
            for (const auto& w: frame.buttons) if (w.name=="PlayButton") {
                std::cout << size[0] << '\t' << size[1] << '\t' << "UiHud::frame" << '\t' << w.name << '\t'
                          << w.rect.x << '\t' << w.rect.y << '\t' << w.rect.width << '\t' << w.rect.height << '\t'
                          << w.visible << '\t' << w.callback << '\n';
            }
        }
        return 0;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
