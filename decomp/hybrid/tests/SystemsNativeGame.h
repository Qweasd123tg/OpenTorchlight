#ifndef SYSTEMS_NATIVE_GAME_H
#define SYSTEMS_NATIVE_GAME_H
#include "Game.h"
#include "Settings.h"
#include "SDL.h"
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/CharacterLibraryBoundary.h"
#include <OgreRoot.h>
TL_ORIGINAL(void, systemsGameCtor,(CGame*,std::string,CSettings*,bool),"_ZN5CGameC1ESsP9CSettingsb")
TL_ORIGINAL(void, systemsGameDtor,(CGame*),"_ZN5CGameD1Ev")
TL_ORIGINAL(void, systemsGameSettingsCtor,(CSettings*,std::wstring,std::wstring,std::wstring,std::wstring),"_ZN9CSettingsC1ESbIwSt11char_traitsIwESaIwEES3_S3_S3_")
TL_ORIGINAL(void, systemsGameSettingsDtor,(CSettings*),"_ZN9CSettingsD1Ev")
extern "C" void systemsGameRootCtor(void*,const std::string&,const std::string&,const std::string&) __asm__("_ZN4Ogre4RootC1ERKSsS2_S2_");
extern "C" void systemsGameRootDtor(void*) __asm__("_ZN4Ogre4RootD1Ev");
namespace systems_game {
inline int videoInit(const char*){return 0;}
inline int numDisplays(){return 0;}
inline int desktopMode(int,SDL_DisplayMode*mode){std::memset(mode,0,sizeof(*mode));mode->w=1280;mode->h=720;return 0;}
}
class SystemsNativeGame {
public:
 bool ownsRoot,ownsSettings;Ogre::Root* root;CSettings*settings;CGame*game;
 SystemsNativeGame():ownsRoot(false),ownsSettings(true),root(Ogre::Root::getSingletonPtr()),settings(NULL),game(NULL){
  if(!root){ownsRoot=true;root=static_cast<Ogre::Root*>(Ogre::NedAllocImpl::allocBytes(0x398,0,0,0));std::string empty;systemsGameRootCtor(root,empty,empty,empty);}
  settings=static_cast<CSettings*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSettings),0,0,0));systemsGameSettingsCtor(settings,L"",L"",L"",L"");
  construct();
 }
 SystemsNativeGame(Ogre::Root*r,CSettings*s):ownsRoot(false),ownsSettings(false),root(r),settings(s),game(NULL){construct();}
 void construct(){std::string empty;
  game=static_cast<CGame*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGame),0,0,0));
  CharacterLibraryBoundary video(characterLibraryEntry(NULL,"SDL_VideoInit"),&systems_game::videoInit),displays(characterLibraryEntry(NULL,"SDL_GetNumVideoDisplays"),&systems_game::numDisplays),desktop(characterLibraryEntry(NULL,"SDL_GetDesktopDisplayMode"),&systems_game::desktopMode);
  if(video.failed()||displays.failed()||desktop.failed())_exit(64);
  systemsGameCtor(game,empty,settings,false);
 }
 ~SystemsNativeGame(){
  if(game){game->m_settings=NULL;game->m_root=NULL;game->m_renderWindow=NULL;game->m_gameClient=NULL;game->m_masterResourceManager=NULL;game->m_cameraControl=NULL;game->m_soundManager=NULL;game->m_logManager=NULL;
  systemsGameDtor(game);Ogre::NedAllocImpl::deallocBytes(game);}
  if(ownsSettings&&settings){systemsGameSettingsDtor(settings);Ogre::NedAllocImpl::deallocBytes(settings);}
  if(ownsRoot&&root){systemsGameRootDtor(root);Ogre::NedAllocImpl::deallocBytes(root);}
 }
};
#endif
