// Bounded BSim/FID experiment, not a semantic-equivalence or completion gate.
// Args: expected-sha256 targets.tsv|- new-output.json [candidate.json candidate-sha256]
// '-' selects all non-external, non-thunk functions of a SMALL candidate library (max 1000).
// The TSV selects 1..64 exact original entries. Names are output labels, never score inputs.
// @category OpenTorchlight
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.security.MessageDigest;
import java.util.*;
import com.google.gson.*;
import generic.jar.ResourceFile;
import generic.lsh.vector.*;
import ghidra.app.decompiler.*;
import ghidra.app.decompiler.signature.SignatureResult;
import ghidra.app.script.GhidraScript;
import ghidra.feature.fid.hash.FidHashQuad;
import ghidra.feature.fid.service.FidService;
import ghidra.features.bsim.query.GenSignatures;
import ghidra.framework.Application;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.util.xml.SpecXmlUtils;
import ghidra.xml.NonThreadedXmlPullParserImpl;
import ghidra.xml.XmlPullParser;

public class LibraryMatchPilot extends GhidraScript {
    private final Gson gson = new GsonBuilder().setPrettyPrinting().serializeNulls().create();
    private final LSHVectorFactory vectors = new WeightedLSHCosineVectorFactory();
    private final FidService fid = new FidService();

