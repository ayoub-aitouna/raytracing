#include "includes/scene.hpp"
#include "Materials/headers/MaterialBase.hpp"
#include "includes/camera.hpp"
#include "Objects/headers/objectbase.hpp"
#include "Objects/headers/objectplan.hpp"
#include "Objects/headers/objsphere.hpp"
#include "Objects/headers/Cylinder.hpp"
#include "Objects/headers/Cone.hpp"
#include "Materials/headers/SimpleMaterial.hpp"
#include "Lights/headers/pointlight.hpp"
#include "includes/ray.h"
#include <cstdio>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "../parser/parcer.hpp"
#include "Textures/headers/checker.hpp"

std::shared_ptr<RT::SimpleMaterial> RT::Scene::createMaterial(qbVector<double> color, double reflectivity, double shininess)
{
	std::shared_ptr<RT::SimpleMaterial> material = std::make_shared<RT::SimpleMaterial>(RT::SimpleMaterial());
	material->m_baseColor = color;
	material->m_reflectivity = reflectivity;
	material->m_shininess = shininess;
	return material;
}

RT::Scene::Scene()
{
	auto checkerTexture = std::make_shared<RT::Texture::Checker>(RT::Texture::Checker());
	checkerTexture->SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
								0.0,
								qbVector<double>{std::vector<double>{16, 16}});
	auto Cylinder = std::make_shared<RT::Texture::Checker>(RT::Texture::Checker());
	
	Cylinder->SetColor(qbVector<double>{std::vector<double>{.5,.5,.9}}, qbVector<double>{std::vector<double>{1,0.1,0.1}});
	Cylinder->SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
								0.0,
								qbVector<double>{std::vector<double>{M_PI * 4, 4}});
	// read .rt file and render scene
	RT::parcer p;
	RT::SceneInstance m_scene;
	m_scene = p.parsemap(NULL);
	m_camera = RT::Camera(m_scene.getCamera());
	m_camera.UpdateCameraGeometry();

	for (auto obj : m_scene.getobjects())
		m_objectList.push_back(obj);
	for (auto light : m_scene.getLIghts())
		m_lightList.push_back(light);
	m_objectList.at(1)->m_pmaterial->AssingTexture(Cylinder);
	m_objectList.at(2)->m_pmaterial->AssingTexture(Cylinder);
	m_objectList.at(4)->m_pmaterial->AssingTexture(checkerTexture);
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

	for (int y = 0; y < ySize; ++y)
	{
		int progress = (((float)(y) / (float)ySize) * 100) + 1;
		if (progress < 100)
			printf("\033[A\33[2K\r %d%%\n", progress);
		else
			printf("\033[A\33[2K\r DONE.\n");
		for (int x = 0; x < xSize; ++x)
		{
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;

			m_camera.GenerateRay(normX, normY, cameraRay);

			std::shared_ptr<ObjectBase> closest_obj;
			qbVector<double> closestIntPoint{3};
			qbVector<double> closestLocalNormal{3};
			qbVector<double> closestLocalColor{3};

			bool found_int = CastRay(cameraRay, closest_obj, closestIntPoint, closestLocalNormal, closestLocalColor);
			// calculat the illumination
			if (found_int)
			{
				// check if object has material
				if (closest_obj->has_material)
				{
					RT::MaterialBase::m_reflectionRayCount = 0;
					// use material to compute the color
					qbVector<double> color = closest_obj->m_pmaterial->ComputeColor(m_objectList, m_lightList,
																					closest_obj, closestIntPoint, closestLocalNormal, cameraRay);
					image.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
				}
				else
				{
					qbVector<double> diffuseColor = RT::MaterialBase::ComputeDiffuseColoe(m_objectList, m_lightList,
																						  closest_obj, closestIntPoint, closestLocalNormal, closest_obj->m_baseColor);
					image.SetPixel(x, y, diffuseColor.GetElement(0), diffuseColor.GetElement(1), diffuseColor.GetElement(2));
				}
			}
		}
	}
	return true;
}

bool RT::Scene::CastRay(RT::Ray &cats_ray, std::shared_ptr<ObjectBase> &closest_obj,
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
				closest_norm = localNormal;
				closest_color = localColor;
			}
		}
	}
	return (found_int);
}
