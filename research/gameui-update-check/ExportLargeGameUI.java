// Targeted read-only export; no game execution and no production changes.
import java.nio.file.Files;
import java.nio.file.Path;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;

public class ExportLargeGameUI extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1) throw new IllegalArgumentException("Expected output directory");
        Path output = Path.of(args[0]);
        Files.createDirectories(output);
        Function fn = getFunctionAt(toAddr(0xab8100));
        if (fn == null) throw new IllegalStateException("No exact function at 0xab8100");
        DecompInterface dc = new DecompInterface();
        try {
            dc.toggleCCode(true);
            dc.toggleSyntaxTree(false);
            DecompileOptions options = new DecompileOptions();
            options.setMaxPayloadMBytes(128);
            dc.setOptions(options);
            if (!dc.openProgram(currentProgram)) throw new IllegalStateException(dc.getLastMessage());
            println("Exporting " + fn.getName(true) + " with 600-second decompile timeout");
            DecompileResults result = dc.decompileFunction(fn, 600, monitor);
            if (!result.decompileCompleted()) {
                Files.writeString(output.resolve("updateIngameUI.error.txt"), result.getErrorMessage());
                throw new IllegalStateException(result.getErrorMessage());
            }
            Files.writeString(output.resolve("updateIngameUI.c"),
                "/* Navigation draft only. Verify against original ASM. Address 0xab8100. */\n" +
                result.getDecompiledFunction().getC());
            Files.deleteIfExists(output.resolve("updateIngameUI.error.txt"));
            println("Target export complete");
        } finally { dc.dispose(); }
    }
}
