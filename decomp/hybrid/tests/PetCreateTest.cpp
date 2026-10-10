// Original-versus-compiled Pet creation fixture; collaborators are controlled.
// Requires successful completion, full trace and final field equality.
#include <cstring>
#include <map>
#include <limits>
#include <new>
#include <string>
#define protected public
#define private public
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <CEGUI.h>
#include <CEGUIMemberFunctionSlot.h>
#include "FileSystem.h"
#include <OgreEntity.h>
#include <OgreMesh.h>
#include "GenericModel.h"
#include "PetMenu.h"
#include "SkillTooltip.h"
#undef protected
#undef private
#include "DynamicPropertyFile.h"
#include "ResourceManager.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalCreate, (CPetMenu*), "_ZN8CPetMenu11createMenusEv")
extern "C" void candidateCreate(CPetMenu*) __asm__("_ZN8CPetMenu11createMenusEv");
TL_FUNCTION(propInt,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(modelCreate,"_ZN16CResourceManager18createGenericModelEPN4Ogre12SceneManagerEPKwS4_bbb")
TL_FUNCTION(propFloat,"_ZN20CDynamicPropertyFile8GetFloatEj")
extern "C" char meshGet[] __asm__("_ZNK4Ogre6Entity7getMeshEv");
extern "C" char meshBounds[] __asm__("_ZN4Ogre4Mesh10_setBoundsERKNS_14AxisAlignedBoxEb");
extern "C" char imageGet[] __asm__("_ZNK5CEGUI15ImagesetManager11getImagesetERKNS_6StringE");
extern "C" char windowCreate[] __asm__("_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_");
extern "C" char windowSize[] __asm__("_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
extern "C" char windowPosition[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char windowProperty[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
extern "C" char windowZ[] __asm__("_ZN5CEGUI6Window19setZOrderingEnabledEb");
TL_FUNCTION(fileSingleton,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(fileInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
extern "C" char loadLayout[] __asm__("_ZN5CEGUI13WindowManager16loadWindowLayoutERKNS_6StringEb");
extern "C" char searchChild[] __asm__("_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE");
extern "C" char removeChild[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char addChild[] __asm__("_ZN5CEGUI6Window14addChildWindowEPS0_");
extern "C" char moveBack[] __asm__("_ZN5CEGUI6Window10moveToBackEv");
extern "C" char moveFront[] __asm__("_ZN5CEGUI6Window11moveToFrontEv");
extern "C" char sizeGet[] __asm__("_ZNK5CEGUI6Window7getSizeEv");
extern "C" char mutedSet[] __asm__("_ZN5CEGUI8EventSet13setMutedStateEb");
extern "C" char visibleSet[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
TL_FUNCTION(convertScale,"_ZN7CGameUI20convertToScreenScaleEPN5CEGUI6WindowEb")
TL_FUNCTION(mapFuncs,"_ZN7CGameUI14mapToFunctionsEPN5CEGUI6WindowE")
extern "C" char propertyPresentFn[] __asm__("_ZNK5CEGUI11PropertySet17isPropertyPresentERKNS_6StringE");
TL_FUNCTION(uniqueNames,"_ZN7STRINGS10uniqueNameERKSs")
extern "C" char positionGet[] __asm__("_ZNK5CEGUI6Window11getPositionEv");
extern "C" char fontSet[] __asm__("_ZN5CEGUI6Window7setFontERKNS_6StringE");
extern "C" char textSet[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
extern "C" char topSet[] __asm__("_ZN5CEGUI6Window14setAlwaysOnTopEb");
TL_FUNCTION(extremesFn,"_ZN13CGenericModel16generateExtremesEmb")
TL_FUNCTION(tooltipLoadFn,"_ZN13CSkillTooltip4loadEP7CGameUISbIwSt11char_traitsIwESaIwEE")
extern "C" char getPropertyFn[] __asm__("_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE");
extern "C" char getTooltipFn[] __asm__("_ZNK5CEGUI6Window14getTooltipTextEv");
extern "C" char setIdFn[] __asm__("_ZN5CEGUI6Window5setIDEj");
extern "C" char cameraPositionFn[] __asm__("_ZN4Ogre6Camera11setPositionERKNS_7Vector3E");
extern "C" char cameraLookFn[] __asm__("_ZN4Ogre6Camera6lookAtERKNS_7Vector3E");
TL_FUNCTION(callback0Fn,"_ZN8CPetMenu17handle_RotateLeftERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback1Fn,"_ZN8CPetMenu20handle_EndRotateLeftERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback2Fn,"_ZN8CPetMenu18handle_RotateRightERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback3Fn,"_ZN8CPetMenu21handle_EndRotateRightERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback4Fn,"_ZN8CPetMenu19handle_MouseThroughERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback5Fn,"_ZN8CPetMenu18handle_CloseButtonERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback6Fn,"_ZN8CPetMenu16handle_ItemClickERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback7Fn,"_ZN8CPetMenu15handle_MouseOutERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback8Fn,"_ZN8CPetMenu21handle_SpellMouseOverERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback9Fn,"_ZN8CPetMenu20handle_SpellMouseOutERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback10Fn,"_ZN8CPetMenu16handle_MouseOverERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback11Fn,"_ZN8CPetMenu15handle_SetSpellERKN5CEGUI9EventArgsE")
namespace {
struct Stop {};
struct Case { int width,height; bool replace; float ratio;unsigned faultSubscription;unsigned iconPattern; };
autotest::Capture* cap; CPetMenu* menu; const Case* cs;
unsigned long long pool[1200][(sizeof(CEGUI::Window)+7)/8];unsigned poolCount;void* eventVtable[8];std::map<std::string,CEGUI::Window*> names;CEGUI::UVector2 sizes[1200],positions[1200];unsigned uniqueCount;bool initialFlags;Ogre::Camera* camera;CEGUI::String* tooltipValue;CEGUI::Window* externalRoot;unsigned connectionCount;unsigned refCounts[1200];unsigned long long connectionObjects[1200][4];
int wid(const CEGUI::Window* p){for(unsigned i=0;i<poolCount;++i)if(p==(CEGUI::Window*)pool[i])return i+1;return p?999:-1;}
std::string key(const CEGUI::String& s){std::string k;for(unsigned i=0;i<s.length();++i)k+=char(s[i]);return k;}
CEGUI::Window* window(const std::string& name,CEGUI::Window* parent){std::map<std::string,CEGUI::Window*>::iterator i=names.find(name);if(i!=names.end())return i->second;if(poolCount==1200)_exit(43);CEGUI::Window* w=(CEGUI::Window*)pool[poolCount++];new(&w->d_children) std::vector<CEGUI::Window*>;w->d_parent=parent;*(void***)(static_cast<CEGUI::EventSet*>(w))=eventVtable;names[name]=w;w->d_riseOnClick=initialFlags;w->d_mousePassThroughEnabled=initialFlags;w->d_wantsMultiClicks=initialFlags;w->d_muted=initialFlags;w->d_alwaysOnTop=initialFlags;w->d_zOrderingEnabled=initialFlags;sizes[poolCount-1]=CEGUI::UVector2(CEGUI::UDim(0.25f,40+poolCount),CEGUI::UDim(0.5f,50+poolCount));positions[poolCount-1]=CEGUI::UVector2(CEGUI::UDim(0,(initialFlags?-1.0f:1.0f)*(3+poolCount)),CEGUI::UDim(0,(initialFlags?-1.0f:1.0f)*(7+poolCount)));return w;}
CEGUI::Window* sheet; CEGUI::Imageset* imageSet; CFileSystem* fs;
Ogre::MeshPtr* meshRef; CGenericModel* model; Ogre::Entity* entity; Ogre::Mesh* mesh;
CDynamicPropertyFile* first; CDynamicPropertyFile* second; unsigned calls;
void number(int x){cap->add(&x,sizeof(x));}
int getInt(CDynamicPropertyFile* p,unsigned key){number(1);number(p==first?1:p==second?2:99);number(key);++calls;if(calls==1&&cs->replace)menu->m_pDynamicPropertyFile=second;return calls==1?cs->width:cs->height;}
CGenericModel* create(CResourceManager* r,Ogre::SceneManager* s,const wchar_t* a,const wchar_t* b,bool x,bool y,bool z){number(2);number(r==menu->m_pResourceManager);number(s==menu->m_pPetSceneManager);for(unsigned i=0;i<1024;++i){number(a[i]);if(!a[i])break;}number(-7);for(unsigned i=0;i<1024;++i){number(b[i]);if(!b[i])break;}number(x);number(y);number(z);return model;}
float getFloat(CDynamicPropertyFile* p,unsigned key){number(3);number(p==first?1:p==second?2:99);number(key);return cs->ratio;}
const Ogre::MeshPtr& getMesh(const Ogre::Entity* p){number(4);number(p==entity);return *meshRef;}
void bounds(Ogre::Mesh* p,const Ogre::AxisAlignedBox& b,bool pad){number(5);number(p==mesh);cap->add(&b.getMinimum(),sizeof(Ogre::Vector3));cap->add(&b.getMaximum(),sizeof(Ogre::Vector3));number(b.isNull());number(b.isInfinite());number(pad);}
void position(CGenericModel* p,float x,float y,float z){number(6);number(p==model);cap->add(&x,4);cap->add(&y,4);cap->add(&z,4);}
void visible(CGenericModel* p,bool v){number(7);number(p==model);number(v);}
void text(const CEGUI::String& s){number(s.length());for(unsigned i=0;i<s.length();++i){unsigned c=s[i];do{unsigned char b=c&127;c>>=7;if(c)b|=128;cap->add(&b,1);}while(c);}}
CEGUI::Imageset* getImageset(const CEGUI::ImagesetManager*,const CEGUI::String& s){number(8);text(s);return imageSet;}
CEGUI::Window* makeWindow(CEGUI::WindowManager*,const CEGUI::String& a,const CEGUI::String& b,const CEGUI::String& c){number(9);text(a);text(b);text(c);CEGUI::Window* w=window(key(b),0);if(!sheet)sheet=w;return w;}
void sizeWindow(CEGUI::Window* p,const CEGUI::UVector2& v){number(10);number(wid(p));cap->add(&v,sizeof(v));sizes[wid(p)-1]=v;}
void posWindow(CEGUI::Window* p,const CEGUI::UVector2& v){number(11);number(wid(p));cap->add(&v,sizeof(v));positions[wid(p)-1]=v;}
void property(CEGUI::PropertySet* p,const CEGUI::String& k,const CEGUI::String& v){number(12);number(wid(static_cast<CEGUI::Window*>(p)));text(k);text(v);if(k=="RiseOnClick")static_cast<CEGUI::Window*>(p)->d_riseOnClick=(v=="True");}
void zWindow(CEGUI::Window* p,bool x){number(13);number(wid(p));number(x);p->d_zOrderingEnabled=x;}
// Canonicalize only known original/replacement identities; retain the full
// member-pointer this-adjustment. Different handlers remain distinguishable.
void captureCallback(const CEGUI::MemberFunctionSlot<CPetMenu>* slot){
 intptr_t words[2];typedef char check_member_pointer[sizeof(slot->d_function)==sizeof(words)?1:-1];
 std::memcpy(words,&slot->d_function,sizeof(words));
 char* pairs[][2]={{callback0Fn_original,callback0Fn_linked},{callback1Fn_original,callback1Fn_linked},{callback2Fn_original,callback2Fn_linked},{callback3Fn_original,callback3Fn_linked},{callback4Fn_original,callback4Fn_linked},{callback5Fn_original,callback5Fn_linked},{callback6Fn_original,callback6Fn_linked},{callback7Fn_original,callback7Fn_linked},{callback8Fn_original,callback8Fn_linked},{callback9Fn_original,callback9Fn_linked},{callback10Fn_original,callback10Fn_linked},{callback11Fn_original,callback11Fn_linked}};
 for(unsigned i=0;i<12;++i)if(words[0]==(intptr_t)pairs[i][0]||words[0]==(intptr_t)pairs[i][1]){words[0]=(intptr_t)pairs[i][0];break;}
 cap->add(words,sizeof(words));
}
CEGUI::Event::Connection subscribe(CEGUI::EventSet* p,const CEGUI::String& name,CEGUI::Event::Subscriber sub){number(14);number(wid(static_cast<CEGUI::Window*>(p)));text(name);CEGUI::MemberFunctionSlot<CPetMenu>* f=static_cast<CEGUI::MemberFunctionSlot<CPetMenu>*>(sub.d_functor_impl);captureCallback(f);number(f->d_object==menu);if(cs->faultSubscription==connectionCount+1)throw Stop();number(34);unsigned outstanding=0;for(unsigned i=0;i<connectionCount;++i)outstanding+=refCounts[i]-1;number(outstanding);number(connectionCount?refCounts[connectionCount-1]:0);if(connectionCount==1200)_exit(44);unsigned k=connectionCount++;refCounts[k]=2;CEGUI::Event::Connection result;result.d_object=(CEGUI::BoundSlot*)connectionObjects[k];result.d_count=&refCounts[k];return result;}
CFileSystem* filesystem(){number(15);return fs;}
void file(CFileSystem* p,const std::wstring& path,CFileInfo& info,bool a,bool b,bool c){number(16);number(p==fs);number(path.size());for(unsigned i=0;i<path.size();++i)number(path[i]);number(info.m_eFormat);number(info.m_eLocation);number(info.m_bExists);number(a);number(b);number(c);info.m_sResourceName="resolved-layout";info.m_sPath=L"resolved-path";}
CEGUI::Window* load(CEGUI::WindowManager*,const CEGUI::String& name,bool v){number(17);text(name);number(v);return window("@root",0);}
CEGUI::Window* search(const CEGUI::Window* p,const CEGUI::String& name){number(18);number(wid(p));text(name);if(key(name).find("FixtureEquip")==0&&(cs->iconPattern==4||cs->iconPattern==5&&key(name).find("3")!=std::string::npos))return 0;char buf[32];std::sprintf(buf,"%d/",wid(p));return window(std::string(buf)+key(name),const_cast<CEGUI::Window*>(p));}
void remove(CEGUI::Window* p,CEGUI::Window* c){number(19);number(wid(p));number(wid(c));c->d_parent=0;}
void add(CEGUI::Window* p,CEGUI::Window* c){number(20);number(wid(p));number(wid(c));c->d_parent=p;}
void front(CEGUI::Window* p){number(21);number(wid(p));}
void back(CEGUI::Window* p){number(22);number(wid(p));}
CEGUI::UVector2 size(const CEGUI::Window* p){number(23);number(wid(p));return sizes[wid(p)-1];}
void mute(CEGUI::EventSet* p,bool b){number(24);number(wid(static_cast<CEGUI::Window*>(p)));number(b);p->d_muted=b;}
void visibleWindow(CEGUI::Window* p,bool b){number(25);number(wid(p));number(b);}
void convert(CGameUI* p,CEGUI::Window* w,bool b){number(26);number(p==menu->m_pGameUI);number(wid(w));number(b);}
void mapping(CGameUI* p,CEGUI::Window* w){number(27);number(p==menu->m_pGameUI);number(wid(w));}
// Exercise the actual mapper on both sides, including flattened calls.
// This controlled layout has no onClick properties; PetMenuMapTest covers populated trees.
bool propertyPresent(const CEGUI::PropertySet* p,const CEGUI::String& k){number(28);number(wid(static_cast<const CEGUI::Window*>(p)));text(k);return false;}
std::string unique(const std::string& s){number(29);number(s.size());cap->add(s.data(),s.size());char buf[32];std::sprintf(buf,"%u",++uniqueCount);return s+buf;}
const CEGUI::UVector2& positionWindow(const CEGUI::Window* p){number(30);number(wid(p));return positions[wid(p)-1];}
void font(CEGUI::Window* p,const CEGUI::String& value){number(31);number(wid(p));text(value);}
void textWindow(CEGUI::Window* p,const CEGUI::String& value){number(32);number(wid(p));text(value);}
void top(CEGUI::Window* p,bool value){number(33);number(wid(p));number(value);p->d_alwaysOnTop=value;}
void extremes(CGenericModel* p,unsigned long count,bool value){number(35);number(p==model);number(count);number(value);}
CEGUI::String getProperty(const CEGUI::PropertySet* p,const CEGUI::String& k){number(36);number(wid(static_cast<const CEGUI::Window*>(p)));text(k);std::string value=key(k)+(initialFlags?" long-long-long-long-long-long-long-long-value":" short");return CEGUI::String(value.c_str());}
const CEGUI::String& getTooltip(const CEGUI::Window* p){number(37);number(wid(p));return *tooltipValue;}
void setId(CEGUI::Window* p,unsigned value){number(38);number(wid(p));number(value);p->d_ID=value;}
Ogre::Camera* createCamera(Ogre::SceneManager* p,const std::string& name){number(39);number(p==menu->m_pWardrobeSceneManager);number(name.size());cap->add(name.data(),name.size());return camera;}
void cameraPosition(Ogre::Camera* p,const Ogre::Vector3& v){number(40);number(p==camera);cap->add(&v,sizeof(v));}
void cameraLook(Ogre::Camera* p,const Ogre::Vector3& v){number(41);number(p==camera);cap->add(&v,sizeof(v));}
void nearClip(Ogre::Camera* p,float v){number(42);number(p==camera);cap->add(&v,sizeof(v));}
void farClip(Ogre::Camera* p,float v){number(43);number(p==camera);cap->add(&v,sizeof(v));}
void tooltipLoad(CSkillTooltip* p,CGameUI* ui,std::wstring path){number(44);number(p==menu->m_pSkillTooltip);number(ui==menu->m_pGameUI);cap->addText(path);number(p->m_pGameUI==ui);cap->addText(p->m_sText);number(p->m_iIndex);number(p->m_pRoot==externalRoot);}
void side(const Case& c,bool ours,autotest::Capture& out){
 unsigned long long mem[(sizeof(CPetMenu)+7)/8]={0},properties[2][64]={{0}},resource[8]={0},scene[8]={0};
 unsigned long long modelMem[(sizeof(CGenericModel)+7)/8]={0},entityMem[16]={0},meshMem[16]={0};
 void* table[64]={0};table[10]=(void*)&visible;table[11]=(void*)&position;
 model=(CGenericModel*)modelMem;*(void***)model=table;entity=(Ogre::Entity*)entityMem;mesh=(Ogre::Mesh*)meshMem;model->m_pEntity=entity;
 unsigned long long windowMem[(sizeof(CGameUI)+7)/8]={0},managerMem[128]={0},imageMem[128]={0},fsMem[128]={0};
 std::memset(pool,0,sizeof(pool));poolCount=0;uniqueCount=0;initialFlags=c.replace;connectionCount=0;new(&names)std::map<std::string,CEGUI::Window*>;sheet=0;eventVtable[2]=(void*)&subscribe;imageSet=(CEGUI::Imageset*)imageMem;fs=(CFileSystem*)fsMem;
 CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton=(CEGUI::WindowManager*)managerMem;CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton=(CEGUI::ImagesetManager*)managerMem;

 Ogre::MeshPtr shared;shared.pRep=mesh;meshRef=&shared;
 cap=&out;cs=&c;calls=0;menu=(CPetMenu*)mem;first=(CDynamicPropertyFile*)properties[0];second=(CDynamicPropertyFile*)properties[1];menu->m_pGameUI=(CGameUI*)windowMem;menu->m_pDynamicPropertyFile=first;menu->m_pResourceManager=(CResourceManager*)resource;menu->m_pPetSceneManager=(Ogre::SceneManager*)scene;
 CEGUI::String localTooltip(initialFlags?"tooltip long-long-long-long-long-long-long-long-value":"tooltip");tooltipValue=&localTooltip;
 for(int i=0;i<82;++i){new(&menu->m_DefaultSlotImages[i])CEGUI::String("before image");new(&menu->m_DefaultSlotTooltips[i])CEGUI::String("before tooltip");}
 for(int i=0;i<3;++i){new(&menu->m_TabUnselectedImages[i])CEGUI::String("before tab");new(&menu->m_TabSelectedImages[i])CEGUI::String("before selected");}
 for(int i=0;i<1000;++i)menu->m_aiSlotData[i]=10000+i;
 for(int i=0;i<99;++i)menu->m_SpellGuids[i]=-10000-i;menu->m_NoSpell=-10099;
 for(int i=0;i<12;++i)menu->m_pMainUnidentifiedWindows[i]=(CEGUI::Window*)windowMem;
 // TU-specific original array, pinned by the original ELF hash and STT_FILE.
 std::string* iconNames=reinterpret_cast<std::string*>(0x14cc220);
 for(int i=0;i<12;++i){char name[40];std::sprintf(name,c.iconPattern==3?"FixtureEquip\xc3\xa9%d":"FixtureEquip%d",i);bool empty=c.iconPattern==1||(c.iconPattern==2&&i%2)||(c.iconPattern==0&&i==11);new(&iconNames[i])std::string(empty?"":name);}
 unsigned long long wardrobeMem[8]={0},cameraMem[8]={0};void* sceneTable[128]={0};sceneTable[0x1a8/8]=(void*)&createCamera;*(void***)wardrobeMem=sceneTable;menu->m_pWardrobeSceneManager=(Ogre::SceneManager*)wardrobeMem;
 void* cameraTable[128]={0};cameraTable[0x258/8]=(void*)&nearClip;cameraTable[0x268/8]=(void*)&farClip;*(void***)cameraMem=cameraTable;camera=(Ogre::Camera*)cameraMem;externalRoot=(CEGUI::Window*)windowMem;*(CEGUI::Window**)((char*)windowMem+0x488)=externalRoot;
 detour::Set extras;TL_REDIRECT(extras,extremesFn,&extremes);TL_REDIRECT(extras,tooltipLoadFn,&tooltipLoad);extras.redirect(getPropertyFn,getPropertyFn,&getProperty);extras.redirect(getTooltipFn,getTooltipFn,&getTooltip);extras.redirect(setIdFn,setIdFn,&setId);extras.redirect(cameraPositionFn,cameraPositionFn,&cameraPosition);extras.redirect(cameraLookFn,cameraLookFn,&cameraLook);if(extras.failed())_exit(42);
 detour::Set redirects;TL_REDIRECT(redirects,propInt,&getInt);TL_REDIRECT(redirects,modelCreate,&create);TL_REDIRECT(redirects,propFloat,&getFloat);redirects.redirect(meshGet,meshGet,&getMesh);redirects.redirect(meshBounds,meshBounds,&bounds);redirects.redirect(imageGet,imageGet,&getImageset);redirects.redirect(windowCreate,windowCreate,&makeWindow);redirects.redirect(windowSize,windowSize,&sizeWindow);redirects.redirect(windowPosition,windowPosition,&posWindow);redirects.redirect(windowProperty,windowProperty,&property);redirects.redirect(windowZ,windowZ,&zWindow);TL_REDIRECT(redirects,fileSingleton,&filesystem);TL_REDIRECT(redirects,fileInfo,&file);redirects.redirect(loadLayout,loadLayout,&load);redirects.redirect(searchChild,searchChild,&search);redirects.redirect(removeChild,removeChild,&remove);redirects.redirect(addChild,addChild,&add);redirects.redirect(moveFront,moveFront,&front);redirects.redirect(moveBack,moveBack,&back);redirects.redirect(sizeGet,sizeGet,&size);redirects.redirect(mutedSet,mutedSet,&mute);redirects.redirect(visibleSet,visibleSet,&visibleWindow);TL_REDIRECT(redirects,convertScale,&convert);TL_REDIRECT(redirects,mapFuncs,&mapping);redirects.redirect(propertyPresentFn,propertyPresentFn,&propertyPresent);TL_REDIRECT(redirects,uniqueNames,&unique);redirects.redirect(positionGet,positionGet,&positionWindow);redirects.redirect(fontSet,fontSet,&font);redirects.redirect(textSet,textSet,&textWindow);redirects.redirect(topSet,topSet,&top);if(redirects.failed())_exit(42);
 try {if(ours)autotest::invoke(out,&candidateCreate,menu);else autotest::invoke(out,&originalCreate,menu);number(900);}catch(const Stop&){number(901);}catch(...){number(902);}
 shared.pRep=0;number(calls);number(menu->m_pImageset==imageSet);number(menu->m_pBackground==sheet);number(sheet?sheet->d_mousePassThroughEnabled:-1);
 for(unsigned i=0;i<1000;++i)number(menu->m_aiSlotData[i]);
 for(unsigned i=0;i<99;++i)number(menu->m_SpellGuids[i]);number(menu->m_NoSpell);
 for(unsigned offset=0x20;offset<=0x48;offset+=8){CEGUI::Window* value=0;std::memcpy(&value,(char*)menu+offset,8);number(wid(value));}
 for(unsigned offset=0x1378;offset<0x2048;offset+=8){CEGUI::Window* w=0;std::memcpy(&w,((char*)menu)+offset,8);number(wid(w));}
 for(int i=0;i<82;++i){text(menu->m_DefaultSlotImages[i]);text(menu->m_DefaultSlotTooltips[i]);}for(int i=0;i<3;++i){text(menu->m_TabUnselectedImages[i]);text(menu->m_TabSelectedImages[i]);}for(int i=0;i<2;++i){number(wid(menu->m_pSpellWindows[i]));number(menu->m_pSpellWindows[i]?menu->m_pSpellWindows[i]->d_ID:-1);}
 for(unsigned offset=0x9110;offset<0x9160;offset+=8){CEGUI::Window* value=0;std::memcpy(&value,(char*)menu+offset,8);number(wid(value));}
 number(connectionCount);for(unsigned i=0;i<connectionCount;++i)number(refCounts[i]);number(poolCount);for(unsigned i=0;i<poolCount;++i){CEGUI::Window* w=(CEGUI::Window*)pool[i];number(wid(w->d_parent));number(w->d_mousePassThroughEnabled);number(w->d_riseOnClick);number(w->d_wantsMultiClicks);number(w->d_muted);number(w->d_alwaysOnTop);number(w->d_zOrderingEnabled);intptr_t data=(intptr_t)w->d_userData;intptr_t start=(intptr_t)&menu->m_aiSlotData[0];number(!data?-1:(data>=start&&data<start+4000)?(data-start)/4:-999);}

}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
}
TL_TEST(pet_create_menus_differential){
 int bad=0;unsigned total=0;autotest::Coverage coverage("pet_create_menus_differential",(uint64_t)(uintptr_t)&originalCreate);const int values[]={0,1,1920,1080,-1,2147483647,(-2147483647-1)};
 const float ratios[]={0.0f,0.75f,1.0f,-1.0f,-0.0f,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};
 for(unsigned q=0;q<8;++q)for(unsigned x=0;x<7;++x)for(unsigned y=0;y<7;++y)for(unsigned change=0;change<2;++change)for(unsigned pattern=0;pattern<6;++pattern){Case c={values[x],values[y],bool(change),ratios[q],0,pattern};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);++total;bool ok=pair==0&&u.capture.callStarted&&v.capture.callStarted&&u.capture.callCompleted&&v.capture.callCompleted&&u.reportValid&&v.reportValid&&u.childStatus==0&&v.childStatus==0&&u.capture.issue==0&&v.capture.issue==0&&u.capture.length>100&&u.capture.length==v.capture.length&&!std::memcmp(u.capture.data,v.capture.data,u.capture.length);if(!ok){++bad;if(bad==1){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    FIRST BYTE DIFFERENCE %lu\n",(unsigned long)f);for(size_t k=f/4>12?f/4-12:0;k<f/4+30;++k){unsigned ua=0,va=0;if(k*4+4<=u.capture.length)std::memcpy(&ua,u.capture.data+k*4,4);if(k*4+4<=v.capture.length)std::memcpy(&va,v.capture.data+k*4,4);host->log("    word %lu: %u / %u\n",(unsigned long)k,ua,va);}}host->log("    prefix %u/%u/%u exits %d/%d lengths %lu/%lu\n",x,y,change,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);host->log("    FULL BODY COMPARISON: %u cases, %d differences; bounded UI spies with connection lifetime observation; controlled collaborators\n",total,bad);return bad;
}
