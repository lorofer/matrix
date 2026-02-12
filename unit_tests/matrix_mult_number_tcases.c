#include "tests.h"

START_TEST(matrix_mult_number_tcase_1) {
	matrix_t *m = matrix_calloc(3, 3);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m, 2.0, i, j);
		}
	}

	matrix_t *result = matrix_mult_number(m, 3.0);
	ck_assert_ptr_nonnull(result);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			double val = 0;
			matrix_get_el(result, i, j, &val);
			ck_assert_double_eq_tol(val, 6.0, 1e-7);
		}
	}

	matrix_free(m);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_mult_number_tcase_2) {
	matrix_t *m = matrix_calloc(2, 4);

	double values[2][4] = {{1.5, -2.0, 3.5, 0.0}, {4.0, -1.5, 2.0, 5.5}};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	matrix_t *result = matrix_mult_number(m, -2.0);
	ck_assert_ptr_nonnull(result);

	double expected[2][4] = {{-3.0, 4.0, -7.0, 0.0}, {-8.0, 3.0, -4.0, -11.0}};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			double val = 0;
			matrix_get_el(result, i, j, &val);
			ck_assert_double_eq_tol(val, expected[i][j], 1e-7);
		}
	}

	matrix_free(m);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_mult_number_tcase_3) {
	matrix_t *m = matrix_calloc(1, 1);

	matrix_set_el(m, 7.5, 0, 0);

	matrix_t *result = matrix_mult_number(m, 0.0);
	ck_assert_ptr_nonnull(result);

	double val = 0;
	matrix_get_el(result, 0, 0, &val);
	ck_assert_double_eq_tol(val, 0.0, 1e-7);

	matrix_free(m);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_mult_number_tcase_4) {
	matrix_t *m = matrix_calloc(3, 2);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			matrix_set_el(m, 1.0000001, i, j);
		}
	}

	matrix_t *result = matrix_mult_number(m, 2.0);
	ck_assert_ptr_nonnull(result);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			double val = 0;
			matrix_get_el(result, i, j, &val);
			ck_assert_double_eq_tol(val, 2.0000002, 1e-7);
		}
	}

	matrix_free(m);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_mult_number_tcase_5) {
	matrix_t *result = matrix_mult_number(NULL, 5.0);
	ck_assert_ptr_null(result);
}
END_TEST

START_TEST(matrix_mult_number_tcase_6) {
	matrix_t *m = matrix_calloc(2, 2);

	matrix_set_el(m, 1.0, 0, 0);
	matrix_set_el(m, 2.0, 0, 1);
	matrix_set_el(m, 3.0, 1, 0);
	matrix_set_el(m, 4.0, 1, 1);

	matrix_t *result = matrix_mult_number(m, 1.0);
	ck_assert_ptr_nonnull(result);

	double val = 0;
	matrix_get_el(result, 0, 0, &val);
	ck_assert_double_eq_tol(val, 1.0, 1e-7);

	matrix_get_el(result, 1, 1, &val);
	ck_assert_double_eq_tol(val, 4.0, 1e-7);

	matrix_free(m);
	matrix_free(result);
}
END_TEST

Suite *matrix_mult_number_test_suite() {
	Suite *s = suite_create("matrix_mult_number_tests");
	TCase *tc_core = tcase_create("Core matrix_mult_number_tests");

	tcase_add_test(tc_core, matrix_mult_number_tcase_1);
	tcase_add_test(tc_core, matrix_mult_number_tcase_2);
	tcase_add_test(tc_core, matrix_mult_number_tcase_3);
	tcase_add_test(tc_core, matrix_mult_number_tcase_4);
	tcase_add_test(tc_core, matrix_mult_number_tcase_5);
	tcase_add_test(tc_core, matrix_mult_number_tcase_6);

	suite_add_tcase(s, tc_core);
	return s;
}