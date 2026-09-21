#include "torchlight/pak_archive.hpp"
#include "torchlight/ui_skin.hpp"
#include "torchlight/ui_window_runtime.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace torchlight;
namespace {

void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}

UiWidget widget(std::string name, std::string type = "DefaultWindow") {
    UiWidget result;
    result.name = std::move(name);
    result.type = std::move(type);
    result.properties["UnifiedAreaRect"] = "{{0,0},{0,0},{1,0},{1,0}}";
    result.properties["Marker"] = "retained-until-dead-pool";
    return result;
}

void initialization_registration_and_reentrancy() {
    UiWindowRuntime runtime;
    std::vector<std::string> calls;
    std::optional<UiWindowId> nested;
    bool fail_once = true;
    UiWindowLifecycle lifecycle;
    lifecycle.initialize = [&](UiWindowId id, const UiWidget& value) {
            calls.push_back("init:" + value.name);
            require(!runtime.alive(id), "window registered before initialize returned");
            require(!runtime.find(value.name), "initializing window exposed by name registry");
            require(runtime.window(id).name == value.name,
                    "initialize did not receive its stable ID/widget");
            if (value.name == "outer") {
                nested = runtime.create(widget("nested"));
                require(*nested != id, "reentrant initialize reused factory window ID");
                require(runtime.alive(*nested) && runtime.find("nested") == nested,
                        "reentrant child was not registered after its initialize");
                require(!runtime.alive(id),
                        "outer window registered while reentrant initialize was running");
            }
            if (value.name == "creation-fails" && fail_once) {
                fail_once = false;
                throw std::runtime_error("initialize failure");
            }
        };
    runtime.set_lifecycle(std::move(lifecycle));

    const auto outer = runtime.create(widget("outer"));
    require(outer == 0 && nested == 1 && runtime.alive(outer) &&
                runtime.find("outer") == outer &&
                calls == std::vector<std::string>({"init:outer", "init:nested"}),
            "reentrant factory initialization changed IDs or registration order");

    bool propagated = false;
    try { static_cast<void>(runtime.create(widget("creation-fails"))); }
    catch (const std::runtime_error& error) {
        propagated = std::string(error.what()) == "initialize failure";
    }
    require(propagated && !runtime.find("creation-fails"),
            "initialize exception was hidden or failed window was registered");
    const auto recovered = runtime.create(widget("creation-fails"));
    require(recovered == 3 && runtime.alive(recovered),
            "failed initialization reused its allocated stable ID");
}

void destruction_order_and_deferred_release() {
    UiWindowRuntime runtime;
    std::vector<std::string> calls;
    UiWindowLifecycle lifecycle;
    lifecycle.initialize = [&](UiWindowId, const UiWidget& value) {
            calls.push_back("init:" + value.name);
        };
    lifecycle.reset_tooltip_target = [&](UiWindowId id) {
            calls.push_back("reset:" + runtime.window(id).name);
        };
    lifecycle.release_tooltip = [&](UiWindowId id) {
            calls.push_back("release:" + runtime.window(id).name);
        };
    lifecycle.detach_renderer = [&](UiWindowId, const UiWidget& value) {
            calls.push_back("detach:" + value.name);
        };
    lifecycle.destroy_renderer = [&](UiWindowId, const UiWidget& value) {
            calls.push_back("renderer:" + value.name);
        };
    lifecycle.destroy_factory_object = [&](UiWindowId, const UiWidget& value) {
            require(value.property("Marker") == "retained-until-dead-pool",
                    "dead-pool factory hook received cleared properties");
            calls.push_back("factory:" + value.name);
        };
    runtime.set_lifecycle(std::move(lifecycle));
    runtime.set_event_listener([&](const UiWindowEvent& event) {
        if (event.type == UiWindowEventType::destruction_started)
            calls.push_back("event:" + runtime.window(event.window).name);
    });

    const auto parent = runtime.create(widget("parent"));
    const auto child = runtime.create(widget("child"));
    runtime.add_child(parent, child);
    calls.clear();
    runtime.destroy(parent);
    require(calls == std::vector<std::string>({
                "reset:parent", "release:parent", "detach:parent", "renderer:parent",
                "event:parent", "reset:child", "release:child", "detach:child",
                "renderer:child", "event:child"}),
            "Window destroy dependency/owned-child ordering differs");
    require(!runtime.alive(parent) && !runtime.alive(child) &&
                runtime.window(parent).property("Marker") == "retained-until-dead-pool" &&
                runtime.window(child).property("Marker") == "retained-until-dead-pool",
            "destroy released factory properties before dead-pool cleanup");

    runtime.clean_dead_pool();
    require(calls.size() == 12 && calls[10] == "factory:parent" && calls[11] == "factory:child",
            "dead-pool did not release reverse-destruction factory order");
    bool parent_released = false;
    bool child_released = false;
    try { static_cast<void>(runtime.window(parent)); }
    catch (const std::out_of_range&) { parent_released = true; }
    try { static_cast<void>(runtime.window(child)); }
    catch (const std::out_of_range&) { child_released = true; }
    require(parent_released && child_released,
            "clean_dead_pool retained allocated widgets/properties");
}

