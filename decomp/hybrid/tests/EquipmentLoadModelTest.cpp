// Real headless Ogre nodes/DataGroups/strings; model/resource/render spies.
#include <cstring>
#include <new>
#include <map>
#include <Ogre.h>
#include <OgreLogManager.h>
#define private public
#define protected public
#include "Equipment.h"
#include "GenericModel.h"
#include "ResourceManager.h"
#include "Level.h"
#include "LevelTemplateData.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void, originalEquipmentLoadModel, (CEquipment*,std::wstring,std::wstring), "_ZN10CEquipment9loadModelESbIwSt11char_traitsIwESaIwEES3_")
extern "C" void recoveredEquipmentLoadModel(CEquipment*,std::wstring,std::wstring) __asm__("_ZN10CEquipment9loadModelESbIwSt11char_traitsIwESaIwEES3_");
TL_FUNCTION(lmUnload,"_ZN10CEquipment11unloadModelEv")
TL_FUNCTION(lmCreate,"_ZN16CResourceManager18createGenericModelEPN4Ogre12SceneManagerEPKwS4_bbb")
TL_FUNCTION(lmRim,"_ZN13CGenericModel14setRimLightingESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(lmShadows,"_ZN13CGenericModel15setCastsShadowsEb")
TL_FUNCTION(lmTexture,"_ZN13CGenericModel18setTextureOverrideERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(lmSingle,"_ZN13CGenericModel24setTextureOverrideSingleERKSsRKSbIwSt11char_traitsIwESaIwEE")
namespace {
#define LM_AT(C,F,O) typedef char checked_##F[__builtin_offsetof(C,F)==O?1:-1]
LM_AT(CEquipment,m_pUnitModel,0x2b0);LM_AT(CEquipment,m_pUnitModelSecondary,0x2b8);
LM_AT(CSceneNodeObject,m_pSceneNode,0x58);LM_AT(CSceneNodeObject,m_pEntity,0x60);
LM_AT(CLevel,m_pLevelTemplateData,0x1d8);LM_AT(CLevelTemplateData,m_sRimlightTexture,0x6d8);
#undef LM_AT
typedef char template_size[sizeof(CLevelTemplateData)==0x778?1:-1];
typedef char equipment_size[sizeof(CEquipment)==0x438?1:-1];
struct Case {unsigned seed,mode,warm;};
const Case* input;autotest::Capture* capture;CEquipment* object;
CResourceManager* resources[2];CLevel* levels[2];CDataGroup* groups[2];CGenericModel* models[2];Ogre::Entity* entities[2];Ogre::SceneNode* nodes[5];
unsigned perCallCreated,totalCreated,singleCalls;int queue[2];bool shadows[2];std::wstring rims[2];
void number(int n){capture->add(&n,sizeof(n));}void real(float f){capture->add(&f,sizeof(f));}
void text(const std::wstring& s){number(s.size());capture->add(s.data(),s.size()*sizeof(wchar_t));}
void narrow(const std::string& s){number(s.size());capture->add(s.data(),s.size());}
int modelId(const CGenericModel* m){return m==models[0]?0:m==models[1]?1:-1;}
int nodeId(const Ogre::Node* n){for(int i=0;i<5;++i)if(n==nodes[i])return i;return -1;}
struct Logs:Ogre::LogListener{void messageLogged(const Ogre::String& s,Ogre::LogMessageLevel l,bool d,const Ogre::String&){number(20);narrow(s);number(l);number(d);}};
void unload(CEquipment* p){number(1);number(p==object);number(modelId(p->m_pUnitModel));number(modelId(p->m_pUnitModelSecondary));p->m_pUnitModel=0;p->m_pUnitModelSecondary=0;perCallCreated=0;}
CGenericModel* create(CResourceManager* p,Ogre::SceneManager* scene,const wchar_t* mesh,const wchar_t* material,bool a,bool b,bool c){
    number(2);number(p==resources[0]?0:p==resources[1]?1:-1);number(scene==0);text(mesh);number(material==0);number(a);number(b);number(c);
    if(perCallCreated>=2)_exit(61);unsigned i=perCallCreated++;++totalCreated;
    if(i==0&&input->mode==1)object->m_pResourceManager=resources[1];
    if(i==0&&input->mode==2){object->m_pResourceManager=0;models[0]->m_pEntity=0;}
    return models[i];
}
void rim(CGenericModel* p,std::wstring value){int i=modelId(p);number(3);number(i);text(value);if(i<0)_exit(62);rims[i]=value;if(i==0&&input->mode==3&&object->m_pResourceManager)object->m_pResourceManager->m_pLevel=levels[1];}
void shadow(CGenericModel* p,bool v){int i=modelId(p);number(4);number(i);number(v);if(i<0)_exit(62);shadows[i]=v;}
void visible(CEquipment* p,bool v,bool immediate){number(5);number(p==object);number(v);number(immediate);p->m_bRequestedVisible=v;}
void position(CGenericModel* p,float x,float y,float z){int i=modelId(p);number(6);number(i);real(x);real(y);real(z);p->m_vPosition=Ogre::Vector3(x,y,z);if(p->m_pSceneNode)p->m_pSceneNode->setPosition(x,y,z);if(i==0&&input->mode==4)p->m_pEntity=0;}
void render(Ogre::Entity* p,unsigned char v){int i=p==entities[0]?0:p==entities[1]?1:-1;number(7);number(i);number(v);if(i<0)_exit(63);queue[i]=v;}
void texture(CGenericModel* p,const std::wstring& value){number(8);number(modelId(p));text(value);if(input->mode==5)object->m_pDataGroup=groups[1];}
void single(CGenericModel* p,const std::string& name,const std::wstring& value){number(9);number(modelId(p));narrow(name);text(value);if(input->mode==6&&singleCalls==0){CDataGroup* g=object->m_pDataGroup->AddDataGroup(L"TEXTURE_REPLACE");g->AddDataValue(L"NAME",std::wstring(L"late"),false);g->AddDataValue(L"TEXTURE",std::wstring(L"late texture"),false);}++singleCalls;}
void put(CDataGroup& g,const wchar_t* key,const std::wstring& value){g.AddDataValue(key,value,false);}
void populate(CDataGroup& g,unsigned n,bool alternate){
    if(n%3)put(g,L"MESHFILE_SECONDARY",n%5?L"part":L"");put(g,L"RESOURCEDIRECTORY",alternate?L"other\\raw//":L"media\\Items//");
    if(n%4)put(g,L"TEXTURE_OVERRIDE",alternate?L"alt.dds":n%3?L"main.dds":L"");
    for(unsigned i=0;i<(n+(alternate?2:0))%5;++i){CDataGroup* r=g.AddDataGroup(L"TEXTURE_REPLACE");if(i%3)put(*r,L"NAME",i%2?L"mesh_\x416":std::wstring(L"mesh\0ignored",12));if(i%2)put(*r,L"TEXTURE",L"replacement.dds");}
}
struct Snapshot {
 std::vector<unsigned char> bytes;
 Snapshot(const void* p,size_t n):bytes(static_cast<const unsigned char*>(p),static_cast<const unsigned char*>(p)+n){}
 void pointer(size_t offset,uintptr_t value){if(offset+sizeof(value)>bytes.size())_exit(62);std::memcpy(&bytes[offset],&value,sizeof(value));}
 void emit(){capture->add(&bytes[0],bytes.size());}
};
void side(const Case& c,bool ours,autotest::Capture& out){
    input=&c;capture=&out;perCallCreated=totalCreated=singleCalls=0;queue[0]=queue[1]=-1;shadows[0]=shadows[1]=true;rims[0]=rims[1]=L"old";
    Ogre::LogManager logger;Ogre::Log* log=logger.createLog("equipment-loadmodel-test",true,false,true);Logs listener;log->addListener(&listener);
    Ogre::SceneNode equipmentNode(NULL),oldParent(NULL),primaryNode(NULL),secondaryNode(NULL),otherParent(NULL);nodes[0]=&equipmentNode;nodes[1]=&oldParent;nodes[2]=&primaryNode;nodes[3]=&secondaryNode;nodes[4]=&otherParent;
    if(c.seed%3)nodes[c.seed%3==1?1:4]->addChild(nodes[2]);if((c.seed/3)%3)nodes[(c.seed/3)%3==1?1:4]->addChild(nodes[3]);
    CDataGroup data(L"ITEM",0,4,4,0),alt(L"ALT",0,4,4,0);populate(data,c.seed,false);populate(alt,c.seed,true);groups[0]=&data;groups[1]=&alt;
    unsigned long long equipmentStorage[(sizeof(CEquipment)+7)/8],modelStorage[2][(sizeof(CGenericModel)+7)/8],resourceStorage[2][(sizeof(CResourceManager)+7)/8],levelStorage[2][(sizeof(CLevel)+7)/8],templateStorage[2][(sizeof(CLevelTemplateData)+7)/8],entityStorage[2][(sizeof(Ogre::Entity)+7)/8];
    std::memset(equipmentStorage,0,sizeof(equipmentStorage));std::memset(modelStorage,0,sizeof(modelStorage));std::memset(resourceStorage,0,sizeof(resourceStorage));std::memset(levelStorage,0,sizeof(levelStorage));std::memset(templateStorage,0,sizeof(templateStorage));std::memset(entityStorage,0,sizeof(entityStorage));
    void* equipmentVtable[100]={0};void* modelVtable[64]={0};void* entityVtable[64]={0};equipmentVtable[0x2c0/8]=reinterpret_cast<void*>(&visible);modelVtable[0x58/8]=reinterpret_cast<void*>(&position);entityVtable[0x140/8]=reinterpret_cast<void*>(&render);
    object=reinterpret_cast<CEquipment*>(equipmentStorage);*reinterpret_cast<void***>(object)=equipmentVtable;object->m_pSceneNode=&equipmentNode;object->m_pDataGroup=&data;object->m_bRequestedVisible=true;
    typedef std::wstring Text;CLevelTemplateData* templates[2];
    for(unsigned i=0;i<2;++i){
        models[i]=reinterpret_cast<CGenericModel*>(modelStorage[i]);*reinterpret_cast<void***>(models[i])=modelVtable;models[i]->m_pSceneNode=nodes[2+i];models[i]->m_vPosition=Ogre::Vector3(7,8,9);
        entities[i]=reinterpret_cast<Ogre::Entity*>(entityStorage[i]);*reinterpret_cast<void***>(entities[i])=entityVtable;models[i]->m_pEntity=entities[i];
        resources[i]=reinterpret_cast<CResourceManager*>(resourceStorage[i]);levels[i]=reinterpret_cast<CLevel*>(levelStorage[i]);templates[i]=reinterpret_cast<CLevelTemplateData*>(templateStorage[i]);new(&templates[i]->m_sRimlightTexture)Text(i?L"alternate rim":c.seed%3?L"custom rim":L"");levels[i]->m_pLevelTemplateData=templates[i];resources[i]->m_pLevel=levels[i];
    }
    if(c.seed%7==0)models[0]->m_pEntity=0;if(c.seed%5==0)models[1]->m_pSceneNode=0;
    unsigned chain=(c.seed/4)%4;object->m_pResourceManager=chain==0?0:resources[0];if(chain==1)resources[0]->m_pLevel=0;if(chain==2)levels[0]->m_pLevelTemplateData=0;
    object->m_pUnitModel=models[1];object->m_pUnitModelSecondary=models[0];
    static const wchar_t* meshes[]={L"",L"media\\raw//model.mesh",L"\x416\U0001f525.mesh",L"no extension",L"plain.mesh",L"last"};std::wstring mesh=meshes[(c.seed/4)%6],second=(c.seed/16)%4==0?L"":(c.seed/16)%4==1?L"override\\raw//part.mesh":(c.seed/16)%4==2?L"short":L"\x416";
    if(c.seed%17==0)mesh=std::wstring(L"model\0ignored",13);if(c.seed%19==0)second=std::wstring(L"part\0ignored",12);
    detour::Set patches;TL_REDIRECT(patches,lmUnload,&unload);TL_REDIRECT(patches,lmCreate,&create);TL_REDIRECT(patches,lmRim,&rim);TL_REDIRECT(patches,lmShadows,&shadow);TL_REDIRECT(patches,lmTexture,&texture);TL_REDIRECT(patches,lmSingle,&single);if(patches.failed())_exit(42);
    for(unsigned repeat=0;repeat<=c.warm;++repeat){
        if(repeat==c.warm){if(ours)autotest::invoke(out,&recoveredEquipmentLoadModel,object,mesh,second);else autotest::invoke(out,&originalEquipmentLoadModel,object,mesh,second);}
        else {if(ours)object->loadModel(mesh,second);else originalEquipmentLoadModel(object,mesh,second);}
        number(100+repeat);number(modelId(object->m_pUnitModel));number(modelId(object->m_pUnitModelSecondary));number(nodeId(primaryNode.getParent()));number(nodeId(secondaryNode.getParent()));number(equipmentNode.numChildren());number(oldParent.numChildren());number(otherParent.numChildren());number(object->m_bRequestedVisible);number(totalCreated);number(singleCalls);
        for(unsigned i=0;i<2;++i){number(queue[i]);number(shadows[i]);text(rims[i]);real(models[i]->m_vPosition.x);real(models[i]->m_vPosition.y);real(models[i]->m_vPosition.z);}
    }
    Snapshot eq(object,sizeof(*object));eq.pointer(0,*reinterpret_cast<void***>(object)==equipmentVtable?1:2);eq.pointer(0x58,nodeId(object->m_pSceneNode)+1);eq.pointer(0x68,object->m_pResourceManager==resources[0]?1:object->m_pResourceManager==resources[1]?2:object->m_pResourceManager?3:0);eq.pointer(0x1b0,object->m_pDataGroup==groups[0]?1:object->m_pDataGroup==groups[1]?2:3);eq.pointer(0x2b0,modelId(object->m_pUnitModel)+1);eq.pointer(0x2b8,modelId(object->m_pUnitModelSecondary)+1);eq.emit();
    for(unsigned i=0;i<2;++i){
        Snapshot m(models[i],sizeof(CGenericModel));m.pointer(0,*reinterpret_cast<void***>(models[i])==modelVtable?1:2);m.pointer(0x58,nodeId(models[i]->m_pSceneNode)+1);m.pointer(0x60,models[i]->m_pEntity==entities[0]?1:models[i]->m_pEntity==entities[1]?2:models[i]->m_pEntity?3:0);m.emit();
        Snapshot e(entities[i],sizeof(Ogre::Entity));e.pointer(0,*reinterpret_cast<void***>(entities[i])==entityVtable?1:2);e.emit();
        Snapshot r(resources[i],sizeof(CResourceManager));r.pointer(__builtin_offsetof(CResourceManager,m_pLevel),resources[i]->m_pLevel==levels[0]?1:resources[i]->m_pLevel==levels[1]?2:resources[i]->m_pLevel?3:0);r.emit();
        Snapshot l(levels[i],sizeof(CLevel));l.pointer(0x1d8,levels[i]->m_pLevelTemplateData==templates[0]?1:levels[i]->m_pLevelTemplateData==templates[1]?2:levels[i]->m_pLevelTemplateData?3:0);l.emit();
        Snapshot td(templates[i],sizeof(CLevelTemplateData));td.pointer(0x6d8,templates[i]->m_sRimlightTexture.empty()?0:1);td.emit();text(templates[i]->m_sRimlightTexture);
        std::vector<CDataGroup*> replacements;groups[i]->GetDataGroupsMatchingName(L"TEXTURE_REPLACE",&replacements);number(replacements.size());for(unsigned j=0;j<replacements.size();++j){text(replacements[j]->GetDataValue(L"NAME",L""));text(replacements[j]->GetDataValue(L"TEXTURE",L""));}
    }
    for(unsigned i=0;i<5;++i){number(nodeId(nodes[i]->getParent()));number(nodes[i]->numChildren());for(unsigned j=0;j<nodes[i]->numChildren();++j)number(nodeId(nodes[i]->getChild(j)));const Ogre::Vector3& p=nodes[i]->getPosition();real(p.x);real(p.y);real(p.z);}
    patches.restore();for(unsigned i=0;i<2;++i)templates[i]->m_sRimlightTexture.~Text();log->removeListener(&listener);
}
void original(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),false,c);}void recovered(void* p,autotest::Capture& c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(equipment_loadmodel_differential){
    autotest::Coverage coverage("equipment_loadmodel_differential",(uint64_t)(uintptr_t)&originalEquipmentLoadModel);unsigned count=0;
    for(unsigned n=0;n<960;++n)for(unsigned warm=0;warm<2;++warm){Case c={n<576?n:4+(n-576)%64,n<576?0u:1+(n-576)/64,warm};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);++count;
        int pair=coverage.observe(host,a,b);bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
        if(!ok){size_t i=0;while(i<a.capture.length&&i<b.capture.length&&a.capture.data[i]==b.capture.data[i])++i;host->log("    loadmodel %u mode %u warm %u: status %d/%d bytes %lu/%lu first %lu\n",c.seed,c.mode,c.warm,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)i);coverage.report(host);return 1;}
    }
    coverage.report(host);host->log("    equipment loadModel: %u completed cold/warm cases\n",count);return 0;
}
