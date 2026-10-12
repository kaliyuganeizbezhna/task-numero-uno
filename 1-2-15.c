/**
 * @file 1-2-15.c
 * @brief Лабораторная работа 1. Задание 2 (Вариант 15).
 * Расчет периметра и площади прямоугольного треугольника по двум катетам.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/**
 * @brief Считывает вещественное число с клавиатуры с проверкой правильности
 * @return Считанное положительное значение типа double
 */
double get_double();

/**
 * @brief Считает гипотенузу прямоугольного треугольника по теореме пифагора
 * @param a Длина первого катета
 * @param b Длина второго катета
 * @return Длина гипотенузы (тип double)
 */
double get_hypotenuse(const double a, const double b);

/**
 * @brief Считает периметр прямоугольного треугольника
 * @param a Длина первого катета
 * @param b Длина второго катета
 * @return Периметр треугольника (тип double)
 */
double get_perimeter(const double a, const double b);

/**
 * @brief Считает площадь прямоугольного треугольника
 * @param a Длина первого катета
 * @param b Длина второго катета
 * @return Площадь треугольника (тип double)
 */
double get_area(const double a, const double b);

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении программы
 */
int main()
{
    // Выключение буферизации, чтобы текст пояснение отображался до ввода значений
    setbuf(stdout, NULL);

    // Запрос и ввод первого катета
    printf("Введите длину первого катета (a): ");
    fflush(stdout);
    const double a = get_double();

    // Запрос и ввод второго катета
    printf("Введите длину второго катета (b): ");
    fflush(stdout);
    const double b = get_double();

    // Вывод результатов расчетов
    printf("\nРезультаты:\n");
    printf("P = %.2f\n", get_perimeter(a, b));
    printf("S = %.2f\n", get_area(a, b));

    return 0;
}

double get_double()
{
    double val = 0.0;
    // Проверка что введено именно число, и что длина катета строго больше нуля
    if (scanf("%lf", &val) != 1 || val <= 0.0)
    {
        printf("Введено некорректное значение (длина должна быть числом > 0)\n");
        exit(1);
    }
    return val;
}

double get_hypotenuse(const double a, const double b)
{
    return sqrt(pow(a, 2) + pow(b, 2));
}

double get_perimeter(const double a, const double b)
{
    return a + b + get_hypotenuse(a, b);
}

double get_area(const double a, const double b)
{
    return 0.5 * a * b;
}