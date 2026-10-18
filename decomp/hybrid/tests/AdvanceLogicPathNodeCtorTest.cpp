#include "ParentPairs.h"
#include "Detour.h"
#include "PathNode.h"
#include "TextEvent.h"
#include "GameUI.h"
#include "ResourceManager.h"
#include "OgreUtilities.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
TL_ORIGINAL(void,oldCtor,(CPathNode*,CPathController*,CResourceManager*),"_ZN9CPathNodeC1EP15CPathControllerP16CResourceManager")
extern "C" void newCtor(CPathNode*,CPathController*,CResourceManager*) __asm__("_ZN9CPathNodeC1EP15CPathControllerP16CResourceManager");
TL_FUNCTION(baseCtor,"_ZN19CPositionableObjectC2EP16CResourceManagerPN4Ogre12SceneManagerE")
TL_FUNCTION(baseDtor,"_ZN19CPositionableObjectD2Ev")
TL_FUNCTION(createEntity,"_ZN14OGRE_UTILITIES12createEntityEPN4Ogre12SceneManagerENS_11EPRIMITIVESENS_10EQUERYMASKEPKc")
TL_FUNCTION(attachEntity,"_ZN16CSceneNodeObject21sceneNodeAttachEntityEPN4Ogre6EntityE")
TL_FUNCTION(visible,"_ZN9CPathNode10setVisibleEb")
TL_FUNCTION(position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(singleton,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(textEvent,"_ZN7CGameUI18getTextEventObjectERKN4Ogre7Vector3ERKSsffN5CEGUI6colourES7_b")
extern "C" char materialAddress[] __asm__("_ZN4Ogre6Entity15setMaterialNameERKSs");
namespace {
autotest::Capture*cap;unsigned seed;CPathNode*self;CResourceManager*resource;CPathController*controller;Ogre::SceneManager*manager;CTextEvent*event;std::wstring retained;
void mark(unsigned value){parentpairs::scalar(*cap,value);if(seed>=90 && 1+(seed-90)%7==value)throw int(value);}
struct Node:Ogre::SceneNode{Node():Ogre::SceneNode(NULL){}virtual void showBoundingBox(bool b){parentpairs::scalar(*cap,30);parentpairs::scalar(*cap,b);}virtual void setScale(float x,float y,float z){parentpairs::scalar(*cap,31);parentpairs::scalar(*cap,x);parentpairs::scalar(*cap,y);parentpairs::scalar(*cap,z);}};Node*node;
struct Entity:Ogre::Entity{Entity():Ogre::Entity(){}};Entity*entity;
void construct(CPositionableObject*p,CResourceManager*r,Ogre::SceneManager*m){parentpairs::scalar(*cap,10);parentpairs::scalar(*cap,r==resource);parentpairs::scalar(*cap,m==NULL);new(static_cast<CEditorBaseObject*>(p))CEditorBaseObject;std::memcpy(reinterpret_cast<char*>(p)+0x58,&node,sizeof(node));std::memcpy(reinterpret_cast<char*>(p)+0x68,&r,sizeof(r));}
void destroy(CPositionableObject*p){parentpairs::scalar(*cap,11);parentpairs::scalar(*cap,retained.empty()?0:*reinterpret_cast<const int*>(reinterpret_cast<const char*>(retained.data())-8));p->CEditorBaseObject::~CEditorBaseObject();}
Ogre::Entity*create(Ogre::SceneManager*m,OGRE_UTILITIES::EPRIMITIVES primitive,OGRE_UTILITIES::EQUERYMASK mask,const char*name){parentpairs::scalar(*cap,m==manager);parentpairs::scalar(*cap,primitive);parentpairs::scalar(*cap,mask);cap->addText(std::string(name));mark(1);return entity;}
void material(Ogre::Entity*e,const std::string&name){parentpairs::scalar(*cap,e==entity);cap->addText(name);mark(2);}
void attach(CSceneNodeObject*p,Ogre::Entity*e){parentpairs::scalar(*cap,p==self);parentpairs::scalar(*cap,e==entity);parentpairs::scalar(*cap,entity->getCastShadows());self->m_sText=retained;mark(3);}
void show(CPathNode*p,bool b){parentpairs::scalar(*cap,p==self);parentpairs::scalar(*cap,b);parentpairs::scalar(*cap,p->m_pPathController==controller);parentpairs::scalar(*cap,p->m_iReservedState);parentpairs::scalar(*cap,p->m_iReservedValue);cap->addText(p->m_sText);mark(4);}
Ogre::Vector3 getPosition(CPositionableObject*p,bool world){parentpairs::scalar(*cap,p==self);parentpairs::scalar(*cap,world);mark(5);return Ogre::Vector3(seed*0.25f,-float(seed),3.0f);}
CGameUI*getUI(){mark(6);return reinterpret_cast<CGameUI*>(manager);}
CTextEvent*getText(CGameUI*p,const Ogre::Vector3&pos,const std::string&text,float a,float b,CEGUI::colour c,CEGUI::colour d,bool flag){parentpairs::scalar(*cap,p==reinterpret_cast<CGameUI*>(manager));parentpairs::scalar(*cap,pos.x);parentpairs::scalar(*cap,pos.y);parentpairs::scalar(*cap,pos.z);cap->addText(text);parentpairs::scalar(*cap,a);parentpairs::scalar(*cap,b);parentpairs::scalar(*cap,c.getRed());parentpairs::scalar(*cap,c.getGreen());parentpairs::scalar(*cap,c.getBlue());parentpairs::scalar(*cap,c.getAlpha());parentpairs::scalar(*cap,d.getRed());parentpairs::scalar(*cap,d.getGreen());parentpairs::scalar(*cap,d.getBlue());parentpairs::scalar(*cap,d.getAlpha());parentpairs::scalar(*cap,flag);mark(7);return seed&1?event:NULL;}
void side(void*raw,autotest::Capture&out,bool ours){cap=&out;seed=static_cast<parentpairs::Case*>(raw)->seed;retained=std::wstring(40+seed%9,L'P');// Ogre collaborators remain alive until the isolated child exits.
Node*actualNode=new Node;node=actualNode;Entity*actualEntity=new Entity;entity=actualEntity;unsigned long long memory[(sizeof(CPathNode)+7)/8];std::memset(memory,0xa5,sizeof(memory));self=reinterpret_cast<CPathNode*>(memory);unsigned long long resources[(sizeof(CResourceManager)+7)/8]={0},eventMemory[(sizeof(CTextEvent)+7)/8]={0};resource=reinterpret_cast<CResourceManager*>(resources);event=reinterpret_cast<CTextEvent*>(eventMemory);manager=reinterpret_cast<Ogre::SceneManager*>(eventMemory);controller=reinterpret_cast<CPathController*>(eventMemory);std::memcpy(reinterpret_cast<char*>(resource)+0x10,&manager,sizeof(manager));detour::Set patches;TL_REDIRECT(patches,baseCtor,&construct);TL_REDIRECT(patches,baseDtor,&destroy);TL_REDIRECT(patches,createEntity,&create);TL_REDIRECT(patches,attachEntity,&attach);TL_REDIRECT(patches,visible,&show);TL_REDIRECT(patches,position,&getPosition);TL_REDIRECT(patches,singleton,&getUI);TL_REDIRECT(patches,textEvent,&getText);patches.redirect(materialAddress,materialAddress,&material);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef void(*Fn)(CPathNode*,CPathController*,CResourceManager*);Fn fn=ours?newCtor:oldCtor;if(!autotest::beginInvocation(out,fn))return;bool threw=false;try{fn(self,controller,resource);out.callCompleted=1;}catch(int value){threw=true;parentpairs::scalar(out,value);}if(threw!=(seed>=90))out.issue=autotest::Capture::InvalidReport;parentpairs::scalar(out,threw);if(!threw){parentpairs::scalar(out,self->m_pTextEvent==(seed&1?event:NULL));parentpairs::scalar(out,event->m_Flag82);parentpairs::scalar(out,*reinterpret_cast<float*>(reinterpret_cast<char*>(self)+0x90));parentpairs::scalar(out,*reinterpret_cast<float*>(reinterpret_cast<char*>(self)+0x94));parentpairs::scalar(out,*reinterpret_cast<float*>(reinterpret_cast<char*>(self)+0x98));self->m_sText.~basic_string();destroy(self);}parentpairs::scalar(out,*reinterpret_cast<const int*>(reinterpret_cast<const char*>(retained.data())-8));retained.clear();}
void a(void*p,autotest::Capture&c){side(p,c,false);}void b(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(advance_logic_path_ctor){return parentpairs::run(host,"advance_logic_path_ctor",(uintptr_t)oldCtor,90,a,b);}

TL_TEST(advance_logic_path_ctor_unwind)
{
    for(unsigned i=90;i<97;++i){
        parentpairs::Case input={i};
        autotest::Outcome& x=autotest::g_outcomes[0];
        autotest::Outcome& y=autotest::g_outcomes[1];
        autotest::runChild(a,&input,x);autotest::runChild(b,&input,y);
        if(x.childStatus!=0||y.childStatus!=0||!x.reportValid||!y.reportValid||
           x.capture.issue||y.capture.issue||x.capture.callStarted!=1||y.capture.callStarted!=1||
           x.capture.callCompleted||y.capture.callCompleted||x.capture.callTarget!=(uintptr_t)oldCtor||
           !host->comparison_pair(x.capture.callTarget,y.capture.callTarget)||
           x.capture.length!=y.capture.length||std::memcmp(x.capture.data,y.capture.data,x.capture.length))return 1;
    }
    host->log("    expected PathNode constructor unwinds: 7 equal pairs, excluded from normal coverage\n");
    return 0;
}
