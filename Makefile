CFLAGS=-std=gnu99 -pedantic -Werror -Wall

testMatrix: utils.h matrixMul.c readMatrix.c
	gcc $(CFLAGS) -o testMatrix readMatrix.c matrixMul.h utils.h -ggdb3
