#include "tests.h"

START_TEST(matrix_inverse_tcase_1) {
	matrix_t *m = matrix_calloc(2, 2);

	double values[2][2] = {{4, 7}, {2, 6}};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	matrix_t *inv = matrix_inverse(m);
	ck_assert_ptr_nonnull(inv);

	double expected[2][2] = {{0.6, -0.7}, {-0.2, 0.4}};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			double val = 0;
			matrix_get_el(inv, i, j, &val);
			ck_assert_double_eq_tol(val, expected[i][j], 1e-7);
		}
	}

	matrix_t *product = matrix_mult(m, inv);
	ck_assert_ptr_nonnull(product);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			double val = 0;
			matrix_get_el(product, i, j, &val);
			if (i == j) {
				ck_assert_double_eq_tol(val, 1.0, 1e-7);
			} else {
				ck_assert_double_eq_tol(val, 0.0, 1e-7);
			}
		}
	}

	matrix_free(m);
	matrix_free(inv);
	matrix_free(product);
}
END_TEST

START_TEST(matrix_inverse_tcase_2) {
	matrix_t *m = matrix_calloc(3, 3);

	double values[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	matrix_t *inv = matrix_inverse(m);
	ck_assert_ptr_nonnull(inv);

	matrix_t *product = matrix_mult(m, inv);
	ck_assert_ptr_nonnull(product);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			double val = 0;
			matrix_get_el(product, i, j, &val);
			if (i == j) {
				ck_assert_double_eq_tol(val, 1.0, 1e-7);
			} else {
				ck_assert_double_eq_tol(val, 0.0, 1e-7);
			}
		}
	}

	matrix_free(m);
	matrix_free(inv);
	matrix_free(product);
}
END_TEST

START_TEST(matrix_inverse_tcase_3) {
	matrix_t *m = matrix_calloc(1, 1);
	matrix_set_el(m, 5.0, 0, 0);

	matrix_t *inv = matrix_inverse(m);
	ck_assert_ptr_nonnull(inv);

	double val = 0;
	matrix_get_el(inv, 0, 0, &val);
	ck_assert_double_eq_tol(val, 0.2, 1e-7);

	matrix_free(m);
	matrix_free(inv);
}
END_TEST

START_TEST(matrix_inverse_tcase_4) {
	matrix_t *m = matrix_calloc(2, 2);

	double values[2][2] = {{1, 2}, {2, 4}};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	matrix_t *inv = matrix_inverse(m);
	ck_assert_ptr_null(inv);

	matrix_free(m);
}
END_TEST

START_TEST(matrix_inverse_tcase_5) {
	matrix_t *m = matrix_calloc(2, 3);

	matrix_t *inv = matrix_inverse(m);
	ck_assert_ptr_null(inv);

	matrix_free(m);
}
END_TEST

START_TEST(matrix_inverse_tcase_6) {
	matrix_t *inv = matrix_inverse(NULL);
	ck_assert_ptr_null(inv);
}
END_TEST

START_TEST(matrix_inverse_tcase_7) {
	matrix_t *m = matrix_calloc(3, 3);

	double values[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	matrix_t *inv = matrix_inverse(m);
	ck_assert_ptr_nonnull(inv);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			double val = 0;
			matrix_get_el(inv, i, j, &val);
			if (i == j) {
				ck_assert_double_eq_tol(val, 1.0, 1e-7);
			} else {
				ck_assert_double_eq_tol(val, 0.0, 1e-7);
			}
		}
	}

	matrix_free(m);
	matrix_free(inv);
}
END_TEST

START_TEST(matrix_inverse_tcase_8) {
	matrix_t *m = matrix_calloc(2, 2);

	double values[2][2] = {{0, 2}, {2, 0}};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	matrix_t *inv = matrix_inverse(m);
	ck_assert_ptr_nonnull(inv);

	double expected[2][2] = {{0, 0.5}, {0.5, 0}};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			double val = 0;
			matrix_get_el(inv, i, j, &val);
			ck_assert_double_eq_tol(val, expected[i][j], 1e-7);
		}
	}

	matrix_free(m);
	matrix_free(inv);
}
END_TEST

Suite *matrix_inverse_test_suite() {
	Suite *s = suite_create("matrix_inverse_tests");
	TCase *tc_core = tcase_create("Core matrix_inverse_tests");

	tcase_add_test(tc_core, matrix_inverse_tcase_1);
	tcase_add_test(tc_core, matrix_inverse_tcase_2);
	tcase_add_test(tc_core, matrix_inverse_tcase_3);
	tcase_add_test(tc_core, matrix_inverse_tcase_4);
	tcase_add_test(tc_core, matrix_inverse_tcase_5);
	tcase_add_test(tc_core, matrix_inverse_tcase_6);
	tcase_add_test(tc_core, matrix_inverse_tcase_7);
	tcase_add_test(tc_core, matrix_inverse_tcase_8);

	suite_add_tcase(s, tc_core);
	return s;
}