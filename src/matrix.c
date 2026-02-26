#include "matrix_private.h"

matrix_t *matrix_calloc(int rows, int cols) {
	if (rows < 1 || cols < 1) {
		return NULL;
	}

	matrix_t *result = (matrix_t *)malloc(sizeof(matrix_t));

	if (result == NULL) {
		return NULL;
	}

	result->array = (double *)calloc(rows * cols, sizeof(double));

	if (result->array == NULL) {
		free(result);
		return NULL;
	}

	result->rows = rows;
	result->cols = cols;

	return result;
}

matrix_t *matrix_realloc(matrix_t *M, int rows, int cols) {
	if (_matrix_is_ptr_null(M) || rows < 1 || cols < 1) {
		return NULL;
	}

	matrix_t *result = matrix_calloc(rows, cols);
	if (result == NULL) {
		return NULL;
	}

	if (rows == M->rows && cols == M->cols) {
		result->array = M->array;
		M->array = NULL;
		matrix_free(M);
		return result;
	}

	int min_rows = (M->rows < rows) ? M->rows : rows;
	int min_cols = (M->cols < cols) ? M->cols : cols;

	for (int i = 0; i < min_rows; i++) {
		for (int j = 0; j < min_cols; j++) {
			matrix_set_el(result, matrix_get_el(M, i, j), i, j);
		}
	}

	matrix_free(M);
	return result;
}

void matrix_free(matrix_t *M) {
	if (_matrix_is_ptr_null(M)) {
		return;
	}
	free(M->array);
	M->array = NULL;
	free(M);
}

// ------------------

void matrix_set_el(matrix_t *M, double val, int i, int j) {
	M->array[M->cols * i + j] = val;
}

double matrix_get_el(matrix_t *M, int i, int j) {
	return M->array[M->cols * i + j];
}

int matrix_get_rows(matrix_t *M) {
	return M->rows;
}

int matrix_get_cols(matrix_t *M) {
	return M->cols;
}

double **matrix_get_array(matrix_t *M) {
	if (_matrix_is_ptr_null(M)) {
		return NULL;
	}

	double **result = (double **)calloc(M->rows, sizeof(double *));
	if (result == NULL) {
		return NULL;
	}

	for (int i = 0; i < M->rows; i++) {
		result[i] = (double *)calloc(M->cols, sizeof(double));
		if (result[i] == NULL) {
			return NULL;
		}

		for (int j = 0; j < M->cols; j++) {
			result[i][j] = matrix_get_el(M, i, j);
		}
	}

	return result;
}

// ------------------

int matrix_eq(matrix_t *A, matrix_t *B) {
	if (_matrix_is_ptr_null(A) || _matrix_is_ptr_null(B) || !_matrix_are_sizes_equal(A, B)) {
		return false;
	}

	for (int i = 0; i < (A->rows * A->cols); i++) {
		if (fabs(A->array[i] - B->array[i]) >= 1e-7) {
			return false;
		}
	}

	return true;
}

matrix_t *matrix_sum(matrix_t *A, matrix_t *B) {
	if (_matrix_is_ptr_null(A) || _matrix_is_ptr_null(B) || !_matrix_are_sizes_equal(A, B)) {
		return NULL;
	}

	matrix_t *result = matrix_calloc(A->rows, A->cols);
	if (result == NULL) {
		return NULL;
	}

	for (int i = 0; i < (A->rows * A->cols); i++) {
		result->array[i] = A->array[i] + B->array[i];
	}

	return result;
}

matrix_t *matrix_sub(matrix_t *A, matrix_t *B) {
	if (_matrix_is_ptr_null(A) || _matrix_is_ptr_null(B) || !_matrix_are_sizes_equal(A, B)) {
		return NULL;
	}

	matrix_t *result = matrix_calloc(A->rows, A->cols);
	if (result == NULL) {
		return NULL;
	}

	for (int i = 0; i < A->rows * A->cols; i++) {
		result->array[i] = A->array[i] - B->array[i];
	}

	return result;
}

matrix_t *matrix_mult(matrix_t *A, matrix_t *B) {
	if (_matrix_is_ptr_null(A) || _matrix_is_ptr_null(B) || A->cols != B->rows) {
		return NULL;
	}

	matrix_t *result = matrix_calloc(A->rows, B->cols);
	if (result == NULL) {
		return NULL;
	}

	for (int i = 0; i < A->rows; i++) {
		for (int j = 0; j < B->cols; j++) {
			double sum = 0.0;
			for (int k = 0; k < A->cols; k++) {
				sum += A->array[i * A->cols + k] * B->array[k * B->cols + j];
			}
			matrix_set_el(result, sum, i, j);
		}
	}

	return result;
}

matrix_t *matrix_mult_number(matrix_t *A, double number) {
	if (_matrix_is_ptr_null(A)) {
		return NULL;
	}

	matrix_t *result = matrix_calloc(A->rows, A->cols);
	if (result == NULL) {
		return NULL;
	}

	for (int i = 0; i < A->rows * A->cols; i++) {
		result->array[i] = A->array[i] * number;
	}

	return result;
}

