#include "tests/SmallMassCompare.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "DataGroup.h"
#include "EmptyStrings.h"
#define DECL(ret,id,args,sym) TL_ORIGINAL(ret,id##Old,args,sym) extern "C" ret id##New args __asm__(sym);
DECL(void,deepSoundNames,(CSoundBankDataInformation*,TArrayList<std::wstring>*),"_ZN25CSoundBankDataInformation13getSoundNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")
DECL(void,deepSoundCategory,(CSoundBankDataInformation*,const std::wstring&,TArrayList<std::wstring>*),"_ZN25CSoundBankDataInformation26getSoundNamesByCatgoryNameERKSbIwSt11char_traitsIwESaIwEEP10TArrayListIS3_E")
DECL(void,deepSoundDataDtor,(CSoundBankDataInformation*),"_ZN25CSoundBankDataInformationD1Ev")
DECL(CSoundData*,deepSoundCreate,(CSoundBankDataInformation*,CDataGroup*),"_ZN25CSoundBankDataInformation15createSoundDataEP10CDataGroup")
DECL(void,deepSoundParse,(CSoundBankDataInformation*,const std::wstring&),"_ZN25CSoundBankDataInformation14parseSoundDataERKSbIwSt11char_traitsIwESaIwEE")
DECL(void,deepSoundReload,(CSoundBankDataInformation*,void*),"_ZN25CSoundBankDataInformation6reloadEP17CResourceSettings")
TL_FUNCTION(deepSoundFiles,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(deepSoundFileList,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(deepSoundLoad,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TL_FUNCTION(deepSoundSettings,"_ZN20CDynamicPropertyFile9GetStringEj")
extern "C" char deepSoundGroupRelease[] __asm__("_ZN4FMOD10SoundGroup7releaseEv");
namespace {
using namespace smallmass;unsigned calls;unsigned fileIndex;void* token;std::wstring settingsPath;
void record(unsigned tag,void* p){number(tag);number(p==token);++calls;}
int release(void* p){record(1,p);return 0;}
void* files(){record(2,token);return token;}
void fileList(void* p,const std::wstring& path,TArrayList<std::wstring>& files,std::wstring mask,bool a,bool b,bool c,bool d){record(3,p);text(path);text(mask);number(a);number(b);number(c);number(d);for(unsigned i=0;i<input->index%4;++i){std::wstring file=L"fixture";file+=wchar_t('0'+i);files.add(file);}}
void fill(CDataGroup* data,unsigned i){long long guid=(input->index&16?i%2:i)+100;data->AddDataValue(L"GUID",guid);data->AddDataValue(L"NAME",i&1?L"nameB":L"nameA",false);data->AddDataValue(L"CATEGORY",i%3?L"catA":L"catB",false);data->AddDataValue(L"VOLUME",float(i)*0.2f);data->AddDataValue(L"LOOPS",bool(i&1));CDataGroup* f=data->AddDataGroup(L"FILES");for(unsigned j=0;j<1+i%3;++j)f->AddDataValue(L"FILE",j&1?L"media/Ж.ogg":L"sample.wav",false);}
unsigned load(CDataGroup* p,const std::wstring& path,void* timer){record(4,p);text(path);number(timer!=0);for(unsigned i=0;i<1+input->index%4;++i)fill(p->AddDataGroup(L"SOUND"),i+fileIndex*3);++fileIndex;return 1;}
const std::wstring& setting(void* p,unsigned id){record(5,p);number(id);return settingsPath;}
void capture(CSoundData* s){number(s!=0);if(!s)return;text(s->m_name);text(s->m_category);output->add(&s->m_iGuid,8);floating(s->m_float28);number(s->m_flag2c);floating(s->m_float30);floating(s->m_float34);floating(s->m_float38);number(s->m_probability);number(s->m_files.size());number(field<unsigned>(&s->m_files,12));number(field<unsigned>(&s->m_files,16));for(unsigned i=0;i<s->m_files.size();++i)text(s->m_files[i]);number(s->m_group!=0);}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=fileIndex=0;autotest::g_arenaUsed=0;token=object(8);settingsPath=L"fixture/sounds/";void* storage=object(sizeof(CSoundBankDataInformation));CSoundBankDataInformation* self=static_cast<CSoundBankDataInformation*>(storage);new(self)CSoundBankDataInformation(NULL);TArrayList<std::wstring> names(1+c.index%3);const wchar_t* categories[]={L"",L"A",L"Ж",L"MISSING"};for(unsigned i=0;i<c.index%4;++i)self->m_categoryNames.add(categories[i]);if(c.index&4)names.add(L"prefix");
if(c.op<3||c.op==5){for(unsigned g=0;g<3;++g)if((c.index>>g)&1){for(unsigned i=0;i<(c.index+g)%4;++i){std::wstring name=i&1?L"B":L"A";name+=wchar_t('0'+i);CSoundData* sound=new CSoundData;sound->m_name=name;sound->m_category=categories[g];sound->m_group=c.index&32?static_cast<FMOD::SoundGroup*>(token):0;sound->m_iGuid=g*10+i;sound->m_files.add(L"life.wav");self->m_sounds.add(sound);self->m_soundsByGuid[sound->m_iGuid]=sound;self->m_soundsByCategoryIndex[g][name]=sound;}}}
detour::Set d;d.redirect(deepSoundGroupRelease,deepSoundGroupRelease,&release);TL_REDIRECT(d,deepSoundFiles,&files);TL_REDIRECT(d,deepSoundFileList,&fileList);TL_REDIRECT(d,deepSoundLoad,&load);TL_REDIRECT(d,deepSoundSettings,&setting);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
if(c.op==0)autotest::invoke(out,ours?deepSoundNamesNew:deepSoundNamesOld,self,&names);else if(c.op==1){std::wstring category=categories[(c.index/4)%4];typedef void(*Fn)(CSoundBankDataInformation*,const std::wstring&,TArrayList<std::wstring>*);autotest::invoke<Fn,CSoundBankDataInformation*,const std::wstring&,TArrayList<std::wstring>*>(out,ours?deepSoundCategoryNew:deepSoundCategoryOld,self,category,&names);}else if(c.op==2)autotest::invoke(out,ours?deepSoundDataDtorNew:deepSoundDataDtorOld,self);else if(c.op==3){CDataGroup* data=new CDataGroup(EMPTY_WSTRING,NULL,20,10,NULL);if(c.index%7!=0){CDataGroup* f=data->AddDataGroup(L"FILES");if(c.index%7!=1)for(unsigned i=0;i<1+c.index%4;++i)f->AddDataValue(L"FILE",i&1?L"media/Ж.ogg":L"sample.wav",false);}if(c.index%7!=2)data->AddDataValue(L"GUID",static_cast<long long>(c.index+100));data->AddDataValue(L"NAME",L"MiXeD",false);data->AddDataValue(L"CATEGORY",L"CategoryЖ",false);if(c.index&4){data->AddDataValue(L"VOLUME",0.375f);data->AddDataValue(L"RADIUS",12.5f);data->AddDataValue(L"FREQUENCYVARIATION",-0.25f);data->AddDataValue(L"VOLUMEVARIATION",0.625f);data->AddDataValue(L"LOOPS",bool(c.index&8));data->AddDataValue(L"PLAYCHANCE",int(c.index%101));}
CSoundData*(*fn)(CSoundBankDataInformation*,CDataGroup*)=ours?deepSoundCreateNew:deepSoundCreateOld;if(!autotest::beginInvocation(out,fn))return;CSoundData* result=fn(self,c.index%7==3?0:data);out.callCompleted=1;capture(result);if(result)delete result;if(c.index%7!=2)delete data;}
else if(c.op==4){std::wstring path=L"fixtures/";typedef void(*Fn)(CSoundBankDataInformation*,const std::wstring&);autotest::invoke<Fn,CSoundBankDataInformation*,const std::wstring&>(out,ours?deepSoundParseNew:deepSoundParseOld,self,path);}else autotest::invoke(out,ours?deepSoundReloadNew:deepSoundReloadOld,self,c.index&1?token:static_cast<void*>(0));
number(names.size());for(unsigned i=0;i<names.size();++i)text(names[i]);if(c.op!=2){number(self->m_categoryNames.size());for(unsigned i=0;i<self->m_categoryNames.size();++i)text(self->m_categoryNames[i]);number(self->m_soundsByCategoryIndex.size());for(std::map<unsigned,std::map<std::wstring,CSoundData*> >::iterator g=self->m_soundsByCategoryIndex.begin();g!=self->m_soundsByCategoryIndex.end();++g){number(g->first);number(g->second.size());for(std::map<std::wstring,CSoundData*>::iterator i=g->second.begin();i!=g->second.end();++i)text(i->first);}number(self->m_sounds.size());if(c.op>=4)for(unsigned i=0;i<self->m_sounds.size();++i)capture(self->m_sounds[i]);self->CSoundBankDataInformation::~CSoundBankDataInformation();}number(calls);}
}
TL_TEST(deep_runtime_sound_names){return smallmass::run(host,0,"deep_runtime_sound_names",(uintptr_t)deepSoundNamesOld,execute,64);}
TL_TEST(deep_runtime_sound_category){return smallmass::run(host,1,"deep_runtime_sound_category",(uintptr_t)deepSoundCategoryOld,execute,64);}
TL_TEST(deep_runtime_sounddata_destructor){return smallmass::run(host,2,"deep_runtime_sounddata_destructor",(uintptr_t)deepSoundDataDtorOld,execute,64);}
TL_TEST(deep_runtime_sounddata_create){return smallmass::run(host,3,"deep_runtime_sounddata_create",(uintptr_t)deepSoundCreateOld,execute,84);}
TL_TEST(deep_runtime_sounddata_parse){return smallmass::run(host,4,"deep_runtime_sounddata_parse",(uintptr_t)deepSoundParseOld,execute,64);}
TL_TEST(deep_runtime_sounddata_reload){return smallmass::run(host,5,"deep_runtime_sounddata_reload",(uintptr_t)deepSoundReloadOld,execute,64);}
