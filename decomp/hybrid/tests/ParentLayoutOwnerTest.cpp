#include "ParentPairs.h"
#include "Detour.h"
#include <map>
#include <string>
#define private public
#define protected public
#include "Layout.h"
#include "Editor.h"
#include "OgreUtilities.h"
#undef private
#undef protected
TL_ORIGINAL(void,parentLayoutOwnerOld,(CLayout*,CEditorScene*),"_ZN7CLayout13SetSceneOwnerEP12CEditorScene")
extern "C" void parentLayoutOwnerNew(CLayout*,CEditorScene*) __asm__("_ZN7CLayout13SetSceneOwnerEP12CEditorScene");
TL_FUNCTION(parentLayoutInit,"_ZN12CEditorScene9InitSceneEP16CResourceManagerj")
TL_FUNCTION(parentLayoutBaseOwner,"_ZN16CSceneNodeObject13SetSceneOwnerEP12CEditorScene")
TL_FUNCTION(parentLayoutRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(parentLayoutCreate,"_ZN14OGRE_UTILITIES12createEntityEPN4Ogre12SceneManagerENS_11EPRIMITIVESENS_10EQUERYMASKEPKc")
TL_FUNCTION(parentLayoutAttach,"_ZN16CSceneNodeObject21sceneNodeAttachEntityEPN4Ogre6EntityE")
extern "C" char parentEntityMaterial[] __asm__("_ZN4Ogre6Entity15setMaterialNameERKSs");
namespace {
autotest::Capture* cap;unsigned seed,creates,attachments,materials,scales,baseCalls;
CLayout* receiver;CEditor* editor;CEditorScene* target;CResourceManager* resources[2];Ogre::Entity* entities[3];Ogre::SceneManager* managers[2];
void number(unsigned v){parentpairs::scalar(*cap,v);}
void check(bool value){number(value);if(!value)cap->issue=autotest::Capture::InvalidReport;}
void init(CEditorScene* self,CResourceManager* r,unsigned n){check(self==receiver&&r==NULL&&n==0);}
void base(CSceneNodeObject* self,CEditorScene* scene){number(1);++baseCalls;check(self==receiver&&scene==target);self->m_pSceneOwner=scene;if(seed%11==1)self->m_pResourceManager=resources[1];}
bool running(CResourceManager* self){number(2);check(baseCalls==1&&self==receiver->m_pResourceManager);return seed%4!=0;}
Ogre::Entity* create(Ogre::SceneManager* manager,OGRE_UTILITIES::EPRIMITIVES primitive,OGRE_UTILITIES::EQUERYMASK mask,const char* name)
{
    number(3);check(manager==receiver->m_pResourceManager->m_pSceneManager);number(primitive);number(mask);cap->addText(std::string(name));
    check(primitive==0&&mask==8&&std::strcmp(name,"gm")==0);++creates;return entities[creates%2];
}
void attach(CSceneNodeObject* self,Ogre::Entity* e){number(4);check(self==receiver&&e==entities[creates%2]);++attachments;self->m_pEntity=seed%7==1?entities[2]:e;if(seed%7==2)self->m_pSceneNode=NULL;}
void material(Ogre::Entity* e,const std::string& name){number(5);check(e==receiver->m_pEntity&&name=="lightBlue");cap->addText(name);++materials;}
struct LayoutWitness:CLayout {
    LayoutWitness():CLayout(NULL,static_cast<ELAYOUT_TYPES>(0)){}
    virtual void setScale(float v){number(6);check(this==receiver&&v==1.0f);parentpairs::scalar(*cap,v);++scales;if(scales==1&&seed%9==1)editor->m_EditorScenes.add(target);if(scales==1&&seed%9==2&&editor->m_EditorScenes.size()>1)editor->m_EditorScenes.removeAt(1);}
};
void side(void* raw,autotest::Capture& out,bool ours)
{
    seed=static_cast<parentpairs::Case*>(raw)->seed;cap=&out;creates=attachments=materials=scales=baseCalls=0;
    LayoutWitness* witness=static_cast<LayoutWitness*>(autotest::allocate(sizeof(LayoutWitness)));receiver=witness;
    {detour::Set setup;TL_REDIRECT(setup,parentLayoutInit,&init);if(setup.failed()){out.issue=autotest::Capture::InvalidReport;return;}new(witness)LayoutWitness;}
    editor=static_cast<CEditor*>(autotest::allocate(sizeof(CEditor)));new(&editor->m_EditorScenes)TArrayList<CEditorScene*>(2);gEditor=editor;
    target=seed%6==0?NULL:reinterpret_cast<CEditorScene*>(autotest::allocate(16));CEditorScene* other=reinterpret_cast<CEditorScene*>(autotest::allocate(16));
    for(unsigned i=0;i<2;++i){resources[i]=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));managers[i]=reinterpret_cast<Ogre::SceneManager*>(autotest::allocate(16));resources[i]->m_pSceneManager=managers[i];}
    for(unsigned i=0;i<3;++i)entities[i]=reinterpret_cast<Ogre::Entity*>(autotest::allocate(16));
    receiver->m_pResourceManager=resources[0];receiver->m_pSceneNode=seed%3?reinterpret_cast<Ogre::SceneNode*>(autotest::allocate(16)):NULL;
    for(unsigned i=0;i<seed%7;++i)editor->m_EditorScenes.add((i+seed/7)%3?target:other);
    detour::Set patches;TL_REDIRECT(patches,parentLayoutBaseOwner,&base);TL_REDIRECT(patches,parentLayoutRunning,&running);TL_REDIRECT(patches,parentLayoutCreate,&create);TL_REDIRECT(patches,parentLayoutAttach,&attach);patches.redirect(parentEntityMaterial,parentEntityMaterial,&material);
    if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    typedef void(*Fn)(CLayout*,CEditorScene*);Fn fn=ours?parentLayoutOwnerNew:parentLayoutOwnerOld;autotest::invoke(out,fn,receiver,target);
    number(baseCalls);number(creates);number(attachments);number(materials);number(scales);check(creates==attachments&&attachments==materials&&materials==scales);
    number(receiver->m_pSceneOwner==target);number(receiver->m_pSceneNode!=NULL);number(editor->m_EditorScenes.size());
    editor->m_EditorScenes.~TArrayList();
    // External engine resources are represented only by identity; no renderer runs.
    receiver->m_pEntity=NULL;receiver->m_pSceneNode=NULL;
}
void a(void*p,autotest::Capture&c){side(p,c,false);}void b(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(parent_layout_scene_owner){return parentpairs::run(host,"parent_layout_scene_owner",(uintptr_t)parentLayoutOwnerOld,144,a,b);}
