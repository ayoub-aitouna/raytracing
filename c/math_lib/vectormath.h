#ifndef MATH_H
#define MATH_H

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "types.h"

float		vector_lenght(vector_t v);
float		vector_lenght2(vector_t v);
vector_t	*normalized(vector_t *v);
float		normalize(vector_t *v);
vector_t	*vector(float x, float y, float z);
vector_t	*copy_vector(vector_t v);
vector_t	*equal(vector_t *target, vector_t *v); 
vector_t	*minus(vector_t *target, vector_t *v);
vector_t	*pluse(vector_t *target, vector_t *v);
vector_t	*multiplication(vector_t *target, vector_t *v);
vector_t	*num_multiplication(vector_t *target, float f);
vector_t	*division(vector_t *target, vector_t *v);
vector_t	*num_division(vector_t *target, float l);
float		dot(vector_t v, vector_t u);
vector_t	*cross(vector_t v, vector_t u);
#endif
