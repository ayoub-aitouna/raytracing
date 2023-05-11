#include "headers/checker.hpp"
#include <cmath>
#include <vector>

RT::Texture::Checker::Checker()
{

	color1 = qbVector<double>{std::vector<double>{1,1,1,1}};
	color2 = qbVector<double>{std::vector<double>{0.2,0.2,0.2,1.0}};
}

RT::Texture::Checker::~Checker()
{
}


qbVector<double> RT::Texture::Checker::GetColor(qbVector<double> &u_v_cords)
{

	//Apply local transform to (u,v) cords
	qbVector<double> inputCords = u_v_cords;
	qbVector<double> newCords = AppyTransform(inputCords);
	double newU = newCords.GetElement(0);
	double newV = newCords.GetElement(1);

	qbVector<double> localColor {4};	

	int Check = static_cast<int>(floor(newU)) + static_cast<int>(floor(newV));

	if((Check % 2 ) == 0)
		localColor = color1;
	else
		localColor = color2;
	return  localColor;
}

void RT::Texture::Checker::SetColor(const qbVector<double> &color1, qbVector<double> color2)
{
	this->color1 = color1;
	this->color2 = color2;
}
