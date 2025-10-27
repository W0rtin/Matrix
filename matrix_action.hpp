#pragma once

#include "matrix_io.hpp"

inline void free_matrix(int** a, int x) {
    for (int i = 0; i < x; ++i) delete[] a[i];
    delete[] a;
} //Очистка памяти

inline int** create_matrix(int row, int cols){
    int** m = new int*[row];
    for (int i = 0; i < row; i++) m[i] = new int[cols]{};
    return m;
}//Создание матриц

inline void Set_place(int **m, const int& x, const int& y){
    clear_t();
    
    std::cout << "Вводите числа, которыми хотите заполнить матрицу, но не более чем " << x*y << " чисел\n";
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            int num;
            std::cin >> num;
            
            m[i][j] = num;
        }
    }
    
}//Заполнение матриц

inline int** sum_matrix(int** m1, int** m2, int x = 0, int y = 0){
    int** m3 = create_matrix(x, y);
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            m3[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return m3; 
}//Суммирование матриц

inline int** dis_sum_matrix(int** m1, int** m2, int x = 0, int y = 0){
    std::cout << 1;
    int **m4;
    return m4;
}
