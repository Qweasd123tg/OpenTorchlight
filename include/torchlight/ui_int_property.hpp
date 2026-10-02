#pragma once
#include <cstddef>
#include <cstdint>

namespace torchlight {
// original-code: complete CDynamicPropertyFile::GetInt @0xc6e440 reads
// pointer64 begin/end (+0x40/+0x48), then one indexed int32 or fallback -1.
// The caller owns a stable, readable table throughout the generated call.
// This evaluated port view supplies its own indices; they are not native
// settings registration IDs. See research/generated-settings-int.md.
// Empty tables may use nullptr. Nonempty null tables and unrepresentable
// synthetic pointer64 bounds are rejected before original operations execute.
[[nodiscard]] std::int32_t ui_int_property(const std::int32_t* values,
                                         std::size_t count, std::uint32_t index);
} // namespace torchlight
