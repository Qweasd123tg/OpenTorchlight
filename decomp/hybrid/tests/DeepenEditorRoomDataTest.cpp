#include <map>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "RoomPieceDataInformation.h"
#include "FileSystem.h"
TL_ORIGINAL(void,drOldSpecific,(CRoomPieceDataInformation*,std::wstring&),"_ZN25CRoomPieceDataInformation24LoadSpecificLevelTileSetERSbIwSt11char_traitsIwESaIwEE")
extern "C" void drNewSpecific(CRoomPieceDataInformation*,std::wstring&) __asm__("_ZN25CRoomPieceDataInformation24LoadSpecificLevelTileSetERSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void,drOldLoad,(CRoomPieceDataInformation*),"_ZN25CRoomPieceDataInformation12LoadRoomDataEv")
extern "C" void drNewLoad(CRoomPieceDataInformation*) __asm__("_ZN25CRoomPieceDataInformation12LoadRoomDataEv");
TL_ORIGINAL(void,drOldCtor,(CRoomPieceDataInformation*,CResourceSettings*),"_ZN25CRoomPieceDataInformationC1EP17CResourceSettings")
extern "C" void drNewCtor(CRoomPieceDataInformation*,CResourceSettings*) __asm__("_ZN25CRoomPieceDataInformationC1EP17CResourceSettings");
TL_FUNCTION(drLoad,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TL_FUNCTION(drParse,"_ZN25CRoomPieceDataInformation18ParseRoomPieceDataERKSbIwSt11char_traitsIwESaIwEEP10CDataGroupi")
TL_FUNCTION(drSave,"_ZN10CDataGroup10SaveToFileERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(drString,"_ZN20CDynamicPropertyFile9GetStringEj")
TL_FUNCTION(drSingleton,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(drFiles,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
extern CRoomPieceDataInformation*m_gRoomPieceInformation;
namespace {
struct Case{unsigned mode,seed;};autotest::Capture*cap;unsigned seed,loads,parses,saves,filesCalls;CRoomPieceDataInformation*receiver;CResourceSettings*settings;std::wstring folder;int token;
void n(unsigned x){cap->add(&x,4);}void invalid(){cap->issue=autotest::Capture::InvalidReport;}
CFileSystem*singleton(){return reinterpret_cast<CFileSystem*>(&token);}
const std::wstring&getString(CDynamicPropertyFile*p,unsigned key){n(1);n(key);if(p!=settings||key!=KRESOURCESETTING_S_ROOM_DATA_FOLDER||!receiver->m_RoomPieceCoreDataByGuid.empty())invalid();return folder;}
unsigned files(CFileSystem*p,const std::wstring&path,TArrayList<std::wstring>&out,std::wstring pattern,bool recursive,bool strip,bool mods,bool skip){++filesCalls;n(2);cap->addText(path);cap->addText(pattern);n(recursive);n(strip);n(mods);n(skip);if(p!=singleton()||path!=folder||pattern!=L"*.dat"||recursive||!strip||mods||skip)invalid();for(unsigned i=0;i<seed%4;++i){wchar_t t[64];std::swprintf(t,64,L"room%u.dat",i);out.add(t);}return out.size();}
void load(CDataGroup*p,const std::wstring&path,CTimerStatics*t){++loads;n(3);cap->addText(path);cap->addText(p->GetGroupName());if(t||p->GetGroupName()!=L"ROOMDATA")invalid();if(seed%5)p->AddDataValue(L"NAME",seed&1?L"TileSet":L"mixed",false);if(seed%3)p->AddDataValue(L"COLLISIONTYPE",seed&2?L"OTHER":L"ROOM",false);for(unsigned i=0;i<seed%5;++i){CDataGroup*child=p->AddDataGroup(L"PIECE");child->AddDataValue(L"GUID",1000LL+i);}}
bool parse(CRoomPieceDataInformation*p,const std::wstring&name,CDataGroup*d,int flags){++parses;n(4);cap->addText(name);cap->addText(d->GetGroupName());n(flags);if(p!=receiver||(name!=L"TILESET"&&name!=L"MIXED")||flags!=(seed%3&&seed&2?32:16))invalid();d->AddDataValue(L"MODIFIED",unsigned(parses));return (seed+parses)%3==0;}
int save(CDataGroup*p,const std::wstring&path){++saves;n(5);cap->addText(path);n(p->GetNumberOfDataGroups());for(unsigned i=0;i<p->GetNumberOfDataGroups();++i)n(p->GetDataGroup(i)->GetDataValue(L"MODIFIED",0u));return seed%2;}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;loads=parses=saves=filesCalls=0;folder=L"synthetic/rooms";settings=reinterpret_cast<CResourceSettings*>(&token);uint64_t bytes[(sizeof(CRoomPieceDataInformation)+7)/8];receiver=reinterpret_cast<CRoomPieceDataInformation*>(bytes);detour::Set d;TL_REDIRECT(d,drString,&getString);TL_REDIRECT(d,drSingleton,&singleton);TL_REDIRECT(d,drFiles,&files);TL_REDIRECT(d,drLoad,&load);TL_REDIRECT(d,drParse,&parse);TL_REDIRECT(d,drSave,&save);if(d.failed()){invalid();return;}
 if(c.mode==2){CResourceSettings*arg=seed&1?settings:NULL;typedef void(*Fn)(CRoomPieceDataInformation*,CResourceSettings*);Fn fn=ours?drNewCtor:drOldCtor;if(!autotest::beginInvocation(out,fn))return;fn(receiver,arg);out.callCompleted=1;if(m_gRoomPieceInformation!=receiver||receiver->m_pResourceSettings!=arg)invalid();}
 else{drOldCtor(receiver,NULL);if(c.mode==0){std::wstring path=seed&1?L"specific.dat":L"";typedef void(*Fn)(CRoomPieceDataInformation*,std::wstring&);Fn fn=ours?drNewSpecific:drOldSpecific;if(!autotest::beginInvocation(out,fn))return;fn(receiver,path);out.callCompleted=1;out.addText(path);}
 else{receiver->m_pResourceSettings=seed%7?settings:NULL;for(unsigned i=0;i<seed%4;++i){CRoomPieceDataInformation::CRoomPieceCoreData*p=new CRoomPieceDataInformation::CRoomPieceCoreData;p->m_name=L"owned previous";p->m_visualMeshFiles.add(L"mesh");receiver->m_RoomPieceCoreDataByGuid[100+i]=p;}typedef void(*Fn)(CRoomPieceDataInformation*);Fn fn=ours?drNewLoad:drOldLoad;if(!autotest::beginInvocation(out,fn))return;fn(receiver);out.callCompleted=1;if(!receiver->m_RoomPieceCoreDataByGuid.empty())invalid();}}
 n(loads);n(parses);n(saves);n(filesCalls);n(receiver->m_RoomPieceCoreDataByGuid.size());n(m_gRoomPieceInformation==receiver);receiver->~CRoomPieceDataInformation();n(m_gRoomPieceInformation==NULL);
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned seed=0;seed<48;++seed){Case c={mode,seed};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(h,x,y)){h->log("    room data mode%u seed%u issue%u/%u exit%d/%d\n",mode,seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(deepen_editor_room_specific){return run(host,0,"deepen_editor_room_specific",(uintptr_t)&drOldSpecific);}
TL_TEST(deepen_editor_room_load){return run(host,1,"deepen_editor_room_load",(uintptr_t)&drOldLoad);}
TL_TEST(deepen_editor_room_ctor){return run(host,2,"deepen_editor_room_ctor",(uintptr_t)&drOldCtor);}
