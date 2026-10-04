#ifndef RESOURCESETTINGS_H
#define RESOURCESETTINGS_H
#include "DynamicPropertyFile.h"
class CResourceSettings : public CDynamicPropertyFile
{
public:
    CResourceSettings();
    virtual ~CResourceSettings();
};
extern unsigned int KRESOURCESETTING_S_MASTERRESOURCEFILE;
extern unsigned int KRESOURCESETTING_S_PARTICLE_SYSTEMS;
extern unsigned int KRESOURCESETTING_S_PARTICLE_MATERIALS;
extern unsigned int KRESOURCESETTING_S_PARTICLE_IMAGES;
extern unsigned int KRESOURCESETTING_S_ROOM_DATA_FOLDER;
extern unsigned int KRESOURCESETTING_S_SOUND_DATA_FOLDER;
extern unsigned int KRESOURCESETTING_S_SKILL_FOLDER;
extern unsigned int KRESOURCESETTING_S_MISSILE_FOLDER;
extern unsigned int KRESOURCESETTING_S_AFFIXES_FOLDER;
extern unsigned int KRESOURCESETTING_S_GRAPH_MANAGER;
extern unsigned int KRESOURCESETTING_S_TRANSLATE_FILE;
#endif
