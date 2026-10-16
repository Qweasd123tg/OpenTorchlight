// Bounded constructor/setter comparison. update, file lookup and image decoding
// are collaborator boundaries; this test makes no rendering/update coverage claim.
#include "AutoTest.h"
#include "ObservedWitness.h"
#include "Detour.h"
#include "Wardrobe.h"
#include "FileSystem.h"
#include <OgreImage.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreTextureManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreLogManager.h>
#include <new>
#include <cstring>

#define CTOR_ARGS (CWardrobe*, CCharacter*, Ogre::SceneManager*, Ogre::SceneManager*, CGenericModel*, CGenericModel*, std::wstring, std::wstring, std::wstring, std::wstring, std::wstring, std::wstring)
#define CTOR_NAME "_ZN9CWardrobeC1EP10CCharacterPN4Ogre12SceneManagerES4_P13CGenericModelS6_SbIwSt11char_traitsIwESaIwEESA_SA_SA_SA_SA_"
TL_ORIGINAL(void,oldCtor,CTOR_ARGS,CTOR_NAME)
extern "C" void newCtor CTOR_ARGS __asm__(CTOR_NAME);
TL_ORIGINAL(void,oldSetter,(CWardrobe*,EWardrobeSlot,std::wstring),"_ZN9CWardrobe14setBaseTextureE13EWardrobeSlotSbIwSt11char_traitsIwESaIwEE")
extern "C" void newSetter(CWardrobe*,EWardrobeSlot,std::wstring) __asm__("_ZN9CWardrobe14setBaseTextureE13EWardrobeSlotSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(updateFn,"_ZN9CWardrobe6updateEP10CInventory")
TL_FUNCTION(fileSingleton,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(fileInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
extern "C" char imageLoad[] __asm__("_ZN4Ogre5Image4loadERKSsS2_");
TL_FUNCTION(uniqueName,"_ZN7STRINGS10uniqueNameERKSs")
namespace {
// Bundled library extent checks. ResourceGroupManager is a Runic fork and
// deliberately is NOT instantiated from its shorter vanilla SDK declaration.
typedef char resourceSize[sizeof(Ogre::Resource)==0x78?1:-1];
typedef char resourceManagerSize[sizeof(Ogre::ResourceManager)==0xb0?1:-1];
typedef char textureSize[sizeof(Ogre::Texture)==0xe8?1:-1];
typedef char textureManagerSize[sizeof(Ogre::TextureManager)==0xc0?1:-1];
typedef char imageSize[sizeof(Ogre::Image)==0x50?1:-1];
typedef char logManagerSize[sizeof(Ogre::LogManager)==0x38?1:-1];
extern "C" void groupConstruct(void*) __asm__("_ZN4Ogre20ResourceGroupManagerC1Ev");
extern "C" void groupDestroy(void*) __asm__("_ZN4Ogre20ResourceGroupManagerD1Ev");
void require(bool);
unsigned logsCreated, logsDestroyed, groupsCreated, groupsDestroyed;
class OptionalLogManager {
    Ogre::LogManager* before;
    Ogre::LogManager* owned;
    OptionalLogManager(const OptionalLogManager&);
    OptionalLogManager& operator=(const OptionalLogManager&);
public:
    OptionalLogManager():before(Ogre::LogManager::getSingletonPtr()),owned(0) {
        // A prior test may already own the genuine service. Never replace it.
        if(!before){owned=new Ogre::LogManager;++logsCreated;}
        require(Ogre::LogManager::getSingletonPtr()==(owned?owned:before));
    }
    ~OptionalLogManager(){
        require(Ogre::LogManager::getSingletonPtr()==(owned?owned:before));
        if(owned){delete owned;++logsDestroyed;}
        require(Ogre::LogManager::getSingletonPtr()==before);
    }
};
class OriginalResourceGroups {
    Ogre::ResourceGroupManager* before;
    void* storage;
    OriginalResourceGroups(const OriginalResourceGroups&);
    OriginalResourceGroups& operator=(const OriginalResourceGroups&);
public:
    // Root at 0x2736a4 requests 0x118; alloc at 0x27370e, C1 at 0x273719.
    OriginalResourceGroups():before(Ogre::ResourceGroupManager::getSingletonPtr()),storage(0) {
        if(!before){
            storage=Ogre::NedAllocImpl::allocBytes(0x118,0,0,0);
            try {groupConstruct(storage);++groupsCreated;}
            catch(...) {Ogre::NedAllocImpl::deallocBytes(storage);storage=0;throw;}
        }
        require(static_cast<void*>(Ogre::ResourceGroupManager::getSingletonPtr())==(storage?storage:before));
    }
    ~OriginalResourceGroups(){
        require(static_cast<void*>(Ogre::ResourceGroupManager::getSingletonPtr())==(storage?storage:before));
        if(storage){groupDestroy(storage);Ogre::NedAllocImpl::deallocBytes(storage);++groupsDestroyed;}
        require(Ogre::ResourceGroupManager::getSingletonPtr()==before);
    }
};
struct Fault { unsigned site; explicit Fault(unsigned s):site(s){} };
struct Case { unsigned mask, variant, fault, slot, replace; };
Case* input; autotest::Capture* output; CWardrobe* owner;
unsigned lookups, loads, updates, creates, mipCalls, activeFault;
bool setterPhase;
unsigned oldDestroyed, textureConstructed, textureDestroyed;
unsigned char pixels[4][1024];
Ogre::Image* createdImages[8]; unsigned createdCount;
// These are opaque identity tokens only. Intercepted collaborators never
// dereference them or run a nontrivial object's method on their storage.
unsigned long identities[6];
void number(unsigned n){output->add(&n,sizeof n);}
void event(unsigned n){number(0xc0000000u|n);}
void require(bool b){if(!b)output->issue=autotest::Capture::InvalidReport;}
void stop(unsigned site){if(activeFault==site)throw Fault(site);}
template<class T> T* field(size_t at){return reinterpret_cast<T*>(reinterpret_cast<char*>(owner)+at);}
void snapshot(){
    for(unsigned i=0;i<4;++i){void* p;std::memcpy(&p,field<char>(0x10+8*i),8);unsigned id=0;for(unsigned j=0;j<6;++j)if(p==identities+j)id=j+1;require(!p||id!=0);number(id);}
    require(*field<void*>(0x28)==0);
    output->addText(*field<std::wstring>(0x30));
    for(unsigned i=0;i<5;++i){output->addText(owner->m_meshes[i]);output->addText(owner->m_textures[i]);}
    for(unsigned i=0;i<6;++i){Ogre::Image* im=*field<Ogre::Image*>(0x58+i*8);number(im?1:0);if(im){number(im->getWidth());number(im->getHeight());number(im->getNumMipmaps());number(im->getFormat());}}
    Ogre::TexturePtr& texture=*field<Ogre::TexturePtr>(0x38);number(texture.isNull()?0:1);if(!texture.isNull()){number(texture.useCount());number(texture->getNumMipmaps());}
    for(unsigned i=0;i<4;++i)require(*field<void*>(0xd8+8*i)==0);
    require(*field<void*>(0x100)==identities+1);
    require(*field<void*>(0xf8)==identities);
}
CFileSystem* singleton(){event(1);return reinterpret_cast<CFileSystem*>(identities+5);}
void lookup(CFileSystem* self,const std::wstring& path,CFileInfo& f,bool a,bool b,bool c){
    event(2);require(self==reinterpret_cast<CFileSystem*>(identities+5));output->addText(path);number(a);number(b);number(c);require(!a&&b&&!c);
    unsigned index=lookups++;require(index<(setterPhase?1u:4u));
    if(setterPhase){require(owner->m_textures[input->slot]==path);require(*field<Ogre::Image*>(0x60+8*input->slot)==0);require(oldDestroyed==(input->mask?1u:0u));}
    stop(1+index);
    f.m_bExists=setterPhase?(input->replace!=0):((input->mask&(1u<<index))!=0);
    f.m_sResourceName=std::string("fixture_")+char('0'+index);
    f.m_sResourceGroup=(input->variant&1)?"fixture_group":"";
    f.m_sPath=path;
}
Ogre::Image& load(Ogre::Image* im,const std::string& name,const std::string& group){
    event(3);output->addText(name);output->addText(group);require(group==((input->variant&1)?std::string("fixture_group"):Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));
    require(createdCount<8);if(createdCount<8)createdImages[createdCount++]=im;
    unsigned index=loads++;stop(10+index);
    unsigned w=(input->variant&2)?8:4,h=(input->variant&2)?4:2,m=(input->variant&4)?1:0;
    Ogre::PixelFormat format=(input->variant&4)?Ogre::PF_L8:Ogre::PF_A8R8G8B8;
    return im->loadDynamicImage(pixels[index%4],w,h,1,format,false,1,m);
}
std::string name(const std::string& prefix){event(4);output->addText(prefix);require(prefix=="wtex_");return "wtex_fixture";}
void update(CWardrobe* self,CInventory* inventory){event(7);require(self==owner&&!inventory);++updates;snapshot();stop(21);}
class Texture:public Ogre::Texture {
public:
    Texture(Ogre::ResourceManager* m):Ogre::Texture(m,"wtex_fixture",1,"General",true,0){++textureConstructed;require(reinterpret_cast<char*>(&mHeight)-reinterpret_cast<char*>(this)==0x78);require(reinterpret_cast<char*>(&mNumMipmaps)-reinterpret_cast<char*>(this)==0x98);require(reinterpret_cast<char*>(&mInternalResourcesCreated)-reinterpret_cast<char*>(this)==0xe1);}
    ~Texture(){event(9);++textureDestroyed;}
    void setNumMipmaps(size_t n){event(6);number(n);++mipCalls;require(n==5);Ogre::Texture::setNumMipmaps(n);}
    Ogre::HardwarePixelBufferSharedPtr getBuffer(size_t,size_t){require(false);return Ogre::HardwarePixelBufferSharedPtr();}
protected:
    void loadImpl(){require(false);}
    void createInternalResourcesImpl(){require(false);}
    void freeInternalResourcesImpl(){}
};
class Manager:public Ogre::TextureManager {
public:
    Ogre::TexturePtr retained;
    ~Manager(){}
    Ogre::TexturePtr createManual(const Ogre::String& n,const Ogre::String& g,Ogre::TextureType t,Ogre::uint w,Ogre::uint h,Ogre::uint d,int m,Ogre::PixelFormat f,int u,Ogre::ManualResourceLoader* l,bool gamma,Ogre::uint fsaa){
        event(5);++creates;output->addText(n);output->addText(g);number(t);number(w);number(h);number(d);number(m);number(f);number(u);number(l!=0);number(gamma);number(fsaa);
        require(n=="wtex_fixture"&&g==Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME&&t==Ogre::TEX_TYPE_2D&&d==1&&u==Ogre::TU_DEFAULT&&!l&&!gamma&&!fsaa);
        require(w==((input->variant&2)?8u:4u)&&h==((input->variant&2)?4u:2u)&&m==((input->variant&4)?1:0)&&f==((input->variant&4)?Ogre::PF_L8:Ogre::PF_A8R8G8B8));
        stop(20);retained=Ogre::TexturePtr(new Texture(this));return retained;
    }
    Ogre::PixelFormat getNativeFormat(Ogre::TextureType,Ogre::PixelFormat f,int){return f;}
    bool isHardwareFilteringSupported(Ogre::TextureType,Ogre::PixelFormat,int,bool){return false;}
protected:
    Ogre::Resource* createImpl(const Ogre::String&,Ogre::ResourceHandle,const Ogre::String&,bool,Ogre::ManualResourceLoader*,const Ogre::NameValuePairList*){require(false);return 0;}
};
class OldImage:public Ogre::Image {
public: ~OldImage(){event(8);++oldDestroyed;}
};
void resetCounters(){lookups=loads=updates=creates=mipCalls=createdCount=0;}
void cleanupComplete(){
    // No CWardrobe destructor coverage: explicitly end its live subobjects,
    // after observations. update was suppressed, so no mesh/entity exists.
    for(unsigned i=0;i<6;++i){Ogre::Image*& im=*field<Ogre::Image*>(0x58+i*8);delete im;im=0;}
    for(int i=4;i>=0;--i){owner->m_textures[i].~basic_string();owner->m_meshes[i].~basic_string();}
    field<Ogre::TexturePtr>(0x38)->~TexturePtr();
    field<std::wstring>(0x30)->~basic_string();
    owner->CRunicCore::~CRunicCore();
    }
void invokeCtor(bool ours){
    typedef void(*Fn) CTOR_ARGS;Fn fn=ours?newCtor:oldCtor;
    if(!setterPhase&&!autotest::beginInvocation(*output,fn))return;
    std::wstring helmet=(input->variant&2)?L"helmet.mesh":L"";
    std::wstring shoulder=(input->variant&4)?L"shoulder.mesh":L"";
    if(input->variant==7){helmet.assign(L"\0H",2);shoulder.assign(L"S\0T",3);}
    fn(owner,reinterpret_cast<CCharacter*>(identities),reinterpret_cast<Ogre::SceneManager*>(identities+1),reinterpret_cast<Ogre::SceneManager*>(identities+2),reinterpret_cast<CGenericModel*>(identities+3),(input->variant&1)?reinterpret_cast<CGenericModel*>(identities+4):0,L"base/path/base.dds",L"chest.dds",L"boots.dds",L"gloves.dds",helmet,shoulder);
}
void side(void* p,autotest::Capture& out,bool ours,bool setter){
    input=static_cast<Case*>(p);output=&out;textureConstructed=textureDestroyed=0;setterPhase=false;activeFault=setter?0:input->fault;resetCounters();
    logsCreated=logsDestroyed=groupsCreated=groupsDestroyed=0;
    Ogre::LogManager* initialLog=Ogre::LogManager::getSingletonPtr();
    Ogre::ResourceGroupManager* initialGroups=Ogre::ResourceGroupManager::getSingletonPtr();
    std::memset(pixels,0x5a,sizeof pixels);
    owner=static_cast<CWardrobe*>(::operator new(sizeof(CWardrobe)));
    // Raw owner storage only; no nontrivial object is zero-initialized.
    detour::Set patches;TL_REDIRECT(patches,updateFn,&update);TL_REDIRECT(patches,fileSingleton,&singleton);TL_REDIRECT(patches,fileInfo,&lookup);patches.redirect(imageLoad,imageLoad,&load);TL_REDIRECT(patches,uniqueName,&name);
    if(patches.failed()){out.issue=autotest::Capture::InvalidReport;::operator delete(owner);return;}
    require(Ogre::TextureManager::getSingletonPtr()==0);
    if(out.issue!=autotest::Capture::Complete){::operator delete(owner);return;}
    unsigned fault=0;bool complete=false;
    {
        // Real managers provide legal empty-resource teardown, with no renderer,
        // resource locations, codecs, or log files created.
        OptionalLogManager logManager;
        OriginalResourceGroups resourceGroups;
        Manager tm;
        require(reinterpret_cast<char*>(&tm.retained)-reinterpret_cast<char*>(&tm)==0xc0);
        try {
            // Setter setup does not emit a constructor primary-call receipt.
            if(setter)setterPhase=true;
            if(setter){setterPhase=false;typedef void(*Fn) CTOR_ARGS;Fn fn=ours?newCtor:oldCtor;fn(owner,reinterpret_cast<CCharacter*>(identities),reinterpret_cast<Ogre::SceneManager*>(identities+1),reinterpret_cast<Ogre::SceneManager*>(identities+2),reinterpret_cast<CGenericModel*>(identities+3),0,L"base.dds",L"chest.dds",L"boots.dds",L"gloves.dds",L"",L"");}
            else invokeCtor(ours);
            complete=true;
            require(updates==1&&lookups==4);require(creates==((input->mask&1)?1u:0u));require(mipCalls==creates);
            if(setter){
                if(input->mask){Ogre::Image*& old=*field<Ogre::Image*>(0x60+8*input->slot);delete old;old=new OldImage;old->loadDynamicImage(pixels[0],4,2,1,Ogre::PF_A8R8G8B8,false,1,0);}
                oldDestroyed=0;
                if(out.issue!=autotest::Capture::Complete)throw Fault(99);
                out.reset();setterPhase=true;activeFault=input->fault;resetCounters();snapshot();
                typedef void(*Setter)(CWardrobe*,EWardrobeSlot,std::wstring);Setter fn=ours?newSetter:oldSetter;
                if(autotest::beginInvocation(out,fn)){fn(owner,static_cast<EWardrobeSlot>(input->slot),(input->variant&2)?std::wstring():std::wstring(L"replacement.dds"));out.callCompleted=1;}
                require(lookups==1&&updates==0&&creates==0);snapshot();
            }else {out.callCompleted=1;snapshot();}
        }catch(const Fault& e){fault=e.site;number(0xf0000000u|fault);if(complete)snapshot();}
        catch(...){out.issue=autotest::Capture::InvalidReport;}
        if(complete)cleanupComplete();
        else {for(unsigned i=0;i<createdCount;++i)delete createdImages[i];}
        require(tm.retained.isNull()||tm.retained.useCount()==1);
        tm.retained.setNull();require(textureDestroyed==textureConstructed);number(textureConstructed);number(textureDestroyed);
    }
    require(Ogre::LogManager::getSingletonPtr()==initialLog);
    require(Ogre::ResourceGroupManager::getSingletonPtr()==initialGroups);
    require(Ogre::TextureManager::getSingletonPtr()==0);
    require(logsCreated==(initialLog?0u:1u)&&logsDestroyed==logsCreated);
    require(groupsCreated==(initialGroups?0u:1u)&&groupsDestroyed==groupsCreated);
    number(logsCreated);number(logsDestroyed);number(groupsCreated);number(groupsDestroyed);
    ::operator delete(owner);patches.restore();require(!patches.failed());observed_witness::finish(out,fault);
}
void ctorOld(void*p,autotest::Capture&o){side(p,o,false,false);}void ctorNew(void*p,autotest::Capture&o){side(p,o,true,false);}
void setterOld(void*p,autotest::Capture&o){side(p,o,false,true);}void setterNew(void*p,autotest::Capture&o){side(p,o,true,true);}
bool compare(const tlhybrid_host* host,autotest::Coverage& coverage,Case& c,bool setter,unsigned& witnesses){
    autotest::Outcome a,b;autotest::runChild(setter?setterOld:ctorOld,&c,a);autotest::runChild(setter?setterNew:ctorNew,&c,b);
    int result=observed_witness::observe(host,coverage,a,b,c.fault,witnesses);
    if(result){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    wardrobe mask %u variant %u fault %u slot %u replace %u status %d/%d first %lu len %lu/%lu issue %u/%u\n",c.mask,c.variant,c.fault,c.slot,c.replace,a.status,b.status,(unsigned long)at,(unsigned long)a.capture.length,(unsigned long)b.capture.length,a.capture.issue,b.capture.issue);return false;}
    if(c.fault&&witnesses==1&&!observed_witness::negativeControls(host,coverage,a,b,c.fault))return false;return true;
}
}
TL_TEST(wardrobe_constructor_bounded){
    autotest::Coverage coverage("wardrobe_constructor_bounded",(uint64_t)(uintptr_t)oldCtor);unsigned witnesses=0,normals=0,exceptions=0;
    for(unsigned mask=0;mask<16;++mask)for(unsigned v=0;v<8;++v){Case c={mask,v,0,0,0};if(!compare(host,coverage,c,false,witnesses)){coverage.report(host);return 1;}++normals;}
    const unsigned faults[]={1,2,3,4,10,11,12,13,20,21};
    for(unsigned v=0;v<2;++v)for(unsigned i=0;i<10;++i){Case c={15,v,faults[i],0,0};if(!compare(host,coverage,c,false,witnesses)){coverage.report(host);return 1;}++exceptions;}
    coverage.report(host);return observed_witness::totals(host,coverage,witnesses,normals,exceptions)?0:1;
}
TL_TEST(wardrobe_set_base_texture_bounded){
    autotest::Coverage coverage("wardrobe_set_base_texture_bounded",(uint64_t)(uintptr_t)oldSetter);unsigned witnesses=0,normals=0,exceptions=0;
    for(unsigned slot=0;slot<5;++slot)for(unsigned mask=0;mask<16;mask+=15)for(unsigned v=0;v<8;++v)for(unsigned present=0;present<2;++present){Case c={mask,v,0,slot,present};if(!compare(host,coverage,c,true,witnesses)){coverage.report(host);return 1;}++normals;}
    for(unsigned slot=0;slot<5;++slot)for(unsigned f=0;f<2;++f){Case c={15,1,f?10u:1u,slot,1};if(!compare(host,coverage,c,true,witnesses)){coverage.report(host);return 1;}++exceptions;}
    coverage.report(host);return observed_witness::totals(host,coverage,witnesses,normals,exceptions)?0:1;
}
