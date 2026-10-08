#!/usr/bin/env python3
"""Compile against installed pinned Ghidra, then execute real LP64 datatype checks."""
from pathlib import Path
import json
import shutil
import subprocess
import tempfile
import unittest

import ghidra_draft
import toolchain
import types_export


@unittest.skipUnless((ghidra_draft.GHIDRA_HOME / 'Ghidra').is_dir() and shutil.which('javac'),
                     'requires the installed Ghidra SDK and a JDK')
class GhidraJava(unittest.TestCase):
    def test_script_api_and_lp64_widths(self):
        cp = ':'.join(str(p) for p in ghidra_draft.GHIDRA_HOME.rglob('*.jar'))
        helper = r'''
import java.lang.reflect.*;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import ghidra.program.model.data.*;
import ghidra.program.model.data.Array;
public class WidthProbe {
 public static void main(String[] args) throws Exception {
  ghidra.framework.HeadlessGhidraApplicationConfiguration configuration=new ghidra.framework.HeadlessGhidraApplicationConfiguration();
  configuration.setInitializeLogging(false);
  ghidra.framework.Application.initializeApplication(new ghidra.GhidraApplicationLayout(new java.io.File(args[0])),configuration);
  ghidra.util.UniversalIdGenerator.initialize();
  DecompDrafts s=new DecompDrafts();
  Field classes=DecompDrafts.class.getDeclaredField("classes");
  classes.setAccessible(true); classes.set(s,new JsonObject());
  Method primitive=DecompDrafts.class.getDeclaredMethod("primitive",String.class,int.class);
  primitive.setAccessible(true);
  String[] names={"long int","long unsigned int","int","unsigned int"};
  int[] sizes={8,8,4,4};
  for(int i=0;i<names.length;i++)
   if(((DataType)primitive.invoke(s,names[i],0)).getLength()!=sizes[i])
    throw new AssertionError(names[i]);
  if(primitive.invoke(s,"long int",4)!=null) throw new AssertionError("conflicting long width");
  Method basic=DecompDrafts.class.getDeclaredMethod("basic",String.class,int.class);
  basic.setAccessible(true);
  DataType p=(DataType)basic.invoke(s,"long int*",8);
  if(((ghidra.program.model.data.Pointer)p).getDataType().getLength()!=8)
   throw new AssertionError("pointee long");
  DataType a=(DataType)basic.invoke(s,"long unsigned int[3]",24);
  if(a.getLength()!=24) throw new AssertionError("array long");
  Array matrixArray=(Array)basic.invoke(s,"float[3][4]",48);
  if(matrixArray.getNumElements()!=3 || ((Array)matrixArray.getDataType()).getNumElements()!=4 || matrixArray.getLength()!=48)
   throw new AssertionError("multidimensional array shape/width lost");
  if(basic.invoke(s,"float[][4]",0)!=null) throw new AssertionError("unknown extent guessed");
  if(basic.invoke(s,"Unknown*",8)!=null) throw new AssertionError("unknown pointee guessed");
  Method parts=DecompDrafts.class.getDeclaredMethod("qualifiedParts",String.class);
  parts.setAccessible(true);
  if(!parts.invoke(null,"Ogre::Vector3").toString().equals("[Ogre, Vector3]"))
   throw new AssertionError("qualified scopes flattened");
  if(!parts.invoke(null,"Ogre::Holder<CEGUI::Thing>").toString().equals("[Ogre, Holder<CEGUI::Thing>]"))
   throw new AssertionError("template argument namespace split as outer scope");
  Method prepare=DecompDrafts.class.getDeclaredMethod("prepareClass",String.class);
  prepare.setAccessible(true);
  String unsupported="typedef __va_list_tag __va_list_tag";
  if((Boolean)prepare.invoke(s,unsupported)) throw new AssertionError("invalid class imported");
  Field errors=DecompDrafts.class.getDeclaredField("typeErrors"); errors.setAccessible(true);
  if(!((java.util.Set<?>)errors.get(s)).contains(unsupported))
   throw new AssertionError("unsupported class not recorded");
  ((java.util.Set<String>)errors.get(s)).add("KnownPointee");
  StandAloneDataTypeManager manager=new StandAloneDataTypeManager("pointer-regression");
  int transaction=manager.startTransaction("opaque pointer");
  Field dataManager=DecompDrafts.class.getDeclaredField("dtm");dataManager.setAccessible(true);dataManager.set(s,manager);
  Field classMap=DecompDrafts.class.getDeclaredField("classes"); classMap.setAccessible(true);
  ((JsonObject)classMap.get(s)).add("KnownPointee",new JsonObject());
  Field structures=DecompDrafts.class.getDeclaredField("structs"); structures.setAccessible(true);
  ((java.util.Map<String,Structure>)structures.get(s)).put("KnownPointee",new StructureDataType("KnownPointee",8));
  DataType opaquePointer=(DataType)basic.invoke(s,"KnownPointee*",8);
  if(!(opaquePointer instanceof Pointer) || opaquePointer.getLength()!=8 ||
     !((Pointer)opaquePointer).getDataType().getName().startsWith("opaque_"))
   throw new AssertionError("known incomplete pointee lost pointer ABI or reused partial fields");
  try { basic.invoke(s,"KnownPointee",8); throw new AssertionError("by-value layout guessed"); }
  catch(InvocationTargetException expected) { }
  // Layouts below come from the pinned compiler, never from expected sizes.
  JsonObject layouts=JsonParser.parseString(java.nio.file.Files.readString(java.nio.file.Paths.get(args[1]))).getAsJsonObject();
  classMap.set(s,layouts);
  JsonObject identities=JsonParser.parseString(java.nio.file.Files.readString(java.nio.file.Paths.get(args[2]))).getAsJsonObject();
  Method importIdentities=DecompDrafts.class.getDeclaredMethod("importClassIdentities",JsonObject.class);importIdentities.setAccessible(true);
  importIdentities.invoke(s,identities);
  Field vtables=DecompDrafts.class.getDeclaredField("vtables");vtables.setAccessible(true);vtables.set(s,new JsonObject());
  java.util.Map<String,Structure> structs=(java.util.Map<String,Structure>)structures.get(s);
  structs.clear();
  // Plain class namespaces need a Program, templates deliberately don't.
  for(String name:layouts.keySet()) if(name.indexOf('<')<0)
   structs.put(name,new StructureDataType(name,0,manager));
  Method fill=DecompDrafts.class.getDeclaredMethod("fill",String.class);fill.setAccessible(true);
  fill.invoke(s,"Containers");
  Structure containers=structs.get("Containers");
  JsonObject owner=layouts.getAsJsonObject("Containers");
  if(containers.getLength()!=owner.get("size").getAsInt()) throw new AssertionError("owner size");
  Structure vector=(Structure)containers.getComponentAt(0).getDataType();
  if(!vector.getName().equals(owner.getAsJsonArray("fields").get(0).getAsJsonObject().get("type").getAsString()))
   throw new AssertionError("template identity rewritten");
  Structure impl=(Structure)vector.getComponentAt(0).getDataType();
  if(!impl.getComponentAt(0).getFieldName().equals("_M_start") ||
     !impl.getComponentAt(8).getFieldName().equals("_M_finish") ||
     !impl.getComponentAt(16).getFieldName().equals("_M_end_of_storage"))
   throw new AssertionError("vector storage wasn't recovered through its private/base structs");
  int mapOffset=owner.getAsJsonArray("fields").get(1).getAsJsonObject().get("offset").getAsInt();
  Structure map=(Structure)containers.getComponentAt(mapOffset).getDataType();
  Structure tree=(Structure)map.getComponentAt(0).getDataType();
  Structure treeImpl=(Structure)tree.getComponentAt(0).getDataType();
  Structure header=(Structure)treeImpl.getComponentAt(8).getDataType();
  if(!header.getComponentAt(0).getFieldName().equals("_M_color") ||
     !header.getComponentAt(8).getFieldName().equals("_M_parent") ||
     !header.getComponentAt(16).getFieldName().equals("_M_left") ||
     !header.getComponentAt(24).getFieldName().equals("_M_right") ||
     !treeImpl.getComponentAt(40).getFieldName().equals("_M_node_count"))
   throw new AssertionError("map storage wasn't recovered through its private/base structs");
  for(String name:new String[]{"CCollisionList","CSoundBankDataInformation","CDataGroup","Ogre::Matrix4"}) {
   fill.invoke(s,name);
   if(structs.get(name).getLength()!=layouts.getAsJsonObject(name).get("size").getAsInt())
    throw new AssertionError("actual recovered header layout " + name);
  }
  DataType matrixUnion=structs.get("Ogre::Matrix4").getComponentAt(0).getDataType();
  if(!(matrixUnion instanceof Union) || matrixUnion.getLength()!=64 || ((Union)matrixUnion).getNumComponents()!=2)
   throw new AssertionError("real Matrix4 anonymous union flattened or guessed");
  Union views=(Union)matrixUnion;
  Array rows=(Array)views.getComponent(0).getDataType();
  if(rows.getNumElements()!=4 || ((Array)rows.getDataType()).getNumElements()!=4)
   throw new AssertionError("real Matrix4 array dimensions lost");
  JsonObject repository=null;
  for(com.google.gson.JsonElement field:layouts.getAsJsonObject("CDataGroup").getAsJsonArray("fields"))
   if(field.getAsJsonObject().get("name").getAsString().equals("m_pRepository")) repository=field.getAsJsonObject();
  if(repository==null) throw new AssertionError("missing current CDataGroup repository field");
  String repositoryPointer=repository.get("ghidra_type").getAsString();
  String repositoryValue=repositoryPointer.substring(0,repositoryPointer.length()-1);
  if(layouts.has(repositoryValue)) throw new AssertionError("repository unexpectedly acquired a value layout");
  DataType repositoryType=structs.get("CDataGroup").getComponentAt(repository.get("offset").getAsInt()).getDataType();
  if(!(repositoryType instanceof Pointer) || repositoryType.getLength()!=8 ||
     !((Pointer)repositoryType).getDataType().getDescription().contains("Incomplete pointee: " + repositoryValue))
   throw new AssertionError("compiler-known forward declaration lost pointer identity");
  if(basic.invoke(s,repositoryValue,8)!=null) throw new AssertionError("forward declaration accepted by value");
  if(basic.invoke(s,"Unknown*",8)!=null) throw new AssertionError("unknown pointer accepted after importing identities");
  if(basic.invoke(s,"Ogre*",8)!=null) throw new AssertionError("namespace identity accepted as a class declaration");
  // Reverse fill order: a fresh importer must not depend on JSON key order.
  DecompDrafts reverse=new DecompDrafts();classMap.set(reverse,layouts);dataManager.set(reverse,manager);vtables.set(reverse,new JsonObject());
  importIdentities.invoke(reverse,identities);
  java.util.Map<String,Structure> reversed=(java.util.Map<String,Structure>)structures.get(reverse);
  for(String name:layouts.keySet()) reversed.put(name,new StructureDataType(name,0,manager));
  Field completed=DecompDrafts.class.getDeclaredField("filledClasses");completed.setAccessible(true);
  java.util.List<String> order=new java.util.ArrayList<>();
  for(String name:layouts.keySet()) if(((java.util.Set<?>)completed.get(s)).contains(name)) order.add(name);
  java.util.Collections.reverse(order);
  for(String name:order) fill.invoke(reverse,name);
  if(reversed.get("Containers").getLength()!=containers.getLength()) throw new AssertionError("order-dependent fill");
  int constPairs=0;
  for(String name:layouts.keySet()) {
   if(name.startsWith("std::pair<const ") && name.endsWith(">")) {
    // Leading cv stripping must not erase qualifiers inside template arguments.
    basic.invoke(s,name,layouts.getAsJsonObject(name).get("size").getAsInt());
    constPairs++;
   }
  }
  if(constPairs==0) throw new AssertionError("missing qualified template regression input");
  JsonObject missing=JsonParser.parseString("{\"size\":8,\"bases\":[],\"fields\":[{\"offset\":0,\"name\":\"value\",\"type\":\"Unknown\",\"size\":8}]}").getAsJsonObject();
  layouts.add("MissingValue",missing);structs.put("MissingValue",new StructureDataType("MissingValue",0,manager));
  try { fill.invoke(s,"MissingValue"); throw new AssertionError("unknown value layout guessed"); }
  catch(InvocationTargetException expected) { }
  JsonObject badBase=JsonParser.parseString("{\"size\":8,\"bases\":[{\"name\":\"Containers\",\"offset\":null}],\"fields\":[]}").getAsJsonObject();
  layouts.add("BadBase",badBase);structs.put("BadBase",new StructureDataType("BadBase",0,manager));
  try { fill.invoke(s,"BadBase"); throw new AssertionError("unknown base offset guessed"); }
  catch(InvocationTargetException expected) { }
  if(!((java.util.Set<?>)errors.get(s)).contains("MissingValue") || !((java.util.Set<?>)errors.get(s)).contains("BadBase"))
   throw new AssertionError("failed value layouts not quarantined");
  // An unknown-size base contributes no fields but still blocks its owner.
  // Both traversal orders must reject the owner before marking it complete.
  JsonObject incompleteBases=JsonParser.parseString("{\"BaseOwner\":{\"size\":8,\"bases\":[{\"name\":\"MissingBase\",\"offset\":0}],\"fields\":[{\"offset\":0,\"name\":\"value\",\"type\":\"int\",\"size\":4}]},\"MissingBase\":{\"size\":0,\"bases\":[],\"fields\":[]}}").getAsJsonObject();
  for(String[] traversal:new String[][]{{"BaseOwner","MissingBase"},{"MissingBase","BaseOwner"}}) {
   DecompDrafts importer=new DecompDrafts();classMap.set(importer,incompleteBases);dataManager.set(importer,manager);vtables.set(importer,new JsonObject());
   java.util.Map<String,Structure> imported=(java.util.Map<String,Structure>)structures.get(importer);
   for(String name:incompleteBases.keySet()) imported.put(name,new StructureDataType(name,0,manager));
   for(String name:traversal) {
    try { fill.invoke(importer,name); throw new AssertionError("unknown-size base accepted via " + name); }
    catch(InvocationTargetException expected) { }
   }
   if(((java.util.Set<?>)completed.get(importer)).contains("BaseOwner") ||
      !((java.util.Set<?>)errors.get(importer)).contains("BaseOwner") ||
      !((java.util.Set<?>)errors.get(importer)).contains("MissingBase"))
    throw new AssertionError("unknown-size base did not quarantine owner in both orders");
  }
  Method apply=DecompDrafts.class.getDeclaredMethod("applyPrototype",
    ghidra.program.model.listing.Function.class,JsonObject.class);
  apply.setAccessible(true);
  JsonObject proto=new JsonObject();proto.addProperty("ret",unsupported);
  if((Boolean)apply.invoke(s,null,proto)) throw new AssertionError("target unsupported prototype accepted");
  // Apply a real pointer prototype to a real Ghidra Program/function, using
  // the same current CDataGroup field that previously poisoned that prototype.
  ghidra.program.model.lang.Language language=ghidra.program.util.DefaultLanguageService.getLanguageService().getLanguage(new ghidra.program.model.lang.LanguageID("x86:LE:64:default"));
  Object consumer=new Object();
  ghidra.program.database.ProgramDB program=new ghidra.program.database.ProgramDB("pointer-prototype",language,language.getCompilerSpecByID(new ghidra.program.model.lang.CompilerSpecID("gcc")),consumer);
  int programTransaction=program.startTransaction("pointer prototype");
  try {
   Field currentProgram=ghidra.program.flatapi.FlatProgramAPI.class.getDeclaredField("currentProgram");currentProgram.setAccessible(true);currentProgram.set(s,program);
   ghidra.program.model.address.Address entry=program.getAddressFactory().getDefaultAddressSpace().getAddress(0x1000);
   ghidra.program.model.listing.Function target=program.getFunctionManager().createFunction("target",entry,new ghidra.program.model.address.AddressSet(entry,entry),ghidra.program.model.symbol.SourceType.USER_DEFINED);
   JsonObject pointerPrototype=JsonParser.parseString("{\"ret\":\"bool\",\"ret_size\":1,\"trusted\":true,\"member\":false,\"static\":true,\"sret\":false,\"params\":[{\"type\":\"CDataGroup*\",\"size\":8}]}").getAsJsonObject();
   if(!(Boolean)apply.invoke(s,target,pointerPrototype)) throw new AssertionError("CDataGroup pointer prototype rejected");
   DataType parameter=target.getParameter(0).getDataType();
   if(!(parameter instanceof Pointer) || parameter.getLength()!=8 || !((Pointer)parameter).getDataType().getName().equals("CDataGroup"))
    throw new AssertionError("CDataGroup pointer prototype lost identity");
   JsonObject matrixPrototype=JsonParser.parseString("{\"ret\":\"void\",\"ret_size\":0,\"trusted\":true,\"member\":false,\"static\":true,\"sret\":false,\"params\":[{\"type\":\"Ogre::Matrix4*\",\"size\":8}]}").getAsJsonObject();
   if(!(Boolean)apply.invoke(s,target,matrixPrototype)) throw new AssertionError("Matrix4 pointer prototype rejected");
   String iteratorName=null;
   for(String name:layouts.keySet()) if(name.startsWith("__gnu_cxx::__normal_iterator<Ogre::Vector3*")) iteratorName=name;
   if(iteratorName==null) throw new AssertionError("missing actual vector iterator layout");
   matrixPrototype.getAsJsonArray("params").get(0).getAsJsonObject().addProperty("type",iteratorName);
   if(!(Boolean)apply.invoke(s,target,matrixPrototype) || target.getParameter(0).getDataType().getLength()!=8)
    throw new AssertionError("actual by-value iterator prototype rejected");
   if(!(Boolean)apply.invoke(s,target,pointerPrototype)) throw new AssertionError("restore pointer prototype");
   String signature=target.getSignature().toString();
   pointerPrototype.getAsJsonArray("params").get(0).getAsJsonObject().addProperty("type","Unknown*");
   if((Boolean)apply.invoke(s,target,pointerPrototype) || !signature.equals(target.getSignature().toString()))
    throw new AssertionError("unknown prototype guessed or mutated");
   pointerPrototype.getAsJsonArray("params").get(0).getAsJsonObject().addProperty("type",repositoryValue);
   if((Boolean)apply.invoke(s,target,pointerPrototype)) throw new AssertionError("forward class by-value prototype accepted");
  } finally { program.endTransaction(programTransaction,true);program.release(consumer); }
  manager.endTransaction(transaction,true);manager.close();

 }
}
'''
        with tempfile.TemporaryDirectory(prefix='otl-java-type-test-') as tmp:
            source = Path(tmp) / 'WidthProbe.java'
            source.write_text(helper)
            fixture = Path(tmp) / 'containers.cpp'
            fixture.write_text('#include <vector>\n#include <map>\n#include <OgreMatrix4.h>\n'
                               '#include "EmptyStrings.h"\n#include "CollisionList.h"\n'
                               '#include "SoundBankDataInformation.h"\n#include "SoundData.h"\n'
                               'typedef char safe[(sizeof(TSafePointer<void*>) > 0) ? 1 : -1];\n'
                               'typedef char safe_list[(sizeof(TArrayList<TSafePointer<void*>*>) > 0) ? 1 : -1];\n'
                               'struct Containers { std::vector<int> values; std::map<long long, int*> lookup; '
                               'std::pair<const int, long> keyValue; };\n'
                               'Containers containers;\nstd::vector<Ogre::Vector3>::iterator vector_iterator;\n')
            obj = fixture.with_suffix('.o')
            toolchain.compile_source(fixture, obj, ['-g', '-O0', '-fno-eliminate-unused-debug-types',
                                                   '-femit-class-debug-always'], cache=False)
            layouts = Path(tmp) / 'layouts.json'
            dies = types_export.parse_dies(obj)
            layouts.write_text(json.dumps(types_export.header_classes(dies)))
            identities = Path(tmp) / 'identities.json'
            identities.write_text(json.dumps(types_export.type_identities(dies)))
            script = Path(ghidra_draft.__file__).parent / 'ghidra' / 'DecompDrafts.java'
            compiled = subprocess.run(['javac', '-cp', cp, '-d', tmp, str(script), str(source)],
                                      capture_output=True, text=True, timeout=60)
            self.assertEqual(compiled.returncode, 0, compiled.stderr)
            result = subprocess.run(['java', '-Duser.home=' + tmp, '-cp', tmp + ':' + cp,
                                     'WidthProbe', str(ghidra_draft.GHIDRA_HOME), str(layouts), str(identities)],
                                    capture_output=True, text=True, timeout=30)
            self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == '__main__':
    unittest.main()
