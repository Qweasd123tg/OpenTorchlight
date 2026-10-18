#include <cstring>

#include <map>
#include <vector>
#include <string>
#include <stdint.h>
#include <new>
#include <OgreVector3.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#define protected public
#include "Descriptor.h"
#include "EditorScene.h"
#include "CollisionShape.h"
#include "CameraShake.h"
#include "GameStateController.h"
#include "ResourceManager.h"
#include "GameClient.h"
#include "Player.h"
#include "ParticleTechWrapper.h"
#undef private
#undef protected
#define TARGET(old,newer,sym) TL_ORIGINAL(void,old,(void*,void*,unsigned,void*),sym) extern "C" void newer(void*,void*,unsigned,void*) __asm__(sym);
TARGET(aeOldCollision,aeNewCollision,"_ZN25CCollisionShapeDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
TARGET(aeOldShake,aeNewShake,"_ZN22CCameraShakeDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
TARGET(aeOldState,aeNewState,"_ZN30CGameStateControllerDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
TARGET(aeOldTechnique,aeNewTechnique,"_ZN30CParticleTechWrapperDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
TL_FUNCTION(aeParent,"_ZN29CPositionableObjectDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
TL_FUNCTION(aePosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(aeStart,"_ZN12CCameraShake16startCameraShakeERKN4Ogre7Vector3Eb")
TL_FUNCTION(aePerform,"_ZN20CGameStateController19performStateControlEv")
TL_FUNCTION(aeHelp,"_ZN20CGameStateController8showHelpEv")
TL_FUNCTION(aeHeal,"_ZN20CGameStateController10healPlayerEv")
TL_FUNCTION(aeTeleport,"_ZN10CCharacter16teleportToMasterEf")
extern "C" char aeCollisionTable[] __asm__("_ZTV15CCollisionShape");
extern "C" char aeShakeTable[] __asm__("_ZTV12CCameraShake");
extern "C" char aeStateTable[] __asm__("_ZTV20CGameStateController");
extern "C" char aeTechniqueTable[] __asm__("_ZTV20CParticleTechWrapper");
extern "C" char aeBaseTable[] __asm__("_ZTV17CEditorBaseObject");
namespace {
struct Case {unsigned op,kind,event,seed;};
autotest::Capture* output;Case input;void* current;void* descriptor;void* sender;void* owner;CPlayer* player;CCharacter* followers[4];unsigned calls;
void number(unsigned x){output->add(&x,4);}void identity(void* p,void* expected){number(p==expected);if(p!=expected)output->issue=autotest::Capture::InvalidReport;}
void enabled(void*p,bool value){number(1);identity(p,current);number(value);}
bool getEnabled(void*p){number(9);identity(p,current);return input.seed&1;}
void activate(void*p,bool v){number(10);identity(p,current);number(v);}
void stop(void*p){number(11);identity(p,current);}
void play(void*p){number(12);identity(p,current);}
void broadcast(void*p,unsigned event){number(13);identity(p,current);number(event);}
void parent(void*p,void* object,unsigned event,void* data){number(2);identity(p,descriptor);identity(object,current);number(event);identity(data,sender);}
Ogre::Vector3 position(void*p,bool absolute){number(3);identity(p,owner);number(absolute);return Ogre::Vector3(input.seed*0.25f,-3.5f,7.75f);}
void start(void*p,const Ogre::Vector3& v,bool update){number(4);identity(p,current);output->add(&v,sizeof(v));number(update);}
void perform(void*p){number(5);identity(p,current);number(static_cast<CGameStateController*>(p)->m_bEnabled);}
void help(void*p){number(6);identity(p,current);}void heal(void*p){number(7);identity(p,current);}
void teleport(void*p,float distance){number(8);unsigned id=99;for(unsigned i=0;i<4;++i)if(p==followers[i])id=i;number(id);output->add(&distance,4);if(id==99)output->issue=autotest::Capture::InvalidReport;++calls;
 if(calls==1 && input.seed%4==1)player->m_Followers.clear();
 if(calls==1 && input.seed%4==2)player->m_Followers.push_back(followers[3]);
}
void side(void*raw,autotest::Capture& out,bool ours){input=*static_cast<Case*>(raw);output=&out;calls=0;
 uint64_t self[128]={0},object[1024]={0},send[16]={0},scene[(sizeof(CEditorScene)+7)/8]={0},resources[(sizeof(CResourceManager)+7)/8]={0},client[(sizeof(CGameClient)+7)/8]={0},playerMem[(sizeof(CPlayer)+7)/8]={0},follow[4][16]={{0}};
 descriptor=self;sender=send;current=object;owner=scene;player=reinterpret_cast<CPlayer*>(playerMem);for(unsigned i=0;i<4;++i)followers[i]=reinterpret_cast<CCharacter*>(follow[i]);
 char* table=input.op==0?aeCollisionTable:input.op==1?aeShakeTable:input.op==2?aeStateTable:aeTechniqueTable;
 void* collisionTable[80]={0};if(input.op==0){std::memcpy(collisionTable,aeCollisionTable,sizeof(collisionTable));collisionTable[2+8]=reinterpret_cast<void*>(&enabled);table=reinterpret_cast<char*>(collisionTable);}
 if(input.op==3){std::memcpy(collisionTable,aeTechniqueTable,sizeof(collisionTable));collisionTable[2+9]=reinterpret_cast<void*>(&getEnabled);collisionTable[2+6]=reinterpret_cast<void*>(&broadcast);collisionTable[2+0x200/8]=reinterpret_cast<void*>(&stop);collisionTable[2+0x208/8]=reinterpret_cast<void*>(&play);collisionTable[2+0x218/8]=reinterpret_cast<void*>(&activate);table=reinterpret_cast<char*>(collisionTable);}
 *reinterpret_cast<void**>(object)=(input.kind==2?aeBaseTable:table)+16;
 CDescriptor* desc=reinterpret_cast<CDescriptor*>(self);desc->m_pSceneOwner=input.seed&0x100?NULL:reinterpret_cast<CEditorScene*>(scene);
 reinterpret_cast<CEditorBaseObject*>(object)->m_pSceneOwner=reinterpret_cast<CEditorScene*>(scene);
 CResourceManager* res=reinterpret_cast<CResourceManager*>(resources);CGameClient* cli=reinterpret_cast<CGameClient*>(client);
 reinterpret_cast<CEditorScene*>(scene)->m_pResourceManager=res;new(&res->m_GameClients)TArrayList<CGameClient*>(2);res->m_GameClients.add(cli);cli->m_pPlayer=input.seed%5?player:NULL;
 new(&player->m_Followers)std::vector<CCharacter*>;for(unsigned i=0;i<input.seed%4;++i)player->m_Followers.push_back(followers[i]);
 reinterpret_cast<CGameStateController*>(object)->m_bEnabled=(input.seed&1)!=0;
 detour::Set d;TL_REDIRECT(d,aeParent,&parent);TL_REDIRECT(d,aePosition,&position);TL_REDIRECT(d,aeStart,&start);TL_REDIRECT(d,aePerform,&perform);TL_REDIRECT(d,aeHelp,&help);TL_REDIRECT(d,aeHeal,&heal);TL_REDIRECT(d,aeTeleport,&teleport);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Fn)(void*,void*,unsigned,void*);Fn fn=input.op==0?(ours?aeNewCollision:aeOldCollision):input.op==1?(ours?aeNewShake:aeOldShake):input.op==2?(ours?aeNewState:aeOldState):(ours?aeNewTechnique:aeOldTechnique);
 autotest::invoke(out,fn,descriptor,input.kind?current:NULL,input.event,sender);
 number(reinterpret_cast<CGameStateController*>(object)->m_bEnabled);number(player->m_Followers.size());number(calls);
 player->m_Followers.~vector();res->m_GameClients.~TArrayList<CGameClient*>();
}
void original(void*p,autotest::Capture&c){side(p,c,false);}void recovered(void*p,autotest::Capture&c){side(p,c,true);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uint64_t address){autotest::Coverage coverage(name,address);const unsigned events[]={0,1,2,3,14,15,16,17,74,75,76,77,80,81,0x80000000u,0xffffffffu};
 for(unsigned seed=0;seed<16;++seed)for(unsigned kind=0;kind<3;++kind)for(unsigned e=0;e<16;++e){
  // These two malformed inputs fault in the shipped shake dispatch. Valid
  // shake activation and null/wrong-type nonactivation run through both bodies.
  if(op==1&&kind!=1&&events[e]==15)continue;
  Case c={op,kind,events[e],seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
  if(coverage.observe(host,a,b)){host->log("    advance dispatch %u seed %u kind %u event %u status %d/%d bytes %lu/%lu\n",op,seed,kind,c.event,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}
 }coverage.report(host);return 0;}
}
TL_TEST(advance_editor_collision_dispatch){return run(host,0,"advance_editor_collision_dispatch",(uint64_t)(uintptr_t)aeOldCollision);}
TL_TEST(advance_editor_shake_dispatch){return run(host,1,"advance_editor_shake_dispatch",(uint64_t)(uintptr_t)aeOldShake);}
TL_TEST(advance_editor_state_dispatch){return run(host,2,"advance_editor_state_dispatch",(uint64_t)(uintptr_t)aeOldState);}

TL_TEST(advance_editor_particle_dispatch){return run(host,3,"advance_editor_particle_dispatch",(uint64_t)(uintptr_t)aeOldTechnique);}

TL_TEST(advance_editor_shake_original_faults)
{
    unsigned matches = 0;
    for (unsigned kind = 0; kind < 3; kind += 2)
        for (unsigned missingOwner = 0; missingOwner < 2; ++missingOwner) {
            Case c = {1, kind, missingOwner ? 0u : 15u, missingOwner ? 0x100u : 0u};
            autotest::Outcome a, b;
            autotest::runChild(original, &c, a);
            autotest::runChild(recovered, &c, b);
            if (a.reportValid || b.reportValid || !WIFEXITED(a.childStatus) ||
                !WIFEXITED(b.childStatus) || WEXITSTATUS(a.childStatus) != 139 ||
                WEXITSTATUS(b.childStatus) != 139)
                return 1;
            ++matches;
        }
    host->log("    Original malformed shake inputs: %u matching SIGSEGV exits, excluded from normal coverage\n", matches);
    return matches == 4 ? 0 : 1;
}
