#include "matrixMul.h"
// this function use the right and left matrix to multply and save the result to the result
// result: a structure contains the result of the mnultiplications

matrix_t * multiply(matrix_t * left, matrix_t * right) {

// Malloc the space for result
    matrix_t *result = malloc(sizeof(*result)); 

    if(result == NULL) {
        perror("not enough space for result.\n");
        exit(EXIT_FAILURE);
    }

    result->values = malloc(left->rows * sizeof(*result->values));
    if(result->values == NULL) {
        perror("not enough space for values.\n");
        exit(EXIT_FAILURE);
    } 

    for(size_t i = 0; i < left->rows; i++) {     
        result->values[i] = malloc(right->columns * sizeof(*result->values[i]));
        if(result->values[i] == NULL) {
            perror("not enough space for **values.\n");
            exit(EXIT_FAILURE);
        }
    }

// Set the matrix size for result
    result->rows = left->rows;
    result->columns = right->columns;

// Initializing elements of matrix result to 0
    for (size_t i = 0; i < result->rows; ++i) { //i represent the row of the result
        for (size_t j = 0; j < result->columns; ++j) {  //j represent the co of the result
            result->values[i][j] = 0;
        }
    }

// Multiplying left and right matrices and storing it into result
    for (size_t i = 0; i < left->rows; ++i) { 
        for (size_t j = 0; j < right->columns; ++j) {
            for (size_t k = 0; k < left->columns; ++k) {    //this level of loop is to calculate the result[i][j]
                result->values[i][j] += left->values[i][k] * right->values[k][j];
            }
        }
    }

    return result;
}
