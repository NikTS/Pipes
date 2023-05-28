#ifndef Matrix4x4_hpp
#define Matrix4x4_hpp

// Подключение стандартных библиотек
#include <math.h>
#include <cassert>

// Подключение внутренних типов
#include "CalcNumber.hpp"
#include "Point.hpp"

/// Матрица размера 4 на 4.
///
/// Матрица состоит из следующих элементов:
///
/// --------------
///
/// | a11 a12  a13 a14 |
///
/// | a21 a22 a23 a24 |
///
/// | a31 a32 a33 a34 |
///
/// | a41 a42 a43 a44 |
///
/// --------------
class Matrix4x4 {
    
public:
    
    // MARK: - Открытые объекты
    
    /// Элементы матрицы.
    CalcNumber elems[4][4];
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param a11 Элемент матрицы a11.
    /// \param a12 Элемент матрицы a12.
    /// \param a13 Элемент матрицы a13.
    /// \param a14 Элемент матрицы a14.
    /// \param a21 Элемент матрицы a21.
    /// \param a22 Элемент матрицы a22.
    /// \param a23 Элемент матрицы a23.
    /// \param a24 Элемент матрицы a24.
    /// \param a31 Элемент матрицы a31.
    /// \param a32 Элемент матрицы a32.
    /// \param a33 Элемент матрицы a33.
    /// \param a34 Элемент матрицы a34.
    /// \param a41 Элемент матрицы a41.
    /// \param a42 Элемент матрицы a42.
    /// \param a43 Элемент матрицы a43.
    /// \param a44 Элемент матрицы a44.
    explicit Matrix4x4(CalcNumber a11, CalcNumber a12, CalcNumber a13, CalcNumber a14, CalcNumber a21, CalcNumber a22, CalcNumber a23, CalcNumber a24, CalcNumber a31, CalcNumber a32, CalcNumber a33, CalcNumber a34, CalcNumber a41, CalcNumber a42, CalcNumber a43, CalcNumber a44);
    
    /// Конструктор.
    ///
    /// \param matrix Двумерный массив, содержащий элементы матрицы.
    explicit Matrix4x4(CalcNumber matrix[4][4]);
    
    /// Конструктор по умолчанию. Создается матрица с нулевыми элементами.
    explicit Matrix4x4();
    
    /// Конструктор копирования.
    ///
    /// \param anotherMatrix Копируемая матрица.
    Matrix4x4(const Matrix4x4 & anotherMatrix);
    
    // MARK: - Открытые статические методы
    
    /// Вернуть нулевую матрицу, в которой все элементы равны нулю.
    ///
    /// \return Нулевая матрица.
    static Matrix4x4 getZeroMatrix();
    
    /// Вернуть единичную матрицу с единицами на главной диагонали.
    ///
    /// \return Единичная матрица.
    static Matrix4x4 getIdentityMatrix();
    
    /// Вернуть матрицу поворота вокруг оси Ox на угол alpha.
    ///
    /// Положительным углам соответствует вращение против часовой стрелки при наблюдении за вращением против направления соответствующей оси.
    ///
    /// \param alpha Угол вращения.
    ///
    /// \return Матрица поворота вокруг оси Ox на угол alpha против часовой стрелки.
    static Matrix4x4 getRotateXMatrix(CalcNumber alpha);
    
    /// Вернуть матрицу поворота вокруг оси Oy на угол alpha.
    ///
    /// Положительным углам соответствует вращение против часовой стрелки при наблюдении за вращением против направления соответствующей оси.
    ///
    /// \param alpha Угол вращения.
    ///
    /// \return Матрица поворота вокруг оси Oy на угол alpha против часовой стрелки.
    static Matrix4x4 getRotateYMatrix(CalcNumber alpha);
    
    /// Вернуть матрицу поворота вокруг оси Oz на угол alpha.
    ///
    /// Положительным углам соответствует вращение против часовой стрелки при наблюдении за вращением против направления соответствующей оси.
    ///
    /// \param alpha Угол вращения.
    ///
    /// \return Матрица поворота вокруг оси Oz на угол alpha против часовой стрелки.
    static Matrix4x4 getRotateZMatrix(CalcNumber alpha);
    
    /// Вернуть матрицу переноса на вектор (dx, dy, dz).
    ///
    /// \param dx Смещение по оси Ox.
    /// \param dy Смещение по оси Oy.
    /// \param dz Смещение по оси Oz.
    ///
    /// \return Матрица переноса на вектор (dx, dy, dz).
    static Matrix4x4 getTranslateMatrix(CalcNumber dx, CalcNumber dy, CalcNumber dz);
    
