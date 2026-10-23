#include <Ogre.h>
#include "AutoTest.h"
#include "SystemsFixtureWorker.h"
#define private public
#include "WeaponTrail.h"
#undef private
#include "DataGroup.h"
#include "SceneNodeObject.h"
#include "SafePointer.h"
#include "ParticleNativeOwners.h"

TL_ORIGINAL(void, trailOldCtor, (CWeaponTrail*,Ogre::SceneManager*,const std::string&,int,float), "_ZN12CWeaponTrailC1EPN4Ogre12SceneManagerERKSsif")
TL_ORIGINAL(void, trailOldDataCtor, (CWeaponTrail*,Ogre::SceneManager*,CDataGroup*), "_ZN12CWeaponTrailC1EPN4Ogre12SceneManagerEP10CDataGroup")
TL_ORIGINAL(void, trailOldDtor, (CWeaponTrail*), "_ZN12CWeaponTrailD1Ev")
TL_ORIGINAL(void, trailOldFade, (CWeaponTrail*,float,bool), "_ZN12CWeaponTrail7fadeOutEfb")
TL_ORIGINAL(void, trailOldUpdate, (CWeaponTrail*,float,Ogre::Vector3*,Ogre::Vector3*,bool,CSceneNodeObject*), "_ZN12CWeaponTrail6updateEfPN4Ogre7Vector3ES2_bP16CSceneNodeObject")
extern "C" void trailNewDataCtor(CWeaponTrail*,Ogre::SceneManager*,CDataGroup*) __asm__("_ZN12CWeaponTrailC1EPN4Ogre12SceneManagerEP10CDataGroup");
extern "C" void trailNewFade(CWeaponTrail*,float,bool) __asm__("_ZN12CWeaponTrail7fadeOutEfb");
extern "C" void trailNewUpdate(CWeaponTrail*,float,Ogre::Vector3*,Ogre::Vector3*,bool,CSceneNodeObject*) __asm__("_ZN12CWeaponTrail6updateEfPN4Ogre7Vector3ES2_bP16CSceneNodeObject");

