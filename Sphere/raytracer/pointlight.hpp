#ifndef POINTLIGHT_H

#define POINTLIGHT_H
#include "lightbase.hpp"


namespace RT {
class PointLight : public LightBase
	{
		public:
			PointLight();
			virtual ~PointLight() override;

			//function to compute illumination cintribition
			virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
					const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
					const std::shared_ptr<RT::ObjectBase> &currentObject,
					qbVector<double> Color, double &intensity) override;
	};
}
#endif
