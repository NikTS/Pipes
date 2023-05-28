#ifndef LineTester_hpp
#define LineTester_hpp

// Подключение стандартных библиотек
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

// Подключение внутренних типов
#include "Line.hpp"

/// Тестер для класса Line.
class LineTester {
    
public:
    
    // MARK: - Открытые методы
    
    /// Тестировать класс Line.
    void test();
    
};

// MARK: - Реализация

/// Тестировать класс Line.
void LineTester::test() {
    
    Line line { Point(1, 0, 0), Point(0, -1, 0) };
    
    assert(line.a() == Point(1, 0, 0));
    assert(line.b() == Point(0, -1, 0));
    assert(line.directionVector() == Point(-1, -1, 0) / sqrt(2));
    assert(line.projectionForPoint(Point(1, 0, 0)) == Point(1, 0, 0));
    assert(line.projectionForPoint(Point(0, 0, 1)) == Point(0.5, -0.5, 0));
    assert(line.distanceToPoint(Point(1, 0, 0)) == 0);
    assert(line.distanceToPoint(Point(0, 0, 1)) == sqrt(1.5));
    assert(line.contains(Point(1, 0, 0)) == true);
    assert(line.contains(Point(0.5, -0.5, 0)) == true);
    assert(line.contains(Point(0.5, 0.5, 0)) == false);
    assert(line.contains(Point(0.5, -0.5, 1)) == false);
    
    std::cout << "Тестирование класса Line завершилось успешно.\n";
    
}

#endif /* LineTester_hpp */
