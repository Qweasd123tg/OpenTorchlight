// Headless full-entry comparison: platform/resource/UI collaborators are
// controlled; snapshots include event order and constructed interface state.
#include <string>
#include <map>
#include <vector>
#include <cstring>
#include <cstdio>
#include <new>
#define private public
#define protected public
#include <CEGUI.h>
#include <CEGUIExceptions.h>
#undef GenericException
#include <CEGUIMemberFunctionSlot.h>
#include <OgreUTFString.h>
#include <OgreLogManager.h>
#include "GameUI.h"
#include "FileSystem.h"
#include "Settings.h"
#include "MasterResourceManager.h"
#include "SoundBank.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "SDL.h"
#include "EquipmentTooltip.h"
#include "SkillTooltip.h"
#include "SkillFoldout.h"
#include "TextEvent.h"
#include "TLinkedList.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool,originalStartup,(CGameUI*),"_ZN7CGameUI6createEv")
extern "C" bool candidateStartup(CGameUI*) __asm__("_ZN7CGameUI6createEv");
TL_FUNCTION(startupDependency00,"_ZN10FILESYSTEM18GetApplicationPathEv")
TL_FUNCTION(startupDependency01,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
extern "C" char startupDependency02[] __asm__("SDL_RWFromFile");
extern "C" char startupDependency03[] __asm__("SDL_LoadBMP_RW");
extern "C" char startupDependency04[] __asm__("SDL_CreateColorCursor");
extern "C" char startupDependency05[] __asm__("SDL_FreeSurface");
TL_FUNCTION(startupDependency06,"_ZN7CGameUI14getAspectRatioEv")
TL_FUNCTION(startupDependency07,"_ZN7CGameUI15getWindowHeightEv")
TL_FUNCTION(startupDependency08,"_ZN7STRINGS16GetValueAsStringEf")
TL_FUNCTION(startupDependency09,"_ZN7CGameUI14getWindowWidthEv")
extern "C" char startupDependency10[] __asm__("_ZN4Ogre10LogManager12getSingletonEv");
extern "C" char startupDependency11[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
TL_FUNCTION(startupDependency12,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(startupDependency13,"_ZN10CSoundBankC2ER13CSoundManagerb")
TL_FUNCTION(startupDependency14,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(startupDependency15,"_ZN10CSoundBank9addSampleEix")
extern "C" char startupDependency16[] __asm__("_ZN5CEGUI17OgreCEGUIRendererC1EPN4Ogre12RenderWindowEhbjPNS1_12SceneManagerE");
TL_FUNCTION(startupDependency17,"_ZN10FILESYSTEM14GetAppDataPathEv")
TL_FUNCTION(startupDependency18,"_ZN7STRINGS21StringConvertToNarrowEPKw")
extern "C" char startupDependency19[] __asm__("_ZN5CEGUI6SystemC1EPNS_8RendererEPNS_16ResourceProviderEPNS_9XMLParserEPNS_12ScriptModuleERKNS_6StringESB_");
TL_FUNCTION(startupDependency20,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(startupDependency21,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
extern "C" char startupDependency22[] __asm__("_ZN5CEGUI13SchemeManager10loadSchemeERKNS_6StringES3_");
extern "C" char startupDependency23[] __asm__("_ZNK5CEGUI13SchemeManager9getSchemeERKNS_6StringE");
extern "C" char startupDependency24[] __asm__("_ZN5CEGUI6System14setDefaultFontERKNS_6StringE");
extern "C" char startupDependency25[] __asm__("_ZNK5CEGUI11FontManager7getFontERKNS_6StringE");
extern "C" char startupDependency26[] __asm__("_ZN5CEGUI6System17setDefaultTooltipERKNS_6StringE");
extern "C" char startupDependency27[] __asm__("_ZN5CEGUI6Window14setAlwaysOnTopEb");
extern "C" char startupDependency28[] __asm__("_ZN5CEGUI7Tooltip12setHoverTimeEf");
extern "C" char startupDependency29[] __asm__("_ZN5CEGUI7Tooltip14setDisplayTimeEf");
extern "C" char startupDependency30[] __asm__("_ZN5CEGUI6Window8activateEv");
extern "C" char startupDependency31[] __asm__("_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_");
extern "C" char startupDependency32[] __asm__("_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
extern "C" char startupDependency33[] __asm__("_ZN5CEGUI6System11setGUISheetEPNS_6WindowE");
extern "C" char startupDependency34[] __asm__("_ZN5CEGUI13WindowManager16loadWindowLayoutERKNS_6StringEb");
TL_FUNCTION(startupDependency35,"_ZN7CGameUI20convertToScreenScaleEPN5CEGUI6WindowEb")
extern "C" char startupDependency36[] __asm__("_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE");
extern "C" char startupDependency37[] __asm__("_ZN5CEGUI9BoundSlotD1Ev");
extern "C" char startupDependency38[] __asm__("_ZN5CEGUI14SubscriberSlotD1Ev");
TL_FUNCTION(startupDependency39,"_ZN7STRINGS10uniqueNameERKSs")
extern "C" char startupDependency40[] __asm__("_ZN5CEGUI6Window14addChildWindowEPS0_");
extern "C" char startupDependency41[] __asm__("_ZN5CEGUI6Window10moveToBackEv");
extern "C" char startupDependency42[] __asm__("_ZN5CEGUI6Window19setZOrderingEnabledEb");
extern "C" char startupDependency43[] __asm__("_ZNK5CEGUI15ImagesetManager11getImagesetERKNS_6StringE");
extern "C" char startupDependency44[] __asm__("_ZN5CEGUI8Imageset19setNativeResolutionERKNS_4SizeE");
TL_FUNCTION(startupDependency45,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
extern "C" char startupDependency46[] __asm__("_ZN5CEGUI15ImagesetManager14createImagesetERKNS_6StringES3_");
TL_FUNCTION(startupDependency47,"_ZN7CGameUI14mapToFunctionsEPN5CEGUI6WindowE")
TL_FUNCTION(startupDependency48,"_ZN7CGameUI16mapEventHandlersEPN5CEGUI6WindowE")
extern "C" char startupDependency49[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char startupDependency50[] __asm__("_ZNK5CEGUI6Window12getPixelRectEv");
extern "C" char startupDependency51[] __asm__("_ZN5CEGUI6Window10setTooltipEPNS_7TooltipE");
extern "C" char startupDependency52[] __asm__("_ZNK5CEGUI6Window11getPositionEv");
extern "C" char startupDependency53[] __asm__("_ZNK5CEGUI6Window7getSizeEv");
extern "C" char startupDependency54[] __asm__("_ZN5CEGUI6Window24setWantsMultiClickEventsEb");
extern "C" char startupDependency55[] __asm__("_ZN5CEGUI11RadioButton11setSelectedEb");
extern "C" char startupDependency56[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" char startupDependency57[] __asm__("_ZN5CEGUI8EventSet13setMutedStateEb");
extern "C" char startupDependency58[] __asm__("_ZNK5CEGUI8Imageset8getImageERKNS_6StringE");
extern "C" char startupDependency59[] __asm__("_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE");
extern "C" char startupDependency60[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
TL_FUNCTION(startupDependency61,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(startupDependency62,"_ZN7CGameUI20getImageFromImageSetEPKh")
extern "C" char startupDependency63[] __asm__("_ZN5CEGUI6Window5setIDEj");
extern "C" char startupDependency64[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
TL_FUNCTION(startupDependency65,"_ZN7STRINGS16GetValueAsStringEj")
extern "C" char startupDependency66[] __asm__("_ZNK5CEGUI6Window8getWidthEv");
extern "C" char startupDependency67[] __asm__("_ZNK5CEGUI6Window9getHeightEv");
TL_FUNCTION(startupDependency68,"_ZN14CInventoryMenuC2ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerES8_PN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency69,"_ZN10CSkillMenuC1ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerES8_PN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency70,"_ZN12CJournalMenuC2ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerES8_PN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency71,"_ZN10CQuestMenuC2ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerES8_PN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency72,"_ZN13CMerchantMenuC2ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency73,"_ZN12CEnchantMenuC2ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency74,"_ZN12CCombineMenuC2ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency75,"_ZN10CStashMenuC2ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency76,"_ZN10CStatsMenuC1ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency77,"_ZN8CPetMenuC1ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerES8_PN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency78,"_ZN12COptionsMenuC2ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency79,"_ZN13CSettingsMenuC2ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency80,"_ZN8CDieMenuC2ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency81,"_ZN13CWaypointMenuC2ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency82,"_ZN11CDialogMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency83,"_ZN16CQuestDialogMenuC2ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency84,"_ZN14CCinematicMenuC2ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency85,"_ZN10CModalMenuC2ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency86,"_ZN8CTipMenuC2ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency87,"_ZN16CInteractiveMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency88,"_ZN12CFishingMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency89,"_ZN7CGameUI25setInteractiveMenuVisibleEb")
TL_FUNCTION(startupDependency90,"_ZN10CRunicCoreC2Ev")
TL_FUNCTION(startupDependency91,"_ZN17CEquipmentTooltip4loadEP7CGameUISbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(startupDependency92,"_ZN13CSkillTooltip4loadEP7CGameUISbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(startupDependency93,"_ZN13CSkillFoldout4loadEP7CGameUISbIwSt11char_traitsIwESaIwEE")
extern "C" char startupDependency94[] __asm__("_ZN5CEGUI6System12getSingletonEv");
TL_FUNCTION(startupDependency95,"_ZN8CConsoleC1EP7CGameUIP16CResourceManagerPN5CEGUI6WindowE")
TL_FUNCTION(startupDependency96,"_ZN7CGameUI9toggleFPSEv")
TL_FUNCTION(startupDependency97,"_ZN10CTextEvent10createTextEP7CGameUIPN5CEGUI6WindowE")
TL_FUNCTION(startupDependency98,"_ZN12CMenuManagerC1ER7CGameUIR9CSettingsPN4Ogre6CameraEPNS4_12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_FUNCTION(startupDependency99,"_ZN9CFileInfoD1Ev")
TL_FUNCTION(startupDependency100,"_ZN5CEGUI16GenericExceptionC2ERKS0_")
TL_FUNCTION(startupDependency101,"_ZN5CEGUI16GenericExceptionD1Ev")
TL_FUNCTION(startupDependency102,"_ZN10CRunicCoreD1Ev")

class CResourceManager;
namespace startup_fixture {
struct Case {unsigned scenario,variant;};
static Case current;
static autotest::Capture* cap;
static unsigned long long objects[40][5120];
static unsigned long long windowMemory[256][256],fontMemory[8][256];
static unsigned windowCount,fontCount,uniqueCount,aspectCount,fileCount,soundCount,baseCount,eventCount,connectionCount,cursorCount,surfaceCount;
static void* eventVtable[8];static void* fontVtable[10];
static CGameUI* game;static CEGUI::System* systemObject;
static std::map<std::string,CEGUI::Window*> windowNames;
static std::map<std::string,CEGUI::Font*> fontNames;
static CEGUI::UVector2 sizes[256],positions[256];
static CEGUI::String texts[256],properties[256];
static const void* identities[1024];static unsigned identityCount;
template<class T>T* object(unsigned n){return reinterpret_cast<T*>(objects[n]);}
template<class T>T& field(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
static void n(int x){cap->add(&x,sizeof(x));}static void f(float x){cap->add(&x,sizeof(x));}
static void q(long long x){cap->add(&x,sizeof(x));}
static int remember(const void* p){if(!p)return -1;for(unsigned i=0;i<identityCount;++i)if(identities[i]==p)return i;if(identityCount==1024)_exit(62);identities[identityCount]=p;return identityCount++;}
static void ptr(const void* p){if(!p){n(-1);return;}for(unsigned i=0;i<identityCount;++i)if(identities[i]==p){n(i);return;}cap->issue=autotest::Capture::UnsupportedPointer;n(-2);}
static std::string ascii(const CEGUI::String& s){std::string r;for(size_t i=0;i<s.length();++i)r+=char(s[i]);return r;}
static void str(const CEGUI::String& s){n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
static int wid(const CEGUI::Window* p){for(unsigned i=0;i<windowCount;++i)if(p==reinterpret_cast<CEGUI::Window*>(windowMemory[i]))return i;_exit(63);}
static CEGUI::Window* window(const std::string& name,CEGUI::Window* parent){
 std::map<std::string,CEGUI::Window*>::iterator old=windowNames.find(name);if(old!=windowNames.end())return old->second;
 if(windowCount==256)_exit(64);unsigned i=windowCount++;CEGUI::Window* p=reinterpret_cast<CEGUI::Window*>(windowMemory[i]);
 remember(p);*(void***)(static_cast<CEGUI::EventSet*>(p))=eventVtable;
 p->d_parent=parent;p->d_riseOnClick=true;p->d_mousePassThroughEnabled=false;p->d_wantsMultiClicks=true;p->d_zOrderingEnabled=true;p->d_visible=true;p->d_ID=700+i;
 positions[i]=CEGUI::UVector2(CEGUI::UDim(.1f*i,3+i),CEGUI::UDim(-.2f*i,7+i));
 sizes[i]=CEGUI::UVector2(CEGUI::UDim((int(i%3)-1)*.25f,40+i),CEGUI::UDim(.4f,60+i));
 texts[i]="before";properties[i]="before-property";windowNames[name]=p;return p;
}
static CEGUI::Font* font(const std::string& name){
 std::map<std::string,CEGUI::Font*>::iterator old=fontNames.find(name);if(old!=fontNames.end())return old->second;
 if(fontCount==8)_exit(65);CEGUI::Font* p=reinterpret_cast<CEGUI::Font*>(fontMemory[fontCount++]);remember(p);*(void***)p=fontVtable;
 new(&field<CEGUI::String>(p,0x368))CEGUI::String("old-colour");new(&field<CEGUI::String>(p,0x418))CEGUI::String("old-underline");field<bool>(p,0x4c8)=false;fontNames[name]=p;return p;
}
extern "C" char exceptionBaseCtor[] __asm__("_ZN5CEGUI9ExceptionC2ERKNS_6StringES3_S3_i");
static void exceptionCtor(CEGUI::Exception* p,const CEGUI::String& message,const CEGUI::String& name,const CEGUI::String& file,int line){
 new(&p->d_message)CEGUI::String(message);new(&p->d_filename)CEGUI::String(file);new(&p->d_name)CEGUI::String(name);p->d_line=line;
}
static void throwGeneric(const char* reason){throw CEGUI::GenericException(CEGUI::String(reason),CEGUI::String("fixture"),17);}
static std::wstring appPath(){n(1);return current.variant&1?L"/fixture/Ω/":L"/fixture/";}
static std::string utf8(const std::wstring& s){n(2);cap->addText(s);return Ogre::UTFString(s).asUTF8();}
static SDL_RWops* rw(const char* path,const char* mode){n(3);cap->addText(std::string(path));cap->addText(std::string(mode));return object<SDL_RWops>(20);}
static SDL_Surface* bmp(SDL_RWops* p,int release){n(4);ptr(p);n(release);++surfaceCount;return current.scenario==1&&surfaceCount==2?NULL:object<SDL_Surface>(20+surfaceCount);}
static SDL_Cursor* cursor(SDL_Surface* p,int x,int y){n(5);ptr(p);n(x);n(y);++cursorCount;return current.scenario==2&&cursorCount==3?NULL:object<SDL_Cursor>(25+cursorCount);}
static void freeSurface(SDL_Surface* p){n(6);ptr(p);}
static float aspect(CGameUI* p){n(7);ptr(p);++aspectCount;return aspectCount==1?1.3333f+current.variant*.07f:1.75f;}
static float height(CGameUI* p){n(8);ptr(p);return 768.f+current.variant;}
static std::string floatString(float v){n(9);f(v);char s[64];std::sprintf(s,"%.6f",v);return s;}
static float width(CGameUI* p){n(10);ptr(p);return 1024.f+current.variant;}
static Ogre::LogManager* logger(){n(11);return object<Ogre::LogManager>(10);}
static void log(Ogre::LogManager* p,const std::string& s,Ogre::LogMessageLevel level,bool suppress){n(12);ptr(p);cap->addText(s);n(level);n(suppress);}
static CMasterResourceManager* master(){n(13);return object<CMasterResourceManager>(1);}
static void soundCtor(CSoundBank* p,CSoundManager* manager,bool flag){n(14);n(remember(p));ptr(manager);n(flag);}
static CSoundData* soundData(CSoundBankDataInformation* p,const std::wstring& s){n(15);ptr(p);cap->addText(s);unsigned i=soundCount++;return current.variant&(1u<<i)?object<CSoundData>(14+i):NULL;}
static void sample(CSoundBank* p,int id,long long guid){n(16);ptr(p);n(id);q(guid);}
static void rendererCtor(void* p,Ogre::RenderWindow* window,unsigned char queue,bool post,unsigned quads,Ogre::SceneManager* scene){n(17);n(remember(p));ptr(window);n(queue);n(post);n(quads);ptr(scene);}
static std::wstring dataPath(){n(18);return current.variant&2?L"/data/é/":L"/data/";}
static std::string narrow(const wchar_t* p){n(19);std::wstring s(p);cap->addText(s);return Ogre::UTFString(s).asUTF8();}
static void systemCtor(CEGUI::System* p,CEGUI::Renderer* renderer,CEGUI::ResourceProvider* resources,CEGUI::XMLParser* parser,CEGUI::ScriptModule* script,const CEGUI::String& config,const CEGUI::String& logfile){
 n(20);n(remember(p));ptr(renderer);ptr(resources);ptr(parser);ptr(script);str(config);str(logfile);systemObject=p;
 p->d_defaultFont=font("initial");p->d_defaultTooltip=static_cast<CEGUI::Tooltip*>(window("default-tooltip",NULL));p->d_activeSheet=NULL;
}
static CFileSystem* filesystem(){n(21);return object<CFileSystem>(9);}
static void fileInfo(CFileSystem* p,const std::wstring& path,CFileInfo& info,bool a,bool b,bool c){
 n(22);ptr(p);cap->addText(path);n(a);n(b);n(c);n(info.m_eFormat);n(info.m_eLocation);n(info.m_bExists);cap->addText(info.m_sResourceName);
 ++fileCount;if(current.scenario==12&&path==L"media/ui/guilookskin.scheme")throwGeneric("resolve first scheme");info.m_sResourceName=Ogre::UTFString(path).asUTF8();info.m_sPath=path;info.m_sResourceGroup="fixture";info.m_eFormat=3;info.m_eLocation=0;info.m_bExists=!(current.scenario==3&&path.find(L"missing")!=std::wstring::npos);
}
static CEGUI::Scheme* loadScheme(CEGUI::SchemeManager* p,const CEGUI::String& file,const CEGUI::String& group){n(23);ptr(p);str(file);str(group);if(current.scenario==13&&ascii(file).find("guilookskin")!=std::string::npos)throwGeneric("load first scheme");return object<CEGUI::Scheme>(11);}
static CEGUI::Scheme* scheme(CEGUI::SchemeManager* p,const CEGUI::String& name){n(24);ptr(p);str(name);return object<CEGUI::Scheme>(11);}
static void defaultFont(CEGUI::System* p,const CEGUI::String& name){n(25);ptr(p);str(name);p->d_defaultFont=font(ascii(name));}
static CEGUI::Font* getFont(CEGUI::FontManager* p,const CEGUI::String& name){n(26);ptr(p);str(name);return font(ascii(name));}
static void defaultTooltip(CEGUI::System* p,const CEGUI::String& name){n(27);ptr(p);str(name);p->d_defaultTooltip=static_cast<CEGUI::Tooltip*>(window("tooltip/"+ascii(name),NULL));}
static void top(CEGUI::Window* p,bool v){n(28);ptr(p);n(v);p->d_alwaysOnTop=v;}
static void hover(CEGUI::Tooltip* p,float v){n(29);ptr(p);f(v);}
static void display(CEGUI::Tooltip* p,float v){n(30);ptr(p);f(v);}
static void activate(CEGUI::Window* p){n(31);ptr(p);p->d_active=true;}
static void fontResolution(CEGUI::Font* p,const CEGUI::Size& size){n(32);ptr(p);cap->add(&size,sizeof(size));}
static CEGUI::Window* makeWindow(CEGUI::WindowManager* p,const CEGUI::String& type,const CEGUI::String& name,const CEGUI::String& prefix){n(33);ptr(p);str(type);str(name);str(prefix);return window(ascii(name),NULL);}
static void sizeWindow(CEGUI::Window* p,const CEGUI::UVector2& size){n(34);ptr(p);cap->add(&size,sizeof(size));sizes[wid(p)]=size;}
static CEGUI::Window* sheet(CEGUI::System* p,CEGUI::Window* value){n(35);ptr(p);ptr(value);CEGUI::Window* old=p->d_activeSheet;p->d_activeSheet=value;return old;}
static CEGUI::Window* layout(CEGUI::WindowManager* p,const CEGUI::String& name,bool random){n(36);ptr(p);str(name);n(random);return window(ascii(name),NULL);}
static void scale(CGameUI* p,CEGUI::Window* w,bool v){n(37);ptr(p);ptr(w);n(v);}
static CEGUI::Window* child(const CEGUI::Window* p,const CEGUI::String& name){n(38);ptr(p);str(name);if(current.scenario==4&&name=="PetAggressive")return NULL;char s[32];std::sprintf(s,"%d/",wid(p));return window(s+ascii(name),const_cast<CEGUI::Window*>(p));}
static void boundDtor(CEGUI::BoundSlot*){n(39);}
static void subscriberDtor(CEGUI::SubscriberSlot* p){n(40);p->d_functor_impl=NULL;}
static std::string unique(const std::string& s){n(41);cap->addText(s);char b[32];std::sprintf(b,"%u",++uniqueCount);return s+b;}
static void add(CEGUI::Window* p,CEGUI::Window* c){n(42);ptr(p);ptr(c);c->d_parent=p;}
static void back(CEGUI::Window* p){n(43);ptr(p);}
static void zOrder(CEGUI::Window* p,bool v){n(44);ptr(p);n(v);p->d_zOrderingEnabled=v;}
static CEGUI::Imageset* getImageset(CEGUI::ImagesetManager* p,const CEGUI::String& name){n(45);ptr(p);str(name);return object<CEGUI::Imageset>(31+(ascii(name).size()%3));}
static void imagesetResolution(CEGUI::Imageset* p,const CEGUI::Size& size){n(46);ptr(p);cap->add(&size,sizeof(size));if(current.scenario==15&&(p==object<CEGUI::Imageset>(34)||p==object<CEGUI::Imageset>(35)||p==object<CEGUI::Imageset>(36)))throwGeneric("resize item imageset");}
static unsigned fileList(CFileSystem* p,const std::wstring& directory,TArrayList<std::wstring>& files,std::wstring pattern,bool a,bool b,bool c,bool d){n(47);ptr(p);cap->addText(directory);cap->addText(pattern);n(a);n(b);n(c);n(d);unsigned count=current.scenario==5?0:current.variant%4+1;for(unsigned i=0;i<count;++i){wchar_t s[64];std::swprintf(s,64,L"media/ui/itemicons/%ls%u.imageset",i%2?L"missing":L"present",i);files.add(s);}return count;}
static CEGUI::Imageset* makeImageset(CEGUI::ImagesetManager* p,const CEGUI::String& name,const CEGUI::String& group){n(48);ptr(p);str(name);str(group);if(current.scenario==14)throwGeneric("load item imageset");return current.scenario==6?NULL:object<CEGUI::Imageset>(34+ascii(name).size()%3);}
static void functions(CGameUI* p,CEGUI::Window* w){n(49);ptr(p);ptr(w);}
static void handlers(CGameUI* p,CEGUI::Window* w){n(50);ptr(p);ptr(w);}
static void remove(CEGUI::Window* p,CEGUI::Window* c){n(51);ptr(p);ptr(c);c->d_parent=NULL;}
static CEGUI::Rect pixelRect(const CEGUI::Window* p){n(52);ptr(p);float i=wid(p);return CEGUI::Rect(i+.25f,i+1.f,i+200.f,i+300.f);}
static void tooltip(CEGUI::Window* p,CEGUI::Tooltip* t){n(53);ptr(p);ptr(t);p->d_customTip=t;}
static const CEGUI::UVector2& position(const CEGUI::Window* p){n(54);ptr(p);return positions[wid(p)];}
static CEGUI::UVector2 size(const CEGUI::Window* p){n(55);ptr(p);return sizes[wid(p)];}
static void multi(CEGUI::Window* p,bool v){n(56);ptr(p);n(v);p->d_wantsMultiClicks=v;}
static void selected(CEGUI::RadioButton* p,bool v){n(57);ptr(p);n(v);}
static void visible(CEGUI::Window* p,bool v){n(58);ptr(p);n(v);p->d_visible=v;}
static void muted(CEGUI::EventSet* p,bool v){n(59);ptr(static_cast<CEGUI::Window*>(p));n(v);p->d_muted=v;}
static const CEGUI::Image& getImage(CEGUI::Imageset* p,const CEGUI::String& name){n(60);ptr(p);str(name);return *object<CEGUI::Image>(37);}
static CEGUI::String imageString(const CEGUI::Image* p){n(61);ptr(p);return CEGUI::String("fixture-image");}
static void property(CEGUI::PropertySet* p,const CEGUI::String& name,const CEGUI::String& value){n(62);CEGUI::Window* w=static_cast<CEGUI::Window*>(p);ptr(w);str(name);str(value);properties[wid(w)]=value;}
static int setting(CDynamicPropertyFile* p,unsigned id){n(63);ptr(p);n(id);if(id==100)return int(current.variant%4)-1;if(id==101)return current.variant%3-1;return (id+current.variant)%226;}
static const CEGUI::Image* gameImage(CGameUI* p,const unsigned char* name){n(64);ptr(p);cap->addText(std::string(reinterpret_cast<const char*>(name)));return object<CEGUI::Image>(38);}
static void id(CEGUI::Window* p,unsigned v){n(65);ptr(p);n(v);p->d_ID=v;}
static void text(CEGUI::Window* p,const CEGUI::String& value){n(66);ptr(p);str(value);texts[wid(p)]=value;}
static std::string unsignedString(unsigned x){n(67);n(x);char b[32];std::sprintf(b,"%u",x);return b;}
static CEGUI::UDim windowWidth(const CEGUI::Window* p){n(68);ptr(p);return sizes[wid(p)].d_x;}
static CEGUI::UDim windowHeight(const CEGUI::Window* p){n(69);ptr(p);return sizes[wid(p)].d_y;}
static void constructor68(void* p,CGameUI* ui,CSettings* settings,Ogre::RenderWindow* render,Ogre::SceneManager* scene,Ogre::SceneManager* second,CEGUI::Window* root,CResourceManager* resources){n(168);n(remember(p));ptr(ui);ptr(settings);ptr(render);ptr(scene);ptr(second);ptr(root);ptr(resources);}
static void constructor69(void* p,CGameUI* ui,CSettings* settings,Ogre::RenderWindow* render,Ogre::SceneManager* scene,Ogre::SceneManager* second,CEGUI::Window* root,CResourceManager* resources){n(169);n(remember(p));ptr(ui);ptr(settings);ptr(render);ptr(scene);ptr(second);ptr(root);ptr(resources);}
static void constructor70(void* p,CGameUI* ui,CSettings* settings,Ogre::RenderWindow* render,Ogre::SceneManager* scene,Ogre::SceneManager* second,CEGUI::Window* root,CResourceManager* resources){n(170);n(remember(p));ptr(ui);ptr(settings);ptr(render);ptr(scene);ptr(second);ptr(root);ptr(resources);}
static void constructor71(void* p,CGameUI* ui,CSettings* settings,Ogre::RenderWindow* render,Ogre::SceneManager* scene,Ogre::SceneManager* second,CEGUI::Window* root,CResourceManager* resources){n(171);n(remember(p));ptr(ui);ptr(settings);ptr(render);ptr(scene);ptr(second);ptr(root);ptr(resources);}
static void constructor72(void* p,CGameUI* ui,CSettings* settings,Ogre::RenderWindow* render,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(172);n(remember(p));ptr(ui);ptr(settings);ptr(render);ptr(scene);ptr(root);ptr(resources);}
static void constructor73(void* p,CGameUI* ui,CSettings* settings,Ogre::RenderWindow* render,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(173);n(remember(p));ptr(ui);ptr(settings);ptr(render);ptr(scene);ptr(root);ptr(resources);}
static void constructor74(void* p,CGameUI* ui,CSettings* settings,Ogre::RenderWindow* render,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(174);n(remember(p));ptr(ui);ptr(settings);ptr(render);ptr(scene);ptr(root);ptr(resources);}
static void constructor75(void* p,CGameUI* ui,CSettings* settings,Ogre::RenderWindow* render,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(175);n(remember(p));ptr(ui);ptr(settings);ptr(render);ptr(scene);ptr(root);ptr(resources);}
static void constructor76(void* p,CGameUI* ui,CSettings* settings,Ogre::RenderWindow* render,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(176);n(remember(p));ptr(ui);ptr(settings);ptr(render);ptr(scene);ptr(root);ptr(resources);}
static void constructor77(void* p,CGameUI* ui,CSettings* settings,Ogre::RenderWindow* render,Ogre::SceneManager* scene,Ogre::SceneManager* second,CEGUI::Window* root,CResourceManager* resources){n(177);n(remember(p));ptr(ui);ptr(settings);ptr(render);ptr(scene);ptr(second);ptr(root);ptr(resources);}
static void constructor78(void* p,CGameUI* ui,CSettings* settings,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(178);n(remember(p));ptr(ui);ptr(settings);ptr(scene);ptr(root);ptr(resources);}
static void constructor79(void* p,CGameUI* ui,CSettings* settings,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(179);n(remember(p));ptr(ui);ptr(settings);ptr(scene);ptr(root);ptr(resources);}
static void constructor80(void* p,CGameUI* ui,CSettings* settings,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(180);n(remember(p));ptr(ui);ptr(settings);ptr(scene);ptr(root);ptr(resources);}
static void constructor81(void* p,CGameUI* ui,CSettings* settings,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(181);n(remember(p));ptr(ui);ptr(settings);ptr(scene);ptr(root);ptr(resources);}
static void constructor82(void* p,CGameUI* ui,CSettings* settings,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(182);n(remember(p));ptr(ui);ptr(settings);ptr(scene);ptr(root);ptr(resources);}
static void constructor83(void* p,CGameUI* ui,CSettings* settings,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(183);n(remember(p));ptr(ui);ptr(settings);ptr(scene);ptr(root);ptr(resources);}
static void constructor84(void* p,CGameUI* ui,CSettings* settings,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(184);n(remember(p));ptr(ui);ptr(settings);ptr(scene);ptr(root);ptr(resources);}
static void constructor85(void* p,CGameUI* ui,CSettings* settings,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(185);n(remember(p));ptr(ui);ptr(settings);ptr(scene);ptr(root);ptr(resources);}
static void constructor86(void* p,CGameUI* ui,CSettings* settings,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(186);n(remember(p));ptr(ui);ptr(settings);ptr(scene);ptr(root);ptr(resources);}
static void constructor87(void* p,CGameUI* ui,CSettings* settings,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(187);n(remember(p));ptr(ui);ptr(settings);ptr(scene);ptr(root);ptr(resources);}
static void constructor88(void* p,CGameUI* ui,CSettings* settings,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(188);n(remember(p));ptr(ui);ptr(settings);ptr(scene);ptr(root);ptr(resources);}
static void interactive(CGameUI* p,bool value){n(189);ptr(p);n(value);}
static void baseCtor(CRunicCore* p){n(190);n(remember(p));field<void*>(p,8)=NULL;++baseCount;}
static void equipmentLoad(CEquipmentTooltip* p,CGameUI* ui,std::wstring path){n(191);ptr(p);ptr(ui);cap->addText(path);q(p->m_iCachedItemGuid);ptr(p->m_pParent);}
static void skillLoad(CSkillTooltip* p,CGameUI* ui,std::wstring path){n(192);ptr(p);ptr(ui);cap->addText(path);ptr(p->m_pGameUI);cap->addText(p->m_sText);n(p->m_iIndex);ptr(p->m_pRoot);}
static void foldoutLoad(CSkillFoldout* p,CGameUI* ui,std::wstring path){n(193);ptr(p);ptr(ui);cap->addText(path);n(p->m_iSelection);ptr(p->m_pGameUI);ptr(p->m_pParent);n(p->m_bFlagCB1);for(unsigned i=0;i<100;++i)q(p->m_SkillIndices[i]);}
static CEGUI::System* getSystem(){n(194);return systemObject;}
static void consoleCtor(void* p,CGameUI* ui,CResourceManager* resources,CEGUI::Window* root){n(195);n(remember(p));ptr(ui);ptr(resources);ptr(root);}
static void fps(CGameUI* p){n(196);ptr(p);}
static void createText(CTextEvent* p,CGameUI* ui,CEGUI::Window* root){n(197);ptr(p);ptr(ui);ptr(root);f(p->m_Value10);f(p->m_Value14);f(p->m_Value18);cap->addText(p->m_Text);
 f(p->m_Colour28.getRed());f(p->m_Colour28.getGreen());f(p->m_Colour28.getBlue());f(p->m_Colour28.getAlpha());
 f(p->m_Colour40.getRed());f(p->m_Colour40.getGreen());f(p->m_Colour40.getBlue());f(p->m_Colour40.getAlpha());
 f(p->m_Value60);f(p->m_Value64);f(p->m_Value68);f(p->m_Value70);ptr(p->m_pWindow);n(p->m_Flag80);n(p->m_Flag81);n(p->m_Flag82);
 char b[32];std::sprintf(b,"event-%u",eventCount++);p->m_pWindow=window(b,root);
}
static void menuManagerCtor(void* p,CGameUI* ui,CSettings* settings,Ogre::Camera* camera,Ogre::SceneManager* scene,CEGUI::Window* root,CResourceManager* resources){n(198);n(remember(p));ptr(ui);ptr(settings);ptr(camera);ptr(scene);ptr(root);ptr(resources);}
static void unexpected(){_exit(69);}
TL_FUNCTION(callback0,"_ZN7CGameUI19handle_MouseThroughERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback1,"_ZN7CGameUI19handle_ClickThroughERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback2,"_ZN7CGameUI21handle_SkillMouseOverERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback3,"_ZN7CGameUI20handle_SkillMouseOutERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback4,"_ZN7CGameUI17handle_SkillClickERKN5CEGUI9EventArgsE")
static CEGUI::Event::Connection subscribe(CEGUI::EventSet* p,const CEGUI::String& name,CEGUI::Event::Subscriber sub){
 n(210);ptr(static_cast<CEGUI::Window*>(p));str(name);CEGUI::MemberFunctionSlot<CGameUI>* slot=static_cast<CEGUI::MemberFunctionSlot<CGameUI>*>(sub.d_functor_impl);
 intptr_t words[2];typedef char member_size[sizeof(slot->d_function)==sizeof(words)?1:-1];std::memcpy(words,&slot->d_function,sizeof(words));
 char* pairs[][2]={{callback0_original,callback0_linked},{callback1_original,callback1_linked},{callback2_original,callback2_linked},{callback3_original,callback3_linked},{callback4_original,callback4_linked}};
 bool known=false;for(unsigned i=0;i<5;++i)if(words[0]==reinterpret_cast<intptr_t>(pairs[i][0])||words[0]==reinterpret_cast<intptr_t>(pairs[i][1])){n(i);known=true;break;}
 if(!known){cap->issue=autotest::Capture::UnsupportedPointer;n(-1);}q(words[1]);ptr(slot->d_object);++connectionCount;
 CEGUI::Event::Connection result;
 if(current.scenario==7){result.d_object=static_cast<CEGUI::BoundSlot*>(::operator new(sizeof(CEGUI::BoundSlot)));result.d_count=new unsigned(1);}
 return result;
}
static void setup(const Case& c,autotest::Capture& out){
 current=c;cap=&out;identityCount=windowCount=fontCount=uniqueCount=aspectCount=fileCount=soundCount=baseCount=eventCount=connectionCount=cursorCount=surfaceCount=0;
 std::memset(objects,0,sizeof(objects));std::memset(windowMemory,0,sizeof(windowMemory));std::memset(fontMemory,0,sizeof(fontMemory));
 new(&windowNames)std::map<std::string,CEGUI::Window*>;new(&fontNames)std::map<std::string,CEGUI::Font*>;
 for(unsigned i=0;i<40;++i)remember(objects[i]);game=object<CGameUI>(0);systemObject=NULL;
 eventVtable[2]=reinterpret_cast<void*>(&subscribe);fontVtable[7]=reinterpret_cast<void*>(&fontResolution);
 field<void*>(game,0x10)=objects[2];field<void*>(game,0x18)=objects[3];field<void*>(game,0x20)=objects[4];field<void*>(game,0x28)=objects[5];
 field<void*>(game,0x78)=objects[6];field<void*>(game,0x4d0)=objects[7];field<void*>(game,0x1308)=objects[8];
 field<void*>(objects[1],0x98)=objects[12];field<void*>(objects[1],0x100)=objects[13];
 for(unsigned i=0;i<4;++i)field<long long>(objects[14+i],0x20)=1000000+100*i+c.variant;
 new(reinterpret_cast<void*>(0x14b7d00))std::string();new(reinterpret_cast<void*>(0x14b7d08))std::wstring();
 for(unsigned i=0;i<226;++i){wchar_t b[64];std::swprintf(b,64,L"Key%u%ls",i,c.variant&1?L"Ω":L"");new(reinterpret_cast<std::wstring*>(0x14b8440)+i)std::wstring(b);}
 for(unsigned i=0;i<10;++i)reinterpret_cast<unsigned*>(0x14b9c40)[i]=110+i;
 KSETTINGS_TOGGLE_ITEM_NAME=100;KSETTINGS_DISPLAY_STATS=101;KSETTINGS_KEYMAP_SWAPSKILLS=102;KSETTINGS_KEYMAP_SHOWITEMS=103;
 new(&field<std::vector<SDL_Cursor*> >(game,0x19f0))std::vector<SDL_Cursor*>;
 if(c.scenario==8)field<std::vector<SDL_Cursor*> >(game,0x19f0).resize(7,object<SDL_Cursor>(30));
 new(&field<TArrayList<std::wstring> >(game,0x440))TArrayList<std::wstring>(1+c.variant%3);
 new(&field<TArrayList<CEGUI::Imageset*> >(game,0x458))TArrayList<CEGUI::Imageset*>(1+c.variant%3);
 if(c.scenario==9)field<TArrayList<CEGUI::Imageset*> >(game,0x458).add(object<CEGUI::Imageset>(39));
 new(&field<std::vector<void*> >(game,0x1930))std::vector<void*>;
 new(&field<std::vector<void*> >(game,0x1948))std::vector<void*>;
 if(c.scenario==10){field<std::vector<void*> >(game,0x1930).reserve(32);field<std::vector<void*> >(game,0x1948).reserve(32);}
 if(c.scenario==11)field<CEGUI::Window*>(game,0xe0)=window("existing-information",NULL);
 CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton=object<CEGUI::WindowManager>(18);
 CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton=object<CEGUI::ImagesetManager>(19);
 CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton=object<CEGUI::FontManager>(18);
 CEGUI::Singleton<CEGUI::SchemeManager>::ms_Singleton=object<CEGUI::SchemeManager>(19);
}
static void snapshot(){
 n(900);n(aspectCount);n(fileCount);n(soundCount);n(baseCount);n(eventCount);n(connectionCount);n(cursorCount);n(surfaceCount);
 const unsigned offsets[]={0xe0,0xe8,0xf0,0xf8,0x100,0x108,0x110,0x118,0x120,0x128,0x130,0x138,0x140,0x148,0x150,0x158,0x160,0x168,0x170,0x178,0x180,0x190,0x198,0x1a8,0x1b0,0x1b8,0x1c0,0x1c8,0x1d0,0x1d8,0x1e0,0x1e8,0x1f0,0x1f8,0x200,0x208,0x210,0x218,0x220,0x238,0x240,0x428,0x430,0x438,0x470,0x478,0x480,0x488,0x490,0x498,0x4a0,0x4a8,0x4b0,0x4b8,0x4c0,0x580,0x588,0x1310,0x1318,0x1690,0x16a8};
 for(unsigned i=0;i<sizeof(offsets)/sizeof(offsets[0]);++i){n(offsets[i]);ptr(field<void*>(game,offsets[i]));}
 for(unsigned off=0x4d8;off<0x580;off+=8)ptr(field<void*>(game,off));
 for(unsigned off=0x260;off<0x3b0;off+=8)ptr(field<void*>(game,off));
 for(unsigned i=0;i<100;++i)q(field<long long>(game,0x1320+8*i));
 f(field<float>(game,0x4c8));f(field<float>(game,0x4cc));
 cap->add(static_cast<char*>(static_cast<void*>(game))+0x16cc,0xc0);
 cap->add(static_cast<char*>(static_cast<void*>(game))+0x199c,0x50);
 std::vector<SDL_Cursor*>& cursors=field<std::vector<SDL_Cursor*> >(game,0x19f0);n(cursors.size());for(unsigned i=0;i<cursors.size();++i)ptr(cursors[i]);
 TArrayList<std::wstring>& files=field<TArrayList<std::wstring> >(game,0x440);n(files.m_nCount);n(files.m_nCapacity);for(unsigned i=0;i<files.size();++i)cap->addText(files[i]);
 TArrayList<CEGUI::Imageset*>& images=field<TArrayList<CEGUI::Imageset*> >(game,0x458);n(images.m_nCount);n(images.m_nCapacity);for(unsigned i=0;i<images.size();++i)ptr(images[i]);
 for(unsigned off=0x1930;off<=0x1948;off+=0x18){std::vector<void*>& values=field<std::vector<void*> >(game,off);n(values.size());for(unsigned i=0;i<values.size();++i)ptr(values[i]);}
 ptr(field<void*>(objects[1],0xa0));
 for(unsigned i=0;i<windowCount;++i){CEGUI::Window* p=reinterpret_cast<CEGUI::Window*>(windowMemory[i]);ptr(p);ptr(p->d_parent);n(p->d_riseOnClick);n(p->d_mousePassThroughEnabled);n(p->d_wantsMultiClicks);n(p->d_zOrderingEnabled);n(p->d_visible);n(p->d_alwaysOnTop);n(p->d_active);n(p->d_muted);n(p->d_ID);ptr(p->d_customTip);str(texts[i]);str(properties[i]);cap->add(&sizes[i],sizeof(sizes[i]));cap->add(&positions[i],sizeof(positions[i]));}
 for(unsigned i=0;i<fontCount;++i){void* p=fontMemory[i];ptr(p);str(field<CEGUI::String>(p,0x368));str(field<CEGUI::String>(p,0x418));n(field<bool>(p,0x4c8));}
 for(unsigned off=0x1698;off<=0x16a0;off+=8){void* list=field<void*>(game,off);n(list!=NULL);if(!list){cap->issue=autotest::Capture::UnsupportedPointer;return;}
  TLinkedListNode<CTextEvent*>* p=field<TLinkedListNode<CTextEvent*>*>(list,0);TLinkedListNode<CTextEvent*>* previous=NULL;unsigned count=0;
  while(p&&count<=100){n(p->m_pPrevious==previous);ptr(p->m_Data);ptr(p->m_Data->m_pWindow);previous=p;p=p->m_pNext;++count;}n(count);n(p==NULL);
  if(p)cap->issue=autotest::Capture::Overflow;
 }
}
static void side(const Case& c,bool ours,autotest::Capture& out){setup(c,out);detour::Set patches0,patches1,patches2,patches3;
 TL_REDIRECT(patches0,startupDependency00,&appPath);
 TL_REDIRECT(patches0,startupDependency01,&utf8);
 patches0.redirect(startupDependency02,startupDependency02,&rw);
 patches0.redirect(startupDependency03,startupDependency03,&bmp);
 patches0.redirect(startupDependency04,startupDependency04,&cursor);
 patches0.redirect(startupDependency05,startupDependency05,&freeSurface);
 TL_REDIRECT(patches0,startupDependency06,&aspect);
 TL_REDIRECT(patches0,startupDependency07,&height);
 TL_REDIRECT(patches0,startupDependency08,&floatString);
 TL_REDIRECT(patches0,startupDependency09,&width);
 patches0.redirect(startupDependency10,startupDependency10,&logger);
 patches0.redirect(startupDependency11,startupDependency11,&log);
 TL_REDIRECT(patches0,startupDependency12,&master);
 TL_REDIRECT(patches0,startupDependency13,&soundCtor);
 TL_REDIRECT(patches0,startupDependency14,&soundData);
 TL_REDIRECT(patches0,startupDependency15,&sample);
 patches0.redirect(startupDependency16,startupDependency16,&rendererCtor);
 TL_REDIRECT(patches0,startupDependency17,&dataPath);
 TL_REDIRECT(patches0,startupDependency18,&narrow);
 patches0.redirect(startupDependency19,startupDependency19,&systemCtor);
 TL_REDIRECT(patches0,startupDependency20,&filesystem);
 TL_REDIRECT(patches0,startupDependency21,&fileInfo);
 patches0.redirect(startupDependency22,startupDependency22,&loadScheme);
 patches0.redirect(startupDependency23,startupDependency23,&scheme);
 patches0.redirect(startupDependency24,startupDependency24,&defaultFont);
 patches0.redirect(startupDependency25,startupDependency25,&getFont);
 patches0.redirect(startupDependency26,startupDependency26,&defaultTooltip);
 patches0.redirect(startupDependency27,startupDependency27,&top);
 patches1.redirect(startupDependency28,startupDependency28,&hover);
 patches1.redirect(startupDependency29,startupDependency29,&display);
 patches1.redirect(startupDependency30,startupDependency30,&activate);
 patches1.redirect(startupDependency31,startupDependency31,&makeWindow);
 patches1.redirect(startupDependency32,startupDependency32,&sizeWindow);
 patches1.redirect(startupDependency33,startupDependency33,&sheet);
 patches1.redirect(startupDependency34,startupDependency34,&layout);
 TL_REDIRECT(patches1,startupDependency35,&scale);
 patches1.redirect(startupDependency36,startupDependency36,&child);
 patches1.redirect(startupDependency37,startupDependency37,&boundDtor);
 patches1.redirect(startupDependency38,startupDependency38,&subscriberDtor);
 TL_REDIRECT(patches1,startupDependency39,&unique);
 patches1.redirect(startupDependency40,startupDependency40,&add);
 patches1.redirect(startupDependency41,startupDependency41,&back);
 patches1.redirect(startupDependency42,startupDependency42,&zOrder);
 patches1.redirect(startupDependency43,startupDependency43,&getImageset);
 patches1.redirect(startupDependency44,startupDependency44,&imagesetResolution);
 TL_REDIRECT(patches1,startupDependency45,&fileList);
 patches1.redirect(startupDependency46,startupDependency46,&makeImageset);
 TL_REDIRECT(patches1,startupDependency47,&functions);
 TL_REDIRECT(patches1,startupDependency48,&handlers);
 patches1.redirect(startupDependency49,startupDependency49,&remove);
 patches1.redirect(startupDependency50,startupDependency50,&pixelRect);
 patches1.redirect(startupDependency51,startupDependency51,&tooltip);
 patches1.redirect(startupDependency52,startupDependency52,&position);
 patches1.redirect(startupDependency53,startupDependency53,&size);
 patches1.redirect(startupDependency54,startupDependency54,&multi);
 patches1.redirect(startupDependency55,startupDependency55,&selected);
 patches2.redirect(startupDependency56,startupDependency56,&visible);
 patches2.redirect(startupDependency57,startupDependency57,&muted);
 patches2.redirect(startupDependency58,startupDependency58,&getImage);
 patches2.redirect(startupDependency59,startupDependency59,&imageString);
 patches2.redirect(startupDependency60,startupDependency60,&property);
 TL_REDIRECT(patches2,startupDependency61,&setting);
 TL_REDIRECT(patches2,startupDependency62,&gameImage);
 patches2.redirect(startupDependency63,startupDependency63,&id);
 patches2.redirect(startupDependency64,startupDependency64,&text);
 TL_REDIRECT(patches2,startupDependency65,&unsignedString);
 patches2.redirect(startupDependency66,startupDependency66,&windowWidth);
 patches2.redirect(startupDependency67,startupDependency67,&windowHeight);
 TL_REDIRECT(patches2,startupDependency68,&constructor68);
 TL_REDIRECT(patches2,startupDependency69,&constructor69);
 TL_REDIRECT(patches2,startupDependency70,&constructor70);
 TL_REDIRECT(patches2,startupDependency71,&constructor71);
 TL_REDIRECT(patches2,startupDependency72,&constructor72);
 TL_REDIRECT(patches2,startupDependency73,&constructor73);
 TL_REDIRECT(patches2,startupDependency74,&constructor74);
 TL_REDIRECT(patches2,startupDependency75,&constructor75);
 TL_REDIRECT(patches2,startupDependency76,&constructor76);
 TL_REDIRECT(patches2,startupDependency77,&constructor77);
 TL_REDIRECT(patches2,startupDependency78,&constructor78);
 TL_REDIRECT(patches2,startupDependency79,&constructor79);
 TL_REDIRECT(patches2,startupDependency80,&constructor80);
 TL_REDIRECT(patches2,startupDependency81,&constructor81);
 TL_REDIRECT(patches2,startupDependency82,&constructor82);
 TL_REDIRECT(patches2,startupDependency83,&constructor83);
 TL_REDIRECT(patches3,startupDependency84,&constructor84);
 TL_REDIRECT(patches3,startupDependency85,&constructor85);
 TL_REDIRECT(patches3,startupDependency86,&constructor86);
 TL_REDIRECT(patches3,startupDependency87,&constructor87);
 TL_REDIRECT(patches3,startupDependency88,&constructor88);
 TL_REDIRECT(patches3,startupDependency89,&interactive);
 TL_REDIRECT(patches3,startupDependency90,&baseCtor);
 TL_REDIRECT(patches3,startupDependency91,&equipmentLoad);
 TL_REDIRECT(patches3,startupDependency92,&skillLoad);
 TL_REDIRECT(patches3,startupDependency93,&foldoutLoad);
 patches3.redirect(startupDependency94,startupDependency94,&getSystem);
 TL_REDIRECT(patches3,startupDependency95,&consoleCtor);
 TL_REDIRECT(patches3,startupDependency96,&fps);
 TL_REDIRECT(patches3,startupDependency97,&createText);
 TL_REDIRECT(patches3,startupDependency98,&menuManagerCtor);
 TL_REDIRECT(patches3,startupDependency102,&unexpected);
 patches3.redirect(exceptionBaseCtor,exceptionBaseCtor,&exceptionCtor);
 if(patches0.failed()||patches1.failed()||patches2.failed()||patches3.failed())_exit(60);
 if(ours)autotest::invoke(out,&candidateStartup,game);else autotest::invoke(out,&originalStartup,game);
 snapshot();
}
static void left(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}
static void right(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(gameui_create_differential){
 using namespace startup_fixture;
 autotest::Coverage coverage("gameui_create_differential",reinterpret_cast<uintptr_t>(&originalStartup));
 unsigned count=0;
 for(unsigned scenario=0;scenario<16;++scenario)for(unsigned variant=0;variant<16;++variant){
  Case c={scenario,variant};autotest::Outcome a,b;autotest::runChild(left,&c,a);autotest::runChild(right,&c,b);
  int diff=coverage.observe(host,a,b);++count;
  if(diff||a.childStatus||b.childStatus||!a.reportValid||!b.reportValid||!a.capture.callCompleted||!b.capture.callCompleted){
   coverage.report(host);host->log("    startup case %u/%u differs exits %d/%d lengths %lu/%lu issues %d/%d\n",scenario,variant,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length,a.capture.issue,b.capture.issue);
   unsigned off=0;while(off<a.capture.length&&off<b.capture.length&&a.capture.data[off]==b.capture.data[off])++off;
   host->log("    first mismatch %u\n",off);
   for(unsigned j=off>24?off-24:0;j<off+48&&(j<a.capture.length||j<b.capture.length);++j)host->log("%u:%02x/%02x ",j,j<a.capture.length?(unsigned char)a.capture.data[j]:0,j<b.capture.length?(unsigned char)b.capture.data[j]:0);
   host->log("\n");return 1;
  }
 }
 coverage.report(host);host->log("    startup complete pairs %u\n",count);return 0;
}
