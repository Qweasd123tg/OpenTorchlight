#include "FinishLevelFixture.h"
#include "NativeConsoleFixture.h"
#include "Layout.h"
#include "DescriptorManager.h"
#include "GenericModel.h"
#include <clocale>
TL_ORIGINAL(void,coOriginal,(CConsole*,std::wstring,std::wstring),"_ZN8CConsole18createObjectByNameESbIwSt11char_traitsIwESaIwEES3_")
extern "C" void coCandidate(CConsole*,std::wstring,std::wstring) __asm__("_ZN8CConsole18createObjectByNameESbIwSt11char_traitsIwESaIwEES3_");
TL_FUNCTION(coLookup,"_ZN12CEditorScene26GetDescriptorInSceneByNameEPKwb")
TL_FUNCTION(coCreate,"_ZN12CEditorScene24CreateObjectByDescriptorEP11CDescriptorP17CEditorBaseObjectS3_b")
TL_FUNCTION(coLog,"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(coLoad,"_ZN13CGenericModel9loadModelESbIwSt11char_traitsIwESaIwEES3_bbb")
namespace {
autotest::Capture*output;CSettings*settings;Ogre::SceneManager*scene;CResourceManager*resources;CConsole*console;CEditorScene*owner;unsigned seed,created,logs,deleted;std::vector<CGenericModel*>models;std::vector<TSafePointer<CDescriptor>*>descriptors;TSafePointer<CLayout>layoutWeak;
void number(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){number(s.size());output->add(s.data(),s.size()*4);}
std::wstring name(unsigned i){switch(i%4){case 0:return L"fixture type";case 1:return L"Тип 漢字";case 2:return L"";default:return std::wstring(L"before\0after",12);}}
struct Descriptor: CDescriptor {
 Descriptor(unsigned i):CDescriptor(0){setDescriptorName(name(i));CEditorBaseObject::m_sName=L"different inherited name";}
 ~Descriptor(){++deleted;}
 CEditorBaseObject*CreateObject(CEditorScene*){return NULL;}
};
void addDescriptor(CDescriptorManager*m,unsigned i){Descriptor*p=new Descriptor(i);m->m_descriptors.push_back(p);TSafePointer<CDescriptor>*weak=new TSafePointer<CDescriptor>;weak->setObject(p);descriptors.push_back(weak);}
CDescriptor*lookup(CEditorScene*p,const wchar_t*n,bool create){number(10);wide(n);number(create);owner=p;layoutWeak.setObject(dynamic_cast<CLayout*>(p));number(layoutWeak.getObject()!=NULL);number(p->getResourceManager()==resources);CDescriptorManager*m=p->getDescriptorManager();number(m!=NULL);number(m->m_descriptors.size());unsigned count=seed/7%4;if(seed/28%3!=0)count=1;for(unsigned i=0;i<count;++i)addDescriptor(m,seed+i);return seed/28%3?m->m_descriptors[0]:NULL;}
void load(CGenericModel*p,std::wstring path,std::wstring group,bool a,bool b,bool c){number(11);number(p!=NULL);wide(path);wide(group);number(a);number(b);number(c);}
CEditorBaseObject*create(CEditorScene*p,CDescriptor*d,CEditorBaseObject*parent,CEditorBaseObject*own,bool load){number(12);number(p==owner);number(d==owner->getDescriptorManager()->m_descriptors[0]);number(parent==NULL);number(own==NULL);number(load);++created;CGenericModel*model=new CGenericModel(resources,resources->m_pSceneManager,L"",L"",false);models.push_back(model);return model;}
void log(CConsole*p,std::wstring text){number(13);number(p==console);wide(text);if(logs++==0&&seed/28%3==0&&(seed/84&1))addDescriptor(owner->getDescriptorManager(),seed+17);}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;created=logs=deleted=0;models.clear();descriptors.clear();layoutWeak.setObject(NULL);owner=NULL;CStringTranslate translate(L"");menugui::Fixture gui(*settings,scene);finishlevel::Fixture world;resources=&world.resources;resources->m_pSceneManager=gui.nativeClient.scenes[0];menugui::Console con(gui);console=con.p;console->m_resources=resources;console->m_gameClient=gui.nativeClient.client;CPlayer*player=nativegame::createPlayer(resources);gui.nativeClient.client->m_pPlayer=player;
 const wchar_t*counts[]={L"0",L"1",L"2",L"3",L"100001",L"-1",L"x"};std::wstring count=counts[seed%7];std::wstring requested=seed/28%3==2?L"Generic Model":name(seed/7);
 if(seed>=168){if(seed&1)resources->m_pLevel=NULL;else gui.nativeClient.client->m_pPlayer=NULL;}
 detour::Set calls;TL_REDIRECT(calls,coLookup,&lookup);TL_REDIRECT(calls,coCreate,&create);TL_REDIRECT(calls,coLog,&log);TL_REDIRECT(calls,coLoad,&load);if(calls.failed())std::abort();
 typedef void(*Fn)(CConsole*,std::wstring,std::wstring);Fn fn=ours?coCandidate:coOriginal;if(!autotest::beginInvocation(out,fn))return;fn(console,requested,count);out.callCompleted=1;number(created);number(logs);number(deleted);number(layoutWeak.getObject()==NULL);number(descriptors.size());for(unsigned i=0;i<descriptors.size();++i)number(descriptors[i]->getObject()==NULL);
 // Keep mutation controls bounded even if they deliberately omit the native scope destructor.
 calls.restore();if(layoutWeak.getObject())delete layoutWeak.getObject();for(unsigned i=0;i<descriptors.size();++i)delete descriptors[i];descriptors.clear();for(unsigned i=0;i<models.size();++i)delete models[i];models.clear();gui.nativeClient.client->m_pPlayer=NULL;nativegame::destroyPlayer(player);resources->m_pLevel=&world.level;
}
int run(const tlhybrid_host*host){std::string old=std::setlocale(LC_CTYPE,NULL);if(!std::setlocale(LC_CTYPE,"C.UTF-8"))return 1;int result;{tlheadless::Environment env;env.loadGameSkin();CEGUI::SchemeManager::getSingleton().loadScheme("media/ui/WindowsLook.scheme");nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;result=smallmass::run(host,0,"complete_ui_console_createobject",0xaf1950,&side,184);}std::setlocale(LC_CTYPE,old.c_str());return result;}
}
TL_TEST(complete_ui_console_createobject){return run(host);}
