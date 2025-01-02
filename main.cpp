#include <iostream>
#include <iomanip>
#include "sparse_matrix.h"



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
