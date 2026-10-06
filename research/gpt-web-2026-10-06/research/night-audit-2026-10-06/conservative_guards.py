"""Research reference guards. No production import or state mutation.

Snapshot hashing trades additional invalidations for avoiding false freshness.
Object identity is for reusing a test result, NOT a semantic MATCH proof.
"""
import hashlib,json

def digest_bytes(data):
 return hashlib.sha256(data).hexdigest()

def manifest_digest(values):
 return digest_bytes(json.dumps(values,sort_keys=True,separators=(',',':')).encode())

def draft_fingerprint(*,elf_sha,exported_types,tool_digests,header_input_digests):
 return manifest_digest({'schema':'draft-input-v2-conservative','elf':elf_sha,'types':exported_types,'tools':tool_digests,'header_inputs':header_input_digests})

def reusable_test_fingerprint(*,object_bytes,elf_sha,harness_inputs,link_inputs,mutation_inputs):
 return manifest_digest({'schema':'accepted-test-v2-conservative','object':digest_bytes(object_bytes),'elf':elf_sha,'harness':harness_inputs,'link':link_inputs,'mutation':mutation_inputs})

def reusable(stored,current):
 return bool(stored) and stored==current
