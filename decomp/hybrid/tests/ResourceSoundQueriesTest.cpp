#include <cstring>
#include <map>
#include <string>
#include <stdint.h>
#include "AutoTest.h"
#include "SoundBankDataInformation.h"
#define QUERY(ret,old,newer,args,symbol) TL_ORIGINAL(ret,old,args,symbol) extern "C" ret newer args __asm__(symbol);
QUERY(int,oldIndex,newIndex,(void*,unsigned,const std::wstring&),"_ZN25CSoundBankDataInformation29getSoundIndexInCategoryByNameEjRKSbIwSt11char_traitsIwESaIwEE")
QUERY(std::wstring,oldSoundName,newSoundName,(void*,unsigned,unsigned),"_ZN25CSoundBankDataInformation27getSoundNameByCategoryIndexEjj")
QUERY(std::wstring,oldCategoryName,newCategoryName,(void*,unsigned),"_ZN25CSoundBankDataInformation19getCategoryNameByIDEj")
QUERY(unsigned,oldCategoryID,newCategoryID,(void*,const std::wstring&),"_ZN25CSoundBankDataInformation13getCategoryIDERKSbIwSt11char_traitsIwESaIwEE")
QUERY(void*,oldSoundInCategory,newSoundInCategory,(void*,const std::wstring&,const std::wstring&),"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEES5_")
QUERY(void*,oldSound,newSound,(void*,const std::wstring&),"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
#undef QUERY
namespace {
struct Case{unsigned mode,seed;};
void text(autotest::Capture&o,const std::wstring&s){unsigned n=s.size();o.add(&n,4);if(n)o.add(s.data(),n*4);}
int id(void*p,uint64_t*items){if(!p)return -1;for(unsigned i=0;i<8;++i)if(p==&items[i])return i;return -2;}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);uint64_t storage[(sizeof(CSoundBankDataInformation)+7)/8],items[8];std::memset(storage,0xa5,sizeof(storage));CSoundBankDataInformation*self=reinterpret_cast<CSoundBankDataInformation*>(storage);
 TArrayList<std::wstring>*categories=new(&self->m_categoryNames)TArrayList<std::wstring>(2);typedef std::map<unsigned,std::map<std::wstring,CSoundData*> >Groups;Groups*groups=new(&self->m_soundsByCategoryIndex)Groups;
 const wchar_t*names[]={L"",L"A",L"AA",L"Ж"};for(unsigned i=0;i<c.seed%5;++i)categories->add(names[(i+c.seed/17)%4]);
 for(unsigned g=0;g<4;++g)if((c.seed/5)&(1u<<g)){std::map<std::wstring,CSoundData*>&sounds=(*groups)[g];for(unsigned i=0;i<(c.seed/11+g)%5;++i)sounds[names[i]]=c.seed&64?NULL:reinterpret_cast<CSoundData*>(&items[(g+i)%8]);}
 Groups before=*groups;unsigned category=(c.seed/7)%6,index=(c.seed/13)%6;const std::wstring query=names[(c.seed/3)%4],categoryQuery=names[(c.seed/19)%4];
 int expectedID=-1;for(unsigned i=0;i<categories->size();++i)if((*categories)[i]==categoryQuery){expectedID=i;break;}
 if(c.mode==0){int expected=-1;Groups::const_iterator g=groups->find(category);if(g!=groups->end()){unsigned at=0;for(std::map<std::wstring,CSoundData*>::const_iterator i=g->second.begin();i!=g->second.end();++i,++at)if(i->first==query){expected=at;break;}}
  int(*fn)(void*,unsigned,const std::wstring&)=ours?newIndex:oldIndex;if(!autotest::beginInvocation(out,fn))return;int result=fn(self,category,query);out.callCompleted=1;out.add(&result,4);if(result!=expected)out.issue=autotest::Capture::InvalidReport;}
 else if(c.mode==1){std::wstring expected;Groups::const_iterator g=groups->find(category);if(g!=groups->end()){unsigned at=0;for(std::map<std::wstring,CSoundData*>::const_iterator i=g->second.begin();i!=g->second.end();++i,++at)if(at==index){expected=i->first;break;}}
  std::wstring(*fn)(void*,unsigned,unsigned)=ours?newSoundName:oldSoundName;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(self,category,index);out.callCompleted=1;text(out,result);if(result!=expected)out.issue=autotest::Capture::InvalidReport;}
 else if(c.mode==2){std::wstring expected=categories->size()?(*categories)[category<categories->size()?category:0]:std::wstring();std::wstring(*fn)(void*,unsigned)=ours?newCategoryName:oldCategoryName;if(!autotest::beginInvocation(out,fn))return;std::wstring result=fn(self,category);out.callCompleted=1;text(out,result);if(result!=expected)out.issue=autotest::Capture::InvalidReport;}
 else if(c.mode==3){unsigned(*fn)(void*,const std::wstring&)=ours?newCategoryID:oldCategoryID;if(!autotest::beginInvocation(out,fn))return;unsigned result=fn(self,categoryQuery);out.callCompleted=1;out.add(&result,4);if(result!=static_cast<unsigned>(expectedID))out.issue=autotest::Capture::InvalidReport;}
 else if(c.mode==4){void*expected=NULL;Groups::const_iterator g=groups->find(expectedID);if(expectedID>=0&&g!=groups->end()){std::map<std::wstring,CSoundData*>::const_iterator i=g->second.find(query);if(i!=g->second.end())expected=i->second;}
  void*(*fn)(void*,const std::wstring&,const std::wstring&)=ours?newSoundInCategory:oldSoundInCategory;if(!autotest::beginInvocation(out,fn))return;int result=id(fn(self,categoryQuery,query),items);out.callCompleted=1;out.add(&result,4);if(result!=id(expected,items))out.issue=autotest::Capture::InvalidReport;}
 else{void*expected=NULL;for(unsigned at=0;at<categories->size();++at){Groups::const_iterator g=groups->find(at);if(g==groups->end())break;std::map<std::wstring,CSoundData*>::const_iterator i=g->second.find(query);if(i!=g->second.end()){expected=i->second;break;}}
  void*(*fn)(void*,const std::wstring&)=ours?newSound:oldSound;if(!autotest::beginInvocation(out,fn))return;int result=id(fn(self,query),items);out.callCompleted=1;out.add(&result,4);if(result!=id(expected,items))out.issue=autotest::Capture::InvalidReport;}
 if(*groups!=before)out.issue=autotest::Capture::InvalidReport;groups->~Groups();categories->~TArrayList();
}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned n=0;n<160;++n){Case c={mode,n};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(coverage.observe(host,x,y)){host->log("    sound query mode %u seed %u issue %u/%u exits %d/%d\n",mode,n,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(resource_sound_index){return run(host,0,"resource_sound_index",(uintptr_t)&oldIndex);}
TL_TEST(resource_sound_name){return run(host,1,"resource_sound_name",(uintptr_t)&oldSoundName);}
TL_TEST(resource_sound_category_name){return run(host,2,"resource_sound_category_name",(uintptr_t)&oldCategoryName);}
TL_TEST(resource_sound_category_id){return run(host,3,"resource_sound_category_id",(uintptr_t)&oldCategoryID);}
TL_TEST(resource_sound_in_category){return run(host,4,"resource_sound_in_category",(uintptr_t)&oldSoundInCategory);}
TL_TEST(resource_sound_any_category){return run(host,5,"resource_sound_any_category",(uintptr_t)&oldSound);}
