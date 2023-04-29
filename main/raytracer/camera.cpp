#include "includes/camera.hpp"
#include "includes/ray.h"
#include <math.h>
#include <string>
#include <vector>

RT::Camera::Camera()
{
	m_cameraPosition = qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}};
	m_cameraLookAt = qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
	m_upVector = qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
	m_cameraLenght = 1.0;
	m_cameraHorSize = 1.0;
	m_cameraAspectRation = 1.0;
}

void RT::Camera::SetPosition(const qbVector<double> &newPosition)
{
	m_cameraPosition = newPosition;
}

void RT::Camera::SetLookAt(const qbVector<double> &newLookAt)
{
	m_cameraLookAt = newLookAt;
}

void RT::Camera::SetUp(const qbVector<double> &upVector)
{
	m_upVector = upVector;
}

void RT::Camera::SetLenght(double lenght)
{
	m_cameraLenght = lenght;
}

void RT::Camera::SetHorzSize(double newHorzSize)
{
	m_cameraHorSize = newHorzSize;
}

void RT::Camera::SetAspect(double newAspect)
{
	m_cameraAspectRation = newAspect;
}

// getters

qbVector<double> RT::Camera::GetPosition()
{
	return m_cameraPosition;
}

qbVector<double> RT::Camera::GetLookAt()
{
	return m_cameraLookAt;
}

qbVector<double> RT::Camera::GetUp()
{
	return m_upVector;
}

double RT::Camera::GetLenght()
{
	return m_cameraLenght;
}

double RT::Camera::GetHorzSize()
{
	return m_cameraHorSize;
}

double RT::Camera::GetAspect()
{
	return m_cameraAspectRation;
}

qbVector<double> RT::Camera::GetU()
{
	return m_projectionScreenU;
}

qbVector<double> RT::Camera::GetV()
{
	return m_projectionScreenV;
}

qbVector<double> RT::Camera::GetScreenCenter()
{
	return m_projectionScreenCentre;
}

void print_vector(qbVector<double> &inputVector, std::string msg)
{
	int Rows = inputVector.GetNumDims();
	std::cout << msg << std::endl;
	for (int row = 0; row < Rows; ++row)
	{
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	}
}

// Function to comput camera geometry

void RT::Camera::UpdateCameraGeometry()
{
	// first comput the vector from camera position to lookAt possition
	m_aligmentVector = m_cameraLookAt - m_cameraPosition;
	m_aligmentVector.Normalize();
	/* print_vector(m_upVector, "the UP Vectore"); */
	/* print_vector(m_aligmentVector,"m_aligmentVector"); */
	// Second, comput the U and V Vectors.

	m_projectionScreenU = qbVector<double>::cross(m_aligmentVector, m_upVector);
	m_projectionScreenU.Normalize();
	/* print_vector(m_projectionScreenU, "projectionScreeen U"); */
	m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_aligmentVector);
	m_projectionScreenV.Normalize();

	/* print_vector(m_projectionScreenV, "m_projectionScreenV"); */

	// thirdly comput the position of the center point of the screen.
	m_projectionScreenCentre = m_cameraPosition + (m_cameraLenght * m_aligmentVector);

	// modify the U and V vectors to match the Size and aspect ratio.
	m_projectionScreenU = m_projectionScreenU * m_cameraHorSize;
	m_projectionScreenV = m_projectionScreenV * (m_cameraHorSize / m_cameraAspectRation);
}

bool RT::Camera::GenerateRay(float proScreenX, float proScreenY, RT::Ray &cameraRay)
{
	// Compute the location of the screen point in world coordinates.
	qbVector<double> screenWorldPart1 = m_projectionScreenCentre + (m_projectionScreenU * proScreenX);
	qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);

	// Use this point along with the camera position to compute the ray.
	cameraRay.m_point1 = m_cameraPosition;
	cameraRay.m_point2 = screenWorldCoordinate;
	cameraRay.m_lab = screenWorldCoordinate - m_cameraPosition;

	return true;
}

