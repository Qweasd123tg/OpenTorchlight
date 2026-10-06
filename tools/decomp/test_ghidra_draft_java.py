#!/usr/bin/env python3
"""Compile against installed pinned Ghidra, then execute real LP64 datatype checks."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

import ghidra_draft


@unittest.skipUnless((ghidra_draft.GHIDRA_HOME / 'Ghidra').is_dir() and shutil.which('javac'),
                     'requires the installed Ghidra SDK and a JDK')
class GhidraJava(unittest.TestCase):
    def test_script_api_and_lp64_widths(self):
        cp = ':'.join(str(p) for p in ghidra_draft.GHIDRA_HOME.rglob('*.jar'))
        helper = '''
import java.lang.reflect.*;
import com.google.gson.JsonObject;
import ghidra.program.model.data.*;
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
  Method apply=DecompDrafts.class.getDeclaredMethod("applyPrototype",
    ghidra.program.model.listing.Function.class,JsonObject.class);
  apply.setAccessible(true);
  JsonObject proto=new JsonObject();proto.addProperty("ret",unsupported);
  if((Boolean)apply.invoke(s,null,proto)) throw new AssertionError("target unsupported prototype accepted");
  manager.endTransaction(transaction,true);manager.close();

 }
}
'''
        with tempfile.TemporaryDirectory(prefix='otl-java-type-test-') as tmp:
            source = Path(tmp) / 'WidthProbe.java'
            source.write_text(helper)
            script = Path(ghidra_draft.__file__).parent / 'ghidra' / 'DecompDrafts.java'
            compiled = subprocess.run(['javac', '-cp', cp, '-d', tmp, str(script), str(source)],
                                      capture_output=True, text=True, timeout=60)
            self.assertEqual(compiled.returncode, 0, compiled.stderr)
            result = subprocess.run(['java', '-Duser.home=' + tmp, '-cp', tmp + ':' + cp,
                                     'WidthProbe', str(ghidra_draft.GHIDRA_HOME)],
                                    capture_output=True, text=True, timeout=30)
            self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == '__main__':
    unittest.main()
