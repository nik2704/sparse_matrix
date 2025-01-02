#pragma once

#include "matrix.h"

template<class T, T N>
class Matrix;

/**
 * @brief Proxy для работы с матрицей.
 */
template<class T, T DefaultValue>
class Proxy {
public:
    Proxy(Matrix<T, DefaultValue>& matrix, size_t line) : line_(line), matrix_(matrix) {}

    ~Proxy() = default;

    /**
     * @brief Переопределение оператора [].
     * 
     * @return Указатель на текущий объект.
     */
    Proxy& operator[](int position) {
        cell_coords_ = std::make_pair(line_, position);
        current_element_ = matrix_.getElement(cell_coords_);

        return *this;
    }

    /**
     * @brief Переопределение оператора =. Присвоение в ячейку значения по умолчанию освобождает ячейку.
     */
    Proxy& operator=(T newValue) {
        if (newValue == matrix_.getDefaultValue()) {
            matrix_.deleteElement(cell_coords_);
        } else {
            matrix_.insertElement(cell_coords_, newValue);
        }

        return *this;  // Для поддержки канонической формы оператора =, допускающую выражения ((matrix[100][100] = 314) = 0) = 217
    }

    /**
     * @brief Переопределение оператора (). Неявное преобразование Proxy в тип T. Возврат текущего элемента.
     */
    operator T() {
        return current_element_;
    }

private:
    size_t line_;                           //номер строки
    T current_element_;                     //текущее значение ячейки
    std::pair<size_t, size_t> cell_coords_; //координаты ячейки
    Matrix<T, DefaultValue>&  matrix_;      //хранилище
};
