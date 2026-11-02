/**
 * @file 3-2-15.c
 * @brief Лабораторная работа 3. Задание 2 (Вариант 15).
 * 1. Вычисление суммы первых n членов ряда: sum_{k=1}^n (-1)^k * (1 + k) / (k + 2)!
 * 2. Вычисление суммы членов этого же ряда, по модулю не меньших заданного e.
 * Использовано рекуррентное соотношение для вычисления слагаемых без факториала в лоб.
 * 3. Дополнительная задача: поиск суммы нечетных делителей натурального числа.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief Считывание натурального числа
 * @param prompt Текст подсказки перед вводом
 * @return Натуральное число
 */
int get_positive_int(const char* prompt);

/**
 * @brief Считывание точности e
 * @param prompt Текст подсказки перед вводом
 * @return Положительное число типа double
 */
double get_positive_double(const char* prompt);

/**
 * @brief Вычисление суммы первых n членов ряда рекуррентно
 * @param n Количество членов последовательности
 * @return Сумма первых n членов
 */
double get_sum_n(const int n);

/**
 * @brief Вычисление суммы членов ряда с модулем не меньше e
 * @param e Порог точности (e > 0)
 * @param count_used Указатель на переменную для сохранения числа слагаемых
 * @return Сумма слагаемых
 */
double get_sum_by_precision(const double e, int* count_used);

/**
 * @brief Поиск суммы всех нечетных делителей натурального числа
 * @param number Натуральное число
 * @return Сумма нечетных делителей
 */
int get_odd_divisors_sum(const int number);

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении
 */
int main()
{
    // Выключение буферизации под шиндовс
    setbuf(stdout, NULL);

    // Вычисление суммы n членов ряда
    const int n = get_positive_int("Введите n: ");
    const double sum_n = get_sum_n(n);
    printf("Сумма первых %d членов ряда: %.10f\n\n", n, sum_n);

    // Вычисление суммы членов с |a_k| >= e
    const double e = get_positive_double("Введите e: ");
    int count_terms = 0;
    const double sum_e = get_sum_by_precision(e, &count_terms);
    printf("Сумма слагаемых (|a_k| >= %e): %.10f (учтено: %d)\n", e, sum_e, count_terms);

    // Дополнительная задача
    printf("\nДополнительная задача (сумма нечетных делителей):\n");
    const int number = get_positive_int("Введите натуральное число: ");
    const int div_sum = get_odd_divisors_sum(number);
    printf("Сумма нечетных делителей: %d\n", div_sum);

    return 0;
}

int get_positive_int(const char* prompt)
{
    // Проверка на непустой указатель подсказки
    if (prompt == NULL)
    {
        exit(1);
    }

    int val = 0;
    printf("%s", prompt);
    fflush(stdout);

    // Проверка ввода натурального числа
    if (scanf("%d", &val) != 1 || val <= 0)
    {
        printf("Ошибка: необходимо ввести натуральное число (> 0).\n");
        exit(1);
    }
    return val;
}

double get_positive_double(const char* prompt)
{
    // Проверка на непустой указатель подсказки
    if (prompt == NULL)
    {
        exit(1);
    }

    double val = 0.0;
    printf("%s", prompt);
    fflush(stdout);

    // Проверка ввода точности e > 0
    if (scanf("%lf", &val) != 1 || val <= 0.0)
    {
        printf("Ошибка: точность e должна быть вещественным числом больше 0.\n");
        exit(1);
    }
    return val;
}

double get_sum_n(const int n)
{
    // Первый член ряда при k = 1: a_1 = -2/6 = -1/3
    double a_k = -1.0 / 3.0;
    double sum = a_k;

    // Рекуррентный пересчет слагаемых без прямого вычисления факториала
    for (int k = 2; k <= n; k++)
    {
        // a_k = -a_{k-1} * (k + 1) / (k * (k + 2))
        a_k = -a_k * ((double)(k + 1)) / ((double)(k * (k + 2)));
        sum += a_k;
    }

    return sum;
}

double get_sum_by_precision(const double e, int* count_used)
{
    // Проверка указателя
    if (count_used == NULL)
    {
        exit(1);
    }

    double sum = 0.0;
    int k = 1;

    // Начальное значение слагаемого при k = 1
    double a_k = -1.0 / 3.0;

    // Суммирование, пока модуль слагаемого не станет меньше e
    while (fabs(a_k) >= e)
    {
        sum += a_k;
        k++;

        // Рекуррентный шаг
        a_k = -a_k * ((double)(k + 1)) / ((double)(k * (k + 2)));

        // Защита от зависания при слишком малом e
        if (k > 1000000)
        {
            break;
        }
    }

    *count_used = k - 1;
    return sum;
}

int get_odd_divisors_sum(const int number)
{
    int sum = 0;

    // Перебор делителей от 1 до number
    for (int d = 1; d <= number; d++)
    {
        // Проверка на нечетный делитель
        if (number % d == 0 && d % 2 != 0)
        {
            sum += d;
        }
    }

    return sum;
}
