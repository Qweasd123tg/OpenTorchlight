#include "FinishLevelFixture.h"
#include "Automap.h"
#include "Settings.h"
#include "QuestManager.h"
TL_ORIGINAL(void,sceneOld0,(CLevel*),"_ZN6CLevel13toggleAutomapEv")
extern "C" void sceneNew0(CLevel*) __asm__("_ZN6CLevel13toggleAutomapEv");
TL_ORIGINAL(void,sceneOld1,(CLevel*),"_ZN6CLevel21updateMaterialAmbientEv")
extern "C" void sceneNew1(CLevel*) __asm__("_ZN6CLevel21updateMaterialAmbientEv");
TL_ORIGINAL(void,sceneOld2,(CLevel*,std::wstring,bool,ELevelEntryType,std::vector<std::wstring>*,std::wstring),"_ZN6CLevel14loadRoomLayoutESbIwSt11char_traitsIwESaIwEEb15ELevelEntryTypePSt6vectorIS3_SaIS3_EES3_")
extern "C" void sceneNew2(CLevel*,std::wstring,bool,ELevelEntryType,std::vector<std::wstring>*,std::wstring) __asm__("_ZN6CLevel14loadRoomLayoutESbIwSt11char_traitsIwESaIwEEb15ELevelEntryTypePSt6vectorIS3_SaIS3_EES3_");
TL_ORIGINAL(void,sceneOld3,(CLevel*),"_ZN6CLevel14updateNPCIconsEv")
extern "C" void sceneNew3(CLevel*) __asm__("_ZN6CLevel14updateNPCIconsEv");
TL_FUNCTION(sceneMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(sceneSetInt,"_ZN20CDynamicPropertyFile6SetIntEji")
TL_FUNCTION(sceneVisible,"_ZN8CAutomap10setVisibleEb")
TL_FUNCTION(sceneFullscreen,"_ZN8CAutomap13setFullscreenEb")
TL_FUNCTION(sceneObjects,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEEP10TArrayListIP17CEditorBaseObjectE")
TL_FUNCTION(sceneAmbient,"_ZN13CGenericModel10setAmbientERN4Ogre11ColourValueE")
TL_FUNCTION(sceneModelLoad,"_ZN13CGenericModel9loadModelESbIwSt11char_traitsIwESaIwEES3_bbb")
TL_FUNCTION(sceneTemplateLoad,"_ZN18CLevelTemplateData4loadEPKw")
TL_FUNCTION(sceneInitScene,"_ZN12CEditorScene9InitSceneEP16CResourceManagerj")
TL_FUNCTION(sceneEnabled,"_ZN12CEditorScene10setEnabledEb")
TL_FUNCTION(sceneLayoutVisible,"_ZN7CLayout10setVisibleEb")
TL_FUNCTION(sceneLayoutLoad,"_ZN7CLayout14loadLayoutFileERKSbIwSt11char_traitsIwESaIwEEbP13CTimerStaticsbbj")
TL_FUNCTION(sceneMerge,"_ZN6CLevel24mergeLayoutsForRoomPieceERKSbIwSt11char_traitsIwESaIwEEP7CLayout")
TL_FUNCTION(sceneLoad,"_ZN6CLevel14loadRoomLayoutEP18CLevelTemplateDatab15ELevelEntryTypePSt6vectorISbIwSt11char_traitsIwESaIwEESaIS7_EES7_")
TL_FUNCTION(sceneIcon,"_ZN13CQuestManager16calculateNPCIconEP10CCharacter")
TL_FUNCTION(sceneISA,"_ZN16CResourceManager3ISAEN9UNITTYPES10EUNITTYPESES1_")
TL_FUNCTION(sceneTheme,"_ZN9CBaseUnit12addUnitThemeERKSbIwSt11char_traitsIwESaIwEE")
namespace finishscene {
// External client/player/automap/master context is a typed scalar ABI view.
// Native lifetimes of those world subsystems are outside these Level cases.
template<class T>struct View{union{long double alignment;char bytes[sizeof(T)];}storage;View(){std::memset(&storage,0,sizeof storage);}T*get(){return reinterpret_cast<T*>(storage.bytes);}};
struct Case{unsigned target,variant;};static unsigned variant,target;static bool record;static std::vector<unsigned>trace;static CMasterResourceManager*master;static CRoomPiece*pieces[2];static CEditorBaseObject*foreignObject;static CResourceManager*resources;
static void n(unsigned x){if(record)trace.push_back(x);}static void scalar(float x){unsigned b;std::memcpy(&b,&x,4);n(b);}static void text(const std::wstring&s){n(s.size());for(unsigned i=0;i<s.size();++i)n(unsigned(s[i]));}
static CMasterResourceManager*singleton(){return master;}static bool setInt(CDynamicPropertyFile*p,unsigned index,int value){n(10);n(p==NULL);n(index);n(unsigned(value));return true;}
static void visible(CAutomap*p,bool value){n(20);n(value);p->m_bVisible=value;}static void fullscreen(CAutomap*p,bool value){n(30);n(value);p->m_bFullscreen=value;}
static void objects(CEditorScene*scene,const std::wstring&name,TArrayList<CEditorBaseObject*>*out){n(40);n(unsigned(scene->getGuid()));text(name);if(name==L"Scene Object"){if((variant+unsigned(scene->getGuid()))%3==0)out->add(foreignObject);}else if(name==L"Room Piece"){for(unsigned i=0;i<(variant+unsigned(scene->getGuid()))%3;++i)out->add(pieces[i]);out->add(NULL);if(variant%2)out->add(foreignObject);}}
static void ambient(CGenericModel*model,Ogre::ColourValue&value){n(50);text(model->m_sModelPath);scalar(value.r);scalar(value.g);scalar(value.b);scalar(value.a);}
static void modelLoad(CGenericModel*,std::wstring,std::wstring,bool,bool,bool){}
static void templateLoad(CLevelTemplateData*p,const wchar_t*file){n(60);text(file?std::wstring(file):L"<null>");p->m_levelName=file?file:L"no filename";}
static void init(CEditorScene*p,CResourceManager*r,unsigned flags){n(70);n(r==resources);n(flags);p->m_pResourceManager=r;}
static void enabled(CEditorScene*p,bool value){n(80);n(value);p->m_bEnabled=value;}static void layoutVisible(CLayout*p,bool value){n(90);n(value);p->m_bVisible=value;}
static void layoutLoad(CLayout*p,const std::wstring&file,bool merge,CTimerStatics*t,bool a,bool b,unsigned flags){n(100);text(file);n(merge);n(t!=NULL);n(a);n(b);n(flags);n(p->m_bEnabled);n(resources->m_bFlag2);}
static void merge(CLevel*,const std::wstring&name,CLayout*p){n(110);text(name);n(p->m_bEnabled);n(resources->m_bFlag2);}
static void load(CLevel*p,CLevelTemplateData*t,bool merged,ELevelEntryType entry,std::vector<std::wstring>*extra,std::wstring waypoint){n(120);n(t!=NULL);n(merged);n(unsigned(entry));n(extra?extra->size():~0u);if(extra)for(unsigned i=0;i<extra->size();++i)text((*extra)[i]);text(waypoint);n(resources->m_bFlag2);n(p->m_RoomScenes.size());if(t)n(t==p->m_pLevelTemplateData);}
static long long icon(CQuestManager*,CCharacter*p){n(130);n(unsigned(p->getGuid()));const long long results[]={0,1,256,257};return results[(variant+unsigned(p->getGuid()))%4];}
static int isa(CResourceManager*,UNITTYPES::EUNITTYPES a,UNITTYPES::EUNITTYPES b){n(140);n(unsigned(a));n(unsigned(b));return a==b;}
static void theme(CBaseUnit*p,const std::wstring&name){n(150);n(unsigned(p->getGuid()));text(name);}
static void wide(uintptr_t a){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(a),8);if(!p)new(reinterpret_cast<void*>(a))std::wstring;}
static void side(void*input,autotest::Capture&out,bool candidate){
 Case c=*static_cast<Case*>(input);variant=c.variant;target=c.target;record=false;trace.clear();finishlevel::Fixture f;resources=&f.resources;wide(0x1495cc8);wide(0x1492210);
 View<CMasterResourceManager>masterView;master=masterView.get();master->m_pSettings=NULL;View<CAutomap>mapView;CAutomap*map=mapView.get();map->m_bVisible=c.variant%3!=0;map->m_bFullscreen=c.variant%3==2;f.level.m_automap=c.variant%5?map:NULL;KSETTINGS_AUTOMAP=137;
 View<CGameClient>clientView;View<CPlayer>playerView;CGameClient*client=clientView.get();CPlayer*player=playerView.get();client->m_pPlayer=c.variant%5?player:NULL;player->m_questManager=NULL;f.level.m_pGameClient=c.variant%7?client:NULL;
 detour::Set boundary;TL_REDIRECT(boundary,sceneMaster,&singleton);TL_REDIRECT(boundary,sceneSetInt,&setInt);TL_REDIRECT(boundary,sceneVisible,&visible);TL_REDIRECT(boundary,sceneFullscreen,&fullscreen);TL_REDIRECT(boundary,sceneObjects,&objects);TL_REDIRECT(boundary,sceneAmbient,&ambient);TL_REDIRECT(boundary,sceneModelLoad,&modelLoad);TL_REDIRECT(boundary,sceneTemplateLoad,&templateLoad);TL_REDIRECT(boundary,sceneInitScene,&init);TL_REDIRECT(boundary,sceneEnabled,&enabled);TL_REDIRECT(boundary,sceneLayoutVisible,&layoutVisible);TL_REDIRECT(boundary,sceneLayoutLoad,&layoutLoad);TL_REDIRECT(boundary,sceneMerge,&merge);TL_REDIRECT(boundary,sceneLoad,&load);TL_REDIRECT(boundary,sceneIcon,&icon);TL_REDIRECT(boundary,sceneISA,&isa);TL_REDIRECT(boundary,sceneTheme,&theme);if(boundary.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 CLevelTemplateData*oldTemplate=new CLevelTemplateData(NULL);oldTemplate->m_state761=c.variant%2;oldTemplate->m_materialAmbientColorR=float(c.variant%5)*0.25f;oldTemplate->m_materialAmbientColorG=-0.5f;oldTemplate->m_materialAmbientColorB=0.75f;oldTemplate->m_materialAmbientColorA=1.0f;TSafePointer<CLevelTemplateData>oldWitness;oldWitness.setObject(oldTemplate);f.level.m_pLevelTemplateData=c.variant%4||c.target==1?oldTemplate:NULL;
 CEditorScene scene0(L"room0"),scene1(L"room1"),scene2(L"room2");CEditorScene*scenes[]={&scene0,&scene1,&scene2};for(unsigned i=0;i<c.variant%4;++i){scenes[i]->setGuid(i);f.level.m_RoomScenes.add(scenes[i]);}CEditorBaseObject foreign;foreignObject=&foreign;
 CRoomPiece*piece0=NULL,*piece1=NULL;CGenericModel*model0=NULL,*model1=NULL;if(c.target==1){piece0=new CRoomPiece(NULL);piece1=new CRoomPiece(NULL);model0=new CGenericModel(NULL,NULL,L"model0",L"fixture",false);model1=new CGenericModel(NULL,NULL,L"model1",L"fixture",false);model0->m_sModelPath=L"model0";model1->m_sModelPath=L"model1";piece0->m_pGenericModel=c.variant%2?model0:NULL;piece1->m_pGenericModel=c.variant%3?model1:NULL;}pieces[0]=piece0;pieces[1]=piece1;
 CCharacter ch0(NULL),ch1(NULL),ch2(NULL);CCharacter*characters[]={&ch0,&ch1,&ch2};unsigned types[]={0x7f,0x82,0x86,0x85,0x84,0x29,0x1d};for(unsigned i=0;i<3;++i){characters[i]->setGuid(10+i);characters[i]->m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>(types[(variant+i)%7]);characters[i]->m_bBaseUnitFlag190=(variant+i)%9==0;characters[i]->m_forcedHidden=(variant+i)%3==0;characters[i]->m_bEnabled=(variant+i)%2;characters[i]->m_pResourceManager=&f.resources;if(i<c.variant%4)finishlevel::prepend(f.level.m_pCharacters,characters[i]);}if(c.variant%3==0)finishlevel::prepend<CCharacter*>(f.level.m_pCharacters,NULL);
 // The load target appends a new owning layout, while the preceding scenes are borrowed.
 unsigned borrowed=f.level.m_RoomScenes.size();std::wstring filename=c.variant%3?L"fixture/level_Ω.dat":L"",waypoint=c.variant%2?L"entry/К":L"";std::vector<std::wstring>extra;extra.push_back(L"one");if(c.variant%2)extra.push_back(L"two");std::vector<std::wstring>*extras=c.variant%3?&extra:NULL;
 trace.clear();record=true;
 switch(c.target){
 case 0:if(candidate)autotest::invoke<void(*)(CLevel*),CLevel*>(out,sceneNew0,&f.level);else autotest::invoke<void(*)(CLevel*),CLevel*>(out,sceneOld0,&f.level);break;
 case 1:if(candidate)autotest::invoke<void(*)(CLevel*),CLevel*>(out,sceneNew1,&f.level);else autotest::invoke<void(*)(CLevel*),CLevel*>(out,sceneOld1,&f.level);break;
 case 2:if(candidate)autotest::invoke<void(*)(CLevel*,std::wstring,bool,ELevelEntryType,std::vector<std::wstring>*,std::wstring),CLevel*,std::wstring,bool,ELevelEntryType,std::vector<std::wstring>*,std::wstring>(out,sceneNew2,&f.level,filename,bool(c.variant%2),static_cast<ELevelEntryType>(c.variant%5),extras,waypoint);else autotest::invoke<void(*)(CLevel*,std::wstring,bool,ELevelEntryType,std::vector<std::wstring>*,std::wstring),CLevel*,std::wstring,bool,ELevelEntryType,std::vector<std::wstring>*,std::wstring>(out,sceneOld2,&f.level,filename,bool(c.variant%2),static_cast<ELevelEntryType>(c.variant%5),extras,waypoint);break;
 case 3:if(candidate)autotest::invoke<void(*)(CLevel*),CLevel*>(out,sceneNew3,&f.level);else autotest::invoke<void(*)(CLevel*),CLevel*>(out,sceneOld3,&f.level);break;
 }
 record=false;finishlevel::number(out,trace.size());for(unsigned i=0;i<trace.size();++i)finishlevel::number(out,trace[i]);finishlevel::number(out,map->m_bVisible);finishlevel::number(out,map->m_bFullscreen);finishlevel::number(out,resources->m_bFlag2);finishlevel::number(out,oldWitness.getObject()!=NULL);finishlevel::number(out,f.level.m_RoomScenes.size());if(f.level.m_pLevelTemplateData){finishlevel::number(out,f.level.m_pLevelTemplateData->m_state761);out.addText(f.level.m_pLevelTemplateData->m_levelName);}
 for(unsigned i=borrowed;i<f.level.m_RoomScenes.size();++i)delete f.level.m_RoomScenes[i];f.level.m_RoomScenes.m_nCount=borrowed;
 if(f.level.m_pLevelTemplateData && f.level.m_pLevelTemplateData!=oldWitness.getObject())delete f.level.m_pLevelTemplateData;f.level.m_pLevelTemplateData=NULL;if(oldWitness.getObject())delete oldWitness.getObject();
 if(piece0){piece0->m_pGenericModel=NULL;piece1->m_pGenericModel=NULL;delete piece0;delete piece1;}delete model0;delete model1;for(unsigned i=0;i<3;++i)characters[i]->m_pResourceManager=NULL;
}
static void original(void*p,autotest::Capture&o){side(p,o,false);}static void ours(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(finish_level_scene_938830){autotest::Coverage coverage("finish_level_scene_938830",0x938830);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishscene::Case c={0,n};autotest::compareCase(finishscene::original,finishscene::ours,&c,stats,host,"scene",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_scene_950a40){autotest::Coverage coverage("finish_level_scene_950a40",0x950a40);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishscene::Case c={1,n};autotest::compareCase(finishscene::original,finishscene::ours,&c,stats,host,"scene",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_scene_9622f0){autotest::Coverage coverage("finish_level_scene_9622f0",0x9622f0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishscene::Case c={2,n};autotest::compareCase(finishscene::original,finishscene::ours,&c,stats,host,"scene",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
TL_TEST(finish_level_scene_95c3d0){autotest::Coverage coverage("finish_level_scene_95c3d0",0x95c3d0);autotest::Stats stats={0,0,0,0};for(unsigned n=0;n<96;++n){finishscene::Case c={3,n};autotest::compareCase(finishscene::original,finishscene::ours,&c,stats,host,"scene",n,&coverage);}coverage.report(host);return stats.different||stats.incomplete||coverage.missing||coverage.completed!=96;}
