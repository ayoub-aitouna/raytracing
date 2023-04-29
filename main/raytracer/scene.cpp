#include "includes/scene.hpp"
#include "includes/camera.hpp"
#include "Objects/headers/objectbase.hpp"
#include "Objects/headers/objectplan.hpp"
#include "Objects/headers/objsphere.hpp"
#include "Materials/headers/SimpleMaterial.hpp"
#include "Lights/headers/pointlight.hpp"
#include "includes/ray.h"
#include <cstdio>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "../parser/parcer.hpp"

RT::Scene::Scene()
{
	m_camera.SetPosition(qbVector<double>{std::vector<double>{0, -10, -1}});
	m_camera.SetLookAt(qbVector<double>{std::vector<double>{0, 0, 0}});
	m_camera.SetUp(qbVector<double>{std::vector<double>{0, 0, 0.1}});
	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();
	auto testMaterial = std::make_shared<RT::SimpleMaterial>(RT::SimpleMaterial());
	testMaterial->m_baseColor = qbVector<double>{std::vector<double>{0.25, 0.5, 0.8}};
	testMaterial->m_reflectivity = 0.5;
	testMaterial->m_shininess = 10.0;

	RT::parcer p;
	RT::SceneInstance m_scene = p.parsemap(NULL);
	for (auto obj : m_scene.getobjects())
		m_objectList.push_back(obj);
	for (auto light : m_scene.getLIghts())
		m_lightList.push_back(light);
	m_objectList.at(0) -> AssingMAterial(testMaterial);
	m_objectList.at(1) -> AssingMAterial(testMaterial);
	m_objectList.at(2) -> AssingMAterial(testMaterial);

}
bool RT::Scene::Render(Image &image)
{
	// configure the camera
	int xSize = image.GetXSize();
	int ySize = image.GetYSize();

	// Loop Over each pixel in out image
	RT::Ray cameraRay;
	qbVector<double> intPoint{3};
	qbVector<double> localNormal{3};
	qbVector<double> localColor{3};

	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;

	for (int x = 0; x < xSize; ++x)
	{
		int progress = (((float)(x) / (float)xSize) * 100) + 1;
		if (progress < 100)
			printf("\033[A\33[2K\r %d%%\n", progress);
		else
			printf("\033[A\33[2K\r DONE.\n");
		for (int y = 0; y < ySize; ++y)
		{
			std::shared_ptr<ObjectBase> closest_obj;
			qbVector<double> closestIntPoint{3};
			qbVector<double> closestLocalNormal{3};
			qbVector<double> closestLocalColor{3};
			qbVector<double> color;
			double normX = (static_cast<double>(x) * xFact) - 1;
			double normY = (static_cast<double>(y) * yFact) - 1;

			m_camera.GenerateRay(normX, normY, cameraRay);
			bool found_int = castRay(cameraRay, closest_obj, closestIntPoint, closestLocalNormal, closestLocalColor);
			// calculat the illumination
			if (found_int)
			{
				// check if object has material
				if (closest_obj->has_material)
				{
					// use material to compute the color
					qbVector<double> color = closest_obj->m_pmaterial->ComputeColor(m_objectList, m_lightList,
							closest_obj, closestIntPoint, closestLocalNormal, cameraRay);
					image.SetPixel(x, y,color.GetElement(0), color.GetElement(1), color.GetElement(2));
				}
				else
				{
					qbVector<double> diffuseColor = RT::MaterialBase::ComputeDiffuseColoe(m_objectList, m_lightList,
							closest_obj, closestIntPoint, closestLocalNormal, closest_obj->m_baseColor);
					image.SetPixel(x, y,diffuseColor.GetElement(0), diffuseColor.GetElement(1), diffuseColor.GetElement(2));
				}
			}
		}
	}
	return true;
}

bool RT::Scene::castRay(RT::Ray &cats_ray, std::shared_ptr<ObjectBase> &closest_obj,
		qbVector<double> &closest_int, qbVector<double> &closest_norm,
		qbVector<double> &closest_color)
{
	qbVector<double> intPoint{3};
	qbVector<double> localNormal{3};
	qbVector<double> localColor{3};
	bool found_int = false;
	double minDist = 1e6;

	for (auto obj : m_objectList)
	{
		bool valid_int = obj->TestIntersectioons(cats_ray, intPoint, localNormal, localColor);
		if (valid_int)
		{
			found_int = true;
			double dist = (intPoint - cats_ray.m_point1).norm();

			if (dist < minDist)
			{
				minDist = dist;
				closest_obj = obj;
				closest_int = intPoint;
				closest_color = localColor;
				closest_norm = localNormal;
			}
		}
	}
	return (found_int);
}
