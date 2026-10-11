// Differential UI layout receipts. CEGUI value returns use the pinned headers:
// UVector2 has a nontrivial destructor (hidden result pointer), while Size and
// Rect are SSE aggregates. In particular Rect stores top,bottom,left,right.
#include <cstring>
#include <vector>
#include <CEGUI.h>
#include "GameUI.h"
#include "AutoTest.h"
#include "Detour.h"

TL_ORIGINAL(void, originalScale, (CGameUI*,CEGUI::Window*,bool), "_ZN7CGameUI20convertToScreenScaleEPN5CEGUI6WindowEb")
TL_ORIGINAL(void, originalCombo, (CGameUI*,CEGUI::Combobox*), "_ZN7CGameUI13sizeComboListEPN5CEGUI8ComboboxE")
extern "C" void candidateScale(CGameUI*,CEGUI::Window*,bool) __asm__("_ZN7CGameUI20convertToScreenScaleEPN5CEGUI6WindowEb");
extern "C" void candidateCombo(CGameUI*,CEGUI::Combobox*) __asm__("_ZN7CGameUI13sizeComboListEPN5CEGUI8ComboboxE");
TL_FUNCTION(scaleX, "_ZN7CGameUI7scaledXEf")
TL_FUNCTION(scaleY, "_ZN7CGameUI7scaledYEf")
#define LINK(name,symbol) extern "C" char name[] __asm__(symbol)
LINK(positionLink,"_ZNK5CEGUI6Window11getPositionEv");
LINK(sizeLink,"_ZNK5CEGUI6Window7getSizeEv");
LINK(setPositionLink,"_ZN5CEGUI6Window11setPositionERKNS_8UVector2E");
LINK(setSizeLink,"_ZN5CEGUI6Window7setSizeERKNS_8UVector2E");
LINK(countLink,"_ZNK5CEGUI8Combobox12getItemCountEv");
LINK(itemLink,"_ZNK5CEGUI8Combobox23getListboxItemFromIndexEm");
LINK(editLink,"_ZNK5CEGUI8Combobox10getEditboxEv");
LINK(dropLink,"_ZNK5CEGUI8Combobox11getDropListEv");
LINK(scrollLink,"_ZNK5CEGUI7Listbox16getHorzScrollbarEv");
LINK(visibleLink,"_ZNK5CEGUI6Window9isVisibleEb");
LINK(lookNameLink,"_ZNK5CEGUI6Window12getLookNFeelEv");
LINK(managerLink,"_ZN5CEGUI17WidgetLookManager12getSingletonEv");
LINK(lookLink,"_ZNK5CEGUI17WidgetLookManager13getWidgetLookERKNS_6StringE");
LINK(namedLink,"_ZNK5CEGUI14WidgetLookFeel12getNamedAreaERKNS_6StringE");
LINK(areaLink,"_ZNK5CEGUI9NamedArea7getAreaEv");
LINK(rectLink,"_ZNK5CEGUI13ComponentArea12getPixelRectERKNS_6WindowE");
LINK(yLink,"_ZNK5CEGUI6Window12getYPositionEv");
LINK(heightLink,"_ZN5CEGUI6Window9setHeightERKNS_4UDimE");
#undef LINK

