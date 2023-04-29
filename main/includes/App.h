#ifndef APP_H
#define app_h
#include <SDL2/SDL.h>
#include "../raytracer/includes/image.hpp"
#include "../raytracer/includes/scene.hpp"
#include "../raytracer/includes/camera.hpp"

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
