#ifndef OBJECTBASE_H
#define OBJECTBASE_H
#include "../qbLinAlg/qbVector.h"
#include "ray.h"

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

		public:
			qbVector<double> m_baseColor {3};
	};
}
#endif
