// Original-versus-recovered icon setup. Real data/string services, UI spies.
#include <cstring>
#include <new>
#include <map>
#include <limits>
#include <Ogre.h>
#include <OgreLogManager.h>
#define private public
#define protected public
#include <CEGUI.h>
#include "Equipment.h"
#include "Inventory.h"
#include "Settings.h"
#include "MasterResourceManager.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalEquipmentIcon, (CEquipment*,CGameUI*,bool), "_ZN10CEquipment10createIconER7CGameUIb")
extern "C" void recoveredEquipmentIcon(CEquipment*,CGameUI*,bool) __asm__("_ZN10CEquipment10createIconER7CGameUIb");
TL_FUNCTION(icIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(icScaled,"_ZN7CGameUI7scaledYEf")
TL_FUNCTION(icImage,"_ZN7CGameUI20getImageFromImageSetEPKh")
TL_FUNCTION(icMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(icFloat,"_ZN20CDynamicPropertyFile8GetFloatEj")
TL_FUNCTION(icUnique,"_ZN7STRINGS10uniqueNameERKSs")
// Both sides link these imported library functions through the same ELF PLT.
extern "C" char icCreate[] __asm__("_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_");
extern "C" char icPosition[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char icSize[] __asm__("_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
extern "C" char icProperty[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
extern "C" char icImageString[] __asm__("_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE");
extern "C" char icAdd[] __asm__("_ZN5CEGUI6Window14addChildWindowEPS0_");
namespace {
#define IC_AT(C,F,O) typedef char checked_##F[__builtin_offsetof(C,F)==O?1:-1]
IC_AT(CEquipment,m_pIconWindow,0x2c8);IC_AT(CEquipment,m_bGamblerIcon,0x25d);
IC_AT(CEGUI::Window,d_children,0x78);IC_AT(CEGUI::Window,d_mousePassThroughEnabled,0x3e2);
IC_AT(CEGUI::Image,d_scaledWidth,0x20);IC_AT(CEGUI::Image,d_scaledHeight,0x24);
#undef IC_AT
typedef char icon_equipment_size[sizeof(CEquipment)==0x438?1:-1];
struct Case{unsigned seed,mode,warm;};
const Case* input;autotest::Capture* capture;CEquipment* object;CGameUI* ui;CCharacter* owner;
CEGUI::Window* windows[2];CEGUI::Image* imageObject;CEGUI::WindowManager* manager;
CMasterResourceManager* masterObject;CSettings* settings;CDataGroup* replacement;
unsigned created,imageCalls,ratioCalls,uniqueCalls;unsigned long long service;
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}
void narrow(const std::string& s){number(s.size());capture->add(s.data(),s.size());}
void cegui(const CEGUI::String& s){number(s.length());for(size_t i=0;i<s.length();++i)number(s[i]);}
void vector(const CEGUI::UVector2& v){real(v.d_x.d_scale);real(v.d_x.d_offset);real(v.d_y.d_scale);real(v.d_y.d_offset);}
int windowId(const CEGUI::Window* w){return w==windows[0]?0:w==windows[1]?1:-1;}
struct Logs:Ogre::LogListener{void messageLogged(const Ogre::String& s,Ogre::LogMessageLevel l,bool d,const Ogre::String&){number(20);narrow(s);number(l);number(d);}};
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){number(1);number(p==owner);number(t);if(input->mode==1)object->m_pDataGroup=replacement;return (input->seed/4)%4==3;}
float scaled(CGameUI* p,float value){number(2);number(p==ui);real(value);return value*(input->seed%3+1)*0.5f;}
std::string unique(const std::string& prefix){number(3);narrow(prefix);return prefix+static_cast<char>('A'+uniqueCalls++);}
CEGUI::Window* create(CEGUI::WindowManager* p,const CEGUI::String& type,const CEGUI::String& name,const CEGUI::String& prefix){number(4);number(p==manager);cegui(type);cegui(name);cegui(prefix);if(created>=2)_exit(61);return windows[created++];}
void size(CEGUI::Window* p,const CEGUI::UVector2& v){number(5);number(windowId(p));vector(v);}
void position(CEGUI::Window* p,const CEGUI::UVector2& v){number(6);number(windowId(p));vector(v);}
const CEGUI::Image* image(CGameUI* p,const unsigned char* name){number(7);number(p==ui);narrow(reinterpret_cast<const char*>(name));++imageCalls;if(input->mode==2&&imageCalls==1)return 0;if(input->mode==3&&imageCalls%2==0)return 0;return imageObject;}
CMasterResourceManager* master(){number(8);return masterObject;}
float ratio(CDynamicPropertyFile* p,unsigned int key){number(9);number(p==settings);number(key==KSETTINGS_YRATIO);static const float values[]={1.0f,0.5f,2.0f,-1.0f,0.0f,1.3f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};unsigned index=input->seed/16;if(input->mode==4)index+=ratioCalls; ++ratioCalls;if(input->mode==5){imageObject->d_scaledWidth+=7;imageObject->d_scaledHeight-=3;}return values[index%8];}
CEGUI::String imageString(const CEGUI::Image* p){number(10);number(p==imageObject);number(p==0);return p?CEGUI::String("image-value"):CEGUI::String("");}
void property(CEGUI::PropertySet* p,const CEGUI::String& key,const CEGUI::String& value){number(11);number(p==static_cast<CEGUI::PropertySet*>(windows[1]));cegui(key);cegui(value);}
void add(CEGUI::Window* p,CEGUI::Window* child){number(12);number(windowId(p));number(windowId(child));p->d_children.push_back(child);}
void put(CDataGroup& g,const wchar_t* key,const std::wstring& value){g.AddDataValue(key,value,false);}
void newIcon(CEquipment* p,CGameUI* u,bool force){p->createIcon(*u,force);}
void oldIcon(CEquipment* p,CGameUI* u,bool force){originalEquipmentIcon(p,u,force);}
// Capture every initialized fixture byte, canonicalizing only named pointer fields.
struct Snapshot {
 std::vector<unsigned char> bytes;
 Snapshot(const void* p,size_t n):bytes(static_cast<const unsigned char*>(p),static_cast<const unsigned char*>(p)+n){}
 void pointer(size_t offset,uintptr_t value){if(offset+sizeof(value)>bytes.size())_exit(62);std::memcpy(&bytes[offset],&value,sizeof(value));}
 void emit(){capture->add(&bytes[0],bytes.size());}
};
void wide(const std::wstring& value){number(value.size());capture->add(value.data(),value.size()*sizeof(wchar_t));int refs;std::memcpy(&refs,reinterpret_cast<const char*>(value.data())-8,4);number(refs);}
void side(const Case& c,bool ours,autotest::Capture& out){
    input=&c;capture=&out;created=imageCalls=ratioCalls=uniqueCalls=0;
    Ogre::LogManager logger;Ogre::Log* log=logger.createLog("equipment-icon-test",true,false,true);Logs listener;log->addListener(&listener);
    CDataGroup data(L"ITEM",0,4,4,0),other(L"OTHER",0,4,4,0);replacement=&other;
    static const wchar_t* icons[]={L"",L"icons/sword",L"icons\\shield",L"\x416\U0001f525",L"missing",L"icon:space name"};
    if(c.seed%7)put(data,L"ICON",icons[(c.seed/32)%6]);if(c.seed%3)put(data,L"GAMBLER_ICON",c.seed%5?L"gamble":L"");put(other,L"GAMBLER_ICON",L"other gamble");put(other,L"ICON",L"other icon");
    static const wchar_t* classes[]={L"destroyer",L"alchemist",L"",L"destroyer",L"unknown"};
    for(unsigned i=0;i<(c.seed/8)%6;++i){CDataGroup* group=data.AddDataGroup(L"WARDROBE");put(*group,L"CLASS",classes[i%5]);if((c.seed+i)%3)put(*group,L"ICON",(c.seed+i)%5?std::wstring(L"wardrobe ")+static_cast<wchar_t>(L'A'+i):L"");}
    if(c.mode==6)put(data,L"ICON",std::wstring(L"icon\0tail",9));
    unsigned long long equipmentStorage[(sizeof(CEquipment)+7)/8],uiStorage[(sizeof(CGameUI)+7)/8],characterStorage[(sizeof(CCharacter)+7)/8],inventoryStorage[(sizeof(CInventory)+7)/8],imageStorage[(sizeof(CEGUI::Image)+7)/8],masterStorage[(sizeof(CMasterResourceManager)+7)/8],windowStorage[2][(sizeof(CEGUI::Window)+7)/8];
    std::memset(equipmentStorage,0,sizeof(equipmentStorage));std::memset(uiStorage,0,sizeof(uiStorage));std::memset(characterStorage,0,sizeof(characterStorage));std::memset(inventoryStorage,0,sizeof(inventoryStorage));std::memset(imageStorage,0,sizeof(imageStorage));std::memset(masterStorage,0,sizeof(masterStorage));std::memset(windowStorage,0,sizeof(windowStorage));
    object=reinterpret_cast<CEquipment*>(equipmentStorage);ui=reinterpret_cast<CGameUI*>(uiStorage);CCharacter* character=reinterpret_cast<CCharacter*>(characterStorage);CInventory* inventory=reinterpret_cast<CInventory*>(inventoryStorage);imageObject=reinterpret_cast<CEGUI::Image*>(imageStorage);masterObject=reinterpret_cast<CMasterResourceManager*>(masterStorage);
    typedef std::wstring Text;new(&object->m_sName)Text(L"ICON TEST");new(&character->m_sName)Text(classes[(c.seed/16)%5]);ui->m_pCharacter=c.seed%11?character:0;
    owner=character;unsigned chain=(c.seed/4)%4;object->m_pInventory=chain?inventory:0;inventory->m_pPositionableObject=chain>=2?reinterpret_cast<CCharacter*>(owner):0;object->m_pDataGroup=c.seed%13?&data:0;object->m_bGamblerIcon=(c.seed&32)!=0;
    typedef std::vector<CEGUI::Window*> Children;
    for(unsigned i=0;i<2;++i){windows[i]=reinterpret_cast<CEGUI::Window*>(windowStorage[i]);new(&windows[i]->d_children)Children();}
    object->m_pIconWindow=(c.seed&2)?windows[0]:0;if(object->m_pIconWindow)windows[0]->d_children.push_back(windows[1]);
    imageObject->d_scaledWidth=16.25f+(c.seed%7)*17.0f;imageObject->d_scaledHeight=32.5f+(c.seed%5)*25.0f;
    manager=reinterpret_cast<CEGUI::WindowManager*>(&service);CEGUI::WindowManager* oldManager=CEGUI::WindowManager::ms_Singleton;CEGUI::WindowManager::ms_Singleton=manager;
    settings=reinterpret_cast<CSettings*>(&service);masterObject->m_pSettings=settings;
    detour::Set patches;TL_REDIRECT(patches,icIsa,&isa);TL_REDIRECT(patches,icScaled,&scaled);TL_REDIRECT(patches,icImage,&image);TL_REDIRECT(patches,icMaster,&master);TL_REDIRECT(patches,icFloat,&ratio);TL_REDIRECT(patches,icUnique,&unique);
    patches.redirect(icCreate,icCreate,&create);patches.redirect(icPosition,icPosition,&position);patches.redirect(icSize,icSize,&size);patches.redirect(icProperty,icProperty,&property);patches.redirect(icImageString,icImageString,&imageString);patches.redirect(icAdd,icAdd,&add);
    if(patches.failed())_exit(42);
    // Missing-image creation deliberately leaves the parent without a child;
    // do not fabricate an original precondition for a forced second call.
    for(unsigned repeat=0;repeat<=c.warm;++repeat){
        bool force=(c.seed&1)!=0;if(repeat&&object->m_pIconWindow&&windows[0]->d_children.empty())force=false;
        if(repeat==c.warm){if(ours)autotest::invoke(out,&recoveredEquipmentIcon,object,ui,force);else autotest::invoke(out,&originalEquipmentIcon,object,ui,force);}
        else {if(ours)newIcon(object,ui,force);else oldIcon(object,ui,force);}
        number(100+repeat);number(object->m_bGamblerIcon);number(windowId(object->m_pIconWindow));number(windows[0]->d_children.size());number(windows[1]->d_mousePassThroughEnabled);number(windows[1]->d_muted);number(created);number(imageCalls);number(ratioCalls);
    }
    wide(object->m_sName);wide(character->m_sName);
    Snapshot e(object,sizeof(*object));
    e.pointer(__builtin_offsetof(CEquipment,m_sName),1);
    e.pointer(__builtin_offsetof(CEquipment,m_pDataGroup),object->m_pDataGroup==&data?1:object->m_pDataGroup==&other?2:object->m_pDataGroup?3:0);
    e.pointer(__builtin_offsetof(CEquipment,m_pInventory),object->m_pInventory==inventory?1:object->m_pInventory?2:0);
    e.pointer(__builtin_offsetof(CEquipment,m_pIconWindow),windowId(object->m_pIconWindow)+2);e.emit();
    Snapshot u(ui,sizeof(*ui));u.pointer(__builtin_offsetof(CGameUI,m_pCharacter),ui->m_pCharacter==character?1:ui->m_pCharacter?2:0);u.emit();
    Snapshot ch(character,sizeof(*character));ch.pointer(__builtin_offsetof(CCharacter,m_sName),1);ch.emit();
    Snapshot inv(inventory,sizeof(*inventory));inv.pointer(__builtin_offsetof(CInventory,m_pPositionableObject),inventory->m_pPositionableObject==owner?1:inventory->m_pPositionableObject?2:0);inv.emit();
    Snapshot im(imageObject,sizeof(*imageObject));im.emit();
    Snapshot mr(masterObject,sizeof(*masterObject));mr.pointer(__builtin_offsetof(CMasterResourceManager,m_pSettings),masterObject->m_pSettings==settings?1:masterObject->m_pSettings?2:0);mr.emit();
    for(unsigned i=0;i<2;++i){Snapshot win(windows[i],sizeof(CEGUI::Window));size_t offset=__builtin_offsetof(CEGUI::Window,d_children);win.pointer(offset,0);win.pointer(offset+8,windows[i]->d_children.size());win.pointer(offset+16,windows[i]->d_children.capacity());win.emit();for(size_t j=0;j<windows[i]->d_children.size();++j)number(windowId(windows[i]->d_children[j]));}
    patches.restore();CEGUI::WindowManager::ms_Singleton=oldManager;object->m_sName.~Text();character->m_sName.~Text();for(unsigned i=0;i<2;++i)windows[i]->d_children.~Children();log->removeListener(&listener);
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_icon_differential){
    autotest::Coverage coverage("equipment_icon_differential",(uint64_t)(uintptr_t)&originalEquipmentIcon);
    unsigned count=0;
    for(unsigned n=0;n<1280;++n)for(unsigned warm=0;warm<2;++warm){Case c={n<896?n:1+(n-896)%64,n<896?0u:1+(n-896)/64,warm};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);++count;
        int pair=coverage.observe(host,a,b);
        bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok){size_t i=0;while(i<a.capture.length&&i<b.capture.length&&a.capture.data[i]==b.capture.data[i])++i;host->log("    icon %u mode %u warm %u: status %d/%d bytes %lu/%lu first %lu\n",c.seed,c.mode,c.warm,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)i);coverage.report(host);return 1;}
    }
    coverage.report(host);host->log("    equipment icon: %u completed cold/warm cases\n",count);return 0;
}
