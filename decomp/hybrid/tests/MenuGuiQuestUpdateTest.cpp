#include "MenuGuiFixture.h"
#include "MenuModelGpuBoundary.h"
#define private public
#define protected public
#include "GenericModel.h"
#undef protected
#undef private
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include "GameVariables.h"
TL_ORIGINAL(void,mgQuestCreateForUpdate,(CQuestMenu*),"_ZN10CQuestMenu11createMenusEv")
TL_ORIGINAL(void,mgOldQuestUpdate,(CQuestMenu*,float),"_ZN10CQuestMenu6updateEf")
extern "C" void mgNewQuestUpdate(CQuestMenu*,float) __asm__("_ZN10CQuestMenu6updateEf");
TL_FUNCTION(mgQuestEditorState,"_ZN16CResourceManager18getEditorIsRunningEv")
namespace {
CSettings*settings;Ogre::SceneManager*scene;bool notEditor(CResourceManager*){return false;}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
    settings->SetInt(KSETTINGS_RES_WIDTH,c.index&16?1600:320);settings->SetInt(KSETTINGS_RES_HEIGHT,c.index&32?900:480);settings->SetFloat(KSETTINGS_YRATIO,c.index&64?.5f:1.5f);
    CStringTranslate translate(L"");menugui::ModelGpuBoundary gpu;menugui::Fixture f(*settings,scene);detour::Set editor;TL_REDIRECT(editor,mgQuestEditorState,&notEditor);if(editor.failed())std::abort();
    mgQuestCreateForUpdate(f.quest);f.root->addChildWindow(f.quest->m_rootWindow);
    f.quest->m_allowAbandon=(c.index&1)!=0;f.quest->m_closed=(c.index&2)!=0;f.quest->m_selectedQuestChanged=(c.index&4)!=0;
    unsigned animation=c.index/8%4;if(animation==1)f.quest->m_model->playAnimation("CLOSE",false,1,-1);if(animation==2)f.quest->m_model->queueBlendAnimation("CLOSE",false,.1f,1);if(animation==3)f.quest->m_model->playAnimation("OPEN",false,1,-1);
    f.quest->m_model->setPosition(float(int(c.index%3)-1)*150,float(int(c.index/3%3)-1)*20,0);
    const float deltas[]={0,.016f,.5f,5};float delta=deltas[c.index/96%4];
    typedef void(*Fn)(CQuestMenu*,float);Fn fn=ours?mgNewQuestUpdate:mgOldQuestUpdate;if(!autotest::beginInvocation(out,fn))return;fn(f.quest,delta);out.callCompleted=1;
    unsigned flags[]={f.quest->m_allowAbandon,f.quest->m_closed,f.quest->m_selectedQuestChanged,f.quest->m_rootWindow->getParent()==f.root};out.add(flags,sizeof(flags));out.add(&f.quest->m_screenEdge,4);out.add(&f.quest->m_modelAnchor,4);
    const Ogre::Vector3&a=f.quest->m_model->m_pSkeleton->getBone("tag_topskill")->_getDerivedPosition();out.add(&a,sizeof(a));const Ogre::Vector3&b=f.quest->m_model->m_pSkeleton->getBone("tag_bottomskill")->_getDerivedPosition();out.add(&b,sizeof(b));
    std::string snapshot=tlheadless::snapshot(*f.root);unsigned n=snapshot.size();out.add(&n,4);out.add(snapshot.data(),snapshot.size());
}
}
TL_TEST(complete_menu_quest_update_real_bones){tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,0,"complete_menu_quest_update_real_bones",0xbc2020,&side,384);}
