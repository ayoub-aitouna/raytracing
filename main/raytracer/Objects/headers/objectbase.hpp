#ifndef OBJECTBASE_H
#define OBJECTBASE_H
#include "../../../qbLinAlg/qbVector.h"
#include "../../includes/ray.h"
#include "../../includes/gtfm.hpp"
#include <cmath>
#include <math.h>

namespace RT {
	/* Forward-declar the material base class . This will overriden later
	*/
	class MaterialBase;
	class ObjectBase
	{
		public:
			ObjectBase();
			virtual ~ObjectBase();
			//function to test each section
			virtual bool TestIntersectioons(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);
			//Function to test floating-point numbers are close to being equal.
			bool CloseEnough(const double f1, const double f2);
			void SetTransformMatrix(const RT::Gtform &transformMatrix);
			// Funtion to Assing material
			bool AssingMAterial(const std::shared_ptr<RT::MaterialBase> &objMaterial);

		public:
			qbVector<double> m_baseColor {3};
			//geometric transform Applied to object
			RT::Gtform m_trasformMatrix;

			// a refrence to the material assinged to this object
			std::shared_ptr<RT::MaterialBase> m_pmaterial;
			// flag to indecate if this object has a material
			bool has_material = false;
	};
}

#endif
