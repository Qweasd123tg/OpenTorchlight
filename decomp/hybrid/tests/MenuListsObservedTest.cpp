#include <cstring>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#include "TArrayList.h"
TL_ORIGINAL(void,original0,(void*,void*),"_ZN13CDropdownMenu15addMenuListenerEP13iMenuListener")
extern "C" void candidate0(void*,void*) __asm__("_ZN13CDropdownMenu15addMenuListenerEP13iMenuListener");
TL_ORIGINAL(void,original1,(void*,void*),"_ZN13CDropdownMenu18removeMenuListenerEP13iMenuListener")
extern "C" void candidate1(void*,void*) __asm__("_ZN13CDropdownMenu18removeMenuListenerEP13iMenuListener");
TL_ORIGINAL(void,original2,(void*,int,int),"_ZN13CDropdownMenu14broadcastEventE10EMENU_TYPE11EMENU_EVENT")
extern "C" void candidate2(void*,int,int) __asm__("_ZN13CDropdownMenu14broadcastEventE10EMENU_TYPE11EMENU_EVENT");
TL_ORIGINAL(bool,original3,(void*,void*),"_ZN10CQuestMenu16handle_MouseOverERKN5CEGUI9EventArgsE")
extern "C" bool candidate3(void*,void*) __asm__("_ZN10CQuestMenu16handle_MouseOverERKN5CEGUI9EventArgsE");
TL_ORIGINAL(bool,original4,(void*,void*),"_ZN10CQuestMenu15handle_MouseOutERKN5CEGUI9EventArgsE")
extern "C" bool candidate4(void*,void*) __asm__("_ZN10CQuestMenu15handle_MouseOutERKN5CEGUI9EventArgsE");
TL_ORIGINAL(void,original5,(void*),"_ZN17CContinueGameMenu10scrollDownEv")
extern "C" void candidate5(void*) __asm__("_ZN17CContinueGameMenu10scrollDownEv");
TL_FUNCTION(rewardsFn,"_ZN13CQuestRewards14getRewardItemsEv")
TL_FUNCTION(updateListFn,"_ZN17CContinueGameMenu19updateCharacterListEv")

