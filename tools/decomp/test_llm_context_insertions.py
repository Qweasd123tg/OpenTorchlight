"""Exact existing insertion declarations: offline identity and freshness guards."""
from pathlib import Path
from types import SimpleNamespace
from unittest import TestCase, main, mock
import copy
import hashlib
import test_llm_context as fixtures
from llm_context import ContextIndex


class PinnedInsertionTests(TestCase):
    setUp = fixtures.PacketContextTests.setUp
    write_header = fixtures.PacketContextTests.write_header
    add_function = fixtures.PacketContextTests.add_function
    index = fixtures.PacketContextTests.index
    wide = 'std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >'

    def insertion(self, variant):
        source = Path(__file__).resolve().parents[2] / 'decomp/include'
        if variant == 'repository':
            scope, address, size = 'TRepository<' + self.wide + ' >', 0xc64bf0, 1409
            symbol = '_ZN11TRepositoryISbIwSt11char_traitsIwESaIwEEE7addItemERS3_'
            method, params, header = 'addItem', self.wide + '&', 'TRepository.h'
        else:
            pointee, address, symbol = {
                'unit': ('CBaseUnit', 0x9ca560, '_ZN10TArrayListIP9CBaseUnitE3addES1_'),
                'editor': ('CEditorBaseObject', 0x9e0a30, '_ZN10TArrayListIP17CEditorBaseObjectE3addES1_'),
            }[variant]
            scope, size, method, params, header = 'TArrayList<' + pointee + '*>', 180, 'add', pointee + '*', 'TArrayList.h'
            self.write_header('Pointee.h', 'class ' + pointee + ' { public: int value; };\n')
            self.mapping[pointee] = ['Pointee.h']
        (self.include/header).write_bytes((source/header).read_bytes())
        f = fixtures.function(address, scope, method, tu=1, size=size,
                              kind='inline_or_template', bind=['weak'], names=[symbol], params=params)
        f['mangled'] = symbol
        self.add_function(f)
        self.image.symbols = [SimpleNamespace(type=2, bind=2, defined=True, value=address, name=symbol, size=size)]
        return f, header

    def context(self, f, **kwargs):
        return self.index(**kwargs).build(self.target, '1000: call ' + f['address'])

    def test_three_reviewed_identities_supply_only_existing_headers(self):
        for variant in ('unit','editor','repository'):
            with self.subTest(variant=variant), mock.patch.object(ContextIndex,'_string_template_headers',return_value=True):
                f, header = self.insertion(variant)
                result = self.context(f).require_complete()
                expected = (header,) if variant == 'repository' else ('Pointee.h',header)
                self.assertEqual(result.headers, expected)
                self.assertIn((self.include/header).read_text(), result.text)
                self.assertIn('No specialization or prototype synthesized', result.text)

    def test_source_hash_pins_are_real_reviewed_headers(self):
        source=Path(__file__).resolve().parents[2]/'decomp/include'
        for header,digest in [('TArrayList.h',ContextIndex.WINDOW_ARRAY_HEADER_SHA256),
                              ('TRepository.h',ContextIndex.REPOSITORY_HEADER_SHA256)]:
            self.assertEqual(hashlib.sha256((source/header).read_bytes()).hexdigest(),digest)

    def test_db_identity_mutations_remain_gaps(self):
        changes={'kind':'function','bind':['global'],'method':'clear','params':'int','cv':'const',
                 'qualified':'Other::add','scope':'TArrayList<COther*>','mangled':'_fake',
                 'names':['_fake'],'size':181,'address':'0x1234'}
        for variant in ('unit','editor','repository'):
            for field,value in changes.items():
                with self.subTest(variant=variant,field=field), mock.patch.object(ContextIndex,'_string_template_headers',return_value=True):
                    f,_=self.insertion(variant);address=f['address'];f[field]=value
                    result=self.index().build(self.target,'1000: call '+address)
                    self.assertTrue(result.gaps)

    def test_elf_identity_mutations_remain_gaps(self):
        for variant in ('unit','editor','repository'):
            for change in ('missing','name','size','address','bind','type','undefined'):
                with self.subTest(variant=variant,change=change), mock.patch.object(ContextIndex,'_string_template_headers',return_value=True):
                    f,_=self.insertion(variant);symbol=self.image.symbols[0]
                    if change=='missing':self.image.symbols=[]
                    elif change=='name':symbol.name='_fake'
                    elif change=='size':symbol.size+=1
                    elif change=='address':symbol.value+=1
                    elif change=='bind':symbol.bind=1
                    elif change=='type':symbol.type=1
                    else:symbol.defined=False
                    self.assertTrue(self.context(f).gaps)

    def test_missing_changed_or_stale_template_is_rejected(self):
        for variant in ('unit','editor','repository'):
            for change in ('missing','changed','stale'):
                with self.subTest(variant=variant,change=change), mock.patch.object(ContextIndex,'_string_template_headers',return_value=True):
                    f,header=self.insertion(variant);index=self.index()
                    if change=='missing':(self.include/header).unlink();index=self.index()
                    elif change=='changed':(self.include/header).write_text('// changed\n');index=self.index()
                    else:index.sources[header]+='// stale scanned source\n'
                    self.assertTrue(index.build(self.target,'1000: call '+f['address']).gaps)

    def test_pointer_element_requires_unique_complete_current_header(self):
        for variant in ('unit','editor'):
            for change in ('unmapped','forward','ambiguous','stale'):
                with self.subTest(variant=variant,change=change):
                    f,_=self.insertion(variant);pointee='CBaseUnit' if variant=='unit' else 'CEditorBaseObject';index=None
                    if change=='unmapped':self.mapping.pop(pointee)
                    elif change=='forward':self.write_header('Pointee.h','class '+pointee+';\n')
                    elif change=='ambiguous':
                        self.write_header('OtherPointee.h','class '+pointee+' { int other; };\n');self.mapping[pointee].append('OtherPointee.h')
                    else:
                        index=self.index();self.write_header('Pointee.h','class '+pointee+' { int changed; };\n')
                    self.assertTrue((index or self.index()).build(self.target,'1000: call '+f['address']).gaps)
                    # Keep each subcase independent of preceding mapping/header changes.
                    self.mapping.pop(pointee,None)
                    (self.include/'OtherPointee.h').unlink(missing_ok=True)

    def test_repository_requires_pinned_string_implementation(self):
        f,_=self.insertion('repository')
        with mock.patch.object(ContextIndex,'_string_template_headers',return_value=False):
            self.assertTrue(self.context(f).gaps)

    def test_other_missing_callee_stays_visible(self):
        for variant in ('unit','editor','repository'):
            with self.subTest(variant=variant), mock.patch.object(ContextIndex,'_string_template_headers',return_value=True):
                f,_=self.insertion(variant);self.add_function(fixtures.function(0x3000,'CUnrelated','missing',tu=2))
                result=self.index().build(self.target,'1000: call '+f['address']+'\n1005: call 3000')
                self.assertEqual(len(result.gaps),1);self.assertIn('CUnrelated::missing',result.gaps[0])

    def test_union_destructor_pin_keeps_real_header_and_hash_guard(self):
        source=Path(__file__).resolve().parents[2]/'decomp/include'
        for name in ('TArrayList.h','DescriptorProp.h'):
            (self.include/name).write_bytes((source/name).read_bytes())
        self.mapping['UNIONDATA32BIT']='DescriptorProp.h'
        self.db['tus'][1]['name']='DescriptorProp.cpp'
        scope='TArrayList<UNIONDATA32BIT>'
        names=['_ZN10TArrayListI14UNIONDATA32BITED1Ev','_ZN10TArrayListI14UNIONDATA32BITED2Ev']
        f=fixtures.function(0x70ca90,scope,'~TArrayList',tu=1,size=26,
                            kind='inline_or_template',bind=['weak'],names=names,params='')
        f['mangled']=names[0];self.add_function(f)
        self.image.symbols=[SimpleNamespace(type=2,bind=2,defined=True,value=0x70ca90,name=n,size=26) for n in names]
        result=self.context(f).require_complete()
        self.assertEqual(result.headers,('DescriptorProp.h','TArrayList.h'))
        owner=self.include/'DescriptorProp.h'
        owner.write_text(owner.read_text()+'// unreviewed header change\n')
        self.assertTrue(self.context(f).gaps)

    def test_coherent_unreviewed_template_method_stays_gap(self):
        f,_=self.insertion('unit');old=f['address'];f.update(scope='TArrayList<CCharacter*>',qualified='TArrayList<CCharacter*>::add',params='CCharacter*',mangled='_ZN10TArrayListIP10CCharacterE3addES1_',names=['_ZN10TArrayListIP10CCharacterE3addES1_'])
        self.image.symbols[0].name=f['mangled'];self.write_header('Character.h','class CCharacter { int value; };\n');self.mapping['CCharacter']='Character.h'
        self.assertTrue(self.index().build(self.target,'1000: call '+old).gaps)


