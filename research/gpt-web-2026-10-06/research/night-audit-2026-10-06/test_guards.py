from pathlib import Path
import copy,json
from conservative_guards import draft_fingerprint,reusable_test_fingerprint,reusable
base={'elf_sha':'elf','exported_types':{'classes':{'Base':{'size':8},'Derived':{'base':'Base'}},'prototypes':{'own':'int','callee':'int'},'vtables':{'Derived':['slot0']}},'tool_digests':{'ghidra':'v1'},'header_input_digests':{'base.h':'h1'}}
old=draft_fingerprint(**base);checks=[]
for name,change in [
 ('callee',lambda x:x['exported_types']['prototypes'].update(callee='double')),
 ('base',lambda x:x['exported_types']['classes']['Base'].update(size=16)),
 ('vtable',lambda x:x['exported_types']['vtables']['Derived'].append('slot1')),
 ('tool',lambda x:x['tool_digests'].update(ghidra='v2')),
 ('header',lambda x:x['header_input_digests'].update({'base.h':'h2'})),
 ('elf',lambda x:x.update(elf_sha='other'))]:
 x=copy.deepcopy(base);change(x);assert not reusable(old,draft_fingerprint(**x));checks.append(name)
assert reusable(old,draft_fingerprint(**copy.deepcopy(base)));assert not reusable(None,old)
p=Path(__file__).parent/'acceptance';context={'elf_sha':'pinned','harness_inputs':{'selftest':'h1'},'link_inputs':{'sdk':'s1'},'mutation_inputs':{'generator':'m1','seed':123,'cases':100}}
fp=lambda name:reusable_test_fingerprint(object_bytes=(p/(name+'.o')).read_bytes(),**context)
for a,b in [('lit80a','lit80b'),('lit300a','lit300b'),('catch_int','catch_double')]:
 assert fp(a)!=fp(b);checks.append(a+' vs '+b)
old=fp('catch_int');context['harness_inputs']['selftest']='h2';assert old!=fp('catch_int');checks.append('harness changed')
out={'changed_inputs_rejected':checks,'unchanged_accepted':True,'legacy_missing_digest_rejected':True,'scope':'fingerprint tests only; no production integration and no semantic equivalence proof'}
(Path(__file__).parent/'guard-results.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out))
