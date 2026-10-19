#include <string>
#include <vector>
#include <map>
#include <new>
#include <limits>
#define private public
#define protected public
#include "Player.h"
#include "Level.h"
#include "LevelState.h"
#include "LevelTemplateData.h"
#include "LogicNodeState.h"
#include "TriggerSphere.h"
#include "TriggerBox.h"
#include "PropertyNode.h"
#include "RandomGroup.h"
#include "Timeline.h"
#include "Counter.h"
#include "LogicTimer.h"
#include "OutputIncrementor.h"
#include "Teleport.h"
#include "AnimationPlayer.h"
#include "PuzzleRandomizer.h"
#include "UnitSpawner.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldPlayerStore,(CPlayer*,CLevel&),"_ZN7CPlayer20storeLevelSavedStateER6CLevel")
extern "C" void newPlayerStore(CPlayer*,CLevel&) __asm__("_ZN7CPlayer20storeLevelSavedStateER6CLevel");
TL_FUNCTION(pst_tracking,"_ZN7CPlayer21updateDungeonTrackingESbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(pst_stored,"_ZN7CPlayer18updateStoredLevelsER6CLevel")
TL_FUNCTION(pst_formations,"_ZN11CLevelState13addFormationsEP10TArrayListIP14CFormationNodeER6CLevel")
TL_FUNCTION(pst_additem,"_ZN11CLevelState7addItemER5CItem")
TL_FUNCTION(pst_addchar,"_ZN11CLevelState12addCharacterER10CCharacterR6CLevel")
TL_FUNCTION(pst_automap,"_ZN11CLevelState10addAutomapEP8CAutomap")
TL_FUNCTION(pst_isa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(pst_quest,"_ZN9CBaseUnit14getIsQuestUnitEv")
TL_FUNCTION(pst_alive,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(pst_resources,"_ZN16CSceneNodeObject18setResourceManagerEP16CResourceManager")
TL_FUNCTION(pst_editor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(pst_bbox,"_ZN13CPropertyNode17updateBoundingBoxEv")
TL_FUNCTION(pst_hash,"_ZN17CEditorBaseObject32calculateParentHierarchyHashCodeEv")
TL_FUNCTION(pst_objects,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEEP10TArrayListIP17CEditorBaseObjectE")
namespace {
void initNativeStrings(){
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x145dd00),8);if(!p)new(reinterpret_cast<void*>(0x145dd00))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x145dd08),8);if(!p)new(reinterpret_cast<void*>(0x145dd08))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1471fe0),8);if(!p)new(reinterpret_cast<void*>(0x1471fe0))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1471fe8),8);if(!p)new(reinterpret_cast<void*>(0x1471fe8))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1479460),8);if(!p)new(reinterpret_cast<void*>(0x1479460))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1479468),8);if(!p)new(reinterpret_cast<void*>(0x1479468))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x147c348),8);if(!p)new(reinterpret_cast<void*>(0x147c348))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x147c340),8);if(!p)new(reinterpret_cast<void*>(0x147c340))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1484120),8);if(!p)new(reinterpret_cast<void*>(0x1484120))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1484128),8);if(!p)new(reinterpret_cast<void*>(0x1484128))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x148a300),8);if(!p)new(reinterpret_cast<void*>(0x148a300))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x148a308),8);if(!p)new(reinterpret_cast<void*>(0x148a308))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14949c8),8);if(!p)new(reinterpret_cast<void*>(0x14949c8))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14949c0),8);if(!p)new(reinterpret_cast<void*>(0x14949c0))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1495f80),8);if(!p)new(reinterpret_cast<void*>(0x1495f80))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1495f88),8);if(!p)new(reinterpret_cast<void*>(0x1495f88))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1497a20),8);if(!p)new(reinterpret_cast<void*>(0x1497a20))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1497a28),8);if(!p)new(reinterpret_cast<void*>(0x1497a28))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1497ea0),8);if(!p)new(reinterpret_cast<void*>(0x1497ea0))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1497ea8),8);if(!p)new(reinterpret_cast<void*>(0x1497ea8))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14995c0),8);if(!p)new(reinterpret_cast<void*>(0x14995c0))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14995c8),8);if(!p)new(reinterpret_cast<void*>(0x14995c8))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1499a40),8);if(!p)new(reinterpret_cast<void*>(0x1499a40))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1499a48),8);if(!p)new(reinterpret_cast<void*>(0x1499a48))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x149b0e0),8);if(!p)new(reinterpret_cast<void*>(0x149b0e0))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x149b0e8),8);if(!p)new(reinterpret_cast<void*>(0x149b0e8))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x149c700),8);if(!p)new(reinterpret_cast<void*>(0x149c700))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x149c708),8);if(!p)new(reinterpret_cast<void*>(0x149c708))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x149d920),8);if(!p)new(reinterpret_cast<void*>(0x149d920))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x149d928),8);if(!p)new(reinterpret_cast<void*>(0x149d928))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14a7080),8);if(!p)new(reinterpret_cast<void*>(0x14a7080))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14a7088),8);if(!p)new(reinterpret_cast<void*>(0x14a7088))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14a72a0),8);if(!p)new(reinterpret_cast<void*>(0x14a72a0))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14a72a8),8);if(!p)new(reinterpret_cast<void*>(0x14a72a8))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14a8a28),8);if(!p)new(reinterpret_cast<void*>(0x14a8a28))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14a8a20),8);if(!p)new(reinterpret_cast<void*>(0x14a8a20))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14aafa0),8);if(!p)new(reinterpret_cast<void*>(0x14aafa0))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14aafa8),8);if(!p)new(reinterpret_cast<void*>(0x14aafa8))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14ab1a0),8);if(!p)new(reinterpret_cast<void*>(0x14ab1a0))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14ab1a8),8);if(!p)new(reinterpret_cast<void*>(0x14ab1a8))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14abce8),8);if(!p)new(reinterpret_cast<void*>(0x14abce8))std::wstring;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14abce0),8);if(!p)new(reinterpret_cast<void*>(0x14abce0))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1516200),8);if(!p)new(reinterpret_cast<void*>(0x1516200))std::string;}
{void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x1516208),8);if(!p)new(reinterpret_cast<void*>(0x1516208))std::wstring;}
for(unsigned i=0;i<7;++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14abf40+i*8),8);if(!p)new(reinterpret_cast<void*>(0x14abf40+i*8))std::wstring(L"native spawn category");}
}
struct Case{unsigned index;};
struct State{Case c;autotest::Capture*out;bool observing;CPlayer*self;CLevel*level;CResourceManager*resources;CItem*items[5];CCharacter*characters[7];CEditorBaseObject*objects[13];CEditorScene*scenes[3];};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){if(active->observing)active->out->add(&n,4);}void fp(float n){if(active->observing)active->out->add(&n,4);}void ll(long long n){if(active->observing)active->out->add(&n,8);}void wide(const std::wstring&s){num(s.size());if(active->observing)active->out->add(s.data(),s.size()*4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}
unsigned itemId(CBaseUnit*p){for(unsigned i=0;i<5;++i)if(active->items[i]==p)return i;return 99;}unsigned charId(CCharacter*p){for(unsigned i=0;i<7;++i)if(active->characters[i]==p)return i;return 99;}unsigned objId(CEditorBaseObject*p){for(unsigned i=0;i<13;++i)if(active->objects[i]==p)return i;return 99;}
const wchar_t*descriptors[]={L"Player Sphere Trigger",L"Player Box Trigger",L"Property Node",L"Group",L"Timeline",L"Counter",L"Timer",L"Output Incrementor",L"Teleport",L"Animation Controller",L"Puzzle Input",L"Unit Spawner"};
void tracking(CPlayer*p,std::wstring name,int depth){num(1);num(p==active->self);wide(name);num(depth);}
void stored(CPlayer*p,CLevel&l){num(2);num(p==active->self);num(&l==active->level);}
void formations(CLevelState*,TArrayList<CFormationNode*>*p,CLevel&l){num(3);num(p==&active->level->m_formations);num(&l==active->level);}
void addItem(CLevelState*,CItem&i){num(4);num(itemId(&i));}
void addCharacter(CLevelState*,CCharacter&c,CLevel&l){num(5);num(charId(&c));num(&l==active->level);}
void automap(CLevelState*,CAutomap*p){num(6);num(p==active->level->m_automap);}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){num(7);num(itemId(p));num(type);return (hash(30+itemId(p))&1)!=0;}
bool quest(CBaseUnit*p){num(8);num(itemId(p));return hash(40+itemId(p))%3==0;}
bool alive(CCharacter*p){num(9);num(charId(p));return hash(50+charId(p))%4!=0;}
void resources(CSceneNodeObject*p,CResourceManager*r){p->m_pResourceManager=r;}
bool editor(CResourceManager*){return false;}
void bbox(CPropertyNode*){}
void hierarchyHash(CEditorBaseObject*p){num(10);num(objId(p));p->m_iParentHierarchyHashCode=(static_cast<long long>(objId(p))+1)*0x100000007LL;}
void objects(CEditorScene*s,const std::wstring&name,TArrayList<CEditorBaseObject*>*list){num(11);unsigned room=0;while(room<3&&active->scenes[room]!=s)++room;num(room);wide(name);num(list->m_nGrowBy);unsigned family=0;while(family<12&&name!=descriptors[family])++family;if(family==12){active->out->issue=autotest::Capture::InvalidReport;return;}unsigned count=hash(60+family*3+room)%5;for(unsigned i=0;i<count;++i)list->add(i==1?NULL:i==2?active->objects[12]:active->objects[family]);}
class Item:public CItem{public:Item():CItem(NULL){}virtual void setActiveInLevel(bool){}virtual void*getUnitModel(){return NULL;}virtual void*getUnitCollisionModel(){return NULL;}};
float scalar(unsigned n){const float values[]={-1,0,1,.25f,3.5f,-7.25f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};return values[hash(n)%8];}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;std::memset(&s,0,sizeof s);active=&s;s.c=c;s.out=&out;initNativeStrings();s.self=static_cast<CPlayer*>(autotest::allocate(sizeof(CPlayer)));s.resources=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));s.level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));CPlayer&p=*s.self;CLevel&l=*s.level;CLevelTemplateData*t=static_cast<CLevelTemplateData*>(autotest::allocate(sizeof(CLevelTemplateData)));l.m_pLevelTemplateData=t;t->m_isTown=hash(1)&1;t->m_dontStore=hash(2)%3==0;s.resources->m_pLevel=&l;p.m_pResourceManager=s.resources;new(&p.m_savedLevels)std::vector<CLevelState*>;new(&l.m_sDungeonName)std::wstring(hash(3)&1?L"Dungeon Ж":L"");l.m_iLevelDepth=int(hash(4)%9)-3;p.m_levelSaveSerial=int(hash(5)%13)-6;p.m_journalStats[2]=int(hash(6)%21)-10;p.m_playTime=scalar(7);new(&l.m_chunks)std::vector<CChunk*>;new(&l.m_RoomScenes)TArrayList<CEditorScene*>(2);new(&l.m_formations)TArrayList<CFormationNode*>(10);
for(unsigned i=0;i<hash(8)%4;++i){CLevelState*v=new CLevelState(i==1?l.m_iLevelDepth:l.m_iLevelDepth+1);v->m_sLevelName=i==1?l.m_sDungeonName:L"different";v->m_iStateVersion=scalar(90+i);p.m_savedLevels.push_back(v);}
for(unsigned i=0;i<hash(9)%4;++i){CChunk*v=static_cast<CChunk*>(autotest::allocate(sizeof(CChunk)));new(&v->m_filename)std::wstring(i%2?L"room/chunk.layout":L"");l.m_chunks.push_back(v);}
for(unsigned i=0;i<3;++i){s.scenes[i]=static_cast<CEditorScene*>(autotest::allocate(sizeof(CEditorScene)));if(i<hash(10)%4)l.m_RoomScenes.add(s.scenes[i]);}l.m_automap=hash(11)&1?static_cast<CAutomap*>(autotest::allocate(0x100)):NULL;
TLinkedList<CItem*> itemList;itemList.m_pHead=NULL;TLinkedListNode<CItem*>itemNodes[5];for(int i=4;i>=0;--i){s.items[i]=new Item;s.items[i]->m_bItemFlag218=hash(100+i)&1;s.items[i]->m_bBaseUnitFlag190=hash(110+i)%3==0;itemNodes[i].m_Data=s.items[i];itemNodes[i].m_pNext=itemList.m_pHead;itemList.m_pHead=&itemNodes[i];}l.m_items=&itemList;
TLinkedList<CCharacter*>charList;charList.m_pHead=NULL;TLinkedListNode<CCharacter*>charNodes[7];for(int i=6;i>=0;--i){CCharacter*v=i==0?static_cast<CCharacter*>(&p):new CCharacter(NULL);s.characters[i]=v;unsigned master=hash(120+i)%3;v->m_pMaster=master==0?NULL:master==1?&p:s.characters[6];v->m_bBaseUnitFlag190=hash(130+i)%3==0;charNodes[i].m_Data=v;charNodes[i].m_pNext=charList.m_pHead;charList.m_pHead=&charNodes[i];}l.m_pCharacters=&charList;
s.objects[0]=new CTriggerSphere(NULL);s.objects[1]=new CTriggerBox(NULL);s.objects[2]=new CPropertyNode(s.resources);s.objects[3]=new CRandomGroup(NULL);s.objects[4]=new CTimeline;s.objects[5]=new CCounter;s.objects[6]=new CLogicTimer(NULL);s.objects[7]=new COutputIncrementor(NULL);s.objects[8]=new CTeleport(NULL);s.objects[9]=new CAnimationPlayer(NULL);s.objects[10]=new CPuzzleRandomizer(NULL);s.objects[11]=new CUnitSpawner(NULL);s.objects[12]=new CEditorBaseObject;
CPositionableObject*parent=static_cast<CTeleport*>(s.objects[8]);for(unsigned i=0;i<13;++i){CEditorBaseObject*v=s.objects[i];v->m_iGuid=100+i;v->m_iOriginalGuid=0x100000100LL+i;v->m_iParentHierarchyHashCode=hash(140+i)&1?0:0x123450001LL+i;v->m_pParentPositionableObject=hash(160+i)&1?parent:NULL;CPositionableObject*pos=dynamic_cast<CPositionableObject*>(v);if(pos){pos->m_vPosition=Ogre::Vector3(float(i),-float(i),float(i)+.5f);pos->m_bEnabled=hash(180+i)&1;pos->m_bVisible=hash(200+i)&1;}}
for(unsigned i=0;i<2;++i){CLogicTrigger*v=static_cast<CLogicTrigger*>(s.objects[i]);v->m_bActive=hash(220+i)&1;v->m_bHasActivated=hash(230+i)&1;v->m_bHasDeactivated=hash(240+i)&1;v->m_bTriggerEnabled=hash(250+i)&1;}
CTimeline*timeline=static_cast<CTimeline*>(s.objects[4]);timeline->m_fSetTimelineDuration=scalar(260);timeline->m_fTimelinePosition=scalar(261);timeline->m_bEnabled=hash(262)&1;timeline->m_bIsPlayingBackwards=hash(263)&1;timeline->m_bTimelineWasStopped=hash(264)&1;
CCounter*counter=static_cast<CCounter*>(s.objects[5]);counter->m_iValue=int(hash(270));counter->m_bEnabled=hash(271)&1;
CLogicTimer*timer=static_cast<CLogicTimer*>(s.objects[6]);timer->m_fMinTime=scalar(280);timer->m_fTimeRemaining=scalar(281);timer->m_iRepeatsLeft=int(hash(282));timer->m_bEnabled=hash(283)&1;
COutputIncrementor*increment=static_cast<COutputIncrementor*>(s.objects[7]);increment->m_iCount=hash(290);increment->m_iRepeatsLeft=int(hash(291));increment->m_bEnabled=hash(292)&1;
CAnimationPlayer*animation=static_cast<CAnimationPlayer*>(s.objects[9]);animation->m_bAnimationPlaying=hash(300)&1;animation->m_bLoop=hash(301)&1;animation->m_fForceDuration=scalar(302);
CPuzzleRandomizer*puzzle=static_cast<CPuzzleRandomizer*>(s.objects[10]);puzzle->m_bEnabled=hash(310)&1;
CUnitSpawner*spawner=static_cast<CUnitSpawner*>(s.objects[11]);spawner->m_spawning=hash(320)&1;spawner->m_reset18c=int(hash(321));spawner->m_reset188=int(hash(322));
typedef void(*F)(CPlayer*,CLevel&);F f=ours?newPlayerStore:oldPlayerStore;if(!autotest::beginInvocation(out,f))return;s.observing=true;f(&p,l);f(&p,l);out.callCompleted=1;num(p.m_levelSaveSerial);num(p.m_journalStats[2]);num(p.m_savedLevels.size());for(unsigned i=0;i<p.m_savedLevels.size();++i){CLevelState*v=p.m_savedLevels[i];num(v->m_iLevelId);wide(v->m_sLevelName);fp(v->m_iStateVersion);num(v->m_bUnknownB0);num(v->m_bUnknownB1);num(v->m_lLevelStrings.size());for(unsigned j=0;j<v->m_lLevelStrings.size();++j)wide(v->m_lLevelStrings[j]);num(v->m_lLogicStates.size());for(unsigned j=0;j<v->m_lLogicStates.size();++j){CLogicNodeState*n=v->m_lLogicStates[j];out.add(&n->m_bActive,5);out.add(&n->m_nStateVersion,16);wide(n->m_wstrName);num(n->m_nCurrentState);ll(n->m_parentGuid);ll(n->m_parentHierarchyHash);ll(n->m_guid);vec(n->m_position);}}
// Complete real saved-state and logic-node lifetimes after the observed operation.
s.observing=false;for(unsigned i=0;i<p.m_savedLevels.size();++i)delete p.m_savedLevels[i];p.m_savedLevels.~vector();for(unsigned i=0;i<l.m_chunks.size();++i)l.m_chunks[i]->m_filename.~basic_string();l.m_chunks.~vector();l.m_RoomScenes.~TArrayList();l.m_formations.~TArrayList();l.m_sDungeonName.~basic_string();}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(all_player_store_level){detour::Set h;TL_REDIRECT(h,pst_tracking,&tracking);TL_REDIRECT(h,pst_stored,&stored);TL_REDIRECT(h,pst_formations,&formations);TL_REDIRECT(h,pst_additem,&addItem);TL_REDIRECT(h,pst_addchar,&addCharacter);TL_REDIRECT(h,pst_automap,&automap);TL_REDIRECT(h,pst_isa,&isa);TL_REDIRECT(h,pst_quest,&quest);TL_REDIRECT(h,pst_alive,&alive);TL_REDIRECT(h,pst_resources,&resources);TL_REDIRECT(h,pst_editor,&editor);TL_REDIRECT(h,pst_bbox,&bbox);TL_REDIRECT(h,pst_hash,&hierarchyHash);TL_REDIRECT(h,pst_objects,&objects);if(h.failed())return 1;autotest::Coverage coverage("all_player_store_level",0x8f6080);for(unsigned i=0;i<2048;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    player store seed%u status%d/%d bytes%lu/%lu start%u/%u done%u/%u\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length,a.capture.callStarted,b.capture.callStarted,a.capture.callCompleted,b.capture.callCompleted);for(unsigned k=0;k<a.capture.length&&k<b.capture.length;++k)if(a.capture.data[k]!=b.capture.data[k]){host->log("    first byte%u %02x/%02x\n",k,(unsigned char)a.capture.data[k],(unsigned char)b.capture.data[k]);break;}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=2048||coverage.different||coverage.missing;}
