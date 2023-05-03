#ifndef MATERIALBASE_H
#define MATERIALBASE_H
#include <memory>
#include <vector>
#include "../../../qbLinAlg/qbVector.h"
#include "../../Objects/headers/objectbase.hpp"
#include "../../Lights/headers/lightbase.hpp"
#include "../../includes/ray.h"
namespace RT
{
	class MaterialBase
	{
		public:
			MaterialBase();
			virtual ~MaterialBase();

			// function to compute illumination cintribition
			virtual qbVector<double> ComputeColor(
				const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
				const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
				const std::shared_ptr<RT::ObjectBase> &currentObject,
				const qbVector<double> &intPoint, const qbVector<double> &localNormal,
				const RT::Ray &cameraRay);

			// Function to calculat diffuse color.
			static qbVector<double> ComputeDiffuseColoe(
				const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
				const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
				const std::shared_ptr<RT::ObjectBase> &currentObject,
				const qbVector<double> &intPoint, const qbVector<double> &localNormal,
				const qbVector<double>	&baseColor);

			qbVector<double> ComputeReflectionColor(
				const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
				const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
				const std::shared_ptr<RT::ObjectBase> &currentObject,
				const qbVector<double> &intPoint, const qbVector<double> &localNormal,
				const RT::Ray &incidentRay);

			// Function to cast a ray into the scene.
			bool castRay(
					const RT::Ray &castRay,
					const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
					const std::shared_ptr<RT::ObjectBase> &thisObj,
					std::shared_ptr<RT::ObjectBase> &closestObj,
					qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
					qbVector<double> &closestLocalColor);

		public:
			inline static int m_max_reflectionsRays;
			inline static int m_reflectionRayCount;

		private:
	};
}
#endif
