#include "NativeConsoleFixture.h"
#include "RoomPieceDataInformation.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "DataValue.h"
TL_ORIGINAL(bool,fxOld,(CDataGroup*),"_ZL13fixRoomPiecesP10CDataGroup")
extern "C" bool fxNew(CDataGroup*) __asm__("__tlhybrid_local_186__ZL13fixRoomPiecesP10CDataGroup");
TL_FUNCTION(fxRoom,"_ZN25CRoomPieceDataInformation40_GetRoomPieceCoreDataByGuidByClosestGuidEx")
TL_FUNCTION(fxSound,"_ZN25CSoundBankDataInformation37getSoundDataObjectByGuidThatIsClosestEx")
extern CRoomPieceDataInformation*m_gRoomPieceInformation;
namespace {
autotest::Capture*output;unsigned seed;CRoomPieceDataInformation*rooms;CSoundBankDataInformation*sounds;CRoomPieceDataInformation::CRoomPieceCoreData*piece;CSoundData*sample;
void num(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){num(s.size());output->add(s.data(),s.size()*4);}
CRoomPieceDataInformation::CRoomPieceCoreData* room(CRoomPieceDataInformation*p,long long guid){num(11);num(p==rooms);output->add(&guid,8);return seed&1?piece:NULL;}
CSoundData* sound(CSoundBankDataInformation*p,long long guid){num(12);num(p==sounds);output->add(&guid,8);return seed&2?sample:NULL;}
void tree(CDataGroup*p){wide(p->GetGroupName());num(p->GetNumberOfDataValues());for(unsigned i=0;i<p->GetNumberOfDataValues();++i){CDataValue*v=p->GetDataValue(i);wide(v->GetDataValueName());wide(v->GetValueString(false));}num(p->GetNumberOfDataGroups());for(unsigned i=0;i<p->GetNumberOfDataGroups();++i)tree(p->GetDataGroup(i));}
void build(CDataGroup*root,unsigned depth,unsigned ordinal){
 const wchar_t*descriptors[]={L"Room Piece",L"Sound",L"Other",L"room piece"};const wchar_t*values[]={L"",L"0",L"-1",L"9223372036854775807",L"-9223372036854775808",L"0001",L"1x"};
 for(unsigned i=0;i<2;++i){CDataGroup*object=root->AddDataGroup(i?L"SECOND":L"FIRST");unsigned profile=seed+ordinal+i;
  if(!(profile&8)){CDataGroup*props=object->AddDataGroup(L"PROPERTIES");if(profile%11)props->AddDataValue(L"DESCRIPTOR",descriptors[profile/4%4],false);if(!(profile&16)){CDataGroup*guid=props->AddDataGroup(L"GUID");if(!(profile&32))guid->AddDataValue(L"VALUE",values[profile%7],false);}}
  if(depth){CDataGroup*children=object->AddDataGroup(L"CHILDREN");if(i==0)build(children,depth-1,ordinal+5);}
 }
}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;menugui::ConsoleStrings strings;CMasterResourceManager*master=CMasterResourceManager::getSingleton();CRoomPieceDataInformation*savedGlobal=m_gRoomPieceInformation;CRoomPieceDataInformation*oldRooms=master->m_pRoomPieceInformation;CSoundBankDataInformation*oldSounds=master->m_pSoundBankDataInformation;
 TSafePointer<CRoomPieceDataInformation::CRoomPieceCoreData>weakRoom;TSafePointer<CSoundData>weakSound;
 {
 CRoomPieceDataInformation roomOwner(NULL);CSoundBankDataInformation soundOwner(NULL);rooms=&roomOwner;sounds=&soundOwner;master->m_pRoomPieceInformation=rooms;master->m_pSoundBankDataInformation=sounds;
 CRoomPieceDataInformation::CRoomPieceCoreData core;core.m_name=L"owned-room-core";core.m_guid=seed&4?(-9223372036854775807LL-1):9223372036854775807LL;piece=&core;weakRoom.setObject(piece);core.m_visualMeshFiles.add(L"proof.mesh");core.m_snapRotation.add(90);
 CSoundData data;data.m_group=NULL;data.m_iGuid=seed&4?-1:0x123456789abcdefLL;data.m_name=L"owned-sound-data";sample=&data;weakSound.setObject(sample);
 CDataGroup root(L"ROOT",NULL,3,3,NULL);if(seed>1)build(&root,seed&64?2:seed&128?1:0,0);detour::Set lookups;TL_REDIRECT(lookups,fxRoom,&room);TL_REDIRECT(lookups,fxSound,&sound);if(lookups.failed())std::abort();typedef bool(*Fn)(CDataGroup*);Fn fn=ours?fxNew:fxOld;if(!autotest::beginInvocation(out,fn))return;num(fn(seed==0?NULL:&root));out.callCompleted=1;tree(&root);num(weakRoom.getObject()==piece);num(weakSound.getObject()==sample);lookups.restore();master->m_pRoomPieceInformation=oldRooms;master->m_pSoundBankDataInformation=oldSounds;
 }
 m_gRoomPieceInformation=savedGlobal;num(weakRoom.getObject()==NULL);num(weakSound.getObject()==NULL);
}
int run(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;return smallmass::run(host,0,"complete_ui_console_fixroom",0xaeed30,&side,256);}
}
TL_TEST(complete_ui_console_fixroom){return run(host);}
