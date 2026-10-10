# Source from Bash, from any working directory.
OTL_HANDOFF_ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
export OTL_DECOMP_CACHE="$OTL_HANDOFF_ROOT/toolchain"
export TORCHLIGHT_ELF="$OTL_HANDOFF_ROOT/inputs/Torchlight.bin.x86_64"
export TORCHLIGHT_GAME_DIR="$OTL_HANDOFF_ROOT/inputs"
export OTL_ORIGINAL_DISASM=tu
export OTL_JOBS=2 OTL_COMPARE_JOBS=2 OTL_BUILD_JOBS=2 OTL_SELFTEST_JOBS=2
export PYTHONUNBUFFERED=1
