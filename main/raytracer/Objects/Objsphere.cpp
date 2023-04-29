#include "headers/objectbase.hpp"
#include "headers/objsphere.hpp"
#include "../includes/ray.h"
#include <cmath>
#include <math.h>
#include <sys/types.h>
#include <vector>

RT::ObjSphere::ObjSphere()
{}

RT::ObjSphere::~ObjSphere()
{
}

// F to test for intersection
bool RT::ObjSphere::TestIntersectioons(const RT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
	//Copy the ray and apply the backword transform
	//appliyng from word to local
	RT::Ray bckRay = m_trasformMatrix.Apply(castRay, RT::BCKTFORM);

	// t^2(v.v) + 2t(p1.v)+(p1.p1) -r^2 = 0;
	// at^2 + bt + c = 0
	// a = (v.v);
	// b = 2(p1.v)
	// c = (p1 . p1) - r^2
	// comput the values of a,b,c.

	qbVector<double> vhat = bckRay.m_lab;
	vhat.Normalize();

	//Note that a is equal to thr squared magnitude of the direction of thr cast ras . As this will be a unit vector,
	//we cam canclude that the value of 'a' willl always be 1.
	//a = 1.0

	//calculate b.
	double b = 2 * qbVector<double>::dot(bckRay.GetPoint1(), vhat);
	double raduis = 1.0;
	double c = qbVector<double>::dot(bckRay.GetPoint1(), bckRay.GetPoint1()) - std::sqrt(raduis);
	// test if there is interstaction dela = b^2 - 4ac; and a = 1.0 so delta - b^2 -4c;
	double intTest = (b * b) - 4.0 * c;
	// intersection in the local world
	qbVector<double> poi;

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
			poi = bckRay.m_point1 + (vhat * t1);
		else
			poi = bckRay.m_point1 + (vhat * t2);
		// we transform the intersection back to the word coordiantes
		// from local to world
		intPoint = m_trasformMatrix.Apply(poi, RT::FWDTFORM);
		// we calculate the origin of sphere which is {0.0.0);
		// and then transform it into the word coordiantes
		// so we have the localNormal for the sphere in words coordiantes
		qbVector<double> objOrigin = qbVector<double> {std::vector<double>{.0,.0,.0}};
		qbVector<double> newObjOrigin = m_trasformMatrix.Apply(objOrigin, RT::FWDTFORM);
		// compute the local Normal (for sphere at origin)
		// the normal is form the center to the interstaction point 
		// normal = intPoint - center
		localNormal = intPoint - newObjOrigin;
		localNormal.Normalized();
		// return the base color 
		localColor = m_baseColor;
		return true;
	}
	return false;
	}
