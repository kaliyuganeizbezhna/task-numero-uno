/**
 * @file 2-2-15.c
 * @brief Лабораторная работа 2. Задание 2 (Вариант 15).
 * Разветвленный вычислительный процесс для кусочно-заданной функции:
 * y = tg(x) + pi/3 при x > a
 * y = sin(x) * a    при x <= a
 * Константа a = 2.0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief Константа числа Пи для вычислений
 */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении
 */
int main()
{
    // Выключение буферизации под шиндовс для вывода в консоль
    setbuf(stdout, NULL);

    // Константа варианта 15
    const double a = 2.0;

    printf("Вычисление функции y(x):\n");
    printf("  y = tg(x) + pi/3, если x > %.1f\n", a);
    printf("  y = sin(x) * a,   если x <= %.1f\n\n", a);

    // Запрос и ввод аргумента x
    const double x = get_double("Введите значение аргумента x: ");

    // Вычисление и вывод результата
    const double y = calculate_y(x, a);
    printf("\nРезультат вычисления: y(%.4f) = %.5f\n", x, y);

    return 0;
}

double get_double(const char* prompt)
{
    double val = 0.0;
    printf("%s", prompt);
    fflush(stdout);

    // Проверка, что введено именно число.
    if (scanf("%lf", &val) != 1)
    {
        printf("Ошибка: введено некорректное вещественное число.\n");
        exit(1);
    }
    return val;
}

double calculate_y(const double x, const double a)
{
    // Ветка x > a
    if (x > a)
    {
        // Проверка деления на ноль для тангенса (cos(x) ~ 0)
        if (fabs(cos(x)) < 1e-7)
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
