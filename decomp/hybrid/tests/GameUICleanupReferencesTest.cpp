// Original 0xa988b0 versus the recovered full-TU public entry. The independent
// script below predicts every byte at every callback, not just equal traces.
// No target detour, weak implementation, window system, or synthetic String ABI.
// String constructors/destructors execute normally; allocation-failure injection
// and an independent destructor-order witness are intentionally not claimed.
#include <climits>
#include <cstring>
#include <vector>
#include <new>
#include <CEGUI.h>
#include "GameUI.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,oldCleanup,(CGameUI*),"_ZN7CGameUI17cleanupReferencesEv")
extern "C" void newCleanup(CGameUI*) __asm__("_ZN7CGameUI17cleanupReferencesEv");
TL_FUNCTION(imageFn,"_ZN7CGameUI20getImageFromImageSetEPKh")
TL_FUNCTION(hoverFn,"_ZN7CGameUI16setMouseOverItemEP5CItemb")
TL_FUNCTION(cursorFn,"_ZN7CGameUI14setCursorStateE12ECursorState")
TL_FUNCTION(removeFn,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(merchantFn,"_ZN13CMerchantMenu9setPlayerEP10CCharacter")
TL_FUNCTION(enchantFn,"_ZN12CEnchantMenu9setPlayerEP10CCharacter")
TL_FUNCTION(combineFn,"_ZN12CCombineMenu9setPlayerEP10CCharacter")
TL_FUNCTION(stashFn,"_ZN10CStashMenu9setPlayerEP10CCharacter")
extern "C" char propertyFn[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");
extern "C" char imageStringFn[] __asm__("_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE");
namespace {
enum Call { Property=1,Image,ImageString,Release,Hover,Owner,Merchant,Enchant,Combine,Stash,Cursor };
struct Case {
    unsigned mask,mutation,fault,repeat,alias;
    int cursor,replacementCursor;
    bool actualHover,reseed;
    Case():mask(15),mutation(0),fault(0),repeat(1),alias(0),cursor(3),replacementCursor(4),actualHover(false),reseed(false){}
};
struct Failure { unsigned ordinal; explicit Failure(unsigned n):ordinal(n){} };
struct Block { unsigned char* p; unsigned size; };
struct Event {
    unsigned kind,number; void* self; void* argument; unsigned value;
    std::vector<unsigned char> prefix;
};
Block blocks[48]; unsigned blockCount,arenaSize,eventIndex,step,oracleErrors,activeFault;
std::vector<unsigned char> shadow,expectedFinal;
std::vector<Event> events;
const Case* testCase; autotest::Capture* capture;
void* ui; void* menus[3][7]; void* tips[3]; void* icons[6]; void* objects[6]; void* imageObject;
void* tables[3][7][10];
const unsigned menuOffset[]={0x4d8,0x4f0,0x4f8,0x500,0x508,0x4e8,0x568};
const unsigned hoverOffset[]={0x1020,0x3438,0xf0,0x190,0x3408,0x1370};
const unsigned menuSize[]={0x1030,0x3480,0x110,0x1b0,0x3430,0x1380,0x80};
const unsigned refOffset[]={0x58,0x80,0x90,0xa0};
const unsigned indices[]={0,UINT_MAX,0x76543210,29};
const char* attackText="set:Cleanup image:Attack \xCE\xBB";
// Oracle failures remain data: normal mutants must finish and count as different,
// never masquerade as incomplete invocation evidence.
void invalid(){++oracleErrors;}
void n(unsigned x){capture->add(&x,sizeof(x));}
void pointer(const void* p){capture->addPointer(p);}
template<class T>T& field(void* p,unsigned offset,bool model=false){
    unsigned char* a=(unsigned char*)p+offset;
    if(model){size_t k=a-(unsigned char*)autotest::g_arena;if(k+sizeof(T)>shadow.size())_exit(81);a=&shadow[k];}
    return *reinterpret_cast<T*>(a);
}
void* object(unsigned bytes){
    if(blockCount==48)_exit(82);
    unsigned char* p=(unsigned char*)autotest::allocate(bytes+32);if(!p)_exit(83);
    std::memset(p,0xd3,16);std::memset(p+16,0xa5,bytes);std::memset(p+16+bytes,0x6c,16);
    blocks[blockCount].p=p;blocks[blockCount++].size=bytes;return p+16;
}
void forbidden(){_exit(84);}
void setOwner(void*,void*);
void initialize(){
    autotest::g_arenaUsed=0;blockCount=eventIndex=step=oracleErrors=0;
    ui=object(0x1a08);
    for(unsigned j=0;j<6;++j){objects[j]=object(0x30);icons[j]=object(0x40);}
    imageObject=object(0x30);
    for(unsigned bank=0;bank<3;++bank)for(unsigned j=0;j<7;++j){
        for(unsigned k=0;k<10;++k)tables[bank][j][k]=(void*)&forbidden;
        tables[bank][j][7]=(void*)&setOwner;
        menus[bank][j]=object(menuSize[j]);field<void*>(menus[bank][j],0)=tables[bank][j];
        if(j<6)field<void*>(menus[bank][j],hoverOffset[j])=objects[(bank+j)%6];
    }
    for(unsigned j=0;j<7;++j)field<void*>(ui,menuOffset[j])=menus[0][j];
    for(unsigned j=0;j<3;++j){tips[j]=object(0x30);field<long long>(tips[j],0x10)=0x1122334455667700LL+j;}
    for(unsigned j=0;j<3;++j)field<void*>(ui,0x4a0+j*8)=tips[testCase->alias?0:j];
    field<void*>(ui,0x210)=icons[0];field<void*>(ui,0x238)=icons[1];field<void*>(ui,0x208)=icons[2];
    for(unsigned j=0;j<4;++j){field<void*>(ui,refOffset[j])=(testCase->mask&(1u<<j))?objects[j]:0;field<unsigned>(ui,refOffset[j]+8)=indices[(j+testCase->mask)%4];}
    field<void*>(ui,0x68)=objects[4];field<unsigned>(ui,0x70)=43;
    field<int>(ui,0x12fc)=testCase->cursor;
    field<long long>(ui,0xb0)=0x246813579abcdefLL;
    arenaSize=autotest::g_arenaUsed;
}
// Shared collaborator contract only. It never performs cleanupReferences writes.
// Deliberately observable callbacks rebind objects or mutate safe slots, including
// the current release slot. The independent script supplies target-owned writes.
void callbackEffect(unsigned kind,void* self,void* arg,unsigned value,bool model){
    if(kind==Property)field<unsigned>(self,0x20,model)=value+101;
    if(kind==Owner)field<unsigned>(self,0x20,model)^=0x87654321;
    if(kind>=Merchant&&kind<=Stash)field<unsigned>(self,0x24,model)+=1;
    if(kind==Hover)field<unsigned>(ui,0x1800,model)^=0x12345678;
    if(kind==Cursor)field<int>(ui,0x12fc,model)=0;
    if(testCase->mutation==1){
        if(kind==Property&&value==0)field<void*>(ui,0x238,model)=icons[4];
        if(kind==Image)field<void*>(ui,0x208,model)=icons[3];
        if(kind==ImageString)field<void*>(ui,0x208,model)=icons[5];
    }
    if(testCase->mutation==2){
        if(kind==Owner)for(unsigned j=1;j<7;++j)if(j!=5&&self==field<void*>(ui,menuOffset[j],model)){
            void* replacement=self==menus[1][j]?menus[2][j]:menus[1][j];
            field<void*>(ui,menuOffset[j],model)=replacement;break;
        }
        if(kind==Enchant){field<void*>(ui,0x4f0,model)=menus[2][1];field<void*>(ui,0x508,model)=menus[2][4];field<void*>(ui,0x568,model)=menus[2][6];}
    }
    if(testCase->mutation==3&&kind==Owner&&self==field<void*>(ui,0x568,model))field<int>(ui,0x12fc,model)=testCase->replacementCursor;
    if(testCase->mutation==4&&kind==Release){
        field<void*>(arg,0,model)=objects[5]; // successful caller must clear this too
        if(arg==(unsigned char*)ui+0x80){
            field<long long>(ui,0xb0,model)=0x5555444433332222LL;
            field<void*>(ui,0x90,model)=objects[5];field<unsigned>(ui,0x98,model)=73;
            field<void*>(ui,0xa0,model)=objects[4];field<unsigned>(ui,0xa8,model)=UINT_MAX;
        }
        if(arg==(unsigned char*)ui+0x58){
            // Real-hover lane must reload tooltip pointers after the callback.
            field<void*>(ui,0x4a0,model)=tips[2];field<long long>(tips[2],0x10,model)=779;
        }
    }
    if(testCase->mutation==5&&kind==Hover){
        for(unsigned j=1;j<7;++j)if(j!=5)field<void*>(ui,menuOffset[j],model)=menus[1][j];
        field<int>(ui,0x12fc,model)=testCase->replacementCursor;
    }
}
void modelCall(unsigned kind,void* self,void* arg=0,unsigned value=0){
    Event e;e.kind=kind;e.self=self;e.argument=arg;e.value=value;e.number=events.size()+1;e.prefix=shadow;events.push_back(e);
    callbackEffect(kind,self,arg,value,true);
    if(activeFault==e.number)throw Failure(e.number);
}
void modelRelease(unsigned off){
    void* p=field<void*>(ui,off,true);
    if(p){modelCall(Release,p,(unsigned char*)ui+off,field<unsigned>(ui,off+8,true));field<void*>(ui,off,true)=0;}
}
void modelCleanup(){
    for(unsigned j=0;j<6;++j)field<void*>(field<void*>(ui,menuOffset[j],true),hoverOffset[j],true)=0;
    for(unsigned j=0;j<3;++j)field<long long>(field<void*>(ui,0x4a0+j*8,true),0x10,true)=-1;
    field<long long>(ui,0x228,true)=field<long long>(ui,0x248,true)=field<long long>(ui,0x250,true)=-1;
    modelCall(Property,field<void*>(ui,0x210,true),0,0);
    modelCall(Property,field<void*>(ui,0x238,true),0,1);
    modelCall(Image,ui);modelCall(ImageString,imageObject);
    modelCall(Property,field<void*>(ui,0x208,true),0,2);
    modelRelease(0x58);
    if(testCase->actualHover){
        modelRelease(0x68);
        for(unsigned j=0;j<3;++j)field<long long>(field<void*>(ui,0x4a0+j*8,true),0x10,true)=-1;
    }else modelCall(Hover,ui,0,1);
    // Slot +0x38 is setOwner(NULL), not setOpen(false); slot +0x40 is
    // forbidden. Spell out the independently audited vtable/assembly order.
    // The repeated merchant rebind is intentional.
    modelCall(Owner,field<void*>(ui,0x4f0,true));modelCall(Merchant,field<void*>(ui,0x4f0,true));
    modelCall(Owner,field<void*>(ui,0x4f8,true));modelCall(Enchant,field<void*>(ui,0x4f8,true));
    modelCall(Owner,field<void*>(ui,0x500,true));modelCall(Combine,field<void*>(ui,0x500,true));
    modelCall(Merchant,field<void*>(ui,0x4f0,true));
    modelCall(Owner,field<void*>(ui,0x508,true));modelCall(Stash,field<void*>(ui,0x508,true));
    modelCall(Owner,field<void*>(ui,0x568,true));
    int cursor=field<int>(ui,0x12fc,true);if(cursor==3||cursor==4)modelCall(Cursor,ui);
    field<long long>(ui,0xb0,true)=-1;
    modelRelease(0x80);modelRelease(0x90);modelRelease(0xa0);
}
void observe(unsigned kind,void* self,void* arg=0,unsigned value=0){
    if(eventIndex>=events.size()){invalid();++eventIndex;n(kind);pointer(self);pointer(arg);n(value);n(eventIndex);callbackEffect(kind,self,arg,value,false);return;}
    const Event& e=events[eventIndex++];
    n(kind);pointer(self);pointer(arg);n(value);n(eventIndex);
    if(e.kind!=kind||e.self!=self||e.argument!=arg||e.value!=value)invalid();
    if(std::memcmp(autotest::g_arena,&e.prefix[0],arenaSize))invalid();
    callbackEffect(kind,self,arg,value,false);
    if(activeFault==eventIndex)throw Failure(eventIndex);
}
void property(void* self,const CEGUI::String& key,const CEGUI::String& value){
    // Verify real string contents and distinct live key/value temporary objects.
    if(&key==&value||key.length()!=5)invalid();
    const char* k="Image";for(size_t j=0;j<key.length();++j)if(j>=5||key[j]!=(unsigned char)k[j])invalid();
    unsigned role=eventIndex<events.size()?events[eventIndex].value:99;
    CEGUI::String expected(role==2?attackText:"");
    if(value!=expected)invalid();
    n(key.length());n(value.length());for(size_t j=0;j<value.length();++j)n(value[j]);
    observe(Property,self,0,role);
}
void* getImage(void* self,const unsigned char* name){if(std::strcmp((const char*)name,"skill_attack"))invalid();observe(Image,self);return imageObject;}
void imageString(CEGUI::String* result,void* p){observe(ImageString,p);new(result)CEGUI::String(attackText);}
void release(void* p,void* slot,unsigned index){if(field<void*>(slot,0)!=p||field<unsigned>(slot,8)!=index)invalid();observe(Release,p,slot,index);}
void hover(void* self,void* item,bool clear){observe(Hover,self,item,clear?1:0);}
void setOwner(void* self,void* owner){observe(Owner,self,owner);}
void merchant(void* self,void* player){observe(Merchant,self,player);}
void enchant(void* self,void* player){observe(Enchant,self,player);}
void combine(void* self,void* player){observe(Combine,self,player);}
void stash(void* self,void* player){observe(Stash,self,player);}
void cursor(void* self,int value){observe(Cursor,self,0,(unsigned)value);}
void redirect(detour::Set& d){
    TL_REDIRECT(d,imageFn,&getImage);TL_REDIRECT(d,cursorFn,&cursor);TL_REDIRECT(d,removeFn,&release);
    TL_REDIRECT(d,merchantFn,&merchant);TL_REDIRECT(d,enchantFn,&enchant);TL_REDIRECT(d,combineFn,&combine);TL_REDIRECT(d,stashFn,&stash);
    if(!testCase->actualHover)TL_REDIRECT(d,hoverFn,&hover);
    d.redirect(propertyFn,propertyFn,&property);d.redirect(imageStringFn,imageStringFn,&imageString);
}
void snapshot(){
    // Lossless RLE, including arena alignment gaps and all object redzones.
    // The forked sides share the same arena base and static vtable addresses;
    // pointers therefore have one canonical representation in raw snapshots.
    n(arenaSize);const unsigned char* p=(const unsigned char*)autotest::g_arena;
    for(unsigned k=0;k<arenaSize;){unsigned run=1;while(k+run<arenaSize&&p[k+run]==p[k])++run;n(run);capture->add(p+k,1);k+=run;}n(0);
    for(unsigned j=0;j<blockCount;++j)for(unsigned k=0;k<16;++k)if(blocks[j].p[k]!=0xd3||blocks[j].p[16+blocks[j].size+k]!=0x6c)invalid();
    n(eventIndex);n(events.size());n(oracleErrors);
}
void reseed(){
    if(!testCase->reseed)return;
    field<void*>(ui,0x90)=objects[2];field<unsigned>(ui,0x98)=0xabcdef01;
    field<int>(ui,0x12fc)=4;
    field<void*>(ui,0x68)=objects[4];field<long long>(tips[0],0x10)=556;
}
void side(void* context,autotest::Capture& out,bool candidate){
    testCase=(const Case*)context;capture=&out;initialize();detour::Set d;redirect(d);
    if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    for(step=0;step<testCase->repeat;++step){
        if(step)reseed();
        activeFault=step?0:testCase->fault;
        events.clear();eventIndex=0;shadow.assign((unsigned char*)autotest::g_arena,(unsigned char*)autotest::g_arena+arenaSize);
        bool modelCaught=false;try{modelCleanup();}catch(const Failure& f){modelCaught=true;if(f.ordinal!=activeFault)invalid();}
        expectedFinal=shadow;
        autotest::Capture invocation;invocation.reset();bool caught=false;
        try{autotest::invoke(invocation,candidate?&newCleanup:&oldCleanup,(CGameUI*)ui);}
        catch(const Failure& f){caught=true;n(f.ordinal);if(f.ordinal!=activeFault)invalid();}
        catch(...){invalid();}
        if(caught!=modelCaught||caught!=(activeFault!=0)||eventIndex!=events.size())invalid();
        if(std::memcmp(autotest::g_arena,&expectedFinal[0],arenaSize))invalid();
        n(step);n(caught);n(invocation.callStarted);n(invocation.callCompleted);
        if(invocation.callStarted!=1||invocation.callCompleted!=(caught?0u:1u))invalid();
        if(!step){out.callTarget=invocation.callTarget;out.callStarted=invocation.callStarted;out.callCompleted=invocation.callCompleted;}
        if(invocation.issue)out.issue=invocation.issue;
        snapshot();
    }
}
void before(void* p,autotest::Capture& out){side(p,out,false);}
void after(void* p,autotest::Capture& out){side(p,out,true);}
bool pair(const tlhybrid_host* host,autotest::Coverage& cv,Case& c,unsigned& count){
    autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);++count;
    unsigned ae=UINT_MAX,be=UINT_MAX;
    if(a.capture.length>=4)std::memcpy(&ae,a.capture.data+a.capture.length-4,4);
    if(b.capture.length>=4)std::memcpy(&be,b.capture.data+b.capture.length-4,4);
    bool okay=!ae&&!be&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!a.capture.issue&&!b.capture.issue&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    if(!c.fault){if(cv.observe(host,a,b))okay=false;}
    else okay=okay&&a.capture.callTarget==(uint64_t)(uintptr_t)&oldCleanup&&a.capture.callStarted==1&&b.capture.callStarted==1&&!a.capture.callCompleted&&!b.capture.callCompleted&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget);
    if(!okay){cv.report(host);host->log("    cleanup #%u mask=%u cursor=%d replacement=%d mutation=%u actualHover=%u repeat=%u alias=%u reseed=%u fault=%u exits=%d/%d valid=%u/%u issue=%u/%u completion=%u/%u bytes=%lu/%lu\n",count,c.mask,c.cursor,c.replacementCursor,c.mutation,unsigned(c.actualHover),c.repeat,c.alias,unsigned(c.reseed),c.fault,a.childStatus,b.childStatus,unsigned(a.reportValid),unsigned(b.reportValid),a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length);}
    return okay;
}
}
TL_TEST(gameui_cleanup_references){
    autotest::Coverage cv("gameui_cleanup_references",(uint64_t)(uintptr_t)&oldCleanup);unsigned count=0;
    const int cursors[]={INT_MIN,-1,0,1,2,3,4,5,INT_MAX};
    for(unsigned mask=0;mask<16;++mask)for(unsigned cursor=0;cursor<9;++cursor){Case c;c.mask=mask;c.cursor=cursors[cursor];c.repeat=2;c.alias=mask%2;if(!pair(host,cv,c,count))return 1;}
    for(unsigned lane=0;lane<2;++lane)for(unsigned mutation=0;mutation<=5;++mutation){
        if(lane&&mutation==5)continue;
        for(unsigned cursor=0;cursor<9;++cursor){Case c;c.actualHover=lane;c.mutation=mutation;c.replacementCursor=cursors[cursor];c.cursor=cursors[(cursor+3)%9];c.repeat=2;c.reseed=true;if(!pair(host,cv,c,count))return 1;}
    }
    cv.report(host);host->log("    cleanup: %u normal call pairs, full-prefix and final byte oracle\n",count);
    return cv.completed!=count||cv.different||cv.missing;
}
TL_TEST(gameui_cleanup_references_exceptions){
    autotest::Coverage cv("cleanup exceptions excluded from acceptance",(uint64_t)(uintptr_t)&oldCleanup);unsigned count=0;
    // Both all-present lanes have 21 boundaries: the real-hover release takes
    // the place of the isolated hover callback. Every fault is reached once,
    // then the same retained state is retried successfully without reseeding.
    for(unsigned lane=0;lane<2;++lane)for(unsigned mutation=0;mutation<=4;++mutation)for(unsigned fault=1;fault<=21;++fault){
        Case c;c.actualHover=lane;c.mutation=mutation;c.fault=fault;c.repeat=2;if(!pair(host,cv,c,count))return 1;
    }
    host->log("    cleanup: %u expected-throw/recovery witnesses, no completed coverage credited\n",count);return 0;
}
