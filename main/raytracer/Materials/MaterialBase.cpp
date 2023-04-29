#include "headers/MaterialBase.hpp"

RT::MaterialBase::MaterialBase()
{}

RT::MaterialBase::~MaterialBase()
{}

// function to compute illumination cintribition
qbVector<double> RT::MaterialBase::ComputeColor(const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
		const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
		const std::shared_ptr<RT::ObjectBase> &currentObject,
		const qbVector<double> &intPoint, const qbVector<double> &localNormal,
		const RT::Ray &cameraRay)
{
	//Define an initial Material
	qbVector<double> mtColor {3};

	return (mtColor);
}

// Function to calculat diffuse color.
qbVector<double> RT::MaterialBase::ComputeDiffuseColoe(const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
		const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
		const std::shared_ptr<RT::ObjectBase> &currentObject,
		const qbVector<double> &intPoint, const qbVector<double> &localNormal,
		const qbVector<double>	&baseColor)
{
	// comput the color due to diffuse illumination
	qbVector<double> diffuseColor {3};
	double intensity;
	qbVector<double> color{3};
	double red =0, green = 0, blue = 0;

	bool validIllum = false;
	bool IlumFound = false;

	for(auto curLight : lightList)
	{
		validIllum = curLight->ComputeIllumination(intPoint, localNormal, objectList, currentObject, color, intensity);
		if(validIllum)
		{
			IlumFound = true;
			red += color.GetElement(0) * intensity;
			green += color.GetElement(1) * intensity;
			blue += color.GetElement(2) * intensity;
		}
	}
	if(IlumFound)
	{
		diffuseColor.SetElement(0, red * baseColor.GetElement(0));
		diffuseColor.SetElement(1, green * baseColor.GetElement(1));
		diffuseColor.SetElement(2, blue * baseColor.GetElement(2));
	}
	return  diffuseColor;
}






