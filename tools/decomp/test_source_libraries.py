"""Safety regressions for source inputs; synthetic bytes never imply game proof."""
import hashlib
import json
from pathlib import Path
import tempfile
from types import SimpleNamespace
import unittest
from unittest import mock
import source_libraries as lib


def save(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value))

class Targets(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup)
        self.root=Path(self.temp.name)
        self.addresses=json.loads((Path(__file__).resolve().parents[2]/'decomp/recovery-targets.json').read_text())['addresses']
        self.db=dict(original_elf_sha256=lib.ORIGINAL,tus=[dict(id=1,kind='fltk')],
                     functions={a:dict(address=a,tu=1,kind='function') for a in self.addresses})
        self.ledger=dict(schema=1,original_elf_sha256=lib.ORIGINAL,addresses=self.addresses,
                         addresses_sha256=lib.digest('\n'.join(self.addresses).encode()))
        save(self.root/'decomp/recovery-targets.json', self.ledger)
    def test_classification_never_shrinks_original_set(self):
        self.assertEqual(len(lib.target_functions(self.root,self.db)),5247)
    def test_removed_target_rejected(self):
        self.ledger['addresses']=self.addresses[:-1];save(self.root/'decomp/recovery-targets.json',self.ledger)
        self.assertRaises(ValueError,lib.target_functions,self.root,self.db)
    def test_target_kind_change_rejected(self):
        self.db['functions'][self.addresses[0]]['kind']='compiler'
        self.assertRaises(ValueError,lib.target_functions,self.root,self.db)
    def test_changed_ledger_digest_rejected(self):
        self.ledger['addresses_sha256']='0'*64;save(self.root/'decomp/recovery-targets.json',self.ledger)
        self.assertRaises(ValueError,lib.target_functions,self.root,self.db)

    def test_swap_valid_target_and_rehash_cannot_change_original_set(self):
        extra='0x7ffffffff0';self.db['functions'][extra]=dict(address=extra,tu=1,kind='function')
        changed=sorted(self.addresses[1:]+[extra],key=lambda a:int(a,16))
        self.ledger['addresses']=changed;self.ledger['addresses_sha256']=lib.digest('\n'.join(changed).encode())
        save(self.root/'decomp/recovery-targets.json',self.ledger)
        self.assertRaises(ValueError,lib.target_functions,self.root,self.db)

