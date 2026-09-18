cmake_minimum_required(VERSION 3.16)
project(torchlight_recovery LANGUAGES C CXX)

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
# CEGUI 0.6.2 uses FreeType for <Font> resources. Optional: without it the UI
# keeps the explicitly marked prototype glyph font.
find_package(Freetype QUIET)
# Menu music ships as plain OGG next to the game. Optional like FreeType:
# without vorbisfile/ALSA the player records the requested track but stays
# silent instead of failing the build (TORCHLIGHT_HAVE_MUSIC unset).
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(VORBISFILE IMPORTED_TARGET vorbisfile)
    pkg_check_modules(ALSA IMPORTED_TARGET alsa)
endif()
if(VORBISFILE_FOUND AND ALSA_FOUND)
    set(TORCHLIGHT_HAVE_MUSIC TRUE)
endif()
set(TORCHLIGHT_ORIGINAL "" CACHE FILEPATH "Original Linux executable for behavioral comparison")
set(TORCHLIGHT_GAME_DIR "" CACHE PATH "Read-only directory containing pak.zip (independent of ELF)")
if(TORCHLIGHT_ORIGINAL AND NOT TORCHLIGHT_GAME_DIR)
    get_filename_component(_TORCHLIGHT_GAME_DIR "${TORCHLIGHT_ORIGINAL}" DIRECTORY)
    set(TORCHLIGHT_GAME_DIR "${_TORCHLIGHT_GAME_DIR}" CACHE PATH "Read-only directory containing pak.zip" FORCE)
endif()
option(TORCHLIGHT_ENABLE_RENDER "Build available offscreen rendering targets" ON)
option(TORCHLIGHT_ENABLE_DESKTOP "Build the Wayland adapter when its SDK is available" ON)
# Same test inputs/assertions; instrumentation may need a larger wall-clock budget.
# Explicit cache value is reported by check.py, never inferred from a failed test.
set(TORCHLIGHT_TEST_TIMEOUT_SCALE 1 CACHE STRING "Wall-clock multiplier (1-10), e.g. 4 for sanitizer builds")
if(NOT TORCHLIGHT_TEST_TIMEOUT_SCALE MATCHES "^([1-9]|10)$")
    message(FATAL_ERROR "TORCHLIGHT_TEST_TIMEOUT_SCALE must be an integer from 1 to 10")
endif()


add_library(torchlight_core STATIC
    src/actor_motion.cpp
    src/adm_document.cpp
    src/animation_events.cpp
    src/animation_manifest.cpp
    src/attack_action.cpp
    src/character_stats.cpp
    src/collision_scene.cpp
    src/line_of_sight.cpp
    src/combat.cpp
    src/consumable.cpp
    src/merchant.cpp
    src/economy.cpp
    src/quests.cpp
    src/skills.cpp
    src/checkpoint.cpp
    src/save_codec.cpp
    src/save_store.cpp
    src/settings.cpp
    src/ui_layout.cpp
    src/ui_font.cpp
    src/ui_text.cpp
    src/ui_hud.cpp
    src/frontend.cpp
    src/interaction.cpp
    src/damage.cpp
    src/dds_texture.cpp
    src/equipment.cpp
    src/entity_world.cpp
    src/enemy_ai.cpp
    src/vitals.cpp
    src/input_state.cpp
    src/inventory.cpp
    src/inventory_view.cpp
    src/player_session.cpp
    src/population.cpp
    src/progression.cpp
    src/treasure.cpp
    src/key_manager.cpp
    src/level_scene.cpp
    src/level_transition.cpp
    src/logic_runtime.cpp
    src/master_resource_index.cpp
    src/mouse_manager.cpp
    src/navigation_grid.cpp
    src/ogre_material.cpp
    src/ogre_mesh.cpp
    src/ogre_skeleton.cpp
    src/pak_archive.cpp
    src/pathfinder_rules.cpp
    src/pointer_movement.cpp
    src/player.cpp
    src/png_texture.cpp
    src/random_level.cpp
    src/randomizer.cpp
    src/resource_config.cpp
    src/scene_animation.cpp
    src/scene_geometry.cpp
    src/scene_math.cpp
    src/skeletal_animation.cpp
    src/spawn_class.cpp
    src/stat_graph.cpp
    src/unit_definition.cpp
    src/unit_type.cpp
    src/music.cpp)
target_include_directories(torchlight_core PUBLIC include)
target_compile_features(torchlight_core PUBLIC cxx_std_17)
target_link_libraries(torchlight_core PUBLIC ZLIB::ZLIB PNG::PNG)
if(TORCHLIGHT_HAVE_MUSIC)
    target_link_libraries(torchlight_core PUBLIC PkgConfig::VORBISFILE PkgConfig::ALSA)
    target_compile_definitions(torchlight_core PUBLIC TORCHLIGHT_HAVE_MUSIC=1)
    message(STATUS "Music: vorbisfile + ALSA playback enabled")
else()
    message(STATUS "Music: vorbisfile/ALSA not found; silent track tracking only")
endif()
if(Freetype_FOUND)
    target_link_libraries(torchlight_core PUBLIC Freetype::Freetype)
    target_compile_definitions(torchlight_core PUBLIC TORCHLIGHT_HAVE_FREETYPE=1)
    message(STATUS "UI fonts: FreeType ${FREETYPE_VERSION_STRING}")
else()
    message(STATUS "UI fonts: FreeType not found; prototype glyph fallback only")
