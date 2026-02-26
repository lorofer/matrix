#include "tests.h"

START_TEST(matrix_calc_complements_tcase_1) {
	matrix_t *m = matrix_calloc(2, 2);

	double values[2][2] = {{1, 2}, {3, 4}};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	matrix_t *result = matrix_calc_complements(m);
	ck_assert_ptr_nonnull(result);

	double expected[2][2] = {{4, -3}, {-2, 1}};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			ck_assert_double_eq_tol(matrix_get_el(result, i, j), expected[i][j], 1e-7);
		}
	}

	matrix_free(m);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_calc_complements_tcase_2) {
	matrix_t *m = matrix_calloc(3, 3);

	double values[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	matrix_t *result = matrix_calc_complements(m);
	ck_assert_ptr_nonnull(result);

	double expected[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ck_assert_double_eq_tol(matrix_get_el(result, i, j), expected[i][j], 1e-7);
		}
	}

	matrix_free(m);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_calc_complements_tcase_3) {
	matrix_t *m = matrix_calloc(1, 1);
	matrix_set_el(m, 5.0, 0, 0);

	matrix_t *result = matrix_calc_complements(m);
	ck_assert_ptr_nonnull(result);

	ck_assert_double_eq_tol(matrix_get_el(result, 0, 0), 1.0, 1e-7);

	matrix_free(m);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_calc_complements_tcase_4) {
	matrix_t *m = matrix_calloc(2, 3);

	matrix_t *result = matrix_calc_complements(m);
	ck_assert_ptr_null(result);

	matrix_free(m);
}
END_TEST

START_TEST(matrix_calc_complements_tcase_5) {
	matrix_t *result = matrix_calc_complements(NULL);
	ck_assert_ptr_null(result);
}
END_TEST

START_TEST(matrix_calc_complements_tcase_6) {
	matrix_t *m = matrix_calloc(3, 3);

	double values[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	matrix_t *result = matrix_calc_complements(m);
	ck_assert_ptr_nonnull(result);

	double expected[3][3] = {{-1, 38, -27}, {1, -41, 29}, {-1, 34, -24}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ck_assert_double_eq_tol(matrix_get_el(result, i, j), expected[i][j], 1e-7);
		}
	}

	matrix_free(m);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_calc_complements_tcase_7) {
	matrix_t *m = matrix_calloc(3, 3);

	double values[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	matrix_t *result = matrix_calc_complements(m);
	ck_assert_ptr_nonnull(result);

	double expected[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ck_assert_double_eq_tol(matrix_get_el(result, i, j), expected[i][j], 1e-7);
		}
	}

	matrix_free(m);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_calc_complements_tcase_8) {
	matrix_t *m = matrix_calloc(3, 3);

	double values[3][3] = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m, values[i][j], i, j);
		}
	}

	matrix_t *result = matrix_calc_complements(m);
	ck_assert_ptr_nonnull(result);

	double expected[3][3] = {{4, 0, 0}, {0, 4, 0}, {0, 0, 4}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ck_assert_double_eq_tol(matrix_get_el(result, i, j), expected[i][j], 1e-7);
		}
	}

	matrix_free(m);
	matrix_free(result);
}
END_TEST

Suite *matrix_calc_complements_test_suite() {
	Suite *s = suite_create("matrix_calc_complements_tests");
	TCase *tc_core = tcase_create("Core matrix_calc_complements_tests");

	tcase_add_test(tc_core, matrix_calc_complements_tcase_1);
	tcase_add_test(tc_core, matrix_calc_complements_tcase_2);
	tcase_add_test(tc_core, matrix_calc_complements_tcase_3);
	tcase_add_test(tc_core, matrix_calc_complements_tcase_4);
	tcase_add_test(tc_core, matrix_calc_complements_tcase_5);
	tcase_add_test(tc_core, matrix_calc_complements_tcase_6);
	tcase_add_test(tc_core, matrix_calc_complements_tcase_7);
	tcase_add_test(tc_core, matrix_calc_complements_tcase_8);

	suite_add_tcase(s, tc_core);
	return s;
}