// Inclusive rectangle hit tests, observable collaborator order and reloads.
#include <cstring>
#include <vector>
#include <limits.h>
#include "GameUI.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(bool, originalMousePanel, (CGameUI*,int,int), "_ZN7CGameUI14mouseOverPanelEii")
extern "C" bool candidateMousePanel(CGameUI*,int,int) __asm__("_ZN7CGameUI14mouseOverPanelEii");
TL_FUNCTION(panelWidth,"_ZN7CGameUI14getWindowWidthEv")
TL_FUNCTION(panelHeight,"_ZN7CGameUI15getWindowHeightEv")
TL_FUNCTION(panelLeft,"_ZN7CGameUI11leftCoveredEv")
TL_FUNCTION(panelRight,"_ZN7CGameUI12rightCoveredEv")
namespace {
enum { Width=1,Height,Left,Right,Bytes=0x1a08 };
struct Case {
    float rect[5][4];int x,y;unsigned covered,mutation,fault,repeat,fill;
    Case():x(15),y(25),covered(3),mutation(0),fault(0),repeat(1),fill(0xa5) {
        for(unsigned r=0;r<5;++r){rect[r][0]=20+r*100;rect[r][1]=30+r*100;rect[r][2]=10+r*100;rect[r][3]=20+r*100;}
    }
};
const unsigned offsets[]={0x19cc,0x19dc,0x19bc,0x199c,0x19ac};
const Case* current;autotest::Capture* capture;CGameUI* ui;
unsigned char expected[Bytes];unsigned calls[4],errors;bool returned;
struct Stop{};
template<class T>T& at(void* p,unsigned n){return *reinterpret_cast<T*>(static_cast<char*>(p)+n);}
void number(unsigned n){capture->add(&n,4);}
void expect(bool good){number(good);if(!good)++errors;}
void require(bool good){if(!good)_exit(90);}
float bits(unsigned n){float f;std::memcpy(&f,&n,4);return f;}
void record(){expect(!std::memcmp(ui,expected,Bytes));capture->add(ui,Bytes);}
void mutate(unsigned tag){
    if(current->mutation==tag || current->mutation==5){
        unsigned r=tag==Width?0:tag==Height?1:tag==Left?3:4;
        float rect[]={float(current->y),float(current->y),float(current->x),float(current->x)};
        std::memcpy(static_cast<void*>(reinterpret_cast<char*>(ui)+offsets[r]),rect,16);
        std::memcpy(expected+offsets[r],rect,16);
    }
}
void boundary(CGameUI* p,unsigned tag){
    require(p==ui);number(tag);capture->addPointer(p);++calls[tag-1];record();mutate(tag);
    if(current->fault==tag)throw Stop();
}
float width(CGameUI* p){boundary(p,Width);return bits(0x7fc01234);}
float height(CGameUI* p){boundary(p,Height);return -777.5f;}
bool left(CGameUI* p){boundary(p,Left);return (current->covered&1)!=0;}
bool right(CGameUI* p){boundary(p,Right);return (current->covered&2)!=0;}
bool contains(unsigned r){const float* a=reinterpret_cast<float*>(expected+offsets[r]);float x=float(current->x),y=float(current->y);return x>=a[2]&&x<=a[3]&&y>=a[0]&&y<=a[1];}
bool reference(unsigned& leftCalls,unsigned& rightCalls){
    leftCalls=rightCalls=0;
    if(contains(0)||contains(1)||contains(2))return true;
    leftCalls=1;if((current->covered&1)&&contains(3))return true;
    rightCalls=1;return (current->covered&2)&&contains(4);
}
void side(void* raw,autotest::Capture& out,bool ours){
    current=static_cast<Case*>(raw);capture=&out;errors=0;autotest::g_arenaUsed=0;
    unsigned char* base=static_cast<unsigned char*>(autotest::allocate(Bytes+32));require(base!=0);
    std::memset(base,0xd3,16);std::memset(base+16,current->fill,Bytes);std::memset(base+16+Bytes,0x6c,16);
    ui=reinterpret_cast<CGameUI*>(base+16);
    for(unsigned r=0;r<5;++r)std::memcpy(base+16+offsets[r],current->rect[r],16);
    std::memcpy(expected,ui,Bytes);
    detour::Set hooks;TL_REDIRECT(hooks,panelWidth,&width);TL_REDIRECT(hooks,panelHeight,&height);
    TL_REDIRECT(hooks,panelLeft,&left);TL_REDIRECT(hooks,panelRight,&right);require(!hooks.failed());
    bool (*fn)(CGameUI*,int,int)=ours?&candidateMousePanel:&originalMousePanel;
    require(autotest::beginInvocation(out,fn));bool threw=false;
    for(unsigned iteration=0;iteration<current->repeat;++iteration){
        std::memset(calls,0,sizeof(calls));returned=false;bool result=false;
        try{result=fn(ui,current->x,current->y);returned=true;}catch(const Stop&){threw=true;}catch(...){require(false);}
        number(iteration);number(result);number(returned);number(threw);
        // Mutations alter only rectangles at observed boundaries. The final
        // independent answer remains valid for these monotone miss->hit changes.
        if(!threw){unsigned l,r;bool want=reference(l,r);expect(result==want);expect(calls[0]==1&&calls[1]==1);expect(calls[2]==l&&calls[3]==r);}
        else expect(current->fault && calls[current->fault-1]==1);
        record();capture->add(calls,sizeof(calls));
        for(unsigned j=0;j<16;++j)require(base[j]==0xd3&&base[16+Bytes+j]==0x6c);
        if(threw)break;
    }
    if(!threw)out.callCompleted=1;
    hooks.restore();require(!hooks.failed());out.addHeapInUse();number(0x50414e4c);number(errors);number(threw);
}
void originalSide(void* p,autotest::Capture& o){side(p,o,false);}
void candidateSide(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(gameui_layout_mouse_panel){
    std::vector<Case> cases;
    for(unsigned r=0;r<5;++r)for(unsigned c=0;c<4;++c){
        const int dx[]={-1,0,5,10,11},dy[]={-1,0,5,10,11};
        for(unsigned edge=0;edge<5;++edge){Case a;a.covered=c;a.x=10+100*r+dx[edge];a.y=25+100*r;cases.push_back(a);a.x=15+100*r;a.y=20+100*r+dy[edge];cases.push_back(a);}
    }
    const unsigned special[]={0,0x80000000u,0x7fc12345u,0xffc43210u,0x7f800000u,0xff800000u,0x7f7fffffu,1};
    for(unsigned r=0;r<5;++r)for(unsigned f=0;f<4;++f)for(unsigned s=0;s<8;++s){Case c;c.x=15+100*r;c.y=25+100*r;c.rect[r][f]=bits(special[s]);cases.push_back(c);}
    for(unsigned m=0;m<6;++m)for(unsigned c=0;c<4;++c){Case a;a.x=-10;a.y=-20;a.mutation=m;a.covered=c;a.repeat=3;a.fill=m&1?0:0xa5;cases.push_back(a);}
    for(unsigned r=0;r<5;++r){Case c;c.x=0;c.y=0;for(unsigned i=0;i<4;++i)c.rect[r][i]=0;cases.push_back(c);c.rect[r][0]=1;c.rect[r][1]=-1;cases.push_back(c);}
    const int extremes[]={INT_MIN,INT_MAX,16777215,16777216,16777217,-16777217};
    for(unsigned i=0;i<6;++i){Case c;c.x=extremes[i];c.y=extremes[5-i];c.rect[0][0]=c.rect[0][1]=float(c.y);c.rect[0][2]=c.rect[0][3]=float(c.x);cases.push_back(c);}
    autotest::Coverage coverage("gameui_layout_mouse_panel",(uint64_t)(uintptr_t)&originalMousePanel);
    for(unsigned i=0;i<cases.size();++i){autotest::Outcome a,b;autotest::runChild(originalSide,&cases[i],a);autotest::runChild(candidateSide,&cases[i],b);int result=coverage.observe(host,a,b);unsigned wa[3]={0},wb[3]={0};if(a.capture.length>=12)std::memcpy(wa,a.capture.data+a.capture.length-12,12);if(b.capture.length>=12)std::memcpy(wb,b.capture.data+b.capture.length-12,12);if(result||wa[0]!=0x50414e4c||wb[0]!=0x50414e4c||wa[1]||wb[1]||wa[2]||wb[2]){host->log("    mouse case %u: x=%d y=%d mutation=%u exits=%d/%d\n",i,cases[i].x,cases[i].y,cases[i].mutation,a.childStatus,b.childStatus);coverage.report(host);return 1;}}
    coverage.report(host);if(coverage.completed!=cases.size())return 1;
    unsigned unwinds=0;
    for(unsigned fault=1;fault<=4;++fault){
        Case c;c.x=-10;c.y=-20;c.fault=fault;
        autotest::Outcome a,b;autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);
        unsigned wa[3]={0},wb[3]={0};
        if(a.capture.length>=12)std::memcpy(wa,a.capture.data+a.capture.length-12,12);
        if(b.capture.length>=12)std::memcpy(wb,b.capture.data+b.capture.length-12,12);
        bool ok=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&
            a.capture.callStarted==1&&b.capture.callStarted==1&&!a.capture.callCompleted&&!b.capture.callCompleted&&
            a.capture.callTarget==(uint64_t)(uintptr_t)&originalMousePanel&&host->comparison_pair&&
            host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&
            !std::memcmp(a.capture.data,b.capture.data,a.capture.length)&&wa[0]==0x50414e4c&&wb[0]==0x50414e4c&&
            !wa[1]&&!wb[1]&&wa[2]==1&&wb[2]==1;
        if(!ok){host->log("    mouse expected-unwind %u failed\n",fault);return 1;}++unwinds;
    }
    host->log("    mouse panel: %u expected-unwind witnesses, excluded from normal coverage\n",unwinds);
    return 0;
}
