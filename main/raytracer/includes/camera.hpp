#ifndef CAMERA_H
#define CAMERA_H
#include "../../qbLinAlg/qbVector.h"
#include "ray.h"

namespace RT {
	class Camera{
		public:
			Camera();
			Camera (Camera& camera);
			//Function to set camera position
			void SetPosition	(const qbVector<double> &newPosition);
			void SetLookAt		(const qbVector<double> &newLookAt);
			void SetUp			(const qbVector<double> &upVector);
			void SetLenght		(double lenght);
			void SetHorzSize	(double newHorzSize);
			void SetAspect		(double newAspect);

			//Function to return parameters
			qbVector<double>	GetPosition();
			qbVector<double>	GetLookAt();
			qbVector<double>	GetUp();
			qbVector<double>	GetU();
			qbVector<double>	GetV();
			qbVector<double>	GetScreenCenter();
			double				GetLenght();
			double				GetHorzSize();
			double				GetAspect();
			//Function to generate a ray
			bool					GenerateRay(float proScreenX, float proScreenY, RT::Ray &cameraRay);
			// Function to update cemera geometry
			void				UpdateCameraGeometry();

		private:
			qbVector<double>	m_cameraPosition	{3};
			qbVector<double>	m_cameraLookAt		{3};
			qbVector<double>	m_upVector			{3};
			qbVector<double>	m_uVector			{3};
			double				m_cameraLenght;
			double				m_cameraHorSize;
			double				m_cameraAspectRation;

			qbVector<double>	m_aligmentVector			{3};
			qbVector<double>	m_projectionScreenU			{3};
			qbVector<double>	m_projectionScreenV			{3};
			qbVector<double>	m_projectionScreenCentre	{3};
	};

}
#endif
