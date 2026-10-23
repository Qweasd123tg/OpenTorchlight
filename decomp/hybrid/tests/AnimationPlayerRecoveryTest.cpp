#include <Ogre.h>
#include <fenv.h>
#include <cstring>
#include <vector>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "AnimationPlayer.h"
#include "Character.h"
#include "Equipment.h"
#include "Player.h"
#include "GenericModel.h"
#include "UnitResourceList.h"
#include "MasterResourceManager.h"
#include "GameClient.h"
#undef protected
#undef private
#include "tests/NativeMenuClient.h"
#include "tests/FinishLevelFixture.h"

TL_ORIGINAL(void, animationStopOriginal,(CAnimationPlayer*,bool),"_ZN16CAnimationPlayer13stopAnimationEb")
extern "C" void animationStopCandidate(CAnimationPlayer*,bool) __asm__("_ZN16CAnimationPlayer13stopAnimationEb");
TL_ORIGINAL(void, animationBoolOriginal,(CAnimationPlayer*,bool),"_ZN16CAnimationPlayer13playAnimationEb")
extern "C" void animationBoolCandidate(CAnimationPlayer*,bool) __asm__("_ZN16CAnimationPlayer13playAnimationEb");
TL_ORIGINAL(void, animationPlayOriginal,(CAnimationPlayer*),"_ZN16CAnimationPlayer13playAnimationEv")
extern "C" void animationPlayCandidate(CAnimationPlayer*) __asm__("_ZN16CAnimationPlayer13playAnimationEv");
TL_ORIGINAL(void, animationCtor,(CAnimationPlayer*,CResourceManager*),"_ZN16CAnimationPlayerC1EP16CResourceManager")
TL_ORIGINAL(void, animationDtor,(CAnimationPlayer*),"_ZN16CAnimationPlayerD1Ev")
TL_FUNCTION(animationPlaying,"_ZNK13CGenericModel16animationPlayingERKSs")
TL_FUNCTION(animationQueued,"_ZNK13CGenericModel15animationQueuedERKSs")
TL_FUNCTION(animationBlend,"_ZN13CGenericModel14blendAnimationERKSsbfff")
TL_FUNCTION(animationQueue,"_ZN13CGenericModel19queueBlendAnimationERKSsbff")
TL_FUNCTION(animationAI,"_ZN10CCharacter18setAIPlayAnimationERKSsbff")
TL_FUNCTION(animationLength,"_ZNK13CGenericModel25getAnimationLengthSecondsERKSs")
TL_FUNCTION(animationMasterList,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(animationDataGroup,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(animationByGroup,"_ZN6CLevel23getBaseUnitsByDataGroupEP10CDataGroupR10TArrayListIP9CBaseUnitE")
TL_FUNCTION(animationByType,"_ZN6CLevel18getUnitsByUnitTypeEN9UNITTYPES10EUNITTYPESER10TArrayListIP9CBaseUnitE")
TL_FUNCTION(animationType,"_ZN10CHierarchy15getTypeIDByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(animationPlaySeam,"_ZN16CAnimationPlayer13playAnimationEv")
TL_FUNCTION(animationBoolSeam,"_ZN16CAnimationPlayer13playAnimationEb")
TL_FUNCTION(animationRemove,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_ORIGINAL(void, animationRemoveOriginal,(CRunicCore*,TSafePointer<void*>*,unsigned),"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")

namespace {
struct Case {unsigned op,seed;bool negative;};
const Case* current;autotest::Capture* output;CAnimationPlayer* self;
CResourceManager* resources;CGameClient* client;CBaseUnit* units[5];CGenericModel* models[4];
CLevel* levels[2];CResourceManager* alternative;CUnitResourceList* resourceList;CDataGroup* unitGroup;
unsigned modelCalls[5],playingCalls,queuedCalls,aiCalls,stateCalls,blendCalls,queueCalls,lengthCalls,eventCalls,removedCalls;
bool mutated;std::vector<void*> oldReferences;detour::Set* removeHook;

void number(long long v){output->add(&v,sizeof v);}void scalar(float v){output->add(&v,sizeof v);}
float bits(unsigned v){float r;std::memcpy(&r,&v,4);return r;}
const unsigned floats[]={0,0x80000000u,0x3f800000u,0xbf800000u,0x3f000000u,0x40000000u,0x7f800000u,0xff800000u,0x7fc01234u,0xffc05678u,1,0x7f7fffffu};
unsigned unitID(const void* p){if(!p)return 98;for(unsigned i=0;i<5;++i)if(p==units[i])return i;return 99;}
unsigned modelID(const void* p){if(!p)return 98;for(unsigned i=0;i<4;++i)if(p==models[i])return i;return 99;}
unsigned levelID(const void* p){if(!p)return 98;return p==levels[0]?0:p==levels[1]?1:99;}
unsigned safeCount(CRunicCore* p){if(!p->m_pSafePointers)return 0;unsigned count=0;for(unsigned i=0;i<p->m_pSafePointers->size();++i)if((*p->m_pSafePointers)[i])++count;return count;}
void addTarget(CBaseUnit* unit){TSafePointer<CBaseUnit>* p=OGRE_NEW_T(TSafePointer<CBaseUnit>,Ogre::MEMCATEGORY_GENERAL)();p->setObject(unit);self->m_lAnimationTargets.add(p);}
void clearTargets(){for(unsigned i=0;i<self->m_lAnimationTargets.size();++i)if(self->m_lAnimationTargets[i])OGRE_DELETE_T(self->m_lAnimationTargets[i],TSafePointer<CBaseUnit>,Ogre::MEMCATEGORY_GENERAL);self->m_lAnimationTargets.clear();}
void snapshot(){number(self->m_bAnimationPlaying);number(self->m_bLoop);number(self->m_bPlayIdle);number(self->m_bDurationActive);scalar(self->m_fRemainingDuration);scalar(self->m_fBlendTime);scalar(self->m_fBlendOutTime);scalar(self->m_fForceDuration);number(self->m_lAnimationTargets.size());}
void event(CAnimationPlayer* p,unsigned value)
{
    number(10);number(p==self);number(value);++eventCalls;snapshot();
    if(value!=112&&value!=113)output->issue=autotest::Capture::InvalidReport;
    if((value==112&&self->m_bAnimationPlaying)||(value==113&&!self->m_bAnimationPlaying))output->issue=autotest::Capture::InvalidReport;
    if(current->seed%11==10){self->m_bAnimationPlaying=!self->m_bAnimationPlaying;self->m_bLoop=!self->m_bLoop;}
}
void* model(CBaseUnit* p)
{
    unsigned id=unitID(p);number(11);number(id);if(id>=5){output->issue=autotest::Capture::InvalidReport;return NULL;}
    unsigned call=++modelCalls[id],mode=current->seed/11%5;
    CGenericModel* result=models[(id+(mode==2||mode==3?call:0))%4];
    if(mode==1&&call==1&&id!=2)result=NULL;
    if(current->op==2&&current->seed==501&&id==3&&call==4)result=NULL;
    number(call);number(modelID(result));
    if(current->seed%17==16&&call==1)self->m_bLoop=!self->m_bLoop;
    return result;
}
void mutateTarget(){if(self->m_lAnimationTargets.size()&&self->m_lAnimationTargets[0])self->m_lAnimationTargets[0]->setObject(units[3]);}
bool playing(const CGenericModel* p,const std::string& name)
{
    number(12);number(modelID(p));output->addText(name);++playingCalls;
    bool result=current->op==2&&current->seed==501?false:((current->seed/4+modelID(p))&1)!=0;number(result);
    if(current->seed%10==2&&!mutated){mutated=true;addTarget(units[1]);}
    if(current->seed%10==3&&result&&self->m_lAnimationTargets.size()&&self->m_lAnimationTargets[0])self->m_lAnimationTargets[0]->setObject(NULL);
    return result;
}
bool queued(const CGenericModel* p,const std::string& name)
{
    number(13);number(modelID(p));output->addText(name);++queuedCalls;
    bool result=current->op==2&&current->seed==501?false:((current->seed/8+modelID(p))&1)!=0;number(result);
    if(current->seed%10==1&&!mutated){mutated=true;mutateTarget();}
    if(current->seed%10==4&&!mutated){mutated=true;addTarget(units[4]);self->m_fBlendTime=0.75f;}
    return result;
}
void ai(CCharacter* p,const std::string& name,bool loop,float blend,float speed){number(14);number(unitID(p));output->addText(name);number(loop);scalar(blend);scalar(speed);++aiCalls;if(speed!=1.0f)output->issue=autotest::Capture::InvalidReport;if(current->seed%13==12)self->m_fBlendTime=0.125f;}
void state(CCharacter* p,EAIState value){number(15);number(unitID(p));number(value);++stateCalls;p->m_eAIState=value;}
void blend(CGenericModel* p,const std::string& name,bool loop,float time,float speed,float extra){number(16);number(modelID(p));output->addText(name);number(loop);scalar(time);scalar(speed);scalar(extra);++blendCalls;if(speed!=1.0f||extra!=-1.0f)output->issue=autotest::Capture::InvalidReport;if(current->seed%10==5&&!mutated){mutated=true;mutateTarget();self->m_fBlendTime=0.625f;}}
void queue(CGenericModel* p,const std::string& name,bool loop,float time,float speed){number(17);number(modelID(p));output->addText(name);number(loop);scalar(time);scalar(speed);++queueCalls;if(name!="IDLE"||!loop||time!=0.2f||speed!=1.0f)output->issue=autotest::Capture::InvalidReport;}
float length(const CGenericModel* p,const std::string& name)
{
    number(18);number(modelID(p));output->addText(name);++lengthCalls;float value=bits(floats[current->seed/96%12]);scalar(value);
    if(current->seed%10==6&&!mutated){mutated=true;clearTargets();}
    if(current->seed%10==7){self->m_fForceDuration=2.25f;self->m_fBlendOutTime=0.125f;}
    return value;
}
CUnitResourceList* masterList(CResourceManager* p){number(20);number(p==resources?0:p==alternative?1:99);return resourceList;}
CDataGroup* dataGroup(CUnitResourceList* p,const std::wstring& group,const std::wstring& name)
{
    number(21);number(p==resourceList);output->addText(group);output->addText(name);
    if(group!=L"MONSTERS"&&group!=L"PROPS")output->issue=autotest::Capture::InvalidReport;
    if(current->seed%10==8)self->m_pResourceManager=alternative;
    return current->seed%7==0?NULL:unitGroup;
}
void fill(TArrayList<CBaseUnit*>& out)
{
    number(out.size());if(out.size())output->issue=autotest::Capture::InvalidReport;
    unsigned count=current->seed/7%7;if(count==6)count=17;
    for(unsigned i=0;i<count;++i){CBaseUnit* p=(i+current->seed)%7==0?NULL:units[(i+current->seed/3)%5];out.add(p);number(unitID(p));}number(out.size());
}
void byGroup(CLevel* p,CDataGroup* group,TArrayList<CBaseUnit*>& out){number(22);number(levelID(p));number(group==unitGroup);fill(out);}
void byType(CLevel* p,UNITTYPES::EUNITTYPES type,TArrayList<CBaseUnit*>& out){number(23);number(levelID(p));number(type);fill(out);}
UNITTYPES::EUNITTYPES type(CHierarchy* p,const std::wstring& name){number(24);number(p==CMasterResourceManager::getSingleton()->m_pHierarchy);output->addText(name);return static_cast<UNITTYPES::EUNITTYPES>(73+current->seed%3);}
void playSeam(CAnimationPlayer* p){number(25);number(p==self);snapshot();if(current->seed%10==9)self->m_bPlayIdle=!self->m_bPlayIdle;}
void boolSeam(CAnimationPlayer* p,bool loop){number(26);number(p==self);number(loop);snapshot();self->m_bDurationActive=loop;}
void remove(CRunicCore* p,TSafePointer<void*>* ref,unsigned index)
{
    number(27);number(unitID(p));unsigned id=999;for(unsigned i=0;i<oldReferences.size();++i)if(oldReferences[i]==ref)id=i;number(id);number(index);++removedCalls;
    removeHook->restore();animationRemoveOriginal(p,ref,index);TL_REDIRECT((*removeHook),animationRemove,&remove);if(removeHook->failed())output->issue=autotest::Capture::InvalidReport;
}

union PlayerStorage{long double align;unsigned char data[sizeof(CAnimationPlayer)];};
void side(void* argument,autotest::Capture& out,bool ours)
{
    current=static_cast<Case*>(argument);output=&out;mutated=false;std::memset(modelCalls,0,sizeof modelCalls);
    playingCalls=queuedCalls=aiCalls=stateCalls=blendCalls=queueCalls=lengthCalls=eventCalls=removedCalls=0;oldReferences.clear();
    finishlevel::Fixture world,otherWorld;levels[0]=&world.level;levels[1]=&otherWorld.level;alternative=&otherWorld.resources;alternative->m_pLevel=levels[1];
    CLevel* savedLevel=resources->m_pLevel;resources->m_pLevel=levels[0];
    CPlayer* savedPlayer=client->m_pPlayer;client->m_pPlayer=current->seed%23==0?NULL:static_cast<CPlayer*>(units[2]);
    CUnitResourceList list;resourceList=&list;CDataGroup group(L"ANIMATION_TARGET",NULL,2,2,NULL);unitGroup=&group;
    unsigned initialSafe[5];for(unsigned i=0;i<5;++i)initialSafe[i]=safeCount(units[i]);
    int before=g_iTotalCountOfObjects;
    PlayerStorage storage;self=reinterpret_cast<CAnimationPlayer*>(storage.data);animationCtor(self,resources);
    void** originalSelfTable=*reinterpret_cast<void***>(self);void* selfTable[18];std::memcpy(selfTable,originalSelfTable-2,sizeof selfTable);selfTable[2+0x30/8]=reinterpret_cast<void*>(&event);*reinterpret_cast<void***>(self)=selfTable+2;
    void** originalTables[5];void* tables[5][108];
    for(unsigned i=0;i<5;++i){originalTables[i]=*reinterpret_cast<void***>(units[i]);unsigned count=i<3?108:63;std::memcpy(tables[i],originalTables[i]-2,count*sizeof(void*));tables[i][2+0x1e0/8]=reinterpret_cast<void*>(&model);if(i<3){tables[i][2+0x348/8]=reinterpret_cast<void*>(&state);static_cast<CCharacter*>(units[i])->m_eAIState=static_cast<EAIState>(101+i);}*reinterpret_cast<void***>(units[i])=tables[i]+2;}
    unsigned seed=current->seed;
    const wchar_t* categories[]={L"PLAYER",L"MONSTERS",L"UNITTYPE",L"PROP",L"unknown",L"player"};self->m_sCategory=categories[seed/2%6];self->m_sUnitType=seed&8?L"monster_kind":L"fixture_kind";self->m_sAnimationName=seed%3==0?L"WALK":seed%3==1?L"IDLE":L"";
    self->m_bAnimationPlaying=bool(seed&2);self->m_bLoop=bool(seed&1);self->m_bPlayIdle=bool(seed&4);self->m_bDurationActive=bool(seed&8);
    self->m_fRemainingDuration=bits(floats[seed/5%12]);self->m_fBlendTime=bits(floats[seed/3%12]);self->m_fBlendOutTime=bits(floats[seed/16%12]);self->m_fForceDuration=bits(floats[seed/8%12]);
    if(current->op==1||current->op==3){addTarget(units[0]);self->m_lAnimationTargets.add(NULL);addTarget(NULL);addTarget(units[4]);}
    else if(current->op!=4&&seed%13){unsigned count=seed%6;for(unsigned i=0;i<count;++i)addTarget(i==3?NULL:units[i%5]);}
    if(current->op==2&&seed==501){clearTargets();addTarget(units[3]);self->m_bLoop=true;}
    // A real dead owner invalidates both the old animation weak reference and
    // an independent witness before play(bool) clears its stale references.
    TSafePointer<CBaseUnit> deadWitness;
    if(current->op==1||current->op==3){CEquipment* dead=new CEquipment(resources);deadWitness.setObject(dead);addTarget(dead);delete dead;if(deadWitness.getObject())out.issue=autotest::Capture::InvalidReport;}
    for(unsigned i=0;i<self->m_lAnimationTargets.size();++i)oldReferences.push_back(self->m_lAnimationTargets[i]);
    if((current->op==1||current->op==3||current->op==4)&&seed%17==0)self->m_pResourceManager=NULL;
    else if((current->op==1||current->op==3||current->op==4)&&seed%19==0)resources->m_pLevel=NULL;
    detour::Set hooks,removal;removeHook=&removal;
    TL_REDIRECT(hooks,animationPlaying,&playing);TL_REDIRECT(hooks,animationQueued,&queued);TL_REDIRECT(hooks,animationBlend,&blend);TL_REDIRECT(hooks,animationQueue,&queue);TL_REDIRECT(hooks,animationAI,&ai);TL_REDIRECT(hooks,animationLength,&length);TL_REDIRECT(hooks,animationMasterList,&masterList);TL_REDIRECT(hooks,animationDataGroup,&dataGroup);TL_REDIRECT(hooks,animationByGroup,&byGroup);TL_REDIRECT(hooks,animationByType,&byType);TL_REDIRECT(hooks,animationType,&type);TL_REDIRECT(removal,animationRemove,&remove);
    if(current->op==1)TL_REDIRECT(hooks,animationPlaySeam,&playSeam);
    if(current->op==2)TL_REDIRECT(hooks,animationBoolSeam,&boolSeam);
    if(hooks.failed()||removal.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    snapshot();feclearexcept(FE_ALL_EXCEPT);
    if(current->op==0)autotest::invoke(out,ours?animationStopCandidate:animationStopOriginal,self,bool(seed&1));
    else if(current->op==1||current->op==3)autotest::invoke(out,ours?animationBoolCandidate:animationBoolOriginal,self,bool(seed&1));
    else autotest::invoke(out,ours?animationPlayCandidate:animationPlayOriginal,self);
    number(fetestexcept(FE_ALL_EXCEPT));removal.restore();hooks.restore();
    if(ours&&current->negative)self->m_bPlayIdle=!self->m_bPlayIdle;
    snapshot();number(self->m_pResourceManager==resources?0:self->m_pResourceManager==alternative?1:self->m_pResourceManager==NULL?98:99);number(eventCalls);number(playingCalls);number(queuedCalls);number(aiCalls);number(stateCalls);number(blendCalls);number(queueCalls);number(lengthCalls);number(removedCalls);number(deadWitness.getObject()==NULL);
    for(unsigned i=0;i<self->m_lAnimationTargets.size();++i){TSafePointer<CBaseUnit>* p=self->m_lAnimationTargets[i];number(p!=NULL);if(p)number(unitID(p->getObject()));}
    for(unsigned i=0;i<5;++i){number(modelCalls[i]);number(safeCount(units[i]));if(i<3)number(static_cast<CCharacter*>(units[i])->m_eAIState);*reinterpret_cast<void***>(units[i])=originalTables[i];}
    *reinterpret_cast<void***>(self)=originalSelfTable;animationDtor(self);
    for(unsigned i=0;i<5;++i){number(safeCount(units[i]));if(safeCount(units[i])!=initialSafe[i])out.issue=autotest::Capture::InvalidReport;}
    number(g_iTotalCountOfObjects-before);resources->m_pLevel=savedLevel;client->m_pPlayer=savedPlayer;
}
void original(void*p,autotest::Capture&out){side(p,out,false);}void candidate(void*p,autotest::Capture&out){side(p,out,true);}
int run(const tlhybrid_host* host,unsigned op)
{
    nativegame::Services* services=new nativegame::Services;menugui::Audio* audio=new menugui::Audio(services->master);menugui::Client* owner=new menugui::Client(*services->settings,services->master,*services->master->m_pSoundManager);(void)audio;
    resources=owner->resources;client=owner->client;finishlevel::initializeCharacterText();units[0]=new CCharacter(resources);units[1]=new CCharacter(resources);units[2]=nativegame::createPlayer(resources);units[3]=new CEquipment(resources);units[4]=new CEquipment(resources);
    for(unsigned i=0;i<4;++i)models[i]=new CGenericModel(NULL,NULL,OGRE_UTILITIES::PRIMITIVE_SPHERE);
    const char* labels[]={"animation_stop_recovery","animation_bool_recovery","animation_play_recovery","animation_bool_composed","animation_play_composed"};const uint64_t addresses[]={0xdd1a30,0xdd2cd0,0xdd3470,0xdd2cd0,0xdd3470};const unsigned counts[]={512,1152,512,288,288};
    autotest::Coverage coverage(labels[op],addresses[op]);
    for(unsigned i=0;i<counts[op];++i){Case c={op,i,false};autotest::Outcome a,b;autotest::runChild(original,&c,a,2000,10000);autotest::runChild(candidate,&c,b,2000,10000);if(coverage.observe(host,a,b)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    animation recovery op%u seed%u status%d/%d issue%u/%u bytes%lu/%lu first%lu\n",op,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);for(unsigned j=at;j<at+32&&j<a.capture.length&&j<b.capture.length;++j)host->log("    byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);coverage.report(host);return 1;}}
    coverage.report(host);Case c={op,111,true};autotest::Outcome a,b;autotest::runChild(original,&c,a,2000,10000);autotest::runChild(candidate,&c,b,2000,10000);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);host->log("    animation negative op%u detected%u\n",op,detected?1:0);return !detected||!a.reportValid||!b.reportValid||a.childStatus||b.childStatus||autotest::incomplete(a)||autotest::incomplete(b);
}
int stopWorker(const tlhybrid_host* host){return run(host,0);}int boolWorker(const tlhybrid_host* host){return run(host,1);}int playWorker(const tlhybrid_host* host){return run(host,2);}int boolComposedWorker(const tlhybrid_host* host){return run(host,3);}int playComposedWorker(const tlhybrid_host* host){return run(host,4);}
}
TL_TEST(animation_stop_recovery){return systems_fixture::isolated(stopWorker,host,180);}
TL_TEST(animation_bool_recovery){return systems_fixture::isolated(boolWorker,host,180);}
TL_TEST(animation_play_recovery){return systems_fixture::isolated(playWorker,host,180);}
TL_TEST(animation_bool_composed){return systems_fixture::isolated(boolComposedWorker,host,180);}
TL_TEST(animation_play_composed){return systems_fixture::isolated(playComposedWorker,host,180);}
