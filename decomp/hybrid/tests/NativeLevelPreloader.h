#ifndef TL_EDITOR_NATIVE_LEVEL_PRELOADER_H
#define TL_EDITOR_NATIVE_LEVEL_PRELOADER_H
#include "MasterResourceManager.h"
#include "ParticlePreloader.h"
namespace editorlevel {
// Call inside the comparison child: ownership remains with its native Master.
inline void ensurePreloader(CMasterResourceManager* master) {
    if (!master->m_pParticlePreloader)
        master->m_pParticlePreloader = new CParticlePreloader(NULL);
}
}
#endif
