#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/CharacterEmptyGlobals.h"
#define private public
#include "DataValue.h"
#include "FileReader.h"
#undef private
#include "DataGroup.h"
#include "PairStyle.h"
#include "FileSystem.h"
#include "StringUtilities.h"
#include "TRepository.h"
#include <OgreLogManager.h>
#include <OgreMemoryAllocatorConfig.h>
#include <fstream>
#include <iterator>
#include <sys/stat.h>
TL_ORIGINAL(void,prGroupCtor,(CDataGroup*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,prGroupDtor,(CDataGroup*),"_ZN10CDataGroupD1Ev")
TL_ORIGINAL(void,prReaderCtor,(CFileReader*),"_ZN11CFileReaderC1Ev")
TL_ORIGINAL(void,prReaderDtor,(CFileReader*),"_ZN11CFileReaderD1Ev")
TL_ORIGINAL(bool,prReaderLoad,(CFileReader*,FILE*),"_ZN11CFileReader8ReadFileEP8_IO_FILE")
TL_ORIGINAL(void,prFsCtor,(CFileSystem*,bool),"_ZN11CFileSystemC1Eb")
TL_ORIGINAL(void,prFsDtor,(CFileSystem*),"_ZN11CFileSystemD1Ev")
TL_ORIGINAL(void,prGetInfo,(CFileSystem*,const std::wstring&,CFileInfo&,bool,bool,bool),"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(prInfoEntry,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_ORIGINAL(void,prParseOld,(CPairStyle*,CFileReader*,CDataGroup*),"_ZN10CPairStyle14ParseSubGroupsEP11CFileReaderP10CDataGroup")
extern "C" void prParseNew(CPairStyle*,CFileReader*,CDataGroup*) __asm__("_ZN10CPairStyle14ParseSubGroupsEP11CFileReaderP10CDataGroup");
TL_ORIGINAL(int,prSaveOld,(CPairStyle*,const std::wstring&,CDataGroup*),"_ZN10CPairStyle19SaveDataGroupToFileERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup")
extern "C" int prSaveNew(CPairStyle*,const std::wstring&,CDataGroup*) __asm__("_ZN10CPairStyle19SaveDataGroupToFileERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup");
TL_ORIGINAL(int,prLoadOld,(CPairStyle*,const std::wstring&,CDataGroup*,CTimerStatics*),"_ZN10CPairStyle19LoadDataGroupToFileERKSbIwSt11char_traitsIwESaIwEEP10CDataGroupP13CTimerStatics")
extern "C" int prLoadNew(CPairStyle*,const std::wstring&,CDataGroup*,CTimerStatics*) __asm__("_ZN10CPairStyle19LoadDataGroupToFileERKSbIwSt11char_traitsIwESaIwEEP10CDataGroupP13CTimerStatics");
extern CFileSystem* g_pFileSystem;
namespace {
struct Case {unsigned seed,op,observed,negative;};
std::string directory;autotest::Capture*output;const Case*input;unsigned infoCalls;CFileSystem*systemOwner;
void word(unsigned x){output->add(&x,4);}
void tree(CDataGroup*group,unsigned depth=0){if(depth>12){output->issue=autotest::Capture::InvalidReport;return;}output->addText(group->GetGroupName());word(group->m_b58);word(group->m_DataValues.size());for(unsigned i=0;i<group->m_DataValues.size();++i){CDataValue*v=group->m_DataValues[i];output->addText(v->GetDataValueName());word(v->m_eType);if(v->m_eType==CDataValue::DATAVALUE_STRING||v->m_eType==CDataValue::DATAVALUE_TRANSLATE)output->addText(v->GetValueString(false));else output->add(&v->m_Value,8);}word(group->m_DataGroups.size());for(unsigned i=0;i<group->m_DataGroups.size();++i)tree(group->m_DataGroups[i],depth+1);}
void info(CFileSystem*self,const std::wstring&name,CFileInfo&out,bool compiled,bool binary,bool mods){if(self!=systemOwner)output->issue=autotest::Capture::InvalidReport;word(++infoCalls);output->addText(name);word(compiled);word(binary);word(mods);output->addText(out.m_sModName);output->addText(out.m_sPath);word(out.m_eFormat);word(out.m_eLocation);word(out.m_bExists);
 // This typed seam supplies a resolved mod path while retaining a native owner.
 // Disk reads and both serializers remain native dependencies.
 std::string plain="resolved.dat";if(input->seed%8==1)plain="missing/sub/file.dat";
 if(input->seed%5==0)plain="Unicode-Ж.dat";
 out.m_sModName=(input->seed/2)%2?directory+"/":"";out.m_sPath=STRINGS::StringConvertToWide(plain);out.m_sResourceName=plain;out.m_sResourceGroup="";out.m_eLocation=FILE_LOCATION_DISK;out.m_eFormat=FILE_FORMAT_TEXT;out.m_bExists=input->seed%3!=0;
}
struct Log:Ogre::LogListener{std::vector<std::string>text;std::vector<int>level;std::vector<unsigned char>mask;virtual void messageLogged(const Ogre::String&s,Ogre::LogMessageLevel l,bool m,const Ogre::String&){text.push_back(s);level.push_back(l);mask.push_back(m);}};
void utf16(const std::string&path,const std::wstring&text){FILE*f=std::fopen(path.c_str(),"wb");if(!f)std::abort();unsigned short marker=0xfeff;std::fwrite(&marker,2,1,f);for(unsigned i=0;i<text.size();++i){unsigned short ch=text[i];std::fwrite(&ch,2,1,f);}std::fclose(f);}
std::wstring document(unsigned seed){const wchar_t*types[]={L"INTEGER",L"INTEGER64",L"FLOAT",L"DOUBLE",L"UNSIGNED INT",L"BOOL",L"STRING",L"TRANSLATE",L"DIALOG",L"unknown"};const wchar_t*values[]={L"-2147483648",L"9223372036854775807",L"-1.25",L"2.125",L"4294967295",L"true",L"Unicode Ж:middle:tail",L"translated",L"dialogue",L"free text"};std::wstring text;if(seed%4!=0)text=L"[Root]\r\n";for(unsigned i=0;i<seed%11;++i){text+=L"<";text+=types[(i+seed)%10];text+=L">mixedName:";text+=values[(i+seed)%10];text+=seed&1?L"\n":L"\r\n";}switch((seed/3)%8){case 0:text+=L"[Child]\n<STRING>leaf:a:b:c\n[/different]\n";break;case 1:text+=L"<STRING>empty:\n<STRING>no-value\n";break;case 2:text+=L"`ignored\n \t<BOOL>boolean:false\n";break;case 3:text+=L"<STRING>name>:value\ntext\n<>\n[]\n[not-closed\n";break;case 4:text+=L"[One]\n[Two]\n<INTEGER>num:17\n[/Two]\n[/One]\n";break;case 5:text+=L"[/early]\n<INTEGER>ignored:5\n";break;case 6:for(unsigned i=0;i<80;++i)text+=L"<STRING>x:a:b:c:d:e:f:g:h:i\n";break;default:text+=L"[UnicodeЖ]\n<STRING>text: \t a : b \r\n[/end]\n";}
 if(seed&8)text+=L"[/Root]\n";if(seed&16)text+=L"<INTEGER>last:99";else text+=L"\n\n";return text;}
void bytes(const std::string&path){std::ifstream f(path.c_str(),std::ios::binary);word(f.is_open());std::string data((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());word(data.size());output->add(data.data(),data.size());}
void fileCleanup(const std::string&path){unlink(path.c_str());unlink((path+".ADM").c_str());unlink((path+".adm").c_str());}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);input=&c;output=&out;infoCalls=0;initEmptyGlobals();Ogre::LogManager logs;Ogre::Log*log=logs.createLog("pair-style-recovery",true,false,true);Log logged;log->addListener(&logged);uint64_t groupMemory[(sizeof(CDataGroup)+7)/8];CDataGroup*group=reinterpret_cast<CDataGroup*>(groupMemory);prGroupCtor(group,c.seed&1?L"PREEXISTING":L"",NULL,1+c.seed%4,1+c.seed%3,NULL);for(unsigned i=0;i<c.seed/7%4;++i)group->AddDataValue(L"prior",int(i));CPairStyle style;
 if(c.op==0){uint64_t readerMemory[(sizeof(CFileReader)+7)/8];CFileReader*reader=reinterpret_cast<CFileReader*>(readerMemory);prReaderCtor(reader);FILE*f=std::tmpfile();if(!f)std::abort();unsigned short marker=0xfeff;std::fwrite(&marker,2,1,f);std::wstring text=document(c.seed);for(unsigned i=0;i<text.size();++i){unsigned short ch=text[i];std::fwrite(&ch,2,1,f);}std::rewind(f);if(!prReaderLoad(reader,f))std::abort();std::fclose(f);typedef void(*Fn)(CPairStyle*,CFileReader*,CDataGroup*);Fn fn=ours?prParseNew:prParseOld;if(autotest::beginInvocation(out,fn)){fn(&style,c.seed%17==0?NULL:reader,c.seed%19==0?NULL:group);out.callCompleted=1;}word(reader->m_iLength);word(reader->m_iPosition);word(reader->m_iCharacterSize);word(reader->m_pBuffer!=NULL);if(reader->m_pBuffer)out.add(reader->m_pBuffer,reader->m_iLength*sizeof(wchar_t));prReaderDtor(reader);
 }else{char cwd[4096];if(!getcwd(cwd,sizeof(cwd))||chdir(directory.c_str()))std::abort();CFileSystem*prior=g_pFileSystem;CFileSystem*fs=static_cast<CFileSystem*>(Ogre::NedAllocImpl::allocBytes(sizeof(CFileSystem),0,0,0));g_pFileSystem=fs;prFsCtor(fs,false);systemOwner=fs;
  std::string base=directory+"/native.dat",resolved=directory+"/resolved.dat",unicode=directory+"/Unicode-Ж.dat";fileCleanup(base);fileCleanup(resolved);fileCleanup(unicode);utf16(resolved,document(c.seed));utf16(unicode,document(c.seed));if(c.op==2||c.seed%3!=0)utf16(base,document(c.seed));if(c.op==1){group->AddDataValue(L"integer",int(c.seed)-45);group->AddDataValue(L"double",double(c.seed)/7);group->AddDataValue(L"string",L"Unicode Ж : text",false);if(c.seed&2){CDataGroup*child=group->AddDataGroup(L"child");child->AddDataValue(L"translated",L"text",true);}}
  detour::Set redirects;if(c.observed){TL_REDIRECT(redirects,prInfoEntry,&info);if(redirects.failed())std::abort();}
  std::wstring path=STRINGS::StringConvertToWide(base);if(c.seed%8==1)path=STRINGS::StringConvertToWide(directory+"/missing/sub/file.dat");if(c.seed%13==0)path=L"";CDataGroup*argument=c.seed%11==0?NULL:group;int result=0;if(c.op==1){typedef int(*Fn)(CPairStyle*,const std::wstring&,CDataGroup*);Fn fn=ours?prSaveNew:prSaveOld;if(autotest::beginInvocation(out,fn)){result=fn(&style,path,argument);out.callCompleted=1;}}else{typedef int(*Fn)(CPairStyle*,const std::wstring&,CDataGroup*,CTimerStatics*);Fn fn=ours?prLoadNew:prLoadOld;if(autotest::beginInvocation(out,fn)){result=fn(&style,path,argument,NULL);out.callCompleted=1;}}word(result);word(infoCalls);char after[4096];if(!getcwd(after,sizeof(after)))std::abort();output->addText(std::string(after));
  redirects.restore();bytes(base);bytes(base+".ADM");bytes(base+".adm");bytes(resolved);bytes(resolved+".ADM");bytes(resolved+".adm");bytes(unicode);bytes(unicode+".ADM");bytes(unicode+".adm");fileCleanup(base);fileCleanup(resolved);fileCleanup(unicode);prFsDtor(fs);Ogre::NedAllocImpl::deallocBytes(fs);g_pFileSystem=prior;if(chdir(cwd))std::abort();
 }
 if(ours&&c.negative)group->SetGroupName(L"DELIBERATE_NEGATIVE_CONTROL");tree(group);word(logged.text.size());for(unsigned i=0;i<logged.text.size();++i){out.addText(logged.text[i]);word(logged.level[i]);word(logged.mask[i]);}log->removeListener(&logged);prGroupDtor(group);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}unsigned operation,observed;
int worker(const tlhybrid_host*host){initEmptyGlobals();char temp[]="/tmp/otl-pair-recovery-XXXXXX";char*p=mkdtemp(temp);if(!p)return 1;directory=p;const char*name=operation==0?"pair_style_parse":operation==1?(observed?"pair_style_save_observed":"pair_style_save_native"):(observed?"pair_style_load_observed":"pair_style_load_native");uintptr_t address=operation==0?(uintptr_t)prParseOld:operation==1?(uintptr_t)prSaveOld:(uintptr_t)prLoadOld;autotest::Coverage coverage(name,address);unsigned count=operation==0?384:128;int failed=0;for(unsigned seed=0;seed<count;++seed){Case c={seed,operation,observed,0};autotest::Outcome a,b;autotest::runChild(original,&c,a,4000,20000);autotest::runChild(candidate,&c,b,4000,20000);if(coverage.observe(host,a,b)){unsigned at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    pair op%u observed%u seed%u issue%u/%u valid%u/%u status%d/%d first%u bytes%lu/%lu\n",operation,observed,seed,a.capture.issue,b.capture.issue,a.reportValid,b.reportValid,a.childStatus,b.childStatus,at,(unsigned long)a.capture.length,(unsigned long)b.capture.length);failed=1;break;}}coverage.report(host);Case control={43,operation,observed,1};autotest::Outcome a,b;autotest::runChild(original,&control,a,4000,20000);autotest::runChild(candidate,&control,b,4000,20000);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);bool complete=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);host->log("    %s negative detected%u completed%u\n",name,unsigned(detected),unsigned(complete));rmdir(directory.c_str());return failed||coverage.completed!=count||!detected||!complete;}
}
TL_TEST(pair_style_parse){operation=0;observed=0;return systems_fixture::isolated(worker,host,300);}
TL_TEST(pair_style_save_native){operation=1;observed=0;return systems_fixture::isolated(worker,host,180);}
TL_TEST(pair_style_save_observed){operation=1;observed=1;return systems_fixture::isolated(worker,host,180);}
TL_TEST(pair_style_load_native){operation=2;observed=0;return systems_fixture::isolated(worker,host,180);}
TL_TEST(pair_style_load_observed){operation=2;observed=1;return systems_fixture::isolated(worker,host,180);}
