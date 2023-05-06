#include "headers/Cylinder.hpp"
#include <cmath>
#include <vector>

RT::ObjCylinder::ObjCylinder()
{}

RT::ObjCylinder::~ObjCylinder()
{}


bool RT::ObjCylinder::TestIntersectioons(const RT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
	// to find the interstaction point we need to solve equatoin at^2 + b +c = 0
	// in the giveen a = (vx^2 + vy^2) &&  b = 2 * ( VxPx + VyPy) && c = Px^2 + Py^2 - r^2
	// in local coords and unit CYLINDER we have r = 1; 
	// c = px^2 + py^2
	// smallest t is the distance between camera and point of intersection

	RT::Ray bckRay = m_trasformMatrix.Apply(castRay, RT::BCKTFORM);

	qbVector<double> v = bckRay.m_lab;
	qbVector<double> p = bckRay.m_point1;
	qbVector<double> poi;

	double a = std::pow(v.GetElement(0), 2)  + std::pow(v.GetElement(1), 2);
	double b = 2 * ((v.GetElement(0) * p.GetElement(0)) + (v.GetElement(1) * p.GetElement(1)));
	double c = std::pow(p.GetElement(0), 2) + std::pow(p.GetElement(1), 2);
	double intTest = std::pow(b, 2) - 4.0 * a * c;

	//if intTest is negative then the ray those not intersecte with the object
	if(intTest < 0)
		return false;

	double numSQRT = std::sqrt(intTest);
	double t1 = (-b - numSQRT) / 2 * a;
	double t2 = (-b + numSQRT) / 2 * a;

	double t = t1 < t2 ? t1 : t2;
	poi = p + t * v;
	if(std::fabs(poi.GetElement(0) >= 1))
		return false;

	intPoint = m_trasformMatrix.Apply(intPoint, RT::FWDTFORM);
	//calculat the local normal 
	qbVector<double> localOrijin  = qbVector<double>{std::vector<double>{0,0,0}};
	qbVector<double> GbOrigin = m_trasformMatrix.Apply(localOrijin, RT::FWDTFORM);
	localNormal = intPoint - GbOrigin;
	localNormal.Normalize();

	localColor = m_baseColor;
	return (true);
}
