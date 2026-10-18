#include "AutoTest.h"
#include "Automap.h"
#include <OgreColourValue.h>
#include <new>
#define DECL(old,neo,args,symbol) TL_ORIGINAL(void,old,args,symbol) extern "C" void neo args __asm__(symbol);
DECL(oClear,nClear,(CAutomap*),"_ZN8CAutomap13clearNPCIconsEv")
DECL(oVisibility,nVisibility,(CAutomap*,Ogre::Billboard*,bool),"_ZN8CAutomap22setNPCBillboardVisibleEPN4Ogre9BillboardEb")
DECL(oFinalize,nFinalize,(CAutomap*),"_ZN8CAutomap8finalizeEv")
DECL(oPosition,nPosition,(CAutomap*,const Ogre::Vector3&),"_ZN8CAutomap17setPlayerPositionERKN4Ogre7Vector3E")
#undef DECL
namespace {
struct Case { unsigned op, seed; };
autotest::Capture* capture;
Ogre::Billboard* billboards;
unsigned removeCalls;
void number(unsigned x) { capture->add(&x, sizeof(x)); }
void id(Ogre::Billboard* b) { number(b ? unsigned(b-billboards)+1 : 0); }
void removeBillboard(Ogre::BillboardSet*, Ogre::Billboard* b) { ++removeCalls; id(b); }
void vectorState(const std::vector<Ogre::Billboard*>& v) {
    number(v.size()); number(v.capacity());
    for (unsigned i=0; i<v.size(); ++i) id(v[i]);
}
void floatVectorState(const std::vector<float>& v) {
    number(v.size()); number(v.capacity());
    for (unsigned i=0; i<v.size(); ++i) capture->add(&v[i],4);
}
void side(void* raw, autotest::Capture& out, bool ours) {
    Case c=*static_cast<Case*>(raw); capture=&out; removeCalls=0;
    uint64_t storage[(sizeof(CAutomap)+7)/8];
    std::memset(storage,0xa5,sizeof(storage));
    CAutomap* self=reinterpret_cast<CAutomap*>(storage);
    new (&self->m_vMapTileBillboards) std::vector<Ogre::Billboard*>;
    new (&self->m_vMapTileRevealValues) std::vector<float>;
    new (&self->m_vNPCBillboards) std::vector<Ogre::Billboard*>;
    new (&self->m_vNPCRevealValues) std::vector<float>;
    new (&self->m_hiddenNPCBillboards) TArrayList<Ogre::Billboard*>(1+c.seed%3);
    Ogre::Billboard pool[6]; billboards=pool;
    for (unsigned i=0; i<6; ++i) {
        pool[i].mParentSet=NULL;
        pool[i].mPosition=Ogre::Vector3(float(i),float(i+1),-float(i));
        pool[i].mColour=Ogre::ColourValue(.1f*i,.2f,.3f,.4f);
    }
    self->m_pPlayerBillboard=pool+5;
    self->m_bTilesChanged=c.seed&1;
    self->m_bFullMap=c.seed&2;
    self->m_minimumX=float(int(c.seed%3)-1)*4.0f;
    self->m_minimumZ=float(int(c.seed%5)-2)*2.0f;
    const float sizes[]={0,4,16,20,32,17.5f,19.999f,21.25f};
    self->m_maximumX=self->m_minimumX+sizes[c.seed%8];
    self->m_maximumZ=self->m_minimumZ+sizes[(c.seed/8)%8];
    self->m_iMapGridWidth=16; self->m_iMapGridHeight=16;
    self->m_pRevealedTiles=new float[256];
    for (unsigned i=0;i<256;++i) self->m_pRevealedTiles[i]=float((i+c.seed)%5)*.25f;
    if (c.op==2 && (c.seed&16)) {
        delete[] self->m_pRevealedTiles;
        self->m_pRevealedTiles=NULL;
    }
    for (unsigned i=0;i<c.seed%5;++i) {
        self->m_vMapTileBillboards.push_back(pool+i);
        self->m_vMapTileRevealValues.push_back(float(i)*.25f);
        self->m_vNPCBillboards.push_back(pool+4-i);
        self->m_vNPCRevealValues.push_back(float(i)*.2f);
        self->m_hiddenNPCBillboards.add(pool+(i+c.seed)%6);
    }
    // Exercise removal without growth, reuse of spare capacity, and fresh growth.
    if (c.seed&8) self->m_hiddenNPCBillboards.remove(pool+c.seed%6);
    void* table[0x240/sizeof(void*)]; std::memset(table,0,sizeof(table));
    table[0x230/sizeof(void*)]=reinterpret_cast<void*>(&removeBillboard);
    void* receiver[1]={table};
    self->m_pTileBillboardSet=reinterpret_cast<Ogre::BillboardSet*>(receiver);
    if (c.op==0) autotest::invoke(out,ours?nClear:oClear,self);
    else if (c.op==1) autotest::invoke(out,ours?nVisibility:oVisibility,self,pool+(c.seed/2)%6,bool(c.seed&4));
    else if (c.op==2) autotest::invoke(out,ours?nFinalize:oFinalize,self);
    else {
        const float positions[]={-32,-4,-.001f,0,.001f,3.999f,4,8,16,32,48,64};
        Ogre::Vector3 position(positions[c.seed%12],float(c.seed%7),positions[(c.seed/4)%12]);
        autotest::invoke(out,ours?nPosition:oPosition,self,position);
        out.add(&position,sizeof(position));
    }
    number(removeCalls); number(self->m_bTilesChanged);
    number(self->m_iMapGridWidth); number(self->m_iMapGridHeight);
    if (c.op==0 && removeCalls!=c.seed%5) out.issue=autotest::Capture::InvalidReport;
    if (c.op==2 && self->m_iMapGridWidth>4 && self->m_iMapGridHeight<4) out.issue=autotest::Capture::InvalidReport;
    int n=self->m_iMapGridWidth*self->m_iMapGridHeight;
    if(n<0||n>1024) { out.issue=autotest::Capture::InvalidReport; return; }
    out.add(self->m_pRevealedTiles,n*sizeof(float));
    vectorState(self->m_vMapTileBillboards); floatVectorState(self->m_vMapTileRevealValues);
    vectorState(self->m_vNPCBillboards); floatVectorState(self->m_vNPCRevealValues);
    number(self->m_hiddenNPCBillboards.size());
    out.add(reinterpret_cast<const unsigned char*>(&self->m_hiddenNPCBillboards)+8,12);
    for(unsigned i=0;i<self->m_hiddenNPCBillboards.size();++i) id(self->m_hiddenNPCBillboards[i]);
    for(unsigned i=0;i<6;++i) { out.add(&pool[i].mPosition,sizeof(pool[i].mPosition)); out.add(&pool[i].mColour,sizeof(pool[i].mColour)); }
    // Unknown state and the viewport/material pointers must survive every operation.
    out.add(self->m_ViewportState,sizeof(self->m_ViewportState));
    out.add(self->m_gapA3,sizeof(self->m_gapA3));
    delete[] self->m_pRevealedTiles;
    self->m_hiddenNPCBillboards.~TArrayList();
    self->m_vMapTileBillboards.~vector(); self->m_vMapTileRevealValues.~vector();
    self->m_vNPCBillboards.~vector(); self->m_vNPCRevealValues.~vector();
}
void original(void* c,autotest::Capture& out) { side(c,out,false); }
void candidate(void* c,autotest::Capture& out) { side(c,out,true); }
int run(const tlhybrid_host* host,unsigned op,const char* name,uint64_t address) {
    autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<64;++i) {
        Case c={op,i}; autotest::Outcome& a=autotest::g_outcomes[0]; autotest::Outcome& b=autotest::g_outcomes[1];
        autotest::runChild(original,&c,a); autotest::runChild(candidate,&c,b);
        if(coverage.observe(host,a,b)) {
            host->log("    seed %u status %d/%d child %d/%d bytes %lu/%lu\n",i,a.status,b.status,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
            unsigned at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;
            host->log("    first difference %u\n",at); coverage.report(host); return 1;
        }
    }
    coverage.report(host); return 0;
}
}
TL_TEST(continue_automap_clear) { return run(host,0,"continue_automap_clear",(uint64_t)(uintptr_t)oClear); }
TL_TEST(continue_automap_visibility) { return run(host,1,"continue_automap_visibility",(uint64_t)(uintptr_t)oVisibility); }
TL_TEST(continue_automap_finalize) { return run(host,2,"continue_automap_finalize",(uint64_t)(uintptr_t)oFinalize); }
TL_TEST(continue_automap_position) { return run(host,3,"continue_automap_position",(uint64_t)(uintptr_t)oPosition); }
