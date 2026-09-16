"""Real EGL surfaceless context; no mock GL functions or desktop claims."""
from __future__ import annotations
import ctypes as C
from contextlib import contextmanager
import os

class Unavailable(RuntimeError):
    """This environment cannot perform the requested graphics check."""

@contextmanager
def surfaceless(width: int = 1024, height: int = 768):
    if not (1 <= width <= 4096 and 1 <= height <= 4096):
        raise ValueError("invalid pbuffer size")
    os.environ.setdefault("LIBGL_ALWAYS_SOFTWARE", "1")
    try:
        egl = C.CDLL("libEGL.so.1")
    except OSError as exc:
        raise Unavailable(f"EGL runtime missing: {exc}") from exc
    ptr, integer, boolean = C.c_void_p, C.c_int, C.c_uint
    def fn(name, result, *args):
        f = getattr(egl, name)
        f.restype, f.argtypes = result, list(args)
        return f
    get = fn("eglGetProcAddress", ptr, C.c_char_p)
    address = get(b"eglGetPlatformDisplayEXT")
    if not address:
        raise Unavailable("EGL_EXT_platform_base entry point unavailable")
    display = C.CFUNCTYPE(ptr, C.c_uint, ptr, C.POINTER(integer))(address)(0x31DD, None, None)
    major, minor = integer(), integer()
    if not fn("eglInitialize", boolean, ptr, C.POINTER(integer), C.POINTER(integer))(display, C.byref(major), C.byref(minor)):
        raise Unavailable("cannot initialize EGL surfaceless platform")
    context = surface = None
    try:
        if not fn("eglBindAPI", boolean, C.c_uint)(0x30A0):
            raise Unavailable("EGL cannot bind GLES")
        attrs = (integer * 15)(0x3033, 1, 0x3040, 4, 0x3024, 8, 0x3023, 8,
                               0x3022, 8, 0x3021, 8, 0x3025, 16, 0x3038)
        config, count = ptr(), integer()
        if not fn("eglChooseConfig", boolean, ptr, C.POINTER(integer), C.POINTER(ptr), integer,
                  C.POINTER(integer))(display, attrs, C.byref(config), 1, C.byref(count)) or not count.value:
            raise Unavailable("RGBA8/depth16 GLES2 pbuffer configuration unavailable")
        surface = fn("eglCreatePbufferSurface", ptr, ptr, ptr, C.POINTER(integer))(
            display, config, (integer * 5)(0x3057, width, 0x3056, height, 0x3038))
        context = fn("eglCreateContext", ptr, ptr, ptr, ptr, C.POINTER(integer))(
            display, config, None, (integer * 3)(0x3098, 2, 0x3038))
        if not context or not surface or not fn("eglMakeCurrent", boolean, ptr, ptr, ptr, ptr)(display, surface, surface, context):
            raise Unavailable("cannot create/make current real GLES context")
        gs = C.CFUNCTYPE(C.c_char_p, C.c_uint)(get(b"glGetString"))
        def text(enum):
            value = gs(enum)
            return value.decode("utf-8", "replace") if value else "unknown"
        yield {"egl": f"{major.value}.{minor.value}", "renderer": text(0x1F01),
               "version": text(0x1F02), "vendor": text(0x1F00), "surface": "surfaceless-pbuffer",
               "window_test": False, "width": width, "height": height}
    finally:
        fn("eglMakeCurrent", boolean, ptr, ptr, ptr, ptr)(display, None, None, None)
        if context:
            fn("eglDestroyContext", boolean, ptr, ptr)(display, context)
        if surface:
            fn("eglDestroySurface", boolean, ptr, ptr)(display, surface)
        fn("eglTerminate", boolean, ptr)(display)
