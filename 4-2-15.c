/**
 * @file 4-2-15.c
 * @brief Лабораторная работа 4. Задание 2 (Вариант 15).
 * Обработка одномерного массива целых чисел (модификация и вставка):
 * 1. Замена первого элемента, кратного 5, на 0.
 * 2. Вставка числа K после всех нечетных элементов, начинающихся на цифру K.
 * 3. Формирование нового массива M из массива P:
 *    M[0] = 0, M[n - 1] = 0, M[i] = -P[i] * (i + 1).
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CAPACITY 200
#define MAX_INITIAL_SIZE 100
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
 * @brief Считывание начального размера массива в диапазоне [1; MAX_INITIAL_SIZE]
 * @return Начальный размер массива n
 */
int get_initial_array_size();

/**
 * @brief Считывание цифры K в диапазоне [1; 9]
 * @return Значение K
 */
int get_k_digit();

/**
 * @brief Считывание режима заполнения массива
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
 * @brief Замена первого элемента, кратного 5, на значение 0
 * @param arr Массив
 * @param n Количество элементов
 * @return Индекс замененного элемента или -1, если такой элемент отсутствует
 */
int replace_first_divisible_by_5(int arr[], const int n);

/**
 * @brief Получение первой цифры числа (по абсолютному значению)
 * @param x Число
 * @return Первая цифра числа
 */
int get_first_digit(const int x);

/**
 * @brief Вставка заданного числа K после всех нечетных элементов, начинающихся на цифру K
 * @param arr Массив
 * @param n Указатель на текущее количество элементов в массиве (будет увеличено)
 * @param k Вставляемое число
 * @return Количество произведенных вставок
 */
int insert_k_after_matching_odds(int arr[], int* n, const int k);

/**
 * @brief Формирование массива M из массива P по заданному правилу
 * @param p Исходный массив P
 * @param m Результирующий массив M
 * @param n Количество элементов
 */
void build_m_from_p(const int p[], int m[], const int n);

int main()
{
    setbuf(stdout, NULL);
    srand((unsigned int)time(NULL));

    int arr[MAX_CAPACITY];
    int n = get_initial_array_size();
    const FillMode mode = get_fill_mode();

    if (mode == MODE_MANUAL)
    {
        fill_manual(arr, n);
    }
    else
    {
        fill_random(arr, n);
    }

    printf("\nИсходный массив P:\n");
    print_array(arr, n);

    printf("\n1. Замена первого элемента, кратного 5, на 0:\n");
    const int idx_replaced = replace_first_divisible_by_5(arr, n);
    if (idx_replaced != -1)
    {
        printf("Элемент на позиции %d заменен на 0.\n", idx_replaced + 1);
    }
    else
    {
        printf("Элемент, кратный 5, не найден.\n");
    }
    printf("Массив после пункта 1:\n");
    print_array(arr, n);

    printf("\n2. Вставка числа K после нечетных элементов с первой цифрой K:\n");
    const int k = get_k_digit();
    const int inserted_count = insert_k_after_matching_odds(arr, &n, k);
    printf("Количество вставок числа %d: %d\n", k, inserted_count);
    printf("Массив после вставки (новый размер n = %d):\n", n);
    print_array(arr, n);

    printf("\n3. Формирование массива M из массива P:\n");
    int m[MAX_CAPACITY];
    build_m_from_p(arr, m, n);
    printf("Сформированный массив M:\n");
    print_array(m, n);

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

int get_initial_array_size()
{
    int n = 0;
    printf("Введите начальный размер массива n (от 1 до %d): ", MAX_INITIAL_SIZE);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_INITIAL_SIZE)
    {
        printf("Ошибка: некорректный размер массива.\n");
        exit(1);
    }
    return n;
}

int get_k_digit()
{
    int k = 0;
    printf("Введите цифру K (от 1 до 9): ");

    if (scanf("%d", &k) != 1 || k < 1 || k > 9)
    {
        printf("Ошибка: K должно быть цифрой от 1 до 9.\n");
        exit(1);
    }
    return k;
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

int replace_first_divisible_by_5(int arr[], const int n)
{
    if (arr == NULL)
    {
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 5 == 0)
        {
            arr[i] = 0;
            return i;
        }
    }
    return -1;
}

int get_first_digit(const int x)
{
    int val = abs(x);
    while (val >= 10)
    {
        val /= 10;
    }
    return val;
}

int insert_k_after_matching_odds(int arr[], int* n, const int k)
{
    if (arr == NULL || n == NULL)
    {
        exit(1);
    }

    int inserted = 0;
    for (int i = 0; i < *n; i++)
    {
        if ((arr[i] % 2 != 0) && (get_first_digit(arr[i]) == k))
        {
            if (*n >= MAX_CAPACITY)
            {
                printf("Предупреждение: достигнут лимит емкости массива.\n");
                break;
            }

            for (int j = *n; j > i + 1; j--)
            {
                arr[j] = arr[j - 1];
            }

            arr[i + 1] = k;
            (*n)++;
            inserted++;
            i++;
        }
    }

    return inserted;
}

void build_m_from_p(const int p[], int m[], const int n)
{
    if (p == NULL || m == NULL)
    {
        exit(1);
    }

    if (n <= 0)
    {
        return;
    }

    m[0] = 0;
    if (n > 1)
    {
        m[n - 1] = 0;
    }

    for (int i = 1; i < n - 1; i++)
    {
        m[i] = -p[i] * (i + 1);
    }
}
