#!/usr/bin/env python3
"""Evidence must preserve widths and stop conclusions at ambiguous state."""
import copy
import io
from pathlib import Path
import stat
import sys
import unittest
import zipfile

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from analyze_pcode import analyze
from original import SUPPORTED_SHA256
from setup_ghidra import checked_members, DIRECTORY


def node(space, offset, size=8, register=None):
    return dict(space=space, space_id=1, offset=hex(offset), size=size,
                constant=space=='const', register=register)


def op(name, inputs, output=None, index=0):
    return dict(operation=name, inputs=inputs, output=output, index=index)


def instruction(address, operations):
    return dict(address=hex(address), pcode=operations, flows=[], fallthrough=None,
                is_computed=False, is_terminal=False)


def packet(rows, blocks=()):
    return dict(schema=2, address='0x1000', symbol='raw-test',
                original_elf_sha256=SUPPORTED_SHA256, instructions=rows,
                basic_blocks=[dict(entry=hex(b)) for b in blocks])


RDI=node('register',0x38,8,'RDI')
RAX=node('register',0,8,'RAX')
EAX=node('register',0,4,'EAX')
TMP=node('unique',0x100)
RAM=node('const',1,4)


class EvidenceBoundaries(unittest.TestCase):
    def test_addressing_retains_exact_store_width_without_a_field_name(self):
        evidence=analyze(packet([instruction(0x1000,[
            op('INT_ADD',[RDI,node('const',0x180)],TMP),
            op('STORE',[RAM,TMP,node('register',0x30,8,'RSI')],index=1)])]))
        self.assertEqual(evidence['locations'][0]['location'],
                         dict(base='block-register-input',register='RDI',block='0x1000',offset='0x180'))
        self.assertEqual(evidence['memory_accesses'][0]['bytes'],8)
        self.assertNotIn('field',str(evidence))
        self.assertEqual(evidence['original_status_promotions'],0)

    def test_partial_register_write_cannot_reuse_old_wide_value(self):
        evidence=analyze(packet([instruction(0x1000,[
            op('COPY',[RDI],RAX),op('COPY',[node('const',7,4)],EAX,index=1),
            op('STORE',[RAM,RAX,node('const',1,1)],index=2)])]))
        self.assertEqual(evidence['memory_accesses'][0]['address_expression']['operation'],'unknown')

    def test_calls_and_block_joins_do_not_invent_preserved_values(self):
        for boundary in ('call','join'):
            rows=[instruction(0x1000,[op('COPY',[RDI],RAX)])]
            if boundary=='call': rows.append(instruction(0x1001,[op('CALL',[node('ram',0x3000)])]))
            rows.append(instruction(0x1002,[op('STORE',[RAM,RAX,node('const',1,1)])]))
            evidence=analyze(packet(rows,blocks=(0x1002,) if boundary=='join' else ()))
            expression=evidence['memory_accesses'][0]['address_expression']
            self.assertEqual(expression['operation'],'unknown' if boundary=='call' else 'block_input')
            if boundary=='join': self.assertEqual(expression['register'],'RAX')
            else: self.assertEqual(evidence['unresolved'][0]['code'],'external_effects_not_modeled')

    def test_unique_temporaries_do_not_carry_between_instructions(self):
        evidence=analyze(packet([instruction(0x1000,[op('COPY',[RDI],TMP)]),
                                instruction(0x1001,[op('LOAD',[RAM,TMP],EAX)])]))
        self.assertEqual(evidence['memory_accesses'][0]['address_expression']['operation'],'unknown')

    def test_internal_micro_branch_preserves_raw_access_with_unknown_address(self):
        evidence=analyze(packet([instruction(0x1000,[
            op('CBRANCH',[node('const',2),node('register',0x201,1,'ZF')]),
            op('STORE',[RAM,RDI,node('const',7,4)],index=1)])]))
        self.assertEqual(evidence['unresolved'][0]['code'],'internal_pcode_flow_not_solved')
        self.assertEqual(evidence['locations'][0]['status'],'unresolved-address')
        self.assertEqual(evidence['memory_accesses'][0]['bytes'],4)

    def test_schema_identity_and_invalid_width_are_rejected(self):
        base=packet([instruction(0x1000,[op('LOAD',[RAM,RDI],EAX)])])
        for edit in (lambda x:x.update(schema=1), lambda x:x.update(original_elf_sha256='0'*64),
                     lambda x:x['instructions'][0]['pcode'][0]['inputs'][1].update(size=0)):
            altered=copy.deepcopy(base);edit(altered)
            with self.assertRaises(ValueError):analyze(altered)

    def test_archive_paths_and_symlinks_cannot_escape_pinned_tool_root(self):
        for filename,symlink in ((DIRECTORY+'/support/file',False),('../escape',False),
                                 (DIRECTORY+'/../escape',False),('/absolute',False),
                                 (DIRECTORY+'/link',True),('other/file',False)):
            buffer=io.BytesIO()
            with zipfile.ZipFile(buffer,'w') as archive:
                entry=zipfile.ZipInfo(filename)
                if symlink:entry.external_attr=(stat.S_IFLNK|0o777)<<16
                archive.writestr(entry,b'input')
            with zipfile.ZipFile(buffer) as archive:
                if filename==DIRECTORY+'/support/file':self.assertEqual(len(checked_members(archive)),1)
                else:
                    with self.assertRaises(ValueError):checked_members(archive)


if __name__=='__main__':unittest.main()
