// Ghidra headless post-script. Emits resolved function-to-function calls for
// the complete program as a deterministic, searchable TSV file.
import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Set;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

public class ExportCallGraph extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] arguments = getScriptArgs();
        if (arguments.length != 1) {
            throw new IllegalArgumentException("Expected output TSV path");
        }
        Path outputPath = Paths.get(arguments[0]);
        Path temporaryPath = Paths.get(arguments[0] + ".tmp");
        Files.createDirectories(outputPath.getParent());

        int functionCount = 0;
        int edgeCount = 0;
        try (BufferedWriter writer = Files.newBufferedWriter(
                 temporaryPath, StandardCharsets.UTF_8)) {
            writer.write("caller_address\tcaller_symbol\tcallee_address\tcallee_symbol\n");
            FunctionIterator functions =
                currentProgram.getFunctionManager().getFunctions(true);
            while (functions.hasNext()) {
                Function caller = functions.next();
                functionCount++;
                Set<Function> called = caller.getCalledFunctions(monitor);
                List<Function> callees = new ArrayList<>(called);
                callees.sort(Comparator.comparing(Function::getEntryPoint));
                for (Function callee : callees) {
                    writer.write(caller.getEntryPoint().toString());
                    writer.write('\t');
                    writer.write(clean(caller.getName(true)));
                    writer.write('\t');
                    writer.write(callee.getEntryPoint().toString());
                    writer.write('\t');
                    writer.write(clean(callee.getName(true)));
                    writer.write('\n');
                    edgeCount++;
                }
            }
        }
        Files.move(temporaryPath, outputPath, StandardCopyOption.REPLACE_EXISTING);
        println("Call graph complete: " + functionCount + " functions, " +
                edgeCount + " resolved edges");
    }

    private static String clean(String value) {
        return value.replace('\t', ' ').replace('\n', ' ').replace('\r', ' ');
    }
}
