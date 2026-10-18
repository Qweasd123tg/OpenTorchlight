#include "SmallMassCompare.h"
#include "UnitResourceList.h"
#include "FileSystem.h"
#include "Utilities.h"
#include "StringUtilities.h"
#include "EmptyStrings.h"
#include <OgreLogManager.h>
TL_ORIGINAL(void, resourceDtor,(CUnitResourceList*),"_ZN17CUnitResourceListD1Ev")
extern "C" void resourceDtorNew(CUnitResourceList*) __asm__("_ZN17CUnitResourceListD1Ev");
TL_ORIGINAL(CDataGroup*, resourceWide,(CUnitResourceList*,const wchar_t*,const wchar_t*),"_ZN17CUnitResourceList22getDataGroupByFileNameEPKwS1_")
extern "C" CDataGroup* resourceWideNew(CUnitResourceList*,const wchar_t*,const wchar_t*) __asm__("_ZN17CUnitResourceList22getDataGroupByFileNameEPKwS1_");
TL_ORIGINAL(CDataGroup*, resourceChild,(CUnitResourceList*,const std::wstring&,bool),"_ZN17CUnitResourceList14parseChildFileERKSbIwSt11char_traitsIwESaIwEEb")
extern "C" CDataGroup* resourceChildNew(CUnitResourceList*,const std::wstring&,bool) __asm__("_ZN17CUnitResourceList14parseChildFileERKSbIwSt11char_traitsIwESaIwEEb");
TL_ORIGINAL(void, resourceDirectory,(CUnitResourceList*,ERESOURCE_GROUPS,std::wstring,std::wstring,CDataGroup*,bool),"_ZN17CUnitResourceList20parseMasterDirectoryE16ERESOURCE_GROUPSSbIwSt11char_traitsIwESaIwEES4_P10CDataGroupb")
extern "C" void resourceDirectoryNew(CUnitResourceList*,ERESOURCE_GROUPS,std::wstring,std::wstring,CDataGroup*,bool) __asm__("_ZN17CUnitResourceList20parseMasterDirectoryE16ERESOURCE_GROUPSSbIwSt11char_traitsIwESaIwEES4_P10CDataGroupb");
TL_FUNCTION(deepenLoad,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TL_FUNCTION(deepenSave,"_ZN10CDataGroup10SaveToFileERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(deepenGuid,"_ZN9UTILITIES16createUniqueGuidEv")
TL_FUNCTION(deepenFiles,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(deepenLoadUnit,"_ZN17CUnitResourceList8loadFileE16ERESOURCE_GROUPSSbIwSt11char_traitsIwESaIwEES4_bP10CDataGroup")
namespace deepen_resource {
using namespace smallmass;
CUnitResourceList* active;CDataGroup* parent;unsigned loads,saves;
void check(bool b){number(b);if(!b)_exit(45);}
void load(CDataGroup* group,const std::wstring& file,CTimerStatics* timer){
 number(1);text(file);number(timer==0);++loads;
 unsigned depth=file==L"child.dat"?input->index/32%4:unsigned(file[4]-L'0');
 if(depth){std::wstring base=L"base0.dat";base[4]+=depth-1;group->SetDataValue(L"BASEFILE",base,false);}
 group->SetDataValue(L"DONTCREATE",bool(input->index&1));
 if(input->index&2)group->SetDataValue(L"UNIT_GUID",L"original-guid",false);
 if(input->index&4)group->SetDataValue(L"DISPLAYNAME",L"existing display",false);
 if(input->index&8)group->SetDataValue(L"NAME",L"Test 名称",false);
 group->SetDataValue(L"DEPTH",int(depth));
}
int save(CDataGroup* group,const std::wstring& file){number(2);text(file);text(group->GetDataValue(L"UNIT_GUID",EMPTY_WSTRING));text(group->GetDataValue(L"DISPLAYNAME",EMPTY_WSTRING));++saves;return int(input->index%3)-1;}
long long guid(){number(3);return input->index&64?-1LL:123456789012345LL;}
unsigned files(CFileSystem*,const std::wstring& path,TArrayList<std::wstring>& out,std::wstring pattern,bool recurse,bool strip,bool mods,bool skip){
 number(10);text(path);text(pattern);number(field<unsigned>(&out,0x10));number(recurse);number(strip);number(mods);number(skip);
 for(unsigned i=0;i<input->index%6;++i){std::wstring file=L"media/Test0.dat";file[10]+=i;out.add(file);}return out.size();
}
void loadUnit(CUnitResourceList* self,ERESOURCE_GROUPS kind,std::wstring group,std::wstring file,bool overwrite,CDataGroup* value){number(11);number(self==active);number(kind);text(group);text(file);number(overwrite);number(value==parent);}
CDataGroup* group(const wchar_t* name){return new CDataGroup(name,0,3,2,0);}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;
 CUnitResourceList* previous=m_pGlobalUnitResourceList;m_pGlobalUnitResourceList=0;
 CUnitResourceList* self=::new(object(sizeof(CUnitResourceList)))CUnitResourceList;active=self;
 int count=g_iTotalCountOfObjects;
 if(c.op==0){
  TSafePointer<CUnitResourceList> weak;weak.setObject(self);
  for(unsigned i=0;i<c.index%5;++i){CDataGroup* data=group(L"owned");data->SetDataValue(L"NAME",L"nonempty",false);self->m_loadedDataGroups.add(data);self->m_dataGroupsByGuid[i]=data;self->m_dataGroupsByResourceGroupAndName[L"group"][STRINGS::GetValueAsWString(i)]=data;self->m_dataGroupsByFileItemAndName[L"file"][STRINGS::GetValueAsWString(i)]=data;self->m_dataGroupsByResourceGroupAndGuid[L"group"][i]=data;self->m_playerClassNames.add(STRINGS::GetValueAsWString(i));}
  if(c.index&8)self->m_pMasterDataGroup=group(L"master");
  out.addHeapInUse();autotest::invoke(out,ours?resourceDtorNew:resourceDtor,self);out.addHeapInUse();number(weak.getObject()==0);number(m_pGlobalUnitResourceList==0);number(g_iTotalCountOfObjects-count);
  m_pGlobalUnitResourceList=previous;return;
 }
 if(c.op==1){
  CDataGroup* data=group(L"first");CDataGroup* other=group(L"second");
  self->m_dataGroupsByFileItemAndName[L"MEDIA/FILE.DAT"][L"OBJECT/PATH"]=data;
  self->m_dataGroupsByFileItemAndName[L"ZFILE"][L"ZOBJECT"]=other;
  self->m_dataGroupsByFileItemAndName[L"AFILE"][L"AOBJECT"]=other;
  const wchar_t* file=c.index%4==0?L"media/file.dat":c.index%4==1?L"MEDIA/FILE.DAT":c.index%4==2?L"missing":L"zfile";
  const wchar_t* item=c.index%5==0?L"object\\path":c.index%5==1?L"OBJECT/PATH":c.index%5==2?L"missing":c.index%5==3?L"zobject":L"";
  if(c.index%4==2&&c.index&32)item=0;
  typedef CDataGroup* (*Fn)(CUnitResourceList*,const wchar_t*,const wchar_t*);Fn fn=ours?resourceWideNew:resourceWide;
  if(!autotest::beginInvocation(out,fn))return;CDataGroup* result=fn(self,file,item);out.callCompleted=1;number(result==data?1:result==other?2:result?3:0);
  delete data;delete other;
 }else if(c.op==2){
  loads=saves=0;detour::Set p;TL_REDIRECT(p,deepenLoad,&load);TL_REDIRECT(p,deepenSave,&save);TL_REDIRECT(p,deepenGuid,&guid);if(p.failed())_exit(42);
  typedef CDataGroup* (*Fn)(CUnitResourceList*,const std::wstring&,bool);Fn fn=ours?resourceChildNew:resourceChild;
  const std::wstring file=L"child.dat";if(!autotest::beginInvocation(out,fn))return;CDataGroup* result=fn(self,file,bool(c.index&16));out.callCompleted=1;
  check(result!=0);number(loads);number(saves);text(result->GetDataValue(L"BASEFILE",EMPTY_WSTRING));text(result->GetDataValue(L"NAME",EMPTY_WSTRING));text(result->GetDataValue(L"UNIT_GUID",EMPTY_WSTRING));text(result->GetDataValue(L"DISPLAYNAME",EMPTY_WSTRING));number(result->GetDataValue(L"DONTCREATE",false));number(result->GetDataValue(L"DEPTH",-1));delete result;
 }else{
  parent=c.index&1?group(L"parent"):0;detour::Set p;TL_REDIRECT(p,deepenFiles,&files);TL_REDIRECT(p,deepenLoadUnit,&loadUnit);if(p.failed())_exit(42);
  std::wstring directory=c.index%3==0?L"":L"media/units";std::wstring name=c.index%7==0?L"":L"monster";
  autotest::invoke(out,ours?resourceDirectoryNew:resourceDirectory,self,static_cast<ERESOURCE_GROUPS>(c.index%7),directory,name,parent,bool(c.index&2));delete parent;
 }
 self->~CUnitResourceList();m_pGlobalUnitResourceList=previous;
}
}
TL_TEST(deepen_unit_resources_destructor){return smallmass::run(host,0,"deepen_unit_resources_destructor",(uint64_t)(uintptr_t)resourceDtor,&deepen_resource::execute,48);}
TL_TEST(deepen_unit_resources_wide_lookup){return smallmass::run(host,1,"deepen_unit_resources_wide_lookup",(uint64_t)(uintptr_t)resourceWide,&deepen_resource::execute,96);}
TL_TEST(deepen_unit_resources_child_files){return smallmass::run(host,2,"deepen_unit_resources_child_files",(uint64_t)(uintptr_t)resourceChild,&deepen_resource::execute,128);}
TL_TEST(deepen_unit_resources_master_directory){return smallmass::run(host,3,"deepen_unit_resources_master_directory",(uint64_t)(uintptr_t)resourceDirectory,&deepen_resource::execute,84);}
