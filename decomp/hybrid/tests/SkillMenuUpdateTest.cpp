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
#include "SkillMenu.h"
#include "Character.h"
#include "GenericModel.h"
#include "SkillTooltip.h"
#include "SkillManager.h"
#include "DynamicPropertyFile.h"
#include "GameVariables.h"
#include "StringTranslate.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldUpdate,(CSkillMenu*,float),"_ZN10CSkillMenu6updateEf")
extern "C" void newUpdate(CSkillMenu*,float) __asm__("_ZN10CSkillMenu6updateEf");
TL_FUNCTION(settingsFn,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(convertFn,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(numberFn,"_ZN7STRINGS16GetValueAsStringEi")
TL_FUNCTION(animationFn,"_ZN13CGenericModel15updateAnimationEfb")
TL_FUNCTION(modelPosFn,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(playingFn,"_ZNK13CGenericModel16animationPlayingERKSs")
TL_FUNCTION(queuedFn,"_ZNK13CGenericModel15animationQueuedERKSs")
TL_FUNCTION(scaledFn,"_ZN7CGameUI7scaledYEf")
TL_FUNCTION(translateSingletonFn,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateFn,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(skillFn,"_ZN13CSkillManager14getSkillByGuidEx")
TL_FUNCTION(showFn,"_ZN13CSkillTooltip11showTooltipEP9CBaseUnitP6CSkillff")
extern "C" char textFn[] __asm__("_ZN5CEGUI6Window7setTextERKNS_6StringE");
extern "C" char positionFn[] __asm__("_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
extern "C" char removeFn[] __asm__("_ZN5CEGUI6Window17removeChildWindowEPS0_");
extern "C" char entityFn[] __asm__("_ZN4Ogre6Entity16_updateAnimationEv");
namespace {
struct Case {unsigned state,layout,hover,profile,mutate,cache,serial;};
autotest::Capture* cap;const Case* input;CSkillMenu* menu;CCharacter* actors[2];CGenericModel* model;Ogre::Entity* entity;Ogre::SkeletonInstance* skeleton;Ogre::Bone* bones[3];Ogre::Vector3 tags[3];CGameUI* uis[2];CSkillManager* manager;CSkill* skill;CSkillTooltip* tooltip;CStringTranslate* translator;CDynamicPropertyFile* properties[2];
CEGUI::Window* windows[8];unsigned long long windowMemory[8][(sizeof(CEGUI::Window)+7)/8];CEGUI::UVector2 positions[8];unsigned scaleCalls,positionCalls,settingsCalls,frame;unsigned long long branches;
template<class T>T& at(void* p,size_t offset){return *(T*)((char*)p+offset);}
void n(int x){cap->add(&x,4);}void f(float x){cap->add(&x,4);}void str(const CEGUI::String& s){n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
int wid(const CEGUI::Window* p){for(unsigned i=0;i<8;++i)if(p==windows[i])return i;if(p)_exit(44);return -1;}
int aid(const CCharacter* p){return p==actors[0]?0:p==actors[1]?1:-1;}
void text(CEGUI::Window* p,const CEGUI::String& s){branches|=1;n(1);n(wid(p));str(s);p->d_text=s;}
void position(CEGUI::Window* p,const CEGUI::UVector2& v){n(6);n(wid(p));cap->add(&v,sizeof(v));positions[wid(p)]=v;}
void remove(CEGUI::Window* p,CEGUI::Window* child){branches|=wid(child)==1?2:4;n(7);n(wid(p));n(wid(child));child->d_parent=0;}
int setting(CDynamicPropertyFile* p,unsigned key){n(8);n(p==properties[0]?0:1);n(key);++settingsCalls;if(input->mutate)menu->m_pProperties=properties[1];const int values[]={1920,0,1,-1,1080,2147483647,(-2147483647-1)};return values[(input->serial+settingsCalls-1)%7];}
std::string convert(const std::wstring& s){n(11);cap->addText(s);// Pinned CEGUI 0.6.2 encoded_size overreads a four-byte UTF-8 sequence.
 // Keep non-BMP code points observable at the converter boundary, with a
 // controlled ASCII return; do not accept comparisons of uninitialized bytes.
 return input->profile==5?std::string("non-BMP converter boundary"):Ogre::UTFString(s).asUTF8();}
CStringTranslate* getTranslator(){branches|=8;n(14);return translator;}
std::wstring translate(CStringTranslate* p,const wchar_t* key){n(15);n(p==translator);cap->addText(std::wstring(key));if(input->profile==1)return L"";if(input->profile==2)return L"Ω中";if(input->profile==5)return L"Ω中 \U0001f600";if(input->profile==3)return std::wstring(L"embedded\0tail",13);return L"Points Remaining";}
std::string number(int value){n(16);n(value);char b[40];std::sprintf(b,"%d",value);return b;}
void animation(CGenericModel* p,float dt,bool b){branches|=16;n(19);n(p==model);f(dt);n(b);if(input->mutate&&input->profile==4)menu->m_pOwner=0;}
void updateEntity(Ogre::Entity* p){n(20);n(p==entity);}
Ogre::Bone* bone(Ogre::SkeletonInstance* p,const std::string& s){n(21);n(p==skeleton);n(s.size());cap->add(s.data(),s.size());return s=="tag_topskill"?bones[0]:s=="tag_bottomskill"?bones[1]:bones[2];}
const Ogre::Vector3& derived(Ogre::Bone* p){n(22);unsigned i=p==bones[0]?0:p==bones[1]?1:2;n(i);if(input->mutate)tags[i].x+=.25f;return tags[i];}
Ogre::Vector3 modelPosition(CPositionableObject* p,bool absolute){n(23);n(p==model);n(absolute);n(++positionCalls);return Ogre::Vector3(input->mutate?float(positionCalls):3.0f,-7,11);}
float scaled(CGameUI* p,float x){n(24);n(p==uis[0]?0:1);f(x);n(++scaleCalls);if(input->mutate)menu->m_pGameUI=menu->m_pGameUI==uis[0]?uis[1]:uis[0];const float factors[]={1,.75f,-1,0,-0.0f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity()};return x*factors[input->serial%8];}
bool playing(const CGenericModel* p,const std::string& s){branches|=32;n(30);n(p==model);n(s.size());cap->add(s.data(),s.size());return input->profile==1;}
bool queued(const CGenericModel* p,const std::string& s){branches|=64;n(31);n(p==model);n(s.size());cap->add(s.data(),s.size());return input->profile==2;}
void modelVisible(CGenericModel* p,bool b){branches|=128;n(32);n(p==model);n(b);}
CSkill* getSkill(CSkillManager* p,long long guid){branches|=256;n(38);n(p==manager);cap->add(&guid,8);return input->hover==2?0:skill;}
void show(CSkillTooltip* p,CBaseUnit* owner,CSkill* s,float x,float y){branches|=512;n(39);n(p==tooltip);n(aid((CCharacter*)owner));n(s==skill);f(x);f(y);p->m_pWindow->d_parent=windows[0];}
void layout(CSkillMenu* p){branches|=1024;n(46);n(p==menu);n(p->m_iCachedSkillPoints);if(input->mutate){p->m_pOwner=actors[1];at<int>(actors[1],0x460)=static_cast<int>(static_cast<unsigned int>(at<int>(actors[1],0x460))+3u);}}
void canon(unsigned char* snapshot,unsigned offset,uintptr_t value){memcpy(snapshot+offset,&value,sizeof(value));}
void side(const Case& c,bool ours,autotest::Capture& output) {
 cap=&output;input=&c;branches=0;scaleCalls=positionCalls=settingsCalls=0;
 unsigned long long mm[(sizeof(CSkillMenu)+7)/8]={0},am[2][256]={{0}},gm[(sizeof(CGenericModel)+7)/8]={0},em[16]={0},sm[16]={0},bm[3][16]={{0}},um[2][900]={{0}},pm[2][16]={{0}},skm[32]={0},sk[32]={0},tm[(sizeof(CSkillTooltip)+7)/8]={0},trm[16]={0};
 menu=(CSkillMenu*)mm;model=(CGenericModel*)gm;entity=(Ogre::Entity*)em;skeleton=(Ogre::SkeletonInstance*)sm;manager=(CSkillManager*)skm;skill=(CSkill*)sk;tooltip=(CSkillTooltip*)tm;translator=(CStringTranslate*)trm;
 void* menuTable[64]={0};menuTable[0x48/8]=(void*)&layout;*(void***)menu=menuTable;
 void* modelTable[64]={0};modelTable[0x50/8]=(void*)&modelVisible;*(void***)model=modelTable;model->m_pEntity=entity;model->m_pSkeleton=skeleton;
 void* skeletonTable[64]={0};skeletonTable[0x1b0/8]=(void*)&bone;*(void***)skeleton=skeletonTable;
 void* boneTable[80]={0};boneTable[0x200/8]=(void*)&derived;
 for(unsigned i=0;i<3;++i){bones[i]=(Ogre::Bone*)bm[i];*(void***)bones[i]=boneTable;tags[i]=Ogre::Vector3(c.layout==0?-1000.0f:float(100+70*i),40+20*i,3);}
 const int points[]={0,1,-1,2147483647,(-2147483647-1)};
 for(unsigned i=0;i<2;++i){actors[i]=(CCharacter*)am[i];at<CSkillManager*>(actors[i],0x1c8)=c.hover==1?0:manager;at<int>(actors[i],0x460)=points[(c.profile+i)%5];uis[i]=(CGameUI*)um[i];at<long>(uis[i],0x12d0)=i?-9223372036854775807L:9223372036854775807L;at<long>(uis[i],0x12d8)=long(200+400*i);properties[i]=(CDynamicPropertyFile*)pm[i];}
 memset(windowMemory,0,sizeof(windowMemory));memset(positions,0,sizeof(positions));
 for(unsigned i=0;i<8;++i){windows[i]=(CEGUI::Window*)windowMemory[i];new(&windows[i]->d_text)CEGUI::String("initial text");}
 menu->m_pRoot=windows[0];menu->m_pBackground=windows[1];windows[1]->d_parent=windows[0];menu->m_pTopFrame=windows[2];menu->m_pBottomFrame=windows[3];menu->m_pSkillPoints=windows[4];tooltip->m_pWindow=windows[5];windows[5]->d_parent=c.layout%2?windows[6]:0;menu->m_pTooltip=tooltip;
 menu->m_pOwner=actors[0];menu->m_bOpenPartial=c.state&1;menu->m_bClosed=c.state&2;if(c.state==2&&c.hover==3)menu->m_pTooltip=0;menu->m_pGameUI=uis[0];menu->m_pProperties=properties[0];menu->m_pModel=model;menu->m_bSkillHovered=c.hover!=0;menu->m_HoveredSkillGuid=0x1234567887654321LL;menu->m_fScreenEdge=-11;menu->m_fTopX=-12;menu->m_iCachedSkillPoints=c.layout==0?at<int>(actors[0],0x460):12345;
 const uintptr_t cacheAddress=0x14d2f48,guardAddress=0x14d2f40;
 if(c.cache==0){memset((void*)cacheAddress,0,sizeof(std::wstring));*(unsigned long long*)guardAddress=0;}
 else{new((void*)cacheAddress)std::wstring(c.cache==2?L"cached Points":L"");*(unsigned long long*)guardAddress=1;}
 detour::Set d,imports;
#define R(N,F) TL_REDIRECT(d,N,&F)
 R(settingsFn,setting);R(numberFn,number);R(convertFn,convert);R(animationFn,animation);R(modelPosFn,modelPosition);R(playingFn,playing);R(queuedFn,queued);R(scaledFn,scaled);R(translateSingletonFn,getTranslator);R(translateFn,translate);R(skillFn,getSkill);R(showFn,show);
#undef R
#define I(N,F) imports.redirect(N,N,&F)
 I(textFn,text);I(positionFn,position);I(removeFn,remove);I(entityFn,updateEntity);
#undef I
 if(d.failed()||imports.failed())_exit(43);
 for(frame=0;frame<2;++frame){
  if(frame&&menu->m_pOwner==0)menu->m_pOwner=actors[0];
  n(90);n(frame);float elapsed=frame?-0.0f:.125f;
  if(frame){if(ours)newUpdate(menu,elapsed);else oldUpdate(menu,elapsed);}
  else if(ours)autotest::invoke(output,&newUpdate,menu,elapsed);else autotest::invoke(output,&oldUpdate,menu,elapsed);
  n(91);unsigned char snapshot[sizeof(CSkillMenu)];memcpy(snapshot,menu,sizeof(snapshot));
  canon(snapshot,0,1);canon(snapshot,0x10,wid(menu->m_pRoot));canon(snapshot,0x18,wid(menu->m_pBackground));canon(snapshot,0x20,wid(menu->m_pTopFrame));canon(snapshot,0x28,wid(menu->m_pBottomFrame));canon(snapshot,0x30,aid(menu->m_pOwner));canon(snapshot,0x48,menu->m_pProperties==properties[0]?0:menu->m_pProperties==properties[1]?1:99);canon(snapshot,0x50,menu->m_pGameUI==uis[0]?0:menu->m_pGameUI==uis[1]?1:99);canon(snapshot,0x60,menu->m_pModel==model?1:99);canon(snapshot,0x88,wid(menu->m_pSkillPoints));canon(snapshot,0x750,menu->m_pTooltip==tooltip?1:menu->m_pTooltip?99:0);cap->add(snapshot,sizeof(snapshot));
  for(unsigned i=0;i<8;++i){str(windows[i]->d_text);n(wid(windows[i]->d_parent));}cap->add(positions,sizeof(positions));
 }
 n(*(unsigned char*)guardAddress);if(*(unsigned char*)guardAddress)cap->addText(*(std::wstring*)cacheAddress);for(unsigned i=0;i<2;++i)n(at<int>(actors[i],0x460));cap->add(&branches,sizeof(branches));
}
void a(void* p,autotest::Capture& c){side(*(Case*)p,false,c);}void b(void* p,autotest::Capture& c){side(*(Case*)p,true,c);}
}
TL_TEST(skillmenu_update_differential){
 autotest::Coverage coverage("skillmenu_update_differential",(uint64_t)(uintptr_t)&oldUpdate);unsigned long long all=0;unsigned serial=0;
 for(unsigned state=0;state<4;++state)for(unsigned layout=0;layout<3;++layout)for(unsigned hover=0;hover<4;++hover)for(unsigned profile=0;profile<6;++profile)for(unsigned mutate=0;mutate<2;++mutate)for(unsigned cache=0;cache<3;++cache){
  Case c={state,layout,hover,profile,mutate,cache,serial++};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);
  if(x.capture.length>=8){unsigned long long flags;memcpy(&flags,x.capture.data+x.capture.length-8,8);all|=flags;}
  if(coverage.observe(host,x,y)){coverage.report(host);size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    case %u state %u layout %u hover %u profile %u mutate %u cache %u status %d/%d bytes %lu/%lu first %lu\n",c.serial,state,layout,hover,profile,mutate,cache,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t off=first>48?(first-48)&~size_t(3):0;off<first+128&&off+4<=x.capture.length&&off+4<=y.capture.length;off+=4){int u,v;memcpy(&u,x.capture.data+off,4);memcpy(&v,y.capture.data+off,4);float uf,vf;memcpy(&uf,&u,4);memcpy(&vf,&v,4);host->log("      %lu %d/%d floats %g/%g\n",(unsigned long)off,u,v,double(uf),double(vf));}return 1;}
 }
 coverage.report(host);host->log("    skill menu update: %u scenarios, two frames; branch witnesses 0x%llx\n",serial,all);return all==2047?0:1;
}
