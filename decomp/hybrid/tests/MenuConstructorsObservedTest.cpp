#include <cstring>
#include <string>
#include <new>
#include "AutoTest.h"
#include "ObservedWitness.h"
#include "Detour.h"
// One actual constructor invocation per case, including static cache states,
// callback order, untouched padding, and exception cleanup.
TL_ORIGINAL(void,original0,(void*,void*,void*,void*,void*,void*),"_ZN12COptionsMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
extern "C" void candidate0(void*,void*,void*,void*,void*,void*) __asm__("_ZN12COptionsMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager");
TL_ORIGINAL(void,original1,(void*,void*,void*,void*,void*,void*),"_ZN13CSettingsMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
extern "C" void candidate1(void*,void*,void*,void*,void*,void*) __asm__("_ZN13CSettingsMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager");
TL_ORIGINAL(void,original2,(void*,void*,void*,void*,void*,void*),"_ZN8CTipMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
extern "C" void candidate2(void*,void*,void*,void*,void*,void*) __asm__("_ZN8CTipMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager");
TL_ORIGINAL(void,original3,(void*,void*,void*,void*,void*,void*),"_ZN10CModalMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
extern "C" void candidate3(void*,void*,void*,void*,void*,void*) __asm__("_ZN10CModalMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager");
TL_ORIGINAL(void,original4,(void*,void*,void*,void*,void*,void*),"_ZN11CDialogMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
extern "C" void candidate4(void*,void*,void*,void*,void*,void*) __asm__("_ZN11CDialogMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager");
TL_ORIGINAL(void,original5,(void*,void*,void*,void*,void*,void*),"_ZN8CDieMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
extern "C" void candidate5(void*,void*,void*,void*,void*,void*) __asm__("_ZN8CDieMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager");
TL_ORIGINAL(void,original6,(void*,void*,void*,void*,void*,void*),"_ZN16CQuestDialogMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
extern "C" void candidate6(void*,void*,void*,void*,void*,void*) __asm__("_ZN16CQuestDialogMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager");
TL_ORIGINAL(void,original7,(void*,void*,void*,void*,void*,void*),"_ZN14CCinematicMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
extern "C" void candidate7(void*,void*,void*,void*,void*,void*) __asm__("_ZN14CCinematicMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager");
TL_FUNCTION(target_base,"_ZN13CDropdownMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManagerj")
TL_FUNCTION(target_destroy,"_ZN13CDropdownMenuD1Ev")
TL_FUNCTION(target_singleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(target_translate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(target_title,"_ZN13CDropdownMenu8setTitleERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_runic,"_ZN10CRunicCoreD1Ev")
TL_FUNCTION(create0,"_ZN12COptionsMenu11createMenusEv")
TL_FUNCTION(create1,"_ZN13CSettingsMenu11createMenusEv")
TL_FUNCTION(create2,"_ZN8CTipMenu11createMenusEv")
TL_FUNCTION(create3,"_ZN10CModalMenu11createMenusEv")
TL_FUNCTION(create4,"_ZN11CDialogMenu11createMenusEv")
TL_FUNCTION(create5,"_ZN8CDieMenu11createMenusEv")
TL_FUNCTION(create6,"_ZN16CQuestDialogMenu11createMenusEv")
TL_FUNCTION(create7,"_ZN14CCinematicMenu11createMenusEv")
TL_ORIGINAL(void,originalQuestDestroy,(void*),"_ZN10CQuestMenuD1Ev")
extern "C" void candidateQuestDestroy(void*) __asm__("_ZN10CQuestMenuD1Ev");

namespace {
struct Case {unsigned op,seed,cache,mode;};
Case* input;autotest::Capture* output;void* active;void* params[5];unsigned size;
void num(unsigned x){output->add(&x,4);}void ptr(void*p){output->add(&p,8);}
void text(const std::wstring&s){num(s.size());if(!s.empty())output->add(s.data(),s.size()*sizeof(wchar_t));}
void state(){
 unsigned char copy[1024];std::memcpy(copy,active,size);
 unsigned stringOffset=input->op==6?0x130:input->op==7?0xe0:0;
 if(stringOffset){const std::string&v=*reinterpret_cast<std::string*>(static_cast<char*>(active)+stringOffset);num(v.size());if(!v.empty())output->add(v.data(),v.size());std::memset(copy+stringOffset,0,8);}
 output->add(copy,size);
}
void base(void*self,void*ui,void*settings,void*scene,void*parent,void*resources,unsigned kind){
 num(1);ptr(self);ptr(ui);ptr(settings);ptr(scene);ptr(parent);ptr(resources);num(kind);
 output->add(self,size);std::memset(self,(input->seed*17+31)&255,0xc0);
}
void destroy(void*self){num(5);ptr(self);state();}
void create(void*self){num(2);ptr(self);state();static_cast<unsigned char*>(self)[0x32]^=0x55;
 if(input->mode==1)throw 101;
 if((input->seed&1)==0)static_cast<unsigned char*>(self)[0xc0]^=1;
}
void* singleton(){num(3);return params[0];}
std::wstring translate(void*self,const wchar_t*source){num(4);ptr(self);text(std::wstring(source));state();if(input->mode==2)throw 102;
 return input->seed%3==0?L"":input->seed%3==1?L"Translated \u0414\u0438\u0430\u043b\u043e\u0433":L"A longer translated menu heading with punctuation !?";
}
void title(void*self,const std::wstring&value){num(6);ptr(self);text(value);state();if(input->mode==3)throw 103;static_cast<unsigned char*>(self)[0x31]^=0x23;}
void runic(void*self){num(7);ptr(self);output->add(self,0x388);}
void deleteOwned(void*object){num(8);ptr(object);output->add(active,0x388);if(input->seed%3==1){void*nil=NULL;std::memcpy(static_cast<char*>(active)+0x1d8,&nil,8);}}
void side(Case&c,bool ours,autotest::Capture&out){
 input=&c;output=&out;unsigned long long bytes[128],p[5][4];std::memset(bytes,(c.seed*37+19)&255,sizeof(bytes));std::memset(p,0,sizeof(p));active=bytes;
 for(unsigned i=0;i<5;++i)params[i]=p[i];if(c.seed&1)params[3]=NULL;if(c.seed&2)params[4]=NULL;
 const unsigned sizes[]={200,336,232,248,248,264,520,256};size=c.op<8?sizes[c.op]:0x388;
 const uintptr_t guards[]={0x14cb328,0x14d1830,0x1528e28,0x14c9de8,0x14beb10,0x14c0098,0x14ced18,0x1533720};
 if(c.op<8){
  uint64_t*guard=reinterpret_cast<uint64_t*>(guards[c.op]);*guard=c.cache==0?0:1;
  std::wstring*cache=new(reinterpret_cast<void*>(guards[c.op]+8))std::wstring;
  if(c.cache==2)*cache=L"Already cached \u0418\u0433\u0440\u0430";
  detour::Set patches;TL_REDIRECT(patches,target_base,&base);TL_REDIRECT(patches,target_destroy,&destroy);TL_REDIRECT(patches,target_singleton,&singleton);TL_REDIRECT(patches,target_translate,&translate);TL_REDIRECT(patches,target_title,&title);
 TL_REDIRECT(patches,create0,&create);
 TL_REDIRECT(patches,create1,&create);
 TL_REDIRECT(patches,create2,&create);
 TL_REDIRECT(patches,create3,&create);
 TL_REDIRECT(patches,create4,&create);
 TL_REDIRECT(patches,create5,&create);
 TL_REDIRECT(patches,create6,&create);
 TL_REDIRECT(patches,create7,&create);
 if(patches.failed())_exit(41);
 void(*fn)(void*,void*,void*,void*,void*,void*)=NULL;
 switch(c.op){
 case 0:fn=ours?candidate0:original0;break;
 case 1:fn=ours?candidate1:original1;break;
 case 2:fn=ours?candidate2:original2;break;
 case 3:fn=ours?candidate3:original3;break;
 case 4:fn=ours?candidate4:original4;break;
 case 5:fn=ours?candidate5:original5;break;
 case 6:fn=ours?candidate6:original6;break;
 case 7:fn=ours?candidate7:original7;break;

 }
 if(!autotest::beginInvocation(out,fn))return;
 unsigned fault=0;
 try{fn(bytes,params[0],params[1],params[2],params[3],params[4]);out.callCompleted=1;num(1000);}catch(int n){fault=static_cast<unsigned>(n);num(n);}
 state();text(*cache);out.add(guard,8);patches.restore();observed_witness::finish(out,fault);
 }else{
  void*table[2]={NULL,reinterpret_cast<void*>(&deleteOwned)};void*objects[2][4]={{table,NULL,NULL,NULL},{table,NULL,NULL,NULL}};
  void*a=c.seed&1?NULL:objects[0];void*b=c.seed&2?NULL:objects[1];std::memcpy(static_cast<char*>(active)+0x1b0,&a,8);std::memcpy(static_cast<char*>(active)+0x1d8,&b,8);
  void**list=c.seed%4?new void*[c.seed%9+1]:NULL;for(unsigned i=0;list&&i<c.seed%9+1;++i)list[i]=objects[i%2];std::memcpy(static_cast<char*>(active)+0x370,&list,8);
  detour::Set patches;TL_REDIRECT(patches,target_runic,&runic);if(patches.failed())_exit(42);
  autotest::invoke(out,ours?candidateQuestDestroy:originalQuestDestroy,active);out.add(active,size);patches.restore();observed_witness::finish(out,0);
 }
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned first,unsigned last,const char*name){const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2,(uint64_t)(uintptr_t)original3,(uint64_t)(uintptr_t)original4,(uint64_t)(uintptr_t)original5,(uint64_t)(uintptr_t)original6,(uint64_t)(uintptr_t)original7,(uint64_t)(uintptr_t)originalQuestDestroy};
 for(unsigned op=first;op<last;++op){autotest::Coverage coverage(name,addresses[op]);unsigned witnesses=0;for(unsigned n=0;n<192;++n){Case c={op,n,n%3,(n/3)%4};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
  const unsigned expectedFault=op>=8?0u:c.mode==1?101u:c.mode==2&&c.cache!=2?102u:c.mode==3?103u:0u;
  if(observed_witness::observe(host,coverage,a,b,expectedFault,witnesses)){host->log("    constructor op %u case %u cache %u mode %u status %d/%d bytes %lu/%lu\n",op,n,c.cache,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}
  if(expectedFault&&witnesses==1&&!observed_witness::negativeControls(host,coverage,a,b,expectedFault))return 1;
 }coverage.report(host);if(!observed_witness::totals(host,coverage,witnesses,op<8?64u:192u,op<8?128u:0u))return 1;}return 0;
}
}
TL_TEST(menu_constructors_observed){return run(host,0,8,"menu_constructors_observed");}
TL_TEST(quest_destructor_observed){return run(host,8,9,"quest_destructor_observed");}
