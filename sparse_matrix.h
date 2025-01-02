#pragma once
#include <map>
#include <tuple>
#include <iterator>


/**
 * @brief Класс разреженной матрицы.
 * 
 * @tparam T Тип элеиентов разреженной матрицы.
 * @tparam DefaultValue Значение по усолчанию, используемое для не заполненных ячеек.
 */
template <typename T, T DefaultValue>
class Matrix {
public:
    /**
     * @brief Proxy для доступа к строкам матрицы.
     */
    class RowProxy {
    public:
        /**
         * @brief Конструктор прокси-объекта.
         * 
         * @param row Ссылка на строку матрицы.
         * @param row_index Индекс в строке матрицы.
         * @param rows Ссылка на хранилище.
         */
        RowProxy(std::map<int, T>& row, int row_index, std::map<int, std::map<int, T>>& rows) : row_(row), row_index_(row_index), rows_(rows) {}

        /**
         * @brief Доступ к ячейке в строке матрицы.
         * 
         * @param column Индекс ячейки.
         * @return Ссылка на значение.
         */
        T& operator[](int cell_index) {
            if (row_.find(cell_index) == row_.end()) {
                row_[cell_index] = DefaultValue;
            }

            return row_[cell_index];
        }

        RowProxy& operator=(const T& value) {
            if (value == DefaultValue) {
                clear(row_index_);
            } else {
                row_[row_index_] = value;
            }

            return *this;
        }

        /**
         * @brief Очистка ячейки. удаление значения.
         * 
         * @param column Индекс в строке (для удаления).
         */
        void clear(int cell_index) {
            row_.erase(cell_index);

            if (row_.empty()) {
                rows_.erase(row_index_);
            }
        }

    private:
        std::map<int, T>& row_;                 // Ссылка на строку
        int row_index_;                         // Индекс строки
        std::map<int, std::map<int, T>>& rows_; // Ссылка на хранилище (все строки)
    };

    /**
     * @brief Конструктор по умолчанию.
     */
    Matrix() = default;

    /**
     * @brief Конструктор копирования.
     * 
     * @param other Обхект для копирования.
     */
    Matrix(const Matrix& other) : rows_(other.rows_) {}

    /**
     * @brief Оператор присваивания.
     * 
     * @param other Объект для копирования.
     * @return Ссылка на матрицу.
     */
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            rows_ = other.rows_;
        }

        return *this;
    }

    /**
     * @brief Конструктор перемещения.
     * 
     * @param other Объект для перемещения.
     */
    Matrix(Matrix&& other) noexcept : rows_(std::move(other.rows_)) {}

    /**
     * @brief Оператор приваивания перемещением.
     * 
     * @param other Объект для перемещения.
     * @return Ссылка на матрицу.
     */
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            rows_ = std::move(other.rows_);
        }

        return *this;
    }

    /**
     * @brief Доступ к строке.
     * 
     * @param row_index Индекс строки.
     * @return Proxy объект, соответствующий строке.
     */
    RowProxy operator[](int row_index) {
        return RowProxy(rows_[row_index], row_index, rows_);
    }

    /**
     * @brief Вычисление числа занятых ячеек в матрице.
     * 
     * @return Число занятых ячеек в матрице
     */
    int size() const {
        int count = 0;

        for (const auto& row : rows_) {
            count += row.second.size();
        }

        return count;
    }

    /**
     * @brief Итератор для обхода занятых ячеек.
     */
    class Iterator {
        public:
            Iterator(typename std::map<int, std::map<int, T>>::iterator rowIt,
                    typename std::map<int, std::map<int, T>>::iterator rowEndIt)
                : rowIt_(rowIt), rowEndIt_(rowEndIt) {
                if (rowIt_ != rowEndIt_) {
                    colIt_ = rowIt_->second.begin();
                    skipEmptyRows();
                }
            }

            bool operator!=(const Iterator& other) const {
                return rowIt_ != other.rowIt_ || (rowIt_ != rowEndIt_ && colIt_ != other.colIt_);
            }

            void operator++() {
                ++colIt_;
                if (colIt_ == rowIt_->second.end()) {
                    ++rowIt_;
                    skipEmptyRows();
                }
            }

            std::tuple<int, int, T> operator*() const {
                return std::make_tuple(rowIt_->first, colIt_->first, colIt_->second);
            }

        private:
            typename std::map<int, std::map<int, T>>::iterator rowIt_;
            typename std::map<int, std::map<int, T>>::iterator rowEndIt_;
            typename std::map<int, T>::iterator colIt_;

            void skipEmptyRows() {
                while (rowIt_ != rowEndIt_ && rowIt_->second.empty()) {
                    ++rowIt_;
                }
                if (rowIt_ != rowEndIt_) {
                    colIt_ = rowIt_->second.begin();
                }
            }
        };    

    Iterator begin() {
        return Iterator(rows_.begin(), rows_.end());
    }

    /**
     * @brief Получение итератора, указывающего на последнюю занятую ячейку.
     * 
     * @return Итератор, указывающий на последнюю занятую ячейку.
     */
    Iterator end() {
        return Iterator(rows_.end(), rows_.end());
    }

private:
    std::map<int, std::map<int, T>> rows_; // Строки матрицы.
};