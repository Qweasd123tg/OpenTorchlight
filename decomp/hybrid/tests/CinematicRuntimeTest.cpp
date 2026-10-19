#include "MenuGuiFixture.h"
#include "CinematicMenu.h"
#include "Cinematic.h"
#include "Cinematics.h"
#include "SoundData.h"
#include "SoundBankDataInformation.h"
#include "GameVariables.h"
#include <CEGUIImageset.h>
#include <CEGUIImagesetManager.h>
#include <CEGUIPropertyHelper.h>
#include <OgreResourceGroupManager.h>
#include <limits>
#include <fstream>
TL_ORIGINAL(void,ciCtor,(CCinematicMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN14CCinematicMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,ciDtor,(CCinematicMenu*),"_ZN14CCinematicMenuD1Ev")
TL_ORIGINAL(void,ciOldCreate,(CCinematicMenu*),"_ZN14CCinematicMenu11createMenusEv")
TL_ORIGINAL(void,ciBaseCreate,(CDropdownMenu*),"_ZN13CDropdownMenu11createMenusEv")
TL_ORIGINAL(void,ciOldText,(CCinematicMenu*,std::wstring),"_ZN14CCinematicMenu7setTextESbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,ciOldDisplay,(CCinematicMenu*,float),"_ZN14CCinematicMenu17updateTextDisplayEf")
extern "C" void ciNewCreate(CCinematicMenu*) __asm__("_ZN14CCinematicMenu11createMenusEv");
extern "C" void ciNewText(CCinematicMenu*,std::wstring) __asm__("_ZN14CCinematicMenu7setTextESbIwSt11char_traitsIwESaIwEE");
extern "C" void ciNewDisplay(CCinematicMenu*,float) __asm__("_ZN14CCinematicMenu17updateTextDisplayEf");
TL_FUNCTION(ciCreateHook,"_ZN14CCinematicMenu11createMenusEv")
TL_FUNCTION(ciSoundLookup,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(ciSoundAdd,"_ZN10CSoundBank9addSampleEix")
TL_FUNCTION(ciSoundPlay,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
namespace {
CSettings*settings;Ogre::SceneManager*scene;autotest::Capture*output;CSoundData*sample;unsigned presence;
void num(unsigned n){output->add(&n,4);}
CSoundData* lookup(CSoundBankDataInformation*p,const std::wstring&name){num(11);num(p==CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation);num(name.size());output->add(name.data(),name.size()*4);return presence?sample:NULL;}
void add(CSoundBank*,int id,long long guid){num(12);num(id);output->add(&guid,8);}
int play(CSoundBank*,int id,Ogre::SceneNode*n,float a,float b,bool c){num(13);num(id);num(n!=NULL);num(c);output->add(&a,4);output->add(&b,4);return 0;}
void skipCinematic(CCinematicMenu*){}
void snapshot(autotest::Capture&out,CEGUI::Window*w){std::string s=tlheadless::snapshot(*w);unsigned n=s.size();out.add(&n,4);out.add(s.data(),n);}
struct Menu{
 CCinematicMenu*p;
 explicit Menu(menugui::Fixture&f){p=static_cast<CCinematicMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CCinematicMenu),0,0,0));detour::Set setup;TL_REDIRECT(setup,mgDropdownCreate,&menugui::skipDropdown);TL_REDIRECT(setup,mgTitle,&menugui::skipTitle);TL_REDIRECT(setup,ciCreateHook,&skipCinematic);if(setup.failed())std::abort();ciCtor(p,*f.ui,*settings,f.nativeClient.scenes[0],f.root,&f.resources);}
 ~Menu(){if(p->m_cinematicData){if(p->m_skipWindow)p->m_skipWindow->setProperty("Image","");CEGUI::ImagesetManager::getSingleton().destroyImageset(p->m_cinematicData);p->m_cinematicData=NULL;}if(p->m_pUnknown18)CEGUI::WindowManager::getSingleton().destroyWindow(static_cast<CEGUI::Window*>(p->m_pUnknown18));ciDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}
};
struct Data{
 CCinematics*registry;bool owned;CCinematic*entry;std::string folder;
 explicit Data(unsigned index):registry(CCinematics::getSingleton()),owned(false),entry(NULL){
  if(!registry){registry=new CCinematics(L"/missing-ui-proof-cinematics/");owned=true;}
  entry=new(Ogre::NedAllocImpl::allocBytes(sizeof(CCinematic),0,0,0))CCinematic;entry->m_sName=L"ui-proof-cinematic";entry->m_sImage=L"ui-proof-cinematic.imageset";
  const wchar_t*texts[]={L"",L"ASCII\\nnext",L"Текст \\n漢字",L"long"};entry->m_sText=texts[(index/2)%4];if((index/2)%4==3)entry->m_sText=std::wstring(900,L'x');entry->m_sSound=index&2?L"test-Cinematic-sound":L"";
  registry->m_mapCinematics[entry->m_sName]=registry->m_lCinematics.size();registry->m_lCinematics.add(entry);
  char name[120];std::sprintf(name,"/tmp/otl-ui-cinematic-%ld",long(getpid()));folder=name;if(mkdir(folder.c_str(),0700))std::abort();
  std::ofstream xml((folder+"/ui-proof-cinematic.imageset").c_str());xml<<"<?xml version=\"1.0\"?><Imageset Name=\"UIProofCinematic\" Imagefile=\"ui-proof-cinematic.dds\" NativeHorzRes=\"1024\" NativeVertRes=\"768\" AutoScaled=\"false\"><Image Name=\"image\" XPos=\"0\" YPos=\"0\" Width=\"16\" Height=\"8\" /></Imageset>";xml.close();
  unsigned char dds[136]={0};std::memcpy(dds,"DDS ",4);dds[4]=124;dds[12]=8;dds[16]=16;std::ofstream bytes((folder+"/ui-proof-cinematic.dds").c_str(),std::ios::binary);bytes.write(reinterpret_cast<char*>(dds),sizeof(dds));bytes.close();
  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(folder,"FileSystem","Headless");
 }
 ~Data(){registry->m_mapCinematics.erase(entry->m_sName);registry->m_lCinematics.remove(entry);entry->~CCinematic();Ogre::NedAllocImpl::deallocBytes(entry);if(owned)delete registry;Ogre::ResourceGroupManager::getSingleton().removeResourceLocation(folder,"Headless");unlink((folder+"/ui-proof-cinematic.imageset").c_str());unlink((folder+"/ui-proof-cinematic.dds").c_str());rmdir(folder.c_str());}
};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;settings->SetInt(KSETTINGS_RES_WIDTH,800+int(c.index%12)*80);settings->SetInt(KSETTINGS_RES_HEIGHT,600+int(c.index%7)*30);CStringTranslate translate(L"");menugui::Fixture f(*settings,scene);Menu menu(f);CCinematicMenu*p=menu.p;CEGUI::WindowManager&wm=CEGUI::WindowManager::getSingleton();
 if(c.op==0){
  CEGUI::Window*parent=wm.createWindow("DefaultWindow","display-parent"),*text=wm.createWindow("GuiLook/StaticText","display-text");f.root->addChildWindow(parent);parent->addChildWindow(text);float scales[]={0,.3f,.7f,1.3f};parent->setSize(CEGUI::UVector2(CEGUI::UDim(0,300),CEGUI::UDim(scales[c.index/60%4],120)));p->m_textWindow=text;
  const char*names[]={"","ASCII","\320\242\320\265\320\272\321\201\321\202","longer cinematic text"};p->m_cinematicName=names[c.index%4];text->setText(c.index&1?names[c.index%4]:"old");float duration[]={0,5,-1,std::numeric_limits<float>::quiet_NaN(),20};p->m_textDuration=duration[c.index/4%5];p->m_textIndex=float(c.index/20%3)*4;
  float elapsed=c.index&1?.25f:7;typedef void(*Fn)(CCinematicMenu*,float);Fn fn=ours?ciNewDisplay:ciOldDisplay;if(!autotest::beginInvocation(out,fn))return;fn(p,elapsed);out.callCompleted=1;out.add(&p->m_textIndex,4);snapshot(out,parent);
 }else{
  ciBaseCreate(p);
  if(c.op==1){typedef void(*Fn)(CCinematicMenu*);Fn fn=ours?ciNewCreate:ciOldCreate;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;snapshot(out,static_cast<CEGUI::Window*>(p->m_pUnknown18));unsigned fields[]={p->m_cinematicWindow==static_cast<CEGUI::Window*>(p->m_pUnknown18)->recursiveChildSearch("Skip"),p->m_textWindow==static_cast<CEGUI::Window*>(p->m_pUnknown18)->recursiveChildSearch("DialogText"),p->m_skipWindow==static_cast<CEGUI::Window*>(p->m_pUnknown18)->recursiveChildSearch("Background")};out.add(fields,sizeof(fields));}
  else{
   ciOldCreate(p);Data data(c.index);CSoundData sound; sound.m_group=NULL;sound.m_iGuid=0x1234567812345678LL;sample=&sound;presence=c.index&4;
   if(!(c.index&8)){delete p->m_pSoundBank;p->m_pSoundBank=NULL;}TSafePointer<CSoundBank> previousBank;previousBank.setObject(p->m_pSoundBank);
   if(c.index&16){p->m_cinematicData=CEGUI::ImagesetManager::getSingleton().createImageset("OldUIProofCinematic",CEGUI::System::getSingleton().getRenderer()->createTexture(8));p->m_cinematicData->defineImage("image",CEGUI::Point(0,0),CEGUI::Size(8,8),CEGUI::Point(0,0));}
   p->m_textIndex=3;p->m_textDuration=17;p->m_cinematicName="previous";p->m_displayedCharacters=7;p->m_textWindow->setText("before");
   detour::Set audio;TL_REDIRECT(audio,ciSoundLookup,&lookup);TL_REDIRECT(audio,ciSoundAdd,&add);TL_REDIRECT(audio,ciSoundPlay,&play);if(audio.failed())std::abort();std::wstring name=c.index&1?L"ui-proof-cinematic":L"missing";
   typedef void(*Fn)(CCinematicMenu*,std::wstring);Fn fn=ours?ciNewText:ciOldText;if(!autotest::beginInvocation(out,fn))return;fn(p,name);out.callCompleted=1;
   num(previousBank.getObject()!=NULL);num(p->m_pSoundBank!=NULL);num(CEGUI::ImagesetManager::getSingleton().isImagesetPresent("OldUIProofCinematic"));num(p->m_displayedCharacters);out.add(&p->m_textIndex,4);out.add(&p->m_textDuration,4);num(p->m_cinematicName.size());out.add(p->m_cinematicName.data(),p->m_cinematicName.size());if(p->m_cinematicData){CEGUI::Size size=p->m_cinematicData->getNativeResolution();out.add(&size,sizeof(size));}snapshot(out,static_cast<CEGUI::Window*>(p->m_pUnknown18));
  }
 }
}
int run(const tlhybrid_host*host,unsigned op,const char*name,unsigned address,unsigned count){tlheadless::Environment env;env.loadGameSkin();nativegame::Services services;if(!services.ready())return 1;menugui::Audio audio(CMasterResourceManager::getSingleton());settings=CMasterResourceManager::getSingleton()->m_pSettings;scene=services.scene;return smallmass::run(host,op,name,address,&side,count);}
}
TL_TEST(complete_ui_cinematic_display){return run(host,0,"complete_ui_cinematic_display",0xe992f0,240);}
TL_TEST(complete_ui_cinematic_create){return run(host,1,"complete_ui_cinematic_create",0xe9b180,24);}
TL_TEST(complete_ui_cinematic_text){return run(host,2,"complete_ui_cinematic_text",0xe9a5a0,64);}
