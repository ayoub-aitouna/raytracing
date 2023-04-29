#include "parcer.hpp"
#include "parse.h"
#include <cstring>
#include <memory>
#include <tuple>
#include <vector>
#include "../raytracer/Materials/headers/SimpleMaterial.hpp"

char *str_append(char *str, char c)
{
	int len = 0;
	int i = 0;
	if (str)
		len = strlen(str);
	char *new_str = (char *)malloc(sizeof(char) * (len + 2));

	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = 0;
	return (new_str);
}

post_t *getposition(char *line, int *index)
{
	post_t *position = (post_t *)malloc(sizeof(post_t));

	int i = 0;
	float positions[3];
	char *cur_pos = NULL;
	int p_i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
	{
		while (line[i] && line[i] != ' ' && line[i] != ',')
			cur_pos = str_append(cur_pos, line[i++]);
		positions[p_i++] = atof(cur_pos);
		if (line[i] == ',')
			i++;
		free(cur_pos);
		cur_pos = NULL;
	}
	position->x = positions[0];
	position->y = positions[1];
	position->z = positions[2];
	*index += (i);
	return (position);
}

char *get_type(char *line, int *index)
{
	char *name = NULL;
	int i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
	{
		name = str_append(name, line[i]);
		i++;
	}
	*index += i;
	return (name);
}

RT::SceneInstance RT::parcer::parsemap(char **map)
{
	char *line = NULL;
	int i = 0;
	int o_index = 0;
	int l_index = 0;
	int fd = open("scene.rt", O_RDONLY);
	SceneInstance m_scene_instance;
	RT::Gtform tm;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		i = 0;
		char *name = get_type(line, &i);
		if (strcmp(name, "pl") == 0 || strcmp(name, "sp") == 0)
		{
			post_t *pos = getposition(line + i, &i);
			post_t *st = getposition(line + i, &i);
			post_t *color = getposition(line + i, &i);
			if (strcmp(name, "sp") == 0)
				m_scene_instance.addObject(std::make_shared<ObjSphere>(RT::ObjSphere()));
			if (strcmp(name, "pl") == 0)
				m_scene_instance.addObject(std::make_shared<ObjectPlan>(RT::ObjectPlan()));
			tm.SetTransform(qbVector<double>{std::vector<double>{pos->x, pos->y, pos->z}},
					qbVector<double>{std::vector<double>{.0, .0, .0}},
					qbVector<double>{std::vector<double>{st->x, st->y, st->z}});
			m_scene_instance.getobjects().at(o_index)->SetTransformMatrix(tm);
			m_scene_instance.getobjects().at(o_index)->m_baseColor = qbVector<double>{std::vector<double>{color->x, color->y, color->z}};
			o_index++;
		}
		else if (strcmp(name, "L") == 0)
		{
			post_t *pos = getposition(line + i, &i);
			post_t *color = getposition(line + i, &i);
			m_scene_instance.addLight(std::make_shared<PointLight>(RT::PointLight()));
			m_scene_instance.getLIghts().at(l_index)->m_location = qbVector<double>{std::vector<double>{pos->x, pos->y, pos->z}};
			m_scene_instance.getLIghts().at(l_index++)->m_color = qbVector<double>{std::vector<double>{color->x, color->y, color->z}};
		}
	}
	return (m_scene_instance);
}
