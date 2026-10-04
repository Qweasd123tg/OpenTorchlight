#ifndef INTERACTIVEMENU_H
#define INTERACTIVEMENU_H

#include "RunicCore.h"

class CGameUI;
class CSettings;
class CResourceManager;

namespace Ogre {
class SceneManager;
}

namespace CEGUI {
class Window;
}

class CInteractiveMenu : public CRunicCore
{
public:
    virtual ~CInteractiveMenu();

    virtual void update(float fDeltaTime);
    virtual void setVisible(bool bVisible);
    virtual void createMenus();

    CInteractiveMenu(CGameUI& gameUI,
                     CSettings& settings,
                     Ogre::SceneManager* sceneManager,
                     CEGUI::Window* parentWindow,
                     CResourceManager* resourceManager);

    CEGUI::Window* m_pParentWindow;
    CEGUI::Window* m_pMenuWindow;
    CEGUI::Window* m_pMenuContent;
    CEGUI::Window* m_pMenuButtons;
    CResourceManager* m_pResourceManager;
    bool m_bVisible;
    float m_fAnimationTime;
};

#endif
