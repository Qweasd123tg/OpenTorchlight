#!/usr/bin/env python3
"""Read-only inventory of the game's effect metadata arrays; values remain unknown."""
from pathlib import Path
import argparse,json,re
from archive import symbols,functions

NAMES={
'gEFFECT_TYPE_NAMES':(8,1,'wstring candidate'),
'gEFFECT_TYPE_DESCRIPTIONS_GOOD':(8,1,'wstring candidate'),
'gEFFECT_TYPE_DESCRIPTIONS_GOOD_OT':(8,1,'wstring candidate'),
'gEFFECT_TYPE_DESCRIPTIONS_BAD':(8,1,'wstring candidate'),
'gEFFECT_TYPE_DESCRIPTIONS_BAD_OT':(8,1,'wstring candidate'),
'gEFFECT_TYPE_MIN_VALUES':(4,1,'int32 candidate'),
'gEFFECT_TYPE_MAX_VALUES':(4,1,'int32 candidate'),
'gEFFECT_TYPE_BONUS':(4,1,'int32 candidate'),
'gEFFECT_TYPE_PROPERTY_TAGS':(8,5,'wstring candidate'),
'gEFFECT_TYPE_GRAPHS':(8,5,'wstring candidate'),
}

def run(root):
    fs=list(functions(root));rows=[]
    for s in symbols(root):
        if s['name'] not in NAMES:continue
        width,columns,typ=NAMES[s['name']]
        if s['size']%(width*columns):raise ValueError('nonintegral suggested table shape')
        refs=[dict(function_address=hex(f.address),function=f.name,file=f.path)
              for f in fs if re.search(r'\b'+re.escape(s['name'])+r'\b',f.text)]
        rows.append({**s,'address':hex(s['address']),'element_width_assumption':width,'element_type_hypothesis':typ,
                     'suggested_shape':[s['size']//(width*columns)]+([columns]if columns>1 else []),
                     'references_in_archive':refs,'values':None,'status':'SHAPE_CANDIDATE_ONLY'})
    return {'tables':rows,'table_count':len(rows),'bytes':sum(r['size']for r in rows),
            'row_count_candidates':sorted({r['suggested_shape'][0]for r in rows}),
            'source_gate':'types, static initializer behavior, original ELF and table contents must be checked',
            'name_tables_py_filter':'bind == local; these ten symbols have nm B, global BSS',
            'original_elf_executed':False}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('root',type=Path);p.add_argument('out',type=Path);a=p.parse_args();d=run(a.root)
    a.out.write_text(json.dumps(d,indent=2,ensure_ascii=False)+'\n');print(json.dumps({k:v for k,v in d.items()if k!='tables'},indent=2))
