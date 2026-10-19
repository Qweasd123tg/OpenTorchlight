#include <ParticleUniverseTechnique.h>
void fpConfigure(ParticleUniverse::ParticleTechnique*p,bool flag,bool keep){p->mRunicFlag5b1=flag;p->setKeepLocal(keep);}
unsigned fpFlags(ParticleUniverse::ParticleTechnique*p){return unsigned(p->mRunicFlag5b1)|(unsigned(p->isKeepLocal())<<1);}
