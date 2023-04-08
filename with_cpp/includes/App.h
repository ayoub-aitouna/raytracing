#ifndef APP_H
#define app_h
#include <SDL2/SDL.h>
#include "../raytracer/image.hpp"
#include "../raytracer/scene.hpp"
#include "../raytracer/camera.hpp"

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
		void PrintVector(const qbVector<double> &inputVector);
	private:
		Image m_image;
		RT::Scene m_scene;
		bool isRunning;
		SDL_Window *pWindow;
		SDL_Renderer *pRenderer;
};

#endif
