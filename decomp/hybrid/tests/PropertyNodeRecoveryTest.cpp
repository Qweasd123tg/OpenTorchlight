#include <Ogre.h>
#include <fenv.h>
#include <cstring>
#include <vector>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "PropertyNode.h"
#include "Level.h"
#include "GameClient.h"
#include "Player.h"
#undef protected
#undef private
#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/ParticleNativeOwners.h"
#include "UtilitiesMath.h"

TL_ORIGINAL(void, propertyKillOriginal, (CPropertyNode*), "_ZN13CPropertyNode19killOrMoveBaseUnitsEv")
extern "C" void propertyKillCandidate(CPropertyNode*) __asm__("_ZN13CPropertyNode19killOrMoveBaseUnitsEv");
TL_ORIGINAL(void, propertyBoundsOriginal, (CPropertyNode*), "_ZN13CPropertyNode17updateBoundingBoxEv")
extern "C" void propertyBoundsCandidate(CPropertyNode*) __asm__("_ZN13CPropertyNode17updateBoundingBoxEv");
TL_FUNCTION(propertyPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(propertyHP,"_ZN10CCharacter2HPEv")
TL_FUNCTION(propertyModifyHP,"_ZN10CCharacter8modifyHPEf")
TL_FUNCTION(propertyTeleport,"_ZN10CCharacter16teleportToMasterEf")
TL_FUNCTION(propertyExpand,"_ZN4MATH12expandBoundsERN4Ogre7Vector3ES2_S1_")
TL_ORIGINAL(void, propertyExpandOriginal,(Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3),"_ZN4MATH12expandBoundsERN4Ogre7Vector3ES2_S1_")

namespace {
struct Case { unsigned seed; bool bounds,negative; };
const Case* current;autotest::Capture* output;CPropertyNode* property;
ParticleNativeOwners owners;CCharacter* actors[7];CPlayer* player;
Ogre::Vector3 positions[8],scaleValue;Ogre::Quaternion rotationValue;
CCullingBounds* culling[2];TLinkedListNode<CCharacter*>* links;
unsigned positionCalls[8],scaleCalls,orientationCalls,expandCalls,hpCalls[7],teleportCalls[7];
float damage[7];detour::Set* expandHook;

void number(long long value){output->add(&value,sizeof value);}
void scalar(float value){output->add(&value,sizeof value);}
void vector(const Ogre::Vector3& value){output->add(&value,sizeof value);}
float bits(unsigned value){float result;std::memcpy(&result,&value,4);return result;}
unsigned identity(const void* p){if(p==property)return 8;for(unsigned i=0;i<7;++i)if(p==actors[i])return i;return 99;}
void event(unsigned tag,const void* p){number(tag);number(identity(p));}

Ogre::Vector3 position(CPositionableObject* p,bool world)
{
    unsigned id=identity(p);event(1,p);number(world);
    if(id>8||!world){output->issue=autotest::Capture::InvalidReport;return Ogre::Vector3::ZERO;}
    unsigned slot=id==8?7:id;++positionCalls[slot];
    if(!current->bounds&&current->seed%13==12&&id==8&&links)links[0].m_pNext=&links[2];
    Ogre::Vector3 result=positions[slot];
    // Repeated character reads must remain observable across callbacks.
    if(!current->bounds&&current->seed%7==6&&positionCalls[slot]>1)result.x+=2.0f;
    vector(result);return result;
}
const Ogre::Vector3& scale(CPropertyNode* p)
{
    event(2,p);++scaleCalls;
    if(current->seed%10==8)property->m_cullingBounds=culling[1];
    return scaleValue;
}
float scaleX(CPropertyNode* p)
{
    event(3,p);++scaleCalls;
    if(!current->bounds&&current->seed%17==16){property->m_iPropertyNodeType=9;actors[4]->m_pMaster=actors[0];}
    scalar(scaleValue.x);return scaleValue.x;
}
const Ogre::Quaternion& orientation(Ogre::SceneNode*)
{
    number(4);++orientationCalls;
    if(current->seed%10==9)property->m_cullingBounds=culling[1];
    return rotationValue;
}
int hp(CCharacter* p){unsigned id=identity(p);event(5,p);if(id>=7){output->issue=autotest::Capture::InvalidReport;return 0;}++hpCalls[id];int result=int(current->seed%41)-7+int(id)*13;number(result);return result;}
void modify(CCharacter* p,float amount){unsigned id=identity(p);event(6,p);scalar(amount);if(id>=7){output->issue=autotest::Capture::InvalidReport;return;}damage[id]+=amount;if(current->seed%19==18&&links&&id<6)links[id].m_pNext=NULL;}
void teleport(CCharacter* p,float distance){unsigned id=identity(p);event(7,p);scalar(distance);if(id>=7){output->issue=autotest::Capture::InvalidReport;return;}++teleportCalls[id];positions[id].x-=distance;if(current->seed%23==22&&id<6)actors[id+1]->m_bInActiveRange=false;}

void expand(Ogre::Vector3& minimum,Ogre::Vector3& maximum,Ogre::Vector3 point)
{
    number(9);number(&minimum==&culling[0]->m_vWorldMinimum?0:1);vector(minimum);vector(maximum);vector(point);++expandCalls;
    expandHook->restore();propertyExpandOriginal(minimum,maximum,point);TL_REDIRECT((*expandHook),propertyExpand,&expand);
    if(expandHook->failed()){output->issue=autotest::Capture::InvalidReport;return;}
    // Check that local corners are read at each native expansion, and that
    // final AABB selection reloads the owner pointer after the callbacks.
    if(current->seed%10==6&&expandCalls==2)culling[0]->m_vMaximum.x+=3.5f;
    if(current->seed%10==7&&expandCalls==3)property->m_cullingBounds=culling[1];
    vector(minimum);vector(maximum);
}

union PropertyStorage { long double alignment; unsigned char data[sizeof(CPropertyNode)]; };
void captureBounds(CCullingBounds* b)
{
    vector(b->m_vMinimum);vector(b->m_vMaximum);vector(b->m_vLocalMinimum);vector(b->m_vLocalMaximum);
    vector(b->m_vWorldMinimum);vector(b->m_vWorldMaximum);
    for(unsigned i=0;i<8;++i)vector(b->m_WorldCorners[i]);
}

void side(void* argument,autotest::Capture& out,bool ours)
{
    current=static_cast<Case*>(argument);output=&out;
    std::memset(positionCalls,0,sizeof positionCalls);std::memset(hpCalls,0,sizeof hpCalls);
    std::memset(teleportCalls,0,sizeof teleportCalls);std::memset(damage,0,sizeof damage);
    scaleCalls=orientationCalls=expandCalls=0;links=NULL;
    PropertyStorage storage;std::memset(&storage,0,sizeof storage);property=reinterpret_cast<CPropertyNode*>(storage.data);
    void* propertyTable[64]={0};propertyTable[0xa8/8]=reinterpret_cast<void*>(&scale);propertyTable[0xb0/8]=reinterpret_cast<void*>(&scaleX);
    void* propertyTablePointer=propertyTable;std::memcpy(property,&propertyTablePointer,sizeof(void*));
    // Real OGRE bounds and native culling owners; the property storage exposes
    // only the explicitly initialized fields needed by these two methods.
    new(&property->m_bounds) Ogre::AxisAlignedBox(Ogre::Vector3(-2,-2,-2),Ogre::Vector3(2,2,2));
    culling[0]=new CCullingBounds;culling[1]=new CCullingBounds;
    for(unsigned j=0;j<2;++j){for(unsigned i=0;i<8;++i)culling[j]->m_WorldCorners[i]=Ogre::Vector3(91+j,92+i,93);culling[j]->m_vWorldMinimum=Ogre::Vector3(-71,-72,-73);culling[j]->m_vWorldMaximum=Ogre::Vector3(71,72,73);}
    property->m_cullingBounds=culling[0];
    const unsigned seed=current->seed;
    scaleValue=Ogre::Vector3(1.0f,3.0f,1.0f);rotationValue=Ogre::Quaternion::IDENTITY;
    for(unsigned i=0;i<8;++i)positions[i]=Ogre::Vector3::ZERO;
    detour::Set hooks,expansion;
    TL_REDIRECT(hooks,propertyPosition,&position);
    if(current->bounds){
        const float sizes[]={0.0f,-0.0f,1.0f,-2.0f,0.125f,13.5f};
        scaleValue=Ogre::Vector3(sizes[(seed/10)%6],float(seed%7)-3,sizes[(seed/60)%6]);
        positions[7]=Ogre::Vector3(float(int(seed%11)-5)*0.25f,float(int(seed%13)-6),float(int(seed%17)-8)*0.5f);
        switch(seed/360%5){case 0:break;case 1:rotationValue=Ogre::Quaternion(Ogre::Radian(0.7853981634f),Ogre::Vector3::UNIT_Y);break;case 2:rotationValue=Ogre::Quaternion(Ogre::Radian(-1.25f),Ogre::Vector3::UNIT_X);break;case 3:rotationValue=Ogre::Quaternion(0.75f,0.25f,-0.125f,0.5f);break;case 4:rotationValue=Ogre::Quaternion(0,0,0,0);break;}
        if(seed>=1800){const unsigned values[]={0x7f800000u,0xff800000u,0x7fc01234u,0xffc05678u,0x00000001u,0x80000001u,0x7f7fffffu,0xff7fffffu};unsigned n=seed-1800;float value=bits(values[n/10%8]);switch(n/80%3){case 0:scaleValue.x=value;break;case 1:positions[7].z=value;break;case 2:rotationValue.w=value;break;}}
        void* nodeTable[72]={0};nodeTable[0x1f8/8]=reinterpret_cast<void*>(&orientation);void* node[4]={nodeTable,NULL,NULL,NULL};property->m_pSceneNode=reinterpret_cast<Ogre::SceneNode*>(node);
        expandHook=&expansion;TL_REDIRECT(expansion,propertyExpand,&expand);
        if(hooks.failed()||expansion.failed()){out.issue=autotest::Capture::InvalidReport;return;}
        feclearexcept(FE_ALL_EXCEPT);autotest::invoke(out,ours?propertyBoundsCandidate:propertyBoundsOriginal,property);
        number(fetestexcept(FE_ALL_EXCEPT));number(expandCalls);number(scaleCalls);number(orientationCalls);number(positionCalls[7]);
        if(expandCalls!=8||scaleCalls!=1||orientationCalls!=1||positionCalls[7]!=1)out.issue=autotest::Capture::InvalidReport;
        if(ours&&current->negative)culling[0]->m_WorldCorners[4].y+=123;
        number(property->m_cullingBounds==culling[1]);captureBounds(culling[0]);captureBounds(culling[1]);
        vector(property->m_bounds.getMinimum());vector(property->m_bounds.getMaximum());number(property->m_bounds.isNull()?0:property->m_bounds.isInfinite()?2:1);
    }else{
        finishlevel::Fixture fixture;fixture.resources.m_pLevel=&fixture.level;
        union ClientStorage {long double align;unsigned char bytes[sizeof(CGameClient)];} clientStorage;
        std::memset(&clientStorage,0,sizeof clientStorage);CGameClient* client=reinterpret_cast<CGameClient*>(clientStorage.bytes);
        client->m_pPlayer=seed%9==0?NULL:player;
        fixture.resources.m_GameClients.add(seed%31==0?NULL:client);if(seed%29==0)fixture.resources.m_pLevel=NULL;
        property->m_pResourceManager=&fixture.resources;
        property->m_iPropertyNodeType=seed%3==0?8:seed%3==1?9:6;
        scaleValue.x=float(int(seed/3%7)-2);positions[7]=Ogre::Vector3(float(int(seed/21%3)-1),0,0);
        const Ogre::Vector3 points[]={Ogre::Vector3(0,0,0),Ogre::Vector3(2,2,2),Ogre::Vector3(-2,-2,-2),Ogre::Vector3(3,0,0),Ogre::Vector3(0,3,0),Ogre::Vector3(0,0,-3),Ogre::Vector3(1,0,0)};
        TLinkedListNode<CCharacter*> nodes[7];links=nodes;
        for(unsigned i=0;i<7;++i){
            positions[i]=points[(seed/63+i)%7];actors[i]->m_bInActiveRange=((seed/7+i)%4)!=0;
            actors[i]->m_pMaster=(seed/5+i)%3==0?actors[0]:(seed/5+i)%3==1?NULL:actors[6];
            nodes[i].m_Data=actors[i];nodes[i].m_pNext=i==6?NULL:&nodes[i+1];nodes[i].m_pPrevious=i?&nodes[i-1]:NULL;
        }
        fixture.level.m_pCharacters->m_pHead=seed%37==0?NULL:nodes;
        if(seed%11==0)property->m_bounds.setNull();else if(seed%11==1)property->m_bounds.setInfinite();
        if(seed>=504){unsigned n=seed-504;const unsigned values[]={0x7fc01234u,0x7f800000u,0xff800000u,0x80000000u};positions[3][n/4%3]=bits(values[n%4]);scaleValue.x=bits(values[n/12%4]);}
        TL_REDIRECT(hooks,propertyHP,&hp);TL_REDIRECT(hooks,propertyModifyHP,&modify);TL_REDIRECT(hooks,propertyTeleport,&teleport);
        if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
        feclearexcept(FE_ALL_EXCEPT);autotest::invoke(out,ours?propertyKillCandidate:propertyKillOriginal,property);
        number(fetestexcept(FE_ALL_EXCEPT));number(scaleCalls);number(property->m_iPropertyNodeType);
        if(ours&&current->negative)damage[4]+=123;
        for(unsigned i=0;i<7;++i){number(positionCalls[i]);number(hpCalls[i]);number(teleportCalls[i]);scalar(damage[i]);vector(positions[i]);number(actors[i]->m_bInActiveRange);number(identity(actors[i]->m_pMaster));number(nodes[i].m_pNext?nodes[i].m_pNext-nodes:-1);}
        number(positionCalls[7]);fixture.level.m_pCharacters->m_pHead=NULL;links=NULL;
    }
    expansion.restore();hooks.restore();delete culling[0];delete culling[1];property->m_bounds.~AxisAlignedBox();
}
void original(void*p,autotest::Capture&out){side(p,out,false);}void candidate(void*p,autotest::Capture&out){side(p,out,true);}
int worker(const tlhybrid_host* host,bool bounds)
{
    if(!bounds){owners=particleNativeOwners(0);player=nativegame::createPlayer(owners.resources);actors[0]=player;for(unsigned i=1;i<7;++i)actors[i]=new CCharacter(owners.resources);}
    const char* label=bounds?"property_bounds_recovery":"property_kill_move_recovery";autotest::Coverage coverage(label,bounds?0x9f0330:0x9e7f60);
    unsigned count=bounds?2040:552;
    for(unsigned i=0;i<count;++i){Case c={i,bounds,false};autotest::Outcome a,b;autotest::runChild(original,&c,a,2000,10000);autotest::runChild(candidate,&c,b,2000,10000);if(coverage.observe(host,a,b)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    property bounds%u seed%u status%d/%d issue%u/%u bytes%lu/%lu first%lu\n",bounds,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);for(unsigned j=at;j<at+20&&j<a.capture.length&&j<b.capture.length;++j)host->log("    byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);coverage.report(host);return 1;}}
    coverage.report(host);Case c={38,bounds,true};autotest::Outcome a,b;autotest::runChild(original,&c,a,2000,10000);autotest::runChild(candidate,&c,b,2000,10000);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);host->log("    property negative bounds%u detected%u\n",bounds,detected?1:0);return !detected||!a.reportValid||!b.reportValid||a.childStatus||b.childStatus||autotest::incomplete(a)||autotest::incomplete(b);
}
int boundsWorker(const tlhybrid_host* host){return worker(host,true);}int killWorker(const tlhybrid_host* host){return worker(host,false);}
}
TL_TEST(property_bounds_recovery){return systems_fixture::isolated(boundsWorker,host,180);}
TL_TEST(property_kill_move_recovery){return systems_fixture::isolated(killWorker,host,180);}
