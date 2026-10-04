#ifndef SPLASH_H
#define SPLASH_H

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

// Borderless window with logo.bmp shown while the game loads.
class CSplash
{
public:
    CSplash();
    virtual ~CSplash();

    void Init(void* parentWindow, int unused);
    void Show();
    void Hide();
    void findCenterForWindow(int width, int height, int& x, int& y);

    bool m_bVisible;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_pTexture;
    int m_iWidth;
    int m_iHeight;
};

#endif
