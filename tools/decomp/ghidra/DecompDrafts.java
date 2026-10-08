// Ghidra headless post-script for tools/decomp/ghidra_draft.py.
// Applies recovered class layouts (build-decomp/types.json) as the `this`
// structures of class namespaces, gives every polymorphic class a vtable
// structure with method-named slots, then decompiles the target functions.
//
// Arguments: <types.json> <targets.txt: one hex address per line> <output dir>
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.decompiler.parallel.DecompileConfigurer;
import ghidra.app.decompiler.parallel.DecompilerCallback;
import ghidra.app.decompiler.parallel.ParallelDecompiler;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.*;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.GhidraClass;
import ghidra.program.model.listing.ParameterImpl;
import ghidra.program.model.listing.ReturnParameterImpl;
import ghidra.program.model.listing.Variable;
import ghidra.program.model.listing.VariableStorage;
import ghidra.program.model.listing.VariableUtilities;
import ghidra.program.model.symbol.Namespace;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.program.model.symbol.SymbolUtilities;
import ghidra.app.util.NamespaceUtils;
import ghidra.util.task.TaskMonitor;

public class DecompDrafts extends GhidraScript {
    private DataTypeManager dtm;
    private JsonObject classes;
    private JsonObject vtables;
    private final Set<String> typeErrors = new HashSet<>();
    private final Set<Function> prototypeErrors = new HashSet<>();
    private final Map<String, Structure> structs = new HashMap<>();
    private final Map<String, Union> unions = new HashMap<>();
    private final Set<String> filledClasses = new HashSet<>();
    private final Set<String> fillingClasses = new HashSet<>();
    private final Set<String> declaredClasses = new HashSet<>();
    private final CategoryPath category = new CategoryPath("/decomp");

    private static List<String> qualifiedParts(String name) throws Exception {
        List<String> parts = new ArrayList<>();
        int start = 0;
        int templates = 0;
        for (int i = 0; i < name.length(); i++) {
            char c = name.charAt(i);
            if (c == '<') templates++;
            if (c == '>') templates--;
            if (templates < 0) throw new IllegalArgumentException("unbalanced type name " + name);
            if (templates == 0 && c == ':' && i + 1 < name.length() && name.charAt(i + 1) == ':') {
                parts.add(name.substring(start, i));
                start = ++i + 1;
            }
        }
        if (templates != 0) throw new IllegalArgumentException("unbalanced type name " + name);
        parts.add(name.substring(start));
        for (String part : parts) {
            SymbolUtilities.validateName(part);
        }
        return parts;
    }

    private Structure structFor(String name) throws Exception {
        if (typeErrors.contains(name)) {
            throw new IllegalArgumentException("unsupported/conflicting class " + name);
        }
        if (structs.containsKey(name)) {
            return structs.get(name);
        }
        if (name.indexOf('<') >= 0) {
            // C++ template spellings can contain spaces rejected by the symbol
            // table. Datatype names support those spellings, so keep the exact
            // identity without inventing a class namespace or flattening scopes.
            StructureDataType body = new StructureDataType(category, name, 0, dtm);
            body.setDescription("C++ type: " + name);
            Structure s = (Structure) dtm.addDataType(body, DataTypeConflictHandler.REPLACE_HANDLER);
            structs.put(name, s);
            return s;
        }
        List<String> parts = qualifiedParts(name);
        SymbolTable table = currentProgram.getSymbolTable();
        Namespace ns = currentProgram.getGlobalNamespace();
        for (String part : parts) {
            Namespace child = table.getNamespace(part, ns);
            ns = child != null ? child : table.createNameSpace(ns, part, SourceType.USER_DEFINED);
        }
        GhidraClass cls = ns instanceof GhidraClass ? (GhidraClass) ns : NamespaceUtils.convertNamespaceToClass(ns);
        Structure s = VariableUtilities.findOrCreateClassStruct(cls, dtm);
        structs.put(name, s);
        return s;
    }

