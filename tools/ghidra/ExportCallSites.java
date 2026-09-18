// Ghidra headless post-script. Emits one row per call site, preserving
// multiplicity and order: caller -> callsite address -> callee.
// The existing ExportCallGraph.java emits only the set of called functions
// sorted by entry point, so sequences A->B->A and B->A look identical.
// This exporter keeps every instruction address that performs the call,
// which is the minimum needed for a code-first transfer (who calls what,
// from where, how many times, in which order). Branch conditions and
// virtual-table targets are NOT resolved here; they are recovered per
// function from disassembly/decompilation in the function package.
import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;

public class ExportCallSites extends GhidraScript {
    private static class Row {
        String caller;
        String callerName;
        String callsite;
        String callee;
        String calleeName;
        String mnemonic;
    }

    @Override
    protected void run() throws Exception {
        String[] arguments = getScriptArgs();
        if (arguments.length != 1) {
            throw new IllegalArgumentException("Expected output TSV path");
        }
        Path outputPath = Paths.get(arguments[0]);
        Path temporaryPath = Paths.get(arguments[0] + ".tmp");
        Files.createDirectories(outputPath.getParent());

        List<Row> rows = new ArrayList<>();
        FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
        while (functions.hasNext()) {
            Function caller = functions.next();
            InstructionIterator instructions =
                currentProgram.getListing().getInstructions(caller.getBody(), true);
            while (instructions.hasNext()) {
                Instruction instruction = instructions.next();
                if (!instruction.getFlowType().isCall()) {
                    continue;
                }
                Reference[] references = currentProgram.getReferenceManager()
                    .getReferencesFrom(instruction.getAddress());
                for (Reference reference : references) {
                    if (!reference.getReferenceType().isCall()) {
                        continue;
                    }
                    Address target = reference.getToAddress();
                    Function callee =
                        currentProgram.getFunctionManager().getFunctionAt(target);
                    String calleeAddress;
                    String calleeName;
                    if (callee != null) {
                        calleeAddress = callee.getEntryPoint().toString();
                        calleeName = clean(callee.getName(true));
                    } else {
                        calleeAddress = target.toString();
                        calleeName = clean(resolveSymbol(target));
                    }
                    Row row = new Row();
                    row.caller = caller.getEntryPoint().toString();
                    row.callerName = clean(caller.getName(true));
                    row.callsite = instruction.getAddress().toString();
                    row.callee = calleeAddress;
                    row.calleeName = calleeName;
                    row.mnemonic = clean(instruction.getMnemonicString());
                    rows.add(row);
                }
            }
            if ((rows.size() % 20000) == 0) {
                monitor.checkCanceled();
            }
        }
        rows.sort(Comparator.comparing((Row r) -> r.caller)
            .thenComparing(r -> r.callsite).thenComparing(r -> r.callee));

        int functionCount = currentProgram.getFunctionManager().getFunctionCount();
        try (BufferedWriter writer = Files.newBufferedWriter(
                 temporaryPath, StandardCharsets.UTF_8)) {
            writer.write("caller_address\tcaller_symbol\tcallsite_address\t"
                + "callee_address\tcallee_symbol\tmnemonic\n");
            for (Row row : rows) {
                writer.write(row.caller);
                writer.write('\t');
                writer.write(row.callerName);
                writer.write('\t');
                writer.write(row.callsite);
                writer.write('\t');
                writer.write(row.callee);
                writer.write('\t');
                writer.write(row.calleeName);
                writer.write('\t');
                writer.write(row.mnemonic);
                writer.write('\n');
            }
        }
        Files.move(temporaryPath, outputPath, StandardCopyOption.REPLACE_EXISTING);
        println("Call sites complete: " + functionCount + " functions, "
            + rows.size() + " call-site edges");
    }

    private String resolveSymbol(Address address) {
        SymbolTable symbols = currentProgram.getSymbolTable();
        Symbol primary = symbols.getPrimarySymbol(address);
        if (primary != null) {
            return primary.getName(true);
        }
        return "<unresolved:" + address.toString() + ">";
    }

    private static String clean(String value) {
        return value.replace('\t', ' ').replace('\n', ' ').replace('\r', ' ');
    }
}
