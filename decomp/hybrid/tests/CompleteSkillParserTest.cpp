#include <cstring>
#include <map>
#include <string>
#include <new>
#include "tests/SmallMassCompare.h"
#include "SkillParser.h"
#include "TRepository.h"
#include "FileSystem.h"
#include "ResourceSettings.h"
#define DECL(ret,old,now,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret now args __asm__(sym);
DECL(void,spOldOne,spNewOne,(CSkillParser*,const std::wstring&),"_ZN12CSkillParser10parseSkillERKSbIwSt11char_traitsIwESaIwEE")
DECL(void,spOldAll,spNewAll,(CSkillParser*),"_ZN12CSkillParser11parseSkillsEv")
#undef DECL
TL_ORIGINAL(void,spNativeGroup,(CDataGroup*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_FUNCTION(spGroupCtor,"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_FUNCTION(spLoad,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TL_FUNCTION(spSave,"_ZN10CDataGroup10SaveToFileERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(spGuid,"_ZN9UTILITIES16createUniqueGuidEv")
TL_FUNCTION(spClear,"_ZN12CSkillParser11clearSkillsEv")
TL_FUNCTION(spGetString,"_ZN20CDynamicPropertyFile9GetStringEj")
TL_FUNCTION(spGetFS,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(spFiles,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(spParse,"_ZN12CSkillParser10parseSkillERKSbIwSt11char_traitsIwESaIwEE")
namespace {
using namespace smallmass;
unsigned seed; std::wstring name,folder; CDataGroup* loaded; CSkillParser* parser; unsigned clearCalls,saveCalls;detour::Set*ctorHooks;
void groupCtor(CDataGroup*p,const std::wstring&n,CDataGroup*parent,unsigned v,unsigned g,TRepository<std::wstring>*r){
 number(1);text(n);number(parent!=NULL);number(v);number(g);number(r!=NULL);
 // CDataGroup owns the nonglobal root repository; supply matching heap allocation.
 ctorHooks->restore();
 spNativeGroup(p,n,parent,v,g,r?r:new TRepository<std::wstring>(std::wstring()));
 TL_REDIRECT(*ctorHooks,spGroupCtor,&groupCtor);if(ctorHooks->failed())std::abort();
}
void load(CDataGroup*p,const std::wstring&path,CTimerStatics*t){
 number(2);text(path);number(t!=NULL);loaded=p;
 if(seed%5!=0)p->AddDataValue(L"NAME",name,false);
 if(seed&4)p->AddDataValue(L"UNIQUE_GUID",(seed&8)?-1LL:0x123456789abcLL);
 p->AddDataValue(L"EXTRA",L"kept",false);
}
int save(CDataGroup*p,const std::wstring&path){number(3);text(path);number(p==loaded);++saveCalls;return 0;}
long long guid(){number(4);return 0x112233440000LL+seed;}
void clear(CSkillParser*p){number(5);number(p==parser);++clearCalls;p->m_skills.clear();}
const std::wstring& getString(CDynamicPropertyFile*,unsigned k){number(6);number(k);return folder;}
CFileSystem* getFS(){number(7);return reinterpret_cast<CFileSystem*>(0x1040);}
unsigned files(CFileSystem*p,const std::wstring&path,TArrayList<std::wstring>&out,std::wstring pattern,bool a,bool b,bool c,bool d){
 number(8);number(p==reinterpret_cast<CFileSystem*>(0x1040));text(path);text(pattern);number(a);number(b);number(c);number(d);
 for(unsigned i=0;i<seed%5;++i)out.add(i&1?L"media/skills/Ж.dat":L"media/skills/a.dat");return out.size();
}
void parse(CSkillParser*p,const std::wstring&path){number(9);number(p==parser);text(path);p->m_skills[path]=NULL;}
void parserSide(Case& c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;saveCalls=clearCalls=0;loaded=NULL;
 const unsigned cells[]={0x14dd9c8,0x14dd9d8,0x14dda88,0x152f138,0x14f3908};
 for(unsigned i=0;i<5;++i)new(reinterpret_cast<void*>(cells[i]))std::wstring();
 CSkillParser*self=static_cast<CSkillParser*>(object(sizeof(CSkillParser)));parser=self;
 new(&self->m_skills)std::map<std::wstring,CDataGroup*>();
 self->m_pResourceSettings=(seed&1)?reinterpret_cast<CResourceSettings*>(0x1000):NULL;
 const wchar_t*names[]={L"",L"FiRe",L"Жар",L"Fire",L"Mixed_Name"};name=names[(seed/5)%5];folder=seed&2?L"media/skills":L"media/Ж";
 std::wstring path=seed&16?L"media/skills/Ж.dat":L"plain.dat";
 CDataGroup* prior=NULL;
 if(seed&32){prior=new CDataGroup(L"PRIOR",NULL,20,10,new TRepository<std::wstring>(std::wstring()));self->m_skills[L"FIRE"]=prior;}
 if(c.op==0){
  typedef void(*Fn)(CSkillParser*,const std::wstring&);Fn fn=ours?spNewOne:spOldOne;
  if(!autotest::beginInvocation(out,fn))return;fn(self,path);out.callCompleted=1;
 }else{
  typedef void(*Fn)(CSkillParser*);Fn fn=ours?spNewAll:spOldAll;
  if(!autotest::beginInvocation(out,fn))return;fn(self);out.callCompleted=1;
 }
 number(saveCalls);number(clearCalls);number(self->m_skills.size());
 for(std::map<std::wstring,CDataGroup*>::iterator i=self->m_skills.begin();i!=self->m_skills.end();++i){
  text(i->first);number(i->second==loaded);number(i->second==prior);
  if(i->second&&i->second==loaded){text(i->second->GetDataValue(L"NAME",std::wstring()));text(i->second->GetDataValue(L"EXTRA",std::wstring()));long long value=i->second->GetDataValue(L"UNIQUE_GUID",-999LL);out.add(&value,sizeof(value));}
 }
 // Native parseSkill overwrites duplicate-name map slots without deleting prior.
 bool foundPrior=false;
 for(std::map<std::wstring,CDataGroup*>::iterator i=self->m_skills.begin();i!=self->m_skills.end();++i){if(i->second==prior)foundPrior=true;if(i->second)delete i->second;}
 if(prior&&!foundPrior)delete prior;
 self->m_skills.~map();
}
}
TL_TEST(complete_skill_parser_one){detour::Set ctor;ctorHooks=&ctor;TL_REDIRECT(ctor,spGroupCtor,&groupCtor);detour::Set h;TL_REDIRECT(h,spLoad,&load);TL_REDIRECT(h,spSave,&save);TL_REDIRECT(h,spGuid,&guid);if(h.failed())return 1;return smallmass::run(host,0,"complete_skill_parser_one",0xcdc070,&parserSide,128);}
TL_TEST(complete_skill_parser_all){detour::Set h;TL_REDIRECT(h,spClear,&clear);TL_REDIRECT(h,spGetString,&getString);TL_REDIRECT(h,spGetFS,&getFS);TL_REDIRECT(h,spFiles,&files);TL_REDIRECT(h,spParse,&parse);if(h.failed())return 1;return smallmass::run(host,1,"complete_skill_parser_all",0xcdc590,&parserSide,64);}
