#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

class Image
{
	public:
		Image();
		~Image();
		void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer);
		void SetPixel(const int x, const int y, double red, double green, double blue);
		void Display();
		
		// Functions to return the dimensions of the image.
		int GetXSize();
		int GetYSize();

	private:
		Uint32 ConvertColor(const double red, const double green , const double blue);
		void InitTexture();
		void ComputeMaxValues();

	private:
		//Arrays to store image
		std::vector<std::vector<double>> m_rChannel;
		std::vector<std::vector<double>> m_gChannel;
		std::vector<std::vector<double>> m_bChannel;

		//Store the dimensions of the image.
		int m_xSize;
		int m_ySize;

		//SDL2 Stuff.
		SDL_Renderer *m_pRenderer;
		SDL_Texture *m_pTexture;
		double m_max_red, m_max_green, m_max_blue, m_overall_max;
};

#endif
