#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "image.hpp"
#include "camera.hpp"
#include "lightbase.hpp"
#include "objectbase.hpp"
#include "objsphere.hpp"
#include "pointlight.hpp"
#include "../../qbLinAlg/qbVector.h"

namespace RT {
	class Scene
	{
		public:
			Scene();
			bool Render(Image &image);

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
