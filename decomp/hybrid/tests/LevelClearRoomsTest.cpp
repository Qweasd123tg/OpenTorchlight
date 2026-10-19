#include "tests/FinishLevelFixture.h"
#include "NativeConsoleFixture.h"
#include "Light.h"
TL_ORIGINAL(void,crOld,(CLevel*),"_ZN6CLevel18clearOutRoomPiecesEv")
extern "C" void crNew(CLevel*) __asm__("_ZN6CLevel18clearOutRoomPiecesEv");
TL_FUNCTION(crObjects,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEEP10TArrayListIP17CEditorBaseObjectE")
TL_FUNCTION(crAnimated,"_ZN10CRoomPiece22getRoomPieceIsAnimatedEv")
TL_FUNCTION(crConsole,"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
namespace {
autotest::Capture*output;CSettings*settings;Ogre::SceneManager*scene;CLevel*level;CConsole*console;CEditorScene*scenes[3];CEditorBaseObject*objects[9];unsigned deleted[9],seed;
void word(unsigned v){output->add(&v,4);}void text(const std::wstring&s){word(s.size());if(!s.empty())output->add(s.data(),s.size()*4);}
unsigned id(const void*p){if(!p)return 0;for(unsigned i=0;i<9;++i)if(p==objects[i])return i+1;return 99;}
struct Scene:CEditorScene{Scene():CEditorScene(L"clear-room-fixture"){}virtual void DeleteObjectInScene(CEditorBaseObject*p){unsigned i=0;while(i<3&&scenes[i]!=this)++i;word(1);word(i);unsigned n=id(p);word(n);if(n==0||n>9)std::abort();++deleted[n-1];}};
bool animated(CRoomPiece*p){unsigned n=id(p);word(2);word(n);bool v=(seed+n)%3==0;word(v);return v;}
void consoleText(CConsole*p,std::wstring s){word(3);word(p==console);text(s);}
void query(CEditorScene*p,const std::wstring&name,TArrayList<CEditorBaseObject*>*out){unsigned i=0;while(i<3&&scenes[i]!=p)++i;if(i==3)std::abort();word(4);word(i);text(name);word(out->size());word(out->m_nCapacity);word(out->m_nGrowBy);word(out->m_pData==NULL);unsigned n=(seed/3+i)%11;for(unsigned j=0;j<n;++j){unsigned index=(j+i+(name==L"Light"?4:0))%10;out->add(index==9?NULL:objects[index]);}if((seed&32)&&i==0&&name==L"Room Piece"&&level->m_RoomScenes.size()==1)level->m_RoomScenes.add(scenes[1]);}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;std::memset(deleted,0,sizeof deleted);CStringTranslate translation(L"");menugui::Fixture menu(*settings,scene);menugui::Console owner(menu);console=owner.p;finishlevel::Fixture f;level=&f.level;f.resources.m_pSceneManager=menu.nativeClient.scenes[0];CMasterResourceManager::getSingleton()->m_pSceneManager=menu.nativeClient.scenes[0];level->m_pGameClient=menu.nativeClient.client;CGameUI*previousUI=menu.nativeClient.client->m_pGameUI;menu.nativeClient.client->m_pGameUI=menu.ui;
 for(unsigned i=0;i<3;++i)scenes[i]=new Scene;
 for(unsigned i=0;i<4;++i){CRoomPiece*p=new CRoomPiece(&f.resources);objects[i]=p;p->m_bIsBakeable=(seed+i)&1;}
 for(unsigned i=4;i<7;++i)objects[i]=new CLight(&f.resources);objects[7]=new CEditorBaseObject;objects[8]=new CPositionableObject(&f.resources,f.resources.m_pSceneManager);
 for(unsigned i=0;i<9;++i)objects[i]->SetSceneOwner(scenes[(seed+i)%3]);for(unsigned i=0;i<seed%4;++i)level->m_RoomScenes.add(scenes[i]);
 detour::Set hooks;TL_REDIRECT(hooks,crObjects,&query);TL_REDIRECT(hooks,crAnimated,&animated);TL_REDIRECT(hooks,crConsole,&consoleText);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Fn)(CLevel*);Fn fn=ours?crNew:crOld;if(!autotest::beginInvocation(out,fn))return;fn(level);out.callCompleted=1;out.add(deleted,sizeof deleted);word(level->m_RoomScenes.size());for(unsigned i=0;i<4;++i)word(static_cast<CRoomPiece*>(objects[i])->m_bIsBakeable);
 hooks.restore();for(unsigned i=0;i<9;++i){objects[i]->SetSceneOwner(NULL);delete objects[i];}level->m_RoomScenes.clear();for(unsigned i=0;i<3;++i)delete scenes[i];menu.nativeClient.client->m_pGameUI=previousUI;level->m_pGameClient=NULL;
}
}
TL_TEST(level_clear_rooms){tlheadless::Environment env;env.loadGameSkin();CEGUI::SchemeManager::getSingleton().loadScheme("media/ui/WindowsLook.scheme");nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"level_clear_rooms",0x95a0f0,&side,192);}
