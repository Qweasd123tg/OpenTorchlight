#include <cstring>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#define protected public
#include "CharacterSaveState.h"
#include "ItemSaveState.h"
#include "Effect.h"
#include "UnitTheme.h"
#include "UnitThemes.h"
#undef protected
#undef private
TL_ORIGINAL(void,saveOriginal,(CCharacterSaveState*,FILE*),"_ZN19CCharacterSaveState4saveEP8_IO_FILE")
TL_ORIGINAL(void,loadOriginal,(CCharacterSaveState*,FILE*,unsigned),"_ZN19CCharacterSaveState4loadEP8_IO_FILEj")
extern "C" void saveCandidate(CCharacterSaveState*,FILE*) __asm__("_ZN19CCharacterSaveState4saveEP8_IO_FILE");
extern "C" void loadCandidate(CCharacterSaveState*,FILE*,unsigned) __asm__("_ZN19CCharacterSaveState4loadEP8_IO_FILEj");
TL_FUNCTION(saveItem,"_ZN14CItemSaveState4saveEP8_IO_FILE")
TL_FUNCTION(loadItem,"_ZN14CItemSaveState4loadEP8_IO_FILEj")
TL_FUNCTION(saveCalculate,"_ZN7CEffect18calculateBaseValueENS_15ECALCULATETYPESE")
TL_FUNCTION(saveFX,"_ZN7CEffect5setFXERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(saveThemes,"_ZN11CUnitThemes12getSingletonEv")
TL_FUNCTION(saveGraphs,"_ZN7CEffect9setGraphsESbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case { unsigned op,seed,version,control; };
autotest::Capture* capture;bool armed;CUnitThemes*catalog;CUnitTheme*themeA,*themeB;
void number(unsigned v){if(armed)capture->add(&v,4);}
void scalar(float v){if(armed)capture->add(&v,4);}
void text(const std::wstring&v){if(armed)capture->addText(v);}
float calculate(CEffect*p,CEffect::ECALCULATETYPES mode){number(101);number(mode);number(p->m_iLevel);scalar(p->m_fValue24);for(unsigned i=0;i<4;++i)scalar(p->m_values[i]);p->m_fValueC0=p->m_values[0]+p->m_values[1]*2+p->m_values[2]*3+p->m_values[3]*4;return p->m_fValueC0;}
void fx(CEffect*p,const std::wstring&v){number(103);text(v);p->m_particleName=v;}
void graphs(CEffect*p,std::wstring v){number(107);text(v);p->m_name90=v;}
CUnitThemes* themes(){number(127);return catalog;}
void itemSave(CItemSaveState*p,FILE*f){number(109);number(p->m_iIndex);number(p->m_iStackSize);fwrite(&p->m_iIndex,4,1,f);fwrite(&p->m_iStackSize,4,1,f);}
void itemLoad(CItemSaveState*p,FILE*f,unsigned version){number(113);number(version);fread(&p->m_iIndex,4,1,f);fread(&p->m_iStackSize,4,1,f);number(p->m_iIndex);number(p->m_iStackSize);}
std::vector<unsigned char> bytes(FILE*f){long length=ftell(f);if(length<0||length>1500000)_exit(44);std::vector<unsigned char>b(length);rewind(f);if(length&&fread(&b[0],1,length,f)!=size_t(length))_exit(45);return b;}
void record(const std::vector<unsigned char>&b){number(b.size());if(b.size()<180000){if(!b.empty())capture->add(&b[0],b.size());}else{uint64_t hash=1469598103934665603ULL;for(unsigned i=0;i<b.size();++i){hash^=b[i];hash*=1099511628211ULL;}capture->add(&hash,8);}}
void fill(CCharacterSaveState*p,unsigned seed,bool large){
 p->m_flag20C=seed&1;p->m_guid20=0x1234567800000000LL+seed;p->m_guid28=-77-seed;p->m_guid10=0x7abcde0000000000LL+seed;
 p->m_flag18=seed%3==0;p->m_flag30=seed%3==1;p->m_flag31=seed%3==2;p->m_flag32=seed%2;p->m_flag33=seed%4==0;p->m_flag34=seed*17;
 p->m_scale=seed*0.125f-3;p->m_transformationTime=seed*0.5f;p->m_townTravelTime=-float(seed);p->m_petMode=seed%5;p->m_alignment=seed%4;
 p->m_guid50=0x445566778899aabbLL;p->m_guid58=-123456789;p->m_value60=seed+91;p->m_name=large?std::wstring(seed&1?65536:65535,L'x'):seed%3==0?L"":seed%3==1?L"name Ж":L"AbcΩ";
 p->m_value64=seed-29;p->m_value68=seed+27;p->m_position=Ogre::Vector3(seed,-float(seed),seed/4.0f);for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j)p->m_orientation[i][j]=int(i*4+j)-7+seed/8.0f;
 p->m_valueD0=-77;p->m_valueD4=seed*3;p->m_valueD8=-123;p->m_valueDC=seed+33;p->m_hp=seed*1.75f;p->m_valueE4=0xabcdef00+seed;p->m_valueE8=0xffffffff-seed;
 p->m_mana=seed*2.25f;p->m_maxManaBase=777;p->m_maxManaBonus=-71;p->m_experienceReward=17+seed;p->m_fameReward=-19;p->m_playTime=seed/8.0f;p->m_bravery=-float(seed)/4.0f;
 p->m_freeStatPoints=seed;p->m_freeSkillPoints=seed+3;p->m_freePerkPoints=seed+9;p->m_guidB8=0x11abcdef12345678LL;p->m_guidC0=-892;p->m_guidC8=0x78abcd0099887766LL;
 for(unsigned i=0;i<seed%5;++i)p->m_values.push_back(i*11-seed);for(unsigned i=0;i<4;++i){p->m_knownSpells[i]=(i+seed)%3?L"fire Ж":L"";p->m_spellLevels[i]=int(seed)-i*17;}
 for(unsigned i=0;i<7;++i)p->m_damageDefense[i]=i*113-seed;p->m_meleeStat=seed+10;p->m_rangedStat=seed-10;p->m_defenseStat=-77;p->m_magicStat=89;p->m_value174=seed*39;p->m_value184=-89;
 p->m_guid200=0x3141592653589793LL;p->m_value208=seed+45;
 for(unsigned i=0;i<seed%4;++i)p->m_strings.add(large?std::wstring(seed&1?65536:65535,L'm'):i%2?L"mod-Ж":L"");
 for(unsigned i=0;i<seed%3;++i){CItemSaveState*q=new CItemSaveState;q->m_iIndex=i+123;q->m_iStackSize=seed*3+i;p->m_pets.push_back(q);}
 static const unsigned levels[]={0,1000,1001,0xffffffff};
 for(unsigned g=0;g<3;++g)for(unsigned i=0;i<(seed+g)%3;++i){CEffect*e=new CEffect(static_cast<EEFFECT_TYPE>((seed+i)%7),true,static_cast<EEFFECT_ACTIVATION>((seed+g)%3),float(int(seed)-8)+0.75f,2,3,false);
 e->m_sName=i%2?L"effect Ж":L"MixedCase";e->m_name88=L"unused secondary";e->m_particleName=L"fx";e->m_name90=L"graph";
 e->m_flag31=(seed+i)%2;e->m_eDamageType=static_cast<EDAMAGE_TYPES>((seed+i)%5);e->m_flag33=seed%2;e->m_modifierFlag32=i%2;e->m_flag30=(seed+g)%2;e->m_flag37=(seed+i+g)%2;
 e->m_pUnitTheme=(seed+g+i)%3==0?NULL:(seed+g+i)%3==1?themeA:themeB;
 e->m_iLevel=levels[(seed+i+g)%4];e->m_value3C=seed+91;e->m_value40=-int(seed)-72;e->m_value44=-12;e->m_fRemainingDuration=seed/8.0f;e->m_value38=-float(seed)/16.0f;e->m_fValueC0=-77.5f;
 for(unsigned j=0;j<4;++j)e->m_values[j]=(int(j)-2)*1.125f+seed/8.0f;p->m_items[g].push_back(e);}
}
// Transcode a complete native v19 record. Offsets and legacy omissions come
// from the native FILE operations, independently of the candidate loader.
struct Stream { const std::vector<unsigned char>&in;std::vector<unsigned char>out;size_t pos;Stream(const std::vector<unsigned char>&v):in(v),pos(0){}
 unsigned value(unsigned n){if(pos+n>in.size())_exit(46);unsigned v=0;for(unsigned i=0;i<n;++i)v|=unsigned(in[pos+i])<<(8*i);return v;}
 void take(unsigned n,bool keep=true){if(pos+n>in.size())_exit(47);if(keep)out.insert(out.end(),in.begin()+pos,in.begin()+pos+n);pos+=n;}
 void string(bool keep=true){unsigned n=value(2);take(2+2*n,keep);}
};
std::vector<unsigned char> legacy(const std::vector<unsigned char>&latest,unsigned version,unsigned seed){Stream s(latest);s.take(51);s.take(version>7?8:4);if(version<=7)s.take(4,false);s.take(12);s.string();s.take(84);s.take(24);s.take(4,version>1);s.take(8);s.take(4,version>1);s.take(28+16);s.take(8,version>11);
 unsigned n=s.value(4);s.take(4+n*4);for(unsigned i=0;i<4;++i){s.string();s.take(4);}s.take(52);s.take(version>18?8:4);if(version<=18)s.take(4,false);s.take(4);
 n=s.value(4);s.take(4,version>8);for(unsigned i=0;i<n;++i)s.string(version>8);n=s.value(4);s.take(4+n*8);
 for(unsigned g=0;g<3;++g){n=s.value(4);bool negative=seed==15&&g==1;s.take(4,!negative);if(negative)for(unsigned k=0;k<4;++k)s.out.push_back(255);size_t empty=s.out.size();for(unsigned i=0;i<n;++i){s.string();s.string(version>3);s.string();s.string(version>6);size_t flag=s.out.size();s.take(12);if(seed&4){s.out[flag]=255;s.out[flag+9]=128;s.out[flag+10]=2;s.out[flag+11]=255;}s.take(1,version>6);s.take(8);s.take(version>4?8:4);if(version<=4)s.take(4,false);s.take(44);if(negative)s.out.resize(empty);}}
 if(s.pos!=latest.size())_exit(48);if(seed&8){s.out[0]=255;for(unsigned i=25;i<30;++i)s.out[i]=128+i;}return s.out;}
void saveControl(CCharacterSaveState*p,FILE*f){saveCandidate(p,f);fseek(f,0,SEEK_SET);unsigned char changed=!p->m_flag20C;fwrite(&changed,1,1,f);fseek(f,0,SEEK_END);}
void loadControl(CCharacterSaveState*p,FILE*f,unsigned v){loadCandidate(p,f,v);if(p->m_items[0].size())p->m_items[0][0]->m_value40^=1;else p->m_guid50^=1;}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);capture=&out;armed=false;detour::Set patches;TL_REDIRECT(patches,saveItem,&itemSave);TL_REDIRECT(patches,loadItem,&itemLoad);TL_REDIRECT(patches,saveCalculate,&calculate);TL_REDIRECT(patches,saveFX,&fx);TL_REDIRECT(patches,saveGraphs,&graphs);TL_REDIRECT(patches,saveThemes,&themes);if(patches.failed())_exit(43);
 // Only the catalog's native core and typed lookup subobjects are needed.
 // No synthetic vtable or virtual operation is used on this collaborator.
 uint64_t catalogStorage[(sizeof(CUnitThemes)+7)/8];catalog=reinterpret_cast<CUnitThemes*>(catalogStorage);new(static_cast<CRunicCore*>(catalog))CRunicCore;new(&catalog->m_sFilename)std::wstring;new(&catalog->m_Themes)TArrayList<CUnitTheme*>(2);
 themeA=new CUnitTheme;themeA->m_iGuid=0x1122334455667788LL;themeB=new CUnitTheme;themeB->m_iGuid=0x7766554433221100LL;
 CUnitTheme*other=new CUnitTheme;other->m_iGuid=33;if(c.seed%4){catalog->m_Themes.add(other);catalog->m_Themes.add(themeA);}
 CCharacterSaveState*p=new CCharacterSaveState;fill(p,c.seed,c.op==2);if(c.op==0&&c.seed%5==0)p->m_name=L"Abc\U0001f642";TSafePointer<CCharacterSaveState>weak;weak.setObject(p);
 FILE*f=tmpfile();if(!f)_exit(49);
 if(c.op!=1){armed=true;autotest::invoke(out,ours?(c.control?&saveControl:&saveCandidate):&saveOriginal,p,f);record(bytes(f));}
 else{saveOriginal(p,f);std::vector<unsigned char>input=legacy(bytes(f),c.version,c.seed);delete p;p=new CCharacterSaveState;weak.setObject(p);p->m_guidC8=0x4321000012345678LL;
  if(c.seed&1){CItemSaveState*q=new CItemSaveState;q->m_iIndex=-101;q->m_iStackSize=27;p->m_pets.push_back(q);p->m_strings.add(L"existing mod");CEffect*e=new CEffect(static_cast<EEFFECT_TYPE>(0),false,static_cast<EEFFECT_ACTIVATION>(0),1,2,3,false);e->m_sName=L"existing";e->m_name88=L"existing2";e->m_particleName=L"existingfx";e->m_name90=L"existinggraph";e->m_eDamageType=static_cast<EDAMAGE_TYPES>(0);e->m_flag31=0;e->m_flag33=false;e->m_modifierFlag32=false;e->m_value3C=3;e->m_value40=4;e->m_value44=5;e->m_fRemainingDuration=7;p->m_items[1].push_back(e);}
  freopen(NULL,"w+b",f);if(!input.empty())fwrite(&input[0],1,input.size(),f);rewind(f);armed=true;autotest::invoke(out,ours?(c.control?&loadControl:&loadCandidate):&loadOriginal,p,f,c.version);number(ftell(f));number(feof(f));fclose(f);f=tmpfile();saveOriginal(p,f);record(bytes(f));}
 fclose(f);std::vector<TSafePointer<CItemSaveState>*>items;std::vector<TSafePointer<CEffect>*>effects;
 for(unsigned i=0;i<p->m_pets.size();++i){TSafePointer<CItemSaveState>*w=new TSafePointer<CItemSaveState>;w->setObject(p->m_pets[i]);items.push_back(w);}for(unsigned g=0;g<3;++g)for(unsigned i=0;i<p->m_items[g].size();++i){TSafePointer<CEffect>*w=new TSafePointer<CEffect>;w->setObject(p->m_items[g][i]);effects.push_back(w);}
 delete p;number(weak.getObject()==NULL);if(weak.getObject())out.issue=autotest::Capture::InvalidReport;for(unsigned i=0;i<items.size();++i){number(items[i]->getObject()==NULL);if(items[i]->getObject())out.issue=autotest::Capture::InvalidReport;delete items[i];}for(unsigned i=0;i<effects.size();++i){number(effects[i]->getObject()==NULL);if(effects[i]->getObject())out.issue=autotest::Capture::InvalidReport;delete effects[i];}delete themeA;delete themeB;delete other;catalog->m_Themes.~TArrayList();catalog->m_sFilename.~basic_string();static_cast<CRunicCore*>(catalog)->~CRunicCore();}
void original(void*p,autotest::Capture&o){side(p,o,false);}void recovered(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(character_save_storage){int failures=0;const unsigned versions[]={0,1,2,3,4,5,6,7,8,9,11,12,18,19,0xffffffff};for(unsigned op=0;op<3;++op){autotest::Coverage coverage("character_save_storage",op==1?(uintptr_t)&loadOriginal:(uintptr_t)&saveOriginal);unsigned cases=op==1?240:op==2?4:32;for(unsigned i=0;i<cases;++i){Case c={op,op==2?i+1:i%16,op==1?versions[i/16]:19,0};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage.observe(host,a,b);bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus;TL_CHECK(failures,ok);if(!ok){host->log("    save storage op%u seed%u version%u status%d/%d issue%u/%u bytes%lu/%lu\n",op,c.seed,c.version,a.status,b.status,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}coverage.report(host);return failures;}}coverage.report(host);}
 for(unsigned op=0;op<2;++op){Case c={op,5,19,1};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool caught=(a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length)!=0)&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus;TL_CHECK(failures,caught);host->log("    save storage negative %u detected %u\n",op,unsigned(caught));}return failures;}
