#ifndef SYSTEMS_NATIVE_EDITOR_CONTROLS_H
#define SYSTEMS_NATIVE_EDITOR_CONTROLS_H
#include <Ogre.h>
#include <deque>
#include "tests/NativeGameServices.h"
#include "tests/SystemsNativeGame.h"
#define private public
#define protected public
#include "Editor.h"
#include "EditorObjectManager.h"
#include "ObjectControl3D.h"
#include "ResourceManager.h"
#undef protected
#undef private
namespace nativeeditor {
TL_ORIGINAL(void,editorCtor,(CEditor*),"_ZN7CEditorC1Ev")
TL_ORIGINAL(void,resourceCtor,(CResourceManager*,Ogre::SceneManager*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,resourceDtor,(CResourceManager*),"_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void,managerCtor,(CEditorObjectManager*,CResourceManager*),"_ZN20CEditorObjectManagerC1EP16CResourceManager")
TL_ORIGINAL(void,managerDtor,(CEditorObjectManager*),"_ZN20CEditorObjectManagerD1Ev")
TL_FUNCTION(initControls,"_ZN16CObjectControl3D12InitControlsEv")
TL_FUNCTION(createDirectory,"_ZN10FILESYSTEM22CreateAppDataDirectoryERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(copyFile,"_Z10copyFileToRKSbIwSt11char_traitsIwESaIwEES4_")
inline bool directory(const std::wstring&){return true;}
inline void copy(const std::wstring&,const std::wstring&){}
inline unsigned& initCalls(){static unsigned count=0;return count;}
inline void init(CObjectControl3D*p){if(!p||!p->m_resources||!p->m_controlsNode)std::abort();++initCalls();}
// Child-worker fixture only. Native C1s construct every owner; InitControls is
// an explicit constructor asset boundary and ends before any tested method.
// This does not certify InitEditor, InitControls, or editor application teardown.
struct Controls {
 SystemsNativeGame game;
 CEditor*previous;CEditor*editor;CResourceManager*resources;CEditorObjectManager*manager;CObjectControl3D*control;
 Controls(nativegame::Services&services):game(Ogre::Root::getSingletonPtr(),services.settings),previous(gEditor),editor(NULL),resources(NULL),manager(NULL),control(NULL){
  editor=static_cast<CEditor*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEditor),0,0,0));
  {detour::Set setup;TL_REDIRECT(setup,createDirectory,&directory);TL_REDIRECT(setup,copyFile,&copy);if(setup.failed())std::abort();editorCtor(editor);}
  gEditor=editor;
  // The native InitEditor writes these actual links at 71c6c0 (+58),
  // 71c6d6 (+50), 71c731 (+128), and 71c76a (+120).
  editor->m_pEditorResourceManager=static_cast<iEditorResourceManager*>(game.game);editor->m_pSettings=services.settings;
  resources=static_cast<CResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CResourceManager),0,0,0));resourceCtor(resources,services.scene);editor->m_pUnknown128=resources;
  manager=static_cast<CEditorObjectManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEditorObjectManager),0,0,0));initCalls()=0;
  {detour::Set setup;TL_REDIRECT(setup,initControls,&init);if(setup.failed())std::abort();managerCtor(manager,resources);}
  editor->m_pObjectManager=manager;control=manager->m_pObjectControl;if(initCalls()!=1||!control)std::abort();
 }
 ~Controls(){
  managerDtor(manager);Ogre::NedAllocImpl::deallocBytes(manager);editor->m_pObjectManager=NULL;
  resourceDtor(resources);Ogre::NedAllocImpl::deallocBytes(resources);editor->m_pUnknown128=NULL;editor->m_pEditorResourceManager=NULL;editor->m_pSettings=NULL;
  // Keep the native editor itself alive until the private worker exits, as in
  // StateUndoFamilyTest. Its full application destructor is outside this seam.
  gEditor=previous;
 }
private:Controls(const Controls&);Controls&operator=(const Controls&);
};
}
#endif
