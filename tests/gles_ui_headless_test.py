#!/usr/bin/env python3
"""Real Mesa EGL surfaceless render/readback. NOT Wayland or a full desktop test.
The isolated probe uses test-only GLES ABI declarations, no emulated GL functions.
"""
import argparse,ctypes as C,os,sys
from pathlib import Path

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe',required=True);parser.add_argument('--fixture',required=True)
    parser.add_argument('--hud-fixture',required=True)
    parser.add_argument('--output',type=Path)
    a=parser.parse_args();os.environ.setdefault('LIBGL_ALWAYS_SOFTWARE','1')
    try:e=C.CDLL('libEGL.so.1')
    except OSError as exc:print('SKIP: EGL runtime absent:',exc);return 77
    def function(name,result,*args):
        f=getattr(e,name);f.restype=result;f.argtypes=list(args);return f
    ptr=C.c_void_p;integer=C.c_int
    get=function('eglGetProcAddress',ptr,C.c_char_p)
    address=get(b'eglGetPlatformDisplayEXT')
    if not address:print('SKIP: no surfaceless display API');return 77
    display=C.CFUNCTYPE(ptr,C.c_uint,ptr,C.POINTER(integer))(address)(0x31DD,None,None)
    init=function('eglInitialize',C.c_uint,ptr,C.POINTER(integer),C.POINTER(integer))
    major,minor=integer(),integer()
    if not init(display,C.byref(major),C.byref(minor)):print('SKIP: cannot initialize EGL surfaceless');return 77
    terminate=function('eglTerminate',C.c_uint,ptr)
    surface=context=None
    try:
        if not function('eglBindAPI',C.c_uint,C.c_uint)(0x30A0):raise RuntimeError('eglBindAPI GLES failed')
        attributes=(integer*15)(0x3033,1,0x3040,4,0x3024,8,0x3023,8,0x3022,8,0x3021,8,0x3025,16,0x3038)
        config,count=ptr(),integer()
        choose=function('eglChooseConfig',C.c_uint,ptr,C.POINTER(integer),C.POINTER(ptr),integer,C.POINTER(integer))
        if not choose(display,attributes,C.byref(config),1,C.byref(count)) or not count.value:raise RuntimeError('no pbuffer config')
        create=function('eglCreatePbufferSurface',ptr,ptr,ptr,C.POINTER(integer))
        surface=create(display,config,(integer*5)(0x3057,1024,0x3056,768,0x3038))
        context=function('eglCreateContext',ptr,ptr,ptr,ptr,C.POINTER(integer))(display,config,None,(integer*3)(0x3098,2,0x3038))
        make=function('eglMakeCurrent',C.c_uint,ptr,ptr,ptr,ptr)
        if not surface or not context or not make(display,surface,surface,context):raise RuntimeError('EGL context creation failed')
        getstr=C.CFUNCTYPE(C.c_char_p,C.c_uint)(get(b'glGetString'))
        print('Actual GL renderer:',getstr(0x1F01).decode(),'version:',getstr(0x1F02).decode())
        probe=C.CDLL(a.probe).render_frontend_probe;probe.restype=integer
        probe.argtypes=[C.c_char_p,integer,integer,integer,C.POINTER(C.c_ubyte),C.c_char_p,C.c_uint]
        results=[]
        for w,h,page in [(1024,768,0),(512,384,0),(1024,768,1),(1024,768,2)]:
            pixels=(C.c_ubyte*(w*h*4))();error=C.create_string_buffer(2048)
            if probe(os.fsencode(a.fixture),w,h,page,pixels,error,len(error)):raise RuntimeError(error.value.decode())
            image=bytes(pixels)
            if len(set(image))<12:raise RuntimeError('blank/corrupt rendered UI')
            # The main-page authored imageset has a 2x2 orange/blue background;
            # sample away from text/buttons, including resized-coordinate mapping.
            # CEGUI-direct mapping (no letterbox): at native size the full image
            # shows, so the bottom corner is solid blue. The menu background
            # scales by YRATIO (original CMainMenu::createMenus call), so at
            # 512x384 it still covers the viewport and the corner stays solid
            # blue instead of landing in a blend zone.
            if page==0:
                def pixel(x,y):return tuple(image[((h-1-y)*w+x)*4:((h-1-y)*w+x)*4+4])
                top=pixel(w-10,20);bottom=pixel(w-10,h-10)
                assert top[0]>200 and top[2]<40,(top,'atlas top/orientation wrong')
                assert bottom[2]>200 and bottom[0]<40,(bottom,'atlas bottom/orientation wrong')
            results.append(image)
            if a.output and w==1024 and page==0:
                # PPM is only a local test artifact, no dependency on imaging packages.
                rows=[image[y*w*4:(y+1)*w*4] for y in range(h-1,-1,-1)]
                rgb=b''.join(bytes(row[i:i+3]) for row in rows for i in range(0,len(row),4))
                a.output.write_bytes(f'P6\n{w} {h}\n255\n'.encode()+rgb)
        assert results[0]!=results[2] and results[2]!=results[3],'page transitions render identical images'
        hud=C.CDLL(a.probe).render_hud_probe
        hud.restype=integer
        hud.argtypes=[C.c_char_p,integer,integer,C.c_float,C.c_float,C.c_float,
                      C.POINTER(C.c_ubyte),C.c_char_p,C.c_uint]
        w,h=1024,768
        def hud_frame(health,mana,xp):
            pixels=(C.c_ubyte*(w*h*4))()
            if hud(os.fsencode(a.hud_fixture),w,h,health,mana,xp,pixels,error,len(error)):
                raise RuntimeError(error.value.decode())
            return bytes(pixels)
        def sample(image,x,y):return tuple(image[((h-1-y)*w+x)*4:((h-1-y)*w+x)*4+4])
        half=hud_frame(0.5,0.5,0.5)
        assert sample(half,15,135)[0]>200 and sample(half,15,135)[2]<60,(sample(half,15,135),'health fill bottom')
        assert sample(half,15,105)[0]<60,(sample(half,15,105),'health empty top')
        assert sample(half,35,135)[2]>200 and sample(half,35,135)[0]<60,(sample(half,35,135),'mana fill bottom')
        assert sample(half,15,152)[0]>200 and sample(half,15,152)[2]<60,(sample(half,15,152),'xp fill left')
        assert sample(half,45,152)[0]<60,(sample(half,45,152),'xp empty right')
        quarter=hud_frame(0.25,1.0,0.0)
        assert sample(quarter,15,135)[0]>200 and sample(quarter,15,105)[0]<60,(sample(quarter,15,105),'health quarter anchor')
        assert sample(quarter,35,105)[2]>200 and sample(quarter,35,135)[2]>200,(sample(quarter,35,135),'mana full')
        assert sample(quarter,15,152)[0]<60,(sample(quarter,15,152),'zero xp')
        print('4 real GLES UI frames and 2 HUD bar frames passed: atlas crop/orientation, resize, '
              'create, pause, original bottomhud geometry, bar fractions. No original assets or Wayland used.')
    finally:
        function('eglMakeCurrent',C.c_uint,ptr,ptr,ptr,ptr)(display,None,None,None)
        if context:function('eglDestroyContext',C.c_uint,ptr,ptr)(display,context)
        if surface:function('eglDestroySurface',C.c_uint,ptr,ptr)(display,surface)
        terminate(display)
    return 0
if __name__=='__main__':raise SystemExit(main())