    /// Вернуть матрицу переноса на вектор translateVector.
    ///
    /// \param translateVector Вектор переноса.
    ///
    /// \return Матрица переноса на вектор translateVector.
    static Matrix4x4 getTranslateMatrix(Point translateVector);
    
    /// Вернуть матрицу переноса по оси Ox на dx.
    ///
    /// \param dx Смещение по оси Ox.
    ///
    /// \return Матрица переноса по оси Ox на dx.
    static Matrix4x4 getTranslateXMatrix(CalcNumber dx);
    
    /// Вернуть матрицу переноса по оси Oy на dy.
    ///
    /// \param dy Смещение по оси Oy.
    ///
    /// \return Матрица переноса по оси Oy на dy.
    static Matrix4x4 getTranslateYMatrix(CalcNumber dy);
    
    /// Вернуть матрицу переноса по оси Oz на dz.
    ///
    /// \param dz Смещение по оси Oz.
    ///
    /// \return Матрица переноса по оси Oz на dz.
    static Matrix4x4 getTranslateZMatrix(CalcNumber dz);
    
    // MARK: - Открытые методы
    
    /// Оператор копирования.
    ///
    /// \param anotherMatrix Копируемая матрица.
    Matrix4x4 & operator=(const Matrix4x4 & anotherMatrix);
    
    /// Оператор сравнения.
    ///
    /// \param anotherMatrix Вторая матрица.
    ///
    /// \return true, если матрицы совпадают, иначе false.
    bool operator==(const Matrix4x4 & anotherMatrix) const;
    
    /// Оператор сравнения.
    ///
    /// \param anotherMatrix Вторая матрица.
    ///
    /// \return true, если матрицы не совпадают, иначе true.
    bool operator!=(const Matrix4x4 & anotherMatrix) const;
    
    /// Вернуть модуль максимального по модулю элемента матрицы.
    ///
    /// \return Модуль максимального по модулю элемента матрицы.
    CalcNumber maxAbs() const;
    
    /// Вернуть определитель матрицы.
    ///
    /// \return Определитель матрицы.
    CalcNumber determinant() const;
    
    /// Оператор сложения.
    ///
    /// \param anotherMatrix Вторая матрица.
    ///
    /// \return Матрица, равная сумм.е данной матрицы и anotherMatrix.
    Matrix4x4 operator+ (const Matrix4x4 & anotherMatrix) const;
    
    /// Присваивающий оператор сложения.
    ///
    /// \param anotherMatrix Вторая матрица.
    ///
    /// \return Ссылка на себя.
    Matrix4x4 & operator+= (const Matrix4x4 & anotherMatrix);
    
    /// Оператор сложения с числом. Прибавляет к каждому элементу матрицы число number.
    ///
    /// \param number Число.
    ///
    /// \return Матрица, равная сумм.е данной матрицы и числа number.
    Matrix4x4 operator+ (CalcNumber number) const;
    
    /// Присваивающий оператор сложения с числом. Прибавляет к каждому элементу матрицы число number.
    ///
    /// \param number Число.
    ///
    /// \return Ссылка на себя.
    Matrix4x4 & operator+= (CalcNumber number);
    
    /// Оператор вычитания.
    ///
    /// \param anotherMatrix Вторая матрица.
    ///
    /// \return Матрица, равная разности данной матрицы и anotherMatrix.
    Matrix4x4 operator- (const Matrix4x4 & anotherMatrix) const;
    
    /// Присваивающий оператор вычитания.
    ///
    /// \param anotherMatrix Вторая матрица.
    ///
    /// \return Ссылка на себя.
    Matrix4x4 & operator-= (const Matrix4x4 & anotherMatrix);
    
    /// Оператор вычитания числа. Вычитает из каждого элемента матрицы число number.
    ///
    /// \param number Число.
    ///
    /// \return Матрица, равная разности данной матрицы и числа number.
    Matrix4x4 operator- (CalcNumber number) const;
    
    /// Присваивающий оператор вычитания числа. Вычитает из каждого элемента матрицы число number.
    ///
    /// \param number Число.
    ///
    /// \return Ссылка на себя.
    Matrix4x4 & operator-= (CalcNumber number);
    
    /// Оператор умножения на другую матрицу.
    ///
    /// \param anotherMatrix Вторая матрица.
    ///
    /// \return Матрица, равная произведению данной матрицы и anotherMatrix.
    Matrix4x4 operator* (const Matrix4x4 & anotherMatrix) const;
    
