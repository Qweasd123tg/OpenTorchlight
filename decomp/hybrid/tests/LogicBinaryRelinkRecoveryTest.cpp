#include <Ogre.h>
#include <cstring>
#include <vector>
#include <map>
#include <climits>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "LogicObject.h"
#include "LogicGroup.h"
#include "LogicLink.h"
#include "LogicWrapper.h"
#include "Descriptor.h"
#include "DescriptorLoadConfiguration.h"
#include "OgreReader.h"
#undef protected
#undef private
#include "UTFConversion.h"

TL_ORIGINAL(void, relinkOriginal,(CLogicObject*,CLogicGroup*,COgreReader*,CDescriptorLoadConfiguration*,std::map<int,int>&),"_ZN12CLogicObject35loadAndRelinkObjectInFromBinaryFileEP11CLogicGroupP11COgreReaderP28CDescriptorLoadConfigurationRSt3mapIiiSt4lessIiESaISt4pairIKiiEEE")
extern "C" void relinkCandidate(CLogicObject*,CLogicGroup*,COgreReader*,CDescriptorLoadConfiguration*,std::map<int,int>&) __asm__("_ZN12CLogicObject35loadAndRelinkObjectInFromBinaryFileEP11CLogicGroupP11COgreReaderP28CDescriptorLoadConfigurationRSt3mapIiiSt4lessIiESaISt4pairIKiiEEE");
TL_ORIGINAL(void, relinkObjectCtor,(CLogicObject*,CEditorScene*,long long,unsigned),"_ZN12CLogicObjectC1EP12CEditorScenexj")
TL_ORIGINAL(void, relinkObjectDtor,(CLogicObject*),"_ZN12CLogicObjectD1Ev")
TL_ORIGINAL(void, relinkReadOriginal,(COgreReader*,void*,unsigned),"_ZN11COgreReader4readEPvj")
TL_ORIGINAL(CLogicObject*, relinkGroupOriginal,(CLogicGroup*,unsigned),"_ZN11CLogicGroup21GetLogicObjectByIndexEj")
TL_ORIGINAL(unsigned, relinkOutputIndexOriginal,(CDescriptor*,std::wstring),"_ZN11CDescriptor26GetOutputLogicWrapperIndexESbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(unsigned, relinkInputIndexOriginal,(CDescriptor*,std::wstring),"_ZN11CDescriptor25GetInputLogicWrapperIndexESbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(CLogicWrapper*, relinkOutputOriginal,(CDescriptor*,unsigned),"_ZN11CDescriptor21GetOutputLogicWrapperEj")
TL_ORIGINAL(CLogicWrapper*, relinkInputOriginal,(CDescriptor*,unsigned),"_ZN11CDescriptor20GetInputLogicWrapperEj")
TL_ORIGINAL(unsigned, relinkAddOriginal,(CLogicObject*,CLogicWrapper*,CLogicObject*,CLogicWrapper*),"_ZN12CLogicObject12AddLogicLinkEP13CLogicWrapperPS_S1_")
TL_FUNCTION(relinkRead,"_ZN11COgreReader4readEPvj")
TL_FUNCTION(relinkGroup,"_ZN11CLogicGroup21GetLogicObjectByIndexEj")
TL_FUNCTION(relinkOutputIndex,"_ZN11CDescriptor26GetOutputLogicWrapperIndexESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(relinkInputIndex,"_ZN11CDescriptor25GetInputLogicWrapperIndexESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(relinkOutput,"_ZN11CDescriptor21GetOutputLogicWrapperEj")
TL_FUNCTION(relinkInput,"_ZN11CDescriptor20GetInputLogicWrapperEj")
TL_FUNCTION(relinkAdd,"_ZN12CLogicObject12AddLogicLinkEP13CLogicWrapperPS_S1_")

namespace {
struct Case {unsigned seed;bool observed,negative;};
struct Descriptor:CDescriptor {Descriptor():CDescriptor(0){} CEditorBaseObject* CreateObject(CEditorScene*){return NULL;}};
const Case* current;autotest::Capture* output;CLogicObject* self;CLogicObject* nodes[6];
CDescriptor* descriptors[4];std::map<int,int>* remaps;unsigned readCalls,groupCalls,outputIndexCalls,inputIndexCalls,addCalls;
detour::Set readHook,groupHook,outputIndexHook,inputIndexHook,outputHook,inputHook,addHook;
std::vector<CLogicWrapper*> originalOutputs[4],originalInputs[4];
void number(long long value){output->add(&value,sizeof value);}
unsigned descriptorID(CDescriptor* p){if(!p)return 98;for(unsigned i=0;i<4;++i)if(p==descriptors[i])return i;return 99;}
unsigned nodeID(CLogicObject* p){if(!p)return 98;for(unsigned i=0;i<6;++i)if(p==nodes[i])return i;return 99;}
void wrapper(CLogicWrapper* p){number(p!=NULL);if(!p)return;number(descriptorID(p->m_pDescriptor));number(p->m_iID);output->addText(p->m_sName);}
void checkHooks(){if(readHook.failed()||groupHook.failed()||outputIndexHook.failed()||inputIndexHook.failed()||outputHook.failed()||inputHook.failed()||addHook.failed())output->issue=autotest::Capture::InvalidReport;}

void read(COgreReader* reader,void* data,unsigned size)
{
    number(1);number(reader->m_iPosition);number(size);++readCalls;
    if(size>256){output->issue=autotest::Capture::InvalidReport;return;}
    output->add(data,size);
    readHook.restore();relinkReadOriginal(reader,data,size);TL_REDIRECT(readHook,relinkRead,&read);checkHooks();
    output->add(data,size);number(reader->m_iPosition);
    if(current->seed%10==1&&readCalls==4)(*remaps)[10]=2;
}
CLogicObject* group(CLogicGroup* p,unsigned index)
{
    number(2);number(index);++groupCalls;groupHook.restore();CLogicObject* result=relinkGroupOriginal(p,index);TL_REDIRECT(groupHook,relinkGroup,&group);checkHooks();number(nodeID(result));
    if(current->seed%10==2&&groupCalls==1)self->m_pLinkedDescriptor=descriptors[1];
    return result;
}
unsigned outputIndex(CDescriptor* p,std::wstring name)
{
    number(3);number(descriptorID(p));output->addText(name);++outputIndexCalls;
    outputIndexHook.restore();unsigned result=relinkOutputIndexOriginal(p,name);TL_REDIRECT(outputIndexHook,relinkOutputIndex,&outputIndex);checkHooks();number(result);
    if(current->seed%10==3&&outputIndexCalls==1)self->m_pLinkedDescriptor=descriptors[1];
    if(current->seed%10==6&&result!=~0u)p->m_OutputLogicWrappers[result]=NULL;
    return result;
}
unsigned inputIndex(CDescriptor* p,std::wstring name)
{
    number(4);number(descriptorID(p));output->addText(name);++inputIndexCalls;
    inputIndexHook.restore();unsigned result=relinkInputIndexOriginal(p,name);TL_REDIRECT(inputIndexHook,relinkInputIndex,&inputIndex);checkHooks();number(result);
    if(current->seed%10==4&&inputIndexCalls==1)for(unsigned i=1;i<6;++i)if(nodes[i])nodes[i]->m_pLinkedDescriptor=descriptors[3];
    if(current->seed%10==7&&result!=~0u)p->m_InputLogicWrappers[result]=NULL;
    return result;
}
CLogicWrapper* getOutput(CDescriptor* p,unsigned index)
{
    number(5);number(descriptorID(p));number(index);outputHook.restore();CLogicWrapper* result=relinkOutputOriginal(p,index);TL_REDIRECT(outputHook,relinkOutput,&getOutput);checkHooks();wrapper(result);if(current->seed%10==6)p->m_OutputLogicWrappers[index]=originalOutputs[descriptorID(p)][index];return result;
}
CLogicWrapper* getInput(CDescriptor* p,unsigned index)
{
    number(6);number(descriptorID(p));number(index);inputHook.restore();CLogicWrapper* result=relinkInputOriginal(p,index);TL_REDIRECT(inputHook,relinkInput,&getInput);checkHooks();wrapper(result);if(current->seed%10==7)p->m_InputLogicWrappers[index]=originalInputs[descriptorID(p)][index];return result;
}
unsigned add(CLogicObject* p,CLogicWrapper* from,CLogicObject* destination,CLogicWrapper* to)
{
    number(7);number(nodeID(p));wrapper(from);number(nodeID(destination));wrapper(to);++addCalls;
    addHook.restore();unsigned result=relinkAddOriginal(p,from,destination,to);TL_REDIRECT(addHook,relinkAdd,&add);checkHooks();number(result);
    if(current->seed%10==5&&addCalls==1){(*remaps)[11]=1;self->m_pLinkedDescriptor=NULL;}
    return result;
}

void append(std::vector<char>& bytes,const void* p,unsigned count){const char* s=static_cast<const char*>(p);bytes.insert(bytes.end(),s,s+count);}
void integer(std::vector<char>& bytes,int value){append(bytes,&value,4);}
void text(std::vector<char>& bytes,const std::wstring& value){utf16string encoded=UTF32ToUTF16(value);integer(bytes,encoded.size());append(bytes,encoded.data(),encoded.size()*2);}
CLogicObject* makeNode(unsigned id){CLogicObject* p=static_cast<CLogicObject*>(Ogre::NedAllocImpl::allocBytes(sizeof(CLogicObject),0,0,0));relinkObjectCtor(p,NULL,-1,id);return p;}
void mapState(const std::map<int,int>& m){number(m.size());for(std::map<int,int>::const_iterator i=m.begin();i!=m.end();++i){number(i->first);number(i->second);}}

void side(void* argument,autotest::Capture& out,bool ours)
{
    current=static_cast<Case*>(argument);output=&out;readCalls=groupCalls=outputIndexCalls=inputIndexCalls=addCalls=0;
    int before=g_iTotalCountOfObjects;
    {
        Descriptor outputDescriptor,alternateOutput,inputDescriptor,alternateInput;
        CDescriptor* ds[]={&outputDescriptor,&alternateOutput,&inputDescriptor,&alternateInput};for(unsigned i=0;i<4;++i)descriptors[i]=ds[i];
        const std::wstring names[]={L"",L"OUT",L"SECOND",L"\u03a9\u4e2d\u0416",std::wstring(63,L'X'),std::wstring(L"A\0B",3),L"\U0001f642"};
        for(unsigned d=0;d<4;++d){originalOutputs[d].clear();originalInputs[d].clear();for(unsigned n=0;n<7;++n){ds[d]->AddOutputLogic(names[n],100*d+n);ds[d]->AddInputLogic(names[n],100*d+n+50);}for(unsigned n=0;n<ds[d]->m_OutputLogicWrappers.size();++n)originalOutputs[d].push_back(ds[d]->m_OutputLogicWrappers[n]);for(unsigned n=0;n<ds[d]->m_InputLogicWrappers.size();++n)originalInputs[d].push_back(ds[d]->m_InputLogicWrappers[n]);}
        CLogicGroup graph(NULL);for(unsigned i=0;i<6;++i){nodes[i]=i==3?NULL:makeNode(1000+i);graph.m_logicObjects.add(nodes[i]);if(nodes[i])nodes[i]->m_pLinkedDescriptor=i==4?NULL:i==0?ds[0]:ds[2];}
        self=nodes[0];if(current->seed%11==0)self->m_pLinkedDescriptor=NULL;
        self->m_fLeft=-13.5f;self->m_fTop=7.25f;self->m_fRight=99;self->m_fBottom=101;
        for(unsigned i=0;i<current->seed%4;++i)relinkAddOriginal(self,originalOutputs[0][1],nodes[1],originalInputs[2][1]);
        if(current->seed%6==0)self->m_Links.add(NULL);
        std::map<int,int> ids;remaps=&ids;ids[0]=1;ids[10]=1;ids[11]=2;ids[12]=3;ids[13]=4;ids[14]=99;ids[15]=-1;ids[16]=0;ids[-1]=2;ids[INT_MIN]=1;ids[INT_MAX]=4;
        unsigned seed=current->seed,count=seed%13;std::vector<char> bytes;integer(bytes,count);
        const int targets[]={10,11,12,13,14,15,16,17,-1,INT_MIN,INT_MAX,0};
        for(unsigned i=0;i<count;++i){integer(bytes,targets[(seed/13+i)%12]);unsigned n=(seed/156+i)%8;text(bytes,n==7?L"missing":names[n]);unsigned inputName=(seed/39+i*3)%8;text(bytes,inputName==7?L"missing":names[inputName]);}
        // Truncate only exactly at read boundaries: native read() checks EOF,
        // while a partial read beyond EOF is outside its valid ABI contract.
        if(seed%31==0)bytes.clear();
        else if(seed%31==1){bytes.resize(4);int n=3;std::memcpy(&bytes[0],&n,4);}
        else if(seed%31==2){bytes.clear();integer(bytes,1);integer(bytes,10);text(bytes,L"OUT");}
        else if(seed%31==3){bytes.clear();integer(bytes,1);integer(bytes,10);text(bytes,L"OUT");integer(bytes,6);}
        COgreReader reader;Ogre::DataStreamPtr stream(new Ogre::MemoryDataStream(bytes.empty()?NULL:&bytes[0],bytes.size(),false));reader.ReadFile(stream);
        CDescriptorLoadConfiguration configuration;configuration.m_iVersion=37;configuration.m_Remaps[71]=91;
        std::memset(m_gStringTEMP,0x5a,sizeof m_gStringTEMP);std::memset(m_gStringTEMP1,0x6b,sizeof m_gStringTEMP1);
        unsigned oldCount=self->m_Links.size();number(oldCount);number(bytes.size());mapState(ids);
        if(current->observed){TL_REDIRECT(readHook,relinkRead,&read);TL_REDIRECT(groupHook,relinkGroup,&group);TL_REDIRECT(outputIndexHook,relinkOutputIndex,&outputIndex);TL_REDIRECT(inputIndexHook,relinkInputIndex,&inputIndex);TL_REDIRECT(outputHook,relinkOutput,&getOutput);TL_REDIRECT(inputHook,relinkInput,&getInput);TL_REDIRECT(addHook,relinkAdd,&add);checkHooks();}
        if(out.issue)return;
        autotest::invoke(out,ours?relinkCandidate:relinkOriginal,self,&graph,&reader,seed&1?&configuration:NULL,ids);
        if(ours&&current->negative)self->m_iID+=123;
        number(reader.m_iPosition);number(reader.m_iSize);number(readCalls);number(groupCalls);number(outputIndexCalls);number(inputIndexCalls);number(addCalls);mapState(ids);
        number(configuration.m_iVersion);number(configuration.m_Remaps.size());number(configuration.m_Remaps[71]);
        number(self->m_iID);out.add(&self->m_fLeft,16);number(self->m_Links.size());number(descriptorID(self->m_pLinkedDescriptor));
        for(unsigned i=0;i<self->m_Links.size();++i){CLogicLink* link=self->m_Links[i];number(link!=NULL);if(link){number(nodeID(link->m_pInitiatingLogicObject));number(nodeID(link->m_pLinkingToLogicObject));number(descriptorID(link->m_pLinkingToDescriptor));number(link->m_pEditorScene==NULL);wrapper(link->m_pOutputLogicWrapper);wrapper(link->m_pInputLogicWrapper);}}
        for(unsigned i=0;i<6;++i)if(nodes[i])number(descriptorID(nodes[i]->m_pLinkedDescriptor));
        out.add(m_gStringTEMP,sizeof m_gStringTEMP);out.add(m_gStringTEMP1,sizeof m_gStringTEMP1);
        readHook.restore();groupHook.restore();outputIndexHook.restore();inputIndexHook.restore();outputHook.restore();inputHook.restore();addHook.restore();
        for(unsigned d=0;d<4;++d){for(unsigned i=0;i<originalOutputs[d].size();++i)ds[d]->m_OutputLogicWrappers[i]=originalOutputs[d][i];for(unsigned i=0;i<originalInputs[d].size();++i)ds[d]->m_InputLogicWrappers[i]=originalInputs[d][i];}
        graph.m_logicObjects.clear();for(unsigned i=0;i<6;++i)if(nodes[i]){relinkObjectDtor(nodes[i]);Ogre::NedAllocImpl::deallocBytes(nodes[i]);nodes[i]=NULL;}
    }
    number(g_iTotalCountOfObjects-before);
}
void original(void* p,autotest::Capture&out){side(p,out,false);}void candidate(void* p,autotest::Capture&out){side(p,out,true);}
int run(const tlhybrid_host* host,bool observed)
{
    const char* label=observed?"logic_binary_relink_observed":"logic_binary_relink_native";autotest::Coverage coverage(label,0x7b1ba0);
    for(unsigned i=0;i<1248;++i){Case c={i,observed,false};autotest::Outcome a,b;autotest::runChild(original,&c,a,2000,10000);autotest::runChild(candidate,&c,b,2000,10000);if(coverage.observe(host,a,b)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    relink observed%u seed%u status%d/%d issue%u/%u bytes%lu/%lu first%lu\n",observed,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);coverage.report(host);return 1;}}
    coverage.report(host);Case c={38,observed,true};autotest::Outcome a,b;autotest::runChild(original,&c,a,2000,10000);autotest::runChild(candidate,&c,b,2000,10000);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);host->log("    relink negative observed%u detected%u\n",observed,detected?1:0);return !detected||!a.reportValid||!b.reportValid||a.childStatus||b.childStatus||autotest::incomplete(a)||autotest::incomplete(b);
}
}
TL_TEST(logic_binary_relink_native){return run(host,false);}
TL_TEST(logic_binary_relink_observed){return run(host,true);}
