# include "multiply.h"
# include "readMatrix.h"
# include "utils.h"

int main(int argc, const char **argv) {
    //if we got wrong numbers of input files, exit the process
    if (argc != 3) {
        fprintf(stderr, "Usage: matrixMul inputMatrix1 inputMatrix2");
        exit(EXIT_FAILURE);
    }

    /*
    leftMatrix: read from the first inputfile.
    rightMatrix: read from the second inputfile.
    multiplyMatrix: the result of multiplication of two matrix above.
    */
    matrix_t *leftMatrix = readMatrix(argv[1]);
    matrix_t *rightMatrix = readMatrix(argv[2]);
    printMatrix(leftMatrix);
    
    printMatrix(rightMatrix);
    
    matrix_t *multiplyMatrix = multiply(leftMatrix, rightMatrix);
    
    //print out the matrix multilication result to standard output
    printMatrix (multiplyMatrix);

    //free all the memories allocated before
    freeMatrix(leftMatrix);
    freeMatrix(rightMatrix);
    freeMatrix(multiplyMatrix);
    
    return EXIT_SUCCESS;
}
