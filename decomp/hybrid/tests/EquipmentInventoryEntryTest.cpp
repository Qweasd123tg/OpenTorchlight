#include <cstring>
#include <new>
#include <Ogre.h>
#define private public
#define protected public
#include "Equipment.h"
#include "Player.h"
#include "GameClient.h"
#include "Particle.h"
#include "EditorScene.h"
#undef private
#undef protected
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,originalInventoryEntry,(CEquipment*,CInventory*,CCharacter*),"_ZN10CEquipment16addedToInventoryEP10CInventoryP10CCharacter")
TL_FUNCTION(ieQuest,"_ZN9CBaseUnit14questEventFireE13EQUEST_EVENTSP10CCharacterPS_")
TL_FUNCTION(ieState,"_ZN9CBaseUnit18broadcastUnitStateE12EUNIT_STATES")
TL_FUNCTION(ieIsa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(ieIcon,"_ZN10CEquipment10createIconER7CGameUIb")
TL_FUNCTION(iePrice,"_ZN10CEquipment16recalculatePriceEv")
TL_FUNCTION(ieRemove,"_ZN12CEditorScene19RemoveObjectInSceneEP17CEditorBaseObject")
TL_FUNCTION(ieStop,"_ZN9CParticle4StopEb")
namespace {
template<class T>struct Raw{unsigned long long data[(sizeof(T)+7)/8];Raw(){std::memset(data,0,sizeof(data));}T*get(){return reinterpret_cast<T*>(data);}};
struct Case{unsigned n,flags,mode;};const Case*input;autotest::Capture*capture;
void number(int n){capture->add(&n,sizeof(n));}
struct World;World*world;
struct World{
 Raw<CEquipment>item;Raw<CCharacter>actor,master;Raw<CPlayer>players[2];Raw<CResourceManager>managers[2];Raw<CGameClient>clients[2];Raw<CParticle>particles[2];Raw<CPositionableObject>layout;unsigned long long inventories[3],uis[2],scenes[2];void*itemTable[112];void*layoutTable[64];
 World(){std::memset(itemTable,0,sizeof(itemTable));std::memset(layoutTable,0,sizeof(layoutTable));for(unsigned j=0;j<2;++j){new(&managers[j].get()->m_GameClients)TArrayList<CGameClient*>;managers[j].get()->m_GameClients.add(clients[j].get());clients[j].get()->m_pPlayer=players[j].get();clients[j].get()->m_pGameUI=reinterpret_cast<CGameUI*>(&uis[j]);}}
 ~World(){for(unsigned j=0;j<2;++j)managers[j].get()->m_GameClients.~TArrayList<CGameClient*>();}
 CInventory*inventory(unsigned j){return reinterpret_cast<CInventory*>(&inventories[j]);}
 CEditorScene*scene(unsigned j){return reinterpret_cast<CEditorScene*>(&scenes[j]);}
 int inventoryID(CInventory*p){for(unsigned j=0;j<3;++j)if(p==inventory(j))return j;return -1;}
};
void quest(CBaseUnit*p,EQUEST_EVENTS e,CCharacter*c,CBaseUnit*t){number(10);number(p==world->item.get());number(e);number(c==world->players[0].get()?0:c==world->players[1].get()?1:c?3:2);number(t==world->item.get());number(world->inventoryID(world->item.get()->m_pInventory));if(input->mode==1)world->item.get()->m_pResourceManager=world->managers[1].get();if(input->mode==2)world->item.get()->m_bGamblerIcon=true;}
void state(CBaseUnit*p,EUNIT_STATES s){number(11);number(p==world->item.get());number(s);if(input->mode==3)world->actor.get()->m_pMaster=world->master.get();}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){number(12);number(p==world->actor.get()?0:p==world->master.get()?1:2);number(t);if(input->mode==4)world->item.get()->m_pResourceManager=world->managers[1].get();return t==UNITTYPES::PLAYER&&(p==world->actor.get()?(input->flags&32)!=0:(input->flags&128)!=0);}
void icon(CEquipment*p,CGameUI&ui,bool b){number(13);number(p==world->item.get());number(&ui==reinterpret_cast<CGameUI*>(&world->uis[0])?0:1);number(b);number(world->inventoryID(p->m_pInventory));if(input->mode==5)p->m_pInventory=world->inventory(2);}
void price(CEquipment*p){number(14);number(p==world->item.get());number(world->inventoryID(p->m_pInventory));}
void parent(CEquipment*p,long long guid){number(15);number(p==world->item.get());capture->add(&guid,sizeof(guid));p->m_iParentGuid=guid;if(input->mode==6)world->actor.get()->m_pMaster=world->master.get();}
void event(CEquipment*p,unsigned e){number(16);number(p==world->item.get());number(e);number(p->m_bItemFlag1F2);if(input->mode==7){p->m_pSceneOwner=world->scene(1);p->m_pParticle_3D0=world->particles[1].get();}}
void remove(CEditorScene*s,CEditorBaseObject*p){number(17);number(s==world->scene(0)?0:1);number(p==world->item.get());number(world->item.get()->m_bItemFlag1F2);if(input->mode==8)world->item.get()->m_pParticle_3D0=world->particles[1].get();}
void stop(CParticle*p,bool immediate){number(18);number(p==world->particles[0].get()?0:1);number(immediate);}
void visible(CPositionableObject*p,bool b){number(19);number(p==world->layout.get());number(b);p->m_bVisible=b;}
void side(const Case&c,bool ours,autotest::Capture&out){input=&c;capture=&out;World w;world=&w;w.itemTable[0x18/8]=reinterpret_cast<void*>(&parent);w.itemTable[0x30/8]=reinterpret_cast<void*>(&event);w.layoutTable[0x50/8]=reinterpret_cast<void*>(&visible);*reinterpret_cast<void***>(w.item.get())=w.itemTable;*reinterpret_cast<void***>(w.layout.get())=w.layoutTable;
 CEquipment*p=w.item.get();p->m_pResourceManager=w.managers[0].get();p->m_pInventory=(c.flags&1)?w.inventory((c.flags&2)?1:0):NULL;p->m_bGamblerIcon=(c.flags&4)!=0;p->m_bUnknown430=true;p->m_pPositionableObject=(c.n%3)?w.layout.get():NULL;
 if(c.flags&8)w.clients[0].get()->m_pGameUI=NULL;if(c.flags&16)w.clients[0].get()->m_pPlayer=NULL;w.actor.get()->m_pMaster=(c.flags&64)?w.master.get():NULL;w.actor.get()->m_iGuid=0x123456789LL+c.n;p->m_pSceneOwner=(c.flags&256)?w.scene(0):NULL;p->m_pParticle_3D0=(c.flags&512)?w.particles[0].get():NULL;
 detour::Set patches;TL_REDIRECT(patches,ieQuest,&quest);TL_REDIRECT(patches,ieState,&state);TL_REDIRECT(patches,ieIsa,&isa);TL_REDIRECT(patches,ieIcon,&icon);TL_REDIRECT(patches,iePrice,&price);TL_REDIRECT(patches,ieRemove,&remove);TL_REDIRECT(patches,ieStop,&stop);if(patches.failed())_exit(42);
 for(unsigned repeat=0;repeat<2;++repeat){if(ours)p->CEquipment::addedToInventory(w.inventory(1),w.actor.get());else originalInventoryEntry(p,w.inventory(1),w.actor.get());number(w.inventoryID(p->m_pInventory));number(p->m_bItemFlag1F2);number(p->m_bUnknown430);capture->add(&p->m_iParentGuid,sizeof(p->m_iParentGuid));}
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_inventory_entry_differential){int failures=0;for(unsigned n=0;n<4096;++n){Case c={n,n%1024,0};if(n>=1024)c.mode=1+((n-1024)/384)%8;
 autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool ok=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;if(!ok)host->log("    inventory entry case %u status %d/%d sizes %lu/%lu\n",n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);TL_CHECK(failures,ok);if(!ok)return failures;}host->log("    inventory entry: 4096 cases, two calls per side\n");return failures;}
