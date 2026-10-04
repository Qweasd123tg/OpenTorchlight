#include <cstring>
#include <limits>
#include <new>
#include <vector>
#include <OgreSceneNode.h>
#include "AutoTest.h"
#include "TriggerSphere.h"
#include "TriggerBox.h"
#include "GameClient.h"
#include "Player.h"
#include "ResourceManager.h"

TL_ORIGINAL(void, originalSphereUpdate, (CTriggerSphere*, float, CEditorScene*),
            "_ZN14CTriggerSphere13updateTriggerEfP12CEditorScene")

TL_ORIGINAL(void, originalBoxUpdate, (CTriggerBox*, float, CEditorScene*),
            "_ZN11CTriggerBox13updateTriggerEfP12CEditorScene")

namespace {
struct Case { unsigned int seed; bool box; };
void callOriginal(CTriggerSphere* object) { originalSphereUpdate(object,0.25f,NULL); }
void callOriginal(CTriggerBox* object) { originalBoxUpdate(object,0.25f,NULL); }
std::vector<unsigned int> events;
void recordEvent(void*, unsigned int event) { events.push_back(event); }
void pointerAt(void* object, size_t offset, const void* value) {
    std::memcpy(static_cast<char*>(object)+offset,&value,sizeof(value));
}
void vectorAt(void* object, size_t offset, const Ogre::Vector3& value) {
    std::memcpy(static_cast<char*>(object)+offset,&value,sizeof(value));
}
struct AlignedPlayer { long long data[(sizeof(CPlayer)+7)/8]; };
struct AlignedClient { long long data[(sizeof(CGameClient)+7)/8]; };
struct AlignedManager { long long data[(sizeof(CResourceManager)+7)/8]; };

typedef char sphere_size[sizeof(CTriggerSphere)==0x108?1:-1];

template<class Trigger>
void body(Case& c,bool ours,autotest::Capture& out) {
    Trigger sphere(NULL);
    char* self=reinterpret_cast<char*>(&sphere);
    void* table[60];std::memcpy(table,*reinterpret_cast<void***>(self),sizeof(table));
    table[6]=reinterpret_cast<void*>(&recordEvent);
    *reinterpret_cast<void***>(self)=table;
    AlignedManager manager;std::memset(&manager,0,sizeof(manager));
    TArrayList<CGameClient*>* clients=new(reinterpret_cast<char*>(&manager)+0x28) TArrayList<CGameClient*>(4);
    AlignedPlayer players[3];AlignedClient gameClients[3];
    std::memset(players,0,sizeof(players));std::memset(gameClients,0,sizeof(gameClients));
    Ogre::SceneNode sphereNode(NULL), playerNode(NULL);
    Ogre::Vector3 center(7.0f,-3.0f,2.0f);
    vectorAt(self,0x84,center);
    static const float radii[]={0.0f,1.0f,3.0f,-1.0f,0.5f};
    float radius=radii[c.seed%5];
    if(c.seed%29==0)radius=std::numeric_limits<float>::quiet_NaN();
    if(c.seed%31==0)radius=std::numeric_limits<float>::infinity();
    if(c.box) {
        vectorAt(self,0x104,Ogre::Vector3(radius*2,radius*2,radius*2));
        vectorAt(self,0x110,Ogre::Vector3(radius,radius,radius));
    } else std::memcpy(self+0x104,&radius,sizeof(radius));
    self[0x100]=(c.seed>>1)&1;self[0x101]=(c.seed>>2)&1;self[0x102]=(c.seed>>3)&1;
    self[0x103]=c.seed%11!=0;self[0x81]=c.seed%7!=0;
    unsigned int count=c.seed%4;
    for(unsigned int i=0;i<count;++i) {
        pointerAt(&gameClients[i],0x58,c.seed%13==0?NULL:&players[i]);
        clients->add(reinterpret_cast<CGameClient*>(&gameClients[i]));
    }
    pointerAt(self,0x68,c.seed%17==0?NULL:&manager);
    for(unsigned int step=0;step<8;++step) {
        events.clear();
        for(unsigned int i=0;i<count;++i) {
            float distance=(step==0?0.0f:step==1?radius:step==2?-radius:
                            step==3?radius+0.001f:step==4?radius-0.001f:step==5?20.0f:step==6?-20.0f:0.25f);
            Ogre::Vector3 position=center;
            position[(c.seed+i)%3]+=distance;
            if(i==1)position+=Ogre::Vector3(0.1f,0.2f,0.3f);
            vectorAt(&players[i],0x84,position);
        }
        // Real OGRE nodes make absolute-position mutations observable.
        if(c.seed%5==0 && count) {
            playerNode.setPosition(center+Ogre::Vector3(step%2?0.0f:30.0f,0.0f,0.0f));
            pointerAt(&players[0],0x58,&playerNode);pointerAt(&players[0],0x50,&sphere);
        }
        if(c.seed%5==1) {
            sphereNode.setPosition(center+Ogre::Vector3(step%2?0.0f:30.0f,0.0f,0.0f));
            pointerAt(self,0x58,&sphereNode);pointerAt(self,0x50,&sphere);
        }
        if(ours)sphere.updateTrigger(0.25f,NULL);else callOriginal(&sphere);
        out.add(self+0x100,c.box?28:8);
        size_t n=events.size();out.add(&n,sizeof(n));
        for(size_t i=0;i<n;++i)out.add(&events[i],sizeof(events[i]));
    }
    pointerAt(self,0x58,NULL);pointerAt(self,0x50,NULL);pointerAt(self,0x68,NULL);
    clients->~TArrayList<CGameClient*>();
}
void dispatch(void* p,bool ours,autotest::Capture& out) {
    Case& c=*static_cast<Case*>(p);
    if(c.box)body<CTriggerBox>(c,ours,out);else body<CTriggerSphere>(c,ours,out);
}
void original(void* p,autotest::Capture& out) {dispatch(p,false,out);}
void recovered(void* p,autotest::Capture& out) {dispatch(p,true,out);}
}
TL_TEST(trigger_geometry_boundaries_and_events) {
    int failures=0;
    for(unsigned int shape=0;shape<2;++shape)
    for(unsigned int seed=0;seed<160;++seed) {
        Case c={seed,shape!=0};autotest::Outcome a,b;
        autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
        bool same=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&
                  WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
                  a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&
                  std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!same)host->log("    trigger shape %u seed %u status %d/%d bytes %lu/%lu\n",shape,seed,a.status,b.status,
                          (unsigned long)a.capture.length,(unsigned long)b.capture.length);
        TL_CHECK(failures,same);
    }
    return failures;
}
