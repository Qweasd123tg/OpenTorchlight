// Active-character HUD including pet controls, name and status; stops before level name.
#include <cstring>
#include <new>
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
struct Case { int hp,maxhp,maxmana; float mana; unsigned seed,mode,label; int xp,level; unsigned pattern,xpmode; unsigned petShow,petMode,cacheMatches,petKind,petCallback,textFlags,petStats;float timer; };
struct TextWindow { unsigned char padding[0xc0];CEGUI::String text; };
struct World {
    unsigned long long ui[0x1a08/8],actors[2][0x700/8],radio[0x800/8];
    unsigned long long cinema[0x100/8],editor[0x100/8],menu[8],vt[8],target,settings,managers[2],pets[2][0x720/8],client[0x80/8],level;void* petEntries[2][1];TextWindow* nameWindow;TextWindow* statusWindow;unsigned managerCalls,gateCalls;
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
int setting(void*,unsigned) { return 0; }
bool pressed(void*,unsigned) { return true; }
void unused(void*) {}
bool modal(void*) { return true; }
void* editor() { return world->editor; }
void closeMenu(void*,bool) {}
bool notOpen(void*) { return false; }
void finish();
void visible(void* window,bool value) {
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
    reachedBoundary=true;throw std::runtime_error("gameui pet boundary");
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
    number(28);number(window==world->nameWindow?0:1);
    const char* bytes=reinterpret_cast<const char*>(value.c_str());unsigned length=std::strlen(bytes);
    number(length);output->add(bytes,length);
    static_cast<TextWindow*>(window)->text=value;
    if(window==world->nameWindow&&input->petCallback==4)at<int>(world->pets[0],0x330)=0x2a;
}
std::wstring finishName(void* level) {number(29);number(level==&world->level);finish();return L"";}
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
void model() {
    visible(reinterpret_cast<void*>(0x140),true);
    float current=float(hp(actor()));int maximum=maxhp(actor());
    bar(0x16cc,0x171c,0x140,0x150,current/float(maximum));
    {
        std::string top=originalNumber(maxhp(actor()));
        std::string now=originalNumber(hp(actor()));
        std::string text=std::string(hpLabels[input->label])+":"+now+"/"+top;
        CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(text.c_str()));
        tooltip(reinterpret_cast<void*>(0x148),converted);
    }
    visible(reinterpret_cast<void*>(0x158),true);
    current=mana(actor());maximum=maxmana(actor());
    bar(0x16dc,0x172c,0x158,0x168,current/float(maximum));
    {
        std::string top=originalNumber(maxmana(actor()));
        std::string now=originalNumber(int(mana(actor())));
        std::string text=std::string(manaLabels[input->label])+":"+now+"/"+top;
        CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(text.c_str()));
        tooltip(reinterpret_cast<void*>(0x160),converted);
    }
    int level=at<int>(actor(),0x100);
    float experience=float(at<int>(actor(),0x448));
    void* resource=manager();int previous=gate(resource,level-1);
    level=at<int>(actor(),0x100);resource=manager();int currentGate=gate(resource,level);
    level=at<int>(actor(),0x100);resource=manager();int previousAgain=gate(resource,level-1);
    float ratio=(experience-float(previous))/float(currentGate-previousAgain);
    if(ratio<0.0f)ratio=0.0f;else if(ratio>1.0f)ratio=1.0f;
    size(reinterpret_cast<void*>(0x1d0),CEGUI::UVector2(
        CEGUI::UDim(0,float(int(cached(0x173c).d_x.asAbsolute(1)*ratio))),
        CEGUI::UDim(0,cached(0x173c).d_y.asAbsolute(1))));
    {
        level=at<int>(actor(),0x100);resource=manager();
        std::string top=originalNumber(gate(resource,level));
        std::string now=originalNumber(at<int>(actor(),0x448));
        std::string text=std::string(xpLabels[input->label])+":"+now+"/"+top;
        CEGUI::String converted(reinterpret_cast<const CEGUI::utf8*>(text.c_str()));
        tooltip(reinterpret_cast<void*>(0x1d8),converted);
    }
    petHUD();finishName(&world->level);
}
void side(void* context,autotest::Capture& capture,bool expected) {
    Case& c=*static_cast<Case*>(context);TextWindow nameWindow,statusWindow;std::wstring names[2]={L"Buddy",L"Fox"};World state;world=&state;input=&c;output=&capture;reachedBoundary=false;
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
    at<void*>(world->client,0x70)=&world->level;
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
    detour::Set patches;
    TL_REDIRECT(patches,settingsGet,&setting);TL_REDIRECT(patches,mousePressed,&pressed);TL_REDIRECT(patches,mouseHeld,&pressed);
    TL_REDIRECT(patches,updateSlots,&unused);TL_REDIRECT(patches,editorSingleton,&editor);TL_REDIRECT(patches,modalPartial,&modal);
    TL_REDIRECT(patches,characterHP,&hp);TL_REDIRECT(patches,characterMaxHP,&maxhp);
    TL_REDIRECT(patches,characterMana,&mana);TL_REDIRECT(patches,characterMaxMana,&maxmana);TL_REDIRECT(patches,masterSingleton,&manager);TL_REDIRECT(patches,experienceGate,&gate);
    patches.redirect(reinterpret_cast<char*>(0x554718),reinterpret_cast<char*>(0x554718),&visible);
    patches.redirect(reinterpret_cast<char*>(0x5548a8),reinterpret_cast<char*>(0x5548a8),&position);
    patches.redirect(reinterpret_cast<char*>(0x555178),reinterpret_cast<char*>(0x555178),&size);
    patches.redirect(reinterpret_cast<char*>(0x554b48),reinterpret_cast<char*>(0x554b48),&tooltip);
    TL_REDIRECT(patches,leftCovered,&covered);TL_REDIRECT(patches,petNearDeath,&nearDeath);TL_REDIRECT(patches,levelName,&finishName);
    patches.redirect(reinterpret_cast<char*>(0x554dc8),reinterpret_cast<char*>(0x554dc8),&select);
    patches.redirect(reinterpret_cast<char*>(0x555c08),reinterpret_cast<char*>(0x555c08),&text);
    if(patches.failed()) _exit(42);
    for(unsigned repeat=0;repeat<2;++repeat){
        reachedBoundary=false;world->managerCalls=world->gateCalls=0;
        try { if(expected)model();else originalUpdate(world->ui,0.125f,world->client,NULL);_exit(43); }
        catch(const std::runtime_error& e) { if(!reachedBoundary||std::strcmp(e.what(),"gameui pet boundary")!=0)_exit(44); }
        number(actorID(actor()));number(at<int>(world->ui,0x16c8));
        number(at<int>(world->pets[0],0x710));number(at<int>(world->pets[1],0x710));
        number(at<int>(world->pets[0],0x330));number(at<int>(world->pets[1],0x330));
        const char* a=reinterpret_cast<const char*>(nameWindow.text.c_str());number(std::strlen(a));output->add(a,std::strlen(a));
        const char* b=reinterpret_cast<const char*>(statusWindow.text.c_str());number(std::strlen(b));output->add(b,std::strlen(b));
    }
}
void original(void* p,autotest::Capture& c) { side(p,c,false); }
void expected(void* p,autotest::Capture& c) { side(p,c,true); }
}
TL_TEST(gameui_pet_prefix_characterization) {
    int failures=0;unsigned count=0;
    const unsigned modes[]={0,1,2,7};const float timers[]={-1.1f,0,9.99f,10,59.99f,60,61.25f,3599.75f,3600,3661.25f};
    for(unsigned show=0;show<3;++show)for(unsigned mode=0;mode<4;++mode)
    for(unsigned match=0;match<2;++match)for(unsigned kind=0;kind<3;++kind)
    for(unsigned callback=0;callback<5;++callback)for(unsigned flags=0;flags<4;++flags)
    for(unsigned label=0;label<3;++label) {
        Case c={5,100,100,12.75f,count%3,0,label,50,1,0,0,show,modes[mode],match,kind,callback,flags,(count/7)%4,timers[(count/11)%10]};
        autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(expected,&c,b);
        bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
            a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        TL_CHECK(failures,ok);
        if(!ok){for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first difference %u: %u/%u\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}host->log("    pet case %u show %u mode %u match %u kind %u callback %u flags %u label %u status %d/%d sizes %lu/%lu\n",count,show,mode,match,kind,callback,flags,label,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);return failures;}
        ++count;
    }
    host->log("    gameui pets: %u cases, two frames per side\n",count);return failures;
}
