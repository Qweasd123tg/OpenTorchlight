#ifndef OTL_NATIVE_CONSOLE_FIXTURE_H
#define OTL_NATIVE_CONSOLE_FIXTURE_H
#include "MenuGuiFixture.h"
#include "Console.h"
TL_ORIGINAL(void, ncCtor,(CConsole*,CGameUI*,CResourceManager*,CEGUI::Window*),"_ZN8CConsoleC1EP7CGameUIP16CResourceManagerPN5CEGUI6WindowE")
TL_ORIGINAL(void, ncDtor,(CConsole*),"_ZN8CConsoleD1Ev")
namespace menugui {
// Console.cpp's two native TU-local empty strings. Before-main tests run before
// that TU's dynamic initializer. Construct real standard strings only when the
// exact native eight-byte pointer storage is still zero; restore its lifetime.
struct ConsoleStrings {
 bool narrow,wide;
 ConsoleStrings():narrow(false),wide(false){
  void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14bb2c0),8);if(!p){new(reinterpret_cast<void*>(0x14bb2c0))std::string;narrow=true;}
  std::memcpy(&p,reinterpret_cast<void*>(0x14bb2c8),8);if(!p){new(reinterpret_cast<void*>(0x14bb2c8))std::wstring;wide=true;}
 }
 ~ConsoleStrings(){if(wide){reinterpret_cast<std::wstring*>(0x14bb2c8)->~basic_string();std::memset(reinterpret_cast<void*>(0x14bb2c8),0,8);}if(narrow){reinterpret_cast<std::string*>(0x14bb2c0)->~basic_string();std::memset(reinterpret_cast<void*>(0x14bb2c0),0,8);}}
};
struct Console {
 ConsoleStrings strings;
 CConsole*p;CGameUI*ui;CConsole*previous;
 explicit Console(Fixture&f):p(NULL),ui(f.ui),previous(f.ui->m_console){
  p=static_cast<CConsole*>(Ogre::NedAllocImpl::allocBytes(sizeof(CConsole),0,0,0));ncCtor(p,f.ui,&f.resources,f.root);f.ui->m_console=p;
 }
 ~Console(){ui->m_console=previous;ncDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}
private:Console(const Console&);Console&operator=(const Console&);
};
}
#endif
