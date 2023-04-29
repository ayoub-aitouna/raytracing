#include "headers/SimpleMaterial.hpp"
#include <cmath>

RT::SimpleMaterial::SimpleMaterial()
{}

RT::SimpleMaterial::~SimpleMaterial()
{}


// function to compute illumination cintribition
qbVector<double> RT::SimpleMaterial::ComputeColor(const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
		const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
		const std::shared_ptr<RT::ObjectBase> &currentObject,
		const qbVector<double> &intPoint, const qbVector<double> &localNormal,
		const RT::Ray &cameraRay)
{
	//Define an initial Material
	qbVector<double> mtColor {3};
	qbVector<double> refColor {3};
	qbVector<double> difColor {3};
	qbVector<double> specColor {3};
	difColor = ComputeDiffuseColoe(objectList, lightList, currentObject, intPoint, localNormal, m_baseColor);
	// comput the specular compunent
	if(m_shininess > 0)
		specColor = ComputeSpectular(objectList, lightList, intPoint, localNormal, cameraRay);
	//Add spectular component to final color 
	mtColor = difColor + specColor;
	return (mtColor);
}

qbVector<double> RT::SimpleMaterial::ComputeSpectular(const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
		const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
		const qbVector<double> &intPoint, const qbVector<double> &localNormal,
		const RT::Ray &cameraRay)
{
	double SpectacularIntisity = 0;
	double red = 0, green = 0 , blue = 0;
	qbVector<double> specColor {3};
	for(auto curLight: lightList)
	{
		qbVector<double> lightDir = (curLight->m_location - intPoint).Normalized();
		qbVector<double> specColor {3};
		// add small padding from start point and the surface 
		// to avoid the ray from inetersact with the same object again.
		qbVector<double> startPoint = intPoint + (lightDir * 0.001);
		RT::Ray lightRay (startPoint, startPoint + lightDir);
		qbVector<double> poi {3};
		qbVector<double> poiNormal {3};
		qbVector<double> poiColor {3};
		bool validInt = false;

		//loop through all the objects in thee scene to check if and object abstract light in other words casting a shadow
		for(auto curObj : objectList)
		{
			if((validInt = curObj->TestIntersectioons(lightRay, poi, poiNormal, poiColor)))
				break;
		}
		// if no interstaction with any object found then there is no shadows
		// and proceed with calculating the the I(s,v)
		if(!validInt)
		{
			qbVector<double> reflacted_vector;
			reflacted_vector = lightRay.m_lab - 2 * (qbVector<double>::dot(lightRay.m_lab, localNormal))* localNormal;
			double dotProduct = qbVector<double>::dot(reflacted_vector, cameraRay.m_lab);
			if(dotProduct > 0.0)
				SpectacularIntisity = curLight->m_intensity * std::pow(dotProduct, m_shininess);
		}
		red += curLight->m_color.GetElement(0) * SpectacularIntisity;
		green += curLight->m_color.GetElement(1) * SpectacularIntisity;
		blue += curLight->m_color.GetElement(2) * SpectacularIntisity;
	}
	specColor.SetElement(0, red);
	return specColor;
}

