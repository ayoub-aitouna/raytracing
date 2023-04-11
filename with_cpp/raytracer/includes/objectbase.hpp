#ifndef OBJECTBASE_H
#define OBJECTBASE_H
#include "../../qbLinAlg/qbVector.h"
#include "ray.h"
#include "gtfm.hpp"

namespace RT {
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

		public:
			qbVector<double> m_baseColor {3};
			//geometric transform Applied to object
			RT::Gtform m_trasformMatrix;
	};
}
#endif
