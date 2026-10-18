#include <cstring>
#include <string>
#include <map>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "LogicObject.h"
#include "LogicGroup.h"
#include "LogicLink.h"
#include "Descriptor.h"
#include "LogicWrapper.h"
#undef private
TL_ORIGINAL(void,loOldSave,(CLogicObject*,CDataGroup*),"_ZN12CLogicObject26saveLogicObjectToDataGroupEP10CDataGroup")
extern "C" void loNewSave(CLogicObject*,CDataGroup*) __asm__("_ZN12CLogicObject26saveLogicObjectToDataGroupEP10CDataGroup");
TL_ORIGINAL(void,loOldLoad,(CLogicObject*,CLogicGroup*,CDataGroup*,CDescriptorLoadConfiguration*,std::map<int,int>*),"_ZN12CLogicObject26loadLogicObjectByDataGroupEP11CLogicGroupP10CDataGroupP28CDescriptorLoadConfigurationPSt3mapIiiSt4lessIiESaISt4pairIKiiEEE")
extern "C" void loNewLoad(CLogicObject*,CLogicGroup*,CDataGroup*,CDescriptorLoadConfiguration*,std::map<int,int>*) __asm__("_ZN12CLogicObject26loadLogicObjectByDataGroupEP11CLogicGroupP10CDataGroupP28CDescriptorLoadConfigurationPSt3mapIiiSt4lessIiESaISt4pairIKiiEEE");
TL_FUNCTION(loGet,"_ZN12CLogicObject9GetObjectEv")
namespace {
struct Descriptor: CDescriptor { Descriptor():CDescriptor(0){} CEditorBaseObject* CreateObject(CEditorScene*){return NULL;} };
struct Case {unsigned mode,seed;};
autotest::Capture* cap;CEditorBaseObject* object;unsigned gets;
void n(unsigned x){cap->add(&x,4);}void bad(){cap->issue=autotest::Capture::InvalidReport;}
CEditorBaseObject* get(CLogicObject*){++gets;return object;}
void tree(CDataGroup* p){cap->addText(p->GetGroupName());n(p->m_DataValues.size());for(unsigned i=0;i<p->m_DataValues.size();++i){CDataValue*v=p->m_DataValues[i];cap->addText(v->GetDataValueName());n(v->GetValueType());cap->addText(v->GetValueAsString());}n(p->m_DataGroups.size());for(unsigned i=0;i<p->m_DataGroups.size();++i)tree(p->m_DataGroups[i]);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;gets=0;int before=g_iTotalCountOfObjects;
 {Descriptor outputDesc,inputDesc;outputDesc.AddOutputLogic(L"OUT",7);outputDesc.AddOutputLogic(L"SECOND",9);inputDesc.AddInputLogic(L"IN",3);inputDesc.AddInputLogic(L"OTHER",4);CEditorBaseObject real;real.setGuid(0x123456789LL+c.seed);real.setOriginalGuid(-1000-c.seed);object=c.seed%3?&real:NULL;
 CLogicGroup group(NULL);CLogicObject*self=new CLogicObject(NULL,-1,0x80000000u+c.seed);self->m_pLinkedDescriptor=&outputDesc;self->m_fLeft=-19.25f*c.seed;self->m_fTop=3.5f*c.seed;self->m_fRight=1000+c.seed;self->m_fBottom=2000+c.seed;group.m_logicObjects.add(self);
 for(unsigned i=1;i<5;++i){CLogicObject*p=new CLogicObject(NULL,-1,i);p->m_pLinkedDescriptor=i==3?NULL:&inputDesc;group.m_logicObjects.add(p);}std::map<int,int> ids;ids[10]=1;ids[11]=2;ids[12]=3;ids[13]=4;ids[14]=99;ids[-1]=2;
 CDataGroup data(c.mode==0?L"container":c.seed%13==0?L"WRONG":L"LOGICOBJECT",NULL,2,2,NULL);data.AddDataValue(L"untouched",17);for(unsigned i=0;i<c.seed%4;++i)self->AddLogicLink(outputDesc.GetOutputLogicWrapper(i%2),group.m_logicObjects[1+i%2],inputDesc.GetInputLogicWrapper(i%2));if(c.seed&1)self->m_Links.add(NULL);
 if(c.mode==1){if(c.seed&1)data.AddDataValue(L"X",-12.5f*c.seed);if(c.seed&2)data.AddDataValue(L"Y",100.25f+c.seed);for(unsigned i=0;i<c.seed%11;++i){CDataGroup*link=data.AddDataGroup(i==9?L"OTHER":L"LOGICLINK");if(i!=8)link->AddDataValue(L"LINKINGTO",unsigned(10+i%6));link->AddDataValue(L"OUTPUTNAME",i%5==0?L"":i%5==1?L"missing":i%5==2?L"SECOND":L"OUT",false);link->AddDataValue(L"INPUTNAME",i%4==0?L"":i%4==1?L"missing":i%4==2?L"OTHER":L"IN",false);}}
 unsigned oldCount=self->m_Links.size();std::map<int,int> oldIDs=ids;
 {detour::Set patches;if(c.mode==0){TL_REDIRECT(patches,loGet,&get);}if(patches.failed()){std::fprintf(stderr,"patch failed\n");bad();return;}
 if(c.mode==0){typedef void(*Fn)(CLogicObject*,CDataGroup*);Fn fn=ours?loNewSave:loOldSave;if(!autotest::beginInvocation(out,fn))return;fn(self,c.seed%17?&data:NULL);out.callCompleted=1;}
 else{typedef void(*Fn)(CLogicObject*,CLogicGroup*,CDataGroup*,CDescriptorLoadConfiguration*,std::map<int,int>*);Fn fn=ours?loNewLoad:loOldLoad;if(!autotest::beginInvocation(out,fn))return;fn(self,c.seed%17?&group:NULL,c.seed%19?&data:NULL,NULL,&ids);out.callCompleted=1;}
 n(gets);}
 tree(&data);out.add(&self->m_fLeft,16);n(self->m_Links.size());n(oldCount);if(ids!=oldIDs){std::fprintf(stderr,"ids changed\n");bad();}n(ids.size());for(std::map<int,int>::iterator i=ids.begin();i!=ids.end();++i){out.add(&i->first,4);out.add(&i->second,4);}
 for(unsigned i=0;i<self->m_Links.size();++i){CLogicLink*p=self->m_Links[i];n(p!=NULL);if(!p)continue;n(p->m_pInitiatingLogicObject==self);n(p->m_pLinkingToLogicObject->m_iID);n(p->m_pEditorScene==NULL);cap->addText(p->m_pInputLogicWrapper->m_sName);cap->addText(p->m_pOutputLogicWrapper->m_sName);}
 }n(g_iTotalCountOfObjects-before);}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*name,uintptr_t addr){autotest::Coverage coverage(name,addr);for(unsigned i=0;i<100;++i){Case c={mode,i};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){h->log("    logic object mode%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",mode,i,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(deepen_editor_logic_object_save){return run(host,0,"deepen_editor_logic_object_save",(uintptr_t)&loOldSave);}
TL_TEST(deepen_editor_logic_object_load){return run(host,1,"deepen_editor_logic_object_load",(uintptr_t)&loOldLoad);}
