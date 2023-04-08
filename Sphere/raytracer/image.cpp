#include "image.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <vector>

// the default constructor.

Image::Image()
{
	m_xSize = 0;
	m_ySize = 0;
	m_pTexture = NULL;
}

// the Destructor
Image::~Image()
{
	if(m_pTexture)
		SDL_DestroyTexture(m_pTexture);
}

//function to initiliaze
void Image::Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer)
{
	//Resize the image arrays.
	m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

	//Store the dimensions.
	m_xSize = xSize;
	m_ySize = ySize;

	// Store the pointer to the renderer.
	m_pRenderer = pRenderer;

	//Initialize the texture.
	InitTexture();
}


// Function to set Pexiles

void Image::SetPixel(const int x, const int y, double red, double green, double blue)
{
	m_rChannel.at(x).at(y) = red;
	m_gChannel.at(x).at(y) = green;
	m_bChannel.at(x).at(y) = blue;
}

// Functions to return the dimensions of the image.
int Image::GetXSize()
{
	return m_xSize;
}
int Image::GetYSize()
{
	return m_ySize;
}

// Function to generate the display.

void Image::Display()
{
	// Allocato memory for a pixeel buffer.
	Uint32 *tempPixels = new Uint32[m_xSize * m_ySize];
	//clear the pixel buffer;
	memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));
	for(int x = 0 ; x < m_xSize; x++)
	{
		for (int y = 0; y < m_ySize; y++)
			tempPixels[(y * m_xSize) + x] = ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y));
	}

	// Update the texture eith the Pexile buffer
	SDL_UpdateTexture(m_pTexture, NULL, tempPixels, m_xSize * sizeof(Uint32));

	//delete the pixel buffer
	delete [] tempPixels;

	// Copy the texture to the renderre
	
	SDL_Rect srcRect, bounds;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = m_ySize;
	srcRect.w = m_xSize;
	bounds = srcRect;
	SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);

}

void Image::InitTexture()
{
	Uint32 rmask, gmask, bmask, amask;
	
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
	#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
	#endif
	if(m_pTexture)
		SDL_DestroyTexture(m_pTexture);
	SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

Uint32 Image::ConvertColor(const double red, const double green , const double blue)
{
	
	unsigned char r = static_cast<unsigned char>(red);
	unsigned char g = static_cast<unsigned char>(green);
	unsigned char b = static_cast<unsigned char>(blue);

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 pixelColor = (b << 24) + (g << 16) + (r << 8) + 255;
	#else
		Uint32 pixelColor = (255 << 24) + (b << 16) + (g << 8) + r;
	#endif
	
	return pixelColor;
}
