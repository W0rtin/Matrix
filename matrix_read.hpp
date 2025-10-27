#pragma once

#include <iostream>
#include <string>
#include <climits>
#include "matrix_io.hpp"

inline bool dig_esc(int& out){
    std::string s;
    bool digit = false;
    
    std::cout << "> " << std::flush;
    
    while (true){
        int chr = getch();
        
        if (chr == 27) {
            std::cout << "\nОтмена\n";
            return false;
        }
        
        //пробелы и тд между цифрами
        if (chr == ' ' || chr == '\n' || chr == '\t' || chr == '\r'){
            if (!(s.size() == 1 && s[0] == '-')) {
                std::cout << '\n';
                break;
            }
            else continue;
        }
        
        //Обработка Backspace
        if (chr == 8 || chr == 127){
            if (!(s.empty())){
                s.pop_back();
                std::cout << "\b \b" << std::flush;
                if (s.empty()) digit = false;
            }
            continue;
        }
        
        //Обработка отрицательных чисел
        if (chr == '-' && s.empty()){
            s.push_back('-');
            std::cout << '-' << std::flush;
            continue;
        }
        
        //Обработка чисел
        if (chr >= '0' && chr <= '9'){
            s.push_back(static_cast<char>(chr));
            std::cout << static_cast<char>(chr) << std::flush;
            continue;
        }
    }
    
    long long sign = 1;
    int ind = 0;
    
    if (s[0] == '-' ){
        sign = -1;
        ind = 1;
    }
    
    long long val = 0;
    for (; ind < s.size(); ++ind){
        val = val*10 + (s[ind]-'0');
        if (sign == 1 && val > INT_MAX){
            val = INT_MAX;
            break;
        }
        else if (sign == -1 && -val < INT_MIN){
            val = -(long long)INT_MIN;
            break;
        }
    }
    val *= sign;
    if(val > INT_MAX) val = INT_MAX;
    if(val < INT_MIN) val = INT_MIN;
    out = static_cast<char>(val);
    return true;
}

inline bool fill(int** m, int x, int y){
    clear_t();
    std::cout
    << "Ввод без Enter: просто печатайте цифры, знак '-' считается только перед числов \n"
    << "Enter/space - завершить число, Backspace - стереть, Esc - прервать программу \n";
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            int val = 0;
            if (!dig_esc(val)) return false;
            m[i][j] = val;
        }
    }
    return true;
}
