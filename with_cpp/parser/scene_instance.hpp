#ifndef SCENE_INSTANS_HPP
#define SCENE_INSTANS_HPP
#include <cerrno>
#include <vector>
#include <memory>
#include <vector>
#include "../raytracer/includes/objectbase.hpp"
#include "../raytracer/includes/objsphere.hpp"
#include "../raytracer/includes/objectplan.hpp"
#include "../raytracer/includes/lightbase.hpp"
#include "../raytracer/includes/pointlight.hpp"
#include "../raytracer/includes/camera.hpp"

namespace RT {
	class SceneInstance{
		public:
			SceneInstance();
			~SceneInstance();
		private:
				std::vector<std::shared_ptr<RT::ObjectBase>> m_objectList;
				std::vector<std::shared_ptr<RT::LightBase>> m_lightList;
				RT::Camera m_camera;
		public:
				void addObject(std::shared_ptr<RT::ObjectBase> object);
				void addLight(std::shared_ptr<RT::LightBase> light);
				void setCamera(RT::Camera camera);
				std::vector<std::shared_ptr<RT::ObjectBase>> getobjects(void);
				std::vector<std::shared_ptr<RT::LightBase>> getLIghts(void);
				RT::Camera getCamera(void);
	};
}
#endif
