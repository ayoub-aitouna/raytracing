#include "includes/scene.hpp"
#include "includes/camera.hpp"
#include "includes/objectbase.hpp"
#include "includes/objsphere.hpp"
#include "includes/pointlight.hpp"
#include "includes/ray.h"
#include <memory>
#include <vector>

RT::Scene::Scene()
{
	m_camera.SetPosition(qbVector<double>{std::vector<double>{0, -10, 0}});
	m_camera.SetLookAt(qbVector<double>{std::vector<double>{0, 0, 0}});
	m_camera.SetUp(qbVector<double>{std::vector<double>{0, 0, 0.1}});
	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();

	//Cunstroct a test sphere
	m_objectList.push_back(std::make_shared<RT::ObjSphere> (RT::ObjSphere()));

	//Cunstroct a teset Light
	m_lightList.push_back(std::make_shared<RT::PointLight>(RT::PointLight()));
	m_lightList.at(0)->m_location = qbVector<double>{std::vector<double>{5,-10,5}};
	m_lightList.at(0)->m_color = qbVector<double>{std::vector<double>{255.0,255.0,255.0,255.0}};
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
		for (int y = 0; y < ySize; ++y)
		{
			// normlize X and y coordinates
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;
			// generate the ray for this pixel.
			m_camera.GenerateRay(normX, normY, cameraRay);

			// test for interstaction with all objects in the Scene
			for (auto currentObject : m_objectList)
			{
				bool validInt = currentObject->TestIntersectioons(cameraRay, intPoint, localNormal, localColor);
				// if we have valide intersection , change pixel to red
				if (validInt)
				{
					//Comput the intensity of illumination
					double intensity;
					qbVector<double> color {3};
					bool valideIlum = false;
					for(auto currentlight : m_lightList)
					{
						valideIlum = currentlight->ComputeIllumination(intPoint, localNormal, m_objectList, currentObject, color, intensity);

					}
					// Comput the distance between camera ana point of interstaction

					double dist = (intPoint - cameraRay.m_point1).norm();
					if(dist > maxDist)
						maxDist = dist;
					if(dist < minDist)
						minDist = dist;

					//image.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
					if(valideIlum)
						image.SetPixel(x,y,255.0 * intensity,0.0,0.0);
					else
						image.SetPixel(x,y,0,0,0);
				}
				else
				{
					image.SetPixel(x, y, 0.0, 0.0, 0.0);
				}
			}
		}
	}
	std::cout << "Minimum distanst : " << minDist<<std::endl;
	std::cout << "Maximum distanst : " << maxDist<<std::endl;

	return true;
}