namespace {
enum { UISize=0x1a08, WindowSize=0x400, MaxBlocks=32 };
struct Case {
    unsigned combo,axis,layout,value,mutation,repeat,visible,count,fault;
    Case(unsigned c=0):combo(c),axis(0),layout(0),value(0),mutation(0),repeat(1),visible(0),count(3),fault(0) {}
};
struct Block { unsigned char* p; unsigned size; unsigned char expected[UISize]; };
Block blocks[MaxBlocks];unsigned blockCount;
Case* current;autotest::Capture* capture;CGameUI* ui;
CEGUI::Window* windows[6];CEGUI::Window** children[2];
CEGUI::UVector2 positions[6],sizes[6],savedPosition,savedSize;
CEGUI::String* lookName;
void* items[5];void** itemTable;
void *editbox,*droplist,*scrollbar,*manager,*look,*named,*area;
CEGUI::UDim comboY;
CEGUI::Rect pixelRect;
unsigned calls,errors,active,phase,visited,order[16],orderCount,mutated,iteration;
unsigned countCalls,itemCalls,pixelCalls,comboStage,liveCount;
float sum,editHeight,dropHeight,comboHeight;
struct Injected { unsigned tag; explicit Injected(unsigned n):tag(n) {} };
unsigned unwindWitness,catches,faultHits;bool returned;
struct InvocationWitness { ~InvocationWitness() { if(!returned)++unwindWitness; } };

template<class T> T& at(void* p,unsigned offset) { return *reinterpret_cast<T*>(static_cast<char*>(p)+offset); }
void number(unsigned n) { capture->add(&n,sizeof(n)); }
void scalar(float f) { capture->add(&f,sizeof(f)); }
void pointer(const void* p) { capture->addPointer(p); }
void require(bool ok,unsigned reason) { if(!ok)_exit(60+reason); }
void expect(bool ok,unsigned reason) { number(reason);number(ok);if(!ok)++errors; }
bool same(float a,float b) { return !std::memcmp(&a,&b,sizeof(a)); }
void event(unsigned tag) {
    number(tag);require(++calls<300,1);
    if(current->fault==tag){++faultHits;throw Injected(tag);}
}
void* guarded(unsigned size,unsigned fill) {
    require(blockCount<MaxBlocks&&size<=UISize,2);
    unsigned char* p=static_cast<unsigned char*>(autotest::allocate(size+32));require(p!=0,3);
    std::memset(p,0xda,16);std::memset(p+16,fill,size);std::memset(p+16+size,0x9b,16);
    Block& b=blocks[blockCount++];b.p=p+16;b.size=size;std::memcpy(b.expected,b.p,size);return b.p;
}
void commit(void* p,unsigned offset,const void* value,unsigned size) {
    for(unsigned i=0;i<blockCount;++i)if(p==blocks[i].p) {
        require(offset+size<=blocks[i].size,4);std::memcpy(blocks[i].p+offset,value,size);
        std::memcpy(blocks[i].expected+offset,value,size);return;
    }
    require(false,5);
}
template<class T> void change(void* p,unsigned offset,const T& value) { commit(p,offset,&value,sizeof(value)); }
void checkBlocks(bool record) {
    for(unsigned i=0;i<blockCount;++i) {
        Block& b=blocks[i];
        require(!std::memcmp(b.p,b.expected,b.size),6);
        for(unsigned j=0;j<16;++j)require(b.p[int(j)-16]==0xda&&b.p[b.size+j]==0x9b,7);
        if(record){pointer(b.p);capture->add(b.p-16,b.size+32);}
    }
}
float value(unsigned index) {
    static const unsigned bits[]={0u,0x80000000u,0x3f800000u,0xc0200000u,0x42f68000u,
        1u,0x7f7fffffu,0xff7fffffu,0x7f800000u,0xff800000u,0x7fc12345u,0xffc45678u};
    float f;unsigned n=bits[index%12];std::memcpy(&f,&n,4);return f;
}
CEGUI::UVector2 vector(float x,float y,float sx,float sy) {
    return CEGUI::UVector2(CEGUI::UDim(sx,x),CEGUI::UDim(sy,y));
}
unsigned windowIndex(const void* p) {
    for(unsigned i=0;i<6;++i)if(p==windows[i])return i;
    require(false,8);return 0;
}
float scaled(float f,unsigned axis) { return f*(axis?1.75f:-.625f)+float(iteration+1)*.25f; }
const CEGUI::UVector2& getPosition(const CEGUI::Window* w) {
    event(1);pointer(w);checkBlocks(false);active=windowIndex(w);
    expect(phase==0,9);expect(visited<orderCount&&active==order[visited],10);
    ++visited;phase=1;savedPosition=positions[active];return positions[active];
}
float scale(CGameUI* receiver,float f,unsigned axis) {
    event(axis?2:3);pointer(receiver);scalar(f);
    expect(receiver==ui,11);expect(axis==current->axis,12);
    expect(phase==1||phase==2||phase==5||phase==6,13);
    const CEGUI::UVector2& input=phase<3?savedPosition:savedSize;
    float wanted=(phase==1||phase==5)?input.d_x.d_offset:input.d_y.d_offset;
    expect(same(f,wanted),14);
    float result=scaled(f,axis);scalar(result);
    // Both coordinates must have been copied before the first callback.
    if((current->mutation&1)&&(phase==1||phase==5)) {
        positions[active].d_y.d_offset=191.5f;
        sizes[active].d_y.d_offset=-371.25f;
    }
    ++phase;return result;
}
float xScale(CGameUI* receiver,float f) { return scale(receiver,f,1); }
float yScale(CGameUI* receiver,float f) { return scale(receiver,f,0); }
void inspectVector(const CEGUI::UVector2& actual,const CEGUI::UVector2& source) {
    capture->add(&actual,sizeof(actual));
    expect(same(actual.d_x.d_scale,source.d_x.d_scale)&&same(actual.d_y.d_scale,source.d_y.d_scale),15);
    expect(same(actual.d_x.d_offset,scaled(source.d_x.d_offset,current->axis)),16);
    expect(same(actual.d_y.d_offset,scaled(source.d_y.d_offset,current->axis)),17);
}
void setPosition(CEGUI::Window* w,const CEGUI::UVector2& p) {
    event(4);pointer(w);expect(w==windows[active]&&phase==3,18);inspectVector(p,savedPosition);
    expect(&p!=&positions[active],19);positions[active]=p;phase=4;
    if(current->mutation&2)sizes[active]=vector(23.75f,-17.125f,.375f,-.875f);
}
CEGUI::UVector2 getSize(const CEGUI::Window* w) {
    event(5);pointer(w);expect(w==windows[active]&&phase==4,20);
    savedSize=sizes[active];phase=5;return sizes[active];
}
void setSize(CEGUI::Window* w,const CEGUI::UVector2& size) {
    event(6);pointer(w);expect(w==windows[active]&&phase==7,21);inspectVector(size,savedSize);
    expect(&size!=&sizes[active],22);sizes[active]=size;phase=0;
    // Child count is captured once, but the begin pointer is reloaded after
    // each recursive return. Repoint and expand from three to four live children
    // during child 1; all captured indices remain valid in the new vector.
    if((current->mutation&4)&&!mutated&&active==1&&current->layout==1) {
        change(windows[0],0x78,children[1]);
        change(windows[0],0x80,children[1]+4);
        change(windows[0],0x88,children[1]+4);mutated=1;
    }
}

unsigned long getCount(const void* combo) {
    event(20);pointer(combo);expect(combo==windows[0]&&comboStage==0,23);
    expect(countCalls==itemCalls&&pixelCalls==itemCalls,24);++countCalls;
    number(liveCount);return liveCount;
}
void* getItem(const void* combo,unsigned long index) {
    event(21);pointer(combo);capture->add(&index,sizeof(index));
    expect(combo==windows[0]&&comboStage==0,25);
    expect(index==itemCalls&&countCalls==itemCalls+1,26);require(index<5,27);
    ++itemCalls;return items[index];
}
CEGUI::Size itemSize(const void* item) {
    event(22);pointer(item);expect(pixelCalls<itemCalls&&item==items[pixelCalls],28);
    unsigned index=pixelCalls++;
    float height=(index+1)*3.125f;
    if(current->value==1)height=index&1?-7.5f:7.5f;
    if(current->value>=8&&current->value<12)height=value(current->value);
    if(current->value==12) {
        static const float v[]={16777216.f,1.f,-16777216.f,2.f,-2.f};height=v[index];
    }
    if(current->value==13) {
        static const float v[]={1.e20f,-1.e20f,3.25f,-3.25f,.125f};height=v[index];
    }
    if(current->value==14)height=index==0?16777216.f:0.f;
    if(current->value==15)height=index==0?-16777216.f:0.f;
    sum+=height;scalar(height);
    if((current->mutation&1)&&index==0)liveCount=1;
    if((current->mutation&2)&&index==0)liveCount=5;
    // Width is intentionally unrelated and must never contribute to height.
    return CEGUI::Size(-913.75f-index*67.f,height);
}
void* getEdit(const void* combo) {
    event(23);pointer(combo);expect(combo==windows[0]&&comboStage++==0,29);
    expect(countCalls==itemCalls+1&&pixelCalls==itemCalls,30);
    editHeight=at<float>(editbox,0x19c);return editbox;
}
void* getDrop(const void* combo) {
    event(24);pointer(combo);expect(combo==windows[0]&&comboStage++==1,31);
    if(current->mutation&4)change(editbox,0x19c,999.25f);return droplist;
}
void* getScrollbar(const void* drop) {
    event(25);pointer(drop);expect(drop==droplist&&comboStage++==2,32);return scrollbar;
}
bool isVisible(const void* scroll,bool localOnly) {
    event(26);pointer(scroll);number(localOnly);
    expect(scroll==scrollbar&&!localOnly&&comboStage++==3,33);return current->visible!=0;
}
const CEGUI::String& getLookName(const void* drop) {
    event(27);pointer(drop);expect(drop==droplist&&comboStage++==4,34);return *lookName;
}
void* getManager() { event(28);expect(comboStage++==5,35);return manager; }
const void* getLook(const void* m,const CEGUI::String& name) {
    event(29);pointer(m);expect(m==manager&&comboStage++==6,36);
    expect(&name==lookName&&name==*lookName,37);
    if(current->mutation&8)change(droplist,0x19c,137.25f);
    dropHeight=at<float>(droplist,0x19c);return look;
}
const void* getNamed(const void* l,const CEGUI::String& name) {
    event(30);pointer(l);expect(l==look&&comboStage++==7,38);
    const char* wanted=current->visible?"ItemRenderingAreaHScroll":"ItemRenderingArea";
    expect(!std::strcmp(name.c_str(),wanted),39);capture->addText(std::string(name.c_str()));
    // Drop height is loaded before getNamedArea, rather than after getPixelRect.
    if(current->mutation&16)change(droplist,0x19c,-421.5f);return named;
}
const void* getArea(const void* n) {
    event(31);pointer(n);expect(n==named&&comboStage++==8,40);return area;
}
CEGUI::Rect getRect(const void* a,const CEGUI::Window& drop) {
    event(32);pointer(a);pointer(&drop);expect(a==area&&&drop==droplist&&comboStage++==9,41);
    if(current->mutation&32)change(windows[0],0x19c,-91.5f);
    comboHeight=at<float>(windows[0],0x19c);capture->add(&pixelRect,sizeof(pixelRect));return pixelRect;
}
const CEGUI::UDim& getY(const CEGUI::Window* drop) {
    event(33);pointer(drop);expect(drop==droplist&&comboStage++==10,42);
    // Combo pixel height is captured before this call, and offset is read after.
    if(current->mutation&64) {
        change(windows[0],0x19c,1241.f);comboY.d_offset=-17.75f;
    }
    capture->add(&comboY,sizeof(comboY));return comboY;
}
void setHeight(CEGUI::Window* combo,const CEGUI::UDim& height) {
    event(34);pointer(combo);capture->add(&height,sizeof(height));
    expect(combo==windows[0]&&comboStage++==11,43);
    float relative=comboY.d_scale*comboHeight;
    // All relative inputs are finite and int-representable, including signed
    // zero and both sides of half-integer boundaries. Avoid host cast UB.
    float rounded=float(int(relative+(relative>0.f?.5f:-.5f)));
    float border=dropHeight-(pixelRect.d_bottom-pixelRect.d_top);
    float expectedHeight=sum+editHeight;expectedHeight+=border;
    float extra=rounded+comboY.d_offset;extra-=editHeight;expectedHeight+=extra;
    expect(same(height.d_scale,0.f)&&same(height.d_offset,expectedHeight),44);
    change(windows[0],0x1b0,height);
}
void forbiddenVirtual() { require(false,45); }

void setup() {
    autotest::g_arenaUsed=0;blockCount=calls=errors=visited=phase=mutated=0;
    countCalls=itemCalls=pixelCalls=comboStage=0;unwindWitness=catches=faultHits=0;returned=false;sum=0.f;liveCount=current->count;
    require(sizeof(CEGUI::UVector2)==16&&sizeof(CEGUI::Size)==8&&sizeof(CEGUI::Rect)==16,46);
    ui=static_cast<CGameUI*>(guarded(UISize,current->value&1?0xa5:0x5a));
    for(unsigned i=0;i<6;++i) {
        windows[i]=static_cast<CEGUI::Window*>(guarded(WindowSize,0x30+i));
        // Only the vector's standard three-pointer storage is inspected by
        // these entry points; it is never passed to real CEGUI or destroyed.
        CEGUI::Window** empty=0;change(windows[i],0x78,empty);change(windows[i],0x80,empty);change(windows[i],0x88,empty);
        positions[i]=vector(value(current->value+i),value(current->value+i+3),.125f*i,-.375f*i);
        sizes[i]=vector(value(current->value+i+6),value(current->value+i+9),-.25f*i,.625f*i);
    }
    for(unsigned i=0;i<2;++i) {
        children[i]=static_cast<CEGUI::Window**>(guarded(4*sizeof(void*),0));
        for(unsigned j=0;j<4;++j)change(children[i],j*sizeof(void*),windows[j+1]);
    }
    orderCount=1;order[0]=0;
    if(current->layout==1) {
        change(windows[0],0x78,children[0]);change(windows[0],0x80,children[0]+3);change(windows[0],0x88,children[0]+4);
        change(children[1],sizeof(void*),windows[4]);
        orderCount=4;order[0]=1;order[1]=(current->mutation&4)?4:2;order[2]=3;order[3]=0;
    } else if(current->layout==2) {
        change(windows[0],0x78,children[0]);change(windows[0],0x80,children[0]+2);change(windows[0],0x88,children[0]+4);
        change(children[1],0,windows[3]);change(children[1],sizeof(void*),windows[4]);
        change(windows[1],0x78,children[1]);change(windows[1],0x80,children[1]+2);change(windows[1],0x88,children[1]+4);
        orderCount=5;order[0]=3;order[1]=4;order[2]=1;order[3]=2;order[4]=0;
    } else if(current->layout==3) {
        change(children[0],sizeof(void*),windows[1]);
        change(windows[0],0x78,children[0]);change(windows[0],0x80,children[0]+2);change(windows[0],0x88,children[0]+4);
        orderCount=3;order[0]=1;order[1]=1;order[2]=0;
    }
    editbox=guarded(WindowSize,0x61);droplist=guarded(WindowSize,0x62);scrollbar=guarded(64,0x63);
    manager=guarded(32,0x64);look=guarded(32,0x65);named=guarded(32,0x66);area=guarded(32,0x67);
    itemTable=static_cast<void**>(guarded(6*sizeof(void*),0));
    for(unsigned i=0;i<6;++i)change(itemTable,i*sizeof(void*),reinterpret_cast<void*>(&forbiddenVirtual));
    change(itemTable,0x10,reinterpret_cast<void*>(&itemSize));
    for(unsigned i=0;i<5;++i){items[i]=guarded(64,0x70+i);change(items[i],0,itemTable);}
    change(editbox,0x198,CEGUI::Size(811.5f,27.125f));
    change(droplist,0x198,CEGUI::Size(913.25f,77.5f));
    static const float heights[]={100.f,-100.f,0.f,-0.f,1.f,3.f,13.f,71.5f};
    change(windows[0],0x198,CEGUI::Size(-159.f,heights[current->value%8]));
    static const float relative[]={.25f,-.25f,0.f,-0.f,.5f,-.5f,.4999f,-.5001f};
    comboY=CEGUI::UDim(relative[current->value%8],13.625f);
    pixelRect.d_top=-11.25f;pixelRect.d_bottom=21.375f;
    pixelRect.d_left=143.75f;pixelRect.d_right=-291.125f;
    if(current->value==14||current->value==15) {
        const float sign=current->value==14?1.f:-1.f;
        change(editbox,0x19c,sign);
        change(droplist,0x19c,-16777216.f*sign);
        pixelRect.d_top=pixelRect.d_bottom=0.f;
        comboY=CEGUI::UDim(0.f,2.f*sign);
    }
}
void redirects(detour::Set& d) {
#define PATCH(link,fn) d.redirect(link,link,&fn)
    PATCH(positionLink,getPosition);PATCH(sizeLink,getSize);PATCH(setPositionLink,setPosition);PATCH(setSizeLink,setSize);
    TL_REDIRECT(d,scaleX,&xScale);TL_REDIRECT(d,scaleY,&yScale);
    PATCH(countLink,getCount);PATCH(itemLink,getItem);PATCH(editLink,getEdit);PATCH(dropLink,getDrop);
    PATCH(scrollLink,getScrollbar);PATCH(visibleLink,isVisible);PATCH(lookNameLink,getLookName);
    PATCH(managerLink,getManager);PATCH(lookLink,getLook);PATCH(namedLink,getNamed);PATCH(areaLink,getArea);
    PATCH(rectLink,getRect);PATCH(yLink,getY);PATCH(heightLink,setHeight);
#undef PATCH
    require(!d.failed(),47);
}
void side(void* raw,autotest::Capture& out,bool ours) {
    current=static_cast<Case*>(raw);capture=&out;iteration=0;setup();
    out.addHeapInUse(); // Baseline before either real CEGUI string is constructed.
    {
        CEGUI::String realName("Torchlight/ComboTest/Look");lookName=&realName;
        detour::Set d;redirects(d);
        if(current->combo) {
            void(*fn)(CGameUI*,CEGUI::Combobox*)=ours?&candidateCombo:&originalCombo;
            require(autotest::beginInvocation(out,fn),48);
            try {
                InvocationWitness witness;
                fn(ui,reinterpret_cast<CEGUI::Combobox*>(windows[0]));returned=true;
            } catch(const Injected& failure) {
                ++catches;expect(failure.tag==current->fault,54);
            } catch(...) { require(false,55); }
            expect(returned==!current->fault,56);
            expect(unwindWitness==unsigned(bool(current->fault))&&catches==unwindWitness&&faultHits==unwindWitness,57);
            if(returned)expect(comboStage==12,49);
        } else {
            void(*fn)(CGameUI*,CEGUI::Window*,bool)=ours?&candidateScale:&originalScale;
            require(autotest::beginInvocation(out,fn),50);
            for(iteration=0;iteration<current->repeat;++iteration) {
                visited=0;phase=0;number(0x100+iteration);
                fn(ui,windows[0],current->axis!=0);expect(visited==orderCount&&phase==0,51);
            }
            for(unsigned i=0;i<6;++i){capture->add(&positions[i],sizeof(positions[i]));capture->add(&sizes[i],sizeof(sizes[i]));}
            returned=true;
        }
        checkBlocks(true);if(returned)out.callCompleted=1;
        d.restore();require(!d.failed(),53);
    }
    out.addHeapInUse(); // After areaName and the real look name have unwound.
    number(0x554e5744u);number(unwindWitness);number(catches);number(faultHits);number(returned);number(errors);
}
void originalSide(void* raw,autotest::Capture& out){side(raw,out,false);}
void candidateSide(void* raw,autotest::Capture& out){side(raw,out,true);}
int run(const tlhybrid_host* host,const char* name,unsigned combo,const std::vector<Case>& cases) {
    uint64_t address=combo?(uint64_t)(uintptr_t)&originalCombo:(uint64_t)(uintptr_t)&originalScale;
    autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<cases.size();++i) {
        Case c=cases[i];autotest::Outcome a,b;autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);
        int observed=coverage.observe(host,a,b);
        unsigned errorsA=~0u,errorsB=~0u;
        if(a.capture.length>=sizeof(errorsA))std::memcpy(&errorsA,a.capture.data+a.capture.length-sizeof(errorsA),sizeof(errorsA));
        if(b.capture.length>=sizeof(errorsB))std::memcpy(&errorsB,b.capture.data+b.capture.length-sizeof(errorsB),sizeof(errorsB));
        if(observed||errorsA||errorsB) {
            size_t first=0;while(first<a.capture.length&&first<b.capture.length&&a.capture.data[first]==b.capture.data[first])++first;
            host->log("    layout %s case %u axis %u layout %u value %u mutation %u visible %u count %u: exits %d/%d completed %u/%u first %u lengths %u/%u\n",
                name,i,c.axis,c.layout,c.value,c.mutation,c.visible,c.count,a.childStatus,b.childStatus,
                a.capture.callCompleted,b.capture.callCompleted,(unsigned)first,(unsigned)a.capture.length,(unsigned)b.capture.length);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);return coverage.completed!=cases.size()||coverage.completed<20;
}
bool unwindReceipt(const autotest::Outcome& result) {
    unsigned words[6];if(result.capture.length<sizeof(words))return false;
    std::memcpy(words,result.capture.data+result.capture.length-sizeof(words),sizeof(words));
    return words[0]==0x554e5744u&&words[1]==1&&words[2]==1&&words[3]==1&&!words[4]&&!words[5];
}
int runUnwinds(const tlhybrid_host* host,const std::vector<Case>& cases) {
    const uint64_t address=(uint64_t)(uintptr_t)&originalCombo;
    unsigned completed=0;
    for(unsigned i=0;i<cases.size();++i) {
        Case c=cases[i];autotest::Outcome a,b;autotest::runChild(originalSide,&c,a);autotest::runChild(candidateSide,&c,b);
        bool ok=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&
            a.capture.callStarted==1&&b.capture.callStarted==1&&!a.capture.callCompleted&&!b.capture.callCompleted&&
            a.capture.callTarget==address&&host->abi_version==TLHYBRID_ABI_VERSION&&host->comparison_pair&&
            host->comparison_pair(address,b.capture.callTarget)&&a.capture.length==b.capture.length&&
            !std::memcmp(a.capture.data,b.capture.data,a.capture.length)&&unwindReceipt(a)&&unwindReceipt(b);
        if(!ok) {
            host->log("    layout combo unwind case %u callback %u visible %u exits %d/%d completed %u/%u lengths %u/%u\n",
                i,c.fault,c.visible,a.childStatus,b.childStatus,a.capture.callCompleted,b.capture.callCompleted,
                (unsigned)a.capture.length,(unsigned)b.capture.length);return 1;
        }
        ++completed;
    }
    host->log("    gameui_layout_size_combo: %u expected-unwind receipts, excluded from normal coverage\n",completed);
    return 0;
}
}
TL_TEST(gameui_layout_convert_scale) {
    std::vector<Case> cases;
    for(unsigned axis=0;axis<2;++axis)for(unsigned layout=0;layout<4;++layout)for(unsigned value=0;value<12;++value) {
        Case c;c.axis=axis;c.layout=layout;c.value=value;cases.push_back(c);
    }
    for(unsigned axis=0;axis<2;++axis)for(unsigned layout=0;layout<4;++layout)for(unsigned mutation=1;mutation<8;++mutation) {
        Case c;c.axis=axis;c.layout=layout;c.mutation=mutation;c.value=4;
        // Repeat on the same objects except vector-count mutation, whose next
        // top-level invocation intentionally sees a different child count.
        c.repeat=(mutation&4)?1:3;cases.push_back(c);
    }
    return run(host,"gameui_layout_convert_scale",0,cases);
}
TL_TEST(gameui_layout_size_combo) {
    std::vector<Case> cases;
    for(unsigned visible=0;visible<2;++visible)for(unsigned count=0;count<6;++count)for(unsigned v=0;v<12;++v) {
        Case c(1);c.visible=visible;c.count=count;c.value=v;cases.push_back(c);
    }
    for(unsigned visible=0;visible<2;++visible)for(unsigned mutation=1;mutation<128;++mutation) {
        Case c(1);c.visible=visible;c.mutation=mutation;c.value=mutation%8;c.count=3;cases.push_back(c);
    }
    // Finite cancellation tests distinguish accumulation order and prevent
    // algebraic cancellation of the independently rounded edit-height terms.
    for(unsigned visible=0;visible<2;++visible)for(unsigned v=12;v<16;++v)for(unsigned count=3;count<=5;count+=2) {
        Case c(1);c.visible=visible;c.value=v;c.count=count;cases.push_back(c);
    }
    int normal=run(host,"gameui_layout_size_combo",1,cases);if(normal)return normal;
    std::vector<Case> faults;
    // All boundaries occur after the real areaName constructor. Tags 31-34
    // follow getNamedArea's c_str(), so the real temporary also owns an encoded
    // heap buffer whose destructor must run on the original/candidate unwind.
    for(unsigned visible=0;visible<2;++visible)for(unsigned tag=27;tag<=34;++tag)for(unsigned mutation=0;mutation<2;++mutation) {
        Case c(1);c.visible=visible;c.fault=tag;c.mutation=mutation?127:0;faults.push_back(c);
    }
    return runUnwinds(host,faults);
}
// Negative controls: pre-order traversal; always scaledX; scale relative terms;
// cache child begin/count incorrectly; use stale size before setPosition; omit
// copying position; cache combo count; use item width or Rect's physical x pair;
// wrong visibility flag; stale/reloaded edit/drop/combo heights; wrong rounding.
