#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include <new>
#include <CEGUIString.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#define protected public
#include "EditorImage.h"
#include "MenuManager.h"
#include "ContinueGameMenu.h"
#include "InteractiveMenu.h"
#include "FileSystem.h"
#undef private
#undef protected
#define TARGET(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
TARGET(void,aeMOldImageVisible,aeMNewImageVisible,(CEditorImage*,bool),"_ZN12CEditorImage10setVisibleEb")
TARGET(void,aeMOldImageFile,aeMNewImageFile,(CEditorImage*,const std::wstring&),"_ZN12CEditorImage16setImageFileNameERKSbIwSt11char_traitsIwESaIwEE")
TARGET(void,aeMOldUpdate,aeMNewUpdate,(CMenuManager*,float,void*,void*),"_ZN12CMenuManager6updateEfP11CGameClientPN4Ogre12RenderWindowE")
TARGET(bool,aeMOldInput,aeMNewInput,(CMenuManager*,void*,float,bool),"_ZN12CMenuManager12processInputEPvfb")
TARGET(void,aeMOldActive,aeMNewActive,(CMenuManager*,int),"_ZN12CMenuManager13setActiveMenuE5EMenu")
TARGET(void,aeMOldCreate,aeMNewCreate,(CInteractiveMenu*),"_ZN16CInteractiveMenu11createMenusEv")
TL_FUNCTION(aeMImage,"_ZN12CEditorImage20getImageByFileOrNameERKSbIwSt11char_traitsIwESaIwEEPh")
TL_FUNCTION(aeMMouse,"_ZN13CMouseManager6updateEPv")
TL_FUNCTION(aeMCanContinue,"_ZN17CContinueGameMenu11canContinueEv")
TL_FUNCTION(aeMSelect,"_ZN17CContinueGameMenu15selectCharacterEib")
TL_FUNCTION(aeMFiles,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(aeMInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
extern "C" char aeMLoad[] __asm__("_ZN5CEGUI13WindowManager16loadWindowLayoutERKNS_6StringEb");
extern "C" char aeMChild[] __asm__("_ZNK5CEGUI6Window8getChildERKNS_6StringE");
extern "C" char aeMAddChild[] __asm__("_ZN5CEGUI6Window14addChildWindowEPS0_");
extern "C" char aeMVisible[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" void*aeMWindowManager __asm__("_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE");
namespace {
struct Case{unsigned op,seed,variant;};Case input;autotest::Capture*output;void*self;CMenuManager*manager;void*menus[8];void*window;void*objects[6];unsigned calls;const std::wstring*activeImageName;
void number(unsigned n){output->add(&n,4);}void check(bool x){number(x);if(!x)output->issue=autotest::Capture::InvalidReport;}
unsigned id(void*p){if(!p)return 0;for(unsigned i=0;i<8;++i)if(p==menus[i])return i+1;for(unsigned i=0;i<6;++i)if(p==objects[i])return i+20;return p==self?10:99;}
void event(unsigned n,void*p){number(n);number(id(p));}
void change(){if(++calls==1&&input.variant==1){manager->m_pUnknownDD8=menus[5];manager->m_pUnknownDE0=menus[6];manager->m_pContinueGameMenu=reinterpret_cast<CContinueGameMenu*>(menus[7]);}if(input.variant==2)manager->m_UnknownDF0=37;}
void broadcast(void*p,unsigned code){event(1,p);number(code);number(static_cast<CEditorImage*>(p)->m_bVisible);}
long image(void*p,const std::wstring&name,unsigned char*property){event(2,p);check(&name==activeImageName);output->addText(name);output->addText(std::string(reinterpret_cast<char*>(property)));output->addText(static_cast<CEditorImage*>(p)->m_sImageFileName);return 0x12345678;}
void update(void*p,float elapsed){event(3,p);output->add(&elapsed,4);change();}
bool process(void*p,void*w,float elapsed,bool active){event(4,p);check(w==window);output->add(&elapsed,4);number(active);change();return (input.variant!=3||id(p)!=(input.seed/16)%4+1);}
void mouse(void*p,void*w){number(5);check(p==reinterpret_cast<char*>(manager)+0xd58);check(w==window);if(input.variant==2)manager->m_pUnknownDD0=menus[4];}
void open(void*p,bool flag){event(6,p);number(flag);if(id(p)==2||id(p)==6)number(static_cast<unsigned char*>(p)[0xf8]);if(id(p)==3||id(p)==7)number(static_cast<unsigned char*>(p)[0xd0]);change();}
bool canContinue(void*p){event(7,p);return input.seed&1;}
bool select(void*p,int index,bool flag){event(8,p);number(index);number(flag);return input.seed&2;}
void*files(){number(9);return objects[0];}
void info(void*p,const std::wstring&name,CFileInfo&out,bool a,bool b,bool c){event(10,p);output->addText(name);output->addText(out.m_sModName);output->addText(out.m_sResourceName);output->addText(out.m_sPath);number(out.m_eFormat);number(out.m_eLocation);number(out.m_bExists);number(a);number(b);number(c);const char*names[]={"","layout.xml","\320\226-layout.xml"};out.m_sResourceName=input.seed%4==3?std::string(180,'L'):names[input.seed%3];out.m_sModName="mod";out.m_sPath=L"resolved/path";out.m_sResourceGroup="group";}
void text(const CEGUI::String&s){number(s.length());for(size_t i=0;i<s.length();++i)number(s[i]);}
void*load(void*p,const CEGUI::String&name,bool flag){event(11,p);text(name);number(flag);return objects[2];}
void*child(void*p,const CEGUI::String&name){event(12,p);text(name);return name==CEGUI::String("TopBar")?objects[3]:objects[4];}
void addChild(void*p,void*child){event(13,p);check(child==objects[2]);}
void visible(void*p,bool flag){event(14,p);number(flag);}
void interactiveVisible(void*p,bool flag){event(15,p);number(flag);static_cast<CInteractiveMenu*>(p)->m_bVisible=flag;}
void side(void*raw,autotest::Capture&out,bool ours){input=*static_cast<Case*>(raw);output=&out;calls=0;uint64_t storage[(sizeof(CMenuManager)+7)/8]={0},menuStorage[8][96]={{0}},windows[6][64]={{0}};self=storage;manager=reinterpret_cast<CMenuManager*>(storage);window=windows[5];for(unsigned i=0;i<8;++i)menus[i]=menuStorage[i];for(unsigned i=0;i<6;++i)objects[i]=windows[i];
 void*menuTable[8]={0};menuTable[2]=reinterpret_cast<void*>(&process);menuTable[3]=reinterpret_cast<void*>(&update);menuTable[7]=reinterpret_cast<void*>(&open);
 for(unsigned i=0;i<8;++i){*reinterpret_cast<void**>(menus[i])=menuTable;static_cast<unsigned char*>(menus[i])[0x30]=(input.seed>>(2*(i%4)))&1;static_cast<unsigned char*>(menus[i])[0x31]=(input.seed>>(2*(i%4)+1))&1;}
 manager->m_pUnknownDD0=menus[0];manager->m_pUnknownDD8=menus[1];manager->m_pUnknownDE0=menus[2];manager->m_pContinueGameMenu=reinterpret_cast<CContinueGameMenu*>(menus[3]);manager->m_UnknownDF0=input.seed%9;
 void*selfTable[8]={0};selfTable[6]=reinterpret_cast<void*>(&broadcast);selfTable[3]=reinterpret_cast<void*>(&interactiveVisible);*reinterpret_cast<void**>(storage)=selfTable;
 CEditorImage*editorImage=reinterpret_cast<CEditorImage*>(storage);if(input.op<2){editorImage->m_pWindow=input.seed&1?reinterpret_cast<CEGUI::Window*>(objects[2]):NULL;editorImage->m_pParentWindow=input.seed&2?reinterpret_cast<CEGUI::Window*>(objects[1]):NULL;editorImage->m_pGameUI=input.seed&4?reinterpret_cast<CGameUI*>(objects[0]):NULL;editorImage->m_bVisible=input.seed&8;new(&editorImage->m_sImageFileName)std::wstring(input.seed&16?L"Ж-image":L"");}
 CInteractiveMenu*interactive=reinterpret_cast<CInteractiveMenu*>(storage);if(input.op==5){interactive->m_pParentWindow=reinterpret_cast<CEGUI::Window*>(objects[1]);interactive->m_bVisible=input.seed&1;}
 void*oldManager=aeMWindowManager;aeMWindowManager=objects[0];detour::Set d;TL_REDIRECT(d,aeMImage,&image);TL_REDIRECT(d,aeMMouse,&mouse);TL_REDIRECT(d,aeMCanContinue,&canContinue);TL_REDIRECT(d,aeMSelect,&select);TL_REDIRECT(d,aeMFiles,&files);TL_REDIRECT(d,aeMInfo,&info);d.redirect(aeMLoad,aeMLoad,&load);d.redirect(aeMChild,aeMChild,&child);d.redirect(aeMAddChild,aeMAddChild,&addChild);d.redirect(aeMVisible,aeMVisible,&visible);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(input.op==0)autotest::invoke(out,ours?aeMNewImageVisible:aeMOldImageVisible,editorImage,(input.seed&32)!=0);
 if(input.op==1){std::wstring name=input.variant==0?L"":input.variant==1?L"Ж-image":input.variant==2?L"other image":std::wstring(140,L'Ж');const std::wstring&argument=input.seed&32?editorImage->m_sImageFileName:name;activeImageName=&argument;typedef void(*Fn)(CEditorImage*,const std::wstring&);Fn fn=ours?aeMNewImageFile:aeMOldImageFile;autotest::invoke<Fn,CEditorImage*,const std::wstring&>(out,fn,editorImage,argument);}
 float elapsed=input.variant==0?0.0f:input.variant==1?-0.0f:input.variant==2?-0.125f:3.75f;
 if(input.op==2)autotest::invoke(out,ours?aeMNewUpdate:aeMOldUpdate,manager,elapsed,objects[0],window);
 if(input.op==3)autotest::invoke(out,ours?aeMNewInput:aeMOldInput,manager,window,elapsed,(input.seed&1)!=0);
 if(input.op==4){const int states[]={0,1,2,3,4,5,6,-1,37};autotest::invoke(out,ours?aeMNewActive:aeMOldActive,manager,states[(input.seed/9)%9]);number(manager->m_UnknownDF0);}
 if(input.op==5){autotest::invoke(out,ours?aeMNewCreate:aeMOldCreate,interactive);check(interactive->m_pMenuWindow==objects[2]);check(interactive->m_pMenuContent==objects[3]);check(interactive->m_pMenuButtons==objects[4]);number(interactive->m_bVisible);}
 if(input.op<2){number(editorImage->m_bVisible);out.addText(editorImage->m_sImageFileName);editorImage->m_sImageFileName.~basic_string();}
 for(unsigned i=0;i<8;++i){number(static_cast<unsigned char*>(menus[i])[0xf8]);number(static_cast<unsigned char*>(menus[i])[0xd0]);}
 aeMWindowManager=oldManager;
}
void old(void*p,autotest::Capture&c){side(p,c,false);}void newer(void*p,autotest::Capture&c){side(p,c,true);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uint64_t address){autotest::Coverage coverage(name,address);unsigned count=op<2?64:op==5?24:op==4?81:256;
 for(unsigned seed=0;seed<count;++seed)for(unsigned variant=0;variant<4;++variant){Case c={op,seed,variant};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(newer,&c,b);if(coverage.observe(host,a,b)){host->log("    advance menus%u seed%u variant%u status%d/%d bytes%lu/%lu\n",op,seed,variant,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);unsigned limit=a.capture.length<b.capture.length?a.capture.length:b.capture.length;for(unsigned i=0;i<limit;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    first difference%u %u/%u\n",i,a.capture.data[i],b.capture.data[i]);break;}coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(advance_editor_image_visibility){return run(host,0,"advance_editor_image_visibility",(uint64_t)(uintptr_t)aeMOldImageVisible);}
TL_TEST(advance_editor_image_file){return run(host,1,"advance_editor_image_file",(uint64_t)(uintptr_t)aeMOldImageFile);}
TL_TEST(advance_editor_menu_update){return run(host,2,"advance_editor_menu_update",(uint64_t)(uintptr_t)aeMOldUpdate);}
TL_TEST(advance_editor_menu_input){return run(host,3,"advance_editor_menu_input",(uint64_t)(uintptr_t)aeMOldInput);}
TL_TEST(advance_editor_menu_active){return run(host,4,"advance_editor_menu_active",(uint64_t)(uintptr_t)aeMOldActive);}
TL_TEST(advance_editor_interactive_create){return run(host,5,"advance_editor_interactive_create",(uint64_t)(uintptr_t)aeMOldCreate);}