    private boolean prepareClass(String name) {
        try {
            classType(name);
            return true;
        } catch (Exception e) {
            typeErrors.add(name);
            printerr("diagnostic skip: class " + name + ": " + e);
            return false;
        }
    }

    private DataType classType(String name) throws Exception {
        JsonObject layout = classes.getAsJsonObject(name);
        if (layout != null && layout.has("kind") && layout.get("kind").getAsString().equals("union")) {
            if (typeErrors.contains(name)) throw new IllegalArgumentException("unsupported union " + name);
            if (!unions.containsKey(name)) {
                unions.put(name, (Union) dtm.addDataType(new UnionDataType(category, name, dtm),
                    DataTypeConflictHandler.REPLACE_HANDLER));
            }
            return unions.get(name);
        }
        return structFor(name);
    }

    private void importClassIdentities(JsonObject identities) {
        if (identities == null) return;
        for (String ref : identities.keySet()) {
            JsonObject identity = identities.getAsJsonObject(ref);
            String tag = identity.get("tag").getAsString();
            if (tag.equals("DW_TAG_class_type") || tag.equals("DW_TAG_structure_type")
                    || tag.equals("DW_TAG_union_type")) {
                declaredClasses.add(identity.get("name").getAsString());
            }
        }
    }

    private DataType basic(String type, int size) throws Exception {
        String t = type.trim().replaceFirst("^(?:(?:const|volatile)\\s+)+", "");
        if (t.endsWith("*")) {
            String inner = t.substring(0, t.length() - 1).trim();
            DataType target;
            if ((typeErrors.contains(inner) && classes.has(inner) && structs.containsKey(inner))
                    || (!classes.has(inner) && declaredClasses.contains(inner))) {
                // A known C++ class can be incomplete behind a pointer. Its
                // invalid field layout must not contaminate an enclosing 8-byte
                // pointer field or a scalar/pointer call ABI. Never reuse its
                // old, partially populated structure for dereferences.
                StructureDataType opaque = new StructureDataType(new CategoryPath("/decomp/incomplete-pointees"),
                    "opaque_" + inner, 0, dtm);
                opaque.setDescription("Incomplete pointee: " + inner + "; pointer identity only, no field layout or by-value ABI");
                target = dtm.addDataType(opaque, DataTypeConflictHandler.KEEP_HANDLER);
            } else {
                // Pointees may be incomplete and do not create a value-layout
                // dependency (including self-referential tree/list nodes).
                target = classes.has(inner) ? classType(inner) : basic(inner, 0);
            }
            if (target == null) {
                return null;  // unknown pointees are not silently replaced with void
            }
            return new PointerDataType(target, 8, dtm);
        }
        int bracket = t.indexOf('[');
        if (bracket > 0 && t.endsWith("]")) {
            int closing = t.indexOf(']', bracket);
            String extent = t.substring(bracket + 1, closing);
            if (!extent.matches("[0-9]+")) return null;
            String inner = t.substring(0, bracket) + t.substring(closing + 1);
            int count = Integer.parseInt(extent);
            DataType element = basic(inner, 0);
            if (element != null && element.getLength() > 0 && count > 0) {
                return new ArrayDataType(element, count, element.getLength(), dtm);
            }
            return null;
        }
        if (classes.has(t)) {
            fill(t);
            return classType(t);
        }
        DataType p = primitive(t, size);
        if (p != null) {
            return p;
        }
        if (size > 0 && (t.startsWith("undefined") || t.equals("?"))) {
            return Undefined.getUndefinedDataType(size);
        }
        return null;
    }

