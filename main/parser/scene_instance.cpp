#include "scene_instance.hpp"
#include <cstdio>
#include <ios>

RT::SceneInstance::SceneInstance()
{}

RT::SceneInstance::~SceneInstance()
{}

void RT::SceneInstance::addObject(std::shared_ptr<RT::ObjectBase> object)
{
	m_objectList.push_back(object);
}

void RT::SceneInstance::addLight(std::shared_ptr<RT::LightBase> light)
{
	m_lightList.push_back(light);
}

std::vector<std::shared_ptr<RT::ObjectBase>> RT::SceneInstance::getobjects(void)
{
	return (m_objectList);
}

std::vector<std::shared_ptr<RT::LightBase>> RT::SceneInstance::getLIghts(void)
{
	return (m_lightList);
}

RT::Camera RT::SceneInstance::getCamera(void)
{
	return (m_camera);
}
