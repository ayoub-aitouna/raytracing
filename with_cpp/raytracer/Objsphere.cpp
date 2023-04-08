#include "objectbase.hpp"
#include "objsphere.hpp"
#include <cmath>
#include <math.h>

RT::ObjSphere::ObjSphere()
{}

RT::ObjSphere::~ObjSphere()
{
}

// F to test for intersection
bool RT::ObjSphere::TestIntersectioons(const RT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
	// t^2(v.v) + 2t(p1.v)+(p1.p1) -r^2 = 0;
	// at^2 + bt + c = 0
	// a = (v.v);
	// b = 2(p1.v)
	// c = (p1 . p1) - r^2
	// comput the values of a,b,c.
	
	qbVector<double> vhat = castRay.m_lab;
	vhat.Normalize();
	
	//Note that a is equal to thr squared magnitude of the direction of thr cast ras . As this will be a unit vector,
	//we cam canclude that the value of 'a' willl always be 1.
	//a - 1.0
	
	//calculate b.
	double b = 2 * qbVector<double>::dot(castRay.GetPoint1(), vhat);

	double raduis = 1.0;
	double c = qbVector<double>::dot(castRay.GetPoint1(),castRay.GetPoint1()) - std::sqrt(raduis);

	// test if there is interstaction dela = b^2 - 4ac; and a = 1.0 so delta - b^2 -4c;
	double intTest = (b * b) - 4.0 * c;

	if(intTest > 0.0)
	{
		// we have intersection
		double numSQRT = sqrtf(intTest);
		double t1 = (-b + numSQRT) / 2.0;
		double t2 = (-b - numSQRT) / 2.0;
		//if either t1 || t2 are negative , then at least part of the object is behind the camera and so we ignore it.
		if(t1 < 0.0 || t2 < 0.0)
			return false;
		// Determine which point of interstaction was closest to the camera
		if(t1 < t2)
			intPoint = castRay.m_point1 + (vhat * t1);
		else
			intPoint = castRay.m_point1 + (vhat * t2);
		// compute the local Normal (for sphere at origin)
		// the normal is form the center to the interstaction point 
		// normal = intPoint - center
		// the center is the center so {0.0,0.0,0.0}
		// means that localNormal = intPoint
		localNormal = intPoint;
		localNormal.Normalized();
		return true;
	}
	return false;
}