    private DataType primitive(String t, int size) {
        switch (t) {
            case "int": case "signed int": return size == 0 || size == 4 ? IntegerDataType.dataType : null;
            case "long": case "long int": case "signed long": case "signed long int":
                return size == 0 || size == 8 ? LongLongDataType.dataType : null;
            case "unsigned int": return size == 0 || size == 4 ? UnsignedIntegerDataType.dataType : null;
            case "unsigned long": case "unsigned long int": case "long unsigned int":
                return size == 0 || size == 8 ? UnsignedLongLongDataType.dataType : null;
            case "long long": case "long long int": return LongLongDataType.dataType;
            case "long long unsigned int": case "unsigned long long": return UnsignedLongLongDataType.dataType;
            case "short": case "short int": return ShortDataType.dataType;
            case "short unsigned int": case "unsigned short": return UnsignedShortDataType.dataType;
            case "char": case "signed char": return CharDataType.dataType;
            case "unsigned char": return UnsignedCharDataType.dataType;
            case "bool": return BooleanDataType.dataType;
            case "float": return FloatDataType.dataType;
            case "double": return DoubleDataType.dataType;
            case "wchar_t": return WideChar32DataType.dataType;
            case "void": return VoidDataType.dataType;
            case "std::wstring": case "std::string": {
                StructureDataType s = new StructureDataType(category, t.equals("std::wstring") ? "wstring" : "string", 0, dtm);
                s.add(new PointerDataType(t.equals("std::wstring") ? WideChar32DataType.dataType : CharDataType.dataType, 8, dtm), 8, "_M_p", null);
                return dtm.addDataType(s, DataTypeConflictHandler.KEEP_HANDLER);
            }
            default: return null;
        }
    }

    private Structure vtableFor(String name) {
        if (!vtables.has(name)) {
            return null;
        }
        StructureDataType s = new StructureDataType(category, name + "_vtbl", 0, dtm);
        for (JsonElement slot : vtables.getAsJsonArray(name)) {
            s.add(new PointerDataType(VoidDataType.dataType, 8, dtm), 8, slot.getAsString(), null);
        }
        return (Structure) dtm.addDataType(s, DataTypeConflictHandler.REPLACE_HANDLER);
    }

    // Flattened fields of a class and its bases at their final offsets.
    private void collect(String name, int base, StructureDataType out, int depth) throws Exception {
        if (depth > 40 || !classes.has(name) || typeErrors.contains(name)) {
            throw new IllegalArgumentException("unrepresented/cyclic base " + name);
        }
        JsonObject c = classes.getAsJsonObject(name);
        if (c.has("layout_errors")) {
            throw new IllegalArgumentException("unsupported DWARF layout " + name + ": " + c.get("layout_errors"));
        }
        for (JsonElement b : c.getAsJsonArray("bases")) {
            JsonObject bo = b.getAsJsonObject();
            if (bo.get("offset").isJsonNull() || bo.get("offset").getAsInt() < 0) {
                throw new IllegalArgumentException("unknown base offset " + name);
            }
            String baseName = bo.get("name").getAsString();
            // An empty/unknown-size base must not be accepted simply because
            // flattening it contributes no fields. Validate the entire base
            // before its owner can enter filledClasses, regardless of order.
            fill(baseName);
            collect(baseName, base + bo.get("offset").getAsInt(), out, depth + 1);
        }
        for (JsonElement f : c.getAsJsonArray("fields")) {
            JsonObject fo = f.getAsJsonObject();
            int offset = base + fo.get("offset").getAsInt();
            String fname = fo.get("name").getAsString();
            int size = fo.get("size").getAsInt();
            DataType dt = fname.startsWith("_vptr") ? null : basic(fo.get(fo.has("ghidra_type") ? "ghidra_type" : "type").getAsString(), size);
            if (fname.startsWith("_vptr")) {
                continue;  // vptrs are set by the caller with the most derived vtable type
            }
            if (dt == null || dt.getLength() <= 0 || dt.getLength() != size
                    || offset + dt.getLength() > out.getLength()) {
                throw new IllegalArgumentException("unrepresented/conflicting field " + name + "::" + fname);
            }
            try {
                out.replaceAtOffset(offset, dt, dt.getLength(), fname, null);
            } catch (Exception e) {
                throw new IllegalArgumentException("overlapping field " + name + "::" + fname, e);
            }
        }
    }

