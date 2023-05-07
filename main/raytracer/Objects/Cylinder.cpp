#include "headers/Cylinder.hpp"
#include <cmath>
#include <vector>
#include <stdlib.h>

RT::ObjCylinder::ObjCylinder()
{}

RT::ObjCylinder::~ObjCylinder()
{}

double *init_solutions()
{

	double *solutions = malloc(sizeof(double) * 4);
	int i = 0;
	while(i < 4)
		solutions[i++] = 100e6;
	return solutions;
}

bool RT::ObjCylinder::TestIntersectioons(const RT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
	// to find the interstaction point we need to solve equatoin at^2 + b +c = 0
	// in the giveen a = (vx^2 + vy^2) &&  b = 2 * ( VxPx + VyPy) && c = Px^2 + Py^2 - r^2
	// in local coords and unit CYLINDER we have r = 1; 
	// c = px^2 + py^2
	// smallest t is the distance between camera and point of intersection

	RT::Ray bckRay = m_trasformMatrix.Apply(castRay, RT::BCKTFORM);

	qbVector<double> v = bckRay.m_lab;
	v.Normalize();
	qbVector<double> p = bckRay.m_point1;
	qbVector<double> poi;

	double *solution = init_solutions();
	int *is_valide =  (int *)calloc(4, sizeof(int));

	double a = std::pow(v.GetElement(0), 2)  + std::pow(v.GetElement(1), 2);
	double b = 2 * ((v.GetElement(0) * p.GetElement(0)) + (v.GetElement(1) * p.GetElement(1)));
	double c = std::pow(p.GetElement(0), 2) + std::pow(p.GetElement(1), 2);
	double intTest = std::pow(b, 2) - 4.0 * a * c;

	std::array<qbVector<double>, 4> intpoints;

	//if intTest is negative then the ray those not intersecte with the object
	if(intTest >= 0)
	{
		double numSQRT = std::sqrt(intTest);

		solution[0] = (-b - numSQRT) / 2 * a;
		solution[1] = (-b + numSQRT) / 2 * a;

		intpoints.at(0) = p + solution[0] * v;
		intpoints.at(1) = p + solution[1] * v;
		if(solution[0] > 0 && std::fabs(intpoints.at(0).GetElement(2)) <= 1)
			is_valide[0] = 1;
		if(solution[1] > 0 && std::fabs(intpoints.at(1).GetElement(2)) <= 1)
			is_valide[1] = 1;
	}

	// if vector hase no z values of very close to 0 no need to test for interstaction
	// with caps cus the vector is near the middle of Cylinder
	if(!CloseEnough(v.GetElement(2), 0.0))
	{
		// calculat the intersection with the caps as a plan 
		solution[2] = (bckRay.m_point1.GetElement(2) - 1) / -v.GetElement(2);
		solution[3] = (bckRay.m_point1.GetElement(2) + 1) / -v.GetElement(2);

		intpoints.at(2) = p + solution[2] * v;
		intpoints.at(3) = p + solution[3] * v;
		if(solution[2] > 0.0 && (std::sqrtf(std::pow(intpoints.at(2).GetElement(0)) + std::pow(intpoints.at(2).GetElement(1)) < 1.0)))
			is_valide[2] = 1;
		if(solution[3] > 0.0 && (std::sqrtf(std::pow(intpoints.at(3).GetElement(0)) + std::pow(intpoints.at(3).GetElement(1)) < 1.0)))
			is_valide[2] = 1;
	}
	if(!is_valide[0] && !is_valide[1] && !is_valide[2] && !is_valide[3])
		return false;
	intPoint = m_trasformMatrix.Apply(intPoint, RT::FWDTFORM);
	//calculat the local normal 
	qbVector<double> localOrijin  = qbVector<double>{std::vector<double>{0,0,0}};
	qbVector<double> GbOrigin = m_trasformMatrix.Apply(localOrijin, RT::FWDTFORM);

	qbVector<double> ORGnormal = qbVector<double>{std::vector<double>{intPoint.GetElement(0), intPoint.GetElement(1), 0}};

	localColor = m_trasformMatrix.Apply(ORGnormal, RT::BCKTFORM) - GbOrigin;
	localNormal.Normalize();

	localColor = m_baseColor;
	return (true);
}
