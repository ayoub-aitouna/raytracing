#include "lightbase.hpp"

RT::LightBase::LightBase()
{

}

RT::LightBase::~LightBase()
{}

//Compute illumination
bool RT::LightBase::ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal, const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList, const std::shared_ptr<RT::ObjectBase> &currentObject, qbVector<double> Color, double &intensity)
{
	return false;
}
