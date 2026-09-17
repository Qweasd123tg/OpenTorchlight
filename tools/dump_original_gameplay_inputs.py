#!/usr/bin/env python3
"""Read-only, bounded inputs still needed for real currency and ranged launch.
No process execution; no original resource/code copying; exact ELF hash required.
Names below describe USE SITES, not guessed meanings of the missing wide strings.
"""
from __future__ import annotations
import argparse, hashlib, json, math, struct, sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from verify_original_entry_dispatch import ELF_SHA256,virtual_bytes

STRINGS={
    'gold_percent_key_low_at_8ca993':0xfd1e98,
    'gold_percent_key_high_at_8ca9e4':0xfd1ec0,
    'gold_graph_at_8cabC1':0xfd1f48,
    'gold_graph_at_8cac81':0xfd1f80,
    'gold_graph_at_8cad04':0xfd1f20,
    'gold_graph_at_8cad8c':0xfd1ee8,
    'spawner_give_loot_property_at_65cf25':0xfc2078,
}
FLOATS={'ranged_pitch_operand':0xfa86d0,'weapon_muzzle_offset_operand':0xfc676c,
        # Use-site names only; no guessed values or automatic runtime defaults.
        'timed_recovery_effect_scale':0xfa86dc,
        'population_density_divisor':0xfce4e0,
        'update_ingame_delta_operand':0xfa86d8}


def wide_string(image,address):
    data=bytearray()
    for i in range(256):
        raw=virtual_bytes(image,address+4*i,4)
        if raw==b'\0'*4:
            text=data.decode('utf-32-le',errors='strict')
            if not text:raise ValueError(f'empty string at {address:x}')
            return text
        data.extend(raw)
    raise ValueError(f'unterminated bounded UTF-32 string at {address:x}')

def extract(image):
    sha=hashlib.sha256(image).hexdigest()
    if sha!=ELF_SHA256:raise ValueError(f'ELF SHA-256 mismatch: {sha}')
    strings={name:{'address':hex(addr),'utf32le_text':wide_string(image,addr)} for name,addr in STRINGS.items()}
    numbers={}
    for name,addr in FLOATS.items():
        raw=virtual_bytes(image,addr,4);value=struct.unpack('<f',raw)[0]
        if not math.isfinite(value):raise ValueError(f'nonfinite numeric operand at {addr:x}')
        numbers[name]={'address':hex(addr),'bytes_le':raw.hex(),'float32':value}
    return {'elf_sha256':sha,'mode':'read-only bounded data; no execution',
            'status':'new evidence for review, NOT automatic runtime overrides','strings':strings,'constants':numbers}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--original',type=Path,required=True)
    p.add_argument('--output',type=Path);a=p.parse_args()
    try:
        # Read-only source cannot be replaced accidentally through --output.
        if a.output and (a.output.resolve()==a.original.resolve() or
                         (a.output.exists() and a.original.samefile(a.output))):
            raise ValueError('output must not overwrite ELF')
        result=json.dumps(extract(a.original.read_bytes()),ensure_ascii=False,indent=2,allow_nan=False)+'\n'
        if a.output:a.output.write_text(result,encoding='utf-8')
        else:print(result,end='')
    except (OSError,ValueError,UnicodeError,struct.error) as e:p.exit(1,f'FAIL: {e}\n')
    return 0
if __name__=='__main__':raise SystemExit(main())
