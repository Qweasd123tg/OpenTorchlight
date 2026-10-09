#include <cstring>
#include <string>
#include <new>
#include <limits>
#define private public
#define protected public
#include <CEGUI.h>
#include "SkillFoldout.h"
#include "Skill.h"
#include "BaseUnit.h"
#include "GameUI.h"
#include "SkillManager.h"
#include "Inventory.h"
#include "EquipmentRef.h"
#include "StringTranslate.h"
#include "MasterResourceManager.h"
#include "Settings.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldShow,(CSkillFoldout*,CBaseUnit*,float,float,bool,bool),"_ZN13CSkillFoldout11showFoldoutEP9CBaseUnitffbb")
extern "C" void newShow(CSkillFoldout*,CBaseUnit*,float,float,bool,bool) __asm__("_ZN13CSkillFoldout11showFoldoutEP9CBaseUnitffbb");
TL_FUNCTION(scaledFn,"_ZN7CGameUI7scaledYEf")
TL_FUNCTION(convertFn,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(translateSingletonFn,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(translateFn,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(knownFn,"_ZN13CSkillManager11knownSkillsE22ESKILL_ACTIVATION_TYPE")
TL_FUNCTION(iconFn,"_ZN6CSkill12getSkillIconEv")
TL_FUNCTION(effectiveFn,"_ZN6CSkill28calculateEffectiveSkillLevelEv")
TL_FUNCTION(valueFn,"_ZN7STRINGS16GetValueAsStringEi")
TL_FUNCTION(narrowFn,"_ZN7STRINGS21StringConvertToNarrowEPKw")
TL_FUNCTION(uiImageFn,"_ZN7CGameUI20getImageFromImageSetEPKh")
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dataFn,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(masterFn,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(ratioFn,"_ZN20CDynamicPropertyFile8GetFloatEj")
TL_FUNCTION(widthFn,"_ZN7CGameUI14getWindowWidthEv")
TL_FUNCTION(heightFn,"_ZN7CGameUI15getWindowHeightEv")
#define IMP(N,S) extern "C" char N[] __asm__(S)
IMP(addFn,"_ZN5CEGUI6Window14addChildWindowEPS0_");
IMP(sizeFn,"_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
IMP(posFn,"_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
IMP(imageStringFn,"_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE");
IMP(propertyFn,"_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
IMP(frontFn,"_ZN5CEGUI6Window11moveToFrontEv");
IMP(tooltipFn,"_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE");
IMP(textFn,"_ZN5CEGUI6Window7setTextERKNS_6StringE");
IMP(visibleFn,"_ZN5CEGUI6Window10setVisibleEb");
IMP(enabledFn,"_ZN5CEGUI6Window10setEnabledEb");
IMP(idFn,"_ZN5CEGUI6Window5setIDEj");
IMP(getWidthFn,"_ZNK5CEGUI6Window8getWidthEv");
IMP(getHeightFn,"_ZNK5CEGUI6Window9getHeightEv");
#undef IMP
namespace {
struct Case {unsigned mode,scale,flags,mutate,placement;};
autotest::Capture* cap;const Case* input;CSkillFoldout* fold;CGameUI* ui[2];CSkill* skills[24];CBaseUnit* owner;CSkillManager* manager;CStringTranslate* translator;CBaseUnit* items[24];CDataGroup* data[24];CMasterResourceManager* masters[2];CSettings* settings[2];
CEGUI::Window* windows[204];unsigned long long wm[204][(sizeof(CEGUI::Window)+7)/8];CEGUI::UVector2 positions[204],sizes[204];std::wstring icons[24],itemIcons[24];CEGUI::Image* images[32];unsigned long long im[32][32];unsigned knownCalls,scaleCalls,imageCount,ratioCalls,masterCalls,effectiveCalls[24];unsigned long long branches;
template<class T>T& at(void* p,size_t offset){return *(T*)((char*)p+offset);}
void n(int x){cap->add(&x,4);}void f(float x){cap->add(&x,4);}void str(const CEGUI::String& s){n(s.length());for(size_t i=0;i<s.length();++i)n(s[i]);}
int wid(const CEGUI::Window* p){for(unsigned i=0;i<204;++i)if(p==windows[i])return i;if(p)_exit(44);return -1;}
int sid(const CSkill* p){for(int i=0;i<24;++i)if(p==skills[i])return i;_exit(45);}
int iid(const CBaseUnit* p){for(int i=0;i<24;++i)if(p==items[i])return i;_exit(46);}
int uiid(const CGameUI* p){return p==ui[0]?0:p==ui[1]?1:-1;}
void add(CEGUI::Window* p,CEGUI::Window* q){branches|=1;n(1);n(wid(p));n(wid(q));q->d_parent=p;}
void visible(CEGUI::Window* p,bool b){n(2);n(wid(p));n(b);p->d_visible=b;}
void enabled(CEGUI::Window* p,bool b){n(3);n(wid(p));n(b);p->d_enabled=b;}
void front(CEGUI::Window* p){n(4);n(wid(p));}
void size(CEGUI::Window* p,const CEGUI::UVector2& v){n(5);n(wid(p));cap->add(&v,sizeof(v));sizes[wid(p)]=v;}
void position(CEGUI::Window* p,const CEGUI::UVector2& v){n(6);n(wid(p));cap->add(&v,sizeof(v));positions[wid(p)]=v;}
void property(CEGUI::PropertySet* p,const CEGUI::String& k,const CEGUI::String& v){n(7);n(wid(static_cast<CEGUI::Window*>(p)));str(k);str(v);}
void text(CEGUI::Window* p,const CEGUI::String& s){n(8);n(wid(p));str(s);p->d_text=s;}
void tooltip(CEGUI::Window* p,const CEGUI::String& s){n(9);n(wid(p));str(s);p->d_tooltipText=s;}
void setId(CEGUI::Window* p,unsigned id){branches|=id==95?2:id==1000?4:8;n(10);n(wid(p));n(id);p->d_ID=id;}
float scaled(CGameUI* p,float x){n(11);n(uiid(p));f(x);++scaleCalls;const float values[]={1,.75f,-1,0,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()};float result=x*values[input->scale];if(input->mutate){result+=float(scaleCalls)*.03125f;fold->m_pGameUI=p==ui[0]?ui[1]:ui[0];}return result;}
unsigned count(){return input->mode<4?0:input->mode==8?14:input->mode==17?20:input->mode==9?10:input->mode==10?12:6;}
int known(CSkillManager* p,ESKILL_ACTIVATION_TYPE t){n(12);n(p==manager);n(t);++knownCalls;return count();}
void effective(CSkill* p){n(13);int i=sid(p);n(i);++effectiveCalls[i];if(input->mode==18)at<unsigned>(p,0xe0)=effectiveCalls[i]%2;}
const std::wstring& icon(CSkill* p){n(14);int i=sid(p);n(i);return icons[i];}
std::string value(int x){n(15);n(x);char b[32];std::sprintf(b,"%d",x);return b;}
std::string narrow(const wchar_t* s){n(16);cap->addText(std::wstring(s));return s[0]=='i'?"item_icon":"skill_icon";}
std::string convert(const std::wstring& s){n(17);cap->addText(s);return input->mode==15?"converted \xce\xa9":"translated attack";}
CStringTranslate* getTranslator(){n(18);return translator;}
std::wstring translate(CStringTranslate* p,const wchar_t* s){n(19);n(p==translator);cap->addText(std::wstring(s));return input->mode==15?std::wstring(L"unicode Ω\0ignored",17):input->mode==14?L"":L"weapon attack";}
const CEGUI::Image* getImage(CGameUI* p,const unsigned char* s){n(20);n(uiid(p));cap->addText(std::string((const char*)s));bool item=std::strcmp((const char*)s,"item_icon")==0;if(item&&input->mode==13){branches|=16;return 0;}unsigned k=imageCount++%32;images[k]=(CEGUI::Image*)im[k];at<float>(images[k],0x20)=float(32+k%5*10);at<float>(images[k],0x24)=input->mode==14?0.0f:float(24+k%3*12);return images[k];}
CEGUI::String imageString(const CEGUI::Image* p){n(21);unsigned i=0;for(;i<32;++i)if(p==images[i])break;n(i);char s[32];std::sprintf(s,"image%u",i);return CEGUI::String(s);}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES type){n(22);int i=iid(p);n(i);n(type);return type==1?(input->mode==11?i%3!=0:true):type==129?(input->mode==11?i%4==0:false):false;}
const std::wstring& getData(CDataGroup* p,const std::wstring& key,const std::wstring& fallback){n(23);int i=0;for(;i<24;++i)if(p==data[i])break;n(i);cap->addText(key);cap->addText(fallback);return itemIcons[i%24];}
CMasterResourceManager* master(){n(24);n(masterCalls);return masters[input->mutate?(masterCalls++%2):0];}
float ratio(CDynamicPropertyFile* p,unsigned key){n(25);n(p==settings[0]?0:1);n(key);++ratioCalls;if(input->mutate&&imageCount){CEGUI::Image* image=images[(imageCount-1)%32];at<float>(image,0x20)+=7;at<float>(image,0x24)+=3;}return input->mode==14?0.0f:input->mutate?(ratioCalls%2?1.25f:.75f):1.0f;}
float screenWidth(CGameUI* p){branches|=32;n(26);n(uiid(p));if(input->mutate)*(CGameUI**)0x14b9c68=ui[1];return input->placement==2?180.5f:1920.75f;}
float screenHeight(CGameUI* p){n(27);n(uiid(p));return input->placement==2?100.75f:1080.5f;}
CEGUI::UDim getWidth(const CEGUI::Window* p){n(28);n(wid(p));CEGUI::UDim v=sizes[wid(p)].d_x;if(input->mode==19)v.d_scale=2.75f;return v;}
CEGUI::UDim getHeight(const CEGUI::Window* p){n(29);n(wid(p));CEGUI::UDim v=sizes[wid(p)].d_y;if(input->mode==19)v.d_scale=-2.75f;return v;}
void canon(unsigned char* snapshot,unsigned offset,uintptr_t value){memcpy(snapshot+offset,&value,sizeof(value));}
void side(const Case& c,bool ours,autotest::Capture& out){
 cap=&out;input=&c;knownCalls=scaleCalls=imageCount=ratioCalls=masterCalls=0;branches=0;memset(wm,0,sizeof(wm));memset(positions,0,sizeof(positions));memset(sizes,0,sizeof(sizes));memset(im,0,sizeof(im));memset(images,0,sizeof(images));memset(effectiveCalls,0,sizeof(effectiveCalls));
 unsigned long long fm[(sizeof(CSkillFoldout)+7)/8]={0},om[384]={0},sm[24][64]={{0}},mgr[32]={0},um[2][16]={{0}},trm[16]={0},inv[80]={0},refmem[24][8]={{0}},itemmem[24][64]={{0}},datamem[24][32]={{0}},mastermem[2][64]={{0}},settingmem[2][32]={{0}};
 fold=(CSkillFoldout*)fm;owner=(CBaseUnit*)om;manager=(CSkillManager*)mgr;translator=(CStringTranslate*)trm;
 for(unsigned i=0;i<2;++i){ui[i]=(CGameUI*)um[i];masters[i]=(CMasterResourceManager*)mastermem[i];settings[i]=(CSettings*)settingmem[i];masters[i]->m_pSettings=settings[i];}
 for(unsigned i=0;i<204;++i){windows[i]=(CEGUI::Window*)wm[i];new(&windows[i]->d_text)CEGUI::String("before");new(&windows[i]->d_tooltipText)CEGUI::String("tip");windows[i]->d_visible=windows[i]->d_enabled=true;windows[i]->d_ID=9000+i;}
 fold->m_pGameUI=ui[0];fold->m_pParent=windows[0];fold->m_pWindow=windows[1];windows[1]->d_parent=c.mode==0?windows[203]:0;fold->m_iSelection=-7;
 for(unsigned col=0;col<10;++col)for(unsigned row=0;row<10;++row){unsigned k=col*10+row;fold->m_Icons[col][row]=windows[2+k];fold->m_Hotkeys[col][row]=windows[102+k];fold->m_ItemGuids[col][row]=-2000-k;fold->m_SkillIndices[k]=-1000-k;}
 at<CSkillManager*>(owner,0x1c8)=c.mode==2?0:manager;at<CInventory*>(owner,0x490)=(CInventory*)inv;
 for(unsigned i=0;i<24;++i)at<long long>(owner,0x950+i*8)=-777;
 TArrayList<CSkill*>* list=(TArrayList<CSkill*>*)((char*)manager+0x60);new(list)TArrayList<CSkill*>(24);
 for(unsigned i=0;i<24;++i){skills[i]=(CSkill*)sm[i];icons[i]=L"skill";at<int>(skills[i],0x60)=0;at<unsigned char>(skills[i],0x6b)=0;at<unsigned char>(skills[i],0x6d)=1;at<unsigned char>(skills[i],0x6f)=1;at<unsigned>(skills[i],0xd8)=i%3*5;at<unsigned>(skills[i],0xe0)=1;at<long long>(skills[i],0x150)=0x1234567800000000LL+i;list->add(skills[i]);}
 if(c.mode==5){at<unsigned>(skills[0],0xe0)=0;at<unsigned char>(skills[1],0x6b)=1;at<unsigned char>(skills[2],0x6d)=0;at<unsigned char>(skills[3],0x6f)=0;at<int>(skills[4],0x60)=4;}
 if(c.mode==6){const unsigned levels[]={0,4,5,49,50,0xffffffffU};for(unsigned i=0;i<6;++i)at<unsigned>(skills[i],0xd8)=levels[i];}
 if(c.mode==7)list->m_nCapacity=1;
 if(c.mode==8)for(unsigned i=0;i<14;++i)at<unsigned>(skills[i],0xd8)=0;
 if(c.mode==9)for(unsigned i=0;i<10;++i)at<unsigned>(skills[i],0xd8)=45;
 if(c.mode==10)for(unsigned i=0;i<12;++i)at<unsigned>(skills[i],0xd8)=50;
 if(c.mode==17)for(unsigned i=0;i<20;++i)at<unsigned>(skills[i],0xd8)=(i/2)*5;
 if(c.mode==16){at<long long>(owner,0x950)=at<long long>(skills[0],0x150);at<long long>(owner,0x9b0+11*8)=at<long long>(skills[1],0x150);at<long long>(owner,0x9b0+2*8)=-999;}
 TArrayList<CEquipmentRef*>* inventory=(TArrayList<CEquipmentRef*>*)((char*)inv+0x30);new(inventory)TArrayList<CEquipmentRef*>(24);
 unsigned itemCount=c.mode>=11?(c.mode==12?24:8):0;
 for(unsigned i=0;i<24;++i){CEquipmentRef* ref=(CEquipmentRef*)refmem[i];items[i]=(CBaseUnit*)itemmem[i];data[i]=(CDataGroup*)datamem[i];items[i]->m_pDataGroup=data[i];items[i]->m_iUnitValue1A0=0x2345678900000000LL+(c.mode==12?i/2:i);ref->m_pUnknown10=items[i];itemIcons[i]=L"item";if(i<itemCount)inventory->add(ref);}
 if(c.mode==20)inventory->m_nCapacity=1;
 *(CGameUI**)0x14b9c68=ui[0];new((void*)0x14b7d08)std::wstring();
 if(c.mode==21){new((void*)0x14b9c78)std::wstring(L"cached weapon");*(unsigned long long*)0x14b9c70=1;}else{memset((void*)0x14b9c78,0,sizeof(std::wstring));*(unsigned long long*)0x14b9c70=0;}
 detour::Set d;
#define R(N,F) TL_REDIRECT(d,N,&F)
 R(scaledFn,scaled);R(convertFn,convert);R(translateSingletonFn,getTranslator);R(translateFn,translate);R(knownFn,known);R(iconFn,icon);R(effectiveFn,effective);R(valueFn,value);R(narrowFn,narrow);R(uiImageFn,getImage);R(isaFn,isa);R(dataFn,getData);R(masterFn,master);R(ratioFn,ratio);R(widthFn,screenWidth);R(heightFn,screenHeight);
#undef R
#define I(N,F) d.redirect(N,N,&F)
 I(addFn,add);I(sizeFn,size);I(posFn,position);I(imageStringFn,imageString);I(propertyFn,property);I(frontFn,front);I(tooltipFn,tooltip);I(textFn,text);I(visibleFn,visible);I(enabledFn,enabled);I(idFn,setId);I(getWidthFn,getWidth);I(getHeightFn,getHeight);
#undef I
 if(d.failed())_exit(43);
 float x=c.placement==0?-1.0f:c.placement==1?25.5f:500.0f,y=c.placement==0?-1.0f:c.placement==1?300.25f:10.0f;
 CBaseUnit* target=c.mode==1?0:owner;
 if(ours)autotest::invoke(out,&newShow,fold,target,x,y,bool(c.flags&1),bool(c.flags&2));else autotest::invoke(out,&oldShow,fold,target,x,y,bool(c.flags&1),bool(c.flags&2));
 n(100);unsigned char snapshot[sizeof(CSkillFoldout)];memcpy(snapshot,fold,sizeof(snapshot));canon(snapshot,0x338,uiid(fold->m_pGameUI));canon(snapshot,0x340,wid(fold->m_pParent));canon(snapshot,0x348,wid(fold->m_pWindow));for(unsigned col=0;col<10;++col)for(unsigned row=0;row<10;++row){unsigned k=col*10+row;canon(snapshot,0x350+k*8,wid(fold->m_Icons[col][row]));canon(snapshot,0x670+k*8,wid(fold->m_Hotkeys[col][row]));}cap->add(snapshot,sizeof(snapshot));
 for(unsigned i=0;i<204;++i){CEGUI::Window* p=windows[i];n(wid(p->d_parent));n(p->d_visible);n(p->d_enabled);n(p->d_ID);n(p->d_userData?(intptr_t)p->d_userData-(intptr_t)fold:-1);str(p->d_text);str(p->d_tooltipText);}cap->add(sizes,sizeof(sizes));cap->add(positions,sizeof(positions));cap->add(effectiveCalls,sizeof(effectiveCalls));n(knownCalls);n(scaleCalls);n(ratioCalls);n(*(unsigned char*)0x14b9c70);if(*(unsigned char*)0x14b9c70)cap->addText(*(std::wstring*)0x14b9c78);cap->add(&branches,sizeof(branches));
}
void a(void* p,autotest::Capture& out){side(*(Case*)p,false,out);}void b(void* p,autotest::Capture& out){side(*(Case*)p,true,out);}
}
TL_TEST(skill_foldout_show_differential){
 autotest::Coverage coverage("skill_foldout_show_differential",(uint64_t)(uintptr_t)&oldShow);unsigned total=0;unsigned long long all=0;
 for(unsigned mode=0;mode<22;++mode)for(unsigned scale=0;scale<6;++scale)for(unsigned flags=0;flags<4;++flags)for(unsigned mutate=0;mutate<2;++mutate)for(unsigned placement=0;placement<3;++placement){
  Case c={mode,scale,flags,mutate,placement};autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);++total;
  if(x.capture.length>=8){unsigned long long f;memcpy(&f,x.capture.data+x.capture.length-8,8);all|=f;}
  if(coverage.observe(host,x,y)){coverage.report(host);size_t first=0;while(first<x.capture.length&&first<y.capture.length&&x.capture.data[first]==y.capture.data[first])++first;host->log("    case mode %u scale %u flags %u mutate %u placement %u exits %d/%d lengths %lu/%lu first %lu\n",mode,scale,flags,mutate,placement,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length,(unsigned long)first);for(size_t off=first>48?(first-48)&~size_t(3):0;off<first+100&&off+4<=x.capture.length&&off+4<=y.capture.length;off+=4){int u,v;memcpy(&u,x.capture.data+off,4);memcpy(&v,y.capture.data+off,4);float uf,vf;memcpy(&uf,&u,4);memcpy(&vf,&v,4);host->log("      %lu %d/%d floats %g/%g\n",(unsigned long)off,u,v,double(uf),double(vf));}return 1;}
 }
 coverage.report(host);host->log("    foldout: %u full-body cases, branch witnesses 0x%llx\n",total,all);return all==63?0:1;
}
