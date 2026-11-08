/**
 * @file 2-1-15.c
 * @brief Лабораторная работа 2. Задание 1 (Вариант 15).
 * Консольное приложение для вычисления суммы, разности или среднего арифметического
 * двух целых чисел с использованием перечислимого типа enum.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Перечисление доступных математических операций
 */
typedef enum
{
    OP_SUM = 1,
    OP_DIFF = 2,
    OP_AVG = 3
} Operation;

/**
 * @brief Считывание целого числа с клавиатуры с проверкой ввода
 * @param prompt Текст подсказки перед вводом
 * @return Считанное целое число
 */
int get_int(const char* prompt);

/**
 * @brief Считывание выбора операции из меню с проверкой диапазона
 * @return Выбранный пункт операции
 */
Operation get_operation();

/**
 * @brief Вычисление суммы двух целых чисел
 * @param a Первое число
 * @param b Второе число
 * @return Сумма a + b
 */
int get_sum(const int a, const int b);

/**
 * @brief Вычисление разности двух целых чисел
 * @param a Первое число
 * @param b Второе число
 * @return Разность a - b
 */
int get_diff(const int a, const int b);

/**
 * @brief Вычисление среднего арифметического двух целых чисел
 * @param a Первое число
 * @param b Второе число
 * @return Среднее арифметическое
 */
double get_avg(const int a, const int b);

int main()
{
    setbuf(stdout, NULL);

    const int a = get_int("Введите первое целое число (a): ");
    const int b = get_int("Введите второе целое число (b): ");

    printf("\nВыберите операцию:\n");
    printf("%d - Сумма (a + b)\n", OP_SUM);
    printf("%d - Разность (a - b)\n", OP_DIFF);
    printf("%d - Среднее арифметическое ((a + b) / 2)\n", OP_AVG);

    const Operation op = get_operation();

    printf("\nРезультат:\n");
    switch (op)
    {
        case OP_SUM:
            printf("Сумма: %d + %d = %d\n", a, b, get_sum(a, b));
            break;
        case OP_DIFF:
            printf("Разность: %d - %d = %d\n", a, b, get_diff(a, b));
            break;
        case OP_AVG:
            printf("Среднее арифметическое: (%.1f + %.1f) / 2 = %.2f\n", (double)a, (double)b, get_avg(a, b));
            break;
        default:
            printf("Неизвестная операция\n");
            break;
    }

    return 0;
}

int get_int(const char* prompt)
{
    if (prompt == NULL)
    {
        exit(1);
    }

    int val = 0;
    printf("%s", prompt);

    if (scanf("%d", &val) != 1)
    {
        printf("Ошибка: необходимо ввести корректное целое число.\n");
        exit(1);
    }
    return val;
}

Operation get_operation()
{
    int choice = 0;
    printf("Ваш выбор: ");

    if (scanf("%d", &choice) != 1 || choice < OP_SUM || choice > OP_AVG)
    {
        printf("Ошибка: необходимо выбрать вариант от %d до %d.\n", OP_SUM, OP_AVG);
        exit(1);
    }
    return (Operation)choice;
}

int get_sum(const int a, const int b)
{
    return a + b;
}

int get_diff(const int a, const int b)
{
    return a - b;
}

double get_avg(const int a, const int b)
{
    return (a + b) / 2.0;
}
