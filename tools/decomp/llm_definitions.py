"""Fail-closed boundaries for a model's one-definition response."""
import re
from collections import defaultdict
from types import MappingProxyType

import ghidra_cpp
import mutate


def single_definition(f, code):
    """Reject extra top-level definitions/directives before compiling model text."""
    masked = mutate.mask(code)
    if re.search(r"(?m)^\s*#", masked):
        return "Return only the definition, without preprocessor directives."
    span = mutate.definition(code, masked, f)
    if not span or span[1] < span[0]:
        return "No unique complete definition with the requested signature."
    prefix, suffix = masked[:span[0]], masked[span[1] + 1:]
    if any(token in prefix for token in ("{", "}", ";")) or suffix.strip():
        return "The response contains declarations or definitions besides the requested function."
    # mutate.definition normally uses arity to locate a body for mutation. A
    # model response needs the exact parameter types, not only that locator.
    qualified = f["demangled"].split("(", 1)[0]
    declaration = re.search(re.escape(qualified) + r"\s*\(", prefix)
    if declaration is None:
        return "The requested qualified function name is absent."
    close = mutate.matching(masked, declaration.end() - 1, "(", ")")
    params = masked[declaration.end():close].strip()
    actual = [mutate.canonical_parameter(ghidra_cpp.cxx_type(p), named=True) for p in ghidra_cpp.split_args(params)
              if p.strip() and p.strip() != "void"]
    expected = [mutate.canonical_parameter(ghidra_cpp.cxx_type(p)) for p in ghidra_cpp.split_args(f.get("params") or "")
                if p.strip() and p.strip() != "void"]
    if actual != expected:
        return "Parameter types differ from the requested symbol."
    return None


def identity(f):
    qualified = f.get("qualified") or f["demangled"].split("(", 1)[0]
    qualified = re.sub(r"^(?:non-virtual|virtual|covariant return) thunk to ", "", qualified)
    return qualified, f.get("params", ""), f.get("cv", "")


def closure(f, db):
    """Original addresses of the same C++ definition, including ABI thunks/variants."""
    wanted = identity(f)
    return {address for address, other in db["functions"].items()
            if other.get("tu") == f.get("tu") and other.get("kind") != "compiler"
            and identity(other) == wanted}


def verdict(f, unit, db):
    """All emitted variants must match; a receipt for one cannot accept another."""
    addresses = closure(f, db)
    emitted = [row for row in unit["functions"] if row.get("address") in addresses
               and row["status"] not in ("MISSING", "EXTRA")]
    target = [row for row in emitted if row["address"] == f["address"] and not row.get("weak")]
    if not target:
        return "compile-error", "The requested definition was not emitted as a strong original symbol."
    failed = [row for row in emitted if row["status"] != "MATCH"]
    if failed:
        return "DIFF", "Emitted ABI variants differ: " + ", ".join(
            row["address"] for row in failed)
    return "MATCH", ""


class DefinitionIndex:
    """Explicit immutable index of one ELF symbol snapshot; no process-global cache.

    Construct again after loading a different database. Only the closure lookup
    is optimized: no statuses or MATCH receipts are cached here. The caller's
    dictionaries are not retained or modified. Passing a newly built index is
    therefore safe across worktrees and repeated restoration attempts.
    """
    def __init__(self, db):
        groups = defaultdict(set)
        for address, other in db["functions"].items():
            if other.get("kind") != "compiler":
                groups[(other.get("tu"), identity(other))].add(address)
        self._groups = MappingProxyType({key: frozenset(value)
                                         for key, value in groups.items()})
        self.function_count = len(db["functions"])

    def closure(self, f):
        # A fresh set preserves the public closure() API and prevents mutation
        # of the shared snapshot by downstream set operations.
        return set(self._groups.get((f.get("tu"), identity(f)), ()))

    def verdict(self, f, unit):
        return self.verdicts([f], unit)[0]

    def verdicts(self, functions, unit):
        """Same order, duplicates, weak-symbol and ABI rules as verdict()."""
        functions = list(functions)
        closures = [self.closure(f) for f in functions]
        relevant = set().union(*closures) if closures else set()
        positions = defaultdict(list)
        for number, row in enumerate(unit["functions"]):
            if row.get("address") in relevant and row["status"] not in ("MISSING", "EXTRA"):
                positions[row.get("address")].append((number, row))
        answers = []
        for f, addresses in zip(functions, closures):
            emitted = [item for address in addresses
                       for item in positions.get(address, ())]
            # Reasons retain the original object-report order, not hash order.
            emitted.sort(key=lambda item: item[0])
            rows = [item[1] for item in emitted]
            target = [r for r in rows if r["address"] == f["address"] and not r.get("weak")]
            if not target:
                answers.append(("compile-error", "The requested definition was not emitted as a strong original symbol."))
                continue
            failed = [r for r in rows if r["status"] != "MATCH"]
            if failed:
                answers.append(("DIFF", "Emitted ABI variants differ: " + ", ".join(r["address"] for r in failed)))
            else:
                answers.append(("MATCH", ""))
        return answers