    private void fill(String name) throws Exception {
        if (typeErrors.contains(name)) {
            throw new IllegalArgumentException("unsupported/conflicting class " + name);
        }
        if (filledClasses.contains(name)) return;
        if (!fillingClasses.add(name)) {
            throw new IllegalArgumentException("cyclic value layout " + name);
        }
        try {
            JsonObject c = classes.getAsJsonObject(name);
            int size = c.get("size").getAsInt();
            if (size <= 0) {
                throw new IllegalArgumentException("unknown class size " + name);
            }
            if (c.has("kind") && c.get("kind").getAsString().equals("union")) {
                if (c.has("layout_errors") || c.getAsJsonArray("bases").size() != 0) {
                    throw new IllegalArgumentException("unsupported union layout " + name);
                }
                UnionDataType body = new UnionDataType(category, name, dtm);
                for (JsonElement element : c.getAsJsonArray("fields")) {
                    JsonObject field = element.getAsJsonObject();
                    int width = field.get("size").getAsInt();
                    DataType type = basic(field.get(field.has("ghidra_type") ? "ghidra_type" : "type").getAsString(), width);
                    if (field.get("offset").getAsInt() != 0 || type == null || type.getLength() <= 0
                            || type.getLength() != width || width > size) {
                        throw new IllegalArgumentException("unrepresented union member " + name);
                    }
                    body.add(type, width, field.get("name").getAsString(), null);
                }
                if (body.getLength() != size) throw new IllegalArgumentException("conflicting union size " + name);
                ((Union) classType(name)).replaceWith(body);
                filledClasses.add(name);
                return;
            }
            StructureDataType body = new StructureDataType(category, name, size, dtm);
            Structure vt = vtableFor(name);
            if (vt != null) {
                body.replaceAtOffset(0, new PointerDataType(vt, 8, dtm), 8, "_vptr", null);
            }
            collect(name, 0, body, 0);
            Structure target = structFor(name);
            target.replaceWith(body);
            filledClasses.add(name);
        } catch (Exception e) {
            typeErrors.add(name);
            throw e;
        } finally {
            fillingClasses.remove(name);
        }
    }

    // Integer argument registers of the System V AMD64 ABI by operand size.
    private static final String[][] INT_REGS = {
        {"DIL", "SIL", "DL", "CL", "R8B", "R9B"}, {"DI", "SI", "DX", "CX", "R8W", "R9W"},
        {"EDI", "ESI", "EDX", "ECX", "R8D", "R9D"}, {"RDI", "RSI", "RDX", "RCX", "R8", "R9"}};

    private VariableStorage intRegister(int index, int size) throws Exception {
        int row = size <= 1 ? 0 : size <= 2 ? 1 : size <= 4 ? 2 : 3;
        Register r = currentProgram.getRegister(INT_REGS[row][index]);
        if (r == null) {
            r = currentProgram.getRegister(INT_REGS[3][index]);
        }
        return new VariableStorage(currentProgram, r);
    }

    private DataType protoType(String type, int size) throws Exception {
        DataType dt = "?".equals(type) ? null : basic(type, size);
        if (dt == null || dt.getLength() <= 0) {
            dt = "?".equals(type) && size > 0 && size <= 8 ? Undefined.getUndefinedDataType(size) : null;
        }
        return dt;
    }

