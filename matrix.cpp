#include <iostream>
#include "main.hpp"

int main(){
    clear_t();
    int x, y, t;
    int** m1;
    int** m2;
    
    std::cout << "Нажмите любую клавишу для старта, Ecs - выход <:\n";
    if(getch() == 27) return 0;
    
    while (t != 27){
        t = getch();
        std::cout
        << "\nМеня (без Enter): \n"
        << "1 - Задать размеры матрицы\n"
        << "2 - Заполнить матрицу 1\n"
        << "3 - Заполнить матрицу 2\n"
        << "4 - Показать матрицы\n"
        << "5 - Действия над матрицами \n"
        << "Esc - выход\n";
        
        switch(t){
            case '1':{
                clear_t();
                std::cout << "Введите X, Y:\n";
                std::cout << "X "; if (!dig_esc(x)) break;
                std::cout << "Y "; if (!dig_esc(y)) break;
                if  (x <= 0 || y <= 0) {std::cout << "Размеры должны быть больше 0\n"; break;}
                
                m1 = create_matrix(x, y);
                m2 = create_matrix(x, y);
                
                std::cout << "Заданные размеры: " << x << 'x' << y << '\n';
                break;}
            
            case '2':{
                clear_t();
                if (!m1) {std::cout << "Сначала задайте размеры матриц\n"; break;}
                if (!fill(m1, x, y)) std::cout << "Ошибка, был нажат Esc\n";
                else std::cout << "Матрица 1 заполнена";
                break;}
            
            case '3':{
                clear_t();
                if (!m2) {std::cout << "Сначала задайте размеры матриц\n"; break;}
                if (!fill(m2, x, y)) std::cout << "Ошибка, был нажат Esc\n";
                else std::cout << "Матрица 2 заполнена";
                break;}
                
            case '4':{
                clear_t();
                if (!m1 && !m2) {std::cout << "Сначала задайте размеры матриц\n"; break;}
                
                std::cout << "Первая матрицы: \n";
                for (int i = 0; i < x; i++){
                    for (int j = 0; j < y; j++){
                        std::cout << m1[i][j] << ' ';
                    }
                    std::cout << '\n';
                }
                
                std::cout << "Вторая матрицы: \n";
                for (int i = 0; i < x; i++){
                    for (int j = 0; j < y; j++){
                        std::cout << m2[i][j] << ' ';
                    }
                    std::cout << '\n';
                }
                break;}
            //case 5 починить
            case '5':{
                clear_t();
                std::cout
                << "1 - Сложить матрицы\n"
                << "2 - Вычесть матрицы (скоро)\n"
                << "3 - Перемножить матрицы (скоро)\n"
                << "4 - Возвести матрицы в степень (скоро)";
                int t1 = getch();
                if (t1 == '1'){
                    clear_t();
                    int** m_sum = sum_matrix(m1, m2, x, y);
                    for (int i = 0; i < x; i++){
                        for (int j = 0; j < y; j++){
                            std::cout << m_sum[i][j] << ' ';
                        }
                        std::cout << '\n';
                    }
                    free_matrix(m_sum, x);
                }
            }
                
                
                
            default:
                clear_t();
                std::cout << "Неизвестная команда\n";
                break;
        }
    }
    
    free_matrix(m1, x);
    free_matrix(m2, x);
    
    std::cout << "\nВыход\n";
    return 0;
}
