#include <stdint.h>
#include <cstring>
#include <new>
#include <string>
#include <map>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#include "SafePointer.h"
#define private public
#include "TRepository.h"
#include "DataGroup.h"
#include "DataValue.h"
#include "FileSystem.h"
#include "PairStyle.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,oName,nName,(CDataGroup*,unsigned),"_ZN10CDataGroup14SetGroupNameIDEj")
DECL(CDataValue*,oUnion,nUnion,(CDataGroup*,unsigned,UNIONDATA64BIT,CDataValue::EDATAVALUETYPES),"_ZN10CDataGroup12AddDataValueEj14UNIONDATA64BITN10CDataValue15EDATAVALUETYPESE")
DECL(CDataValue*,oText,nText,(CDataGroup*,const std::wstring&,std::wstring,std::wstring),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES3_S3_")
DECL(int,oSave,nSave,(CDataGroup*,const std::wstring&),"_ZN10CDataGroup10SaveToFileERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,oCtor,(CDataGroup*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,oDtor,(CDataGroup*),"_ZN10CDataGroupD1Ev")
TL_FUNCTION(singleton,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(fileInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(savePair,"_ZN10CPairStyle19SaveDataGroupToFileERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup")
TL_FUNCTION(pairDtor,"_ZN10CPairStyleD1Ev")
TL_ORIGINAL(void,realPairDtor,(CPairStyle*),"_ZN10CPairStyleD1Ev")
#undef DECL
namespace {
struct Case{unsigned mode,seed;};autotest::Capture* capture;unsigned seed;CDataGroup* receiver;CFileSystem* filesystem;
struct SaveFailure { unsigned stage; explicit SaveFailure(unsigned value):stage(value){} };
unsigned faultStage,styleDestructions,infoCalls,saveCalls;
std::string* narrowWitnesses;
std::wstring* pathWitness;
CPairStyle* expectedStyle;
detour::Set* styleDtorPatch;
// The original narrow and wide COW string destructors decrement data-8.
int references(const std::string& value){int refs;std::memcpy(&refs,value.c_str()-8,4);return refs;}
int references(const std::wstring& value){int refs;std::memcpy(&refs,reinterpret_cast<const char*>(value.c_str())-8,4);return refs;}
void number(unsigned value){capture->add(&value,4);}
void destroyedStyle(CPairStyle* style){
    ++styleDestructions;number(4);number(expectedStyle==NULL||expectedStyle==style);
    if(expectedStyle&&expectedStyle!=style)capture->issue=autotest::Capture::InvalidReport;
    // Observe the call, then restore and execute the actual destructor rather
    // than replacing its lifetime effects with a trace-only fake.
    styleDtorPatch->restore();realPairDtor(style);
}
CFileSystem* getSingleton(){number(1);return filesystem;}
void getInfo(CFileSystem*self,const std::wstring& file,CFileInfo& info,bool a,bool b,bool c){
 ++infoCalls;number(2);number(self==filesystem);capture->addText(file);number(a);number(b);number(c);
 info.m_bExists=seed&1;info.m_sPath=seed&2?L"resolved/path.DAT":L"";
 if(narrowWitnesses){info.m_sModName=narrowWitnesses[0];info.m_sResourceName=narrowWitnesses[1];info.m_sResourceGroup=narrowWitnesses[2];info.m_sPath=*pathWitness;}
 if(faultStage==1)throw SaveFailure(1);
}
int save(CPairStyle* style,const std::wstring& file,CDataGroup* group){
 ++saveCalls;expectedStyle=style;number(3);number(group==receiver);capture->addText(file);number(group->m_b58);
 if(faultStage==2)throw SaveFailure(2);
 return int(seed*98765)^int(0x80000000u);
}
void repository(TRepository<std::wstring>& r){number(r.m_iNextID);number(r.m_Values.size());for(std::map<unsigned,std::wstring>::iterator i=r.m_Values.begin();i!=r.m_Values.end();++i){number(i->first);capture->addText(i->second);}number(r.m_IDs.size());for(std::map<std::wstring,unsigned>::iterator i=r.m_IDs.begin();i!=r.m_IDs.end();++i){capture->addText(i->first);number(i->second);}number(r.m_RefCounts.size());for(std::map<unsigned,unsigned short>::iterator i=r.m_RefCounts.begin();i!=r.m_RefCounts.end();++i){number(i->first);capture->add(&i->second,2);}}
void state(CDataGroup* group){number(group->m_iNameID);number(group->m_b58);number(group->m_b59);number(group->m_DataValues.size());number(group->m_DataValues.m_nCapacity);number(group->m_DataValues.m_nGrowBy);for(unsigned i=0;i<group->m_DataValues.size();++i){CDataValue* v=group->m_DataValues[i];number(v->m_bStringValue);capture->add(&v->m_Value,8);number(v->m_iNameID);number(v->m_eType);}number(group->m_DataGroups.size());for(unsigned i=0;i<group->m_DataGroups.size();++i)state(group->m_DataGroups[i]);}
void side(void*raw,autotest::Capture& out,bool ours){const Case&c=*static_cast<Case*>(raw);capture=&out;seed=c.seed;faultStage=styleDestructions=infoCalls=saveCalls=0;narrowWitnesses=NULL;pathWitness=NULL;expectedStyle=NULL;styleDtorPatch=NULL;TRepository<std::wstring> r(L"<default>");std::wstring names[]={L"",L"name",L"Ж",L"value",L"<default>"};for(unsigned i=0;i<seed%6&&i<5;++i){r.m_Values[i]=names[i];r.m_IDs[names[i]]=i;if(seed&4)r.m_RefCounts[i]=(seed&8)?65535:3;}r.m_iNextID=5;uint64_t parentStorage[(sizeof(CDataGroup)+7)/8],storage[(sizeof(CDataGroup)+7)/8];
 std::memset(parentStorage,0xa5,sizeof(parentStorage));std::memset(storage,0xa5,sizeof(storage));
 CDataGroup*parent=reinterpret_cast<CDataGroup*>(parentStorage);CDataGroup*self=reinterpret_cast<CDataGroup*>(storage);
 // A root owns and Ned-deletes its non-global repository (D1 @c617a0).
 // This child borrows the local repository; the separately constructed parent
 // uses the original global repository and therefore never owns local storage.
 oCtor(parent,L"fixture-parent",NULL,2,2,NULL);
 oCtor(self,L"root",parent,(seed%3)+1,2,&r);self->m_b58=seed&2;
 if(c.mode==0){if(seed%7==0)self->m_pRepository=NULL;typedef void(*Fn)(CDataGroup*,unsigned);Fn fn=ours?nName:oName;if(!autotest::beginInvocation(out,fn))return;fn(self,seed%4?seed%7:unsigned(-1));}
 else if(c.mode==1){for(unsigned i=0;i<seed%4;++i)self->AddDataValue(names[i],int(i));UNIONDATA64BIT value;value.signed64=(seed%4==0)?-1:(seed/3)%7;unsigned id=(seed%4==0)?unsigned(-1):seed%7;typedef CDataValue*(*Fn)(CDataGroup*,unsigned,UNIONDATA64BIT,CDataValue::EDATAVALUETYPES);Fn fn=ours?nUnion:oUnion;if(!autotest::beginInvocation(out,fn))return;CDataValue* result=fn(self,id,value,static_cast<CDataValue::EDATAVALUETYPES>(seed%10));number(result==self->m_DataValues[self->m_DataValues.size()-1]);}
 else if(c.mode==2){for(unsigned i=0;i<seed%4;++i)self->AddDataValue(names[i],int(i));std::wstring types[]={L"INTEGER",L"INTEGER64",L"FLOAT",L"DOUBLE",L"UNSIGNED INT",L"BOOL",L"TRANSLATE",L"DIALOG",L"STRING",L"UNKNOWN"};std::wstring values[]={L"0",L"-1",L"1.25",L"true",L"FALSE",L"9223372036854775807",L"Ж",L""};typedef CDataValue*(*Fn)(CDataGroup*,const std::wstring&,std::wstring,std::wstring);Fn fn=ours?nText:oText;if(!autotest::beginInvocation(out,fn))return;CDataValue* result=fn(self,names[seed%5],types[seed%10],values[(seed/3)%8]);number(result==self->m_DataValues[self->m_DataValues.size()-1]);}
 else {
    for(unsigned i=0;i<seed%4;++i){CDataGroup*child=self->AddDataGroup(names[i]);child->m_b58=true;if(i%2)child->AddDataGroup(L"leaf")->m_b58=true;}
    uint64_t fs[(sizeof(CFileSystem)+7)/8];filesystem=reinterpret_cast<CFileSystem*>(fs);receiver=self;
    std::string ownedText[3];std::wstring ownedPath;
    int previousReferences[4]={0,0,0,0};
    detour::Set d,destructorPatch;
    TL_REDIRECT(d,singleton,&getSingleton);TL_REDIRECT(d,fileInfo,&getInfo);TL_REDIRECT(d,savePair,&save);
    if(c.mode==4){
        faultStage=1+seed%2;
        for(unsigned i=0;i<3;++i)ownedText[i]=std::string(80+seed+i*13,char('a'+i));
        ownedPath=std::wstring(70+seed,L'p');
        narrowWitnesses=ownedText;pathWitness=&ownedPath;
        for(unsigned i=0;i<3;++i)previousReferences[i]=references(ownedText[i]);
        previousReferences[3]=references(ownedPath);
        styleDtorPatch=&destructorPatch;TL_REDIRECT(destructorPatch,pairDtor,&destroyedStyle);
    }
    if(d.failed()||destructorPatch.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    typedef int(*Fn)(CDataGroup*,const std::wstring&);Fn fn=ours?nSave:oSave;
    bool dirtyBefore=self->m_b58;
    if(!autotest::beginInvocation(out,fn))return;
    unsigned thrown=0;
    try{int result=fn(self,names[seed%5]);out.add(&result,4);}
    catch(const SaveFailure& failure){thrown=failure.stage;}
    catch(...){out.issue=autotest::Capture::InvalidReport;return;}
    out.callCompleted=1;number(thrown);number(infoCalls);number(saveCalls);
    if(c.mode==4){
        number(styleDestructions);
        if(thrown!=faultStage||styleDestructions!=1||infoCalls!=1||saveCalls!=(faultStage==2?1u:0u))
            out.issue=autotest::Capture::InvalidReport;
        for(unsigned i=0;i<3;++i){int refs=references(ownedText[i]);out.add(&refs,4);if(refs!=previousReferences[i])out.issue=autotest::Capture::InvalidReport;}
        int refs=references(ownedPath);out.add(&refs,4);if(refs!=previousReferences[3])out.issue=autotest::Capture::InvalidReport;
        // setDirty(false) follows successful style saving. Both failure sites
        // must leave the complete group's dirty flags at their input values.
        if(self->m_b58!=dirtyBefore)out.issue=autotest::Capture::InvalidReport;
        for(unsigned i=0;i<self->m_DataGroups.size();++i){CDataGroup* child=self->m_DataGroups[i];if(!child->m_b58)out.issue=autotest::Capture::InvalidReport;for(unsigned j=0;j<child->m_DataGroups.size();++j)if(!child->m_DataGroups[j]->m_b58)out.issue=autotest::Capture::InvalidReport;}
    }else if(thrown)out.issue=autotest::Capture::InvalidReport;
    narrowWitnesses=NULL;pathWitness=NULL;
 }
 out.callCompleted=1;state(self);repository(r);self->m_pRepository=&r;TSafePointer<CDataGroup> ref;ref.setObject(self);oDtor(self);number(ref.getObject()==NULL);if(ref.getObject())out.issue=autotest::Capture::InvalidReport;repository(r);oDtor(parent);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*n,uintptr_t addr){autotest::Coverage coverage(n,addr);for(unsigned i=0;i<120;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(h,a,b)){h->log("    data group mode %u seed %u issue %u/%u exits %d/%d\n",mode,i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
#define TEST(name,mode,old) TL_TEST(name){return run(host,mode,#name,(uintptr_t)&old);}
TEST(bulk_data_group_name_id,0,oName)
TEST(bulk_data_group_save_path,3,oSave)

TEST(bulk_data_group_save_exceptions,4,oSave)
