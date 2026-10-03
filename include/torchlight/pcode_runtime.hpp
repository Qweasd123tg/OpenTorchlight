#pragma once

// Scalar execution of Ghidra raw p-code. Register offsets/widths come from the
// pinned x86:LE:64 language, not C++ object layouts. All memory is owner supplied.
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <stdexcept>

#if defined(__FAST_MATH__)
#error "raw p-code floating operations require IEEE NaN semantics (disable fast-math)"
#endif

namespace torchlight::pcode {
template<std::size_t N> class ByteState;
using RegisterFile = ByteState<8192>;
struct ImportCall {
    std::uint64_t caller, instruction;
    std::size_t pcode_index;
    std::uint64_t target;
};
struct RegisterRange { std::size_t offset, size; };
// The caller can collect this observed address for exact source export. A
// missing translated body is a tooling gap, never a guessed guest result.
class UntranslatedCallTarget final : public std::runtime_error {
public:
    const std::uint64_t target;
    explicit UntranslatedCallTarget(std::uint64_t value)
        : std::runtime_error("p-code CALLIND target outside exact compiled raw entries"), target(value) {}
};
struct Memory {
    virtual ~Memory() = default;
    virtual std::uint64_t read(std::uint64_t address, std::size_t width) = 0;
    virtual void write(std::uint64_t address, std::size_t width, std::uint64_t value) = 0;
    // Only an explicitly reviewed callsite may reach this boundary. Neither
    // bank aliases the caller's registers; unspecified imports never become stubs.
    virtual void invoke_import(const ImportCall&, const RegisterFile&, RegisterFile&) {
        throw std::runtime_error("p-code imported call has no production implementation");
    }
};

// An explicit adapter budget for the host's C++ call stack. This is not an
// original guest effect; every generated shared-machine entry uses one owner.
class CallDepth {
    std::size_t limit_, current_ = 0;
    friend class CallDepthGuard;
public:
    static constexpr std::size_t maximum_limit = 64;
    explicit CallDepth(std::size_t limit = maximum_limit) : limit_(limit) {
        if (!limit || limit > maximum_limit)
            throw std::runtime_error("p-code shared call-depth limit outside 1..64");
    }
    CallDepth(const CallDepth&) = delete;
    CallDepth& operator=(const CallDepth&) = delete;
    std::size_t limit() const noexcept { return limit_; }
    std::size_t current() const noexcept { return current_; }
};
class CallDepthGuard {
    CallDepth& depth_;
public:
    explicit CallDepthGuard(CallDepth& depth) : depth_(depth) {
        if (depth_.current_ >= depth_.limit_)
            throw std::runtime_error("p-code shared call-depth adapter budget exceeded");
        ++depth_.current_;
    }
    ~CallDepthGuard() { --depth_.current_; }
    CallDepthGuard(const CallDepthGuard&) = delete;
    CallDepthGuard& operator=(const CallDepthGuard&) = delete;
};

inline std::uint64_t mask(std::size_t width) {
    if (width == 0 || width > 8) throw std::runtime_error("p-code scalar width outside 1..8");
    return width == 8 ? UINT64_MAX : ((std::uint64_t{1} << (width * 8)) - 1);
}
template<std::size_t N> class ByteState {
    std::array<std::uint8_t, N> bytes_{};
    std::array<bool, N> initialized_{};
    std::array<bool, N> invalidated_{};
    void bounds(std::size_t offset, std::size_t width) const {
        if (!width || width > 8 || offset > N || width > N-offset)
            throw std::runtime_error("p-code byte-state bounds");
    }
public:
    void reset() noexcept { initialized_.fill(false); invalidated_.fill(false); }
    void invalidate(std::size_t offset, std::size_t width) {
        bounds(offset,width);
        for (std::size_t i=0; i<width; ++i) {
            initialized_[offset+i]=false;
            invalidated_[offset+i]=true;
        }
    }
    std::size_t initialized_count() const noexcept {
        std::size_t count=0;
        for (bool byte : initialized_) count += byte;
        return count;
    }
    bool initialized(std::size_t offset, std::size_t width) const {
        bounds(offset,width);
        for (std::size_t i=0; i<width; ++i) if (!initialized_[offset+i]) return false;
        return true;
    }
    std::uint64_t read(std::size_t offset, std::size_t width, const char* context="p-code") const {
        if (!initialized(offset,width)) throw std::runtime_error(context);
        std::uint64_t value=0;
        for (std::size_t i=0; i<width; ++i) value |= std::uint64_t{bytes_[offset+i]} << (i*8);
        return value;
    }
    void write(std::size_t offset, std::size_t width, std::uint64_t value) {
        bounds(offset,width);
        for (std::size_t i=0; i<width; ++i) {
            bytes_[offset+i]=static_cast<std::uint8_t>(value >> (i*8));
            initialized_[offset+i]=true;
            invalidated_[offset+i]=false;
        }
    }
    void merge_initialized(const ByteState& source) noexcept {
        for (std::size_t i=0; i<N; ++i) {
            if (source.invalidated_[i]) {
                initialized_[i]=false;
                invalidated_[i]=true;
            } else if (source.initialized_[i]) {
                bytes_[i]=source.bytes_[i];
                initialized_[i]=true;
                invalidated_[i]=false;
            }
        }
    }
};

inline std::uint64_t sign_extend(std::uint64_t value, std::size_t width) {
    value &= mask(width);
    const auto sign=std::uint64_t{1} << (width*8-1);
    return (value ^ sign) - sign;
}
inline bool signed_less(std::uint64_t a, std::uint64_t b, std::size_t width) {
    const auto m=mask(width);
    const auto sign=std::uint64_t{1} << (width*8-1);
    return ((a & m) ^ sign) < ((b & m) ^ sign);
}
inline bool carry(std::uint64_t a, std::uint64_t b, std::size_t width) {
    a &= mask(width); b &= mask(width);
    return b > mask(width)-a;
}
inline bool signed_carry(std::uint64_t a, std::uint64_t b, std::size_t width) {
    const auto m=mask(width); a &= m; b &= m;
    const auto sign=std::uint64_t{1} << (width*8-1);
    return ((~(a^b) & (a^(a+b))) & sign) != 0;
}
inline bool signed_borrow(std::uint64_t a, std::uint64_t b, std::size_t width) {
    const auto m=mask(width); a &= m; b &= m;
    const auto sign=std::uint64_t{1} << (width*8-1);
    return (((a^b) & (a^(a-b))) & sign) != 0;
}
inline std::uint64_t shift_left(std::uint64_t a, std::uint64_t count, std::size_t width) {
    const auto m=mask(width);
    return count >= width*8 ? 0 : (a << count) & m;
}
inline std::uint64_t shift_right(std::uint64_t a, std::uint64_t count, std::size_t width) {
    const auto m=mask(width);
    return count >= width*8 ? 0 : (a & m) >> count;
}
inline std::uint64_t shift_signed_right(std::uint64_t a, std::uint64_t count, std::size_t width) {
    const auto extended=sign_extend(a,width);
    const bool negative=(extended >> 63) != 0;
    if (count >= width*8) return negative ? mask(width) : 0;
    if (!count) return a & mask(width);
    return ((extended >> count) | (negative ? (UINT64_MAX << (64-count)) : 0)) & mask(width);
}
inline std::uint64_t subpiece(std::uint64_t a, std::uint64_t count) {
    return count >= 8 ? 0 : a >> (count*8);
}
inline unsigned popcount(std::uint64_t a) noexcept {
    unsigned count=0;
    while (a) { a &= a-1; ++count; }
    return count;
}
inline double floating(std::uint64_t bits, std::size_t width) {
    static_assert(sizeof(float)==4 && sizeof(double)==8);
    static_assert(std::numeric_limits<float>::is_iec559 && std::numeric_limits<double>::is_iec559);
    if (width==4) { const auto b=static_cast<std::uint32_t>(bits); float f; std::memcpy(&f,&b,4); return f; }
    if (width==8) { double d; std::memcpy(&d,&bits,8); return d; }
    throw std::runtime_error("p-code float width outside binary32/binary64");
}
// Scalar SSE MULSS/MULSD result-bit contract only (not universal FLOAT_MULT/x87).
// original-code: MULSS XMM0,[RSP+0xc] @0xa83e89/0xa83eb9 consumes
// ratio as left/destination, offset as right; native comparison confirms first
// NaN payload wins and invalid infinity*zero yields negative indefinite.
// MULSD follows the same scalar SSE bit rule, independently calibrated against
// the native instruction; no original production binary64 function is claimed.
// Use the actual operand precision, then store that precision before extracting
// its bits. In particular binary32 arithmetic never widens through floating().
// Host rounding mode/exception flags and original MXCSR are outside this helper's
// contract; no fast-math is allowed. Volatile forces the precision store even on
// targets with excess intermediate precision.
inline std::uint64_t float_multiply(std::uint64_t left, std::uint64_t right,
                                    std::size_t width) {
    static_assert(sizeof(float)==4 && sizeof(double)==8);
    static_assert(std::numeric_limits<float>::is_iec559 && std::numeric_limits<double>::is_iec559);
    if (width==4) {
        const auto a=static_cast<std::uint32_t>(left), b=static_cast<std::uint32_t>(right);
        const auto magnitude_a=a & UINT32_C(0x7fffffff), magnitude_b=b & UINT32_C(0x7fffffff);
        if (magnitude_a>UINT32_C(0x7f800000)) return a | UINT32_C(0x00400000);
        if (magnitude_b>UINT32_C(0x7f800000)) return b | UINT32_C(0x00400000);
        if ((magnitude_a==UINT32_C(0x7f800000) && magnitude_b==0) ||
            (magnitude_b==UINT32_C(0x7f800000) && magnitude_a==0)) return UINT32_C(0xffc00000);
        float x,y; std::memcpy(&x,&a,4); std::memcpy(&y,&b,4);
        volatile float stored=x*y;
        const float result=stored; std::uint32_t bits; std::memcpy(&bits,&result,4);
        return bits;
    }
    if (width==8) {
        const auto magnitude_a=left & UINT64_C(0x7fffffffffffffff), magnitude_b=right & UINT64_C(0x7fffffffffffffff);
        if (magnitude_a>UINT64_C(0x7ff0000000000000)) return left | UINT64_C(0x0008000000000000);
        if (magnitude_b>UINT64_C(0x7ff0000000000000)) return right | UINT64_C(0x0008000000000000);
        if ((magnitude_a==UINT64_C(0x7ff0000000000000) && magnitude_b==0) ||
            (magnitude_b==UINT64_C(0x7ff0000000000000) && magnitude_a==0)) return UINT64_C(0xfff8000000000000);
        double x,y; std::memcpy(&x,&left,8); std::memcpy(&y,&right,8);
        volatile double stored=x*y;
        const double result=stored; std::uint64_t bits; std::memcpy(&bits,&result,8);
        return bits;
    }
    throw std::runtime_error("p-code float width outside binary32/binary64");
}
inline void check_return(std::uint64_t target, std::uint64_t sentinel) {
    if (target != sentinel) throw std::runtime_error("p-code RETURN target differs from explicit sentinel");
}
template<std::size_t I, std::size_t O, std::size_t C>
inline void invoke_import(Memory& memory, RegisterFile& machine, const ImportCall& call,
                          std::uint64_t return_address,
                          const std::array<RegisterRange,I>& inputs,
                          const std::array<RegisterRange,O>& outputs,
                          const std::array<RegisterRange,C>& clobbers) {
    const auto stack=machine.read(0x20,8,"p-code import has uninitialized RSP");
    check_return(memory.read(stack,8),return_address);
    if (stack>UINT64_MAX-8) throw std::runtime_error("p-code imported RET overflows RSP");
    RegisterFile arguments, result;
    for (const auto& range : inputs)
        arguments.write(range.offset,range.size,
            machine.read(range.offset,range.size,"p-code import has uninitialized declared input"));
    memory.invoke_import(call,arguments,result);
    check_return(memory.read(stack,8),return_address);
    std::size_t output_bytes=0;
    for (const auto& range : outputs) {
        output_bytes += range.size;
        if (!result.initialized(range.offset,range.size))
            throw std::runtime_error("p-code import omitted a declared output");
    }
    if (result.initialized_count()!=output_bytes)
        throw std::runtime_error("p-code import initialized undeclared output bytes");
    // Publish only the declared effects after validation, never merge a callback
    // bank wholesale. Explicit invalidations propagate through generated callees.
    for (const auto& range : clobbers) machine.invalidate(range.offset,range.size);
    for (const auto& range : outputs)
        machine.write(range.offset,range.size,result.read(range.offset,range.size));
    // Raw CALL already pushed this slot. Reproduce the normal original RET's
    // RIP load and pop, rather than manufacturing a second call/return stack.
    machine.write(0x288,8,return_address);
    machine.write(0x20,8,stack+8);
}
} // namespace torchlight::pcode