    /// Присваивающий оператор умножения на другую матрицу.
    ///
    /// \param anotherMatrix Вторая матрица.
    ///
    /// \return Ссылка на себя.
    Matrix4x4 & operator*= (const Matrix4x4 & anotherMatrix);
    
    /// Оператор умножения на вектор-столбец, полученный из вектора vector добавлением справа единицы. Результат умножения (вектор-столбец) возвращается без последнего элемента.
    ///
    /// \param vector Вектор.
    ///
    /// \return Результат умножения.
    Point operator* (const Point & vector) const;
    
    /// Оператор умножения на число. Умножает каждый элемент матрицы на число number.
    ///
    /// \param number Число.
    ///
    /// \return Матрица, равная произведению данной матрицы и числа number.
    Matrix4x4 operator* (CalcNumber number) const;
    
    /// Присваивающий оператор умножения на число. Умножает каждый элемент матрицы на число number.
    ///
    /// \param number Число.
    ///
    /// \return Ссылка на себя.
    Matrix4x4 & operator*= (CalcNumber number);
    
    /// Оператор деления на число. Делит каждый элемент матрицы на число number.
    ///
    /// \param number Число.
    ///
    /// \return Матрица, равная частному данной матрицы и числа number.
    Matrix4x4 operator/ (CalcNumber number) const;
    
    /// Присваивающий оператор деления на число. Делит каждый элемент матрицы на число number.
    ///
    /// \param number Число.
    ///
    /// \return Ссылка на себя.
    Matrix4x4 & operator/= (CalcNumber number);
    
    /// Вернуть противоположную матрицу к данной.
    ///
    /// \return Противоположная матрица к данной.
    Matrix4x4 opposed() const;
    
    /// Заменить матрицу на противоположную.
    ///
    /// \return Ссылка на себя.
    Matrix4x4 & oppose();
    
    /// Вернуть транспонированную матрицу к данной.
    ///
    /// \return Транспонированная матрица к данной.
    Matrix4x4 transposed() const;
    
    /// Транспонировать матрицу.
    ///
    /// \return Ссылка на себя.
    Matrix4x4 & transpose();
    
    /// Вернуть обратную матрицу к данной. Данная матрица должна быть обратимой.
    ///
    /// \return Обратная матрица к данной.
    Matrix4x4 inversed() const;
    
    /// Обратить матрицу. Матрица должна быть обратимой.
    ///
    /// \return Ссылка на себя.
    Matrix4x4 & inverse();
    
};

// MARK: - Внешние операторы

/// Оператор умножения вектора-строки на матрицу matrix. Вектор-строка получается из вектора vector добавлением справа единицы. Результат умножения (вектор-строка) возвращается без последнего элемента.
///
/// \param vector Вектор.
/// \param matrix Матрица.
///
/// \return Результат умножения.
Point operator* (const Point & vector, const Matrix4x4 & matrix);

/// Присваивающий оператор умножения вектора-строки на матрицу matrix. Вектор-строка получается из вектора vector добавлением справа единицы. Результат умножения (вектор-строка) возвращается без последнего элемента.
///
/// \param vector Вектор.
/// \param matrix Матрица.
///
/// \return Ссылка на измененную вектор-строку.
Point & operator*= (Point & vector, const Matrix4x4 & matrix);

// MARK: - Реализация

/// Конструктор.
///
/// \param a11 Элемент матрицы a11.
/// \param a12 Элемент матрицы a12.
/// \param a13 Элемент матрицы a13.
/// \param a14 Элемент матрицы a14.
/// \param a21 Элемент матрицы a21.
/// \param a22 Элемент матрицы a22.
/// \param a23 Элемент матрицы a23.
/// \param a24 Элемент матрицы a24.
/// \param a31 Элемент матрицы a31.
/// \param a32 Элемент матрицы a32.
/// \param a33 Элемент матрицы a33.
/// \param a34 Элемент матрицы a34.
/// \param a41 Элемент матрицы a41.
/// \param a42 Элемент матрицы a42.
/// \param a43 Элемент матрицы a43.
/// \param a44 Элемент матрицы a44.
Matrix4x4::Matrix4x4(CalcNumber a11, CalcNumber a12, CalcNumber a13, CalcNumber a14, CalcNumber a21, CalcNumber a22, CalcNumber a23, CalcNumber a24, CalcNumber a31, CalcNumber a32, CalcNumber a33, CalcNumber a34, CalcNumber a41, CalcNumber a42, CalcNumber a43, CalcNumber a44) {
    
    elems[0][0] = a11;
    elems[0][1] = a12;
    elems[0][2] = a13;
    elems[0][3] = a14;
    elems[1][0] = a21;
    elems[1][1] = a22;
    elems[1][2] = a23;
    elems[1][3] = a24;
    elems[2][0] = a31;
    elems[2][1] = a32;
    elems[2][2] = a33;
    elems[2][3] = a34;
    elems[3][0] = a41;
    elems[3][1] = a42;
    elems[3][2] = a43;
    elems[3][3] = a44;
    
}

