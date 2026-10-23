"""Compiler-free cleanup LSDA boundary and per-call isolation regressions."""
from types import SimpleNamespace
import unittest

import objdiff_eh


def fixture(offsets=(0, 4), rows=((0, 8, 4, 0),), section=None):
    # These bounded fixtures use single-byte ULEB128 values only.
    body = bytes(value for row in rows for value in row)
    data = b'\xff\xff\x01' + bytes([len(body)]) + body
    image = SimpleNamespace(data=data, sections=[SimpleNamespace(
        offset=0, size=len(data), addr=4096, index=0)],
        relocs={} if section is not None else [])
    frames = objdiff_eh.Frames(
        ((section, 128, 136, 'EH LSDA equivalence unverified', '__gxx_personality_v0'),),
        lsdas=((section, 128, 136, 0, 0, None),))
    insns = [(128 + offset, 'nop', '') for offset in offsets]
    return image, frames, insns


def signature(image, frames, insns, section=None):
    return objdiff_eh.cleanup_signature(image, frames, 128, 8, insns, section)


class CleanupBoundaries(unittest.TestCase):
    def test_every_instruction_subset_and_landing_pad(self):
        for mask in range(128):
            offsets = [0] + [i + 1 for i in range(7) if mask >> i & 1]
            for pad in range(10):
                for section in (None, 3):
                    with self.subTest(offsets=offsets, pad=pad, section=section):
                        args = fixture(offsets, ((0, 8, pad, 0),), section)
                        self.assertEqual(signature(*args, section) is not None,
                                         pad == 0 or pad in offsets)

    def test_later_bad_landing_pad_is_not_hidden(self):
        self.assertIsNotNone(signature(*fixture(rows=((0, 4, 0, 0), (4, 4, 4, 0)))))
        self.assertIsNone(signature(*fixture(rows=((0, 4, 0, 0), (4, 4, 8, 0)))))

    def test_malformed_offsets_fail_closed(self):
        for offsets in ((), (1,), (0, 0), (0, 2, 1), (0, 8), (0, 9), (-1, 0), (0, -1)):
            with self.subTest(offsets=offsets):
                self.assertIsNone(signature(*fixture(offsets)))

    def test_list_tuple_and_one_shot_iterator_agree(self):
        image, frames, insns = fixture()
        expected = signature(image, frames, insns)
        self.assertIsNotNone(expected)
        self.assertEqual(signature(image, frames, tuple(insns)), expected)
        self.assertEqual(signature(image, frames, iter(insns)), expected)
        self.assertIsInstance(expected, tuple)
        self.assertIsInstance(expected[2], tuple)
        self.assertIsInstance(expected[3], tuple)
        self.assertIsInstance(expected[3][0], tuple)

    def test_each_call_observes_changed_instruction_and_image_inputs(self):
        image, frames, insns = fixture()
        expected = signature(image, frames, insns)
        insns.pop()
        self.assertIsNone(signature(image, frames, insns))
        insns.append((132, 'nop', ''))
        self.assertEqual(signature(image, frames, insns), expected)
        original = image.data
        image.data = original[:-2] + b'\x08' + original[-1:]
        self.assertIsNone(signature(image, frames, insns))
        image.data = original
        self.assertEqual(signature(image, frames, insns), expected)


if __name__ == '__main__':
    unittest.main()
