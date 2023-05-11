#include "headers/flat.hpp"
#include "headers/TextureBase.hpp"
#include <vector>

RT::Texture::Flat::Flat()
{
	m_color = qbVector<double> {std::vector<double> {1,0,0,1}};
}

RT::Texture::Flat::~Flat()
{}



qbVector<double> RT::Texture::Flat::GetColor(qbVector<double> &u_v_cords)
{
	return m_color;
}

void RT::Texture::Flat::SetColor(const qbVector<double> &inputColor)
{
	m_color = inputColor;
}