/// Конструктор.
///
/// \param matrix Двумерный массив, содержащий элементы матрицы.
Matrix4x4::Matrix4x4(CalcNumber matrix[4][4]) {
    
    std::memcpy(elems, matrix, 16 * sizeof(CalcNumber));
    
}

/// Конструктор по умолчанию. Создается матрица с нулевыми элементами.
Matrix4x4::Matrix4x4(): Matrix4x4(
                            0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0
                        ) {}

/// Конструктор копирования.
///
/// \param anotherMatrix Копируемая матрица.
Matrix4x4::Matrix4x4(const Matrix4x4 & anotherMatrix) {
    
    std::memcpy(elems, anotherMatrix.elems, 16 * sizeof(CalcNumber));
    
}

/// Вернуть нулевую матрицу, в которой все элементы равны нулю.
///
/// \return Нулевая матрица.
Matrix4x4 Matrix4x4::getZeroMatrix() {
    
    return Matrix4x4(
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0
    );
    
}

/// Вернуть единичную матрицу с единицами на главной диагонали.
///
/// \return Единичная матрица.
Matrix4x4 Matrix4x4::getIdentityMatrix() {
    
    return Matrix4x4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    );
    
}

/// Вернуть матрицу поворота вокруг оси Ox на угол alpha.
///
/// Положительным углам соответствует вращение против часовой стрелки при наблюдении за вращением против направления соответствующей оси.
///
/// \param alpha Угол вращения.
///
/// \return Матрица поворота вокруг оси Ox на угол alpha против часовой стрелки.
Matrix4x4 Matrix4x4::getRotateXMatrix(CalcNumber alpha) {
    
    CalcNumber sinAlpha = sin(alpha), cosAlpha = cos(alpha);
    
    return Matrix4x4(
            1, 0, 0, 0,
            0, cosAlpha, -sinAlpha, 0,
            0, sinAlpha, cosAlpha, 0,
            0, 0, 0, 1
            );
    
}

/// Вернуть матрицу поворота вокруг оси Oy на угол alpha.
///
/// Положительным углам соответствует вращение против часовой стрелки при наблюдении за вращением против направления соответствующей оси.
///
/// \param alpha Угол вращения.
///
/// \return Матрица поворота вокруг оси Oy на угол alpha против часовой стрелки.
Matrix4x4 Matrix4x4::getRotateYMatrix(CalcNumber alpha) {
    
    CalcNumber sinAlpha = sin(alpha), cosAlpha = cos(alpha);
    
    return Matrix4x4(
            cosAlpha, 0, sinAlpha, 0,
            0, 1, 0, 0,
            -sinAlpha, 0, cosAlpha, 0,
            0, 0, 0, 1
            );
    
}

/// Вернуть матрицу поворота вокруг оси Oz на угол alpha.
///
/// Положительным углам соответствует вращение против часовой стрелки при наблюдении за вращением против направления соответствующей оси.
///
/// \param alpha Угол вращения.
///
/// \return Матрица поворота вокруг оси Oz на угол alpha против часовой стрелки.
Matrix4x4 Matrix4x4::getRotateZMatrix(CalcNumber alpha) {
    
    CalcNumber sinAlpha = sin(alpha), cosAlpha = cos(alpha);
    
    return Matrix4x4(
            cosAlpha, -sinAlpha, 0, 0,
            sinAlpha, cosAlpha, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
            );
    
}

/// Вернуть матрицу переноса на вектор (dx, dy, dz).
///
/// \param dx Смещение по оси Ox.
/// \param dy Смещение по оси Oy.
/// \param dz Смещение по оси Oz.
///
/// \return Матрица переноса на вектор (dx, dy, dz).
Matrix4x4 Matrix4x4::getTranslateMatrix(CalcNumber dx, CalcNumber dy, CalcNumber dz) {
    
    return Matrix4x4(
            1, 0, 0, dx,
            0, 1, 0, dy,
            0, 0, 1, dz,
            0, 0, 0, 1
            );
    
}