    @Override protected void run() throws Exception {
        long start = System.nanoTime();
        String[] args = getScriptArgs();
        if (args.length != 3 && args.length != 5)
            throw new IllegalArgumentException("expected-sha targets.tsv|- new-output.json [candidate.json candidate-sha]");
        if (!args[0].matches("[0-9a-f]{64}") || !args[0].equals(currentProgram.getExecutableSHA256()))
            throw new IllegalArgumentException("Loaded program SHA-256 differs from expected input");
        Path output = Paths.get(args[2]).toAbsolutePath();
        if (Files.exists(output, LinkOption.NOFOLLOW_LINKS)) throw new IOException("Output exists: " + output);
        ResourceFile weights = GenSignatures.getWeightsFile(currentProgram.getLanguageID(), currentProgram.getLanguageID());
        byte[] weightBytes;
        try (InputStream in = weights.getInputStream()) { weightBytes = in.readAllBytes(); }
        XmlPullParser parser = new NonThreadedXmlPullParserImpl(new ByteArrayInputStream(weightBytes),
            "BSim weights", SpecXmlUtils.getXmlHandler(), false);
        vectors.readWeights(parser);
        Map<String,Object> report = obj("schema",1,"elf_sha256",args[0],
            "ghidra_version",Application.getApplicationVersion(),"language",currentProgram.getLanguageID().toString(),
            "compiler_spec",currentProgram.getCompilerSpec().getCompilerSpecID().toString(),
            "weights_sha256",sha(weightBytes),"signature_settings",vectors.getSettings(),
            "method","BSim direct weighted-vector comparison; FID hash comparison, no contextual analyzer",
            "signature_timeout_seconds",30,"game_executed",false,"program_modified_by_script",false);
        List<Function> functions = new ArrayList<>();
        if (args[1].equals("-")) {
            FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
            while (it.hasNext()) {
                Function f = it.next();
                if (!f.isExternal() && !f.isThunk()) functions.add(f);
                if (functions.size() > 1000) throw new IllegalArgumentException("Candidate exceeds 1000 functions");
            }
            if (functions.isEmpty()) throw new IllegalArgumentException("Empty candidate library");
            report.put("selection", "all non-external non-thunk functions, including ELF boilerplate");
        } else {
            byte[] selection = Files.readAllBytes(Paths.get(args[1]));
            report.put("targets_sha256",sha(selection));
            Set<Address> seen = new HashSet<>();
            for (String raw : new String(selection, StandardCharsets.UTF_8).split("\\R")) {
                if (raw.isBlank() || raw.startsWith("#") || raw.startsWith("address\t")) continue;
                String address = raw.split("\t", -1)[0];
                if (!address.matches("0x[0-9a-fA-F]{1,16}")) throw new IllegalArgumentException("Invalid entry: " + raw);
                Address a = toAddr(address);
                Function f = getFunctionAt(a);
                if (f == null || f.isExternal() || f.isThunk() || !seen.add(a))
                    throw new IllegalArgumentException("Missing/duplicate/non-body entry: " + address);
                functions.add(f);
            }
            if (functions.isEmpty() || functions.size() > 64) throw new IllegalArgumentException("Select 1..64 exact entries");
        }
        JsonObject candidates = null;
        List<LSHVector> candidateVectors = new ArrayList<>();
        if (args.length == 5) {
            byte[] bytes = Files.readAllBytes(Paths.get(args[3]));
            candidates = JsonParser.parseString(new String(bytes, StandardCharsets.UTF_8)).getAsJsonObject();
            if (!args[4].matches("[0-9a-f]{64}") || !args[4].equals(candidates.get("elf_sha256").getAsString()))
                throw new IllegalArgumentException("Candidate ELF identity mismatch");
            for (String key : List.of("schema","ghidra_version","language","compiler_spec","weights_sha256","signature_settings"))
                if (!gson.toJsonTree(report.get(key)).equals(candidates.get(key)))
                    throw new IllegalArgumentException("Incompatible candidate settings: " + key);
            for (JsonElement e : candidates.getAsJsonArray("functions")) {
                JsonObject c = e.getAsJsonObject();
                candidateVectors.add(c.get("bsim_status").getAsString().equals("ok")
                    ? vectors.buildVector(gson.fromJson(c.get("features"),int[].class)) : null);
            }
            report.put("candidate_export_sha256",sha(bytes));
            report.put("candidate_elf_sha256",args[4]);
            report.put("candidate_count",candidateVectors.size());
        }
        DecompInterface dc = new DecompInterface();
        List<Object> rows = new ArrayList<>();
        try {
            dc.setOptions(new DecompileOptions()); dc.toggleSyntaxTree(false);
            dc.setSignatureSettings(vectors.getSettings());
            if (!dc.openProgram(currentProgram)) throw new IOException(dc.getLastMessage());
            for (Function f : functions) {
                monitor.checkCancelled();
                Map<String,Object> row = obj("address",address(f),"name",f.getName(),"qualified_name",f.getName(true),
                    "body_bytes",f.getBody().getNumAddresses(),"fid",fingerprint(f));
                SignatureResult signature = dc.generateSignatures(f, false, 30, monitor);
                LSHVector vector = null;
                String status = signature == null ? "unavailable" : signature.hasbaddata || signature.hasunimplemented
                    ? "incomplete_instructions" : signature.features.length == 0 ? "empty" : "ok";
                row.put("bsim_status",status);
                row.put("diagnostic",dc.getLastMessage());
                if (signature != null) {
                    row.put("has_bad_data",signature.hasbaddata);
                    row.put("has_unimplemented",signature.hasunimplemented);
                    row.put("features",signature.features);
                }
                if (status.equals("ok")) {
                    vector = vectors.buildVector(signature.features);
                    row.put("self_significance",vectors.getSelfSignificance(vector));
                }
                if (candidates != null) {
                    List<Map<String,Object>> scores = new ArrayList<>();
                    List<Object> fullMatches = new ArrayList<>(), specificMatches = new ArrayList<>();
                    JsonObject queryFid = gson.toJsonTree(row.get("fid")).isJsonNull() ? null
                        : gson.toJsonTree(row.get("fid")).getAsJsonObject();
                    JsonArray pool = candidates.getAsJsonArray("functions");
                    for (int i=0; i<pool.size(); i++) {
                        JsonObject c = pool.get(i).getAsJsonObject();
                        Map<String,Object> label = obj("address",c.get("address").getAsString(),"name",c.get("name").getAsString());
                        if (queryFid != null && !c.get("fid").isJsonNull()) {
                            JsonObject cf = c.getAsJsonObject("fid");
                            if (queryFid.get("full_hash").equals(cf.get("full_hash")) && queryFid.get("code_units").equals(cf.get("code_units"))) {
                                fullMatches.add(label);
                                if (queryFid.equals(cf)) specificMatches.add(label);
                            }
                        }
                        if (vector == null || candidateVectors.get(i) == null) continue;
                        VectorCompare cmp = new VectorCompare();
                        double sim = vector.compare(candidateVectors.get(i),cmp);
                        double signif = vectors.calculateSignificance(cmp);
                        if (!Double.isFinite(sim) || !Double.isFinite(signif)) throw new IOException("Non-finite BSim comparison");
                        Map<String,Object> score = new LinkedHashMap<>(label);
                        score.put("similarity",sim); score.put("significance",signif); scores.add(score);
                    }
                    scores.sort(Comparator.<Map<String,Object>>comparingDouble(s -> (double)s.get("similarity")).reversed()
                        .thenComparing(s -> (String)s.get("address")));
                    row.put("scores",scores); row.put("fid_full_matches",fullMatches); row.put("fid_specific_matches",specificMatches);
                }
                rows.add(row);
            }
        } finally { dc.closeProgram(); dc.dispose(); }
        report.put("functions",rows);
        report.put("script_elapsed_seconds",(System.nanoTime()-start)/1e9);
        report.put("warning","Similarity and hash matches are discovery evidence, not source-version identification or semantic equivalence. Symbols label results; existing types may affect decompilation. Static analysis coverage remains bounded.");
        Files.createDirectories(output.getParent());
        Files.writeString(output,gson.toJson(report)+"\n",StandardCharsets.UTF_8,StandardOpenOption.CREATE_NEW);
        println("Library match pilot written: " + output);
    }
    private Map<String,Object> fingerprint(Function f) throws Exception {
        FidHashQuad h = fid.hashFunction(f);
        return h == null ? null : obj("code_units",Short.toUnsignedInt(h.getCodeUnitSize()),
            "full_hash",String.format("%016x",h.getFullHash()),
            "specific_additional_size",Byte.toUnsignedInt(h.getSpecificHashAdditionalSize()),
            "specific_hash",String.format("%016x",h.getSpecificHash()));
    }
    private static String address(Function f) { return String.format("0x%08x",f.getEntryPoint().getOffset()); }
    private static String sha(byte[] bytes) throws Exception { return HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(bytes)); }
    private static Map<String,Object> obj(Object... pairs) {
        Map<String,Object> m = new LinkedHashMap<>();
        for (int i=0;i<pairs.length;i+=2) m.put((String)pairs[i],pairs[i+1]);
        return m;
    }
}
