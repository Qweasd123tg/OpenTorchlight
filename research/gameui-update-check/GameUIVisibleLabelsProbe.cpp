#define OTL_RECOVERED_TEST_PLT
#include "implementation/RecoveredPhases.h"
// Complete controlled active-character frames: hidden labels, no perf overlay or queued tips.
#include <cstring>
#include <new>
#include <Ogre.h>
#include <limits>
#include <CEGUIcolour.h>
#include <CEGUIPropertyHelper.h>
#include <stdexcept>
#include <string>
#include <CEGUIString.h>
#include <CEGUIUDim.h>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void originalUpdate(void*,float,void*,void*) __asm__("__tlorig__ZN7CGameUI14updateIngameUIEfP11CGameClientPN4Ogre12RenderWindowE");
extern "C" std::string originalNumber(int) __asm__("__tlorig__ZN7STRINGS16GetValueAsStringEi");
extern "C" std::string originalNarrow(const wchar_t*) __asm__("__tlorig__ZN7STRINGS21StringConvertToNarrowEPKw");
extern "C" std::string originalUnsigned(unsigned) __asm__("__tlorig__ZN7STRINGS16GetValueAsStringEj");
extern "C" std::string originalUTF8(const std::wstring&) __asm__("__tlorig__ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(uiHeight,"_ZN7CGameUI15getWindowHeightEv")
TL_FUNCTION(rightEdge,"_ZN7CGameUI15rightScreenEdgeEv")
TL_FUNCTION(leftEdge,"_ZN7CGameUI14leftScreenEdgeEv")
TL_FUNCTION(settingsFloat,"_ZN20CDynamicPropertyFile8GetFloatEj")
TL_FUNCTION(textEvents,"_ZN7CGameUI16updateTextEventsEfRN4Ogre7Vector3ERNS0_7Matrix4Eb")
TL_FUNCTION(hideItem,"_ZN5CItem12hideItemTextEv")
TL_FUNCTION(hideCharacter,"_ZN10CCharacter17hideCharacterTextEv")
TL_FUNCTION(consoleVisible,"_ZN8CConsole10getVisibleEv")
TL_FUNCTION(consoleUpdate,"_ZN8CConsole6updateEf")
TL_FUNCTION(finalMenuUpdate,"_ZN12CMenuManager6updateEfP11CGameClientPN4Ogre12RenderWindowE")
TL_FUNCTION(uiWidth,"_ZN7CGameUI14getWindowWidthEv")
TL_FUNCTION(leftCovered,"_ZN7CGameUI11leftCoveredEv")
TL_FUNCTION(petNearDeath,"_ZN10CCharacter14isPetNearDeathEv")
TL_FUNCTION(levelName,"_ZN6CLevel7getNameEv")
TL_FUNCTION(settingsGet,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(mousePressed,"_ZN13CMouseManager13buttonPressedE12EMouseButton")
TL_FUNCTION(mouseHeld,"_ZN13CMouseManager10buttonHeldE12EMouseButton")
TL_FUNCTION(updateSlots,"_ZN7CGameUI11updateSlotsEv")
TL_FUNCTION(editorSingleton,"_ZN7CEditor12getSingletonEv")
TL_FUNCTION(modalPartial,"_ZN7CGameUI22modalDialogOpenPartialEv")
TL_FUNCTION(characterHP,"_ZN10CCharacter2HPEv")
TL_FUNCTION(characterMaxHP,"_ZN10CCharacter5maxHPEv")
TL_FUNCTION(characterMana,"_ZN10CCharacter9manaFloatEv")
TL_FUNCTION(characterMaxMana,"_ZN10CCharacter7maxManaEv")
TL_FUNCTION(experienceGate,"_ZN22CMasterResourceManager14experienceGateEi")
TL_FUNCTION(masterSingleton,"_ZN22CMasterResourceManager12getSingletonEv")
namespace {
template<class T> T& at(void* p,unsigned offset) {
    return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);
}
struct Case { int hp,maxhp,maxmana; float mana; unsigned seed,mode,label; int xp,level; unsigned pattern,xpmode; unsigned petShow,petMode,cacheMatches,petKind,petCallback,textFlags,petStats;float timer; unsigned levelPresent,modalFlag,clockCallback,initialText,menuMode,interactiveFlag,subCount,dropCount;float duration0,alpha0,duration1,alpha1,elapsed; unsigned cameraMode,rotation,listCount,consoleMode;float screenWidth,screenHeight;unsigned labelHeld,labelCovered,labelHidden,labelHover,labelMode;int labelToggle;float labelX,labelY,labelWidth,labelHeight; };
struct TextWindow { unsigned char padding[0xc0];CEGUI::String text; };
struct Node{void* value;Node* next;};
struct World {
    unsigned long long ui[0x1a08/8],actors[2][0x700/8],radio[0x800/8];
    unsigned long long cinema[0x100/8],editor[0x100/8],menu[8],vt[16],target,settings,managers[2],pets[2][0x720/8],client[0x80/8],level[2][0x200/8];void* petEntries[2][1];TextWindow* nameWindow;TextWindow* statusWindow;unsigned managerCalls,gateCalls,modalCalls;TextWindow* extra[4];unsigned long long interactive[2][8],children[8][8],dropdownVT[16];void* lists[2][4];void* alternate[2][4];bool changed[2];unsigned long long cameras[2],cameraVT[0x2e0/8],itemTokens[4][0x230/8],characterTokens[4][0x490/8],consoles[2],finalMenus[2],renderWindow;Node itemNodes[2][2],characterNodes[2][2];Node* itemHeads[2];Node* characterHeads[2];Ogre::Quaternion* rotations;Ogre::Vector3* positions;Ogre::Matrix4* projections;unsigned orientationCalls;
    World() { std::memset(this,0,sizeof(*this)); }
};
World* world;
const Case* input;
autotest::Capture* output;
bool reachedBoundary;
const char* hpLabels[]={"HP","Здоровье","生命"};
const char* fleeLabels[]={"Fleeing","Бежит","逃跑"};
const char* xpLabels[]={"XP","Опыт","经验"};
const char* manaLabels[]={"Mana","Мана","魔力"};
void number(unsigned value) { output->add(&value,sizeof(value)); }
unsigned actorID(void* actor) { return actor==world->actors[0]?0:actor==world->actors[1]?1:actor==world->pets[0]?2:actor==world->pets[1]?3:99; }
void* actor() { return at<void*>(world->ui,0x38); }
int setting(void* self,unsigned key) {number(60);number(self==&world->settings);if(key==*reinterpret_cast<unsigned*>(0x150b624)){number(1);return 77;}number(2);return input->labelToggle;}
bool pressed(void*,unsigned) { return true; }
void unused(void*) {}
bool modal(void* self) {++world->modalCalls;number(30);number(self==world->ui);return world->modalCalls==1?true:input->modalFlag!=0;}
void* editor() { return world->editor; }
void closeMenu(void*,bool) {}
bool notOpen(void*) { return false; }
void finish();
void visible(void* window,bool value) {
    for(unsigned i=0;i<4;++i)if(window==world->extra[i]){number(31);number(i);number(value);}
    if(window==reinterpret_cast<void*>(0x138)){number(32);number(value);}
    if(window==reinterpret_cast<void*>(0x170)){number(23);number(value);if(value&&input->petCallback==2)world->petEntries[0][0]=world->pets[1];}
    if(window==world->statusWindow){number(24);number(value);}
    if(window==reinterpret_cast<void*>(0x140)||window==reinterpret_cast<void*>(0x158)) {
        number(10); number(reinterpret_cast<unsigned long>(window)); number(value);
    }
}
int hp(void* who) { unsigned id=actorID(who);number(11);number(id);const int values[]={-1,25,200,0};return id>=2?values[input->petStats]+int(id-2)*3:input->hp+int(id)*7; }
int maxhp(void* who) { unsigned id=actorID(who);number(12);number(id);const int values[]={1,100,100,0};return id>=2?values[input->petStats]+int(id-2)*5:input->maxhp+int(id)*2; }
float mana(void* who) { unsigned id=actorID(who);number(13);number(id);const float values[]={-0.25f,12.75f,250.75f,0};return id>=2?values[input->petStats]+float(id-2)*0.625f:input->mana+float(id)*0.625f; }
int maxmana(void* who) { unsigned id=actorID(who);number(14);number(id);const int values[]={1,100,100,0};return id>=2?values[input->petStats]+int(id-2)*7:input->maxmana+int(id)*3; }
void position(void* window,const CEGUI::UVector2& value) {
    number(15);number(reinterpret_cast<unsigned long>(window));output->add(&value,sizeof(value));
    if(input->mode==1&&window==reinterpret_cast<void*>(0x140)) at<float>(world->ui,0x1724)=-3.5f;
    if(input->mode==3&&window==reinterpret_cast<void*>(0x150)) at<void*>(world->ui,0x38)=world->actors[1];
}
void size(void* window,const CEGUI::UVector2& value) {
    number(16);number(reinterpret_cast<unsigned long>(window));output->add(&value,sizeof(value));
    if(input->xpmode==4&&window==reinterpret_cast<void*>(0x1d0)){at<int>(actor(),0x448)-=11;at<int>(actor(),0x100)+=2;}
    if(input->mode==2&&window==reinterpret_cast<void*>(0x140)) at<float>(world->ui,0x1728)=17.25f;
}
void tooltip(void* window,const CEGUI::String& value) {
    number(17);number(reinterpret_cast<unsigned long>(window));
    const char* bytes=reinterpret_cast<const char*>(value.c_str());
    unsigned length=std::strlen(bytes);number(length);output->add(bytes,length);
}
void finish() {
    reachedBoundary=true;throw std::runtime_error("gameui level boundary");
}
bool covered(void* self) {
    number(25);number(self==world->ui);
    if(input->petCallback==1)at<void*>(world->ui,0x38)=world->actors[1];
    return input->petShow==1;
}
bool nearDeath(void* who) {number(26);number(actorID(who));return input->petKind==1;}
void select(void* window,bool value) {
    number(27);number(reinterpret_cast<unsigned long>(window));number(value);
    if(input->petCallback==3)at<int>(world->pets[0],0x710)+=10;
}
void text(void* window,const CEGUI::String& value) {
    number(28);unsigned id=window==world->nameWindow?0:window==world->statusWindow?1:99;for(unsigned i=0;i<4;++i)if(window==world->extra[i])id=i+2;number(id);
    const char* bytes=reinterpret_cast<const char*>(value.c_str());unsigned length=std::strlen(bytes);
    number(length);output->add(bytes,length);
    static_cast<TextWindow*>(window)->text=value;
    if(window==world->extra[1]&&input->clockCallback==1){at<float>(world->ui,0x1980)=1;at<float>(world->ui,0x1984)=0.5f;}
    if(window==world->extra[1]&&input->clockCallback==5){at<float>(world->ui,0x1980)=-1;at<float>(world->ui,0x1984)=std::numeric_limits<float>::quiet_NaN();}
    if(window==world->extra[0]&&input->clockCallback==4)at<void*>(world->client,0x70)=NULL;
    if(window==world->nameWindow&&input->petCallback==4)at<int>(world->pets[0],0x330)=0x2a;
}
std::wstring levelValue(void* level) {number(29);number(level==&world->level);const wchar_t* names[]={L"Town",L"Город",L"城镇"};return std::wstring(names[input->label])+(level==world->level[1]?L" II":L"");}
float widthRead(void* self){number(33);number(self==world->ui);return input->screenWidth;}
float heightRead(void* self){number(36);number(self==world->ui);if(input->cameraMode==1)at<float>(world->ui,0x1684)=1000.0f;return input->screenHeight;}
float rightRead(void* self){number(37);number(self==world->ui);return input->screenWidth-30.0f;}
float leftRead(void* self){number(38);number(self==world->ui);return 20.0f;}
float settingFloat(void* settings,unsigned key){number(39);number(settings==&world->settings);number(key==*reinterpret_cast<unsigned*>(0x150b470));if(input->cameraMode==2)at<void*>(world->ui,0x10)=&world->cameras[1];return 17.5f;}
unsigned cameraID(void* p){return p==&world->cameras[0]?0:p==&world->cameras[1]?1:99;}
void* camera(){return at<void*>(world->ui,0x10);}
const Ogre::Quaternion& cameraOrientation(void* p){unsigned id=cameraID(p);number(40);number(id);++world->orientationCalls;if(input->cameraMode==3&&world->orientationCalls==1)at<void*>(world->ui,0x10)=&world->cameras[1];return world->rotations[id%2];}
const Ogre::Vector3& cameraPosition(void* p){unsigned id=cameraID(p);number(41);number(id);if(input->cameraMode==5)at<void*>(world->ui,0x10)=&world->cameras[1];return world->positions[id%2];}
const Ogre::Matrix4& cameraProjection(void* p){unsigned id=cameraID(p);number(42);number(id);if(input->cameraMode==4)at<void*>(world->ui,0x10)=&world->cameras[1];return world->projections[id%2];}
void events(void* self,float elapsed,Ogre::Vector3& up,Ogre::Matrix4& matrix,bool active){number(43);number(self==world->ui);output->add(&elapsed,sizeof(elapsed));output->add(&up,sizeof(up));output->add(&matrix,sizeof(matrix));number(active);output->add(reinterpret_cast<char*>(world->ui)+0x1680,12);if(input->cameraMode==7)at<void*>(world->client,0x70)=world->level[1];}
unsigned itemID(void* p){for(unsigned i=0;i<4;++i)if(p==&world->itemTokens[i])return i;return 99;}
unsigned characterID(void* p){for(unsigned i=0;i<4;++i)if(p==&world->characterTokens[i])return i;return 99;}
void itemHidden(void* p){unsigned id=itemID(p);number(44);number(id);if(input->cameraMode==8&&id==0)at<void*>(world->client,0x70)=world->level[1];if(input->cameraMode==9&&id==0)world->itemNodes[0][0].next=NULL;}
void characterHidden(void* p){unsigned id=characterID(p);number(45);number(id);if(input->cameraMode==10&&id==0)world->characterNodes[0][0].next=NULL;}
bool consoleIsVisible(void* p){number(46);number(p==&world->consoles[0]?0:1);if(input->cameraMode==6){at<void*>(world->ui,0x1690)=&world->consoles[1];at<void*>(world->ui,0x588)=&world->finalMenus[1];}return input->consoleMode==2;}
void consoleTick(void* p,float elapsed){number(47);number(p==&world->consoles[0]?0:1);output->add(&elapsed,sizeof(elapsed));if(input->cameraMode==6)at<void*>(world->ui,0x588)=&world->finalMenus[0];}
void finalTick(void* p,float elapsed,void* client,void* window){number(48);number(p==&world->finalMenus[0]?0:1);output->add(&elapsed,sizeof(elapsed));number(client==world->client);number(window==&world->renderWindow);}
void captureString(const CEGUI::String& value){const char* bytes=reinterpret_cast<const char*>(value.c_str());unsigned length=std::strlen(bytes);number(length);output->add(bytes,length);}
void property(void* window,const CEGUI::String& key,const CEGUI::String& value){
    number(34);unsigned id=99;for(unsigned i=0;i<4;++i)if(window==world->extra[i])id=i;number(id);captureString(key);captureString(value);
    if((window==world->extra[1]||window==world->extra[3])&&key==CEGUI::String("TextColour")){
        if(input->clockCallback==2)at<void*>(world->ui,0x110)=world->extra[3];
        if(input->clockCallback==3)at<float>(world->ui,0x1994)=0;
    }
}
unsigned tickID(void* object){if(object==world->menu)return 16;if(object==world->interactive[0])return 17;if(object==world->interactive[1])return 18;for(unsigned i=0;i<8;++i)if(object==world->children[i])return i;return 99;}
void tick(void* object,float elapsed){
    unsigned id=tickID(object);number(35);number(id);output->add(&elapsed,sizeof(elapsed));
    if(id<8){unsigned family=id/4;unsigned base=family?0x1948:0x1930;void** begin=at<void**>(world->ui,base);void** end=at<void**>(world->ui,base+8);unsigned count=end-begin;
        if(!world->changed[family]){world->changed[family]=true;
            if(input->menuMode==1&&count<4)at<void**>(world->ui,base+8)=begin+count+1;
            if(input->menuMode==2)at<void**>(world->ui,base+8)=begin;
            if(input->menuMode==3){at<void**>(world->ui,base)=world->alternate[family];at<void**>(world->ui,base+8)=world->alternate[family]+count;}
        }
    }
    if(input->menuMode==4&&id==16)at<void*>(world->ui,0x570)=world->interactive[1];
    if(input->menuMode==4&&id==18)at<void*>(world->ui,0x570)=world->interactive[0];
}
std::string timerText(float remaining) {
    unsigned minutes=0,hours=0;
    while(remaining>=60.0f){remaining-=60.0f;++minutes;}
    while(minutes>59){minutes-=60;++hours;}
    return originalUnsigned(hours)+":"+(minutes<10?"0":"")+originalUnsigned(minutes)+":"+
        (remaining<10.0f?"0":"")+originalNumber(int(remaining));
}
void* manager() {
    ++world->managerCalls;number(19);number(world->managerCalls);
    if(input->xpmode==1&&world->managerCalls==1)at<int>(actor(),0x448)+=37;
    if(input->xpmode==2&&world->managerCalls==1)at<int>(actor(),0x100)+=4;
    if(input->xpmode==5&&world->managerCalls==4)at<void*>(world->ui,0x38)=world->actors[1];
    return &world->managers[world->managerCalls%2];
}
int gate(void* resource,int level) {
    number(20);number(resource==&world->managers[0]?0:1);number(level);
    const int patterns[][4]={{0,100,0,100},{100,200,100,200},{200,100,200,100},
        {0,0,0,0},{50,150,75,200},{16777216,16777217,16777216,16777217}};
    unsigned call=world->gateCalls++;
    if(call>=4)_exit(46);
    if(input->xpmode==3&&call==0)at<void*>(world->ui,0x38)=world->actors[1];
    return patterns[input->pattern][call];
}
CEGUI::UVector2& cached(unsigned offset) { return at<CEGUI::UVector2>(world->ui,offset); }
void bar(unsigned pos,unsigned dim,unsigned window,unsigned sub,float ratio) {
    if(ratio<0.0f) ratio=0.0f;
    position(reinterpret_cast<void*>(window),CEGUI::UVector2(
        CEGUI::UDim(0,cached(pos).d_x.asAbsolute(1)),
        CEGUI::UDim(0,(cached(pos).d_y.asAbsolute(1)+cached(dim).d_y.asAbsolute(1))-
                         cached(dim).d_y.asAbsolute(1)*ratio)));
    size(reinterpret_cast<void*>(window),CEGUI::UVector2(
        CEGUI::UDim(0,cached(dim).d_x.asAbsolute(1)),
        CEGUI::UDim(0,cached(dim).d_y.asAbsolute(1)*ratio)));
    position(reinterpret_cast<void*>(sub),CEGUI::UVector2(CEGUI::UDim(0,0),
        CEGUI::UDim(0,-(cached(dim).d_y.asAbsolute(1)-cached(dim).d_y.asAbsolute(1)*ratio))));
}
void petHUD() {
    unsigned long begin=at<unsigned long>(actor(),0x648),end=at<unsigned long>(actor(),0x650);
    if(unsigned((end-begin)>>3)!=0&&!covered(world->ui)) {
        begin=at<unsigned long>(actor(),0x648);end=at<unsigned long>(actor(),0x650);
        void* pet=(end-begin)>>3?*reinterpret_cast<void**>(begin):NULL;
        visible(reinterpret_cast<void*>(0x170),true);
        int mode=at<int>(pet,0x710);
        if(mode!=at<int>(world->ui,0x16c8)) {
            at<int>(world->ui,0x16c8)=mode;
            if(mode==0)select(reinterpret_cast<void*>(0x1c8),true);
            else if(mode==1)select(reinterpret_cast<void*>(0x1b8),true);
            else if(mode==2)select(reinterpret_cast<void*>(0x1c0),true);
        }
        float ratio=float(hp(pet));ratio/=float(maxhp(pet));if(ratio<0)ratio=0;
        size(reinterpret_cast<void*>(0x180),CEGUI::UVector2(
            CEGUI::UDim(0,float(int(cached(0x174c).d_x.asAbsolute(1)*ratio))),
            CEGUI::UDim(0,cached(0x174c).d_y.asAbsolute(1))));
        ratio=mana(pet);ratio/=float(maxmana(pet));if(ratio<0)ratio=0;
        size(reinterpret_cast<void*>(0x190),CEGUI::UVector2(
            CEGUI::UDim(0,float(int(cached(0x175c).d_x.asAbsolute(1)*ratio))),
            CEGUI::UDim(0,cached(0x175c).d_y.asAbsolute(1))));
        {
            std::string top=originalNumber(maxhp(pet)),now=originalNumber(hp(pet));
            std::string value=std::string(hpLabels[input->label])+":"+now+"/"+top;
            CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));
            tooltip(reinterpret_cast<void*>(0x178),converted);
        }
        {
            std::string top=originalNumber(maxmana(pet)),now=originalNumber(int(mana(pet)));
            std::string value=std::string(manaLabels[input->label])+":"+now+"/"+top;
            CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));
            tooltip(reinterpret_cast<void*>(0x198),converted);
        }
        std::string narrow=originalNarrow(at<const wchar_t*>(pet,0x4c0));
        CEGUI::String name(reinterpret_cast<const CEGUI::utf8*>(narrow.c_str()));
        if(world->nameWindow->text!=name) {
            CEGUI::String fresh(name.c_str());text(world->nameWindow,fresh);
        }
        if(at<int>(pet,0x330)==0x2a) {
            std::string value=timerText(at<float>(pet,0x684));
            if(world->statusWindow->text!=value) {
                CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));
                text(world->statusWindow,converted);
            }
            visible(world->statusWindow,true);
        } else if(nearDeath(pet)) {
            std::string value=std::string(fleeLabels[input->label])+"!";
            if(world->statusWindow->text!=value) {
                CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));
                text(world->statusWindow,converted);
            }
            visible(world->statusWindow,true);
        } else visible(world->statusWindow,false);
    } else visible(reinterpret_cast<void*>(0x170),false);
}
void message(unsigned pointer,unsigned stringOffset,unsigned durationOffset,unsigned alphaOffset){
    if(at<float>(world->ui,alphaOffset)>0){
        std::string value=originalUTF8(at<std::wstring>(world->ui,stringOffset));
        TextWindow* current=at<TextWindow*>(world->ui,pointer);
        if(current->text!=value){CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));text(at<void*>(world->ui,pointer),converted);}
        float duration=at<float>(world->ui,durationOffset)-input->elapsed;
        float oldAlpha=at<float>(world->ui,alphaOffset);
        at<float>(world->ui,durationOffset)=duration;
        if(duration<=0){at<float>(world->ui,durationOffset)=0;at<float>(world->ui,alphaOffset)=oldAlpha+input->elapsed*(-2.0f);}
        float alpha=at<float>(world->ui,alphaOffset);
        if(alpha!=oldAlpha){
            float rendered=alpha>0?alpha:0;
            property(at<void*>(world->ui,pointer),CEGUI::String("TextColour"),CEGUI::PropertyHelper::colourToString(CEGUI::colour(1,1,1,rendered)));
            property(at<void*>(world->ui,pointer),CEGUI::String("DropTextColour"),CEGUI::PropertyHelper::colourToString(CEGUI::colour(0,0,0,rendered)));
        }
        visible(at<void*>(world->ui,pointer),true);
    }else visible(at<void*>(world->ui,pointer),false);
}
void levelAndMessages(){
    void* level=at<void*>(world->client,0x70);
    if(level){
        std::wstring wide=levelValue(level);std::string value=originalUTF8(wide);
        TextWindow* current=at<TextWindow*>(world->ui,0x100);
        if(current->text!=value){CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));text(at<void*>(world->ui,0x100),converted);}
        visible(at<void*>(world->ui,0x100),true);
        if(modal(world->ui)){visible(at<void*>(world->ui,0x110),false);visible(at<void*>(world->ui,0x118),false);}
        else{message(0x110,0x1978,0x1980,0x1984);message(0x118,0x1988,0x1990,0x1994);}
    }
}
void tickMenus(){
    for(unsigned family=0;family<2;++family){unsigned base=family?0x1948:0x1930;
        for(unsigned i=0;i<unsigned(at<void**>(world->ui,base+8)-at<void**>(world->ui,base));++i)tick(at<void**>(world->ui,base)[i],input->elapsed);
    }
    tick(at<void*>(world->ui,0x578),input->elapsed);tick(at<void*>(world->ui,0x570),input->elapsed);
    bool interactive=at<unsigned char>(at<void*>(world->ui,0x570),0x38)!=0;
    visible(reinterpret_cast<void*>(0x138),!interactive);visible(reinterpret_cast<void*>(0x140),!interactive);
    if(interactive)visible(reinterpret_cast<void*>(0x170),false);
}
bool both(void* self){number(61);number(self==world->ui);return input->labelCovered;}
bool key(void* self,unsigned key){number(62);number(self==reinterpret_cast<char*>(world->ui)+0x590);number(key);return input->labelHeld;}
bool isA(void* p,unsigned type){number(63);number(itemID(p));number(type);return input->labelHover==2;}
void* cast(void* p,const void* src,const void* dst,long offset){number(64);number(itemID(p));number(src==reinterpret_cast<void*>(0xfd1da0));number(dst==reinterpret_cast<void*>(0xfd10c0));number(offset);return NULL;}
Ogre::Vector3 objectPosition(void* p,bool absolute){number(65);number(itemID(p));number(characterID(p));number(absolute);return Ogre::Vector3(1,2,3);}
Ogre::Vector3 screenPosition(void* self,const Ogre::Vector3* pos,const Ogre::Vector3* up,Ogre::Matrix4 matrix){number(66);number(self==world->ui);output->add(pos,sizeof(*pos));output->add(up,sizeof(*up));output->add(&matrix,sizeof(matrix));return Ogre::Vector3(input->labelX,input->labelY,-1);}
void shown(void* p,bool character){number(67);number(character);number(character?characterID(p):itemID(p));
 if(input->labelMode==1){at<float>(world->ui,0x1684)=320;at<float>(world->ui,0x1688)=240;}
 if(input->labelMode==2){at<float>(p,character?0x46c:0x220)=999;at<float>(p,character?0x474:0x228)=888;}
 if(input->labelMode==3)at<void*>(p,character?0x478:0x1e8)=reinterpret_cast<void*>(0x3010+(character?0x100:0));
}
void itemShown(void* p){shown(p,false);}void characterShown(void* p){shown(p,true);}
void activeCameraAndTail(){
    at<float>(world->ui,0x1684)=widthRead(world->ui);at<float>(world->ui,0x1688)=heightRead(world->ui);
    float right=rightRead(world->ui);float left=leftRead(world->ui);
    at<float>(world->ui,0x1680)=(right-left)/at<float>(world->ui,0x1684);
    settingFloat(at<void*>(world->ui,0x78),*reinterpret_cast<unsigned*>(0x150b470));
    Ogre::Matrix3 rotation;cameraOrientation(camera()).ToRotationMatrix(rotation);
    Ogre::Matrix4 view=Ogre::Matrix4::IDENTITY;view=rotation;view.setTrans(cameraPosition(camera()));view=view.inverse();
    Ogre::Matrix4 matrix=cameraProjection(camera())*view;Ogre::Vector3 up=cameraOrientation(camera()).yAxis();editor();
    events(world->ui,input->elapsed,up,matrix,true);
    void* level=at<void*>(world->client,0x70);Node* item=*at<Node**>(level,0xc0);
    while(item){modal(world->ui);itemHidden(item->value);item=item->next;}
    level=at<void*>(world->client,0x70);Node* character=*at<Node**>(level,0xc8);
    while(character){modal(world->ui);characterHidden(character->value);character=character->next;}
    modal(world->ui);
    void* console=at<void*>(world->ui,0x1690);if(console&&consoleIsVisible(console))consoleTick(at<void*>(world->ui,0x1690),input->elapsed);
    finalTick(at<void*>(world->ui,0x588),input->elapsed,world->client,&world->renderWindow);
}
void model(){gameui_recovered::Labels labels={hpLabels[input->label],manaLabels[input->label],xpLabels[input->label],fleeLabels[input->label]};
 gameui_recovered::Frame frame(world->ui,world->client,&world->renderWindow,input->elapsed,labels);
 frame.run();
}
void side(void* context,autotest::Capture& capture,bool expected) {
    Case& c=*static_cast<Case*>(context);TextWindow nameWindow,statusWindow,extra[4];std::wstring names[2]={L"Buddy",L"Fox"};Ogre::Quaternion rotations[2];Ogre::Vector3 positions[2];Ogre::Matrix4 projections[2];World state;world=&state;input=&c;output=&capture;reachedBoundary=false;
    for(unsigned i=0;i<4;++i)world->extra[i]=&extra[i];
    gameui_recovered::service::keyShowItems=101;gameui_recovered::settingsToggleNames=102;
    world->rotations=rotations;world->positions=positions;world->projections=projections;
    world->cameraVT[0x2d8/8]=reinterpret_cast<unsigned long long>(&cameraProjection);
    world->cameras[0]=world->cameras[1]=reinterpret_cast<unsigned long long>(world->cameraVT);
    at<void*>(world->ui,0x10)=&world->cameras[0];at<unsigned char>(world->ui,0x1999)=c.labelHidden;
    at<void*>(world->ui,0x68)=c.labelHover?world->itemTokens[0]:NULL;at<void*>(world->ui,0x58)=c.labelHover?world->characterTokens[0]:NULL;
    for(unsigned j=0;j<4;++j){at<void*>(world->itemTokens[j],0x1e8)=reinterpret_cast<void*>(0x3000+j);at<void*>(world->characterTokens[j],0x478)=reinterpret_cast<void*>(0x3100+j);at<float>(world->itemTokens[j],0x220)=c.labelWidth;at<float>(world->itemTokens[j],0x228)=c.labelHeight;at<float>(world->characterTokens[j],0x46c)=c.labelWidth;at<float>(world->characterTokens[j],0x474)=c.labelHeight;}
    at<void*>(world->ui,0x1690)=c.consoleMode?&world->consoles[0]:NULL;at<void*>(world->ui,0x588)=&world->finalMenus[0];
    const Ogre::Quaternion qs[]={Ogre::Quaternion(1,0,0,0),Ogre::Quaternion(0.70710677f,0,0.70710677f,0),Ogre::Quaternion(0.5f,0.5f,0.5f,0.5f),Ogre::Quaternion(0.7f,0.2f,0.1f,0.3f)};
    for(unsigned i=0;i<2;++i){
        rotations[i]=qs[(c.rotation+i)%4];positions[i]=Ogre::Vector3(float(c.rotation)-2.0f+i,float(i)-0.5f,3.0f+i);
        projections[i]=Ogre::Matrix4::IDENTITY;projections[i][0][0]=1.25f+float(c.rotation)/16;projections[i][0][2]=0.2f*c.rotation;projections[i][1][1]=0.75f;projections[i][1][3]=2;projections[i][2][2]=-1.01f;projections[i][2][3]=-0.2f;projections[i][3][2]=-1;projections[i][3][3]=0;
        for(unsigned j=0;j<2;++j){world->itemNodes[i][j].value=&world->itemTokens[i*2+j];world->characterNodes[i][j].value=&world->characterTokens[i*2+j];world->itemNodes[i][j].next=j+1<c.listCount?&world->itemNodes[i][j+1]:NULL;world->characterNodes[i][j].next=j+1<c.listCount?&world->characterNodes[i][j+1]:NULL;}
        world->itemHeads[i]=c.listCount?&world->itemNodes[i][0]:NULL;world->characterHeads[i]=c.listCount?&world->characterNodes[i][0]:NULL;
        at<void*>(world->level[i],0xc0)=&world->itemHeads[i];at<void*>(world->level[i],0xc8)=&world->characterHeads[i];
    }
    world->nameWindow=&nameWindow;world->statusWindow=&statusWindow;
    for(unsigned i=0;i<2;++i){
        world->petEntries[i][0]=world->pets[i];
        at<void*>(world->actors[i],0x648)=world->petEntries[i];
        at<void*>(world->actors[i],0x650)=world->petEntries[i]+(c.petShow!=0?1:0);
        at<int>(world->pets[i],0x710)=i==0?int(c.petMode):int((c.petMode+1)%3);
        at<int>(world->pets[i],0x330)=c.petKind==2?0x2a:2;
        at<float>(world->pets[i],0x684)=c.timer;
        at<const wchar_t*>(world->pets[i],0x4c0)=names[i].c_str();
    }
    at<int>(world->ui,0x16c8)=c.cacheMatches?int(c.petMode):int(c.petMode)+1;
    at<void*>(world->client,0x70)=c.levelPresent?&world->level:NULL;
    nameWindow.text=CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(c.textFlags&1?"Buddy":"different"));
    std::string initial=c.petKind==2?timerText(c.timer):std::string(fleeLabels[c.label])+"!";
    statusWindow.text=CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(c.textFlags&2?initial.c_str():"different"));
    at<void*>(world->ui,0x78)=&world->settings;at<void*>(world->ui,0x200)=world->radio;
    at<void*>(world->ui,0x540)=world->cinema;at<unsigned char>(world->cinema,0x31)=1;
    at<void*>(world->ui,0x38)=world->actors[0];
    for(unsigned i=0;i<2;++i) { at<int>(world->actors[i],0x330)=2;at<int>(world->actors[i],0x100)=c.level+int(i)*3;at<int>(world->actors[i],0x448)=c.xp+int(i)*5;at<void*>(world->actors[i],0x340)=&world->target; }
    at<unsigned char>(world->editor,0x64)=2;
    world->vt[3]=reinterpret_cast<unsigned long long>(&closeMenu);
    world->vt[5]=reinterpret_cast<unsigned long long>(&notOpen);
    world->menu[0]=reinterpret_cast<unsigned long long>(world->vt);
    at<void*>(world->ui,0x578)=world->menu;at<void*>(world->ui,0x4d8)=world->menu;
    const unsigned windows[]={0x140,0x148,0x150,0x158,0x160,0x168,0x1d0,0x1d8,0x170,0x178,0x180,0x190,0x198,0x1b8,0x1c0,0x1c8};
    for(unsigned i=0;i<16;++i) at<void*>(world->ui,windows[i])=reinterpret_cast<void*>(windows[i]);
    at<void*>(world->ui,0x1b0)=&nameWindow;at<void*>(world->ui,0x1a8)=&statusWindow;
    const float values[]={-3.5f,-0.5f,0,0.5f,2.5f,17.25f};
    for(unsigned i=0;i<8;++i) {
        at<float>(world->ui,0x16cc+i*4)=values[(c.seed+i)%6];
        at<float>(world->ui,0x171c+i*4)=values[(c.seed*3+i+2)%6];
    }
    for(unsigned i=0;i<4;++i)at<float>(world->ui,0x173c+i*4)=values[(c.seed+i+1)%6];
    for(unsigned i=0;i<8;++i)at<float>(world->ui,0x174c+i*4)=values[(c.seed+i+2)%6];
    if(c.seed!=0){at<float>(world->ui,0x1750)+=200.0f;at<float>(world->ui,0x1760)+=240.0f;}
    const unsigned long guards[]={0x14b9bb8,0x14b9bc0,0x14b9bc8,0x14b9bd0};
    for(unsigned i=0;i<4;++i) *reinterpret_cast<unsigned char*>(guards[i])=1;
    new(reinterpret_cast<void*>(0x14b9c10))std::string(hpLabels[c.label]);
    new(reinterpret_cast<void*>(0x14b9c08))std::string(manaLabels[c.label]);
    new(reinterpret_cast<void*>(0x14b9c00))std::string(xpLabels[c.label]);
    new(reinterpret_cast<void*>(0x14b9bf8))std::string(fleeLabels[c.label]);
    const wchar_t* notes0[]={L"Notice",L"Сообщение",L"消息"};const wchar_t* notes1[]={L"Warning",L"Ошибка",L"警告"};
    new(reinterpret_cast<char*>(world->ui)+0x1978)std::wstring(notes0[c.label]);
    new(reinterpret_cast<char*>(world->ui)+0x1988)std::wstring(notes1[c.label]);
    at<float>(world->ui,0x1980)=c.duration0;at<float>(world->ui,0x1984)=c.alpha0;
    at<float>(world->ui,0x1990)=c.duration1;at<float>(world->ui,0x1994)=c.alpha1;
    at<void*>(world->ui,0x100)=&extra[0];at<void*>(world->ui,0x110)=&extra[1];at<void*>(world->ui,0x118)=&extra[2];at<void*>(world->ui,0x138)=reinterpret_cast<void*>(0x138);
    const wchar_t* levelNames[]={L"Town",L"Город",L"城镇"};
    for(unsigned i=0;i<4;++i){std::wstring wide=i==0?levelNames[c.label]:i==2?notes1[c.label]:notes0[c.label];std::string value=c.initialText?originalUTF8(wide):"different";extra[i].text=CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(value.c_str()));}
    world->vt[2]=reinterpret_cast<unsigned long long>(&tick);world->vt[10]=reinterpret_cast<unsigned long long>(&tick);
    for(unsigned i=0;i<2;++i){world->interactive[i][0]=reinterpret_cast<unsigned long long>(world->vt);at<unsigned char>(world->interactive[i],0x38)=i?c.interactiveFlag==0:c.interactiveFlag!=0;}
    at<void*>(world->ui,0x570)=world->interactive[0];
    std::memcpy(world->dropdownVT,world->vt,sizeof(world->vt));world->dropdownVT[3]=reinterpret_cast<unsigned long long>(&tick);
    for(unsigned i=0;i<8;++i)world->children[i][0]=reinterpret_cast<unsigned long long>(i<4?world->vt:world->dropdownVT);
    for(unsigned family=0;family<2;++family){unsigned base=family?0x1948:0x1930;for(unsigned i=0;i<4;++i){world->lists[family][i]=world->children[family*4+i];world->alternate[family][i]=world->children[family*4+3-i];}at<void**>(world->ui,base)=world->lists[family];at<void**>(world->ui,base+8)=world->lists[family]+(family?c.dropCount:c.subCount);}
    detour::Set patches;
    TL_REDIRECT(patches,settingsGet,&setting);TL_REDIRECT(patches,mousePressed,&pressed);TL_REDIRECT(patches,mouseHeld,&pressed);
    TL_REDIRECT(patches,updateSlots,&unused);TL_REDIRECT(patches,editorSingleton,&editor);TL_REDIRECT(patches,modalPartial,&modal);
    TL_REDIRECT(patches,characterHP,&hp);TL_REDIRECT(patches,characterMaxHP,&maxhp);
    TL_REDIRECT(patches,characterMana,&mana);TL_REDIRECT(patches,characterMaxMana,&maxmana);TL_REDIRECT(patches,masterSingleton,&manager);TL_REDIRECT(patches,experienceGate,&gate);
    patches.redirect(reinterpret_cast<char*>(0x554718),reinterpret_cast<char*>(0x554718),&visible);
    patches.redirect(reinterpret_cast<char*>(0x5548a8),reinterpret_cast<char*>(0x5548a8),&position);
    patches.redirect(reinterpret_cast<char*>(0x555178),reinterpret_cast<char*>(0x555178),&size);
    patches.redirect(reinterpret_cast<char*>(0x554b48),reinterpret_cast<char*>(0x554b48),&tooltip);
    TL_REDIRECT(patches,leftCovered,&covered);TL_REDIRECT(patches,petNearDeath,&nearDeath);TL_REDIRECT(patches,levelName,&levelValue);TL_REDIRECT(patches,uiWidth,&widthRead);
    patches.redirect(reinterpret_cast<char*>(0x554dc8),reinterpret_cast<char*>(0x554dc8),&select);
    patches.redirect(reinterpret_cast<char*>(0x555c08),reinterpret_cast<char*>(0x555c08),&text);
    patches.redirect(reinterpret_cast<char*>(0x5532d8),reinterpret_cast<char*>(0x5532d8),&property);
    TL_REDIRECT(patches,uiHeight,&heightRead);TL_REDIRECT(patches,rightEdge,&rightRead);TL_REDIRECT(patches,leftEdge,&leftRead);TL_REDIRECT(patches,settingsFloat,&settingFloat);
    TL_REDIRECT(patches,textEvents,&events);TL_REDIRECT(patches,hideItem,&itemHidden);TL_REDIRECT(patches,hideCharacter,&characterHidden);
    TL_REDIRECT(patches,consoleVisible,&consoleIsVisible);TL_REDIRECT(patches,consoleUpdate,&consoleTick);TL_REDIRECT(patches,finalMenuUpdate,&finalTick);
    patches.redirect(reinterpret_cast<char*>(0x554d48),reinterpret_cast<char*>(0x554d48),&cameraOrientation);
    patches.redirect(reinterpret_cast<char*>(0x5545c8),reinterpret_cast<char*>(0x5545c8),&cameraPosition);
    patches.redirect(reinterpret_cast<char*>(0xa82ae0),reinterpret_cast<char*>(0xa82ae0),&both);
    patches.redirect(reinterpret_cast<char*>(0x91a680),reinterpret_cast<char*>(0x91a680),&key);
    patches.redirect(reinterpret_cast<char*>(0x7f62a0),reinterpret_cast<char*>(0x7f62a0),&isA);
    patches.redirect(reinterpret_cast<char*>(0x555758),reinterpret_cast<char*>(0x555758),&cast);
    patches.redirect(reinterpret_cast<char*>(0x9e7080),reinterpret_cast<char*>(0x9e7080),&objectPosition);
    patches.redirect(reinterpret_cast<char*>(0xa82f40),reinterpret_cast<char*>(0xa82f40),&screenPosition);
    patches.redirect(reinterpret_cast<char*>(0x8b60b0),reinterpret_cast<char*>(0x8b60b0),&itemShown);
    patches.redirect(reinterpret_cast<char*>(0x816e20),reinterpret_cast<char*>(0x816e20),&characterShown);
    if(patches.failed()) _exit(42);
    for(unsigned repeat=0;repeat<2;++repeat){
        reachedBoundary=false;world->managerCalls=world->gateCalls=world->modalCalls=world->orientationCalls=0;world->changed[0]=world->changed[1]=false;
        try { if(expected)model();else originalUpdate(world->ui,c.elapsed,world->client,&world->renderWindow); }
        catch(const std::runtime_error&) { _exit(44); }
        output->add(reinterpret_cast<char*>(world->ui)+0x1680,12);number(at<void*>(world->client,0x70)==world->level[0]?0:1);
        output->add(reinterpret_cast<char*>(world->ui)+0x1980,8);output->add(reinterpret_cast<char*>(world->ui)+0x1990,8);
        for(unsigned i=0;i<4;++i)captureString(extra[i].text);
        number(at<void*>(world->client,0x70)!=NULL);
        number(actorID(actor()));number(at<int>(world->ui,0x16c8));
        number(at<int>(world->pets[0],0x710));number(at<int>(world->pets[1],0x710));
        number(at<int>(world->pets[0],0x330));number(at<int>(world->pets[1],0x330));
        const char* a=reinterpret_cast<const char*>(nameWindow.text.c_str());number(std::strlen(a));output->add(a,std::strlen(a));
        const char* b=reinterpret_cast<const char*>(statusWindow.text.c_str());number(std::strlen(b));output->add(b,std::strlen(b));
    }
    typedef std::wstring WString;at<WString>(world->ui,0x1978).~WString();at<WString>(world->ui,0x1988).~WString();
}
void original(void* p,autotest::Capture& c) { side(p,c,false); }
void expected(void* p,autotest::Capture& c) { side(p,c,true); }
}
namespace {
Case baseCase(){Case c;std::memset(&c,0,sizeof(c));c.hp=5;c.maxhp=100;c.mana=12.75f;c.maxmana=100;c.xp=50;c.level=1;c.elapsed=0.125f;return c;}
bool compare(const tlhybrid_host*host,Case& c,unsigned index){
    autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(expected,&c,b);
    bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
    if(!ok){for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first difference %u: %u/%u\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}host->log("    level case %u callback %u level %u modal %u menu %u counts %u/%u status %d/%d sizes %lu/%lu\n",index,c.clockCallback,c.levelPresent,c.modalFlag,c.menuMode,c.subCount,c.dropCount,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);}
    return ok;
}
}
TL_TEST(gameui_recovered_visible_labels){
 int failures=0;unsigned count=0;const int toggles[]={0,1,-1};const float positions[]={-10,0,100,790,900};
 for(unsigned toggle=0;toggle<3;++toggle)for(unsigned held=0;held<2;++held)for(unsigned hover=0;hover<3;++hover)
 for(unsigned covered=0;covered<2;++covered)for(unsigned hidden=0;hidden<2;++hidden)for(unsigned mode=0;mode<4;++mode)for(unsigned pos=0;pos<5;++pos){
 Case c=baseCase();c.levelPresent=1;c.screenWidth=800;c.screenHeight=600;c.listCount=1;c.labelToggle=toggles[toggle];c.labelHeld=held;c.labelHover=hover;c.labelCovered=covered;c.labelHidden=hidden;c.labelMode=mode;c.labelX=positions[pos];c.labelY=positions[4-pos];c.labelWidth=100;c.labelHeight=30;
 bool ok=compare(host,c,count);TL_CHECK(failures,ok);if(!ok){host->log(" visible labels case %u toggle %d held %u hover %u covered %u hidden %u mode %u pos %u\n",count,c.labelToggle,held,hover,covered,hidden,mode,pos);return failures;}++count;
 }host->log("    recovered visible labels: %u cases, existing windows, two frames\n",count);return failures;
}
