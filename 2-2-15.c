/**
 * @file 2-2-15.c
 * @brief Лабораторная работа 2. Задание 2 (Вариант 15).
 * Разветвленный вычислительный процесс для кусочно-заданной функции:
 * y = tg(x) + pi/3 при x > a
 * y = sin(x) * a    при x <= a
 * Константа a = 2.0.
 */

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

/**
 * @brief Считывание вещественного числа с клавиатуры с проверкой ввода
 * @param prompt Текст подсказки перед вводом
 * @return Считанное вещественное число
 */
double get_double(const char* prompt);

/**
 * @brief Вычисление значения кусочно-заданной функции y(x)
 * @param x Вещественный аргумент x
 * @param a Константа границы условий
 * @return Результат вычисления функции
 */
double calculate_y(const double x, const double a);

int main()
{
    setbuf(stdout, NULL);

    const double a = 2.0;

    printf("Вычисление функции y(x):\n");
    printf("y = tg(x) + pi/3, если x > %.1f\n", a);
    printf("y = sin(x) * a,   если x <= %.1f\n\n", a);

    const double x = get_double("Введите значение аргумента x: ");
    const double y = calculate_y(x, a);
    printf("Результат: y(%.4f) = %.5f\n", x, y);

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

double calculate_y(const double x, const double a)
{
    if (x > a)
    {
        if (fabs(cos(x)) < DBL_EPSILON)
        {
            printf("Ошибка: тангенс не определен при данном значении x (cos(x) ~ 0).\n");
            exit(1);
        }
        return tan(x) + (M_PI / 3.0);
    }
    else
    {
        return sin(x) * a;
    }
}
