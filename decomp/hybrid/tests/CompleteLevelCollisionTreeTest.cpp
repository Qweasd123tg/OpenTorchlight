#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/SmallMassCompare.h"
#include "Quadtree.h"
#include "Utilities.h"
#include "UtilitiesMath.h"
#include <limits>
TL_ORIGINAL(void,lcSortOld,(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&),"_ZN6CLevel16sortForCollisionERKN4Ogre7Vector3ES3_")
TL_ORIGINAL(void,lcPointsOld,(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float),"_ZN6CLevel24sortForCollisionByPointsERKN4Ogre7Vector3ES3_f")
TL_ORIGINAL(bool,lcRayOld,(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,bool),"_ZN6CLevel12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_RjS4_b")
TL_ORIGINAL(bool,lcSphereOld,(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&),"_ZN6CLevel15sphereCollisionERKN4Ogre7Vector3ES3_fRS1_S4_S4_RjS4_")
extern "C" void lcSortNew(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&) __asm__("_ZN6CLevel16sortForCollisionERKN4Ogre7Vector3ES3_");
extern "C" void lcPointsNew(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float) __asm__("_ZN6CLevel24sortForCollisionByPointsERKN4Ogre7Vector3ES3_f");
extern "C" bool lcRayNew(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,bool) __asm__("_ZN6CLevel12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_RjS4_b");
extern "C" bool lcSphereNew(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&) __asm__("_ZN6CLevel15sphereCollisionERKN4Ogre7Vector3ES3_fRS1_S4_S4_RjS4_");
TL_FUNCTION(lcObjectRay,"_ZN6CLevel18objectRayCollisionERKN4Ogre7Vector3ES3_RS1_S4_RjPP9CBaseUnitb")
namespace {
autotest::Capture*output;CLevel*level;unsigned seed;
void word(unsigned n){output->add(&n,4);}void scalar(float f){output->add(&f,4);}void vec(const Ogre::Vector3&v){output->add(&v,sizeof v);}
bool objectRay(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,Ogre::Vector3&h,Ogre::Vector3&n,unsigned&m,CBaseUnit**unit,bool flag){
 word(100);word(p==level);word(unit==NULL);word(flag);vec(a);vec(b);
 unsigned k=seed/3%8;if(k==0||k==7)return false;
 const float fractions[]={0,.1f,.25f,.5f,.75f,1,1.25f};h=a+(b-a)*fractions[k];n=Ogre::Vector3(2,-3,4);m=1000+seed%13;vec(h);vec(n);word(m);return true;
}
void addTriangle(CCollisionList&c,const Ogre::Vector3&a,const Ogre::Vector3&b,const Ogre::Vector3&d,unsigned material){unsigned n=c.getVertexCount();c.addVertex(a,-1);c.addVertex(b,-1);c.addVertex(d,-1);c.addFace(n,n+1,n+2,material,-1);}
void nodeState(CQuadtreeNode<unsigned>*p,unsigned depth=0){word(p!=NULL);if(!p)return;if(depth>16)std::abort();vec(p->m_minimum);vec(p->m_maximum);word(p->m_subdivided);word(p->m_data.size());for(unsigned i=0;i<p->m_data.size();++i){word(p->m_data[i]);vec(p->m_dataMinimum[i]);vec(p->m_dataMaximum[i]);}if(p->m_subdivided)for(unsigned i=0;i<4;++i)nodeState(p->m_children[i],depth+1);}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;seed=c.index;finishlevel::Fixture f;level=&f.level;
 CCollisionList*list=new CCollisionList;
 for(unsigned x=0;x<4;++x)for(unsigned z=0;z<4;++z){float a=-24+12*float(x),b=-24+12*float(z),y=float(int((x+z+seed/32)%3)-1)*2;addTriangle(*list,Ogre::Vector3(a,y,b),Ogre::Vector3(a,y,b+12),Ogre::Vector3(a+12,y,b+12),x*4+z);addTriangle(*list,Ogre::Vector3(a,y,b),Ogre::Vector3(a+12,y,b+12),Ogre::Vector3(a+12,y,b),x*4+z+20);}
 for(unsigned i=0;i<4;++i){float a=-18+12*float(i);addTriangle(*list,Ogre::Vector3(a,-10,-24),Ogre::Vector3(a,10,24),Ogre::Vector3(a,10,-24),80+i);addTriangle(*list,Ogre::Vector3(a,-10,-24),Ogre::Vector3(a,-10,24),Ogre::Vector3(a,10,24),90+i);}
 list->calculateFaceBounds();list->calculateNormals();
 CQuadtree<unsigned>*tree=new CQuadtree<unsigned>;tree->m_minimumCellSize=seed%3==0?64:seed%3==1?8:2;tree->m_minimum=Ogre::Vector3(-32,-40,-32);tree->m_maximum=Ogre::Vector3(32,40,32);tree->m_root=new CQuadtreeNode<unsigned>;CQuadtreeNode<unsigned>*root=tree->m_root;root->m_minimum=tree->m_minimum;root->m_maximum=tree->m_maximum;root->m_subdivided=false;for(unsigned i=0;i<4;++i)root->m_children[i]=NULL;
 unsigned faces=seed%11==0?0:list->getFaceCount();for(unsigned i=0;i<faces;++i){unsigned n=seed&1?faces-1-i:i;root->addData(n,list->getMinFaceBounds(n),list->getMaxFaceBounds(n),tree->m_minimumCellSize);}
 if(seed%23==0)tree->m_root=NULL;
 level->m_collisionList=(seed%19==0&&c.op>1)?NULL:list;level->m_collisionTree=tree;
 for(unsigned i=0;i<seed%9;++i)level->m_collisionIndices.push_back(700+i);if(seed&8)level->m_collisionIndices.reserve(128);
 const float radii[]={0,.01f,.4f,1,3,12,-.125f,32};float radius=radii[seed/7%8];float x=float(int(seed%17)-8)*3,z=float(int(seed/17%17)-8)*3;
 Ogre::Vector3 a(x,seed&1?20.0f:-20.0f,z),b(x+float(int(seed/3%7)-3),seed&1?-25.0f:25.0f,z+float(int(seed/5%7)-3));
 if(seed%31==0)b=a;if(seed%37==0)a.x=std::numeric_limits<float>::quiet_NaN();
 Ogre::Vector3 hit(81,82,83),normal(91,92,93),position(71,72,73),extra(61,62,63);unsigned material=0xabcde;bool result=false;
 detour::Set hooks;TL_REDIRECT(hooks,lcObjectRay,&objectRay);if(hooks.failed())std::abort();
 if(c.op==0){Ogre::Vector3 minimum=a,maximum=a;MATH::expandBounds(minimum,maximum,b);if(seed&16){minimum-=Ogre::Vector3(radius,radius,radius);maximum+=Ogre::Vector3(radius,radius,radius);}typedef void(*Fn)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&);Fn fn=ours?lcSortNew:lcSortOld;if(!autotest::beginInvocation(out,fn))return;fn(level,minimum,maximum);}
 else if(c.op==1){typedef void(*Fn)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float);Fn fn=ours?lcPointsNew:lcPointsOld;if(!autotest::beginInvocation(out,fn))return;fn(level,a,b,radius);}
 else if(c.op==2){typedef bool(*Fn)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&,bool);Fn fn=ours?lcRayNew:lcRayOld;if(!autotest::beginInvocation(out,fn))return;result=fn(level,a,b,hit,normal,material,extra,seed&2);}
 else {typedef bool(*Fn)(CLevel*,const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned&,Ogre::Vector3&);Fn fn=ours?lcSphereNew:lcSphereOld;if(!autotest::beginInvocation(out,fn))return;result=fn(level,a,b,radius,position,hit,normal,material,extra);}
 out.callCompleted=1;word(result);word(material);vec(a);vec(b);scalar(radius);vec(hit);vec(normal);vec(position);vec(extra);word(level->m_collisionIndices.size());word(level->m_collisionIndices.capacity());for(unsigned i=0;i<level->m_collisionIndices.size();++i)word(level->m_collisionIndices[i]);nodeState(tree->m_root);
 hooks.restore();level->m_collisionList=NULL;level->m_collisionTree=NULL;tree->m_root=root;delete tree;delete list;
}
}
TL_TEST(complete_level_collision_tree){nativegame::Services services;if(!services.ready())return 1;const char*names[]={"level_collision_tree_sort","level_collision_tree_points","level_collision_tree_ray","level_collision_tree_sphere"};const unsigned addresses[]={0x94dec0,0x94da90,0x94e250,0x94edb0};for(unsigned i=0;i<4;++i)if(smallmass::run(host,i,names[i],addresses[i],&side,512))return 1;return 0;}