    // Applies a prototype from the recovered headers (types_export.py): the parameter types of the
    // symbol, the declared return type where it is trusted, no `this` for static members, and an
    // object returned through a hidden pointer as the first argument (RDI, then `this` in RSI),
    // which Ghidra does not infer for non-trivial classes of 8 bytes such as std::wstring.
    private boolean applyPrototype(Function fn, JsonObject p) throws Exception {
        if (p.has("variadic") && p.get("variadic").getAsBoolean()) {
            return false;  // preserve a variadic signature until its call ABI is represented
        }
        if (typeErrors.contains(p.get("ret").getAsString())) {
            return false;
        }
        boolean isStatic = p.has("member") ? !p.get("member").getAsBoolean() : p.get("static").getAsBoolean();
        List<DataType> types = new ArrayList<>();
        for (JsonElement e : p.getAsJsonArray("params")) {
            JsonObject po = e.getAsJsonObject();
            String spelling = po.get("type").getAsString();
            if (typeErrors.contains(spelling.replace("const ", "").replace("volatile ", "").replace("*", "").trim())) {
                return false;
            }
            DataType dt = protoType(spelling, po.get("size").getAsInt());
            if (dt == null) {
                return false;  // an object passed by value: Ghidra's own signature stays
            }
            types.add(dt);
        }
        int retSize = p.get("ret_size").getAsInt();
        DataType ret = p.get("trusted").getAsBoolean() ? protoType(p.get("ret").getAsString(), retSize) : null;
        Namespace parent = fn.getParentNamespace();
        if (p.get("sret").getAsBoolean()) {
            DataType object = ret != null && ret.getLength() > 0 && !(ret instanceof Undefined) ? ret
                : classes.has(p.get("ret").getAsString()) ? classType(p.get("ret").getAsString())
                : new ArrayDataType(ByteDataType.dataType, Math.max(1, retSize), 1, dtm);
            DataType pointer = new PointerDataType(object, 8, dtm);
            List<Variable> params = new ArrayList<>();
            int ints = 0;
            int floats = 0;
            params.add(new ParameterImpl("__return_storage_ptr__", pointer, intRegister(ints++, 8), currentProgram));
            if (!isStatic) {
                DataType self = parent != null && classes.has(parent.getName(true)) ? structFor(parent.getName(true))
                    : VoidDataType.dataType;
                params.add(new ParameterImpl("this", new PointerDataType(self, 8, dtm), intRegister(ints++, 8),
                    currentProgram));
            }
            for (int i = 0; i < types.size(); i++) {
                DataType dt = types.get(i);
                VariableStorage at;
                if (dt instanceof FloatDataType || dt instanceof DoubleDataType) {
                    if (floats >= 8) {
                        return false;
                    }
                    at = new VariableStorage(currentProgram,
                        currentProgram.getRegister("XMM" + floats++ + (dt.getLength() == 4 ? "_Da" : "_Qa")));
                } else {
                    if (dt.getLength() > 8 || ints >= 6) {
                        return false;  // stack arguments: not worth custom storage here
                    }
                    at = intRegister(ints++, dt.getLength());
                }
                params.add(new ParameterImpl("param_" + (i + 1), dt, at, currentProgram));
            }
            Variable result = new ReturnParameterImpl(pointer,
                new VariableStorage(currentProgram, currentProgram.getRegister("RAX")), currentProgram);
            fn.updateFunction(isStatic ? "__stdcall" : "__thiscall", result, params,
                Function.FunctionUpdateType.CUSTOM_STORAGE, true, SourceType.USER_DEFINED);
            return true;
        }
        List<Variable> params = new ArrayList<>();
        for (int i = 0; i < types.size(); i++) {
            params.add(new ParameterImpl("param_" + (i + 1), types.get(i), currentProgram));
        }
        Variable result = new ReturnParameterImpl(ret != null ? ret : fn.getReturnType(), currentProgram);
        fn.updateFunction(isStatic ? "__stdcall" : "__thiscall", result, params,
            Function.FunctionUpdateType.DYNAMIC_STORAGE_FORMAL_PARAMS, true, SourceType.USER_DEFINED);
        return true;
    }

