CFLAGS=-std=gnu99 -pedantic -Werror -Wall

MatrixMult: matrixMul.c matrixMul.h multiply.h readMatrix.h utils.h
	gcc $(CFLAGS) -o MatrixMul matrixMul.c matrixMul.h readMatrix.h multiply.h utils.h -ggdb3
