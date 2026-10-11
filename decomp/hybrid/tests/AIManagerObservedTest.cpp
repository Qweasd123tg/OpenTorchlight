#include <cstring>
#include <vector>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "TArrayList.h"
TL_ORIGINAL(void,originalInit,(void*),"_ZN10CAIManager9initalizeEv")
extern "C" void candidateInit(void*) __asm__("_ZN10CAIManager9initalizeEv");
TL_FUNCTION(target_getGroup,"_ZN10CDataGroup18GetDataGroupByNameERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(target_matching,"_ZN10CDataGroup25GetDataGroupsMatchingNameERKSbIwSt11char_traitsIwESaIwEEPSt6vectorIPS_SaIS7_EE")
TL_FUNCTION(target_watcher,"_ZN14CAIStatWatcherC1EP10CDataGroupP10CAIManager")

namespace {
struct Case{unsigned seed,mode;};Case*input;autotest::Capture*output;void*active;void*data[8];std::vector<void*>*stats;unsigned made;
void num(unsigned v){output->add(&v,4);}void ptr(void*p){output->add(&p,8);}void*getGroup(void*p,const std::wstring&name,bool create){num(1);ptr(p);output->addText(name);num(create);return input->mode==2?NULL:data[0];}
unsigned matching(void*p,const std::wstring&name,std::vector<void*>*out){num(2);ptr(p);output->addText(name);stats=out;for(unsigned i=0;i<(input->seed/8)%8;++i)out->push_back(data[i]);return out->size();}
void watcher(void*p,void*group,void*manager){num(3);ptr(group);ptr(manager);num(made);std::memset(p,(input->seed*23+made+13)&255,0xb8);++made;if(input->mode==3&&stats->size()>1)stats->pop_back();if(input->mode==4&&made==1)stats->push_back(data[7]);if(input->mode==5&&made==1)reinterpret_cast<TArrayList<void*>*>(static_cast<char*>(active)+0x28)->add(data[6]);}
void side(Case&c,bool ours,autotest::Capture&out){input=&c;output=&out;made=0;stats=NULL;unsigned long long self[0x58/8],character[0x200/8]={0},groups[8][0x60/8]={{0}};std::memset(self,(c.seed*11+3)&255,sizeof(self));active=self;void*ch=c.mode==0?NULL:character;std::memcpy(reinterpret_cast<char*>(self)+0x10,&ch,8);for(unsigned i=0;i<8;++i)data[i]=groups[i];void*group=c.mode==1?NULL:data[1];std::memcpy(reinterpret_cast<char*>(character)+0x1b0,&group,8);TArrayList<void*>*list=new(reinterpret_cast<char*>(self)+0x28)TArrayList<void*>(1+(c.seed/8)%4);for(unsigned i=0;i<(c.seed/8)%3;++i)list->add(data[i]);unsigned initial=list->size();
 detour::Set patches;TL_REDIRECT(patches,target_getGroup,&getGroup);TL_REDIRECT(patches,target_matching,&matching);TL_REDIRECT(patches,target_watcher,&watcher);if(patches.failed())_exit(41);autotest::invoke(out,ours?candidateInit:originalInit,active);num(made);num(list->size());unsigned*fields=reinterpret_cast<unsigned*>(reinterpret_cast<char*>(list)+8);out.add(fields,12);for(unsigned i=0;i<list->size();++i){void*p=(*list)[i];unsigned identity=8;for(unsigned j=0;j<8;++j)if(p==data[j])identity=j;num(identity);if(identity==8)out.add(p,0xb8);}std::memset(list,0,8);out.add(self,sizeof(self));out.add(character,sizeof(character));out.add(groups,sizeof(groups));patches.restore();}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(ai_manager_initialize_observed){autotest::Coverage coverage("ai_manager_initialize_observed",(uint64_t)(uintptr_t)originalInit);for(unsigned n=0;n<384;++n){Case c={n,n%8};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    AI initialize %u status %d/%d bytes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
