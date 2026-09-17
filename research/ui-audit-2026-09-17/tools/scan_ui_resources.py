#!/usr/bin/env python3
"""Read-only manifest of shipped UI resources. Counts are NOT parity scores.
Malformed XML is reported, never silently repaired; lower-case property keys
are kept separately. No binary textures, fonts, or game assets are copied out.
"""
from __future__ import annotations
import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
import xml.etree.ElementTree as ET
from zipfile import ZipFile

TARGETS={'bottomhud.layout','inventorymenu.layout','merchantmenu.layout','petmenu.layout',
         'skillmenu.layout','questmenu.layout','journalmenu.layout','stashmenu.layout',
         'enchantmenu.layout','combinemenu.layout','optionsmenu.layout','mainmenuframe.layout',
         'charactercreate.layout','characterload.layout','settingsmenu.layout'}
FEATURES=('FrameComponent','ImageryComponent','TextComponent','StateImagery','Child','ImageDim',
          'FontDim','WidgetDim','PropertyDim','UnifiedDim','AbsoluteDim','DimOperator')

def decode(data):
    return data.decode('utf-16') if data.startswith((b'\xff\xfe',b'\xfe\xff')) else data.decode('utf-8-sig')

def sha_file(p):
    h=hashlib.sha256()
    with p.open('rb') as f:
        for b in iter(lambda:f.read(1024*1024),b''):h.update(b)
    return h.hexdigest()

def scan(path):
    layouts=[];errors=[];looks={};mappings={};mapping_sources={};duplicates=[];imagesets=[]
    types=Counter();properties=Counter();lowerprops=[];selected=[]
    with ZipFile(path) as z:
        names=[n for n in z.namelist() if n.lower().startswith('media/ui/') and n.lower().endswith(('.layout','.looknfeel','.scheme','.imageset'))]
        for name in sorted(names):
            data=z.read(name)
            try:root=ET.fromstring(decode(data))
            except (UnicodeError,ET.ParseError) as e:
                errors.append({'path':name,'error':str(e)});continue
            if name.lower().endswith('.layout'):
                windows=list(root.iter('Window')); wc=Counter(w.get('Type','') for w in windows)
                types.update(wc)
                for w in windows:
                    for p in w.findall('Property'):
                        if 'Name' in p.attrib:properties[p.attrib['Name']]+=1
                        else:lowerprops.append({'path':name,'window':w.get('Name'),'attributes':p.attrib})
                item={'path':name,'sha256':hashlib.sha256(data).hexdigest(),'windows':len(windows),'types':dict(wc),
                      'onClick_windows':sum(any(p.get('Name')=='onClick' for p in w.findall('Property')) for w in windows),
                      'repeated_window_names':[k for k,v in Counter(w.get('Name','') for w in windows).items() if v>1]}
                layouts.append(item)
                if Path(name).name.lower() in TARGETS:
                    selected.append({**item,'widgets':[{'name':w.get('Name'),'type':w.get('Type'),
                                       'properties':{p.get('Name'):p.get('Value','') for p in w.findall('Property') if 'Name' in p.attrib}}
                                                      for w in windows]})
            elif name.lower().endswith('.looknfeel'):
                for w in root.iter('WidgetLook'):
                    looks[w.get('name','')]={'source':name,'features':{t:len(list(w.iter(t))) for t in FEATURES},
                        'state_names':[s.get('name') for s in w.findall('StateImagery')],
                        'section_names':[s.get('name') for s in w.findall('ImagerySection')]}
            elif name.lower().endswith('.scheme'):
                for m in root.iter('FalagardMapping'):
                    key=m.get('WindowType','')
                    if key in mappings:duplicates.append({'type':key,'first':mapping_sources[key],'second':name,'identical':mappings[key]==m.attrib})
                    mappings[key]=dict(m.attrib);mapping_sources[key]=name
            elif name.lower().endswith('.imageset'):
                offsets=[{'name':i.get('Name'),'x':i.get('XOffset','0'),'y':i.get('YOffset','0')} for i in root.iter('Image')
                         if float(i.get('XOffset','0'))!=0 or float(i.get('YOffset','0'))!=0]
                imagesets.append({'path':name,'attributes':root.attrib,'image_count':len(list(root.iter('Image'))),
                                 'nonzero_offset_images':offsets})
        inventory_files=[{'path':i.filename,'size':i.file_size,'crc32':format(i.CRC,'08x')} for i in z.infolist()
                         if i.filename.lower().startswith('media/ui/models/inventory/') and not i.is_dir()]
    usage=[]
    for t,n in sorted(types.items()):
        mapping=mappings.get(t)
        lookname=mapping.get('LookNFeel') if mapping else t
        usage.append({'type':t,'windows':n,'mapping':mapping,'look':looks.get(lookname)})
    feature_totals={t:sum(l['features'][t] for name,l in looks.items() if any(u['mapping'] and u['mapping']['LookNFeel']==name for u in usage)) for t in FEATURES}
    return {'pak_sha256':sha_file(path),'xml_files_considered':len(names),'parsed_layouts':len(layouts),
            'window_instances':sum(types.values()),'distinct_window_types':len(types),'parse_errors':errors,
            'types':dict(types),'properties':dict(properties),'lowercase_or_missing_Name_properties':lowerprops,
            'type_to_look_usage':usage,'features_in_unique_mapped_used_looks':feature_totals,
            'layouts':layouts,'selected_layouts':selected,'scheme_duplicate_mappings':duplicates,
            'imagesets':imagesets,'inventory_model_files':inventory_files,
            'scope':'Static XML only. Does not count dynamically created windows or prove any renderer/controller behavior.'}

if __name__=='__main__':
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--pak',type=Path,required=True);ap.add_argument('--output',type=Path,required=True)
    a=ap.parse_args();r=scan(a.pak);a.output.parent.mkdir(parents=True,exist_ok=True)
    a.output.write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    for k in ('xml_files_considered','parsed_layouts','window_instances','distinct_window_types','parse_errors','features_in_unique_mapped_used_looks'):
        print(k,':',r[k])
