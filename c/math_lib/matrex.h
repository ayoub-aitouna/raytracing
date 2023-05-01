#ifndef MATREX_H
#define MATREX_H

# include<stdlib.h>
# include<unistd.h>
# include<math.h>
# include "types.h"

matrex_t	*creat_matrex(int r, int c);
matrex_t	*mt_multiplication(matrex_t *mt1, matrex_t * mt2);
void fill_mt(matrex_t *mt, double* values);
void print_matrex(matrex_t *matrex);
#endif
