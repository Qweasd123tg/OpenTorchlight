#include "AutoTest.h"
#include "tests/Detour.h"
#include <X11/Xlib.h>
#include <clocale>
#include <cstdlib>
#include <cstring>
TL_ORIGINAL(int,gbO,(void*,unsigned*,const unsigned char*,int),"gb2312_mbtowc")
extern "C" int gbC(void*,unsigned*,const unsigned char*,int) __asm__("__tlhybrid_local_490_gb2312_mbtowc");
TL_ORIGINAL(int,jpO,(char*,int),"XConvertEucJpToUtf8")
extern "C" int jpC(char*,int) __asm__("XConvertEucJpToUtf8");
TL_ORIGINAL(int,cnO,(char*,int),"XConvertEucCnToUtf8")
extern "C" int cnC(char*,int) __asm__("XConvertEucCnToUtf8");
TL_ORIGINAL(int,gbcO,(char*,int),"XConvertGb2312ToUtf8")
extern "C" int gbcC(char*,int) __asm__("XConvertGb2312ToUtf8");
TL_ORIGINAL(int,cpO,(char*,int),"XConvertCp936extToUtf8")
extern "C" int cpC(char*,int) __asm__("XConvertCp936extToUtf8");
TL_ORIGINAL(int,bigO,(char*,int),"XConvertBig5ToUtf8")
extern "C" int bigC(char*,int) __asm__("XConvertBig5ToUtf8");
TL_ORIGINAL(int,krO,(char*,int),"XConvertEucKrToUtf8")
extern "C" int krC(char*,int) __asm__("XConvertEucKrToUtf8");
TL_ORIGINAL(int,twO,(char*,int),"XConvertEucTwToUtf8")
extern "C" int twC(char*,int) __asm__("XConvertEucTwToUtf8");
TL_ORIGINAL(int,eucO,(const char*,char*,int,int),"XConvertEucToUtf8")
extern "C" int eucC(const char*,char*,int,int) __asm__("XConvertEucToUtf8");
TL_ORIGINAL(int,lookupO,(XIC,XKeyPressedEvent*,char*,int,KeySym*,Status*),"XUtf8LookupString")
extern "C" int lookupC(XIC,XKeyPressedEvent*,char*,int,KeySym*,Status*) __asm__("XUtf8LookupString");
TL_ORIGINAL(int,decO,(const unsigned char*,int,unsigned*),"XConvertUtf8ToUcs")
extern "C" int decC(const unsigned char*,int,unsigned*) __asm__("XConvertUtf8ToUcs");
TL_ORIGINAL(int,encO,(unsigned,char*),"XConvertUcsToUtf8")
extern "C" int encC(unsigned,char*) __asm__("XConvertUcsToUtf8");
TL_ORIGINAL(int,lenO,(const unsigned char*,int),"XUtf8CharByteLen")
extern "C" int lenC(const unsigned char*,int) __asm__("XUtf8CharByteLen");
TL_ORIGINAL(int,countO,(const unsigned char*,int),"XCountUtf8Char")
extern "C" int countC(const unsigned char*,int) __asm__("XCountUtf8Char");
TL_ORIGINAL(int,fastO,(const unsigned char*,int,unsigned*),"XFastConvertUtf8ToUcs")
extern "C" int fastC(const unsigned char*,int,unsigned*) __asm__("XFastConvertUtf8ToUcs");
TL_ORIGINAL(unsigned,ksO,(KeySym),"KeySymToUcs4")
extern "C" unsigned ksC(KeySym) __asm__("KeySymToUcs4");
TL_ORIGINAL(long,kslO,(KeySym),"XKeysymToUcs")
extern "C" long kslC(KeySym) __asm__("XKeysymToUcs");
TL_ORIGINAL(unsigned,decodeO,(const char*,const char*,int*),"fl_utf8decode")
extern "C" unsigned decodeC(const char*,const char*,int*) __asm__("fl_utf8decode");
TL_ORIGINAL(const char*,fwdO,(const char*,const char*,const char*),"fl_utf8fwd")
extern "C" const char* fwdC(const char*,const char*,const char*) __asm__("fl_utf8fwd");
TL_ORIGINAL(const char*,backO,(const char*,const char*,const char*),"fl_utf8back")
extern "C" const char* backC(const char*,const char*,const char*) __asm__("fl_utf8back");
TL_ORIGINAL(int,bytesO,(unsigned),"fl_utf8bytes")
extern "C" int bytesC(unsigned) __asm__("fl_utf8bytes");
TL_ORIGINAL(int,encodeO,(unsigned,char*),"fl_utf8encode")
extern "C" int encodeC(unsigned,char*) __asm__("fl_utf8encode");
TL_ORIGINAL(unsigned,ucs16O,(unsigned,unsigned short*,unsigned),"fl_ucs_to_Utf16")
extern "C" unsigned ucs16C(unsigned,unsigned short*,unsigned) __asm__("fl_ucs_to_Utf16");
TL_ORIGINAL(unsigned,to16O,(const char*,unsigned,unsigned short*,unsigned),"fl_utf8toUtf16")
extern "C" unsigned to16C(const char*,unsigned,unsigned short*,unsigned) __asm__("fl_utf8toUtf16");
TL_ORIGINAL(unsigned,towcO,(const char*,unsigned,wchar_t*,unsigned),"fl_utf8towc")
extern "C" unsigned towcC(const char*,unsigned,wchar_t*,unsigned) __asm__("fl_utf8towc");
TL_ORIGINAL(unsigned,toaO,(const char*,unsigned,char*,unsigned),"fl_utf8toa")
extern "C" unsigned toaC(const char*,unsigned,char*,unsigned) __asm__("fl_utf8toa");
TL_ORIGINAL(unsigned,fromwcO,(char*,unsigned,const wchar_t*,unsigned),"fl_utf8fromwc")
extern "C" unsigned fromwcC(char*,unsigned,const wchar_t*,unsigned) __asm__("fl_utf8fromwc");
TL_ORIGINAL(unsigned,fromaO,(char*,unsigned,const char*,unsigned),"fl_utf8froma")
extern "C" unsigned fromaC(char*,unsigned,const char*,unsigned) __asm__("fl_utf8froma");
TL_ORIGINAL(int,validO,(const char*,unsigned),"fl_utf8test")
extern "C" int validC(const char*,unsigned) __asm__("fl_utf8test");
TL_ORIGINAL(int,widthO,(unsigned),"fl_wcwidth_")
extern "C" int widthC(unsigned) __asm__("fl_wcwidth_");
TL_ORIGINAL(int,widthsO,(const char*),"fl_wcwidth")
extern "C" int widthsC(const char*) __asm__("fl_wcwidth");
TL_ORIGINAL(int,localeO,(),"fl_utf8locale")
extern "C" int localeC() __asm__("fl_utf8locale");
TL_ORIGINAL(unsigned,frommbO,(char*,unsigned,const char*,unsigned),"fl_utf8from_mb")
extern "C" unsigned frommbC(char*,unsigned,const char*,unsigned) __asm__("fl_utf8from_mb");
TL_ORIGINAL(unsigned,tombO,(const char*,unsigned,char*,unsigned),"fl_utf8to_mb")
extern "C" unsigned tombC(const char*,unsigned,char*,unsigned) __asm__("fl_utf8to_mb");
namespace {
void(*originals[])()={reinterpret_cast<void(*)()>(gbO),reinterpret_cast<void(*)()>(jpO),reinterpret_cast<void(*)()>(cnO),reinterpret_cast<void(*)()>(gbcO),reinterpret_cast<void(*)()>(cpO),reinterpret_cast<void(*)()>(bigO),reinterpret_cast<void(*)()>(krO),reinterpret_cast<void(*)()>(twO),reinterpret_cast<void(*)()>(eucO),reinterpret_cast<void(*)()>(lookupO),reinterpret_cast<void(*)()>(decO),reinterpret_cast<void(*)()>(encO),reinterpret_cast<void(*)()>(lenO),reinterpret_cast<void(*)()>(countO),reinterpret_cast<void(*)()>(fastO),reinterpret_cast<void(*)()>(ksO),reinterpret_cast<void(*)()>(kslO),reinterpret_cast<void(*)()>(decodeO),reinterpret_cast<void(*)()>(fwdO),reinterpret_cast<void(*)()>(backO),reinterpret_cast<void(*)()>(bytesO),reinterpret_cast<void(*)()>(encodeO),reinterpret_cast<void(*)()>(ucs16O),reinterpret_cast<void(*)()>(to16O),reinterpret_cast<void(*)()>(towcO),reinterpret_cast<void(*)()>(toaO),reinterpret_cast<void(*)()>(fromwcO),reinterpret_cast<void(*)()>(fromaO),reinterpret_cast<void(*)()>(validO),reinterpret_cast<void(*)()>(widthO),reinterpret_cast<void(*)()>(widthsO),reinterpret_cast<void(*)()>(localeO),reinterpret_cast<void(*)()>(frommbO),reinterpret_cast<void(*)()>(tombO)};
void(*candidates[])()={reinterpret_cast<void(*)()>(gbC),reinterpret_cast<void(*)()>(jpC),reinterpret_cast<void(*)()>(cnC),reinterpret_cast<void(*)()>(gbcC),reinterpret_cast<void(*)()>(cpC),reinterpret_cast<void(*)()>(bigC),reinterpret_cast<void(*)()>(krC),reinterpret_cast<void(*)()>(twC),reinterpret_cast<void(*)()>(eucC),reinterpret_cast<void(*)()>(lookupC),reinterpret_cast<void(*)()>(decC),reinterpret_cast<void(*)()>(encC),reinterpret_cast<void(*)()>(lenC),reinterpret_cast<void(*)()>(countC),reinterpret_cast<void(*)()>(fastC),reinterpret_cast<void(*)()>(ksC),reinterpret_cast<void(*)()>(kslC),reinterpret_cast<void(*)()>(decodeC),reinterpret_cast<void(*)()>(fwdC),reinterpret_cast<void(*)()>(backC),reinterpret_cast<void(*)()>(bytesC),reinterpret_cast<void(*)()>(encodeC),reinterpret_cast<void(*)()>(ucs16C),reinterpret_cast<void(*)()>(to16C),reinterpret_cast<void(*)()>(towcC),reinterpret_cast<void(*)()>(toaC),reinterpret_cast<void(*)()>(fromwcC),reinterpret_cast<void(*)()>(fromaC),reinterpret_cast<void(*)()>(validC),reinterpret_cast<void(*)()>(widthC),reinterpret_cast<void(*)()>(widthsC),reinterpret_cast<void(*)()>(localeC),reinterpret_cast<void(*)()>(frommbC),reinterpret_cast<void(*)()>(tombC)};
struct Case {unsigned target,base,mode;};
void word(autotest::Capture&o,unsigned x){o.add(&x,4);}
const unsigned scalars[]={0,1,0x1f,0x7f,0x80,0x7ff,0x800,0xd7ff,0xd800,0xdbff,0xdc00,0xdfff,0xe000,0xffff,0x10000,0x10ffff,0x110000,0x1fffff,0x200000,0x3ffffff,0x4000000,0x7fffffff,0x80000000,0xffffffff};
void side(void*raw,autotest::Capture&o,bool ours){Case c=*static_cast<Case*>(raw);unsigned t=c.target;void(*fn)()=ours?candidates[t]:originals[t];if(!autotest::beginInvocation(o,fn))return;
for(unsigned j=0;j<256;++j){unsigned v=c.base+j,mode=c.mode;unsigned char storage[160];char dst[160];wchar_t wide[32];std::memset(storage,0,160);std::memset(dst,0xa5,160);for(unsigned z=0;z<32;++z)wide[z]=scalars[(v+z)%24];unsigned char*b=storage+16;for(unsigned z=0;z<16;++z)b[z]=z?((mode&1)?0xbf:0x80):v&255;b[1]=v>>8;b[8]=0;unsigned u=0xa5a5a5a5;int n=0xa5a5;unsigned r=0;long lr=0;unsigned length=mode%9;unsigned cap[]={0,1,2,3,4,7,8,16,32};unsigned capacity=cap[mode%9];unsigned scalar=scalars[v%24];if(t>=1&&t<=8&&mode==3){b[0]=0x8f;b[1]=v;b[2]=v>>8;}if(t>=10&&!(t==15||t==16||t==29))b[1]=(mode&1)?0xbf:0x80;
switch(t){
case 0:r=(ours?gbC:gbO)(NULL,&u,b,mode%3);break;
case 1:r=(ours?jpC:jpO)(reinterpret_cast<char*>(b),mode<4?mode:2);break;
case 2:r=(ours?cnC:cnO)(reinterpret_cast<char*>(b),mode<4?mode:2);break;
case 3:r=(ours?gbcC:gbcO)(reinterpret_cast<char*>(b),mode<4?mode:2);break;
case 4:r=(ours?cpC:cpO)(reinterpret_cast<char*>(b),mode<4?mode:2);break;
case 5:r=(ours?bigC:bigO)(reinterpret_cast<char*>(b),mode<4?mode:2);break;
case 6:r=(ours?krC:krO)(reinterpret_cast<char*>(b),mode<4?mode:2);break;
case 7:r=(ours?twC:twO)(reinterpret_cast<char*>(b),mode<4?mode:2);break;
case 8:{const char*locales[]={NULL,"","UTF-8","utf8","ja_JP","Big5","big5","GBK","gbk","zh_CN","zh_CN.EUC","zh_TW","zh_TW.EUC","chinese-t","chinese-","ko_KR","unknown"};r=(ours?eucC:eucO)(locales[mode%17],reinterpret_cast<char*>(b),2,128);break;}
case 10:r=(ours?decC:decO)(b,length,&u);break;
case 11:r=(ours?encC:encO)(scalar,dst+16);break;
case 12:r=(ours?lenC:lenO)(b,length);break;
case 13:r=(ours?countC:countO)(b,length);break;
case 14:r=(ours?fastC:fastO)(b,length,&u);break;
case 15:r=(ours?ksC:ksO)(static_cast<KeySym>(mode==1?(v|0x01000000):(mode==2?(static_cast<unsigned long>(scalars[v%24])|0x01000000UL):v)));break;
case 16:lr=(ours?kslC:kslO)(static_cast<KeySym>(mode==1?(v|0x01000000):(mode==2?(static_cast<unsigned long>(scalars[v%24])|0x01000000UL):v)));break;
case 17:r=(ours?decodeC:decodeO)(reinterpret_cast<char*>(b),(mode&16)?NULL:reinterpret_cast<char*>(b+length),(mode&32)?NULL:&n);break;
case 18:case 19:{const char*start=reinterpret_cast<char*>(b);const char*rr=(t==18?(ours?fwdC:fwdO):(ours?backC:backO))(start+(mode%8),start,start+8);r=rr-start;break;}
case 20:r=(ours?bytesC:bytesO)(scalar);break;
case 21:r=(ours?encodeC:encodeO)(scalar,dst+16);break;
case 22:r=(ours?ucs16C:ucs16O)(scalar,reinterpret_cast<unsigned short*>(dst+16),capacity);break;
case 23:r=(ours?to16C:to16O)(reinterpret_cast<char*>(b),length,reinterpret_cast<unsigned short*>(dst+16),capacity);break;
case 24:r=(ours?towcC:towcO)(reinterpret_cast<char*>(b),length,reinterpret_cast<wchar_t*>(dst+16),capacity);break;
case 25:r=(ours?toaC:toaO)(reinterpret_cast<char*>(b),length,dst+16,capacity);break;
case 26:r=(ours?fromwcC:fromwcO)(dst+16,capacity,wide,length);break;
case 27:r=(ours?fromaC:fromaO)(dst+16,capacity,reinterpret_cast<char*>(b),length);break;
case 28:r=(ours?validC:validO)(reinterpret_cast<char*>(b),length);break;
case 29:r=(ours?widthC:widthO)(v);break;
case 30:r=(ours?widthsC:widthsO)(reinterpret_cast<char*>(b));break;
case 31:{unsetenv("LC_CTYPE");unsetenv("LC_ALL");unsetenv("LANG");const char*names[]={"LC_CTYPE","LC_ALL","LANG"};const char*values[]={"C","C.UTF-8","en_US.utf8","","POSIX"};if(mode) setenv(names[(mode/5)%3],values[mode%5],1);r=(ours?localeC:localeO)();setenv("LC_CTYPE","C",1);u=(ours?localeC:localeO)();break;}
case 32:case 33:{setlocale(LC_CTYPE,(mode&16)?"C.UTF-8":"C");setenv("LC_ALL",(mode&32)?"C":"en_US.UTF-8",1);unsetenv("LC_CTYPE");unsetenv("LANG");r=t==32?(ours?frommbC:frommbO)(dst+16,capacity,reinterpret_cast<char*>(b),length):(ours?tombC:tombO)(reinterpret_cast<char*>(b),length,dst+16,capacity);break;}
default:o.issue=autotest::Capture::InvalidReport;return;
}
word(o,r);o.add(&lr,sizeof(lr));word(o,u);o.add(&n,4);o.add(dst,160);o.add(storage,160);
}o.callCompleted=1;}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
static int runFltkPure(const tlhybrid_host*host,unsigned t){int failures=0;autotest::Stats stats={0,0,0};char name[80];std::sprintf(name,"complete_fltk_source_%u",t);autotest::Coverage cov(name,reinterpret_cast<uintptr_t>(originals[t]));unsigned cases=0;unsigned modes=t==0?3:t<=7?4:t==8?17:t==17?64:(t==31?16:((t==32||t==33)?64:9));unsigned batches=(t==0||(t>=1&&t<=7)||t==15||t==16)?256:t==29?4352:3;if(t==29)modes=1;if(t==15||t==16)modes=3;for(unsigned mode=0;mode<modes;++mode)for(unsigned batch=0;batch<batches;++batch){Case c={t,batch*256,mode};bool ok=autotest::compareCase(original,candidate,&c,stats,host,name,cases++,&cov);TL_CHECK(failures,ok);}cov.report(host);failures+=stats.incomplete+(cov.completed!=cases);return failures;}

TL_TEST(complete_fltk_source_0){return runFltkPure(host,0);}
TL_TEST(complete_fltk_source_1){return runFltkPure(host,1);}
TL_TEST(complete_fltk_source_2){return runFltkPure(host,2);}
TL_TEST(complete_fltk_source_3){return runFltkPure(host,3);}
TL_TEST(complete_fltk_source_4){return runFltkPure(host,4);}
TL_TEST(complete_fltk_source_5){return runFltkPure(host,5);}
TL_TEST(complete_fltk_source_6){return runFltkPure(host,6);}
TL_TEST(complete_fltk_source_7){return runFltkPure(host,7);}
TL_TEST(complete_fltk_source_8){return runFltkPure(host,8);}
TL_TEST(complete_fltk_source_10){return runFltkPure(host,10);}
TL_TEST(complete_fltk_source_11){return runFltkPure(host,11);}
TL_TEST(complete_fltk_source_12){return runFltkPure(host,12);}
TL_TEST(complete_fltk_source_13){return runFltkPure(host,13);}
TL_TEST(complete_fltk_source_14){return runFltkPure(host,14);}
TL_TEST(complete_fltk_source_15){return runFltkPure(host,15);}
TL_TEST(complete_fltk_source_16){return runFltkPure(host,16);}
TL_TEST(complete_fltk_source_17){return runFltkPure(host,17);}
TL_TEST(complete_fltk_source_18){return runFltkPure(host,18);}
TL_TEST(complete_fltk_source_19){return runFltkPure(host,19);}
TL_TEST(complete_fltk_source_20){return runFltkPure(host,20);}
TL_TEST(complete_fltk_source_21){return runFltkPure(host,21);}
TL_TEST(complete_fltk_source_22){return runFltkPure(host,22);}
TL_TEST(complete_fltk_source_23){return runFltkPure(host,23);}
TL_TEST(complete_fltk_source_24){return runFltkPure(host,24);}
TL_TEST(complete_fltk_source_25){return runFltkPure(host,25);}
TL_TEST(complete_fltk_source_26){return runFltkPure(host,26);}
TL_TEST(complete_fltk_source_27){return runFltkPure(host,27);}
TL_TEST(complete_fltk_source_28){return runFltkPure(host,28);}
TL_TEST(complete_fltk_source_29){return runFltkPure(host,29);}
TL_TEST(complete_fltk_source_30){return runFltkPure(host,30);}
TL_TEST(complete_fltk_source_31){return runFltkPure(host,31);}
TL_TEST(complete_fltk_source_32){return runFltkPure(host,32);}
TL_TEST(complete_fltk_source_33){return runFltkPure(host,33);}
