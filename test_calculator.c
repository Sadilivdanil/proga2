#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "calculator.h"

// Тест для функции сложения
START_TEST(test_add) {
    ck_assert_msg(add(2, 3) == 5, "2 + 3 должно быть 5");
    ck_assert_msg(add(-1, 1) == 0, "-1 + 1 должно быть 0");
    ck_assert_msg(add(0, 0) == 0, "0 + 0 должно быть 0");
}
END_TEST

// Тест для функции вычитания
START_TEST(test_subtract) {
    ck_assert_msg(subtract(5, 3) == 2, "5 - 3 должно быть 2");
    ck_assert_msg(subtract(10, -5) == 15, "10 - (-5) должно быть 15");
    ck_assert_msg(subtract(0, 0) == 0, "0 - 0 должно быть 0");
}
END_TEST

// Тест для функции умножения
START_TEST(test_multiply) {
    ck_assert_msg(multiply(2, 3) == 6, "2 * 3 должно быть 6");
    ck_assert_msg(multiply(-1, 5) == -5, "-1 * 5 должно быть -5");
    ck_assert_msg(multiply(0, 100) == 0, "0 * 100 должно быть 0");
}
END_TEST

// Тест для функции деления
START_TEST(test_divide) {
    ck_assert_msg(divide(6, 3) == 2, "6 / 3 должно быть 2");
    ck_assert_msg(divide(10, 2) == 5, "10 / 2 должно быть 5");
    ck_assert_msg(divide(5, 2) == 2, "5 / 2 должно быть 2 (целочисленное деление)");
    ck_assert_msg(divide(10, 0) == 0, "10 / 0 должно возвращать 0 (обработка ошибки)");
}
END_TEST

// Тест для функции факториала
START_TEST(test_fact) {
    ck_assert_int_eq(fact(0), 1);   // 0! = 1
    ck_assert_int_eq(fact(1), 1);   // 1! = 1
    ck_assert_int_eq(fact(5), 12); // 5! = 120
}
END_TEST

// Создание тестового набора
Suite *calculator_suite(void) {
    Suite *s = suite_create("Calculator Tests");
    TCase *tc_core = tcase_create("Core Functions");

    tcase_add_test(tc_core, test_add);
    tcase_add_test(tc_core, test_subtract);
    tcase_add_test(tc_core, test_multiply);
    tcase_add_test(tc_core, test_divide);
    tcase_add_test(tc_core, test_fact);

    suite_add_tcase(s, tc_core);
    return s;
}

// Функция вывода результатов
void print_test_results(int passed, int total) {
    printf("\n=== Результаты тестирования ===\n");
    printf("Всего тестов: %d\n", total);
    printf("Успешных:     %d\n", passed);
    printf("Неудачных:    %d\n", total - passed);
    
    if (passed == total) {
        printf("\nВсе тесты успешно пройдены!\n");
    } else {
        printf("\nОбнаружены ошибки в тестах!\n");
    }
}

int main(void) {
    Suite *s = calculator_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    
    
    int total = srunner_ntests_run(sr);
    int failed = srunner_ntests_failed(sr);
    int passed = total - failed;
    
    print_test_results(passed, total);
    
    srunner_free(sr);
    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}