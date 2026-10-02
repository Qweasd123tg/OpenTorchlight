add_test(NAME recovery_codegen COMMAND ${Python3_EXECUTABLE}
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/recovery_codegen_test.py")
add_test(NAME recovery_generated_current COMMAND ${Python3_EXECUTABLE}
    "${CMAKE_CURRENT_SOURCE_DIR}/tools/generate_recovered.py"
    --out-dir "${TORCHLIGHT_RECOVERED_DIR}" --check
    --report "${CMAKE_CURRENT_BINARY_DIR}/recovery-current.json")
set_tests_properties(recovery_codegen recovery_generated_current PROPERTIES LABELS "core" TIMEOUT 30)
add_test(NAME pcode_analysis COMMAND ${Python3_EXECUTABLE}
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/pcode_analysis_test.py")
set_tests_properties(pcode_analysis PROPERTIES LABELS "core" TIMEOUT 30)
if(TORCHLIGHT_ENABLE_GHIDRA_PROBES)
    if(NOT TORCHLIGHT_ORIGINAL)
        message(FATAL_ERROR "Ghidra probes require TORCHLIGHT_ORIGINAL and a prepared pinned tool/project")
    endif()
    add_test(NAME original_ghidra_pcode_calibration COMMAND ${Python3_EXECUTABLE}
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/ghidra_probe_process.py"
        --original "${TORCHLIGHT_ORIGINAL}"
        --reference-python "${TORCHLIGHT_REFERENCE_PYTHON}"
        --output-dir "${CMAKE_CURRENT_BINARY_DIR}/pcode-calibration")
    set_tests_properties(original_ghidra_pcode_calibration PROPERTIES LABELS "reference" TIMEOUT 900)
endif()
if(TORCHLIGHT_ORIGINAL)
    add_test(NAME original_recovery_contracts COMMAND ${Python3_EXECUTABLE}
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/generate_recovered.py"
        --original "${TORCHLIGHT_ORIGINAL}" --out-dir "${TORCHLIGHT_RECOVERED_DIR}" --check
        --report "${CMAKE_CURRENT_BINARY_DIR}/recovery-original.json")
    set_tests_properties(original_recovery_contracts PROPERTIES LABELS "reference" TIMEOUT 60)
endif()
# Use CMake's existing test registration, not a second hand-maintained game
# checklist. Labels carry execution/evidence boundaries, never function closure.
get_property(_recovery_registered DIRECTORY PROPERTY TESTS)
set(_recovery_checks)
foreach(_test IN LISTS _recovery_registered)
    get_test_property(${_test} LABELS _labels)
    if(("core" IN_LIST _labels OR "assets" IN_LIST _labels OR "reference" IN_LIST _labels)
            AND NOT "render" IN_LIST _labels AND NOT "desktop" IN_LIST _labels
            AND NOT "ui-integration" IN_LIST _labels)
        list(APPEND _recovery_checks ${_test})
    endif()
endforeach()
list(SORT _recovery_checks)
# All configured CPU executables/shared probes are included: Python tests can
# hide helper dependencies. In --recover, render/desktop are configured OFF.
# Their Ninja dependencies also materialize authored fixture archives. No game
# process, GUI click, frame scenario or performance run is part of this target.
get_property(_recovery_targets DIRECTORY PROPERTY BUILDSYSTEM_TARGETS)
set(_recovery_consumers torchlight_recovered_code torchlight_core)
foreach(_target IN LISTS _recovery_targets)
    get_target_property(_type ${_target} TYPE)
    if(_type STREQUAL "EXECUTABLE" OR _type STREQUAL "SHARED_LIBRARY" OR _type STREQUAL "MODULE_LIBRARY")
        list(APPEND _recovery_consumers ${_target})
    endif()
endforeach()
add_custom_target(torchlight_recovery_gates DEPENDS ${_recovery_consumers})
string(REPLACE ";" "\", \"" _recovery_checks_json "${_recovery_checks}")
file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/recovery-plan.json" CONTENT
    "{\"schema\":2,\"kind\":\"reviewed-recovery-chain\",\"scope\":\"registered-cpu-resource-reference\",\"build_target\":\"torchlight_recovery_gates\",\"generated_dir\":\"generated/recovered/torchlight/recovered\",\"required_tests\":[\"${_recovery_checks_json}\"]}\n")
