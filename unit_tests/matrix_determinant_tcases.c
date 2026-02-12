#include "tests.h"

START_TEST(matrix_determinant_tcase_1) {
	matrix_t *m = matrix_calloc(2, 2);

	double values[2][2] = {{3, 4}, {2, 1}};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	double det = 0;
	int status = matrix_determinant(m, &det);
	ck_assert_int_eq(status, EXIT_SUCCESS);
	ck_assert_double_eq_tol(det, -5.0, 1e-7);

	matrix_free(m);
}
END_TEST

START_TEST(matrix_determinant_tcase_2) {
	matrix_t *m = matrix_calloc(3, 3);

	double values[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	double det = 0;
	int status = matrix_determinant(m, &det);
	ck_assert_int_eq(status, EXIT_SUCCESS);
	ck_assert_double_eq_tol(det, 0.0, 1e-7);

	matrix_free(m);
}
END_TEST

START_TEST(matrix_determinant_tcase_3) {
	matrix_t *m = matrix_calloc(1, 1);
	matrix_set_el(m, 7.5, 0, 0);

	double det = 0;
	int status = matrix_determinant(m, &det);
	ck_assert_int_eq(status, EXIT_SUCCESS);
	ck_assert_double_eq_tol(det, 7.5, 1e-7);

	matrix_free(m);
}
END_TEST

START_TEST(matrix_determinant_tcase_4) {
	matrix_t *m = matrix_calloc(3, 3);

	double values[3][3] = {{2, 4, 1}, {0, 3, 5}, {1, -2, 2}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	double det = 0;
	int status = matrix_determinant(m, &det);
	ck_assert_int_eq(status, EXIT_SUCCESS);
	ck_assert_double_eq_tol(det, 49.0, 1e-7);

	matrix_free(m);
}
END_TEST

START_TEST(matrix_determinant_tcase_5) {
	matrix_t *m = matrix_calloc(2, 3);

	double det = 0;
	int status = matrix_determinant(m, &det);
	ck_assert_int_eq(status, EXIT_FAILURE);

	matrix_free(m);
}
END_TEST

START_TEST(matrix_determinant_tcase_6) {
	double det = 0;
	int status = matrix_determinant(NULL, &det);
	ck_assert_int_eq(status, EXIT_FAILURE);
}
END_TEST

START_TEST(matrix_determinant_tcase_7) {
	matrix_t *m = matrix_calloc(3, 3);

	double values[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	double det = 0;
	int status = matrix_determinant(m, &det);
	ck_assert_int_eq(status, EXIT_SUCCESS);
	ck_assert_double_eq_tol(det, 1.0, 1e-7);

	matrix_free(m);
}
END_TEST

Suite *matrix_determinant_test_suite() {
	Suite *s = suite_create("matrix_determinant_tests");
	TCase *tc_core = tcase_create("Core matrix_determinant_tests");

	tcase_add_test(tc_core, matrix_determinant_tcase_1);
	tcase_add_test(tc_core, matrix_determinant_tcase_2);
	tcase_add_test(tc_core, matrix_determinant_tcase_3);
	tcase_add_test(tc_core, matrix_determinant_tcase_4);
	tcase_add_test(tc_core, matrix_determinant_tcase_5);
	tcase_add_test(tc_core, matrix_determinant_tcase_6);
	tcase_add_test(tc_core, matrix_determinant_tcase_7);

	suite_add_tcase(s, tc_core);
	return s;
}