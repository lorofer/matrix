#include "tests.h"

START_TEST(matrix_mult_tcase_1) {
	matrix_t *m1 = matrix_calloc(2, 3);
	matrix_t *m2 = matrix_calloc(3, 2);

	double vals1[2][3] = {{1, 2, 3}, {4, 5, 6}};
	double vals2[3][2] = {{7, 8}, {9, 10}, {11, 12}};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m1, vals1[i][j], i, j);
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			matrix_set_el(m2, vals2[i][j], i, j);
		}
	}

	matrix_t *result = matrix_mult(m1, m2);
	ck_assert_ptr_nonnull(result);

	double expected[2][2] = {{58, 64}, {139, 154}};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			double val = 0;
			matrix_get_el(result, i, j, &val);
			ck_assert_double_eq_tol(val, expected[i][j], 1e-7);
		}
	}

	matrix_free(m1);
	matrix_free(m2);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_mult_tcase_2) {
	matrix_t *m1 = matrix_calloc(1, 3);
	matrix_t *m2 = matrix_calloc(3, 1);

	matrix_set_el(m1, 2, 0, 0);
	matrix_set_el(m1, 3, 0, 1);
	matrix_set_el(m1, 4, 0, 2);

	matrix_set_el(m2, 5, 0, 0);
	matrix_set_el(m2, 6, 1, 0);
	matrix_set_el(m2, 7, 2, 0);

	matrix_t *result = matrix_mult(m1, m2);
	ck_assert_ptr_nonnull(result);

	double val = 0;
	matrix_get_el(result, 0, 0, &val);
	ck_assert_double_eq_tol(val, 56, 1e-7);

	matrix_free(m1);
	matrix_free(m2);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_mult_tcase_3) {
	matrix_t *m1 = matrix_calloc(2, 2);
	matrix_t *m2 = matrix_calloc(2, 2);

	double vals1[2][2] = {{1.5, 2.5}, {3.5, 4.5}};
	double vals2[2][2] = {{0.5, 1.5}, {2.5, 3.5}};

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++) {
			matrix_set_el(m1, vals1[i][j], i, j);
			matrix_set_el(m2, vals2[i][j], i, j);
		}

	matrix_t *result = matrix_mult(m1, m2);
	ck_assert_ptr_nonnull(result);

	double expected[2][2] = {{7, 11}, {13, 21}};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			double val = 0;
			matrix_get_el(result, i, j, &val);
			ck_assert_double_eq_tol(val, expected[i][j], 1e-7);
		}
	}

	matrix_free(m1);
	matrix_free(m2);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_mult_tcase_4) {
	matrix_t *m1 = matrix_calloc(2, 3);
	matrix_t *m2 = matrix_calloc(4, 2);

	matrix_t *result = matrix_mult(m1, m2);
	ck_assert_ptr_null(result);

	matrix_free(m1);
	matrix_free(m2);
}
END_TEST

START_TEST(matrix_mult_tcase_5) {
	matrix_t *result = matrix_mult(NULL, NULL);
	ck_assert_ptr_null(result);
}
END_TEST

START_TEST(matrix_mult_tcase_6) {
	matrix_t *m1 = matrix_calloc(3, 3);
	matrix_t *m2 = matrix_calloc(3, 3);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m1, 0, i, j);
			matrix_set_el(m2, (i == j) ? 1.0 : 0.0, i, j);
		}
	}

	matrix_t *result = matrix_mult(m1, m2);
	ck_assert_ptr_nonnull(result);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			double val = 0;
			matrix_get_el(result, i, j, &val);
			ck_assert_double_eq_tol(val, 0, 1e-7);
		}
	}

	matrix_free(m1);
	matrix_free(m2);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_mult_tcase_7) {
	matrix_t *m1 = matrix_calloc(2, 2);
	matrix_t *m2 = matrix_calloc(2, 2);

	double vals1[2][2] = {{1, 2}, {3, 4}};
	double vals2[2][2] = {{-1, 0}, {0, -1}};

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++) {
			matrix_set_el(m1, vals1[i][j], i, j);
			matrix_set_el(m2, vals2[i][j], i, j);
		}

	matrix_t *result = matrix_mult(m1, m2);
	ck_assert_ptr_nonnull(result);

	double expected[2][2] = {{-1, -2}, {-3, -4}};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			double val = 0;
			matrix_get_el(result, i, j, &val);
			ck_assert_double_eq_tol(val, expected[i][j], 1e-7);
		}
	}

	matrix_free(m1);
	matrix_free(m2);
	matrix_free(result);
}
END_TEST

Suite *matrix_mult_test_suite() {
	Suite *s = suite_create("matrix_mult_tests");
	TCase *tc_core = tcase_create("Core matrix_mult_tests");

	tcase_add_test(tc_core, matrix_mult_tcase_1);
	tcase_add_test(tc_core, matrix_mult_tcase_2);
	tcase_add_test(tc_core, matrix_mult_tcase_3);
	tcase_add_test(tc_core, matrix_mult_tcase_4);
	tcase_add_test(tc_core, matrix_mult_tcase_5);
	tcase_add_test(tc_core, matrix_mult_tcase_6);
	tcase_add_test(tc_core, matrix_mult_tcase_7);

	suite_add_tcase(s, tc_core);
	return s;
}