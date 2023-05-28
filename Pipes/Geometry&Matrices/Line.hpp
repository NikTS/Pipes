#ifndef Line_hpp
#define Line_hpp

// Подключение внутренних типов
#include "CalcNumber.hpp"
#include "Object.hpp"
#include "Point.hpp"
#include "SoLESolver.hpp"

/// Прямая.
class Line: public Object {
    
    /*
     
     Реализация структуры хранит представление прямой в виде двух несовпадающих точек A и B, принадлежащих данной прямой.
     
     */
    
    // MARK: - Скрытые объекты
    
    /// Первая точка, принадлежащая прямой.
    Point _a;
    
    /// Вторая точка, принадлежащая прямой.
    Point _b;
    
    /// Флаг, равный true, если directionVector верно корректно настроен, иначе false.
    bool _directionVectorIsCalculated;
    
    /// Направляющий вектор единичной длины.
    Point _directionVector;
    
public:
    
    // MARK: - Конструкторы
    
    /// Конструктор, принимающий на вход две несовпадающие точки A и B, принадлежащие прямой. Точки не должны совпадать.
    ///
    /// \param a Первая точка, принадлежащая прямой.
    /// \param b Вторая точка, принадлежащая прямой.
    explicit Line(Point a, Point b);
    
    // MARK: - Открытые методы
    
    /// Вернуть первую точку, принадлежащую прямой.
    ///
    /// \return Первая точка.
    Point a() const;
    
    /// Вернуть вторую точку, принадлежащую прямой.
    ///
    /// \return Вторая точка.
    Point b() const;
    
    /// Вернуть направляющий вектор единичной длины.
    ///
    /// \return Направляющий вектор единичной длины.
    Point directionVector();
    
    /// Вернуть проекцию точки point на прямую.
    ///
    /// \param point Точка.
    ///
    /// \returns Проекция точки point на прямую.
    Point projectionForPoint(const Point & point);
    
    /// Вернуть расстояние от точки point до прямой.
    ///
    /// \param point Точка.
    ///
    /// \returns Расстояние от точки point до прямой.
    CalcNumber distanceToPoint(const Point & point);
    
    /// Проверить, принадлежит ли точка point прямой.
    ///
    /// При проверке учитывается статический параметр lengthEpsilon. Если расстоние от точки до прямой не превосходит lengthEpsilon, то точка считается принадлежащей прямой. Иначе точка считается не принадлежащей прямой.
    ///
    /// \param point Точка.
    ///
    /// \returns true, если точка point принадлежит прямой, иначе false.
    bool contains(const Point & point);
    
};

// MARK: - Реализация

/// Конструктор, принимающий на вход две несовпадающие точки A и B, принадлежащие прямой. Точки не должны совпадать.
///
/// \param a Первая точка, принадлежащая прямой.
/// \param b Вторая точка, принадлежащая прямой.
Line::Line(Point a, Point b): _a(a), _b(b), _directionVectorIsCalculated(false), _directionVector(0, 0, 0) {
    
    assert(a != b);
    
}

/// Вернуть первую точку, принадлежащую прямой.
///
/// \return Первая точка.
Point Line::a() const {
    
    return _a;
    
}

/// Вернуть вторую точку, принадлежащую прямой.
///
/// \return Вторая точка.
Point Line::b() const {
    
    return _b;
    
}

/// Вернуть направляющий вектор единичной длины.
///
/// \return Направляющий вектор единичной длины.
Point Line::directionVector() {
    
    // Реализация 1) рассчитывает направляющий вектор единичной длины в случае необходимости, 2) возвращает данный вектор.
    
    if (_directionVectorIsCalculated == false) {
        
        _directionVector = Point(_b.x - _a.x, _b.y - _a.y, _b.z - _a.z);
        
        // Нормализация направляющего вектора
        CalcNumber normMult = _directionVector.length();
        _directionVector.x /= normMult;
        _directionVector.y /= normMult;
        _directionVector.z /= normMult;
        
        _directionVectorIsCalculated = true;
        
    }
    
    return _directionVector;
    
}

/// Вернуть проекцию точки point на прямую.
///
/// \param point Точка.
///
/// \returns Проекция точки point на прямую.
Point Line::projectionForPoint(const Point & point) {
    
    Point lineDirection = directionVector();
    
    CalcNumber ldx = lineDirection.x, ldy = lineDirection.y, ldz = lineDirection.z;
    
    /// \todo исправить, определитель может быть равен нулю
    return SoLESolver::solveSoLE3x3WithNonZeroDeterminant(
                        ldy, -ldx, 0, ldy * _a.x - ldx * _a.y,
                        ldz, 0, -ldx, ldz * _a.x - ldx * _a.z,
                        ldx, ldy, ldz, lineDirection.scalarProdWith(point)
    );
    
}

/// Вернуть расстояние от точки point до прямой.
///
/// \param point Точка.
///
/// \returns Расстояние от точки point до прямой.
CalcNumber Line::distanceToPoint(const Point & point) {
    
    Point aToPointVector = point - _a;
    return aToPointVector.vectorProdWith(directionVector()).length();
    
}

/// Проверить, принадлежит ли точка point прямой.
///
/// При проверке учитывается статический параметр lengthEpsilon. Если расстоние от точки до прямой не превосходит lengthEpsilon, то точка считается принадлежащей прямой. Иначе точка считается не принадлежащей прямой.
///
/// \param point Точка.
///
/// \returns true, если точка point принадлежит прямой, иначе false.
bool Line::contains(const Point & point) {
    
    return (distanceToPoint(point) <= Object::lengthEpsilon);
    
}

#endif /* Line_hpp */
