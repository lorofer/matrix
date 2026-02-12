#include "tests.h"

START_TEST(matrix_accessors_tcase_1) {
	const int rows = 3, cols = 3;
	matrix_t *matrix = matrix_calloc(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int status = matrix_set_el(matrix, (rows * i + j), i, j);
			ck_assert_int_eq(status, 0);
		}
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double val = -1;
			int status = matrix_get_el(matrix, i, j, &val);
			ck_assert_int_eq(status, 0);
			ck_assert_double_eq(val, (rows * i + j));
		}
	}

	matrix_free(matrix);
}
END_TEST

START_TEST(matrix_accessors_tcase_2) {
	const int rows = 3, cols = 3;
	matrix_t *matrix = matrix_calloc(rows, cols);

	int status = matrix_set_el(matrix, 777, rows, cols);
	ck_assert_int_eq(status, 1);

	matrix_free(matrix);
}
END_TEST

START_TEST(matrix_accessors_tcase_3) {
	const int rows = 3, cols = 3;
	matrix_t *matrix = matrix_calloc(rows, cols);

	double val = -1;
	int status = matrix_get_el(matrix, rows, cols, &val);
	ck_assert_int_eq(status, 1);

	matrix_free(matrix);
}
END_TEST

START_TEST(matrix_accessors_tcase_4) {
	matrix_t *matrix = matrix_calloc(3, 3);

	int status = matrix_get_el(matrix, 0, 0, NULL);
	ck_assert_int_eq(status, 1);

	matrix_free(matrix);
}
END_TEST

START_TEST(matrix_accessors_tcase_5) {
	double val = -1;
	int status = matrix_get_el(NULL, 0, 0, &val);
	ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(matrix_accessors_tcase_6) {
	matrix_t *matrix = matrix_calloc(3, 3);

	int status = matrix_set_el(matrix, 777, -1, -1);
	ck_assert_int_eq(status, 1);

	matrix_free(matrix);
}
END_TEST

START_TEST(matrix_accessors_tcase_7) {
	matrix_t *matrix = matrix_calloc(3, 3);

	double val = -1;
	int status = matrix_get_el(matrix, -1, -1, &val);
	ck_assert_int_eq(status, 1);

	matrix_free(matrix);
}
END_TEST

START_TEST(matrix_accessors_tcase_8) {
	const int rows = 3, cols = 3;
	matrix_t *matrix = matrix_calloc(rows, cols);

	int received_rows;
	int received_cols;
	int rows_status = matrix_get_rows(matrix, &received_rows);
	int cols_status = matrix_get_cols(matrix, &received_cols);

	ck_assert_int_eq(rows_status, 0);
	ck_assert_int_eq(cols_status, 0);
	ck_assert_int_eq(received_rows, rows);
	ck_assert_int_eq(received_cols, cols);

	matrix_free(matrix);
}
END_TEST

START_TEST(matrix_accessors_tcase_9) {
	int received_rows;
	int received_cols;
	int rows_status = matrix_get_rows(NULL, &received_rows);
	int cols_status = matrix_get_cols(NULL, &received_cols);

	ck_assert_int_eq(rows_status, 1);
	ck_assert_int_eq(cols_status, 1);
}
END_TEST

START_TEST(matrix_accessors_tcase_10) {
	const int rows = 3, cols = 3;
	matrix_t *matrix = matrix_calloc(rows, cols);

	int rows_status = matrix_get_rows(matrix, NULL);
	int cols_status = matrix_get_cols(matrix, NULL);

	ck_assert_int_eq(rows_status, 1);
	ck_assert_int_eq(cols_status, 1);

	matrix_free(matrix);
}
END_TEST

Suite *matrix_accessors_test_suite() {
	Suite *s = suite_create("matrix_accessors_tests");
	TCase *tc_core = tcase_create("Core matrix_accessors_tests");

	tcase_add_test(tc_core, matrix_accessors_tcase_1);
	tcase_add_test(tc_core, matrix_accessors_tcase_2);
	tcase_add_test(tc_core, matrix_accessors_tcase_3);
	tcase_add_test(tc_core, matrix_accessors_tcase_4);
	tcase_add_test(tc_core, matrix_accessors_tcase_5);
	tcase_add_test(tc_core, matrix_accessors_tcase_6);
	tcase_add_test(tc_core, matrix_accessors_tcase_7);
	tcase_add_test(tc_core, matrix_accessors_tcase_8);
	tcase_add_test(tc_core, matrix_accessors_tcase_9);
	tcase_add_test(tc_core, matrix_accessors_tcase_10);

	suite_add_tcase(s, tc_core);

	return s;
}