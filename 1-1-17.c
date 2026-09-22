/**
 * @file 1-1-17.c
 * @brief Работа 1. Задание 1 (Вариант 17)
 * Программа для расчета математических выражений a и b по заданным формулам
 */

#include <stdio.h>
#include <math.h>

/**
 * @brief Вычисляет значение математической функции a по формуле варианта
 * @param x Вещественный параметр x
 * @param y Вещественный параметр y
 * @param z Вещественный параметр z
 * @return Результат вычисления функции a (тип double)
 */
double A(const double x, const double y, const double z);

/**
 * @brief Вычисляет значение математической функции b по формуле варианта
 * @param x Вещественный параметр x
 * @param y Вещественный параметр y
 * @param z Вещественный параметр z
 * @return Результат вычисления функции b (тип double)
 */
double B(const double x, const double y, const double z);

/**
 * @brief Главная функция программы
 * Инициализирует входные константы, выводит их на экран и отображает результаты расчетов
 * @return Код 0 при успешном выполнении
 */
int main()
{
    // Исходные константы согласно варианту 17
    const double x = 0.78;
    const double y = 1.24;
    const double z = 0.5;
    
    // Вывод исходных данных
    printf("x=%.2f y=%.2f z=%.2f\n", x, y, z);
    
    // Вывод рассчитанных результатов
    printf("a=%.5f\n", A(x, y, z));
    printf("b=%.5f\n", B(x, y, z));
    
    return 0;
}

double A(const double x, const double y, const double z)
{
    return (2 * pow(z, x)) / sqrt(pow(y, x) * (x + y) - 3 * z);
}

double B(const double x, const double y, const double z)
{
    return x * exp(sqrt(z)) * cos(cos(pow(x, 2) / (y * z)));
}
