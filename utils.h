#include "matrixMul.h"

void printMatrix(matrix_t * matrix) {
    for(size_t row = 0; row < matrix->rows; row++){
        for(size_t col = 0; col < matrix->columns; col++){
            printf("%f ", matrix->values[row][col]);
        }
        printf("\n");
    }
}
