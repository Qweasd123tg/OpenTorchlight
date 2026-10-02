# Accepted raw operations -> compiled bodies -> checked production state owners.
# Builds need no Ghidra or proprietary input. Native reference gates separately
# verify the accepted instruction bytes against the pinned external ELF.
set(TORCHLIGHT_LIFTED_UI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/research/lifted-ui")
set(TORCHLIGHT_LIFTED_INCLUDE "${CMAKE_CURRENT_BINARY_DIR}/generated/lifted")
set(TORCHLIGHT_LIFTED_HEADER "${TORCHLIGHT_LIFTED_INCLUDE}/torchlight/generated/ui_state_queries.hpp")
set(TORCHLIGHT_LIFTED_INPUTS
    "${TORCHLIGHT_LIFTED_UI_DIR}/00a83e70.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00a828f0.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00a82900.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00a84d20.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00a84d30.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00c2b9c0.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00c2b700.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00c33490.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00c6e410.json")
add_custom_command(OUTPUT "${TORCHLIGHT_LIFTED_HEADER}"
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/tools/lift_pcode.py"
        ${TORCHLIGHT_LIFTED_INPUTS}
        --abi "${TORCHLIGHT_LIFTED_UI_DIR}/abi.json"
        --out "${TORCHLIGHT_LIFTED_HEADER}"
        --report "${CMAKE_CURRENT_BINARY_DIR}/lifted-ui-code.json"
    DEPENDS ${TORCHLIGHT_LIFTED_INPUTS} "${TORCHLIGHT_LIFTED_UI_DIR}/abi.json"
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/lift_pcode.py"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/torchlight/pcode_runtime.hpp"
    VERBATIM)
add_custom_target(torchlight_lifted_code DEPENDS "${TORCHLIGHT_LIFTED_HEADER}")
add_dependencies(torchlight_core torchlight_lifted_code)
target_sources(torchlight_core PRIVATE "${TORCHLIGHT_LIFTED_HEADER}")
target_include_directories(torchlight_core PRIVATE "${TORCHLIGHT_LIFTED_INCLUDE}")