/// Вернуть матрицу переноса на вектор translateVector.
///
/// \param translateVector Вектор переноса.
///
/// \return Матрица переноса на вектор translateVector.
Matrix4x4 Matrix4x4::getTranslateMatrix(Point translateVector) {
    
    return getTranslateMatrix(translateVector.x, translateVector.y, translateVector.z);
    
}

/// Вернуть матрицу переноса по оси Ox на dx.
///
/// \param dx Смещение по оси Ox.
///
/// \return Матрица переноса по оси Ox на dx.
Matrix4x4 Matrix4x4::getTranslateXMatrix(CalcNumber dx) {
    
    return getTranslateMatrix(dx, 0, 0);
    
}

/// Вернуть матрицу переноса по оси Oy на dy.
///
/// \param dy Смещение по оси Oy.
///
/// \return Матрица переноса по оси Oy на dy.
Matrix4x4 Matrix4x4::getTranslateYMatrix(CalcNumber dy) {
    
    return getTranslateMatrix(0, dy, 0);
    
}

/// Вернуть матрицу переноса по оси Oz на dz.
///
/// \param dz Смещение по оси Oz.
///
/// \return Матрица переноса по оси Oz на dz.
Matrix4x4 Matrix4x4::getTranslateZMatrix(CalcNumber dz) {
    
    return getTranslateMatrix(0, 0, dz);
    
}

/// Оператор копирования.
///
/// \param anotherMatrix Копируемая матрица.
Matrix4x4 & Matrix4x4::operator=(const Matrix4x4 & anotherMatrix) {
    
    std::memcpy(elems, anotherMatrix.elems, 16 * sizeof(CalcNumber));
    
    return *this;
    
}

/// Оператор сравнения.
///
/// \param anotherMatrix Вторая матрица.
///
/// \return true, если матрицы совпадают, иначе false.
bool Matrix4x4::operator==(const Matrix4x4 & anotherMatrix) const {
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (elems[i][j] != anotherMatrix.elems[i][j]) {
                return false;
            }
        }
    }
    return true;
    
}

/// Оператор сравнения.
///
/// \param anotherMatrix Вторая матрица.
///
/// \return true, если матрицы не совпадают, иначе true.
bool Matrix4x4::operator!=(const Matrix4x4 & anotherMatrix) const {
    
    return ((*this == anotherMatrix) == false);
    
}

/// Вернуть модуль максимального по модулю элемента матрицы.
///
/// \return Модуль максимального по модулю элемента матрицы.
CalcNumber Matrix4x4::maxAbs() const {
    
    CalcNumber maxAbs = -1;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (abs(elems[i][j]) > maxAbs) {
                maxAbs = abs(elems[i][j]);
            }
        }
    }
    
    return maxAbs;
    
}

/// Вернуть определитель матрицы.
///
/// \return Определитель матрицы.
CalcNumber Matrix4x4::determinant() const {
    
    // 1. Создается временная матрица tempMatrix, равная данной матрице.
    CalcNumber tempMatrix[4][4];
    std::memcpy(tempMatrix, this->elems, 16 * sizeof(CalcNumber));
    
    // 2. Матрица tempMatrix приводится к диагональному виду с помощью преобразований Гаусса, сохраняющих определитель.
    for (int i = 0; i < 4; i++) {
        
        // 2.1. Если элемент [i][i] равен нулю, а элемент [k][i] не равен нулю для некоторого k > i, то i-я и k-я строчки меняются местами. Если же для всех k >= i элементы [k][i] равны нулю, то определитель равен нулю.
        for (int k = i; k < 4; k++) {
            if (tempMatrix[k][i] != 0) {
                if (k > i) {
                    CalcNumber tempRow[4];
                    std::memcpy(tempRow, tempMatrix[i], 4 * sizeof(CalcNumber));
                    std::memcpy(tempMatrix[i], tempMatrix[k], 4 * sizeof(CalcNumber));
                    std::memcpy(tempMatrix[k], tempRow, 4 * sizeof(CalcNumber));
                }
                break;
            }
            if (k == 3) {
                return 0;
            }
        }
        
        // 2.2. Выполняются преобразования Гаусса для строчек k > i, в результате которых обнуляются элементы [k][i].
        for (int k = i + 1; k < 4; k++) {
            CalcNumber coef = tempMatrix[k][i] / tempMatrix[i][i];
            tempMatrix[k][i] = 0;
            for (int j = i + 1; j < 4; j++) {
                tempMatrix[k][j] -= tempMatrix[i][j] * coef;
            }
        }
    }
    
    // 3. Определитель матрицы tempMatrix находится как произведение элементов главной диагонали.
    return tempMatrix[0][0] * tempMatrix[1][1] * tempMatrix[2][2] * tempMatrix[3][3];
    
}