matrix_t *matrix_transpose(matrix_t *A) {
	if (_matrix_is_ptr_null(A)) {
		return NULL;
	}

	matrix_t *result = matrix_calloc(A->cols, A->rows);
	if (result == NULL) {
		return NULL;
	}

	for (int i = 0; i < A->rows; i++) {
		for (int j = 0; j < A->cols; j++) {
			matrix_set_el(result, matrix_get_el(A, i, j), j, i);
		}
	}

	return result;
}

matrix_t *matrix_calc_complements(matrix_t *A) {
	if (_matrix_is_ptr_null(A) || !_matrix_is_square(A)) {
		return NULL;
	}

	matrix_t *result = matrix_calloc(A->rows, A->cols);
	if (result == NULL) {
		return NULL;
	}

	for (int i = 0; i < A->rows; i++) {
		for (int j = 0; j < A->cols; j++) {
			if (A->rows == 1) {
				matrix_set_el(result, 1.0, i, j);
				continue;
			}

			matrix_t *sub = _matrix_get_submatrix(A, i, j);
			if (sub == NULL) {
				matrix_free(result);
				return NULL;
			}

			double det = 0;
			int status = matrix_determinant(sub, &det);
			matrix_free(sub);

			if (status == EXIT_FAILURE) {
				matrix_free(result);
				return NULL;
			}

			double complement = det * pow(-1, i + j);
			matrix_set_el(result, complement, i, j);
		}
	}

	return result;
}

int matrix_determinant(matrix_t *A, double *result) {
	if (_matrix_is_ptr_null(A) || !_matrix_is_square(A) || result == NULL) {
		return EXIT_FAILURE;
	}

	int n = A->rows;

	if (n == 1) {
		*result = A->array[0];
		return EXIT_SUCCESS;
	}

	if (n == 2) {
		*result = A->array[0] * A->array[3] - A->array[1] * A->array[2];
		return EXIT_SUCCESS;
	}

	double det = 0.0;

	for (int k = 0; k < n; k++) {
		matrix_t *minor = matrix_calloc(n - 1, n - 1);
		if (minor == NULL) {
			return EXIT_FAILURE;
		}

		int minor_i = 0;
		for (int i = 1; i < n; i++) {
			int minor_j = 0;
			for (int j = 0; j < n; j++) {
				if (j == k) {
					continue;
				}

				matrix_set_el(minor, matrix_get_el(A, i, j), minor_i, minor_j);
				minor_j++;
			}
			minor_i++;
		}

		double minor_det = 0;
		int status = matrix_determinant(minor, &minor_det);
		matrix_free(minor);

		if (status == EXIT_FAILURE) {
			return EXIT_FAILURE;
		}

		det += (k % 2 == 0 ? 1 : -1) * matrix_get_el(A, 0, k) * minor_det;
	}

	*result = det;
	return EXIT_SUCCESS;
}

matrix_t *matrix_inverse(matrix_t *A) {
	if (_matrix_is_ptr_null(A) || !_matrix_is_square(A)) {
		return NULL;
	}

	double det = 0;
	int status = matrix_determinant(A, &det);
	if (status == EXIT_FAILURE || fabs(det) < 1e-12) {
		return NULL;
	}

	if (A->rows == 1) {
		matrix_t *result = matrix_calloc(1, 1);
		if (result == NULL) {
			return NULL;
		}
		matrix_set_el(result, 1.0 / det, 0, 0);
		return result;
	}

	matrix_t *complements = matrix_calc_complements(A);
	if (complements == NULL) {
		return NULL;
	}

	matrix_t *transposed = matrix_transpose(complements);
	matrix_free(complements);

	if (transposed == NULL) {
		return NULL;
	}

	matrix_t *result = matrix_mult_number(transposed, 1.0 / det);
	matrix_free(transposed);

	return result;
}

bool _matrix_are_coordinates_correct(matrix_t *M, int i, int j) {
	if ((i >= 0 && i < M->rows) && (j >= 0 && j < M->cols)) {
		return true;
	}
	return false;
}

bool _matrix_is_ptr_null(matrix_t *M) {
	if (M == NULL) {
		return true;
	}
	return false;
}

bool _matrix_are_sizes_equal(matrix_t *A, matrix_t *B) {
	if (A->rows == B->rows && A->cols == B->cols) {
		return true;
	}
	return false;
}

bool _matrix_is_square(matrix_t *M) {
	if (M->rows == M->cols) {
		return true;
	}
	return false;
}

matrix_t *_matrix_get_submatrix(matrix_t *M, int del_row, int del_col) {
	if (_matrix_is_ptr_null(M) || M->rows < 2 || M->cols < 2) {
		return NULL;
	}

	if (!_matrix_are_coordinates_correct(M, del_row, del_col)) {
		return NULL;
	}

	matrix_t *result = matrix_calloc(M->rows - 1, M->cols - 1);
	if (result == NULL) {
		return NULL;
	}

	int res_i = 0;
	for (int i = 0; i < M->rows; i++) {
		if (i == del_row) {
			continue;
		}

		int res_j = 0;
		for (int j = 0; j < M->cols; j++) {
			if (j == del_col) {
				continue;
			}

			matrix_set_el(result, matrix_get_el(M, i, j), res_i, res_j);
			res_j++;
		}
		res_i++;
	}

	return result;
}
