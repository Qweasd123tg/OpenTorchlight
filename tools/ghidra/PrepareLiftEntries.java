// Explicit ELF symbol preparation in an owned analysis cache. Args: request.json result.json.
// Mutates listing/function bounds, never program bytes; no analysis, decompiler or ABI inference.
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.security.MessageDigest;
import java.util.*;
import com.google.gson.*;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;

public class PrepareLiftEntries extends GhidraScript {
    private static final Gson JSON = new GsonBuilder().setPrettyPrinting().create();
    private record Target(Address entry, int size, String sha, AddressSet span, Function existing) {}
    private String hash(byte[] bytes) throws Exception {
        return HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(bytes));
    }
    private String addr(Address address) {
        return String.format("0x%08x", address.getOffset());
    }
    private Map<String,Object> object(Object... values) {
        Map<String,Object> result = new LinkedHashMap<>();
        for (int i = 0; i < values.length; i += 2) result.put((String)values[i], values[i + 1]);
        return result;
    }
    private byte[] originalBytes(Address entry, int size, String sha) throws Exception {
        byte[] bytes = new byte[size];
        if (currentProgram.getMemory().getBytes(entry, bytes) != size || !hash(bytes).equals(sha))
            throw new IllegalStateException("Imported symbol bytes differ from pinned ELF at " + addr(entry));
        return bytes;
    }
    private boolean same(AddressSetView left, AddressSetView right) {
        return new AddressSet(left).subtract(right).isEmpty() && new AddressSet(right).subtract(left).isEmpty();
    }
    private void checkInstructions(Target target) throws Exception {
        Instruction at = currentProgram.getListing().getInstructionContaining(target.entry());
        if (at != null && !at.getMinAddress().equals(target.entry()))
            throw new IllegalStateException("Exact entry falls inside an existing instruction: " + addr(target.entry()));
        InstructionIterator instructions = currentProgram.getListing().getInstructions(target.span(), true);
        while (instructions.hasNext()) {
            Instruction ins = instructions.next();
            if (!target.span().contains(ins.getMinAddress(), ins.getMaxAddress()))
                throw new IllegalStateException("Decoded instruction crosses exact ELF symbol bound: " + addr(ins.getMinAddress()));
        }
    }
    @Override protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) throw new IllegalArgumentException("Expected request.json result.json");
        Path requestPath = Path.of(args[0]).toAbsolutePath(), output = Path.of(args[1]).toAbsolutePath();
        if (Files.exists(output, LinkOption.NOFOLLOW_LINKS))
            throw new IllegalArgumentException("Preparation result already exists");
        byte[] requestBytes = Files.readAllBytes(requestPath);
        JsonObject request = JsonParser.parseString(new String(requestBytes, StandardCharsets.UTF_8)).getAsJsonObject();
        String elf = request.get("original_elf_sha256").getAsString();
        if (request.get("schema").getAsInt() != 1 ||
                !request.get("kind").getAsString().equals("bounded-lift-preparation-request") ||
                !elf.equals("91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b") ||
                !elf.equalsIgnoreCase(currentProgram.getExecutableSHA256()) ||
                !request.get("ghidra_version").getAsString().equals(Application.getApplicationVersion()) ||
                !Application.getApplicationVersion().equals("12.1.3") ||
                !request.get("language").getAsString().equals(currentProgram.getLanguageID().toString()) ||
                !currentProgram.getLanguageID().toString().equals("x86:LE:64:default") ||
                !currentProgram.getCompilerSpec().getCompilerSpecID().toString().equals("gcc") ||
                !request.get("image_base").getAsString().equals("0x" + Long.toUnsignedString(currentProgram.getImageBase().getOffset(), 16)) ||
                request.get("analysis_requested").getAsBoolean() || request.get("decompiler_requested").getAsBoolean())
            throw new IllegalArgumentException("Preparation program/tool/request identity differs");
        JsonArray entries = request.getAsJsonArray("entries");
        if (entries.isEmpty() || entries.size() > 1024)
            throw new IllegalArgumentException("Select 1..1024 exact functions");
        FunctionManager manager = currentProgram.getFunctionManager();
        Listing listing = currentProgram.getListing();
        AddressSpace ram = currentProgram.getAddressFactory().getDefaultAddressSpace();
        List<Target> targets = new ArrayList<>();
        Set<Address> seen = new HashSet<>();
        long total = 0;
        // Validate the complete batch before any listing or body mutation.
        for (JsonElement element : entries) {
            monitor.checkCancelled();
            JsonObject row = element.getAsJsonObject();
            String rawAddress = row.get("address").getAsString();
            if (!rawAddress.matches("0x[0-9a-f]{8,16}"))
                throw new IllegalArgumentException("Malformed exact source address");
            Address entry = ram.getAddress(Long.parseUnsignedLong(rawAddress.substring(2), 16));
            int size = row.get("size").getAsInt();
            String sha = row.get("full_symbol_sha256").getAsString();
            if (!seen.add(entry) || size < 1 || size > 1 << 20 || !sha.matches("[0-9a-f]{64}"))
                throw new IllegalArgumentException("Duplicate target or invalid bounded symbol size/hash");
            total += size;
            if (total > 8 << 20) throw new IllegalArgumentException("Batch exceeds eight MiB of symbol bytes");
            AddressSet span = new AddressSet(entry, entry.addNoWrap(size - 1L));
            if (!currentProgram.getMemory().getLoadedAndInitializedAddressSet().contains(span))
                throw new IllegalArgumentException("Source span is not loaded initialized memory");
            originalBytes(entry, size, sha);
            for (Target prior : targets) if (prior.span().intersects(span))
                throw new IllegalArgumentException("Selected exact symbol ranges overlap");
            Iterator<Function> overlaps = manager.getFunctionsOverlapping(span);
            while (overlaps.hasNext()) {
                Function fn = overlaps.next();
                if (!fn.getEntryPoint().equals(entry))
                    throw new IllegalStateException("Source span overlaps a different existing function at " + addr(fn.getEntryPoint()));
            }
            Function existing = manager.getFunctionAt(entry);
            if (existing != null && !same(existing.getBody(), new AddressSet(entry)) && !same(existing.getBody(), span))
                throw new IllegalStateException("Existing exact function has unreviewed nonexact body: " + addr(entry));
            if (listing.getDefinedDataContaining(entry) != null || listing.getDefinedData(span, true).hasNext())
                throw new IllegalStateException("Source span conflicts with existing defined data: " + addr(entry));
            Target target = new Target(entry, size, sha, span, existing);
            checkInstructions(target);
            targets.add(target);
        }
        int transaction = currentProgram.startTransaction("Prepare explicit bounded raw-lift entries");
        boolean committed = false;
        List<Object> prepared = new ArrayList<>();
        try {
            for (Target target : targets) {
                monitor.checkCancelled();
                // This is a flow decoder within a pinned symbol span. Passing
                // the whole range as startSet would sweep padding/data as code.
                DisassembleCommand command = new DisassembleCommand(target.entry(), target.span(), true);
                command.enableCodeAnalysis(false);
                if (!command.applyTo(currentProgram, monitor) || listing.getInstructionAt(target.entry()) == null)
                    throw new IllegalStateException("Exact-entry disassembly failed: " + addr(target.entry()) + " " + command.getStatusMsg());
                checkInstructions(target);
                Function fn = target.existing();
                if (fn == null) fn = manager.createFunction(null, target.entry(), target.span(), SourceType.IMPORTED);
                else fn.setBody(target.span());
                if (fn == null || !same(fn.getBody(), target.span()))
                    throw new IllegalStateException("Exact ELF function bounds were not installed");
                originalBytes(target.entry(), target.size(), target.sha());
                int instructions = 0, bytes = 0;
                InstructionIterator iter = listing.getInstructions(target.span(), true);
                while (iter.hasNext()) {
                    Instruction ins = iter.next();
                    ++instructions;
                    bytes += ins.getLength();
                }
                prepared.add(object("address", addr(target.entry()), "size", target.size(),
                    "full_symbol_sha256", target.sha(), "instructions", instructions,
                    "instruction_bytes", bytes, "symbol_bytes_without_decoded_instruction", target.size() - bytes,
                    "previous_body", target.existing() == null ? "absent" : "accepted exact entry",
                    "boundary", "ELF symbol span bounds only; gaps remain unassessed; no function completion claim"));
            }
            committed = true;
        } finally {
            currentProgram.endTransaction(transaction, committed);
        }
        Map<String,Object> result = object("schema", 1, "kind", "bounded-lift-preparation-result",
            "status", "PREPARED", "request_sha256", hash(requestBytes), "original_elf_sha256", elf,
            "ghidra_version", Application.getApplicationVersion(), "language", currentProgram.getLanguageID().toString(),
            "entries", prepared, "analysis_requested", false, "decompiler_requested", false,
            "program_database_modified", true, "program_bytes_modified", false,
            "original_status_promotions", 0, "game_executed", false);
        Path staged = Files.createTempFile(output.getParent(), ".bounded-preparation-", ".json");
        Files.writeString(staged, JSON.toJson(result) + "\n", StandardCharsets.UTF_8);
        Files.move(staged, output, StandardCopyOption.ATOMIC_MOVE);
        println("Prepared exact ELF spans without full analysis: " + entries.size());
    }
}
