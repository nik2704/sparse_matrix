// #include <iostream>
// #include <string>
// #include <cassert>
// #include <tuple>
// #include "matrix.h"


// int main() {

//     Matrix<int, 0> matrix;

//     assert(matrix.size() == 0);
//     auto a = matrix[0][0];
//     assert(a == 0);
//     assert(matrix.size() == 0);
//     matrix[100][100] = 314;
//     assert(matrix[100][100] == 314);
//     assert(matrix.size() == 1);
//     matrix[100][100] = 0;
//     assert(matrix[100][100] == 0);
//     assert(matrix.size() == 0);


//     for (auto i = 0; i < 10; i++)
//         matrix[i][i] = i;
//     for (auto i = 0, j = 9; i < 10; i++, j--)
//         matrix[i][j] = j;

//     std::cout<<"size: "<<matrix.size()<<std::endl;

//     for(auto c : matrix){
//         int x,y,v;
//         std::tie(x, y, v) = c;
//         std::cout<<"["<<x<<"]"<<"["<<y<<"]"<<" value: "<<v<< std::endl;
//     }

//     for(auto i = 1; i < 9; i++){
//         for (auto j = 1; j < 9; j++){
//             std::cout<<matrix[i][j]<<" ";
//         }
//         std::cout<<std::endl;
//     }
//   return 0;
// }

#include <cassert>
#include <iostream>
#include <iomanip>
#include "matrix.h"



/**
 * @brief  Пример использования.
 */
int main() {
    Matrix<int, 0> matrix;

    // Заполняем главную диагональ значениями от 0 до 9
    for (int i = 0; i < 10; ++i) {
        matrix[i][i] = i;
    }

    // Заполняем второстепенную диагональ значениями от 9 до 0
    for (int i = 0; i < 10; ++i) {
        matrix[i][9 - i] = 9 - i;
    }

    // Выводим фрагмент матрицы от [1,1] до [8,8]
    std::cout << "Фрагменты от [1,1] до [8,8]:\n";
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            std::cout << std::setw(3) << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Выводим количество занятых ячеек
    std::cout << "\nКоличество занятых ячеек: " << matrix.size() << std::endl;

    // Выводим все занятые ячейки с их позициями
    std::cout << "\nЗанятые ячейки (позиция и знаяения):\n";
    for (auto c : matrix) {
        int x, y, v;
        std::tie(x, y, v) = c;
        std::cout << "Позиция: (" << x << ", " << y << "), Значение: " << v << std::endl;
    }

    return 0;
}
