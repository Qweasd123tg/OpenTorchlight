#!/usr/bin/env python3
"""Authored callback/state fixture; original game assets are never embedded."""
import sys
import zipfile
from pathlib import Path
from make_hud_fixture import hud_png

path = Path(sys.argv[1]); path.parent.mkdir(parents=True, exist_ok=True)
def button(name, x, disabled=False, visible=True):
    return f'''<Window Type="GuiLook/ImageButton" Name="{name}">
<Property Name="UnifiedAreaRect" Value="{{{{0,{x}}},{{0,20}},{{0,{x+40}}},{{0,60}}}}"/>
<Property Name="NormalImage" Value=""/>
<Property Name="HoverImage" Value="set:HudTest image:Hover"/>
<Property Name="PushedImage" Value="set:HudTest image:Pushed"/>
<Property Name="DisabledImage" Value="set:HudTest image:Disabled"/>
<Property Name="Disabled" Value="{'True' if disabled else 'False'}"/>
<Property Name="Visible" Value="{'True' if visible else 'False'}"/>
<Property Name="onClick" Value="guiToggleInventory"/>
</Window>'''
layout = '<GUILayout><Window Type="DefaultWindow" Name="root">'+button('InventoryButton',20)+button('DisabledButton',80,True)+button('HiddenButton',140,False,False)+'</Window></GUILayout>'
look = '''<Falagard><WidgetLook name="GuiLook/ImageButton">
<PropertyDefinition name="NormalImage" initialValue="set:HudTest image:Normal"/>
<PropertyDefinition name="HoverImage" initialValue="set:HudTest image:Hover"/>
</WidgetLook></Falagard>'''
images = '<Imageset Name="HudTest" Imagefile="hud.png">'+''.join(
    f'<Image Name="{name}" XPos="{x}" YPos="{y}" Width="2" Height="2"/>'
    for name,x,y in [('Normal',1,1),('Hover',5,1),('Pushed',5,5),('Disabled',1,5)])+'</Imageset>'
with zipfile.ZipFile(path,'w',zipfile.ZIP_STORED) as z:
    for name,text in [('bottomhud.layout',layout),('GuiLook.looknfeel',look),('hud.imageset',images)]:
        z.writestr('media/UI/'+name,text)
    z.writestr('media/UI/hud.png',hud_png())