/// Оператор сложения.
///
/// \param anotherMatrix Вторая матрица.
///
/// \return Матрица, равная сумм.е данной матрицы и anotherMatrix.
Matrix4x4 Matrix4x4::operator+ (const Matrix4x4 & anotherMatrix) const {
    
    Matrix4x4 resultMatrix = *this;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            resultMatrix.elems[i][j] += anotherMatrix.elems[i][j];
        }
    }
    
    return resultMatrix;
    
}

/// Присваивающий оператор сложения.
///
/// \param anotherMatrix Вторая матрица.
///
/// \return Ссылка на себя.
Matrix4x4 & Matrix4x4::operator+= (const Matrix4x4 & anotherMatrix) {
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            elems[i][j] += anotherMatrix.elems[i][j];
        }
    }
    
    return *this;
    
}

/// Оператор сложения с числом. Прибавляет к каждому элементу матрицы число number.
///
/// \param number Число.
///
/// \return Матрица, равная сумм.е данной матрицы и числа number.
Matrix4x4 Matrix4x4::operator+ (CalcNumber number) const {
    
    Matrix4x4 resultMatrix = *this;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            resultMatrix.elems[i][j] += number;
        }
    }
    
    return resultMatrix;
    
}

/// Присваивающий оператор сложения с числом. Прибавляет к каждому элементу матрицы число number.
///
/// \param number Число.
///
/// \return Ссылка на себя.
Matrix4x4 & Matrix4x4::operator+= (CalcNumber number) {
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            elems[i][j] += number;
        }
    }
    
    return *this;
    
}

/// Оператор вычитания.
///
/// \param anotherMatrix Вторая матрица.
///
/// \return Матрица, равная разности данной матрицы и anotherMatrix.
Matrix4x4 Matrix4x4::operator- (const Matrix4x4 & anotherMatrix) const {
    
    Matrix4x4 resultMatrix = *this;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            resultMatrix.elems[i][j] -= anotherMatrix.elems[i][j];
        }
    }
    
    return resultMatrix;
    
}

/// Присваивающий оператор вычитания.
///
/// \param anotherMatrix Вторая матрица.
///
/// \return Ссылка на себя.
Matrix4x4 & Matrix4x4::operator-= (const Matrix4x4 & anotherMatrix) {
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            elems[i][j] -= anotherMatrix.elems[i][j];
        }
    }
    
    return *this;
    
}

/// Оператор вычитания числа. Вычитает из каждого элемента матрицы число number.
///
/// \param number Число.
///
/// \return Матрица, равная разности данной матрицы и числа number.
Matrix4x4 Matrix4x4::operator- (CalcNumber number) const {
    
    Matrix4x4 resultMatrix = *this;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            resultMatrix.elems[i][j] -= number;
        }
    }
    
    return resultMatrix;
    
}

/// Присваивающий оператор вычитания числа. Вычитает из каждого элемента матрицы число number.
///
/// \param number Число.
///
/// \return Ссылка на себя.
Matrix4x4 & Matrix4x4::operator-= (CalcNumber number) {
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            elems[i][j] -= number;
        }
    }
    
    return *this;
    
}

/// Оператор умножения на другую матрицу.
///
/// \param anotherMatrix Вторая матрица.
///
/// \return Матрица, равная произведению данной матрицы и anotherMatrix.
Matrix4x4 Matrix4x4::operator* (const Matrix4x4 & anotherMatrix) const {
    
    Matrix4x4 resultMatrix;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            
            CalcNumber val = 0;
            for (int k = 0; k < 4 ; k++) {
                val += elems[i][k] * anotherMatrix.elems[k][j];
            }
            resultMatrix.elems[i][j] = val;
            
        }
    }
    
    return resultMatrix;
    
}

/// Присваивающий оператор умножения на другую матрицу.
///
/// \param anotherMatrix Вторая матрица.
///
/// \return Ссылка на себя.
Matrix4x4 & Matrix4x4::operator*= (const Matrix4x4 & anotherMatrix) {
    
    *this = (*this) * anotherMatrix;
    
    return *this;
    
}

