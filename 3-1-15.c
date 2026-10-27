/**
 * @file 3-1-15.c
 * @brief Лабораторная работа 3. Задание 1 (Вариант 15).
 * 1. Табулирование функции y = cos(x) - e^(-x^2/2) + x - 1 на интервале [1; 2] с шагом 0.1.
 * 2. Дополнительная задача: нахождение суммы цифр введенного числа a (a < 1000).
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении
 */
int main()
{
    // Выключение буферизации под шиндовс
    setbuf(stdout, NULL);

    // Параметры табуляции по варианту 15
    const double x_start = 1.0;
    const double x_end = 2.0;
    const double x_step = 0.1;

    printf("--- ЧАСТЬ 1: ТАБУЛИРОВАНИЕ ФУНКЦИИ ---\n");
    printf("Функция: y = cos(x) - e^(-x^2/2) + x - 1\n");
    printf("Интервал: [%.1f; %.1f], шаг: %.1f\n\n", x_start, x_end, x_step);

    tabulate(x_start, x_end, x_step);

    printf("\n--- ЧАСТЬ 2: ДОПОЛНИТЕЛЬНАЯ ЗАДАЧА ---\n");
    printf("Определение суммы цифр числа a (a < 1000)\n");

    const int a = get_digit_number();
    const int sum = get_digits_sum(a);

    printf("Сумма цифр числа %d равна: %d\n", a, sum);

    return 0;
}

double calculate_function(const double x)
{
    // y = cos(x) - exp(-x^2 / 2) + x - 1
    return cos(x) - exp(-pow(x, 2.0) / 2.0) + x - 1.0;
}

void tabulate(const double start, const double end, const double step)
{
    printf("+---------+-----------------+\n");
    printf("|    x    |      y(x)       |\n");
    printf("+---------+-----------------+\n");

    // Цикл табуляции с шагом 0.1
    for (double x = start; x <= end + step / 2.0; x += step)
    {
        const double y = calculate_function(x);
        // Проверка на корректность результата
        if (isnan(y) || isinf(y))
        {
            printf("| %7.2f | Решений нет     |\n", x);
        }
        else
        {
            printf("| %7.2f | %15.6f |\n", x, y);
        }
    }
    printf("+---------+-----------------+\n");
}

int get_digit_number()
{
    int val = 0;
    printf("Введите целое положительное число a (a < 1000): ");
    fflush(stdout);

    // Проверка ввода: число строго от 1 до 999
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
    // Последовательное отделение цифр через остаток от 10
    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