    private void writeStatus(Path out, String address, String status, String error) throws Exception {
        JsonObject receipt = new JsonObject();
        receipt.addProperty("status", status);
        receipt.addProperty("error", error == null ? "" : error);
        Files.writeString(out.resolve(address + ".status.json"), receipt.toString(), StandardCharsets.UTF_8);
    }

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        dtm = currentProgram.getDataTypeManager();
        JsonObject root = JsonParser.parseString(Files.readString(Paths.get(args[0]))).getAsJsonObject();
        String expectedElf = root.get("original_elf_sha256").getAsString();
        if (!expectedElf.equals(currentProgram.getExecutableSHA256())) {
            throw new IllegalArgumentException("Ghidra project executable SHA256 differs from the requested original ELF");
        }
        classes = root.getAsJsonObject("classes");
        importClassIdentities(root.getAsJsonObject("type_identities"));
        vtables = root.getAsJsonObject("vtables");
        if (root.has("class_conflicts")) {
            typeErrors.addAll(root.getAsJsonObject("class_conflicts").keySet());
        }
        List<String> targets = Files.readAllLines(Paths.get(args[1]), StandardCharsets.UTF_8);
        Path out = Paths.get(args[2]);
        Files.createDirectories(out);

        for (String name : classes.keySet()) {
            prepareClass(name);
        }
        int filled = 0;
        for (String name : classes.keySet()) {
            if (typeErrors.contains(name)) {
                continue;
            }
            try {
                fill(name);
                filled++;
            } catch (Exception e) {
                typeErrors.add(name);
                printerr("type " + name + ": " + e);
            }
        }
        println("applied " + filled + " class layouts");

        Set<Function> prototyped = new HashSet<>();
        JsonObject prototypes = root.has("prototypes") ? root.getAsJsonObject("prototypes") : new JsonObject();
        int failed = 0;
        if (root.has("prototype_conflicts")) {
            for (String address : root.getAsJsonObject("prototype_conflicts").keySet()) {
                Function fn = getFunctionAt(toAddr(address));
                if (fn != null) {
                    prototypeErrors.add(fn);
                    failed++;
                }
            }
        }
        for (String address : prototypes.keySet()) {
            Function fn = getFunctionAt(toAddr(address));
            if (fn == null) {
                continue;
            }
            try {
                if (applyPrototype(fn, prototypes.getAsJsonObject(address))) {
                    prototyped.add(fn);
                } else {
                    prototypeErrors.add(fn);
                    failed++;
                }
            } catch (Exception e) {
                failed++;
                prototypeErrors.add(fn);
                printerr("prototype " + address + ": " + e);
            }
        }
        println("applied " + prototyped.size() + " method prototypes from the headers (" + failed + " failed)");

        // SDK signatures are keyed by exact ELF linkage name. Demangled short names are
        // deliberately not matched, and aggregate register classes still require an ABI probe.
        JsonObject sdk = root.has("sdk_prototypes") ? root.getAsJsonObject("sdk_prototypes") : new JsonObject();
        int sdkApplied = 0;
        int sdkUnverified = 0;
        for (Function fn : currentProgram.getFunctionManager().getFunctions(true)) {
            Function target = fn.isThunk() ? fn.getThunkedFunction(true) : fn;
            String link = target != null && sdk.has(target.getName()) ? target.getName()
                : sdk.has(fn.getName()) ? fn.getName() : null;
            if (link == null) {
                continue;
            }
            JsonObject p = sdk.getAsJsonObject(link);
            if (!"SCALAR_OR_POINTER".equals(p.get("abi_status").getAsString())) {
                sdkUnverified++;
                continue;
            }
            try {
                if (applyPrototype(fn, p)) {
                    prototyped.add(fn);
                    sdkApplied++;
                } else {
                    prototypeErrors.add(fn);
                    sdkUnverified++;
                }
            } catch (Exception e) {
                prototypeErrors.add(fn);
                sdkUnverified++;
                printerr("SDK prototype " + link + ": " + e);
            }
        }
        println("applied " + sdkApplied + " exact scalar/pointer SDK prototypes (" + sdkUnverified
            + " found but unrepresented/aggregate)");

