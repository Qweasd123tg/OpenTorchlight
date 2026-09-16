#!/usr/bin/env python3
"""Minimal authored HUD fixture: bottomhud.layout plus a colored atlas.
Separate from frontend.pak.zip so the fixed v1 checkpoint identity stays valid."""
import sys, zipfile, struct, zlib
from pathlib import Path

def hud_png():
    """8x8 atlas with one-texel margins so linear filtering cannot bleed."""
    blocks={(0,0):(255,0,0,255),(4,0):(0,0,255,255),(0,4):(255,140,0,255),(4,4):(0,255,0,255)}
    rows=[]
    for y in range(8):
        row=bytearray()
        for x in range(8):
            row+=bytes(blocks[(x//4*4,y//4*4)])
        rows.append(bytes(row))
    def chunk(tag,data): return struct.pack('>I',len(data))+tag+data+struct.pack('>I',zlib.crc32(tag+data))
    raw=b''.join(b'\0'+row for row in rows)
    return b'\x89PNG\r\n\x1a\n'+chunk(b'IHDR',struct.pack('>IIBBBBB',8,8,8,6,0,0,0))+chunk(b'IDAT',zlib.compress(raw))+chunk(b'IEND',b'')

def window(name,pos,size,image):
    return (f'<Window Type="GuiLook/StaticImage" Name="{name}">'
      f'<Property Name="UnifiedPosition" Value="{{{{0,{pos[0]}}},{{0,{pos[1]}}}}}"/>'
      f'<Property Name="UnifiedSize" Value="{{{{0,{size[0]}}},{{0,{size[1]}}}}}"/>'
      f'<Property Name="Image" Value="set:HudTest image:{image}"/></Window>')

def main():
    path=Path(sys.argv[1]);path.parent.mkdir(parents=True,exist_ok=True)
    body=(window('PlayerHealthBarSub',(10,100),(10,40),'HealthFill')
        + window('PlayerManaBarSub',(30,100),(10,40),'ManaFill')
        + window('ExperienceBarSub',(10,150),(40,4),'XpFill'))
    layout=('<?xml version="1.0" encoding="UTF-16"?><GUILayout>'+body+'</GUILayout>').encode('utf-16')
    imageset=('<Imageset Name="HudTest" Imagefile="hud.png">'
      '<Image Name="HealthFill" XPos="1" YPos="1" Width="2" Height="2"/>'
      '<Image Name="ManaFill" XPos="5" YPos="1" Width="2" Height="2"/>'
      '<Image Name="XpFill" XPos="1" YPos="5" Width="2" Height="2"/>'
      '<Image Name="SpareFill" XPos="5" YPos="5" Width="2" Height="2"/></Imageset>')
    with zipfile.ZipFile(path,'w',zipfile.ZIP_STORED) as z:
        z.writestr('media/UI/bottomhud.layout',layout)
        z.writestr('media/UI/imagesets/hudtest.imageset',imageset)
        z.writestr('media/UI/imagesets/hud.png',hud_png())
    print('Authored HUD fixture: 3 original-geometry bars, 8x8 colored atlas; no original assets')

if __name__=='__main__':
    main()
