#ifndef TESTS_H
#define TESTS_H

#include <check.h>
#include <stdlib.h>

#include "../src/matrix.h"

Suite *matrix_memory_test_suite();
Suite *matrix_accessors_test_suite();
Suite *matrix_get_array_test_suite();
Suite *matrix_eq_test_suite();
Suite *matrix_sum_test_suite();
Suite *matrix_sub_test_suite();
Suite *matrix_mult_test_suite();
Suite *matrix_mult_number_test_suite();
Suite *matrix_transpose_test_suite();
Suite *matrix_calc_complements_test_suite();
Suite *matrix_determinant_test_suite();
Suite *matrix_inverse_test_suite();

#endif