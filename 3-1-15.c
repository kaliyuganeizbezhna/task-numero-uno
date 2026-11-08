/**
 * @file 3-1-15.c
 * @brief Лабораторная работа 3. Задание 1 (Вариант 15).
 * 1. Табулирование функции y = cos(x) - e^(-x^2/2) + x - 1 на интервале [x_start; x_end] с шагом dx.
 * 2. Дополнительная задача: сумма цифр числа a (a < 1000).
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief Считывание вещественного числа с клавиатуры с проверкой ввода
 * @param prompt Текст подсказки перед вводом
 * @return Считанное вещественное число
 */
double get_double(const char* prompt);

/**
 * @brief Вычисление значения функции y(x) по формуле варианта
 * @param x Вещественный аргумент x
 * @return Значение функции y
 */
double calculate_function(const double x);

/**
 * @brief Табулирование функции на заданном отрезке
 * @param start Начало интервала
 * @param end Конец интервала
 * @param step Шаг аргумента
 */
void tabulate(const double start, const double end, const double step);

/**
 * @brief Считывание числа a для дополнительной задачи (a < 1000)
 * @return Считанное натуральное число
 */
int get_digit_number();

/**
 * @brief Вычисление суммы цифр целого числа
 * @param n Число для подсчета суммы цифр
 * @return Сумма цифр
 */
int get_digits_sum(int n);

int main()
{
    setbuf(stdout, NULL);

    printf("Табуляция функции y = cos(x) - e^(-x^2/2) + x - 1\n");

    const double x_start = get_double("Введите начало интервала: ");
    const double x_end = get_double("Введите конец интервала: ");
    if (x_start >= x_end)
    {
        printf("Ошибка: начало интервала должно быть строго меньше конца.\n");
        exit(1);
    }

    const double x_step = get_double("Введите шаг (dx): ");
    if (x_step <= 0.0)
    {
        printf("Ошибка: шаг должен быть больше нуля.\n");
        exit(1);
    }

    printf("\nРезультаты табуляции:\n");
    tabulate(x_start, x_end, x_step);

    printf("\nДополнительная задача (сумма цифр числа a < 1000):\n");
    const int a = get_digit_number();
    const int sum = get_digits_sum(a);
    printf("Сумма цифр: %d\n", sum);

    return 0;
}

double get_double(const char* prompt)
{
    if (prompt == NULL)
    {
        exit(1);
    }

    double val = 0.0;
    printf("%s", prompt);

    if (scanf("%lf", &val) != 1)
    {
        printf("Ошибка: введено некорректное вещественное число.\n");
        exit(1);
    }
    return val;
}

double calculate_function(const double x)
{
    return cos(x) - exp(-pow(x, 2.0) / 2.0) + x - 1.0;
}

void tabulate(const double start, const double end, const double step)
{
    printf("x\ty\n");

    for (double x = start; x <= end + step / 2.0; x += step)
    {
        const double y = calculate_function(x);
        if (isnan(y) || isinf(y))
        {
            printf("%.2f\tнет решений\n", x);
        }
        else
        {
            printf("%.2f\t%.6f\n", x, y);
        }
    }
}

int get_digit_number()
{
    int val = 0;
    printf("Введите число a: ");

    if (scanf("%d", &val) != 1 || val <= 0 || val >= 1000)
    {
        printf("Ошибка: число должно быть целым, положительным и меньше 1000.\n");
        exit(1);
    }
    return val;
}

int get_digits_sum(int n)
{
    int sum = 0;
    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
