#ifndef SoLESolverTester_hpp
#define SoLESolverTester_hpp

// Подключение стандартных библиотек
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

// Подключение внутренних типов
#include "SoLESolver.hpp"

/// Тестер для класса SoLESolver.
class SoLESolverTester {
    
public:
    
    // MARK: - Открытые методы
    
    /// Тестировать класс SoLESolver.
    void test();
    
};

// MARK: - Реализация

/// Тестировать класс SoLESolver.
void SoLESolverTester::test() {
    
    assert(SoLESolver::solveSoLE3x3WithNonZeroDeterminant(2, -2, 1, -3, 1, 3, -2, 1, 3, -1, -1, 2) == Point(-1.4, -2, -4.2));
    
    std::cout << "Тестирование класса SoLESolver завершилось успешно.\n";
    
}


#endif /* SoLESolverTester_hpp */
