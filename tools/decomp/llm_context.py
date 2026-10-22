"""Automatic read-only, one-hop packet context; no ELF/DB loads or subprocesses.

Construct ContextIndex once from Loop's already-loaded db/image and hand-header map,
after header preparation. build() consumes the same exact ASM that the prompt shows.
This is deliberately a shallow declaration scanner, not a C++ parser or a type oracle.
"""
from __future__ import annotations

from dataclasses import dataclass
from fractions import Fraction
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
    int_array_values: tuple[int, ...] | None = None
    whole_header: bool = False
    scalar_array_bytes: bytes | None = None
    asm_symbol: str | None = None
    scalar_literal_bytes: bytes | None = None


@dataclass(frozen=True)
class LocalType:
    name: str
    text: str
    safe: bool
    reason: str = ""
    qualified: str = ""


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


def _float32_literal_bytes(token):
    """Round a bounded decimal float literal exactly, including ties/subnormals."""
    if (len(token) > 32 or not re.fullmatch(
            r"-?(?:(?:0|[1-9][0-9]*)\.[0-9]*|\.[0-9]+)(?:[eE][+-]?[0-9]{1,2})?[fF]", token)):
        return None
    value = abs(Fraction(token[:-1]))
    sign = (1 << 31) if token.startswith("-") else 0
    if not value:
        return sign.to_bytes(4, "little")
    numerator, denominator = value.numerator, value.denominator
    exponent = numerator.bit_length() - denominator.bit_length()
    if ((exponent >= 0 and numerator < denominator << exponent)
            or (exponent < 0 and numerator << -exponent < denominator)):
        exponent -= 1
    quantum = max(exponent - 23, -149)
    if quantum < 0:
        numerator <<= -quantum
    else:
        denominator <<= quantum
    significand, remainder = divmod(numerator, denominator)
    if remainder * 2 > denominator or (remainder * 2 == denominator and significand & 1):
        significand += 1
    if significand >= 1 << 24:
        significand >>= 1
        quantum += 1
    if significand < 1 << 23:
        bits = significand
    elif quantum + 23 > 127:
        return None
    else:
        bits = ((quantum + 150) << 23) | (significand - (1 << 23))
    return (sign | bits).to_bytes(4, "little")


def _scan(text, *, typedefs=False):
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
            head = re.sub(r"^(?:public|protected|private)\s*:\s*", "", head)
            ns = re.fullmatch(r"namespace\s+(\w+)", head)
            cls = re.fullmatch(r"(?:class|struct|union)\s+(?:__attribute__\(\(\w+\)\)\s+)?(\w+)\s*(?::[^{};]*)?", head)
            array = re.fullmatch(r"(?:static\s+)?(?:const\s+)?std::(?:w?string)\s+(\w+)\s*\[\s*(?:[0-9]+)?\s*\]\s*=", head)
            integer_array = re.fullmatch(r"static\s+const\s+int\s+(\w+)\s*\[\s*([1-9][0-9]{0,3})\s*\]\s*=", head)
            scalar_array = re.fullmatch(r"static\s+const\s+(bool|float)\s+(\w+)\s*\[\s*([1-9][0-9]{0,3})\s*\]\s*=", head)
            kind, name = (("namespace", ns[1]) if ns else
                          ("class", cls[1]) if cls else
                          ("string_array", array[1]) if array else
                          ("int_array", integer_array[1]) if integer_array else
                          ("scalar_array", scalar_array[2]) if scalar_array else ("body", ""))
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
                if kind == "int_array" and all(k == "namespace" for k, _ in scopes):
                    # Deliberately only explicit decimal int32 values and extent.
                    # Keep source/linkage verbatim; ELF evidence is checked at use.
                    literal = r"-?(?:0|[1-9][0-9]*)"
                    values = text[opening + 1:i]
                    tail = re.match(r"\s*;", masked[i + 1:])
                    extent = int(re.search(r"\[\s*([1-9][0-9]{0,3})\s*\]", masked[beginning:opening])[1])
                    if (tail and extent <= 4096 and len(values) <= 65536
                            and re.fullmatch(r"\s*" + literal + r"(?:\s*,\s*" + literal + r")*\s*,?\s*", values)):
                        tokens = re.findall(literal, values)
                        if len(tokens) == extent and all(len(t.lstrip("-")) <= 10 for t in tokens):
                            numbers = tuple(int(t) for t in tokens)
                            if all(-(1 << 31) <= n < (1 << 31) for n in numbers):
                                first = re.search(r"\S", masked[beginning:opening])
                                declaration = text[beginning + first.start():i + 1 + tail.end()].strip()
                                qualified = "::".join([n for _, n in scopes] + [name])
                                declarations.append(Declaration(qualified, "data", declaration, scopes, 0, numbers))
                if kind == "scalar_array" and all(k == "namespace" for k, _ in scopes):
                    # Only complete literal initializers, with exact ELF bytes
                    # required at use. No expressions, casts, macros or zero fill.
                    array_head = masked[beginning:opening]
                    scalar_type = re.search(r"static\s+const\s+(bool|float)\b", array_head)[1]
                    extent = int(re.search(r"\[\s*([1-9][0-9]{0,3})\s*\]", array_head)[1])
                    values = text[opening + 1:i]
                    tail = re.match(r"\s*;", masked[i + 1:])
                    if tail and extent <= 4096 and len(values) <= 65536:
                        tokens = values.strip().removesuffix(",").split(",")
                        chunks = []
                        for value in tokens:
                            value = value.strip()
                            chunks.append((b"\x01" if value == "true" else b"\x00" if value == "false" else None)
                                          if scalar_type == "bool" else _float32_literal_bytes(value))
                        if len(chunks) == extent and all(c is not None for c in chunks):
                            first = re.search(r"\S", masked[beginning:opening])
                            declaration = text[beginning + first.start():i + 1 + tail.end()].strip()
                            qualified = "::".join([n for _, n in scopes] + [name])
                            declarations.append(Declaration(qualified, "data", declaration, scopes,
                                                            scalar_array_bytes=b"".join(chunks)))
                if kind == "class":
                    end = i + 1
                    semicolon = re.match(r"\s*;", masked[end:])
                    if semicolon:
                        end += semicolon.end()
                        beginning += re.search(r"\S", masked[beginning:opening]).start()
                        reason = ("non-top-level/anonymous scope" if any(k != "namespace" for k, _ in scopes) else
                                  "nested braces/inline bodies" if re.search(r"[{}]", masked[opening + 1:i]) else "")
                        if scopes and not reason:
                            body = re.sub(r"\b(?:public|protected|private)\s*:", "", masked[opening + 1:i])
                            members = [part.strip() for part in body.split(";") if part.strip()]
                            class_head = masked[beginning:opening]
                            def call_declaration(part):
                                method = re.search(r"(?<![\w:])(~?\w+)\s*\(", part)
                                return (method and "=" not in part[:method.start()]
                                        and declaration_headers.declared_signatures(part + ";", method[1]))
                            if (":" in class_head or re.search(r"\bvirtual\b", body)
                                    or any(not call_declaration(part) for part in members)):
                                reason = "namespace type is not opaque declaration-only calls (fields/bases/virtuals)"
                        snippet = text[beginning:end].strip()
                        for _, namespace in reversed(scopes):
                            snippet = f"namespace {namespace} {{\n{snippet}\n}}"
                        qualified = "::".join([n for _, n in scopes if n] + [name])
                        types.append(LocalType(name, snippet, not reason, reason, qualified))
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
                list_object = re.fullmatch(r"(?:static\s+)?TArrayList\s*<\s*std::(?:w?string)\s*>\s+(\w+)\s*\(\s*[1-9][0-9]*\s*\)", clean)
                zero_scalar = re.fullmatch(r"static\s+long\s+long\s+(\w+)\s*=\s*0", clean)
                repository = re.fullmatch(r"static\s+TRepository\s*<\s*std::wstring\s*>\s+(g_GlobalRepository)\s*\(\s*EMPTY_WSTRING\s*\)", clean)
                # Reviewed TU-local scalar initializers stay verbatim. Only a
                # single wide literal, bool token or finite float32 literal;
                # expressions, constructors, macros and compound declarations
                # cannot create declaration context through this path.
                scalar = re.fullmatch(r"static\s+(?:(const)\s+)?(std::wstring|bool|float)\s+(\w+)\s*=\s*(.*?)\s*;", original, re.S)
                integer_scalar = re.fullmatch(r"static\s+(?:const\s+)?(int|unsigned\s+int)\s+(\w+)\s*=\s*(-?(?:0|[1-9][0-9]{0,9}))\s*;", original)
                integer_bytes = None
                if integer_scalar and not scopes:
                    value = int(integer_scalar[3])
                    signed = integer_scalar[1] == "int"
                    in_range = -(1 << 31) <= value < (1 << 31) if signed else 0 <= value < (1 << 32)
                    if in_range:
                        integer_bytes = value.to_bytes(4, "little", signed=signed)
                literal_scalar = None
                if scalar and not scopes:
                    typ, value = scalar[2], scalar[4]
                    wide_literal = r'L"(?:\\(?:[\'"?\\abfnrtv]|[0-7]{1,3}|x[0-9a-fA-F]+|u[0-9a-fA-F]{4}|U[0-9a-fA-F]{8})|[^"\\\r\n])*"'
                    if ((typ == "std::wstring" and scalar[1] == "const" and re.fullmatch(wide_literal, value))
                            or (typ == "bool" and value in ("true", "false"))
                            or (typ == "float" and _float32_literal_bytes(value) is not None)):
                        literal_scalar = scalar[3]
                callback = re.fullmatch(r"typedef\s+([^;{}]+?)\s*\(\s*\*\s*(\w+)\s*\)\s*\(([^;{}]*)\)", clean)
                typedef = re.fullmatch(r"typedef\s+[^;{}()]+?\s+(\w+)", clean)
                whole_header = False
                asm_symbol = None
                asm_alias = re.fullmatch(r'extern\s+std::wstring\s+(\w+)\s+__asm__\(\s*"([A-Za-z_]\w*)"\s*\)\s*;', original)
                if asm_alias and all(k == "namespace" for k, _ in scopes):
                    name, kind, width = asm_alias[1], "data", 0
                    asm_symbol = asm_alias[2]
                elif callback and typedefs:
                    name, kind, width = callback[2], "callback", 0
                elif typedef and typedefs:
                    name, kind, width = typedef[1], "typedef", 0
                elif integer_bytes is not None:
                    name, kind, width = integer_scalar[2], "data", 0
                elif literal_scalar is not None:
                    name, kind, width = literal_scalar, "data", 0
                elif (zero_scalar or repository) and not scopes:
                    name, kind, width = (zero_scalar or repository)[1], "data", 0
                    whole_header = bool(repository)
                elif list_object and all(k == "namespace" for k, _ in scopes):
                    name, kind, width = list_object[1], "data", 0
                elif fn and "=" not in clean[:fn.start()] and not clean.startswith(("typedef ", "using ")):
                    name, kind, width = fn[1], "function", 0
                else:
                    var = re.fullmatch(r"(.+?)\b((?:\w+::)*\w+)\s*((?:\[[^\]]*\]\s*)*)", clean)
                    if (not var or any(c in clean for c in "()=")
                            or len(ghidra_cpp.split_args(clean)) != 1
                            or clean.startswith(("typedef ", "using ", "class ", "struct ", "enum "))):
                        start = i + 1
                        continue
                    name, kind, width = var[2], "data", 0
                    # A pointer object is not its pointee; unsigned-char blobs are not strings.
                    typ = var[1].strip()
                    # Commas are type arguments only, never compound objects.
                    # Unbalanced/unsupported expressions do not establish a type.
                    if "," in typ:
                        depth = 0
                        for ch in typ:
                            if ch == "<": depth += 1
                            elif ch == ">": depth -= 1
                            if depth < 0: break
                        if depth or not re.fullmatch(r"[\w\s:<>,*&]+", typ):
                            start = i + 1
                            continue
                        whole_header = True
                    if var[3] and re.fullmatch(r"(?:(?:extern|static|const)\s+)*(?:char|wchar_t)(?:\s+const)?", typ):
                        width = 4 if re.search(r"\bwchar_t\b", typ) else 1
                qualified = "::".join([n for _, n in scopes] + [name])
                declarations.append(Declaration(qualified, kind, original, scopes, width,
                                                whole_header=whole_header, asm_symbol=asm_symbol,
                                                scalar_literal_bytes=integer_bytes))
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


