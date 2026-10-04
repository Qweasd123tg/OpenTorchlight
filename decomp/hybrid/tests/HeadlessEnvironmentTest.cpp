#include "HybridTest.h"
#include "HeadlessGui.h"

TL_TEST(headless_environment)
{
    int failures = 0;
    try
    {
        tlheadless::Environment environment;
        environment.loadGameSkin();
        CEGUI::WindowManager& windows = CEGUI::WindowManager::getSingleton();
        CEGUI::Window* layout = windows.loadWindowLayout("media/ui/diemenu.layout");
        TL_CHECK(failures, layout->getChildCount() == 8);
        const std::string original = tlheadless::snapshot(*layout);
        CEGUI::Window* child = layout->getChildAtIdx(0);
        const CEGUI::String text = child->getText();
        child->setText("mutation probe");
        TL_CHECK(failures, tlheadless::snapshot(*layout) != original);
        child->setText(text);
        TL_CHECK(failures, tlheadless::snapshot(*layout) == original);
        const bool visible = child->isVisible(true);
        child->setVisible(!visible);
        TL_CHECK(failures, tlheadless::snapshot(*layout) != original);
        child->setVisible(visible);
        TL_CHECK(failures, tlheadless::snapshot(*layout) == original);
        const CEGUI::URect area = child->getArea();
        child->setPosition(CEGUI::UVector2(CEGUI::UDim(0,17), CEGUI::UDim(0,23)));
        TL_CHECK(failures, tlheadless::snapshot(*layout) != original);
        child->setArea(area);
        TL_CHECK(failures, tlheadless::snapshot(*layout) == original);
        windows.destroyWindow(layout);

        Ogre::SceneManager* scene = environment.root().createSceneManager(Ogre::ST_GENERIC, "headless");
        Ogre::SceneNode* node = scene->getRootSceneNode()->createChildSceneNode("probe");
        node->setPosition(1,2,3);
        TL_CHECK(failures, node->getPosition() == Ogre::Vector3(1,2,3));
        TL_CHECK(failures, scene->getSceneNode("probe") == node);
        environment.root().destroySceneManager(scene);
    }
    catch (const CEGUI::Exception& error)
    {
        host->log("    CEGUI: %s\n", error.getMessage().c_str());
        return 1;
    }
    catch (const Ogre::Exception& error)
    {
        host->log("    OGRE: %s\n", error.getFullDescription().c_str());
        return 1;
    }
    TL_CHECK(failures, CEGUI::System::getSingletonPtr() == 0);
    TL_CHECK(failures, Ogre::Root::getSingletonPtr() == 0);
    return failures;
}
