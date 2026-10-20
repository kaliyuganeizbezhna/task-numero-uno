/**
 * @file 1-3-15.c
 * @brief Лабораторная работа 1. Задание 3 (Вариант 15).
 * Расчет энергии, необходимой для плавления льда массой m при t = -10 C.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Считывает вещественное число с клавиатуры с проверкой правильности
 * @return Считанное значение массы типа double (> 0)
 */
double get_double();

/**
 * @brief Вычисляет количество теплоты для нагрева льда до 0 C
 * @param m Масса льда в кг
 * @param c_ice Удельная теплоемкость льда
 * @param t_start Начальная температура
 * @param t_melt Температура плавления льда
 * @return Теплота нагрева Q1 в Джоулях
 */
double get_heating_energy(const double m, const double c_ice, const double t_start, const double t_melt);

/**
 * @brief Вычисляет количество теплоты для фазового перехода (плавления) льда
 * @param m Масса льда в кг
 * @param lambda_ice Удельная теплота плавления льда
 * @return Теплота плавления Q2 в Джоулях
 */
double get_melting_energy(const double m, const double lambda_ice);

/**
 * @brief Вычисляет суммарную энергию, нужную для полного плавления
 * @param m Масса льда в кг
 * @param c_ice Удельная теплоемкость льда
 * @param lambda_ice Удельная теплота плавления льда
 * @param t_start Начальная температура
 * @param t_melt Температура плавления льда
 * @return Суммарная энергия Q в Джоулях
 */
double get_total_energy(const double m, const double c_ice, const double lambda_ice, const double t_start, const double t_melt);

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении программы
 */
int main()
{
    // Выключение буферизации, чтобы текст пояснение отображался до ввода значений
    setbuf(stdout, NULL);

    // Физические константы
    const double c_ice = 2100.0;       // Удельная теплоемкость льда, Дж/(кг * C)
    const double lambda_ice = 3.3e5;   // Удельная теплота плавления льда, Дж/кг (330 000)
    const double t_start = -10.0;      // Начальная температура, C
    const double t_melt = 0.0;         // Температура плавления льда, C

    // Запрос ввода массы
    printf("Введите массу куска льда m (в кг): ");
    fflush(stdout);
    const double m = get_double();

    // Расчет и вывод суммарной энергии
    const double q_total = get_total_energy(m, c_ice, lambda_ice, t_start, t_melt);

    printf("\nРезультаты расчетов:\n");
    printf("Затраченная энергия Q = %.2f Дж\n", q_total);
    printf("В килоджоулях: Q = %.2f кДж\n", q_total / 1000.0);

    return 0;
}

double get_double()
{
    double val = 0.0;
    // Масса не может быть строкой, нулем или отрицательной
    if (scanf("%lf", &val) != 1 || val <= 0.0)
    {
        printf("Масса должна быть числом больше 0\n");
        exit(1);
    }
    return val;
}

double get_heating_energy(const double m, const double c_ice, const double t_start, const double t_melt)
{
    return c_ice * m * (t_melt - t_start);
}

double get_melting_energy(const double m, const double lambda_ice)
{
    return lambda_ice * m;
}

double get_total_energy(const double m, const double c_ice, const double lambda_ice, const double t_start, const double t_melt)
{
    return get_heating_energy(m, c_ice, t_start, t_melt) + get_melting_energy(m, lambda_ice);
}
