
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <new>
#include <stdexcept>
#include <fenv.h>
#include <OgreVector3.h>
#include "AutoTest.h"
#include "ObservedWitness.h"
#include "Detour.h"
#include "DataGroup.h"
extern "C" void* editorGlobal __asm__("gEditor");
extern "C" char editorMemory[4000] __asm__("sEditorTmpMemory");
extern "C" wchar_t editorString[1000] __asm__("sEditorString");
extern "C" unsigned collisionKey __asm__("KSETTINGS_DISPLAY_COLLISION");
extern "C" const std::wstring& valueName(CDataValue*) __asm__("_ZN10CDataValue16GetDataValueNameEv");
extern "C" int scrubKey __asm__("_ZL21gGlobalRandomScrubKey");
extern "C" void* roomTable[] __asm__("_ZTV10CRoomPiece");
extern "C" void* timelineTable[] __asm__("_ZTV9CTimeline");
extern "C" void* particleTable[] __asm__("_ZTV16CParticleWrapper");
extern "C" void* techTable[] __asm__("_ZTV20CParticleTechWrapper");
extern "C" void* layoutTable[] __asm__("_ZTV7CLayout");
extern "C" void* objectTable[] __asm__("_ZTV17CEditorBaseObject");
extern "C" char textureTarget[] __asm__("_ZN4Ogre14TextureManager12getSingletonEv");
extern "C" char chdirTarget[] __asm__("chdir");
extern "C" char randTarget[] __asm__("rand");
TL_ORIGINAL(void,original0,(long long),"_Z13rollRoomPiecex")
extern "C" void candidate0(long long) __asm__("_Z13rollRoomPiecex");
TL_ORIGINAL(void,original1,(),"_Z28EditorToggleDisplayCollisionv")
extern "C" void candidate1() __asm__("_Z28EditorToggleDisplayCollisionv");
TL_ORIGINAL(void,original2,(wchar_t*,float),"_Z21EditorTestCameraShakePwf")
extern "C" void candidate2(wchar_t*,float) __asm__("_Z21EditorTestCameraShakePwf");
TL_ORIGINAL(void,original3,(wchar_t*,float,float,float),"_Z15EditorPlaySoundPwfff")
extern "C" void candidate3(wchar_t*,float,float,float) __asm__("_Z15EditorPlaySoundPwfff");
TL_ORIGINAL(void,original4,(),"_Z21EditorReloadAllAssetsv")
extern "C" void candidate4() __asm__("_Z21EditorReloadAllAssetsv");
TL_ORIGINAL(float,original5,(long long,float),"_Z28EditorTimelineSetPercentDonexf")
extern "C" float candidate5(long long,float) __asm__("_Z28EditorTimelineSetPercentDonexf");
TL_ORIGINAL(void,original6,(const wchar_t*,const wchar_t*),"_Z31EditorConvertLayoutToNewTilesetPKwS0_")
extern "C" void candidate6(const wchar_t*,const wchar_t*) __asm__("_Z31EditorConvertLayoutToNewTilesetPKwS0_");
TL_ORIGINAL(void*,original7,(char*),"_Z24EditorGetUnitsByUnittypePc")
extern "C" void* candidate7(char*) __asm__("_Z24EditorGetUnitsByUnittypePc");
TL_ORIGINAL(void,original8,(unsigned,long long,unsigned),"_Z15EditorFireEventjxj")
extern "C" void candidate8(unsigned,long long,unsigned) __asm__("_Z15EditorFireEventjxj");
TL_ORIGINAL(void*,original9,(unsigned,long long,unsigned,wchar_t*),"_Z20EditorGetListOfItemsjxjPw")
extern "C" void* candidate9(unsigned,long long,unsigned,wchar_t*) __asm__("_Z20EditorGetListOfItemsjxjPw");
TL_FUNCTION(target_master,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(target_lookup,"_Z16GetObjectInScenex")
TL_FUNCTION(target_sceneName,"_ZN7CEditor14GetEditorSceneESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_sceneID,"_ZN7CEditor14GetEditorSceneEj")
TL_FUNCTION(target_getInt,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(target_setInt,"_ZN20CDynamicPropertyFile6SetIntEji")
TL_FUNCTION(target_selectVisual,"_ZN10CRoomPiece20selectNewVisualIndexEv")
TL_FUNCTION(target_setGuid,"_ZN10CRoomPiece16setRoomPieceGuidEx")
TL_FUNCTION(target_shakeCtor,"_ZN12CCameraShakeC1ERKSbIwSt11char_traitsIwESaIwEEN4Ogre7Vector3Ef")
TL_FUNCTION(target_camera,"_ZN16CResourceManager16getCameraControlEv")
TL_FUNCTION(target_addSafe,"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(target_cleanPath,"_ZN10FILESYSTEM9CleanPathERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_localPath,"_ZN10FILESYSTEM12GetLocalPathEv")
TL_FUNCTION(target_utf8,"_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_createSound,"_ZN13CSoundManager11createSoundESbIwSt11char_traitsIwESaIwEE10SOUND_TYPEbff")
TL_FUNCTION(target_playSound,"_ZN13CSoundManager9playSoundEP14CSoundInstancePN4Ogre9SceneNodeEif")
TL_FUNCTION(target_releaseSound,"_ZN13CSoundManager12releaseSoundEP14CSoundInstance")
TL_FUNCTION(target_reloadParticles,"_ZN18CParticlePreloader21ReloadEditorParticlesEv")
TL_FUNCTION(target_reloadSounds,"_ZN11CGameClient19reloadSoundBankDataEv")
TL_FUNCTION(target_missileSingleton,"_ZN17CMissilePreloader13getSingleltonEv")
TL_FUNCTION(target_reloadMissiles,"_ZN17CMissilePreloader14reloadMissilesEv")
TL_FUNCTION(target_questSingleton,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(target_reloadQuests,"_ZN13CQuestManager12reloadQuestsEv")
TL_FUNCTION(target_themeSingleton,"_ZN11CUnitThemes12getSingletonEv")
TL_FUNCTION(target_reloadThemes,"_ZN11CUnitThemes6reloadEv")
TL_FUNCTION(target_setsSingleton,"_ZN5CSets12getSingletonEv")
TL_FUNCTION(target_reloadSets,"_ZN5CSets6reloadEP19CEffectGroupManager")
TL_FUNCTION(target_recipesSingleton,"_ZN8CRecipes12getSingletonEv")
TL_FUNCTION(target_reloadRecipes,"_ZN8CRecipes6reloadEv")
TL_FUNCTION(target_spawnSingleton,"_ZN17CSpawnClassParser12getSingletonEv")
TL_FUNCTION(target_reloadSpawn,"_ZN17CSpawnClassParser19reloadFromDirectoryEPKw")
TL_FUNCTION(target_cinemaSingleton,"_ZN11CCinematics12getSingletonEv")
TL_FUNCTION(target_reloadCinema,"_ZN11CCinematics6reloadEv")
TL_FUNCTION(target_reloadEffects,"_ZN19CEffectGroupManager6reloadEv")
TL_FUNCTION(target_clearLayouts,"_ZN7CLayout25removeAllCloneableObjectsEv")
TL_FUNCTION(target_fileExists,"_ZN10FILESYSTEM10FileExistsERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_loadLayout,"_ZN7CLayout14loadLayoutFileERKSbIwSt11char_traitsIwESaIwEEbP13CTimerStaticsbbj")
TL_FUNCTION(target_timelinePercent,"_ZN9CTimeline22SetTimelinePercentDoneEf")
TL_FUNCTION(target_seedRandom,"_ZN9UTILITIES7setSeedEi")
TL_FUNCTION(target_descriptorObjects,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_particleUpdate,"_ZN16ParticleUniverse14ParticleSystem7_updateEf")
TL_FUNCTION(target_roomSingleton,"_ZN25CRoomPieceDataInformation12getSingletonEv")
TL_FUNCTION(target_tiles,"_ZN25CRoomPieceDataInformation29getRoomPieceCoreDataByTilesetERKSbIwSt11char_traitsIwESaIwEER10TArrayListIPNS_18CRoomPieceCoreDataEE")
TL_FUNCTION(target_loadGroup,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TL_FUNCTION(target_saveGroup,"_ZN10CDataGroup10SaveToFileERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_convert,"_Z17convertRoomPiecesP10CDataGroupR10TArrayListIPN25CRoomPieceDataInformation18CRoomPieceCoreDataEE")
TL_FUNCTION(target_unitType,"_ZN16CResourceManager17getUnitTypeByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_masterList,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(target_unitGroups,"_ZN17CUnitResourceList23getDataGroupsByUnitTypeEjR10TArrayListIP10CDataGroupE")
TL_FUNCTION(target_roomLoad,"_ZN25CRoomPieceDataInformation12LoadRoomDataEv")
TL_FUNCTION(target_clearSelection,"_ZN20CEditorObjectManager20ClearSelectedObjectsEv")
TL_FUNCTION(target_selectObject,"_ZN20CEditorObjectManager20EditorObjectSelectedEP17CEditorBaseObject")
TL_FUNCTION(target_graphSingleton,"_ZN13CGraphManager12getSingletonEv")
TL_FUNCTION(target_reloadGraphs,"_ZN13CGraphManager6reloadEv")
TL_FUNCTION(target_gameClient,"_ZN7CEditor13getGameClientEv")
TL_FUNCTION(target_toggleLight,"_ZN11CGameClient17togglePlayerLightEv")
TL_FUNCTION(target_propertyValues,"_ZN11CDescriptor23GetPropertyListOfValuesEP17CEditorBaseObjectjRSt6vectorISbIwSt11char_traitsIwESaIwEESaIS6_EE")

namespace {
struct Case{unsigned op,seed,mode;float value;};struct List{void**data;unsigned count,capacity,grow,pad;};typedef std::map<long long,void*> Map;
Case*input;autotest::Capture*output;void*editors[2],*masters[2],*managers[2],*resources[2],*scenes[2],*objects[8],*services[24],*cameras[2],*previews[2];Map*maps[2];List queryList;CDataGroup*dataGroups[8];unsigned calls,masterCalls;void*allocatedShake;void*cameraReference;std::vector<std::wstring>*currentValues;
void num(unsigned n){output->add(&n,4);}void ptr(const void*p){output->add(&p,8);}void fl(float v){output->add(&v,4);}void event(unsigned n,void*p){num(n);ptr(p);}void put(void*p,unsigned off,void*v){std::memcpy(static_cast<char*>(p)+off,&v,8);}void word(void*p,unsigned off,unsigned v){std::memcpy(static_cast<char*>(p)+off,&v,4);}void change(){++calls;if(input->mode==3)editorGlobal=editors[calls%2];if(input->mode==4)collisionKey+=3;if(input->mode==5){long long v=71111+calls;std::memcpy(static_cast<char*>(objects[0])+0x140,&v,8);}if(input->mode==6&&calls%3==0){queryList.count=2;queryList.capacity=0;}}
void listState(const List&v){num(v.count);num(v.capacity);num(v.grow);if(v.data){unsigned n=v.capacity<8?8:v.capacity;output->add(v.data,8*n);}}
void groupState(CDataGroup*g){output->addText(g->GetGroupName());num(g->m_DataValues.size());for(unsigned i=0;i<g->m_DataValues.size();++i){CDataValue*v=g->m_DataValues[i];output->addText(valueName(v));output->addText(v->GetValueAsString());output->addText(v->GetValueTypeAsString());}num(g->m_DataGroups.size());for(unsigned i=0;i<g->m_DataGroups.size();++i)groupState(g->m_DataGroups[i]);}
void*master(){num(1);change();return masters[(input->mode==4?masterCalls++:0)%2];}
void*lookup(long long guid){num(2);output->add(&guid,8);change();if(input->mode==7)return NULL;if(input->mode==8)return objects[4];return objects[input->op==5?1:input->op==9?4:0];}
void*sceneName(void*p,std::wstring name){event(3,p);output->addText(name);change();return input->mode==7?NULL:scenes[calls%2];}
void*sceneID(void*p,unsigned index){event(4,p);num(index);change();return input->mode==7?NULL:scenes[calls%2];}
int getInt(void*p,unsigned key){event(5,p);num(key);change();const int values[]={0,1,-1,2,int(0x80000000u)};return values[(input->seed/12)%5];}
void setInt(void*p,unsigned key,int value){event(6,p);num(key);num(value);change();}
void selectVisual(void*p){event(7,p);change();word(p,0x140,0x7890+input->seed);}
void setGuid(void*p,long long guid){event(8,p);output->add(&guid,8);change();std::memcpy(static_cast<char*>(p)+0x140,&guid,8);}
void shakeCtor(void*p,const std::wstring&name,Ogre::Vector3 direction,float duration){event(9,p);output->addText(name);output->add(&direction,12);fl(duration);change();std::memset(p,0x48+input->seed%30,0xa0);allocatedShake=p;if(input->mode==9){allocatedShake=NULL;throw std::runtime_error("shake constructor");}}
void*camera(void*p){event(10,p);change();return cameras[calls%2];}
unsigned addSafe(void*p,void*reference){event(11,p);ptr(reference);output->add(reference,12);change();cameraReference=reference;put(reference,0,services[4]);return input->seed*997u;}
std::wstring cleanPath(const std::wstring&name){num(12);output->addText(name);change();return L"cleaned/"+name;}
std::wstring localPath(){num(13);change();return L"test/cwd";}
std::string utf8(const std::wstring&name){num(14);output->addText(name);change();return "test/cwd";}
int changeDirectory(const char*path){num(15);output->addText(std::string(path));change();return input->seed&1?-1:0;}
void*createSound(void*p,std::wstring path,int kind,bool flag,float minimum,float maximum){event(16,p);output->addText(path);num(kind);num(flag);fl(minimum);fl(maximum);change();return input->mode==9?NULL:services[3];}
int playSound(void*p,void*sound,void*node,int channel,float volume){event(17,p);ptr(sound);ptr(node);num(channel);fl(volume);change();return input->seed;}
void releaseSound(void*p,void*sound){event(18,p);ptr(sound);change();}
void*texture(){num(19);change();return services[9];}
void textureBits(void*p,unsigned short a,unsigned short b,bool c){event(20,p);num(a);num(b);num(c);change();}
void textureReload(void*p,bool a){event(21,p);num(a);change();}
void*client(void*p){event(22,p);change();return input->mode==7?NULL:services[1];}
void reloadSets(void*p,void*effects){event(23,p);ptr(effects);change();}
void reloadSpawn(void*p,const wchar_t*path){event(24,p);output->addText(std::wstring(path));change();}
void clearLayouts(){num(25);change();if(input->mode==6)*reinterpret_cast<std::wstring*>(static_cast<char*>(objects[2])+0x168)=L"changed layout";}
bool fileExists(const std::wstring&path){num(26);output->addText(path);change();return input->seed&16;}
void loadLayout(void*p,const std::wstring&path,bool a,void*timer,bool b,bool c,unsigned seed){event(27,p);output->addText(path);num(a);ptr(timer);num(b);num(c);num(seed);change();}
float timelinePercent(void*p,float percent){event(28,p);fl(percent);change();float duration=float((input->seed/12)%5)*0.0125f;std::memcpy(static_cast<char*>(p)+0x94,&duration,4);return input->value;}
void seedRandom(int seed){num(29);num(seed);change();if(input->mode==6){float duration=0.06666667f;std::memcpy(static_cast<char*>(objects[1])+0x94,&duration,4);}}
void*descriptorObjects(void*p,const std::wstring&name){event(30,p);output->addText(name);change();return input->op==5&&input->mode==9?NULL:&queryList;}
bool playing(void*p){event(31,p);change();return input->seed&32;}
void stop(void*p){event(32,p);change();put(p,0x118,services[7]);}
void start(void*p){event(33,p);change();put(p,0x118,services[8]);}
void particleUpdate(void*p,float elapsed){event(34,p);fl(elapsed);change();if(input->mode==6){put(objects[3],0x118,services[calls%2+7]);put(objects[6],0x118,services[calls%2+7]);}}
void tiles(void*p,const std::wstring&name,TArrayList<void*>&out){event(35,p);output->addText(name);num(out.size());change();for(unsigned i=0;i<(input->seed/12)%5;++i)out.add(objects[i]);}
bool loadGroup(void*p,const std::wstring&name,void*timer){num(36);output->addText(name);ptr(timer);groupState(static_cast<CDataGroup*>(p));change();if(input->seed&16)static_cast<CDataGroup*>(p)->AddDataGroup(L"OBJECTS")->AddDataValue(L"SEED",input->seed);return input->seed&32;}
void saveGroup(void*p,const std::wstring&name){num(37);output->addText(name);groupState(static_cast<CDataGroup*>(p));change();}
bool convert(CDataGroup*group,TArrayList<void*>&pieces){num(38);groupState(group);num(pieces.size());for(unsigned i=0;i<pieces.size();++i)ptr(pieces[i]);change();group->AddDataValue(L"CONVERTED",true);return input->seed&64;}
unsigned unitType(void*p,const std::wstring&name){event(39,p);output->addText(name);change();const unsigned v[]={0,1,21,22,23,0xffffffffu};return v[(input->seed/12)%6];}
void*masterList(void*p){event(40,p);change();return services[10];}
void unitGroups(void*p,unsigned type,TArrayList<CDataGroup*>&out){event(41,p);num(type);num(out.size());change();for(unsigned i=0;i<(input->seed/12)%8;++i)out.add(dataGroups[i]);if(input->mode==10&&out.size())reinterpret_cast<List*>(&out)->capacity=0;}
void clearSelection(void*p){event(42,p);change();reinterpret_cast<List*>(static_cast<char*>(p)+0x40)->count=0;}
void*collisionMesh(void*p){event(43,p);change();return input->seed&16?NULL:services[18];}
void selectObject(void*p,void*object){event(44,p);ptr(object);change();List*list=reinterpret_cast<List*>(static_cast<char*>(p)+0x40);if(list->count<8)list->data[list->count++]=object;}
void fireEvent(void*p,unsigned eventID,long long guid){event(45,p);num(eventID);output->add(&guid,8);change();}
int randValue(){num(46);change();return int(input->seed*98765u);}
void propertyValues(void*p,void*object,unsigned property,std::vector<std::wstring>&values){event(47,p);ptr(object);num(property);num(values.size());change();const wchar_t*words[]={L"alpha",L"",L"\u03a9\u4f60",L"alpha",L"final",L"x|y"};for(unsigned i=0;i<(input->seed/12)%7;++i)values.push_back(words[i%6]);if(input->mode==10){values.clear();values.push_back(std::wstring(999,L'Z'));}}
void reloadParticles(void*p){event(50,p);change();}
void reloadSounds(void*p){event(51,p);change();}
void reloadMissiles(void*p){event(52,p);change();}
void reloadQuests(void*p){event(53,p);change();}
void reloadThemes(void*p){event(54,p);change();}
void reloadRecipes(void*p){event(55,p);change();}
void reloadCinema(void*p){event(56,p);change();}
void reloadEffects(void*p){event(57,p);change();}
void roomLoad(void*p){event(58,p);change();}
void reloadGraphs(void*p){event(59,p);change();}
void toggleLight(void*p){event(60,p);change();}
void*missileSingleton(){num(70);change();return services[11];}
void*questSingleton(){num(71);change();return services[12];}
void*themeSingleton(){num(72);change();return services[13];}
void*setsSingleton(){num(73);change();return services[14];}
void*recipesSingleton(){num(74);change();return services[15];}
void*spawnSingleton(){num(75);change();return services[16];}
void*cinemaSingleton(){num(76);change();return services[17];}
void*roomSingleton(){num(77);change();return services[18];}
void*graphSingleton(){num(78);change();return services[19];}
void* gameClient(void*p){return client(p);}

void initList(void*p,unsigned count,unsigned capacity){List&v=*reinterpret_cast<List*>(p);v.data=new void*[8];v.count=count;v.capacity=capacity;v.grow=3;v.pad=0;for(unsigned i=0;i<8;++i)v.data[i]=objects[i];}
void mapState(Map&m){num(m.size());for(Map::iterator it=m.begin();it!=m.end();++it){output->add(&it->first,8);ptr(it->second);}}
void side(Case&c,bool ours,autotest::Capture&out){input=&c;output=&out;calls=masterCalls=0;allocatedShake=cameraReference=NULL;currentValues=NULL;
 unsigned long long ed[2][64]={{0}},mast[2][64]={{0}},man[2][16]={{0}},res[2][8]={{0}},sc[2][64]={{0}},obj[8][128]={{0}},srv[24][8]={{0}},cam[2][20]={{0}},prev[2][0x548/8]={{0}},visual[4]={0},core[8]={0};
 for(unsigned i=0;i<2;++i){editors[i]=ed[i];masters[i]=mast[i];managers[i]=man[i];resources[i]=res[i];scenes[i]=sc[i];cameras[i]=cam[i];previews[i]=prev[i];}for(unsigned i=0;i<24;++i)services[i]=srv[i];for(unsigned i=0;i<8;++i)objects[i]=obj[i];
 void*roomVtable[2+61];std::memcpy(roomVtable,roomTable,sizeof(roomVtable));roomVtable[2+0x1e0/8]=reinterpret_cast<void*>(&collisionMesh);
 void*particleVtable[2+67];std::memcpy(particleVtable,particleTable,sizeof(particleVtable));particleVtable[2+0x200/8]=reinterpret_cast<void*>(&stop);particleVtable[2+0x208/8]=reinterpret_cast<void*>(&start);particleVtable[2+0x210/8]=reinterpret_cast<void*>(&playing);
 void*techVtable[2+67];std::memcpy(techVtable,techTable,sizeof(techVtable));techVtable[2+0x200/8]=reinterpret_cast<void*>(&stop);techVtable[2+0x208/8]=reinterpret_cast<void*>(&start);techVtable[2+0x210/8]=reinterpret_cast<void*>(&playing);
 for(unsigned i=0;i<8;++i){void**table=(i==0||i==5)?roomVtable:i==1?timelineTable:i==3?techVtable:i==6?(c.seed&64?techVtable:particleVtable):i==2||i==7?layoutTable:objectTable;put(objects[i],0,table+2);put(objects[i],0x48,scenes[i%2]);put(objects[i],0x38,c.mode==9?NULL:services[0]);new(static_cast<char*>(objects[i])+0x168)std::wstring(i%2?L"layout alpha":L"layout beta");long long guid=(c.seed/12)%5==0?-1:0x123456789LL+c.seed;std::memcpy(static_cast<char*>(objects[i])+0x140,&guid,8);static_cast<char*>(objects[i])[0x150]=(c.seed/24)%2;put(objects[i],0x118,services[7]);}
 put(visual,0x10,c.seed&16?core:NULL);static_cast<char*>(static_cast<void*>(core))[0x31]=c.seed&32;put(objects[0],0x148,c.seed&64?visual:NULL);
 void*resourceTable[11]={0};resourceTable[10]=reinterpret_cast<void*>(&client);void*sceneTable[59]={0};sceneTable[58]=reinterpret_cast<void*>(&fireEvent);void*textureTable[46]={0};textureTable[45]=reinterpret_cast<void*>(&textureBits);textureTable[13]=reinterpret_cast<void*>(&textureReload);put(services[9],0,textureTable);
 for(unsigned i=0;i<2;++i){put(resources[i],0,resourceTable);put(editors[i],0x58,c.mode==2?NULL:resources[i]);put(editors[i],0x120,managers[i]);put(editors[i],0x128,c.mode==11?NULL:services[i+20]);static_cast<char*>(editors[i])[0x49]=c.mode==1;
  put(masters[i],0x90,services[i+21]);put(masters[i],0x98,c.mode==8?NULL:services[2]);put(masters[i],0xe8,services[19]);put(masters[i],0xf0,c.mode==8?NULL:previews[i]);put(masters[i],0xf8,c.mode==8?NULL:services[11]);put(masters[i],0x58,c.mode==8?NULL:services[12]);static_cast<char*>(previews[i])[0x540]=c.seed&16;
  put(scenes[i],0,sceneTable);maps[i]=new(static_cast<char*>(managers[i])+0x10)Map;for(unsigned j=0;j<(c.seed/12)%8;++j)(*maps[i])[j*100+7]=c.mode==9&&j%2?NULL:objects[j];initList(static_cast<char*>(managers[i])+0x40,(c.seed/24)%8,8);initList(static_cast<char*>(cameras[i])+0x58,(c.seed/24)%8,c.mode==10?0:8);
 }
 if(c.op==4&&c.mode==11)put(editors[0],0x120,NULL);
 void*queryData[8];for(unsigned i=0;i<8;++i)queryData[i]=objects[i];queryList.data=queryData;queryList.count=(c.seed/12)%8;queryList.capacity=c.mode==10?0:8;queryList.grow=2;queryList.pad=0;
 for(unsigned i=0;i<8;++i){dataGroups[i]=new CDataGroup(L"UNIT",NULL,10,10,NULL);if((i+c.seed)%3)dataGroups[i]->AddDataValue(L"NAME",std::wstring(i+1,L'A'+i),false);}
 editorGlobal=editors[0];collisionKey=100+c.seed;scrubKey=int(c.seed*7919u);std::memset(editorMemory,c.seed|0x81,4000);std::memset(editorString,c.seed|0x82,4000);wchar_t name[64]=L"asset/\u03a9 name";wchar_t other[64]=L"path/layout.dat";wchar_t separator[16]=L" | ";if(c.mode==6)separator[0]=0;
 detour::Set patches;
 TL_REDIRECT(patches,target_master,&master);
 TL_REDIRECT(patches,target_lookup,&lookup);
 TL_REDIRECT(patches,target_sceneName,&sceneName);
 TL_REDIRECT(patches,target_sceneID,&sceneID);
 TL_REDIRECT(patches,target_getInt,&getInt);
 TL_REDIRECT(patches,target_setInt,&setInt);
 TL_REDIRECT(patches,target_selectVisual,&selectVisual);
 TL_REDIRECT(patches,target_setGuid,&setGuid);
 TL_REDIRECT(patches,target_shakeCtor,&shakeCtor);
 TL_REDIRECT(patches,target_camera,&camera);
 TL_REDIRECT(patches,target_addSafe,&addSafe);
 TL_REDIRECT(patches,target_cleanPath,&cleanPath);
 TL_REDIRECT(patches,target_localPath,&localPath);
 TL_REDIRECT(patches,target_utf8,&utf8);
 TL_REDIRECT(patches,target_createSound,&createSound);
 TL_REDIRECT(patches,target_playSound,&playSound);
 TL_REDIRECT(patches,target_releaseSound,&releaseSound);
 TL_REDIRECT(patches,target_reloadParticles,&reloadParticles);
 TL_REDIRECT(patches,target_reloadSounds,&reloadSounds);
 TL_REDIRECT(patches,target_missileSingleton,&missileSingleton);
 TL_REDIRECT(patches,target_reloadMissiles,&reloadMissiles);
 TL_REDIRECT(patches,target_questSingleton,&questSingleton);
 TL_REDIRECT(patches,target_reloadQuests,&reloadQuests);
 TL_REDIRECT(patches,target_themeSingleton,&themeSingleton);
 TL_REDIRECT(patches,target_reloadThemes,&reloadThemes);
 TL_REDIRECT(patches,target_setsSingleton,&setsSingleton);
 TL_REDIRECT(patches,target_reloadSets,&reloadSets);
 TL_REDIRECT(patches,target_recipesSingleton,&recipesSingleton);
 TL_REDIRECT(patches,target_reloadRecipes,&reloadRecipes);
 TL_REDIRECT(patches,target_spawnSingleton,&spawnSingleton);
 TL_REDIRECT(patches,target_reloadSpawn,&reloadSpawn);
 TL_REDIRECT(patches,target_cinemaSingleton,&cinemaSingleton);
 TL_REDIRECT(patches,target_reloadCinema,&reloadCinema);
 TL_REDIRECT(patches,target_reloadEffects,&reloadEffects);
 TL_REDIRECT(patches,target_clearLayouts,&clearLayouts);
 TL_REDIRECT(patches,target_fileExists,&fileExists);
 TL_REDIRECT(patches,target_loadLayout,&loadLayout);
 TL_REDIRECT(patches,target_timelinePercent,&timelinePercent);
 TL_REDIRECT(patches,target_seedRandom,&seedRandom);
 TL_REDIRECT(patches,target_descriptorObjects,&descriptorObjects);
 TL_REDIRECT(patches,target_particleUpdate,&particleUpdate);
 TL_REDIRECT(patches,target_roomSingleton,&roomSingleton);
 TL_REDIRECT(patches,target_tiles,&tiles);
 TL_REDIRECT(patches,target_loadGroup,&loadGroup);
 TL_REDIRECT(patches,target_saveGroup,&saveGroup);
 TL_REDIRECT(patches,target_convert,&convert);
 TL_REDIRECT(patches,target_unitType,&unitType);
 TL_REDIRECT(patches,target_masterList,&masterList);
 TL_REDIRECT(patches,target_unitGroups,&unitGroups);
 TL_REDIRECT(patches,target_roomLoad,&roomLoad);
 TL_REDIRECT(patches,target_clearSelection,&clearSelection);
 TL_REDIRECT(patches,target_selectObject,&selectObject);
 TL_REDIRECT(patches,target_graphSingleton,&graphSingleton);
 TL_REDIRECT(patches,target_reloadGraphs,&reloadGraphs);
 TL_REDIRECT(patches,target_gameClient,&gameClient);
 TL_REDIRECT(patches,target_toggleLight,&toggleLight);
 TL_REDIRECT(patches,target_propertyValues,&propertyValues);

 patches.redirect(textureTarget,textureTarget,&texture);patches.redirect(chdirTarget,chdirTarget,&changeDirectory);patches.redirect(randTarget,randTarget,&randValue);if(patches.failed())_exit(41);feclearexcept(FE_ALL_EXCEPT);unsigned threw=0;
 try{switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,static_cast<long long>(c.seed)*98765431);break;
 case 1:autotest::invoke(out,ours?candidate1:original1);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,c.mode==7?NULL:name,c.value);break;
 case 3:autotest::invoke(out,ours?candidate3:original3,name,c.value,-c.value,c.value*0.5f);break;
 case 4:autotest::invoke(out,ours?candidate4:original4);break;
 case 5:autotest::invoke(out,ours?candidate5:original5,static_cast<long long>(c.seed)*131, c.value);break;
 case 6:autotest::invoke(out,ours?candidate6:original6,static_cast<const wchar_t*>(name),static_cast<const wchar_t*>(other));break;
 case 7:{void*(*fn)(char*)=ours?candidate7:original7;if(!autotest::beginInvocation(out,fn))return;void*ret=fn(reinterpret_cast<char*>(name));out.callCompleted=1;ptr(ret);break;}
 case 8:autotest::invoke(out,ours?candidate8:original8,c.seed&8?0xffffffffu:c.seed,static_cast<long long>(c.seed)*0x123456789LL,(c.seed/12)%18);break;
 case 9:{void*(*fn)(unsigned,long long,unsigned,wchar_t*)=ours?candidate9:original9;if(!autotest::beginInvocation(out,fn))return;void*ret=fn(c.seed,static_cast<long long>(c.seed)*0x123456789LL,c.seed*1234567u,separator);out.callCompleted=1;ptr(ret);break;}
 }}catch(const std::runtime_error&e){threw=std::strcmp(e.what(),"shake constructor")==0?1u:~0u;out.addText(e.what());}
 num(threw);num(fetestexcept(FE_ALL_EXCEPT));num(calls);num(masterCalls);num(collisionKey);num(scrubKey);ptr(editorGlobal);out.add(editorMemory,4000);out.add(editorString,4000);if(allocatedShake)out.add(allocatedShake,0xa0);if(cameraReference)out.add(cameraReference,12);
 for(unsigned i=0;i<2;++i){mapState(*maps[i]);std::memset(static_cast<char*>(managers[i])+0x10,0,48);List&selection=*reinterpret_cast<List*>(static_cast<char*>(managers[i])+0x40);listState(selection);put(managers[i],0x40,NULL);List&shakes=*reinterpret_cast<List*>(static_cast<char*>(cameras[i])+0x58);num(shakes.count);num(shakes.capacity);num(shakes.grow);for(unsigned j=0;j<shakes.count;++j){void*p=shakes.data[j];ptr(p);if(p==cameraReference)out.add(p,12);}put(cameras[i],0x58,NULL);}
 for(unsigned i=0;i<8;++i){out.addText(*reinterpret_cast<std::wstring*>(static_cast<char*>(objects[i])+0x168));std::memset(static_cast<char*>(objects[i])+0x168,0,8);}
 listState(queryList);out.add(ed,sizeof(ed));out.add(mast,sizeof(mast));out.add(man,sizeof(man));out.add(res,sizeof(res));out.add(sc,sizeof(sc));out.add(obj,sizeof(obj));out.add(srv,sizeof(srv));out.add(cam,sizeof(cam));out.add(prev,sizeof(prev));out.add(visual,sizeof(visual));out.add(core,sizeof(core));out.add(name,sizeof(name));out.add(other,sizeof(other));out.add(separator,sizeof(separator));patches.restore();observed_witness::finish(out,threw);
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned op,const char*name){const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2,(uint64_t)(uintptr_t)original3,(uint64_t)(uintptr_t)original4,(uint64_t)(uintptr_t)original5,(uint64_t)(uintptr_t)original6,(uint64_t)(uintptr_t)original7,(uint64_t)(uintptr_t)original8,(uint64_t)(uintptr_t)original9};
 const float values[]={0.0f,-0.0f,1.0f,-1.0f,0.5f,2.0f,0.0166666675f,0.2f,1.01f,0.00001f};autotest::Coverage coverage(name,addresses[op]);unsigned witnesses=0;for(unsigned n=0;n<864;++n){Case c={op,n,n%12,values[(n/12)%10]};if(n%31==0){unsigned bits=0x7fc01234;std::memcpy(&c.value,&bits,4);}autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);const unsigned expectedFault=op==2&&c.mode==9?1u:0u;if(observed_witness::observe(host,coverage,a,b,expectedFault,witnesses)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    editor more %u/%u mode %u status %d/%d first %lu bytes %lu/%lu\n",op,n,c.mode,a.status,b.status,(unsigned long)at,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(size_t i=0;i<a.capture.length&&i<b.capture.length&&i<220;i+=4){unsigned aa=0,bb=0;std::memcpy(&aa,a.capture.data+i,4);std::memcpy(&bb,b.capture.data+i,4);host->log("    word %lu %08x/%08x\n",(unsigned long)i,aa,bb);}coverage.report(host);return 1;}if(expectedFault&&witnesses==1&&!observed_witness::negativeControls(host,coverage,a,b,expectedFault))return 1;}coverage.report(host);return observed_witness::totals(host,coverage,witnesses,op==2?792u:864u,op==2?72u:0u)?0:1;}
}
TL_TEST(editor_more_roll){return run(host,0,"editor_more_roll");}
TL_TEST(editor_more_collision){return run(host,1,"editor_more_collision");}
TL_TEST(editor_more_shake){return run(host,2,"editor_more_shake");}
TL_TEST(editor_more_sound){return run(host,3,"editor_more_sound");}
TL_TEST(editor_more_assets){return run(host,4,"editor_more_assets");}
TL_TEST(editor_more_timeline){return run(host,5,"editor_more_timeline");}
TL_TEST(editor_more_tileset){return run(host,6,"editor_more_tileset");}
TL_TEST(editor_more_units){return run(host,7,"editor_more_units");}
TL_TEST(editor_more_event){return run(host,8,"editor_more_event");}
TL_TEST(editor_more_values){return run(host,9,"editor_more_values");}
