# Reviewed source data -> production C++ -> existing consumers. No guessed ABI.
find_package(Python3 REQUIRED COMPONENTS Interpreter)
set(TORCHLIGHT_RECOVERY_MANIFEST "${CMAKE_CURRENT_SOURCE_DIR}/research/recovery-contracts.json")
set(TORCHLIGHT_RECOVERED_INCLUDE "${CMAKE_CURRENT_BINARY_DIR}/generated/recovered")
set(TORCHLIGHT_RECOVERED_DIR "${TORCHLIGHT_RECOVERED_INCLUDE}/torchlight/recovered")
set(TORCHLIGHT_RECOVERED_HEADERS
    "${TORCHLIGHT_RECOVERED_DIR}/ui_bindings.hpp"
    "${TORCHLIGHT_RECOVERED_DIR}/mwc_float.hpp")
set(_recovery_original_args)
set(_recovery_original_dependencies)
if(TORCHLIGHT_ORIGINAL)
    list(APPEND _recovery_original_args --original "${TORCHLIGHT_ORIGINAL}")
    list(APPEND _recovery_original_dependencies "${TORCHLIGHT_ORIGINAL}")
endif()
add_custom_command(OUTPUT ${TORCHLIGHT_RECOVERED_HEADERS}
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/tools/generate_recovered.py"
        --manifest "${TORCHLIGHT_RECOVERY_MANIFEST}" --out-dir "${TORCHLIGHT_RECOVERED_DIR}"
        --report "${CMAKE_CURRENT_BINARY_DIR}/recovered-code.json" ${_recovery_original_args}
    DEPENDS "${TORCHLIGHT_RECOVERY_MANIFEST}"
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/generate_recovered.py"
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/original.py"
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/audit_original.py"
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/automation_state.py"
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/recovery_templates/ui_bindings.hpp.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/recovery_templates/mwc_float.hpp.in"
        ${_recovery_original_dependencies}
    VERBATIM)
add_custom_target(torchlight_recovered_code DEPENDS ${TORCHLIGHT_RECOVERED_HEADERS})
add_dependencies(torchlight_core torchlight_recovered_code)
target_sources(torchlight_core PRIVATE ${TORCHLIGHT_RECOVERED_HEADERS})
target_include_directories(torchlight_core PRIVATE "${TORCHLIGHT_RECOVERED_INCLUDE}")
