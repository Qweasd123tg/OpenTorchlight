#include <string>
#include <map>
#include <typeinfo>
#include <OgreLogManager.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "DataGroup.h"
#include "TRepository.h"
#include "FileSystem.h"
#undef private
#include "PairStyle.h"
#include "OgreResourceFile.h"
#include "TimerStatics.h"
#define TARGET(ret,old,newer,args,symbol) TL_ORIGINAL(ret,old,args,symbol) extern "C" ret newer args __asm__(symbol);
TARGET(CDataValue*,dgOldCopy,dgNewCopy,(CDataGroup*,CDataValue*,TArrayList<CDataValue*>*),"_ZN10CDataGroup13CopyDataValueEP10CDataValueP10TArrayListIS1_E")
TARGET(CDataValue*,dgOldID,dgNewID,(CDataGroup*,unsigned,UNIONDATA64BIT,CDataValue::EDATAVALUETYPES),"_ZN10CDataGroup12AddDataValueEj14UNIONDATA64BITN10CDataValue15EDATAVALUETYPESE")
TARGET(CDataValue*,dgOldString,dgNewString,(CDataGroup*,const std::wstring&,std::wstring,std::wstring),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES3_S3_")
TARGET(void,dgOldName,dgNewName,(CDataGroup*,const std::wstring&),"_ZN10CDataGroup12SetGroupNameERKSbIwSt11char_traitsIwESaIwEE")
TARGET(void,dgOldGroup,dgNewGroup,(CDataGroup*,CDataGroup*,bool),"_ZN10CDataGroup13CopyDataGroupEPS_b")
TARGET(void,dgOldLoad,dgNewLoad,(CDataGroup*,const std::wstring&,CTimerStatics*),"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TARGET(CDataValue*,dgOldFind,dgNewFind,(CDataGroup*,const std::wstring&),"_ZN10CDataGroup18GetDataValueByNameERKSbIwSt11char_traitsIwESaIwEE")
TARGET(CDataValue*,dgOldAdd,dgNewAdd,(CDataGroup*,const std::wstring&,const std::wstring&,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
#undef TARGET
TL_FUNCTION(dgFS,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(dgCached,"_ZN11CFileSystem12getDataGroupERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(dgInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(dgDelegate,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP20iDataFileSaveAndLoadP13CTimerStatics")
extern "C" char dgLogSingleton[] __asm__("_ZN4Ogre10LogManager12getSingletonEv");
extern "C" char dgLogMessage[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace {
struct Case{unsigned mode,seed;};autotest::Capture*cap;unsigned seed,loads,logs,infos;CDataGroup*cachedGroup,*receiver;CTimerStatics*timing;int token;
void n(unsigned x){cap->add(&x,4);}void bad(){cap->issue=autotest::Capture::InvalidReport;}
CFileSystem*fs(){return reinterpret_cast<CFileSystem*>(&token);}Ogre::LogManager*logger(){return reinterpret_cast<Ogre::LogManager*>(&token);}
CDataGroup*cached(CFileSystem*p,const std::wstring&file){n(1);cap->addText(file);if(p!=fs())bad();return seed&1?cachedGroup:NULL;}
void info(CFileSystem*p,const std::wstring&file,CFileInfo&i,bool a,bool b,bool c){++infos;n(2);cap->addText(file);n(a);n(b);n(c);if(p!=fs()||a||!b||c)bad();i.m_bExists=true;i.m_eFormat=(seed/2)%5;i.m_eLocation=(seed/10)%4;i.m_sPath=L"resolved/path";}
void delegate(CDataGroup*p,const std::wstring&file,iDataFileSaveAndLoad*style,CTimerStatics*t){++loads;n(3);cap->addText(file);cap->addText(typeid(*style).name());n(t!=NULL);if(p!=receiver||t!=timing)bad();p->AddDataValue(L"loaded",seed);p->SetGroupName(L"delegated");}
void log(Ogre::LogManager*p,const std::string&s,Ogre::LogMessageLevel l,bool mask){++logs;n(4);cap->addText(s);n(l);n(mask);if(p!=logger()||l!=Ogre::LML_CRITICAL||mask)bad();}
void repository(TRepository<std::wstring>&r){n(r.m_iNextID);n(r.m_Values.size());for(std::map<unsigned,std::wstring>::iterator i=r.m_Values.begin();i!=r.m_Values.end();++i){n(i->first);cap->addText(i->second);}n(r.m_RefCounts.size());for(std::map<unsigned,unsigned short>::iterator i=r.m_RefCounts.begin();i!=r.m_RefCounts.end();++i){n(i->first);cap->add(&i->second,2);}}
void value(CDataValue*p){n(p!=NULL);if(!p)return;cap->addText(p->GetDataValueName());n(p->m_eType);cap->add(&p->m_Value,8);n(p->m_bStringValue);}
void tree(CDataGroup*p){cap->addText(p->GetGroupName());n(p->m_b58);n(p->m_b59);n(p->m_DataValues.m_nCapacity);n(p->m_DataValues.m_nGrowBy);n(p->m_DataValues.size());for(unsigned i=0;i<p->m_DataValues.size();++i)value(p->m_DataValues[i]);n(p->m_DataGroups.m_nCapacity);n(p->m_DataGroups.m_nGrowBy);n(p->m_DataGroups.size());for(unsigned i=0;i<p->m_DataGroups.size();++i)tree(p->m_DataGroups[i]);}
void fill(CDataGroup&g,unsigned count,unsigned salt){for(unsigned i=0;i<count;++i){wchar_t name[24];std::swprintf(name,24,L"value%u",i%3);if(i&1)g.AddDataValue(name,L"retained Ж",false);else g.AddDataValue(name,int(salt+i));}for(unsigned i=0;i<salt%3;++i){CDataGroup*d=g.AddDataGroup(i&1?L"second":L"child");d->AddDataValue(L"leaf",int(i+salt));}}
unsigned index(CDataGroup&g,CDataValue*p){for(unsigned i=0;i<g.m_DataValues.size();++i)if(g.m_DataValues[i]==p)return i;return ~0u;}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;cap=&out;loads=logs=infos=0;TRepository<std::wstring> repo(L"");
 {CDataGroup parent(L"parent",NULL,2,2,NULL);CDataGroup source(L"source",&parent,2,2,&repo);fill(source,seed%6,seed%4);CDataGroup data(L"destination",&parent,1+seed%3,1+seed%2,&repo);receiver=&data;fill(data,c.mode==5&&seed&1?0:(seed/3)%5,seed%4);data.setDirty(false);TArrayList<CDataValue*> pool(2);for(unsigned i=0;i<data.m_DataValues.size();++i)pool.add(data.m_DataValues[i]);
 if(c.mode==0){CDataValue*input=source.m_DataValues.size()?source.m_DataValues[seed%source.m_DataValues.size()]:NULL;typedef CDataValue*(*Fn)(CDataGroup*,CDataValue*,TArrayList<CDataValue*>*);Fn fn=ours?dgNewCopy:dgOldCopy;if(!autotest::beginInvocation(out,fn))return;CDataValue*result=fn(&data,input,seed%7?&pool:NULL);out.callCompleted=1;value(result);n(index(data,result));n(pool.size());for(unsigned i=0;i<pool.size();++i)n(index(data,pool[i]));}
 else if(c.mode==1){std::wstring name=L"byid",text=L"string data";unsigned id=repo.addItem(name);unsigned stringID=repo.addItem(text);UNIONDATA64BIT v;v.signed64=seed&2?-0x123456789abcLL:0x123456789abcdefLL;unsigned type=seed%10;if(type==5||type==8)v.unsigned32=stringID;typedef CDataValue*(*Fn)(CDataGroup*,unsigned,UNIONDATA64BIT,CDataValue::EDATAVALUETYPES);Fn fn=ours?dgNewID:dgOldID;if(!autotest::beginInvocation(out,fn))return;CDataValue*result=fn(&data,seed%11?id:~0u,v,static_cast<CDataValue::EDATAVALUETYPES>(type));out.callCompleted=1;value(result);n(index(data,result));}
 else if(c.mode==2){const wchar_t*types[]={L"INTEGER",L"INTEGER64",L"FLOAT",L"DOUBLE",L"UNSIGNED INT",L"BOOL",L"TRANSLATE",L"DIALOG",L"STRING",L"unknown"};std::wstring name=seed%3?L"typed":L"",type=types[seed%10],text=seed%4==0?L"false":seed%4==1?L"-123":seed%4==2?L"15.25":L"Ж text";typedef CDataValue*(*Fn)(CDataGroup*,const std::wstring&,std::wstring,std::wstring);Fn fn=ours?dgNewString:dgOldString;if(!autotest::beginInvocation(out,fn))return;CDataValue*result=fn(&data,name,type,text);out.callCompleted=1;value(result);n(index(data,result));cap->addText(name);cap->addText(type);cap->addText(text);}
 else if(c.mode==3){const wchar_t*names[]={L"",L"/",L"///",L"//same",L"destination",L"new",L"Ж/path"};std::wstring name=names[seed%7];TRepository<std::wstring>*saved=data.m_pRepository;if(seed%11==0)data.m_pRepository=NULL;const std::wstring&input=seed&16?source.GetGroupName():name;typedef void(*Fn)(CDataGroup*,const std::wstring&);Fn fn=ours?dgNewName:dgOldName;if(!autotest::beginInvocation(out,fn))return;fn(&data,input);out.callCompleted=1;n(data.m_pRepository==NULL);data.m_pRepository=saved;cap->addText(name);}
 else if(c.mode==4){typedef void(*Fn)(CDataGroup*,CDataGroup*,bool);Fn fn=ours?dgNewGroup:dgOldGroup;if(!autotest::beginInvocation(out,fn))return;fn(&data,seed%13?&source:NULL,seed&1);out.callCompleted=1;}
 else if(c.mode==5){cachedGroup=&source;CTimerStatics timer;timing=seed&2?&timer:NULL;std::wstring path=L"synthetic/path.dat";detour::Set patches;TL_REDIRECT(patches,dgFS,&fs);TL_REDIRECT(patches,dgCached,&cached);TL_REDIRECT(patches,dgInfo,&info);TL_REDIRECT(patches,dgDelegate,&delegate);patches.redirect(reinterpret_cast<char*>(0x554918),dgLogSingleton,&logger);patches.redirect(reinterpret_cast<char*>(0x554e68),dgLogMessage,&log);if(patches.failed()){bad();return;}typedef void(*Fn)(CDataGroup*,const std::wstring&,CTimerStatics*);Fn fn=ours?dgNewLoad:dgOldLoad;if(!autotest::beginInvocation(out,fn))return;fn(&data,path,timing);out.callCompleted=1;n(loads);n(logs);n(infos);if(seed&1){if(!data.m_b59)bad();for(unsigned i=0;i<source.m_DataValues.size();++i)n(data.m_DataValues[data.m_DataValues.size()-source.m_DataValues.size()+i]==source.m_DataValues[i]);}}
 else if(c.mode==6){std::wstring name=seed%4==0?L"missing":seed%4==1?L"value0":seed%4==2?L"value1":L"value2";if((seed&16)&&data.m_DataValues.size())name=data.m_DataValues[data.m_DataValues.size()-1]->GetDataValueName();typedef CDataValue*(*Fn)(CDataGroup*,const std::wstring&);Fn fn=ours?dgNewFind:dgOldFind;if(!autotest::beginInvocation(out,fn))return;CDataValue*result=fn(&data,name);out.callCompleted=1;n(index(data,result));value(result);}
 else{std::wstring name=seed%3?L"value0":L"new",text=seed%4?L"retained Ж":L"";const std::wstring&input=(seed&16)&&data.m_DataValues.size()?data.m_DataValues[0]->GetDataValueName():name;typedef CDataValue*(*Fn)(CDataGroup*,const std::wstring&,const std::wstring&,bool);Fn fn=ours?dgNewAdd:dgOldAdd;if(!autotest::beginInvocation(out,fn))return;CDataValue*result=fn(&data,input,text,seed&1);out.callCompleted=1;value(result);n(index(data,result));cap->addText(text);}
 tree(&data);tree(&source);repository(repo);
 // Cached values are borrowed; previously owned values stay owned by this fixture.
 if(data.m_b59){unsigned ownedValues=data.m_DataValues.size()-source.m_DataValues.size(),ownedGroups=data.m_DataGroups.size()-source.m_DataGroups.size();for(unsigned i=0;i<ownedValues;++i)delete data.m_DataValues[i];for(unsigned i=0;i<ownedGroups;++i)delete data.m_DataGroups[i];}
 }repository(repo);}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*name,uintptr_t addr){autotest::Coverage coverage(name,addr);for(unsigned i=0;i<120;++i){Case c={mode,i};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){for(unsigned z=0;z<x.capture.length&&z<y.capture.length;++z)if(x.capture.data[z]!=y.capture.data[z]){h->log("    first difference %u %u/%u\n",z,unsigned((unsigned char)x.capture.data[z]),unsigned((unsigned char)y.capture.data[z]));break;}h->log("    data group mode%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",mode,i,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(deepen_editor_data_copy_value){return run(host,0,"deepen_editor_data_copy_value",(uintptr_t)&dgOldCopy);}
TL_TEST(deepen_editor_data_add_id){return run(host,1,"deepen_editor_data_add_id",(uintptr_t)&dgOldID);}
TL_TEST(deepen_editor_data_add_typed){return run(host,2,"deepen_editor_data_add_typed",(uintptr_t)&dgOldString);}
TL_TEST(deepen_editor_data_set_name){return run(host,3,"deepen_editor_data_set_name",(uintptr_t)&dgOldName);}
TL_TEST(deepen_editor_data_copy_group){return run(host,4,"deepen_editor_data_copy_group",(uintptr_t)&dgOldGroup);}
TL_TEST(deepen_editor_data_load){return run(host,5,"deepen_editor_data_load",(uintptr_t)&dgOldLoad);}
TL_TEST(deepen_editor_data_old_find){return run(host,6,"deepen_editor_data_old_find",(uintptr_t)&dgOldFind);}
TL_TEST(deepen_editor_data_old_add_string){return run(host,7,"deepen_editor_data_old_add_string",(uintptr_t)&dgOldAdd);}
