#include "vectormath.h"
#include <stdio.h>

void printv(vector_t vector)
{
	printf("{.x %f, .y %f, .z %f}\n",vector.x, vector.y, vector.z);
}

int main()
{
	vector_t * v = vector(1, 2, 3);
	vector_t * u = vector(3, 2, 3);
	printf("lenght = %f\n", vector_lenght(*v));
	printv(*v);
	printv(*u);
	//printv(*copy_vector(*v));
//	printv(*normalized(v));
	printf("v.u = %f \n",dot(*v,*u));
	printv(*cross(*v, *u));
}
