cmake_minimum_required(VERSION 3.16)
project(torchlight_recovery LANGUAGES C CXX)

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)

add_library(torchlight_core STATIC
    src/actor_motion.cpp
    src/adm_document.cpp
    src/collision_scene.cpp
    src/combat.cpp
    src/dds_texture.cpp
    src/entity_world.cpp
    src/input_state.cpp
    src/key_manager.cpp
    src/level_scene.cpp
    src/level_transition.cpp
    src/logic_runtime.cpp
    src/master_resource_index.cpp
    src/mouse_manager.cpp
    src/navigation_grid.cpp
    src/ogre_material.cpp
    src/ogre_mesh.cpp
    src/pak_archive.cpp
    src/pathfinder_rules.cpp
    src/pointer_movement.cpp
    src/player.cpp
    src/png_texture.cpp
    src/random_level.cpp
    src/randomizer.cpp
    src/resource_config.cpp
    src/scene_geometry.cpp
    src/spawn_class.cpp
    src/unit_definition.cpp
    src/unit_type.cpp)
target_include_directories(torchlight_core PUBLIC include)
target_compile_features(torchlight_core PUBLIC cxx_std_17)
target_link_libraries(torchlight_core PUBLIC ZLIB::ZLIB PNG::PNG)
set_target_properties(torchlight_core PROPERTIES POSITION_INDEPENDENT_CODE ON)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(torchlight_core PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(torchlight_bootstrap src/bootstrap_main.cpp)
target_link_libraries(torchlight_bootstrap PRIVATE torchlight_core)
add_executable(torchlight_level_rules_dump tools/level_rules_dump.cpp)
target_link_libraries(torchlight_level_rules_dump PRIVATE torchlight_core)
add_executable(torchlight_player_units_dump tools/player_units_dump.cpp)
target_link_libraries(torchlight_player_units_dump PRIVATE torchlight_core)

if(UNIX AND NOT ANDROID)
    find_package(PkgConfig)
    if(PkgConfig_FOUND)
        pkg_check_modules(EGL IMPORTED_TARGET egl)
        pkg_check_modules(GLES2 IMPORTED_TARGET glesv2)
        pkg_check_modules(WAYLAND_CLIENT IMPORTED_TARGET wayland-client)
        pkg_check_modules(WAYLAND_EGL IMPORTED_TARGET wayland-egl)
    endif()
    find_program(WAYLAND_SCANNER wayland-scanner)
    set(XDG_SHELL_XML /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml)
    if(EGL_FOUND AND GLES2_FOUND AND WAYLAND_CLIENT_FOUND AND WAYLAND_EGL_FOUND AND
       WAYLAND_SCANNER AND EXISTS ${XDG_SHELL_XML})
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
        add_library(torchlight_gles2 STATIC src/gles_scene_renderer.cpp)
        target_link_libraries(torchlight_gles2 PUBLIC torchlight_core PkgConfig::GLES2)
        target_compile_features(torchlight_gles2 PUBLIC cxx_std_17)
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(torchlight_gles2 PRIVATE -Wall -Wextra -Wpedantic -Werror)
        endif()
        add_executable(torchlight_desktop src/linux_desktop_main.cpp)
        target_link_libraries(torchlight_desktop PRIVATE
            torchlight_gles2 torchlight_xdg_shell PkgConfig::WAYLAND_EGL PkgConfig::EGL)
        target_compile_features(torchlight_desktop PRIVATE cxx_std_17)
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(torchlight_desktop PRIVATE -Wall -Wextra -Wpedantic -Werror)
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
    else()
        message(STATUS "Desktop shell disabled: Wayland, EGL, GLES2, or xdg-shell files are missing")
    endif()
endif()

include(CTest)
set(TORCHLIGHT_ORIGINAL "" CACHE FILEPATH "Original Linux executable for behavioral comparison")
if(BUILD_TESTING AND NOT CMAKE_CROSSCOMPILING)
    add_library(input_comparison SHARED tests/input_c_api.cpp)
    target_link_libraries(input_comparison PRIVATE torchlight_core)
    add_library(action_comparison SHARED tests/action_c_api.cpp)
    target_link_libraries(action_comparison PRIVATE torchlight_core)
    add_library(randomizer_comparison SHARED tests/randomizer_c_api.cpp)
    target_link_libraries(randomizer_comparison PRIVATE torchlight_core)
    add_library(pathfinder_comparison SHARED tests/pathfinder_c_api.cpp)
    target_link_libraries(pathfinder_comparison PRIVATE torchlight_core)
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
    add_executable(unit_type_test tests/unit_type_test.cpp)
    target_link_libraries(unit_type_test PRIVATE torchlight_core)
    add_executable(combat_test tests/combat_test.cpp)
    target_link_libraries(combat_test PRIVATE torchlight_core)
    add_executable(level_transition_test tests/level_transition_test.cpp)
    target_link_libraries(level_transition_test PRIVATE torchlight_core)
    if(TORCHLIGHT_ORIGINAL)
        find_package(Python3 REQUIRED COMPONENTS Interpreter)
        add_test(NAME original_input_comparison
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_original_input.py
                --original ${TORCHLIGHT_ORIGINAL}
                --library $<TARGET_FILE:input_comparison>)
        set_tests_properties(original_input_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
        add_test(NAME original_action_comparison
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_original_action.py
                --original ${TORCHLIGHT_ORIGINAL}
                --library $<TARGET_FILE:action_comparison>)
        set_tests_properties(original_action_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
        add_test(NAME original_randomizer_comparison
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_original_random.py
                --original ${TORCHLIGHT_ORIGINAL}
                --library $<TARGET_FILE:randomizer_comparison>)
        set_tests_properties(original_randomizer_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
        add_test(NAME original_pathfinder_comparison
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/compare_original_pathfinder.py
                --original ${TORCHLIGHT_ORIGINAL}
                --library $<TARGET_FILE:pathfinder_comparison>)
        set_tests_properties(original_pathfinder_comparison PROPERTIES TIMEOUT 60 SKIP_RETURN_CODE 77)
        get_filename_component(TORCHLIGHT_GAME_DIR "${TORCHLIGHT_ORIGINAL}" DIRECTORY)
        add_test(NAME original_pak_archive
            COMMAND pak_archive_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME actor_motion COMMAND actor_motion_test)
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
        add_test(NAME original_unit_types
            COMMAND unit_type_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_combat
            COMMAND combat_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_level_transitions
            COMMAND level_transition_test --original "${TORCHLIGHT_GAME_DIR}/pak.zip")
        add_test(NAME original_data_bootstrap
            COMMAND torchlight_bootstrap "${TORCHLIGHT_GAME_DIR}")
        if(TARGET gles_render_smoke_test)
            add_test(NAME gles_render_smoke COMMAND gles_render_smoke_test)
            set_tests_properties(gles_render_smoke PROPERTIES
                TIMEOUT 30 ENVIRONMENT "EGL_PLATFORM=surfaceless")
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
    else()
        message(STATUS "Original comparison not configured: set TORCHLIGHT_ORIGINAL to run it")
    endif()
endif()
