#include "tests.h"

START_TEST(matrix_accessors_tcase_1) {
	const int rows = 3, cols = 3;
	matrix_t *matrix = matrix_calloc(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix_set_el(matrix, (rows * i + j), i, j);
		}
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			ck_assert_double_eq(matrix_get_el(matrix, i, j), (rows * i + j));
		}
	}

	matrix_free(matrix);
}
END_TEST

START_TEST(matrix_accessors_tcase_2) {
	const int rows = 3, cols = 3;
	matrix_t *matrix = matrix_calloc(rows, cols);

	int received_rows = matrix_get_rows(matrix);
	int received_cols = matrix_get_cols(matrix);

	ck_assert_int_eq(received_rows, rows);
	ck_assert_int_eq(received_cols, cols);

	matrix_free(matrix);
}
END_TEST

Suite *matrix_accessors_test_suite() {
	Suite *s = suite_create("matrix_accessors_tests");
	TCase *tc_core = tcase_create("Core matrix_accessors_tests");

	tcase_add_test(tc_core, matrix_accessors_tcase_1);
	tcase_add_test(tc_core, matrix_accessors_tcase_2);

	suite_add_tcase(s, tc_core);

	return s;
}