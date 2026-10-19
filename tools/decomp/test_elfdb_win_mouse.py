"""Offline tests for the strictly pinned WinMouse input ownership correction."""
import copy
from types import SimpleNamespace
from unittest import TestCase,main
import elfdb

class WinMouseOwnershipTest(TestCase):
    def inputs(self):
        files=[{'id':4,'name':'LinuxUtils.cpp'},{'id':5,'name':'WinMouseAndKeys.cpp'},{'id':6,'name':'ShellUtils.cpp'}]
        funcs={a:{'mangled':n,'size':s,'tu':4,'tu_confidence':'position-guess'}for n,a,s,c in elfdb.WIN_MOUSE_HELPERS}
        funcs[0xf63100]={'mangled':'left','size':8,'tu':4,'tu_confidence':'local-symbol'}
        funcs[0xf632d0]={'mangled':'right','size':8,'tu':6,'tu_confidence':'position-guess'}
        symbols=[SimpleNamespace(name=n,size=s,bind=elfdb.STB_LOCAL,type=elfdb.STT_OBJECT,file='WinMouseAndKeys.cpp',shndx=i)for n,s,i in [('_ZL6MouseX',8,0),('_ZL6MouseY',8,0),('_ZL9keyStates',256,0),('_ZL12virt2scanMap',892,1)]]
        code={a:bytes.fromhex(c)for n,a,s,c in elfdb.WIN_MOUSE_HELPERS}
        image=SimpleNamespace(sha256=elfdb.elfimage.ORIGINAL_SHA256,symbols=symbols,sections=[SimpleNamespace(name='.bss'),SimpleNamespace(name='.rodata')],read=lambda a,s:code[a])
        return image,files,funcs,code
    def reject(self,mutate):
        image,files,funcs,code=self.inputs();mutate(image,files,funcs,code);before=copy.deepcopy(funcs)
        self.assertEqual(elfdb.assign_win_mouse_helpers(image,files,funcs),0);self.assertEqual(funcs,before)
    def test_only_eight_helpers_move_and_all_other_metadata_stays_identical(self):
        image,files,funcs,code=self.inputs();before=copy.deepcopy(funcs)
        self.assertEqual(elfdb.assign_win_mouse_helpers(image,files,funcs),8)
        self.assertEqual(len(funcs),len(before))
        for a,f in funcs.items():
            expected=before[a]
            if a in code:expected.update(tu=5,tu_confidence='local-data-owner')
            self.assertEqual(f,expected)
        self.assertEqual([f['tu']for a,f in sorted(funcs.items())],sorted(f['tu']for f in funcs.values()))
    def test_other_elf_is_not_reclassified(self):self.reject(lambda i,f,fs,c:setattr(i,'sha256','another ELF'))
    def test_foreign_local_map_owner_is_not_substituted(self):self.reject(lambda i,f,fs,c:setattr(i.symbols[-1],'file','LinuxUtils.cpp'))
    def test_wrong_table_size_is_rejected(self):self.reject(lambda i,f,fs,c:setattr(i.symbols[-1],'size',1024))
    def test_global_same_name_map_does_not_count_as_local_evidence(self):self.reject(lambda i,f,fs,c:setattr(i.symbols[-1],'bind',elfdb.STB_GLOBAL))
    def test_stronger_function_ownership_is_never_overwritten(self):self.reject(lambda i,f,fs,c:fs[0xf63210].update(tu_confidence='local-symbol'))
    def test_changed_function_code_is_rejected(self):self.reject(lambda i,f,fs,c:c.update({0xf63210:b'changed'}))
    def test_added_function_inside_block_is_rejected(self):self.reject(lambda i,f,fs,c:fs.update({0xf63211:{'mangled':'foreign','size':1,'tu':4}}))
    def test_link_order_boundaries_are_required(self):self.reject(lambda i,f,fs,c:fs[0xf632d0].update(tu=4))
    def test_ambiguous_stt_file_owner_is_rejected(self):self.reject(lambda i,f,fs,c:f.append({'id':8,'name':'WinMouseAndKeys.cpp'}))
if __name__=='__main__':main()
