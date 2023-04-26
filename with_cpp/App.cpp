#include "includes/App.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <vector>
#include "./qbLinAlg/qbVector.h"
#include "./parser/parse.h"

App::App()
{
	isRunning = true;
	pWindow = NULL;
	pRenderer = NULL;
}

bool App::Oninit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;
	pWindow = SDL_CreateWindow("raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if (!pWindow)
		return false;
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
	// Initialise the qbImage instance.
	m_image.Initialize(1280, 720, pRenderer);
	SDL_SetRenderDrawColor(pRenderer,255, 255, 255, 255);
	SDL_RenderClear(pRenderer);
	m_scene.Render(m_image);
	//Display Image
	m_image.Display();
	//Show the Rsult
	SDL_RenderPresent(pRenderer);
	return true;
}

int App::OnExecute()
{
	SDL_Event event;
	if (!Oninit())
		return -1;
	while (isRunning)
	{
		while (SDL_PollEvent(&event) != 0)
			OnEvent(&event);
		OnLoop();
		OnRender();
	}
	return (0);
}

void App::OnEvent(SDL_Event *event)
{
	if(event->type == SDL_QUIT || event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		isRunning = false;
}

void App::OnLoop()
{
	//onLoop
}

void App::OnRender()
{
	/*SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	  SDL_RenderClear(pRenderer);	
	  m_scene.Render(m_image);
	//Display Image
	m_image.Display();
	SDL_RenderPresent(pRenderer);
	*/
}

void App::OnExit()
{
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;
	SDL_QUIT;
}


