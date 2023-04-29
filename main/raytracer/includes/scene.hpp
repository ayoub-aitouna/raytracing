#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "image.hpp"
#include "camera.hpp"
#include "../Lights/headers/lightbase.hpp"
#include "../Objects/headers/objectbase.hpp"
#include "../Objects/headers/objsphere.hpp"
#include "../Objects/headers/objectplan.hpp"
#include "../Lights/headers/pointlight.hpp"
#include "../../qbLinAlg/qbVector.h"

namespace RT {
	class Scene
	{
		public:
			Scene();
			bool Render(Image &image);
			bool castRay(RT::Ray &cats_ray, std::shared_ptr<ObjectBase> &closest_obj,
					qbVector<double> &closest_int, qbVector<double> &closest_norm,
					qbVector<double> &closest_color);
			//Private function
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
