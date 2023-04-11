#ifndef LIGHTBASE_H
#define LIGHTBASE_H
#include <memory>
#include <vector>
#include "../../qbLinAlg/qbVector.h"
#include "ray.h"
#include "objectbase.hpp"
namespace RT 
{
	class LightBase
	{
		public:
			LightBase();
			virtual ~LightBase();

			//function to compute illumination cintribition
			virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
					const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
					const std::shared_ptr<RT::ObjectBase> &currentObject,
					qbVector<double> Color, double &intensity);
		public:
			qbVector<double>	m_color {3};
			qbVector<double>	m_location {3};
			double				m_intensity;

	};
}
#endif
