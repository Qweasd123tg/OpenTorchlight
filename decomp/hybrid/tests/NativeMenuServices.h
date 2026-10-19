#ifndef OTL_NATIVE_MENU_SERVICES_H
#define OTL_NATIVE_MENU_SERVICES_H
#include "AutoTest.h"
#include "HeadlessGui.h"
#define private public
#define protected public
#include "GameUI.h"
#include "QuestMenu.h"
#include "QuestDialogMenu.h"
#include "Equipment.h"
#include "SoundManager.h"
#include "StringTranslate.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/SmallMassCompare.h"
TL_ORIGINAL(void,mgSoundCtor,(CSoundManager*,bool),"_ZN13CSoundManagerC1Eb")
TL_ORIGINAL(void,mgSoundDtor,(CSoundManager*),"_ZN13CSoundManagerD1Ev")
namespace menugui {
// Native Services creates the resource master before CGame's audio owner.
// CQuestMenu's native constructor needs that real owner even without FMOD init.
struct Audio {
    CMasterResourceManager* master;
    CSoundManager* owned;
    CSoundManager* previous;
    explicit Audio(CMasterResourceManager*m):master(m),owned(NULL),previous(m->m_pSoundManager){
        if(!previous){owned=static_cast<CSoundManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSoundManager),0,0,0));std::memset(owned,0,sizeof(CSoundManager));mgSoundCtor(owned,false);master->m_pSoundManager=owned;}
    }
    ~Audio(){if(owned){master->m_pSoundManager=previous;mgSoundDtor(owned);Ogre::NedAllocImpl::deallocBytes(owned);}}
};
}
#endif
