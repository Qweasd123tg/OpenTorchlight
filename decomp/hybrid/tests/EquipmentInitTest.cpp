// Controlled child initializer, with real DataGroups, string/path operations,
// effect and sound-bank construction. Rendering and game services are spies.
#include <cstring>
#include <new>
#include <map>
#include <Ogre.h>
#include <OgreLogManager.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#define protected public
#include "Equipment.h"
#include "Effect.h"
#include "EffectManager.h"
#include "DataGroup.h"
#include "ResourceManager.h"
#include "MasterResourceManager.h"
#include "GameClient.h"
#include "GameUI.h"
#include "Character.h"
#include "SoundBank.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#undef private
#undef protected
TL_ORIGINAL(void, originalEquipmentInit, (CEquipment*,CDataGroup*,bool), "_ZN10CEquipment8unitInitEP10CDataGroupb")
extern "C" void recoveredEquipmentInit(CEquipment*,CDataGroup*,bool) __asm__("_ZN10CEquipment8unitInitEP10CDataGroupb");
TL_FUNCTION(eiParent,"_ZN5CItem8unitInitEP10CDataGroupb")
TL_FUNCTION(eiLoad,"_ZN10CEquipment9loadModelESbIwSt11char_traitsIwESaIwEES3_")
TL_FUNCTION(eiCombat,"_ZN10CEquipment20calculateCombatStatsEb")
TL_FUNCTION(eiRequirements,"_ZN10CEquipment15setRequirementsEv")
TL_FUNCTION(eiEnchant,"_ZN10CEquipment7enchantEb")
TL_FUNCTION(eiElemental,"_ZN10CEquipment22createElementalDamagesEv")
TL_FUNCTION(eiPrice,"_ZN10CEquipment16recalculatePriceEv")
TL_FUNCTION(eiEffectValues,"_ZN14CEffectManager21calculateEffectValuesEv")
TL_FUNCTION(eiIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(eiMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(eiSound,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(eiSample,"_ZN10CSoundBank9addSampleEix")
TL_FUNCTION(eiAddEffect,"_ZN9CBaseUnit12addNewEffectEP7CEffect")
TL_FUNCTION(eiRandomFloat,"_ZN9UTILITIES21randomBetweenVolatileEff")
namespace {
#define EI_AT(C,F,O) typedef char checked_##C##_##F[__builtin_offsetof(C,F)==O?1:-1]
EI_AT(CEquipment,m_sUnidentifiedName,0x2d0);EI_AT(CEquipment,m_sDisplayName,0x2d8);
EI_AT(CGameClient,m_pGameUI,0x78);EI_AT(CGameUI,m_pCharacter,0x38);
EI_AT(CMasterResourceManager,m_pSoundManager,0x98);EI_AT(CMasterResourceManager,m_pSoundBankDataInformation,0x100);EI_AT(CSoundData,m_iGuid,0x20);
#undef EI_AT
typedef char equipment_size[sizeof(CEquipment)==0x438?1:-1];
typedef char client_size[sizeof(CGameClient)==0x3910?1:-1];
typedef char ui_size[sizeof(CGameUI)==0x1a08?1:-1];
struct Case {unsigned seed,mode;};
const Case* input;autotest::Capture* capture;CEquipment* object;CDataGroup* rootData;CDataGroup* effectiveData;
CMasterResourceManager* masterObject;CSoundBankDataInformation* soundInfo;CSoundData* soundData;
std::vector<CEffect*>* effects;unsigned soundCalls;unsigned long long services[8];
void number(int n){capture->add(&n,sizeof(n));}
void real(float x){capture->add(&x,sizeof(x));}
void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
void narrow(const std::string& s){number(s.size());capture->add(s.data(),s.size());}
struct Logs:Ogre::LogListener{virtual void messageLogged(const Ogre::String& s,Ogre::LogMessageLevel level,bool debug,const Ogre::String&){number(20);narrow(s);number(level);number(debug);}};
void parent(CItem* p,CDataGroup* data,bool skip){number(1);number(p==object);number(data==rootData);number(skip);object->m_pDataGroup=input->seed%3?effectiveData:data;}
void load(CEquipment* p,std::wstring mesh,std::wstring material){number(2);number(p==object);text(mesh);text(material);if(input->mode==5)object->m_bUnknown25F=!object->m_bUnknown25F;}
void combat(CEquipment* p,bool skip){number(3);number(p==object);number(skip);object->m_iMinimumDamage=17;object->m_iMaximumDamage=23;if(input->mode==4)object->m_bUnknown348=!object->m_bUnknown348;}
void requirements(CEquipment* p){number(4);number(p==object);object->m_iUnknown278=7;}
void enchant(CEquipment* p,bool flag){number(5);number(p==object);number(flag);number(object->m_bUnknown348);if(input->seed%4==0)object->m_bUnknown348=true;if(input->seed%4==1)object->m_bUnknown348=false;if(input->mode==2)object->m_pDataGroup=object->m_pDataGroup==rootData?effectiveData:rootData;}
void elemental(CEquipment* p){number(6);number(p==object);number(object->m_bUnknown348);if(input->mode==6)object->m_bUnknown430=false;}
void price(CEquipment* p){number(7);number(p==object);object->m_iUnknown264=123;}
void effectValues(CEffectManager* p){number(8);number(p==reinterpret_cast<CEffectManager*>(&services[3]));}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){number(9);number(p==object);number(t);return t==UNITTYPES::UNIQUE?input->seed%5==0||input->seed%5==2:t==UNITTYPES::SOCKETABLE?input->seed%5==1||input->seed%5==2:false;}
CMasterResourceManager* master(){number(10);return masterObject;}
CSoundData* sound(CSoundBankDataInformation* p,const std::wstring& name){number(11);number(p==soundInfo);text(name);++soundCalls;if(input->mode==3&&soundCalls==1)masterObject->m_pSoundBankDataInformation=reinterpret_cast<CSoundBankDataInformation*>(&services[5]);if(name.empty()||name.find(L"MISSING")!=std::wstring::npos)return 0;soundData->m_iGuid=1234567890123LL+soundCalls;return soundData;}
void sample(CSoundBank* p,int slot,long long guid){number(12);number(p==object->m_pSoundBank);number(slot);capture->add(&guid,sizeof(guid));}
CEffect* addEffect(CBaseUnit* p,CEffect* effect){number(13);number(p==object);const char* b=reinterpret_cast<const char*>(effect);number(*reinterpret_cast<const int*>(b+0x1c));number(*reinterpret_cast<const int*>(b+0x20));real(*reinterpret_cast<const float*>(b+0x24));number(b[0x30]);real(*reinterpret_cast<const float*>(b+0x38));real(*reinterpret_cast<const float*>(b+0xc4));effects->push_back(effect);return effect;}
float randomFloat(float lo,float hi){number(14);real(lo);real(hi);return lo+(hi-lo)*0.25f;}
void put(CDataGroup& g,const wchar_t* key,const std::wstring& value){g.AddDataValue(key,value,false);}
void putInt(CDataGroup& g,const wchar_t* key,int value){g.AddDataValue(key,static_cast<unsigned int>(value));}
void populate(CDataGroup& g,unsigned n,bool effective){
    std::wstring prefix=effective?L"E":L"R";
    static const wchar_t* const labels[]={L"{tag}Name{later}",L"{}Name",L"{Name",L"}Name{x}",L"",L"Name\x416",L"Plain"};
    put(g,L"NAME",prefix+L"Name");put(g,L"UNIDENTIFIED_NAME",labels[n%7]);if(n%3)put(g,L"DISPLAYNAME",prefix+labels[(n+2)%7]);
    put(g,L"MESHFILE",n%8==0||n%8==6?L"":n%3?L"Sword":L"already.mesh");put(g,L"RESOURCEDIRECTORY",L"media\\units//items");
    static const wchar_t* const uses[]={L"unlimited",L"0",L"12",L"-3",L"not_a_number"};put(g,L"USES",uses[n%5]);
    static const wchar_t* const targets[]={L"user",L"item",L"unknown",L""};put(g,L"TARGET_TYPE",targets[(n/5)%4]);
    if(n%3)g.AddDataValue(L"MERCHANTINFINITE",(n&2)!=0);putInt(g,L"MAXSTACKSIZE",static_cast<int>(n%5)-1);
    put(g,L"DROPPARTICLE",n%2?L"media\\Particles//drop.layout":L"");putInt(g,L"LEVEL",static_cast<int>(n%11)-1);putInt(g,L"SOCKETS",static_cast<int>(n%6)-2);
    static const int blocks[]={0,1,-1,25,-25};putInt(g,L"BLOCK_CHANCE",blocks[(n/3)%5]);g.AddDataValue(L"ALWAYS_IDENTIFIED",effective?(n%2==0):(n%2!=0));
    static const wchar_t* const sounds[]={L"FALL_SOUND",L"LAND_SOUND",L"TAKE_SOUND",L"ATTACK_SOUND",L"STRIKE_SOUND",L"USE_SOUND"};
    for(unsigned i=0;i<6;++i)if((n+i)%3)put(g,sounds[i],(n+i)%5?prefix+sounds[i]:L"missing");
    put(g,L"ATTACHEDLAYOUT",n%4?L"attached.layout":L"");
    for(unsigned i=0;i<n%5;++i){CDataGroup* w=g.AddDataGroup(L"WARDROBE");static const wchar_t* const classes[]={L"destroyer",L"alchemist",L"",L"destroyer"};put(*w,L"CLASS",classes[i]);put(*w,L"ITEM_MESH",(n+i)%4?prefix+std::wstring(1,L'A'+i)+L"\\raw.mesh":L"");}
}
void side(const Case& c,bool ours,autotest::Capture& out){
    input=&c;capture=&out;soundCalls=0;
    Ogre::LogManager logger;Ogre::Log* log=logger.createLog("equipment-init-test",true,false,true);Logs listener;log->addListener(&listener);
    CDataGroup data(L"UNIT",0,4,4,0),effective(L"EFFECTIVE",0,4,4,0);rootData=&data;effectiveData=&effective;if(c.mode!=7){populate(data,c.seed,false);populate(effective,c.seed,true);}
    unsigned long long storage[(sizeof(CEquipment)+7)/8];std::memset(storage,0,sizeof(storage));object=reinterpret_cast<CEquipment*>(storage);
    new(&object->m_sName)std::wstring(L"TEST ITEM");new(&object->m_sUnidentifiedName)std::wstring(L"old U");new(&object->m_sDisplayName)std::wstring(L"old D");new(&object->m_sUnknown3D8)std::wstring(L"old P");
    object->m_bUnknown25F=(c.seed&1)!=0;object->m_bUnknown348=(c.seed&4)!=0;object->m_bUnknown430=(c.seed&8)!=0;object->m_iUnknown260=77;
    unsigned long long resourceStorage[(sizeof(CResourceManager)+7)/8];std::memset(resourceStorage,0,sizeof(resourceStorage));CResourceManager* resources=reinterpret_cast<CResourceManager*>(resourceStorage);
    new(&resources->m_GameClients)TArrayList<CGameClient*>();object->m_pResourceManager=c.seed%8==6?0:resources;
    unsigned long long clientStorage[(sizeof(CGameClient)+7)/8],uiStorage[(sizeof(CGameUI)+7)/8],characterStorage[(sizeof(CCharacter)+7)/8];
    std::memset(clientStorage,0,sizeof(clientStorage));std::memset(uiStorage,0,sizeof(uiStorage));std::memset(characterStorage,0,sizeof(characterStorage));
    CGameClient* client=reinterpret_cast<CGameClient*>(clientStorage);CGameUI* ui=reinterpret_cast<CGameUI*>(uiStorage);CCharacter* character=reinterpret_cast<CCharacter*>(characterStorage);
    static const wchar_t* const classes[]={L"destroyer",L"alchemist",L"",L"unknown",L"\x416"};new(&character->m_sName)std::wstring(classes[(c.seed/8+c.seed/40)%5]);
    unsigned chain=c.seed%8;if(chain!=0){resources->m_GameClients.add(chain==1?0:client);resources->m_GameClients.add(client);}client->m_pGameUI=chain==2?0:ui;ui->m_pCharacter=chain==3?0:character;
    unsigned long long masterStorage[0x190/8],soundStorage[(sizeof(CSoundData)+7)/8];std::memset(masterStorage,0,sizeof(masterStorage));std::memset(soundStorage,0,sizeof(soundStorage));
    masterObject=reinterpret_cast<CMasterResourceManager*>(masterStorage);soundInfo=reinterpret_cast<CSoundBankDataInformation*>(&services[2]);soundData=reinterpret_cast<CSoundData*>(soundStorage);
    masterObject->m_pSoundManager=reinterpret_cast<CSoundManager*>(&services[0]);masterObject->m_pSoundBankDataInformation=soundInfo;
    object->m_pEffectManager=c.seed%3?reinterpret_cast<CEffectManager*>(&services[3]):0;
    int beforeCount=g_iTotalCountOfObjects;if(c.seed%2)object->m_pSoundBank=new CSoundBank(*masterObject->m_pSoundManager,false);
    std::vector<CEffect*> owned;effects=&owned;
    detour::Set patches;TL_REDIRECT(patches,eiParent,&parent);TL_REDIRECT(patches,eiLoad,&load);TL_REDIRECT(patches,eiCombat,&combat);TL_REDIRECT(patches,eiRequirements,&requirements);TL_REDIRECT(patches,eiEnchant,&enchant);TL_REDIRECT(patches,eiElemental,&elemental);TL_REDIRECT(patches,eiPrice,&price);TL_REDIRECT(patches,eiEffectValues,&effectValues);TL_REDIRECT(patches,eiIsa,&isa);TL_REDIRECT(patches,eiMaster,&master);TL_REDIRECT(patches,eiSound,&sound);TL_REDIRECT(patches,eiSample,&sample);TL_REDIRECT(patches,eiAddEffect,&addEffect);TL_REDIRECT(patches,eiRandomFloat,&randomFloat);
    if(patches.failed())_exit(42);
    for(int repeat=0;repeat<2;++repeat){
        CDataGroup* arg=c.mode==1?0:&data;bool skip=(c.seed/2)%2!=0;if(repeat==0){if(ours)autotest::invoke(out,&recoveredEquipmentInit,object,arg,skip);else autotest::invoke(out,&originalEquipmentInit,object,arg,skip);}else{if(ours)object->CEquipment::unitInit(arg,skip);else originalEquipmentInit(object,arg,skip);}
        number(100+repeat);text(object->m_sUnidentifiedName);text(object->m_sDisplayName);text(object->m_sUnknown3D8);number(object->m_iUnknown248);number(object->m_iUnknown260);number(object->m_bUnknown25F);number(object->m_iUnknown23C);number(object->m_iUnknown274);number(object->m_iSocketCount);number(object->m_bUnknown348);number(object->m_bUnknown430);number(object->m_iMinimumDamage);number(object->m_iMaximumDamage);number(object->m_iUnknown278);number(object->m_iUnknown264);
        number(object->m_pSoundBank!=0);if(object->m_pSoundBank){const char* b=reinterpret_cast<const char*>(object->m_pSoundBank);number(*reinterpret_cast<CSoundManager*const*>(b+0x10)==masterObject->m_pSoundManager);number(b[0xb4]);}number(owned.size());number(g_iTotalCountOfObjects-beforeCount);
    }
    for(unsigned i=0;i<owned.size();++i)delete owned[i];if(object->m_pSoundBank)delete object->m_pSoundBank;number(g_iTotalCountOfObjects-beforeCount);patches.restore();
    typedef std::wstring Text;object->m_sName.~Text();object->m_sUnidentifiedName.~Text();object->m_sDisplayName.~Text();object->m_sUnknown3D8.~Text();character->m_sName.~Text();resources->m_GameClients.~TArrayList<CGameClient*>();log->removeListener(&listener);
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}
void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_init_differential){
    int failures=0;
    autotest::Coverage coverage("equipment_init_differential",(uint64_t)(uintptr_t)&originalEquipmentInit);
    for(unsigned n=0;n<1140;++n){Case c={n<480?n:n<560?n-480:n<1060?80+(n-560)%100:n-1060,n<480?0u:n<560?1u:n<1060?2+(n-560)/100:7u};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        int observation=coverage.observe(host,a,b);
        bool ok=observation==0&&WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok)host->log("    comparison_kind=%d\n",observation);
        if(!ok){size_t i=0;while(i<a.capture.length&&i<b.capture.length&&a.capture.data[i]==b.capture.data[i])++i;host->log("    init %u mode %u: status %d/%d bytes %lu/%lu first %lu\n",c.seed,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)i);}
        TL_CHECK(failures,ok);
    }
    coverage.report(host);
    host->log("    equipment init: 1140 cases, two calls per side\n");return failures;
}
