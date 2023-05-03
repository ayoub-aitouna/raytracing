#ifndef SIMPLE_MATERIAL_H
#define SIMPLE_MATERIAL_H

#include "MaterialBase.hpp"
#include <vector>
namespace RT {

	class SimpleMaterial : public MaterialBase
	{
		public :
			SimpleMaterial();
			virtual ~SimpleMaterial();

			// function to compute illumination cintribition
			virtual qbVector<double> ComputeColor(
				const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
					const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
					const std::shared_ptr<RT::ObjectBase> &currentObject,
					const qbVector<double> &intPoint, const qbVector<double> &localNormal,
					const RT::Ray &cameraRay) override;
			// function to compute Spectilar highlights
			qbVector<double> ComputeSpectular(
				const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
					const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
					const qbVector<double> &intPoint, const qbVector<double> &localNormal,
					const RT::Ray &cameraRay);
		public: 
			qbVector<double> m_baseColor {std::vector<double> {1.0,0.0,1.0}};
			double m_reflectivity = 0.0;
			double m_shininess = 0.0;
	};
}
#endif
