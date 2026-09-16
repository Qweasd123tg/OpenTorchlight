#!/usr/bin/env python3
"""Check catalog integrity/statuses; unresolved unused assets do not become silently 'supported'."""
import argparse,json,shutil,struct,subprocess,tempfile,zipfile
from pathlib import Path

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--probe',required=True,type=Path);p.add_argument('--pak',required=True,type=Path)
    p.add_argument('--output-dir',required=True,type=Path);p.add_argument('--negative',action='store_true')
    p.add_argument('--timeout-scale',type=int,choices=range(1,11),default=1)
    a=p.parse_args();a.output_dir.mkdir(parents=True,exist_ok=True)
    work=Path(tempfile.mkdtemp(prefix='catalog-',dir=a.output_dir));pak=a.pak
    if a.negative:
        pak=work/'authored-negative.zip';shutil.copyfile(a.pak,pak)
        with zipfile.ZipFile(pak,'a') as z:
            image=next(z.read(n) for n in z.namelist() if n.lower().endswith('.png'))
            z.writestr('catalog/good.png',image,compress_type=zipfile.ZIP_STORED)
            z.writestr('catalog/bad.png',image,compress_type=zipfile.ZIP_STORED)
            z.writestr('catalog/unknown.extension',b'authored opaque test input')
            z.writestr('catalog/negative.material','''material CatalogNegative
{
 technique
 {
  pass
  {
   texture_unit
   {
    texture absent-catalog-test.png
   }
  }
 }
}
''')
            offset=z.getinfo('catalog/bad.png').header_offset
        with pak.open('r+b') as f:
            f.seek(offset);header=f.read(30);name,extra=struct.unpack_from('<HH',header,26)
            f.seek(offset+30+name+extra);first=f.read(1);f.seek(-1,1);f.write(bytes([first[0]^1]))
    output=work/'catalog.json'
    subprocess.run([str(a.probe),str(pak),str(output)],check=True,timeout=240*a.timeout_scale)
    j=json.loads(output.read_text());nodes={n['id']:n for n in j['nodes']}
    assert len(nodes)==len(j['nodes']),'duplicate node identifiers'
    for e in j['edges']:
        assert e['from'] in nodes and e['to'] in nodes,'dangling catalog edge'
        assert e['target_status']==nodes[e['to']]['status'],'edge status hides target failure'
    if a.negative:
        assert nodes['catalog/good.png']['status']=='supported'
        assert nodes['catalog/bad.png']['status']=='corrupt'
        assert nodes['catalog/unknown.extension']['status']=='unsupported'
        assert nodes['absent-catalog-test.png']['status']=='missing'
    else:
        assert j['decoder_rejections']==0,'a real resource decoder rejected input; see catalog'
        for name in ('media/dungeons/main.dat.adm','media/dungeons/town.dat.adm','media/effectslist.dat.adm'):
            assert nodes[name]['status']=='supported'
        assert any(e['relation']=='parent-dungeon' and e['to']=='media/dungeons/town.dat.adm' for e in j['edges'])
        assert all(nodes[n]['status']=='unsupported' for n in ('runtime:timeline','runtime:full-effects','runtime:full-CEGUI'))
    summary={'status':'PASSED','kind':'catalog-schema-and-parser-boundaries','counts':j['counts'],
             'nodes':len(nodes),'edges':len(j['edges']),'timeout_scale':a.timeout_scale,'evidence':'resource inventory, not game fidelity'}
    (work/'result.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(json.dumps(summary),'evidence:',work)
    return 0
if __name__=='__main__':raise SystemExit(main())
