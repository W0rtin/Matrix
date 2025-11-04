#include <iostream>
#include "matrix_io.hpp"
#include "matrix_read.hpp"
#include "matrix_action.hpp"

int main() {
    clear_t();

    int rows1 = 0;
    int cols1 = 0;
    int rows2 = 0;
    int cols2 = 0;

    int** m1 = nullptr;
    int** m2 = nullptr;

    std::cout << "Нажмите любую клавишу для старта, Esc - выход:\n";
    if (getch() == 27) {
        return 0;
    }

    int cmd = 0;
    while (cmd != 27) {
        // 1. Показать меню
        clear_t();
        std::cout
            << "\nМеню (жми клавишу, Enter не нужен):\n"
            << "1 - Задать размеры матриц\n"
            << "2 - Заполнить матрицу 1\n"
            << "3 - Заполнить матрицу 2\n"
            << "4 - Показать матрицы\n"
            << "5 - Операции над матрицами\n"
            << "Esc - Выход\n";

        // 2. Ждём выбор
        cmd = getch();
        if (cmd == 27) break; // Esc = завершить

        clear_t();

        switch (cmd) {
            // --- Пункт 1: задать размеры и выделить память ---
            case '1': {
                set_matrices_size(m1, rows1, cols1, m2, rows2, cols2);
                break;
            }
            
            // --- Пункт 2: заполнить матрицу 1 ---
            case '2': {
                if (!m1) {
                    std::cout << "Сначала задайте размеры (пункт 1).\n";
                } else {
                    std::cout
                        << "Заполнение матрицы 1 (" << rows1 << "x" << cols1 << ")\n"
                        << "Подсказка: Esc в любой момент = отмена.\n\n";
                    if (!fill(m1, rows1, cols1)) {
                        std::cout << "\nЗаполнение матрицы 1 прервано.\n";
                    } else {
                        std::cout << "\nМатрица 1 заполнена.\n";
                    }
                }

                std::cout << "\nНажмите любую клавишу...\n";
                getch();
                break;
            }

            // --- Пункт 3: заполнить матрицу 2 ---
            case '3': {
                if (!m2) {
                    std::cout << "Сначала задайте размеры (пункт 1).\n";
                } else {
                    std::cout
                        << "Заполнение матрицы 2 (" << rows2 << "x" << cols2 << ")\n"
                        << "Подсказка: Esc в любой момент = отмена.\n\n";
                    if (!fill(m2, rows2, cols2)) {
                        std::cout << "\nЗаполнение матрицы 2 прервано.\n";
                    } else {
                        std::cout << "\nМатрица 2 заполнена.\n";
                    }
                }

                std::cout << "\nНажмите любую клавишу...\n";
                getch();
                break;
            }

            // --- Пункт 4: показать обе матрицы ---
            case '4': {
                if (!m1 || !m2) {
                    std::cout << "Матрицы ещё не готовы для вывода.\n";
                } else {
                    std::cout << "Матрица 1:\n";
                    for (int i = 0; i < rows1; i++) {
                        for (int j = 0; j < cols1; j++) {
                            std::cout << m1[i][j] << ' ';
                        }
                        std::cout << '\n';
                    }

                    std::cout << "\nМатрица 2:\n";
                    for (int i = 0; i < rows2; i++) {
                        for (int j = 0; j < cols2; j++) {
                            std::cout << m2[i][j] << ' ';
                        }
                        std::cout << '\n';
                    }
                }

                std::cout << "\nНажмите любую клавишу...\n";
                getch();
                break;
            }

            // --- Пункт 5: операции ---
            case '5': {
                if (!m1 || !m2) {
                    std::cout << "Матрицы ещё не заданы/не заполнены.\n";
                    std::cout << "\nНажмите любую клавишу...\n";
                    getch();
                    break;
                }

                // подменю
                clear_t();
                std::cout
                    << "Операции с матрицами:\n"
                    << "1 - m1 + m2\n"
                    << "2 - m1 - m2\n"
                    << "3 - m1 * m2\n"
                    << "Esc - Назад\n";

                int subcmd = getch();
                if (subcmd == 27) {
                    break; // назад в главное меню
                }

                clear_t();

                if (subcmd == '1') { //Сложение m1+m2
                    int** m_sum = sum_matrix(m1, rows1, cols1, m2, rows2, cols2);
                    if (!m_sum) {
                        std::cout << "Ошибка при сложении матриц (возможно, размеры не совпадают).\n";
                    } else {
                        std::cout << "m1 + m2:\n";
                        for (int i = 0; i < rows1; i++) {
                            for (int j = 0; j < cols1; j++) {
                                std::cout << m_sum[i][j] << ' ';
                            }
                            std::cout << '\n';
                        }
                        free_matrix(m_sum, rows1);
                    }
                } else if (subcmd == '2') { //Вычитание матриц m1-m2
                    int** m_diff = sub_matrix(m1, rows1, cols1, m2, rows2, cols2);
                    if (!m_diff) {
                        std::cout << "Ошибка при вычитании матриц (возможно, размеры не совпадают).\n";
                    } else {
                        std::cout << "m1 - m2:\n";
                        for (int i = 0; i < rows1; i++) {
                            for (int j = 0; j < cols1; j++) {
                                std::cout << m_diff[i][j] << ' ';
                            }
                            std::cout << '\n';
                        }
                        free_matrix(m_diff, rows1);
                    }
                } else if (subcmd == '3') { //Произведение матриц m1 * m2
                    int** mul_m = multiplication_matrix(m1, rows1, cols1, m2, rows2, cols2);
                    if (!mul_m) {
                        std::cout << "Ошибка при произведении матриц (проверьте: cols1 == rows2).\n";
                    } else {
                        std::cout << "m1 * m2:\n";
                        for (int i = 0; i < rows1; i++) {
                            for (int j = 0; j < cols2; j++) {
                                std::cout << mul_m[i][j] << ' ';
                            }
                            std::cout << '\n';
                        }
                        free_matrix(mul_m, rows1);
                    }
                } else {
                    std::cout << "Неизвестная операция.\n";
                }

                std::cout << "\nНажмите любую клавишу...\n";
                getch();
                break;
            }

            // --- Любая другая клавиша ---
            default: {
                std::cout << "Неизвестная команда.\n";
                std::cout << "\nНажмите любую клавишу...\n";
                getch();
                break;
            }
        }
    }

    // Перед выходом — подчистить память
    if (m1 && rows1 > 0) {
        free_matrix(m1, rows1);
        m1 = nullptr;
    }
    if (m2 && rows2 > 0) {
        free_matrix(m2, rows2);
        m2 = nullptr;
    }


    clear_t();
    std::cout << "Выход.\n";
    return 0;
}
