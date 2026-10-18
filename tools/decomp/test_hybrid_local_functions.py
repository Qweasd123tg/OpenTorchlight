"""Local production helpers must be linkable from the separate hook object."""
import shutil
import subprocess
import tempfile
from pathlib import Path
import unittest
from types import SimpleNamespace
import copy
import elfimage
import hybrid

class LocalHookTests(unittest.TestCase):
    def crt_image(self):
        symbol=SimpleNamespace(name='atexit',value=0xf9f710,size=26,type=elfimage.STT_FUNC,
                               bind=elfimage.STB_LOCAL,defined=True)
        section=SimpleNamespace(type=1,flags=6,addr=0xf9f000,size=0x1000)
        body=bytes.fromhex('488b0501fa47004885c0740a488b1031f6e9c25a5bff31d2ebf5')
        return SimpleNamespace(sha256=elfimage.ORIGINAL_SHA256,symbols=[symbol],
                               section_at=lambda address:section,read=lambda address,size:body)

    def test_original_local_atexit_wrapper_is_explicitly_linked(self):
        image=self.crt_image()
        self.assertEqual(hybrid.native_crt_aliases(image),{'atexit':0xf9f710})
        image.plt={};image.dynsyms=[]
        ctx=SimpleNamespace(functions={},global_data={},local_data={},image=image)
        text,provided=hybrid.originals_script(ctx,[])
        self.assertIn('PROVIDE("atexit" = 0xf9f710);',text)
        self.assertIn('atexit',provided)

    def test_local_crt_alias_rejects_unverified_or_ambiguous_identity(self):
        for change in ('elf','name','address','size','binding','type','undefined','missing','duplicate',
                       'section','writable','no_section','short_section','body','short_body','other_function'):
            with self.subTest(change=change):
                image=self.crt_image();symbol=image.symbols[0]
                if change=='elf':image.sha256='0'*64
                elif change=='name':symbol.name='atexit_other'
                elif change=='address':symbol.value+=1
                elif change=='size':symbol.size+=1
                elif change=='binding':symbol.bind=elfimage.STB_GLOBAL
                elif change=='type':symbol.type=elfimage.STT_OBJECT
                elif change=='undefined':symbol.defined=False
                elif change=='missing':image.symbols=[]
                elif change=='duplicate':image.symbols.append(copy.copy(symbol))
                elif change=='no_section':image.section_at=lambda address:None
                elif change in ('section','writable','short_section'):
                    section=image.section_at(0xf9f710)
                    if change=='section':section.type=8
                    elif change=='writable':section.flags=7
                    else:section.size=1
                elif change=='body':image.read=lambda address,size:b'\0'*26
                elif change=='short_body':image.read=lambda address,size:b'\0'
                else:symbol.name='another_local_runtime'
                self.assertEqual(hybrid.native_crt_aliases(image),{})
    @unittest.skipUnless(shutil.which("as") and shutil.which("ld"), "requires ELF assembler and linker")
    def test_two_tus_can_hook_same_local_name_without_merging_bodies(self):
        owned={"helper": {"names":["helper"], "bind":["local"]},
               "missing": {"names":["missing"], "bind":["local"]}}
        with tempfile.TemporaryDirectory() as d:
            root=Path(d); aliases=[]
            for i in (1,2):
                asm=".text\n.type helper,@function\nhelper:\nmov $%d, %%eax\nret\n.size helper,.-helper\n" % i
                text, mapping=hybrid.export_local_functions(asm,owned,i)
                self.assertEqual(set(mapping), {"helper"})
                aliases.append(mapping["helper"])
                (root/('%s.s'%i)).write_text(text)
                subprocess.run(['as','--64','-o',str(root/('%s.o'%i)),str(root/('%s.s'%i))],check=True)
                syms=elfimage.load_object(root/('%s.o'%i)).symbols
                local=next(s for s in syms if s.name=='helper')
                alias=next(s for s in syms if s.name==mapping['helper'])
                self.assertEqual(local.bind,elfimage.STB_LOCAL)
                self.assertEqual(alias.bind,elfimage.STB_GLOBAL)
                self.assertEqual((alias.value,alias.size,alias.type),(local.value,local.size,local.type))
            (root/'hooks.s').write_text('.data\n.quad '+', '.join(aliases)+'\n')
            subprocess.run(['as','--64','-o',str(root/'hooks.o'),str(root/'hooks.s')],check=True)
            subprocess.run(['ld','-r','-o',str(root/'combined.o'),str(root/'1.o'),str(root/'2.o'),str(root/'hooks.o')],check=True)
            self.assertFalse(hybrid.undefined_symbols(root/'combined.o'))
            self.assertEqual(sum(s.name=='helper' for s in elfimage.load_object(root/'combined.o').symbols),2)
    def test_export_only_emitted_local_functions_owned_by_this_tu(self):
        asm='.text\n.type global,@function\nglobal:\nret\n.type incidental,@function\nincidental:\nret\n'
        owned={'global': {'names':['global'],'bind':['global']}, 'missing': {'names':['missing'],'bind':['local']}}
        self.assertEqual(hybrid.export_local_functions(asm,owned,7),(asm,{}))

if __name__=='__main__': unittest.main()