void teardown_exceptions_stop_at_the_throwing_hook() {
    const std::vector<std::string> hook_names{"reset", "release", "detach", "renderer"};
    for (std::size_t throwing = 0; throwing < hook_names.size(); ++throwing) {
        UiWindowRuntime runtime;
        std::vector<std::string> calls;
        const auto invoke = [&](const char* name) {
            calls.emplace_back(name);
            if (calls.size() - 1 == throwing) throw std::runtime_error(name);
        };
        UiWindowLifecycle lifecycle;
        lifecycle.reset_tooltip_target = [&](UiWindowId) { invoke("reset"); };
        lifecycle.release_tooltip = [&](UiWindowId) { invoke("release"); };
        lifecycle.detach_renderer = [&](UiWindowId, const UiWidget&) { invoke("detach"); };
        lifecycle.destroy_renderer = [&](UiWindowId, const UiWidget&) { invoke("renderer"); };
        lifecycle.destroy_factory_object = [&](UiWindowId, const UiWidget&) {
                calls.push_back("factory");
            };
        runtime.set_lifecycle(std::move(lifecycle));
        const auto id = runtime.create(widget("throws"));
        bool propagated = false;
        try { runtime.destroy(id); }
        catch (const std::runtime_error& error) {
            propagated = error.what() == hook_names[throwing];
        }
        require(propagated && !runtime.alive(id) && calls.size() == throwing + 1,
                "teardown hook exception was hidden or later hooks continued");
        for (std::size_t i = 0; i <= throwing; ++i)
            require(calls[i] == hook_names[i], "teardown stopped at the wrong named hook");
        runtime.destroy(id);
        runtime.clean_dead_pool();
        require(calls.size() == throwing + 1,
                "failed teardown was fabricated as completed on retry/dead-pool cleanup");
    }
}

void resource_lifetime_contract(const char* pak_path) {
    PakArchive archive(pak_path);
    UiResources resources(archive);
    UiSkinCache cache(resources);
    UiWindowRuntime runtime;
    UiWindowLifecycle lifecycle;
    lifecycle.initialize = [&](UiWindowId, const UiWidget& value) {
            resources.attach_window_renderer(value.name, value.type);
        };
    lifecycle.detach_renderer = [&](UiWindowId, const UiWidget& value) {
            resources.detach_window_renderer(value.name);
        };
    lifecycle.destroy_renderer = [&](UiWindowId, const UiWidget& value) {
            resources.destroy_window_renderer(value.name);
        };
    lifecycle.destroy_factory_object = [&](UiWindowId, const UiWidget& value) {
            resources.destroy_window_factory(value.name);
        };
    runtime.set_lifecycle(std::move(lifecycle));

    const auto id = runtime.create(widget("lifecycle-checkbox", "GuiLook/Checkbox"));
    const auto renderer = resources.window_renderer("lifecycle-checkbox");
    require(renderer && !renderer->empty(), "real window renderer was not attached at initialize");

    UiResolvedWidget resolved;
    resolved.name = "lifecycle-checkbox";
    resolved.type = "GuiLook/Checkbox";
    resolved.rect = {10, 10, 80, 30};
    resolved.clip = {0, 0, 200, 100};
    resolved.has_clip = true;
    static_cast<void>(cache.compile(resolved, {}, 200, 100));
    require(cache.compile_count() == 1, "real window cache did not compile fixture");

    const auto image_before = resources.image("set:GuiLook image:WindowLeftEdge");
    auto* const font_before = resources.font("SerifSmall");
    require(image_before && font_before, "real immutable UI image/font fixture missing");

    runtime.destroy(id);
    require(!resources.window_renderer("lifecycle-checkbox"),
            "destroy_renderer retained per-window renderer binding");
    static_cast<void>(cache.compile(resolved, {}, 200, 100));
    require(cache.compile_count() == 2,
            "detach_renderer did not invalidate the per-window render cache");

    const auto replacement = runtime.create(widget("lifecycle-checkbox", "GuiLook/Checkbox"));
    require(resources.window_renderer("lifecycle-checkbox").has_value(),
            "destroyed name was not reusable before dead-pool cleanup");
    static_cast<void>(cache.compile(resolved, {}, 200, 100));
    const auto replacement_compile_count = cache.compile_count();
    runtime.clean_dead_pool();
    require(resources.window_renderer("lifecycle-checkbox").has_value(),
            "old dead-pool factory cleanup erased the replacement renderer");
    static_cast<void>(cache.compile(resolved, {}, 200, 100));
    require(cache.compile_count() == replacement_compile_count,
            "old dead-pool factory cleanup erased the replacement render cache");
    const auto image_after = resources.image("set:GuiLook image:WindowLeftEdge");
    auto* const font_after = resources.font("SerifSmall");
    require(image_after && font_after == font_before &&
                image_after->texture_path == image_before->texture_path &&
                image_after->x == image_before->x && image_after->y == image_before->y,
            "per-window destruction released shared immutable image/font resources");
    runtime.destroy(replacement);
    runtime.clean_dead_pool();
    require(!resources.window_renderer("lifecycle-checkbox"),
            "replacement renderer survived its own destroy/dead-pool cleanup");
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc > 2) throw std::runtime_error("usage: ui_window_lifecycle_test [pak.zip]");
        initialization_registration_and_reentrancy();
        destruction_order_and_deferred_release();
        teardown_exceptions_stop_at_the_throwing_hook();
        if (argc == 2) resource_lifetime_contract(argv[1]);
        std::cout << "PASS: WindowManager factory registration and deferred Window teardown";
        if (argc == 2) std::cout << "; real renderer/cache/resource ownership";
        std::cout << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
