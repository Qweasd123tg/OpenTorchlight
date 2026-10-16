// Independent lifetime oracle for original ELF 91b41ae9...41724b.
// Prepared with tu-4qv4tux0. No raw bytes stand in for owning C++ lifetimes.
// Constructor's load dependency is explicitly intercepted; load is tested separately.
#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <new>
#include <string>
#include <vector>
#define private public
#define protected public
#include "LevelTemplateData.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
#define LTL_PAIR(N,A,S) TL_ORIGINAL(void,ltlOld##N,A,S) extern "C" void ltlNew##N A __asm__(S);
LTL_PAIR(C1,(void*,const wchar_t*),"_ZN18CLevelTemplateDataC1EPKw")
LTL_PAIR(C2,(void*,const wchar_t*),"_ZN18CLevelTemplateDataC2EPKw")
LTL_PAIR(D1,(void*),"_ZN18CLevelTemplateDataD1Ev")
LTL_PAIR(D2,(void*),"_ZN18CLevelTemplateDataD2Ev")
LTL_PAIR(D0,(void*),"_ZN18CLevelTemplateDataD0Ev")
#undef LTL_PAIR
TL_FUNCTION(ltlLoad,"_ZN18CLevelTemplateData4loadEPKw")
TL_FUNCTION(ltlRandomCtor,"_ZN11CRandomizerC1E16ERANDOMIZER_TYPE")
TL_FUNCTION(ltlCoreDtor,"_ZN10CRunicCoreD1Ev")
extern "C" char ltlCopy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_");
extern "C" char ltlLiteral[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_");
extern "C" char ltlRepDestroy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_");
extern "C" char ltlStringDtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEED1Ev");
extern "C" char ltlScalarFree[] __asm__("_ZdlPv");
extern "C" char ltlArrayFree[] __asm__("_ZdaPv");
extern "C" char ltlObjectFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
namespace level_template_lifetime {
typedef std::wstring Wide;
typedef char OwnerABI[sizeof(CLevelTemplateData)==0x778 && sizeof(CRandomizer)==0x68 && sizeof(Wide)==8 ? 1 : -1];
struct Case { unsigned ctor,alias,shape,text,poison,fault; };
static const Case* input;
static const tlhybrid_host* context;
static autotest::Capture* capture;
static CLevelTemplateData* owner;
static unsigned errors,loadCalls,randomCalls,coreCalls,faultHits;
static bool active,constructing;
static int initialObjects;
static detour::Set *copyPatch,*literalPatch,*randomPatch,*corePatch,*repPatch,*stringPatch,*arrayPatch,*scalarPatch,*freePatch;
static void* forwardedRep;
static const wchar_t* filename;
static Wide* keepers;
static TSafePointer<CRunicCore>* witnesses;
static void* objects[48];static unsigned objectCount;
static void* allocations[256];static unsigned allocationKinds[256],allocationCount,freed[256];
static void* reps[39];static unsigned repReleased[39];
static unsigned coreSeen[48];static bool ownedObjects[48];static CChunkType* borrowedType;static CLevelLayout* borrowedLayout;
static const unsigned stringOffsets[39]={0x60,0x68,0xa0,0x518,0x520,0x528,0x530,0x538,0x540,0x548,0x550,0x558,0x560,0x568,0x570,0x578,0x580,0x588,0x590,0x598,0x5a0,0x5a8,0x5b0,0x5b8,0x5c0,0x5c8,0x698,0x6a0,0x6a8,0x6b0,0x6b8,0x6c0,0x6c8,0x6d0,0x6d8,0x6e0,0x6e8,0x6f0,0x770};
template<class T>T& at(void* p,unsigned offset){return *reinterpret_cast<T*>(static_cast<char*>(p)+offset);}
static void n(unsigned value){capture->add(&value,4);}
static void need(bool condition,unsigned code){if(!condition){++errors;n(0xf1000000u+code);}}
// Despite its name, the original counter only increments in C1; D1 never decrements.
static int constructedCount(){return *reinterpret_cast<int*>(0x150b420);}
static int refs(const Wide& s){return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(s.c_str())-8);}
static unsigned offset(const void* p){uintptr_t a=reinterpret_cast<uintptr_t>(p),b=reinterpret_cast<uintptr_t>(owner);return a>=b&&a<b+0x778?unsigned(a-b):~0u;}
static int objectID(const void* p){for(unsigned i=0;i<objectCount;++i)if(objects[i]==p)return i;return -1;}
static unsigned remember(void* p){need(objectCount<48,1);unsigned id=objectCount++;objects[id]=p;ownedObjects[id]=true;return id;}
static void watch(void* p){unsigned id=remember(p);witnesses[id].setObject(static_cast<CRunicCore*>(p));}
static void allocation(void* p,unsigned kind){if(!p)return;for(unsigned i=0;i<allocationCount;++i)if(allocations[i]==p){need(false,2);return;}need(allocationCount<256,3);allocations[allocationCount]=p;allocationKinds[allocationCount++]=kind;}
static void raw(unsigned off,unsigned size){capture->add(reinterpret_cast<char*>(owner)+off,size);}
// Observe only scalar object representations, including poison before initialization.
// Never inspect an unconstructed string/list through its C++ API. Padding, vptrs,
// pointers, and the genuinely uninitialized fog/direction fields are excluded.
static void scalarSnapshot(){
 static const unsigned spans[][2]={{0x58,3},{0x70,3},{0x74,40},{0xa8,12},{0x5d0,11},{0x5dc,0xbc},{0x700,80},{0x760,13}};
 for(unsigned i=0;i<sizeof(spans)/sizeof(spans[0]);++i)raw(spans[i][0],spans[i][1]);
 static const unsigned lists[]={0x10,0x28,0x40,0xb8,0xd0,0xf0};
 for(unsigned i=0;i<6;++i)raw(lists[i]+8,12);
 for(unsigned i=0;i<10;++i){unsigned r=0x108+i*0x68;for(unsigned j=0;j<3;++j)raw(r+0x18+j*24,12);raw(r+0x58,9);}
}
static void constructedString(Wide* value){unsigned off=offset(value);for(unsigned i=0;i<39;++i)if(stringOffsets[i]==off&&!value->empty())reps[i]=const_cast<char*>(reinterpret_cast<const char*>(value->c_str()))-24;}
static void boundary(unsigned off){if(!active||!constructing)return;n(1000+off);scalarSnapshot();if(input->fault==off){++faultHits;throw std::bad_alloc();}}
static void copy(Wide* dest,const Wide& src){unsigned off=offset(dest);if(off!=~0u)boundary(off);copyPatch->restore();reinterpret_cast<void(*)(Wide*,const Wide&)>(ltlCopy)(dest,src);if(active&&constructing&&off!=~0u)constructedString(dest);copyPatch->redirect(ltlCopy,ltlCopy,&copy);need(!copyPatch->failed(),4);}
static void literal(Wide* dest,const wchar_t* src,const void* allocator){unsigned off=offset(dest);if(off!=~0u)boundary(off);literalPatch->restore();reinterpret_cast<void(*)(Wide*,const wchar_t*,const void*)>(ltlLiteral)(dest,src,allocator);if(active&&constructing&&off!=~0u)constructedString(dest);literalPatch->redirect(ltlLiteral,ltlLiteral,&literal);need(!literalPatch->failed(),5);}
static void randomCtor(CRandomizer* p,int type){unsigned off=offset(p);if(active&&constructing){boundary(off);need(off==0x108+randomCalls*0x68&&type==0,6);++randomCalls;}randomPatch->restore();reinterpret_cast<void(*)(CRandomizer*,int)>(ltlRandomCtor_original)(p,type);TL_REDIRECT(*randomPatch,ltlRandomCtor,&randomCtor);need(!randomPatch->failed(),7);}
static void load(CLevelTemplateData* p,const wchar_t* name){if(!active)return;++loadCalls;need(p==owner&&name==filename,8);n(5000);if(input->ctor){for(unsigned i=0;i<39;++i)constructedString(&at<Wide>(owner,stringOffsets[i]));scalarSnapshot();if(input->fault==0x1000){++faultHits;throw std::bad_alloc();}}}
static void releaseRep(void* rep){if(!active)return;for(unsigned i=0;i<39;++i)if(reps[i]==rep){++repReleased[i];n(6000+i);need(repReleased[i]==1,9);}}
static void repDestroy(void* rep,const void* allocator){if(rep!=forwardedRep)releaseRep(rep);repPatch->restore();reinterpret_cast<void(*)(void*,const void*)>(ltlRepDestroy)(rep,allocator);repPatch->redirect(ltlRepDestroy,ltlRepDestroy,&repDestroy);need(!repPatch->failed(),10);}
static void stringDtor(Wide* value){void* rep=const_cast<char*>(reinterpret_cast<const char*>(value->c_str()))-24;void* prior=forwardedRep;forwardedRep=rep;bool unique=!value->empty()&&refs(*value)<1;stringPatch->restore();reinterpret_cast<void(*)(Wide*)>(ltlStringDtor)(value);if(unique)releaseRep(rep);stringPatch->redirect(ltlStringDtor,ltlStringDtor,&stringDtor);forwardedRep=prior;need(!stringPatch->failed(),11);}
static void coreDtor(CRunicCore* p){
 if(active){++coreCalls;int id=objectID(p);if(id>=0){++coreSeen[id];n(7000+id);need(coreSeen[id]==1,12);}
 else {unsigned off=offset(p);need(constructing&&off>=0x108&&off<=0x4b0&&(off-0x108)%0x68==0,13);n(7100+off);}
 }
 corePatch->restore();reinterpret_cast<void(*)(CRunicCore*)>(ltlCoreDtor_original)(p);TL_REDIRECT(*corePatch,ltlCoreDtor,&coreDtor);need(!corePatch->failed(),14);
}
static void freeObserved(void* p,unsigned kind){if(!active)return;for(unsigned i=0;i<allocationCount;++i)if(allocations[i]==p){need(allocationKinds[i]==kind,15);need(!freed[i],16);++freed[i];n(8000+i);n(kind);return;}}
static void arrayFree(void* p){freeObserved(p,1);arrayPatch->restore();reinterpret_cast<void(*)(void*)>(ltlArrayFree)(p);arrayPatch->redirect(ltlArrayFree,ltlArrayFree,&arrayFree);need(!arrayPatch->failed(),17);}
static void scalarFree(void* p){freeObserved(p,3);scalarPatch->restore();reinterpret_cast<void(*)(void*)>(ltlScalarFree)(p);scalarPatch->redirect(ltlScalarFree,ltlScalarFree,&scalarFree);need(!scalarPatch->failed(),35);}
static void objectFree(void* p){freeObserved(p,2);freePatch->restore();reinterpret_cast<void(*)(void*)>(ltlObjectFree)(p);freePatch->redirect(ltlObjectFree,ltlObjectFree,&objectFree);need(!freePatch->failed(),18);}
static void reset(const Case& c,autotest::Capture& out){input=&c;capture=&out;errors=loadCalls=randomCalls=coreCalls=faultHits=objectCount=allocationCount=0;active=constructing=false;forwardedRep=0;borrowedType=0;borrowedLayout=0;std::memset(freed,0,sizeof(freed));std::memset(coreSeen,0,sizeof(coreSeen));std::memset(reps,0,sizeof(reps));std::memset(repReleased,0,sizeof(repReleased));
 // Original TU global constructors have not run at this headless boundary.
 new(reinterpret_cast<void*>(0x1495cc8))Wide();
 owner=static_cast<CLevelTemplateData*>(Ogre::NedAllocImpl::allocBytes(0x778,0,0,0));std::memset(owner,c.poison?0xa5:0x5a,0x778);initialObjects=constructedCount();filename=c.text==0?0:c.text==1?L"":c.text==2?L"fixture/unicode_\u041a\u4e2d.dat":L"fixture/long_name_for_constructor_forwarding.dat";
}
static bool mapped(uintptr_t a,uintptr_t b){return a==b||(context->comparison_pair&&context->comparison_pair(a,b));}
static void normalized(bool candidate){
 scalarSnapshot();need(constructedCount()-initialObjects==11,19);need(!owner->m_layoutRandomizer,20);
 uintptr_t* v=*reinterpret_cast<uintptr_t**>(owner);need(v&&reinterpret_cast<std::ptrdiff_t*>(v)[-2]==0,21);if(v){need(candidate?mapped(0x975370,v[0]):v[0]==0x975370,22);need(candidate?mapped(0x9762d0,v[1]):v[1]==0x9762d0,23);}
 for(unsigned i=0;i<39;++i)capture->addText(at<Wide>(owner,stringOffsets[i]));
 static const unsigned lists[]={0x10,0x28,0x40,0xb8,0xd0,0xf0};for(unsigned i=0;i<6;++i){need(!at<void*>(owner,lists[i]),24);need(!at<unsigned>(owner,lists[i]+8)&&!at<unsigned>(owner,lists[i]+12),25);need(at<unsigned>(owner,lists[i]+16)==(i==5?2u:10u),26);}
 for(unsigned i=0;i<10;++i){CRandomizer& r=at<CRandomizer>(owner,0x108+i*0x68);need(!r.m_Choices.m_pData&&!r.m_Odds.m_pData&&!r.m_ComputedOdds.m_pData,27);need(r.m_eType==RANDOMIZER_NORMAL&&r.m_fDecay==1.0f&&r.m_bOddsDirty,28);}
 // Untouched source fields remain poisoned, without reading them as floats.
 const unsigned untouched[]={0x6f8,0x6fc,0x750,0x754,0x758,0x75c};unsigned poison=input->poison?0xa5a5a5a5u:0x5a5a5a5au;for(unsigned i=0;i<6;++i){unsigned bits;std::memcpy(&bits,reinterpret_cast<char*>(owner)+untouched[i],4);need(bits==poison,29);n(bits);}
}
static void construct(void* p,autotest::Capture& out,bool candidate){
 Case& c=*static_cast<Case*>(p);reset(c,out);constructing=true;remember(owner);
 detour::Set loads,copies,literals,randoms,cores,representations,strings;repPatch=&representations;stringPatch=&strings;copyPatch=&copies;literalPatch=&literals;randomPatch=&randoms;corePatch=&cores;
 TL_REDIRECT(loads,ltlLoad,&load);copies.redirect(ltlCopy,ltlCopy,&copy);literals.redirect(ltlLiteral,ltlLiteral,&literal);TL_REDIRECT(randoms,ltlRandomCtor,&randomCtor);TL_REDIRECT(cores,ltlCoreDtor,&coreDtor);
 representations.redirect(ltlRepDestroy,ltlRepDestroy,&repDestroy);strings.redirect(ltlStringDtor,ltlStringDtor,&stringDtor);
 if(representations.failed()||strings.failed()||loads.failed()||copies.failed()||literals.failed()||randoms.failed()||cores.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Fn)(void*,const wchar_t*);Fn fn=candidate?(c.alias?ltlNewC2:ltlNewC1):(c.alias?ltlOldC2:ltlOldC1);bool threw=false;active=true;
 if(!autotest::beginInvocation(out,fn))return;try{fn(owner,filename);out.callCompleted=1;}catch(const std::bad_alloc&){threw=true;}
 need(threw==(c.fault!=0)&&faultHits==(c.fault?1u:0u),30);
 copies.restore();literals.restore();randoms.restore();
 if(!threw){need(randomCalls==10&&loadCalls==1,31);normalized(candidate);ltlOldD1(owner);}else need(loadCalls==(c.fault==0x1000?1u:0u),32);
 for(unsigned i=0;i<39;++i){need(repReleased[i]==(reps[i]?1u:0u),800+i);n(repReleased[i]);}
 need(constructedCount()==initialObjects+11,33);need(coreSeen[0]==1,34);active=false;Ogre::NedAllocImpl::deallocBytes(owner);n(0x4c544c46);n(errors);
}
static void ctorOriginal(void* p,autotest::Capture& o){construct(p,o,false);}static void ctorCandidate(void* p,autotest::Capture& o){construct(p,o,true);}
static void fillRandom(CRandomizer& r,unsigned seed){for(unsigned i=0;i<1+seed%4;++i){r.m_Choices.add(int(100+seed*7+i));r.m_Odds.add(float(i+1));r.m_ComputedOdds.add(float(i+1)/10);}r.m_bOddsDirty=seed&1;}
static void trackRandom(CRandomizer& r){allocation(r.m_Choices.m_pData,1);allocation(r.m_Odds.m_pData,1);allocation(r.m_ComputedOdds.m_pData,1);}
static void trackSafe(CRunicCore* p){if(p->m_pSafePointers){allocation(p->m_pSafePointers->m_pData,1);allocation(p->m_pSafePointers,2);}}
static void childString(Wide& s,unsigned id){s=Wide(40+id,wchar_t(L'A'+id%24));s[3]=0;s[7]=L'\u03a9';}
static void setupGraph(unsigned shape){
 watch(owner);for(unsigned i=0;i<10;++i){CRandomizer* r=&at<CRandomizer>(owner,0x108+i*0x68);watch(r);if(shape)fillRandom(*r,i);}
 if(!shape)return;
 owner->m_layoutRandomizer=new CRandomizer(RANDOMIZER_DECAY);watch(owner->m_layoutRandomizer);fillRandom(*owner->m_layoutRandomizer,20);allocation(owner->m_layoutRandomizer,2);
 for(unsigned i=0;i<3;++i){if(i==1&&shape==2){owner->m_chunkRandomizers.add(0);continue;}CRandomizer* r=new CRandomizer(RANDOMIZER_NORMAL);watch(r);fillRandom(*r,30+i);owner->m_chunkRandomizers.add(r);allocation(r,2);}
 for(unsigned i=0;i<3;++i){CChunk* ch=new CChunk;watch(ch);ch->m_chunkValue10=int(i);ch->m_odds=int(i*3+1);ch->m_maxAppearance=10;childString(ch->m_filename,i);owner->m_chunks.add(ch);allocation(ch,2);}
 if(shape==2)owner->m_chunks.add(0);
 for(unsigned i=0;i<2;++i){CChunkType* t=new CChunkType;watch(t);t->m_entranceChunk=i==0;t->m_exitChunk=i==1;t->m_registeredWithRandomizers=true;t->m_mustPlace=false;t->m_width=2;t->m_height=3;t->m_maxAppearance=4;childString(t->m_folder,4+i);childString(t->m_name,8+i);t->m_inclusiveFiles.add(Wide(L"one"));t->m_inclusiveFiles.add(Wide(L"two"));t->m_exits.add(Ogre::Vector3(1,2,3));owner->m_chunkTypes.add(t);owner->m_requiredChunkTypes.add(t);owner->m_requiredChunkTypes.add(t);allocation(t,2);allocation(reinterpret_cast<char*>(t->m_inclusiveFiles.m_pData)-sizeof(size_t),1);allocation(t->m_exits.m_pData,1);}
 if(shape==2){owner->m_chunkTypes.add(0);owner->m_requiredChunkTypes.add(0);}
 for(unsigned i=0;i<2;++i){CLevelLayout* l=new CLevelLayout;watch(l);l->m_seed=123+i;l->m_chunks.add(owner->m_chunks[0]);l->m_chunks.add(owner->m_chunks[1]);l->m_chunks.add(owner->m_chunks[0]);for(unsigned j=0;j<2;++j){CChunkInstance* ci=new CChunkInstance;watch(ci);ci->m_chunkTypeIndex=j;ci->m_x=float(i);ci->m_y=0;ci->m_z=float(j);childString(ci->m_name,12+i*2+j);ci->m_usedExits.push_back(1);ci->m_usedExits.push_back(4);l->m_chunkInstances.add(ci);allocation(ci,2);allocation(&ci->m_usedExits[0],3);}if(shape==2)l->m_chunkInstances.add(0);owner->m_layouts.add(l);owner->m_baseLayouts.add(l);allocation(l,2);allocation(l->m_chunks.m_pData,1);allocation(l->m_chunkInstances.m_pData,1);}
 if(shape==2){owner->m_layouts.add(0);owner->m_baseLayouts.add(owner->m_layouts[0]);}
 if(shape==3){owner->m_requiredChunkTypes.m_nCount=0;owner->m_baseLayouts.m_nCount=0;}
 if(shape==4){borrowedType=new CChunkType;watch(borrowedType);ownedObjects[objectCount-1]=false;owner->m_requiredChunkTypes.add(borrowedType);borrowedLayout=new CLevelLayout;watch(borrowedLayout);ownedObjects[objectCount-1]=false;owner->m_baseLayouts.add(borrowedLayout);}
}
static void destroy(void* p,autotest::Capture& out,bool candidate){
 Case& c=*static_cast<Case*>(p);reset(c,out);Wide retained[39];keepers=retained;TSafePointer<CRunicCore> safe[48];witnesses=safe;
 detour::Set loads;TL_REDIRECT(loads,ltlLoad,&load);if(loads.failed()){out.issue=autotest::Capture::InvalidReport;return;}ltlOldC1(owner,0);setupGraph(c.shape);
 for(unsigned i=0;i<39;++i){Wide& s=at<Wide>(owner,stringOffsets[i]);if(c.text==0){s.clear();continue;}childString(s,i);if(c.text==2){Wide shareable(s.data(),s.size());s.swap(shareable);keepers[i]=s;need(s.c_str()==keepers[i].c_str()&&refs(s)==1,36);}else reps[i]=const_cast<char*>(reinterpret_cast<const char*>(s.c_str()))-24;}
 allocation(owner,2);allocation(owner->m_chunkTypes.m_pData,1);allocation(owner->m_chunks.m_pData,1);allocation(owner->m_requiredChunkTypes.m_pData,1);allocation(owner->m_layouts.m_pData,1);allocation(owner->m_baseLayouts.m_pData,1);allocation(owner->m_chunkRandomizers.m_pData,1);
 for(unsigned i=0;i<10;++i)trackRandom(at<CRandomizer>(owner,0x108+i*0x68));if(owner->m_layoutRandomizer)trackRandom(*owner->m_layoutRandomizer);for(unsigned i=0;i<owner->m_chunkRandomizers.size();++i)if(owner->m_chunkRandomizers[i])trackRandom(*owner->m_chunkRandomizers[i]);for(unsigned i=0;i<objectCount;++i)if(ownedObjects[i])trackSafe(static_cast<CRunicCore*>(objects[i]));
 detour::Set cores,representations,strings,arrays,scalars,frees;corePatch=&cores;repPatch=&representations;stringPatch=&strings;arrayPatch=&arrays;scalarPatch=&scalars;freePatch=&frees;
 TL_REDIRECT(cores,ltlCoreDtor,&coreDtor);representations.redirect(ltlRepDestroy,ltlRepDestroy,&repDestroy);strings.redirect(ltlStringDtor,ltlStringDtor,&stringDtor);arrays.redirect(ltlArrayFree,ltlArrayFree,&arrayFree);scalars.redirect(ltlScalarFree,ltlScalarFree,&scalarFree);frees.redirect(ltlObjectFree,ltlObjectFree,&objectFree);
 if(cores.failed()||representations.failed()||strings.failed()||arrays.failed()||scalars.failed()||frees.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Fn)(void*);Fn fn=candidate?(c.alias==0?ltlNewD1:c.alias==1?ltlNewD2:ltlNewD0):(c.alias==0?ltlOldD1:c.alias==1?ltlOldD2:ltlOldD0);active=true;autotest::invoke(out,fn,owner);active=false;
 // The deleting destructor may already have freed owner; only external witnesses
 // and tracked allocation tokens are read here, never a dead object's fields.
 for(unsigned i=0;i<objectCount;++i){need(ownedObjects[i]?!witnesses[i].getObject():witnesses[i].getObject()==objects[i],40+i);need(coreSeen[i]==(ownedObjects[i]?1u:0u),100+i);need(at<unsigned>(&witnesses[i],8)==(ownedObjects[i]?~0u:0u),900+i);n(coreSeen[i]);}
 for(unsigned i=0;i<allocationCount;++i){unsigned want=allocations[i]==owner?(c.alias==2?1u:0u):1u;need(freed[i]==want,200+i);n(freed[i]);}
 for(unsigned i=0;i<39;++i){need(repReleased[i]==(c.text==1?1u:0u),500+i);n(repReleased[i]);if(c.text==2){need(refs(keepers[i])==0,600+i);capture->addText(keepers[i]);}}
 need(constructedCount()==initialObjects+int(objectCount),700);delete borrowedType;delete borrowedLayout;need(constructedCount()==initialObjects+int(objectCount),701);if(c.alias!=2)Ogre::NedAllocImpl::deallocBytes(owner);n(0x4c544c46);n(errors);
}
static void dtorOriginal(void* p,autotest::Capture& o){destroy(p,o,false);}static void dtorCandidate(void* p,autotest::Capture& o){destroy(p,o,true);}
static bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0x4c544c46&&!tail[1];}
static bool pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case& c){context=host;autotest::Outcome a,b;autotest::runChild(c.ctor?ctorOriginal:dtorOriginal,&c,a);autotest::runChild(c.ctor?ctorCandidate:dtorCandidate,&c,b);bool ok=good(a)&&good(b)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
 if(!c.fault){if(coverage.observe(host,a,b))ok=false;}else ok=ok&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==coverage.original&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget);
 if(!ok){host->log("tlhybrid: LevelTemplate lifetime ctor=%u alias=%u shape=%u text=%u poison=%u fault=%x status=%d/%d valid=%u/%u bytes=%lu/%lu\n",c.ctor,c.alias,c.shape,c.text,c.poison,c.fault,a.childStatus,b.childStatus,good(a),good(b),(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned i=0;i<a.capture.length&&i<b.capture.length;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("tlhybrid: first difference %u = %u/%u\n",i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]);break;}for(unsigned side=0;side<2;++side){const autotest::Capture& z=side?b.capture:a.capture;for(size_t i=0;i+4<=z.length;i+=4){unsigned v;std::memcpy(&v,z.data+i,4);if((v&0xffff0000u)==0xf1000000u)host->log("tlhybrid: side %u semantic check %u at byte %lu\n",side,v-0xf1000000u,(unsigned long)i);}}}return ok;
}
}
TL_TEST(level_template_constructor_lifetime){using namespace level_template_lifetime;autotest::Coverage cv("level_template_constructor_lifetime",0x97bfa0);for(unsigned alias=0;alias<2;++alias)for(unsigned text=0;text<4;++text)for(unsigned poison=0;poison<2;++poison){Case c={1,alias,0,text,poison,0};if(!pair(host,cv,c)){cv.report(host);return 1;}}cv.report(host);return cv.completed!=16||cv.different||cv.missing;}
TL_TEST(level_template_constructor_unwind){using namespace level_template_lifetime;autotest::Coverage cv("expected constructor unwinds excluded",0x97bfa0);const unsigned faults[]={0x518,0x6d0,0x6d8,0x6e0,0x6e8,0x6f0,0x770,0x1000};for(unsigned alias=0;alias<2;++alias)for(unsigned i=0;i<8;++i){Case c={1,alias,0,2,i&1,faults[i]};if(!pair(host,cv,c))return 1;}host->log("tlhybrid: LevelTemplate C1/C2: 16 expected dependency-boundary bad_alloc unwinds, no completed-call credit\n");return 0;}
TL_TEST(level_template_destructor_lifetime)
{
    using namespace level_template_lifetime;
    autotest::Coverage d1("level_template_destructor_lifetime",0x975370);
    autotest::Coverage d0("level_template_deleting_destructor_lifetime",0x9762d0);
    unsigned failures=0;
    // Every case runs in fresh children. A differential failure must not hide
    // later aliases: the negative-control runner requires complete D0 evidence.
    for(unsigned alias=0;alias<3;++alias)
        for(unsigned shape=0;shape<5;++shape)
            for(unsigned text=0;text<3;++text)
                for(unsigned poison=0;poison<2;++poison)
                {
                    Case c={0,alias,shape,text,poison,0};
                    if(!pair(host,alias==2?d0:d1,c))
                        ++failures;
                }
    d1.report(host);
    d0.report(host);
    return failures || d1.completed!=60 || d0.completed!=30 ||
        d1.different || d0.different || d1.missing || d0.missing;
}
