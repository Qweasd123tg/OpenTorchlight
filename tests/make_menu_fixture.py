#!/usr/bin/env python3
"""Author-owned menu layouts shaped after the recorded widget bindings.
Not a copy of original resources, not a visual reference for the original game.
"""
from pathlib import Path
import sys
import zipfile
from make_frontend_fixture import doc, png
from make_ui_font_fixture import write_fixture


def prop(name, value):
    from xml.sax.saxutils import escape
    return f'<Property Name="{name}" Value="{escape(value, {chr(34): "&quot;"})}"/>'


def widget(name, kind='GuiLook/StaticText', text='', callback='', x=500, y=550, w=320, h=24, extra='', children=''):
    return (f'<Window Type="{kind}" Name="Root/{name}">' +
            prop('UnifiedPosition', f'{{{{0,{x}}},{{0,{y}}}}}') +
            prop('UnifiedSize', f'{{{{0,{w}}},{{0,{h}}}}}') +
            prop('Text', text) + prop('Font', 'Fixture') +
            (prop('onClick', callback) if callback else '') + extra + children + '</Window>')


def button(name, cb, text, x, y, extra='', children=''):
    return widget(name, 'GuiLook/StandardButton', text, cb, x, y, 240, 40, extra, children)


def write_menu(path):
    write_fixture(path)
    main = widget('Background', 'GuiLook/StaticImage', x=0, y=0, w=1024, h=768,
                  extra=prop('Image', 'set:Author image:Background'))
    for i, (name, cb, text) in enumerate([
            ('NewGame', 'guiNewGameMenu', 'New resource character'),
            ('ContinueGame', 'guiContinueGameMenu', 'Load resource character'),
            ('ContinueLast', 'guiContinueGame', 'Continue resource'),
            ('ExitGame', 'guiExitApplication', 'Exit resource')]):
        main += button(name, cb, text, 100, 250+i*60,
                       extra=prop('Disabled','True') if name=='ContinueLast' else '')
    main += button('Settings', 'guiSettingsMenu', 'Settings', 500, 250)
    main += widget('CopyrightInfo', text='Authored Copyright Π', x=470, y=550)
    main += widget('TabTextA', text='Resource Tab A', x=470, y=585)
    main += widget('TabTextB', 'GuiLook/StaticTextOutline', text='Resource Tab B', x=470, y=620)
    main += widget('Placeholder', text='1', x=800, y=500)
    main += widget('Hidden', text='INVISIBLE', extra=prop('Visible', 'False'))
    main += widget('HiddenParent', 'DefaultWindow', extra=prop('Visible', 'False'),
                   children=widget('HiddenChild', text='ALSO INVISIBLE', x=0, y=0))
    create = ''.join(button(n, 'guiSelect1', n, 100, 210+i*55,
                           extra=prop('Visible','False') if i==1 else '')
                     for i, n in enumerate(['Destroyer', 'Vanquisher', 'Alchemist']))
    create += button('CreatePlayer', 'guiNewGame', 'Create resource', 100, 450)
    create += button('Back', 'guiBack', 'Back resource', 100, 510)
    create += widget('NameLabel', text='Character name', x=500, y=200)
    create += widget('CharacterName', 'GuiLook/Editbox', text='1', x=500, y=235)
    load = ''
    for i in range(5):
        y = 180 + i*65
        load += button(f'Player{i+1}', f'guiSelect{i+1}', 'SLOT TEMPLATE', 90, y)
        load += widget(f'Player{i+1}Name', text='1', x=100, y=y+2, w=210, h=20)
        load += widget(f'Player{i+1}Desc', text='1', x=100, y=y+22, w=210, h=16)
    load += button('Continue', 'guiContinueGame', 'Load selected', 500, 180)
    load += button('Back', 'guiBack', 'Back', 500, 245)
    load += button('Up', 'guiScrollUp', 'Up', 500, 310)
    load += button('Down', 'guiScrollDown', 'Down', 500, 375)
    load += widget('CharacterModsWarning', text='Resource warning', x=500, y=450)
    pause = widget('Title', text='Options', x=386, y=130, w=252, h=40,
                   extra=prop('HorzFormatting', 'CentreAligned'))
    for i,(name,cb,text) in enumerate([('Settings','guiSettingsMenu','Settings'),
                                      ('ExitGame','guiExitGame','Exit game'),
                                      ('ReturnToGame','guiCloseMenu','Return to game')]):
        pause += button(name,cb,text,386,200+i*90)
    # Single quotes, reordered attributes and nested decoy defeat the old
    # substring scan. Only direct PropertyDefinition defaults may win.
    look = '''<Falagard><WidgetLook name='GuiLook/StandardButton'>
    <PropertyDefinition initialValue='set:Author image:Normal' name='NormalImage'/>
    <PropertyDefinition name='HoverImage' initialValue='set:Author image:Hover'/>
    <PropertyDefinition name='PushedImage' initialValue='set:Author image:Pushed'/>
    <PropertyDefinition name='DisabledImage' initialValue='set:Author image:Disabled'/>
    <Child><PropertyDefinition name='NormalImage' initialValue='WRONG'/></Child>
    </WidgetLook></Falagard>'''
    # Four solid texels in a PNG let the GLES test distinguish states.
    import struct, zlib
    def chunk(t, d): return struct.pack('>I',len(d))+t+d+struct.pack('>I',zlib.crc32(t+d))
    rgba=bytes([200,0,0,255, 0,200,0,255, 0,0,200,255, 110,110,110,255])
    palette=b'\x89PNG\r\n\x1a\n'+chunk(b'IHDR',struct.pack('>IIBBBBB',4,1,8,6,0,0,0))+chunk(b'IDAT',zlib.compress(b'\0'+rgba))+chunk(b'IEND',b'')
    images=''.join(f'<Image Name="{n}" XPos="{i}" YPos="0" Width="1" Height="1"/>'
                   for i,n in enumerate(['Normal','Hover','Pushed','Disabled']))
    with zipfile.ZipFile(path,'a',zipfile.ZIP_DEFLATED) as z:
        for name, body in [('mainmenuframe',main),('charactercreate',create),('characterload',load),('optionsmenu',pause)]:
            z.writestr('media/UI/'+name+'.layout',doc(body))
        z.writestr('media/UI/GuiLook.looknfeel',look)
        z.writestr('media/UI/author.imageset','<Imageset Name="Author" Imagefile="palette.png">'+images+'</Imageset>')
        z.writestr('media/UI/palette.png',palette)
        # Main has no image on purpose here; missing references must not hide buttons.

if __name__=='__main__': write_menu(Path(sys.argv[1]))
