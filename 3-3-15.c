/**
 * @file 3-3-15.c
 * @brief Лабораторная работа 3. Задание 3 (Вариант 15).
 * Табулирование функции y = (x * (3 - x)) / ((1 - x)^3) и суммы ее функционального
 * ряда S = sum_{n=1}^inf n * (n + 2) * x^n на интервале [0.1; 1.0] с заданной точностью eps = 4e-5.
 * Вычисление слагаемых ряда выполняется по рекуррентной формуле:
 * u_1 = 3 * x; u_n = u_{n-1} * (n * (n + 2)) / ((n - 1) * (n + 1)) * x.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

/**
 * @brief Вычисление точного значения аналитической функции y(x)
 * @param x Точка вычисления
 * @return Точное значение y(x)
 */
double get_exact_y(const double x);

/**
 * @brief Вычисление суммы функционального ряда в точке x с заданной точностью eps
 * @param x Точка вычисления
 * @param eps Требуемая точность вычислений
 * @param terms_count Указатель для записи числа слагаемых ряда
 * @return Значение суммы ряда S(x)
 */
double get_series_sum(const double x, const double eps, int* terms_count);

/**
 * @brief Табулирование аналитической функции и ряда на интервале [a; b] с шагом h
 * @param a Начало интервала
 * @param b Конец интервала
 * @param h Шаг табулирования
 * @param eps Точность вычисления ряда
 */
void tabulate_comparison(const double a, const double b, const double h, const double eps);

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении
 */
int main()
{
    // Выключение буферизации под шиндовс
    setbuf(stdout, NULL);

    // Константы интервала и точности по варианту 15
    const double a = 0.1;
    const double b = 1.0;
    const double h = 0.1;
    const double eps = 4e-5;

    printf("Табуляция функции и суммы ряда (eps = %.2e):\n", eps);
    tabulate_comparison(a, b, h, eps);

    return 0;
}

double get_exact_y(const double x)
{
    // В точке x = 1.0 деление на ноль
    if (fabs(1.0 - x) < DBL_EPSILON)
    {
        return NAN;
    }
    return (x * (3.0 - x)) / pow(1.0 - x, 3.0);
}

double get_series_sum(const double x, const double eps, int* terms_count)
{
    // Проверка указателя
    if (terms_count == NULL)
    {
        exit(1);
    }

    // При x >= 1 ряд расходится (радиус R = 1)
    if (x >= 1.0 - DBL_EPSILON)
    {
        *terms_count = 0;
        return NAN;
    }

    // Первый член ряда u_1 = 3 * x
    double u_n = 3.0 * x;
    double sum = 0.0;
    int n = 1;

    // Накопление суммы, пока слагаемое по модулю >= eps
    while (fabs(u_n) >= eps)
    {
        sum += u_n;
        n++;

        // Рекуррентный пересчет слагаемого
        u_n = u_n * ((double)(n * (n + 2))) / ((double)((n - 1) * (n + 1))) * x;

        // Ограничение числа итераций от зацикливания
        if (n > 500000)
        {
            break;
        }
    }

    *terms_count = n - 1;
    return sum;
}

void tabulate_comparison(const double a, const double b, const double h, const double eps)
{
    printf("x\ty\t\tS\n");

    for (double x = a; x <= b + h / 2.0; x += h)
    {
        const double y_exact = get_exact_y(x);
        int terms = 0;
        const double s_approx = get_series_sum(x, eps, &terms);

        if (isnan(y_exact) || isnan(s_approx))
        {
            printf("%.1f\tразрыв\t\tряд расходится\n", x);
        }
        else
        {
            printf("%.1f\t%10.6f\t%10.6f\n", x, y_exact, s_approx);
        }
    }
}
