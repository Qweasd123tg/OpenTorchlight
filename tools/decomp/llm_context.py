"""Automatic read-only, one-hop packet context; no ELF/DB loads or subprocesses.

Construct ContextIndex once from Loop's already-loaded db/image and hand-header map,
after header preparation. build() consumes the same exact ASM that the prompt shows.
This is deliberately a shallow declaration scanner, not a C++ parser or a type oracle.
"""
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import re
import hashlib
import os

import headers as declaration_headers
import ghidra_cpp


class ContextError(ValueError):
    """Bad/unreadable input, unsafe extraction, or a mandatory budget overflow."""


@dataclass(frozen=True)
class Context:
    text: str
    headers: tuple[str, ...]
    gaps: tuple[str, ...]

    def require_complete(self):
        if self.gaps:
            raise ContextError("packet context unresolved: " + "; ".join(self.gaps))
        return self


@dataclass(frozen=True)
class Declaration:
    qualified: str
    kind: str
    text: str
    scopes: tuple[tuple[str, str], ...]
    array_width: int = 0


@dataclass(frozen=True)
class LocalType:
    name: str
    text: str
    safe: bool
    reason: str = ""


def _address(value):
    return value if isinstance(value, int) else int(value, 16)


def _basename(name):
    if (not isinstance(name, str) or not name.strip() or name.startswith(".")
            or any(c in name for c in "/\\\0\n\r")):
        raise ContextError(f"expected a plain basename, got {name!r}")
    return name


def _mask(text):
    # Keep offsets and line breaks. A brace in a comment/string is not a C++ brace.
    pattern = r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\''
    masked = re.sub(pattern, lambda m: re.sub(r"[^\n]", " ", m[0]), text)
    return re.sub(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*",
                  lambda m: re.sub(r"[^\n]", " ", m[0]), masked, flags=re.M)


def _scan(text):
    """Only simple declarations outside function bodies; exact source slices.

    Namespace/class scopes are retained. Function-pointer/compound declarations,
    macros, anonymous namespaces and general C++ syntax are not guessed.
    A TU-local class is safe only if it has no nested braces (in particular no
    inline bodies). Unsupported selected local types cause a blocking error.
    """
    masked = _mask(text)
    stack, declarations, types = [], [], []
    start = 0
    for delimiter in re.finditer(r"[{};]", masked):
        i, token = delimiter.start(), delimiter[0]
        head = masked[start:i].strip()
        if token == "{":
            ns = re.fullmatch(r"namespace\s+(\w+)", head)
            cls = re.fullmatch(r"(?:class|struct)\s+(\w+)\s*(?::[^{};]*)?", head)
            array = re.fullmatch(r"(?:static\s+)?const\s+std::(?:w?string)\s+(\w+)\s*\[\s*(?:[0-9]+)?\s*\]\s*=", head)
            kind, name = (("namespace", ns[1]) if ns else
                          ("class", cls[1]) if cls else
                          ("string_array", array[1]) if array else ("body", ""))
            scopes = tuple((k, n) for k, n, *_ in stack)
            stack.append((kind, name, start, i, scopes))
            start = i + 1
        elif token == "}":
            if stack:
                kind, name, beginning, opening, scopes = stack.pop()
                if kind == "string_array" and all(k == "namespace" for k, _ in scopes):
                    # Only literal-only std::string/wstring arrays already in a
                    # header. Retain the complete initializer; never infer bytes
                    # or accept calls/macros/nested initializer expressions.
                    literal = r'(?:L)?"(?:\\.|[^"\\])*"'
                    values = text[opening + 1:i]
                    tail = re.match(r"\s*;", masked[i + 1:])
                    if tail and re.fullmatch(r"\s*" + literal + r"(?:\s*,\s*" + literal + r")*\s*,?\s*", values):
                        first = re.search(r"\S", masked[beginning:opening])
                        declaration = text[beginning + first.start():i + 1 + tail.end()].strip()
                        qualified = "::".join([n for _, n in scopes] + [name])
                        declarations.append(Declaration(qualified, "data", declaration, scopes, 0))
                if kind == "class":
                    end = i + 1
                    semicolon = re.match(r"\s*;", masked[end:])
                    if semicolon:
                        end += semicolon.end()
                        beginning += re.search(r"\S", masked[beginning:opening]).start()
                        reason = ("non-top-level/anonymous scope" if scopes else
                                  "nested braces/inline bodies" if re.search(r"[{}]", masked[opening + 1:i]) else "")
                        types.append(LocalType(name, text[beginning:end].strip(),
                                               not reason, reason))
            start = i + 1
        else:
            scopes = tuple((k, n) for k, n, *_ in stack)
            if all(k in ("class", "namespace") for k, _ in scopes):
                # Strip access labels, not the contents of the following declaration.
                clean = re.sub(r"^(?:public|protected|private)\s*:\s*", "", head)
                first = re.search(r"\S", masked[start:i])
                original = text[start + first.start():i + 1].strip() if first else ""
                original = re.sub(r"^(?:public|protected|private)\s*:\s*", "", original)
                fn = re.search(r"(?<![\w:])(~?\w+)\s*\(", clean)
                if fn and "=" not in clean[:fn.start()] and not clean.startswith(("typedef ", "using ")):
                    name, kind, width = fn[1], "function", 0
                else:
                    var = re.fullmatch(r"(.+?)\b((?:\w+::)*\w+)\s*((?:\[[^\]]*\]\s*)*)", clean)
                    if (not var or any(c in clean for c in "(),=")
                            or clean.startswith(("typedef ", "using ", "class ", "struct ", "enum "))):
                        start = i + 1
                        continue
                    name, kind, width = var[2], "data", 0
                    # A pointer object is not its pointee; unsigned-char blobs are not strings.
                    typ = var[1].strip()
                    if var[3] and re.fullmatch(r"(?:(?:extern|static|const)\s+)*(?:char|wchar_t)(?:\s+const)?", typ):
                        width = 4 if re.search(r"\bwchar_t\b", typ) else 1
                qualified = "::".join([n for _, n in scopes] + [name])
                declarations.append(Declaration(qualified, kind, original, scopes, width))
            start = i + 1
    return declarations, types