class UpstreamInputs(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup);self.root=Path(self.temp.name)
        self.vendor=self.root/'third_party/fltk-1.3.0';self.vendor.mkdir(parents=True)
        paths=['src/xutf8/utf8Input.c','src/xutf8/utf8Utils.c','src/xutf8/keysym2Ucs.c','src/fl_utf.c']
        self.sources=paths
        files={name:lib.digest(b'/* upstream */\n') for name in paths+['FL/h%d.H'%i for i in range(226)]}
        for name in files:
            p=self.vendor/name;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(b'/* upstream */\n')
        save(self.vendor/'source-inputs.json',dict(commit=lib.COMMIT,files=files))
        proof=dict(original_elf_sha256=lib.ORIGINAL,functions=[],local_data=[],tu_ids={})
        funcs={};tus=[];self.native={};symbols=[]
        for i,path in enumerate(paths):
            tu=490+i;name=Path(path).name;proof['tu_ids'][name]=tu;tus.append(dict(id=tu,name=name,kind='fltk'))
            for n in range([10,5,2,17][i]):
                address=0x10000+len(funcs)*16;key=hex(address);sym='function_%d'%len(funcs)
                self.native[address]=bytes([len(funcs)])*8
                funcs[key]=dict(address=key,tu=tu,names=[sym],size=8,kind='function',bind=['global'])
                proof['functions'].append(dict(address=key,name=sym,size=8,owner_id=tu,owner=name,sha256=lib.digest(self.native[address])))
        for i in range(36):
            address=0x40000+i*8;name='table_%d'%i;self.native[address]=b'constant'
            symbols.append(SimpleNamespace(name=name,file='utf8Input.c',defined=True,type=1,bind=0,value=address,size=8,shndx=1))
            proof['local_data'].append(dict(name=name,owner='utf8Input.c',address=hex(address),size=8,section='.rodata',sha256=lib.digest(b'constant')))
        self.db=dict(original_elf_sha256=lib.ORIGINAL,functions=funcs,tus=tus)
        self.image=SimpleNamespace(sha256=lib.ORIGINAL,symbols=symbols,sections=[None,SimpleNamespace(name='.rodata')],read=lambda a,n:self.native[a][:n])
        save(self.root/'decomp/source-libraries/native.json',proof)
        platform=self.root/'decomp/source-libraries/platform/config.h';platform.parent.mkdir(parents=True);platform.write_bytes(b'#define HAVE_LIBC_ICONV 0\n')
        self.spec=dict(schema=1,name='fltk-1.3.0',commit=lib.COMMIT,original_elf_sha256=lib.ORIGINAL,
            provenance_sha256=lib.digest((self.vendor/'source-inputs.json').read_bytes()),native_proof='decomp/source-libraries/native.json',
            native_proof_sha256=lib.digest((self.root/'decomp/source-libraries/native.json').read_bytes()),platform_header='decomp/source-libraries/platform/config.h',
            platform_header_sha256=lib.digest(platform.read_bytes()),sources=paths)
        save(self.root/'decomp/source-libraries/fltk.json',self.spec);save(self.root/'decomp/config.json',dict(source_libraries=['decomp/source-libraries/fltk.json']))
        self.targets=mock.patch.object(lib,'target_functions',return_value=list(funcs.values()));self.targets.start();self.addCleanup(self.targets.stop)
    def test_four_production_units(self):
        units=lib.production_sources(self.root,self.db,self.image)
        self.assertEqual([p.name for p,_ in units],[Path(p).name for p in self.sources])
        self.assertTrue(all('-std=gnu99' in flags for _,flags in units))
    def test_changed_upstream_header_rejected(self):
        (self.vendor/'FL/h13.H').write_text('changed')
        self.assertRaises(ValueError,lib.load,self.root,self.db,self.image)
    def test_escaping_header_symlink_rejected(self):
        outside=self.root/'other';outside.write_text('/* upstream */\n');p=self.vendor/'FL/h13.H';p.unlink();p.symlink_to(outside)
        self.assertRaises(ValueError,lib.load,self.root,self.db,self.image)
    def test_foreign_native_function_owner_rejected(self):
        next(iter(self.db['functions'].values()))['tu']=999
        self.assertRaises(ValueError,lib.load,self.root,self.db,self.image)
    def test_changed_native_table_rejected(self):
        self.native[0x40000]=b'different'
        self.assertRaises(ValueError,lib.load,self.root,self.db,self.image)
    def test_wrong_upstream_source_selected_rejected(self):
        self.assertRaises(ValueError,lib.select,self.root,self.db,self.image,'not-upstream.c')
    def manifest(self):
        out=self.root/'build';out.mkdir();res=dict(source_sha256={},library_source_compile_flags={},original_data_redirects={},original_initializers_omitted={},production_object_sha256={})
        for source,flags in lib.production_sources(self.root,self.db,self.image):
            obj=out/(source.stem+'.o');obj.write_bytes(b'whole complete object '+source.name.encode());name=str(source.relative_to(self.root))
            res['source_sha256'][name]=lib.digest(source.read_bytes());res['library_source_compile_flags'][name]=list(flags);res['production_object_sha256'][name]=lib.digest(obj.read_bytes())
        manifest=dict(original_elf_sha256=lib.ORIGINAL,comparison_only=[dict(original=a,symbol=f['names'][0])for a,f in self.db['functions'].items()],hooks=[],standalone_residual=res)
        save(out/'manifest.json',manifest);return out,manifest
    def test_complete_object_production_binding(self):
        out,_=self.manifest();units=lib.comparison_units(self.root,self.db,self.image,out)
        self.assertEqual(sum(len(u['functions'])for u in units),34)
        self.assertTrue(all(row['object_digest']==u['object_digest']for u in units for row in u['functions']))
    def test_changed_complete_object_rejected(self):
        out,_=self.manifest();(out/'utf8Input.o').write_bytes(b'modified')
        self.assertRaises(ValueError,lib.comparison_units,self.root,self.db,self.image,out)
    def test_missing_production_entry_cannot_accept(self):
        out,m=self.manifest();m['comparison_only'].pop();save(out/'manifest.json',m)
        self.assertRaises(ValueError,lib.comparison_units,self.root,self.db,self.image,out)
    def test_borrowed_native_table_cannot_accept(self):
        out,m=self.manifest();m['standalone_residual']['original_data_redirects']['third_party/fltk-1.3.0/src/fl_utf.c']=['table']
        save(out/'manifest.json',m);self.assertRaises(ValueError,lib.comparison_units,self.root,self.db,self.image,out)

if __name__=='__main__':unittest.main()
