// Bounded, read-only export. Arguments: targets.txt output-dir expected-ELF-SHA256
// No function creation, type commits, byte patching, auto-analysis or game execution.
// Ghidra API references and validation limits: research/codefirst/SOURCES.md.
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.security.MessageDigest;
import java.util.*;
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.framework.Application;
import ghidra.program.model.address.*;
import ghidra.program.model.block.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.PcodeOp;
import ghidra.program.model.symbol.*;

public class ExportCodeFirstPacket extends GhidraScript {
    private String module;
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 3) throw new IllegalArgumentException("Expected targets.txt output-directory expected-ELF-SHA256");
        module = args[2].toLowerCase(Locale.ROOT);
        if (!module.matches("[0-9a-f]{64}") || !module.equalsIgnoreCase(currentProgram.getExecutableSHA256()))
            throw new IllegalStateException("Expected ELF hash differs from the loaded program metadata");
        List<String> targets = new ArrayList<>();
        for (String raw : Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8)) {
            String line = raw.trim();
            if (line.isEmpty() || line.startsWith("#")) continue;
            if (!line.matches("(?:0x)?[0-9a-fA-F]{1,16}")) throw new IllegalArgumentException("Invalid target: " + line);
            String normal = line.replaceFirst("^0x", "").toLowerCase(Locale.ROOT);
            if (!targets.contains(normal)) targets.add(normal);
        }
        if (targets.isEmpty() || targets.size() > 64) throw new IllegalArgumentException("Select 1..64 functions, not the whole program");
        Path output = Paths.get(args[1]).toAbsolutePath();
        if (Files.exists(output, LinkOption.NOFOLLOW_LINKS)) throw new IllegalArgumentException("Output already exists: " + output);
        Files.createDirectories(output.getParent());
        Path temp = Files.createTempDirectory(output.getParent(), ".codefirst-export-");
        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true); decompiler.toggleSyntaxTree(true);
        boolean decompilerReady = decompiler.openProgram(currentProgram);
        List<Object> entries = new ArrayList<>();
        try {
            for (String raw : targets) {
                monitor.checkCancelled();
                Address target = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(raw);
                Function fn = currentProgram.getFunctionManager().getFunctionAt(target);
                // No getFunctionContaining fallback: an interior address must not
                // silently turn into a successful export of another entry.
                String a = addr(target);
                Map<String,Object> data = object("schema",1,"address",a,"original_elf_sha256",module);
                String status = "missing_function";
                if (fn != null) {
                    data = exportFunction(fn, decompiler, decompilerReady);
                    status = "exported";
                } else data.put("error", "No function at this exact entry; review analysis boundaries");
                String filename = a.substring(2) + ".json";
                Files.writeString(temp.resolve(filename), json(data) + "\n", StandardCharsets.UTF_8);
                entries.add(object("address",a,"json",filename,"status",status));
            }
            Map<String,Object> manifest = object("schema",1,"original_elf_sha256",module,
                "ghidra_version",Application.getApplicationVersion(),"program",currentProgram.getName(),
                "language",currentProgram.getLanguageID().toString(),"image_base",addr(currentProgram.getImageBase()),
                "functions",entries,"game_executed",false,"program_modified_by_script",false,
                "warning","Static analysis export, not equivalence. SHA-256 is imported program metadata; instruction bytes are recorded separately. Unknown indirect targets remain unknown.");
            Files.writeString(temp.resolve("manifest.json"), json(manifest) + "\n", StandardCharsets.UTF_8);
            Files.move(temp, output);
            println("Code-first export written: " + output);
        } finally {
            decompiler.dispose();
            // On interruption leave the uniquely named staging directory for
            // diagnosis; no final manifest path is published as a success.
        }
    }

    private Map<String,Object> exportFunction(Function fn, DecompInterface dc, boolean ready) throws Exception {
        String a = addr(fn.getEntryPoint());
        Map<String,Object> result = object("schema",1,"address",a,"original_elf_sha256",module,
            "symbol",fn.getName(true),"signature",fn.getSignature().toString(),"is_thunk",fn.isThunk(),
            "body_ranges",ranges(fn.getBody()),"body_size",fn.getBody().getNumAddresses());
        List<Object> instructions = new ArrayList<>(), calls = new ArrayList<>(), incoming = new ArrayList<>();
        MessageDigest hash = MessageDigest.getInstance("SHA-256");
        InstructionIterator iter = currentProgram.getListing().getInstructions(fn.getBody(), true);
        while (iter.hasNext()) {
            monitor.checkCancelled();
            Instruction ins = iter.next();
            byte[] bytes = ins.getBytes();
            hash.update(addr(ins.getAddress()).getBytes(StandardCharsets.UTF_8)); hash.update(bytes);
            List<Object> refs = new ArrayList<>(), pc = new ArrayList<>(), flows = new ArrayList<>(), operands = new ArrayList<>();
            for (int i=0; i<ins.getNumOperands(); i++) operands.add(ins.getDefaultOperandRepresentation(i));
            Address[] flowAddresses = ins.getFlows();
            if (flowAddresses != null) for (Address f : flowAddresses) flows.add(addr(f));
            for (Reference ref : ins.getReferencesFrom()) {
                Address to = ref.getToAddress();
                Map<String,Object> r = object("to",addr(to),"type",ref.getReferenceType().toString(),"source",ref.getSource().toString());
                Data data = to != null && to.isMemoryAddress() ? currentProgram.getListing().getDataAt(to) : null;
                if (data != null && data.getValue() instanceof String) r.put("string_value",data.getValue());
                refs.add(r);
            }
            for (PcodeOp op : ins.getPcode()) pc.add(op.toString());
            Map<String,Object> row = object("address",addr(ins.getAddress()),"bytes",hex(bytes),"text",ins.toString(),
                "mnemonic",ins.getMnemonicString(),"operands",operands,"flow_type",ins.getFlowType().toString(),
                "is_call",ins.getFlowType().isCall(),"is_jump",ins.getFlowType().isJump(),
                "is_computed",ins.getFlowType().isComputed(),"is_conditional",ins.getFlowType().isConditional(),
                "is_terminal",ins.getFlowType().isTerminal(),"fallthrough",addr(ins.getFallThrough()),
                "flows",flows,"references",refs,"pcode_navigation_only",pc);
            instructions.add(row);
            if (ins.getFlowType().isCall()) {
                List<Object> targets = new ArrayList<>();
                for (Reference ref : ins.getReferencesFrom()) if (ref.getReferenceType().isCall()) {
                    Address target = ref.getToAddress();
                    Function callee = currentProgram.getFunctionManager().getFunctionAt(target);
                    targets.add(object("address",addr(target),"symbol",callee == null ? null : callee.getName(true)));
                }
                calls.add(object("caller_address",a,"callsite_address",addr(ins.getAddress()),
                    "kind","call","computed",ins.getFlowType().isComputed(),"conditional",ins.getFlowType().isConditional(),
                    "targets",targets,"resolution",targets.isEmpty() ? "unresolved" : ins.getFlowType().isComputed() ? "analysis_candidates" : "direct_reference",
                    "warning","static address order, not runtime order; multiple candidates are not sequential calls"));
            }
        }
        result.put("instructions", instructions); result.put("callsites", calls);
        result.put("address_and_instruction_bytes_sha256",hex(hash.digest()));
        BasicBlockModel model = new BasicBlockModel(currentProgram);
        CodeBlockIterator blocks = model.getCodeBlocksContaining(fn.getBody(), monitor);
        List<Object> blockRows = new ArrayList<>();
        while (blocks.hasNext()) {
            monitor.checkCancelled();
            CodeBlock block = blocks.next();
            List<Object> destinations = new ArrayList<>();
            CodeBlockReferenceIterator dest = block.getDestinations(monitor);
            while (dest.hasNext()) {
                CodeBlockReference r = dest.next();
                destinations.add(object("source_site",addr(r.getReferent()),"destination_site",addr(r.getReference()),
                    "destination_block",addr(r.getDestinationAddress()),"flow_type",r.getFlowType().toString()));
            }
            blockRows.add(object("entry",addr(block.getFirstStartAddress()),"ranges",ranges(block),"destinations",destinations));
        }
        result.put("basic_blocks",blockRows);
        ReferenceIterator ri = currentProgram.getReferenceManager().getReferencesTo(fn.getEntryPoint());
        while (ri.hasNext()) {
            monitor.checkCancelled();
            Reference ref = ri.next();
            Function owner = currentProgram.getFunctionManager().getFunctionContaining(ref.getFromAddress());
            incoming.add(object("from",addr(ref.getFromAddress()),"type",ref.getReferenceType().toString(),
                "owner",owner == null ? null : addr(owner.getEntryPoint()),"source",ref.getSource().toString()));
        }
        result.put("incoming_entry_references_including_data",incoming);
        if (ready) {
            DecompileResults r = dc.decompileFunction(fn, 120, monitor);
            if (r.decompileCompleted() && r.getDecompiledFunction() != null) {
                String c = r.getDecompiledFunction().getC();
                result.put("decompiler",object("status","completed","c",c,
                    "sha256",hex(MessageDigest.getInstance("SHA-256").digest(c.getBytes(StandardCharsets.UTF_8))),
                    "diagnostic",r.getErrorMessage()));
            } else result.put("decompiler",object("status","not_completed","diagnostic",r.getErrorMessage()));
        } else result.put("decompiler",object("status","unavailable","diagnostic",dc.getLastMessage()));
        return result;
    }

    private static List<Object> ranges(AddressSetView set) {
        List<Object> out = new ArrayList<>();
        AddressRangeIterator it = set.getAddressRanges();
        while (it.hasNext()) { AddressRange r=it.next(); out.add(object("start",addr(r.getMinAddress()),"end_inclusive",addr(r.getMaxAddress()))); }
        return out;
    }
    private static String addr(Address a) {
        if (a == null || a.equals(Address.NO_ADDRESS)) return null;
        if (!a.isMemoryAddress()) return a.toString();
        return String.format("0x%08x",a.getOffset());
    }
    private static String hex(byte[] data) { StringBuilder b=new StringBuilder(); for(byte v:data)b.append(String.format("%02x",v&255)); return b.toString(); }
    private static Map<String,Object> object(Object... items) {
        Map<String,Object> map=new LinkedHashMap<>(); for(int i=0;i<items.length;i+=2)map.put((String)items[i],items[i+1]); return map;
    }
    private static String json(Object value) {
        if(value==null)return "null";
        if(value instanceof Boolean || value instanceof Number)return value.toString();
        if(value instanceof Map<?,?>) { List<String> p=new ArrayList<>(); for(Map.Entry<?,?> e:((Map<?,?>)value).entrySet())p.add(json(e.getKey().toString())+":"+json(e.getValue())); return "{"+String.join(",",p)+"}"; }
        if(value instanceof Iterable<?>) { List<String> p=new ArrayList<>(); for(Object e:(Iterable<?>)value)p.add(json(e)); return "["+String.join(",",p)+"]"; }
        StringBuilder b=new StringBuilder("\"");
        for(char c:value.toString().toCharArray()) {
            if(c=='"'||c=='\\')b.append('\\').append(c);
            else if(c<' ')b.append(String.format("\\u%04x",(int)c)); else b.append(c);
        }
        return b.append('"').toString();
    }
}
