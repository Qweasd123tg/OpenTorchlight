add_test(NAME recovery_codegen COMMAND ${Python3_EXECUTABLE}
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/recovery_codegen_test.py")
add_test(NAME recovery_generated_current COMMAND ${Python3_EXECUTABLE}
    "${CMAKE_CURRENT_SOURCE_DIR}/tools/generate_recovered.py"
    --out-dir "${TORCHLIGHT_RECOVERED_DIR}" --check
    --report "${CMAKE_CURRENT_BINARY_DIR}/recovery-current.json")
set_tests_properties(recovery_codegen recovery_generated_current PROPERTIES LABELS "core" TIMEOUT 30)
if(TORCHLIGHT_ORIGINAL)
    add_test(NAME original_recovery_contracts COMMAND ${Python3_EXECUTABLE}
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/generate_recovered.py"
        --original "${TORCHLIGHT_ORIGINAL}" --out-dir "${TORCHLIGHT_RECOVERED_DIR}" --check
        --report "${CMAKE_CURRENT_BINARY_DIR}/recovery-original.json")
    set_tests_properties(original_recovery_contracts PROPERTIES LABELS "reference" TIMEOUT 60)
endif()
# Explicit build closure for these reviewed recipes and their production probes.
# Python/original-memory comparison tests have no hidden executable dependency.
add_custom_target(torchlight_recovery_gates DEPENDS
    torchlight_recovered_code ui_function_bindings_test randomizer_comparison
    ui_sound_test missile_motion_test mainmenu_presentation_test)
set(_recovery_checks recovery_codegen recovery_generated_current registry_sync
    ui_function_bindings original_ui_function_bindings original_ui_binding_comparison
    original_recovery_contracts original_randomizer_comparison
    ui_sound_contract original_ui_sound_contract missile_motion
    cegui_error_boundary original_cegui_mainmenu_contract)
string(REPLACE ";" "\", \"" _recovery_checks_json "${_recovery_checks}")
file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/recovery-plan.json" CONTENT
    "{\"schema\":1,\"kind\":\"reviewed-recovery-chain\",\"build_target\":\"torchlight_recovery_gates\",\"generated_dir\":\"generated/recovered/torchlight/recovered\",\"required_tests\":[\"${_recovery_checks_json}\"]}\n")