/// Оператор умножения на вектор-столбец, полученный из вектора vector добавлением справа единицы. Результат умножения (вектор-столбец) возвращается без последнего элемента.
///
/// \param vector Вектор.
///
/// \return Результат умножения.
Point Matrix4x4::operator* (const Point & vector) const {
    
    CalcNumber x = vector.x, y = vector.y, z = vector.z;
    
    return Point(
        elems[0][0] * x + elems[0][1] * y + elems[0][2] * z + elems[0][3],
        elems[1][0] * x + elems[1][1] * y + elems[1][2] * z + elems[1][3],
        elems[2][0] * x + elems[2][1] * y + elems[2][2] * z + elems[2][3]
    );
    
}

/// Оператор умножения на число. Умножает каждый элемент матрицы на число number.
///
/// \param number Число.
///
/// \return Матрица, равная произведению данной матрицы и числа number.
Matrix4x4 Matrix4x4::operator* (CalcNumber number) const {
    
    Matrix4x4 resultMatrix = *this;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            resultMatrix.elems[i][j] *= number;
        }
    }
    
    return resultMatrix;
    
}

/// Присваивающий оператор умножения на число. Умножает каждый элемент матрицы на число number.
///
/// \param number Число.
///
/// \return Ссылка на себя.
Matrix4x4 & Matrix4x4::operator*= (CalcNumber number) {
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            elems[i][j] *= number;
        }
    }
    
    return *this;
    
}

/// Оператор деления на число. Делит каждый элемент матрицы на число number.
///
/// \param number Число.
///
/// \return Матрица, равная частному данной матрицы и числа number.
Matrix4x4 Matrix4x4::operator/ (CalcNumber number) const {
    
    Matrix4x4 resultMatrix = *this;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            resultMatrix.elems[i][j] /= number;
        }
    }
    
    return resultMatrix;
    
}

/// Присваивающий оператор деления на число. Делит каждый элемент матрицы на число number.
///
/// \param number Число.
///
/// \return Ссылка на себя.
Matrix4x4 & Matrix4x4::operator/= (CalcNumber number) {
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            elems[i][j] /= number;
        }
    }
    
    return *this;
    
}

/// Вернуть противоположную матрицу к данной.
///
/// \return Противоположная матрица к данной.
Matrix4x4 Matrix4x4::opposed() const {
    
    return Matrix4x4(
        -elems[0][0], -elems[0][1], -elems[0][2], -elems[0][3],
        -elems[1][0], -elems[1][1], -elems[1][2], -elems[1][3],
        -elems[2][0], -elems[2][1], -elems[2][2], -elems[2][3],
        -elems[3][0], -elems[3][1], -elems[3][2], -elems[3][3]
    );
    
}

/// Заменить матрицу на противоположную.
///
/// \return Ссылка на себя.
Matrix4x4 & Matrix4x4::oppose() {
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            elems[i][j] = -elems[i][j];
        }
    }
    
    return *this;
    
}

/// Вернуть транспонированную матрицу к данной.
///
/// \return Транспонированная матрица к данной.
Matrix4x4  Matrix4x4::transposed() const {
    
    return Matrix4x4(
        elems[0][0], elems[1][0], elems[2][0], elems[3][0],
        elems[0][1], elems[1][1], elems[2][1], elems[3][1],
        elems[0][2], elems[1][2], elems[2][2], elems[3][2],
        elems[0][3], elems[1][3], elems[2][3], elems[3][3]
    );
    
}

/// Транспонировать матрицу.
///
/// \return Ссылка на себя.
Matrix4x4 & Matrix4x4::transpose() {
    
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            CalcNumber temp = elems[i][j];
            elems[i][j] = elems[j][i];
            elems[j][i] = temp;
        }
    }
    
    return *this;
    
}

