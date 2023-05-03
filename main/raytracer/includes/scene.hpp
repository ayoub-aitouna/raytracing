#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "image.hpp"
#include "camera.hpp"
#include "../Lights/headers/lightbase.hpp"
#include "../Objects/headers/objectbase.hpp"
#include "../Materials/headers/MaterialBase.hpp"
#include "../Objects/headers/objsphere.hpp"
#include "../Objects/headers/objectplan.hpp"
#include "../Lights/headers/pointlight.hpp"
#include "../../qbLinAlg/qbVector.h"

namespace RT
{
	class Scene
	{
	public:
		Scene();
		bool Render(Image &image);
		bool CastRay(
			RT::Ray &castRay, std::shared_ptr<RT::ObjectBase> &closestObject,
			qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
			qbVector<double> &closestLocalColor);
		// Private function
	private:
		// private members
	private:
		RT::Camera m_camera;
		// the list of objects in the scene
		std::vector<std::shared_ptr<RT::ObjectBase>> m_objectList;

		// the List of light in the scene
		std::vector<std::shared_ptr<RT::LightBase>> m_lightList;
	};

}

#endif
