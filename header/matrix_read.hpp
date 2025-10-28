#pragma once
#include <iostream>
#include <string>
#include <climits>
#include "matrix_io.hpp"

/*
 * dig_esc
 * Читает целое число с клавиатуры без Enter:
 *  - посимвольно через getch();
 *  - поддерживает Backspace;
 *  - поддерживает '-' в начале;
 *  - завершение по Enter / Space / Tab;
 *  - Esc = отмена ввода -> функция возвращает false.
 *
 * Гарантированно пишет значение в `out`, ограничивая его диапазоном int.
 *
 * Возвращает:
 *   true  - число считано
 *   false - пользователь нажал Esc
 */
inline bool dig_esc(int& out) {
    std::string buf;

    std::cout << "> " << std::flush;

    for (;;) {
        int chr = getch();

        // Esc => отменить ввод
        if (chr == 27) {
            std::cout << "\nОтмена\n";
            return false;
        }

        // Разделитель завершает ввод числа (если уже что-то набрано кроме единственного '-')
        if (chr == ' ' || chr == '\n' || chr == '\t' || chr == '\r') {
            if (!(buf.size() == 1 && buf[0] == '-')) {
                std::cout << '\n';
                break;
            } else {
                continue;
            }
        }

        // Backspace
        if (chr == 8 || chr == 127) {
            if (!buf.empty()) {
                buf.pop_back();
                std::cout << "\b \b" << std::flush;
            }
            continue;
        }

        // Минус можно только в начале
        if (chr == '-' && buf.empty()) {
            buf.push_back('-');
            std::cout << '-' << std::flush;
            continue;
        }

        // Цифры
        if (chr >= '0' && chr <= '9') {
            buf.push_back(static_cast<char>(chr));
            std::cout << static_cast<char>(chr) << std::flush;
            continue;
        }

        // Любой другой символ — просто игнорим
    }

    // конвертация строки buf -> int с защитой по границам
    long long sign = 1;
    size_t idx = 0;

    if (!buf.empty() && buf[0] == '-') {
        sign = -1;
        idx = 1;
    }

    long long val = 0;
    for (; idx < buf.size(); ++idx) {
        val = val * 10 + (buf[idx] - '0');

        // Ограничение сверху/снизу
        if (sign == 1 && val > INT_MAX) {
            val = INT_MAX;
            break;
        } else if (sign == -1 && -val < INT_MIN) {
            val = -(long long)INT_MIN;
            break;
        }
    }

    val *= sign;
    if (val > INT_MAX)  val = INT_MAX;
    if (val < INT_MIN)  val = INT_MIN;

    out = static_cast<int>(val);
    return true;
}


/*
 * fill
 * Заполняет матрицу m[x][y] числами, вводя КАЖДЫЙ элемент через dig_esc().
 * Можно отменить в любой момент нажатием Esc -> тогда возвращается false,
 * и оставшаяся часть матрицы не заполняется.
 */
inline bool fill(int** m, int x, int y) {
    clear_t();
    std::cout
        << "Ввод без Enter:\n"
        << " - Печатайте число (поддерживается '-')\n"
        << " - Enter / Пробел = завершить текущее число\n"
        << " - Backspace = стереть символ\n"
        << " - Esc = отменить ввод и вернуться в меню\n\n";

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            std::cout << "m[" << i << "][" << j << "] ";
            int val = 0;
            if (!dig_esc(val)) {
                return false; // пользователь нажал Esc
            }
            m[i][j] = val;
        }
    }
    return true;
}
