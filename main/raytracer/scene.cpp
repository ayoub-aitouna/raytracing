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
/*
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
	m_objectList.at(0)->AssingMAterial(testMaterial);
	m_objectList.at(1)->AssingMAterial(testMaterial);
	m_objectList.at(2)->AssingMAterial(testMaterial);
}
*/

// The constructor.
RT::Scene::Scene()
{
	// Create some materials.
	auto testMaterial = std::make_shared<RT::SimpleMaterial> (RT::SimpleMaterial());
	auto testMaterial2 = std::make_shared<RT::SimpleMaterial> (RT::SimpleMaterial());
	auto testMaterial3 = std::make_shared<RT::SimpleMaterial> (RT::SimpleMaterial());
	auto floorMaterial = std::make_shared<RT::SimpleMaterial> (RT::SimpleMaterial());
	
	// Setup the materials.
	testMaterial -> m_baseColor = qbVector<double>{std::vector<double>{0.25, 0.5, 0.8}};
	testMaterial -> m_reflectivity = 0.1;
	testMaterial -> m_shininess = 10.0;
	
	testMaterial2 -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.5, 0.0}};
	testMaterial2 -> m_reflectivity = 0.75;
	testMaterial2 -> m_shininess = 10.0;
	
	testMaterial3 -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.8, 0.0}};
	testMaterial3 -> m_reflectivity = 0.25;
	testMaterial3 -> m_shininess = 10.0;
	
	floorMaterial -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};
	floorMaterial -> m_reflectivity = 0.5;
	floorMaterial -> m_shininess = 0.0;
	
	// Configure the camera.
	m_camera.SetPosition(	qbVector<double>{std::vector<double> {0.0, -10.0, -2.0}} );
	m_camera.SetLookAt	( qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}} );
	m_camera.SetUp			( qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}} );
	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();
	
	// Construct a test sphere.
	m_objectList.push_back(std::make_shared<RT::ObjSphere> (RT::ObjSphere()));
	m_objectList.push_back(std::make_shared<RT::ObjSphere> (RT::ObjSphere()));
	m_objectList.push_back(std::make_shared<RT::ObjSphere> (RT::ObjSphere()));
	
	// Construct a test plane.
	m_objectList.push_back(std::make_shared<RT::ObjectPlan> (RT::ObjectPlan()));
	m_objectList.at(3) -> m_baseColor = qbVector<double>{std::vector<double> {0.5, 0.5, 0.5}};
	
	// Define a transform for the plane.
	RT::Gtform planeMatrix;
	planeMatrix.SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}},
														qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
														qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});
	m_objectList.at(3) -> SetTransformMatrix(planeMatrix);
	
	// Modify the spheres.
	RT::Gtform testMatrix1, testMatrix2, testMatrix3;
	testMatrix1.SetTransform(	qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}},
														qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
														qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});
														
	testMatrix2.SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
														qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
														qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});
														
	testMatrix3.SetTransform(	qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
														qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
														qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});
														
	m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
	m_objectList.at(1) -> SetTransformMatrix(testMatrix2);
	m_objectList.at(2) -> SetTransformMatrix(testMatrix3);
	
	m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{0.25, 0.5, 0.8}};
	m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.5, 0.0}};
	m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.8, 0.0}};
	
	// Assign materials to objects.
	m_objectList.at(0) -> AssingMAterial(testMaterial3);
	m_objectList.at(1) -> AssingMAterial(testMaterial);
	m_objectList.at(2) -> AssingMAterial(testMaterial2);
	
	// Construct a test light.
	m_lightList.push_back(std::make_shared<RT::PointLight> (RT::PointLight()));
	m_lightList.at(0) -> m_location = qbVector<double> {std::vector<double> {5.0, -10.0, -5.0}};
	m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {0.0, 0.0, 1.0}};
	
	m_lightList.push_back(std::make_shared<RT::PointLight> (RT::PointLight()));
	m_lightList.at(1) -> m_location = qbVector<double> {std::vector<double> {-5.0, -10.0, -5.0}};
	m_lightList.at(1) -> m_color = qbVector<double> {std::vector<double> {1.0, 0.0, 0.0}};
	
	m_lightList.push_back(std::make_shared<RT::PointLight> (RT::PointLight()));
	m_lightList.at(2) -> m_location = qbVector<double> {std::vector<double> {0.0, -10.0, -5.0}};
	m_lightList.at(2) -> m_color = qbVector<double> {std::vector<double> {0.0, 1.0, 0.0}};
}

