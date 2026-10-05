// Complete updateIngameUI draft; NOT an accepted production replacement.
// Original ABI/layout for ELF 91b41ae9..., GCC 4.4.7, Ogre 1.6.5, CEGUI 0.6.x.
#ifndef OTL_GAMEUI_RECOVERED_PHASES_H
#define OTL_GAMEUI_RECOVERED_PHASES_H
#include <Ogre.h>
#include <OgreUTFString.h>
#include <cmath>
#include <CEGUIString.h>
#include <CEGUIUDim.h>
#include <CEGUIcolour.h>
#include <CEGUIPropertyHelper.h>
#include <string>
namespace gameui_recovered {
template<class T> inline T& field(void* p,unsigned offset){return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);}
namespace service {
extern int hp(void*) __asm__("_ZN10CCharacter2HPEv");
extern int maxhp(void*) __asm__("_ZN10CCharacter5maxHPEv");
extern float mana(void*) __asm__("_ZN10CCharacter9manaFloatEv");
extern int maxmana(void*) __asm__("_ZN10CCharacter7maxManaEv");
extern bool covered(void*) __asm__("_ZN7CGameUI11leftCoveredEv");
extern bool nearDeath(void*) __asm__("_ZN10CCharacter14isPetNearDeathEv");
extern bool modal(void*) __asm__("_ZN7CGameUI22modalDialogOpenPartialEv");
extern void* manager() __asm__("_ZN22CMasterResourceManager12getSingletonEv");
extern int gate(void*,int) __asm__("_ZN22CMasterResourceManager14experienceGateEi");
extern std::wstring levelValue(void*) __asm__("_ZN6CLevel7getNameEv");
extern std::string originalNumber(int) __asm__("_ZN7STRINGS16GetValueAsStringEi");
extern std::string originalUnsigned(unsigned) __asm__("_ZN7STRINGS16GetValueAsStringEj");
extern std::string originalNarrow(const wchar_t*) __asm__("_ZN7STRINGS21StringConvertToNarrowEPKw");
extern std::string originalUTF8(const std::wstring&) __asm__("_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE");
extern float widthRead(void*) __asm__("_ZN7CGameUI14getWindowWidthEv");
extern float heightRead(void*) __asm__("_ZN7CGameUI15getWindowHeightEv");
extern float rightRead(void*) __asm__("_ZN7CGameUI15rightScreenEdgeEv");
extern float leftRead(void*) __asm__("_ZN7CGameUI14leftScreenEdgeEv");
extern float settingFloat(void*,unsigned) __asm__("_ZN20CDynamicPropertyFile8GetFloatEj");
extern void* editor() __asm__("_ZN7CEditor12getSingletonEv");
extern void events(void*,float,Ogre::Vector3&,Ogre::Matrix4&,bool) __asm__("_ZN7CGameUI16updateTextEventsEfRN4Ogre7Vector3ERNS0_7Matrix4Eb");
extern void* global() __asm__("_ZN12CGameGlobals12getSingletonEv");
extern const std::wstring& getTip(void*,int) __asm__("_ZN12CGameGlobals13getContextTipE11EContextTip");
extern void contents(void*,std::wstring&) __asm__("_ZN8CTipMenu11setContentsERSbIwSt11char_traitsIwESaIwEE");
extern bool consoleIsVisible(void*) __asm__("_ZN8CConsole10getVisibleEv");
extern void consoleTick(void*,float) __asm__("_ZN8CConsole6updateEf");
extern void finalTick(void*,float,void*,void*) __asm__("_ZN12CMenuManager6updateEfP11CGameClientPN4Ogre12RenderWindowE");
extern void native_visible(void* p,bool value) __asm__("_ZN5CEGUI6Window10setVisibleEb");
inline void visible(void* p,bool value){
#ifdef OTL_RECOVERED_TEST_PLT
    typedef void (*Fn)(void* p,bool value); return reinterpret_cast<Fn>(0x554718)(p,value);
#else
    return native_visible(p,value);
#endif
}
extern void native_position(void* p,const CEGUI::UVector2& value) __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
inline void position(void* p,const CEGUI::UVector2& value){
#ifdef OTL_RECOVERED_TEST_PLT
    typedef void (*Fn)(void* p,const CEGUI::UVector2& value); return reinterpret_cast<Fn>(0x5548a8)(p,value);
#else
    return native_position(p,value);
#endif
}
extern void native_size(void* p,const CEGUI::UVector2& value) __asm__("_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
inline void size(void* p,const CEGUI::UVector2& value){
#ifdef OTL_RECOVERED_TEST_PLT
    typedef void (*Fn)(void* p,const CEGUI::UVector2& value); return reinterpret_cast<Fn>(0x555178)(p,value);
#else
    return native_size(p,value);
#endif
}
extern void native_tooltip(void* p,const CEGUI::String& value) __asm__("_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE");
inline void tooltip(void* p,const CEGUI::String& value){
#ifdef OTL_RECOVERED_TEST_PLT
    typedef void (*Fn)(void* p,const CEGUI::String& value); return reinterpret_cast<Fn>(0x554b48)(p,value);
#else
    return native_tooltip(p,value);
#endif
}
extern void native_select(void* p,bool value) __asm__("_ZN5CEGUI11RadioButton11setSelectedEb");
inline void select(void* p,bool value){
#ifdef OTL_RECOVERED_TEST_PLT
    typedef void (*Fn)(void* p,bool value); return reinterpret_cast<Fn>(0x554dc8)(p,value);
#else
    return native_select(p,value);
#endif
}
extern void native_text(void* p,const CEGUI::String& value) __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
inline void text(void* p,const CEGUI::String& value){
#ifdef OTL_RECOVERED_TEST_PLT
    typedef void (*Fn)(void* p,const CEGUI::String& value); return reinterpret_cast<Fn>(0x555c08)(p,value);
#else
    return native_text(p,value);
#endif
}
extern void native_property(void* p,const CEGUI::String& key,const CEGUI::String& value) __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
inline void property(void* p,const CEGUI::String& key,const CEGUI::String& value){
#ifdef OTL_RECOVERED_TEST_PLT
    typedef void (*Fn)(void* p,const CEGUI::String& key,const CEGUI::String& value); return reinterpret_cast<Fn>(0x5532d8)(p,key,value);
#else
    return native_property(p,key,value);
#endif
}
extern const Ogre::Quaternion& native_cameraOrientation(void* p) __asm__("_ZNK4Ogre6Camera14getOrientationEv");
inline const Ogre::Quaternion& cameraOrientation(void* p){
#ifdef OTL_RECOVERED_TEST_PLT
    typedef const Ogre::Quaternion& (*Fn)(void* p); return reinterpret_cast<Fn>(0x554d48)(p);
#else
    return native_cameraOrientation(p);
#endif
}
extern const Ogre::Vector3& native_cameraPosition(void* p) __asm__("_ZNK4Ogre6Camera11getPositionEv");
inline const Ogre::Vector3& cameraPosition(void* p){
#ifdef OTL_RECOVERED_TEST_PLT
    typedef const Ogre::Vector3& (*Fn)(void* p); return reinterpret_cast<Fn>(0x5545c8)(p);
#else
    return native_cameraPosition(p);
#endif
}
extern int settingInt(void*,unsigned) __asm__("_ZN20CDynamicPropertyFile6GetIntEj");
extern bool buttonPressed(void*,unsigned) __asm__("_ZN13CMouseManager13buttonPressedE12EMouseButton");
extern bool buttonHeld(void*,unsigned) __asm__("_ZN13CMouseManager10buttonHeldE12EMouseButton");
extern bool native_isVisible(void* p,bool inherited) __asm__("_ZNK5CEGUI6Window9isVisibleEb");
inline bool isVisible(void* p,bool inherited){
#ifdef OTL_RECOVERED_TEST_PLT
 typedef bool(*Fn)(void* p,bool inherited);return reinterpret_cast<Fn>(0x5561d8)(p,inherited);
#else
 return native_isVisible(p,inherited);
#endif
}
extern CEGUI::UDim native_windowWidth(void* p) __asm__("_ZNK5CEGUI6Window8getWidthEv");
inline CEGUI::UDim windowWidth(void* p){
#ifdef OTL_RECOVERED_TEST_PLT
 typedef CEGUI::UDim(*Fn)(void* p);return reinterpret_cast<Fn>(0x5560d8)(p);
#else
 return native_windowWidth(p);
#endif
}
extern CEGUI::UDim native_windowHeight(void* p) __asm__("_ZNK5CEGUI6Window9getHeightEv");
inline CEGUI::UDim windowHeight(void* p){
#ifdef OTL_RECOVERED_TEST_PLT
 typedef CEGUI::UDim(*Fn)(void* p);return reinterpret_cast<Fn>(0x552ab8)(p);
#else
 return native_windowHeight(p);
#endif
}
extern void closeAll(void*) __asm__("_ZN7CGameUI8closeAllEv");
extern void sound(void*,int,float,float) __asm__("_ZN10CSoundBank17queueGlobalSampleEiff");
extern void merchantPlayer(void*,void*) __asm__("_ZN13CMerchantMenu9setPlayerEP10CCharacter");
extern void combinePlayer(void*,void*) __asm__("_ZN12CCombineMenu9setPlayerEP10CCharacter");
extern void enchantPlayer(void*,void*) __asm__("_ZN12CEnchantMenu9setPlayerEP10CCharacter");
extern void stashPlayer(void*,void*) __asm__("_ZN10CStashMenu9setPlayerEP10CCharacter");
extern void enchantOwner(void*,void*) __asm__("_ZN12CEnchantMenu12setOwnerItemEP5CItem");
extern void enchantOpen(void*,bool,unsigned) __asm__("_ZN12CEnchantMenu7setOpenEb8EAIState");
extern std::wstring formatLimit(int) __asm__("_ZN7STRINGS17GetValueAsWStringEi");
extern void modalDialog(void*,std::wstring,std::wstring,bool) __asm__("_ZN7CGameUI15openModalDialogESbIwSt11char_traitsIwESaIwEES3_b");
extern bool isA(void*,unsigned) __asm__("_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE");
extern void returnDragged(void*) __asm__("_ZN7CGameUI17returnDraggedItemEv");
extern void* questForNPC(void*,void*) __asm__("_ZN13CQuestManager14getQuestForNPCEP9CBaseUnit");
extern void questNPC(void*,void*,bool,void*) __asm__("_ZN16CQuestDialogMenu6setNPCEP9CBaseUnitbP6CQuest");
extern void setTarget(void*,void*) __asm__("_ZN10CCharacter9setTargetEPS_");
extern void setTargetItem(void*,void*) __asm__("_ZN10CCharacter13setTargetItemEP5CItem");
extern void removeSafe(void*,void*,unsigned) __asm__("_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj");
extern void mouseOverItem(void*,void*,bool) __asm__("_ZN7CGameUI16setMouseOverItemEP5CItemb");
extern bool eitherCovered(void*) __asm__("_ZN7CGameUI20eitherCoveredPartialEv");
extern bool modalFull(void*) __asm__("_ZN7CGameUI15modalDialogOpenEv");
extern void slots(void*) __asm__("_ZN7CGameUI11updateSlotsEv");
extern void* translator() __asm__("_ZN16CStringTranslate11getSingltonEv");
extern std::wstring translate(void*,const wchar_t*) __asm__("_ZN16CStringTranslate18getTranslateStringEPKw");
extern bool bothCovered(void*) __asm__("_ZN7CGameUI18bothCoveredPartialEv");
extern bool keyHeld(void*,unsigned) __asm__("_ZN11CKeyManager7keyHeldEj");
extern Ogre::Vector3 objectPosition(void*,bool) __asm__("_ZN19CPositionableObject11getPositionEb");
extern Ogre::Vector3 screenPosition(void*,const Ogre::Vector3*,const Ogre::Vector3*,Ogre::Matrix4) __asm__("_ZN7CGameUI17getScreenPositionEPKN4Ogre7Vector3ES3_NS0_7Matrix4E");
extern float scaledY(void*,float) __asm__("_ZN7CGameUI7scaledYEf");
extern std::string uniqueName(const std::string&) __asm__("_ZN7STRINGS10uniqueNameERKSs");
extern std::wstring mimicName(void*) __asm__("_ZN10CCharacter12getMimicNameEv");
extern std::wstring equipmentSet(void*) __asm__("_ZN10CEquipment6getSetEv");
extern bool questUnit(void*) __asm__("_ZN9CBaseUnit14getIsQuestUnitEv");
extern void hideItem(void*) __asm__("_ZN5CItem12hideItemTextEv");
extern void showItem(void*) __asm__("_ZN5CItem12showItemTextEv");
extern void hideCharacter(void*) __asm__("_ZN10CCharacter17hideCharacterTextEv");
extern void showCharacter(void*) __asm__("_ZN10CCharacter17showCharacterTextEv");
extern unsigned keyShowItems __asm__("KSETTINGS_KEYMAP_SHOWITEMS");
extern void* windowManager __asm__("_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE");
extern char itemType __asm__("_ZTI5CItem");
extern char equipmentType __asm__("_ZTI10CEquipment");
extern void* native_createWindow(void* p,const CEGUI::String& type,const CEGUI::String& name,const CEGUI::String& prefix) __asm__("_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_");
inline void* createWindow(void* p,const CEGUI::String& type,const CEGUI::String& name,const CEGUI::String& prefix){
#ifdef OTL_RECOVERED_TEST_PLT
 typedef void*(*Fn)(void* p,const CEGUI::String& type,const CEGUI::String& name,const CEGUI::String& prefix);return reinterpret_cast<Fn>(0x5530d8)(p,type,name,prefix);
#else
 return native_createWindow(p,type,name,prefix);
#endif
}
extern void* native_font(void* p,bool inherited) __asm__("_ZNK5CEGUI6Window7getFontEb");
inline void* font(void* p,bool inherited){
#ifdef OTL_RECOVERED_TEST_PLT
 typedef void*(*Fn)(void* p,bool inherited);return reinterpret_cast<Fn>(0x554028)(p,inherited);
#else
 return native_font(p,inherited);
#endif
}
extern CEGUI::UVector2 native_windowSize(void* p) __asm__("_ZNK5CEGUI6Window7getSizeEv");
inline CEGUI::UVector2 windowSize(void* p){
#ifdef OTL_RECOVERED_TEST_PLT
 typedef CEGUI::UVector2(*Fn)(void* p);return reinterpret_cast<Fn>(0x5532a8)(p);
#else
 return native_windowSize(p);
#endif
}
extern float native_textExtent(void* p,const CEGUI::String& text,float scale) __asm__("_ZN5CEGUI4Font13getTextExtentERKNS_6StringEf");
inline float textExtent(void* p,const CEGUI::String& text,float scale){
#ifdef OTL_RECOVERED_TEST_PLT
 typedef float(*Fn)(void* p,const CEGUI::String& text,float scale);return reinterpret_cast<Fn>(0x555ba8)(p,text,scale);
#else
 return native_textExtent(p,text,scale);
#endif
}
extern void* native_castEquipment(void* p,const void* source,const void* target,long offset) __asm__("__dynamic_cast");
inline void* castEquipment(void* p,const void* source,const void* target,long offset){
#ifdef OTL_RECOVERED_TEST_PLT
 typedef void*(*Fn)(void* p,const void* source,const void* target,long offset);return reinterpret_cast<Fn>(0x555758)(p,source,target,offset);
#else
 return native_castEquipment(p,source,target,offset);
#endif
}
extern bool hasTheme(void*,const std::wstring&) __asm__("_ZN9CBaseUnit12hasUnitThemeERKSbIwSt11char_traitsIwESaIwEE");
extern unsigned addSafe(void*,void*) __asm__("_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE");
extern std::wstring description(void*) __asm__("_ZN10CCharacter14getDescriptionEv");
extern bool automapVisible(void*) __asm__("_ZN6CLevel17getAutomapVisibleEv");
extern void settingSetInt(void*,unsigned,int) __asm__("_ZN20CDynamicPropertyFile6SetIntEji");
extern const std::wstring& settingString(void*,unsigned) __asm__("_ZN20CDynamicPropertyFile9GetStringEj");
extern std::string originalFloat(float) __asm__("_ZN7STRINGS16GetValueAsStringEf");
extern void* missilePreloader(void*) __asm__("_ZN16CResourceManager19getMissilePreloaderEv");
extern int particleCacheCount(void*) __asm__("_ZN18CParticlePreloader21getParticleCacheCountEv");
extern int channelsPlaying(void*) __asm__("_ZN13CSoundManager26getNumberOfChannelsPlayingEv");
extern void* roomAt(void*,const Ogre::Vector3&) __asm__("_ZN6CLevel23getRoomThatPositionIsInERKN4Ogre7Vector3E");
extern std::string fileName(const std::string&) __asm__("_ZN10FILESYSTEM11GetFileNameERKSs");
extern unsigned key_DISPLAY_STATS __asm__("KSETTINGS_DISPLAY_STATS");
extern unsigned key_UPDATE_PERF __asm__("KSETTINGS_UPDATE_PERF");
extern unsigned key_NUM_TICKS_PER_SECOND __asm__("KSETTINGS_NUM_TICKS_PER_SECOND");
extern unsigned key_CURRENT_FPS __asm__("KSETTINGS_CURRENT_FPS");
extern unsigned key_S_VERSION __asm__("KSETTINGS_S_VERSION");
extern unsigned key_F_AVERAGE_FPS __asm__("KSETTINGS_F_AVERAGE_FPS");
extern void* native_materialManager() __asm__("_ZN4Ogre15MaterialManager12getSingletonEv");
inline void* materialManager(){
#ifdef OTL_RECOVERED_TEST_PLT
 typedef void*(*Fn)();return reinterpret_cast<Fn>(0x553708)();
#else
 return native_materialManager();
#endif
}
extern void* native_meshManager() __asm__("_ZN4Ogre11MeshManager12getSingletonEv");
inline void* meshManager(){
#ifdef OTL_RECOVERED_TEST_PLT
 typedef void*(*Fn)();return reinterpret_cast<Fn>(0x553c78)();
#else
 return native_meshManager();
#endif
}
extern void* native_textureManager() __asm__("_ZN4Ogre14TextureManager12getSingletonEv");
inline void* textureManager(){
#ifdef OTL_RECOVERED_TEST_PLT
 typedef void*(*Fn)();return reinterpret_cast<Fn>(0x554988)();
#else
 return native_textureManager();
#endif
}
extern void native_front(void* p) __asm__("_ZN5CEGUI6Window11moveToFrontEv");
inline void front(void* p){
#ifdef OTL_RECOVERED_TEST_PLT
 typedef void(*Fn)(void* p);return reinterpret_cast<Fn>(0x5547c8)(p);
#else
 return native_front(p);
#endif
}
} // namespace service
struct Labels { const char* hp;const char* mana;const char* xp;const char* fleeing; };
// Matches the four original function-local initialization sites, in order.
// First-use and retry after translation exceptions are original-compared.
inline std::string translatedUTF8(const wchar_t* key){std::wstring text=service::translate(service::translator(),key);return service::originalUTF8(text);}
inline Labels localizedLabels(){
    static std::string hp=translatedUTF8(L"HP");
    static std::string mana=translatedUTF8(L"Mana");
    static std::string xp=translatedUTF8(L"XP");
    static std::string fleeing=translatedUTF8(L"Fleeing");
    Labels result={hp.c_str(),mana.c_str(),xp.c_str(),fleeing.c_str()};return result;
}
inline const std::wstring& retirementTitle(){static std::wstring text;if(text.empty())text=service::translate(service::translator(),L"Retire");return text;}
inline const std::wstring& retirementBody(){static std::wstring text;if(text.empty())text=service::translate(service::translator(),L"You cannot retire until you reach level ");return text;}
struct CameraData { Ogre::Vector3 up;Ogre::Matrix4 matrix; };
class Frame {
    struct Node {void* object;Node* next;};
    void* ui; void* client; void* renderWindow; float elapsed; Labels labels;
    template<class T> T& at(void* p,unsigned offset){return field<T>(p,offset);}
    void* actor(){return at<void*>(ui,0x38);}
    void* window(unsigned offset){return at<void*>(ui,offset);}
    CEGUI::String& windowText(unsigned offset){return at<CEGUI::String>(window(offset),0xc0);}
    CEGUI::UVector2& cached(unsigned offset){return at<CEGUI::UVector2>(ui,offset);}
    void virtualTick(void* object,unsigned slot){typedef void(*Fn)(void*,float);reinterpret_cast<Fn>(at<void**>(object,0)[slot/8])(object,elapsed);}
    void tipVisible(void* object,bool show){typedef void(*Fn)(void*,bool);reinterpret_cast<Fn>(at<void**>(object,0)[0x38/8])(object,show);}
    template<class Fn> Fn vcall(void* object,unsigned slot){return reinterpret_cast<Fn>(at<void**>(object,0)[slot/8]);}
    void menuOpen(unsigned offset,bool open){void* object=window(offset);vcall<void(*)(void*,bool)>(object,0x40)(object,open);}
    bool menuOpenPartial(unsigned offset){void* object=window(offset);return vcall<bool(*)(void*)>(object,0x28)(object);}
    void* menuOwner(unsigned offset){void* object=window(offset);return vcall<void*(*)(void*)>(object,0x10)(object);}
    void setMenuOwner(unsigned offset,void* owner){void* object=window(offset);vcall<void(*)(void*,void*)>(object,0x38)(object,owner);}
    void setState(unsigned state){void* who=actor();vcall<void(*)(void*,unsigned)>(who,0x348)(who,state);}
    void menuVisible(unsigned offset,bool visible){void* object=window(offset);vcall<void(*)(void*,bool)>(object,0x18)(object,visible);}
    void clearSafe(void* base,unsigned offset){void* object=at<void*>(base,offset);if(object){service::removeSafe(object,static_cast<char*>(base)+offset,at<unsigned>(base,offset+8));at<void*>(base,offset)=NULL;}}
public:
    Frame(void* self,void* gameClient,void* render,float dt,const Labels& names):ui(self),client(gameClient),renderWindow(render),elapsed(dt),labels(names){}
// Returns true exactly when the cinematic branch completes the frame.
// Caller must have performed first-use localization before this phase.
bool entry(){
    unsigned selected=at<unsigned char>(window(0x200),0x732);
    if(selected!=unsigned(service::settingInt(window(0x78),KSettingsToggleNames())==1)){
        bool next=service::settingInt(window(0x78),KSettingsToggleNames())==1;
        service::select(window(0x200),next);
    }
    void* mouse=static_cast<char*>(ui)+0x12a8;
    bool input=service::buttonPressed(mouse,1)||service::buttonPressed(mouse,0)||
               service::buttonHeld(mouse,1)||service::buttonHeld(mouse,0);
    if(!input){
        void* floating=at<void*>(window(0x430),0x238);
        if(service::isVisible(floating,false)){
            float available=service::widthRead(ui);service::heightRead(ui);
            float wide=service::windowWidth(floating).asAbsolute(1);
            float high=service::windowHeight(floating).asAbsolute(1);
            float x=float(at<long>(ui,0x12d0)),y=float(at<long>(ui,0x12d8));
            if(x+wide+26.0f>available)x=available-(wide+26.0f);
            float boundary=high+26.0f;if(y-boundary<0)y=boundary;
            service::position(floating,CEGUI::UVector2(CEGUI::UDim(0,x),CEGUI::UDim(0,y)));
        }
    }
    void* cinema=window(0x540);
    if(at<unsigned char>(cinema,0x30)||!at<unsigned char>(cinema,0x31)){
        virtualTick(cinema,0x18);return true;
    }
    return false;
}
// Opening and closing states are original-compared; quest/fishing branches
// remain assembly-transcribed pending dedicated end-to-end cases.
// Retirement strings must follow the original lazy-localization lifecycle.
void serviceMenus(const std::wstring& retire,const std::wstring& cannotRetire){serviceMenusImpl(&retire,&cannotRetire);}
void serviceMenus(){serviceMenusImpl(NULL,NULL);}
void serviceMenusImpl(const std::wstring* suppliedTitle,const std::wstring* suppliedBody){
    unsigned state=at<unsigned>(actor(),0x330);
    bool opening=state==0x13||state==0x11||state==0x15||state==0x16||state==0x1a||state==0x1b||state==0x19||state==0x24||state==0x25;
    if(opening){
        unsigned targetOffset=state==0x16?0x350:0x340;
        if(at<void*>(actor(),targetOffset)){
            service::closeAll(ui);
            bool denied=false;
            if(state==0x1b){int limit=at<int>(service::global(),0x48);if(limit>=0&&at<unsigned>(actor(),0x100)<unsigned(limit)){
                const std::wstring& retire=suppliedTitle?*suppliedTitle:retirementTitle();
                const std::wstring& cannotRetire=suppliedBody?*suppliedBody:retirementBody();
                std::wstring formatted=service::formatLimit(limit);
                service::modalDialog(ui,retire,cannotRetire+formatted,false);setState(2);denied=true;
            }}
            if(!denied){
                if(state!=0x16&&state!=0x24&&state!=0x25){void* bank=at<void*>(at<void*>(actor(),0x340),0x298);if(bank)service::sound(bank,0x26,0.0f,0.1f);}
                menuOpen(0x4d8,true);
                unsigned menu=state==0x13?0x4f0:state==0x11?0x500:(state==0x24||state==0x25)?0x508:0x4f8;
                if(state==0x16)service::enchantOwner(window(menu),at<void*>(actor(),targetOffset));
                else setMenuOwner(menu,at<void*>(actor(),targetOffset));
                if(menu==0x4f0)service::merchantPlayer(window(menu),actor());
                else if(menu==0x500)service::combinePlayer(window(menu),actor());
                else if(menu==0x508)service::stashPlayer(window(menu),actor());
                else service::enchantPlayer(window(menu),actor());
                if(menu==0x4f8)service::enchantOpen(window(menu),true,state);else menuOpen(menu,true);
                setState(state==0x13?0x14:state==0x11?0x12:state==0x24?0x26:state==0x25?0x27:0x1c);
            }
        }
    }else if(state==0x14||state==0x1c||state==0x12||state==0x26||state==0x27){
        unsigned menu=state==0x14?0x4f0:state==0x1c?0x4f8:state==0x12?0x500:0x508;
        if(!menuOpenPartial(0x4d8)||!menuOpenPartial(menu)){
            if(menu!=0x508&&menuOwner(menu)&&at<void*>(menuOwner(menu),0x298))service::sound(at<void*>(menuOwner(menu),0x298),0x27,0.0f,0.1f);
            setState(2);menuOpen(menu,false);
            if(state==0x14&&window(0xb8)&&window(0xc8)&&service::isA(window(0xc8),0x29))service::returnDragged(ui);
        }
    }
}
void questAndFishing(){
    if(at<unsigned>(actor(),0x330)==0x1e){
        void* current=actor();void* quest=service::questForNPC(at<void*>(current,0x868),at<void*>(current,0x340));
        if(!quest)setState(2);
        else{service::closeAll(ui);service::questNPC(window(0x538),at<void*>(actor(),0x340),false,NULL);setState(0x1f);}
    }else if(at<unsigned>(actor(),0x330)==0x1f&&!at<unsigned char>(window(0x538),0x30)){
        service::setTarget(actor(),NULL);setState(2);
        void* menu=window(0x538);vcall<void(*)(void*,bool)>(menu,0x38)(menu,false);
    }
    if(at<unsigned>(actor(),0x330)==0x21){
        clearSafe(client,0x1f8);clearSafe(client,0x1e8);clearSafe(client,0x1c8);clearSafe(client,0x1d8);
        service::mouseOverItem(ui,NULL,true);clearSafe(ui,0x58);
        if(!at<unsigned char>(window(0x578),0x30)){service::closeAll(ui);menuVisible(0x578,true);}
        else if(service::eitherCovered(ui)||service::modalFull(ui)){setState(2);service::setTargetItem(actor(),NULL);menuVisible(0x578,false);}
    }else menuVisible(0x578,false);
    service::slots(ui);
}
std::string timerText(float remaining) {
    unsigned minutes=0,hours=0;
    while(remaining>=60.0f){remaining-=60.0f;++minutes;}
    while(minutes>59){minutes-=60;++hours;}
    return service::originalUnsigned(hours)+":"+(minutes<10?"0":"")+service::originalUnsigned(minutes)+":"+
        (remaining<10.0f?"0":"")+service::originalNumber(int(remaining));
}
void bar(unsigned pos,unsigned dim,unsigned window,unsigned sub,float ratio) {
    if(ratio<0.0f) ratio=0.0f;
    service::position(this->window(window),CEGUI::UVector2(
        CEGUI::UDim(0,cached(pos).d_x.asAbsolute(1)),
        CEGUI::UDim(0,(cached(pos).d_y.asAbsolute(1)+cached(dim).d_y.asAbsolute(1))-
                         cached(dim).d_y.asAbsolute(1)*ratio)));
    service::size(this->window(window),CEGUI::UVector2(
        CEGUI::UDim(0,cached(dim).d_x.asAbsolute(1)),
        CEGUI::UDim(0,cached(dim).d_y.asAbsolute(1)*ratio)));
    service::position(this->window(sub),CEGUI::UVector2(CEGUI::UDim(0,0),
        CEGUI::UDim(0,-(cached(dim).d_y.asAbsolute(1)-cached(dim).d_y.asAbsolute(1)*ratio))));
}
void petHUD() {
    unsigned long begin=at<unsigned long>(actor(),0x648),end=at<unsigned long>(actor(),0x650);
    if(unsigned((end-begin)>>3)!=0&&!service::covered(ui)) {
        begin=at<unsigned long>(actor(),0x648);end=at<unsigned long>(actor(),0x650);
        void* pet=(end-begin)>>3?*reinterpret_cast<void**>(begin):NULL;
        service::visible(this->window(0x170),true);
        int mode=at<int>(pet,0x710);
        if(mode!=at<int>(ui,0x16c8)) {
            at<int>(ui,0x16c8)=mode;
            if(mode==0)service::select(this->window(0x1c8),true);
            else if(mode==1)service::select(this->window(0x1b8),true);
            else if(mode==2)service::select(this->window(0x1c0),true);
        }
        float ratio=float(service::hp(pet));ratio/=float(service::maxhp(pet));if(ratio<0)ratio=0;
        service::size(this->window(0x180),CEGUI::UVector2(
            CEGUI::UDim(0,float(int(cached(0x174c).d_x.asAbsolute(1)*ratio))),
            CEGUI::UDim(0,cached(0x174c).d_y.asAbsolute(1))));
        ratio=service::mana(pet);ratio/=float(service::maxmana(pet));if(ratio<0)ratio=0;
        service::size(this->window(0x190),CEGUI::UVector2(
            CEGUI::UDim(0,float(int(cached(0x175c).d_x.asAbsolute(1)*ratio))),
            CEGUI::UDim(0,cached(0x175c).d_y.asAbsolute(1))));
        {
            std::string top=service::originalNumber(service::maxhp(pet)),now=service::originalNumber(service::hp(pet));
            std::string value=std::string(labels.hp)+":"+now+"/"+top;
            CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));
            service::tooltip(this->window(0x178),converted);
        }
        {
            std::string top=service::originalNumber(service::maxmana(pet)),now=service::originalNumber(int(service::mana(pet)));
            std::string value=std::string(labels.mana)+":"+now+"/"+top;
            CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));
            service::tooltip(this->window(0x198),converted);
        }
        std::string narrow=service::originalNarrow(at<const wchar_t*>(pet,0x4c0));
        CEGUI::String name(reinterpret_cast<const CEGUI::utf8*>(narrow.c_str()));
        if(windowText(0x1b0)!=name) {
            CEGUI::String fresh(name.c_str());service::text(window(0x1b0),fresh);
        }
        if(at<int>(pet,0x330)==0x2a) {
            std::string value=timerText(at<float>(pet,0x684));
            if(windowText(0x1a8)!=value) {
                CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));
                service::text(window(0x1a8),converted);
            }
            service::visible(window(0x1a8),true);
        } else if(service::nearDeath(pet)) {
            std::string value=std::string(labels.fleeing)+"!";
            if(windowText(0x1a8)!=value) {
                CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));
                service::text(window(0x1a8),converted);
            }
            service::visible(window(0x1a8),true);
        } else service::visible(window(0x1a8),false);
    } else service::visible(this->window(0x170),false);
}
void message(unsigned pointer,unsigned stringOffset,unsigned durationOffset,unsigned alphaOffset){
    if(at<float>(ui,alphaOffset)>0){
        std::string value=service::originalUTF8(at<std::wstring>(ui,stringOffset));
        CEGUI::String& current=windowText(pointer);
        if(current!=value){CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));service::text(at<void*>(ui,pointer),converted);}
        float duration=at<float>(ui,durationOffset)-elapsed;
        float oldAlpha=at<float>(ui,alphaOffset);
        at<float>(ui,durationOffset)=duration;
        if(duration<=0){at<float>(ui,durationOffset)=0;at<float>(ui,alphaOffset)=oldAlpha+elapsed*(-2.0f);}
        float alpha=at<float>(ui,alphaOffset);
        if(alpha!=oldAlpha){
            float rendered=alpha>0?alpha:0;
            service::property(at<void*>(ui,pointer),CEGUI::String("TextColour"),CEGUI::PropertyHelper::colourToString(CEGUI::colour(1,1,1,rendered)));
            service::property(at<void*>(ui,pointer),CEGUI::String("DropTextColour"),CEGUI::PropertyHelper::colourToString(CEGUI::colour(0,0,0,rendered)));
        }
        service::visible(at<void*>(ui,pointer),true);
    }else service::visible(at<void*>(ui,pointer),false);
}
void levelAndMessages(){
    void* level=at<void*>(client,0x70);
    if(level){
        std::wstring wide=service::levelValue(level);std::string value=service::originalUTF8(wide);
        CEGUI::String& current=windowText(0x100);
        if(current!=value){CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));service::text(at<void*>(ui,0x100),converted);}
        service::visible(at<void*>(ui,0x100),true);
        if(service::modal(ui)){service::visible(at<void*>(ui,0x110),false);service::visible(at<void*>(ui,0x118),false);}
        else{message(0x110,0x1978,0x1980,0x1984);message(0x118,0x1988,0x1990,0x1994);}
    }
}
void tickMenus(){
    for(unsigned family=0;family<2;++family){unsigned base=family?0x1948:0x1930;
        for(unsigned i=0;i<unsigned(at<void**>(ui,base+8)-at<void**>(ui,base));++i)virtualTick(at<void**>(ui,base)[i],family?0x18:0x50);
    }
    virtualTick(at<void*>(ui,0x578),0x10);virtualTick(at<void*>(ui,0x570),0x10);
    bool interactive=at<unsigned char>(at<void*>(ui,0x570),0x38)!=0;
    service::visible(this->window(0x138),!interactive);service::visible(this->window(0x140),!interactive);
    if(interactive)service::visible(this->window(0x170),false);
}
void queuedTips(){
    if(service::modal(ui)||!actor()||at<int*>(ui,0x1968)==at<int*>(ui,0x1960))return;
    int key=*at<int*>(ui,0x1960);void* globals=service::global();std::wstring value=service::getTip(globals,key);
    if(!value.empty()&&!at<unsigned char>(actor(),0xa17+*at<int*>(ui,0x1960))){
        service::contents(at<void*>(ui,0x550),value);tipVisible(at<void*>(ui,0x550),true);
    }
    at<unsigned char>(actor(),0xa17+*at<int*>(ui,0x1960))=1;
    unsigned count=at<int*>(ui,0x1968)-at<int*>(ui,0x1960);
    for(unsigned i=0;i+1<count;++i)at<int*>(ui,0x1960)[i]=at<int*>(ui,0x1960)[i+1];
    --at<int*>(ui,0x1968);
}
void playerHUD() {
    service::visible(this->window(0x140),true);
    float current=float(service::hp(actor()));int maximum=service::maxhp(actor());
    bar(0x16cc,0x171c,0x140,0x150,current/float(maximum));
    {
        std::string top=service::originalNumber(service::maxhp(actor()));
        std::string now=service::originalNumber(service::hp(actor()));
        std::string text=std::string(labels.hp)+":"+now+"/"+top;
        CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(text.c_str()));
        service::tooltip(this->window(0x148),converted);
    }
    service::visible(this->window(0x158),true);
    current=service::mana(actor());maximum=service::maxmana(actor());
    bar(0x16dc,0x172c,0x158,0x168,current/float(maximum));
    {
        std::string top=service::originalNumber(service::maxmana(actor()));
        std::string now=service::originalNumber(int(service::mana(actor())));
        std::string text=std::string(labels.mana)+":"+now+"/"+top;
        CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(text.c_str()));
        service::tooltip(this->window(0x160),converted);
    }
    int level=at<int>(actor(),0x100);
    float experience=float(at<int>(actor(),0x448));
    void* resource=service::manager();int previous=service::gate(resource,level-1);
    level=at<int>(actor(),0x100);resource=service::manager();int currentGate=service::gate(resource,level);
    level=at<int>(actor(),0x100);resource=service::manager();int previousAgain=service::gate(resource,level-1);
    float ratio=(experience-float(previous))/float(currentGate-previousAgain);
    if(ratio<0.0f)ratio=0.0f;else if(ratio>1.0f)ratio=1.0f;
    service::size(this->window(0x1d0),CEGUI::UVector2(
        CEGUI::UDim(0,float(int(cached(0x173c).d_x.asAbsolute(1)*ratio))),
        CEGUI::UDim(0,cached(0x173c).d_y.asAbsolute(1))));
    {
        level=at<int>(actor(),0x100);resource=service::manager();
        std::string top=service::originalNumber(service::gate(resource,level));
        std::string now=service::originalNumber(at<int>(actor(),0x448));
        std::string text=std::string(labels.xp)+":"+now+"/"+top;
        CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(text.c_str()));
        service::tooltip(this->window(0x1d8),converted);
    }
}
CameraData updateCamera(bool active){
    if(active){
    at<float>(ui,0x1684)=service::widthRead(ui);
    at<float>(ui,0x1688)=service::heightRead(ui);
    float right=service::rightRead(ui);float left=service::leftRead(ui);
    at<float>(ui,0x1680)=(right-left)/at<float>(ui,0x1684);
    service::settingFloat(window(0x78),KSettingsYRatio());
    }
    Ogre::Matrix3 rotation;service::cameraOrientation(window(0x10)).ToRotationMatrix(rotation);
    Ogre::Matrix4 view=Ogre::Matrix4::IDENTITY;view=rotation;
    view.setTrans(service::cameraPosition(window(0x10)));view=view.inverse();
    void* camera=window(0x10);typedef const Ogre::Matrix4&(*Projection)(void*);
    CameraData result;result.matrix=reinterpret_cast<Projection>(at<void**>(camera,0)[0x2d8/8])(camera)*view;
    result.up=service::cameraOrientation(window(0x10)).yAxis();if(active)service::editor();
    service::events(ui,elapsed,result.up,result.matrix,active);return result;
}
void noCharacterFrame(){
    if(window(0x138)&&window(0x120)){service::visible(window(0x138),false);service::visible(window(0x120),false);service::visible(window(0x170),false);}
    updateCamera(false);performanceOverlay();queuedTips();finishFrame();
}
// World-label phase: visibility and existing-window positioning compared.
// First-time creation/styling is also compared for the documented finite cases.
void* createWorldLabel(){
    CEGUI::String prefix("");std::string name=service::uniqueName(std::string("gui_"));
    return service::createWindow(service::windowManager,CEGUI::String(reinterpret_cast<const CEGUI::utf8*>("GuiLook/ItemText")),CEGUI::String(name),prefix);
}
void configureWorldLabel(void* label,void* font,const std::string& name){
    float extent=service::textExtent(font,CEGUI::String(name),1.0f)+4.0f;
    float extraWidth=service::scaledY(ui,36.0f)-36.0f;
    float extraHeight=service::scaledY(ui,36.0f)-36.0f;
    float height=(at<float>(font,0x278)-at<float>(font,0x27c))+2.0f+extraHeight;
    service::size(label,CEGUI::UVector2(CEGUI::UDim(0,extraWidth+extent),CEGUI::UDim(0,height)));
    service::text(label,CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(name.c_str())));
    service::property(label,CEGUI::String("VertFormatting"),CEGUI::String("CentreAligned"));
    service::property(label,CEGUI::String("HorzTextFormatting"),CEGUI::String("CentreAligned"));
}
void colorFromGlobals(void* label,unsigned offset){
    std::string color=service::originalUTF8(at<std::wstring>(service::global(),offset));
    service::property(label,CEGUI::String("TextColour"),CEGUI::String(color));
}
void createItemLabel(void* item,void* equipment){
    void* label=createWorldLabel();void* font=service::font(label,true);
    const std::wstring& wide=vcall<const std::wstring&(*)(void*)>(item,0x2a0)(item);
    std::string name=service::originalUTF8(wide);
    int begin=int(name.find("{",0));int end=int(name.find("}",long(begin)));
    if(end!=-1&&begin!=-1&&begin+1<end)name.replace(long(begin),long(end-begin+1),"");
    configureWorldLabel(label,font,name);
    if(service::questUnit(item))colorFromGlobals(label,0x2b0);
    else if(equipment&&!service::equipmentSet(equipment).empty())colorFromGlobals(label,0x2a8);
    else if(service::isA(item,0x36))colorFromGlobals(label,0x2a0);
    else if(vcall<bool(*)(void*)>(item,0x2b0)(item)||service::isA(item,0xa0)){
        if(service::isA(item,0x37))colorFromGlobals(label,0x298);else colorFromGlobals(label,0x290);
    }else service::property(label,CEGUI::String("TextColour"),CEGUI::PropertyHelper::colourToString(CEGUI::colour(0.8f,0.8f,0.8f,1.0f)));
    CEGUI::UVector2 dimensions=service::windowSize(label);
    void* parent=window(0x488);at<void*>(item,0x1e8)=label;at<void*>(item,0x1f8)=parent;
    at<CEGUI::UVector2>(item,0x21c)=dimensions;
}
void createCharacterLabel(void* character){
    void* label=createWorldLabel();void* font=service::font(label,true);
    std::wstring wide=service::mimicName(character);std::string name=service::originalUTF8(wide);
    configureWorldLabel(label,font,name);
    service::property(label,CEGUI::String("TextColour"),CEGUI::PropertyHelper::colourToString(CEGUI::colour(1,1,1,1)));
    CEGUI::UVector2 dimensions=service::windowSize(label);
    at<void*>(character,0x480)=window(0x488);at<void*>(character,0x478)=label;
    at<CEGUI::UVector2>(character,0x468)=dimensions;
}
void positionWorldLabel(void* object,bool character,const Ogre::Vector3& projected){
    float height=at<float>(object,character?0x474:0x228);
    float width=at<float>(object,character?0x46c:0x220);
    if(character)service::showCharacter(object);else service::showItem(object);
    float x=width*(-0.5f)+projected.x,y=height*(-0.5f)+projected.y;
    if(at<float>(ui,0x1684)<width+x+26.0f)x=at<float>(ui,0x1684)-(width+26.0f);
    if(at<float>(ui,0x1688)<height+y+26.0f)y=at<float>(ui,0x1688)-(height+26.0f);
    if(!(x>=0))x=0;if(!(y>=0))y=0;
    service::position(at<void*>(object,character?0x478:0x1e8),CEGUI::UVector2(CEGUI::UDim(0,x),CEGUI::UDim(0,y)));
}
void worldLabels(const CameraData& camera){
    void* level=at<void*>(client,0x70);Node* node=*at<Node**>(level,0xc0);
    while(node){
        void* item=node->object;bool show=false;
        if(item&&!service::modal(ui)&&!at<unsigned char>(ui,0x1999)&&!service::bothCovered(ui)){
            if(item==window(0x68)&&!service::isA(item,0x1e))show=true;
            else{unsigned key=service::settingInt(window(0x78),service::keyShowItems);bool held=service::keyHeld(static_cast<char*>(ui)+0x590,key);int toggle=service::settingInt(window(0x78),KSettingsToggleNames());show=(toggle==1)!=held;}
        }
        if(!show)service::hideItem(item);
        else{
            void* equipment=service::castEquipment(item,&service::itemType,&service::equipmentType,0);
            Ogre::Vector3 position=service::objectPosition(item,true);Ogre::Vector3 up=camera.up;
            Ogre::Vector3 projected=service::screenPosition(ui,&position,&up,camera.matrix);
            if(!at<void*>(item,0x1e8))createItemLabel(item,equipment);
            positionWorldLabel(item,false,projected);
        }
        node=node->next;
    }
    level=at<void*>(client,0x70);node=*at<Node**>(level,0xc8);
    while(node){
        void* character=node->object;bool show=false;
        if(character&&!service::modal(ui)&&!at<unsigned char>(ui,0x1999)&&!service::bothCovered(ui)){
            if(character==window(0x58))show=true;
            else{unsigned key=service::settingInt(window(0x78),service::keyShowItems);show=service::keyHeld(static_cast<char*>(ui)+0x590,key);if(!show)show=service::settingInt(window(0x78),KSettingsToggleNames())==1;}
        }
        if(!show)service::hideCharacter(character);
        else{
            Ogre::Vector3 position=service::objectPosition(character,true);Ogre::Vector3 up=camera.up;
            Ogre::Vector3 projected=service::screenPosition(ui,&position,&up,camera.matrix);
            if(!at<void*>(character,0x478))createCharacterLabel(character);
            positionWorldLabel(character,true,projected);
        }
        node=node->next;
    }
}
// Hover text/health is assembly-transcribed. Dedicated visible-target tests pending.
void hoverHUD(){
    void* target=NULL;void* mouse=static_cast<char*>(ui)+0x12a8;
    if(actor()&&(service::buttonHeld(mouse,1)||service::buttonHeld(mouse,0)))target=at<void*>(actor(),0x340);
    else target=window(0x58);
    if(!target)target=window(0x58);
    bool show=!service::modal(ui)&&!at<unsigned char>(ui,0x1999)&&!service::bothCovered(ui)&&target;
    if(show&&service::isA(target,0xa7)&&service::hasTheme(target,std::wstring(L"MIMICIDLE")))show=false;
    if(show){
        service::visible(window(0x120),true);
        if(!service::isVisible(window(0xf8),false)||target!=window(0x48)){
            std::string title=translatedUTF8(L"Level");
            if(target!=window(0x48)){
                clearSafe(ui,0x48);if(target)at<unsigned>(ui,0x50)=service::addSafe(target,static_cast<char*>(ui)+0x48);
                at<void*>(ui,0x48)=target;
            }
            std::string level=service::originalUnsigned(at<unsigned>(target,0x100));title=title+" "+level;
            service::text(window(0xf8),CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(title.c_str())));
            std::string name=service::originalUTF8(at<std::wstring>(target,0x4c0));
            service::text(window(0xe8),CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(name.c_str())));
            CEGUI::colour color=at<unsigned char>(target,0x702)?CEGUI::colour(1,0.88f,0.24f,1):CEGUI::colour(1,1,1,1);
            service::property(window(0xe8),CEGUI::String("TextColour"),CEGUI::PropertyHelper::colourToString(color));
            std::wstring wide=service::description(target);std::string detail=service::originalUTF8(wide);
            service::text(window(0xf0),CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(detail.c_str())));
        }
        service::visible(window(0xe8),true);service::visible(window(0xf0),true);service::visible(window(0xf8),true);
        int health=service::hp(target);int maximum=service::maxhp(target);float ratio=float(health)/float(maximum);if(ratio<0)ratio=0;
        service::size(window(0x128),CEGUI::UVector2(CEGUI::UDim(0,float(int(at<CEGUI::UDim>(ui,0x176c).asAbsolute(1)*ratio))),CEGUI::UDim(0,at<CEGUI::UDim>(ui,0x1724).asAbsolute(1))));
    }else{service::visible(window(0x120),false);service::visible(window(0xe8),false);service::visible(window(0xf0),false);service::visible(window(0xf8),false);}
}
void updateHUD(){
    if(!(at<unsigned char>(service::editor(),0x64)&2)){
        const unsigned hidden[]={0x1e8,0x1e0,0x138,0x120,0x170,0x100,0x110,0x118};
        for(unsigned i=0;i<8;++i)service::visible(window(hidden[i]),false);
        return;
    }
    hoverHUD();
    bool map=window(0x40)&&service::automapVisible(window(0x40));
    service::visible(window(0x1f0),map);service::visible(window(0x1f8),map);
    if(actor()){
        bool stat=at<int>(actor(),0x45c)>0;
        if(stat){void* menu=window(0x4e0);stat=!vcall<bool(*)(void*)>(menu,0x20)(menu);}
        service::visible(window(0x1e0),stat);
        bool skill=at<int>(actor(),0x460)>0;
        if(skill){void* menu=window(0x558);skill=!vcall<bool(*)(void*)>(menu,0x20)(menu);}
        service::visible(window(0x1e8),skill);
        bool companion=menuOpenPartial(0x4d8)&&(menuOpenPartial(0x4e8)||menuOpenPartial(0x508)||menuOpenPartial(0x4f0)||menuOpenPartial(0x4f8)||menuOpenPartial(0x500));
        service::visible(window(0x108),companion);playerHUD();
    }
    // Original falls through to pet access even if callbacks invalidated actor.
    petHUD();levelAndMessages();tickMenus();
}
// Debug overlay transcription: retains original counter resets and the
// ignored material-memory/channel queries. Documented two-frame cases compared.
void performanceOverlay(){
    if(!window(0xe0))return;
    if(!at<unsigned char>(ui,0x12f8)){
        unsigned key=service::key_DISPLAY_STATS;
        if(service::settingInt(at<void*>(service::manager(),0x90),key)==0)return;
    }
    if(service::settingInt(window(0x78),service::key_UPDATE_PERF)<=0)return;
    service::settingSetInt(window(0x78),service::key_UPDATE_PERF,0);
    void* statistics=at<void*>(service::manager(),0xf0);
    int missiles=at<int>(service::missilePreloader(window(0x1308)),0x88);
    service::settingInt(window(0x78),service::key_NUM_TICKS_PER_SECOND);
    unsigned fpsKey=service::key_CURRENT_FPS;
    int fps=service::settingInt(at<void*>(service::manager(),0x90),fpsKey);
    float frames=fps<2?1.0f:float(fps);float interval=fps<2?0.4f:frames*0.4f;if(interval<=0)interval=0;
    unsigned divisor=unsigned(int(ceilf((frames/interval)*frames)));
    unsigned rates[4];for(unsigned i=0;i<4;++i){unsigned offset=0x4ec+i*4;unsigned total=at<unsigned>(statistics,offset);at<unsigned>(statistics,offset)=0;rates[i]=total/divisor;}
    int updating=at<int>(statistics,0x50c)-int((at<long>(statistics,0x518)-at<long>(statistics,0x510))>>3);
    int systems=at<int>(statistics,0x508),techniques=at<int>(statistics,0x4fc),emitters=at<int>(statistics,0x500),affectors=at<int>(statistics,0x504);
    void* materials=service::materialManager();vcall<unsigned long(*)(void*)>(materials,0x48)(materials);
    int cache=service::particleCacheCount(at<void*>(service::manager(),0xf8));
    void* meshes=service::meshManager();int meshBytes=int(vcall<unsigned long(*)(void*)>(meshes,0x48)(meshes));
    void* textures=service::textureManager();int textureBytes=int(vcall<unsigned long(*)(void*)>(textures,0x48)(textures));
    void* renderStats=vcall<void*(*)(void*)>(renderWindow,0x78)(renderWindow);
    service::channelsPlaying(at<void*>(service::manager(),0x98));
    Ogre::ResourceManager* meshList=static_cast<Ogre::ResourceManager*>(service::meshManager());
    Ogre::ResourceManager::ResourceMapIterator iterator=meshList->getResourceIterator();int meshCount=0;
    while(iterator.hasMoreElements()){++meshCount;Ogre::ResourcePtr resource=iterator.getNext();}
    int seed=0,depth=0,units=0;void* level=window(0x40);
    if(level){seed=at<int>(level,0x228);depth=at<int>(level,0x1a4);units=at<int>(level,0x22c);}
    std::string room;
    if(window(0x40)&&actor()){
        Ogre::Vector3 position=service::objectPosition(actor(),true);
        void* current=service::roomAt(window(0x40),position);
        if(current){std::wstring name=at<std::wstring>(current,0x168);std::string narrow=service::originalNarrow(name.c_str());room=service::fileName(narrow);}
    }
    // Original evaluates tail operands first. Keep formatter calls in that order.
    std::string affectRate=service::originalNumber(int(rates[3]));
    std::string affectCount=service::originalNumber(affectors);
    std::string emitterCount=service::originalNumber(emitters);
    std::string techniqueRate=service::originalNumber(int(rates[1]));
    std::string techniqueCount=service::originalNumber(techniques);
    std::string systemRate=service::originalNumber(int(rates[0]));
    std::string systemCount=service::originalNumber(systems);
    std::string particleRate=service::originalNumber(int(rates[2]));
    std::string particleCount=service::originalNumber(updating);
    std::string cachedCount=service::originalNumber(cache);
    std::string textureMemory=service::originalNumber(textureBytes);
    std::string materialCount=service::originalNumber(0); // original displays a literal zero
    std::string meshNumber=service::originalNumber(meshCount);
    std::string meshMemory=service::originalNumber(meshBytes);
    std::string batch=service::originalNumber(int(at<unsigned long>(renderStats,0x28)));
    std::string triangle=service::originalNumber(int(at<unsigned long>(renderStats,0x20)));
    std::string missileCount=service::originalNumber(missiles);
    std::string unitCount=service::originalNumber(units);
    std::string levelDepth=service::originalNumber(depth);
    std::string levelSeed=service::originalNumber(seed);
    Ogre::UTFString version(service::settingString(window(0x78),service::key_S_VERSION));
    float average=service::settingFloat(window(0x78),service::key_F_AVERAGE_FPS);
    std::string averageText=service::originalFloat(average);
    std::string renderText=service::originalFloat(at<float>(renderStats,0));
    Ogre::UTFString result(std::string("FPS Render / Average : ")+renderText+" / "+averageText+"\nVERSION : ");
    result.append(version);
    result.append(Ogre::UTFString(std::string("\nRoom: ")+room+"\nLevel Seed : "+levelSeed+"\nLevel Depth : "+levelDepth+
        "\nActive Units / Missiles : "+unitCount+" / "+missileCount+"\ntriangle : "+triangle+"\nbatch : "+batch+
        "\nMesh Bytes : "+meshMemory+"\nMeshes : "+meshNumber+"\nMaterials : "+materialCount+"\nTexture Bytes : "+textureMemory+
        "\nParticle Cache Count : "+cachedCount+"\nParticles Updating / Rendering : "+particleCount+" / "+particleRate+
        "\nParticle Systems Created / Updating : "+systemCount+" / "+systemRate+
        "\nParticle Techniques Created / Updating : "+techniqueCount+" / "+techniqueRate+
        "\nParticle Emitters Created : "+emitterCount+"\nParticle Affectors Created / Updating : "+affectCount+" / "+affectRate));
    std::string finalText=result.asUTF8();
    service::text(window(0xe0),CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(finalText.c_str())));
    service::front(window(0xe0));
}
// Complete top-level draft. No original-function fallback, no production hook.
// Some newly transcribed branches still need their dedicated comparisons.
void run(){
    if(entry())return;
    if(!actor()){noCharacterFrame();return;}
    serviceMenus();questAndFishing();updateHUD();
    CameraData camera=updateCamera(true);worldLabels(camera);
    performanceOverlay();queuedTips();finishFrame();
}
void finishFrame(){
    void* console=window(0x1690);
    if(console&&service::consoleIsVisible(console))service::consoleTick(window(0x1690),elapsed);
    service::finalTick(window(0x588),elapsed,client,renderWindow);
}
private:
    static unsigned KSettingsYRatio();
    static unsigned KSettingsToggleNames();
};
extern unsigned settingsToggleNames __asm__("KSETTINGS_TOGGLE_ITEM_NAME");
inline unsigned Frame::KSettingsToggleNames(){return settingsToggleNames;}
extern unsigned settingsYRatio __asm__("KSETTINGS_YRATIO");
inline unsigned Frame::KSettingsYRatio(){return settingsYRatio;}
inline void updateIngameUIDraft(void* self,float elapsed,void* client,void* renderWindow){
    Labels labels=localizedLabels();Frame frame(self,client,renderWindow,elapsed,labels);frame.run();
}
} // namespace gameui_recovered
#endif
