#include <Ogre.h>
#include <CEGUI.h>
void abi_position(CEGUI::Window* window,const CEGUI::UVector2& value){window->setPosition(value);}
CEGUI::UDim abi_width(const CEGUI::Window* window){return window->getWidth();}
CEGUI::String abi_colour(const CEGUI::colour& value){return CEGUI::PropertyHelper::colourToString(value);}
Ogre::MeshManager& abi_singleton(){return Ogre::MeshManager::getSingleton();}
float abi_extent(CEGUI::Font* font,const CEGUI::String& text){return font->getTextExtent(text,1.0f);}
const Ogre::Quaternion& abi_orientation(const Ogre::Camera* camera){return camera->getOrientation();}
CEGUI::UVector2 abi_size(const CEGUI::Window* window){return window->getSize();}
