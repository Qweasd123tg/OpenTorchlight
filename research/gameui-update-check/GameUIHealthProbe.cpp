// A prefix probe ending at PlayerHealthBarSub::setPosition, before local strings.
// This is not a replacement for updateIngameUI and cannot count as acceptance.
#include <cstring>
#include <stdexcept>
#include <CEGUIUDim.h>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void originalUpdate(void*,float,void*,void*) __asm__("__tlorig__ZN7CGameUI14updateIngameUIEfP11CGameClientPN4Ogre12RenderWindowE");
TL_FUNCTION(settingsGet,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(mousePressed,"_ZN13CMouseManager13buttonPressedE12EMouseButton")
TL_FUNCTION(mouseHeld,"_ZN13CMouseManager10buttonHeldE12EMouseButton")
TL_FUNCTION(updateSlots,"_ZN7CGameUI11updateSlotsEv")
TL_FUNCTION(editorSingleton,"_ZN7CEditor12getSingletonEv")
TL_FUNCTION(modalPartial,"_ZN7CGameUI22modalDialogOpenPartialEv")
TL_FUNCTION(characterHP,"_ZN10CCharacter2HPEv")
TL_FUNCTION(characterMaxHP,"_ZN10CCharacter5maxHPEv")
namespace {
template<class T>T& at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
struct Case{int hp,maxhp;unsigned seed,mode;};
struct World{unsigned long long ui[0x1a08/8],character[0x500/8],radio[0x800/8],cinema[0x100/8],editor[0x100/8],menu[8],vt[8],target,settings;unsigned positions;World():target(0),settings(0),positions(0){std::memset(ui,0,sizeof(ui));std::memset(character,0,sizeof(character));std::memset(radio,0,sizeof(radio));std::memset(cinema,0,sizeof(cinema));std::memset(editor,0,sizeof(editor));std::memset(menu,0,sizeof(menu));std::memset(vt,0,sizeof(vt));}};
World*w;const Case*input;autotest::Capture*out;bool reachedBoundary;
void stop(){reachedBoundary=true;throw std::runtime_error("gameui boundary");}
void n(int x){out->add(&x,sizeof(x));}
int zero(void*,unsigned){return 0;}bool yes(void*,unsigned){return true;}void noop(void*){}bool modal(void*){return true;}void*editor(){return w->editor;}void hidden(void*,bool){}void closeMenu(void*,bool){}bool notOpen(void*){return false;}
int hp(void*p){n(1);n(p==w->character);return input->hp;}int maxhp(void*p){n(2);n(p==w->character);return input->maxhp;}
void position(void*p,const CEGUI::UVector2&v){n(3);n(p==reinterpret_cast<void*>(0x140)?0:1);out->add(&v,sizeof(v));++w->positions;if(input->mode==1&&w->positions==1)at<float>(w->ui,0x1724)=-3.5f;if(w->positions==2)stop();}
void size(void*p,const CEGUI::UVector2&v){n(4);n(p==reinterpret_cast<void*>(0x140));out->add(&v,sizeof(v));if(input->mode==2)at<float>(w->ui,0x1728)=17.25f;}
CEGUI::UVector2& pos(){return at<CEGUI::UVector2>(w->ui,0x16cc);}CEGUI::UVector2& dims(){return at<CEGUI::UVector2>(w->ui,0x171c);}
void model(){float ratio=float(hp(w->character))/float(maxhp(w->character));if(ratio<0.0f)ratio=0.0f;
 position(reinterpret_cast<void*>(0x140),CEGUI::UVector2(CEGUI::UDim(0,pos().d_x.asAbsolute(1)),CEGUI::UDim(0,(pos().d_y.asAbsolute(1)+dims().d_y.asAbsolute(1))-dims().d_y.asAbsolute(1)*ratio)));
 size(reinterpret_cast<void*>(0x140),CEGUI::UVector2(CEGUI::UDim(0,dims().d_x.asAbsolute(1)),CEGUI::UDim(0,dims().d_y.asAbsolute(1)*ratio)));
 position(reinterpret_cast<void*>(0x150),CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,-(dims().d_y.asAbsolute(1)-dims().d_y.asAbsolute(1)*ratio))));
}
void side(void*context,autotest::Capture&capture,bool expected){Case&c=*static_cast<Case*>(context);World world;w=&world;input=&c;out=&capture;reachedBoundary=false;
 at<void*>(w->ui,0x78)=&w->settings;at<void*>(w->ui,0x200)=w->radio;at<void*>(w->ui,0x540)=w->cinema;at<unsigned char>(w->cinema,0x31)=1;at<void*>(w->ui,0x38)=w->character;at<int>(w->character,0x330)=2;at<void*>(w->character,0x340)=&w->target;at<unsigned char>(w->editor,0x64)=2;w->vt[3]=reinterpret_cast<unsigned long long>(&closeMenu);w->vt[5]=reinterpret_cast<unsigned long long>(&notOpen);w->menu[0]=reinterpret_cast<unsigned long long>(w->vt);at<void*>(w->ui,0x578)=w->menu;at<void*>(w->ui,0x4d8)=w->menu;at<void*>(w->ui,0x140)=reinterpret_cast<void*>(0x140);at<void*>(w->ui,0x150)=reinterpret_cast<void*>(0x150);
 static const float values[]={-3.5f,-0.51f,-0.5f,0,0.49f,0.5f,0.51f,2.5f,17.25f};for(unsigned j=0;j<4;++j){at<float>(w->ui,0x16cc+j*4)=values[(c.seed+j)%9];at<float>(w->ui,0x171c+j*4)=values[(c.seed*3+j+2)%9];}
 const unsigned long guards[]={0x14b9bb8,0x14b9bc0,0x14b9bc8,0x14b9bd0};for(unsigned j=0;j<4;++j)*reinterpret_cast<unsigned char*>(guards[j])=1;
 detour::Set patches;TL_REDIRECT(patches,settingsGet,&zero);TL_REDIRECT(patches,mousePressed,&yes);TL_REDIRECT(patches,mouseHeld,&yes);TL_REDIRECT(patches,updateSlots,&noop);TL_REDIRECT(patches,editorSingleton,&editor);TL_REDIRECT(patches,modalPartial,&modal);TL_REDIRECT(patches,characterHP,&hp);TL_REDIRECT(patches,characterMaxHP,&maxhp);patches.redirect(reinterpret_cast<char*>(0x554718),reinterpret_cast<char*>(0x554718),&hidden);patches.redirect(reinterpret_cast<char*>(0x5548a8),reinterpret_cast<char*>(0x5548a8),&position);patches.redirect(reinterpret_cast<char*>(0x555178),reinterpret_cast<char*>(0x555178),&size);if(patches.failed())_exit(42);
 try{if(expected)model();else originalUpdate(w->ui,0.125f,NULL,NULL);_exit(43);}catch(const std::runtime_error&e){if(!reachedBoundary||std::strcmp(e.what(),"gameui boundary")!=0)_exit(44);}n(w->positions);out->add(reinterpret_cast<char*>(w->ui)+0x171c,16);
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void expected(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(gameui_health_prefix_characterization){int failures=0;unsigned count=0;const int h[]={-10,0,1,5,100,250};const int m[]={-100,0,1,10,100};for(unsigned a=0;a<6;++a)for(unsigned b=0;b<5;++b)for(unsigned seed=0;seed<9;++seed)for(unsigned mode=0;mode<3;++mode){Case c={h[a],m[b],seed,mode};autotest::Outcome x,y;autotest::runChild(original,&c,x);autotest::runChild(expected,&c,y);bool ok=WIFEXITED(x.status)&&WEXITSTATUS(x.status)==0&&WIFEXITED(y.status)&&WEXITSTATUS(y.status)==0&&x.capture.length==y.capture.length&&x.capture.length<autotest::Capture::kSize&&std::memcmp(x.capture.data,y.capture.data,x.capture.length)==0;TL_CHECK(failures,ok);if(!ok){host->log(" health %d/%d seed %u mode %u status %d/%d sizes %lu/%lu\n",c.hp,c.maxhp,seed,mode,x.status,y.status,(unsigned long)x.capture.length,(unsigned long)y.capture.length);return failures;}++count;}host->log("    gameui HP prefix: %u cases; stops before tooltip strings\n",count);return failures;}
