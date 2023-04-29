#include "headers/objectbase.hpp"
#include <cmath>
#include <math.h>

#define EPSILON 1e-21f;


RT::ObjectBase::ObjectBase()
{
	
}


RT::ObjectBase::~ObjectBase()
{

}

//function to test for intersections
bool RT::ObjectBase::TestIntersectioons(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
	return false;
}
//function to assing the material
bool RT::ObjectBase::AssingMAterial(const std::shared_ptr<RT::MaterialBase> &objMaterial)
{
	m_pmaterial = objMaterial;
	has_material = true;
	return (has_material);
}
bool RT::ObjectBase::CloseEnough(const double f1, const double f2)
{
	return  std::fabs(f1-f2) < EPSILON;
}

void RT::ObjectBase::SetTransformMatrix(const RT::Gtform &transformMatrix)
{
	m_trasformMatrix = transformMatrix;
}
