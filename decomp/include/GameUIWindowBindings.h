#ifndef OTL_GAMEUI_WINDOW_BINDINGS_H
#define OTL_GAMEUI_WINDOW_BINDINGS_H
#include "GameUI.h"
namespace gameui_window_bindings_detail {
// Original mapToFunctions takes addresses of these 97 contiguous function IDs.
struct LayoutFunctions {
    unsigned char prefix[0x1790];
    ELayoutFunction values[97];
};
typedef char layout_function_size[sizeof(ELayoutFunction) == 4 ? 1 : -1];
typedef char layout_functions_offset[
    __builtin_offsetof(LayoutFunctions, values) == 0x1790 ? 1 : -1];
}
#endif
