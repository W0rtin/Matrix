#pragma once

#include <iostream>
#include "matrix_io.hpp"
#include "matrix_read.hpp"

// create_matrix
// Создаёт матрицу rows x cols (int**), заполняет нулями.
// ВАЖНО: потом нужно вызвать free_matrix(matrix, rows).
inline int** create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return nullptr;
    }

    int** m = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        m[i] = new int[cols]{};
    }
    return m;
}

// free_matrix
// Освобождает память, выделенную create_matrix.
inline void free_matrix(int** a, int rows) {
    if (!a || rows <= 0) return;
    for (int i = 0; i < rows; ++i) {
        delete[] a[i];
    }
    delete[] a;
}

// sum_matrix
// Поэлементная сумма двух матриц одинакового размера:
// result = m1 + m2, размер rows1 x cols1.
// При ошибке (nullptr, неправильные размеры) возвращает nullptr.
inline int** sum_matrix(
    int** m1, int rows1, int cols1,
    int** m2, int rows2, int cols2
) {
    if (!m1 || !m2 ||
        rows1 <= 0 || cols1 <= 0 ||
        rows2 <= 0 || cols2 <= 0) {
        return nullptr;
    }

    if (rows1 != rows2 || cols1 != cols2) {
        return nullptr;
    }

    int** result = create_matrix(rows1, cols1);
    if (!result) return nullptr;

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }

    return result;
}

// sub_matrix
// Поэлементная разность двух матриц одинакового размера:
// result = m1 - m2, размер rows1 x cols1.
inline int** sub_matrix(
    int** m1, int rows1, int cols1,
    int** m2, int rows2, int cols2
) {
    if (!m1 || !m2 ||
        rows1 <= 0 || cols1 <= 0 ||
        rows2 <= 0 || cols2 <= 0) {
        return nullptr;
    }

    if (rows1 != rows2 || cols1 != cols2) {
        return nullptr;
    }

    int** result = create_matrix(rows1, cols1);
    if (!result) return nullptr;

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            result[i][j] = m1[i][j] - m2[i][j];
        }
    }

    return result;
}

// multiplication_matrix
// Умножение матриц:
//   m1: rows1 x cols1
//   m2: rows2 x cols2
// Условие: cols1 == rows2
// Результат: матрица rows1 x cols2.
// При ошибке возвращает nullptr.
inline int** multiplication_matrix(
    int** m1, int rows1, int cols1,
    int** m2, int rows2, int cols2
) {
    if (!m1 || !m2 ||
        rows1 <= 0 || cols1 <= 0 ||
        rows2 <= 0 || cols2 <= 0) {
        return nullptr;
    }

    if (cols1 != rows2) {
        return nullptr;
    }

    int result_rows = rows1;
    int result_cols = cols2;

    int** result = create_matrix(result_rows, result_cols);
    if (!result) return nullptr;

    for (int i = 0; i < result_rows; ++i) {
        for (int j = 0; j < result_cols; ++j) {
            int sum = 0;
            for (int k = 0; k < cols1; ++k) {
                sum += m1[i][k] * m2[k][j];
            }
            result[i][j] = sum;
        }
    }

    return result;
}

// set_matrices_size
// Задаёт/пересоздаёт размеры обеих матриц.
// Считывает новые размеры для m1 и m2, при необходимости
// освобождает старые матрицы и создаёт новые.
// Возвращает true, если всё ок; false, если отмена/ошибка.
inline bool set_matrices_size(
    int**& m1, int& rows1, int& cols1,
    int**& m2, int& rows2, int& cols2
) {
    int old_rows1 = rows1;
    int old_rows2 = rows2;

    clear_t();
    std::cout << "Задание размеров матриц\n\n";

    int new_rows1 = 0, new_cols1 = 0;
    int new_rows2 = 0, new_cols2 = 0;

    const int MAX_SIZE = 1000;

    // --- размеры матрицы 1 ---
    std::cout << "Матрица 1:\n";

    std::cout << "rows1 = ";
    if (!dig_esc(new_rows1)) {
        std::cout << "\nОтмена ввода размеров.\n";
        std::cout << "\nНажмите любую клавишу...\n";
        getch();
        return false;
    }

    std::cout << "cols1 = ";
    if (!dig_esc(new_cols1)) {
        std::cout << "\nОтмена ввода размеров.\n";
        std::cout << "\nНажмите любую клавишу...\n";
        getch();
        return false;
    }

    if (new_rows1 <= 0 || new_cols1 <= 0 ||
        new_rows1 > MAX_SIZE || new_cols1 > MAX_SIZE) {
        std::cout << "Размеры матрицы 1 должны быть в диапазоне 1.." << MAX_SIZE << ".\n";
        std::cout << "\nНажмите любую клавишу...\n";
        getch();
        return false;
    }

    clear_t();

    // --- размеры матрицы 2 ---
    std::cout << "Матрица 2:\n";

    std::cout << "rows2 = ";
    if (!dig_esc(new_rows2)) {
        std::cout << "\nОтмена ввода размеров.\n";
        std::cout << "\nНажмите любую клавишу...\n";
        getch();
        return false;
    }

    std::cout << "cols2 = ";
    if (!dig_esc(new_cols2)) {
        std::cout << "\nОтмена ввода размеров.\n";
        std::cout << "\nНажмите любую клавишу...\n";
        getch();
        return false;
    }

    if (new_rows2 <= 0 || new_cols2 <= 0 ||
        new_rows2 > MAX_SIZE || new_cols2 > MAX_SIZE) {
        std::cout << "Размеры матрицы 2 должны быть в диапазоне 1.." << MAX_SIZE << ".\n";
        std::cout << "\nНажмите любую клавишу...\n";
        getch();
        return false;
    }

    // Если матрицы уже существуют — спросим подтверждение
    if (m1 || m2) {
        clear_t();
        std::cout
            << "Внимание: матрицы уже существуют.\n"
            << "При изменении размерности все данные будут удалены.\n\n"
            << "Y - пересоздать матрицы\n"
            << "Любая другая клавиша - отмена\n";

        int c = getch();
        if (c != 'y' && c != 'Y') {
            std::cout << "\nОперация отменена. Возврат в меню.\n";
            std::cout << "\nНажмите любую клавишу...\n";
            getch();
            return false;
        }

        if (m1 && old_rows1 > 0) {
            free_matrix(m1, old_rows1);
            m1 = nullptr;
        }
        if (m2 && old_rows2 > 0) {
            free_matrix(m2, old_rows2);
            m2 = nullptr;
        }
    }

    // создаём новые матрицы
    int** new_m1 = create_matrix(new_rows1, new_cols1);
    int** new_m2 = create_matrix(new_rows2, new_cols2);

    if (!new_m1 || !new_m2) {
        std::cout << "Ошибка: не удалось выделить память под новые матрицы.\n";

        if (new_m1) free_matrix(new_m1, new_rows1);
        if (new_m2) free_matrix(new_m2, new_rows2);

        std::cout << "\nНажмите любую клавишу...\n";
        getch();
        return false;
    }

    // применяем новые значения
    m1 = new_m1;
    m2 = new_m2;
    rows1 = new_rows1;
    cols1 = new_cols1;
    rows2 = new_rows2;
    cols2 = new_cols2;

    clear_t();
    std::cout << "Матрица 1: " << rows1 << "x" << cols1 << "\n";
    std::cout << "Матрица 2: " << rows2 << "x" << cols2 << "\n";
    std::cout << "\nМатрицы пересозданы и заполнены нулями.\n";
    std::cout << "\nНажмите любую клавишу...\n";
    getch();

    return true;
}
