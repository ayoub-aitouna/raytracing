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
#include "./raytracer/Textures/headers/checker.hpp"

App::App()
{
	isRunning = true;
	pWindow = NULL;
	pRenderer = NULL;
}

bool App::Oninit()
{
	int xSize = 1280;
	int ySize = 720;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;
	pWindow = SDL_CreateWindow("raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xSize, ySize, SDL_WINDOW_SHOWN);
	if (!pWindow)
		return false;
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
	// Initialise the qbImage instance.
	m_image.Initialize(xSize, ySize, pRenderer);
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);
	m_scene.Render(m_image);

	// init Texture
	RT::Texture::Checker checkerTexture;
	checkerTexture.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
								M_PI / 4,
								qbVector<double>{std::vector<double>{4.0, 4.0}});

	// for (size_t y = 0; y < ySize; ++y)
	// {
	// 	for (size_t x = 0; x < xSize; ++x)
	// 	{
	// 		double u = static_cast<double>(x) / (static_cast<double>(xSize) / 2.0) - 1.0;
	// 		double v = static_cast<double>(y) / (static_cast<double>(ySize) / 2.0) - 1.0;
	// 		qbVector<double> u_v_cords = qbVector<double>{std::vector<double>{u, v}};
	// 		qbVector<double> pixelColor = checkerTexture.GetColor(u_v_cords);
	// 		m_image.SetPixel(x, y, pixelColor.GetElement(0), pixelColor.GetElement(1), pixelColor.GetElement(2));
	// 	}
	// }

	// Display Image
	m_image.Display();
	// Show the Rsult
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
	OnExit();
	return (0);
}

void App::OnEvent(SDL_Event *event)
{
	if (event->type == SDL_QUIT || event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		isRunning = false;
}

void App::OnLoop()
{
	// onLoop
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
	SDL_Quit();
}
