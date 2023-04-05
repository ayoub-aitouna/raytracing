#ifndef APP_H
#define app_h
#include <SDL2/SDL.h>
#include "../raytracer/image.hpp"
class App
{
public:
    App();

    int OnExecute();
    bool Oninit();
    void OnEvent(SDL_Event *event);
    void OnLoop();
    void OnRender();
    void OnExit();

private:
	Image m_image;
    bool isRunning;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
};

#endif
