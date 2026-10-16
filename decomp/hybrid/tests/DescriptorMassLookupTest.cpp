#include <string>
#include <map>
#include <cstring>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(unsigned,massOld0,(void*,void*,const std::wstring&,void*),"_ZN16CLightDescriptor18GetLightIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned massNew0(void*,void*,const std::wstring&,void*) __asm__("_ZN16CLightDescriptor18GetLightIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(unsigned,massOld1,(void*,void*,const std::wstring&,void*),"_ZN25CPathControllerDescriptor18GetGroupIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned massNew1(void*,void*,const std::wstring&,void*) __asm__("_ZN25CPathControllerDescriptor18GetGroupIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(unsigned,massOld2,(void*,void*,const std::wstring&,void*),"_ZN27CCameraControllerDescriptor18GetGroupIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned massNew2(void*,void*,const std::wstring&,void*) __asm__("_ZN27CCameraControllerDescriptor18GetGroupIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(std::wstring,massOld3,(void*,void*,unsigned,void*),"_ZN22CRandomGroupDescriptor18getQuestStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massNew3(void*,void*,unsigned,void*) __asm__("_ZN22CRandomGroupDescriptor18getQuestStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(std::wstring,massOld4,(void*,void*,unsigned,void*),"_ZN20CCinematicDescriptor22getCinematicStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massNew4(void*,void*,unsigned,void*) __asm__("_ZN20CCinematicDescriptor22getCinematicStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(unsigned,massOld5,(void*,void*,const std::wstring&,void*),"_ZN20CCinematicDescriptor22getCinematicIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned massNew5(void*,void*,const std::wstring&,void*) __asm__("_ZN20CCinematicDescriptor22getCinematicIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(unsigned,massOld6,(void*,void*,const std::wstring&,void*),"_ZN15CItemDescriptor17getItemIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned massNew6(void*,void*,const std::wstring&,void*) __asm__("_ZN15CItemDescriptor17getItemIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(std::wstring,massOld7,(void*,void*,unsigned,void*),"_ZN15CItemDescriptor17getItemStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massNew7(void*,void*,unsigned,void*) __asm__("_ZN15CItemDescriptor17getItemStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(unsigned,massOld8,(void*,void*,const std::wstring&,void*),"_ZN18CMonsterDescriptor20getMonsterIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned massNew8(void*,void*,const std::wstring&,void*) __asm__("_ZN18CMonsterDescriptor20getMonsterIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(std::wstring,massOld9,(void*,void*,unsigned,void*),"_ZN18CMonsterDescriptor20getMonsterStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massNew9(void*,void*,unsigned,void*) __asm__("_ZN18CMonsterDescriptor20getMonsterStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(std::wstring,massOld10,(void*,void*,unsigned,void*),"_ZN26CQuestControllerDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massNew10(void*,void*,unsigned,void*) __asm__("_ZN26CQuestControllerDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(std::wstring,massOld11,(void*,void*,unsigned,void*),"_ZN26CSkillControllerDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massNew11(void*,void*,unsigned,void*) __asm__("_ZN26CSkillControllerDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(std::wstring,massOld12,(void*,void*,unsigned,void*),"_ZN27CCameraControllerDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massNew12(void*,void*,unsigned,void*) __asm__("_ZN27CCameraControllerDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(std::wstring,massOld13,(void*,void*,unsigned,void*),"_ZN22CInteractiveDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massNew13(void*,void*,unsigned,void*) __asm__("_ZN22CInteractiveDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(std::wstring,massOld14,(void*,void*,unsigned,void*),"_ZN25CPathControllerDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massNew14(void*,void*,unsigned,void*) __asm__("_ZN25CPathControllerDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(unsigned,massOld15,(void*,void*,const std::wstring&,void*),"_ZN22CUnitTriggerDescriptor17getItemIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned massNew15(void*,void*,const std::wstring&,void*) __asm__("_ZN22CUnitTriggerDescriptor17getItemIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(std::wstring,massOld16,(void*,void*,unsigned,void*),"_ZN22CUnitTriggerDescriptor17getItemStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massNew16(void*,void*,unsigned,void*) __asm__("_ZN22CUnitTriggerDescriptor17getItemStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(unsigned,massOld17,(void*,void*,const std::wstring&,void*),"_ZN22CUnitTriggerDescriptor25GetTriggerModelIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv")
extern "C" unsigned massNew17(void*,void*,const std::wstring&,void*) __asm__("_ZN22CUnitTriggerDescriptor25GetTriggerModelIDByStringEP12CEditorSceneP17CEditorBaseObjectRKSbIwSt11char_traitsIwESaIwEEPv");
TL_ORIGINAL(std::wstring,massOld18,(void*,void*,unsigned,void*),"_ZN22CUnitTriggerDescriptor25GetTriggerModelStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring massNew18(void*,void*,unsigned,void*) __asm__("_ZN22CUnitTriggerDescriptor25GetTriggerModelStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_FUNCTION(masterTarget,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(groupTarget,"_ZN17CUnitResourceList14getGroupByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(valueTarget,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(literalValueTarget,"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEPKw")
TL_FUNCTION(questSingletonTarget,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(cinemaSingletonTarget,"_ZN11CCinematics12getSingletonEv")
TL_FUNCTION(cinemaTarget,"_ZN11CCinematics12getCinematicEj")
extern "C" void* massBaseTable[] __asm__("_ZTV17CEditorBaseObject");
extern "C" void* massEquipmentTable[] __asm__("_ZTV10CEquipment");
extern "C" void* massMonsterTable[] __asm__("_ZTV8CMonster");
extern "C" void* massQuestTable[] __asm__("_ZTV16CQuestController");
extern "C" void* massSkillTable[] __asm__("_ZTV16CSkillController");
extern "C" void* massCameraTable[] __asm__("_ZTV17CCameraController");
extern "C" void* massInteractTable[] __asm__("_ZTV9CInteract");
extern "C" void* massPathTable[] __asm__("_ZTV15CPathController");
extern "C" void* massTriggerTable[] __asm__("_ZTV12CTriggerUnit");
extern "C" void* massCinematicTable[] __asm__("_ZTV16CCinematicObject");
namespace {
struct Case { unsigned operation,kind,layout,index,category; std::wstring text; };
struct Node {std::wstring name,createAs;};
struct State {
 Node nodes[9];std::map<long long,void*> groups[3];
 uint64_t manager[64],receiver[256],quest[3][32];
 unsigned char resourceMarker,listMarker;
 std::map<std::wstring,void*>* quests;
 autotest::Capture* capture;unsigned calls;
};
State* state;
void invalid(){state->capture->issue=autotest::Capture::InvalidReport;}
void event(unsigned kind,unsigned value){state->capture->add(&kind,4);state->capture->add(&value,4);++state->calls;}
void* master(void* p){if(p!=&state->resourceMarker)invalid();event(1,0);return &state->listMarker;}
void* group(void* p,const std::wstring& name){
 if(p!=&state->listMarker)invalid();unsigned index=3;
 if(name==L"ITEMS")index=0;else if(name==L"MONSTERS")index=1;else if(name==L"PLAYERS"||name==L"PROPS")index=2;
 event(2,index);state->capture->addText(name);if(index==3){invalid();index=0;}return &state->groups[index];
}
Node* node(void* p){for(unsigned i=0;i<9;++i)if(p==&state->nodes[i]){event(3,i);return &state->nodes[i];}invalid();return &state->nodes[0];}
const std::wstring& value(void* p,const std::wstring& key,const std::wstring& fallback){state->capture->addText(key);state->capture->addText(fallback);if(key!=L"NAME")invalid();return node(p)->name;}
const std::wstring& literalValue(void* p,const std::wstring& key,const wchar_t* fallback){state->capture->addText(key);state->capture->addText(std::wstring(fallback));Node* n=node(p);if(key==L"NAME")return n->name;if(key==L"CREATEAS")return n->createAs;invalid();return n->name;}
void* questSingleton(){event(4,0);return state->manager;}
void* cinemaSingleton(){event(5,0);return state->manager;}
void* cinema(void* p,unsigned index){if(p!=state->manager||index>=3)invalid();event(6,index);return &state->nodes[index%3];}
void* table(unsigned kind){switch(kind){case 0:return massEquipmentTable+2;case 1:return massMonsterTable+2;case 2:return massQuestTable+2;case 3:return massSkillTable+2;case 4:return massCameraTable+2;case 5:return massInteractTable+2;case 6:return massPathTable+2;case 7:return massTriggerTable+2;default:return massCinematicTable+2;}}
void side(Case& c,bool ours,autotest::Capture& out){
 State s;state=&s;s.capture=&out;s.calls=0;std::memset(s.manager,0,sizeof(s.manager));std::memset(s.receiver,0,sizeof(s.receiver));std::memset(s.quest,0,sizeof(s.quest));
 const wchar_t* names[]={L"ALPHA",L"BETA",L"OMEGA"};unsigned count=c.layout==0?0:c.layout==1?1:3;
 for(unsigned g=0;g<3;++g)for(unsigned i=0;i<count;++i){unsigned n=g*3+i;s.nodes[n].name=std::wstring(names[i])+static_cast<wchar_t>(L'0'+g);s.nodes[n].createAs=i==1?L"OTHER":L"TRIGGER";s.groups[g][static_cast<long long>(i)*13-7]=&s.nodes[n];}
 detour::Set redirects;TL_REDIRECT(redirects,masterTarget,&master);TL_REDIRECT(redirects,groupTarget,&group);TL_REDIRECT(redirects,valueTarget,&value);TL_REDIRECT(redirects,literalValueTarget,&literalValue);TL_REDIRECT(redirects,questSingletonTarget,&questSingleton);TL_REDIRECT(redirects,cinemaSingletonTarget,&cinemaSingleton);TL_REDIRECT(redirects,cinemaTarget,&cinema);if(redirects.failed()){invalid();return;}
 unsigned objectKind=0,managerOffset=0,categoryOffset=0;std::wstring* category=0;std::wstring* cinemaName=0;bool questMap=false;
 if(c.operation==6){objectKind=0;managerOffset=104;categoryOffset=0;}
 if(c.operation==7){objectKind=0;managerOffset=104;categoryOffset=0;}
 if(c.operation==8){objectKind=1;managerOffset=104;categoryOffset=0;}
 if(c.operation==9){objectKind=1;managerOffset=104;categoryOffset=0;}
 if(c.operation==10){objectKind=2;managerOffset=104;categoryOffset=136;}
 if(c.operation==11){objectKind=3;managerOffset=256;categoryOffset=288;}
 if(c.operation==12){objectKind=4;managerOffset=256;categoryOffset=264;}
 if(c.operation==13){objectKind=5;managerOffset=104;categoryOffset=112;}
 if(c.operation==14){objectKind=6;managerOffset=104;categoryOffset=288;}
 if(c.operation==15){objectKind=7;managerOffset=104;categoryOffset=0;}
 if(c.operation==16){objectKind=7;managerOffset=104;categoryOffset=0;}
 if(c.operation==17){objectKind=7;managerOffset=104;categoryOffset=0;}
 if(c.operation==18){objectKind=7;managerOffset=104;categoryOffset=0;}
 if(c.operation==5)objectKind=8;
 *reinterpret_cast<void**>(s.receiver)=c.kind==1?static_cast<void*>(massBaseTable+2):table(objectKind);
 void* resource=c.kind==3?0:&s.resourceMarker;
 if(managerOffset)std::memcpy(reinterpret_cast<char*>(s.receiver)+managerOffset,&resource,8);
 const wchar_t* categories[]={L"MONSTERS",L"ITEMS",L"PLAYERS",L"PROPS",L"PLAYER",L"UNKNOWN"};
 if(categoryOffset)category=new(reinterpret_cast<char*>(s.receiver)+categoryOffset)std::wstring(categories[c.category%6]);
 if(c.operation==5)cinemaName=new(reinterpret_cast<char*>(s.receiver)+0x68)std::wstring(c.text);
 if(c.operation==3){s.quests=new(reinterpret_cast<char*>(s.manager)+0x40)std::map<std::wstring,void*>;questMap=true;for(unsigned i=0;i<count;++i){new(reinterpret_cast<char*>(s.quest[i])+0x50)std::wstring(names[i]);(*s.quests)[names[i]]=s.quest[i];}}
 if(c.operation==4||c.operation==5)std::memcpy(reinterpret_cast<char*>(s.manager)+0x20,&count,4);
 void* receiver=c.kind==0?0:s.receiver;void* scene=&s.listMarker;void* user=&s.resourceMarker;
 typedef unsigned(*ID)(void*,void*,const std::wstring&,void*);typedef std::wstring(*Name)(void*,void*,unsigned,void*);ID id=0;Name name=0;
 if(c.operation==0){id=ours?massNew0:massOld0;}
 if(c.operation==1){id=ours?massNew1:massOld1;}
 if(c.operation==2){id=ours?massNew2:massOld2;}
 if(c.operation==3){name=ours?massNew3:massOld3;}
 if(c.operation==4){name=ours?massNew4:massOld4;}
 if(c.operation==5){id=ours?massNew5:massOld5;}
 if(c.operation==6){id=ours?massNew6:massOld6;}
 if(c.operation==7){name=ours?massNew7:massOld7;}
 if(c.operation==8){id=ours?massNew8:massOld8;}
 if(c.operation==9){name=ours?massNew9:massOld9;}
 if(c.operation==10){name=ours?massNew10:massOld10;}
 if(c.operation==11){name=ours?massNew11:massOld11;}
 if(c.operation==12){name=ours?massNew12:massOld12;}
 if(c.operation==13){name=ours?massNew13:massOld13;}
 if(c.operation==14){name=ours?massNew14:massOld14;}
 if(c.operation==15){id=ours?massNew15:massOld15;}
 if(c.operation==16){name=ours?massNew16:massOld16;}
 if(c.operation==17){id=ours?massNew17:massOld17;}
 if(c.operation==18){name=ours?massNew18:massOld18;}
 if(id){if(!autotest::beginInvocation(out,id))return;unsigned result=id(scene,receiver,c.text,user);out.callCompleted=1;out.add(&result,4);}else{if(!autotest::beginInvocation(out,name))return;std::wstring result=name(scene,receiver,c.index,user);out.callCompleted=1;out.addText(result);}
 if(c.kind==2&&c.operation>=6){
  bool visits=c.operation==6||c.operation==7||c.operation==8||c.operation==9||c.operation==15||c.operation==16||c.operation==17||(c.operation==18&&c.index!=0);
  if(c.index!=0&&c.operation>=10&&c.operation<=14){if(c.operation==10)visits=c.category==0||c.category==1||c.category==3;else if(c.operation==11)visits=c.category<3;else if(c.operation==12||c.operation==13)visits=c.category<2;else visits=c.category<2;}
  if(visits&&s.calls==0)invalid();
 }
 out.add(&s.calls,4);out.addText(c.text);if(category&&*category!=categories[c.category%6])invalid();
 if(category)category->~basic_string();if(cinemaName)cinemaName->~basic_string();
 if(questMap){for(unsigned i=0;i<count;++i)reinterpret_cast<std::wstring*>(reinterpret_cast<char*>(s.quest[i])+0x50)->~basic_string();s.quests->~map();}
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){
 autotest::Coverage cov(name,address);const unsigned indices[]={0,1,2,3,9,0xffffffffu};
 const wchar_t* values[]={L"",L"ALPHA0",L"BETA0",L"OMEGA0",L"ALPHA1",L"BETA1",L"OMEGA1",L"ALPHA2",L"OMEGA2",L"MONSTERS",L"ITEMS",L"PLAYER",L"POINT",L"DIRECTIONAL",L"SPOTLIGHT",L"UNKNOWN",L"alpha0",L"ALPHA",L"BETA",L"OMEGA",L"PLAYERS",L"PROPS",L"Абя",L"ITEMS "};
 for(unsigned i=0;i<72;++i){Case c;c.operation=operation;c.kind=i<54?2:i<60?0:i<66?1:3;c.layout=(i/6)%3;c.index=indices[i%6];c.category=(i/9)%6;c.text=values[i%24];if(operation==0){const wchar_t* lightNames[]={L"Alpha",L"Additive",L"Multiply",L"",L"alpha",L"UNKNOWN"};c.text=lightNames[i%6];}if(operation==5&&c.kind!=2)c.kind=2;autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log("    massdescriptor op %u case %u exits %d/%d issues %u/%u bytes %lu/%lu\n",operation,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);cov.report(host);return 1;}}
 cov.report(host);return cov.completed==72?0:1;
}
}
TL_TEST(mass_descriptor_5f4d60){return run(host,0,"mass_descriptor_5f4d60",reinterpret_cast<uintptr_t>(&massOld0));}
TL_TEST(mass_descriptor_61c5a0){return run(host,1,"mass_descriptor_61c5a0",reinterpret_cast<uintptr_t>(&massOld1));}
TL_TEST(mass_descriptor_da76d0){return run(host,2,"mass_descriptor_da76d0",reinterpret_cast<uintptr_t>(&massOld2));}
TL_TEST(mass_descriptor_62e990){return run(host,3,"mass_descriptor_62e990",reinterpret_cast<uintptr_t>(&massOld3));}
TL_TEST(mass_descriptor_e66af0){return run(host,4,"mass_descriptor_e66af0",reinterpret_cast<uintptr_t>(&massOld4));}
TL_TEST(mass_descriptor_e700f0){return run(host,5,"mass_descriptor_e700f0",reinterpret_cast<uintptr_t>(&massOld5));}
TL_TEST(mass_descriptor_5e96a0){return run(host,6,"mass_descriptor_5e96a0",reinterpret_cast<uintptr_t>(&massOld6));}
TL_TEST(mass_descriptor_5e9ce0){return run(host,7,"mass_descriptor_5e9ce0",reinterpret_cast<uintptr_t>(&massOld7));}
TL_TEST(mass_descriptor_613880){return run(host,8,"mass_descriptor_613880",reinterpret_cast<uintptr_t>(&massOld8));}
TL_TEST(mass_descriptor_617ae0){return run(host,9,"mass_descriptor_617ae0",reinterpret_cast<uintptr_t>(&massOld9));}
TL_TEST(mass_descriptor_dbe5c0){return run(host,10,"mass_descriptor_dbe5c0",reinterpret_cast<uintptr_t>(&massOld10));}
TL_TEST(mass_descriptor_dc9320){return run(host,11,"mass_descriptor_dc9320",reinterpret_cast<uintptr_t>(&massOld11));}
TL_TEST(mass_descriptor_dabed0){return run(host,12,"mass_descriptor_dabed0",reinterpret_cast<uintptr_t>(&massOld12));}
TL_TEST(mass_descriptor_6670a0){return run(host,13,"mass_descriptor_6670a0",reinterpret_cast<uintptr_t>(&massOld13));}
TL_TEST(mass_descriptor_61dc10){return run(host,14,"mass_descriptor_61dc10",reinterpret_cast<uintptr_t>(&massOld14));}
TL_TEST(mass_descriptor_68d1b0){return run(host,15,"mass_descriptor_68d1b0",reinterpret_cast<uintptr_t>(&massOld15));}
TL_TEST(mass_descriptor_68e500){return run(host,16,"mass_descriptor_68e500",reinterpret_cast<uintptr_t>(&massOld16));}
TL_TEST(mass_descriptor_68e280){return run(host,17,"mass_descriptor_68e280",reinterpret_cast<uintptr_t>(&massOld17));}
TL_TEST(mass_descriptor_68e740){return run(host,18,"mass_descriptor_68e740",reinterpret_cast<uintptr_t>(&massOld18));}
