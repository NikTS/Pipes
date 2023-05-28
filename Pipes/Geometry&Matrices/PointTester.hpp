#ifndef PointTester_hpp
#define PointTester_hpp

// Подключение стандартных библиотек
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

// Подключение внутренних типов
#include "Point.hpp"

/// Тестер для класса Point.
class PointTester {
    
public:
    
    // MARK: - Открытые методы
    
    /// Тестировать класс Point.
    void test();
    
};

// MARK: - Реализация

/// Тестировать класс Point.
void PointTester::test() {
    
    Point p { 1, 2, 3 };
    assert(p.x == 1);
    assert(p.y == 2);
    assert(p.z == 3);
    
    p.x = 6;
    p.y = 7;
    p.z = 8;
    assert(p.x == 6);
    assert(p.y == 7);
    assert(p.z == 8);
    
    assert(p == p);
    assert((p != p) == false);
    
    assert(Point(1, 2, 3) == Point(1, 2, 3));
    assert(Point(1, 5, 3) != Point(1, 2, 3));
    assert(Point(1, 2, 3) != Point(1, 2, 4));
    assert(Point(0, 2, 3) != Point(1, 2, 3));
    
    Point p2 = p;
    assert(p2 == p);
    
    Point p3 { 4, 5, 6 };
    p3 = p;
    assert(p3 == p2);
    
    p3.x = 10;
    assert(p2 == p);
    
    assert(Point(1, 2, 3).maxAbs() == 3);
    assert(Point(1, -4, 3).maxAbs() == 4);
    assert(Point(-10, 2, 3).maxAbs() == 10);
    
    assert(Point(1, 2, 3) + Point(10, 20, 30) == Point(11, 22, 33));
    assert((Point(1, 2, 3) += Point(10, 20, 30)) == Point(11, 22, 33));
    assert(Point(1, 2, 3) + 10 == Point(11, 12, 13));
    assert((Point(1, 2, 3) += 10) == Point(11, 12, 13));
    assert(Point(1, 2, 3) - Point(10, 20, 30) == Point(-9, -18, -27));
    assert((Point(1, 2, 3) -= Point(10, 20, 30)) == Point(-9, -18, -27));
    assert(Point(1, 2, 3) - 10 == Point(-9, -8, -7));
    assert((Point(1, 2, 3) -= 10) == Point(-9, -8, -7));
    assert(Point(1, 2, 3) * 2 == Point(2, 4, 6));
    assert((Point(1, 2, 3) *= 2) == Point(2, 4, 6));
    assert(Point(2, 4, 6) / 2 == Point(1, 2, 3));
    assert((Point(2, 4, 6) /= 2) == Point(1, 2, 3));
    assert(Point(1, 2, 3).scalarProdWith(Point(4, 5, 6)) == 32);
    assert(Point(1, 2, 3).vectorProdWith(Point(4, 5, 6)) == Point(-3, 6, -3));
    assert(Point(1, 4, 8).length() == 9);
    assert(Point(1, 2, 3).distanceToPoint(Point(1, 5, 7)) == 5);
    assert(Point(1, 2, 3).contains(Point(1, 2, 3)) == true);
    assert(Point(1, 2, 3).contains(Point(1, 3, 3)) == false);
    assert(2 * Point(1, 2, 3) == Point(2, 4, 6));
    
    std::cout << "Тестирование класса Point завершилось успешно.\n";
    
}

#endif /* PointTester_hpp */
