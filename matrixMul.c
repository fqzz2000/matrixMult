#include "matrixMul.h"

int main(int argc, const char **argv) {
    // determain whether valid input from cmd
    if (argc != 3) {
        fprintf(stderr, "Usage: matrixMul inputMatrix1 inputMatrix2");
        return EXIT_FAILURE;
    }
    //
    matrix_t *leftMatrix = readMatrix(argv[1]);
    matrix_t *rightMatrix = readMatrix(argv[2]);
    matrix_t *multiplyMatrix = multiply(leftMatrix, rightMatrix);
    
    //
    printMatrix (multiplyMatrix);

    //
    freeMatrix(leftMatrix);
    freeMatrix(rightMatrix);
    freeMatrix(multiplyMatrix);
    return EXIT_SUCCESS;
}