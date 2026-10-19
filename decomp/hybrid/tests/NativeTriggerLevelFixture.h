#ifndef NATIVE_TRIGGER_LEVEL_FIXTURE_H
#define NATIVE_TRIGGER_LEVEL_FIXTURE_H
#include "tests/NativeGameServices.h"
#include "NativeLevelPreloader.h"
#include "Level.h"
#include "ResourceManager.h"
namespace nativetrigger {
struct LevelFixture {
    CResourceManager resources;
    CLevel& level;
    static CLevel* create(nativegame::Services& services,CResourceManager* resources) {
        editorlevel::ensurePreloader(services.master);
        return new CLevel(L"trigger fixture",services.settings,NULL,resources,services.scene,NULL,17,3);
    }
    explicit LevelFixture(nativegame::Services& services):resources(services.scene),level(*create(services,&resources)) {
        resources.m_pLevel=&level;
    }
    ~LevelFixture() { delete &level;resources.m_pLevel=NULL; }
private:
    LevelFixture(const LevelFixture&);
    LevelFixture& operator=(const LevelFixture&);
};
}
#endif
