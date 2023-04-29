#ifndef PLAN_H
# define PLAN_H
#include "objectbase.hpp"

namespace RT {
	class ObjectPlan : public RT::ObjectBase
	{
		public:
			ObjectPlan();	
			//override the distractor
			~ObjectPlan() override;

			//override the function to test for interstactions.
			virtual bool TestIntersectioons(const RT::Ray &castRay,
					qbVector<double> &intPoint, qbVector<double> &localNormal,
					qbVector<double> &localColor) override;

		private:

	};
}
#endif
