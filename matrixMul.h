#ifndef MATRIXMUL_H
#define MATRIXMUL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct matrix_tag {
    double **values;
    size_t rows;
    size_t columns;
};
typedef struct matrix_tag matrix_t;
#endif
