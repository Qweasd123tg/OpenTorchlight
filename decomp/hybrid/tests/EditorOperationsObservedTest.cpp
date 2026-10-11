#include <cstring>
#include <string>
#include <map>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#include "FileSystem.h"
extern "C" void* editorGlobal __asm__("gEditor");
extern "C" unsigned char editorMemory[4000] __asm__("sEditorTmpMemory");
extern "C" void* roomTable[] __asm__("_ZTV10CRoomPiece");
extern "C" void* layoutTable[] __asm__("_ZTV7CLayout");
extern "C" void* objectTable[] __asm__("_ZTV17CEditorBaseObject");
TL_ORIGINAL(long long,original0,(unsigned,unsigned),"_Z25EditorPollObjectIDByIndexjj")
extern "C" long long candidate0(unsigned,unsigned) __asm__("_Z25EditorPollObjectIDByIndexjj");
TL_ORIGINAL(bool,original1,(wchar_t*,wchar_t*),"_Z3IsAPwS_")
extern "C" bool candidate1(wchar_t*,wchar_t*) __asm__("_Z3IsAPwS_");
TL_ORIGINAL(void*,original2,(),"_Z20EditorGetDebugOutputv")
extern "C" void* candidate2() __asm__("_Z20EditorGetDebugOutputv");
TL_ORIGINAL(void*,original3,(),"_Z18EditorAutomapTilesv")
extern "C" void* candidate3() __asm__("_Z18EditorAutomapTilesv");
TL_ORIGINAL(void*,original4,(long long,unsigned*,bool,bool,bool),"_Z19EditorGetObjectSnapxRjbbb")
extern "C" void* candidate4(long long,unsigned*,bool,bool,bool) __asm__("_Z19EditorGetObjectSnapxRjbbb");
TL_ORIGINAL(int,original5,(unsigned,wchar_t*,bool),"_Z15EditorSaveScenejPwb")
extern "C" int candidate5(unsigned,wchar_t*,bool) __asm__("_Z15EditorSaveScenejPwb");
TL_ORIGINAL(void,original6,(),"_Z23reloadEditorLayoutLinksv")
extern "C" void candidate6() __asm__("_Z23reloadEditorLayoutLinksv");
TL_ORIGINAL(void,original7,(unsigned,unsigned),"_Z18EditorSetIngameResjj")
extern "C" void candidate7(unsigned,unsigned) __asm__("_Z18EditorSetIngameResjj");
TL_ORIGINAL(void*,original8,(unsigned*),"_Z33EditorGetObjectsCreatedThisRenderRj")
extern "C" void* candidate8(unsigned*) __asm__("_Z33EditorGetObjectsCreatedThisRenderRj");
TL_ORIGINAL(bool,original9,(wchar_t*),"_Z16EditorFileExistsPw")
extern "C" bool candidate9(wchar_t*) __asm__("_Z16EditorFileExistsPw");
TL_ORIGINAL(unsigned,original10,(int),"_Z12EditorUpdatei")
extern "C" unsigned candidate10(int) __asm__("_Z12EditorUpdatei");
TL_ORIGINAL(void*,original11,(unsigned,unsigned*),"_Z17EditorPollObjectsjRj")
extern "C" void* candidate11(unsigned,unsigned*) __asm__("_Z17EditorPollObjectsjRj");
TL_ORIGINAL(unsigned,original12,(void*,const wchar_t*),"_ZN7CEditor22GetEditorSceneIDByNameEPKw")
extern "C" unsigned candidate12(void*,const wchar_t*) __asm__("_ZN7CEditor22GetEditorSceneIDByNameEPKw");
TL_FUNCTION(target_scene,"_ZN7CEditor14GetEditorSceneEj")
TL_FUNCTION(target_lookup,"_Z16GetObjectInScenex")
TL_FUNCTION(target_isa,"_ZN16CResourceManager3ISAERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(target_save,"_ZN12CEditorScene9saveSceneESbIwSt11char_traitsIwESaIwEEP10TArrayListIP17CEditorBaseObjectE")
TL_FUNCTION(target_fileExists,"_ZN10FILESYSTEM10FileExistsERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_clearLayouts,"_ZN7CLayout25removeAllCloneableObjectsEv")
TL_FUNCTION(target_loadLayout,"_ZN7CLayout14loadLayoutFileERKSbIwSt11char_traitsIwESaIwEEbP13CTimerStaticsbbj")
TL_FUNCTION(target_setInt,"_ZN20CDynamicPropertyFile6SetIntEji")
TL_FUNCTION(target_setFloat,"_ZN20CDynamicPropertyFile8SetFloatEjf")
TL_FUNCTION(target_rescale,"_ZN11CGameClient9rescaleUIEv")
TL_FUNCTION(target_files,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(target_fileInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(target_begin,"_ZN20CEditorObjectManager21EditorUpdateBeginningEv")
TL_FUNCTION(target_end,"_ZN20CEditorObjectManager15EditorUpdateEndEv")

namespace {
struct Case{unsigned op,seed,mode,index;};
struct List{void**data;unsigned count,capacity,grow,padding;};
typedef std::map<long long,void*> Map;typedef std::map<std::wstring,unsigned> Names;
extern "C" Map::iterator objectIterator __asm__("iteratorOfObjectsInScene");
Case* input;autotest::Capture* output;void* editors[2];void* managers[2];void* objects[8];void* scenes[2];void* settings[2];void* resources[2];void* services[4];Map* maps[2];List snapList;
void num(unsigned x){output->add(&x,4);}void ptr(const void*p){output->add(&p,8);}void put(void*p,unsigned off,void*v){std::memcpy(static_cast<char*>(p)+off,&v,8);}void integer(void*p,unsigned off,unsigned v){std::memcpy(static_cast<char*>(p)+off,&v,4);}
void event(unsigned n,void*p){num(n);ptr(p);}void swap(){if(input->mode==5)editorGlobal=editors[1];if(input->mode==6)static_cast<char*>(editorGlobal)[0x49]=1;}
void listState(List&v){num(v.count);num(v.capacity);num(v.grow);num(v.padding);num(v.data!=NULL);if(v.data)output->add(v.data,8*(v.capacity<8?8:v.capacity));}
void* scene(void*p,unsigned id){event(1,p);num(id);swap();return input->mode==3?NULL:scenes[input->seed%2];}
void* lookup(long long id){num(2);output->add(&id,8);swap();return input->mode==3?NULL:objects[0];}
bool isa(void*p,const std::wstring&a,const std::wstring&b){event(3,p);output->addText(a);output->addText(b);swap();return input->seed&1;}
int save(void*p,std::wstring filename,List*selection){event(4,p);output->addText(filename);ptr(selection);if(selection)listState(*selection);swap();return int(input->seed*1234567u);}
bool fileExists(const std::wstring&filename){num(5);output->addText(filename);swap();return input->seed&1;}
void clearLayouts(){num(6);swap();if(input->mode==7)*reinterpret_cast<std::wstring*>(static_cast<char*>(objects[1])+0x168)=L"changed first filename";}
void loadLayout(void*p,const std::wstring&filename,bool a,void*timer,bool b,bool c,unsigned seed){event(7,p);output->addText(filename);num(a);ptr(timer);num(b);num(c);num(seed);swap();}
void setInt(void*p,unsigned key,int value){event(8,p);num(key);num(value);swap();}
void setFloat(void*p,unsigned key,float value){event(9,p);num(key);output->add(&value,4);swap();}
void rescale(void*p){event(10,p);swap();}
void* files(){num(11);swap();return services[0];}
void fileInfo(void*p,const std::wstring&filename,CFileInfo&info,bool a,bool b,bool c){event(12,p);output->addText(filename);output->addText(info.m_sModName);output->addText(info.m_sResourceName);output->addText(info.m_sPath);num(info.m_eFormat);num(info.m_eLocation);output->addText(info.m_sResourceGroup);num(info.m_bExists);num(a);num(b);num(c);info.m_sModName="test";info.m_sPath=L"resolved";info.m_eLocation=1;info.m_bExists=input->seed&1;swap();}
void begin(void*p){event(13,p);swap();}
void end(void*p){event(14,p);}
void update(void*p,int eventCode){event(15,p);num(eventCode);swap();
 List*v=reinterpret_cast<List*>(static_cast<char*>(managers[editorGlobal==editors[1]])+0x40);
 if(input->mode==7){v->count=1;v->data[0]=objects[6];}
 if(input->mode==8)v->count=(input->seed/11)%4;
 if(input->mode==9)static_cast<char*>(managers[0])[0x79]=1;
 if(input->mode==10)static_cast<char*>(editorGlobal)[0x164]=1;
 if(input->mode==11)put(editorGlobal,0x120,NULL);
}
void aspect(void*p,float x,float y){event(16,p);output->add(&x,4);output->add(&y,4);swap();}
void* client(void*p){event(17,p);swap();return services[1];}
void* snap(void*p,int kind){event(18,p);num(kind);swap();return input->mode==7?NULL:&snapList;}
void initList(void*p,unsigned count,unsigned cap){List&v=*new(p)List;v.data=new void*[cap<8?8:cap];v.count=count;v.capacity=cap;v.grow=2;v.padding=0x51;for(unsigned i=0;i<(cap<8?8:cap);++i)v.data[i]=objects[i%8];}
void mapState(Map&m){num(m.size());for(Map::iterator i=m.begin();i!=m.end();++i){output->add(&i->first,8);ptr(i->second);}}
void side(Case&c,bool ours,autotest::Capture&out){
 input=&c;output=&out;unsigned long long ed[2][64]={{0}},man[2][16]={{0}},obj[8][128]={{0}},sc[2][64]={{0}},res[2][8]={{0}},set[2][8]={{0}},srv[4][8]={{0}};
 for(unsigned i=0;i<2;++i){editors[i]=ed[i];managers[i]=man[i];scenes[i]=sc[i];resources[i]=res[i];settings[i]=set[i];}
 for(unsigned i=0;i<4;++i)services[i]=srv[i];for(unsigned i=0;i<8;++i){objects[i]=obj[i];put(objects[i],0,(i==0?roomTable:i%3?layoutTable:objectTable)+2);long long id=static_cast<long long>(c.seed)*0x123456789LL+i*31;std::memcpy(static_cast<char*>(objects[i])+0x10,&id,8);put(objects[i],0x48,scenes[(i+c.seed)%2]);new(static_cast<char*>(objects[i])+0x168)std::wstring(i%2?L"layout one.dat":L"\u043c\u043e\u0434.layout");}
 if(c.mode==4)put(objects[0],0,objectTable+2);
 void* resourceTable[11]={0};resourceTable[2]=reinterpret_cast<void*>(&update);resourceTable[9]=reinterpret_cast<void*>(&aspect);resourceTable[10]=reinterpret_cast<void*>(&client);
 void* snapTable[3]={0,0,reinterpret_cast<void*>(&snap)};put(objects[0],0x100,snapTable);
 for(unsigned i=0;i<2;++i){put(resources[i],0,resourceTable);put(editors[i],0x58,c.mode==2?NULL:resources[i]);put(editors[i],0x120,managers[i]);put(editors[i],0x50,settings[i]);put(editors[i],0x128,services[2]);static_cast<char*>(editors[i])[0x49]=c.mode==1;
  maps[i]=new(static_cast<char*>(managers[i])+0x10)Map;for(unsigned j=0;j<(c.seed/12)%8;++j)(*maps[i])[static_cast<long long>(j*100+7)]=objects[j];
  initList(static_cast<char*>(managers[i])+0x40,(c.seed/12)%4,c.mode==9?0:8);initList(static_cast<char*>(managers[i])+0x58,(c.seed/24)%4,8);static_cast<char*>(managers[i])[0x79]=(c.seed/36)%2;
  std::wstring*debug=new(static_cast<char*>(editors[i])+0x1a8)std::wstring;const unsigned lengths[]={0,1,7,31,998,999};*debug=std::wstring(lengths[(c.seed/12)%6],static_cast<wchar_t>(0x410+i));
  Names*names=new(static_cast<char*>(editors[i])+0xd8)Names;(*names)[L"scene"]=(c.seed*34567u);(*names)[L"\u0438\u043c\u044f"]=(c.seed&1)?0xffffffffu:0;
  Map*m=new(static_cast<char*>(scenes[i])+0x108)Map;const unsigned counts[]={0,1,9,499,501};unsigned count=c.op==11?counts[(c.seed/12)%5]:c.seed%6;for(unsigned j=0;j<count;++j)(*m)[static_cast<long long>(j)*0x123456789LL+c.seed]=objects[j%8];
 }
 if(c.mode==3&&(c.op==6||c.op==10))put(editors[0],0x120,NULL);
 if(c.op==6&&c.mode==11)for(unsigned i=0;i<2;++i)for(Map::iterator it=maps[i]->begin();it!=maps[i]->end();++it)if(it->first%3==1)it->second=NULL;
 objectIterator=maps[0]->begin();for(unsigned i=0;i<c.index%3&&objectIterator!=maps[0]->end();++i)++objectIterator;
 editorGlobal=editors[0];std::memset(editorMemory,c.seed|0x81,4000);
 unsigned values[1000];for(unsigned i=0;i<1000;++i)values[i]=(c.seed*11177+i*131);const unsigned sizes[]={0,1,7,998,999,1000000};snapList.data=reinterpret_cast<void**>(values);snapList.count=sizes[(c.seed/12)%6];snapList.capacity=1000;snapList.grow=2;snapList.padding=0;
 unsigned count=0xabcd1234;wchar_t text[64]=L"scene";if((c.seed/12)%3==1)std::wcscpy(text,L"\u0438\u043c\u044f");if((c.seed/12)%3==2)std::wcscpy(text,L"missing name");wchar_t parent[64]=L"parent \u03a9";
 detour::Set patches;
 TL_REDIRECT(patches,target_scene,&scene);
 TL_REDIRECT(patches,target_lookup,&lookup);
 TL_REDIRECT(patches,target_isa,&isa);
 TL_REDIRECT(patches,target_save,&save);
 TL_REDIRECT(patches,target_fileExists,&fileExists);
 TL_REDIRECT(patches,target_clearLayouts,&clearLayouts);
 TL_REDIRECT(patches,target_loadLayout,&loadLayout);
 TL_REDIRECT(patches,target_setInt,&setInt);
 TL_REDIRECT(patches,target_setFloat,&setFloat);
 TL_REDIRECT(patches,target_rescale,&rescale);
 TL_REDIRECT(patches,target_files,&files);
 TL_REDIRECT(patches,target_fileInfo,&fileInfo);
 TL_REDIRECT(patches,target_begin,&begin);
 TL_REDIRECT(patches,target_end,&end);
 if(patches.failed())_exit(41);
 switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,c.seed,c.index);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,text,parent);break;
 case 2:{void*(*fn)()=ours?candidate2:original2;if(!autotest::beginInvocation(out,fn))return;void*v=fn();out.callCompleted=1;ptr(v);break;}
 case 3:{void*(*fn)()=ours?candidate3:original3;if(!autotest::beginInvocation(out,fn))return;void*v=fn();out.callCompleted=1;ptr(v);break;}
 case 4:{void*(*fn)(long long,unsigned*,bool,bool,bool)=ours?candidate4:original4;if(!autotest::beginInvocation(out,fn))return;void*v=fn((long long)c.seed,&count,(c.seed&1)!=0,(c.seed&2)!=0,(c.seed&4)!=0);out.callCompleted=1;ptr(v);break;}
 case 5:autotest::invoke(out,ours?candidate5:original5,c.seed,text,(c.seed&1)!=0);break;
 case 6:autotest::invoke(out,ours?candidate6:original6);break;
 case 7:autotest::invoke(out,ours?candidate7:original7,c.seed%4==0?0xffffffffu:c.seed*997,c.seed%4==1?0xffffffffu:c.seed*701);break;
 case 8:{void*(*fn)(unsigned*)=ours?candidate8:original8;if(!autotest::beginInvocation(out,fn))return;void*v=fn(&count);out.callCompleted=1;ptr(v);break;}
 case 9:autotest::invoke(out,ours?candidate9:original9,text);break;
 case 10:autotest::invoke(out,ours?candidate10:original10,(int)(c.seed*1234567u));break;
 case 11:{void*(*fn)(unsigned,unsigned*)=ours?candidate11:original11;if(!autotest::beginInvocation(out,fn))return;void*v=fn(c.seed,&count);out.callCompleted=1;ptr(v);break;}
 case 12:autotest::invoke(out,ours?candidate12:original12,editors[0],c.mode==4?NULL:text);break;

 }
 num(count);out.add(editorMemory,4000);ptr(editorGlobal);
 for(unsigned j=0;j<2;++j){mapState(*maps[j]);mapState(*reinterpret_cast<Map*>(static_cast<char*>(scenes[j])+0x108));Names&names=*reinterpret_cast<Names*>(static_cast<char*>(editors[j])+0xd8);num(names.size());for(Names::iterator i=names.begin();i!=names.end();++i){out.addText(i->first);num(i->second);}
  unsigned pos=0;Map::iterator it=maps[j]->begin();while(it!=maps[j]->end()&&it!=objectIterator){++it;++pos;}num(it==objectIterator?pos:0xffffffffu);
  out.addText(*reinterpret_cast<std::wstring*>(static_cast<char*>(editors[j])+0x1a8));std::memset(static_cast<char*>(editors[j])+0x1a8,0,8);std::memset(static_cast<char*>(editors[j])+0xd8,0,48);
  for(unsigned off=0x40;off<=0x58;off+=0x18){List&v=*reinterpret_cast<List*>(static_cast<char*>(managers[j])+off);listState(v);put(managers[j],off,NULL);}std::memset(static_cast<char*>(managers[j])+0x10,0,48);std::memset(static_cast<char*>(scenes[j])+0x108,0,48);
 }
 for(unsigned j=0;j<8;++j){out.addText(*reinterpret_cast<std::wstring*>(static_cast<char*>(objects[j])+0x168));std::memset(static_cast<char*>(objects[j])+0x168,0,8);}
 out.add(ed,sizeof(ed));out.add(man,sizeof(man));out.add(obj,sizeof(obj));out.add(sc,sizeof(sc));out.add(set,sizeof(set));out.add(res,sizeof(res));out.add(srv,sizeof(srv));patches.restore();
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
int run(const tlhybrid_host*host,unsigned first,unsigned last,const char*name){const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2,(uint64_t)(uintptr_t)original3,(uint64_t)(uintptr_t)original4,(uint64_t)(uintptr_t)original5,(uint64_t)(uintptr_t)original6,(uint64_t)(uintptr_t)original7,(uint64_t)(uintptr_t)original8,(uint64_t)(uintptr_t)original9,(uint64_t)(uintptr_t)original10,(uint64_t)(uintptr_t)original11,(uint64_t)(uintptr_t)original12};
 for(unsigned op=first;op<last;++op){autotest::Coverage coverage(name,addresses[op]);for(unsigned n=0;n<288;++n){Case c={op,n,n%12,(n/12)%5};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
  if(coverage.observe(host,a,b)){host->log("    editor operations %u/%u mode %u status %d/%d bytes %lu/%lu\n",op,n,c.mode,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);unsigned stop=a.capture.length<b.capture.length?a.capture.length:b.capture.length;for(unsigned i=0;i<stop;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    first byte %u: %u/%u\n",i,a.capture.data[i],b.capture.data[i]);break;}coverage.report(host);return 1;}
 }coverage.report(host);}return 0;}
}
TL_TEST(editor_operations_queries){return run(host,0,5,"editor_operations_queries");}
TL_TEST(editor_operations_resources){return run(host,5,10,"editor_operations_resources");}
TL_TEST(editor_operations_updates){return run(host,10,13,"editor_operations_updates");}
