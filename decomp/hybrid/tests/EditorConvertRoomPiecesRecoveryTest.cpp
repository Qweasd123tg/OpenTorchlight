#include <Ogre.h>
#include <cstring>
#include <vector>
#include <climits>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "DataGroup.h"
#include "DataValue.h"
#include "RoomPieceData.h"
#include "RoomPieceDataInformation.h"
#include "StringUtilities.h"
typedef CRoomPieceDataInformation::CRoomPieceCoreData Core;
TL_ORIGINAL(bool, convertOriginal,(CDataGroup*,TArrayList<Core*>&),"_Z17convertRoomPiecesP10CDataGroupR10TArrayListIPN25CRoomPieceDataInformation18CRoomPieceCoreDataEE")
extern "C" bool convertCandidate(CDataGroup*,TArrayList<Core*>&) __asm__("_Z17convertRoomPiecesP10CDataGroupR10TArrayListIPN25CRoomPieceDataInformation18CRoomPieceCoreDataEE");
TL_ORIGINAL(const std::wstring&, convertGetOriginal,(CDataGroup*,const std::wstring&,const std::wstring&),"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_ORIGINAL(bool, convertSetOriginal,(CDataGroup*,const std::wstring&,const wchar_t*,bool),"_ZN10CDataGroup12SetDataValueERKSbIwSt11char_traitsIwESaIwEEPKwb")
TL_ORIGINAL(Core*, convertLookupOriginal,(CRoomPieceDataInformation*,long long),"_ZN25CRoomPieceDataInformation27_GetRoomPieceCoreDataByGuidEx")
TL_FUNCTION(convertGet,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(convertSet,"_ZN10CDataGroup12SetDataValueERKSbIwSt11char_traitsIwESaIwEEPKwb")
TL_FUNCTION(convertLookup,"_ZN25CRoomPieceDataInformation27_GetRoomPieceCoreDataByGuidEx")
extern CRoomPieceDataInformation* m_gRoomPieceInformation;
namespace {
struct Case{unsigned seed;bool observed,negative;};
const Case* current;autotest::Capture* output;CDataGroup* root;CRoomPieceDataInformation* catalog;
std::vector<CDataGroup*> groups;std::vector<Core*> oldPieces,newPieces;TArrayList<Core*>* selected;
detour::Set getHook,setHook,lookupHook;unsigned gets,sets,lookups;bool appended;
void number(long long value){output->add(&value,sizeof value);}
unsigned groupID(CDataGroup* p){if(!p)return 998;for(unsigned i=0;i<groups.size();++i)if(p==groups[i])return i;return 999;}
unsigned coreID(Core* p){if(!p)return 998;for(unsigned i=0;i<oldPieces.size();++i)if(p==oldPieces[i])return i;for(unsigned i=0;i<newPieces.size();++i)if(p==newPieces[i])return 100+i;return 999;}
CDataGroup* child(CDataGroup* p,const wchar_t* descriptor,const wchar_t* guid){CDataGroup* n=p->AddDataGroup(L"OBJECT");groups.push_back(n);n->AddDataValue(L"KEEP",17);if(descriptor)n->AddDataValue(L"DESCRIPTOR",descriptor,false);if(guid)n->AddDataValue(L"GUID",guid,false);return n;}
void hookState(){if(getHook.failed()||setHook.failed()||lookupHook.failed())output->issue=autotest::Capture::InvalidReport;}
const std::wstring& get(CDataGroup* p,const std::wstring& key,const std::wstring& fallback)
{
    number(1);number(groupID(p));output->addText(key);output->addText(fallback);++gets;
    getHook.restore();const std::wstring& value=convertGetOriginal(p,key,fallback);TL_REDIRECT(getHook,convertGet,&get);hookState();output->addText(value);
    if(current->seed%9==1&&!appended&&key==L"DESCRIPTOR"){appended=true;child(root,L"Room Piece",L"11");}
    return value;
}
Core* lookup(CRoomPieceDataInformation* p,long long guid)
{
    number(2);number(p==catalog);number(guid);++lookups;
    lookupHook.restore();Core* result=convertLookupOriginal(p,guid);TL_REDIRECT(lookupHook,convertLookup,&lookup);hookState();number(coreID(result));
    if(current->seed%9==2&&lookups==1&&result)result->m_name=L"changed after lookup";
    return result;
}
bool set(CDataGroup* p,const std::wstring& key,const wchar_t* value,bool translate)
{
    number(3);number(groupID(p));output->addText(key);output->addText(std::wstring(value));number(translate);++sets;
    setHook.restore();bool result=convertSetOriginal(p,key,value,translate);TL_REDIRECT(setHook,convertSet,&set);hookState();number(result);
    if(current->seed%9==3&&sets==1)selected->add(newPieces.back());
    if(current->seed%9==4&&sets==1&&!appended){appended=true;child(p,L"Room Piece",L"12");}
    return result;
}
Core* makeCore(const std::wstring& name,long long guid){Core* p=new Core;p->m_name=name;p->m_guid=guid;p->m_queryMask=16;p->m_postRender=false;p->m_preRender=false;p->m_automapLayer=0;p->m_scalable=true;p->m_fixedVariation=false;p->m_snapRotation.add(90.0f);p->m_visualMeshFiles.add(L"fixture.mesh");return p;}
void tree(CDataGroup* p)
{
    number(p!=NULL);if(!p)return;number(groupID(p));output->addText(p->GetGroupName());number(p->GetNumberOfDataValues());
    for(unsigned i=0;i<p->GetNumberOfDataValues();++i){CDataValue* value=p->GetDataValue(i);output->addText(value->GetDataValueName());number(value->GetValueType());output->addText(value->GetValueAsString());}
    number(p->GetNumberOfDataGroups());for(unsigned i=0;i<p->GetNumberOfDataGroups();++i)tree(p->GetDataGroup(i));
}
void nested(CDataGroup* parent,unsigned depth,unsigned ordinal)
{
    if(!depth)return;
    CDataGroup* a=child(parent,L"Other",NULL);child(a,L"Room Piece",ordinal&1?L"10":L"11");nested(a,depth-1,ordinal+1);
}
void side(void* argument,autotest::Capture& out,bool ours)
{
    current=static_cast<Case*>(argument);output=&out;groups.clear();oldPieces.clear();newPieces.clear();gets=sets=lookups=0;appended=false;
    CRoomPieceDataInformation* previous=m_gRoomPieceInformation;int before=g_iTotalCountOfObjects;
    {
        CRoomPieceDataInformation information(NULL);catalog=&information;information.m_pDefaultRoomPieceCoreData=NULL;
        const std::wstring names[]={L"Alpha",L"Beta",L"Alpha",L"\u03a9\u4e2d",L"alpha",std::wstring(L"A\0B",3),L"",std::wstring(160,L'X')};
        const long long ids[]={10,11,12,13,14,15,0,(-9223372036854775807LL-1)};
        for(unsigned i=0;i<8;++i){Core* p=makeCore(names[i],ids[i]);oldPieces.push_back(p);information.m_RoomPieceCoreDataByGuid[ids[i]]=p;}
        Core* same=makeCore(L"Alpha",110);oldPieces.push_back(same);information.m_RoomPieceCoreDataByGuid[110]=same;
        if(current->seed/24%3==1)information.m_pDefaultRoomPieceCoreData=oldPieces[1];
        const unsigned order[]={1,0,2,3,4,5,6,7};
        for(unsigned i=0;i<8;++i)newPieces.push_back(makeCore(names[order[i]],i==0?111:i==1?110:i==2?999:i==3?(-9223372036854775807LL-1):i==4?9223372036854775807LL:i==5?0:i==6?-1:888));
        TArrayList<Core*> replacements(2);selected=&replacements;unsigned mode=current->seed/72%5;
        if(mode!=0)for(unsigned i=0;i<8;++i)if(mode!=2||i>2)replacements.add(newPieces[i]);
        if(mode==3){replacements.clear();replacements.add(newPieces[2]);replacements.add(newPieces[1]);replacements.add(newPieces[0]);}
        if(mode==4){replacements.clear();replacements.add(oldPieces[0]);replacements.add(newPieces[0]);}
        CDataGroup data(L"ROOT",NULL,2,2,NULL);root=&data;groups.push_back(root);root->AddDataValue(L"DESCRIPTOR",L"Room Piece",false);root->AddDataValue(L"GUID",L"10",false);
        unsigned profile=current->seed%24;
        if(profile!=0){
            CDataGroup* first=child(root,L"Room Piece",profile&1?L"10":L"11");nested(first,1+current->seed/360%2,0);
            CDataGroup* carry=child(root,L"Room Piece",profile&2?L"-01":L"-1");child(carry,L"Room Piece",L"12");
            CDataGroup* empty=child(root,L"Room Piece",profile&4?NULL:L"");child(empty,L"Room Piece",L"10");
            CDataGroup* unknown=child(root,L"Room Piece",L"999999");child(unknown,L"Room Piece",L"11");
            CDataGroup* afterUnknown=child(root,L"Room Piece",L"-1");child(afterUnknown,L"Room Piece",L"10");
            CDataGroup* ordinary=child(root,profile&8?L"room piece":L"Other",L"10");child(ordinary,L"Room Piece",L"11");
            root->m_DataGroups.add(NULL);
            const wchar_t* variants[]={L"0",L"+10",L"  10",L"0010",L"10x",L"110",L"13",L"14",L"15",L"-9223372036854775808",L"9223372036854775807",L"-1"};
            CDataGroup* last=child(root,profile&16?NULL:L"Room Piece",variants[profile%12]);nested(last,1,2);
            if(profile==23)child(root,L"Room Piece ",L"10");
        }
        if(current->observed){TL_REDIRECT(getHook,convertGet,&get);TL_REDIRECT(setHook,convertSet,&set);TL_REDIRECT(lookupHook,convertLookup,&lookup);hookState();}
        if(out.issue)return;
        bool(*fn)(CDataGroup*,TArrayList<Core*>&)=ours?convertCandidate:convertOriginal;
        if(!autotest::beginInvocation(out,fn))return;bool result=fn(current->seed%97==0?NULL:root,replacements);out.callCompleted=1;number(result);
        getHook.restore();setHook.restore();lookupHook.restore();
        if(ours&&current->negative)root->SetDataValue(L"GUID",L"negativecontrol",false);
        number(gets);number(sets);number(lookups);number(m_gRoomPieceInformation==catalog);tree(root);
        number(replacements.size());for(unsigned i=0;i<replacements.size();++i)number(coreID(replacements[i]));
        for(unsigned i=0;i<oldPieces.size();++i){number(oldPieces[i]->m_guid);output->addText(oldPieces[i]->m_name);}
        for(unsigned i=0;i<newPieces.size();++i){number(newPieces[i]->m_guid);output->addText(newPieces[i]->m_name);}
        for(unsigned i=0;i<newPieces.size();++i)delete newPieces[i];replacements.clear();
    }
    m_gRoomPieceInformation=previous;number(g_iTotalCountOfObjects-before);
}
void original(void*p,autotest::Capture&out){side(p,out,false);}void candidate(void*p,autotest::Capture&out){side(p,out,true);}
int run(const tlhybrid_host* host,bool observed)
{
    const char* label=observed?"editor_convert_rooms_observed":"editor_convert_rooms_native";autotest::Coverage coverage(label,0x730300);
    for(unsigned i=0;i<720;++i){Case c={i,observed,false};autotest::Outcome a,b;autotest::runChild(original,&c,a,2000,10000);autotest::runChild(candidate,&c,b,2000,10000);if(coverage.observe(host,a,b)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    editorconvert observed%u seed%u status%d/%d issue%u/%u bytes%lu/%lu first%lu\n",observed,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);coverage.report(host);return 1;}}
    coverage.report(host);Case c={111,observed,true};autotest::Outcome a,b;autotest::runChild(original,&c,a,2000,10000);autotest::runChild(candidate,&c,b,2000,10000);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);host->log("    editorconvert negative observed%u detected%u\n",observed,detected?1:0);return !detected||!a.reportValid||!b.reportValid||a.childStatus||b.childStatus||autotest::incomplete(a)||autotest::incomplete(b);
}
}
TL_TEST(editor_convert_rooms_native){return run(host,false);}
TL_TEST(editor_convert_rooms_observed){return run(host,true);}
