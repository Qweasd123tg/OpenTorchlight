"""Bounded, session-local reuse of original disassembly, not MATCH evidence.

The opt-in TU route decodes each bounded original range once. It is used only
when both target endpoints are instruction boundaries in the batch; otherwise
it executes the existing exact --start-address/--stop-address command. No
normalized instructions, references, jump-table or EH checks are bypassed.
"""
from bisect import bisect_left
from collections import OrderedDict
import threading


class OriginalInstructions:
    def __init__(self, db, image, run, parse, *, mode="function", max_groups=4,
                 max_range_bytes=262144, max_single_entries=32):
        if mode not in ("function", "tu"):
            raise ValueError("OTL_ORIGINAL_DISASM must be 'function' or 'tu'")
        if min(max_groups, max_range_bytes, max_single_entries) < 1:
            raise ValueError("disassembly cache limits must be positive")
        self.image, self.run, self.parse, self.mode = image, run, parse, mode
        self.max_groups, self.max_range_bytes = max_groups, max_range_bytes
        self.max_single_entries = max_single_entries
        self.groups, self.single, self.ranges = OrderedDict(), OrderedDict(), {}
        self.lock = threading.RLock()
        self.stats = dict(batch_commands=0, individual_commands=0, hits=0,
                          boundary_fallbacks=0, evictions=0)
        for function in db["functions"].values():
            size = function.get("size", 0)
            if size <= 0:
                continue
            start = int(function["address"], 16)
            tu = function.get("tu")
            old = self.ranges.get(tu)
            self.ranges[tu] = (min(start, old[0]), max(start+size, old[1]), old[2]+1) if old else (start, start+size, 1)

    def _decode(self, start, end):
        return self.parse(self.run([f"--start-address={start:#x}",
                                    f"--stop-address={end:#x}", str(self.image.path)]))

    def _individual(self, start, end):
        key = start, end
        if key in self.single:
            self.single.move_to_end(key)
            self.stats["hits"] += 1
            return [list(row) for row in self.single[key]]
        self.stats["individual_commands"] += 1
        rows = self._decode(start, end)
        # Do not retain unusually large functions in a many-entry cache.
        if len(rows) <= 2048:
            self.single[key] = rows
            while len(self.single) > self.max_single_entries:
                self.single.popitem(last=False)
                self.stats["evictions"] += 1
        return [list(row) for row in rows]

    def instructions(self, function):
        with self.lock:
            start = int(function["address"], 16)
            end = start + function["size"]
            tu = function.get("tu")
            bound = self.ranges.get(tu)
            if self.mode == "function" or not bound or end <= start:
                return self._individual(start, end)
            lo, hi, count = bound
            section = self.image.section_at(lo)
            if (tu is None or count < 2 or hi-lo > self.max_range_bytes or section is None
                    or self.image.section_at(hi-1) is not section):
                return self._individual(start, end)
            if tu not in self.groups:
                self.stats["batch_commands"] += 1
                rows = self._decode(lo, hi)
                addresses = [row[0] for row in rows]
                # Multiple sections or unexpected decoder ordering are not sliced.
                if any(a >= b for a, b in zip(addresses, addresses[1:])):
                    self.stats["boundary_fallbacks"] += 1
                    return self._individual(start, end)
                self.groups[tu] = (rows, addresses)
                while len(self.groups) > self.max_groups:
                    self.groups.popitem(last=False)
                    self.stats["evictions"] += 1
            else:
                self.stats["hits"] += 1
                self.groups.move_to_end(tu)
            rows, addresses = self.groups[tu]
            first, last = bisect_left(addresses, start), bisect_left(addresses, end)
            start_ok = first < len(addresses) and addresses[first] == start
            # The group endpoint was already imposed by objdump itself. All
            # interior endpoints must occur as explicit decoded boundaries.
            end_ok = end == hi or (last < len(addresses) and addresses[last] == end)
            if not start_ok or not end_ok:
                self.stats["boundary_fallbacks"] += 1
                return self._individual(start, end)
            return [list(row) for row in rows[first:last]]
