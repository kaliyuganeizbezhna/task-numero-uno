/**
 * @file 1-3-15.c
 * @brief Лабораторная работа 1. Задание 3 (Вариант 15).
 * Расчет энергии, необходимой для плавления льда массой m при t = -10 C.
 */

#include <stdio.h>
#include <stdlib.h>

// Физические константы
const double C_ICE = 2100.0;       // Удельная теплоемкость льда, Дж/(кг * C)
const double LAMBDA_ICE = 3.3e5;   // Удельная теплота плавления льда, Дж/кг (330 000)
const double T_START = -10.0;      // Начальная температура, C
const double T_MELT = 0.0;         // Температура плавления льда, C

/**
 * @brief Считывает вещественное число с клавиатуры с проверкой правильности
 * @return Считанное значение массы типа double (> 0)
 */
double get_double();

/**
 * @brief Вычисляет количество теплоты для нагрева льда до 0 C
 * @param m Масса льда в кг
 * @return Теплота нагрева Q1 в Джоулях
 */
double get_heating_energy(const double m);

/**
 * @brief Вычисляет количество теплоты для фазового перехода (плавления) льда
 * @param m Масса льда в кг
 * @return Теплота плавления Q2 в Джоулях
 */
double get_melting_energy(const double m);

/**
 * @brief Вычисляет суммарную энергию, нужную для полного плавления
 * @param m Масса льда в кг
 * @return Суммарная энергия Q в Джоулях
 */
double get_total_energy(const double m);

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении программы
 */
int main()
{
    // Выключение буферизации, чтобы текст пояснение отображался до ввода значений
    setbuf(stdout, NULL);

    // Запрос ввода массы
    printf("Введите массу куска льда m (в кг): ");
    fflush(stdout);
    const double m = get_double();

    // Расчет и вывод суммарной энергии
    const double q_total = get_total_energy(m);

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

double get_heating_energy(const double m)
{
    return C_ICE * m * (T_MELT - T_START);
}

double get_melting_energy(const double m)
{
    return LAMBDA_ICE * m;
}

double get_total_energy(const double m)
{
    return get_heating_energy(m) + get_melting_energy(m);
}