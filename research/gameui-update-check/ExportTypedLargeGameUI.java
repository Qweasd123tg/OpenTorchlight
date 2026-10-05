// Scoped research copy of DecompDrafts.java; generic pipeline is unchanged.
// Class layouts are hints. Verify every signature and field against ASM.
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
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.ParameterImpl;
import ghidra.program.model.listing.ReturnParameterImpl;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.listing.GhidraClass;
import ghidra.program.model.listing.VariableUtilities;
import ghidra.program.model.symbol.Namespace;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.app.util.NamespaceUtils;

public class ExportTypedLargeGameUI extends GhidraScript {
    private DataTypeManager dtm;
    private JsonObject classes;
    private JsonObject vtables;
    private final Map<String, Structure> structs = new HashMap<>();
    private final CategoryPath category = new CategoryPath("/decomp");

    private Structure structFor(String name) throws Exception {
        if (structs.containsKey(name)) {
            return structs.get(name);
        }
        SymbolTable table = currentProgram.getSymbolTable();
        Namespace ns = table.getNamespace(name, currentProgram.getGlobalNamespace());
        Structure s = null;
        if (ns != null) {
            GhidraClass cls = ns instanceof GhidraClass ? (GhidraClass) ns : NamespaceUtils.convertNamespaceToClass(ns);
            s = VariableUtilities.findOrCreateClassStruct(cls, dtm);
        }
        if (s == null) {
            s = (Structure) dtm.addDataType(new StructureDataType(category, name, 0, dtm),
                DataTypeConflictHandler.REPLACE_HANDLER);
        }
        structs.put(name, s);
        return s;
    }

    private DataType basic(String type, int size) throws Exception {
        String t = type.replace("const ", "").trim();
        if (t.endsWith("*")) {
            String inner = t.substring(0, t.length() - 1).trim();
            DataType target = inner.endsWith("*") ? basic(inner, 8)
                : classes.has(inner) ? structFor(inner) : primitive(inner, 0);
            return new PointerDataType(target == null ? VoidDataType.dataType : target, 8, dtm);
        }
        int bracket = t.indexOf('[');
        if (bracket > 0 && t.endsWith("]")) {
            String inner = t.substring(0, bracket);
            int count = Integer.parseInt(t.substring(bracket + 1, t.indexOf(']')));
            DataType element = basic(inner, 0);
            if (element != null && element.getLength() > 0 && count > 0) {
                return new ArrayDataType(element, count, element.getLength(), dtm);
            }
            return null;
        }
        if (classes.has(t)) {
            return structFor(t);
        }
        DataType p = primitive(t, size);
        if (p != null) {
            return p;
        }
        return size > 0 ? Undefined.getUndefinedDataType(size) : null;
    }

