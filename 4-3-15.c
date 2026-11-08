/**
 * @file 4-3-15.c
 * @brief Лабораторная работа 4. Задание 3 (Вариант 15).
 * Обработка двумерного массива (матрицы) целых чисел:
 * 1. Замена максимального элемента в каждой строке на номер столбца, в котором он находится.
 * 2. Поиск глобального минимума матрицы и вставка после каждой строки, где он встречается,
 *    новой строки со значениями: 2, 4, 6, 8, ... (арифметическая прогрессия).
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_INITIAL_ROWS 50
#define MAX_INITIAL_COLS 50
#define MIN_RANDOM_VAL -1000
#define MAX_RANDOM_VAL 1000

/**
 * @brief Способ заполнения матрицы
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
 * @brief Считывание размерности матрицы с проверкой диапазона
 * @param prompt Текст подсказки
 * @param max_limit Верхняя граница
 * @return Размерность (число строк или столбцов)
 */
int get_dimension(const char* prompt, const int max_limit);

/**
 * @brief Считывание режима заполнения матрицы
 * @return Выбранный режим (тип FillMode)
 */
FillMode get_fill_mode();

/**
 * @brief Заполнение матрицы значениями с клавиатуры
 * @param mat Двумерный массив
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void fill_manual(int mat[MAX_ROWS][MAX_COLS], const int rows, const int cols);

/**
 * @brief Заполнение матрицы случайными числами из диапазона [-1000; 1000]
 * @param mat Двумерный массив
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void fill_random(int mat[MAX_ROWS][MAX_COLS], const int rows, const int cols);

/**
 * @brief Вывод матрицы на экран в виде таблицы с выравниванием колонок
 * @param mat Двумерный массив
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void print_matrix(int mat[MAX_ROWS][MAX_COLS], const int rows, const int cols);

/**
 * @brief Замена максимального элемента в каждой строке на номер столбца (1-based)
 * @param mat Двумерный массив
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void replace_row_max_with_col_number(int mat[MAX_ROWS][MAX_COLS], const int rows, const int cols);

/**
 * @brief Поиск глобального минимума матрицы
 * @param mat Двумерный массив
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Значение наименьшего элемента матрицы
 */
int find_matrix_min(int mat[MAX_ROWS][MAX_COLS], const int rows, const int cols);

/**
 * @brief Вставка строки с прогрессией (2, 4, 6...) после каждой строки, содержащей минимум
 * @param mat Двумерный массив
 * @param rows Указатель на количество строк (будет увеличиваться при вставках)
 * @param cols Количество столбцов
 * @param min_val Значение глобального минимума
 * @return Количество вставленных строк
 */
int insert_progression_after_min_rows(int mat[MAX_ROWS][MAX_COLS], int* rows, const int cols, const int min_val);

int main()
{
    setbuf(stdout, NULL);
    srand((unsigned int)time(NULL));

    int mat[MAX_ROWS][MAX_COLS];
    int rows = get_dimension("Введите число строк матрицы (от 1 до 50): ", MAX_INITIAL_ROWS);
    const int cols = get_dimension("Введите число столбцов матрицы (от 1 до 50): ", MAX_INITIAL_COLS);
    const FillMode mode = get_fill_mode();

    if (mode == MODE_MANUAL)
    {
        fill_manual(mat, rows, cols);
    }
    else
    {
        fill_random(mat, rows, cols);
    }

    printf("\nИсходная матрица (%d x %d):\n", rows, cols);
    print_matrix(mat, rows, cols);

    printf("\n1. Замена максимального элемента в каждой строке на номер столбца (1..%d):\n", cols);
    replace_row_max_with_col_number(mat, rows, cols);
    printf("Матрица после замены максимумов:\n");
    print_matrix(mat, rows, cols);

    const int min_val = find_matrix_min(mat, rows, cols);
    printf("\n2. Поиск глобального минимума и вставка прогрессии:\n");
    printf("Глобальный минимум матрицы: %d\n", min_val);

    const int inserted_rows = insert_progression_after_min_rows(mat, &rows, cols, min_val);
    printf("Количество вставленных строк: %d\n", inserted_rows);
    printf("Итоговая матрица (%d x %d):\n", rows, cols);
    print_matrix(mat, rows, cols);

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

int get_dimension(const char* prompt, const int max_limit)
{
    if (prompt == NULL)
    {
        exit(1);
    }

    int val = 0;
    printf("%s", prompt);

    if (scanf("%d", &val) != 1 || val < 1 || val > max_limit)
    {
        printf("Ошибка: размерность должна быть от 1 до %d.\n", max_limit);
        exit(1);
    }
    return val;
}

FillMode get_fill_mode()
{
    int choice = 0;
    printf("Выберите способ заполнения матрицы:\n");
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

void fill_manual(int mat[MAX_ROWS][MAX_COLS], const int rows, const int cols)
{
    if (mat == NULL)
    {
        exit(1);
    }

    printf("Введите элементы матрицы по строкам (%d строк по %d чисел):\n", rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (scanf("%d", &mat[i][j]) != 1)
            {
                printf("Ошибка при вводе элемента [%d][%d].\n", i, j);
                exit(1);
            }
        }
    }
}

void fill_random(int mat[MAX_ROWS][MAX_COLS], const int rows, const int cols)
{
    if (mat == NULL)
    {
        exit(1);
    }

    const int span = MAX_RANDOM_VAL - MIN_RANDOM_VAL + 1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = MIN_RANDOM_VAL + rand() % span;
        }
    }
}

void print_matrix(int mat[MAX_ROWS][MAX_COLS], const int rows, const int cols)
{
    if (mat == NULL)
    {
        exit(1);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%7d ", mat[i][j]);
        }
        printf("\n");
    }
}

void replace_row_max_with_col_number(int mat[MAX_ROWS][MAX_COLS], const int rows, const int cols)
{
    if (mat == NULL)
    {
        exit(1);
    }

    for (int i = 0; i < rows; i++)
    {
        int max_val = mat[i][0];
        int max_col = 0;

        for (int j = 1; j < cols; j++)
        {
            if (mat[i][j] > max_val)
            {
                max_val = mat[i][j];
                max_col = j;
            }
        }

        mat[i][max_col] = max_col + 1;
    }
}

int find_matrix_min(int mat[MAX_ROWS][MAX_COLS], const int rows, const int cols)
{
    if (mat == NULL)
    {
        exit(1);
    }

    int min_val = mat[0][0];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (mat[i][j] < min_val)
            {
                min_val = mat[i][j];
            }
        }
    }
    return min_val;
}

int insert_progression_after_min_rows(int mat[MAX_ROWS][MAX_COLS], int* rows, const int cols, const int min_val)
{
    if (mat == NULL || rows == NULL)
    {
        exit(1);
    }

    int inserted = 0;
    for (int i = 0; i < *rows; i++)
    {
        int contains_min = 0;
        for (int j = 0; j < cols; j++)
        {
            if (mat[i][j] == min_val)
            {
                contains_min = 1;
                break;
            }
        }

        if (contains_min)
        {
            if (*rows >= MAX_ROWS)
            {
                printf("Предупреждение: достигнут лимит строк матрицы.\n");
                break;
            }

            for (int r = *rows; r > i + 1; r--)
            {
                for (int c = 0; c < cols; c++)
                {
                    mat[r][c] = mat[r - 1][c];
                }
            }

            for (int c = 0; c < cols; c++)
            {
                mat[i + 1][c] = 2 * (c + 1);
            }

            (*rows)++;
            inserted++;
            i++;
        }
    }

    return inserted;
}