        // Methods whose `this` Ghidra dropped (unused in the body) still take it at call sites.
        int fixed = 0;
        for (Function fn : currentProgram.getFunctionManager().getFunctions(true)) {
            Namespace parent = fn.getParentNamespace();
            String fname = fn.getName();
            // Only real classes: Ghidra also turns plain namespaces (UTILITIES, MATH) into classes.
            boolean real = parent != null && (classes.has(parent.getName(true)) || vtables.has(parent.getName(true)));
            if (!(parent instanceof GhidraClass) || !real || fname.startsWith("Get_") || fname.startsWith("Set_")
                    || prototyped.contains(fn) || "__thiscall".equals(fn.getCallingConventionName())) {
                continue;
            }
            try {
                fn.setCallingConvention("__thiscall");
                fixed++;
            } catch (Exception e) {
                // keep Ghidra's convention
            }
        }
        println("set __thiscall on " + fixed + " methods");

        List<Function> functions = new ArrayList<>();
        for (String line : targets) {
            line = line.trim();
            if (line.isEmpty()) {
                continue;
            }
            Address address = toAddr(line);
            Function f = getFunctionAt(address);
            if (f == null) {
                f = createFunction(address, null);
            }
            if (f == null) {
                writeStatus(out, line, "NO_BODY", "no function");
                continue;
            }
            functions.add(f);
        }
        DecompileConfigurer configurer = decompiler -> {
            decompiler.setOptions(new DecompileOptions());
            decompiler.toggleCCode(true);
        };
        DecompilerCallback<String> callback = new DecompilerCallback<>(currentProgram, configurer) {
            @Override
            public String process(DecompileResults r, TaskMonitor m) throws Exception {
                Function f = r.getFunction();
                String address = "0x" + Long.toHexString(f.getEntryPoint().getOffset());
                Namespace parent = f.getParentNamespace();
                boolean typeError = parent != null && typeErrors.contains(parent.getName(true));
                boolean protoError = prototypeErrors.contains(f);
                List<String> blockers = new ArrayList<>();
                if (typeError) blockers.add("layout: " + parent.getName(true));
                if (protoError) blockers.add("prototype: " + f.getName(true) + " @" + address);
                for (Function callee : f.getCalledFunctions(m)) {
                    if (prototypeErrors.contains(callee)) {
                        protoError = true;
                        blockers.add("callee prototype: " + callee.getName(true) + " @0x" +
                                     Long.toHexString(callee.getEntryPoint().getOffset()));
                    }
                }
                if (typeError || protoError) {
                    java.util.Collections.sort(blockers);
                    writeStatus(out, address, "TYPE_ERROR", String.join("; ", blockers));
                } else if (r.isTimedOut()) {
                    writeStatus(out, address, "TIMEOUT", r.getErrorMessage());
                } else if (!r.decompileCompleted() || r.getDecompiledFunction() == null) {
                    writeStatus(out, address, "NO_BODY", r.getErrorMessage());
                } else {
                    String code = r.getDecompiledFunction().getC();
                    if (code == null || !code.contains("{")) {
                        writeStatus(out, address, "NO_BODY", "decompiler returned no body");
                    } else {
                        Files.writeString(out.resolve(address + ".c"), code, StandardCharsets.UTF_8);
                        writeStatus(out, address, "COMPLETE", "");
                    }
                }
                return null;
            }
        };
        int timeout = args.length > 3 ? Integer.parseInt(args[3]) : 120;
        if (timeout <= 0) {
            throw new IllegalArgumentException("positive decompilation timeout required");
        }
        callback.setTimeout(timeout);
        try {
            ParallelDecompiler.decompileFunctions(callback, functions, monitor);
        } finally {
            callback.dispose();
        }
        println("decompiled " + functions.size() + " functions");
    }
}
