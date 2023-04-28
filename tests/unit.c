#include "unit.h"

int main() {
    int fail = 0;

    Suite* s21_matrix_tests[] = {suite_s21_create_matrix(),
                                 suite_s21_eq_matrix(),
                                 suite_s21_sum_matrix(),
                                 suite_s21_sub_matrix(),
                                 suite_s21_mult_number(),
                                 suite_s21_mult_matrix(),
                                 suite_s21_transpose(),
                                 suite_s21_calc_complements(),
                                 suite_s21_determinant(),
                                 suite_s21_inverse_matrix(),
                                 NULL};

    for (int i = 0; s21_matrix_tests[i] != NULL; i++) {
        SRunner* sr = srunner_create(s21_matrix_tests[i]);

        srunner_set_fork_status(sr, CK_NOFORK);
        srunner_run_all(sr, CK_NORMAL);

        fail += srunner_ntests_failed(sr);
        srunner_free(sr);
    }

    printf("========= FAILED: %d =========\n", fail);

    return fail == 0 ? 0 : 1;

    return 0;
}