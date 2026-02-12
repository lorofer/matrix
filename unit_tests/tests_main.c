#include "tests.h"

int main() {
	SRunner *sr = srunner_create(matrix_memory_test_suite());
	srunner_add_suite(sr, matrix_accessors_test_suite());
	srunner_add_suite(sr, matrix_eq_test_suite());
	srunner_add_suite(sr, matrix_sum_test_suite());
	srunner_add_suite(sr, matrix_sub_test_suite());
	srunner_add_suite(sr, matrix_mult_test_suite());
	srunner_add_suite(sr, matrix_mult_number_test_suite());
	srunner_add_suite(sr, matrix_transpose_test_suite());
	srunner_add_suite(sr, matrix_determinant_test_suite());
	srunner_add_suite(sr, matrix_calc_complements_test_suite());
	//   srunner_add_suite(sr, s21_inverse_matrix_test_suite());

	srunner_set_fork_status(sr, CK_NOFORK);
	srunner_run_all(sr, CK_NORMAL);

	int number_failed = srunner_ntests_failed(sr);

	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}