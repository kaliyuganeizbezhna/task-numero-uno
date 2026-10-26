/**
 * @file 2-3-15.c
 * @brief Лабораторная работа 2. Задание 3 (Вариант 15).
 * Разветвленный алгоритм обработки трех действительных чисел:
 * удвоить числа, если a < b < c, иначе заменить их абсолютными значениями.
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
 * @brief Проверка условия строгого возрастания a < b < c
 * @param a Первое число
 * @param b Второе число
 * @param c Третье число
 * @return 1 если условие выполняется, 0 если нет
 */
int is_strictly_increasing(const double a, const double b, const double c);

/**
 * @brief Обработка тройки чисел по правилу варианта 15
 * @param a Указатель на первое число
 * @param b Указатель на второе число
 * @param c Указатель на третье число
 */
void process_numbers(double* a, double* b, double* c);

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении
 */
int main()
{
    // Выключение буферизации под шиндовс для нормального вывода
    setbuf(stdout, NULL);

    printf("Обработка трех чисел a, b, c по условию:\n");
    printf("Если a < b < c -> удваиваем числа.\n");
    printf("Иначе -> заменяем каждое число его модулем |x|.\n\n");

    // Ввод трех действительных чисел
    double a = get_double("Введите число a: ");
    double b = get_double("Введите число b: ");
    double c = get_double("Введите число c: ");

    // Вывод исходных данных
    printf("\nИсходные значения: a = %.4f, b = %.4f, c = %.4f\n", a, b, c);

    // Обработка тройки чисел
    process_numbers(&a, &b, &c);

    // Вывод полученных результатов
    printf("Результат обработки: a = %.4f, b = %.4f, c = %.4f\n", a, b, c);

    return 0;
}

double get_double(const char* prompt)
{
    double val = 0.0;
    printf("%s", prompt);
    fflush(stdout);

    // Проверка, что введено вещественное число
    if (scanf("%lf", &val) != 1)
    {
        printf("Ошибка: введено некорректное вещественное число.\n");
        exit(1);
    }
    return val;
}

int is_strictly_increasing(const double a, const double b, const double c)
{
    return (a < b && b < c);
}

void process_numbers(double* a, double* b, double* c)
{
    // Проверка строгого возрастания
    if (is_strictly_increasing(*a, *b, *c))
    {
        printf("Условие a < b < c выполнено: удваиваем значения.\n");
        *a *= 2.0;
        *b *= 2.0;
        *c *= 2.0;
    }
    else
    {
        printf("Условие a < b < c не выполнено: заменяем значения их модулями.\n");
        *a = fabs(*a);
        *b = fabs(*b);
        *c = fabs(*c);
    }
}
