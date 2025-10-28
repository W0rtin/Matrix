#pragma once
#include <iostream>
#include "matrix_io.hpp"  // for clear_t (if you want to use it here)

/*
 * create_matrix
 * Выделяет динамическую матрицу размера rows x cols.
 * Возвращает указатель на массив указателей int**:
 *   m[i] указывает на строку из cols элементов.
 * Строки инициализируются нулями.
 * Важно: память нужно потом освободить через free_matrix(m, rows).
 */
inline int** create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return nullptr;
    }

    int** m = new int*[rows];
    for (int i = 0; i < rows; i++) {
        m[i] = new int[cols]{};
    }
    return m;
}


/*
 * free_matrix
 * Освобождает память, выделенную в create_matrix.
 * rows — то же количество строк, что передавали в create_matrix.
 */
inline void free_matrix(int** a, int rows) {
    if (!a) return;
    for (int i = 0; i < rows; ++i) {
        delete[] a[i];
    }
    delete[] a;
}


/*
 * sum_matrix
 * Создаёт и возвращает новую матрицу result = m1 + m2 размером rows x cols.
 * Память под result выделяется через create_matrix.
 * ВЫЗЫВАЮЩИЙ обязан вызвать free_matrix(result, rows), когда результат больше не нужен.
 * Если вход некорректен — возвращает nullptr.
 */
inline int** sum_matrix(int** m1, int** m2, int rows, int cols) {
    if (!m1 || !m2 || rows <= 0 || cols <= 0) {
        return nullptr;
    }

    int** result = create_matrix(rows, cols);
    if (!result) return nullptr;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }

    return result;
}


/*
 * sub_matrix
 * Создаёт и возвращает новую матрицу result = m1 - m2 размером rows x cols.
 * Аналогично sum_matrix: вызывающий код обязан потом вызвать free_matrix(result, rows).
 * Если вход некорректен — возвращает nullptr.
 */
inline int** sub_matrix(int** m1, int** m2, int rows, int cols) {
    if (!m1 || !m2 || rows <= 0 || cols <= 0) {
        return nullptr;
    }

    int** result = create_matrix(rows, cols);
    if (!result) return nullptr;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = m1[i][j] - m2[i][j];
        }
    }

    return result;
}
