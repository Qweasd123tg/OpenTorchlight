"""Indexed EH lookups retain the conservative overlap gate exactly."""
from dataclasses import FrozenInstanceError
import random
import unittest

from objdiff_eh import Frames


def linear(frames, start, size, section):
    matches = [(lo, hi, why, personality) for sec, lo, hi, why, personality in frames.ranges
               if sec == section and lo < start + size and start < hi]
    if frames.error:
        reason = frames.error
    elif any(lo > start or hi < start + size for lo, hi, _, _ in matches):
        reason = "EH FDE partially overlaps function; association unverified"
    elif len(matches) > 1:
        reason = "multiple EH FDEs overlap function; association unverified"
    else:
        reason = matches[0][2] if matches else None
    return reason, sorted({p for _, _, _, p in matches if p})


class IndexedEH(unittest.TestCase):
    def compare(self, frames, *query):
        self.assertEqual(linear(frames, *query), (frames.reason(*query), frames.personalities(*query)))

    def test_nested_duplicate_and_partial_ranges_are_not_hidden_by_nearest_start(self):
        frames = Frames([(None, 0, 100, None, "outer"), (None, 30, 40, None, "inner"),
                         (None, 30, 40, "LSDA", "duplicate"), (None, 50, 70, None, None)])
        for query in ((35, 1, None), (25, 10, None), (40, 5, None), (50, 20, None), (95, 10, None)):
            self.compare(frames, *query)
        self.assertIn("multiple", frames.reason(35, 1))
        self.assertIn("partially", frames.reason(25, 10))
        self.assertEqual(["duplicate", "inner", "outer"], frames.personalities(35, 1))

    def test_sections_and_half_open_boundaries(self):
        frames = Frames([(1, 10, 20, "LSDA", "p1"), (2, 10, 20, None, "p2")])
        for section in (None, 1, 2, 3):
            for start, size in ((10, 10), (0, 10), (20, 1), (10, 0), (15, 0), (9, 2)):
                self.compare(frames, start, size, section)
        self.assertEqual("LSDA", frames.reason(10, 10, 1))
        self.assertIsNone(frames.reason(10, 10, 2))

    def test_error_remains_global_and_personalities_keep_their_original_behavior(self):
        frames = Frames([(None, 1, 20, None, "p")], "malformed section")
        self.compare(frames, 2, 3, None)
        self.compare(frames, 200, 3, None)
        self.assertEqual("malformed section", frames.reason(200, 3))

    def test_snapshot_cannot_acquire_a_stale_index(self):
        rows = [(None, 1, 20, None, None)]
        frames = Frames(rows)
        rows.append((None, 2, 10, "unverified", None))
        self.assertEqual(1, len(frames.ranges))
        self.assertIsNone(frames.reason(3, 1))
        with self.assertRaises(FrozenInstanceError):
            frames.ranges = ()

    def test_index_matches_linear_gate_on_unsorted_and_overlapping_inputs(self):
        rng = random.Random(7)
        for _ in range(100):
            frames = Frames([(rng.choice((None, 1, 2)), rng.randint(-5, 100), rng.randint(-5, 100),
                              rng.choice((None, "LSDA", "bad encoding")), rng.choice((None, "p0", "p1")))
                             for _ in range(30)], rng.choice((None, None, "malformed section")))
            for _ in range(60):
                self.compare(frames, rng.randint(-10, 110), rng.randint(-2, 25), rng.choice((None, 1, 2, 3)))


if __name__ == "__main__":
    unittest.main()
