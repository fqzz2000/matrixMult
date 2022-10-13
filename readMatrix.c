#include "utils.h"
/*
 * take a stirng line, separate it by space and put values in the array 
 */
size_t processLine(char * line, double * array)  {
    char * token;
    char * placeHolder;
    size_t lineSize = strlen(line);
    char lineHeap[lineSize + 1];
    strncpy(lineHeap, line, lineSize);
    lineHeap[lineSize] = '\0';
    size_t idx = 0;
    token = strtok(lineHeap, " \n");
    while (token != NULL) {
        array[idx++] = strtod(token, &placeHolder);
        token = strtok(NULL, " \n");
    }
    return idx;
}
/*
 * read matrix information from a file stream
 */
matrix_t * readFileToMatrix(FILE * f) {
    matrix_t * mat = malloc(sizeof(*mat));
    mat->values = NULL;
    char * linePtr = NULL;
    size_t bufferSize = 0;
    ssize_t n = 0;
    size_t rows = 0;
    // read the number of rows and cols
    getline(&linePtr, &bufferSize, f);
    mat->columns = strtoul(linePtr, NULL, 10);
    free(linePtr);
    linePtr = NULL;
    getline(&linePtr, &bufferSize, f);
    mat->rows = strtoul(linePtr, NULL, 10);
    free(linePtr);
    linePtr = NULL;
    printf("%lu\n", mat->columns);
    printf("%lu\n", mat->columns);
    // read data into mat->values
    while ((n = getline(&linePtr, &bufferSize, f)) != EOF) {
        printf("%ld\n", n);
        if (mat->columns != n - 1) {
            fprintf(stderr, "inconsistant col numbers\n");
            exit(EXIT_FAILURE);
        }
        // allocate memory for each rows
        mat->values = (double **) realloc(mat->values, (rows + 1) * sizeof(*mat->values));
        mat->values[rows] = (double *) malloc(mat->columns * sizeof(*(mat->values[rows])));
        // put numbers into the corresponding rows
        processLine(linePtr, mat->values[rows]);
        free(linePtr);
        linePtr = NULL;
        rows++;
    }
    free(linePtr);
    return mat;
}
/*
 * read matrix from a given file name
 */
matrix_t * readMatrix(const char * filename) {
    FILE * matrixFile = fopen(filename, "r");
    if (matrixFile == NULL) {
        fprintf(stderr, "cannot open the file\n");
        exit(EXIT_FAILURE);
    }
    matrix_t * mat = readFileToMatrix(matrixFile);
    fclose(matrixFile);
    return mat;
}
/*
 * free the memory allocated by matrix_t
 */
void freeMatrix(matrix_t * mat) {
    for (size_t i = 0; i < mat->rows; i++) {
        free(mat->values[i]);
    }
    free(mat->values);
    free(mat);
}
int main(void) {
    matrix_t * mat = readMatrix("input1.txt");
    printMatrix(mat);
    freeMatrix(mat);
}
