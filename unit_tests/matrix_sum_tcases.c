#include "tests.h"

START_TEST(matrix_sum_tcase_1) {
	matrix_t *m1 = matrix_calloc(3, 3);
	matrix_t *m2 = matrix_calloc(3, 3);

	double values[3][3] = {
		{1.0, 2.0, 3.0},
		{1.0, 2.0, 3.0},
		{1.0, 2.0, 3.0},
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m1, values[i][j], i, j);
			matrix_set_el(m2, values[i][j], i, j);
		}
	}

	matrix_t *result = matrix_sum(m1, m2);
	ck_assert_ptr_nonnull(result);

	double result_matrix[3][3] = {
		{2.0, 4.0, 6.0},
		{2.0, 4.0, 6.0},
		{2.0, 4.0, 6.0},
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			double val = 0;
			matrix_get_el(result, i, j, &val);
			ck_assert_double_eq_tol(val, result_matrix[i][j], 1e-7);
		}
	}

	matrix_free(m1);
	matrix_free(m2);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_sum_tcase_2) {
	matrix_t *m1 = matrix_calloc(3, 2);
	matrix_t *m2 = matrix_calloc(3, 2);

	double values[3][2] = {
		{1.0, 2.0},
		{1.0, 2.0},
		{1.0, 2.0},
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			matrix_set_el(m1, values[i][j], i, j);
			matrix_set_el(m2, values[i][j], i, j);
		}
	}

	matrix_t *result = matrix_sum(m1, m2);
	ck_assert_ptr_nonnull(result);

	double result_matrix[3][2] = {
		{2.0, 4.0},
		{2.0, 4.0},
		{2.0, 4.0},
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			double val = 0;
			matrix_get_el(result, i, j, &val);
			ck_assert_double_eq_tol(val, result_matrix[i][j], 1e-7);
		}
	}

	matrix_free(m1);
	matrix_free(m2);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_sum_tcase_3) {
	matrix_t *m1 = matrix_calloc(3, 3);
	matrix_t *m2 = matrix_calloc(3, 3);

	double values1[3][3] = {
		{1.0000000, 2.0, 3.0},
		{1.0, 2.0, 3.0},
		{1.0, 2.0, 3.0},
	};
	double values2[3][3] = {
		{1.0000001, 2.0, 3.0},
		{1.0, 2.0, 3.0},
		{1.0, 2.0, 3.0},
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m1, values1[i][j], i, j);
			matrix_set_el(m2, values2[i][j], i, j);
		}
	}

	matrix_t *result = matrix_sum(m1, m2);
	ck_assert_ptr_nonnull(result);

	double result_matrix[3][3] = {
		{2.0000001, 4.0, 6.0},
		{2.0, 4.0, 6.0},
		{2.0, 4.0, 6.0},
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			double val = 0;
			matrix_get_el(result, i, j, &val);
			ck_assert_double_eq_tol(val, result_matrix[i][j], 1e-7);
		}
	}

	matrix_free(m1);
	matrix_free(m2);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_sum_tcase_4) {
	matrix_t *m1 = matrix_calloc(3, 3);
	matrix_t *m2 = matrix_calloc(3, 3);

	matrix_set_el(m1, 5.0, 0, 0);
	matrix_set_el(m2, 5.0, 0, 0);

	matrix_t *result = matrix_sum(m1, m2);
	ck_assert_ptr_nonnull(result);

	double result_matrix[1][1] = {
		{10.0},
	};
	double val = 0;
	matrix_get_el(result, 0, 0, &val);
	ck_assert_double_eq_tol(val, result_matrix[0][0], 1e-7);

	matrix_free(m1);
	matrix_free(m2);
	matrix_free(result);
}
END_TEST

START_TEST(matrix_sum_tcase_5) {
	matrix_t *m1 = matrix_calloc(3, 2);
	matrix_t *m2 = matrix_calloc(2, 3);

	double values1[3][2] = {
		{1.0, 2.0},
		{1.0, 2.0},
		{1.0, 2.0},
	};
	double values2[2][3] = {
		{1.0, 2.0, 3.0},
		{1.0, 2.0, 3.0},
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			matrix_set_el(m1, values1[i][j], i, j);
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m2, values2[i][j], i, j);
		}
	}

	matrix_t *result = matrix_sum(m1, m2);
	ck_assert_ptr_null(result);

	matrix_free(m1);
	matrix_free(m2);
}
END_TEST

START_TEST(matrix_sum_tcase_6) {
	matrix_t *result = matrix_sum(NULL, NULL);
	ck_assert_ptr_null(result);
}
END_TEST

Suite *matrix_sum_test_suite() {
	Suite *s = suite_create("matrix_sum_tests");
	TCase *tc_core = tcase_create("Core matrix_sum_tests");

	tcase_add_test(tc_core, matrix_sum_tcase_1);
	tcase_add_test(tc_core, matrix_sum_tcase_2);
	tcase_add_test(tc_core, matrix_sum_tcase_3);
	tcase_add_test(tc_core, matrix_sum_tcase_4);
	tcase_add_test(tc_core, matrix_sum_tcase_5);
	tcase_add_test(tc_core, matrix_sum_tcase_6);

	suite_add_tcase(s, tc_core);

	return s;
}