def _standard_string_aliases(text):
    """Only the two standard typedefs in the pinned pre-C++11 string ABI.

    Normalize before the shared parser strips whitespace or moves const. No
    custom traits/allocator, inline ABI namespace, or similarly named namespace.
    This changes lookup text only, never the supplied source declaration.
    """
    pattern = (r"(?<![\w:])std::basic_string\s*<\s*(char|wchar_t)\s*,\s*"
               r"std::char_traits\s*<\s*\1\s*>\s*,\s*"
               r"std::allocator\s*<\s*\1\s*>\s*>" )
    return re.sub(pattern, lambda m: "std::wstring" if m[1] == "wchar_t" else "std::string", text)


def _declares_callee(declaration, callee):
    """Match parameter and member-cv identity, never a name-only overload.

    Reuse the existing conservative declaration parser. Return type and static
    status are not encoded by ordinary Itanium names and are deliberately not
    inferred here. Unsupported declarators / unresolved typedefs remain gaps.
    """
    if "params" not in callee or "cv" not in callee:
        return False
    method = callee.get("method", "")
    if not re.fullmatch(r"~?[A-Za-z_]\w*", method):
        return False
    text = _standard_string_aliases(declaration.text)
    # The shared parser's word boundary is before an identifier, not '~'.
    if method.startswith("~"):
        text = re.sub(r"~\s*" + re.escape(method[1:]) + r"(?=\s*\()", method[1:], text)
        method = method[1:]
    canonical = dict(callee, params=_standard_string_aliases(callee["params"]))
    expected = ghidra_cpp.signature_key(canonical)[1:3]
    declared = declaration_headers.declared_signatures(text, method)
    return any((params, cv) == expected for params, cv, _static in declared)


def _instructions(f, asm):
    start, end = _address(f["address"]), _address(f["address"]) + int(f["size"])
    if start <= 0 or end <= start:
        raise ContextError("target needs a nonzero address and positive byte size")
    pattern = r"^\s*([0-9a-fA-F]+):\s+(?:(?:[0-9a-fA-F]{2})\s+)*([a-z][a-z0-9.]*)\s*(.*)$"
    out = []
    for line in asm.splitlines():
        m = re.match(pattern, line)
        if m and start <= int(m[1], 16) < end:
            out.append((int(m[1], 16), m[2], m[3]))
    return out


def _references(f, asm):
    calls, data, notes = set(), set(), set()
    insns = _instructions(f, asm)
    if not insns:
        raise ContextError("no instructions for the target range in supplied ASM")
    start, end = _address(f["address"]), _address(f["address"]) + int(f["size"])
    for address, mnemonic, operands in insns:
        code = operands.split("#", 1)[0].split(";", 1)[0].strip()
        if mnemonic in ("call", "callq", "jmp", "jmpq"):
            direct = re.match(r"^(?:0x)?([0-9a-fA-F]+)(?:\s|$)", code)
            if direct:
                value = int(direct[1], 16)
                if not start <= value < end:
                    calls.add(value)
            elif mnemonic.startswith("call"):
                notes.add(f"Indirect call at {address:#x}: callee is unresolved, not inferred from labels.")
            # A jump table's absolute base still needs data context.
            if direct:
                continue
        # Objdump's RIP target comment is numeric evidence; symbol annotations are not.
        rip = re.search(r"#\s*(?:0x)?([0-9a-fA-F]+)\b", operands)
        if rip:
            data.add(int(rip[1], 16))
        elif "%rip" in code:
            notes.add(f"RIP reference at {address:#x} lacks a numeric target; not guessed.")
        for m in re.finditer(r"(?<![\w%-])0x([0-9a-fA-F]+)\b", code):
            if not code[m.end():].startswith("(%rip)"):
                data.add(int(m[1], 16))
    return sorted(calls), sorted(data), sorted(notes)


