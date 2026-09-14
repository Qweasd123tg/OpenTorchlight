// Ghidra headless post-script. Exports selected game namespaces into one
// searchable C-like text file per class.
import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

public class ExportClassDecompilations extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] arguments = getScriptArgs();
        if (arguments.length != 2) {
            throw new IllegalArgumentException(
                "Expected class-list path and output-directory path");
        }
        Path classList = Paths.get(arguments[0]);
        Path outputDirectory = Paths.get(arguments[1]);
        Files.createDirectories(outputDirectory);

        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true);
        decompiler.toggleSyntaxTree(true);
        if (!decompiler.openProgram(currentProgram)) {
            throw new IllegalStateException(decompiler.getLastMessage());
        }

        int totalFunctions = 0;
        int totalFailures = 0;
        try {
            List<String> lines = Files.readAllLines(classList, StandardCharsets.UTF_8);
            for (String rawLine : lines) {
                String line = rawLine.trim();
                if (line.isEmpty() || line.startsWith("#")) {
                    continue;
                }
                String[] fields = line.split("\\s+");
                if (fields.length != 2 ||
                    !fields[0].matches("[A-Za-z_][A-Za-z0-9_]*") ||
                    !fields[1].matches("[a-z0-9_]+")) {
                    throw new IllegalArgumentException("Invalid class line: " + rawLine);
                }

                String namespace = fields[0];
                Path outputPath = outputDirectory.resolve(fields[1] + ".c");
                Path temporaryPath = outputDirectory.resolve(fields[1] + ".c.tmp");
                int functionCount = 0;
                int failureCount = 0;

                try (BufferedWriter writer = Files.newBufferedWriter(
                         temporaryPath, StandardCharsets.UTF_8)) {
                    writer.write("/* Targeted Ghidra class export.\n");
                    writer.write("   namespace=" + namespace + "\n");
                    writer.write("   Treat pseudocode as navigation evidence. */\n\n");

                    FunctionIterator functions =
                        currentProgram.getFunctionManager().getFunctions(true);
                    while (functions.hasNext()) {
                        Function function = functions.next();
                        String symbol = function.getName(true);
                        if (!symbol.startsWith(namespace + "::")) {
                            continue;
                        }
                        functionCount++;
                        writer.write("\n/* address=" + function.getEntryPoint() + "\n");
                        writer.write("   symbol=" + symbol + " */\n");
                        DecompileResults result =
                            decompiler.decompileFunction(function, 120, monitor);
                        if (result.decompileCompleted()) {
                            String code = result.getDecompiledFunction().getC()
                                .replaceAll("[\\t ]+\\r?\\n", "\\n").stripTrailing();
                            writer.write(code);
                            writer.write("\n");
                        } else {
                            failureCount++;
                            writer.write("/* DECOMPILATION FAILED: ");
                            writer.write(result.getErrorMessage().replace("*/", "* /"));
                            writer.write(" */\n");
                        }
                    }
                    writer.write("\n/* export-summary functions=" + functionCount +
                                 " failures=" + failureCount + " */\n");
                }
                Files.move(temporaryPath, outputPath,
                           java.nio.file.StandardCopyOption.REPLACE_EXISTING);
                totalFunctions += functionCount;
                totalFailures += failureCount;
                println(fields[1] + " <- " + namespace + " (" + functionCount +
                        " functions, " + failureCount + " failures)");
            }
        } finally {
            decompiler.dispose();
        }
        println("Core export complete: " + totalFunctions + " functions, " +
                totalFailures + " failures");
    }
}
