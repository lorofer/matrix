#ifndef MATRIX_PRIVATE_H
#define MATRIX_PRIVATE_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "matrix.h"

struct matrix_struct {
	double *array;
	int rows;
	int cols;
};

bool _matrix_is_ptr_null(matrix_t *M);
bool _matrix_are_coordinates_correct(matrix_t *M, int i, int j);
bool _matrix_are_sizes_equal(matrix_t *A, matrix_t *B);
bool _matrix_is_square(matrix_t *M);
matrix_t *_matrix_get_submatrix(matrix_t *M, int del_row, int del_col);

#endif