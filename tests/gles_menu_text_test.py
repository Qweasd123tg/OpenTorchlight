#!/usr/bin/env python3
"""Real Mesa EGL menu/text readback; authored fixtures, not original frames."""
import argparse
import ctypes as C
import os


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--probe',required=True);p.add_argument('--fixture',required=True)
    p.add_argument('--font-fixture');p.add_argument('--font-only',action='store_true')
    a=p.parse_args();os.environ.setdefault('LIBGL_ALWAYS_SOFTWARE','1')
    try:egl=C.CDLL('libEGL.so.1')
    except OSError as e:print('NOT RUN: EGL runtime absent',e);return 77
    ptr=C.c_void_p;integer=C.c_int
    def fn(name,result,*args):
        f=getattr(egl,name);f.restype=result;f.argtypes=list(args);return f
    get=fn('eglGetProcAddress',ptr,C.c_char_p)
    address=get(b'eglGetPlatformDisplayEXT')
    if not address:print('NOT RUN: surfaceless display unavailable');return 77
    d=C.CFUNCTYPE(ptr,C.c_uint,ptr,C.POINTER(integer))(address)(0x31DD,None,None)
    major,minor=integer(),integer()
    if not fn('eglInitialize',C.c_uint,ptr,C.POINTER(integer),C.POINTER(integer))(d,C.byref(major),C.byref(minor)):
        print('NOT RUN: cannot initialize EGL');return 77
    surface=context=None
    try:
        assert fn('eglBindAPI',C.c_uint,C.c_uint)(0x30A0),'GLES API unavailable'
        attrs=(integer*15)(0x3033,1,0x3040,4,0x3024,8,0x3023,8,0x3022,8,0x3021,8,0x3025,16,0x3038)
        config,count=ptr(),integer()
        assert fn('eglChooseConfig',C.c_uint,ptr,C.POINTER(integer),C.POINTER(ptr),integer,C.POINTER(integer))(d,attrs,C.byref(config),1,C.byref(count)) and count.value
        surface=fn('eglCreatePbufferSurface',ptr,ptr,ptr,C.POINTER(integer))(d,config,(integer*5)(0x3057,1024,0x3056,768,0x3038))
        context=fn('eglCreateContext',ptr,ptr,ptr,ptr,C.POINTER(integer))(d,config,None,(integer*3)(0x3098,2,0x3038))
        make=fn('eglMakeCurrent',C.c_uint,ptr,ptr,ptr,ptr)
        assert surface and context and make(d,surface,surface,context),'EGL context unavailable'
        gs=C.CFUNCTYPE(C.c_char_p,C.c_uint)(get(b'glGetString'))
        print('Actual GL:',gs(0x1f01).decode(),gs(0x1f02).decode())
        lib=C.CDLL(a.probe);error=C.create_string_buffer(2048)
        def sample(im,w,h,x,y):return tuple(im[((h-1-y)*w+x)*4:((h-1-y)*w+x)*4+4])
        def bright(im,w,h,box):
            x0,y0,x1,y1=box
            return sum(sample(im,w,h,x,y)[0]>150 and sample(im,w,h,x,y)[1]>150
                       for y in range(y0,y1) for x in range(x0,x1))
        count_frames=0
        if not a.font_only:
            probe=lib.render_frontend_probe;probe.restype=integer
            probe.argtypes=[C.c_char_p,integer,integer,integer,C.POINTER(C.c_ubyte),C.c_char_p,C.c_uint]
            frames=[]
            for w,h,page in [(1024,768,0),(512,384,0),(1024,768,1),(1024,768,2),(1024,768,3),(1024,768,4)]:
                pixels=(C.c_ubyte*(w*h*4))()
                if probe(os.fsencode(a.fixture),w,h,page,pixels,error,len(error)):raise RuntimeError(error.value.decode())
                im=bytes(pixels);frames.append(im);count_frames+=1
                if page==0 and w==1024:
                    hover=sample(im,w,h,220,255)
                    normal=sample(im,w,h,220,435)
                    disabled=sample(im,w,h,220,375)
                    settings=sample(im,w,h,620,255)
                    assert hover[1]>180 and hover[0]<20,('hover skin',hover)
                    assert normal[0]>180 and normal[1]<20,('normal skin',normal)
                    assert 100<=disabled[0]<=120 and disabled[0]==disabled[1]==disabled[2],('disabled skin',disabled)
                    assert settings[0]>180 and settings[1]<20,('settings skin',settings)
                    assert bright(im,w,h,(470,550,790,574))>10,'resource CopyrightInfo pixels missing'
                    assert bright(im,w,h,(470,620,790,644))>10,'StaticTextOutline label dropped'
                if page==2:
                    assert bright(im,w,h,(386,130,638,170))>10,'Options resource title pixels missing'
                if page==3:
                    assert bright(im,w,h,(100,182,310,200))>10,'saved name pixels missing'
                if page==4:
                    # Authored Checkbox look puts labels past the box
                    # (x+w+5, LeftAligned, degenerate wrap): the look-area clip
                    # must start at the text top, not below it, or labels vanish;
                    # forced centring would push them ~200px right of the box.
                    assert bright(im,w,h,(441,160,560,200))>10,'settings checkbox label dropped'
                    assert bright(im,w,h,(441,210,560,250))>10,'second settings checkbox label dropped'
                    assert bright(im,w,h,(600,160,760,200))==0,'settings checkbox label misaligned'
            assert frames[0]!=frames[2]!=frames[3]!=frames[4]!=frames[5],'menus rendered identically'
            print('6 authored resource menu frames passed: labels, skin states, create, pause, load, settings, resize')
        if a.font_fixture:
            probe=lib.render_font_sequence_probe;probe.restype=integer
            probe.argtypes=[C.c_char_p,integer,C.POINTER(C.c_ubyte),C.c_char_p,C.c_uint]
            frames=[];counts=[]
            for step in range(8):
                w,h=(512,384) if step==3 else (1024,768)
                pixels=(C.c_ubyte*(w*h*4))()
                if probe(os.fsencode(a.font_fixture),step,pixels,error,len(error)):raise RuntimeError(error.value.decode())
                im=bytes(pixels);frames.append(im);count_frames+=1
                n=bright(im,w,h,(40,20,120,100));counts.append(n)
                assert n>0,('resource glyph atlas not uploaded',step,n)
                if step==5:
                    assert bright(im,w,h,(40,20,80,44))>0 and bright(im,w,h,(40,44,80,70))>0,'multiline text collapsed'
                if step==6:
                    inside=bright(im,w,h,(44,25,52,35))
                    assert n==inside and inside>0,('glyph escaped parent clip',n,inside)
                if step==7:
                    for y in (20,44,68):assert bright(im,w,h,(40,y,60,y+24))>0,'word wrapping failed'
            assert counts[1]>counts[0],('new glyph B was not uploaded',counts)
            assert counts[2]<counts[0],('UTF8 Π decoded as individual bytes',counts)
            assert 0<counts[3]<counts[1],('resize did not invalidate atlas',counts)
            assert frames[4]==frames[1],'font resize roundtrip changed the framebuffer'
            print('8 real FreeType sequence frames passed; bright-pixel counts:',counts)
        print('PASS:',count_frames,'actual GLES frames; no original pak, CEGUI or Wayland parity claim')
    finally:
        fn('eglMakeCurrent',C.c_uint,ptr,ptr,ptr,ptr)(d,None,None,None)
        if context:fn('eglDestroyContext',C.c_uint,ptr,ptr)(d,context)
        if surface:fn('eglDestroySurface',C.c_uint,ptr,ptr)(d,surface)
        fn('eglTerminate',C.c_uint,ptr)(d)
    return 0
if __name__=='__main__':raise SystemExit(main())
