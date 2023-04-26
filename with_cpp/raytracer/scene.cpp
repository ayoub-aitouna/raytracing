#include "includes/scene.hpp"
#include "includes/camera.hpp"
#include "includes/objectbase.hpp"
#include "includes/objectplan.hpp"
#include "includes/objsphere.hpp"
#include "includes/pointlight.hpp"
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
	RT::parcer p;
	RT::SceneInstance m_scene = p.parsemap(NULL);
	for (auto obj : m_scene.getobjects())
		m_objectList.push_back(obj);
	for (auto light : m_scene.getLIghts())
		m_lightList.push_back(light);
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
			qbVector<double> intPoint{3};
			qbVector<double> localNormal{3};
			qbVector<double> localColor{3};
			std::shared_ptr<ObjectBase> closest_obj;
			qbVector<double> closest_int{3};
			qbVector<double> closest_color{3};
			qbVector<double> closest_norm{3};

			double normX = (static_cast<double>(x) * xFact) - 1;
			double normY = (static_cast<double>(y) * yFact) - 1;
			bool found_int = false;
			double minDist = 1e6;

			m_camera.GenerateRay(normX, normY, cameraRay);

			for (auto obj : m_objectList)
			{
				bool valid_int = obj->TestIntersectioons(cameraRay, intPoint, localNormal, localColor);

				if (valid_int)
				{
					found_int = true;
					double dist = (intPoint - cameraRay.m_point1).norm();

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
			// calculat the illumination
			if (found_int)
			{
				double red = 0, blue = 0, green = 0;

				bool validIIlumination = false;
				bool illuminationFound = false;
				double Intisity;

				qbVector<double> color{3};

				for (auto curr_light : m_lightList)
				{

					validIIlumination = curr_light->ComputeIllumination(closest_int, closest_norm,
																		m_objectList, closest_obj, color, Intisity);

					if (validIIlumination)
					{
						illuminationFound = true;
						red += color.GetElement(0) * Intisity;
						green += color.GetElement(1) * Intisity;
						blue += color.GetElement(2) * Intisity;
						// RT::Gtform::PrintVector(color);
					}
				}

				if (illuminationFound)
				{
					red *= closest_color.GetElement(0);
					green *= closest_color.GetElement(1);
					blue *= closest_color.GetElement(2);

					image.SetPixel(x, y, red, green, blue);
				}
			}
		}
	}
	return true;
}
