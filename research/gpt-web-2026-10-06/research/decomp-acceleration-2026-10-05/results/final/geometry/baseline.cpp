#include <CEGUI.h>
void geometry(CEGUI::Window* window) {
    CEGUI::UVector2 size; CEGUI::UDim width,height;
    CEGUI::Window::getSize(&size,window);
    CEGUI::Window::getWidth(&width,window);
    CEGUI::Window::getHeight(&height,window);
    CEGUI::Window::setSize(window,&size);
    CEGUI::Window::setPosition(window,&size);
}
