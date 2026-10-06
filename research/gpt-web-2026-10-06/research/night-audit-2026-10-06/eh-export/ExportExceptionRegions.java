import ghidra.app.script.GhidraScript;
import ghidra.app.plugin.exceptionhandlers.gcc.RegionDescriptor;
import ghidra.app.plugin.exceptionhandlers.gcc.sections.EhFrameSection;
import ghidra.app.plugin.exceptionhandlers.gcc.structures.gccexcepttable.*;
import ghidra.program.model.address.*;
import com.google.gson.*;
import java.nio.file.*;
import java.util.*;

public class ExportExceptionRegions extends GhidraScript {
 protected void run() throws Exception {
  Set<Long> targets=new HashSet<>(Arrays.asList(0xa980e0L,0xba26b0L,0xb6ab50L,0xbf7cc0L,0xab8100L));
  List<RegionDescriptor> regions=new EhFrameSection(monitor,currentProgram).analyze(0);
  JsonArray selected=new JsonArray(), inventory=new JsonArray(); int withTables=0;
  for(RegionDescriptor r:regions){
   if(r.getLSDATable()!=null){withTables++; JsonObject e=new JsonObject();e.addProperty("function",r.getRangeStart().toString());e.addProperty("size",r.getRangeSize());e.addProperty("lsda",String.valueOf(r.getLSDAAddress(null)));inventory.add(e);}
   if(!targets.contains(r.getRangeStart().getOffset()))continue;
   JsonObject row=new JsonObject(); row.addProperty("function",r.getRangeStart().toString());row.addProperty("size",r.getRangeSize());
   row.addProperty("lsda",String.valueOf(r.getLSDAAddress(null)));
   JsonArray calls=new JsonArray(),actions=new JsonArray();
   if(r.getCallSiteTable()!=null)for(LSDACallSiteRecord c:r.getCallSiteTable().getCallSiteRecords()){
    JsonObject x=new JsonObject(); x.addProperty("start",c.getCallSite().getMinAddress().toString());x.addProperty("end_inclusive",c.getCallSite().getMaxAddress().toString());x.addProperty("landing",c.getLandingPadOffset()==0?null:String.valueOf(c.getLandingPad()));x.addProperty("landing_offset",c.getLandingPadOffset());x.addProperty("action_offset",c.getActionOffset());calls.add(x);
   }
   if(r.getActionTable()!=null)for(LSDAActionRecord a:r.getActionTable().getActionRecords()){
    JsonObject x=new JsonObject();x.addProperty("address",a.getAddress().toString());x.addProperty("filter",a.getActionTypeFilter());x.addProperty("next",String.valueOf(a.getNextActionAddress()));
    if(a.getActionTypeFilter()>0&&r.getTypeTable()!=null){
     Address ti=r.getTypeTable().getTypeInfoAddress(a.getActionTypeFilter());x.addProperty("type_info",String.valueOf(ti));
     if(ti!=null && !ti.equals(Address.NO_ADDRESS) && ti.getOffset()!=0){var syms=currentProgram.getSymbolTable().getSymbols(ti);JsonArray ns=new JsonArray();for(var sym:syms)ns.add(sym.getName(true));x.add("type_names",ns);}
    }
    actions.add(x);
   }
   row.add("callsites",calls);row.add("actions",actions);selected.add(row);
  }
  JsonObject out=new JsonObject();out.addProperty("regions",regions.size());out.addProperty("regions_with_lsda",withTables);out.add("selected",selected);out.add("lsda_inventory",inventory);
  Files.writeString(Paths.get(getScriptArgs()[0]),new GsonBuilder().setPrettyPrinting().create().toJson(out));
  println("EXPORTED selected="+selected.size()+" regions="+regions.size()+" lsda="+withTables);
 }
}