namespace {
struct Case { unsigned operation, seed, negative; };
ParticleNativeOwners owners;
Ogre::MeshPtr entityMesh;
void number(autotest::Capture& out, unsigned n) { out.add(&n,sizeof n); }
void scalar(autotest::Capture& out, float f) { out.add(&f,sizeof f); }
void vector(autotest::Capture& out,const Ogre::Vector3& v) { scalar(out,v.x);scalar(out,v.y);scalar(out,v.z); }
void colour(autotest::Capture& out,const Ogre::ColourValue& c) { scalar(out,c.r);scalar(out,c.g);scalar(out,c.b);scalar(out,c.a); }
void captureString(autotest::Capture& out,const std::string& s) { number(out,s.size());out.add(s.data(),s.size()); }

void geometry(autotest::Capture& out,Ogre::ManualObject* object)
{
    number(out,object->getVisible());number(out,object->getRenderQueueGroup());
    number(out,object->getNumSections());
    const Ogre::AxisAlignedBox& bounds=object->getBoundingBox();
    number(out,bounds.isNull());
    if (!bounds.isNull()) {vector(out,bounds.getMinimum());vector(out,bounds.getMaximum());}
    for (unsigned i=0;i<object->getNumSections();++i) {
        Ogre::ManualObject::ManualObjectSection* section=object->getSection(i);
        captureString(out,section->getMaterialName());
        Ogre::RenderOperation operation;section->getRenderOperation(operation);
        number(out,operation.operationType);number(out,operation.useIndexes);
        Ogre::VertexData* data=operation.vertexData;
        number(out,data->vertexStart);number(out,data->vertexCount);
        if (data->vertexCount>64) {out.issue=autotest::Capture::InvalidReport;return;}
        const Ogre::VertexDeclaration::VertexElementList& elements=data->vertexDeclaration->getElements();
        number(out,elements.size());
        for (Ogre::VertexDeclaration::VertexElementList::const_iterator e=elements.begin();e!=elements.end();++e) {
            number(out,e->getSource());number(out,e->getOffset());number(out,e->getType());number(out,e->getSemantic());number(out,e->getIndex());
        }
        const Ogre::VertexBufferBinding::VertexBufferBindingMap& bindings=data->vertexBufferBinding->getBindings();
        number(out,bindings.size());
        for (Ogre::VertexBufferBinding::VertexBufferBindingMap::const_iterator b=bindings.begin();b!=bindings.end();++b) {
            number(out,b->first);number(out,b->second->getVertexSize());
            size_t offset=data->vertexStart*b->second->getVertexSize();
            size_t length=data->vertexCount*b->second->getVertexSize();
            void* bytes=b->second->lock(offset,length,Ogre::HardwareBuffer::HBL_READ_ONLY);
            out.add(bytes,length);b->second->unlock();
        }
    }
}

void side(void* raw,autotest::Capture& out,bool ours)
{
    Case c=*static_cast<Case*>(raw);
    CWeaponTrail* trail=static_cast<CWeaponTrail*>(Ogre::NedAllocImpl::allocBytes(sizeof(CWeaponTrail),0,0,0));
    std::memset(trail,0x5a,sizeof *trail);
    Ogre::ManualObject* object=NULL;
    Ogre::SceneNode* node=NULL;
    CSceneNodeObject* owner=NULL;
    CDataGroup* data=NULL;
    if (c.operation==0) {
        unsigned mode=c.seed%8;
        if (mode) data=new CDataGroup(mode==1?L"OTHER":L"WEAPONTRAIL",NULL,20,10,NULL);
        if (mode>=3) {
            const int sizes[]={1,2,5,8,20};
            data->SetDataValue(L"MAXSEGMENTS",sizes[(c.seed/8)%5]);
            data->SetDataValue(L"FADETIME",float(int(c.seed%5)-1)*.25f);
            data->SetDataValue(L"WIDTH",float(int(c.seed%7)-2)*.5f);
            if (mode==5 || mode==6)
                data->SetDataValue(L"TEXTURE",mode==5?L"media/textures/trail-new.dds":L"media/textures/trail-existing.dds");
        }
        typedef void (*F)(CWeaponTrail*,Ogre::SceneManager*,CDataGroup*);
        F f=ours?trailNewDataCtor:trailOldDataCtor;
        if (!autotest::beginInvocation(out,f)) return;
        f(trail,owners.scene,data);out.callCompleted=1;
        object=trail->m_object;
    } else {
        trailOldCtor(trail,owners.scene,std::string("native-trail-fixture"),8,1.25f);
        object=trail->m_object;
        const unsigned sizes[]={0,1,2,4,7,8};
        unsigned size=sizes[c.seed%6];
        for (unsigned i=0;i<size;++i) {
            CWeaponTrail::Segment segment;
            segment.start=Ogre::Vector3(float(i)*.25f,float(int(i%3)-1),float(i)*-.5f);
            segment.end=segment.start+Ogre::Vector3(.25f,1.5f,-.125f);
            if ((c.seed/6)%3==0) {segment.start=Ogre::Vector3(1,2,3);segment.end=Ogre::Vector3(2,4,6);}
            segment.startColour=Ogre::ColourValue(.125f*i,.5f,.75f,1.f);
            segment.endColour=Ogre::ColourValue(1.f,.125f*i,.25f,.75f);
            segment.distance=-123.f;trail->m_segments.push_back(segment);
        }
        trail->m_active=true;
        trail->m_startColour=Ogre::ColourValue(.25f,.5f,.75f,1.f);
        trail->m_endColour=Ogre::ColourValue(.75f,.25f,.5f,.5f);
        trail->m_fadeScale=(c.seed/3)%4*.5f;
        trail->m_fadeTime=(c.seed/5)%3 ? .5f : 0.f;
        float elapsed=float(int(c.seed%5)-1)*.125f;
        if (c.operation==1) {
            trail->m_active=bool((c.seed/6)&1);
            typedef void (*F)(CWeaponTrail*,float,bool);F f=ours?trailNewFade:trailOldFade;
            if (!autotest::beginInvocation(out,f)) return;
            f(trail,elapsed,bool(c.seed&1));out.callCompleted=1;
        } else {
            unsigned mode=(c.seed/6)%24;
            trail->m_active=mode!=0 && mode!=1;
            trail->m_fading=mode>=20;
            trail->m_positionOffset=Ogre::Vector3(.125f,-.25f,.5f);
            Ogre::Vector3 position(.5f,-1.25f,2.f),direction(.25f,2.f,-.5f);
            Ogre::Vector3* supplied=mode==2?NULL:&position;
            if (mode==3) trail->m_object=NULL;
            if (mode>=8) {
                Ogre::SceneNode* parent=owners.scene->getRootSceneNode()->createChildSceneNode();
                parent->setPosition(-2,1,3);parent->setScale(1,2,.5f);
                node=parent->createChildSceneNode();node->setPosition(.25f,-.5f,1.f);
                node->setOrientation(Ogre::Quaternion(Ogre::Degree(30),Ogre::Vector3::UNIT_Z));
                trail->setWeaponNode(node);supplied=NULL;
                if (mode>=12) {
                    owner=new CSceneNodeObject(owners.resources,owners.scene);
                    owner->getSceneNode()->setPosition(2,3,-1);
                    owner->getSceneNode()->setOrientation(Ogre::Quaternion(Ogre::Degree(45),Ogre::Vector3::UNIT_Y));
                }
                if (mode>=16 && mode<20) {
                    Ogre::Entity* entity=owners.scene->createEntity("trail-fixture-entity",entityMesh->getName());
                    node->attachObject(entity);trail->setWeaponEntity(entity);
                }
            }
            typedef void (*F)(CWeaponTrail*,float,Ogre::Vector3*,Ogre::Vector3*,bool,CSceneNodeObject*);
            F f=ours?trailNewUpdate:trailOldUpdate;
            if (!autotest::beginInvocation(out,f)) return;
            f(trail,elapsed,supplied,&direction,bool(mode&1),owner);out.callCompleted=1;
        }
    }
    if (ours && c.negative) trail->m_fadeScale+=.125f;
    number(out,trail->m_maxSegments);scalar(out,trail->m_width);
    number(out,trail->m_active);scalar(out,trail->m_fadeScale);
    number(out,trail->m_fading);scalar(out,trail->m_fadeTime);
    colour(out,trail->m_startColour);colour(out,trail->m_endColour);
    vector(out,trail->m_positionOffset);captureString(out,trail->m_name);captureString(out,trail->m_material);
    number(out,trail->m_object!=NULL);number(out,trail->m_segments.size());
    for (std::list<CWeaponTrail::Segment>::const_iterator i=trail->m_segments.begin();i!=trail->m_segments.end();++i) {
        vector(out,i->start);vector(out,i->end);colour(out,i->startColour);colour(out,i->endColour);scalar(out,i->distance);
    }
    if (node) vector(out,node->getPosition());
    if (object) {
        geometry(out,object);
        number(out,object->getParentSceneNode()==trail->m_parentNode);
        number(out,trail->m_parentNode->numAttachedObjects());
        if (!trail->m_material.empty()) {
            Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().getByName(trail->m_material);
            number(out,!material.isNull());
            if (!material.isNull()) {
                number(out,material->getReceiveShadows());
                Ogre::Pass* pass=material->getTechnique(0)->getPass(0);
                number(out,pass->getLightingEnabled());number(out,pass->getDepthCheckEnabled());number(out,pass->getDepthWriteEnabled());
                number(out,pass->getSourceBlendFactor());number(out,pass->getDestBlendFactor());number(out,pass->getCullingMode());
                number(out,pass->getNumTextureUnitStates());
                if (pass->getNumTextureUnitStates()) captureString(out,pass->getTextureUnitState(0)->getTextureName());
            }
        }
        std::string name=trail->m_name;
        TSafePointer<CWeaponTrail> weak;weak.setObject(trail);
        trail->m_object=object;trailOldDtor(trail);
        number(out,weak.getObject()==NULL);number(out,owners.scene->hasManualObject(name));
    } else {
        // The native data constructor deliberately leaves invalid groups uninitialised.
        trail->m_material.~basic_string();trail->m_name.~basic_string();
        trail->m_segments.~list();trail->CRunicCore::~CRunicCore();
    }
    Ogre::NedAllocImpl::deallocBytes(trail);
    delete data;
}
void before(void* p,autotest::Capture& out) { side(p,out,false); }
void after(void* p,autotest::Capture& out) { side(p,out,true); }
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address,unsigned cases)
{
    owners=particleNativeOwners(0);
    if (!Ogre::MaterialManager::getSingleton().resourceExists("WeaponTrail")) {
        Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("WeaponTrail","General");
        material->removeAllTechniques();
    }
    Ogre::MaterialManager::getSingleton().create("TRAIL-EXISTING.DDS","General");
    entityMesh=Ogre::MeshManager::getSingleton().createManual("weapon-fixture-mesh","General");
    entityMesh->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);entityMesh->load();
    autotest::Coverage coverage(name,address);
    for (unsigned i=0;i<cases;++i) {
        Case c={operation,i,0};autotest::Outcome a,b;
        autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);
        if (coverage.observe(host,a,b)) {
            size_t offset=0;while(offset<a.capture.length&&offset<b.capture.length&&a.capture.data[offset]==b.capture.data[offset]) ++offset;
            host->log("    weapon op%u seed%u status%d/%d bytes%lu/%lu first%lu\n",operation,i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)offset);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);
    Case c={operation,7,1};autotest::Outcome a,b;
    autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);
    bool detected=a.capture.length!=b.capture.length || std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    return !detected||autotest::incomplete(a)||autotest::incomplete(b)||!a.reportValid||!b.reportValid||a.childStatus||b.childStatus;
}
int ctorWorker(const tlhybrid_host* h) { return run(h,0,"weapon_data_constructor_recovery",0xa4cdd0,48); }
int fadeWorker(const tlhybrid_host* h) { return run(h,1,"weapon_fade_recovery",0xa4a0f0,72); }
int updateWorker(const tlhybrid_host* h) { return run(h,2,"weapon_update_recovery",0xa4a470,144); }
}
TL_TEST(weapon_data_constructor_recovery) { return systems_fixture::isolated(ctorWorker,host); }
TL_TEST(weapon_fade_recovery) { return systems_fixture::isolated(fadeWorker,host); }
TL_TEST(weapon_update_recovery) { return systems_fixture::isolated(updateWorker,host); }
