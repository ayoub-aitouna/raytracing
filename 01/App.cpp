#include "includes/App.h"
#include "raytracer/image.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdio>

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
	// Get the dimensions of the output image.
	int xSize = m_image.GetXSize();
	int ySize = m_image.GetYSize();
	// Create some colour variations.
	for (int x = 0; x < xSize; ++x)
	{
		for (int y = 0; y < ySize; ++y)
		{
			double red = (static_cast<double>(x) / static_cast<double>(xSize)) * 255.0;
			double green = (static_cast<double>(y) / static_cast<double>(ySize)) * 255.0;
			m_image.SetPixel(x, y, red, green, 0.0);
		}
	}
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
	if(event->type == SDL_QUIT)
		isRunning = false;
}

void App::OnLoop()
{

}

void App::OnRender()
{
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);	

	//Display Image
	m_image.Display();

	SDL_RenderPresent(pRenderer);
}

void App::OnExit()
{
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;
	SDL_QUIT;
}
