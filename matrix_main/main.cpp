#include <iostream>
#include "matrix_io.hpp"
#include "matrix_read.hpp"
#include "matrix_action.hpp"

int main() {
    clear_t();

    int rows = 0;
    int cols = 0;

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
                std::cout << "Введите размеры матриц:\n";

                std::cout << "rows = ";
                if (!dig_esc(rows)) {
                    std::cout << "\nОтмена ввода размеров.\n";
                    std::cout << "\nНажмите любую клавишу...\n";
                    getch();
                    break;
                }

                std::cout << "cols = ";
                if (!dig_esc(cols)) {
                    std::cout << "\nОтмена ввода размеров.\n";
                    std::cout << "\nНажмите любую клавишу...\n";
                    getch();
                    break;
                }

                if (rows <= 0 || cols <= 0) {
                    std::cout << "Размеры должны быть > 0.\n";
                    std::cout << "\nНажмите любую клавишу...\n";
                    getch();
                    break;
                }

                // Если у нас уже были матрицы старого размера — освободим
                if (m1) {
                    free_matrix(m1, rows);
                    m1 = nullptr;
                }
                if (m2) {
                    free_matrix(m2, rows);
                    m2 = nullptr;
                }

                // Выделяем новые
                m1 = create_matrix(rows, cols);
                m2 = create_matrix(rows, cols);

                if (!m1 || !m2) {
                    std::cout << "Ошибка: не удалось выделить память.\n";
                    // если одна создалась, а другая нет — подчистим
                    if (m1) { free_matrix(m1, rows); m1 = nullptr; }
                    if (m2) { free_matrix(m2, rows); m2 = nullptr; }
                } else {
                    std::cout << "Созданы две матрицы " << rows << "x" << cols << " и заполнены нулями.\n";
                }

                std::cout << "\nНажмите любую клавишу...\n";
                getch();
                break;
            }

            // --- Пункт 2: заполнить матрицу 1 ---
            case '2': {
                if (!m1) {
                    std::cout << "Сначала задайте размеры (пункт 1).\n";
                } else {
                    std::cout
                        << "Заполнение матрицы 1 (" << rows << "x" << cols << ")\n"
                        << "Подсказка: Esc в любой момент = отмена.\n\n";
                    if (!fill(m1, rows, cols)) {
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
                        << "Заполнение матрицы 2 (" << rows << "x" << cols << ")\n"
                        << "Подсказка: Esc в любой момент = отмена.\n\n";
                    if (!fill(m2, rows, cols)) {
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
                    for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                            std::cout << m1[i][j] << ' ';
                        }
                        std::cout << '\n';
                    }

                    std::cout << "\nМатрица 2:\n";
                    for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
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
                    << "Esc - Назад\n";

                int subcmd = getch();
                if (subcmd == 27) {
                    break; // назад в главное меню
                }

                clear_t();

                if (subcmd == '1') {
                    int** m_sum = sum_matrix(m1, m2, rows, cols);
                    if (!m_sum) {
                        std::cout << "Ошибка при сложении матриц.\n";
                    } else {
                        std::cout << "m1 + m2:\n";
                        for (int i = 0; i < rows; i++) {
                            for (int j = 0; j < cols; j++) {
                                std::cout << m_sum[i][j] << ' ';
                            }
                            std::cout << '\n';
                        }
                        free_matrix(m_sum, rows);
                    }
                } else if (subcmd == '2') {
                    int** m_diff = sub_matrix(m1, m2, rows, cols);
                    if (!m_diff) {
                        std::cout << "Ошибка при вычитании матриц.\n";
                    } else {
                        std::cout << "m1 - m2:\n";
                        for (int i = 0; i < rows; i++) {
                            for (int j = 0; j < cols; j++) {
                                std::cout << m_diff[i][j] << ' ';
                            }
                            std::cout << '\n';
                        }
                        free_matrix(m_diff, rows);
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
    if (m1) {
        free_matrix(m1, rows);
        m1 = nullptr;
    }
    if (m2) {
        free_matrix(m2, rows);
        m2 = nullptr;
    }

    clear_t();
    std::cout << "Выход.\n";
    return 0;
}
