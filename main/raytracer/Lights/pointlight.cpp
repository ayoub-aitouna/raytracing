#include "headers/pointlight.hpp"
#include "../includes/ray.h"
#include <vector>

RT::PointLight::PointLight()
{
	m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	m_intensity = 1.0;
}

RT::PointLight::~PointLight()
{
}

bool RT::PointLight::ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal, const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList, const std::shared_ptr<RT::ObjectBase> &currentObject, qbVector<double> &Color, double &intensity)
{
	Color = m_color;
	intensity = 0.0;
	// Construct a vector pointing from the intersection point to the light.
	qbVector<double>	lightDir = (m_location - intPoint).Normalized();
	// Compute a starting point.
	qbVector<double>	startPoint = intPoint;
	double				lightDist = (m_location - startPoint).norm();
	RT::Ray lightRay	(startPoint, startPoint + lightDir);
	qbVector<double>	poi {3};
	qbVector<double>	poicolor {3};
	qbVector<double>	poinormal {3};
	bool				valid_int = false;

	for (auto obj : objectList) {
		if(obj != currentObject)
		{
			valid_int = obj->TestIntersectioons(lightRay, poi, poinormal, poicolor);
			if(valid_int)
			{
				double dist = (poi - startPoint).norm();
				if(dist > lightDist)
					valid_int = false;

			}
		}
		if(valid_int)
			break;
	}
	if(valid_int)
		return false;

	//Compute the angle between local normal and the light ray
	//Note that we asume that localNormal is a unit vector.
	//unit vector is vector with lenght 1
	/* a & b are vectors 
	 * we calculat the angle between them by the formula 
	 a.b = |a|.|b| cosO
	 then we conclude O
	 O = (a.b) / |a|.|b|
	 a & b are unit vector so |a|.|b| = 1
	 so O = a.b
	 */

	double angle = acos(qbVector<double>::dot(localNormal, lightDir));

	// if the normal is point away from the light , then we have no ilumination
	double halfPI = 1.5708;
	if(angle > halfPI)
		return false;

	// else we do have illumination
	Color = m_color;
	intensity = m_intensity * (1.0 - (angle / halfPI));
	return true;
}
