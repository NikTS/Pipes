#ifndef PlaneTester_hpp
#define PlaneTester_hpp

// Подключение стандартных библиотек
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

// Подключение внутренних типов
#include "Plane.hpp"

/// Тестер для класса Plane.
class PlaneTester {
    
public:
    
    // MARK: - Открытые методы
    
    /// Тестировать класс Plane.
    void test();
    
};

// MARK: - Реализация

/// Тестировать класс Plane.
void PlaneTester::test() {
    
    Plane plane { 1, 1, 1, 1 };
    
    assert(plane.a() == 1 / sqrt(3));
    assert(plane.b() == 1 / sqrt(3));
    assert(plane.c() == 1 / sqrt(3));
    assert(plane.d() == 1 / sqrt(3));
    assert(plane.normalVector() == Point(1, 1, 1) / sqrt(3));
    assert(plane.projectionForPoint(Point(0, 0, -1)) == Point(0, 0, -1));
    assert((plane.projectionForPoint(Point(1, 2, 0)) - Point(-1.0/3, 2.0/3, -4.0/3)).maxAbs() < 1e-6);
    assert(plane.distanceToPoint(Point(0, 0, -1)) == 0);
    assert(plane.distanceToPoint(Point(1, 2, 0)) == 4/sqrt(3));
    assert(plane.contains(Point(0, 0, -1)) == true);
    assert(plane.contains(Point(1, 2, 0)) == false);
    
    std::cout << "Тестирование класса Plane завершилось успешно.\n";
    
}

#endif /* PlaneTester_hpp */
