#include "headers/MaterialBase.hpp"

RT::MaterialBase::MaterialBase()
{
	m_max_reflectionsRays = 6;
	m_reflectionRayCount = 0;

}

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
		validIllum = 
		curLight -> ComputeIllumination(intPoint, localNormal,
				objectList, currentObject, color, intensity);
		
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

qbVector<double> RT::MaterialBase::ComputeReflectionColor(
		const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
		const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
		const std::shared_ptr<RT::ObjectBase> &currentObject,
		const qbVector<double> &intPoint, const qbVector<double> &localNormal,
		const RT::Ray &incidentRay)
{
	qbVector<double> reflectionColor {3};

	//Compute the reflection vectore
	qbVector<double> d = incidentRay.m_lab;
	qbVector<double> reflectionVector  = d - (2 * qbVector<double>::dot(d, localNormal) * localNormal);
	
	// construct the reflection Ray
	RT::Ray reflectionRay (intPoint, intPoint + reflectionVector);

	// cast to scene and find cloeset objct that intertract with it
	std::shared_ptr<RT::ObjectBase> closestObj;
	qbVector<double> closestLocalNormal {3};
	qbVector<double> closestLocalColor {3};
	qbVector<double> closestIntPoint {3};

	bool intFound = castRay(reflectionRay, objectList, currentObject, closestObj,
			closestIntPoint, closestLocalNormal, closestLocalColor);

	// calc the illumination for the closestObj assuming that therer awas a valid int
	qbVector<double> mtColor {3};
	if ((intFound) && (m_reflectionRayCount < m_max_reflectionsRays))
	{
		//increment refRayCount 
		m_reflectionRayCount++;

		//check if obj has matreial
		if(closestObj->has_material)
			// use the material to calc the color 
			mtColor = closestObj->m_pmaterial->
			ComputeColor(objectList, lightList, closestObj,
					closestIntPoint, closestLocalNormal, reflectionRay);
		else
			mtColor = RT::MaterialBase::ComputeDiffuseColoe(objectList, lightList, closestObj,
					closestIntPoint, closestLocalNormal, closestObj->m_baseColor);
	}else
	{
		// leave mtColor as it is
	}
	reflectionColor = mtColor;
	return (reflectionColor);
}

// function to cast ray to the scene 
bool RT::MaterialBase::castRay(const RT::Ray &castRay, const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
		const std::shared_ptr<RT::ObjectBase> &thisObj,
		std::shared_ptr<RT::ObjectBase> &closestObj,
		qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
		qbVector<double> &closestLocalColor)
{

	qbVector<double> intPoint {3};
	qbVector<double> localNormal {3};
	qbVector<double> localColor {3};

	double minDist  = 1e6;
	bool intfound = false;

	for(auto curobj : objectList)
	{
		if(curobj != thisObj)
		{

			bool valid_int = curobj->TestIntersectioons(castRay, intPoint, localNormal, localColor);
			if(valid_int)
			{
				intfound = true;
				double dist = (intPoint - castRay.m_point1).norm();

				if(dist < minDist)
				{
					minDist = dist;
					closestObj = curobj;
					closestIntPoint = intPoint;
					closestLocalNormal = localNormal;
					closestLocalColor = localColor;
				}
			}
		}
	}
	return (intfound);
}