endif()
set_target_properties(torchlight_core PROPERTIES POSITION_INDEPENDENT_CODE ON)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(torchlight_core PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(torchlight_asset_catalog src/asset_catalog_main.cpp)
target_link_libraries(torchlight_asset_catalog PRIVATE torchlight_core)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(torchlight_asset_catalog PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_library(torchlight_application STATIC src/application.cpp)
target_link_libraries(torchlight_application PUBLIC torchlight_core)
target_compile_features(torchlight_application PUBLIC cxx_std_17)
set_target_properties(torchlight_application PROPERTIES POSITION_INDEPENDENT_CODE ON)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(torchlight_application PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(torchlight_bootstrap src/bootstrap_main.cpp)
target_link_libraries(torchlight_bootstrap PRIVATE torchlight_core)
add_executable(torchlight_level_rules_dump tools/level_rules_dump.cpp)
target_link_libraries(torchlight_level_rules_dump PRIVATE torchlight_core)
add_executable(torchlight_player_units_dump tools/player_units_dump.cpp)
target_link_libraries(torchlight_player_units_dump PRIVATE torchlight_core)
add_executable(torchlight_scene_camera_dump tools/scene_camera_dump.cpp)
target_link_libraries(torchlight_scene_camera_dump PRIVATE torchlight_core)

if(UNIX AND NOT ANDROID)
    find_package(PkgConfig)
    if(PkgConfig_FOUND)
        pkg_check_modules(EGL IMPORTED_TARGET egl)
        pkg_check_modules(GLES2 IMPORTED_TARGET glesv2)
        pkg_check_modules(WAYLAND_CLIENT IMPORTED_TARGET wayland-client)
        pkg_check_modules(WAYLAND_EGL IMPORTED_TARGET wayland-egl)
    endif()
    find_program(WAYLAND_SCANNER wayland-scanner)
    find_file(XDG_SHELL_XML xdg-shell.xml PATHS
        /usr/share/wayland-protocols/stable/xdg-shell
        /usr/share/qt6/wayland/protocols/xdg-shell)
    if(TORCHLIGHT_ENABLE_RENDER AND EGL_FOUND AND GLES2_FOUND)
        add_library(torchlight_gles2 STATIC src/gles_scene_renderer.cpp src/gles_ui_renderer.cpp)
        target_link_libraries(torchlight_gles2 PUBLIC torchlight_core PkgConfig::GLES2)
        target_compile_features(torchlight_gles2 PUBLIC cxx_std_17)
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(torchlight_gles2 PRIVATE -Wall -Wextra -Wpedantic -Werror)
        endif()
        add_executable(gles_render_smoke_test tests/gles_render_smoke_test.cpp)
        target_link_libraries(gles_render_smoke_test PRIVATE PkgConfig::EGL PkgConfig::GLES2)
        target_compile_features(gles_render_smoke_test PRIVATE cxx_std_17)
        add_executable(ogre_mesh_render_test tests/ogre_mesh_render_test.cpp)
        target_link_libraries(ogre_mesh_render_test PRIVATE
            torchlight_core PkgConfig::EGL PkgConfig::GLES2)
        target_compile_features(ogre_mesh_render_test PRIVATE cxx_std_17)
        add_executable(scene_geometry_render_test tests/scene_geometry_render_test.cpp)
        target_link_libraries(scene_geometry_render_test PRIVATE
            torchlight_gles2 PkgConfig::EGL)
        target_compile_features(scene_geometry_render_test PRIVATE cxx_std_17)
    endif()
    if(TORCHLIGHT_ENABLE_DESKTOP AND TARGET torchlight_gles2 AND
       WAYLAND_CLIENT_FOUND AND WAYLAND_EGL_FOUND AND WAYLAND_SCANNER AND
       XDG_SHELL_XML AND EXISTS "${XDG_SHELL_XML}")
        set(XDG_SHELL_HEADER ${CMAKE_CURRENT_BINARY_DIR}/generated/xdg-shell-client-protocol.h)
        set(XDG_SHELL_CODE ${CMAKE_CURRENT_BINARY_DIR}/generated/xdg-shell-protocol.c)
        add_custom_command(
            OUTPUT ${XDG_SHELL_HEADER}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/generated
            COMMAND ${WAYLAND_SCANNER} client-header ${XDG_SHELL_XML} ${XDG_SHELL_HEADER}
            DEPENDS ${XDG_SHELL_XML})
        add_custom_command(
            OUTPUT ${XDG_SHELL_CODE}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/generated
            COMMAND ${WAYLAND_SCANNER} private-code ${XDG_SHELL_XML} ${XDG_SHELL_CODE}
            DEPENDS ${XDG_SHELL_XML})
        add_library(torchlight_xdg_shell STATIC ${XDG_SHELL_CODE} ${XDG_SHELL_HEADER})
        target_include_directories(torchlight_xdg_shell PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/generated)
        target_link_libraries(torchlight_xdg_shell PUBLIC PkgConfig::WAYLAND_CLIENT)
        # original-code: the SDL2 original grabs the mouse at window creation
        # (SDL_SetWindowGrab(1)); on Wayland that is pointer confinement.
        # Vendored unstable-v1 protocol, see research/window-policy.md.
        set(POINTER_CONSTRAINTS_XML ${CMAKE_CURRENT_SOURCE_DIR}/tools/wayland-protocols/pointer-constraints-unstable-v1.xml)
        set(POINTER_CONSTRAINTS_HEADER ${CMAKE_CURRENT_BINARY_DIR}/generated/pointer-constraints-unstable-v1-client-protocol.h)
        set(POINTER_CONSTRAINTS_CODE ${CMAKE_CURRENT_BINARY_DIR}/generated/pointer-constraints-unstable-v1-protocol.c)
        add_custom_command(
            OUTPUT ${POINTER_CONSTRAINTS_HEADER}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/generated
            COMMAND ${WAYLAND_SCANNER} client-header ${POINTER_CONSTRAINTS_XML} ${POINTER_CONSTRAINTS_HEADER}
            DEPENDS ${POINTER_CONSTRAINTS_XML})
        add_custom_command(
            OUTPUT ${POINTER_CONSTRAINTS_CODE}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/generated
            COMMAND ${WAYLAND_SCANNER} private-code ${POINTER_CONSTRAINTS_XML} ${POINTER_CONSTRAINTS_CODE}
            DEPENDS ${POINTER_CONSTRAINTS_XML})
        add_library(torchlight_pointer_constraints STATIC ${POINTER_CONSTRAINTS_CODE} ${POINTER_CONSTRAINTS_HEADER})
        target_include_directories(torchlight_pointer_constraints PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/generated)
        target_link_libraries(torchlight_pointer_constraints PUBLIC PkgConfig::WAYLAND_CLIENT)
        add_executable(torchlight_desktop src/linux_desktop_main.cpp)
        target_link_libraries(torchlight_desktop PRIVATE
            torchlight_application torchlight_gles2 torchlight_xdg_shell torchlight_pointer_constraints PkgConfig::WAYLAND_EGL PkgConfig::EGL)
        target_compile_features(torchlight_desktop PRIVATE cxx_std_17)
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(torchlight_desktop PRIVATE -Wall -Wextra -Wpedantic -Werror)
        endif()

    else()
        message(STATUS "Desktop shell disabled: Wayland, EGL, GLES2, or xdg-shell files are missing")
    endif()
endif()

include(CTest)
if(BUILD_TESTING AND NOT CMAKE_CROSSCOMPILING)
    add_executable(attack_action_test tests/attack_action_test.cpp)
    target_link_libraries(attack_action_test PRIVATE torchlight_core)
    add_test(NAME ordinary_attack_action COMMAND attack_action_test)
    add_library(input_comparison SHARED tests/input_c_api.cpp)
    target_link_libraries(input_comparison PRIVATE torchlight_core)
    add_library(action_comparison SHARED tests/action_c_api.cpp)
    target_link_libraries(action_comparison PRIVATE torchlight_core)
    add_library(randomizer_comparison SHARED tests/randomizer_c_api.cpp)
    target_link_libraries(randomizer_comparison PRIVATE torchlight_core)
    add_library(pathfinder_comparison SHARED tests/pathfinder_c_api.cpp)
    target_link_libraries(pathfinder_comparison PRIVATE torchlight_core)
    add_library(camera_comparison SHARED tests/camera_c_api.cpp)
    target_link_libraries(camera_comparison PRIVATE torchlight_core)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
        add_library(ogre_camera_reference SHARED tests/ogre_camera_reference.cpp)
        target_compile_features(ogre_camera_reference PRIVATE cxx_std_17)
        target_compile_definitions(ogre_camera_reference PRIVATE _GLIBCXX_USE_CXX11_ABI=0)
        target_link_libraries(ogre_camera_reference PRIVATE ${CMAKE_DL_LIBS})
    endif()
    add_executable(pak_archive_test tests/pak_archive_test.cpp)
    target_link_libraries(pak_archive_test PRIVATE torchlight_core)
    add_executable(actor_motion_test tests/actor_motion_test.cpp)
    target_link_libraries(actor_motion_test PRIVATE torchlight_core)
    add_executable(collision_mesh_test tests/collision_mesh_test.cpp)
    target_link_libraries(collision_mesh_test PRIVATE torchlight_core)
    add_executable(adm_document_test tests/adm_document_test.cpp)
    target_link_libraries(adm_document_test PRIVATE torchlight_core)
    add_executable(master_resource_index_test tests/master_resource_index_test.cpp)
    target_link_libraries(master_resource_index_test PRIVATE torchlight_core)
    add_executable(unit_definition_test tests/unit_definition_test.cpp)
    target_link_libraries(unit_definition_test PRIVATE torchlight_core)
    add_executable(level_scene_test tests/level_scene_test.cpp)
    target_link_libraries(level_scene_test PRIVATE torchlight_core)
    add_executable(logic_runtime_test tests/logic_runtime_test.cpp)
    target_link_libraries(logic_runtime_test PRIVATE torchlight_core)
    add_executable(random_level_test tests/random_level_test.cpp)
    target_link_libraries(random_level_test PRIVATE torchlight_core)
    add_executable(player_test tests/player_test.cpp)
    target_link_libraries(player_test PRIVATE torchlight_core)
    add_executable(ogre_mesh_test tests/ogre_mesh_test.cpp)
    target_link_libraries(ogre_mesh_test PRIVATE torchlight_core)
    add_executable(ogre_material_test tests/ogre_material_test.cpp)
    target_link_libraries(ogre_material_test PRIVATE torchlight_core)
    add_executable(ogre_skeleton_test tests/ogre_skeleton_test.cpp)
    target_link_libraries(ogre_skeleton_test PRIVATE torchlight_core)
    add_executable(animation_manifest_test tests/animation_manifest_test.cpp)
    target_link_libraries(animation_manifest_test PRIVATE torchlight_core)
    add_executable(animation_events_test tests/animation_events_test.cpp)
    target_link_libraries(animation_events_test PRIVATE torchlight_core)
    add_executable(skeletal_animation_test tests/skeletal_animation_test.cpp)
    target_link_libraries(skeletal_animation_test PRIVATE torchlight_core)
    add_executable(dds_texture_test tests/dds_texture_test.cpp)
    target_link_libraries(dds_texture_test PRIVATE torchlight_core)
    add_executable(png_texture_test tests/png_texture_test.cpp)
    target_link_libraries(png_texture_test PRIVATE torchlight_core)
    add_executable(scene_geometry_test tests/scene_geometry_test.cpp)
    target_link_libraries(scene_geometry_test PRIVATE torchlight_core)
    add_executable(spawn_class_test tests/spawn_class_test.cpp)
    target_link_libraries(spawn_class_test PRIVATE torchlight_core)
    add_executable(entity_world_test tests/entity_world_test.cpp)
    target_link_libraries(entity_world_test PRIVATE torchlight_core)
    add_executable(enemy_ai_test tests/enemy_ai_test.cpp)
    target_link_libraries(enemy_ai_test PRIVATE torchlight_core)
    add_executable(unit_type_test tests/unit_type_test.cpp)
    target_link_libraries(unit_type_test PRIVATE torchlight_core)
    add_executable(combat_test tests/combat_test.cpp)
    target_link_libraries(combat_test PRIVATE torchlight_core)
    add_executable(damage_test tests/damage_test.cpp)
    target_link_libraries(damage_test PRIVATE torchlight_core)
    add_executable(equipment_test tests/equipment_test.cpp)
    target_link_libraries(equipment_test PRIVATE torchlight_core)
    add_executable(level_transition_test tests/level_transition_test.cpp)
    target_link_libraries(level_transition_test PRIVATE torchlight_core)
    add_executable(warp_arrival_test tests/warp_arrival_test.cpp)
    target_link_libraries(warp_arrival_test PRIVATE torchlight_core)
    add_test(NAME actor_motion COMMAND actor_motion_test)
    add_test(NAME animation_events COMMAND animation_events_test)
    add_test(NAME damage_calculation COMMAND damage_test)
    add_test(NAME warp_arrival COMMAND warp_arrival_test)
    add_executable(level_entry_test tests/level_entry_test.cpp)
    target_link_libraries(level_entry_test PRIVATE torchlight_core)
    add_test(NAME level_entry_fallback COMMAND level_entry_test)
    find_package(Python3 REQUIRED COMPONENTS Interpreter)
    set(TORCHLIGHT_REFERENCE_PYTHON "${Python3_EXECUTABLE}" CACHE FILEPATH
        "PIE Python interpreter for original fixed-address comparison (optional)")

    set(AI_COOLDOWN_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/ai-cooldown.pak.zip)
    add_custom_command(
        OUTPUT ${AI_COOLDOWN_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_ai_cooldown_fixture.py
            ${AI_COOLDOWN_FIXTURE}
        DEPENDS tests/make_ai_cooldown_fixture.py
        VERBATIM)
    add_custom_target(ai_cooldown_fixture DEPENDS ${AI_COOLDOWN_FIXTURE})
    add_executable(enemy_ai_cooldown_test tests/enemy_ai_cooldown_test.cpp)
    target_link_libraries(enemy_ai_cooldown_test PRIVATE torchlight_core)
    add_dependencies(enemy_ai_cooldown_test ai_cooldown_fixture)
    add_test(NAME enemy_ai_cooldown COMMAND enemy_ai_cooldown_test ${AI_COOLDOWN_FIXTURE})
    set_tests_properties(enemy_ai_cooldown PROPERTIES TIMEOUT 30)
    add_executable(ai_cooldown_probe tests/ai_cooldown_probe.cpp)
    target_link_libraries(ai_cooldown_probe PRIVATE torchlight_core)
    add_test(NAME ai_cooldown_export_comparison
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_ai_cooldown.py
            --disassembly-dir ${CMAKE_CURRENT_SOURCE_DIR}/research/disassembly
            --probe $<TARGET_FILE:ai_cooldown_probe>)
    set_tests_properties(ai_cooldown_export_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
    if(UNIX AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_test(NAME desktop_gameplay_syntax
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/check_desktop_gameplay_syntax.py
                --root ${CMAKE_CURRENT_SOURCE_DIR} --compiler ${CMAKE_CXX_COMPILER})
        set_tests_properties(desktop_gameplay_syntax PROPERTIES TIMEOUT 60)
    endif()
    add_executable(inventory_view_test tests/inventory_view_test.cpp)
    target_link_libraries(inventory_view_test PRIVATE torchlight_core)
    add_test(NAME inventory_view COMMAND inventory_view_test)
    add_executable(inventory_test tests/inventory_test.cpp)
    target_link_libraries(inventory_test PRIVATE torchlight_core)
    add_test(NAME inventory_instances COMMAND inventory_test)
    set(ITEM_CYCLE_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/item-cycle.pak.zip)
    add_custom_command(OUTPUT ${ITEM_CYCLE_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_item_cycle_fixture.py
            ${ITEM_CYCLE_FIXTURE}
        DEPENDS tests/make_item_cycle_fixture.py tests/make_ai_cooldown_fixture.py
        VERBATIM)
    add_custom_target(item_cycle_fixture DEPENDS ${ITEM_CYCLE_FIXTURE})
    add_executable(item_cycle_test tests/item_cycle_test.cpp)
    target_link_libraries(item_cycle_test PRIVATE torchlight_core)
    add_dependencies(item_cycle_test item_cycle_fixture)
    add_test(NAME item_cycle COMMAND item_cycle_test ${ITEM_CYCLE_FIXTURE})
    set_tests_properties(item_cycle PROPERTIES TIMEOUT 30)
    add_executable(attack_speed_probe tests/attack_speed_probe.cpp)
    target_link_libraries(attack_speed_probe PRIVATE torchlight_core)
    add_test(NAME attack_speed_export_comparison
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_attack_speed.py
            --probe $<TARGET_FILE:attack_speed_probe>)
    set_tests_properties(attack_speed_export_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
    set(ORDINARY_COMBAT_FIXTURE "${CMAKE_CURRENT_BINARY_DIR}/fixtures/ordinary-combat.pak.zip")
    add_custom_command(OUTPUT ${ORDINARY_COMBAT_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_attack_fixture.py ${ORDINARY_COMBAT_FIXTURE}
        DEPENDS tests/make_attack_fixture.py tests/make_ai_cooldown_fixture.py tests/make_item_cycle_fixture.py
        VERBATIM)
    add_custom_target(ordinary_combat_fixture DEPENDS ${ORDINARY_COMBAT_FIXTURE})
    add_executable(ordinary_combat_test tests/ordinary_combat_test.cpp)
    target_link_libraries(ordinary_combat_test PRIVATE torchlight_core)
    add_dependencies(ordinary_combat_test ordinary_combat_fixture)
    add_test(NAME ordinary_combat COMMAND ordinary_combat_test ${ORDINARY_COMBAT_FIXTURE})
    set_tests_properties(ordinary_combat PROPERTIES TIMEOUT 60)
    set(FRONTEND_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/frontend.pak.zip)
    add_custom_command(OUTPUT ${FRONTEND_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_frontend_fixture.py ${FRONTEND_FIXTURE}
        DEPENDS tests/make_frontend_fixture.py tests/make_attack_fixture.py tests/make_item_cycle_fixture.py tests/make_ai_cooldown_fixture.py
        VERBATIM)
    add_custom_target(frontend_fixture DEPENDS ${FRONTEND_FIXTURE})
    set(HUD_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/hud.pak.zip)
    add_custom_command(OUTPUT ${HUD_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_hud_fixture.py ${HUD_FIXTURE}
        DEPENDS tests/make_hud_fixture.py
        VERBATIM)
    add_custom_target(hud_fixture DEPENDS ${HUD_FIXTURE})
    add_executable(frontend_test tests/frontend_test.cpp)
    target_link_libraries(frontend_test PRIVATE torchlight_core)
    add_dependencies(frontend_test frontend_fixture)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(frontend_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    add_test(NAME frontend COMMAND frontend_test ${FRONTEND_FIXTURE})
    add_executable(music_test tests/music_test.cpp)
    target_link_libraries(music_test PRIVATE torchlight_core)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(music_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    add_test(NAME music COMMAND music_test)
    if(TORCHLIGHT_HAVE_MUSIC AND TORCHLIGHT_GAME_DIR)
        add_executable(music_tracks_probe tests/music_tracks_probe.cpp)
        target_link_libraries(music_tracks_probe PRIVATE PkgConfig::VORBISFILE)
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(music_tracks_probe PRIVATE -Wall -Wextra -Wpedantic -Werror)
        endif()
        add_test(NAME original_music_tracks
            COMMAND music_tracks_probe "${TORCHLIGHT_GAME_DIR}/music")
    endif()
    add_executable(settings_test tests/settings_test.cpp)
    target_link_libraries(settings_test PRIVATE torchlight_core)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(settings_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    add_test(NAME settings COMMAND settings_test)
    set(MENU_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/menu-widgets.pak.zip)
    add_custom_command(OUTPUT ${MENU_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_menu_fixture.py ${MENU_FIXTURE}
        DEPENDS tests/make_menu_fixture.py tests/make_frontend_fixture.py tests/make_ui_font_fixture.py
        VERBATIM)
    add_custom_target(menu_fixture DEPENDS ${MENU_FIXTURE})
    add_executable(frontend_menu_test tests/frontend_menu_test.cpp)
    target_link_libraries(frontend_menu_test PRIVATE torchlight_core)
    add_dependencies(frontend_menu_test menu_fixture)
    add_executable(ui_text_test tests/ui_text_test.cpp)
    target_link_libraries(ui_text_test PRIVATE torchlight_core)
    foreach(_ui_target frontend_menu_test ui_text_test)
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(${_ui_target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
        endif()
    endforeach()
    add_test(NAME frontend_menu_resources COMMAND frontend_menu_test ${MENU_FIXTURE})
    add_test(NAME ui_text_layout COMMAND ui_text_test)
    set_tests_properties(frontend_menu_resources ui_text_layout PROPERTIES TIMEOUT 30)
    set(UI_FONT_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/ui-font.pak.zip)
    add_custom_command(OUTPUT ${UI_FONT_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_ui_font_fixture.py ${UI_FONT_FIXTURE}
        DEPENDS tests/make_ui_font_fixture.py VERBATIM)
    add_custom_target(ui_font_fixture DEPENDS ${UI_FONT_FIXTURE})
    if(Freetype_FOUND)
        add_executable(ui_font_atlas_test tests/ui_font_atlas_test.cpp)
        target_link_libraries(ui_font_atlas_test PRIVATE torchlight_core)
        add_dependencies(ui_font_atlas_test ui_font_fixture)
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(ui_font_atlas_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
        endif()
        add_test(NAME ui_font_atlas COMMAND ui_font_atlas_test ${UI_FONT_FIXTURE})
        set_tests_properties(ui_font_atlas PROPERTIES TIMEOUT 30)
    endif()
    add_executable(menu_resource_probe tests/menu_resource_probe.cpp)
    target_link_libraries(menu_resource_probe PRIVATE torchlight_core)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(menu_resource_probe PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_menu_presentation
            COMMAND menu_resource_probe "${TORCHLIGHT_GAME_DIR}/pak.zip")
    endif()
    add_executable(frontend_resource_test tests/frontend_resource_test.cpp)
    target_link_libraries(frontend_resource_test PRIVATE torchlight_core)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(frontend_resource_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    if(Freetype_FOUND)
        add_executable(ui_font_probe tests/ui_font_probe.cpp)
        target_link_libraries(ui_font_probe PRIVATE torchlight_core)
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(ui_font_probe PRIVATE -Wall -Wextra -Wpedantic -Werror)
        endif()
        if(TORCHLIGHT_GAME_DIR)
            add_test(NAME original_ui_font_resource
                COMMAND ui_font_probe "${TORCHLIGHT_GAME_DIR}/pak.zip")
        endif()
    endif()
    add_executable(frontend_cycle_test tests/frontend_cycle_test.cpp)
    target_link_libraries(frontend_cycle_test PRIVATE torchlight_core)
    add_dependencies(frontend_cycle_test frontend_fixture)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(frontend_cycle_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    add_test(NAME frontend_campaign_cycle COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/frontend_cycle_process_test.py
        --probe $<TARGET_FILE:frontend_cycle_test> --fixture ${FRONTEND_FIXTURE})
    set_tests_properties(frontend_campaign_cycle PROPERTIES TIMEOUT 120)
    add_test(NAME coverage_map_current COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/coverage_map.py --check --root ${CMAKE_CURRENT_SOURCE_DIR})
    set_tests_properties(coverage_map_current PROPERTIES TIMEOUT 60)
    # Optional real EGL/GLVND readback test, not a substitute for the desktop SDK.
    find_library(UI_TEST_GL_DISPATCH NAMES GL libGL.so.1)
    if(UNIX AND UI_TEST_GL_DISPATCH AND TORCHLIGHT_ENABLE_RENDER)
        add_library(gles_ui_probe SHARED tests/gles_ui_probe.cpp src/gles_ui_renderer.cpp)
        target_include_directories(gles_ui_probe PRIVATE tests/support/gles-api)
        target_link_libraries(gles_ui_probe PRIVATE torchlight_core ${UI_TEST_GL_DISPATCH})
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(gles_ui_probe PRIVATE -Wall -Wextra -Wpedantic -Werror)
        endif()
        add_library(application_scenario_probe SHARED
            tests/application_scenario_probe.cpp src/gles_scene_renderer.cpp src/gles_ui_renderer.cpp)
        target_include_directories(application_scenario_probe PRIVATE tests/support/gles-api)
        target_link_libraries(application_scenario_probe PRIVATE torchlight_application ${UI_TEST_GL_DISPATCH})
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(application_scenario_probe PRIVATE -Wall -Wextra -Wpedantic -Werror)
        endif()
        add_dependencies(gles_ui_probe frontend_fixture hud_fixture menu_fixture ui_font_fixture)
        add_test(NAME gles_ui_headless COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/gles_ui_headless_test.py
            --probe $<TARGET_FILE:gles_ui_probe> --fixture ${FRONTEND_FIXTURE}
            --hud-fixture ${HUD_FIXTURE})
        set(_ui_font_args)
        if(Freetype_FOUND)
            list(APPEND _ui_font_args --font-fixture ${UI_FONT_FIXTURE})
        endif()
        add_test(NAME gles_menu_text COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/gles_menu_text_test.py
            --probe $<TARGET_FILE:gles_ui_probe> --fixture ${MENU_FIXTURE} ${_ui_font_args})
        set_tests_properties(gles_menu_text PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
        set_tests_properties(gles_ui_headless PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
        set(TORCHLIGHT_PYTHON_ASAN_PRELOAD "" CACHE FILEPATH "ASan runtime for the optional Python-hosted EGL probe")
        if(TORCHLIGHT_PYTHON_ASAN_PRELOAD)
            # Python and Mesa own process-global allocations. Native core tests
            # still use leak detection; this host checks address/UB errors only.
            set_tests_properties(gles_ui_headless gles_menu_text PROPERTIES ENVIRONMENT
                "LD_PRELOAD=${TORCHLIGHT_PYTHON_ASAN_PRELOAD};ASAN_OPTIONS=detect_leaks=0:halt_on_error=1;UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1")
        endif()
    endif()
    add_executable(save_checkpoint_test tests/save_checkpoint_test.cpp)
    target_link_libraries(save_checkpoint_test PRIVATE torchlight_core)
    add_dependencies(save_checkpoint_test ordinary_combat_fixture)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(save_checkpoint_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    add_test(NAME save_checkpoint COMMAND save_checkpoint_test ${ORDINARY_COMBAT_FIXTURE}
        ${CMAKE_CURRENT_BINARY_DIR}/checkpoint-test-saves self)
    add_test(NAME save_fresh_process COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/save_process_test.py
        --probe $<TARGET_FILE:save_checkpoint_test> --fixture ${ORDINARY_COMBAT_FIXTURE})
    add_test(NAME save_atomic_process COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/save_atomic_process_test.py
        --probe $<TARGET_FILE:save_checkpoint_test> --fixture ${ORDINARY_COMBAT_FIXTURE})
    set_tests_properties(save_checkpoint save_fresh_process save_atomic_process PROPERTIES TIMEOUT 90)
    add_executable(gameplay_continuation_test tests/gameplay_continuation_test.cpp)
    target_link_libraries(gameplay_continuation_test PRIVATE torchlight_core)
    add_dependencies(gameplay_continuation_test ordinary_combat_fixture)
    add_test(NAME gameplay_continuation COMMAND gameplay_continuation_test ${ORDINARY_COMBAT_FIXTURE})
    set_tests_properties(gameplay_continuation PROPERTIES TIMEOUT 60)
    add_executable(death_finalization_test tests/death_finalization_test.cpp)
    target_link_libraries(death_finalization_test PRIVATE torchlight_core)
    add_dependencies(death_finalization_test item_cycle_fixture)
    add_test(NAME death_finalization COMMAND death_finalization_test ${ITEM_CYCLE_FIXTURE})
    set_tests_properties(death_finalization PROPERTIES TIMEOUT 60)
    add_executable(effect_catalog_probe tests/effect_catalog_probe.cpp)
    target_link_libraries(effect_catalog_probe PRIVATE torchlight_core)
    add_test(NAME effect_catalog_source
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/effect_catalog_source_test.py
            --probe $<TARGET_FILE:effect_catalog_probe>)
    set_tests_properties(effect_catalog_source PROPERTIES TIMEOUT 60)

    add_test(NAME read_only_extractors
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/read_only_extractors_test.py)
    set_tests_properties(read_only_extractors PROPERTIES TIMEOUT 30)
    add_executable(player_vitals_probe tests/player_vitals_probe.cpp)
    target_link_libraries(player_vitals_probe PRIVATE torchlight_core)
    add_test(NAME combat_inputs_evidence
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_player_vitals.py
            --probe $<TARGET_FILE:player_vitals_probe> --constants-only)
    add_test(NAME player_vitals_export_comparison
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_player_vitals.py
            --probe $<TARGET_FILE:player_vitals_probe>)
    set_tests_properties(player_vitals_export_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)

    set(PROGRESSION_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/progression.pak.zip)
    add_custom_command(OUTPUT ${PROGRESSION_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_progression_fixture.py ${PROGRESSION_FIXTURE}
        DEPENDS tests/make_progression_fixture.py tests/make_attack_fixture.py tests/make_item_cycle_fixture.py tests/make_ai_cooldown_fixture.py
        VERBATIM)
    add_custom_target(progression_fixture DEPENDS ${PROGRESSION_FIXTURE})
    add_executable(reward_cycle_test tests/reward_cycle_test.cpp)
    target_link_libraries(reward_cycle_test PRIVATE torchlight_core)
    add_dependencies(reward_cycle_test progression_fixture)
    add_executable(reward_resource_probe tests/reward_resource_probe.cpp)
    target_link_libraries(reward_resource_probe PRIVATE torchlight_core)
    add_dependencies(reward_resource_probe progression_fixture)
    add_test(NAME reward_resource_graphs COMMAND reward_resource_probe ${PROGRESSION_FIXTURE})
    add_test(NAME reward_unavailable COMMAND reward_cycle_test --unavailable ${ORDINARY_COMBAT_FIXTURE})
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_progression_resource_graphs COMMAND reward_resource_probe ${TORCHLIGHT_GAME_DIR}/pak.zip)
    endif()
    add_executable(world_gold_probe tests/world_gold_probe.cpp)
    target_link_libraries(world_gold_probe PRIVATE torchlight_core)
    add_executable(checkpoint_upgrade_probe tests/checkpoint_upgrade_probe.cpp)
    target_link_libraries(checkpoint_upgrade_probe PRIVATE torchlight_core)
    add_executable(monster_experience_probe tests/monster_experience_probe.cpp)
    target_link_libraries(monster_experience_probe PRIVATE torchlight_core)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        foreach(_reward_target reward_cycle_test reward_resource_probe world_gold_probe
                monster_experience_probe checkpoint_upgrade_probe)
            target_compile_options(${_reward_target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
        endforeach()
    endif()
    add_test(NAME progression_numeric COMMAND reward_cycle_test --numeric)
    add_test(NAME reward_cycle COMMAND reward_cycle_test ${PROGRESSION_FIXTURE})
    add_test(NAME reward_fresh_process COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/reward_save_process_test.py
        --probe $<TARGET_FILE:reward_cycle_test> --fixture ${PROGRESSION_FIXTURE})
    add_test(NAME legacy_reward_save_migration COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/legacy_reward_save_test.py
        --probe $<TARGET_FILE:save_checkpoint_test> --upgrade $<TARGET_FILE:checkpoint_upgrade_probe>
        --fixture ${FRONTEND_FIXTURE})
    add_test(NAME world_gold_export_comparison COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_world_gold.py --probe $<TARGET_FILE:world_gold_probe>)
    add_test(NAME monster_experience_export_comparison COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_monster_experience.py --probe $<TARGET_FILE:monster_experience_probe>)
    set_tests_properties(progression_numeric reward_cycle reward_fresh_process legacy_reward_save_migration
        world_gold_export_comparison monster_experience_export_comparison PROPERTIES TIMEOUT 90)
    set_tests_properties(world_gold_export_comparison monster_experience_export_comparison
        PROPERTIES SKIP_RETURN_CODE 77)
    if(TORCHLIGHT_ORIGINAL)
        add_test(NAME original_world_gold_comparison COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_world_gold.py --probe $<TARGET_FILE:world_gold_probe>
            --original ${TORCHLIGHT_ORIGINAL})
        add_test(NAME original_monster_experience_comparison COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_monster_experience.py --probe $<TARGET_FILE:monster_experience_probe>
            --original ${TORCHLIGHT_ORIGINAL})
        set_tests_properties(original_world_gold_comparison original_monster_experience_comparison
            PROPERTIES TIMEOUT 90 SKIP_RETURN_CODE 77)
    endif()

    add_executable(item_cycle_resource_test tests/item_cycle_resource_test.cpp)
    target_link_libraries(item_cycle_resource_test PRIVATE torchlight_core)
    add_dependencies(item_cycle_resource_test item_cycle_fixture)
    add_test(NAME item_cycle_resource_fixture
        COMMAND item_cycle_resource_test --pak ${ITEM_CYCLE_FIXTURE})
    set_tests_properties(item_cycle_resource_fixture PROPERTIES TIMEOUT 60)

    if(TORCHLIGHT_ORIGINAL)
        add_test(NAME original_player_vitals_comparison
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_player_vitals.py
                --probe $<TARGET_FILE:player_vitals_probe> --original "${TORCHLIGHT_ORIGINAL}")
        set_tests_properties(original_player_vitals_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
        add_test(NAME original_attack_speed_comparison
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_attack_speed.py
                --original "${TORCHLIGHT_ORIGINAL}" --probe $<TARGET_FILE:attack_speed_probe>)
        set_tests_properties(original_attack_speed_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
        add_test(NAME original_ai_cooldown_comparison
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_ai_cooldown.py
                --original ${TORCHLIGHT_ORIGINAL}
                --probe $<TARGET_FILE:ai_cooldown_probe>)
        set_tests_properties(original_ai_cooldown_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
        add_test(NAME original_level_entry_dispatch
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/verify_original_entry_dispatch.py
                --original ${TORCHLIGHT_ORIGINAL})
        set_tests_properties(original_level_entry_dispatch PROPERTIES TIMEOUT 30)
        if(TARGET ogre_camera_reference)
            add_test(NAME original_camera_comparison
                COMMAND ${TORCHLIGHT_REFERENCE_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_original_camera.py
                    --original ${TORCHLIGHT_ORIGINAL}
                    --library $<TARGET_FILE:camera_comparison>
                    --ogre-reference $<TARGET_FILE:ogre_camera_reference>
                    --scene-dump $<TARGET_FILE:torchlight_scene_camera_dump>)
            set_tests_properties(original_camera_comparison PROPERTIES TIMEOUT 60)
        endif()
        add_test(NAME original_input_comparison
            COMMAND ${TORCHLIGHT_REFERENCE_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_original_input.py
                --original ${TORCHLIGHT_ORIGINAL}
                --library $<TARGET_FILE:input_comparison>)
        set_tests_properties(original_input_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
        add_test(NAME original_action_comparison
            COMMAND ${TORCHLIGHT_REFERENCE_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_original_action.py
                --original ${TORCHLIGHT_ORIGINAL}
                --library $<TARGET_FILE:action_comparison>)
        set_tests_properties(original_action_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
        add_test(NAME original_randomizer_comparison
            COMMAND ${TORCHLIGHT_REFERENCE_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_original_random.py
                --original ${TORCHLIGHT_ORIGINAL}
                --library $<TARGET_FILE:randomizer_comparison>)
        set_tests_properties(original_randomizer_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
        add_test(NAME original_pathfinder_comparison
            COMMAND ${TORCHLIGHT_REFERENCE_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_original_pathfinder.py
                --original ${TORCHLIGHT_ORIGINAL}
                --library $<TARGET_FILE:pathfinder_comparison>)
        set_tests_properties(original_pathfinder_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)

    else()
        message(STATUS "Original comparison not configured: set TORCHLIGHT_ORIGINAL to run it")
    endif()
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_frontend_checkpoint
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/save_process_test.py
                --probe $<TARGET_FILE:frontend_resource_test> --fixture "${TORCHLIGHT_GAME_DIR}/pak.zip")
        set_tests_properties(original_frontend_checkpoint PROPERTIES TIMEOUT 240)
        add_test(NAME original_item_cycle
            COMMAND item_cycle_resource_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        set_tests_properties(original_item_cycle PROPERTIES TIMEOUT 180)

        add_test(NAME original_pak_archive
            COMMAND pak_archive_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_collision_meshes
            COMMAND collision_mesh_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_adm_document
            COMMAND adm_document_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_master_resource_index
            COMMAND master_resource_index_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_unit_definitions
            COMMAND unit_definition_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_level_scene
            COMMAND level_scene_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_logic_runtime
            COMMAND logic_runtime_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_random_levels
            COMMAND random_level_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_players
            COMMAND player_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_ogre_meshes
            COMMAND ogre_mesh_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_ogre_materials
            COMMAND ogre_material_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_ogre_skeletons
            COMMAND ogre_skeleton_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_animation_manifests
            COMMAND animation_manifest_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_skeletal_animation
            COMMAND skeletal_animation_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_dds_textures
            COMMAND dds_texture_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_png_textures
            COMMAND png_texture_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_scene_geometry
            COMMAND scene_geometry_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_spawn_classes
            COMMAND spawn_class_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_entity_world
            COMMAND entity_world_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_equipment
            COMMAND equipment_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_enemy_ai
            COMMAND enemy_ai_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_unit_types
            COMMAND unit_type_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_combat
            COMMAND combat_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_level_transitions
            COMMAND level_transition_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_data_bootstrap
            COMMAND torchlight_bootstrap --pak "${TORCHLIGHT_GAME_DIR}/pak.zip")
        if(EXISTS "${TORCHLIGHT_GAME_DIR}/resources.cfg")
            add_test(NAME original_resource_configuration
                COMMAND torchlight_bootstrap "${TORCHLIGHT_GAME_DIR}")
        endif()
        if(TARGET ogre_mesh_render_test)
            add_test(NAME original_ogre_mesh_render
                COMMAND ogre_mesh_render_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
            set_tests_properties(original_ogre_mesh_render PROPERTIES
                TIMEOUT 30 ENVIRONMENT "EGL_PLATFORM=surfaceless")
        endif()
        if(TARGET scene_geometry_render_test)
            add_test(NAME original_scene_geometry_render
                COMMAND scene_geometry_render_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
            set_tests_properties(original_scene_geometry_render PROPERTIES
                TIMEOUT 30 ENVIRONMENT "EGL_PLATFORM=surfaceless")
        endif()
    endif()
        if(TARGET gles_render_smoke_test)
            add_test(NAME gles_render_smoke COMMAND gles_render_smoke_test)
            set_tests_properties(gles_render_smoke PROPERTIES
                TIMEOUT 30 ENVIRONMENT "EGL_PLATFORM=surfaceless")
        endif()

    add_executable(parent_dungeon_test tests/parent_dungeon_test.cpp)
    target_link_libraries(parent_dungeon_test PRIVATE torchlight_core)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(parent_dungeon_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    add_test(NAME parent_dungeon COMMAND parent_dungeon_test)
    add_test(NAME scenario_first_difference
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/scenario_diff_test.py)
    add_test(NAME asset_catalog_negative
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/asset_catalog_test.py
            --probe $<TARGET_FILE:torchlight_asset_catalog> --pak ${FRONTEND_FIXTURE}
            --output-dir ${CMAKE_CURRENT_BINARY_DIR}/catalog-evidence --negative
            --timeout-scale ${TORCHLIGHT_TEST_TIMEOUT_SCALE})
    set_tests_properties(asset_catalog_negative PROPERTIES TIMEOUT 90)
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_asset_catalog
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/asset_catalog_test.py
                --probe $<TARGET_FILE:torchlight_asset_catalog> --pak ${TORCHLIGHT_GAME_DIR}/pak.zip
                --output-dir ${CMAKE_CURRENT_BINARY_DIR}/catalog-evidence
                --timeout-scale ${TORCHLIGHT_TEST_TIMEOUT_SCALE})
        if(TARGET application_scenario_probe)
            add_test(NAME application_scenario_render
                COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/application_scenario_test.py
                    --probe $<TARGET_FILE:application_scenario_probe>
                    --game-dir ${TORCHLIGHT_GAME_DIR}
                    --output-dir ${CMAKE_CURRENT_BINARY_DIR}/scenario-evidence --roundtrip
                    --speed-probe $<TARGET_FILE:attack_speed_probe>
                    --timeout-scale ${TORCHLIGHT_TEST_TIMEOUT_SCALE})
            add_test(NAME application_combat_render
                COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/application_combat_test.py
                    --probe $<TARGET_FILE:application_scenario_probe>
                    --game-dir ${TORCHLIGHT_GAME_DIR}
                    --output-dir ${CMAKE_CURRENT_BINARY_DIR}/scenario-evidence
                    --timeout-scale ${TORCHLIGHT_TEST_TIMEOUT_SCALE})
            set_tests_properties(application_combat_render PROPERTIES TIMEOUT 600)
            set_tests_properties(application_scenario_render PROPERTIES TIMEOUT 900)
            if(TORCHLIGHT_PYTHON_ASAN_PRELOAD)
                set_tests_properties(application_scenario_render application_combat_render PROPERTIES ENVIRONMENT
                    "LD_PRELOAD=${TORCHLIGHT_PYTHON_ASAN_PRELOAD};ASAN_OPTIONS=detect_leaks=0:halt_on_error=1;UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1")
            endif()
        endif()
    endif()

    add_executable(random_observation_test tests/random_observation_test.cpp)
    target_link_libraries(random_observation_test PRIVATE torchlight_core)
    add_test(NAME random_observation COMMAND random_observation_test)

    add_test(NAME verification_driver
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/verification_driver_test.py)
    set_tests_properties(verification_driver PROPERTIES TIMEOUT 40)

    set(VITALS_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/vitals.pak.zip)
    add_custom_command(OUTPUT ${VITALS_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_vitals_fixture.py ${VITALS_FIXTURE}
        DEPENDS tests/make_vitals_fixture.py tests/make_attack_fixture.py tests/make_item_cycle_fixture.py tests/make_ai_cooldown_fixture.py
        VERBATIM)
    add_custom_target(vitals_fixture DEPENDS ${VITALS_FIXTURE})
    add_executable(vitals_test tests/vitals_test.cpp)
    target_link_libraries(vitals_test PRIVATE torchlight_core)
    add_dependencies(vitals_test vitals_fixture)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(vitals_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    add_test(NAME vitals_numeric COMMAND vitals_test --numeric)
    add_test(NAME vitals_resource_cycle COMMAND vitals_test ${VITALS_FIXTURE})
    add_test(NAME vitals_fresh_process COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/vitals_process_test.py
        --probe $<TARGET_FILE:vitals_test> --fixture ${VITALS_FIXTURE})
    add_test(NAME vitals_v2_migration COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/vitals_legacy_test.py
        --probe $<TARGET_FILE:vitals_test> --fixture ${VITALS_FIXTURE})
    set_tests_properties(vitals_numeric vitals_resource_cycle vitals_fresh_process vitals_v2_migration PROPERTIES TIMEOUT 90)

    add_test(NAME collect_game_inputs_safety COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/collect_game_inputs_test.py)
    set_tests_properties(collect_game_inputs_safety PROPERTIES TIMEOUT 30)

    set(CONSUMABLE_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/consumables.pak.zip)
    add_custom_command(OUTPUT ${CONSUMABLE_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_consumable_fixture.py ${CONSUMABLE_FIXTURE}
        DEPENDS tests/make_consumable_fixture.py tests/make_attack_fixture.py tests/make_item_cycle_fixture.py tests/make_ai_cooldown_fixture.py)
    add_custom_target(consumable_fixture DEPENDS ${CONSUMABLE_FIXTURE})
    add_executable(consumable_test tests/consumable_test.cpp)
    target_link_libraries(consumable_test PRIVATE torchlight_core)
    add_dependencies(consumable_test consumable_fixture)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(consumable_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    add_test(NAME consumable_cycle COMMAND consumable_test ${CONSUMABLE_FIXTURE})
    add_test(NAME consumable_fresh_process COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/consumable_process_test.py $<TARGET_FILE:consumable_test> ${CONSUMABLE_FIXTURE})
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_consumables COMMAND consumable_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
    endif()

    set(POPULATION_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/population.pak.zip)
    add_custom_command(OUTPUT ${POPULATION_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_population_fixture.py ${POPULATION_FIXTURE}
        DEPENDS tests/make_population_fixture.py tests/make_attack_fixture.py tests/make_ai_cooldown_fixture.py tests/make_item_cycle_fixture.py VERBATIM)
    add_custom_target(population_fixture DEPENDS ${POPULATION_FIXTURE})
    add_executable(population_test tests/population_test.cpp)
    target_link_libraries(population_test PRIVATE torchlight_core)
    add_dependencies(population_test population_fixture)
    add_test(NAME population_cycle COMMAND population_test ${POPULATION_FIXTURE})
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_population COMMAND population_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
    endif()

    set(RANGED_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/ranged.pak.zip)
    add_custom_command(OUTPUT ${RANGED_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_ranged_fixture.py ${RANGED_FIXTURE}
        DEPENDS tests/make_ranged_fixture.py tests/make_attack_fixture.py tests/make_ai_cooldown_fixture.py tests/make_item_cycle_fixture.py VERBATIM)
    add_custom_target(ranged_fixture DEPENDS ${RANGED_FIXTURE})
    add_executable(ranged_test tests/ranged_test.cpp)
    target_link_libraries(ranged_test PRIVATE torchlight_core)
    add_dependencies(ranged_test ranged_fixture)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(ranged_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    add_test(NAME ranged_cycle COMMAND ranged_test ${RANGED_FIXTURE})
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_ranged COMMAND ranged_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
    endif()

    add_executable(gameplay_numeric_probe tests/gameplay_numeric_probe.cpp)
    target_link_libraries(gameplay_numeric_probe PRIVATE torchlight_core)
    if(TORCHLIGHT_ORIGINAL)
        add_test(NAME original_gameplay_numeric_comparison
            COMMAND ${TORCHLIGHT_REFERENCE_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_gameplay_numeric.py
            --original ${TORCHLIGHT_ORIGINAL} --probe $<TARGET_FILE:gameplay_numeric_probe>)
        set_tests_properties(original_gameplay_numeric_comparison PROPERTIES TIMEOUT 120 SKIP_RETURN_CODE 77)
    endif()

    set(LEGACY_V3_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/legacy-v3.pak.zip)
    add_custom_command(OUTPUT ${LEGACY_V3_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_legacy_v3_fixture.py ${LEGACY_V3_FIXTURE}
        DEPENDS tests/make_legacy_v3_fixture.py tests/make_attack_fixture.py tests/make_ai_cooldown_fixture.py tests/make_item_cycle_fixture.py VERBATIM)
    add_custom_target(legacy_v3_fixture DEPENDS ${LEGACY_V3_FIXTURE})
    add_executable(legacy_v3_test tests/legacy_v3_test.cpp)
    target_link_libraries(legacy_v3_test PRIVATE torchlight_core)
    add_dependencies(legacy_v3_test legacy_v3_fixture)
    add_test(NAME gameplay_v3_migration COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/legacy_v3_process_test.py --probe $<TARGET_FILE:legacy_v3_test> --fixture ${LEGACY_V3_FIXTURE})

    add_executable(skills_test tests/skills_test.cpp)
    target_link_libraries(skills_test PRIVATE torchlight_core)
    target_compile_options(skills_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    add_test(NAME skills_runtime COMMAND skills_test)
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_skills_runtime COMMAND skills_test "${TORCHLIGHT_GAME_DIR}/pak.zip")
    endif()

    add_executable(economy_probe tests/economy_probe.cpp)
    target_link_libraries(economy_probe PRIVATE torchlight_core)
    if(TORCHLIGHT_ORIGINAL)
        add_test(NAME original_economy_comparison COMMAND ${TORCHLIGHT_REFERENCE_PYTHON}
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_economy.py --original ${TORCHLIGHT_ORIGINAL} --probe $<TARGET_FILE:economy_probe>)
        set_tests_properties(original_economy_comparison PROPERTIES TIMEOUT 120 SKIP_RETURN_CODE 77)
    endif()

    add_executable(quests_test tests/quests_test.cpp)
    target_link_libraries(quests_test PRIVATE torchlight_core)
    add_test(NAME quest_requirements COMMAND quests_test)
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_quest_controllers COMMAND quests_test "${TORCHLIGHT_GAME_DIR}/pak.zip")
    endif()

    add_executable(merchant_test tests/merchant_test.cpp)
    target_link_libraries(merchant_test PRIVATE torchlight_core)
    add_test(NAME merchant_prices COMMAND merchant_test)
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_merchant_purchases COMMAND merchant_test "${TORCHLIGHT_GAME_DIR}/pak.zip")
    endif()

    add_executable(service_fixture tests/service_fixture.cpp)
    target_link_libraries(service_fixture PRIVATE torchlight_core)
    if(TARGET application_scenario_probe AND TORCHLIGHT_GAME_DIR)
        add_test(NAME application_services_render COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/application_services_test.py
            --probe $<TARGET_FILE:application_scenario_probe> --fixture $<TARGET_FILE:service_fixture>
            --game-dir ${TORCHLIGHT_GAME_DIR} --output-dir ${CMAKE_CURRENT_BINARY_DIR}/scenario-evidence
            --timeout-scale ${TORCHLIGHT_TEST_TIMEOUT_SCALE})
        set_tests_properties(application_services_render PROPERTIES TIMEOUT 1200)
        if(TORCHLIGHT_PYTHON_ASAN_PRELOAD)
            set_tests_properties(application_services_render PROPERTIES ENVIRONMENT
                "LD_PRELOAD=${TORCHLIGHT_PYTHON_ASAN_PRELOAD};ASAN_OPTIONS=detect_leaks=0:halt_on_error=1;UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1")
        endif()
    endif()

    add_test(NAME gameplay_v4_migration COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/legacy_v4_process_test.py
        $<TARGET_FILE:consumable_test> ${CONSUMABLE_FIXTURE})

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        foreach(_new_target quests_test merchant_test economy_probe service_fixture)
            target_compile_options(${_new_target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
        endforeach()
    endif()

    add_executable(ui_image_clip_test tests/ui_image_clip_test.cpp)
    target_link_libraries(ui_image_clip_test PRIVATE torchlight_core)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(ui_image_clip_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    add_test(NAME ui_image_clip COMMAND ui_image_clip_test)

    if(TARGET gles_ui_probe)
        add_test(NAME ui_repairs_render COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/ui_repairs_render_test.py
            --probe $<TARGET_FILE:gles_ui_probe> --fixture ${HUD_FIXTURE})
        set_tests_properties(ui_repairs_render PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
    endif()

    set(HUD_INPUT_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/hud-input.pak.zip)
    add_custom_command(OUTPUT ${HUD_INPUT_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_hud_input_fixture.py ${HUD_INPUT_FIXTURE}
        DEPENDS tests/make_hud_input_fixture.py tests/make_hud_fixture.py VERBATIM)
    add_custom_target(hud_input_fixture DEPENDS ${HUD_INPUT_FIXTURE})
    add_executable(ui_hud_input_test tests/ui_hud_input_test.cpp)
    target_link_libraries(ui_hud_input_test PRIVATE torchlight_core)
    add_dependencies(ui_hud_input_test hud_input_fixture)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(ui_hud_input_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    add_test(NAME ui_hud_input COMMAND ui_hud_input_test ${HUD_INPUT_FIXTURE})
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_ui_hud_input COMMAND ui_hud_input_test "${TORCHLIGHT_GAME_DIR}/pak.zip" --original)
    endif()

    if(TARGET application_scenario_probe AND TORCHLIGHT_GAME_DIR)
        add_test(NAME paused_settings_render COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/paused_settings_test.py
            --probe $<TARGET_FILE:application_scenario_probe> --game-dir ${TORCHLIGHT_GAME_DIR}
            --output-dir ${CMAKE_CURRENT_BINARY_DIR}/ui-repair-evidence)
        set_tests_properties(paused_settings_render PROPERTIES TIMEOUT 300 SKIP_RETURN_CODE 77)
    endif()

    set(STATS_FIXTURE ${CMAKE_CURRENT_BINARY_DIR}/fixtures/character-stats.pak.zip)
    add_custom_command(OUTPUT ${STATS_FIXTURE}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/make_stats_fixture.py ${STATS_FIXTURE}
        DEPENDS tests/make_stats_fixture.py tests/make_attack_fixture.py tests/make_ai_cooldown_fixture.py tests/make_item_cycle_fixture.py VERBATIM)
    add_custom_target(character_stats_fixture DEPENDS ${STATS_FIXTURE})
    add_executable(character_stats_test tests/character_stats_test.cpp)
    target_link_libraries(character_stats_test PRIVATE torchlight_core)
    add_dependencies(character_stats_test character_stats_fixture)
    target_compile_options(character_stats_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    add_test(NAME character_stats_cycle COMMAND character_stats_test ${STATS_FIXTURE})
    add_test(NAME character_stats_process_save COMMAND character_stats_test --write ${STATS_FIXTURE} ${CMAKE_CURRENT_BINARY_DIR}/stats-process.otc)
    set_tests_properties(character_stats_process_save PROPERTIES FIXTURES_SETUP stats_process)
    add_test(NAME character_stats_process_load COMMAND character_stats_test --read ${STATS_FIXTURE} ${CMAKE_CURRENT_BINARY_DIR}/stats-process.otc)
    set_tests_properties(character_stats_process_load PROPERTIES FIXTURES_REQUIRED stats_process)
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_character_stats_resources COMMAND character_stats_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
    endif()

    add_executable(character_stats_probe tests/character_stats_probe.cpp)
    target_link_libraries(character_stats_probe PRIVATE torchlight_core)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(character_stats_probe PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    if(TORCHLIGHT_ORIGINAL)
        add_test(NAME original_character_stats_comparison COMMAND ${TORCHLIGHT_REFERENCE_PYTHON}
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_character_stats.py
            --original ${TORCHLIGHT_ORIGINAL} --probe $<TARGET_FILE:character_stats_probe>
            --output ${CMAKE_CURRENT_BINARY_DIR}/character-stats-original.json)
        set_tests_properties(original_character_stats_comparison PROPERTIES TIMEOUT 120 SKIP_RETURN_CODE 77)
    endif()

    add_executable(item_graph_test tests/item_graph_test.cpp)
    target_link_libraries(item_graph_test PRIVATE torchlight_core)
    target_compile_options(item_graph_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
    add_test(NAME item_graph_cycle COMMAND item_graph_test)

    add_executable(item_graph_probe tests/item_graph_probe.cpp)
    target_link_libraries(item_graph_probe PRIVATE torchlight_core)
    target_compile_options(item_graph_probe PRIVATE -Wall -Wextra -Wpedantic -Werror)
    if(TORCHLIGHT_ORIGINAL)
        add_test(NAME original_item_graph_comparison COMMAND ${TORCHLIGHT_REFERENCE_PYTHON}
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_item_graph.py
            --original ${TORCHLIGHT_ORIGINAL} --probe $<TARGET_FILE:item_graph_probe>
            --output ${CMAKE_CURRENT_BINARY_DIR}/item-graph-original.json)
        set_tests_properties(original_item_graph_comparison PROPERTIES TIMEOUT 120 SKIP_RETURN_CODE 77)
    endif()

    add_executable(gameplay_catalog_probe tests/gameplay_catalog_probe.cpp)
    target_link_libraries(gameplay_catalog_probe PRIVATE torchlight_core)
    target_compile_options(gameplay_catalog_probe PRIVATE -Wall -Wextra -Wpedantic -Werror)
    if(TORCHLIGHT_GAME_DIR)
        add_test(NAME original_gameplay_catalog COMMAND gameplay_catalog_probe
            "${TORCHLIGHT_GAME_DIR}/pak.zip" ${CMAKE_CURRENT_BINARY_DIR}/gameplay-catalog.json)
    endif()

    # Every registered test has an execution group. Labels describe dependency
    # and evidence, not fidelity: original_* resource tests are NOT ELF parity.
    get_property(_ot_tests DIRECTORY PROPERTY TESTS)
    foreach(_ot_test IN LISTS _ot_tests)
        if(_ot_test MATCHES "^original_.*_comparison$" OR _ot_test STREQUAL "original_level_entry_dispatch")
            set_tests_properties(${_ot_test} PROPERTIES LABELS "reference")
        elseif(_ot_test MATCHES "_render$" OR _ot_test STREQUAL "gles_render_smoke")
            set_tests_properties(${_ot_test} PROPERTIES LABELS "render")
        elseif(_ot_test MATCHES "^original_")
            set_tests_properties(${_ot_test} PROPERTIES LABELS "assets" TIMEOUT 240)
            if(_ot_test STREQUAL "original_random_levels")
                # ~216s alone; parallel core+render load pushed it past 240s.
                set_tests_properties(${_ot_test} PROPERTIES TIMEOUT 600)
            endif()
        elseif(_ot_test STREQUAL "gles_ui_headless" OR _ot_test STREQUAL "gles_menu_text")
            # Retain the historical portable UI runtime probe while making it
            # discoverable in render as well. Its skip is NOT a pass in check.py.
            set_tests_properties(${_ot_test} PROPERTIES LABELS "core;render")
        else()
            set_tests_properties(${_ot_test} PROPERTIES LABELS "core")
        endif()
        if(NOT TORCHLIGHT_TEST_TIMEOUT_SCALE STREQUAL "1")
            get_test_property(${_ot_test} TIMEOUT _ot_timeout)
            if(_ot_timeout AND NOT _ot_timeout STREQUAL "NOTFOUND")
                math(EXPR _ot_scaled_timeout "${_ot_timeout} * ${TORCHLIGHT_TEST_TIMEOUT_SCALE}")
                set_tests_properties(${_ot_test} PROPERTIES TIMEOUT ${_ot_scaled_timeout})
            endif()
        endif()
    endforeach()

endif()
