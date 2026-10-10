// Original entry against the actual recovered full TU; dependencies are observed.
#include <cstring>
#include <string>
#include <new>
#include <CEGUI.h>
#include "GameUI.h"
#include "Character.h"
#include "Player.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldPlayer,(CGameUI*,CCharacter*),"_ZN7CGameUI9setPlayerEP10CCharacter")
extern "C" void newPlayer(CGameUI*,CCharacter*) __asm__("_ZN7CGameUI9setPlayerEP10CCharacter");
extern "C" void* playerTable[] __asm__("_ZTV7CPlayer");
extern "C" void* characterTable[] __asm__("_ZTV10CCharacter");
TL_FUNCTION(imageFn,"_ZN7CGameUI20getImageFromImageSetEPKh")
TL_FUNCTION(updateFn,"_ZN7CGameUI11updateSlotsEv")
TL_FUNCTION(combineFn,"_ZN12CCombineMenu9setPlayerEP10CCharacter")
TL_FUNCTION(enchantFn,"_ZN12CEnchantMenu9setPlayerEP10CCharacter")
TL_FUNCTION(singleFn,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateFn,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(convertFn,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
#define SDK(N,S) extern "C" char N[] __asm__(S)
SDK(textFn,"_ZN5CEGUI6Window7setTextERKNS_6StringE");
SDK(tipFn,"_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE");
SDK(idFn,"_ZN5CEGUI6Window5setIDEj");
SDK(propFn,"_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
SDK(imageStringFn,"_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE");
#undef SDK
namespace {
enum { Text=1,Tip,ID,Property,Image,ImageString,Single,Translate,Convert,Virtual,Combine,Enchant,Update,Wrong,Last };
struct Case { unsigned kind,pets,mask,repeat,mutation,at,nth,fault,faultNth; bool same; Case():kind(2),pets(1),mask(1023),repeat(1),mutation(0),at(0),nth(1),fault(0),faultNth(1),same(false){} };
struct Failure { unsigned b; Failure(unsigned x):b(x){} };
struct Block { unsigned char* p; unsigned size; }; Block blocks[160];unsigned blockCount,calls[Last],step,changed;
const Case* c;autotest::Capture* cap;void* ui;void* actors[3];void* pets[3];void* lists[2];void* menus[2][12];void* windows[40];void* translator;void* image;
void* table[9];
const unsigned menuOff[]={0x4d8,0x4e0,0x4e8,0x4f0,0x4f8,0x500,0x508,0x558,0x560,0x568,0x4a0,0x4a8};
const unsigned menuSize[]={0x1030,0x100,0x1380,0x3450,0x100,0x1a0,0x3420,0x100,0x100,0x100,0x30,0x30};
template<class T>T& at(void* p,unsigned o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
void n(unsigned v){cap->add(&v,4);}void ptr(const void* p){cap->add(&p,sizeof(p));}
void invalid(){cap->issue=autotest::Capture::InvalidReport;}
void* object(unsigned size){if(blockCount==160)_exit(70);unsigned char* p=(unsigned char*)autotest::allocate(size+32);if(!p)_exit(71);std::memset(p,0xd3,16);std::memset(p+16,0xa5,size);std::memset(p+16+size,0x6c,16);blocks[blockCount].p=p;blocks[blockCount++].size=size;return p+16;}
void str(const CEGUI::String& s){n(s.length());for(size_t j=0;j<s.length();++j)n(s[j]);}
void state(){ptr(at<void*>(ui,0x38));for(unsigned j=0;j<12;++j)ptr(at<void*>(ui,menuOff[j]));for(unsigned j=0;j<3;++j){ptr(at<void*>(actors[j],0x648));ptr(at<void*>(actors[j],0x650));}}
void begin(unsigned b,void* self){n(b);n(++calls[b]);n(step);ptr(self);state();}
void effect(unsigned b){if(!changed&&c->at==b&&calls[b]==c->nth){changed=1;switch(c->mutation){
 case 1:at<void*>(ui,0x38)=actors[1];break;
 case 2:at<void*>(ui,0x38)=0;break;
 case 3:for(unsigned j=0;j<12;++j)at<void*>(ui,menuOff[j])=menus[1][j];break;
 case 4:for(unsigned j=0;j<3;++j){at<void*>(actors[j],0x648)=lists[1];at<void*>(actors[j],0x650)=(char*)lists[1]+24;}break;
 case 5:for(unsigned j=0;j<3;++j)at<void*>(actors[j],0x650)=at<void*>(actors[j],0x648);break;
 case 6:at<void*>(lists[0],0)=pets[2];break;
 case 7:at<void*>(ui,0x240)=windows[35];at<void*>(ui,0x220)=windows[36];at<void*>(ui,0x208)=windows[37];break;
 case 8:at<void*>(ui,0x260)=windows[35];at<void*>(ui,0x2b0)=windows[36];break;
 }}if(c->fault==b&&calls[b]==c->faultNth)throw Failure(b);}
void text(void* self,const CEGUI::String& s){begin(Text,self);str(s);at<unsigned>(self,0x180)=s.length();effect(Text);}
void tip(void* self,const CEGUI::String& s){begin(Tip,self);str(s);at<unsigned>(self,0x184)=s.length();effect(Tip);}
void id(void* self,unsigned x){begin(ID,self);n(x);at<unsigned>(self,0x170)=x;effect(ID);}
void property(void* self,const CEGUI::String& k,const CEGUI::String& v){begin(Property,self);str(k);str(v);at<unsigned>(self,0x188)=v.length();effect(Property);}
void* getImage(void* self,const unsigned char* s){begin(Image,self);n(std::strlen((const char*)s));cap->add(s,std::strlen((const char*)s));effect(Image);return image;}
void imageString(CEGUI::String* result,void* p){begin(ImageString,p);effect(ImageString);new(result)CEGUI::String("set:Test image:Attack");}
void* singleton(){begin(Single,translator);effect(Single);return translator;}
void translate(std::wstring* result,void* self,const wchar_t* key){begin(Translate,self);size_t l=std::wcslen(key);n(l);cap->add(key,l*sizeof(wchar_t));effect(Translate);new(result)std::wstring(L"Left-click: \u03bb \u2603");}
void convert(std::string* result,const std::wstring& s){begin(Convert,translator);n(s.size());cap->add(s.data(),s.size()*sizeof(wchar_t));effect(Convert);new(result)std::string("Bind \xce\xbb \xe2\x98\x83");}
void bind(unsigned b,void* self,void* actor){begin(b,self);ptr(actor);at<void*>(self,0x20)=actor;at<unsigned>(self,0x28)^=calls[b];effect(b);}
void virtualBind(void* self,void* actor){bind(Virtual,self,actor);}void wrong(void* self,void* actor){bind(Wrong,self,actor);}
void combine(void* self,void* actor){bind(Combine,self,actor);}void enchant(void* self,void* actor){bind(Enchant,self,actor);}
void update(void* self){begin(Update,self);at<unsigned>(self,0x1900)^=0x12345678;effect(Update);}
void initialize(){autotest::g_arenaUsed=0;blockCount=step=changed=0;std::memset(calls,0,sizeof(calls));ui=object(sizeof(CGameUI));
 for(unsigned j=0;j<9;++j)table[j]=(void*)(j==7?virtualBind:wrong);
 for(unsigned j=0;j<3;++j){actors[j]=object(sizeof(CPlayer));at<void*>(actors[j],0)=j==2?(void*)(characterTable+2):(void*)(playerTable+2);pets[j]=object(0x80);}
 for(unsigned j=0;j<2;++j){lists[j]=object(24);for(unsigned k=0;k<3;++k)at<void*>(lists[j],k*8)=pets[(k+j)%3];}
 for(unsigned j=0;j<3;++j){at<void*>(actors[j],0x648)=lists[0];at<void*>(actors[j],0x650)=(char*)lists[0]+c->pets*8;}
 for(unsigned j=0;j<2;++j)for(unsigned k=0;k<12;++k){menus[j][k]=object(menuSize[k]);at<void*>(menus[j][k],0)=table;at<void*>(menus[j][k],0x20)=pets[2];}
 for(unsigned j=0;j<12;++j)at<void*>(ui,menuOff[j])=menus[0][j];at<void*>(ui,0x4b0)=object(0x30);
 for(unsigned j=0;j<40;++j){windows[j]=object(0x280);at<void*>(windows[j],0xb0)=windows[j];}
 at<void*>(ui,0x218)=windows[0];at<void*>(ui,0x240)=windows[1];at<void*>(ui,0x220)=windows[2];at<void*>(ui,0x208)=windows[3];at<void*>(ui,0x210)=windows[4];at<void*>(ui,0x238)=windows[5];
 for(unsigned j=0;j<10;++j){at<void*>(ui,0x260+j*8)=(c->mask&(1u<<j))?windows[6+j]:0;at<void*>(ui,0x2b0+j*8)=windows[16+j];at<void*>(ui,0x300+j*8)=windows[26+j];}
 translator=object(0x30);image=object(0x30);void* arg=c->kind==0?0:c->kind==1?actors[2]:actors[0];at<void*>(ui,0x38)=c->same?arg:actors[1];}
void redirect(detour::Set& d){TL_REDIRECT(d,imageFn,&getImage);TL_REDIRECT(d,updateFn,&update);TL_REDIRECT(d,combineFn,&combine);TL_REDIRECT(d,enchantFn,&enchant);TL_REDIRECT(d,singleFn,&singleton);TL_REDIRECT(d,translateFn,&translate);TL_REDIRECT(d,convertFn,&convert);
 d.redirect(textFn,textFn,&text);d.redirect(tipFn,tipFn,&tip);d.redirect(idFn,idFn,&id);d.redirect(propFn,propFn,&property);d.redirect(imageStringFn,imageStringFn,&imageString);}
void snapshot(){n(blockCount);for(unsigned j=0;j<blockCount;++j){Block& b=blocks[j];for(unsigned k=0;k<16;++k)if(b.p[k]!=0xd3||b.p[16+b.size+k]!=0x6c)invalid();n(b.size);cap->add(b.p,b.size+32);}for(unsigned j=0;j<Last;++j)n(calls[j]);n(changed);}
void side(void* p,autotest::Capture& out,bool candidate){c=(Case*)p;cap=&out;initialize();detour::Set d;redirect(d);if(d.failed()){invalid();return;}
 for(step=0;step<c->repeat;++step){autotest::Capture receipt;receipt.reset();void* arg=c->kind==0?0:c->kind==1?actors[2]:actors[0];bool caught=false;n(step);ptr(arg);
 try{autotest::invoke(receipt,candidate?&newPlayer:&oldPlayer,(CGameUI*)ui,(CCharacter*)arg);}catch(const Failure& e){caught=true;n(e.b);if(e.b!=c->fault)invalid();}catch(...){invalid();}
 n(caught);if(caught!=(c->fault!=0))invalid();n(receipt.callStarted);n(receipt.callCompleted);
 if(!step){out.callTarget=receipt.callTarget;out.callStarted=receipt.callStarted;out.callCompleted=receipt.callCompleted;}else if(receipt.callStarted!=1||receipt.callCompleted!=1)invalid();
 if(receipt.issue)out.issue=receipt.issue;
 }if(c->mutation&&!changed)invalid();snapshot();}
void oldSide(void* p,autotest::Capture& c){side(p,c,false);}void newSide(void* p,autotest::Capture& c){side(p,c,true);}
bool same(const autotest::Outcome& a,const autotest::Outcome& b){return a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);}
bool pair(const tlhybrid_host* host,autotest::Coverage& cov,Case& c,unsigned& count){autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);++count;bool okay=same(a,b);if(!c.fault){if(cov.observe(host,a,b))okay=false;}else okay=okay&&a.capture.callStarted==1&&b.capture.callStarted==1&&!a.capture.callCompleted&&!b.capture.callCompleted&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget);
 if(!okay){size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;host->log("    rebind #%u kind=%u pets=%u mask=%x same=%u repeat=%u mutation=%u at=%u nth=%u fault=%u/%u status=%d/%d valid=%u/%u issue=%u/%u complete=%u/%u bytes=%lu/%lu first=%lu\n",count,c.kind,c.pets,c.mask,unsigned(c.same),c.repeat,c.mutation,c.at,c.nth,c.fault,c.faultNth,a.childStatus,b.childStatus,unsigned(a.reportValid),unsigned(b.reportValid),a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)first);cov.report(host);}return okay;}
}
TL_TEST(gameui_player_rebinding){autotest::Coverage coverage("gameui_player_rebinding",(uint64_t)(uintptr_t)&oldPlayer);unsigned count=0;
 const unsigned masks[]={0,1,512,0x155,0x2aa,1023};
 for(unsigned kind=0;kind<3;++kind)for(unsigned pets=0;pets<4;++pets)for(unsigned same=0;same<2;++same)for(unsigned m=0;m<6;++m){Case c;c.kind=kind;c.pets=pets;c.same=same;c.mask=masks[m];c.repeat=2;if(!pair(host,coverage,c,count))return 1;}
 for(unsigned b=Text;b<=Update;++b)for(unsigned mutation=1;mutation<=8;++mutation){Case c;c.at=b;c.mutation=mutation;c.repeat=2;if(!pair(host,coverage,c,count))return 1;}
 for(unsigned nth=1;nth<=7;++nth)for(unsigned mutation=1;mutation<=6;++mutation){Case c;c.at=Virtual;c.nth=nth;c.mutation=mutation;c.repeat=2;if(!pair(host,coverage,c,count))return 1;}
 coverage.report(host);host->log("    %u completed player-rebinding call pairs\n",count);return coverage.completed!=count||coverage.different||coverage.missing;}
TL_TEST(gameui_player_rebinding_exceptions){autotest::Coverage coverage("exceptions",(uint64_t)(uintptr_t)&oldPlayer);unsigned count=0;for(unsigned b=Text;b<=Update;++b){unsigned total=b==Text?40:b==Tip||b==ID?10:b==Property?13:b==Virtual?7:1;for(unsigned nth=1;nth<=total;++nth){Case c;c.fault=b;c.faultNth=nth;if(!pair(host,coverage,c,count))return 1;}}host->log("    %u exception witnesses passed, excluded from completed coverage\n",count);return 0;}