class AdditionalInsertionTests(TestCase):
    """Four reviewed identities; no ELF or ignored proposal input is required."""

    setUp = fixtures.PacketContextTests.setUp
    write_header = fixtures.PacketContextTests.write_header
    add_function = fixtures.PacketContextTests.add_function
    index = fixtures.PacketContextTests.index
    rows = (
        ('CSkill*', 0xcd56e0, 180, '_ZN10TArrayListIP6CSkillE3addES1_'),
        ('CDataGroup*', 0xa7e5e0, 180, '_ZN10TArrayListIP10CDataGroupE3addES1_'),
        ('int', 0xa69ec0, 180, '_ZN10TArrayListIiE3addEi'),
        ('bool', 0x90da90, 176, '_ZN10TArrayListIbE3addEb'),
    )

    def insertion(self, row):
        element, address, size, symbol = row
        scope = 'TArrayList<' + element + '>'
        f = fixtures.function(address, scope, 'add', tu=1, size=size,
                              kind='inline_or_template', bind=['weak'],
                              names=[symbol], params=element)
        f['mangled'] = symbol
        self.add_function(f)
        source = Path(__file__).resolve().parents[2] / 'decomp/include/TArrayList.h'
        (self.include/'TArrayList.h').write_bytes(source.read_bytes())
        if element.endswith('*'):
            name = element[:-1]
            self.write_header('Element.h', 'class ' + name + ' { public: int value; };\n')
            self.mapping[name] = 'Element.h'
        self.image.symbols = [SimpleNamespace(type=2, bind=2, defined=True,
                                              value=address, name=symbol, size=size)]
        return f

    def context(self, f, index=None):
        return (index or self.index()).build(self.target, '1000: call ' + f['address'])

    def test_four_reviewed_positive_headers_without_string_runtime(self):
        for row in self.rows:
            with self.subTest(element=row[0]), mock.patch.object(
                    ContextIndex, '_string_template_headers', return_value=False):
                f = self.insertion(row)
                result = self.context(f).require_complete()
                expected = {'TArrayList.h'} | ({'Element.h'} if row[0].endswith('*') else set())
                self.assertEqual(set(result.headers), expected)
                self.assertIn((self.include/'TArrayList.h').read_text(), result.text)
                self.assertIn('No specialization or prototype synthesized', result.text)

    def test_wrong_db_symbol_address_size_kind_and_element_type_rejected(self):
        changes = [('mangled', '_wrong'), ('names', ['_wrong']), ('address', '0x1234'),
                   ('size', 1), ('kind', 'function'), ('bind', ['global']),
                   ('params', 'unsigned int'), ('cv', 'const'),
                   ('qualified', 'Other::add'), ('scope', 'TArrayList<unsigned int>')]
        for row in self.rows:
            for key, value in changes:
                with self.subTest(element=row[0], field=key):
                    f = self.insertion(row)
                    address = f['address']
                    f[key] = value
                    self.assertTrue(self.index().build(self.target, '1000: call ' + address).gaps)

    def test_wrong_or_missing_elf_function_identity_rejected(self):
        changes = [('name', '_wrong'), ('value', 0x1234), ('size', 1), ('bind', 1),
                   ('type', 1), ('defined', False), ('missing', True)]
        for row in self.rows:
            for key, value in changes:
                with self.subTest(element=row[0], field=key):
                    f = self.insertion(row)
                    if key == 'missing':
                        self.image.symbols = []
                    else:
                        setattr(self.image.symbols[0], key, value)
                    self.assertTrue(self.context(f).gaps)

    def test_header_digest_and_scanned_freshness_rejected(self):
        for row in self.rows:
            for change in ('digest', 'stale', 'missing'):
                with self.subTest(element=row[0], change=change):
                    f = self.insertion(row)
                    index = self.index()
                    header = self.include/'TArrayList.h'
                    if change == 'digest':
                        header.write_text(header.read_text() + '// changed\n')
                        index = self.index()
                    elif change == 'stale':
                        index.sources['TArrayList.h'] += '// stale\n'
                    else:
                        header.unlink()
                        index = self.index()
                    self.assertTrue(self.context(f, index).gaps)

    def test_pointer_type_requires_unique_complete_current_header(self):
        for row in self.rows:
            if not row[0].endswith('*'):
                continue
            for change in ('unmapped', 'forward', 'ambiguous', 'stale'):
                with self.subTest(element=row[0], change=change):
                    f = self.insertion(row)
                    name = row[0][:-1]
                    index = None
                    if change == 'unmapped':
                        self.mapping.pop(name)
                    elif change == 'forward':
                        self.write_header('Element.h', 'class ' + name + ';\n')
                    elif change == 'ambiguous':
                        self.write_header('Other.h', 'class ' + name + ' { int other; };\n')
                        self.mapping[name] = ['Element.h', 'Other.h']
                    else:
                        index = self.index()
                        self.write_header('Element.h', 'class ' + name + ' { int changed; };\n')
                    self.assertTrue(self.context(f, index).gaps)
                    (self.include/'Other.h').unlink(missing_ok=True)


if __name__=='__main__':main()
