#include "tests.h"

START_TEST(matrix_transpose_tcase_1) {
	matrix_t *m = matrix_calloc(2, 3);

	double values[2][3] = {{1, 2, 3}, {4, 5, 6}};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	matrix_t *result = matrix_transpose(m);
	ck_assert_ptr_nonnull(result);

	int rows = matrix_get_rows(result);
	int cols = matrix_get_cols(result);
	ck_assert_int_eq(rows, 3);
	ck_assert_int_eq(cols, 2);

	double expected[3][2] = {{1, 4}, {2, 5}, {3, 6}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			ck_assert_double_eq_tol(matrix_get_el(result, i, j), expected[i][j], 1e-7);
		}
	}

	matrix_free(m);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_transpose_tcase_2) {
	matrix_t *m = matrix_calloc(1, 4);

	matrix_set_el(m, 1.5, 0, 0);
	matrix_set_el(m, -2.0, 0, 1);
	matrix_set_el(m, 3.5, 0, 2);
	matrix_set_el(m, 0.0, 0, 3);

	matrix_t *result = matrix_transpose(m);
	ck_assert_ptr_nonnull(result);

	int rows = matrix_get_rows(result);
	int cols = matrix_get_cols(result);
	ck_assert_int_eq(rows, 4);
	ck_assert_int_eq(cols, 1);

	double expected[4][1] = {{1.5}, {-2.0}, {3.5}, {0.0}};

	for (int i = 0; i < 4; i++) {
		ck_assert_double_eq_tol(matrix_get_el(result, i, 0), expected[i][0], 1e-7);
	}

	matrix_free(m);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_transpose_tcase_3) {
	matrix_t *m = matrix_calloc(3, 3);

	double val = 1.0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m, val, i, j);
			val += 1.0;
		}
	}

	matrix_t *result = matrix_transpose(m);
	ck_assert_ptr_nonnull(result);

	double expected[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ck_assert_double_eq_tol(matrix_get_el(result, i, j), expected[i][j], 1e-7);
		}
	}

	matrix_free(m);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_transpose_tcase_4) {
	matrix_t *result = matrix_transpose(NULL);
	ck_assert_ptr_null(result);
}
END_TEST

START_TEST(matrix_transpose_tcase_5) {
	matrix_t *m = matrix_calloc(2, 2);

	matrix_set_el(m, 1.0, 0, 0);
	matrix_set_el(m, 1.0, 0, 1);
	matrix_set_el(m, 1.0, 1, 0);
	matrix_set_el(m, 1.0, 1, 1);

	matrix_t *transposed = matrix_transpose(m);
	ck_assert_ptr_nonnull(transposed);

	ck_assert_int_eq(matrix_eq(m, transposed), 1);

	matrix_free(m);
	matrix_free(transposed);
}
END_TEST

Suite *matrix_transpose_test_suite() {
	Suite *s = suite_create("matrix_transpose_tests");
	TCase *tc_core = tcase_create("Core matrix_transpose_tests");

	tcase_add_test(tc_core, matrix_transpose_tcase_1);
	tcase_add_test(tc_core, matrix_transpose_tcase_2);
	tcase_add_test(tc_core, matrix_transpose_tcase_3);
	tcase_add_test(tc_core, matrix_transpose_tcase_4);
	tcase_add_test(tc_core, matrix_transpose_tcase_5);

	suite_add_tcase(s, tc_core);
	return s;
}