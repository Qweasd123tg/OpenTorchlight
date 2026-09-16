#!/usr/bin/env python3
"""Explicit test-only ABI declarations for hosts without FreeType development files.
Uses an installed freetype-py binding to validate PUBLIC structure offsets.
Links the real FreeType runtime; defines no rasterizer/functions/stubs.
Not installed, auto-detected or used by the normal production build.
Prefer the official FreeType development package wherever available.
"""
import argparse
import ctypes as C
import json
from pathlib import Path
import freetype
from freetype import ft_structs as S


def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('output',type=Path)
    p.add_argument('--library',default='libfreetype.so.6');a=p.parse_args()
    a.output.mkdir(parents=True,exist_ok=True);(a.output/'freetype').mkdir(exist_ok=True)
    out=['#pragma once', '#include <stddef.h>', '#include <stdint.h>',
         'typedef long FT_Long; typedef unsigned long FT_ULong; typedef long FT_F26Dot6;',
         'typedef void *FT_Library;',
         'typedef struct FT_FaceRec_ *FT_Face; typedef struct FT_SizeRec_ *FT_Size;',
         'typedef struct FT_GlyphSlotRec_ *FT_GlyphSlot;',
         'typedef int FT_Render_Mode;',
         '#define FT_LOAD_DEFAULT 0', '#define FT_PIXEL_MODE_MONO 1',
         '#define FT_RENDER_MODE_NORMAL 0', '#define FT_RENDER_MODE_MONO 2']
    runtime=C.CDLL(a.library); handle=C.c_void_p()
    if runtime.FT_Init_FreeType(C.byref(handle)) != 0: raise RuntimeError('FreeType initialization failed')
    major,minor,patch=C.c_int(),C.c_int(),C.c_int()
    runtime.FT_Library_Version(handle,C.byref(major),C.byref(minor),C.byref(patch))
    runtime.FT_Done_FreeType(handle)
    version=(major.value,minor.value,patch.value)
    manifest={'kind':'test-only public ABI declarations; no implementations',
              'binding':str(Path(freetype.__file__).resolve()),'binding_runtime_version':freetype.version(),'linked_library':a.library,'runtime_version':version, 'structs':{}}
    def record(name,original,fields):
        out.append('struct '+name+' {');pos=0;offsets={}
        for field,typename in fields:
            desc=getattr(original,field)
            offset=desc.offset
            if offset>pos: out.append(f'  unsigned char pad_{pos}[{offset-pos}];')
            out.append(f'  {typename} {field};')
            offsets[field]=offset
            pos=offset+desc.size
        out.append('};')
        for field,offset in offsets.items():
            out.append(f'static_assert(offsetof({name},{field})=={offset},"{name}.{field} ABI");')
        manifest['structs'][name]={'binding_size':C.sizeof(original),'offsets':offsets}
    record('FT_Vector',S.FT_Vector,[('x','long'),('y','long')])
    record('FT_Bitmap',S.FT_Bitmap,[('rows','unsigned int'),('width','unsigned int'),('pitch','int'),
                                 ('buffer','unsigned char *'),('num_grays','unsigned short'),
                                 ('pixel_mode','unsigned char'),('palette_mode','unsigned char'),('palette','void *')])
    record('FT_Size_Metrics',S.FT_Size_Metrics,[('x_ppem','unsigned short'),('y_ppem','unsigned short'),
           ('x_scale','long'),('y_scale','long'),('ascender','long'),('descender','long'),('height','long'),('max_advance','long')])
    record('FT_SizeRec_',S.FT_SizeRec,[('metrics','FT_Size_Metrics')])
    record('FT_GlyphSlotRec_',S.FT_GlyphSlotRec,[('advance','FT_Vector'),('bitmap','FT_Bitmap'),('bitmap_left','int'),('bitmap_top','int')])
    record('FT_FaceRec_',S.FT_FaceRec,[('glyph','FT_GlyphSlot'),('size','FT_Size')])
    out+=['extern "C" {',
          'int FT_Init_FreeType(FT_Library*); int FT_Done_FreeType(FT_Library);',
          'int FT_New_Memory_Face(FT_Library,const unsigned char*,FT_Long,FT_Long,FT_Face*);',
          'int FT_Done_Face(FT_Face);',
          'int FT_Set_Char_Size(FT_Face,FT_F26Dot6,FT_F26Dot6,unsigned int,unsigned int);',
          'int FT_Load_Char(FT_Face,FT_ULong,int32_t);',
          'int FT_Render_Glyph(FT_GlyphSlot,FT_Render_Mode);','}']
    for key,val in zip(['MAJOR','MINOR','PATCH'],version):out.append(f'#define FREETYPE_{key} {val}')
    (a.output/'freetype'/'freetype.h').write_text('\n'.join(out)+'\n')
    (a.output/'ft2build.h').write_text('#pragma once\n#define FT_FREETYPE_H "freetype/freetype.h"\n')
    (a.output/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    print(a.output)
if __name__=='__main__':main()
