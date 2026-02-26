#include "tests.h"

START_TEST(matrix_memory_tcase_1) {
	matrix_t *matrix = matrix_calloc(3, 10);
	ck_assert_ptr_nonnull(matrix);
	matrix_free(matrix);
}
END_TEST

START_TEST(matrix_memory_tcase_2) {
	matrix_t *matrix = matrix_calloc(0, -10);
	ck_assert_ptr_null(matrix);
}
END_TEST

START_TEST(matrix_memory_tcase_3) {
	matrix_t *matrix = matrix_calloc(3, 10);
	matrix_t *new_matrix = matrix_realloc(matrix, 3, 3);

	ck_assert_ptr_nonnull(new_matrix);
	ck_assert_ptr_ne(matrix, new_matrix);

	matrix_free(new_matrix);
}
END_TEST

START_TEST(matrix_memory_tcase_4) {
	matrix_t *m1 = matrix_calloc(3, 3);
	double values[3][3] = {
		{1.0, 2.0, 3.0},
		{1.0, 2.0, 3.0},
		{1.0, 2.0, 3.0},
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_set_el(m1, values[i][j], i, j);
		}
	}

	matrix_t *m2 = matrix_realloc(m1, 5, 5);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ck_assert_double_eq(matrix_get_el(m2, i, j), values[i][j]);
		}
	}

	matrix_free(m2);
}
END_TEST

START_TEST(matrix_memory_tcase_5) {
	matrix_t *m1 = matrix_calloc(3, 4);
	double values[3][4] = {
		{1.0, 2.0, 3.0, 4.0},
		{1.0, 2.0, 3.0, 4.0},
		{1.0, 2.0, 3.0, 4.0},
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			matrix_set_el(m1, values[i][j], i, j);
		}
	}

	matrix_t *m2 = matrix_realloc(m1, 2, 2);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			ck_assert_double_eq(matrix_get_el(m2, i, j), values[i][j]);
		}
	}

	matrix_free(m2);
}
END_TEST

Suite *matrix_memory_test_suite() {
	Suite *s = suite_create("matrix_memory_tests");
	TCase *tc_core = tcase_create("Core matrix_memory_tests");

	tcase_add_test(tc_core, matrix_memory_tcase_1);
	tcase_add_test(tc_core, matrix_memory_tcase_2);
	tcase_add_test(tc_core, matrix_memory_tcase_3);
	tcase_add_test(tc_core, matrix_memory_tcase_4);
	tcase_add_test(tc_core, matrix_memory_tcase_5);

	suite_add_tcase(s, tc_core);

	return s;
}