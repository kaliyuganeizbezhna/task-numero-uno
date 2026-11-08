/**
 * @file 4-1-15.c
 * @brief Лабораторная работа 4. Задание 1 (Вариант 15).
 * Обработка одномерного массива целых чисел:
 * 1. Сумма положительных двузначных элементов.
 * 2. Умножение всех четных положительных элементов на последний элемент.
 * 3. Поиск номера первой пары соседних элементов с разными знаками и суммой меньше S.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100
#define MIN_RANDOM_VAL -1000
#define MAX_RANDOM_VAL 1000

/**
 * @brief Способ заполнения массива
 */
typedef enum
{
    MODE_MANUAL = 1,
    MODE_RANDOM = 2
} FillMode;

/**
 * @brief Считывание целого числа с проверкой ввода
 * @param prompt Текст подсказки
 * @return Считанное число
 */
int get_int(const char* prompt);

/**
 * @brief Считывание размера массива в диапазоне [1; MAX_SIZE]
 * @return Размер массива n
 */
int get_array_size();

/**
 * @brief Считывание режима заполнения
 * @return Выбранный режим (тип FillMode)
 */
FillMode get_fill_mode();

/**
 * @brief Заполнение массива значениями с клавиатуры
 * @param arr Массив
 * @param n Количество элементов
 */
void fill_manual(int arr[], const int n);

/**
 * @brief Заполнение массива случайными числами из диапазона [-1000; 1000]
 * @param arr Массив
 * @param n Количество элементов
 */
void fill_random(int arr[], const int n);

/**
 * @brief Вывод массива на экран в одну строку
 * @param arr Массив
 * @param n Количество элементов
 */
void print_array(const int arr[], const int n);

/**
 * @brief Поиск суммы положительных элементов, состоящих из двух цифр
 * @param arr Массив
 * @param n Количество элементов
 * @return Сумма двузначных положительных чисел
 */
int get_sum_two_digit_positives(const int arr[], const int n);

/**
 * @brief Умножение всех четных положительных элементов на последний элемент массива
 * @param arr Массив
 * @param n Количество элементов
 */
void multiply_even_positives(int arr[], const int n);

/**
 * @brief Поиск первой пары соседних элементов с разными знаками и суммой меньше заданного числа
 * @param arr Массив
 * @param n Количество элементов
 * @param target_sum Пороговая сумма S
 * @return Индекс первого элемента найденной пары (-1 если пара не найдена)
 */
int find_diff_sign_pair(const int arr[], const int n, const int target_sum);

int main()
{
    setbuf(stdout, NULL);
    srand((unsigned int)time(NULL));

    int arr[MAX_SIZE];
    const int n = get_array_size();
    const FillMode mode = get_fill_mode();

    if (mode == MODE_MANUAL)
    {
        fill_manual(arr, n);
    }
    else
    {
        fill_random(arr, n);
    }

    printf("\nИсходный массив:\n");
    print_array(arr, n);

    const int sum_2digit = get_sum_two_digit_positives(arr, n);
    printf("\n1. Сумма положительных двузначных элементов [10; 99]: %d\n", sum_2digit);

    printf("\n2. Умножение четных положительных элементов на последний элемент (%d):\n", arr[n - 1]);
    multiply_even_positives(arr, n);
    printf("Массив после преобразования:\n");
    print_array(arr, n);

    printf("\n3. Поиск соседней пары с разными знаками и суммой < S:\n");
    const int target_s = get_int("Введите пороговое число S: ");
    const int pair_idx = find_diff_sign_pair(arr, n, target_s);
    if (pair_idx != -1)
    {
        printf("Найдена пара на позициях %d и %d (значения: %d и %d, сумма: %d < %d)\n",
               pair_idx + 1, pair_idx + 2,
               arr[pair_idx], arr[pair_idx + 1],
               arr[pair_idx] + arr[pair_idx + 1], target_s);
    }
    else
    {
        printf("Подходящая пара элементов с разными знаками не найдена.\n");
    }

    return 0;
}

int get_int(const char* prompt)
{
    if (prompt == NULL)
    {
        exit(1);
    }

    int val = 0;
    printf("%s", prompt);

    if (scanf("%d", &val) != 1)
    {
        printf("Ошибка: необходимо ввести целое число.\n");
        exit(1);
    }
    return val;
}

int get_array_size()
{
    int n = 0;
    printf("Введите размер массива n (от 1 до %d): ", MAX_SIZE);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SIZE)
    {
        printf("Ошибка: некорректный размер массива.\n");
        exit(1);
    }
    return n;
}

FillMode get_fill_mode()
{
    int choice = 0;
    printf("Выберите способ заполнения массива:\n");
    printf("%d - Ввод вручную с клавиатуры\n", MODE_MANUAL);
    printf("%d - Случайными числами [-1000; 1000]\n", MODE_RANDOM);
    printf("Ваш выбор: ");

    if (scanf("%d", &choice) != 1 || (choice != MODE_MANUAL && choice != MODE_RANDOM))
    {
        printf("Ошибка: неверный пункт меню.\n");
        exit(1);
    }
    return (FillMode)choice;
}

void fill_manual(int arr[], const int n)
{
    if (arr == NULL)
    {
        exit(1);
    }

    printf("Введите %d целых чисел:\n", n);
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Ошибка при вводе элемента.\n");
            exit(1);
        }
    }
}

void fill_random(int arr[], const int n)
{
    if (arr == NULL)
    {
        exit(1);
    }

    const int span = MAX_RANDOM_VAL - MIN_RANDOM_VAL + 1;
    for (int i = 0; i < n; i++)
    {
        arr[i] = MIN_RANDOM_VAL + rand() % span;
    }
}

void print_array(const int arr[], const int n)
{
    if (arr == NULL)
    {
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int get_sum_two_digit_positives(const int arr[], const int n)
{
    if (arr == NULL)
    {
        exit(1);
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] >= 10 && arr[i] <= 99)
        {
            sum += arr[i];
        }
    }
    return sum;
}

void multiply_even_positives(int arr[], const int n)
{
    if (arr == NULL)
    {
        exit(1);
    }

    const int last_element = arr[n - 1];

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > 0 && arr[i] % 2 == 0)
        {
            arr[i] *= last_element;
        }
    }
}

int find_diff_sign_pair(const int arr[], const int n, const int target_sum)
{
    if (arr == NULL)
    {
        exit(1);
    }

    for (int i = 0; i < n - 1; i++)
    {
        const int diff_signs = (arr[i] > 0 && arr[i + 1] < 0) || (arr[i] < 0 && arr[i + 1] > 0);
        if (diff_signs && (arr[i] + arr[i + 1] < target_sum))
        {
            return i;
        }
    }

    return -1;
}
