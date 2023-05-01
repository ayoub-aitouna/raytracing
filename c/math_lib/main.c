#include "vectormath.h"
#include <stdio.h>
#include "matrex.h"

void printv(vector_t vector)
{
	printf("{.x %f, .y %f, .z %f}\n",vector.x, vector.y, vector.z);
}

int main(int ac, char **av)
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

	if(ac != 5)
		return (1);

	matrex_t *mt1= creat_matrex(atoi(av[1]), atoi(av[2]));
	matrex_t *mt2= creat_matrex(atoi(av[3]), atoi(av[4]));
	double values1[] = {1,0,0,0,1,0,0,0,1};  // values to fill the matrix
	double values2[] = {2,7,-1,1,5,-4};  // values to fill the matrix
	fill_mt(mt1, values1);
	fill_mt(mt2, values2);
	print_matrex(mt1);
	print_matrex(mt2);
	matrex_t *result = mt_multiplication(mt1, mt2);
	print_matrex(result);
}
