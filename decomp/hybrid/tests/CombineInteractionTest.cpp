#include <cstring>
#include <cstdio>
#include <string>
#define protected public
#define private public
#include "CombineMenu.h"
#include "Equipment.h"
#include "Recipes.h"
#include "SpawnClass.h"
#include "UnitResourceList.h"
#include "SoundBank.h"
#include "Level.h"
#include "Inventory.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalInteraction,(CCombineMenu*),"_ZN12CCombineMenu18performInteractionEv")
extern "C" void candidateInteraction(CCombineMenu*) __asm__("_ZN12CCombineMenu18performInteractionEv");
TL_FUNCTION(recipesFn,"_ZN8CRecipes12getSingletonEv")
TL_FUNCTION(slotFn,"_ZN10CInventory18getEquipmentInSlotEj")
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(masterFn,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(groupFn,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(guidFn,"_ZN16CResourceManager22getUnitGuidByDataGroupEP10CDataGroupRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(removeFn,"_ZN10CInventory15removeEquipmentEP10CEquipment")
TL_FUNCTION(updatedFn,"_ZN12CCombineMenu17itemUpdatedInMenuEP10CEquipmentb")
TL_FUNCTION(soundFn,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(voiceFn,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(pickupFn,"_ZN10CInventory15pickupEquipmentEP10CEquipmentb")
TL_FUNCTION(pickupAtFn,"_ZN10CInventory15pickupEquipmentEP10CEquipmentib")
TL_FUNCTION(positionFn,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(addFn,"_ZN6CLevel7addItemEP5CItemRKN4Ogre7Vector3Eb")
TL_FUNCTION(spawnFn,"_ZN16CResourceManager19getSpawnClassByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(rollFn,"_ZN11CSpawnClass14rollSpawnClassER10TArrayListIP10CDataGroupEPS0_IbEP10CCharacterS8_ijiiii")
TL_FUNCTION(createFn,"_ZN16CResourceManager15createEquipmentEPKwbb")
TL_FUNCTION(enchantFn,"_ZN10CEquipment7enchantEb")
TL_FUNCTION(dataFn,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(statFn,"_ZN10CCharacter25incrementJournalStatisticE17EJournalStatistici")
namespace {
typedef std::map<CEquipment*,std::pair<CInventory*,EEQUIP_LOCATIONS> > Locations;
struct Stop {};
struct Case {unsigned mode,profile;bool change;unsigned fault;};
struct Ingredient {int type;int pad;std::wstring name;int count;};
struct Output {std::wstring spawn,item;};
struct Recipe {char prefix[8];TArrayList<Ingredient*> inputs;TArrayList<Output*> outputs;};
const Case* cs;autotest::Capture* cap;CCombineMenu* menu;CCharacter* actors[2];CInventory* invs[2];CResourceManager* resources[2];CRecipes* allRecipes[2];CUnitResourceList* master;CSpawnClass* spawn;CLevel* level;CSoundBank* bank;CSoundBank* voiceBank;
unsigned long long equipment[20][(sizeof(CEquipment)+7)/8],dataGroups[32][32];void* itemVtable[120];CEquipment* slots[2][16];int kinds[20],deleted[20],enchants[20];bool magic[20],excluded54[20],excluded55[20];unsigned events,singletons,gets,guids,created,witness;std::wstring itemNames[32];
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
CEquipment* item(unsigned i){return reinterpret_cast<CEquipment*>(equipment[i]);}CDataGroup* data(unsigned i){return reinterpret_cast<CDataGroup*>(dataGroups[i]);}
int iid(const void* p){for(unsigned i=0;i<20;++i)if(p==item(i))return i;return p?999:-1;}int did(const void* p){for(unsigned i=0;i<32;++i)if(p==data(i))return i;return p?999:-1;}int aid(const void* p){return p==actors[0]?0:p==actors[1]?1:p?999:-1;}int vid(const void* p){return p==invs[0]?0:p==invs[1]?1:p?999:-1;}int rid(const void* p){return p==resources[0]?0:p==resources[1]?1:p?999:-1;}
void num(int n){cap->add(&n,4);}void wide(const std::wstring& s){num(s.size());cap->add(s.data(),s.size()*4);}void event(int n){num(n);++events;if(cs->fault==events)throw Stop();}
CRecipes* recipes(){event(1);return allRecipes[cs->change&&singletons++?1:0];}
CEquipment* slot(CInventory* v,unsigned s){event(2);int n=vid(v);num(n);num(s);if(n>1||s>=16)_exit(71);CEquipment* p=slots[n][s];if(cs->change&&++gets%3==0)menu->m_pCharacter=actors[gets%2];return p;}
bool isa(CBaseUnit* p,UNITTYPES::EUNITTYPES t){event(3);int i=iid(p);num(i);num(t);if(i<0||i>=20)_exit(72);if(t==54)return excluded54[i];if(t==55)return excluded55[i];return kinds[i]==int(t);}
bool magical(CEquipment* p){event(4);int i=iid(p);num(i);witness|=4;return magic[i];}
CUnitResourceList* masterList(CResourceManager* p){event(5);num(rid(p));return master;}
CDataGroup* group(CUnitResourceList* p,const std::wstring& category,const std::wstring& name){event(6);num(p==master);wide(category);wide(name);witness|=8;return cs->mode==11?0:data(0);}
long long guid(CResourceManager* p,CDataGroup* d,const std::wstring& key){event(7);num(rid(p));num(did(d));wide(key);++guids;if(cs->change&&guids%2)menu->m_pResourceManager=resources[guids%2];return 0x100000005LL+(cs->mode==12?did(d):0);}
void increment(CEquipment* p,int delta){event(8);int i=iid(p);num(i);num(delta);witness|=16;p->m_iUnknown238=static_cast<int>(static_cast<unsigned>(p->m_iUnknown238)+static_cast<unsigned>(delta));if(cs->mode==25)p->m_iUnknown238=0;}
long long remove(CInventory* p,CEquipment* e){event(9);int n=vid(p);num(n);num(iid(e));if(n>1)_exit(73);for(unsigned i=0;i<16;++i)if(slots[n][i]==e){slots[n][i]=0;break;}return 7;}
void updated(CCombineMenu* p,CEquipment* e,bool b){event(10);num(p==menu);num(iid(e));num(b);}
void destroy(CEquipment* p){event(11);int i=iid(p);num(i);witness|=32;if(i<0||i>=20)_exit(74);++deleted[i];}
void sound(CSoundBank* b,int sample,Ogre::SceneNode* node,float a,float c,bool flag){event(12);num(b==bank);num(sample);num(node==reinterpret_cast<Ogre::SceneNode*>(0x1230)?0:node==reinterpret_cast<Ogre::SceneNode*>(0x1240)?1:999);cap->add(&a,4);cap->add(&c,4);num(flag);witness|=sample==24?1:sample==36?2:0;if(cs->change&&cs->profile==3)menu->m_pCharacter=actors[1];}
void voice(CSoundBank* b,int sample,float a,float c){event(13);num(b==voiceBank);num(sample);cap->add(&a,4);cap->add(&c,4);}
CEquipment* pickup(CInventory* p,CEquipment* e,bool b){event(14);num(vid(p));num(iid(e));num(b);witness|=64;return cs->mode==26?0:e;}
CEquipment* pickupAt(CInventory* p,CEquipment* e,int s,bool b){event(15);int n=vid(p);num(n);num(iid(e));num(s);num(b);if(n>1||s<0||s>=16)_exit(75);slots[n][s]=e;return e;}
Ogre::Vector3 position(CPositionableObject* p,bool b){event(16);num(aid(p));num(b);return Ogre::Vector3(12,-3,7);}
void add(CLevel* p,CItem* e,const Ogre::Vector3& v,bool b){event(17);num(p==level);num(iid(e));cap->add(&v,sizeof(v));num(b);}
void drop(CEquipment* p){event(18);num(iid(p));witness|=128;}
CSpawnClass* getSpawn(CResourceManager* p,const std::wstring& s){event(19);num(rid(p));wide(s);witness|=512;if(cs->mode==18){witness|=4096;return 0;}return spawn;}
int roll(CSpawnClass* p,TArrayList<CDataGroup*>& groups,TArrayList<bool>* flags,CCharacter* a,CCharacter* b,int lvl,unsigned q,int x,int y,int z,int w){event(20);num(p==spawn);num(aid(a));num(aid(b));num(lvl);num(q);num(x);num(y);num(z);num(w);num(groups.m_nGrowBy);num(flags->m_nGrowBy);unsigned n=cs->mode==19?0:cs->mode==21?6:3;for(unsigned i=0;i<n;++i){groups.add(data(16+i));flags->add(i%2==0);}if(cs->mode==22&&n){groups.m_nCapacity=1;flags->m_nCapacity=1;}if(cs->change)menu->m_pCharacter=actors[1];return 123;}
CEquipment* create(CResourceManager* p,const wchar_t* name,bool a,bool b){event(21);num(rid(p));wide(std::wstring(name));num(a);num(b);witness|=256;unsigned i=8+created++;if(i>=20)_exit(76);return cs->mode==17?0:item(i);}
void enchant(CEquipment* p,bool b){event(22);int i=iid(p);num(i);num(b);witness|=1024;if(i<0||i>=20)_exit(77);++enchants[i];}
const std::wstring& value(CDataGroup* p,const std::wstring& k,const std::wstring& def){event(23);int i=did(p);num(i);wide(k);wide(def);if(cs->change)menu->m_pResourceManager=resources[i%2];return itemNames[i];}
void statistic(CCharacter* p,EJournalStatistic stat,int amount){event(24);num(aid(p));num(stat);num(amount);witness|=2048;}
void canonical(unsigned char* s,unsigned off,int n){uintptr_t v=n;std::memcpy(s+off,&v,8);}
void side(const Case& c,bool ours,autotest::Capture& out){
 cs=&c;cap=&out;events=singletons=gets=guids=created=witness=0;std::memset(equipment,0,sizeof(equipment));std::memset(deleted,0,sizeof(deleted));std::memset(enchants,0,sizeof(enchants));std::memset(slots,0,sizeof(slots));
 unsigned long long menuMem[(sizeof(CCombineMenu)+7)/8],actorMem[2][0x1800/8]={{0}},invMem[2][64]={{0}},resourceMem[2][64]={{0}},recipesMem[2][16]={{0}},recipeMem[16][8]={{0}},masterMem[64]={0},spawnMem[64]={0},levelMem[64]={0},bankMem[64]={0},voiceMem[64]={0};
 std::memset(menuMem,0x5a,sizeof(menuMem));menu=(CCombineMenu*)menuMem;new(&menu->m_OriginalItemLocations) Locations;g_bDontTrackItemEquipAndUnEquip=c.profile&1;master=(CUnitResourceList*)masterMem;spawn=(CSpawnClass*)spawnMem;level=(CLevel*)levelMem;bank=(CSoundBank*)bankMem;voiceBank=(CSoundBank*)voiceMem;
 Ingredient ingredients[16][4];Ingredient* ingredientPtrs[16][4];Output outputs[16];Output* outputPtrs[16][1];CRecipe* recipePtrs[16];
 for(unsigned i=0;i<2;++i){actors[i]=(CCharacter*)actorMem[i];invs[i]=(CInventory*)invMem[i];resources[i]=(CResourceManager*)resourceMem[i];allRecipes[i]=(CRecipes*)recipesMem[i];at<CInventory*>(actors[i],0x490)=invs[i];at<int>(actors[i],0x100)=11+i;at<CSoundBank*>(actors[i],0x298)=c.profile%2?0:voiceBank;at<Ogre::SceneNode*>(actors[i],0x58)=reinterpret_cast<Ogre::SceneNode*>(0x1230+i*16);at<CResourceManager*>(actors[i],0x68)=resources[i];at<CLevel*>(resources[i],0x18)=level;new(&allRecipes[i]->m_recipes)TArrayList<CRecipe*>;allRecipes[i]->m_recipes.m_pData=recipePtrs;allRecipes[i]->m_recipes.m_nCount=1;allRecipes[i]->m_recipes.m_nCapacity=16;}
 menu->m_pCharacter=actors[0];menu->m_pResourceManager=resources[0];menu->m_pSoundBank=bank;
 for(unsigned i=0;i<4;++i)menu->m_aiSlotData[i]=4+i;
 for(unsigned i=0;i<16;++i){Recipe* r=(Recipe*)recipeMem[i];new(&r->inputs)TArrayList<Ingredient*>;new(&r->outputs)TArrayList<Output*>;recipePtrs[i]=(CRecipe*)r;r->inputs.m_pData=ingredientPtrs[i];r->inputs.m_nCount=1;r->inputs.m_nCapacity=4;r->outputs.m_pData=outputPtrs[i];r->outputs.m_nCount=1;r->outputs.m_nCapacity=1;outputPtrs[i][0]=&outputs[i];char buf[32];std::sprintf(buf,"result%u",i);outputs[i].spawn=L"";outputs[i].item=std::wstring(buf,buf+std::strlen(buf));for(unsigned j=0;j<4;++j){ingredientPtrs[i][j]=&ingredients[i][j];ingredients[i][j].type=1;ingredients[i][j].count=1;ingredients[i][j].name=L"required item";}}
 std::memset(itemVtable,0,sizeof(itemVtable));itemVtable[1]=(void*)&destroy;itemVtable[0x2b0/8]=(void*)&magical;itemVtable[0x338/8]=(void*)&increment;itemVtable[0x360/8]=(void*)&drop;
 for(unsigned i=0;i<20;++i){*(void***)item(i)=itemVtable;item(i)->m_iUnknown238=1;item(i)->m_pDataGroup=data(i);kinds[i]=1;magic[i]=excluded54[i]=excluded55[i]=false;}
 for(unsigned i=0;i<20;++i)if((i+c.profile)%3)menu->m_OriginalItemLocations[item(i)]=std::make_pair(invs[i%2],static_cast<EEQUIP_LOCATIONS>(int(i)-1));
 for(unsigned i=0;i<32;++i){itemNames[i]=c.profile==1?std::wstring(64,L'x'):c.profile==2?std::wstring(L"unit\0tail",9):std::wstring(L"unit_Ω中");}
 for(unsigned a=0;a<2;++a)for(unsigned i=0;i<4;++i)slots[a][4+i]=item(i);
 Recipe* r0=(Recipe*)recipePtrs[0];
 if(c.mode==0)allRecipes[0]->m_recipes.m_nCount=allRecipes[1]->m_recipes.m_nCount=0;
 if(c.mode==1)allRecipes[0]->m_recipes.m_nCount=allRecipes[1]->m_recipes.m_nCount=0x80000000u;
 if(c.mode==2){r0->inputs.m_nCount=0;r0->outputs.m_nCount=0;}
 if(c.mode==3)ingredients[0][0].type=99;
 if(c.mode==5||c.mode==25){ingredients[0][0].count=2;item(0)->m_iUnknown238=5;}
 if(c.mode==6)ingredients[0][0].count=2;
 if(c.mode>=7&&c.mode<=9){ingredients[0][0].type=135;for(unsigned i=0;i<4;++i){magic[i]=c.mode!=8;kinds[i]=c.mode==8?135:1;excluded54[i]=c.mode==9&&i%2==0;excluded55[i]=c.mode==9&&i%2!=0;}}
 if(c.mode>=10&&c.mode<=12)ingredients[0][0].type=22;
 if(c.mode==13||c.mode==14){ingredients[0][0].count=c.mode==13?0:-1;std::memset(slots,0,sizeof(slots));}
 if(c.mode==15){allRecipes[0]->m_recipes.m_nCount=allRecipes[1]->m_recipes.m_nCount=2;ingredients[0][0].count=8;((Recipe*)recipePtrs[1])->inputs.m_nCount=2;ingredients[1][0].count=3;ingredients[1][1].count=1;item(0)->m_iUnknown238=12;}
 if(c.mode==16){allRecipes[0]->m_recipes.m_nCount=allRecipes[1]->m_recipes.m_nCount=12;for(unsigned i=0;i<12;++i){ingredients[i][0].count=0;((Recipe*)recipePtrs[i])->outputs.m_nCount=0;}}
 if(c.mode>=18&&c.mode<=22)outputs[0].spawn=L"SPAWN_CLASS";
 if(c.mode==23){for(unsigned i=0;i<2;++i){allRecipes[i]->m_recipes.m_nCount=3;allRecipes[i]->m_recipes.m_nCapacity=1;}}
 if(c.mode==24){r0->inputs.m_nCount=3;r0->inputs.m_nCapacity=1;item(0)->m_iUnknown238=6;}
 if(c.mode==27){item(0)->m_iUnknown238=0;ingredients[0][0].count=0;}
 if(c.mode==28){item(0)->m_iUnknown238=-2;ingredients[0][0].count=0;}
 if(c.mode==29){ingredients[0][0].count=2147483647;item(0)->m_iUnknown238=2147483647;}
 if(c.mode==30)r0->outputs.m_nCount=0;
 if(c.mode==31){r0->inputs.m_nCount=0;outputs[0].item=std::wstring(L"direct\0tail",11);}
 detour::Set d;TL_REDIRECT(d,recipesFn,&recipes);TL_REDIRECT(d,slotFn,&slot);TL_REDIRECT(d,isaFn,&isa);TL_REDIRECT(d,masterFn,&masterList);TL_REDIRECT(d,groupFn,&group);TL_REDIRECT(d,guidFn,&guid);TL_REDIRECT(d,removeFn,&remove);TL_REDIRECT(d,soundFn,&sound);TL_REDIRECT(d,voiceFn,&voice);TL_REDIRECT(d,pickupFn,&pickup);TL_REDIRECT(d,pickupAtFn,&pickupAt);TL_REDIRECT(d,positionFn,&position);TL_REDIRECT(d,addFn,&add);TL_REDIRECT(d,spawnFn,&getSpawn);TL_REDIRECT(d,rollFn,&roll);TL_REDIRECT(d,createFn,&create);TL_REDIRECT(d,enchantFn,&enchant);TL_REDIRECT(d,dataFn,&value);TL_REDIRECT(d,statFn,&statistic);if(d.failed())_exit(78);
 bool threw=false;try{if(ours)autotest::invoke(out,&candidateInteraction,menu);else autotest::invoke(out,&originalInteraction,menu);}catch(const Stop&){threw=true;}catch(...){_exit(79);}num(threw);num(events);num(created);num(singletons);num(gets);num(guids);
 unsigned char snapshot[sizeof(CCombineMenu)];std::memcpy(snapshot,menu,sizeof(snapshot));std::memset(snapshot+0x18,0,sizeof(Locations));num(menu->m_OriginalItemLocations.size());for(unsigned i=0;i<20;++i){Locations::iterator it=menu->m_OriginalItemLocations.find(item(i));num(it!=menu->m_OriginalItemLocations.end());if(it!=menu->m_OriginalItemLocations.end()){num(vid(it->second.first));num(int(it->second.second));}}canonical(snapshot,0x90,aid(menu->m_pCharacter));canonical(snapshot,0xd0,rid(menu->m_pResourceManager));canonical(snapshot,0xe0,menu->m_pSoundBank==bank);cap->add(snapshot,sizeof(snapshot));for(unsigned i=0;i<20;++i){num(item(i)->m_iUnknown238);num(deleted[i]);num(enchants[i]);}for(unsigned a=0;a<2;++a)for(unsigned i=0;i<16;++i)num(iid(slots[a][i]));cap->add(equipment,sizeof(equipment));cap->add(actorMem,sizeof(actorMem));cap->add(invMem,sizeof(invMem));cap->add(resourceMem,sizeof(resourceMem));cap->add(recipeMem,sizeof(recipeMem));cap->add(dataGroups,sizeof(dataGroups));for(unsigned i=0;i<16;++i){wide(outputs[i].spawn);wide(outputs[i].item);for(unsigned j=0;j<4;++j){num(ingredients[i][j].type);num(ingredients[i][j].count);wide(ingredients[i][j].name);}}num(witness);menu->m_OriginalItemLocations.~Locations();
}
void a(void* c,autotest::Capture& o){side(*(Case*)c,false,o);}void b(void* c,autotest::Capture& o){side(*(Case*)c,true,o);}
}
TL_TEST(combine_interaction_differential){autotest::Coverage coverage("combine_interaction_differential",(uint64_t)(uintptr_t)&originalInteraction);unsigned total=0,branches=0;for(unsigned mode=0;mode<32;++mode)for(unsigned profile=0;profile<4;++profile)for(unsigned change=0;change<2;++change){Case c={mode,profile,bool(change),0};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);int pair=coverage.observe(host,u,v);++total;bool ok=!pair&&u.reportValid&&v.reportValid&&u.childStatus==0&&v.childStatus==0&&u.capture.callStarted&&v.capture.callStarted&&u.capture.callCompleted&&v.capture.callCompleted&&u.capture.issue==0&&v.capture.issue==0&&u.capture.length>100&&u.capture.length==v.capture.length&&!std::memcmp(u.capture.data,v.capture.data,u.capture.length);if(!ok){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    MISMATCH %u/%u/%u first %lu exit %d/%d lengths %lu/%lu\n",mode,profile,change,(unsigned long)f,u.childStatus,v.childStatus,(unsigned long)u.capture.length,(unsigned long)v.capture.length);for(size_t i=f/4>5?f/4-5:0;i<f/4+10;++i){unsigned x=0,y=0;if(i*4+4<=u.capture.length)std::memcpy(&x,u.capture.data+i*4,4);if(i*4+4<=v.capture.length)std::memcpy(&y,v.capture.data+i*4,4);host->log("    word %lu %u/%u\n",(unsigned long)i,x,y);}coverage.report(host);return 1;}unsigned bits=0;std::memcpy(&bits,u.capture.data+u.capture.length-4,4);branches|=bits;}coverage.report(host);host->log("    FULL BODY: %u cases; branch witnesses %x/1fff\n",total,branches);return branches==0x1fff?0:1;}

// Supplemental unwind observations are never counted as successful call coverage.
TL_TEST(combine_interaction_expected_exceptions){unsigned total=0;const unsigned modes[]={20,26};for(unsigned m=0;m<2;++m)for(unsigned fault=1;fault<=30;++fault)for(unsigned change=0;change<2;++change){Case c={modes[m],2,bool(change),fault};autotest::Outcome u,v;autotest::runChild(a,&c,u);autotest::runChild(b,&c,v);++total;bool ok=u.reportValid&&v.reportValid&&u.childStatus==0&&v.childStatus==0&&u.capture.issue==0&&v.capture.issue==0&&u.capture.callStarted&&v.capture.callStarted&&!u.capture.callCompleted&&!v.capture.callCompleted&&u.capture.callTarget==(uint64_t)(uintptr_t)&originalInteraction&&host->comparison_pair&&host->comparison_pair(u.capture.callTarget,v.capture.callTarget)&&u.capture.length>100&&u.capture.length==v.capture.length&&!std::memcmp(u.capture.data,v.capture.data,u.capture.length);if(!ok){size_t f=0;while(f<u.capture.length&&f<v.capture.length&&u.capture.data[f]==v.capture.data[f])++f;host->log("    UNWIND MISMATCH mode %u fault %u change %u first %lu exit %d/%d completed %u/%u lengths %lu/%lu\n",modes[m],fault,change,(unsigned long)f,u.childStatus,v.childStatus,u.capture.callCompleted,v.capture.callCompleted,(unsigned long)u.capture.length,(unsigned long)v.capture.length);return 1;}}host->log("    EXPECTED EXCEPTIONS: %u matching partial-state observations, excluded from normal coverage\n",total);return 0;}
