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
import ghidra.app.util.NamespaceUtils;
import ghidra.util.task.TaskMonitor;

public class SDKTypeAuditFixed extends GhidraScript {
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
            case "int": return IntegerDataType.dataType;
            case "long int": return LongLongDataType.dataType;
            case "unsigned int": return UnsignedIntegerDataType.dataType;
            case "long unsigned int": return UnsignedLongLongDataType.dataType;
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
            dt = size > 0 && size <= 8 ? Undefined.getUndefinedDataType(size) : null;
        }
        return dt;
    }

    // Applies a prototype from the recovered headers (types_export.py): the parameter types of the
    // symbol, the declared return type where it is trusted, no `this` for static members, and an
    // object returned through a hidden pointer as the first argument (RDI, then `this` in RSI),
    // which Ghidra does not infer for non-trivial classes of 8 bytes such as std::wstring.
    private boolean applyPrototype(Function fn, JsonObject p) throws Exception {
        boolean isStatic = p.get("static").getAsBoolean();
        List<DataType> types = new ArrayList<>();
        for (JsonElement e : p.getAsJsonArray("params")) {
            JsonObject po = e.getAsJsonObject();
            DataType dt = protoType(po.get("type").getAsString(), po.get("size").getAsInt());
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
                : classes.has(p.get("ret").getAsString()) ? structFor(p.get("ret").getAsString())
                : new ArrayDataType(ByteDataType.dataType, Math.max(1, retSize), 1, dtm);
            DataType pointer = new PointerDataType(object, 8, dtm);
            List<Variable> params = new ArrayList<>();
            int ints = 0;
            int floats = 0;
            params.add(new ParameterImpl("__return_storage_ptr__", pointer, intRegister(ints++, 8), currentProgram));
            if (!isStatic) {
                DataType self = parent != null && classes.has(parent.getName()) ? structFor(parent.getName())
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

    @Override
    protected void run() throws Exception {
      dtm = currentProgram.getDataTypeManager();
      classes = new JsonObject();
      String[] names = {"long int", "long unsigned int", "int", "unsigned int"};
      for (String name : names) {
        int size = name.startsWith("long") ? 8 : 4;
        DataType direct = basic(name,size);
        DataType ptr = basic(name+"*",8);
        DataType array = basic(name+"[3]",size*3);
        if (direct.getLength()!=size || ((Pointer)ptr).getDataType().getLength()!=size || array.getLength()!=size*3) throw new Exception("width mismatch " + name);
        println("AUDIT " + name + " field=" + direct.getLength() + " pointee=" + ((Pointer)ptr).getDataType().getLength() + " array=" + array.getLength());
      }
    }
}