/// Вернуть обратную матрицу к данной. Данная матрица должна быть обратимой.
///
/// \return Обратная матрица к данной.
Matrix4x4 Matrix4x4::inversed() const {
    
    // 1. Создается временная матрица tempMatrix, равная данной матрице.
    CalcNumber tempMatrix[4][4];
    std::memcpy(tempMatrix, this->elems, 16 * sizeof(CalcNumber));
    
    // 1. Создается единичная матрица resultMatrix.
    CalcNumber resultMatrix[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            resultMatrix[i][j] = 0;
        }
        resultMatrix[i][i] = 1;
    }
    
    // 2. Матрица tempMatrix приводится к диагональному виду с помощью преобразований Гаусса. Эти же преобразования применяются и к resultMatrix.
    for (int i = 0; i < 4; i++) {
        
        // 2.1. Если элемент [i][i] матрицы tempMatrix равен нулю, а элемент [k][i] не равен нулю для некоторого k > i, то i-я и k-я строчки меняются местами в обеих матрицах. Если же для всех k >= i элементы [k][i] равны нулю, то определитель исходной матрицы равен нулю.
        for (int k = i; k < 4; k++) {
            if (tempMatrix[k][i] != 0) {
                if (k > i) {
                    CalcNumber tempRow[4];
                    std::memcpy(tempRow, tempMatrix[i], 4 * sizeof(CalcNumber));
                    std::memcpy(tempMatrix[i], tempMatrix[k], 4 * sizeof(CalcNumber));
                    std::memcpy(tempMatrix[k], tempRow, 4 * sizeof(CalcNumber));
                    std::memcpy(tempRow, resultMatrix[i], 4 * sizeof(CalcNumber));
                    std::memcpy(resultMatrix[i], resultMatrix[k], 4 * sizeof(CalcNumber));
                    std::memcpy(resultMatrix[k], tempRow, 4 * sizeof(CalcNumber));
                }
                break;
            }
            if (k == 3) {
                assert(false);
            }
        }
        
        // 2.2. Выполняются преобразования Гаусса для строчек k > i обеих матриц, в результате которых обнуляются элементы [k][i] матрицы tempMatrix.
        for (int k = i + 1; k < 4; k++) {
            CalcNumber coef = tempMatrix[k][i] / tempMatrix[i][i];
            tempMatrix[k][i] = 0;
            for (int j = i + 1; j < 4; j++) {
                tempMatrix[k][j] -= tempMatrix[i][j] * coef;
            }
            for (int j = 0; j < 4; j++) {
                resultMatrix[k][j] -= resultMatrix[i][j] * coef;
            }
        }
    }
    
    // 3. Диагональная матрица tempMatrix приводится к единичному виду с помощью преобразований Гаусса. Эти же преобразования применяются и к resultMatrix.
    
    for (int i = 3; i >= 0; i--) {
     
        // 3.1. Строчки i обеих матриц делятся на элемент [i][i] матрицы tempMatrix.
        CalcNumber coef = 1.0 / tempMatrix[i][i];
        tempMatrix[i][i] = 1;
        for (int j = 0; j < 4; j++) {
            resultMatrix[i][j] *= coef;
        }
        
        // 3.2. Выполняются преобразования Гаусса для строчек k < i обеих матриц, в результате которых обнуляются элементы [k][i] матрицы tempMatrix.
        for (int k = i - 1; k >= 0; k--) {
            CalcNumber coef = tempMatrix[k][i];
            tempMatrix[k][i] = 0;
            for (int j = 0; j < 4; j++) {
                resultMatrix[k][j] -= resultMatrix[i][j] * coef;
            }
        }
        
    }

    // 4. Возвращается resultMatrix.
    return Matrix4x4(resultMatrix);
    
}

/// Обратить матрицу. Матрица должна быть обратимой.
///
/// \return Ссылка на себя.
Matrix4x4 & Matrix4x4::inverse() {
    
    *this = this->inversed();
    
    return *this;
    
}

/// Оператор умножения вектора-строки на матрицу matrix. Вектор-строка получается из вектора vector добавлением справа единицы. Результат умножения (вектор-строка) возвращается без последнего элемента.
///
/// \param vector Вектор.
/// \param matrix Матрица.
///
/// \return Результат умножения.
Point operator* (const Point & vector, const Matrix4x4 & matrix) {
    
    CalcNumber x = vector.x, y = vector.y, z = vector.z;
    
    return Point(
        matrix.elems[0][0] * x + matrix.elems[1][0] * y + matrix.elems[2][0] * z + matrix.elems[3][0],
        matrix.elems[0][1] * x + matrix.elems[1][1] * y + matrix.elems[2][1] * z + matrix.elems[3][1],
        matrix.elems[0][2] * x + matrix.elems[1][2] * y + matrix.elems[2][2] * z + matrix.elems[3][2]
    );
    
}

/// Присваивающий оператор умножения вектора-строки на матрицу matrix. Вектор-строка получается из вектора vector добавлением справа единицы. Результат умножения (вектор-строка) возвращается без последнего элемента.
///
/// \param vector Вектор.
/// \param matrix Матрица.
///
/// \return Ссылка на измененную вектор-строку.
Point & operator*= (Point & vector, const Matrix4x4 & matrix) {
    
    vector = vector * matrix;
    
    return vector;
    
}

#endif /* Matrix4x4_hpp */
