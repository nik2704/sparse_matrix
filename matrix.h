#pragma once
#include <map>
#include <algorithm>
#include <tuple>
#include "proxy.h"


/**
 * @brief Класс разреженной матрицы.
 * 
 * @tparam T Тип элеиентов разреженной матрицы.
 * @tparam DefaultValue Значение по усолчанию, используемое для не заполненных ячеек.
 */
template<class T, T DefaultValue>
class Matrix{
public:
    /**
     * @brief Конструктор.
     */
    Matrix() : default_value_(DefaultValue) {};

    /**
     * @brief Конструктор копирования.
     */
    Matrix(const Matrix& other) : default_value_(other.default_value_), matrix_(other.matrix_) {}

    /**
     * @brief Конструктор перемещения.
     */
    Matrix(Matrix&& other) noexcept : default_value_(other.default_value_), matrix_(std::move(other.matrix_)) {}

    /**
     * @brief Оператор присваивания (копирование).
     */
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            matrix_ = other.matrix_;
        }
        return *this;
    }

    /**
     * @brief Оператор присваивания (перемещение).
     */
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            matrix_ = std::move(other.matrix_);
        }
        return *this;
    }

    /**
     * @brief Деструктор по умолчанию.
     */
    ~Matrix() {}
    
    Proxy<T, DefaultValue> operator[](size_t x){
        Proxy<T, DefaultValue> proxy(*this, x);

        return proxy;
    };

    /**
     * @brief Получить размер матрицы.
     * 
     * Возвращает количество занятых ячеек в матрице.
     * 
     * @return size_t Количество занятых ячеек в матрице.
     */    
    size_t size(){
        return matrix_.size();
    }
    
    /**
     * @brief Получить значение по умолчанию для не заполненных ячеек.
     * 
     * Возвращает значение, которое используется для ячеек, не заполненных пользователем.
     * 
     * @return T Значение по умолчанию для пустых ячеек.
     */    
    T getDefaultValue(){
        return default_value_;
    }; 
    
    /**
     * @brief Получить элемент по заданным координатам.
     * 
     * Если элемент с заданными координатами существует в матрице, возвращает его значение. 
     * Если элемента нет, возвращает значение по умолчанию.
     * 
     * @param coordinates Пара индексов (x, y) для поиска элемента в матрице.
     * @return const T& Ссылка на элемент матрицы или значение по умолчанию.
     */    
    const T& getElement(std::pair<size_t, size_t> coordinates) const {
        auto it = matrix_.find(coordinates);

        if( it == matrix_.end()){
            return default_value_;
        } else {
            return it->second;
        }
    };
    
    /**
     * @brief Удалить элемент с заданными координатами.
     * 
     * Удаляет элемент из матрицы по указанным координатам, если такой элемент существует.
     * 
     * @param coordinates Пара индексов (x, y) для удаления элемента из матрицы.
     */    
    void deleteElement(std::pair<size_t, size_t> coordinates){
        auto it = matrix_.find(coordinates);

        if (it != matrix_.end()) {
            matrix_.erase(it);
        }
    };
    
    /**
     * @brief Вставить элемент в матрицу.
     * 
     * Вставляет новый элемент с заданными координатами и значением в матрицу. 
     * Если элемент с такими координатами уже существует, он будет обновлен.
     * 
     * @param coordinates Пара индексов (x, y) для вставки элемента.
     * @param value Значение, которое будет присвоено элементу.
     */    
    void insertElement(std::pair<size_t, size_t> coordinates, T value){
        matrix_.emplace(coordinates, value);
    };
    
    /**
     * @brief Итератор для обхода занятых ячеек.
     */
    class Iterator {
    using MatrixIteratorType = typename std::map<std::pair<size_t, size_t>, T>::iterator;

    public:
        Iterator(MatrixIteratorType  it):it_(it){};
        
        MatrixIteratorType getIterator(){
            return this->it_;
        }
        
        void operator++(){
            ++it_;
        };
        
        void operator--(){
            --it_;
        }

        std::tuple<long, long, T> operator*(){
            return std::make_tuple(it_->first.first, it_->first.second, it_->second);
        };        
        
        bool operator !=(Iterator& other){
            return it_ != other.getIterator();
        }
        
        bool operator ==(Iterator& other){
            return it_ == other.getIterator();
        }
        
    private:
        MatrixIteratorType  it_;
    };
    
    
    Iterator begin(){
        return Iterator(matrix_.begin());
    };
    
    Iterator end(){
        return Iterator(matrix_.end());
    };

private:
    const T default_value_;
    std::map<std::pair<size_t, size_t>, T > matrix_;
};