    private DataType primitive(String t, int size) {
        switch (t) {
            case "int": case "long int": return IntegerDataType.dataType;
            case "unsigned int": case "long unsigned int": return size == 8 ? UnsignedLongLongDataType.dataType : UnsignedIntegerDataType.dataType;
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
        if (depth > 12 || !classes.has(name)) {
            return;
        }
        JsonObject c = classes.getAsJsonObject(name);
        for (JsonElement b : c.getAsJsonArray("bases")) {
            JsonObject bo = b.getAsJsonObject();
            collect(bo.get("name").getAsString(), base + bo.get("offset").getAsInt(), out, depth + 1);
        }
        for (JsonElement f : c.getAsJsonArray("fields")) {
            JsonObject fo = f.getAsJsonObject();
            int offset = base + fo.get("offset").getAsInt();
            String fname = fo.get("name").getAsString();
            int size = fo.get("size").getAsInt();
            DataType dt = fname.startsWith("_vptr") ? null : basic(fo.get("type").getAsString(), size);
            if (fname.startsWith("_vptr")) {
                continue;  // vptrs are set by the caller with the most derived vtable type
            }
            if (dt == null || dt.getLength() <= 0 || offset + dt.getLength() > out.getLength()) {
                continue;
            }
            try {
                out.replaceAtOffset(offset, dt, dt.getLength(), fname, null);
            } catch (Exception e) {
                // overlapping draft fields: keep the first
            }
        }
    }

    private void fill(String name) throws Exception {
        JsonObject c = classes.getAsJsonObject(name);
        int size = c.get("size").getAsInt();
        if (size <= 0) {
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
    }

    private void prototype(long address, DataType result, DataType... arguments) throws Exception {
        Function fn = getFunctionAt(toAddr(address));
        if (fn == null) throw new IllegalStateException("Missing known service " + Long.toHexString(address));
        ParameterImpl[] params = new ParameterImpl[arguments.length];
        for (int i = 0; i < arguments.length; ++i)
            params[i] = new ParameterImpl("arg" + i, arguments[i], currentProgram);
        fn.updateFunction("__cdecl", new ReturnParameterImpl(result, currentProgram),
            Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS, true, SourceType.USER_DEFINED, params);
    }

    private void applyVerifiedServiceABIs() throws Exception {
        DataType p = new PointerDataType(VoidDataType.dataType, 8, dtm);
        DataType v = VoidDataType.dataType, b = BooleanDataType.dataType;
        DataType i = IntegerDataType.dataType, f = FloatDataType.dataType;
        // Explicit SysV lowered signatures: 'this' and hidden aggregate result
        // pointers are real arguments, not missing inputs. These are navigation
        // hints supported by ASM and the standalone original-prefix probes.
        prototype(0xc6e440L, i, p, i);       // settings GetInt
        prototype(0x91ad20L, b, p, i);       // mouse buttonPressed
        prototype(0x91ad30L, b, p, i);       // mouse buttonHeld
        prototype(0xa83900L, f, p);         // window width
        prototype(0xa838e0L, f, p);         // window height
        prototype(0x554dc8L, v, p, b);       // RadioButton::setSelected
        prototype(0x5561d8L, b, p, b);       // Window::isVisible
        prototype(0x5560d8L, v, p, p);       // getWidth: output UDim, window
        prototype(0x552ab8L, v, p, p);       // getHeight: output UDim, window
        prototype(0x5548a8L, v, p, p);       // setPosition
        prototype(0x555178L, v, p, p);       // setSize
        prototype(0x554718L, v, p, b);       // setVisible
        prototype(0x554b48L, v, p, p);       // setTooltipText
        prototype(0x80f7e0L, i, p);         // HP
        prototype(0x813e60L, i, p);         // maxHP
        prototype(0x80ea50L, f, p);         // manaFloat
        prototype(0x813a10L, i, p);         // maxMana
        prototype(0xa4e160L, p);            // GameGlobals singleton
        prototype(0x71b800L, p);            // Editor singleton
        prototype(0xa54490L, p);            // MasterResourceManager singleton
        prototype(0xe16d60L, p);            // StringTranslate singleton
        prototype(0xc8dc90L, v, p, p);      // UTF8 string result, wstring input
        prototype(0xc8e810L, v, p, i);      // string result, signed value
        prototype(0xc91f60L, v, p, i);      // string result, unsigned value bits
        prototype(0xc913a0L, v, p, i);      // wstring result, signed value
        prototype(0xa688a0L, v, p, i, f, f);// sound bank, sample, two floats
        println("Applied scoped verified service ABI hints");
    }

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        dtm = currentProgram.getDataTypeManager();
        JsonObject root = JsonParser.parseString(Files.readString(Paths.get(args[0]))).getAsJsonObject();
        classes = root.getAsJsonObject("classes");
        vtables = root.getAsJsonObject("vtables");
        List<String> targets = Files.readAllLines(Paths.get(args[1]), StandardCharsets.UTF_8);
        Path out = Paths.get(args[2]);
        Files.createDirectories(out);

        for (String name : classes.keySet()) {
            structFor(name);
        }
        int filled = 0;
        for (String name : classes.keySet()) {
            try {
                fill(name);
                filled++;
            } catch (Exception e) {
                printerr("type " + name + ": " + e);
            }
        }
        println("applied " + filled + " class layouts");

        // Methods whose `this` Ghidra dropped (unused in the body) still take it at call sites.
        int fixed = 0;
        for (Function fn : currentProgram.getFunctionManager().getFunctions(true)) {
            Namespace parent = fn.getParentNamespace();
            String fname = fn.getName();
            // Only real classes: Ghidra also turns plain namespaces (UTILITIES, MATH) into classes.
            boolean real = parent != null && (classes.has(parent.getName()) || vtables.has(parent.getName()));
            if (!(parent instanceof GhidraClass) || !real || fname.startsWith("Get_") || fname.startsWith("Set_")
                    || "__thiscall".equals(fn.getCallingConventionName())) {
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

        applyVerifiedServiceABIs();
        DecompInterface decompiler = new DecompInterface();
        DecompileOptions options = new DecompileOptions();
        options.setMaxPayloadMBytes(128);
        decompiler.setOptions(options);
        decompiler.toggleSyntaxTree(false);
        decompiler.toggleCCode(true);
        if (!decompiler.openProgram(currentProgram)) {
            throw new IllegalStateException(decompiler.getLastMessage());
        }
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
            Path file = out.resolve(line + ".c");
            if (f == null) {
                Files.writeString(file, "// no function\n");
                continue;
            }
            if (address.getOffset() == 0xab8100L) {
                f.updateFunction("__thiscall", new ReturnParameterImpl(VoidDataType.dataType, currentProgram),
                    Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS, true, SourceType.USER_DEFINED,
                    new ParameterImpl("elapsed", FloatDataType.dataType, currentProgram),
                    new ParameterImpl("client", new PointerDataType(structFor("CGameClient"), 8, dtm), currentProgram),
                    new ParameterImpl("window", new PointerDataType(VoidDataType.dataType, 8, dtm), currentProgram));
            }
            DecompileResults r = decompiler.decompileFunction(f, 600, monitor);
            String code = r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// failed: " + r.getErrorMessage() + "\n";
            Files.writeString(file, code, StandardCharsets.UTF_8);
        }
        decompiler.dispose();
    }
}
