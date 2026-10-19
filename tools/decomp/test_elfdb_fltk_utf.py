"""Pinned-original tests for the vendor ownership correction; never starts game."""
import copy
import unittest
from types import SimpleNamespace
import elfdb
import elfimage

class FltkUtfOwnershipTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        try: cls.image=elfimage.load(elfdb.default_elf())
        except (OSError,SystemExit) as exc: raise unittest.SkipTest(str(exc))
        cls.db=elfdb.load_db()
    def inputs(self):
        files=[dict(id=t['id'],name=t['name'])for t in self.db['tus']]
        owner=next(t['id']for t in files if t['name']=='utf8Input.c')
        funcs={int(f['address'],16):copy.deepcopy(f)for f in self.db['functions'].values()}
        for n,a,size,digest,source in elfdb.FLTK_UTF_FUNCTIONS:
            funcs[a].update(tu=owner,tu_confidence='local-symbol'if n=='gb2312_mbtowc'else'position-guess')
        native=self.image
        image=SimpleNamespace(sha256=native.sha256,symbols=copy.deepcopy(native.symbols),sections=native.sections,read=native.read)
        return image,files,funcs
    def rejected(self,mutation):
        image,files,funcs=self.inputs();mutation(image,files,funcs);before=copy.deepcopy(funcs)
        self.assertEqual(elfdb.assign_fltk_utf_sources(image,files,funcs),0)
        self.assertEqual(funcs,before)
    def test_only_exact34_move_and_metadata_survives(self):
        image,files,funcs=self.inputs();before=copy.deepcopy(funcs);owners={f['name']:f['id']for f in files}
        self.assertEqual(elfdb.assign_fltk_utf_sources(image,files,funcs),34)
        self.assertEqual(set(funcs),set(before))
        expected=copy.deepcopy(before)
        for n,a,size,digest,source in elfdb.FLTK_UTF_FUNCTIONS:
            expected[a]['tu']=owners[source]
            if source!='utf8Input.c':expected[a]['tu_confidence']='pinned-library-source'
        self.assertEqual(funcs,expected)
    def test_foreign_elf(self):self.rejected(lambda im,files,fs:setattr(im,'sha256','0'*64))
    def test_changed_native_function(self):
        def mutate(im,files,fs):
            read=im.read
            im.read=lambda a,s:(bytes([read(a,s)[0]^1])+read(a,s)[1:])if a==0xf93c60 else read(a,s)
        self.rejected(mutate)
    def test_changed_native_table(self):
        def mutate(im,files,fs):
            read=im.read;target=elfdb.FLTK_UTF_DATA[0][1]
            im.read=lambda a,s:(bytes([read(a,s)[0]^1])+read(a,s)[1:])if a==target else read(a,s)
        self.rejected(mutate)
    def test_stt_file_owner_moved(self):
        def mutate(im,files,fs):
            target=elfdb.FLTK_UTF_DATA[0];symbol=next(s for s in im.symbols if s.name==target[0]and s.file==target[4]);symbol.file='foreign.c'
        self.rejected(mutate)
    def test_stronger_function_claim(self):self.rejected(lambda im,files,fs:fs[0xf93c60].update(tu_confidence='local-symbol'))
    def test_nonadjacent_source_groups(self):
        self.rejected(lambda im,files,fs:next(f for f in files if f['name']=='fl_utf.c').update(id=999))
    def test_unexpected_function_inside_block(self):
        self.rejected(lambda im,files,fs:fs.update({0xf92801:dict(mangled='foreign',size=1,tu=490)}))

if __name__=='__main__':unittest.main()