namespace {
struct Case{unsigned op,seed;};
struct List{void**data;unsigned count,capacity,grow;};
void* nodes[8];void* selfObject;TArrayList<void*>*active;TArrayList<void*>*pending;autotest::Capture*cap;unsigned mode,callCount;List*rewardList;
void number(unsigned n){cap->add(&n,4);}unsigned id(void*p){if(!p)return 0;for(unsigned i=0;i<8;++i)if(nodes[i]==p)return i+1;return p==selfObject?9:999;}
void pointer(void*p,unsigned offset,void*v){std::memcpy(static_cast<char*>(p)+offset,&v,8);}void integer(void*p,unsigned offset,int v){std::memcpy(static_cast<char*>(p)+offset,&v,4);}
void eventCallback(void*p,void*menu,int type,int event){number(id(p));number(id(menu));number(type);number(event);
 if(callCount++==0){if(mode==1)active->add(nodes[7]);if(mode==2&&active->size())active->removeAt(0);if(mode==3)pending->add(p);if(mode==4)active->clear();if(mode==5)active->remove(nodes[1]);}}
List*rewards(void*p){number(20);number(id(p));return rewardList;}
void updateList(void*p){number(21);number(id(p));cap->add(static_cast<char*>(p)+0xc4,4);integer(p,0xc0,0x43210000u|mode);}
void listCapture(TArrayList<void*>*p){List&v=*reinterpret_cast<List*>(p);number(v.count);number(v.capacity);number(v.grow);number(v.data!=NULL);if(v.count>64)_exit(51);for(unsigned i=0;i<v.count;++i)number(id(v.data[i]));}
void side(Case&c,bool ours,autotest::Capture&out){
 unsigned long long self[80],objects[8][300]={{0}},event[16]={0};std::memset(self,0xa5,sizeof(self));
 cap=&out;mode=c.seed%6;callCount=0;selfObject=self;for(unsigned i=0;i<8;++i)nodes[i]=objects[i];void*argument=c.seed%9?nodes[c.seed%8]:NULL;
 if(c.op<3){
  active=new(reinterpret_cast<char*>(self)+0x90)TArrayList<void*>(c.seed%5+1);pending=new(reinterpret_cast<char*>(self)+0xa8)TArrayList<void*>(c.seed%3+1);
  void*table[3]={NULL,NULL,reinterpret_cast<void*>(&eventCallback)};for(unsigned i=0;i<8;++i)pointer(nodes[i],0,table);
  unsigned n=(c.seed/6)%9,q=(c.seed/54)%7;
  for(unsigned i=0;i<n;++i)active->add(nodes[(i+c.seed)%7]);
  for(unsigned i=0;i<q;++i)pending->add(i%3==2?NULL:nodes[(i*3+c.seed)%8]);
  if(c.op!=2 && c.seed%11==0)active->add(NULL);
  switch(c.op){case 0:autotest::invoke(out,ours?candidate0:original0,static_cast<void*>(self),argument);break;case 1:autotest::invoke(out,ours?candidate1:original1,static_cast<void*>(self),argument);break;case 2:autotest::invoke(out,ours?candidate2:original2,static_cast<void*>(self),int(c.seed%27)-3,int(c.seed%13)-2);break;}
  listCapture(active);listCapture(pending);active->~TArrayList<void*>();pending->~TArrayList<void*>();std::memset(reinterpret_cast<char*>(self)+0x90,0,48);out.add(self,sizeof(self));out.addHeapInUse();return;
 }
 detour::Set patches;
 if(c.op<5){
  int indexes[]={-1,0,1,2,3,4,9,0x7fffffff};int slot=indexes[(c.seed/6)%8];int selected=indexes[(c.seed/48)%8];
  void*questItems[4]={nodes[3],nodes[3],nodes[3],nodes[3]};void*rewardItems[4]={nodes[5],nodes[6],NULL,nodes[7]};
  List quests={questItems,(c.seed/3)%5,(c.seed/21)%2?4u:2u,1};List items={rewardItems,(c.seed/7)%5,(c.seed/35)%2?4u:2u,1};rewardList=&items;
  pointer(event,0x10,mode==0?NULL:nodes[0]);pointer(nodes[0],0x1d8,&slot);pointer(self,0x180,mode==1?NULL:nodes[1]);pointer(nodes[1],0x868,mode==2?NULL:nodes[2]);
  std::memcpy(static_cast<char*>(nodes[2])+0x18,&quests,sizeof(quests));pointer(nodes[3],0x128,nodes[4]);pointer(self,0x170,c.seed%5?nodes[5+c.seed%3]:NULL);integer(self,0x190,selected);static_cast<unsigned char*>(static_cast<void*>(self))[0x178]=c.seed&1;
  TL_REDIRECT(patches,rewardsFn,&rewards);if(patches.failed())_exit(42);
  if(c.op==3)autotest::invoke(out,ours?candidate3:original3,static_cast<void*>(self),static_cast<void*>(event));else autotest::invoke(out,ours?candidate4:original4,static_cast<void*>(self),static_cast<void*>(event));
 }else{
  std::vector<void*>*v=new(reinterpret_cast<char*>(self)+0x1e8)std::vector<void*>;for(unsigned i=0;i<(c.seed/12)%20;++i)v->push_back(nodes[i%8]);
  const int positions[]={-7,-1,0,1,2,3,4,5,9,19,100,0x7fffffff-1};integer(self,0xc4,positions[c.seed%12]);
  TL_REDIRECT(patches,updateListFn,&updateList);if(patches.failed())_exit(43);autotest::invoke(out,ours?candidate5:original5,static_cast<void*>(self));number(v->size());for(unsigned i=0;i<v->size();++i)number(id((*v)[i]));v->~vector();std::memset(reinterpret_cast<char*>(self)+0x1e8,0,24);
 }
 out.add(self,sizeof(self));out.add(objects,sizeof(objects));out.add(event,sizeof(event));patches.restore();
}
void a(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void b(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned op,const char*name){
 const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2,(uint64_t)(uintptr_t)original3,(uint64_t)(uintptr_t)original4,(uint64_t)(uintptr_t)original5};
 autotest::Coverage coverage(name,addresses[op]);unsigned count=op<3?540:op<5?1152:240;
 for(unsigned n=0;n<count;++n){Case c={op,n};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);
  if(coverage.observe(host,x,y)){size_t k=0;while(k<x.capture.length&&k<y.capture.length&&x.capture.data[k]==y.capture.data[k])++k;
   host->log("    menu lists op %u case %u status %d/%d first %lu bytes %lu/%lu\n",op,n,x.status,y.status,(unsigned long)k,(unsigned long)x.capture.length,(unsigned long)y.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);return 0;
}
}
TL_TEST(menu_observed_add_listener){return run(host,0,"menu_observed_add_listener");}
TL_TEST(menu_observed_remove_listener){return run(host,1,"menu_observed_remove_listener");}
TL_TEST(menu_observed_broadcast){return run(host,2,"menu_observed_broadcast");}
TL_TEST(menu_observed_quest_over){return run(host,3,"menu_observed_quest_over");}
TL_TEST(menu_observed_quest_out){return run(host,4,"menu_observed_quest_out");}
TL_TEST(menu_observed_scroll_down){return run(host,5,"menu_observed_scroll_down");}
