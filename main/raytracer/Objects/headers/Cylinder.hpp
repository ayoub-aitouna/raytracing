#ifndef CYLINDER
# define CYLINDER
#include "objectbase.hpp"

namespace RT {
	class ObjCylinder : public RT::ObjectBase
	{
		public:
			ObjCylinder();	
			//override the distractor
			~ObjCylinder() override;

			//override the function to test for interstactions.
			virtual bool TestIntersectioons(const RT::Ray &castRay,
					qbVector<double> &intPoint, qbVector<double> &localNormal,
					qbVector<double> &localColor) override;

		private:

	};
}
#endif
