#pragma once
#include <iostream>
#include <termios.h>
#include <unistd.h>

/*
 * clear_t
 * Очищает экран терминала с помощью ESC-последовательности.
 * По сути перерисовывает "чистый экран".
 */
inline void clear_t() {
    std::cout << "\033c";
}


/*
 * getch
 * Считывает один символ с клавиатуры БЕЗ ожидания Enter
 * и без эха (символ не печатается сам по себе).
 *
 * Реализация на POSIX-подобных системах (macOS, Linux):
 *  - выключаем canonical mode и echo через termios
 *  - читаем один символ через getchar()
 *  - возвращаем терминал в исходное состояние
 *
 * Возвращает код символа (int), либо 27 (Esc), либо EOF при ошибке tcsetattr().
 */
inline int getch() {
    termios oldt{};
    termios newt{};
    int ch = 0;

    // получить текущие настройки терминала
    if (tcgetattr(STDIN_FILENO, &oldt) != 0) {
        return 27; // fallback: трактуем как Esc
    }

    newt = oldt;
    // снимаем канонический режим (ICANON) и эхо (ECHO),
    // чтобы читать по одному символу без Enter
    newt.c_lflag &= ~(ICANON | ECHO);

    // применяем новые настройки немедленно
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) != 0) {
        return EOF;
    }

    ch = ::getchar();

    // возвращаем старые настройки
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
