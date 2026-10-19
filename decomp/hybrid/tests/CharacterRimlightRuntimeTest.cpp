#include <cstring>
#include <clocale>
#include <execinfo.h>
#include <fcntl.h>
#include <ucontext.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "GenericModel.h"
#include "Equipment.h"
#include "Inventory.h"
#include "Wardrobe.h"
#include "DataGroup.h"
#include "TRepository.h"
#include "FileSystem.h"
#undef private
#undef protected
#include <OgreHardwarePixelBuffer.h>
#include "NativeMenuServices.h"
namespace {
#include "CharacterEmptyGlobals.h"
}
TL_ORIGINAL(void,crOld,(CCharacter*,std::wstring),"_ZN10CCharacter11setRimlightESbIwSt11char_traitsIwESaIwEE")
extern "C" void crNew(CCharacter*,std::wstring) __asm__("_ZN10CCharacter11setRimlightESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(crRim,"_ZN13CGenericModel14setRimLightingESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(crTexture,"_ZN13CGenericModel18setTextureOverrideEN4Ogre10TexturePtrESsSs")
TL_FUNCTION(crOverride,"_ZN13CGenericModel18setTextureOverrideERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(crSingle,"_ZN13CGenericModel24setTextureOverrideSingleERKSsRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(crEquipped,"_ZN10CInventory22getEquipmentEquippedAtE16EEQUIP_LOCATIONS")
TL_FUNCTION(crFiles,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(crWardrobeUpdate,"_ZN9CWardrobe6updateEP10CInventory")
namespace {
struct Case {unsigned seed,control;};
unsigned seed,phase;bool armed,oursSide;autotest::Capture*out;nativegame::Services*services;
CCharacter*self;CGenericModel*models[2];CEquipment*equipment[3];Ogre::Texture*expectedTexture;unsigned destroyed;
void fault(int signal,siginfo_t*info,void*context){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/character/character-rimlight-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);if(fd>=0){char line[200];ucontext_t*uc=static_cast<ucontext_t*>(context);int n=std::snprintf(line,sizeof(line),"signal%d side%u seed%u phase%u rip%llx address%p\n",signal,unsigned(oursSide),seed,phase,(unsigned long long)uc->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,line,n);void*stack[40];int count=backtrace(stack,40);backtrace_symbols_fd(stack,count,fd);close(fd);}raise(signal);}
void num(unsigned value){if(armed)out->add(&value,4);}
void wide(const std::wstring&s){num(s.size());if(armed)out->add(s.data(),s.size()*sizeof(wchar_t));}
void narrow(const std::string&s){num(s.size());if(armed)out->add(s.data(),s.size());}
unsigned modelId(CGenericModel*p){return p==models[0]?1:p==models[1]?2:p?99:0;}
void require(bool ok){if(!ok)_exit(47);}
// Same native Texture C1 and exact SDK extent as WardrobeConstructorTest.
// This fixture never requests a GPU buffer or loaded texture.
class CPUTexture:public Ogre::Texture {
public:
 CPUTexture():Ogre::Texture(NULL,"character-rimlight-texture",1,"General",true,NULL){require(sizeof(Ogre::Resource)==0x78&&sizeof(Ogre::Texture)==0xe8);require(reinterpret_cast<char*>(&mHeight)-reinterpret_cast<char*>(this)==0x78);require(reinterpret_cast<char*>(&mNumMipmaps)-reinterpret_cast<char*>(this)==0x98);require(reinterpret_cast<char*>(&mInternalResourcesCreated)-reinterpret_cast<char*>(this)==0xe1);}
 ~CPUTexture(){++destroyed;}
 Ogre::HardwarePixelBufferSharedPtr getBuffer(size_t,size_t){require(false);return Ogre::HardwarePixelBufferSharedPtr();}
protected:
 void loadImpl(){require(false);}void createInternalResourcesImpl(){require(false);}void freeInternalResourcesImpl(){}
};
// Native CWardrobe C1 constructs TexturePtr at +38 (also WardrobeConstructorTest).
Ogre::TexturePtr& wardrobeTexture(CWardrobe*p){return *reinterpret_cast<Ogre::TexturePtr*>(reinterpret_cast<char*>(p)+0x38);}
class Equipment:public CEquipment {public:Equipment():CEquipment(NULL){}virtual void setRimlight(std::wstring text){num(107);for(unsigned i=0;i<3;++i)if(this==equipment[i])num(i+1);wide(text);}};
void rim(CGenericModel*p,std::wstring text){num(101);num(modelId(p));wide(text);}
void texture(CGenericModel*p,Ogre::TexturePtr text,std::string include,std::string exclude){num(103);num(modelId(p));num(text.isNull());num(text.getPointer()==expectedTexture);num(text.isNull()?0:text.useCount());narrow(include);narrow(exclude);}
void overrideTexture(CGenericModel*p,const std::wstring&text){num(109);num(modelId(p));wide(text);}
void single(CGenericModel*p,const std::string&name,const std::wstring&text){num(113);num(modelId(p));narrow(name);wide(text);}
CEquipment* equipped(CInventory*p,EEQUIP_LOCATIONS slot){num(127);num(p==self->m_pInventory);num(slot);return (seed+unsigned(slot))%4?equipment[(seed+unsigned(slot))%3]:NULL;}
bool file(CFileSystem*,const std::wstring&,CFileInfo&info,bool,bool,bool){info.m_bExists=false;return false;}
void wardrobeUpdate(CWardrobe*,CInventory*){}
std::wstring value(unsigned index){switch(index%4){case 0:return L"";case 1:return L"rim.png";case 2:return L"texture Ж";default:return std::wstring(L"embedded\0name",13);}}
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;oursSide=ours;phase=1;armed=false;out=&capture;destroyed=0;expectedTexture=NULL;struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_sigaction=&fault;action.sa_flags=SA_SIGINFO|SA_RESETHAND;sigemptyset(&action.sa_mask);sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);
 self=new CCharacter(NULL);for(unsigned i=0;i<2;++i)models[i]=new CGenericModel(NULL,services->scene,static_cast<OGRE_UTILITIES::EPRIMITIVES>(0));for(unsigned i=0;i<3;++i)equipment[i]=new Equipment;
 self->m_pUnitModel=seed%11?models[0]:NULL;self->m_pPaperdollModel=(seed/3)%2?models[1]:NULL;self->m_pInventory=seed%5?new CInventory(self,17):NULL;
 CDataGroup*group=new CDataGroup(L"character",NULL,4,4,new TRepository<std::wstring>(L""));self->m_pDataGroup=seed%7?group:NULL;
 if(self->m_pUnitModel){group->AddDataValue(L"TEXTURE_OVERRIDE",value(seed/7),false);for(unsigned i=0;i<(seed/11)%5;++i){CDataGroup*p=group->AddDataGroup(L"TEXTURE_REPLACE");if((seed+i)%3)p->AddDataValue(L"NAME",value(seed+i),false);if((seed+i)%4)p->AddDataValue(L"TEXTURE",value(seed+i+1),false);}}
 if(self->m_pUnitModel&&seed&16){detour::Set setup;TL_REDIRECT(setup,crFiles,&file);TL_REDIRECT(setup,crWardrobeUpdate,&wardrobeUpdate);if(setup.failed())_exit(43);self->m_wardrobe=new CWardrobe(self,services->scene,services->scene,models[0],models[1],L"missing.dds",L"",L"",L"",L"",L"");if(seed&32){wardrobeTexture(self->m_wardrobe)=Ogre::TexturePtr(new CPUTexture);expectedTexture=wardrobeTexture(self->m_wardrobe).getPointer();}}
 phase=2;detour::Set patches;TL_REDIRECT(patches,crRim,&rim);TL_REDIRECT(patches,crTexture,&texture);TL_REDIRECT(patches,crOverride,&overrideTexture);TL_REDIRECT(patches,crSingle,&single);TL_REDIRECT(patches,crEquipped,&equipped);if(patches.failed())_exit(44);
 std::wstring input=value(seed);phase=100;armed=true;typedef void(*F)(CCharacter*,std::wstring);F fn=ours?crNew:crOld;if(!autotest::beginInvocation(capture,fn))return;fn(self,input);capture.callCompleted=1;phase=101;if(ours&&c.control)input+=L"negative";wide(input);if(self->m_wardrobe){num(wardrobeTexture(self->m_wardrobe).isNull()?0:wardrobeTexture(self->m_wardrobe).useCount());wardrobeTexture(self->m_wardrobe).setNull();}num(destroyed);armed=false;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(character_rimlight_runtime){std::setlocale(LC_CTYPE,"C.UTF-8");initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;services=&native;int failures=0;autotest::Coverage coverage("character_rimlight_runtime",(uintptr_t)&crOld);for(unsigned i=0;i<768;++i){Case c={i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    rimlight seed%u status%d/%d bytes%lu/%lu\n",i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}coverage.report(host);return failures;}}coverage.report(host);Case c={63,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    rimlight negative detected%u\n",unsigned(caught));return failures;}
