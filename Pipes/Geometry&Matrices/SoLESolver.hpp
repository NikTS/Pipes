#ifndef SoLESolver_hpp
#define SoLESolver_hpp

// Подключение стандартных библиотек
#include <cassert>

// Подключение внутренних типов
#include "CalcNumber.hpp"
#include "Point.hpp"

/// Решатель СЛАУ (систем линейных алгебраических уравнений).
class SoLESolver {
    
public:
    
    // MARK: - Открытые статические методы
    
    /// Решить СЛАУ с 3 уравнениями и 3 неизвестными с ненулевым главным определителем матрицы коэффициентов системы и вернуть ее решение (которое в данном случае существует и единственно). Метод должен вызываться только для ненулевых главных определителей матрицы коэффициентов системы.
    ///
    /// \param a11 Элемент матрицы a11.
    /// \param a12 Элемент матрицы a12.
    /// \param a13 Элемент матрицы a13.
    /// \param b1 Элемент правой части b1.
    /// \param a21 Элемент матрицы a21.
    /// \param a22 Элемент матрицы a22.
    /// \param a23 Элемент матрицы a23.
    /// \param b2 Элемент правой части b1.
    /// \param a31 Элемент матрицы a31.
    /// \param a32 Элемент матрицы a32.
    /// \param a33 Элемент матрицы a33.
    /// \param b3 Элемент правой части b1.
    ///
    /// \return Решение СЛАУ.
    static Point solveSoLE3x3WithNonZeroDeterminant(CalcNumber a11, CalcNumber a12, CalcNumber a13, CalcNumber b1, CalcNumber a21, CalcNumber a22, CalcNumber a23, CalcNumber b2, CalcNumber a31, CalcNumber a32, CalcNumber a33, CalcNumber b3);
    
};

// MARK: - Реализация

/// Решить СЛАУ с 3 уравнениями и 3 неизвестными с ненулевым главным определителем матрицы коэффициентов системы и вернуть ее решение (которое в данном случае существует и единственно). Метод должен вызываться только для ненулевых главных определителей матрицы коэффициентов системы.
///
/// \param a11 Элемент матрицы a11.
/// \param a12 Элемент матрицы a12.
/// \param a13 Элемент матрицы a13.
/// \param b1 Элемент правой части b1.
/// \param a21 Элемент матрицы a21.
/// \param a22 Элемент матрицы a22.
/// \param a23 Элемент матрицы a23.
/// \param b2 Элемент правой части b1.
/// \param a31 Элемент матрицы a31.
/// \param a32 Элемент матрицы a32.
/// \param a33 Элемент матрицы a33.
/// \param b3 Элемент правой части b1.
///
/// \return Решение СЛАУ.
Point SoLESolver::solveSoLE3x3WithNonZeroDeterminant(CalcNumber a11, CalcNumber a12, CalcNumber a13, CalcNumber b1, CalcNumber a21, CalcNumber a22, CalcNumber a23, CalcNumber b2, CalcNumber a31, CalcNumber a32, CalcNumber a33, CalcNumber b3) {
    
    // 1. Создается временная матрица tempMatrix, равная матрице СЛАУ.
    CalcNumber tempMatrix[3][3];
    tempMatrix[0][0] = a11; tempMatrix[0][1] = a12; tempMatrix[0][2] = a13;
    tempMatrix[1][0] = a21; tempMatrix[1][1] = a22; tempMatrix[1][2] = a23;
    tempMatrix[2][0] = a31; tempMatrix[2][1] = a32; tempMatrix[2][2] = a33;
    
    // 2. Создается вектор-столбец rightPart, равный правой части СЛАУ.
    CalcNumber rightPart[3];
    rightPart[0] = b1; rightPart[1] = b2; rightPart[2] = b3;
    
    // 3. Матрица tempMatrix приводится к диагональному виду с помощью преобразований Гаусса. Те же преобразования применяются и к правой части СЛАУ.
    for (int i = 0; i < 3; i++) {
        
        // 3.1. Если элемент [i][i] матрицы tempMatrix равен нулю, а элемент [k][i] не равен нулю для некоторого k > i, то i-я и k-я строчки матрицы и правой части меняются местами. Если же для всех k >= i элементы [k][i] равны нулю, то определитель матрицы СЛАУ равен нулю.
        for (int k = i; k < 3; k++) {
            if (tempMatrix[k][i] != 0) {
                if (k > i) {
                    CalcNumber tempRow[3];
                    std::memcpy(tempRow, tempMatrix[i], 3 * sizeof(CalcNumber));
                    std::memcpy(tempMatrix[i], tempMatrix[k], 3 * sizeof(CalcNumber));
                    std::memcpy(tempMatrix[k], tempRow, 3 * sizeof(CalcNumber));
                    CalcNumber temp;
                    temp = rightPart[i];
                    rightPart[i] = rightPart[k];
                    rightPart[k] = temp;
                }
                break;
            }
            if (k == 2) {
                assert(false);
            }
        }
        
        // 3.2. Выполняются преобразования Гаусса для строчек k > i, в результате которых обнуляются элементы [k][i] матрицы tempMatrix. Те же преобразования применяются и к правой части СЛАУ.
        for (int k = i + 1; k < 3; k++) {
            CalcNumber coef = tempMatrix[k][i] / tempMatrix[i][i];
            tempMatrix[k][i] = 0;
            for (int j = i + 1; j < 3; j++) {
                tempMatrix[k][j] -= tempMatrix[i][j] * coef;
            }
            rightPart[k] -= rightPart[i] * coef;
        }
    }
    
    // 4. Находится решение СЛАУ.
    CalcNumber z = rightPart[2] / tempMatrix[2][2];
    CalcNumber y = (rightPart[1] - tempMatrix[1][2] * z) / tempMatrix[1][1];
    CalcNumber x = (rightPart[0] - tempMatrix[0][1] * y - tempMatrix[0][2] * z) / tempMatrix[0][0];
    return Point(x, y, z);
    
}

#endif /* SoLESolver_hpp */
