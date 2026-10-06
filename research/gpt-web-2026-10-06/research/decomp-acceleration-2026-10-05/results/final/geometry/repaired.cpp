#include <CEGUI.h>
void geometry(CEGUI::Window* window) {
    CEGUI::UVector2 size; CEGUI::UDim width,height;
    size = ((CEGUI::Window*)(window))->CEGUI::Window::getSize();
    width = ((CEGUI::Window*)(window))->CEGUI::Window::getWidth();
    height = ((CEGUI::Window*)(window))->CEGUI::Window::getHeight();
    ((CEGUI::Window*)(window))->CEGUI::Window::setSize(size);
    ((CEGUI::Window*)(window))->CEGUI::Window::setPosition(size);
}
