#ifndef RAY_H
#define RAY_H

#include "../math_lib/vectormath.h"

typedef struct ray{
	point_t origin;
	vector_t direction;
	float max;
} ray_t ;

ray_t *copy_ray(const ray_t *ray);
ray_t *ray(point_t origin, vector_t direction, float max);
point_t *calculat(ray_t ray, float t);

#endif
