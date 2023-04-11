#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#include <math.h>
#include "../../qbLinAlg/qbVector.h"
#include "objectbase.hpp"
#include "ray.h"
#include "gtfm.hpp"

namespace RT {
class ObjSphere : public ObjectBase
	{
		public:
			 //Note that will define a unit sphere at the origin 
			 ObjSphere();

			 //override the destractor
			 virtual ~ObjSphere() override;
			 virtual bool TestIntersectioons(const RT::Ray &castRay, qbVector<double> &intPoint , qbVector<double> &localNormal, qbVector<double> &localColor) override;

	};

}
#endif
