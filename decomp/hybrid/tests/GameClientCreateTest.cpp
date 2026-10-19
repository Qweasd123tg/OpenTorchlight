#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "GameClientOwnedNative.h"
#include "tests/SystemsFixtureWorker.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include <OgreLight.h>
TL_ORIGINAL(bool,gccOld,(CGameClient*),"_ZN11CGameClient6createEv")
extern "C" bool gccNew(CGameClient*) __asm__("_ZN11CGameClient6createEv");
TL_FUNCTION(gccSetState,"_ZN11CGameClient12setGameStateE10EGameState5EMenu")
TL_FUNCTION(gccSound,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(gccSample,"_ZN10CSoundBank9addSampleEix")
namespace {
unsigned seed;bool armed;CGameClient*client;CSoundData*sound;autotest::Capture*cap;nativegame::Services*native;
void num(unsigned n){if(armed)cap->add(&n,4);}void fp(float f){if(armed)cap->add(&f,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void colour(const Ogre::ColourValue&c){fp(c.r);fp(c.g);fp(c.b);fp(c.a);}
void state(CGameClient*p,EGameState s,EMenu menu){num(101);num(p==client);num(s);num(menu);p->m_gameState=s;}
CSoundData*lookup(CSoundBankDataInformation*p,const std::wstring&name){num(103);num(p==native->master->m_pSoundBankDataInformation);num(std::wstring(name)==L"TOWNPORTALENTER");return seed&1?sound:NULL;}
void sample(CSoundBank*p,int which,long long guid){num(107);num(p==client->m_menuSound);num(which);if(armed)cap->add(&guid,8);}
struct Case{unsigned seed;};
void side(void*raw,autotest::Capture&out,bool ours){seed=static_cast<Case*>(raw)->seed;cap=&out;armed=false;menugui::OwnedClient owner(*native->settings,native->master,*native->master->m_pSoundManager);client=owner.client;
 Ogre::SceneManager*extra=Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC);client->m_resources=extra;
 native->settings->SetInt(KSETTINGS_OVERRIDE_LIGHTING,int(seed/2%3)-1);
 native->settings->SetInt(KSETTINGS_AMBIENT_LIGHT_RED,int(seed*31%511)-100);native->settings->SetInt(KSETTINGS_AMBIENT_LIGHT_GREEN,int(seed*47%511)-100);native->settings->SetInt(KSETTINGS_AMBIENT_LIGHT_BLUE,int(seed*67%511)-100);
 native->settings->SetInt(KSETTINGS_DIRECTIONAL_LIGHT_RED,int(seed*13%511)-100);native->settings->SetInt(KSETTINGS_DIRECTIONAL_LIGHT_GREEN,int(seed*29%511)-100);native->settings->SetInt(KSETTINGS_DIRECTIONAL_LIGHT_BLUE,int(seed*43%511)-100);
 native->settings->SetFloat(KSETTINGS_F_DIRECTIONAL_INTENSITY,float(seed%7)*.25f);client->m_gameResources->m_bFlag3=(seed&2)!=0;client->m_gameState=static_cast<EGameState>(7);
 CSoundData data;data.m_group=NULL;data.m_iGuid=0x123456780000LL+seed*19;sound=&data;detour::Set hooks;TL_REDIRECT(hooks,gccSetState,&state);TL_REDIRECT(hooks,gccSound,&lookup);TL_REDIRECT(hooks,gccSample,&sample);if(hooks.failed())_exit(64);
 armed=true;typedef bool(*F)(CGameClient*);F fn=ours?gccNew:gccOld;if(autotest::beginInvocation(out,fn)){num(fn(client));out.callCompleted=1;}
 num(client->m_ambientLight!=NULL);num(client->m_menuSound!=NULL);num(client->m_gameState);colour(owner.scenes[0]->getAmbientLight());colour(owner.scenes[2]->getAmbientLight());colour(extra->getAmbientLight());
 Ogre::Light*lights[]={client->m_ambientLight,owner.scenes[2]->getLight("Sunlight")};for(unsigned i=0;i<2;++i){Ogre::Light*l=lights[i];num(l->getType());vec(l->getPosition());vec(l->getDirection());colour(l->getDiffuseColour());colour(l->getSpecularColour());num(l->getCastShadows());}
 armed=false;hooks.restore();client->m_resources=NULL;{menugui::CameraNotificationDuringCleanup notify;Ogre::Root::getSingleton().destroySceneManager(extra);}
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;native=&services;menugui::Audio audio(native->master);autotest::Stats stats={0,0,0};autotest::Coverage coverage("gameclient_create",(uintptr_t)gccOld);int failures=0;for(unsigned i=0;i<96;++i){Case c={i};bool ok=autotest::compareCase(before,after,&c,stats,host,"gameclient_create",i,&coverage);TL_CHECK(failures,ok);if(!ok)break;}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=96);}
}
TL_TEST(gameclient_create){return systems_fixture::isolated(&worker,host);}
