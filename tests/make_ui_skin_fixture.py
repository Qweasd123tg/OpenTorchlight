#!/usr/bin/env python3
"""Small author-created XML/PNG fixture; no Torchlight assets or fonts."""
import struct
import zlib
import zipfile
from pathlib import Path
import sys

def png():
    def chunk(t,b): return struct.pack('>I',len(b))+t+b+struct.pack('>I',zlib.crc32(t+b)&0xffffffff)
    row=bytes((255,0,0,255))*8+bytes((0,255,0,255))*8+bytes((0,0,255,255))*8+bytes((255,255,255,255))*8
    return b'\x89PNG\r\n\x1a\n'+chunk(b'IHDR',struct.pack('>IIBBBBB',32,8,8,6,0,0,0))+chunk(b'IDAT',zlib.compress((b'\0'+row)*8))+chunk(b'IEND',b'')

def area(left='0',top='0',width='1',height='1'):
    return f'<Area><Dim type="LeftEdge"><AbsoluteDim value="{left}"/></Dim><Dim type="TopEdge"><AbsoluteDim value="{top}"/></Dim><Dim type="Width"><UnifiedDim scale="{width}" type="Width"/></Dim><Dim type="Height"><UnifiedDim scale="{height}" type="Height"/></Dim></Area>'

def image(name): return '<ImageryComponent>'+area()+f'<Image imageset="Fixture" image="{name}"/></ImageryComponent>'
def state(name,sections): return f'<StateImagery name="{name}"><Layer>'+''.join(f'<Section section="{s}"/>' for s in sections)+'</Layer></StateImagery>'
def fixture(output):
    image_defs=''.join(f'<Image Name="{n}" XPos="{i*8}" YPos="0" Width="8" Height="8"/>' for i,n in enumerate(['Red','Green','Blue','White']))
    image_defs+='<Image Name="Offset" XPos="0" YPos="0" Width="8" Height="8" XOffset="-2.5" YOffset="1.5"/>'
    images=f'<Imageset Name="Fixture" Imagefile="atlas.png" NativeHorzRes="256" NativeVertRes="192" AutoScaled="true">{image_defs}</Imageset>'
    toggle='<WidgetLook name="Test/Toggle">'+''.join(f'<ImagerySection name="{s}">{image(i)}</ImagerySection>' for s,i in [('base','Red'),('hover','Green'),('mark','Blue')])+state('Normal',['base'])+state('Hover',['hover'])+state('Disabled',[])+state('SelectedNormal',['base','mark'])+state('SelectedHover',['hover','mark'])+state('SelectedDisabled',[])+'</WidgetLook>'
    frame_parts=''.join(f'<Image type="{p}" imageset="Fixture" image="White"/>' for p in ['TopLeftCorner','TopRightCorner','BottomLeftCorner','BottomRightCorner','TopEdge','BottomEdge','LeftEdge','RightEdge','Background'])
    frame='<WidgetLook name="Test/Frame"><PropertyDefinition name="FrameColours" initialValue="tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFFFFFF"/><ImagerySection name="frame"><FrameComponent>'+area()+frame_parts+'<ColourRectProperty name="FrameColours"/></FrameComponent></ImagerySection>'+state('Enabled',['frame'])+state('Disabled',['frame'])+'</WidgetLook>'
    picture='<WidgetLook name="Test/Image"><Property name="FrameEnabled" value="False"/><Property name="BackgroundEnabled" value="False"/><PropertyDefinition name="ImageColours" initialValue="tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFFFFFF"/><ImagerySection name="body"><ImageryComponent>'+area()+'<ImageProperty name="Image"/><ColourRectProperty name="ImageColours"/><HorzFormatProperty name="HorzFormatting"/><VertFormatProperty name="VertFormatting"/></ImageryComponent></ImagerySection>'+state('Enabled',[])+state('Disabled',[])+state('NoFrameImage',['body'])+'</WidgetLook>'
    # Label section exists but must not render unless referenced by the active state.
    label='<WidgetLook name="Test/Label"><ImagerySection name="unused"><TextComponent>'+area()+'</TextComponent></ImagerySection>'+state('Enabled',[])+state('Disabled',[])+'</WidgetLook>'
    operator='<WidgetLook name="Test/Operator"><ImagerySection name="body"><ImageryComponent><Area><Dim type="LeftEdge"><AbsoluteDim value="11"/><DimOperator op="Add"><AbsoluteDim value="3"/></DimOperator></Dim><Dim type="TopEdge"><AbsoluteDim value="2"><DimOperator op="Add"><AbsoluteDim value="4"/></DimOperator></AbsoluteDim></Dim><Dim type="Width"><UnifiedDim scale="1" type="Width"/></Dim><Dim type="Height"><UnifiedDim scale="1" type="Height"/></Dim></Area><Image imageset="Fixture" image="White"/></ImageryComponent></ImagerySection>'+state('Enabled',['body'])+'</WidgetLook>'
    mixed='<WidgetLook name="Test/Mixed"><ImagerySection name="mixed"><TextComponent>'+area()+'<Colours topLeft="FFFF0000" topRight="FFFF0000" bottomLeft="FFFF0000" bottomRight="FFFF0000"/></TextComponent><FrameComponent>'+area()+frame_parts+'</FrameComponent></ImagerySection>'+state('Enabled',['mixed'])+'</WidgetLook>'
    gradient='<WidgetLook name="Test/Gradient"><ImagerySection name="gradient"><ImageryComponent>'+area()+'<Image imageset="Fixture" image="White"/><Colours topLeft="FFFF0000" topRight="FF00FF00" bottomLeft="FF0000FF" bottomRight="FFFFFFFF"/></ImageryComponent></ImagerySection>'+state('Enabled',['gradient'])+'</WidgetLook>'
    defs={'Mixed':'Default','Gradient':'Default','Toggle' :'ToggleButton','Frame':'Default','Image':'StaticImage','Label':'Default','Operator':'Default'}
    scheme='<GUIScheme Name="Fixture">'+''.join(f'<FalagardMapping WindowType="Test/{t}" Renderer="Falagard/{r}" LookNFeel="Test/{t}"/>' for t,r in defs.items())+'</GUIScheme>'
    layouts={t:f'<GUILayout><Window Type="DefaultWindow" Name="Root"><Property Name="UnifiedSize" Value="{{{{1,0}},{{1,0}}}}"/><Window Type="Test/{t}" Name="Widget"><Property Name="UnifiedAreaRect" Value="{{{{0,40}},{{0,40}},{{0,120}},{{0,104}}}}"/><Property Name="Image" Value="set:Fixture image:Offset"/><Property Name="Text" Value="HELLO"/></Window></Window></GUILayout>' for t in defs}
    output.parent.mkdir(parents=True,exist_ok=True)
    with zipfile.ZipFile(output,'w',zipfile.ZIP_DEFLATED) as z:
        z.writestr('media/UI/GuiLook.looknfeel','<Falagard>'+toggle+frame+picture+label+operator+mixed+gradient+'</Falagard>')
        z.writestr('media/UI/GuiLookSkin.scheme',scheme);z.writestr('media/UI/fixture.imageset',images);z.writestr('media/UI/atlas.png',png())
        for t,xml in layouts.items():z.writestr(f'media/UI/{t}.layout',xml)
if __name__=='__main__': fixture(Path(sys.argv[1]))
