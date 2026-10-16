#include "AutoTest.h"
#include "BinaryStyle.h"
#include "OgreResourceFile.h"
#include "TRepository.h"
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <unistd.h>
TL_ORIGINAL(void, oldBinaryIndexes, (void*,CDataGroup*,std::map<unsigned,bool>&), "_ZN12CBinaryStyle15getStringIndexsEP10CDataGroupRSt3mapIjbSt4lessIjESaISt4pairIKjbEEE")
extern "C" void newBinaryIndexes(void*,CDataGroup*,std::map<unsigned,bool>&) __asm__("_ZN12CBinaryStyle15getStringIndexsEP10CDataGroupRSt3mapIjbSt4lessIjESaISt4pairIKjbEEE");
TL_ORIGINAL(void, oldOgreIndexes, (void*,CDataGroup*,std::map<unsigned,bool>&), "_ZN17COgreResourceFile15getStringIndexsEP10CDataGroupRSt3mapIjbSt4lessIjESaISt4pairIKjbEEE")
extern "C" void newOgreIndexes(void*,CDataGroup*,std::map<unsigned,bool>&) __asm__("_ZN17COgreResourceFile15getStringIndexsEP10CDataGroupRSt3mapIjbSt4lessIjESaISt4pairIKjbEEE");
TL_ORIGINAL(std::wstring, oldUTF16, (void*,std::ifstream&,unsigned), "_ZN12CBinaryStyle23GetWChar16ArrayAsStringERSt14basic_ifstreamIcSt11char_traitsIcEEj")
extern "C" std::wstring newUTF16(void*,std::ifstream&,unsigned) __asm__("_ZN12CBinaryStyle23GetWChar16ArrayAsStringERSt14basic_ifstreamIcSt11char_traitsIcEEj");
namespace {
struct Case {unsigned operation,index;const char* file;};
void fill(CDataGroup& group,unsigned seed,unsigned depth) {
    static const wchar_t* names[]={L"integer",L"unsigned",L"float",L"double",L"boolean",L"wide",L"translate",L"wide"};
    unsigned count=seed%9;
    for(unsigned i=0;i<count;++i) {
        switch(i%8) {
        case 0:group.AddDataValue(names[i%8],int(seed*17));break;
        case 1:group.AddDataValue(names[i%8],unsigned(seed*101));break;
        case 2:group.AddDataValue(names[i%8],float(seed)/7);break;
        case 3:group.AddDataValue(names[i%8],double(seed)/3);break;
        case 4:group.AddDataValue(names[i%8],bool(seed&1));break;
        case 5:group.AddDataValue(names[i%8],seed&1?L"":L"shared",false);break;
        case 6:group.AddDataValue(names[i%8],seed&2?L"shared":L"\x043f\x0435\x0440\x0435\x0432\x043e\x0434",true);break;
        case 7:group.AddDataValue(names[i%8],L"shared",false);break;
        }
    }
    if(depth)for(unsigned i=0;i<seed%4;++i){CDataGroup* child=group.AddDataGroup(i&1?L"same":L"child");fill(*child,seed+i+1,depth-1);}
}
void record(autotest::Capture& out,CDataGroup& group) {
    out.add(&group.m_iNameID,sizeof(group.m_iNameID));unsigned count=group.m_DataValues.size();out.add(&count,sizeof(count));
    for(unsigned i=0;i<count;++i)out.add(group.m_DataValues[i],sizeof(CDataValue));
    count=group.m_DataGroups.size();out.add(&count,sizeof(count));for(unsigned i=0;i<count;++i)record(out,*group.m_DataGroups[i]);
}
void side(void* raw,autotest::Capture& out,bool ours) {
    const Case& c=*static_cast<Case*>(raw);
    if(c.operation<2) {
        TRepository<std::wstring> repository(L"");CDataGroup group(L"root",NULL,3,2,&repository);fill(group,c.index,c.index%3);
        std::map<unsigned,bool> indexes;if(c.index&1){indexes[0]=false;indexes[1]=false;indexes[0xffffffffu]=true;}
        CBinaryStyle binary;COgreResourceFile ogre;void* object=c.operation?static_cast<void*>(&ogre):static_cast<void*>(&binary);
        typedef void(*Fn)(void*,CDataGroup*,std::map<unsigned,bool>&);Fn fn=c.operation?(ours?newOgreIndexes:oldOgreIndexes):(ours?newBinaryIndexes:oldBinaryIndexes);
        if(!autotest::beginInvocation(out,fn))return;fn(object,&group,indexes);out.callCompleted=1;
        unsigned count=indexes.size();out.add(&count,sizeof(count));for(std::map<unsigned,bool>::const_iterator i=indexes.begin();i!=indexes.end();++i){out.add(&i->first,sizeof(i->first));out.add(&i->second,sizeof(i->second));}record(out,group);
    } else {
        CBinaryStyle binary;std::ifstream stream(c.file,std::ios::binary);
        unsigned lengths[]={0,1,2,3,7,16,1023,1024,1025,0xffffffffu};unsigned length=lengths[c.index%10];
        typedef std::wstring(*Fn)(void*,std::ifstream&,unsigned);Fn fn=ours?newUTF16:oldUTF16;
        if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(&binary,stream,length);out.callCompleted=1;out.addText(result);
        unsigned state=stream.rdstate();std::streamoff position=stream.tellg();std::streamsize read=stream.gcount();out.add(&state,sizeof(state));out.add(&position,sizeof(position));out.add(&read,sizeof(read));
    }
}
void original(void* p,autotest::Capture& out){side(p,out,false);}void candidate(void* p,autotest::Capture& out){side(p,out,true);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uint64_t address) {
    autotest::Coverage coverage(name,address);char path[]="/tmp/otl-accessor-utf-XXXXXX";int fd=mkstemp(path);if(fd<0)return 1;close(fd);
    unsigned count=operation==2?60:54;
    for(unsigned i=0;i<count;++i) {
        if(operation==2) {
            std::ofstream file(path,std::ios::binary);unsigned sizes[]={0,1,4,32,2048,4096};unsigned size=sizes[i/10];
            unsigned short units[]={0x0041,0x0436,0x20ac,0xd83d,0xde00,0,0xd800,0xdc00,0xffff};
            for(unsigned j=0;j<size;++j){unsigned char byte=(j&1)?units[(j/2)%9]>>8:units[(j/2)%9]&255;file.put(byte);}
        }
        Case c={operation,i,path};autotest::Outcome& a=autotest::g_outcomes[0];autotest::Outcome& b=autotest::g_outcomes[1];autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){unlink(path);coverage.report(host);return 1;}
    }
    unlink(path);coverage.report(host);return 0;
}
}
TL_TEST(mass_binary_string_indexes){return run(host,0,"mass_binary_string_indexes",(uint64_t)(uintptr_t)oldBinaryIndexes);}
TL_TEST(mass_ogre_string_indexes){return run(host,1,"mass_ogre_string_indexes",(uint64_t)(uintptr_t)oldOgreIndexes);}
TL_TEST(mass_binary_utf16){return run(host,2,"mass_binary_utf16",(uint64_t)(uintptr_t)oldUTF16);}
