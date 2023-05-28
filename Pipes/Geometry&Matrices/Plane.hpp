#ifndef Plane_hpp
#define Plane_hpp

// Подключение стандартных библиотек
#include <cassert>
#include <math.h>

// Подключение внутренних типов
#include "CalcNumber.hpp"
#include "Object.hpp"
#include "Point.hpp"
#include "SoLESolver.hpp"

/// Плоскость.
class Plane: public Object {
    
    /*
     
     Реализация структуры хранит представление плоскости в виде четверки (A, B, C, D), определяющей общее уравнение плоскости Ax + By + Cz + D = 0 (A, B, C одновременно не равны нулю, sqrt(A^2 + B^2 + C^2) = 1).
     
     */
    
    // MARK: - Скрытые объекты
    
    /// Параметр A в общем уравнении плоскости Ax + By + Cz + D = 0.
    CalcNumber _a;
    
    /// Параметр B в общем уравнении плоскости Ax + By + Cz + D = 0.
    CalcNumber _b;
    
    /// Параметр C в общем уравнении плоскости Ax + By + Cz + D = 0.
    CalcNumber _c;
    
    /// Параметр D в общем уравнении плоскости Ax + By + Cz + D = 0.
    CalcNumber _d;
    
public:
    
    // MARK: - Конструкторы
    
    /// Конструктор. Параметры A, B, C одновременно не должны быть равны нулю.
    ///
    /// \param a Параметр A в общем уравнении плоскости Ax + By + Cz + D = 0.
    /// \param b Параметр B в общем уравнении плоскости Ax + By + Cz + D = 0.
    /// \param c Параметр C в общем уравнении плоскости Ax + By + Cz + D = 0.
    /// \param d Параметр D в общем уравнении плоскости Ax + By + Cz + D = 0.
    explicit Plane(CalcNumber a, CalcNumber b, CalcNumber c, CalcNumber d);
    
    // MARK: - Открытые методы
    
    /// Вернуть параметра A общего уравнения плоскости Ax + By + Cz + D = 0.
    ///
    /// \return Параметр A.
    CalcNumber a() const;
    
    /// Вернуть параметра B общего уравнения плоскости Ax + By + Cz + D = 0.
    ///
    /// \return Параметр B.
    CalcNumber b() const;
    
    /// Вернуть параметра C общего уравнения плоскости Ax + By + Cz + D = 0.
    ///
    /// \return Параметр C.
    CalcNumber c() const;
    
    /// Вернуть параметра D общего уравнения плоскости Ax + By + Cz + D = 0.
    ///
    /// \return Параметр D.
    CalcNumber d() const;
    
    /// Вернуть нормаль единичной длины.
    ///
    /// \return Нормаль единичной длины.
    Point normalVector() const;
    
    /// Вернуть проекцию точки point на плоскость.
    ///
    /// \param point Точка.
    ///
    /// \returns Проекция точки point на плоскость.
    Point projectionForPoint(const Point & point);
    
    /// Вернуть расстояние от точки point до плоскости.
    ///
    /// \param point Точка.
    ///
    /// \returns Расстояние от точки point до плоскости.
    CalcNumber distanceToPoint(const Point & point);
    
    /// Проверить, принадлежит ли точка point плоскости.
    ///
    /// При проверке учитывается статический параметр lengthEpsilon. Если расстоние от точки до плоскости не превосходит lengthEpsilon, то точка считается принадлежащей плоскости. Иначе точка считается не принадлежащей плоскости.
    ///
    /// \param point Точка.
    ///
    /// \returns true, если точка point принадлежит плоскости, иначе false.
    bool contains(const Point & point);
    
};

// MARK: - Реализация

/// Конструктор. Параметры A, B, C одновременно не должны быть равны нулю.
///
/// \param a Параметр A в общем уравнении плоскости Ax + By + Cz + D = 0.
/// \param b Параметр B в общем уравнении плоскости Ax + By + Cz + D = 0.
/// \param c Параметр C в общем уравнении плоскости Ax + By + Cz + D = 0.
/// \param d Параметр D в общем уравнении плоскости Ax + By + Cz + D = 0.
Plane::Plane(CalcNumber a, CalcNumber b, CalcNumber c, CalcNumber d): _a(a), _b(b), _c(c), _d(d) {
    
    assert(a != 0 || b != 0 || c != 0);
    
    // Нормализация параметров a, b, c, d
    CalcNumber normMult = sqrt(a * a + b * b + c * c);
    this->_a /= normMult;
    this->_b /= normMult;
    this->_c /= normMult;
    this->_d /= normMult;
    
}

/// Вернуть параметра A общего уравнения плоскости Ax + By + Cz + D = 0.
///
/// \return Параметр A.
CalcNumber Plane::a() const {
    
    return _a;
    
}

/// Вернуть параметра B общего уравнения плоскости Ax + By + Cz + D = 0.
///
/// \return Параметр B.
CalcNumber Plane::b() const {
    
    return _b;
    
}

/// Вернуть параметра C общего уравнения плоскости Ax + By + Cz + D = 0.
///
/// \return Параметр C.
CalcNumber Plane::c() const {
    
    return _c;
    
}

/// Вернуть параметра D общего уравнения плоскости Ax + By + Cz + D = 0.
///
/// \return Параметр D.
CalcNumber Plane::d() const {
    
    return _d;
    
}

/// Вернуть нормаль единичной длины.
///
/// \return Нормаль единичной длины.
Point Plane::normalVector() const {
    
    return Point(this->_a, this->_b, this->_c);
    
}

/// Вернуть проекцию точки point на плоскость.
///
/// \param point Точка.
///
/// \returns Проекция точки point на плоскость.
Point Plane::projectionForPoint(const Point & point) {
    
    /// \todo исправить, определитель может быть равен нулю
    return SoLESolver::solveSoLE3x3WithNonZeroDeterminant(
                        _b, -_a, 0, _b * point.x - _a * point.y,
                        _c, 0, -_a, _c * point.x - _a * point.z,
                        _a, _b, _c, -_d
    );
    
}

/// Вернуть расстояние от точки point до плоскости.
///
/// \param point Точка.
///
/// \returns Расстояние от точки point до плоскости.
CalcNumber Plane::distanceToPoint(const Point & point) {
    
    return abs(_a * point.x + _b * point.y + _c * point.z + _d);
    
}

/// Проверить, принадлежит ли точка point плоскости.
///
/// При проверке учитывается статический параметр lengthEpsilon. Если расстоние от точки до плоскости не превосходит lengthEpsilon, то точка считается принадлежащей плоскости. Иначе точка считается не принадлежащей плоскости.
///
/// \param point Точка.
///
/// \returns true, если точка point принадлежит плоскости, иначе false.
bool Plane::contains(const Point & point) {
    
    return (distanceToPoint(point) <= lengthEpsilon);
    
}

#endif /* Plane_hpp */
