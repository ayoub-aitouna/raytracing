#ifndef PARSER_H
#define PARSER_H

#include "scene_instance.hpp"
#include "parse.h"
namespace RT
{
	class parcer{
		public:
			RT::SceneInstance parsemap(char **map);
	};
}

#endif
