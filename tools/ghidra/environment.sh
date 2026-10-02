# Shared durable locations. Explicit caller overrides retain their old meaning.
# Generated tool/project/config files stay ignored; original ELF stays external.
ghidra_home="${GHIDRA_HOME:-$project_root/build-source-cache/ghidra/ghidra_12.1.3_PUBLIC}"
analysis_root="${TORCHLIGHT_GHIDRA_ROOT:-$project_root/build-ghidra}"
export XDG_CONFIG_HOME="$analysis_root/config"
export XDG_CACHE_HOME="$analysis_root/cache"
