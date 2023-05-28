#ifndef Matrix4x4Tester_hpp
#define Matrix4x4Tester_hpp

// Подключение стандартных библиотек
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

// Подключение внутренних типов
#include "Matrix4x4.hpp"

/// Тестер для класса Matrix4x4.
class Matrix4x4Tester {
    
public:
    
    // MARK: - Открытые методы
    
    /// Тестировать класс Matrix4x4.
    void test();
    
};

// MARK: - Реализация

/// Тестировать класс Matrix4x4.
void Matrix4x4Tester::test() {
    
    Matrix4x4 m1 {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    };
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(m1.elems[i][j] == 4 * i + j + 1);
        }
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m1.elems[i][j] = 100 - (4 * i + j);
        }
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(m1.elems[i][j] == 100 - (4 * i + j));
        }
    }
    
    Matrix4x4 m2 { m1.elems };
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(m2.elems[i][j] == 100 - (4 * i + j));
        }
    }
    
    Matrix4x4 m3;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(m3.elems[i][j] == 0);
        }
    }
    
    Matrix4x4 m4 = m2;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(m4.elems[i][j] == 100 - (4 * i + j));
        }
    }
    
    Matrix4x4 m5;
    m5 = m4;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(m5.elems[i][j] == 100 - (4 * i + j));
        }
    }
    
    m2.elems[0][0] = 12;
    m5.elems[0][0] = 12;
    
    assert(m4.elems[0][0] == 100);
    
    assert(m2 == m5);
    assert(m2 != m4);
    
    m5 = Matrix4x4::getZeroMatrix();
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(m5.elems[i][j] == 0);
        }
    }
    
    m5 = Matrix4x4::getIdentityMatrix();
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(m5.elems[i][j] == ((i == j) ? 1 : 0));
        }
    }
                   
    assert((Matrix4x4::getRotateXMatrix(M_PI / 2) - Matrix4x4(
                    1, 0, 0, 0,
                    0, 0, -1, 0,
                    0, 1, 0, 0,
                    0, 0, 0, 1
    )).maxAbs() < 1e-6);
    
    assert((Matrix4x4::getRotateYMatrix(M_PI / 2) - Matrix4x4(
                    0, 0, 1, 0,
                    0, 1, 0, 0,
                    -1, 0, 0, 0,
                    0, 0, 0, 1
    )).maxAbs() < 1e-6);
    
    assert((Matrix4x4::getRotateZMatrix(M_PI / 2) - Matrix4x4(
                    0, -1, 0, 0,
                    1, 0, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
    )).maxAbs() < 1e-6);
    
    assert(Matrix4x4::getTranslateMatrix(1, 2, 3) == Matrix4x4(
                    1, 0, 0, 1,
                    0, 1, 0, 2,
                    0, 0, 1, 3,
                    0, 0, 0, 1
    ));
    
    assert(Matrix4x4::getTranslateMatrix(Point(1, 2, 3)) == Matrix4x4(
                    1, 0, 0, 1,
                    0, 1, 0, 2,
                    0, 0, 1, 3,
                    0, 0, 0, 1
    ));
    
    assert(Matrix4x4::getTranslateXMatrix(1) == Matrix4x4(
                    1, 0, 0, 1,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
    ));
    
    assert(Matrix4x4::getTranslateYMatrix(2) == Matrix4x4(
                    1, 0, 0, 0,
                    0, 1, 0, 2,
                    0, 0, 1, 0,
                    0, 0, 0, 1
    ));
    
    assert(Matrix4x4::getTranslateZMatrix(3) == Matrix4x4(
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 3,
                    0, 0, 0, 1
    ));
    
    assert(Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
    ).determinant() == -42);
    
    assert(Matrix4x4(
            1, -20, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
    ).maxAbs() == 20);
    
    assert(Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           )
           +
           Matrix4x4(
            5, 2, 3, 0,
            5, 4, 9, 8,
            -4, 2, -2, 4,
            7, 2, 0, -3
           )
           ==
           Matrix4x4(
            6, 4, 6, 4,
            10, 8, 18, 16,
            2, 4, -1, 8,
            14, 4, 0, 0
    ));
    
    assert((Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           )
           +=
           Matrix4x4(
            5, 2, 3, 0,
            5, 4, 9, 8,
            -4, 2, -2, 4,
            7, 2, 0, -3
           ))
           ==
           Matrix4x4(
            6, 4, 6, 4,
            10, 8, 18, 16,
            2, 4, -1, 8,
            14, 4, 0, 0
    ));
    
    assert(Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           )
           + 10
           ==
           Matrix4x4(
            11, 12, 13, 14,
            15, 14, 19, 18,
            16, 12, 11, 14,
            17, 12, 10, 13
    ));
    
    assert((Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           )
           += 10)
           ==
           Matrix4x4(
            11, 12, 13, 14,
            15, 14, 19, 18,
            16, 12, 11, 14,
            17, 12, 10, 13
    ));
    
    assert(Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           )
           -
           Matrix4x4(
            5, 2, 3, 0,
            5, 4, 9, 8,
            -4, 2, -2, 4,
            7, 2, 0, -3
           )
           ==
           Matrix4x4(
            -4, 0, 0, 4,
            0, 0, 0, 0,
            10, 0, 3, 0,
            0, 0, 0, 6
    ));
    
    assert((Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           )
           -=
           Matrix4x4(
            5, 2, 3, 0,
            5, 4, 9, 8,
            -4, 2, -2, 4,
            7, 2, 0, -3
           ))
           ==
           Matrix4x4(
            -4, 0, 0, 4,
            0, 0, 0, 0,
            10, 0, 3, 0,
            0, 0, 0, 6
    ));
    
    assert(Matrix4x4(
            21, 22, 23, 24,
            25, 24, 29, 28,
            26, 22, 21, 24,
            27, 22, 20, 23
           )
           - 10
           ==
           Matrix4x4(
            11, 12, 13, 14,
            15, 14, 19, 18,
            16, 12, 11, 14,
            17, 12, 10, 13
    ));
    
    assert((Matrix4x4(
            21, 22, 23, 24,
            25, 24, 29, 28,
            26, 22, 21, 24,
            27, 22, 20, 23
           )
           -= 10)
           ==
           Matrix4x4(
            11, 12, 13, 14,
            15, 14, 19, 18,
            16, 12, 11, 14,
            17, 12, 10, 13
    ));
    
    assert(Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           )
           *
           Matrix4x4(
            5, 2, 3, 0,
            5, 4, 9, 8,
            -4, 2, -2, 4,
            7, 2, 0, -3
           )
           ==
           Matrix4x4(
            31, 24, 15, 16,
            65, 60, 33, 44,
            64, 30, 34, 8,
            66, 28, 39, 7
    ));
    
    assert((Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           )
           *=
           Matrix4x4(
            5, 2, 3, 0,
            5, 4, 9, 8,
            -4, 2, -2, 4,
            7, 2, 0, -3
           ))
           ==
           Matrix4x4(
            31, 24, 15, 16,
            65, 60, 33, 44,
            64, 30, 34, 8,
            66, 28, 39, 7
    ));
    
    assert(Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           )
           *
           Point(
            5,
            5,
            -4
           )
           ==
           Point(
            7,
            17,
            40
    ));
    
    assert(Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           )
           * 2
           ==
           Matrix4x4(
            2, 4, 6, 8,
            10, 8, 18, 16,
            12, 4, 2, 8,
            14, 4, 0, 6
    ));
    
    assert((Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           )
           *= 2)
           ==
           Matrix4x4(
            2, 4, 6, 8,
            10, 8, 18, 16,
            12, 4, 2, 8,
            14, 4, 0, 6
    ));
    
    assert(Matrix4x4(
            2, 4, 6, 8,
            10, 8, 18, 16,
            12, 4, 2, 8,
            14, 4, 0, 6
           )
           / 2
           ==
           Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
    ));
    
    assert((Matrix4x4(
            2, 4, 6, 8,
            10, 8, 18, 16,
            12, 4, 2, 8,
            14, 4, 0, 6
           )
           /= 2)
           ==
           Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
    ));
    
    assert(Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           ).opposed()
           ==
           Matrix4x4(
            -1, -2, -3, -4,
            -5, -4, -9, -8,
            -6, -2, -1, -4,
            -7, -2, 0, -3
    ));
    
    assert(Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           ).oppose()
           ==
           Matrix4x4(
            -1, -2, -3, -4,
            -5, -4, -9, -8,
            -6, -2, -1, -4,
            -7, -2, 0, -3
    ));
    
    assert(Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           ).transposed()
           ==
           Matrix4x4(
            1, 5, 6, 7,
            2, 4, 2, 2,
            3, 9, 1, 0,
            4, 8, 4, 3
    ));
    
    assert(Matrix4x4(
            1, 2, 3, 4,
            5, 4, 9, 8,
            6, 2, 1, 4,
            7, 2, 0, 3
           ).transpose()
           ==
           Matrix4x4(
            1, 5, 6, 7,
            2, 4, 2, 2,
            3, 9, 1, 0,
            4, 8, 4, 3
    ));
    
    assert((Matrix4x4(
            1, 2, 1, -1,
            2, 8, 2, -2,
            -1, 2, 1, 4,
            4, 2, 0, 0
           ).inversed()
           -
           Matrix4x4(
            0.25, -0.125, 0, 0.25,
            -0.5, 0.25, 0, 0,
            1.65, -0.425, 0.2, -0.15,
            -0.1, -0.05, 0.2, 0.1
    )).maxAbs() < 1e-6);
    
    assert((Matrix4x4(
            1, 2, 1, -1,
            2, 8, 2, -2,
            -1, 2, 1, 4,
            4, 2, 0, 0
           ).inverse()
           -
           Matrix4x4(
            0.25, -0.125, 0, 0.25,
            -0.5, 0.25, 0, 0,
            1.65, -0.425, 0.2, -0.15,
            -0.1, -0.05, 0.2, 0.1
    )).maxAbs() < 1e-6);
    
    assert(Point(1, 2, 3)
           *
           Matrix4x4(
                1, 2, 0, 1,
                0, 4, 0, 0,
                0, 3, -2, 0,
                -10, 0, 14, -6
           )
           ==
           Point(
            -9, 19, 8
    ));
    
    Point point { 1, 2, 3 };
    assert((point
           *=
           Matrix4x4(
                1, 2, 0, 1,
                0, 4, 0, 0,
                0, 3, -2, 0,
                -10, 0, 14, -6
           ))
           ==
           Point(
            -9, 19, 8
    ));
    
    std::cout << "Тестирование класса Matrix4x4 завершилось успешно.\n";
    
}

#endif /* Matrix4x4Tester_hpp */

