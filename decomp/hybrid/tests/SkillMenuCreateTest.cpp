// Original-versus-compiled Skill-menu creation fixture; collaborators are controlled.
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
#include "SkillMenu.h"
#include "SkillTooltip.h"
#undef protected
#undef private
#include "DynamicPropertyFile.h"
#include "ResourceManager.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalCreate, (CSkillMenu*), "_ZN10CSkillMenu11createMenusEv")
extern "C" void candidateCreate(CSkillMenu*) __asm__("_ZN10CSkillMenu11createMenusEv");
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
TL_FUNCTION(mapHandlers,"_ZN10CSkillMenu16mapEventHandlersEPN5CEGUI6WindowE")
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
TL_FUNCTION(callback0Fn,"_ZN10CSkillMenu19handle_MouseThroughERKN5CEGUI9EventArgsE")
TL_FUNCTION(callback1Fn,"_ZN10CSkillMenu18handle_CloseButtonERKN5CEGUI9EventArgsE")
namespace {
struct Stop {};
struct Case { int width,height; bool replace; float ratio;unsigned faultSubscription;unsigned pathPattern; };
autotest::Capture* cap; CSkillMenu* menu; const Case* cs; std::string* resourceValue; std::wstring* pathValue;
unsigned long long pool[1200][(sizeof(CEGUI::Window)+7)/8];unsigned poolCount;void* eventVtable[8];std::map<std::string,CEGUI::Window*> names;CEGUI::UVector2 sizes[1200],positions[1200];unsigned uniqueCount;bool initialFlags;Ogre::Camera* camera;CEGUI::String* tooltipValue;CEGUI::Window* externalRoot;unsigned connectionCount;unsigned refCounts[1200];unsigned long long connectionObjects[1200][4];
int wid(const CEGUI::Window* p){for(unsigned i=0;i<poolCount;++i)if(p==(CEGUI::Window*)pool[i])return i+1;return p?999:-1;}
std::string key(const CEGUI::String& s){std::string k;for(unsigned i=0;i<s.length();++i)k+=char(s[i]);return k;}
CEGUI::Window* window(const std::string& name,CEGUI::Window* parent){std::map<std::string,CEGUI::Window*>::iterator i=names.find(name);if(i!=names.end())return i->second;if(poolCount==1200)_exit(43);CEGUI::Window* w=(CEGUI::Window*)pool[poolCount++];w->d_parent=parent;*(void***)(static_cast<CEGUI::EventSet*>(w))=eventVtable;names[name]=w;w->d_riseOnClick=initialFlags;w->d_mousePassThroughEnabled=initialFlags;w->d_wantsMultiClicks=initialFlags;w->d_muted=initialFlags;w->d_alwaysOnTop=initialFlags;w->d_zOrderingEnabled=initialFlags;sizes[poolCount-1]=CEGUI::UVector2(CEGUI::UDim(0.25f,40+poolCount),CEGUI::UDim(0.5f,50+poolCount));positions[poolCount-1]=CEGUI::UVector2(CEGUI::UDim(0,(initialFlags?-1.0f:1.0f)*(3+poolCount)),CEGUI::UDim(0,(initialFlags?-1.0f:1.0f)*(7+poolCount)));return w;}
CEGUI::Window* sheet; CEGUI::Imageset* imageSet; CFileSystem* fs;
Ogre::MeshPtr* meshRef; CGenericModel* model; Ogre::Entity* entity; Ogre::Mesh* mesh;
CDynamicPropertyFile* first; CDynamicPropertyFile* second; unsigned calls;
void number(int x){cap->add(&x,sizeof(x));}
int getInt(CDynamicPropertyFile* p,unsigned key){number(1);number(p==first?1:p==second?2:99);number(key);++calls;if(calls==1&&cs->replace)menu->m_pProperties=second;return calls==1?cs->width:cs->height;}
CGenericModel* create(CResourceManager* r,Ogre::SceneManager* s,const wchar_t* a,const wchar_t* b,bool x,bool y,bool z){number(2);number(r==menu->m_pResourceManager);number(s==menu->m_pSceneManager);for(unsigned i=0;i<1024;++i){number(a[i]);if(!a[i])break;}number(-7);for(unsigned i=0;i<1024;++i){number(b[i]);if(!b[i])break;}number(x);number(y);number(z);return model;}
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
void captureCallback(const CEGUI::MemberFunctionSlot<CSkillMenu>* slot){
 intptr_t words[2];typedef char check_member_pointer[sizeof(slot->d_function)==sizeof(words)?1:-1];
 std::memcpy(words,&slot->d_function,sizeof(words));
 char* pairs[][2]={{callback0Fn_original,callback0Fn_linked},{callback1Fn_original,callback1Fn_linked}};
 for(unsigned i=0;i<2;++i)if(words[0]==(intptr_t)pairs[i][0]||words[0]==(intptr_t)pairs[i][1]){words[0]=(intptr_t)pairs[i][0];break;}
 cap->add(words,sizeof(words));
}
CEGUI::Event::Connection subscribe(CEGUI::EventSet* p,const CEGUI::String& name,CEGUI::Event::Subscriber sub){number(14);number(wid(static_cast<CEGUI::Window*>(p)));text(name);CEGUI::MemberFunctionSlot<CSkillMenu>* f=static_cast<CEGUI::MemberFunctionSlot<CSkillMenu>*>(sub.d_functor_impl);captureCallback(f);number(f->d_object==menu);if(cs->faultSubscription==connectionCount+1)throw Stop();number(34);unsigned outstanding=0;for(unsigned i=0;i<connectionCount;++i)outstanding+=refCounts[i]-1;number(outstanding);number(connectionCount?refCounts[connectionCount-1]:0);if(connectionCount==1200)_exit(44);unsigned k=connectionCount++;refCounts[k]=2;CEGUI::Event::Connection result;result.d_object=(CEGUI::BoundSlot*)connectionObjects[k];result.d_count=&refCounts[k];return result;}
CFileSystem* filesystem(){number(15);return fs;}
void file(CFileSystem* p,const std::wstring& path,CFileInfo& info,bool a,bool b,bool c){number(16);number(p==fs);number(path.size());for(unsigned i=0;i<path.size();++i)number(path[i]);number(info.m_eFormat);number(info.m_eLocation);number(info.m_bExists);number(a);number(b);number(c);info.m_sResourceName = *resourceValue;info.m_sPath=*pathValue;}
CEGUI::Window* load(CEGUI::WindowManager*,const CEGUI::String& name,bool v){number(17);text(name);number(v);return window("@root",0);}
CEGUI::Window* search(const CEGUI::Window* p,const CEGUI::String& name){number(18);number(wid(p));text(name);char buf[32];std::sprintf(buf,"%d/",wid(p));return window(std::string(buf)+key(name),const_cast<CEGUI::Window*>(p));}
void remove(CEGUI::Window* p,CEGUI::Window* c){number(19);number(wid(p));number(wid(c));c->d_parent=0;}
void add(CEGUI::Window* p,CEGUI::Window* c){number(20);number(wid(p));number(wid(c));c->d_parent=p;}
void front(CEGUI::Window* p){number(21);number(wid(p));}
void back(CEGUI::Window* p){number(22);number(wid(p));}
CEGUI::UVector2 size(const CEGUI::Window* p){number(23);number(wid(p));return sizes[wid(p)-1];}
void mute(CEGUI::EventSet* p,bool b){number(24);number(wid(static_cast<CEGUI::Window*>(p)));number(b);p->d_muted=b;}
void visibleWindow(CEGUI::Window* p,bool b){number(25);number(wid(p));number(b);}
void convert(CGameUI* p,CEGUI::Window* w,bool b){number(26);number(p==menu->m_pGameUI);number(wid(w));number(b);}
void mapping(CGameUI* p,CEGUI::Window* w){number(27);number(p==menu->m_pGameUI);number(wid(w));}
void handlers(CSkillMenu* p,CEGUI::Window* w){number(28);number(p==menu);number(wid(w));}
std::string unique(const std::string& s){number(29);number(s.size());cap->add(s.data(),s.size());char buf[32];std::sprintf(buf,"%u",++uniqueCount);return s+buf;}
const CEGUI::UVector2& positionWindow(const CEGUI::Window* p){number(30);number(wid(p));return positions[wid(p)-1];}
void font(CEGUI::Window* p,const CEGUI::String& value){number(31);number(wid(p));text(value);}
void textWindow(CEGUI::Window* p,const CEGUI::String& value){number(32);number(wid(p));text(value);}
void top(CEGUI::Window* p,bool value){number(33);number(wid(p));number(value);p->d_alwaysOnTop=value;}
void extremes(CGenericModel* p,unsigned long count,bool value){number(35);number(p==model);number(count);number(value);}
CEGUI::String getProperty(const CEGUI::PropertySet* p,const CEGUI::String& k){number(36);number(wid(static_cast<const CEGUI::Window*>(p)));text(k);std::string value=key(k)+(initialFlags?" long-long-long-long-long-long-long-long-value":" short");return CEGUI::String(value.c_str());}
const CEGUI::String& getTooltip(const CEGUI::Window* p){number(37);number(wid(p));return *tooltipValue;}
void setId(CEGUI::Window* p,unsigned value){number(38);number(wid(p));number(value);p->d_ID=value;}
void cameraPosition(Ogre::Camera* p,const Ogre::Vector3& v){number(40);number(p==camera);cap->add(&v,sizeof(v));}
void cameraLook(Ogre::Camera* p,const Ogre::Vector3& v){number(41);number(p==camera);cap->add(&v,sizeof(v));}
void nearClip(Ogre::Camera* p,float v){number(42);number(p==camera);cap->add(&v,sizeof(v));}
void farClip(Ogre::Camera* p,float v){number(43);number(p==camera);cap->add(&v,sizeof(v));}
void tooltipLoad(CSkillTooltip* p,CGameUI* ui,std::wstring path){number(44);number(p==menu->m_pTooltip);number(ui==menu->m_pGameUI);cap->addText(path);number(p->m_pGameUI==ui);cap->addText(p->m_sText);number(p->m_iIndex);number(p->m_pRoot==externalRoot);if(cs->faultSubscription==3)throw Stop();}

extern "C" char radioSelected[] __asm__("_ZN5CEGUI11RadioButton11setSelectedEb");
bool selected[1200],shown[1200];
void selectRadio(CEGUI::RadioButton* p,bool b){number(45);number(wid(p));number(b);selected[wid(p)-1]=b;}
void showWindow(CEGUI::Window* p,bool b){visibleWindow(p,b);shown[wid(p)-1]=b;}
void pointerField(unsigned char* snapshot,unsigned offset,int value){uintptr_t canonical=static_cast<uintptr_t>(value);std::memcpy(snapshot+offset,&canonical,sizeof(canonical));}
void side(const Case& c,bool ours,autotest::Capture& out){
 unsigned long long mem[(sizeof(CSkillMenu)+7)/8],properties[2][64]={{0}},resource[8]={0},scene[8]={0};
 std::memset(mem,c.replace?0x5a:0xa5,sizeof(mem));
 unsigned long long modelMem[(sizeof(CGenericModel)+7)/8]={0},entityMem[16]={0},meshMem[16]={0};
 void* table[64]={0};table[10]=(void*)&visible;table[11]=(void*)&position;
 model=(CGenericModel*)modelMem;*(void***)model=table;entity=(Ogre::Entity*)entityMem;mesh=(Ogre::Mesh*)meshMem;model->m_pEntity=entity;
 unsigned long long windowMem[(sizeof(CGameUI)+7)/8]={0},managerMem[128]={0},imageMem[128]={0},fsMem[128]={0};
 std::memset(pool,0,sizeof(pool));poolCount=0;uniqueCount=0;initialFlags=c.replace;connectionCount=0;
 for(unsigned i=0;i<1200;++i){selected[i]=initialFlags;shown[i]=initialFlags;}
 new(&names)std::map<std::string,CEGUI::Window*>;sheet=0;eventVtable[2]=(void*)&subscribe;imageSet=(CEGUI::Imageset*)imageMem;fs=(CFileSystem*)fsMem;
 CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton=(CEGUI::WindowManager*)managerMem;
 CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton=(CEGUI::ImagesetManager*)managerMem;
 Ogre::MeshPtr shared;shared.pRep=mesh;meshRef=&shared;
 cap=&out;cs=&c;calls=0;std::string resourceSource=cs->pathPattern==1 ? std::string("long-layout-name-long-layout-name-long-layout-name") : cs->pathPattern==2 ? std::string("embedded\0tail",13) : cs->pathPattern==3 ? std::string("name\xc3\xa9.layout") : std::string("resolved-layout");std::wstring pathSource=L"resolved-path-for-lifetime-observation";resourceValue=&resourceSource;pathValue=&pathSource;menu=(CSkillMenu*)mem;first=(CDynamicPropertyFile*)properties[0];second=(CDynamicPropertyFile*)properties[1];
 menu->m_pGameUI=(CGameUI*)windowMem;menu->m_pProperties=first;menu->m_pResourceManager=(CResourceManager*)resource;menu->m_pSceneManager=(Ogre::SceneManager*)scene;
 externalRoot=(CEGUI::Window*)windowMem;*(CEGUI::Window**)((char*)windowMem+0x488)=externalRoot;
 detour::Set redirects;
 TL_REDIRECT(redirects,propInt,&getInt);TL_REDIRECT(redirects,modelCreate,&create);TL_REDIRECT(redirects,propFloat,&getFloat);
 redirects.redirect(meshGet,meshGet,&getMesh);redirects.redirect(meshBounds,meshBounds,&bounds);redirects.redirect(imageGet,imageGet,&getImageset);
 redirects.redirect(windowCreate,windowCreate,&makeWindow);redirects.redirect(windowSize,windowSize,&sizeWindow);redirects.redirect(windowPosition,windowPosition,&posWindow);
 redirects.redirect(windowProperty,windowProperty,&property);redirects.redirect(windowZ,windowZ,&zWindow);
 TL_REDIRECT(redirects,fileSingleton,&filesystem);TL_REDIRECT(redirects,fileInfo,&file);
 redirects.redirect(loadLayout,loadLayout,&load);redirects.redirect(searchChild,searchChild,&search);redirects.redirect(removeChild,removeChild,&remove);redirects.redirect(addChild,addChild,&add);
 redirects.redirect(moveFront,moveFront,&front);redirects.redirect(moveBack,moveBack,&back);redirects.redirect(visibleSet,visibleSet,&showWindow);
 redirects.redirect(radioSelected,radioSelected,&selectRadio);
 TL_REDIRECT(redirects,convertScale,&convert);TL_REDIRECT(redirects,mapFuncs,&mapping);TL_REDIRECT(redirects,mapHandlers,&handlers);
 TL_REDIRECT(redirects,extremesFn,&extremes);TL_REDIRECT(redirects,tooltipLoadFn,&tooltipLoad);
 if(redirects.failed())_exit(42);
 bool threw=false;try{if(ours)autotest::invoke(out,&candidateCreate,menu);else autotest::invoke(out,&originalCreate,menu);}catch(const Stop&){threw=true;}catch(...){_exit(55);}
 number(threw?901:900);int resourceRefs=99,pathRefs=99;std::memcpy(&resourceRefs,reinterpret_cast<const char*>(resourceSource.data())-8,4);std::memcpy(&pathRefs,reinterpret_cast<const char*>(pathSource.data())-8,4);number(resourceRefs);number(pathRefs);if(resourceRefs!=0||pathRefs!=0)_exit(56);shared.pRep=0;number(calls);
 unsigned char snapshot[sizeof(CSkillMenu)];std::memcpy(snapshot,menu,sizeof(snapshot));
 const unsigned windows[]={0x18,0x20,0x28,0x88,0x90,0x98,0xa0,0xa8,0xb0,0xb8,0xc0,0xc8,0xd0,0xd8};
 for(unsigned i=0;i<sizeof(windows)/sizeof(windows[0]);++i){CEGUI::Window* p;std::memcpy(&p,((char*)menu)+windows[i],sizeof(p));pointerField(snapshot,windows[i],wid(p));}
 pointerField(snapshot,0x48,menu->m_pProperties==first?1:menu->m_pProperties==second?2:99);
 pointerField(snapshot,0x50,menu->m_pGameUI==(CGameUI*)windowMem);
 pointerField(snapshot,0x58,menu->m_pSceneManager==(Ogre::SceneManager*)scene);
 pointerField(snapshot,0x60,menu->m_pModel==model);
 pointerField(snapshot,0x68,menu->m_pResourceManager==(CResourceManager*)resource);
 pointerField(snapshot,0x78,menu->m_pImages==imageSet);
 pointerField(snapshot,0x750,menu->m_pTooltip!=0);
 cap->add(snapshot,sizeof(snapshot));
 number(connectionCount);for(unsigned i=0;i<connectionCount;++i)number(refCounts[i]);
 number(poolCount);for(unsigned i=0;i<poolCount;++i){CEGUI::Window* p=(CEGUI::Window*)pool[i];number(wid(p->d_parent));number(p->d_mousePassThroughEnabled);number(p->d_riseOnClick);number(p->d_zOrderingEnabled);number(selected[i]);number(shown[i]);}
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
}
TL_TEST(skillmenu_create_menus_differential){
 autotest::Coverage coverage("skillmenu_create_menus_differential",(uint64_t)(uintptr_t)&originalCreate);
 const int values[]={0,1,1920,1080,-1,2147483647,(-2147483647-1)};
 const float ratios[]={0.0f,0.75f,1.0f,-1.0f,-0.0f,std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};
 unsigned total=0;
 for(unsigned q=0;q<8;++q)for(unsigned x=0;x<7;++x)for(unsigned y=0;y<7;++y)for(unsigned change=0;change<2;++change){
  Case c={values[x],values[y],bool(change),ratios[q],0,(q+x+y+change)%4};autotest::Outcome u,v;
  autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);++total;
  bool ok=pair==0&&u.capture.callStarted&&v.capture.callStarted&&u.capture.callCompleted&&v.capture.callCompleted&&u.reportValid&&v.reportValid&&u.childStatus==0&&v.childStatus==0&&u.capture.issue==0&&v.capture.issue==0&&u.capture.length>100&&u.capture.length==v.capture.length&&!std::memcmp(u.capture.data,v.capture.data,u.capture.length);
  if(!ok){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    FIRST BYTE DIFFERENCE %lu case %u/%u/%u/%u exit %d/%d size %lu/%lu\n",(unsigned long)f,q,x,y,change,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length);for(size_t k=f/4>8?f/4-8:0;k<f/4+20;++k){unsigned a=0,b=0;if(k*4+4<=u.capture.length)std::memcpy(&a,u.capture.data+k*4,4);if(k*4+4<=v.capture.length)std::memcpy(&b,v.capture.data+k*4,4);host->log("    word %lu: %u / %u\n",(unsigned long)k,a,b);}coverage.report(host);return 1;}
 }
 coverage.report(host);host->log("    FULL BODY COMPARISON: %u completed cases; full menu bytes, ordered calls, window state, member-pointer identities, connection lifetimes\n",total);return 0;
}

// Expected exceptions are supplemental unwind checks, not successful call coverage.
TL_TEST(skillmenu_create_expected_exceptions){
 unsigned total=0;
 for(unsigned fault=1;fault<=3;++fault)for(unsigned pattern=0;pattern<4;++pattern)for(unsigned change=0;change<2;++change){
  Case c={1920,1080,bool(change),0.75f,fault,pattern};autotest::Outcome u,v;
  autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);++total;
  bool ok=u.reportValid&&v.reportValid&&u.childStatus==0&&v.childStatus==0&&u.capture.callStarted==1&&v.capture.callStarted==1&&u.capture.callCompleted==0&&v.capture.callCompleted==0&&u.capture.issue==0&&v.capture.issue==0&&u.capture.callTarget==(uint64_t)(uintptr_t)&originalCreate&&host->comparison_pair&&host->comparison_pair(u.capture.callTarget,v.capture.callTarget)&&u.capture.length>100&&u.capture.length==v.capture.length&&!std::memcmp(u.capture.data,v.capture.data,u.capture.length);
  if(!ok){host->log("    UNWIND MISMATCH fault %u pattern %u flags %u exits %d/%d completed %u/%u lengths %lu/%lu\n",fault,pattern,change,u.childStatus,v.childStatus,u.capture.callCompleted,v.capture.callCompleted,(unsigned long)u.capture.length,(unsigned long)v.capture.length);return 1;}
 }
 host->log("    EXPECTED EXCEPTIONS: %u matching propagations, partial state and restored COW refcounts; excluded from normal completion coverage\n",total);return 0;
}
