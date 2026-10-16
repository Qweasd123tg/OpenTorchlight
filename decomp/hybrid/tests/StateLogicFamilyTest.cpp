#include "AutoTest.h"
#include "Detour.h"
#include "LogicObject.h"
#include "LogicGroup.h"
#include "LogicLink.h"
#include "LogicWrapper.h"
#include "Descriptor.h"
#include "DescriptorLoadConfiguration.h"
#include "OgreReader.h"
#include <fstream>
#include <limits>
struct SmallmatchPass7Probe {
 static void stateLogicBounds(CLogicObject& o,float left,float top,float right,float bottom){o.m_fLeft=left;o.m_fTop=top;o.m_fRight=right;o.m_fBottom=bottom;}
 static void stateLogicCapture(CLogicObject& o,autotest::Capture& c){c.add(&o.m_fLeft,16);c.add(&o.m_iID,4);c.add(&o.m_iObjectID,8);unsigned n=o.m_Links.size();c.add(&n,4);}
 static void stateLogicDescriptor(CLogicObject& o,CDescriptor* d){o.m_pLinkedDescriptor=d;}
 static TArrayList<CLogicLink*>& stateLogicLinks(CLogicObject& o){return o.m_Links;}
};

namespace {
struct Case { unsigned op, index; };
typedef void(*Side)(void*,autotest::Capture&);
int runCases(const tlhybrid_host* host,unsigned op,unsigned count,const char* name,uint64_t address,Side original,Side candidate)
{
    autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<count;++i) {
        Case c={op,i};autotest::Outcome& a=autotest::g_outcomes[0];autotest::Outcome& b=autotest::g_outcomes[1];
        autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        if(coverage.observe(host,a,b)) {
            host->log("    %s case %u original status %d issue %u started %u completed %u; candidate status %d issue %u started %u completed %u\n",name,i,a.childStatus,a.capture.issue,a.capture.callStarted,a.capture.callCompleted,b.childStatus,b.capture.issue,b.capture.callStarted,b.capture.callCompleted);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);return coverage.completed!=count || coverage.different || coverage.missing;
}
}
TL_ORIGINAL(void, old7a7f70, (CLogicObject*, int, int), "_ZN12CLogicObject7SetSizeEii")
extern "C" void new7a7f70(CLogicObject*, int, int) __asm__("_ZN12CLogicObject7SetSizeEii");
TL_ORIGINAL(void, old7a7fa0, (CLogicObject*, std::ofstream*), "_ZN12CLogicObject32saveLogicObjectLinksToBinaryFileEPSt14basic_ofstreamIcSt11char_traitsIcEE")
extern "C" void new7a7fa0(CLogicObject*, std::ofstream*) __asm__("_ZN12CLogicObject32saveLogicObjectLinksToBinaryFileEPSt14basic_ofstreamIcSt11char_traitsIcEE");
TL_ORIGINAL(unsigned, old7a80a0, (CLogicObject*, CLogicWrapper*, CLogicObject*, CLogicWrapper*), "_ZN12CLogicObject12AddLogicLinkEP13CLogicWrapperPS_S1_")
extern "C" unsigned new7a80a0(CLogicObject*, CLogicWrapper*, CLogicObject*, CLogicWrapper*) __asm__("_ZN12CLogicObject12AddLogicLinkEP13CLogicWrapperPS_S1_");
TL_ORIGINAL(unsigned, old7a8230, (CLogicObject*, unsigned, CLogicObject*, unsigned), "_ZN12CLogicObject12AddLogicLinkEjPS_j")
extern "C" unsigned new7a8230(CLogicObject*, unsigned, CLogicObject*, unsigned) __asm__("_ZN12CLogicObject12AddLogicLinkEjPS_j");
TL_ORIGINAL(void, old7a83c0, (CLogicObject*, CLogicGroup*, COgreReader*, CDescriptorLoadConfiguration*, std::map<int,int>&), "_ZN12CLogicObject27loadLogicObjectByBinaryFileEP11CLogicGroupP11COgreReaderP28CDescriptorLoadConfigurationRSt3mapIiiSt4lessIiESaISt4pairIKiiEEE")
extern "C" void new7a83c0(CLogicObject*, CLogicGroup*, COgreReader*, CDescriptorLoadConfiguration*, std::map<int,int>&) __asm__("_ZN12CLogicObject27loadLogicObjectByBinaryFileEP11CLogicGroupP11COgreReaderP28CDescriptorLoadConfigurationRSt3mapIiiSt4lessIiESaISt4pairIKiiEEE");
TL_FUNCTION(saveLink,"_ZN10CLogicLink26saveLogicLinksToBinaryFileEPSt14basic_ofstreamIcSt11char_traitsIcEE")
TL_FUNCTION(readerRead,"_ZN11COgreReader4readEPvj")
namespace {
struct Descriptor: CDescriptor {
 Descriptor():CDescriptor(0){}
 virtual CEditorBaseObject* CreateObject(CEditorScene*){return NULL;}
 void wrappers(CLogicWrapper* in,CLogicWrapper* out){m_InputLogicWrappers.add(in);m_OutputLogicWrappers.add(out);}
};
autotest::Capture* capture;CLogicLink* links[16];COgreReader* reader;unsigned readAt;unsigned char bytes[20];
void linkSave(CLogicLink* p,std::ofstream* stream){unsigned id=99;for(unsigned i=0;i<16;++i)if(p==links[i])id=i;capture->add(&id,4);if(id==99)capture->issue=autotest::Capture::InvalidReport;stream->write(reinterpret_cast<const char*>(&id),4);}
void read(COgreReader* p,void* buffer,unsigned size){bool valid=p==reader&&readAt+size<=sizeof(bytes);capture->add(&valid,1);capture->add(&size,4);if(!valid){capture->issue=autotest::Capture::InvalidReport;return;}std::memcpy(buffer,bytes+readAt,size);readAt+=size;}
void side(void* raw,autotest::Capture& out,bool ours)
{
 Case c=*static_cast<Case*>(raw);capture=&out;
 CLogicObject object(NULL,-1,c.index+100),other(NULL,-1,17);
 Descriptor descriptor,inputDescriptor;
 std::wstring name=L"wrapper";
 CLogicWrapper* input=new CLogicWrapper(&inputDescriptor,53,name);CLogicWrapper* output=new CLogicWrapper(&descriptor,47,name);
 descriptor.wrappers(NULL,output);inputDescriptor.wrappers(input,NULL);
 SmallmatchPass7Probe::stateLogicDescriptor(object,c.index%5==0?NULL:&descriptor);
 SmallmatchPass7Probe::stateLogicDescriptor(other,c.index%7==0?NULL:&inputDescriptor);
 if(c.op==0) {
  const int values[]={-2147483647,-100,-1,0,24,25,26,100,2147483647};
  SmallmatchPass7Probe::stateLogicBounds(object,float(int(c.index)-25),float(c.index)*0.125f,0,0);
  typedef void(*Fn)(CLogicObject*,int,int);Fn fn=ours?new7a7f70:old7a7f70;
  if(!autotest::beginInvocation(out,fn))return;fn(&object,values[c.index%9],values[c.index/9%9]);out.callCompleted=1;
 } else if(c.op==1) {
  for(unsigned i=0;i<16;++i)links[i]=NULL;
  for(unsigned i=0;i<c.index%15;++i){if((i+c.index)%3)links[i]=new CLogicLink(NULL,&object,output,&other,input);SmallmatchPass7Probe::stateLogicLinks(object).add(links[i]);}
  char path[]="/tmp/otl-state-logic-XXXXXX";int fd=mkstemp(path);if(fd<0){out.issue=autotest::Capture::InvalidReport;return;}close(fd);
  std::ofstream stream(path,std::ios::binary);
  detour::Set patches;TL_REDIRECT(patches,saveLink,&linkSave);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(CLogicObject*,std::ofstream*);Fn fn=ours?new7a7fa0:old7a7fa0;
  if(!autotest::beginInvocation(out,fn))return;fn(&object,&stream);out.callCompleted=1;stream.close();
  std::ifstream file(path,std::ios::binary);char data[128];file.read(data,sizeof(data));unsigned length=file.gcount();out.add(&length,4);out.add(data,length);file.close();unlink(path);
 } else if(c.op==2||c.op==3) {
  // Existing links exercise capacity growth and preserve the old insertion index.
  for(unsigned i=0;i<c.index%13;++i)SmallmatchPass7Probe::stateLogicLinks(object).add(NULL);
  unsigned result;
  if(c.op==2){typedef unsigned(*Fn)(CLogicObject*,CLogicWrapper*,CLogicObject*,CLogicWrapper*);Fn fn=ours?new7a80a0:old7a80a0;if(!autotest::beginInvocation(out,fn))return;result=fn(&object,c.index%4==0?NULL:output,c.index%4==1?NULL:&other,c.index%4==2?NULL:input);}
  else {typedef unsigned(*Fn)(CLogicObject*,unsigned,CLogicObject*,unsigned);Fn fn=ours?new7a8230:old7a8230;if(!autotest::beginInvocation(out,fn))return;result=fn(&object,c.index/3%3,c.index%4==0?NULL:&other,c.index/9%3);}
  out.callCompleted=1;out.add(&result,4);
  TArrayList<CLogicLink*>& list=SmallmatchPass7Probe::stateLogicLinks(object);
  for(unsigned i=0;i<list.size();++i){bool present=list[i]!=NULL;out.add(&present,1);if(present){CLogicLink* link=list[i];bool identities[]={link->m_pInitiatingLogicObject==&object,link->m_pLinkingToLogicObject==&other,link->m_pInputLogicWrapper==input,link->m_pOutputLogicWrapper==output,link->m_pEditorScene==NULL};out.add(identities,sizeof(identities));}}
 } else {
  COgreReader stream;reader=&stream;readAt=0;CLogicGroup group(NULL);CDescriptorLoadConfiguration configuration;
  int oldID=int(c.index)-20;long long id=0x100000003LL;float left=float(c.index)*0.25f,top=-float(c.index);
  std::memcpy(bytes,&oldID,4);std::memcpy(bytes+4,&id,8);std::memcpy(bytes+12,&left,4);std::memcpy(bytes+16,&top,4);
  if(c.index%3)configuration.addRemap(id,c.index%3==1?7:-1);
  std::map<int,int> remapped;remapped[oldID]=8;remapped[-999]=2;
  detour::Set patches;TL_REDIRECT(patches,readerRead,&read);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(CLogicObject*,CLogicGroup*,COgreReader*,CDescriptorLoadConfiguration*,std::map<int,int>&);Fn fn=ours?new7a83c0:old7a83c0;
  if(!autotest::beginInvocation(out,fn))return;fn(&object,c.index%5==0?NULL:&group,c.index%5==1?NULL:&stream,&configuration,remapped);out.callCompleted=1;
  out.add(&readAt,4);unsigned n=remapped.size();out.add(&n,4);for(std::map<int,int>::iterator i=remapped.begin();i!=remapped.end();++i){out.add(&i->first,4);out.add(&i->second,4);}
 }
 SmallmatchPass7Probe::stateLogicCapture(object,out);
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void candidate(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(state_logic_7a7f70) {return runCases(host,0,90,"state_logic_7a7f70",(uint64_t)(uintptr_t)old7a7f70,original,candidate);}
TL_TEST(state_logic_7a7fa0) {return runCases(host,1,90,"state_logic_7a7fa0",(uint64_t)(uintptr_t)old7a7fa0,original,candidate);}
TL_TEST(state_logic_7a80a0) {return runCases(host,2,90,"state_logic_7a80a0",(uint64_t)(uintptr_t)old7a80a0,original,candidate);}
TL_TEST(state_logic_7a8230) {return runCases(host,3,90,"state_logic_7a8230",(uint64_t)(uintptr_t)old7a8230,original,candidate);}
TL_TEST(state_logic_7a83c0) {return runCases(host,4,90,"state_logic_7a83c0",(uint64_t)(uintptr_t)old7a83c0,original,candidate);}
