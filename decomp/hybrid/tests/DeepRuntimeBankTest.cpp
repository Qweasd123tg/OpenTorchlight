#include "tests/SmallMassCompare.h"
#include "SoundBank.h"
#include "SoundInstance.h"
#include "SoundData.h"
#include "GameVariables.h"
#define DECL(ret,id,args,sym) TL_ORIGINAL(ret,id##Old,args,sym) extern "C" ret id##New args __asm__(sym);
DECL(CSoundInstance*,deepBankName,(void*,int,const std::wstring&,bool,bool,float,float,float,float,int),"_ZN10CSoundBank9addSampleEiRKSbIwSt11char_traitsIwESaIwEEbbffffi")
DECL(void,deepBankGuid,(void*,int,long long),"_ZN10CSoundBank9addSampleEix")
TL_FUNCTION(deepBankCreate,"_ZN13CSoundManager11createSoundESbIwSt11char_traitsIwESaIwEE10SOUND_TYPEbff")
TL_FUNCTION(deepBankFind,"_ZN25CSoundBankDataInformation24getSoundDataObjectByGuidEx")
TL_FUNCTION(deepBankGroup,"_ZN13CSoundManager16createSoundGroupESs")
extern "C" char deepBankMax[] __asm__("_ZN4FMOD10SoundGroup13setMaxAudibleEi");
extern "C" char deepBankBehavior[] __asm__("_ZN4FMOD10SoundGroup21setMaxAudibleBehaviorE24FMOD_SOUNDGROUP_BEHAVIOR");
extern "C" char deepBankGetGroup[] __asm__("_ZN4FMOD5Sound13getSoundGroupEPPNS_10SoundGroupE");
extern "C" char deepBankSetGroup[] __asm__("_ZN4FMOD5Sound13setSoundGroupEPNS_10SoundGroupE");
namespace {using namespace smallmass;void* token;CSoundInstance* sounds[8];unsigned count;CSoundData* data;
CSoundInstance* result(){CSoundInstance* s=sounds[count++%8];return input->index&8?0:s;}
CSoundInstance* create(void* self,std::wstring name,int type,bool flag,float a,float b){event(1,self);text(name);number(type);number(flag);floating(a);floating(b);return result();}
CSoundData* find(void* self,long long guid){event(2,self);output->add(&guid,8);return input->index&16?0:data;}
void* group(void* self,std::string name){event(3,self);text(name);return token;}
int max(void* self,int n){event(4,self);number(n);return 0;}
int behavior(void* self,int n){event(5,self);number(n);return 0;}
int getGroup(void* self,void** group){event(6,self);*group=input->index&32?token:0;return 0;}
int setGroup(void* self,void* group){event(7,self);pointer(group);return 0;}
CSoundInstance* named(void* self,int id,const std::wstring& name,bool a,bool b,float x,float y,float z,float w,int probability){event(8,self);number(id);text(name);number(a);number(b);floating(x);floating(y);floating(z);floating(w);number(probability);return result();}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;autotest::g_arenaUsed=0;count=0;token=object(8);void* self=object(sizeof(CSoundBank));field<void*>(self,0x10)=object(8);std::vector<std::vector<CSoundInstance*> >& samples=*new(static_cast<char*>(self)+0x48)std::vector<std::vector<CSoundInstance*> >();std::vector<float>& radii=*new(static_cast<char*>(self)+0x60)std::vector<float>();std::vector<float>& volumes=*new(static_cast<char*>(self)+0x78)std::vector<float>();std::vector<int>& probabilities=*new(static_cast<char*>(self)+0x90)std::vector<int>();for(unsigned i=0;i<8;++i){sounds[i]=static_cast<CSoundInstance*>(object(sizeof(CSoundInstance)));sounds[i]->m_pSound=static_cast<FMOD::Sound*>(token);}for(unsigned i=0;i<c.index%4;++i){samples.push_back(std::vector<CSoundInstance*>(1,sounds[i]));radii.push_back(i+1);volumes.push_back(i+2);probabilities.push_back(i+3);}field<float>(self,0xac)=.625f;field<float>(self,0xb0)=12.5f;field<bool>(self,0xc8)=c.index&64;
void* global=object(0x190);CMasterResourceManager* old=m_pMasterResourceManager;m_pMasterResourceManager=static_cast<CMasterResourceManager*>(global);field<void*>(global,0x100)=c.index&64?0:object(8);data=static_cast<CSoundData*>(object(sizeof(CSoundData)));new(&data->m_files)TArrayList<std::wstring>(1);for(unsigned i=0;i<c.index%5;++i)data->m_files.add(i&1?L"a.wav":L"Ж.ogg");data->m_group=c.index&4?static_cast<FMOD::SoundGroup*>(token):0;data->m_flag2c=c.index&2;data->m_float28=.2f;data->m_float30=.3f;data->m_float34=.4f;data->m_float38=.5f;data->m_probability=37;
detour::Set d;TL_REDIRECT(d,deepBankCreate,&create);TL_REDIRECT(d,deepBankFind,&find);TL_REDIRECT(d,deepBankGroup,&group);d.redirect(deepBankMax,deepBankMax,&max);d.redirect(deepBankBehavior,deepBankBehavior,&behavior);d.redirect(deepBankGetGroup,deepBankGetGroup,&getGroup);d.redirect(deepBankSetGroup,deepBankSetGroup,&setGroup);if(c.op==1)d.redirect(reinterpret_cast<char*>(deepBankNameOld),reinterpret_cast<char*>(deepBankNameNew),&named);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
int id=c.index%7==0?-1:int(c.index%5);if(c.op==0){std::wstring name=L"sample/Ж.wav";typedef CSoundInstance*(*Fn)(void*,int,const std::wstring&,bool,bool,float,float,float,float,int);Fn fn=ours?deepBankNameNew:deepBankNameOld;if(!autotest::beginInvocation(out,fn))return;pointer(fn(self,id,name,c.index&2,c.index&4,c.index&16?0:.875f,.375f,-.25f,c.index&32?0:8.5f,41));out.callCompleted=1;}else autotest::invoke(out,ours?deepBankGuidNew:deepBankGuidOld,self,id,123456789123LL);
number(count);number(field<bool>(self,0xc8));number(samples.size());for(unsigned i=0;i<samples.size();++i){number(samples[i].size());for(unsigned j=0;j<samples[i].size();++j)pointer(samples[i][j]);floating(radii[i]);floating(volumes[i]);number(probabilities[i]);}pointer(data->m_group);for(unsigned i=0;i<8;++i)pointer(sounds[i]->m_pSoundData);data->m_files.~TArrayList();samples.~vector();radii.~vector();volumes.~vector();probabilities.~vector();m_pMasterResourceManager=old;}
}
TL_TEST(deep_runtime_bank_named){return smallmass::run(host,0,"deep_runtime_bank_named",(uintptr_t)deepBankNameOld,execute,128);}
TL_TEST(deep_runtime_bank_guid){return smallmass::run(host,1,"deep_runtime_bank_guid",(uintptr_t)deepBankGuidOld,execute,128);}
