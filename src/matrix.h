#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix_struct matrix_t;

matrix_t *matrix_calloc(int rows, int cols);
matrix_t *matrix_realloc(matrix_t *M, int rows, int cols);
void matrix_free(matrix_t *M);

int matrix_set_el(matrix_t *M, double val, int i, int j);
int matrix_get_el(matrix_t *M, int i, int j, double *result);
int matrix_get_rows(matrix_t *M, int *result);
int matrix_get_cols(matrix_t *M, int *result);

int matrix_eq(matrix_t *A, matrix_t *B);
matrix_t *matrix_sum(matrix_t *A, matrix_t *B);
matrix_t *matrix_sub(matrix_t *A, matrix_t *B);
matrix_t *matrix_mult(matrix_t *A, matrix_t *B);
matrix_t *matrix_mult_number(matrix_t *A, double number);

matrix_t *matrix_transpose(matrix_t *A);
matrix_t *matrix_calc_complements(matrix_t *A);
int matrix_determinant(matrix_t *A, double *result);
matrix_t *matrix_inverse(matrix_t *A);

#endif