class ContextIndex:
    """Reusable source/DB index. The image is borrowed, never reopened or modified."""

    # Reviewed SDK files for the pinned x86-64 profile; changed/unlisted inputs
    # remain gaps until explicitly reviewed. These are not namespace exemptions.
    CEGUI_HEADER_SHA256 = {
        'CEGUIWindow.h': '37f12e0e538df1cb67271ced354dae55d2be7a1d35830f00d77bae819d09b792',
        'CEGUIString.h': '0f6b99906ae55d7d8f35e4a50e249d76baaa7ec21d5ecd3b068822364429e6fe',
        'CEGUISingleton.h': 'ad721b29935815b6e943f1963732b63e62440760eea8e1f60a80f602fa942319',
        'CEGUIImagesetManager.h': 'bbe90f6bbe3918154df40927df1855a9bba5a13e5d4412b584217f565b5718a4',
        'CEGUIWindowManager.h': '3a89509c2f777e572723dd0161f5623a6850703ac43ffc26d4c6e4a630a70f31',
        'CEGUIFontManager.h': 'abe0d240dfee54a6f153bc6ab457726829f39ba85b9e24bd00dbeac4db95aec4',
        'CEGUISchemeManager.h': '9312ad97c424bfe9ea5e244bd4f8265c1880d293b8af33bfe0088ae9f4552136',
    }

    OGRE_HEADER_SHA256 = {'OgreResourceGroupManager.h': '1ff3bf682e6723128544d4f0d948fc7408b1179cb1bb42961f80e1967b107529', 'OgrePrerequisites.h': '50f2942df14c86e7b94ff7bebd3e69582b9f9a255952250a2f42c24e1129b32a', 'OgrePlatform.h': '2a985daab37135a00251daae5973e7be8ce0a64e1fb12bb1d5a0280627ecf0e5', 'OgreConfig.h': 'a4252bb5b0f6cf860f335c4d34f29946225c79e3c8392ef7e8ce6107c7c36aaf'}
    OGRE_CONFIG_SHA256 = '0a11e5cd5b3dafe9f832362747afb8147f24f912c88a1e31a303dd466ca47317'

    SAFE_POINTER_HEADER_SHA256 = "f9b4be018fdd063427743f5035c9b297f883475e373a3610b7fdeb2450d9bb47"

    DIAGNOSTIC_BYTES = 32
    STRING_SCAN_LIMIT = 8192
    LIBRARY_SCOPES = {"std", "__gnu_cxx", "__cxxabiv1", "Ogre", "CEGUI", "ParticleUniverse", "FMOD", "boost"}

    def __init__(self, *, root, db, image, headers):
        self.root, self.db, self.image = Path(root).resolve(), db, image
        self.mapping = {key: tuple(sorted({_basename(n) for n in
                                         ([value] if isinstance(value, str) else value)}))
                        for key, value in headers.items()}
        self.functions = {_address(a): f for a, f in db.get("functions", {}).items()}
        self.tus = {t["id"]: t for t in db.get("tus", [])}
        self.objects = sorted(db.get("globals", []),
                              key=lambda g: (_address(g["address"]), g.get("name", ""), g.get("file") or ""))
        # Narrow imported libstdc++ data evidence from the borrowed ELF. A DB
        # label/namespace or version-looking game name alone must not suppress gaps.
        self.elf_weak_functions = set()
        self.elf_object_names = {}
        self.elf_object_sizes = {}
        self.cegui_headers = {}
        self.header_classes = {}
        self.local_object_names = set()
        for symbol in [*getattr(image, "symbols", ()), *getattr(image, "dynsyms", ())]:
            if (symbol.type == 2 and symbol.bind == 2 and symbol.defined
                    and symbol.value and symbol.name and getattr(symbol, "size", 0) > 0):
                self.elf_weak_functions.add((symbol.value, symbol.name, symbol.size))
            if (symbol.type == 1 and symbol.bind == 0 and symbol.defined and symbol.value
                    and getattr(symbol, "size", 0) > 0 and getattr(symbol, "file", None)):
                self.local_object_names.add((symbol.value, symbol.name, symbol.size, symbol.file))
            if (symbol.type == 1 and symbol.bind in (1, 2) and symbol.defined
                    and symbol.value and symbol.name):  # STT_OBJECT, GLOBAL/WEAK
                key = (symbol.value, symbol.name.split("@", 1)[0])
                self.elf_object_names.setdefault(key, set()).add(symbol.name)
                self.elf_object_sizes.setdefault(key, set()).add(getattr(symbol, "size", 0))
        self.copy_data = {address: reloc.symbol.split("@", 1)[0]
                          for address, reloc in getattr(image, "relocs", {}).items()
                          if reloc.type == 5 and reloc.offset == address}  # R_X86_64_COPY
        self.sources, self.declarations, self.local_cache, self.local_declarations = {}, {}, {}, {}
        # Once per immutable staged tree, not once per function. Do not render unrelated files.
        base = self._path("include", "probe.h").parent
        for path in sorted(base.glob("*.h")):
            text = self._read("include", path.name)
            decls, classes = _scan(text)
            self.header_classes[path.name] = {c.name for c in classes if c.reason != "non-top-level/anonymous scope"}
            self.sources[path.name] = text
            self.declarations[path.name] = decls

    def _path(self, directory, name):
        name = _basename(name)
        base = (self.root / "decomp" / directory).resolve()
        path = base / name
        if not base.is_relative_to(self.root) or path.resolve().parent != base:
            raise ContextError(f"unsafe {directory} path: {name!r}")
        return path

    def _read(self, directory, name):
        try:
            return self._path(directory, name).read_text(encoding="utf-8")
        except (OSError, UnicodeError) as error:
            raise ContextError(f"cannot read decomp/{directory}/{name}: {error}") from error

    def _tu(self, f, tu):
        name = tu or self.tus.get(f.get("tu"), {}).get("name") or f.get("file")
        return _basename(name) if name else None

    def _mapped(self, scope):
        return sorted(set(self.mapping.get(scope, ())) | set(self.mapping.get(scope.split("::")[0], ())))

    def _matching(self, qualified, kind):
        return [(name, d) for name, decls in self.declarations.items()
                for d in decls if d.qualified == qualified and d.kind == kind]

    def _objects_at(self, address):
        return [g for g in self.objects if (_address(g["address"]) == address
                or _address(g["address"]) < address < _address(g["address"]) + g.get("size", 0))]

    def _library_data(self, obj):
        """Only version-proven imported std/__gnu_cxx objects, not missing globals.

        Require agreement of DB scope, actual Itanium namespace encoding, a
        defined nonlocal ELF object at the same base/name, GLIBCXX version on
        that borrowed symbol, and a matching COPY relocation. Unversioned game
        definitions/instantiations remain strict gaps until separately proven.
        """
        if obj.get("bind") not in ("global", "weak"):
            return None
        raw = obj.get("name", "").split("@", 1)[0]
        readable = obj.get("demangled") or ""
        if readable.startswith("std::") and re.match(r"^_ZN(?:St(?=[0-9])|Ss(?=[0-9])|Sb(?=I))", raw):
            owner = "std"
        elif readable.startswith("__gnu_cxx::") and re.match(r"^_ZN9__gnu_cxx(?=[0-9IE])", raw):
            owner = "__gnu_cxx"
        else:
            return None
        base = _address(obj["address"])
        if self.copy_data.get(base) != raw:
            return None
        for name in sorted(self.elf_object_names.get((base, raw), ())):
            version = re.search(r"@{1,2}(GLIBCXX_[0-9]+(?:\.[0-9]+)*)$", name)
            if version:
                return f"{owner}; borrowed ELF STT_OBJECT + {version[1]} + matching R_X86_64_COPY"
        return None

    def _dso_registration_handle(self, obj, f, asm):
        """Recognize only the pinned compiler's immediate __cxa_atexit triple.

        __dso_handle belongs to the linked image, not the last STT_FILE group.
        Require original ELF identity and every occurrence to be an immediate
        third argument of the actual imported __cxa_atexit. No name-only or
        generic __cxa exemption, and no inferred C++ data declaration.
        ABI: https://itanium-cxx-abi.github.io/cxx-abi/abi.html#dso-dtor
        """
        if (obj.get("name") != "__dso_handle" or obj.get("demangled") != "__dso_handle"
                or obj.get("bind") != "local" or obj.get("size") != 0):
            return False
        base = _address(obj["address"])
        matches = [s for s in getattr(self.image, "symbols", ())
                   if s.name == "__dso_handle"]
        if (len(matches) != 1 or not matches[0].defined or matches[0].type != 1
                or matches[0].bind != 0 or matches[0].value != base
                or matches[0].size != 0):
            return False
        section = self.image.section_at(base)
        if not section or section.type != 1 or not section.flags & 2 or section.flags & (1 | 4):
            return False
        insns = _instructions(f, asm)
        occurrences = 0
        for i, (_, mnemonic, operands) in enumerate(insns):
            code = operands.split("#", 1)[0].split(";", 1)[0].strip()
            # Count numeric references conservatively, including RIP annotations.
            if base not in _references(dict(f, address=hex(insns[i][0]), size=1),
                                       f"{insns[i][0]:x}: {mnemonic} {operands}")[1]:
                continue
            occurrences += 1
            if mnemonic != "mov" or not re.fullmatch(r"\$0x0*" + f"{base:x}" + r",%edx", code):
                return False
            # The three independent immediate argument loads may appear in
            # any order. Require a complete contiguous triple, unique registers,
            # the same handle in EDX, and the real imported call immediately after.
            valid = False
            for start in range(max(0, i - 2), i + 1):
                if start + 3 >= len(insns):
                    continue
                assigned = {}
                for _, op, args in insns[start:start + 3]:
                    args = args.split("#", 1)[0].split(";", 1)[0].strip()
                    value = re.fullmatch(r"\$0x([0-9a-f]+),%(edi|esi|edx)", args)
                    if op != "mov" or not value or value[2] in assigned:
                        break
                    assigned[value[2]] = int(value[1], 16)
                else:
                    _, op, args = insns[start + 3]
                    target = re.match(r"^(?:0x)?([0-9a-fA-F]+)(?:\s|$)", args)
                    interiors = {x[0] for x in insns[start + 1:start + 4]}
                    enters_inside = any(
                        branch.startswith("j") and (jump := re.match(r"^(?:0x)?([0-9a-fA-F]+)(?:\s|$)", operand))
                        and int(jump[1], 16) in interiors for _, branch, operand in insns)
                    if (set(assigned) == {"edi", "esi", "edx"} and assigned["edx"] == base
                            and op in ("call", "callq") and target and not enters_inside
                            and getattr(self.image, "plt", {}).get(int(target[1], 16)) == "__cxa_atexit"):
                        valid = True
                        break
            if not valid:
                return False
        return occurrences > 0

    def _cegui_header(self, name):
        """Borrow a named pinned SDK header; no compiler, ELF or DB reload."""
        if name in self.cegui_headers:
            return self.cegui_headers[name]
        sdk = (self.root / "third_party/cegui-0.6.2/include").resolve()
        path = sdk / _basename(name)
        value = None
        if (name in self.CEGUI_HEADER_SHA256 and path.resolve().parent == sdk
                and path.is_file()):
            try:
                raw_source = path.read_bytes()
                source = raw_source.decode("utf-8")
                digest = hashlib.sha256(raw_source).hexdigest()
                if digest != self.CEGUI_HEADER_SHA256[name]:
                    self.cegui_headers[name] = None
                    return None
                parsed = re.sub(r"\bCEGUIEXPORT\b", "", source)
                declarations, _ = _scan(parsed)
                value = (declarations, _mask(parsed), digest)
            except (OSError, UnicodeError):
                pass  # Retain a gap, never invent an SDK declaration.
        self.cegui_headers[name] = value
        return value

    def _ogre_data(self, obj):
        """One reviewed OGRE String object under the pinned default build profile."""
        raw = "_ZN4Ogre20ResourceGroupManager27DEFAULT_RESOURCE_GROUP_NAMEE"
        label = "Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME"
        if (obj.get("name") != raw or obj.get("demangled") != label
                or obj.get("bind") not in ("global", "weak") or obj.get("size") != 8):
            return None
        base = _address(obj["address"])
        if (self.copy_data.get(base) != raw or raw not in self.elf_object_names.get((base, raw), ())
                or self.elf_object_sizes.get((base, raw)) != {8}):
            return None
        sec = self.image.section_at(base)
        if (not sec or sec.type != 8 or sec.flags & 3 != 3 or base + 8 > sec.addr + sec.size):
            return None
        try:
            configuration = (self.root / "decomp/config.json").read_bytes()
            if hashlib.sha256(configuration).hexdigest() != self.OGRE_CONFIG_SHA256:
                return None
            cache = Path(os.environ.get("OTL_DECOMP_CACHE", Path.home() / ".cache/opentorchlight/decomp"))
            sdk = (cache / "gcc447/ogre-1.6.5/ogre/OgreMain/include").resolve()
            sources = {}
            for name, expected in self.OGRE_HEADER_SHA256.items():
                path = sdk / name
                if path.resolve().parent != sdk:
                    return None
                raw_source = path.read_bytes()
                if hashlib.sha256(raw_source).hexdigest() != expected:
                    return None
                sources[name] = raw_source.decode("utf-8")
        except (OSError, UnicodeError):
            return None
        prerequisites = _mask(sources["OgrePrerequisites.h"])
        if (not re.search(r"typedef\s+std::string\s+_StringBase\s*;", prerequisites)
                or not re.search(r"typedef\s+_StringBase\s+String\s*;", prerequisites)):
            return None
        owner = re.sub(r"\b(?:_OgreExport|OGRE_AUTO_MUTEX)\b", "", sources["OgreResourceGroupManager.h"])
        declarations, _ = _scan(owner)
        matches = [d for d in declarations if d.kind == "data" and d.qualified == label
                   and re.fullmatch(r"static\s+String\s+DEFAULT_RESOURCE_GROUP_NAME\s*;", _mask(d.text).strip())]
        if len(matches) != 1:
            return None
        return ("OGRE1.6.5 SDK declaration static String DEFAULT_RESOURCE_GROUP_NAME; "
                "exact ELF object/COPY identity, eight-byte default narrow-string profile; "
                "four SDK header pins and decomp/config.json SHA256 " + self.OGRE_CONFIG_SHA256)

    def _cegui_data(self, obj):
        """Exact COPY-imported SDK declarations for the pinned x86-64 ABI.

        Scope/name alone is insufficient. CEGUI::String is 176 bytes and
        pointer/size_type objects are 8 in this project's pinned GCC 4.4.7 SDK
        layout. Unknown SDK objects, changed declarations and other ABIs stay
        unresolved. This supplies declaration context, not behavior acceptance.
        """
        raw = obj.get("name", "")
        label = obj.get("demangled", "")
        if obj.get("bind") not in ("global", "weak") or "@" in raw:
            return None
        base = _address(obj["address"])
        if (self.copy_data.get(base) != raw or raw not in self.elf_object_names.get((base, raw), ())
                or self.elf_object_sizes.get((base, raw)) != {obj.get("size")}):
            return None
        sec = self.image.section_at(base)
        if (not sec or sec.type != 8 or not sec.flags & 2 or not sec.flags & 1
                or obj.get("size", 0) <= 0 or base + obj["size"] > sec.addr + sec.size):
            return None
        event = re.fullmatch(r"CEGUI::Window::(Event\w+)", label)
        if event:
            name = event[1]
            if raw != f"_ZN5CEGUI6Window{len(name)}{name}E" or obj["size"] != 176:
                return None
            header = "CEGUIWindow.h"
            expected = r"static\s+const\s+String\s+" + re.escape(name) + r"\s*;"
        elif label == "CEGUI::String::npos":
            if raw != "_ZN5CEGUI6String4nposE" or obj["size"] != 8:
                return None
            header, expected = "CEGUIString.h", r"static\s+const\s+size_type\s+npos\s*;"
        else:
            singleton = re.fullmatch(r"CEGUI::Singleton<CEGUI::([A-Za-z_]\w*)>::ms_Singleton", label)
            if not singleton or obj["size"] != 8:
                return None
            manager = singleton[1]
            if raw != f"_ZN5CEGUI9SingletonINS_{len(manager)}{manager}EE12ms_SingletonE":
                return None
            base_header = self._cegui_header("CEGUISingleton.h")
            owner_header = self._cegui_header("CEGUI" + manager + ".h")
            if not base_header or not owner_header:
                return None
            if (not re.search(r"namespace\s+CEGUI\s*\{", base_header[1])
                    or not re.search(r"template\s*<\s*(?:class|typename)\s+T\s*>\s*class\s+Singleton\b", base_header[1])
                    or not re.search(r"static\s+T\s*\*\s*ms_Singleton\s*;", base_header[1])
                    or not re.search(r"namespace\s+CEGUI\s*\{", owner_header[1])
                    or not re.search(r"class\s+" + re.escape(manager) + r"\s*:\s*public\s+Singleton\s*<\s*" + re.escape(manager) + r"\s*>", owner_header[1])):
                return None
            return (f"CEGUI0.6.2 SDK singleton declaration + exact ELF object/COPY identity; "
                    f"CEGUISingleton.h SHA256 {base_header[2]}, CEGUI{manager}.h SHA256 {owner_header[2]}")
        evidence = self._cegui_header(header)
        if not evidence:
            return None
        matches = [d for d in evidence[0] if d.kind == "data" and d.qualified == label
                   and re.fullmatch(expected, d.text)]
        if len(matches) != 1:
            return None
        return (f"CEGUI0.6.2 SDK declaration {matches[0].text} + exact ELF object/COPY identity; "
                f"{header} SHA256 {evidence[2]}")

    def _safe_pointer_headers(self, callee, scope):
        """Existing reviewed template body, not a synthesized specialization.

        Deliberately limited to weak TSafePointer<flat-class>::setObject(T*).
        Exact DB/ELF identity, unchanged source and a unique complete pointee
        declaration are required. Other templates/methods remain strict gaps.
        """
        match = re.fullmatch(r"TSafePointer<([A-Za-z_]\w*)>", scope)
        if (not match or callee.get("kind") != "inline_or_template"
                or set(callee.get("bind", ())) != {"weak"}
                or callee.get("method") != "setObject" or callee.get("cv", "")):
            return set()
        pointee = match[1]
        symbol = f"_ZN12TSafePointerI{len(pointee)}{pointee}E9setObjectEPS0_"
        if (callee.get("qualified") != scope + "::setObject"
                or re.sub(r"\s+", "", callee.get("params", "")) != pointee + "*"
                or callee.get("mangled") != symbol or set(callee.get("names", ())) != {symbol}
                or (_address(callee["address"]), symbol, callee.get("size")) not in self.elf_weak_functions):
            return set()
        if "SafePointer.h" not in self.sources:
            return set()
        raw = self._path("include", "SafePointer.h").read_bytes()
        if (hashlib.sha256(raw).hexdigest() != self.SAFE_POINTER_HEADER_SHA256
                or raw.decode("utf-8") != self.sources["SafePointer.h"]):
            return set()
        headers = {h for h in self._mapped(pointee)
                   if pointee in self.header_classes.get(h, ())}
        if len(headers) != 1:
            return set()
        return headers | {"SafePointer.h"}

    def _implicit_destructor_headers(self, callee, scope, candidates):
        """C++98 implicitly declares complete/base D1/D2 destructors.

        Only weak compiler-generated, unqualified top-level class identities;
        a forward declaration, wrong class, ordinary function or D0 is not enough.
        Include the real whole header rather than synthesizing a declaration.
        """
        if (not scope or "::" in scope or callee.get("kind") != "inline_or_template"
                or set(callee.get("bind", ())) != {"weak"}
                or callee.get("method") != "~" + scope or callee.get("params") != ""):
            return set()
        names = set(callee.get("names", ()))
        allowed = {f"_ZN{len(scope)}{scope}D1Ev", f"_ZN{len(scope)}{scope}D2Ev"}
        if not names or not names <= allowed:
            return set()
        found = {h for h in candidates if scope in self.header_classes.get(h, ())}
        return found if len(found) == 1 else set()

    def _available(self, address, objects):
        section = self.image.section_at(address)
        # ELF section flags, not names or a guessed memory map. No bss, text, GOT, RELRO.
        if (not section or section.type != 1 or not section.flags & 2 or section.flags & (1 | 4)):
            return None, 0
        available = section.addr + section.size - address
        # Image.read uses PT_LOAD file bounds; clip to those before reading.
        segments = [s for s in self.image.segments if s[0] == 1 and s[3] <= address < s[3] + s[5]]
        if not segments:
            return section, 0
        available = min(available, min(s[3] + s[5] - address for s in segments))
        for obj in objects:
            if obj.get("size", 0):
                available = min(available, _address(obj["address"]) + obj["size"] - address)
        return section, available

    def _read_bytes(self, address, size):
        try:
            raw = self.image.read(address, size)
        except (ValueError, OSError) as error:
            raise ContextError(f"read-only reference {address:#x}: {error}") from error
        if len(raw) != size:
            raise ContextError(f"short ELF read at {address:#x}: wanted {size}, got {len(raw)}")
        return raw

    def _literal(self, address, objects, width):
        section, available = self._available(address, objects)
        if section is None:
            return None
        if available <= 0:
            raise ContextError(f"read-only reference {address:#x} is not file-backed")
        # SHF_STRINGS with element size 1 is explicit byte-string evidence. Width-4
        # SHF_STRINGS alone does not prove Unicode/wchar_t, so only show hex there.
        section_string = section.flags & 0x20 and section.entsize == 1
        width = width or (1 if section_string else 0)
        origin = "ELF SHF_STRINGS, entsize=1" if section_string else "existing array declaration (not ABI proof)"
        if width and objects and any((address - _address(g["address"])) % width for g in objects):
            width = 0
        if width:
            scanned = bytearray()
            limit = min(available, self.STRING_SCAN_LIMIT)
            for offset in range(0, limit - width + 1, width):
                unit = self._read_bytes(address + offset, width)
                if unit == bytes(width):
                    if width == 1:
                        value = repr(bytes(scanned))  # bytes, no guessed character encoding
                    else:
                        points = [int.from_bytes(scanned[i:i + 4], "little") for i in range(0, len(scanned), 4)]
                        if any(p > 0x10ffff or 0xd800 <= p <= 0xdfff for p in points):
                            break
                        value = ascii("".join(chr(p) for p in points))
                    return (f"{address:#x} ({section.name}): NUL-terminated {'byte' if width == 1 else 'wchar32-LE'} "
                            f"text {value}; {len(scanned) + width} bytes complete through terminator; type from {origin}.")
                scanned.extend(unit)
            else:
                if available > self.STRING_SCAN_LIMIT:
                    raise ContextError(f"typed string at {address:#x} exceeds {self.STRING_SCAN_LIMIT} scan bytes; "
                                       "raise the semantic scan limit, do not truncate the packet")
        prefix = self._read_bytes(address, min(available, self.DIAGNOSTIC_BYTES))
        return (f"{address:#x} ({section.name}): hex {prefix.hex(' ')}; diagnostic prefix only "
                f"({len(prefix)} bytes, at most {self.DIAGNOSTIC_BYTES}; bounded by section/file/object); "
                "not the whole object or an inferred string/type.")

    def build(self, f, asm, *, tu=None, already_shown=(), max_chars=None):
        tu = self._tu(f, tu)
        shown = {_basename(n) for n in already_shown}
        for name in shown:
            if name not in self.sources:
                raise ContextError(f"already_shown header {name} is not an existing indexed header")
        calls, references, notes = _references(f, asm)
        wanted, gaps, data_blocks, facts = set(), [], [], []
        own_scope = f.get("scope") or ""
        own_headers = self._mapped(own_scope) if own_scope else []
        local_names = {own_scope.split("::")[0]} if own_scope else set()
        if tu:
            if tu not in self.local_cache:
                path = self._path("src", tu)
                local_decls, local_defs = _scan(self._read("src", tu)) if path.exists() else ([], [])
                self.local_declarations[tu] = tuple(d for d in local_decls if d.kind == "function")
                self.local_cache[tu] = local_defs
            local_types = {t.name: t for t in self.local_cache[tu]}
            duplicated_local_names = {name for name in local_types
                                      if sum(t.name == name for t in self.local_cache[tu]) > 1}
        else:
            local_types = {}
            duplicated_local_names = set()
        # Local classes referenced in the owning header (e.g. TArrayList<CCinematic*>).
        for name in own_headers:
            if name in self.sources:
                local_names.update(t for t in local_types if re.search(r"\b" + re.escape(t) + r"\b", _mask(self.sources[name])))
        for address in calls:
            callee = self.functions.get(address)
            if not callee or self.tus.get(callee.get("tu"), {}).get("kind") != "game":
                continue  # no library headers and no transitive call graph
            scope = callee.get("scope") or ""
            if scope.split("::")[0] in self.LIBRARY_SCOPES or callee.get("kind") == "compiler":
                continue  # weak library instantiations can be linked into a game STT_FILE group
            qualified = callee.get("qualified") or (scope + "::" if scope else "") + callee.get("method", "")
            label = callee.get("demangled") or qualified or f"{address:#x}"
            facts.append(f"Direct game call/tail-call {address:#x}: {label}; return/static not encoded by symbol.")
            candidates = self._mapped(scope) if scope else []
            matches = self._matching(qualified, "function")
            matched_headers = {name for name, decl in matches
                               if (not candidates or name in candidates) and _declares_callee(decl, callee)}
            implicit_headers = self._implicit_destructor_headers(callee, scope, candidates)
            template_headers = self._safe_pointer_headers(callee, scope)
            if matched_headers:
                wanted.update(matched_headers)
            elif implicit_headers:
                wanted.update(implicit_headers)
                notes.append(f"{address:#x}: weak D1/D2 destructor implicitly declared by the existing complete class header; no guessed return type.")
            elif template_headers:
                wanted.update(template_headers)
                notes.append(f"{address:#x}: existing pinned TSafePointer setObject template body; "
                             f"weak ELF/DB identity and complete pointee header; SafePointer.h SHA256 {self.SAFE_POINTER_HEADER_SHA256}. "
                             "No specialization or prototype synthesized.")
            elif scope in local_types and self._tu(callee, None) == tu:
                local_names.add(scope)
                if not any(d.qualified == qualified and _declares_callee(d, callee)
                           for d in self.local_declarations[tu]):
                    gaps.append(f"No declaration of direct callee {label} in its existing TU-local type")
            else:
                # Include known class headers even if the method was not restored yet,
                # but flag the absent declaration; never synthesize it from return_hint.
                wanted.update(candidates)
                gaps.append(f"No existing declaration of direct callee {label} at {address:#x}")
            if scope in local_types:
                local_names.add(scope)
        for address in references:
            objects = self._objects_at(address)
            widths = set()
            for obj in objects:
                offset = address - _address(obj["address"])
                name = obj.get("demangled") or obj.get("name", "")
                owner = obj.get("file") if obj.get("bind") == "local" else None
                facts.append(f"Named data {address:#x}: {name}+{offset:#x}; symbol base {obj['address']}, "
                             f"size {obj.get('size', 0)}; linkage {obj.get('bind', '?')}"
                             + (f", STT_FILE owner {owner}" if owner else "") + ".")
                if obj.get("name", "").startswith(("_ZTV", "_ZTT", "_ZTI", "_ZTS", "_ZGV")):
                    notes.append(f"{address:#x}: compiler/ABI metadata; no C++ data declaration synthesized.")
                    continue
                if self._dso_registration_handle(obj, f, asm):
                    notes.append(f"{address:#x}: ELF-proven DSO destruction registration handle; "
                                 "all references are compiler __cxa_atexit argument triples; "
                                 "no game declaration required or synthesized.")
                    continue
                library = self._library_data(obj) or self._cegui_data(obj) or self._ogre_data(obj)
                if library:
                    notes.append(f"{address:#x}: library-owned ABI data ({library}); "
                                 "no game declaration required or synthesized.")
                    continue
                if obj.get("bind") == "local" and (not owner or owner != tu):
                    gaps.append(f"Local data {name} belongs to {owner}, not target TU {tu}; no same-name declaration substituted")
                    continue
                raw = obj.get("name", "")
                section = self.image.section_at(_address(obj["address"]))
                local_identity = (_address(obj["address"]), raw, obj.get("size", 0), owner)
                if (obj.get("bind") == "local" and owner == tu
                        and local_identity in self.local_object_names
                        and name.startswith(f.get("demangled", "") + "::")
                        and any(raw.startswith("_ZZ" + symbol[2:] + "E")
                                for symbol in f.get("names", [f.get("mangled", "")]) if symbol.startswith("_Z"))
                        and section and section.type == 8 and section.flags & 2
                        and obj.get("size", 0) > 0
                        and _address(obj["address"]) + obj["size"] <= section.addr + section.size):
                    notes.append(f"{address:#x}: target function-local static storage; exact ELF local STT_OBJECT, "
                                 "matching mangled function identity and STT_FILE; SHT_NOBITS zero initialization. "
                                 "No external header declaration needed; C++ type is not inferred.")
                    continue
                matches = self._matching(name, "data")
                if not matches:
                    gaps.append(f"No existing header declaration for referenced data {name} ({address:#x})")
                for header, declaration in matches:
                    if declaration.array_width:
                        widths.add(declaration.array_width)
                    if any(k == "class" for k, _ in declaration.scopes):
                        wanted.add(header)  # preserve class layout, not a trimmed fake class
                    elif header not in shown:
                        text = _standard_string_aliases(declaration.text)
                        for _, namespace in reversed(declaration.scopes):
                            text = f"namespace {namespace} {{\n{text}\n}}"
                        data_blocks.append((header, text))
            literal = self._literal(address, objects, next(iter(widths)) if len(widths) == 1 else 0)
            if literal:
                facts.append(literal)
        blocks = ["One-hop source/data context. Existing headers are evidence of current declarations, not "
                  "confirmed ABI: inferred return/data types (including generated/promoted ones) still require ASM/caller verification."]
        for name in sorted(wanted - shown):
            if name not in self.sources:
                raise ContextError(f"selected header decomp/include/{name} is missing")
            blocks.append(f"Direct dependency header decomp/include/{name}, whole:\n```cpp\n{self.sources[name]}\n```")
        for name, text in sorted(set(data_blocks)):
            if name not in wanted:
                blocks.append(f"Referenced data declaration, verbatim from decomp/include/{name}:\n```cpp\n{text}\n```")
        for name in sorted(local_names & local_types.keys()):
            if name in duplicated_local_names:
                raise ContextError(f"ambiguous TU-local type name {name} in {tu}; no duplicate/scope guess")
            typ = local_types[name]
            if not typ.safe:
                raise ContextError(f"selected TU-local type {name} in {tu} has {typ.reason}; "
                                   "supply a reviewed declaration-only snippet, not the whole TU")
            blocks.append(f"Existing TU-local type in decomp/src/{tu} (no function bodies):\n```cpp\n{typ.text}\n```")
        if facts:
            blocks.append("Machine references:\n" + "\n".join(dict.fromkeys(facts)))
        if notes or gaps:
            blocks.append("Unresolved/limitations (do not invent declarations or ABI):\n" + "\n".join(sorted(set(notes + gaps))))
        text = "\n\n".join(blocks)
        if max_chars is not None and len(text) > max_chars:
            raise ContextError(f"mandatory context is {len(text)} chars, over {max_chars}; no headers/data were truncated")
        return Context(text, tuple(sorted(wanted - shown)), tuple(sorted(set(gaps))))


def compose_prompt(*, fixed, context, tail, examples="", max_chars=131072):
    """Integration seam: mandatory context participates in llm_packet's hard budget.

    Examples are optional, dropped as a whole. Never trim a header, ASM, draft,
    context, or repair feedback passed in tail. This is not an orchestration loop.
    """
    middle = context.text if isinstance(context, Context) else context
    mandatory = "\n\n".join(p for p in [*fixed, middle, *tail] if p)
    if len(mandatory) > max_chars:
        raise ContextError(f"mandatory prompt is {len(mandatory)} chars, over {max_chars} "
                           f"(context {len(middle)}); optional examples cannot solve this overflow")
    if examples:
        full = "\n\n".join(p for p in [*fixed, examples, middle, *tail] if p)
        if len(full) <= max_chars:
            return full
    return mandatory