def _standard_vector_defaults(text, depth=0):
    """Erase only the pinned std::vector<T, std::allocator<T> > default.

    Balanced arguments and token identities preserve nested types and word
    boundaries. Custom allocators/namespaces and element qualifiers stay distinct.
    This is lookup text only; no declaration or general signature parser changes.
    """
    if depth > 32:
        raise ValueError("vector template nesting exceeds lookup limit")
    pattern = re.compile(r"(?<![\w:])std\s*::\s*vector\s*<")
    out, cursor = [], 0
    for_match = pattern.search(text, cursor)
    while for_match:
        start, opening = for_match.start(), for_match.end() - 1
        if re.search(r"::\s*$", text[:start]):
            cursor = for_match.end()
            for_match = pattern.search(text, cursor)
            continue
        level, part, args, end = 1, opening + 1, [], None
        for i in range(opening + 1, len(text)):
            ch = text[i]
            if ch == '<':
                level += 1
            elif ch == '>':
                level -= 1
                if level == 0:
                    args.append(text[part:i].strip())
                    end = i
                    break
            elif ch == ',' and level == 1:
                args.append(text[part:i].strip())
                part = i + 1
        if end is None or len(args) not in (1, 2) or any(not a for a in args):
            raise ValueError("malformed vector template arguments")
        args = [_standard_vector_defaults(a, depth + 1) for a in args]
        def tokens(value):
            # Do not equate 'unsigned int' with 'unsignedint' or accept expressions.
            token = r"[A-Za-z_]\w*|::|[<>,*&]|[0-9]+"
            if re.sub(token + r"|\s+", "", value):
                raise ValueError("unsupported vector template argument")
            return re.findall(token, value)
        element = tokens(args[0])
        if len(args) == 2 and tokens(args[1]) == ['std', '::', 'allocator', '<', *element, '>']:
            args.pop()
        # Preserve everything before this occurrence, including skipped namespaces.
        out.append(text[:start])
        spelling = 'std::vector<' + ', '.join(args) + '>'
        if depth == 0:
            # parameter_key later removes whitespace. Keep element word boundaries
            # in this lookup-only spelling: unsigned int must not become unsignedint.
            spelling = re.sub(r"(?<=\w)\s+(?=\w)", "|", spelling)
        out.append(spelling)
        text = text[end + 1:]
        cursor = 0
        for_match = pattern.search(text)
    out.append(text)
    return ''.join(out)


def _callback_aliases(sources):
    """Unique global function-pointer typedefs, validated by the existing parser."""
    found = {}
    scoped_typedefs = []
    for filename, source in sources.items():
        masked = _mask(source)
        for declaration in re.finditer(r"\btypedef\b[^;{}]*;", masked):
            before = masked[:declaration.start()]
            if before.count("{") != before.count("}"):
                scoped_typedefs.append(declaration[0])
        for match in re.finditer(r"typedef\s+([^;{}]+?)\s*\(\s*\*\s*(\w+)\s*\)\s*\(([^;{}]*)\)\s*;", masked):
            before = masked[:match.start()]
            if before.count("{") != before.count("}"):
                continue
            callback = match[1].strip() + " (*) (" + match[3].strip() + ")"
            if declaration_headers._unnamed_callback(callback):
                found.setdefault(match[2], set()).add((callback, filename))
    # This lookup has no C++ scope resolver. Defer any global alias mentioned
    # by a scoped typedef rather than substitute a possibly shadowed type.
    return {name: next(iter(values)) for name, values in found.items()
            if len(values) == 1 and not any(re.search(r"\b" + re.escape(name) + r"\b", text)
                                           for text in scoped_typedefs)}


def _expand_callback_aliases(text, aliases):
    for name, (callback, filename) in (aliases or {}).items():
        # Drop only the parameter name after a proven typedef. Pointer-to-alias,
        # qualifiers and compound declarators remain unsupported.
        text = re.sub(r"(?<![\w:])" + re.escape(name) + r"(?:\s+[A-Za-z_]\w*)?(?=\s*[,)]|\s*$)",
                      lambda match: callback, text)
    return text


def _callback_cv_spelling(text):
    def replace(match):
        candidate = match[0]
        if not declaration_headers._unnamed_callback(candidate):
            return candidate
        args = ", ".join(ghidra_cpp.cxx_type(part.strip()) for part in match[2].split(","))
        return match[1].strip() + " (*) (" + args + ")"
    return re.sub(r"([^(),]+?)\(\s*\*\s*\)\s*\(([^()]*)\)", replace, text)


def _declares_callee(declaration, callee, aliases=None):
    """Compatibility entry point; selection and direct calls use one identity."""
    identity = DeclarationIdentity({})
    identity.aliases = aliases or {}
    return identity.matches(declaration, callee, header="")


