#include "utils.h"
#include<regex.h>

/*
 *  return if the input is valid for double format
 */
int isValidDouble(char * string) {
    regex_t regex;
    char * pattern = "^([0-9]+[.][0-9]+|[0-9]+)[\n]?$";
    regcomp(&regex, pattern, REG_EXTENDED);
    if (!regexec(&regex, string, 0, NULL, 0)) {
        regfree(&regex);
        return 1;
    }
    regfree(&regex);
    return 0;
}

/*
 * return if the input is valid for size_t
 *
 */
int isValidSize(char * string) {
    regex_t regex;
    char * pattern = "^[0-9]+[\n]?$";
    regcomp(&regex, pattern, REG_EXTENDED);
    if (!regexec(&regex, string, 0 , NULL, 0)) {
        regfree(&regex);
        return 1;
    }
    regfree(&regex);
    return 0; 
}

/*
 * take a stirng line, separate it by space and put values in the array 
 * read matrix information from a file stream
 */
matrix_t * readFileToMatrix(FILE * f) {
    matrix_t * mat = (matrix_t *) malloc(sizeof(*mat));
    mat->values = NULL;
    char * linePtr = NULL;
    size_t bufferSize = 0;
    ssize_t n = 0;
    size_t cols = 0;
    size_t rows = 0;
    // read the number of rows and cols
    getline(&linePtr, &bufferSize, f);
    if (!isValidSize(linePtr)) {
        fprintf(stderr, "in valid col number\n");
        exit(EXIT_FAILURE);
    }
    mat->columns = strtoul(linePtr, NULL, 10);
    free(linePtr);
    linePtr = NULL;
    getline(&linePtr, &bufferSize, f);
    if (!isValidDouble(linePtr)) {
        fprintf(stderr, "invalid row number\n");
        exit(EXIT_FAILURE);
    }
    mat->rows = strtoul(linePtr, NULL, 10);
    free(linePtr);
    linePtr = NULL;
    // read data into mat->values
    while ((getline(&linePtr, &bufferSize, f))!= EOF) {
        if (n >= mat->columns * mat->rows) {
            fprintf(stderr, "too many inputs\n");
            exit(EXIT_FAILURE);
        }
        // allocate memory for each rows
        if (cols % mat->columns == 0) {
            mat->values = (double **) realloc(mat->values, (rows + 1) * sizeof(*mat->values));
            mat->values[rows] = (double *) malloc(mat->columns * sizeof(*(mat->values[rows])));
            cols = 0;
            rows++;
        }
        if (!isValidDouble(linePtr)) {
            fprintf(stderr, "invalid input in line %ld\n", rows + 1);
            exit(EXIT_FAILURE);
        }
        mat->values[rows - 1][cols] =  strtod(linePtr, NULL);
        // put numbers into the corresponding rows
        free(linePtr);
        linePtr = NULL;
        cols++;
        n++;
    }
    if (n < mat->columns * mat->rows) {
        fprintf(stderr, "insufficient data\n");
        exit(EXIT_FAILURE);
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

