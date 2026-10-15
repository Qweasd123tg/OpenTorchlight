"""Local production helpers must be linkable from the separate hook object."""
import shutil
import subprocess
import tempfile
from pathlib import Path
import unittest
import elfimage
import hybrid

class LocalHookTests(unittest.TestCase):
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