class DeclarationIdentity:
    """The same conservative parameter identity for selection and direct calls.

    Qualification uses complete lexical type names, never short-name matching.
    Callback aliases retain their defining global scope. This does not establish
    return types, static/member ABI, layouts, or missing declarations.
    """

    def __init__(self, sources):
        # Reuse the existing bounded type/default walkers, not a second parser.
        # Import lazily: smallmatch itself uses the packet scanner.
        from smallmatch import _declared_types, _map_defaults
        self.types = _declared_types(sources)
        self.map_defaults = _map_defaults
        self.aliases = _callback_aliases(sources)
        self.scoped_aliases, self.typedef_names = {}, set()
        for header, source in sources.items():
            for declaration in _scan(source, typedefs=True)[0]:
                if declaration.kind not in ("callback", "typedef") or not declaration.scopes:
                    continue
                self.typedef_names.add(declaration.qualified)
                self.scoped_aliases.setdefault(declaration.qualified, []).append((header, declaration))
        self.file_headers = {name for name, source in sources.items()
                             if re.search(r"(?m)^[ \t]*#[ \t]*include\s*<(?:stdio.h|cstdio)>",
                                          ghidra_cpp.protect_lexical(source)[0])}
        if any(re.search(r"\b(?:typedef\b[^;]*\bFILE|(?:class|struct|enum)\s+FILE)\b",
                         _mask(source)) for source in sources.values()):
            self.file_headers.clear()

    def parameter(self, text, *, scope=(), header=None, dependencies=None):
        if scope or header is not None:
            for token in re.findall(r"(?<![\w:])[A-Za-z_]\w*(?![\w:])", text):
                for depth in range(len(scope), 0, -1):
                    qualified = "::".join([*scope[:depth], token])
                    if qualified in self.types:
                        text = re.sub(r"(?<![\w:])" + re.escape(token) + r"(?![\w:])", qualified, text)
                        break
            # A scoped typedef is expanded only at its complete lexical identity.
            # A nearer noncallback typedef or any duplicate blocks substitution.
            alias = re.fullmatch(r"\s*((?:[A-Za-z_]\w*::)*[A-Za-z_]\w*)(?:\s+[A-Za-z_]\w*)?\s*", text)
            if alias:
                names = (["::".join([*scope[:depth], alias[1]]) for depth in range(len(scope), 0, -1)]
                         if "::" not in alias[1] else []) + [alias[1]]
                for qualified in names:
                    if qualified not in self.typedef_names:
                        continue
                    declarations = self.scoped_aliases.get(qualified, [])
                    if len(declarations) != 1 or declarations[0][1].kind != "callback":
                        raise ValueError("ambiguous/shadowed scoped callback")
                    defining_header, declaration = declarations[0]
                    callback = re.fullmatch(r"typedef\s+([^;{}]+?)\s*\(\s*\*\s*\w+\s*\)\s*\(([^;{}]*)\)\s*;", _mask(declaration.text))
                    spelling = callback[1].strip() + " (*) (" + callback[2].strip() + ")" if callback else ""
                    if not declaration_headers._unnamed_callback(spelling):
                        raise ValueError("unsupported scoped callback")
                    defining_scope = tuple(n for _, n in declaration.scopes)
                    for token in re.findall(r"(?<![\w:])[A-Za-z_]\w*(?![\w:])", spelling):
                        for depth in range(len(defining_scope), 0, -1):
                            typ = "::".join([*defining_scope[:depth], token])
                            if typ in self.types:
                                spelling = re.sub(r"(?<![\w:])" + re.escape(token) + r"(?![\w:])", typ, spelling)
                                break
                    text = spelling
                    if dependencies is not None:
                        dependencies.add(defining_header)
                    break
            if dependencies is not None:
                for name, (_, defining_header) in self.aliases.items():
                    if re.search(r"(?<![\w:])" + re.escape(name)
                                 + r"(?:\s+[A-Za-z_]\w*)?(?=\s*[,)]|\s*$)", text):
                        dependencies.add(defining_header)
            text = _expand_callback_aliases(text, self.aliases)
            if header in self.file_headers:
                text = re.sub(r"(?<![\w:])FILE\b", "_IO_FILE", text)
        text = _standard_vector_defaults(_standard_string_aliases(text))
        text = self.map_defaults(text)
        array = re.fullmatch(r"([^()\[\]]+)\(\s*&\s*([A-Za-z_]\w*)?\s*\)\s*\[\s*([1-9][0-9]*)\s*\]", text.strip())
        if array and declaration_headers._callback_type(array[1]):
            base = ghidra_cpp.cxx_type(array[1].strip())
            if "*" not in base:
                words = base.split()
                cv = [word for word in ("const", "volatile") if word in words]
                base = " ".join(cv + [word for word in words if word not in cv])
            text = base + " (&" + (array[2] or "") + ")[" + array[3] + "]"
        if (declaration_headers._unnamed_callback(text)
                and re.search(r"\*\s*(?:const|volatile)\b", text)):
            raise ValueError("callback pointer-object cv is unresolved")
        return _callback_cv_spelling(text)

    def matches(self, declaration, callee, header=None, *, dependencies=None):
        if "params" not in callee or "cv" not in callee:
            return False
        method = callee.get("method", "")
        if not re.fullmatch(r"~?[A-Za-z_]\w*", method):
            return False
        if declaration.qualified != (callee.get("qualified") or
                                     ((callee.get("scope") + "::") if callee.get("scope") else "") + method):
            return False
        try:
            used_headers = set()
            params = ", ".join(self.parameter(p) for p in ghidra_cpp.split_args(callee["params"]))
            expected = ghidra_cpp.signature_key(dict(callee, params=params))[1:3]
            scope = tuple(n for k, n in declaration.scopes)
            declared = declaration_headers.declared_signatures(
                declaration.text, method,
                lambda p: self.parameter(p, scope=scope, header=header, dependencies=used_headers))
        except ValueError:
            return False
        matched = any((params, cv) == expected for params, cv, _static in declared)
        if matched and dependencies is not None:
            dependencies.update(used_headers)
        return matched


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
        'CEGUIEditbox.h': 'a4b38f64e44c225193eb203aecd272609e7e7b6715f4502749dee6fc747f8d83',
        'CEGUIFrameWindow.h': '61cc9094b8a3d55ea15846892a4ff9a6f2a35d22fc5cd4e5ddf1281b075d97fa',
        'CEGUIWindow.h': '37f12e0e538df1cb67271ced354dae55d2be7a1d35830f00d77bae819d09b792',
        'CEGUIString.h': '0f6b99906ae55d7d8f35e4a50e249d76baaa7ec21d5ecd3b068822364429e6fe',
        'CEGUISingleton.h': 'ad721b29935815b6e943f1963732b63e62440760eea8e1f60a80f602fa942319',
        'CEGUIImagesetManager.h': 'bbe90f6bbe3918154df40927df1855a9bba5a13e5d4412b584217f565b5718a4',
        'CEGUIWindowManager.h': '3a89509c2f777e572723dd0161f5623a6850703ac43ffc26d4c6e4a630a70f31',
        'CEGUIFontManager.h': 'abe0d240dfee54a6f153bc6ab457726829f39ba85b9e24bd00dbeac4db95aec4',
        'CEGUISchemeManager.h': '9312ad97c424bfe9ea5e244bd4f8265c1880d293b8af33bfe0088ae9f4552136',
    }

    OGRE_HEADER_SHA256 = {'OgreResourceGroupManager.h': '1ff3bf682e6723128544d4f0d948fc7408b1179cb1bb42961f80e1967b107529', 'OgrePrerequisites.h': '50f2942df14c86e7b94ff7bebd3e69582b9f9a255952250a2f42c24e1129b32a', 'OgrePlatform.h': '2a985daab37135a00251daae5973e7be8ce0a64e1fb12bb1d5a0280627ecf0e5', 'OgreConfig.h': 'a4252bb5b0f6cf860f335c4d34f29946225c79e3c8392ef7e8ce6107c7c36aaf'}
    OGRE_VALUE_HEADER_SHA256 = {'OgrePrerequisites.h': '50f2942df14c86e7b94ff7bebd3e69582b9f9a255952250a2f42c24e1129b32a', 'OgrePlatform.h': '2a985daab37135a00251daae5973e7be8ce0a64e1fb12bb1d5a0280627ecf0e5', 'OgreConfig.h': 'a4252bb5b0f6cf860f335c4d34f29946225c79e3c8392ef7e8ce6107c7c36aaf', 'OgreVector3.h': '3eb0c292006d0d57cb4756169f0390fea22e4d14905be127d353be5d4b493051', 'OgreQuaternion.h': '58fee85f3032d4d0d1e5de279b5cf8e45734a8e40fbe5961a60fd4cbfeddb0b9', 'OgreString.h': '9cdc1263f53e0f5aa49e115e6e3dcaad4b90140a6b5c8ceeab5d95a5fd586ad7', 'OgreMatrix4.h': '9d379f1bd2be7be264de50fed7b6ddad034af06e30eb30a3c2ce752f36e8d416', 'OgreMath.h': '01516be146b17a6a3700f2001f2f33e89953b0f738b5c23ca4475075f33b88f1'}
    OGRE_CONFIG_SHA256 = '870183a4fc081077262dbf2a950d0f325038abecae12fac39c797f29503e92f3'

    OGRE_VALUE_HEADER_SHA256.update({
        'OgreColourValue.h': 'c0d1e6f49898e76c710af5ec486252123bd40b58533f08ad6295a33654587cbf',
        'OgreMovableObject.h': '05f263df5d38820f92812185506ed9cbb285ab49f1af01eb8a948b26006fe88c',
        'OgreSceneManager.h': '3f3eecf9737adf236491b60d994411482fd048b462748c44ba134454a1c380e3',
    })

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
        self.callback_aliases = _callback_aliases(self.sources)
        self.identity = DeclarationIdentity(self.sources)

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
        """Version-proven imported C++ objects and the three stdio stream pointers.

        Require agreement of DB scope, actual Itanium namespace encoding, a
        defined nonlocal ELF object at the same base/name, GLIBCXX version on
        that borrowed symbol, and a matching COPY relocation. Unversioned game
        definitions/instantiations remain strict gaps until separately proven.
        """
        if obj.get("bind") not in ("global", "weak"):
            return None
        raw = obj.get("name", "").split("@", 1)[0]
        readable = obj.get("demangled") or ""
        if raw in ("stdin", "stdout", "stderr") and readable.split("@", 1)[0] == raw:
            if obj.get("size") != 8:
                return None
            owner = "stdio"
        elif readable.startswith("std::") and re.match(r"^_ZN(?:St(?=[0-9])|Ss(?=[0-9])|Sb(?=I))", raw):
            owner = "std"
        elif readable.startswith("__gnu_cxx::") and re.match(r"^_ZN9__gnu_cxx(?=[0-9IE])", raw):
            owner = "__gnu_cxx"
        else:
            return None
        base = _address(obj["address"])
        if self.copy_data.get(base) != raw:
            return None
        if owner == "stdio" and self.elf_object_sizes.get((base, raw)) != {8}:
            return None
        for name in sorted(self.elf_object_names.get((base, raw), ())):
            version = re.search(r"@{1,2}(GLIBC_2\.2\.5)$" if owner == "stdio" else
                                r"@{1,2}(GLIBCXX_[0-9]+(?:\.[0-9]+)*)$", name)
            if version:
                return f"{owner}; borrowed ELF STT_OBJECT + {version[1]} + matching R_X86_64_COPY"
        return None

    STRING_TEMPLATE_HEADERS = {
        "basic_string.h": "7addd054a6f6853580380360029bd06e428828d3577472a34058b7d39381b3f4",
        "basic_string.tcc": "d3c6bff2d8eb0b804da6faf0fad4b282eb3c7421ec5cd92795f30da3c0ba6e19",
    }

    def _string_template_headers(self):
        """Read reviewed compiler headers only; never install or run anything."""
        cache = Path(os.environ.get("OTL_DECOMP_CACHE", str(Path.home() / ".cache/opentorchlight/decomp")))
        directory = cache / "gcc447/usr/include/c++/4.4.4/bits"
        try:
            return all(hashlib.sha256((directory / name).read_bytes()).hexdigest() == digest
                       for name, digest in self.STRING_TEMPLATE_HEADERS.items())
        except OSError:
            return False

    def _string_template_data(self, obj):
        """Two reviewed GNU-unique empty reps from the pinned original image.

        These are template definitions, not imported GLIBCXX COPY objects.
        Require original identity, exact DB and both ELF table identities,
        GNU-unique binding, 32-byte allocated writable zero-fill storage and
        the reviewed compiler declaration/definition. No namespace exemption.
        """
        original = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"
        if self.db.get("original_elf_sha256") != original or getattr(self.image, "sha256", None) != original:
            return None
        variants = {"j": ("unsigned int", 0x1426460), "t": ("unsigned short", 0x1426440)}
        for code, (ctype, base) in variants.items():
            raw = "_ZNSbI%sSt11char_traitsI%sESaI%sEE4_Rep20_S_empty_rep_storageE" % (code, code, code)
            label = "std::basic_string<%s, std::char_traits<%s>, std::allocator<%s> >::_Rep::_S_empty_rep_storage" % (ctype, ctype, ctype)
            if obj.get("name") != raw:
                continue
            if (obj.get("demangled") != label or _address(obj["address"]) != base
                    or obj.get("size") != 32 or obj.get("bind") != "?"
                    or obj.get("file") is not None or obj.get("section") != ".bss"):
                return None
            for symbols in (getattr(self.image, "symbols", ()), getattr(self.image, "dynsyms", ())):
                found = [v for v in symbols if v.name == raw]
                if (len(found) != 1 or not found[0].defined or found[0].type != 1
                        or found[0].bind != 10 or found[0].value != base
                        or found[0].size != 32):
                    return None
            sec = self.image.section_at(base)
            if (not sec or sec.name != ".bss" or sec.type != 8 or sec.flags & 7 != 3
                    or base + 32 > sec.addr + sec.size or base in self.copy_data):
                return None
            if not self._string_template_headers():
                return None
            return "std::basic_string<%s>; pinned GNU-unique STT_OBJECT in both ELF tables, 32-byte BSS, reviewed basic_string.h/tcc" % ctype
        return None

    def _fmod_error_switch_data(self, obj, f, asm, tu):
        """Only the pinned compiler table of the verified ErrorString source.

        This proves a specific header function, not the whole FMOD SDK/runtime
        version, nor arbitrary FMOD/CSWTCH data. No synthetic extern is emitted.
        """
        original = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"
        base = 0xfe38e0
        pins = {10930304: ('_ZN13CSoundManager14getSoundLengthEP14CSoundInstance', 'CSoundManager::getSoundLength', 402, 'c074e2c1f09304da12317782b3b66c9636312ff62384ea7591068cadd46af5cc', [[10930554, 'mov', '0xfe38e0(,%rax,8),%rbp']]), 10930720: ('_ZN13CSoundManager9playSoundEP14CSoundInstancePN4Ogre9SceneNodeEif', 'CSoundManager::playSound', 2124, '8a750d2c351033c1357f3c0e9ed29c5e78563daaa2de82da852474d4afff95f9', [[10931306, 'mov', '0xfe38e0(,%rax,8),%rbp']]), 10933424: ('_ZN13CSoundManager11createSoundESbIwSt11char_traitsIwESaIwEE10SOUND_TYPEbff', 'CSoundManager::createSound', 1950, 'b00320700ac5213e340589919e63d0340cfc24ed71bc6eb17b7ef65dceaa0da8', [[10934199, 'mov', '0xfe38e0(,%r13,8),%rsi']]), 10938400: ('_ZN13CSoundManager10initializeEP9CSettings', 'CSoundManager::initialize', 1682, '63a64a1c5cb2db29dd049f44d54596add7d857db406e67b52e2f2941b4e14d47', [[10939058, 'mov', '0xfe38e0(,%rdx,8),%rbp'], [10939167, 'mov', '0xfe38e0(,%rdx,8),%rbx']])}
        identity = pins.get(_address(f["address"]))
        if (self.db.get("original_elf_sha256") != original or getattr(self.image, "sha256", None) != original
                or not identity or tu != "SoundManager.cpp" or self._tu(f, None) != tu
                or f.get("mangled") != identity[0] or f.get("names") != [identity[0]]
                or f.get("qualified") != identity[1] or f.get("size") != identity[2]
                or obj.get("name") != "CSWTCH.3054" or obj.get("demangled") != "CSWTCH.3054"
                or _address(obj["address"]) != base or obj.get("size") != 768
                or obj.get("file") != tu or obj.get("bind") != "local" or obj.get("section") != ".rodata"):
            return None
        found = [s for s in getattr(self.image,"symbols",()) if s.name == "CSWTCH.3054"]
        if (len(found) != 1 or not found[0].defined or found[0].type != 1 or found[0].bind != 0
                or found[0].value != base or found[0].size != 768 or found[0].file != tu):
            return None
        section = self.image.section_at(base)
        if (not section or section.name != ".rodata" or section.type != 1 or section.flags & 7 != 2
                or base+768 > section.addr+section.size or base in self.copy_data):
            return None
        sdk = self.root / "third_party/fmod-error-4.44.06/include"
        expected_headers = {'fmod.h': '611f6cbaf273a609ee5cc99eec5b6a7d7b1c4a5cee8516f5312db8c47ba77a7c', 'fmod_errors.h': 'c8efee0ca405be7750bdd46686f4e5ef28f540cfcfe71a646877f3399ea3fe2d'}
        try:
            raw = {name:(sdk/name).read_bytes() for name in expected_headers}
            if any(hashlib.sha256(raw[name]).hexdigest() != digest for name,digest in expected_headers.items()):
                return None
            if hashlib.sha256((self.root/"decomp/include/FmodErrors.h").read_bytes()).hexdigest() != '077f45aa8d8a1de4e2c488a75ca2ec9ddd4ecc5fbd72810f174925d9887e6d54':
                return None
            if (hashlib.sha256(self._read_bytes(base,768)).hexdigest()
                    != "01cfdeac9d6d44a717d8f776fc39c28f4f2fccc8dfe602515decb1f9ac36c07b"
                    or hashlib.sha256(self._read_bytes(_address(f["address"]),identity[2])).hexdigest() != identity[3]):
                return None
            # All 96 enum values and terminated strings are checked, including
            # whitespace. Compiler-generated pointer bytes alone are not enough.
            header = raw["fmod.h"].decode("utf-8")
            end = header.index("} FMOD_RESULT;")
            start = header.rfind("typedef enum",0,end)
            enum = _mask(header[start:end]).split("{",1)[1]
            values, value = {}, 0
            for item in enum.split(","):
                item=item.strip()
                if not item: continue
                if "=" in item:
                    name,assigned=item.split("=",1);value=int(assigned.strip(),0)
                else: name=item
                values[name.strip()]=value;value+=1
            errors = raw["fmod_errors.h"].decode("utf-8")
            cases = re.findall(r'case\s+(FMOD_[A-Z0-9_]+)\s*:\s*return\s*"([^"\\]*)"\s*;',errors)
            strings = {values[name]:text for name,text in cases}
            if set(strings) != set(range(96)) or values.get("FMOD_RESULT_FORCEINT") != 65536:
                return None
            interface = (self.root/"decomp/include/FmodInterface.h").read_text()
            if _mask(header[start:end+len("} FMOD_RESULT;")]) not in _mask(interface):
                return None
            for index in range(96):
                address = int.from_bytes(self._read_bytes(base+index*8,8),"little")
                expected = strings[index].encode("ascii")+b"\0"
                target = self.image.section_at(address)
                if (not target or target.name != ".rodata" or target.type != 1 or target.flags & 7 != 2
                        or address+len(expected)>target.addr+target.size
                        or self._read_bytes(address,len(expected)) != expected):
                    return None
        except (OSError,ValueError,KeyError,UnicodeError):
            return None
        actual = {address:(op,args.split("<",1)[0].split("#",1)[0].strip()) for address,op,args in _instructions(f,asm)}
        if any(actual.get(address) != (op,args) for address,op,args in identity[4]):
            return None
        return ("compiler result table of authentic FMOD_ErrorString; all 96 enum-indexed strings byte-verified; "
                "source header is 4.44.06, whole SDK/runtime pin is unchanged; use FmodErrors.h; no data declaration synthesized")

    def _quest_icon_switch_data(self, obj, f, asm, tu):
        """One pinned compiler-generated result table, not a game declaration.

        GCC lowered getNPCIcon's switch to a bounded signed-int lookup. Require
        both ELF/DB identity, local STT_OBJECT ownership, exact immutable bytes
        and the actual indexed consumer instructions. Unknown CSWTCH objects
        remain ordinary unresolved data; no synthetic C++ extern is emitted.
        """
        original = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"
        name, base, symbol = "CSWTCH.4688", 0xff77d0, "_ZN13CQuestManager10getNPCIconEP10CCharacter"
        if (self.db.get("original_elf_sha256") != original
                or getattr(self.image, "sha256", None) != original
                or tu != "QuestManager.cpp" or self._tu(f, None) != tu
                or _address(f["address"]) != 0xd30830 or f.get("size") != 202
                or f.get("names") != [symbol] or f.get("mangled") != symbol
                or f.get("qualified") != "CQuestManager::getNPCIcon"
                or obj.get("name") != name or obj.get("demangled") != name
                or _address(obj["address"]) != base or obj.get("size") != 16
                or obj.get("file") != tu or obj.get("bind") != "local"
                or obj.get("section") != ".rodata"):
            return None
        found = [s for s in getattr(self.image, "symbols", ()) if s.name == name]
        if (len(found) != 1 or not found[0].defined or found[0].type != 1
                or found[0].bind != 0 or found[0].value != base
                or found[0].size != 16 or found[0].file != tu):
            return None
        sec = self.image.section_at(base)
        if (not sec or sec.name != ".rodata" or sec.type != 1
                or sec.flags & 7 != 2 or base + 16 > sec.addr + sec.size
                or base in self.copy_data):
            return None
        try:
            if (self._read_bytes(base, 16) != bytes.fromhex("170000001a00000016000000ffffffff")
                    or hashlib.sha256(self._read_bytes(0xd30830, 202)).hexdigest()
                    != "779ab1c7b0f0a6766221424fd1ed0dca53980ebd135c746fe6bd9eedf8a36c66"):
                return None
        except (ValueError, OSError):
            return None
        actual = {address: (op, args.split("<", 1)[0].split("#", 1)[0].strip())
                  for address, op, args in _instructions(f, asm)}
        expected = {
            0xd308d7: ("or", "$0xffffffff,%eax"),
            0xd308e5: ("mov", "0x70(%rdx),%edx"),
            0xd308e8: ("add", "%eax,%edx"),
            0xd308ea: ("cmp", "$0x3,%edx"),
            0xd308ed: ("ja", "d308bd"),
            0xd308ef: ("mov", "%edx,%edx"),
            0xd308f1: ("mov", "0xff77d0(,%rdx,4),%eax"),
        }
        if any(actual.get(address) != value for address, value in expected.items()):
            return None
        return ("pinned GCC switch result table; local read-only STT_OBJECT; "
                "four complete little-endian signed 32-bit entries [23, 26, 22, -1]; "
                "getNPCIcon subtracts one from state, unsigned-checks index <= 3, "
                "then loads one 32-bit entry; default is -1; no game declaration synthesized")

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
                    if op == "xor" and args == "%esi,%esi":
                        register, immediate = "esi", 0
                    elif op == "mov" and value:
                        register, immediate = value[2], int(value[1], 16)
                    else:
                        break
                    if register in assigned:
                        break
                    assigned[register] = immediate
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
        element = name in {"CEGUIEditbox.h", "CEGUIFrameWindow.h"}
        directory = sdk / "elements" if element else sdk
        path = directory / _basename(name)
        value = None
        if (name in self.CEGUI_HEADER_SHA256 and path.resolve().parent == directory
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

    def _ogre_value_data(self, obj):
        """Only reviewed COPY-imported constants in the pinned default ABI."""
        identities = {
            "_ZN4Ogre4Math2PIE": ("Ogre::Math::PI", 4, "OgreMath.h", "Real", "PI"),
            "_ZN4Ogre4Math6TWO_PIE": ("Ogre::Math::TWO_PI", 4, "OgreMath.h", "Real", "TWO_PI"),
            "_ZN4Ogre12SceneManager24WORLD_GEOMETRY_TYPE_MASKE": ("Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK", 4, "OgreSceneManager.h", "uint32", "WORLD_GEOMETRY_TYPE_MASK"),
            "_ZN4Ogre4Math8fRad2DegE": ("Ogre::Math::fRad2Deg", 4, "OgreMath.h", "Real", "fRad2Deg"),
            "_ZN4Ogre4Math8fDeg2RadE": ("Ogre::Math::fDeg2Rad", 4, "OgreMath.h", "Real", "fDeg2Rad"),
            "_ZN4Ogre7Vector36UNIT_ZE": ("Ogre::Vector3::UNIT_Z", 12, "OgreVector3.h", "Vector3", "UNIT_Z"),
            "_ZN4Ogre4Math12POS_INFINITYE": ("Ogre::Math::POS_INFINITY", 4, "OgreMath.h", "Real", "POS_INFINITY"),
            "_ZN4Ogre7Vector36UNIT_XE": ("Ogre::Vector3::UNIT_X", 12, "OgreVector3.h", "Vector3", "UNIT_X"),
            "_ZN4Ogre7Vector310UNIT_SCALEE": ("Ogre::Vector3::UNIT_SCALE", 12, "OgreVector3.h", "Vector3", "UNIT_SCALE"),
            "_ZN4Ogre11ColourValue4ZEROE": ("Ogre::ColourValue::ZERO", 16, "OgreColourValue.h", "ColourValue", "ZERO"),
            "_ZN4Ogre7Vector36UNIT_YE": ("Ogre::Vector3::UNIT_Y", 12, "OgreVector3.h", "Vector3", "UNIT_Y"),
            "_ZN4Ogre7Vector315NEGATIVE_UNIT_YE": ("Ogre::Vector3::NEGATIVE_UNIT_Y", 12, "OgreVector3.h", "Vector3", "NEGATIVE_UNIT_Y"),
            "_ZN4Ogre7Matrix48IDENTITYE": ("Ogre::Matrix4::IDENTITY", 64, "OgreMatrix4.h", "Matrix4", "IDENTITY"),
            "_ZN4Ogre7Vector34ZEROE": ("Ogre::Vector3::ZERO", 12, "OgreVector3.h", "Vector3", "ZERO"),
            "_ZN4Ogre10Quaternion8IDENTITYE": ("Ogre::Quaternion::IDENTITY", 16, "OgreQuaternion.h", "Quaternion", "IDENTITY"),
            "_ZN4Ogre10StringUtil5BLANKE": ("Ogre::StringUtil::BLANK", 8, "OgreString.h", "String", "BLANK"),
            "_ZN4Ogre11ColourValue5WhiteE": ("Ogre::ColourValue::White", 16, "OgreColourValue.h", "ColourValue", "White"),
            "_ZN4Ogre11ColourValue5BlackE": ("Ogre::ColourValue::Black", 16, "OgreColourValue.h", "ColourValue", "Black"),
            "_ZN4Ogre13MovableObject24msDefaultVisibilityFlagsE": ("Ogre::MovableObject::msDefaultVisibilityFlags", 4, "OgreMovableObject.h", "uint32", "msDefaultVisibilityFlags"),
        }
        raw = obj.get("name", "")
        row = identities.get(raw)
        if not row:
            return None
        label, size, header, typ, member = row
        if (obj.get("demangled") != label or obj.get("bind") not in ("global", "weak")
                or obj.get("size") != size):
            return None
        base = _address(obj["address"])
        if (self.copy_data.get(base) != raw or raw not in self.elf_object_names.get((base, raw), ())
                or self.elf_object_sizes.get((base, raw)) != {size}):
            return None
        sec = self.image.section_at(base)
        if (not sec or sec.type != 8 or sec.flags & 3 != 3 or base + size > sec.addr + sec.size):
            return None
        try:
            if hashlib.sha256((self.root / "decomp/config.json").read_bytes()).hexdigest() != self.OGRE_CONFIG_SHA256:
                return None
            cache = Path(os.environ.get("OTL_DECOMP_CACHE", Path.home() / ".cache/opentorchlight/decomp"))
            sdk = (cache / "gcc447/ogre-1.6.5/ogre/OgreMain/include").resolve()
            sources = {}
            for name, expected in self.OGRE_VALUE_HEADER_SHA256.items():
                path = sdk / name
                if path.resolve().parent != sdk:
                    return None
                value = path.read_bytes()
                if hashlib.sha256(value).hexdigest() != expected:
                    return None
                sources[name] = value.decode("utf-8")
            prerequisites = _mask(sources["OgrePrerequisites.h"])
            config = sources["OgreConfig.h"]
            if (not re.search(r"#\s*define\s+OGRE_DOUBLE_PRECISION\s+0\b", config)
                    or not re.search(r"typedef\s+float\s+Real\s*;", prerequisites)
                    or not re.search(r"typedef\s+std::string\s+_StringBase\s*;", prerequisites)
                    or not re.search(r"typedef\s+_StringBase\s+String\s*;", prerequisites)):
                return None
            declarations, _ = _scan(re.sub(r"\b_OgreExport\b", "", sources[header]))
        except (OSError, UnicodeError, KeyError):
            return None
        qualifier = "" if raw in ("_ZN4Ogre13MovableObject24msDefaultVisibilityFlagsE", "_ZN4Ogre12SceneManager24WORLD_GEOMETRY_TYPE_MASKE") else r"const\s+"
        expected = r"static\s+" + qualifier + typ + r"\s+" + member + r"\s*;"
        matches = [d for d in declarations if d.kind == "data" and d.qualified == label
                   and re.fullmatch(expected, _mask(d.text).strip())]
        if len(matches) != 1:
            return None
        return ("OGRE1.6.5 SDK declaration " + _mask(matches[0].text).strip()
                + "; exact ELF object/COPY identity, pinned float/narrow-string profile, "
                + str(size) + " bytes; " + str(len(self.OGRE_VALUE_HEADER_SHA256))
                + " SDK header pins and decomp/config.json SHA256 "
                + self.OGRE_CONFIG_SHA256 + "; referenced subobject offsets do not imply separate symbols")

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
        event = re.fullmatch(r"CEGUI::(Window)::(Event\w+)", label)
        element_events = {
            "CEGUI::Editbox::EventTextAccepted": ("Editbox", "EventTextAccepted", 0x1424940),
            "CEGUI::FrameWindow::EventCloseClicked": ("FrameWindow", "EventCloseClicked", 0x1423c60),
        }
        element = element_events.get(label)
        if event or element:
            if event:
                owner, name = event[1], event[2]
                header = "CEGUIWindow.h"
            else:
                owner, name, address = element
                if base != address:
                    return None
                header = "CEGUI" + owner + ".h"
            if raw != f"_ZN5CEGUI{len(owner)}{owner}{len(name)}{name}E" or obj["size"] != 176:
                return None
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

    WINDOW_ARRAY_HEADER_SHA256 = "d91f88adac805622a3e58081386a6b121b6b8f0d57bc4621886b9e5af591519f"

    def _window_array_headers(self, callee, scope):
        """Pinned existing pointer-array destructor, without an invented prototype.

        Only the exact weak Window* D1/D2 specialization is recognized. The
        array elements are pointers; this body does not destroy the Windows.
        """
        if (scope != "TArrayList<CEGUI::Window*>"
                or callee.get("kind") != "inline_or_template"
                or set(callee.get("bind", ())) != {"weak"}
                or callee.get("method") != "~TArrayList"
                or callee.get("qualified") != scope + "::~TArrayList"
                or callee.get("params") != "" or callee.get("cv", "")):
            return set()
        names = {"_ZN10TArrayListIPN5CEGUI6WindowEED1Ev",
                 "_ZN10TArrayListIPN5CEGUI6WindowEED2Ev"}
        if (set(callee.get("names", ())) != names or callee.get("mangled") not in names
                or any((_address(callee["address"]), name, callee.get("size"))
                       not in self.elf_weak_functions for name in names)):
            return set()
        header = "TArrayList.h"
        # The shallow class scanner intentionally omits class templates.
        # The exact reviewed template source is authenticated below instead.
        if header not in self.sources:
            return set()
        raw = self._path("include", header).read_bytes()
        if (hashlib.sha256(raw).hexdigest() != self.WINDOW_ARRAY_HEADER_SHA256
                or raw.decode("utf-8") != self.sources[header]):
            return set()
        return {header}

    AXIS_BOX_ARRAY_SDK_SHA256 = {'OgreAxisAlignedBox.h': '3371a8579af08a86687eaec523643759cfa807e3491b5fde8d8bccaa58095401', 'OgrePrerequisites.h': '50f2942df14c86e7b94ff7bebd3e69582b9f9a255952250a2f42c24e1129b32a', 'OgrePlatform.h': '2a985daab37135a00251daae5973e7be8ce0a64e1fb12bb1d5a0280627ecf0e5', 'OgreConfig.h': 'a4252bb5b0f6cf860f335c4d34f29946225c79e3c8392ef7e8ce6107c7c36aaf', 'OgreVector3.h': '3eb0c292006d0d57cb4756169f0390fea22e4d14905be127d353be5d4b493051', 'OgreMatrix4.h': '9d379f1bd2be7be264de50fed7b6ddad034af06e30eb30a3c2ce752f36e8d416', 'OgreMemoryAllocatorConfig.h': '80fe5786bde1ca7148d410e24f6a5aa2f81c11e39108020cf1f0307bcabb0bc6', 'OgreMemoryAllocatedObject.h': '769489c2d7260a4ab919338728a71e51cfb2f0131020924854b7fbf3016ff311', 'OgreMemorySTLAllocator.h': 'cd83b553ec3df877b8d460898303140afc233f5d471e2434ad35cdc484d38a9e', 'OgreMemoryNedAlloc.h': '0b4e3e35618cb6902090ebc5d52a3952b2357389b87a7d467e95dc460a24c099', 'OgreMemoryStdAlloc.h': '45f99d554796d62db295b8cc2c44fe3760996ad47b808469ffa7ef2665bfb975', 'OgreAlignedAllocator.h': 'b33d3f164d8e3bdc0f3a2e31b926d12ba39852292df51773b0ea7e3424b00bd5'}

    def _pinned_destructor_headers(self, callee, scope):
        """Reviewed existing template bodies, never a generic exemption.

        Original ASM: wstring delete[] destroys elements using the array cookie,
        then frees and clears data; safe pointers unregister and reset both fields.
        Quest/BaseUnit/editor/level pointer arrays free only the array storage and clear its pointer.
        Only the reviewed address, size, D1/D2 aliases and unmodified source count.
        """
        wide = "std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >"
        reviewed = {
            "TRepository<" + wide + " >":
                (0xc629f0, 178, "_ZN11TRepositoryISbIwSt11char_traitsIwESaIwEEE",
                 "~TRepository", "TRepository.h", self.REPOSITORY_HEADER_SHA256, None),
            "TArrayList<float>":
                (0x59fb40, 26, "_ZN10TArrayListIfE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<unsigned int>":
                (0x90da70, 26, "_ZN10TArrayListIjE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<CEquipmentRef*>":
                (0x90da50, 26, "_ZN10TArrayListIP13CEquipmentRefE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, "CEquipmentRef"),
            "TArrayList<EEFFECT_STAT_MODIFIERS>":
                (0x7e4740, 26, "_ZN10TArrayListI22EEFFECT_STAT_MODIFIERSE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<CDataGroup*>":
                (0x85acd0, 26, "_ZN10TArrayListIP10CDataGroupE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<UNIONDATA32BIT>":
                (0x70ca90, 26, "_ZN10TArrayListI14UNIONDATA32BITE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<CSkill*>":
                (0xcd57a0, 26, "_ZN10TArrayListIP6CSkillE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, "CSkill"),
            "TArrayList<Ogre::AxisAlignedBox>":
                (0x967520, 91, "_ZN10TArrayListIN4Ogre14AxisAlignedBoxEE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<CLayout*>":
                (0x967160, 26, "_ZN10TArrayListIP7CLayoutE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<CPropertyNode*>":
                (0x967140, 26, "_ZN10TArrayListIP13CPropertyNodeE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<CChunk*>":
                (0x97cb30, 26, "_ZN10TArrayListIP6CChunkE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<CLevelLayout*>":
                (0x97cb50, 26, "_ZN10TArrayListIP12CLevelLayoutE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<CChunkType*>":
                (0x97cb70, 26, "_ZN10TArrayListIP10CChunkTypeE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<CEditorBaseObject*>":
                (0x740b90, 26, "_ZN10TArrayListIP17CEditorBaseObjectE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<CBaseUnit*>":
                (0xd49940, 26, "_ZN10TArrayListIP9CBaseUnitE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<iMenuListener*>":
                (0xb1ba10, 26, "_ZN10TArrayListIP13iMenuListenerE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, "iMenuListener"),
            "TArrayList<CQuestDialogItem*>":
                (0xd26480, 26, "_ZN10TArrayListIP16CQuestDialogItemE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<CQuestDialog*>":
                (0xd1d3f0, 26, "_ZN10TArrayListIP12CQuestDialogE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<TArrayList<CQuestUnitData*>*>":
                (0xd1d3d0, 26, "_ZN10TArrayListIPS_IP14CQuestUnitDataEE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<" + wide + " >":
                (0x5f8e90, 155, "_ZN10TArrayListISbIwSt11char_traitsIwESaIwEEE",
                 "~TArrayList", "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TSafePointer<CItem>":
                (0x591be0, 47, "_ZN12TSafePointerI5CItemE",
                 "~TSafePointer", "SafePointer.h", self.SAFE_POINTER_HEADER_SHA256, "CItem"),
            "TSafePointer<CCharacter>":
                (0x591b50, 47, "_ZN12TSafePointerI10CCharacterE",
                 "~TSafePointer", "SafePointer.h", self.SAFE_POINTER_HEADER_SHA256, "CCharacter"),
            "TSafePointer<CPositionableObject>":
                (0xd06790, 47, "_ZN12TSafePointerI19CPositionableObjectE",
                 "~TSafePointer", "SafePointer.h", self.SAFE_POINTER_HEADER_SHA256, "CPositionableObject"),
            "TSafePointer<CEquipment>":
                (0xacbc90, 47, "_ZN12TSafePointerI10CEquipmentE",
                 "~TSafePointer", "SafePointer.h", self.SAFE_POINTER_HEADER_SHA256, "CEquipment"),
            "TSafePointer<CGraph>":
                (0xcf8e70, 47, "_ZN12TSafePointerI6CGraphE",
                 "~TSafePointer", "SafePointer.h", self.SAFE_POINTER_HEADER_SHA256, "CGraph"),
            "TSafePointer<CSkill>":
                (0x7d5f90, 47, "_ZN12TSafePointerI6CSkillE",
                 "~TSafePointer", "SafePointer.h", self.SAFE_POINTER_HEADER_SHA256, "CSkill"),
            "TSafePointer<CBaseUnit>":
                (0x7d5fc0, 47, "_ZN12TSafePointerI9CBaseUnitE",
                 "~TSafePointer", "SafePointer.h", self.SAFE_POINTER_HEADER_SHA256, "CBaseUnit"),
            "TSafePointer<CEffectManager>":
                (0x7d5ff0, 47, "_ZN12TSafePointerI14CEffectManagerE",
                 "~TSafePointer", "SafePointer.h", self.SAFE_POINTER_HEADER_SHA256, "CEffectManager"),
        }
        entry = reviewed.get(scope)
        if entry is None:
            return set()
        address, size, prefix, method, header, digest, pointee = entry
        names = {prefix + "D1Ev", prefix + "D2Ev"}
        if (callee.get("kind") != "inline_or_template"
                or set(callee.get("bind", ())) != {"weak"}
                or _address(callee["address"]) != address or callee.get("size") != size
                or callee.get("method") != method
                or callee.get("qualified") != scope + "::" + method
                or callee.get("params") != "" or callee.get("cv", "")
                or set(callee.get("names", ())) != names or callee.get("mangled") not in names
                or any((address, name, size) not in self.elf_weak_functions for name in names)):
            return set()
        if header not in self.sources:
            return set()
        raw = self._path("include", header).read_bytes()
        if hashlib.sha256(raw).hexdigest() != digest or raw.decode("utf-8") != self.sources[header]:
            return set()
        headers = {header}
        if scope == "TArrayList<Ogre::AxisAlignedBox>":
            # Native 0x967520 destroys each 40-byte AABB, including its owned
            # corner buffer, then frees the cookie-bearing array. The exact
            # existing template instantiation MATCHes under this SDK/profile.
            try:
                configuration = (self.root / "decomp/config.json").read_bytes()
                if hashlib.sha256(configuration).hexdigest() != self.OGRE_CONFIG_SHA256:
                    return set()
                cache = Path(os.environ.get("OTL_DECOMP_CACHE", Path.home() / ".cache/opentorchlight/decomp"))
                sdk = (cache / "gcc447/ogre-1.6.5/ogre/OgreMain/include").resolve()
                for name, expected in self.AXIS_BOX_ARRAY_SDK_SHA256.items():
                    path = sdk / name
                    if path.resolve().parent != sdk or hashlib.sha256(path.read_bytes()).hexdigest() != expected:
                        return set()
            except OSError:
                return set()
        if scope in ("TArrayList<UNIONDATA32BIT>", "TArrayList<CSkill*>"):
            owner = "DescriptorProp.cpp" if scope == "TArrayList<UNIONDATA32BIT>" else "SkillManager.cpp"
            if self._tu(callee, None) != owner:
                return set()
        if scope == "TArrayList<UNIONDATA32BIT>":
            # The value element (unlike a pointer element) must be complete and
            # have the reviewed trivial destruction semantics. Pin its actual
            # defining header; do not generalize this to arbitrary unions.
            element_header = "DescriptorProp.h"
            expected = "fa61042a581530fd2af7fae6abb34fc71ae2cec53c914749af7b2f1e7902193a"
            source = self.sources.get(element_header)
            if (source is None or hashlib.sha256(source.encode()).hexdigest() != expected
                    or self._path("include", element_header).read_text() != source
                    or "UNIONDATA32BIT" not in self.header_classes.get(element_header, ())):
                return set()
            headers.add(element_header)
        if pointee:
            complete = {h for h in self._mapped(pointee)
                        if pointee in self.header_classes.get(h, ())}
            if len(complete) != 1:
                return set()
            headers.update(complete)
        return headers

    REPOSITORY_HEADER_SHA256 = "7ba56f5caed6ad2de4c4bb6600a1d8e0fb2160127366e9bfb5f7d3269356c7f1"

    def _pinned_insert_headers(self, callee, scope):
        """Seven reviewed weak insertions already declared by generic headers.

        The shallow scanner omits class templates. Supply only authenticated
        existing source for these exact identities, never a generated declaration
        or permission for arbitrary methods/instantiations.
        """
        wide = "std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >"
        reviewed = {
            "TArrayList<CBaseUnit*>":
                (0x9ca560, 180, "_ZN10TArrayListIP9CBaseUnitE3addES1_", "add", "CBaseUnit*",
                 "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, "CBaseUnit"),
            "TArrayList<CEditorBaseObject*>":
                (0x9e0a30, 180, "_ZN10TArrayListIP17CEditorBaseObjectE3addES1_", "add", "CEditorBaseObject*",
                 "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, "CEditorBaseObject"),
            "TArrayList<CSkill*>":
                (0xcd56e0, 180, "_ZN10TArrayListIP6CSkillE3addES1_", "add", "CSkill*",
                 "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, "CSkill"),
            "TArrayList<CDataGroup*>":
                (0xa7e5e0, 180, "_ZN10TArrayListIP10CDataGroupE3addES1_", "add", "CDataGroup*",
                 "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, "CDataGroup"),
            "TArrayList<" + wide + " >":
                (0xafca50, 439, "_ZN10TArrayListISbIwSt11char_traitsIwESaIwEEE3addES3_",
                 "add", wide, "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<int>":
                (0xa69ec0, 180, "_ZN10TArrayListIiE3addEi", "add", "int",
                 "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TArrayList<bool>":
                (0x90da90, 176, "_ZN10TArrayListIbE3addEb", "add", "bool",
                 "TArrayList.h", self.WINDOW_ARRAY_HEADER_SHA256, None),
            "TRepository<" + wide + " >":
                (0xc64bf0, 1409, "_ZN11TRepositoryISbIwSt11char_traitsIwESaIwEEE7addItemERS3_",
                 "addItem", wide + "&", "TRepository.h", self.REPOSITORY_HEADER_SHA256, None),
        }
        entry = reviewed.get(scope)
        if entry is None:
            return set()
        address, size, symbol, method, params, header, digest, pointee = entry
        if (callee.get("kind") != "inline_or_template"
                or set(callee.get("bind", ())) != {"weak"}
                or _address(callee["address"]) != address or callee.get("size") != size
                or callee.get("method") != method or callee.get("cv", "")
                or callee.get("qualified") != scope + "::" + method
                or callee.get("params") != params or callee.get("mangled") != symbol
                or set(callee.get("names", ())) != {symbol}
                or (address, symbol, size) not in self.elf_weak_functions):
            return set()
        source = self.sources.get(header)
        if source is None:
            return set()
        raw = self._path("include", header).read_bytes()
        if hashlib.sha256(raw).hexdigest() != digest or raw.decode("utf-8") != source:
            return set()
        headers = {header}
        if pointee:
            complete = {h for h in self._mapped(pointee)
                        if pointee in self.header_classes.get(h, ())}
            if len(complete) != 1:
                return set()
            owner = next(iter(complete))
            if self._path("include", owner).read_text() != self.sources[owner]:
                return set()
            headers.update(complete)
        elif scope not in ("TArrayList<int>", "TArrayList<bool>") and not self._string_template_headers():
            return set()
        return headers

    QUADTREE_HEADER_SHA256 = "8379f5116bc6783f18f65ab09f6f4192aca7f728ade2bb9c62196678d4618172"

    def _quadtree_headers(self, callee, scope):
        """Two reviewed native instantiations, with the real complete template.

        Quadtree.h layout is backed by native RTTI, allocations, stores and
        owning destructors. The shallow scanner intentionally omits templates.
        Never synthesize a specialization or accept arbitrary instantiations.
        """
        reviewed = {
            "sort": (0x9689b0, 905,
                     "_ZN13CQuadtreeNodeIjE4sortERKN4Ogre7Vector3ES4_bRSt6vectorIjSaIjEE",
                     "Ogre::Vector3 const&, Ogre::Vector3 const&, bool, std::vector<unsigned int, std::allocator<unsigned int> >&"),
            "addData": (0x967af0, 1586,
                        "_ZN13CQuadtreeNodeIjE7addDataEjRKN4Ogre7Vector3ES4_f",
                        "unsigned int, Ogre::Vector3 const&, Ogre::Vector3 const&, float"),
        }
        entry = reviewed.get(callee.get("method"))
        if entry is None or scope != "CQuadtreeNode<unsigned int>":
            return set()
        address, size, name, params = entry
        if (callee.get("kind") != "inline_or_template"
                or set(callee.get("bind", ())) != {"weak"}
                or _address(callee["address"]) != address or callee.get("size") != size
                or callee.get("qualified") != scope + "::" + callee["method"]
                or callee.get("params") != params or callee.get("cv", "")
                or callee.get("mangled") != name or set(callee.get("names", ())) != {name}
                or (address, name, size) not in self.elf_weak_functions):
            return set()
        header = "Quadtree.h"
        source = self.sources.get(header)
        if source is None:
            return set()
        raw = self._path("include", header).read_bytes()
        if (hashlib.sha256(raw).hexdigest() != self.QUADTREE_HEADER_SHA256
                or raw.decode("utf-8") != source):
            return set()
        return {header}

    def _level_update_timer_data(self, obj, f, tu, address):
        """Exact original initialized function-local float storage, not an extern.

        Its 100.0f initializer is file-backed .data, unlike the generic .bss
        route. ASM determines the C++ type separately; include complete bytes.
        """
        raw = "_ZZN6CLevel6updateEPN4Ogre6CameraERKNS0_7Vector3EffP7CPlayerE11UpdateTimer"
        fn = "_ZN6CLevel6updateEPN4Ogre6CameraERKNS0_7Vector3EffP7CPlayer"
        original = "91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b"
        if (self.db.get("original_elf_sha256") != original
                or getattr(self.image, "sha256", None) != original
                or tu != "level.cpp" or _address(f["address"]) != 0x95c7f0
                or f.get("size") != 376 or f.get("mangled") != fn
                or set(f.get("names", ())) != {fn}
                or obj.get("bind") != "local" or obj.get("file") != tu
                or _address(obj["address"]) != 0x14210b4 or address != 0x14210b4
                or obj.get("size") != 4 or obj.get("name") != raw
                or obj.get("demangled") != f.get("demangled", "") + "::UpdateTimer"
                or (address, raw, 4, tu) not in self.local_object_names):
            return False
        section = self.image.section_at(address)
        if (section is None or section.type != 1 or section.name != ".data"
                or section.flags != 3 or address + 4 > section.addr + section.size):
            return False
        try:
            return self.image.read(address, 4) == bytes.fromhex("0000c842")
        except ValueError:
            return False

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

    def _target_local_initializer(self, obj, f, tu):
        """Expose complete original bytes, not an inferred source declaration/type.

        A named local static has no external header dependency. Require exact
        target/function/file identity and reject storage whose bytes are not a
        complete immutable initializer. This is packet evidence, never acceptance.
        """
        raw, name = obj.get("name", ""), obj.get("demangled", "")
        prefix = f.get("demangled", "") + "::"
        if not name.startswith(prefix):
            return None
        local = name[len(prefix):]
        if not re.fullmatch(r"[A-Za-z_][A-Za-z_0-9]*", local):
            return None
        symbols = f.get("names", [f.get("mangled", "")])
        if not any(raw == "_ZZ" + symbol[2:] + "E" + str(len(local)) + local
                   for symbol in symbols if symbol.startswith("_Z")):
            return None
        base, size = _address(obj["address"]), obj.get("size", 0)
        identity = (base, raw, size, obj.get("file"))
        if (obj.get("bind") != "local" or obj.get("file") != tu
                or identity not in self.local_object_names or not 0 < size <= 8192):
            return None
        section, available = self._available(base, [obj])
        if section is None or section.flags != 2 or available < size:
            return None
        # Do not present relocation-dependent pointers as final initialized bytes.
        if any(base - 7 <= offset < base + size
               for offset in getattr(self.image, "relocs", {})):
            return None
        if any(other is not obj and _address(other["address"]) < base + size
               and _address(other["address"]) + other.get("size", 0) > base
               for other in self.objects):
            return None
        payload = self._read_bytes(base, size)
        return (f"{base:#x}: target function-local readonly initialized storage; "
                f"exact ELF local STT_OBJECT, matching mangled function identity and STT_FILE. "
                f"Complete initializer ({size} bytes): {payload.hex(' ')}; "
                f"SHA256 {hashlib.sha256(payload).hexdigest()}. "
                "No external header declaration needed; C++ type is not inferred; "
                "initializer bytes are context, not behavior acceptance.")

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
            local_types = {t.qualified: t for t in self.local_cache[tu]}
            duplicated_local_names = {name for name in local_types
                                      if sum(t.qualified == name for t in self.local_cache[tu]) > 1
                                      or ("::" not in name and sum(t.name == name for t in self.local_cache[tu]) > 1)}
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
            if ((scope.split("::")[0] in self.LIBRARY_SCOPES
                 and scope not in local_types)
                    or callee.get("kind") == "compiler"):
                continue  # weak library instantiations can be linked into a game STT_FILE group
            qualified = callee.get("qualified") or (scope + "::" if scope else "") + callee.get("method", "")
            label = callee.get("demangled") or qualified or f"{address:#x}"
            facts.append(f"Direct game call/tail-call {address:#x}: {label}; return/static not encoded by symbol.")
            candidates = self._mapped(scope) if scope else []
            matches = self._matching(qualified, "function")
            matched_headers, matched_dependencies = set(), set()
            for name, decl in matches:
                if ((not candidates or name in candidates)
                        and self.identity.matches(decl, callee, name, dependencies=matched_dependencies)):
                    matched_headers.add(name)
            implicit_headers = self._implicit_destructor_headers(callee, scope, candidates)
            template_headers = self._safe_pointer_headers(callee, scope)
            window_array_headers = self._window_array_headers(callee, scope)
            pinned_destructor_headers = self._pinned_destructor_headers(callee, scope)
            pinned_insert_headers = self._pinned_insert_headers(callee, scope)
            quadtree_headers = self._quadtree_headers(callee, scope)
            if matched_headers:
                wanted.update(matched_headers | matched_dependencies)
            elif implicit_headers:
                wanted.update(implicit_headers)
                notes.append(f"{address:#x}: weak D1/D2 destructor implicitly declared by the existing complete class header; no guessed return type.")
            elif template_headers:
                wanted.update(template_headers)
                notes.append(f"{address:#x}: existing pinned TSafePointer setObject template body; "
                             f"weak ELF/DB identity and complete pointee header; SafePointer.h SHA256 {self.SAFE_POINTER_HEADER_SHA256}. "
                             "No specialization or prototype synthesized.")
            elif window_array_headers:
                wanted.update(window_array_headers)
                notes.append(f"{address:#x}: existing pinned TArrayList<CEGUI::Window*> D1/D2 destructor body; "
                             f"both weak ELF/DB identities; TArrayList.h SHA256 {self.WINDOW_ARRAY_HEADER_SHA256}. "
                             "No specialization or prototype synthesized.")
            elif pinned_destructor_headers:
                wanted.update(pinned_destructor_headers)
                digest = (self.REPOSITORY_HEADER_SHA256 if scope.startswith('TRepository<') else
                          self.SAFE_POINTER_HEADER_SHA256 if scope.startswith('TSafePointer<') else
                          self.WINDOW_ARRAY_HEADER_SHA256)
                notes.append(f"{address:#x}: existing pinned {scope} D1/D2 destructor body; "
                             "exact reviewed address/size and both weak ELF/DB identities; "
                             f"template source SHA256 {digest}. "
                             "No specialization or prototype synthesized.")
            elif pinned_insert_headers:
                wanted.update(pinned_insert_headers)
                notes.append(f"{address:#x}: existing pinned {scope} insertion template declaration; "
                             "exact reviewed address/size and weak ELF/DB identity; "
                             f"template source SHA256 {self.REPOSITORY_HEADER_SHA256 if scope.startswith('TRepository<') else self.WINDOW_ARRAY_HEADER_SHA256}. "
                             "No specialization or prototype synthesized.")
            elif quadtree_headers:
                wanted.update(quadtree_headers)
                notes.append(f"{address:#x}: exact reviewed native Quadtree<unsigned> method identity; "
                             f"complete existing template declaration; Quadtree.h SHA256 {self.QUADTREE_HEADER_SHA256}. "
                             "No specialization or prototype synthesized.")
            elif scope in local_types and ("::" in scope or self._tu(callee, None) == tu):
                local_names.add(scope)
                local_dependencies = set()
                if not any(d.qualified == qualified and self.identity.matches(d, callee, dependencies=local_dependencies)
                           for d in self.local_declarations[tu]):
                    gaps.append(f"No declaration of direct callee {label} in its existing TU-local type")
                else:
                    wanted.update(local_dependencies)
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
                fmod = self._fmod_error_switch_data(obj, f, asm, tu)
                if fmod:
                    wanted.add("FmodErrors.h")
                    notes.append(f"{address:#x}: {fmod}.")
                    continue
                switch = self._quest_icon_switch_data(obj, f, asm, tu)
                if switch:
                    notes.append(f"{address:#x}: {switch}.")
                    continue
                library = self._library_data(obj) or self._string_template_data(obj) or self._cegui_data(obj) or self._ogre_data(obj) or self._ogre_value_data(obj)
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
                if raw == "_ZZN6CLevel6updateEPN4Ogre6CameraERKNS0_7Vector3EffP7CPlayerE11UpdateTimer":
                    if self._level_update_timer_data(obj, f, tu, address):
                        notes.append(f"{address:#x}: exact ELF/STT_FILE target-local initialized storage; "
                                     "all 4 initializer bytes 00 00 c8 42; C++ type is not inferred; "
                                     "no external header declaration required.")
                    else:
                        gaps.append(f"Level UpdateTimer {address:#x} lacks exact ELF identity/initializer")
                    continue
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
                initializer = self._target_local_initializer(obj, f, tu)
                if initializer:
                    notes.append(initializer)
                    continue
                matches = self._matching(name, "data")
                if not matches:
                    gaps.append(f"No existing header declaration for referenced data {name} ({address:#x})")
                elif len(matches) != 1:
                    gaps.append(f"Ambiguous header declarations for referenced data {name} ({address:#x})")
                    continue
                for header, declaration in matches:
                    if declaration.asm_symbol is not None:
                        identity = (_address(obj["address"]), obj.get("name"), obj.get("size"), owner)
                        section = self.image.section_at(identity[0])
                        if (obj.get("name") != declaration.asm_symbol or obj.get("bind") != "local"
                                or obj.get("size") != 8 or identity not in self.local_object_names
                                or section is None or section.type != 8 or section.flags != 3
                                or identity[0] + 8 > section.addr + section.size):
                            gaps.append(f"Asm-labelled wstring {name} lacks exact local ELF identity/storage")
                            continue
                    if declaration.scalar_literal_bytes is not None:
                        base = _address(obj["address"])
                        section = self.image.section_at(base)
                        identity = (base, obj.get("name", ""), obj.get("size"), owner)
                        if (obj.get("bind") != "local" or identity not in self.local_object_names
                                or obj.get("size") != 4 or section is None or section.type != 1
                                or section.flags not in (2, 3) or base + 4 > section.addr + section.size
                                or self._read_bytes(base, 4) != declaration.scalar_literal_bytes):
                            gaps.append(f"Literal int scalar {name} lacks exact local ELF identity/size/initial bytes")
                            continue
                    if declaration.int_array_values is not None or declaration.scalar_array_bytes is not None:
                        expected = (b"".join(n.to_bytes(4, "little", signed=True)
                                             for n in declaration.int_array_values)
                                    if declaration.int_array_values is not None else declaration.scalar_array_bytes)
                        base = _address(obj["address"])
                        section, available = self._available(base, [obj])
                        identity = (base, obj.get("name", ""), obj.get("size"), owner)
                        if (obj.get("bind") != "local" or identity not in self.local_object_names
                                or obj.get("size") != len(expected) or section is None
                                or available < len(expected)
                                or self._read_bytes(base, len(expected)) != expected):
                            kind = "int" if declaration.int_array_values is not None else "scalar"
                            gaps.append(f"Literal {kind} array {name} lacks exact local ELF identity/size/read-only bytes")
                            continue
                    if declaration.array_width:
                        widths.add(declaration.array_width)
                    if declaration.whole_header or any(k == "class" for k, _ in declaration.scopes):
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
