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
    "${TORCHLIGHT_LIFTED_UI_DIR}/00b05e80.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00c2b9c0.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00c2b700.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00c33490.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00c6e410.json"
    "${TORCHLIGHT_LIFTED_UI_DIR}/00c6e440.json")
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

# Generic shared CPU/RAM backend. No per-function C++ ABI or field adapter is
# inferred here. It is calibrated separately; Application keeps reviewed bindings.
set(TORCHLIGHT_MACHINE_HEADER "${TORCHLIGHT_LIFTED_INCLUDE}/torchlight/generated/shared_machine.hpp")
add_custom_command(OUTPUT "${TORCHLIGHT_MACHINE_HEADER}"
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/tools/lift_pcode.py"
        ${TORCHLIGHT_LIFTED_INPUTS}
        --abi "${TORCHLIGHT_LIFTED_UI_DIR}/shared-machine.json"
        --out "${TORCHLIGHT_MACHINE_HEADER}"
        --report "${CMAKE_CURRENT_BINARY_DIR}/shared-machine-code.json"
    DEPENDS ${TORCHLIGHT_LIFTED_INPUTS} "${TORCHLIGHT_LIFTED_UI_DIR}/shared-machine.json"
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/lift_pcode.py"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/torchlight/pcode_runtime.hpp"
    VERBATIM)
add_custom_target(torchlight_machine_code DEPENDS "${TORCHLIGHT_MACHINE_HEADER}")

# Actual source virtual-call chains for generic backend calibration. These
# fixtures are not new Application bindings or whole-game acceptance claims.
set(TORCHLIGHT_INDIRECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/research/lifted-machine-fixtures")
set(TORCHLIGHT_INDIRECT_INPUTS)
foreach(entry 005a6cd0 005bb4a0 00a82ae0 00ae15f0 00ae1620 00bcca70 00bccaa0)
    list(APPEND TORCHLIGHT_INDIRECT_INPUTS "${TORCHLIGHT_INDIRECT_DIR}/${entry}.json")
endforeach()
set(TORCHLIGHT_INDIRECT_HEADER "${TORCHLIGHT_LIFTED_INCLUDE}/torchlight/generated/indirect_machine.hpp")
add_custom_command(OUTPUT "${TORCHLIGHT_INDIRECT_HEADER}"
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/tools/lift_pcode.py"
        ${TORCHLIGHT_INDIRECT_INPUTS}
        --abi "${TORCHLIGHT_LIFTED_UI_DIR}/shared-machine.json"
        --out "${TORCHLIGHT_INDIRECT_HEADER}"
        --report "${CMAKE_CURRENT_BINARY_DIR}/indirect-machine-code.json"
    DEPENDS ${TORCHLIGHT_INDIRECT_INPUTS} "${TORCHLIGHT_LIFTED_UI_DIR}/shared-machine.json"
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/lift_pcode.py"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/torchlight/pcode_runtime.hpp"
    VERBATIM)
add_custom_target(torchlight_indirect_machine_code DEPENDS "${TORCHLIGHT_INDIRECT_HEADER}")
