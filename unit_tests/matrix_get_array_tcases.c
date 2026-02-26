#include "tests.h"

void free_double_array(double **arr, int r, int c) {
	for (int i = 0; i < r; i++) {
		free(arr[i]);
	}
	free(arr);
}

START_TEST(matrix_get_array_tcase_1) {
	const int rows = 3, cols = 3;
	matrix_t *matrix = matrix_calloc(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix_set_el(matrix, (rows * i + j), i, j);
		}
	}

	double **array = matrix_get_array(matrix);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			ck_assert_double_eq(matrix_get_el(matrix, i, j), array[i][j]);
		}
	}

	matrix_free(matrix);
	free_double_array(array, 3, 3);
}
END_TEST

START_TEST(matrix_get_array_tcase_2) {
	double **array = matrix_get_array(NULL);
	ck_assert_ptr_null(array);
}
END_TEST

Suite *matrix_get_array_test_suite() {
	Suite *s = suite_create("matrix_get_array_tests");
	TCase *tc_core = tcase_create("Core matrix_get_array_tests");

	tcase_add_test(tc_core, matrix_get_array_tcase_1);
	tcase_add_test(tc_core, matrix_get_array_tcase_2);

	suite_add_tcase(s, tc_core);

	return s;
}