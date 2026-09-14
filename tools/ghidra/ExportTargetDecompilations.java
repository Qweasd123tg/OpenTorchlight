// Ghidra headless post-script. Targets use: hexadecimal-address output-name.
// The full Ghidra database remains outside the repository; only reviewed
// conclusions belong under research/.
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;

public class ExportTargetDecompilations extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] arguments = getScriptArgs();
        if (arguments.length != 2) {
            throw new IllegalArgumentException(
                "Expected target-list path and output-directory path");
        }
        Path targetList = Paths.get(arguments[0]);
        Path outputDirectory = Paths.get(arguments[1]);
        Files.createDirectories(outputDirectory);

        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true);
        decompiler.toggleSyntaxTree(true);
        if (!decompiler.openProgram(currentProgram)) {
            throw new IllegalStateException(decompiler.getLastMessage());
        }
        try {
            List<String> lines = Files.readAllLines(targetList, StandardCharsets.UTF_8);
            for (String rawLine : lines) {
                String line = rawLine.trim();
                if (line.isEmpty() || line.startsWith("#")) {
                    continue;
                }
                String[] fields = line.split("\\s+", 2);
                if (fields.length != 2 || !fields[1].matches("[a-z0-9_]+")) {
                    throw new IllegalArgumentException("Invalid target line: " + rawLine);
                }
                Address address = currentProgram.getAddressFactory()
                    .getDefaultAddressSpace().getAddress(fields[0]);
                Path codePath = outputDirectory.resolve(fields[1] + ".c");
                Path errorPath = outputDirectory.resolve(fields[1] + ".error.txt");
                Files.deleteIfExists(codePath);
                Files.deleteIfExists(errorPath);
                Function function = getFunctionAt(address);
                if (function == null) {
                    function = getFunctionContaining(address);
                }
                if (function == null) {
                    String message = "No function at " + fields[0];
                    Files.writeString(errorPath, message + "\n", StandardCharsets.UTF_8);
                    printerr(message);
                    continue;
                }
                DecompileResults result =
                    decompiler.decompileFunction(function, 120, monitor);
                if (!result.decompileCompleted()) {
                    String message = "address=" + function.getEntryPoint() + "\n" +
                        "symbol=" + function.getName(true) + "\n" +
                        "error=" + result.getErrorMessage() + "\n";
                    Files.writeString(errorPath, message, StandardCharsets.UTF_8);
                    printerr("Cannot decompile " + function.getName(true) + ": " +
                             result.getErrorMessage());
                    continue;
                }
                String header = "/* address=" + function.getEntryPoint() +
                    "\n   symbol=" + function.getName(true) + " */\n\n";
                String code = result.getDecompiledFunction().getC()
                    .replaceAll("[\\t ]+\\r?\\n", "\\n").stripTrailing();
                Files.writeString(codePath, header + code + "\n", StandardCharsets.UTF_8);
                println(fields[1] + " <- " + function.getName(true));
            }
        } finally {
            decompiler.dispose();
        }
    }
}