// Function to perform the rendering.
bool RT::Scene::Render(Image &outputImage)
{
	// Get the dimensions of the output image.
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();
	
	// Loop over each pixel in our image.
	RT::Ray cameraRay;
	qbVector<double> intPoint			(3);
	qbVector<double> localNormal	(3);
	qbVector<double> localColor		(3);
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;
	for (int y=0; y<ySize; ++y)
	{
		// Display progress.
		std::cout << "Processing line " << y << " of " << ySize << "." << std::endl;
		
		for (int x=0; x<xSize; ++x)
		{
			// Normalize the x and y coordinates.
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;
			
			// Generate the ray for this pixel.
			m_camera.GenerateRay(normX, normY, cameraRay);
			
			// Test for intersections with all objects in the scene.
			std::shared_ptr<RT::ObjectBase> closestObject;
			qbVector<double> closestIntPoint		{3};
			qbVector<double> closestLocalNormal	{3};
			qbVector<double> closestLocalColor	{3};
			
			bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);
			
			/* Compute the illumination for the closest object, assuming that there
				was a valid intersection. */
			if (intersectionFound)
			{
				// Check if the object has a material.
				if (closestObject -> has_material)
				{
					// Use the material to compute the color.
					RT::MaterialBase::m_reflectionRayCount = 0;
					qbVector<double> color = closestObject -> m_pmaterial -> ComputeColor(	m_objectList, m_lightList,
							closestObject, closestIntPoint,
							closestLocalNormal, cameraRay);
					outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
				}
				else
				{
					// Use the basic method to compute the color.
					qbVector<double> matColor = RT::MaterialBase::ComputeDiffuseColoe(m_objectList, m_lightList,
																																							closestObject, closestIntPoint,
																																							closestLocalNormal, closestObject->m_baseColor);
					outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
				}
			}
		}
	}
	
	return true;
}


/*
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

			// bool found_int = castRay(cameraRay, closest_obj, closestIntPoint, closestLocalNormal, closestLocalColor);
			bool found_int = CastRay(cameraRay, closest_obj, closestIntPoint, closestLocalNormal, closestLocalColor);
			// calculat the illumination
			if (found_int)
			{
				// check if object has material
				if (closest_obj->has_material)
				{
					RT::MaterialBase::m_reflectionRayCount = 0;
					// use material to compute the color
					// print_V(closestIntPoint);
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
*/

// bool RT::Scene::castRay(RT::Ray &cats_ray, std::shared_ptr<ObjectBase> &closest_obj,
// 						qbVector<double> &closest_int, qbVector<double> &closest_norm,
// 						qbVector<double> &closest_color)
// {
// 	qbVector<double> intPoint{3};
// 	qbVector<double> localNormal{3};
// 	qbVector<double> localColor{3};
// 	bool found_int = false;
// 	double minDist = 1e6;

// 	for (auto obj : m_objectList)
// 	{
// 		bool valid_int = obj->TestIntersectioons(cats_ray, intPoint, localNormal, localColor);
// 		if (valid_int)
// 		{
// 			found_int = true;
// 			double dist = (intPoint - cats_ray.m_point1).norm();

// 			if (dist < minDist)
// 			{
// 				minDist = dist;
// 				closest_obj = obj;
// 				closest_int = intPoint;
// 				closest_norm = localNormal;
// 				closest_color = localColor;
// 			}
// 		}
// 	}
// 	return (found_int);
// }


// Function to cast a ray into the scene.
bool RT::Scene::CastRay(
	RT::Ray &castRay, std::shared_ptr<RT::ObjectBase> &closestObject,
	qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
	qbVector<double> &closestLocalColor)
{
	qbVector<double> intPoint			{3};
	qbVector<double> localNormal	{3};
	qbVector<double> localColor		{3};

	double minDist = 1e6;
	bool intersectionFound = false;

	for (auto currentObject : m_objectList)
	{
		bool validInt = currentObject -> TestIntersectioons(castRay, intPoint, localNormal, localColor);
		
		// If we have a valid intersection.
		if (validInt)
		{
			// Set the flag to indicate that we found an intersection.
			intersectionFound = true;
					
			// Compute the distance between the camera and the point of intersection.
			double dist = (intPoint - castRay.m_point1).norm();
					
			/* If this object is closer to the camera than any one that we have
				seen before, then store a reference to it. */
			if (dist < minDist)
			{
				minDist = dist;
				closestObject = currentObject;
				closestIntPoint = intPoint;
				closestLocalNormal = localNormal;
				closestLocalColor = localColor;
			}
		}
	}
	
	return intersectionFound;
}



