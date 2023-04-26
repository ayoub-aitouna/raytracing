#include "../includes/objectplan.hpp"
#include <clocale>
#include <cmath>
#include <functional>
#include <vector>

RT::ObjectPlan::ObjectPlan()
{}

RT::ObjectPlan::~ObjectPlan()
{}


//override the function to test for interstactions.
bool RT::ObjectPlan::TestIntersectioons(const RT::Ray &castRay,
		qbVector<double> &intPoint, qbVector<double> &localNormal,
		qbVector<double> &localColor)
{

	//we have the equatoin to calculate the point of interstactions
	// l = a + t k , l & a & are vectors
	// k is the cast ray normal
	// l is any / all point of interstactions
	// t = castRay.point1[2] / k[2]

	// first we transform out castRay into plan local coords 
	RT::Ray bckRay = m_trasformMatrix.Apply(castRay, RT::BCKTFORM);
	qbVector<double> k = bckRay.m_lab;
	k.Normalize();

	// if will be intersection . if the ray not parallel to the plan 
	if(CloseEnough(k.GetElement(2), 0.0))
		return false;

	// there in an intersection between ray & plan
	double t = bckRay.m_point1.GetElement(2) / (-1 * k.GetElement(2));

	// if t is negative means the plan is behind the camera 
	if(t < 0)
		return false;	

	double u = bckRay.m_point1.GetElement(0) + ( k.GetElement(0) * t);
	double v = bckRay.m_point1.GetElement(1) + ( k.GetElement(1) * t);

	// if magnatude of u & v is less or equal 1 means we on the plan 
	// we do this to have limited plan
	// we can ignore this step and get an infinite plan
	//if(std::abs(u) >= 1  || abs(v) >= 1 )
	//	return  (false);

	// compute the point of intersection
	qbVector<double> pointofInter = bckRay.m_point1 + t * k;
	// transform intpont back to word coord
	intPoint = m_trasformMatrix.Apply(pointofInter, RT::FWDTFORM);
	// comput the local normal
	qbVector<double> localOrigin {std::vector<double>{0,0,0}};
	qbVector<double> normalVector {std::vector<double>{0,0,-1.0}};
	qbVector<double> GlobalOrigin = m_trasformMatrix.Apply(localOrigin, RT::FWDTFORM);
	localNormal = m_trasformMatrix.Apply(normalVector, RT::FWDTFORM) - GlobalOrigin;

	// return the base color
	localColor = m_baseColor;

	return (true);
}


