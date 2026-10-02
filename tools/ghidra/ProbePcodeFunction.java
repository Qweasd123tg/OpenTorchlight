// Executes bounded raw machine-code functions in Ghidra's pinned PcodeEmulator.
// Args: explicit-profile.json output.json expected-ELF-SHA256. Never runs a game,
// changes program bytes, guesses missing state, stubs calls or promotes transfer.
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;
import com.google.gson.*;
import ghidra.app.script.GhidraScript;
import ghidra.pcode.emu.*;
import ghidra.pcode.exec.*;
import ghidra.pcode.exec.PcodeExecutorStatePiece.Reason;
import ghidra.program.model.address.*;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.Function;
import ghidra.program.model.pcode.PcodeOp;

public class ProbePcodeFunction extends GhidraScript {
    private static final Gson JSON = new GsonBuilder().setPrettyPrinting().create();
    private AddressSpace ram;
    private List<Map<String,Object>> effects;
    private List<Region> regions;
    private record Region(String name,long base,int size,boolean writable) {
        boolean covers(long address,int length) {
            return length >= 0 && address >= base && address-base <= size-length;
        }
    }
    private long number(String value) { return Long.parseUnsignedLong(value.replaceFirst("^0x",""),16); }
    private long little(byte[] value) {
        long result = 0;for(int i=0;i<Math.min(8,value.length);i++)result|=(value[i]&255L)<<(8*i);return result;
    }
    private String hex(byte[] value) { return HexFormat.of().formatHex(value); }
    private Map<String,Object> object(Object... values) {
        Map<String,Object> result=new LinkedHashMap<>();for(int i=0;i<values.length;i+=2)result.put((String)values[i],values[i+1]);return result;
    }
    private void check(AddressSpace space,long address,int length,boolean write) {
        if (!space.equals(ram)) throw new IllegalStateException("UNSUPPORTED memory space: "+space);
        for(Region region:regions) if(region.covers(address,length)) {
            if(write&&!region.writable())throw new IllegalStateException("Write to read-only region: "+region.name());
            return;
        }
        throw new IllegalStateException("Unmapped "+(write?"write":"read")+" @0x"+Long.toUnsignedString(address,16)+" size="+length);
    }
    private PcodeEmulationCallbacks<byte[]> callbacks() {
        return new PcodeEmulationCallbacks<byte[]>() {
            @Override public void beforeLoad(PcodeThread<byte[]> thread,PcodeOp op,AddressSpace space,byte[] offset,int size) {
                check(space,little(offset),size,false);
            }
            @Override public void afterLoad(PcodeThread<byte[]> thread,PcodeOp op,AddressSpace space,byte[] offset,int size,byte[] value) {
                effects.add(object("kind","read","site",op.getSeqnum().getTarget().toString(),
                    "address","0x"+Long.toUnsignedString(little(offset),16),"size",size,"bytes_le",hex(value)));
            }
            @Override public void beforeStore(PcodeThread<byte[]> thread,PcodeOp op,AddressSpace space,byte[] offset,int size,byte[] value) {
                check(space,little(offset),size,true);
            }
            @Override public void afterStore(PcodeThread<byte[]> thread,PcodeOp op,AddressSpace space,byte[] offset,int size,byte[] value) {
                effects.add(object("kind","write","site",op.getSeqnum().getTarget().toString(),
                    "address","0x"+Long.toUnsignedString(little(offset),16),"size",size,"bytes_le",hex(value)));
            }
            @Override public <A,U> int readUninitialized(PcodeThread<byte[]> thread,PcodeExecutorStatePiece<A,U> piece,
                    AddressSpace space,A offset,int length,Reason reason) {
                throw new IllegalStateException("Uninitialized "+space+" read, size="+length+", reason="+reason);
            }
        };
    }
    @Override protected void run() throws Exception {
        String[] args=getScriptArgs();
        if(args.length!=3||!args[2].equalsIgnoreCase(currentProgram.getExecutableSHA256()))
            throw new IllegalArgumentException("Expected profile output and matching ELF SHA");
        JsonObject profile=JsonParser.parseString(Files.readString(Path.of(args[0]))).getAsJsonObject();
        if(profile.get("schema").getAsInt()!=1||!profile.get("original_elf_sha256").getAsString().equals(args[2])||
                !profile.get("language").getAsString().equals(currentProgram.getLanguageID().toString()))
            throw new IllegalArgumentException("Unsupported profile/schema/architecture");
        JsonArray cases=profile.getAsJsonArray("cases");
        if(cases.isEmpty()||cases.size()>2048)throw new IllegalArgumentException("Select 1..2048 bounded cases");
        ram=currentProgram.getAddressFactory().getDefaultAddressSpace();
        List<Object> results=new ArrayList<>();
        for(JsonElement element:cases) {
            monitor.checkCancelled();
            JsonObject test=element.getAsJsonObject();
            long entry=number(test.get("entry").getAsString()),stop=number(test.get("return_address").getAsString());
            Function fn=currentProgram.getFunctionManager().getFunctionAt(ram.getAddress(entry));
            if(fn==null)throw new IllegalArgumentException("No exact function entry");
            int limit=test.get("max_instructions").getAsInt();
            if(limit<1||limit>10000)throw new IllegalArgumentException("Invalid step budget");
            effects=new ArrayList<>();regions=new ArrayList<>();
            PcodeEmulator emulator=new PcodeEmulator(currentProgram.getLanguage(),callbacks());
            PcodeThread<byte[]> thread=emulator.newThread();
            // Decode padding is copied from the imported read-only program;
            // executable PCs remain limited to the original function's body.
            AddressRangeIterator body=fn.getBody().getAddressRanges();
            while(body.hasNext()) {
                AddressRange range=body.next();int size=Math.toIntExact(range.getLength())+32;
                if(size>1<<20)throw new IllegalArgumentException("Function range too large");
                byte[] raw=new byte[size];currentProgram.getMemory().getBytes(range.getMinAddress(),raw);
                long base=range.getMinAddress().getOffset();regions.add(new Region("original-code",base,size,false));
                emulator.getSharedState().setVar(ram,base,size,true,raw);
            }
            for(JsonElement item:test.getAsJsonArray("regions")) {
                JsonObject region=item.getAsJsonObject();byte[] bytes=HexFormat.of().parseHex(region.get("bytes_le").getAsString());
                if(bytes.length<1||bytes.length>1<<20)throw new IllegalArgumentException("Invalid region size");
                long base=number(region.get("address").getAsString());
                for(Region previous:regions) if(base<previous.base()+previous.size()&&previous.base()<base+bytes.length)
                    throw new IllegalArgumentException("Overlapping region");
                regions.add(new Region(region.get("name").getAsString(),base,bytes.length,region.get("writable").getAsBoolean()));
                emulator.getSharedState().setVar(ram,base,bytes.length,true,bytes);
            }
            for(Map.Entry<String,JsonElement> item:test.getAsJsonObject("registers").entrySet()) {
                Register register=currentProgram.getRegister(item.getKey());
                if(register==null)throw new IllegalArgumentException("Unknown register: "+item.getKey());
                byte[] bytes=HexFormat.of().parseHex(item.getValue().getAsString());
                if(bytes.length!=register.getMinimumByteSize())throw new IllegalArgumentException("Register width mismatch: "+item.getKey());
                thread.getState().setVar(register,bytes);
            }
            thread.overrideContextWithDefault();thread.reInitialize();
            List<String> pcs=new ArrayList<>();String status="COMPLETE",reason="";
            try {
                while(thread.getCounter().getOffset()!=stop) {
                    if(pcs.size()>=limit)throw new IllegalStateException("Instruction budget exhausted");
                    if(!fn.getBody().contains(thread.getCounter()))throw new IllegalStateException("External/computed target @"+thread.getCounter());
                    pcs.add(thread.getCounter().toString());thread.stepInstruction();
                }
            } catch(RuntimeException error) {status="UNKNOWN";reason=error.getMessage();}
            Map<String,Object> observations=new LinkedHashMap<>();
            if(status.equals("COMPLETE")) {
                for(JsonElement item:test.getAsJsonArray("observe_registers")) {
                    String name=item.getAsString();Register register=currentProgram.getRegister(name);
                    observations.put(name,hex(thread.getState().getVar(register,Reason.INSPECT)));
                }
                for(JsonElement item:test.getAsJsonArray("observe_regions")) {
                    JsonObject region=item.getAsJsonObject();long address=number(region.get("address").getAsString());
                    int size=region.get("size").getAsInt();check(ram,address,size,false);
                    observations.put(region.get("name").getAsString(),hex(emulator.getSharedState().getVar(ram,address,size,true,Reason.INSPECT)));
                }
            }
            results.add(object("id",test.get("id").getAsString(),"entry","0x"+Long.toUnsignedString(entry,16),
                "status",status,"reason",reason,"instruction_trace",pcs,"memory_effects",effects,"observations",observations));
        }
        Path output=Path.of(args[1]);if(Files.exists(output))throw new IllegalArgumentException("Output already exists");
        Files.writeString(output,JSON.toJson(object("schema",1,"kind","bounded-original-pcode-execution",
            "original_elf_sha256",args[2],"scope",profile.get("scope").getAsString(),"results",results,
            "game_executed",false,"original_status_promotions",0))+"\n",StandardCharsets.UTF_8);
        println("P-code execution collected "+results.size()+" explicit cases; unresolved state is UNKNOWN");
    }
}
