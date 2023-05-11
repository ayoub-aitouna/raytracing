#include "headers/SimpleMaterial.hpp"
#include <cmath>

RT::SimpleMaterial::SimpleMaterial()
{
}

RT::SimpleMaterial::SimpleMaterial(qbVector<double> m_baseColor,
								   double m_reflectivity,
								   double m_shininess)
{
	this->m_baseColor = m_baseColor;
	this->m_reflectivity = m_reflectivity;
	this->m_shininess = m_shininess;
}

RT::SimpleMaterial::~SimpleMaterial()
{
}

// function to compute illumination cintribition
qbVector<double> RT::SimpleMaterial::ComputeColor(const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
												  const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
												  const std::shared_ptr<RT::ObjectBase> &currentObject,
												  const qbVector<double> &intPoint, const qbVector<double> &localNormal,
												  const RT::Ray &cameraRay)
{
	// Define an initial Material
	qbVector<double> mtColor{3};
	qbVector<double> refColor{3};
	qbVector<double> difColor{3};
	qbVector<double> specColor{3};

	// clc the diffuse colors
	qbVector<double> selected_color = has_texture ? m_texttures.at(0)->GetColor(currentObject->u_v_cords) : m_baseColor;
	difColor = ComputeDiffuseColoe(objectList, lightList, currentObject, intPoint, localNormal, selected_color);
	// calc the reflection Component
	if (m_reflectivity > 0.0)
	{
		refColor = ComputeReflectionColor(objectList, lightList, currentObject,
										  intPoint, localNormal, cameraRay);
	}

	// combain reflection and diffuse components
	mtColor = (refColor * m_reflectivity) + (difColor * (1 - m_reflectivity));

	// comput the specular compunent
	if (m_shininess > 0.0)
		specColor = ComputeSpectular(objectList, lightList, intPoint, localNormal, cameraRay);

	// Add spectular component to final color
	mtColor = mtColor + specColor;
	return (mtColor);
}

qbVector<double> RT::SimpleMaterial::ComputeSpectular(
	const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
	const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
	const qbVector<double> &intPoint, const qbVector<double> &localNormal,
	const RT::Ray &cameraRay)
{
	double red = 0, green = 0, blue = 0;
	qbVector<double> specColor{3};

	for (auto curLight : lightList)
	{
		double SpectacularIntisity = 0.0;

		qbVector<double> lightDir = (curLight->m_location - intPoint).Normalized();

		// add small padding from start point and the surface
		// to avoid the ray from inetersact with the same object again.
		qbVector<double> startPoint = intPoint + (lightDir * 0.001);

		// construct a ray from the  point of interstaction to the light.
		RT::Ray lightRay(startPoint, startPoint + lightDir);

		qbVector<double> poi{3};
		qbVector<double> poiNormal{3};
		qbVector<double> poiColor{3};
		bool validInt = false;

		// loop through all the objects in thee scene to check if and object abstract light in other words casting a shadow
		for (auto curObj : objectList)
		{
			validInt = curObj->TestIntersectioons(lightRay, poi, poiNormal, poiColor);
			if (validInt)
				break;
		}
		// if no interstaction with any object found then there is no shadows
		// and proceed with calculating the the I(s,v)

		if (!validInt)
		{

			qbVector<double> d = lightRay.m_lab;

			qbVector<double> r = d - (2 * qbVector<double>::dot(d, localNormal) * localNormal);
			r.Normalized();

			qbVector<double> v = cameraRay.m_lab;
			v.Normalized();

			double dotProduct = qbVector<double>::dot(r, v);

			if (dotProduct > 0.0)
				SpectacularIntisity = m_reflectivity * pow(dotProduct, m_shininess);
		}
		red += curLight->m_color.GetElement(0) * SpectacularIntisity;
		green += curLight->m_color.GetElement(1) * SpectacularIntisity;
		blue += curLight->m_color.GetElement(2) * SpectacularIntisity;
	}
	specColor.SetElement(0, red);
	specColor.SetElement(1, green);
	specColor.SetElement(2, blue);
	return specColor;
}
