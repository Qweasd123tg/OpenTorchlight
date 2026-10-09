#include <cstring>
#include <string>
#include <new>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include <OgreBone.h>
#include <OgreEntity.h>
#include <OgreSkeletonInstance.h>
#include <OgreUTFString.h>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreCamera.h>
#include "InventoryMenu.h"
#include "Character.h"
#include "GenericModel.h"
#include "SkillTooltip.h"
#include "SkillManager.h"
#include "SoundBank.h"
#include "DynamicPropertyFile.h"
#include "GameVariables.h"
#include "StringTranslate.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldUpdate,(CInventoryMenu*,float),"_ZN14CInventoryMenu6updateEf")
extern "C" void newUpdate(CInventoryMenu*,float) __asm__("_ZN14CInventoryMenu6updateEf");
TL_FUNCTION(settingsFn,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(convertFn,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(animationFn,"_ZN13CGenericModel15updateAnimationEfb")
TL_FUNCTION(modelPosFn,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(playingFn,"_ZNK13CGenericModel16animationPlayingERKSs")
TL_FUNCTION(queuedFn,"_ZNK13CGenericModel15animationQueuedERKSs")
TL_FUNCTION(scaledFn,"_ZN7CGameUI7scaledYEf")
TL_FUNCTION(translateSingletonFn,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateFn,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(skillFn,"_ZN13CSkillManager14getSkillByGuidEx")
TL_FUNCTION(showFn,"_ZN13CSkillTooltip11showTooltipEP9CBaseUnitP6CSkillff")
TL_FUNCTION(rotationFn,"_ZN4MATH15matrixRotationYERN4Ogre7Matrix4Ef")
extern "C" char textFn[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
extern "C" char propertyFn[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
extern "C" char getPropertyFn[] __asm__("_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE");
extern "C" char visibleFn[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" char isVisibleFn[] __asm__("_ZNK5CEGUI6Window9isVisibleEb");
extern "C" char positionFn[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char entityFn[] __asm__("_ZN4Ogre6Entity16_updateAnimationEv");
extern "C" char dimensionsFn[] __asm__("_ZN4Ogre8Viewport13setDimensionsEffff");
extern "C" char actualWidthFn[] __asm__("_ZNK4Ogre8Viewport14getActualWidthEv");
extern "C" char actualHeightFn[] __asm__("_ZNK4Ogre8Viewport15getActualHeightEv");
TL_FUNCTION(goldFn,"_ZN7STRINGS17GetValueAsWStringEi")
TL_FUNCTION(aliveFn,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(attackFn,"_ZN10CCharacter21performingAttackLooseEv")
TL_FUNCTION(skillLooseFn,"_ZN10CCharacter20performingSkillLooseEv")
TL_FUNCTION(toggleFn,"_ZN10CCharacter24toggleSecondaryWeaponSetEv")
TL_FUNCTION(soundFn,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
namespace {
struct Case {unsigned owner,state,layout,hover,profile,mutate,serial;};
autotest::Capture* cap;const Case* input;CInventoryMenu* menu;CCharacter* actors[2];CGenericModel* model;Ogre::Entity* entity;Ogre::SkeletonInstance* skeleton;Ogre::Bone* bones[3];CPositionableObject* actorModels[2];Ogre::Matrix4 orientations[2];Ogre::Vector3 tags[3];CGameUI* uis[2];Ogre::Viewport* viewport;Ogre::Camera* cameras[2];Ogre::RenderWindow* renderWindow;CSkillManager* manager;CSkill* skill;CSkillTooltip* tooltip;CStringTranslate* translator;CSoundBank* soundBank;CDynamicPropertyFile* properties[2];
CEGUI::Window* windows[24];unsigned long long windowMemory[24][(sizeof(CEGUI::Checkbox)+7)/8];CEGUI::String* imageValues[3];CEGUI::UVector2 positions[24];unsigned long long observedSwitchBranches;unsigned getters[8],scaleCalls,positionCalls,settingsCalls,frame;
void* cameraTables[2][96];void* actorTables[2][64];
template<class T>T& at(void* p,size_t offset){return *(T*)((char*)p+offset);}
void n(int x){cap->add(&x,4);}void f(float x){cap->add(&x,4);}void str(const CEGUI::String& s){n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
int wid(const CEGUI::Window* p){for(unsigned i=0;i<24;++i)if(p==windows[i])return i;if(p)_exit(44);return -1;}
int aid(const CCharacter* p){return p==actors[0]?0:p==actors[1]?1:-1;}
int mid(const CPositionableObject* p){return p==actorModels[0]?0:p==actorModels[1]?1:-1;}
void changeActor(){if(input->mutate&&menu->m_pCharacter)menu->m_pCharacter=menu->m_pCharacter==actors[0]?actors[1]:actors[0];}
void text(CEGUI::Window* p,const CEGUI::String& s){n(1);n(wid(p));str(s);p->d_text=s;}
void property(CEGUI::PropertySet* p,const CEGUI::String& k,const CEGUI::String& v){n(2);int id=wid(static_cast<CEGUI::Window*>(p));n(id);str(k);str(v);if(id>=6&&id<=8&&k=="UnselectedImage")*imageValues[id-6]=v;}
CEGUI::String getProperty(const CEGUI::PropertySet* p,const CEGUI::String& k){n(3);int id=wid(static_cast<const CEGUI::Window*>(p));n(id);str(k);return id>=6&&id<=8?*imageValues[id-6]:CEGUI::String("other");}
bool isVisible(const CEGUI::Window* p,bool inherited){n(4);n(wid(p));n(inherited);if(input->mutate)for(unsigned i=0;i<3;++i)menu->m_TabNotifications[i]=false;return p->d_visible;}
void visible(CEGUI::Window* p,bool b){n(5);n(wid(p));n(b);p->d_visible=b;}
void position(CEGUI::Window* p,const CEGUI::UVector2& v){n(6);n(wid(p));cap->add(&v,sizeof(v));positions[wid(p)]=v;}
void remove(CEGUI::Window* p,CEGUI::Window* child){n(7);n(wid(p));n(wid(child));child->d_parent=0;}
int setting(CDynamicPropertyFile* p,unsigned key){n(8);n(p==properties[0]?0:1);n(key);++settingsCalls;if(input->mutate)menu->m_pDynamicPropertyFile=properties[1];const int values[]={1920,0,1,-1,1080,2147483647};return values[(input->serial+settingsCalls-1)%6];}
std::string convert(const std::wstring& s){n(11);cap->addText(s);return Ogre::UTFString(s).asUTF8();}
CStringTranslate* getTranslator(){n(14);return translator;}
std::wstring translate(CStringTranslate* p,const wchar_t* key){n(15);n(p==translator);std::wstring result(key);cap->addText(result);if(input->profile==1)return L"";if(input->profile==2)result+=L" Ω中";return result;}
void animation(CGenericModel* p,float dt,bool b){n(19);n(p==model);f(dt);n(b);}
void updateEntity(Ogre::Entity* p){n(20);n(p==entity);}
Ogre::Bone* bone(Ogre::SkeletonInstance* p,const std::string& s){n(21);n(p==skeleton);n(s.size());cap->add(s.data(),s.size());return s=="tag_topinventory"?bones[0]:s=="tag_bottominventory"?bones[1]:bones[2];}
const Ogre::Vector3& derived(Ogre::Bone* p){n(22);unsigned i=p==bones[0]?0:p==bones[1]?1:2;n(i);if(input->mutate)tags[i].x+=.25f;return tags[i];}
Ogre::Vector3 modelPosition(CPositionableObject* p,bool absolute){n(23);n(p==model);n(absolute);n(++positionCalls);return Ogre::Vector3(input->mutate?float(positionCalls):3.0f,-7,11);}
float scaled(CGameUI* p,float x){n(24);n(p==uis[0]?0:1);f(x);n(++scaleCalls);if(input->mutate)menu->m_pGameUI=menu->m_pGameUI==uis[0]?uis[1]:uis[0];const float factors[]={1,.75f,-1,0,-0.0f};return x*factors[input->serial%5];}
void dimensions(Ogre::Viewport* p,float x,float y,float w,float h){n(25);n(p==viewport);f(x);f(y);f(w);f(h);}
void aspectA(Ogre::Camera* p,float x){n(26);n(p==cameras[0]?0:1);f(x);}
void aspectB(Ogre::Camera* p,float x){n(27);n(p==cameras[0]?0:1);f(x);}
int actualWidth(const Ogre::Viewport* p){n(28);n(p==viewport);if(input->mutate){menu->m_pWardrobeCamera=cameras[1];cameraTables[0][0x278/8]=(void*)&aspectB;}return input->profile==3?-10:640;}
int actualHeight(const Ogre::Viewport* p){n(29);n(p==viewport);return input->profile==2?0:480;}
bool playing(const CGenericModel* p,const std::string& s){n(30);n(p==model);n(s.size());cap->add(s.data(),s.size());return input->profile==1;}
bool queued(const CGenericModel* p,const std::string& s){n(31);n(p==model);n(s.size());cap->add(s.data(),s.size());return input->profile==2;}
void modelVisible(CGenericModel* p,bool b){n(32);n(p==model);n(b);}
void removeViewport(Ogre::RenderWindow* p,int z){n(33);n(p==renderWindow);n(z);}
const Ogre::Matrix4& getOrientation(CPositionableObject* p){n(35);n(mid(p));return orientations[mid(p)];}
void setOrientation(CPositionableObject* p,const Ogre::Matrix4& v,bool b){n(36);n(mid(p));cap->add(&v,sizeof(v));n(b);orientations[mid(p)]=v;}
void rotation(Ogre::Matrix4& v,float angle){n(37);f(angle);for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j)v[i][j]=(i==j?1.0f:0.125f*float(i+j+1))+angle*.03125f;changeActor();}
CSkill* getSkill(CSkillManager* p,long long guid){n(38);n(p==manager);cap->add(&guid,8);return input->hover==2?0:skill;}
void show(CSkillTooltip* p,CBaseUnit* owner,CSkill* s,float x,float y){n(39);n(p==tooltip);n(aid((CCharacter*)owner));n(s==skill);f(x);f(y);p->m_pWindow->d_parent=windows[0];}
std::wstring gold(int x){n(40);n(x);wchar_t b[40];std::swprintf(b,40,L"%d",x);return b;}
bool alive(CCharacter* p){observedSwitchBranches|=1;if(input->profile==1)observedSwitchBranches|=2;n(41);n(aid(p));changeActor();return input->profile!=1;}
bool attack(CCharacter* p){observedSwitchBranches|=4;if(input->profile==2)observedSwitchBranches|=8;n(42);n(aid(p));changeActor();return input->profile==2;}
bool performing(CCharacter* p){observedSwitchBranches|=16;if(input->profile==3)observedSwitchBranches|=32;n(43);n(aid(p));changeActor();return input->profile==3;}
void toggle(CCharacter* p){observedSwitchBranches|=64;n(44);n(aid(p));p->m_bSecondaryWeaponSet=!p->m_bSecondaryWeaponSet;changeActor();}
void sound(CSoundBank* p,int id,Ogre::SceneNode* node,float a,float b,bool loop){observedSwitchBranches|=128;n(45);n(p==soundBank);n(id);n(node!=0);f(a);f(b);n(loop);changeActor();}
void layout(CInventoryMenu* p){observedSwitchBranches|=256;n(46);n(p==menu);}
void side(const Case& c,bool ours,autotest::Capture& output) {
    cap=&output;input=&c;observedSwitchBranches=0;scaleCalls=positionCalls=settingsCalls=0;memset(getters,0,sizeof(getters));
    unsigned long long mm[(sizeof(CInventoryMenu)+7)/8]={0},am[2][256]={{0}},gm[(sizeof(CGenericModel)+7)/8]={0},em[16]={0},sm[16]={0},bm[3][16]={{0}},om[2][16]={{0}},um[2][900]={{0}},pm[2][16]={{0}},vm[16]={0},cm[2][16]={{0}},rm[16]={0},skm[32]={0},sk[32]={0},tm[(sizeof(CSkillTooltip)+7)/8]={0},trm[16]={0},mam[16]={0};
    menu=(CInventoryMenu*)mm;model=(CGenericModel*)gm;entity=(Ogre::Entity*)em;skeleton=(Ogre::SkeletonInstance*)sm;viewport=(Ogre::Viewport*)vm;renderWindow=(Ogre::RenderWindow*)rm;manager=(CSkillManager*)skm;skill=(CSkill*)sk;tooltip=(CSkillTooltip*)tm;translator=(CStringTranslate*)trm;soundBank=(CSoundBank*)mam;
    void* menuTable[64]={0};menuTable[0x48/8]=(void*)&layout;*(void***)menu=menuTable;
    void* modelTable[64]={0};modelTable[0x50/8]=(void*)&modelVisible;*(void***)model=modelTable;model->m_pEntity=entity;model->m_pSkeleton=skeleton;
    void* skeletonTable[64]={0};skeletonTable[0x1b0/8]=(void*)&bone;*(void***)skeleton=skeletonTable;
    void* boneTable[80]={0};boneTable[0x200/8]=(void*)&derived;
    for(unsigned i=0;i<3;++i){bones[i]=(Ogre::Bone*)bm[i];*(void***)bones[i]=boneTable;tags[i]=Ogre::Vector3(c.layout==0?-1000.0f:float(100+70*i),40+20*i,3);}
    memset(cameraTables,0,sizeof(cameraTables));memset(actorTables,0,sizeof(actorTables));
    for(unsigned i=0;i<2;++i){actors[i]=(CCharacter*)am[i];actorModels[i]=(CPositionableObject*)om[i];actorTables[i][0xe8/8]=(void*)&getOrientation;actorTables[i][0x118/8]=(void*)&setOrientation;*(void***)actorModels[i]=actorTables[i];
        for(unsigned row=0;row<4;++row)for(unsigned col=0;col<4;++col)orientations[i][row][col]=(row==col?1.0f:float(row*4+col+1)*.0625f)+float(i)*.125f;
        at<CSkillManager*>(actors[i],0x1c8)=c.hover==1?0:manager;at<CPositionableObject*>(actors[i],0x208)=actorModels[i];actors[i]->m_iGold=c.profile==3?-2147483647:c.profile==2?2147483647:123+int(i);actors[i]->m_bSecondaryWeaponSet=((c.serial>>4)+i)%2;

        uis[i]=(CGameUI*)um[i];at<long>(uis[i],0x12d0)=long(100+300*i);at<long>(uis[i],0x12d8)=long(200+400*i);properties[i]=(CDynamicPropertyFile*)pm[i];cameras[i]=(Ogre::Camera*)cm[i];cameraTables[i][0x278/8]=i?(void*)&aspectB:(void*)&aspectA;*(void***)cameras[i]=cameraTables[i];
    }
    void* renderTable[32]={0};renderTable[0x60/8]=(void*)&removeViewport;*(void***)renderWindow=renderTable;
    memset(windowMemory,0,sizeof(windowMemory));memset(positions,0,sizeof(positions));
    for(unsigned i=0;i<24;++i){windows[i]=(CEGUI::Window*)windowMemory[i];new(&windows[i]->d_text)CEGUI::String(c.profile==1?"":"initial text");windows[i]->d_visible=((c.layout+i)%2)!=0;}
    menu->m_pParent=windows[0];menu->m_pBackground=windows[1];windows[1]->d_parent=windows[0];menu->m_pPanel=windows[2];menu->m_pForeground48=windows[3];menu->m_pSocketedIconParent=windows[4];menu->m_pForeground38=windows[5];menu->m_pBackpackTab=windows[6];menu->m_pSpellsTab=windows[7];menu->m_pFishTab=windows[8];menu->m_pBackpackSlots=windows[9];menu->m_pSpellsSlots=windows[10];menu->m_pFishSlots=windows[11];
    menu->m_pMoneyWindow=windows[12];menu->m_pWeaponSwitchWindow=windows[13];at<bool>(windows[13],0x732)=(c.serial>>3)%2;menu->m_pSoundBank=soundBank;tooltip->m_pWindow=windows[21];windows[21]->d_parent=c.layout%2?windows[22]:0;menu->m_pSkillTooltip=tooltip;

    CEGUI::String images[3];for(unsigned i=0;i<3;++i){new(&menu->m_TabUnselectedImages[i])CEGUI::String(i==0?"backpack":i==1?"spells":"fish");new(&menu->m_TabSelectedImages[i])CEGUI::String(i==0?"backpack selected":i==1?"spells selected":"fish selected");images[i]=c.layout==0?menu->m_TabUnselectedImages[i]:c.layout==1?menu->m_TabSelectedImages[i]:CEGUI::String("other");imageValues[i]=&images[i];menu->m_TabNotifications[i]=((c.serial/3)>>(i%3))&1;}
    menu->m_pCharacter=c.owner?actors[0]:0;menu->m_bOpen=c.state&1;menu->m_bFullyClosed=c.state&2;if(c.state==2&&c.hover==3)menu->m_pSkillTooltip=0;menu->m_pGameUI=uis[0];menu->m_pDynamicPropertyFile=properties[0];menu->m_pInventoryModel=model;menu->m_pViewport=c.layout%2?viewport:0;menu->m_pWardrobeCamera=cameras[0];menu->m_pRenderWindow=renderWindow;menu->m_bSpellHovered=c.hover!=0;menu->m_HoveredSkillGuid=1234567;menu->m_bRotateLeft=c.owner&&(c.serial%4==1||c.serial%4==3);menu->m_bRotateRight=c.owner&&(c.serial%4==2||c.serial%4==3);menu->m_pHoverObject=(CEquipment*)actors[0];menu->m_fScreenEdge=-11;menu->m_fPanelX=-12;
    const float phases[]={0,.5f,.99f,1.1f,-.25f,-0.0f,2.25f,std::numeric_limits<float>::quiet_NaN(),-std::numeric_limits<float>::infinity()};menu->m_fTabPhase=phases[c.serial%9];
    const uintptr_t cacheGP=0x14c7348,guardGP=0x14c7340;
    unsigned mode=(c.serial/5)%3;
    if(mode==0){memset((void*)cacheGP,0,sizeof(std::wstring));*(unsigned long long*)guardGP=0;}
    else {new((void*)cacheGP)std::wstring(mode==2?L"cached GP":L"");*(unsigned long long*)guardGP=1;}
    detour::Set d,imports;
#define R(N,F) TL_REDIRECT(d,N,&F)
    R(settingsFn,setting);R(goldFn,gold);R(convertFn,convert);R(animationFn,animation);R(modelPosFn,modelPosition);R(playingFn,playing);R(queuedFn,queued);R(scaledFn,scaled);R(translateSingletonFn,getTranslator);R(translateFn,translate);R(skillFn,getSkill);R(showFn,show);R(rotationFn,rotation);R(aliveFn,alive);R(attackFn,attack);R(skillLooseFn,performing);R(toggleFn,toggle);R(soundFn,sound);
#undef R
#define I(N,F) imports.redirect(N,N,&F)
    I(textFn,text);I(propertyFn,property);I(getPropertyFn,getProperty);I(visibleFn,visible);I(isVisibleFn,isVisible);I(positionFn,position);I(removeFn,remove);I(entityFn,updateEntity);I(dimensionsFn,dimensions);I(actualWidthFn,actualWidth);I(actualHeightFn,actualHeight);
#undef I
    if(d.failed()||imports.failed())_exit(43);
    for(frame=0;frame<2;++frame){n(90);n(frame);float elapsed=frame?0.0f:.125f;
        if(frame){if(ours)newUpdate(menu,elapsed);else oldUpdate(menu,elapsed);}
        else if(ours)autotest::invoke(output,&newUpdate,menu,elapsed);else autotest::invoke(output,&oldUpdate,menu,elapsed);
        n(91);f(menu->m_fTabPhase);f(menu->m_fScreenEdge);f(menu->m_fPanelX);n(menu->m_bOpen);n(menu->m_bFullyClosed);n(aid(menu->m_pCharacter));n(menu->m_pViewport==viewport);n(menu->m_pHoverObject!=0);for(unsigned i=0;i<3;++i){n(menu->m_TabNotifications[i]);str(images[i]);}
        for(unsigned i=0;i<24;++i){str(windows[i]->d_text);n(windows[i]->d_visible);n(wid(windows[i]->d_parent));}cap->add(positions,sizeof(positions));cap->add(orientations,sizeof(orientations));
    }
    n(*(unsigned char*)guardGP);if(*(unsigned char*)guardGP)cap->addText(*(std::wstring*)cacheGP);for(unsigned i=0;i<2;++i){n(actors[i]->m_iGold);n(actors[i]->m_bSecondaryWeaponSet);}
    cap->add(&observedSwitchBranches,sizeof(observedSwitchBranches));

}
void a(void* p,autotest::Capture& c){side(*(Case*)p,false,c);}void b(void* p,autotest::Capture& c){side(*(Case*)p,true,c);}
}
TL_TEST(inventory_update_differential){autotest::Coverage coverage("inventory_update_differential",(uint64_t)(uintptr_t)&oldUpdate);unsigned long long switchCoverage=0;unsigned serial=0;for(unsigned owner=0;owner<2;++owner)for(unsigned state=0;state<4;++state)for(unsigned layout=0;layout<4;++layout)for(unsigned hover=0;hover<4;++hover)for(unsigned profile=0;profile<4;++profile)for(unsigned mutate=0;mutate<2;++mutate){Case c={owner,state,layout,hover,profile,mutate,serial++};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);if(x.capture.length>=8){unsigned long long flags;memcpy(&flags,x.capture.data+x.capture.length-8,8);switchCoverage|=flags;}if(coverage.observe(host,x,y)){coverage.report(host);size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    case %u owner %u state %u layout %u hover %u profile %u mutate %u status %d/%d bytes %lu/%lu first %lu\n",c.serial,owner,state,layout,hover,profile,mutate,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t off=first>48?(first-48)&~size_t(3):0;off<first+128&&off+4<=x.capture.length&&off+4<=y.capture.length;off+=4){int u,v;memcpy(&u,x.capture.data+off,4);memcpy(&v,y.capture.data+off,4);float uf,vf;memcpy(&uf,&u,4);memcpy(&vf,&v,4);host->log("      %lu %d/%d floats %g/%g\n",(unsigned long)off,u,v,double(uf),double(vf));}return 1;}}coverage.report(host);host->log("    weapon-switch branch coverage: 0x%llx\n",switchCoverage);return switchCoverage==511?0:1;}
