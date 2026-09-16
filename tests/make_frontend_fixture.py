#!/usr/bin/env python3
"""Authored CEGUI layouts/imageset/PNG added to authored combat resources."""
import sys, zipfile, struct, zlib
from pathlib import Path
from make_attack_fixture import write_fixture

def window(name, callback='', pos=(0,0), size=(300,40), extra=''):
    return (f'<Window Type="Test/Button" Name="Root/{name}">'
      f'<Property Name="UnifiedPosition" Value="{{{{0,{pos[0]}}},{{0,{pos[1]}}}}}"/>'
      f'<Property Name="UnifiedSize" Value="{{{{0,{size[0]}}},{{0,{size[1]}}}}}"/>'
      f'<Property Name="onClick" Value="{callback}"/>{extra}</Window>')
def doc(body):
    return ('<?xml version="1.0" encoding="UTF-16"?><GUILayout><Window Type="DefaultWindow" Name="Root">'
      '<Property Name="Visible" Value="False"/>'+body+'</Window></GUILayout>').encode('utf-16')
def png():
    def chunk(tag,data): return struct.pack('>I',len(data))+tag+data+struct.pack('>I',zlib.crc32(tag+data))
    return b'\x89PNG\r\n\x1a\n'+chunk(b'IHDR',struct.pack('>IIBBBBB',2,2,8,6,0,0,0))+chunk(b'IDAT',zlib.compress(b'\0'+b'\xff\x80\0\xff'*2+b'\0'+b'\0\x40\xff\xff'*2))+chunk(b'IEND',b'')

def main():
    path=Path(sys.argv[1]);path.parent.mkdir(parents=True,exist_ok=True);write_fixture(path)
    background=window('Background',pos=(0,0),size=(1024,768),extra='<Property Name="Image" Value="set:Author image:Background"/>')
    main_ui=background+''.join(window(name,cb,(100,250+i*60)) for i,(name,cb) in enumerate([
      ('NewGame','guiNewGameMenu'),('ContinueGame','guiContinueGameMenu'),('ContinueLast','guiContinueGame'),('ExitGame','guiExitApplication')]))
    create=''.join(window(name,'guiSelect1',(100,210+i*55)) for i,name in enumerate(['Destroyer','Vanquisher','Alchemist']))
    create+=window('CreatePlayer','guiNewGame',(100,450))+window('Back','guiBack',(100,510))
    load=''.join(window('Player'+str(i+1),'guiSelect'+str(i+1),(100,130+i*48)) for i in range(5))
    load+=window('Continue','guiContinueGame',(100,400))+window('Back','guiBack',(100,520))
    load+=window('ScrollDown','guiExitApplication',(500,460),extra='<Property Name="onClick" Value="guiScrollDown"/>')
    load+=window('ScrollUp','guiScrollUp',(500,400))
    with zipfile.ZipFile(path,'a',zipfile.ZIP_DEFLATED) as z:
        z.writestr('media/UI/mainmenuframe.layout',doc(main_ui))
        z.writestr('media/UI/charactercreate.layout',doc(create))
        z.writestr('media/UI/characterload.layout',doc(load))
        z.writestr('media/UI/imagesets/author.imageset','<Imageset Name="Author" Imagefile="author.png"><Image Name="Background" XPos="0" YPos="0" Width="2" Height="2"/></Imageset>')
        z.writestr('media/UI/imagesets/author.png',png())
if __name__=='__main__':main()
