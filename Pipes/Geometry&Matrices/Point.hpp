#ifndef Point_hpp
#define Point_hpp

// Подключение стандартных библиотек
#include <math.h>

// Подключение внутренних типов
#include "CalcNumber.hpp"
#include "Object.hpp"

/// Точка.
class Point: public Object {
    
public:
    
    // MARK: - Открытые объекты
    
    /// \brief X-координата.
    CalcNumber x;
    
    /// \brief Y-координата.
    CalcNumber y;
    
    /// \brief Z-координата.
    CalcNumber z;
    
    // MARK: - Конструкторы
    
    /// \brief Конструктор.
    ///
    /// \param x X-координата.
    /// \param y Y-координата.
    /// \param z Z-координата.
    explicit Point(CalcNumber x, CalcNumber y, CalcNumber z);
    
    /// \brief Конструктор по умолчанию. Создается точка (0, 0, 0).
    explicit Point();
    
    // MARK: - Открытые методы
    
    /// \brief Оператор сравнения.
    ///
    /// \param anotherPoint Вторая точка.
    ///
    /// \return true, если координаты точек совпадают, иначе false.
    bool operator==(const Point & anotherPoint) const;
    
    /// \brief Оператор сравнения.
    ///
    /// \param anotherPoint Вторая точка.
    ///
    /// \return true, если координаты точек не совпадают, иначе true.
    bool operator!=(const Point & anotherPoint) const;
    
    /// \brief Вернуть модуль максимальной по модулю координаты.
    ///
    /// \return Модуль максимальной по модулю координаты.
    CalcNumber maxAbs() const;
    
    /// Оператор сложения. Выполняет покоординатное сложение.
    ///
    /// \param anotherPoint Вторая точка.
    ///
    /// \return Точка, равная сумм.е данной точки и anotherPoint.
    Point operator+ (const Point & anotherPoint) const;
    
    /// Присваивающий оператор сложения. Выполняет покоординатное сложение.
    ///
    /// \param anotherPoint Вторая точка.
    ///
    /// \return Ссылка на себя.
    Point & operator+= (const Point & anotherPoint);
    
    /// Оператор сложения с числом. Прибавляет к каждой координате число number.
    ///
    /// \param number Число.
    ///
    /// \return Точка, равная сумм.е данной точки и числа number.
    Point operator+ (CalcNumber number) const;
    
    /// Присваивающий оператор сложения с числом. Прибавляет к каждой координате число number.
    ///
    /// \param number Число.
    ///
    /// \return Ссылка на себя.
    Point & operator+= (CalcNumber number);
    
    /// Оператор вычитания. Выполняет покоординатное вычитание.
    ///
    /// \param anotherPoint Вторая точка.
    ///
    /// \return Точка, равная разности данной точки и anotherPoint.
    Point operator- (const Point & anotherPoint) const;
    
    /// Присваивающий оператор вычитания. Выполняет покоординатное вычитание.
    ///
    /// \param anotherPoint Вторая точка.
    ///
    /// \return Ссылка на себя.
    Point & operator-= (const Point & anotherPoint);
    
    /// Оператор вычитания числа. Вычитает из каждой координаты число number.
    ///
    /// \param number Число.
    ///
    /// \return Точка, равная разности данной точки и числа number.
    Point operator- (CalcNumber number) const;
    
    /// Присваивающий оператор вычитания числа. Вычитает из каждой координаты число number.
    ///
    /// \param number Число.
    ///
    /// \return Ссылка на себя.
    Point & operator-= (CalcNumber number);
    
    /// Оператор умножения на число. Выполняет покоординатное умножение.
    ///
    /// \param number Число.
    ///
    /// \return Точка, равная произведения данной точки и числа number.
    Point operator* (CalcNumber number) const;
    
    /// Присваивающий оператор умножения на число. Выполняет покоординатное умножение.
    ///
    /// \param number Число.
    ///
    /// \return Ссылка на себя.
    Point & operator*= (CalcNumber number);
    
    /// Оператор деления на число. Выполняет покоординатное деление.
    ///
    /// \param number Число.
    ///
    /// \return Точка, равная частному данной точки и числа number.
    Point operator/ (CalcNumber number) const;
    
    /// Присваивающий оператор деления на число. Выполняет покоординатное деление.
    ///
    /// \param number Число.
    ///
    /// \return Ссылка на себя.
    Point & operator/= (CalcNumber number);
    
    /// Вернуть скалярное произведение двух векторов. Первый вектор определяется данной точкой, второй - точкой secondPoint.
    ///
    /// \param secondPoint Точка, определяющая второй вектор.
    ///
    /// \return Скалярное произведение.
    CalcNumber scalarProdWith(const Point & secondPoint) const;
    
    /// Вернуть векторное произведение двух векторов. Первый вектор определяется данной точкой, второй - точкой secondPoint.
    ///
    /// \param secondPoint Точка, определяющая второй вектор.
    ///
    /// \return Векторное произведение.
    Point vectorProdWith(const Point & secondPoint) const;
    
    /// Вернуть длину вектора, определяемого данной точкой.
    ///
    /// \return Длина вектора.
    CalcNumber length() const;
    
    /// Вернуть расстояние от точки point до данной точки.
    ///
    /// \param point Точка.
    ///
    /// \returns Расстояние от точки point до данной точки.
    CalcNumber distanceToPoint(const Point & point);
    
    /// Проверить, принадлежит ли точка point данной точке.
    ///
    /// При проверке учитывается статический параметр lengthEpsilon. Если расстоние от точки до данной точки не превосходит lengthEpsilon, то точка считается принадлежащей данной точке. Иначе точка считается не принадлежащей данной точке.
    ///
    /// \param point Точка.
    ///
    /// \returns true, если точка point принадлежит данной точке, иначе false.
    bool contains(const Point & point);
    
};

// MARK: - Внешние операторы

/// Оператор умножения числа на точку. Выполняет покоординатное умножение.
///
/// \param number Число.
/// \param point Точка.
///
/// \return Точка, равная произведения точки point и числа number.
Point operator* (CalcNumber number, const Point & point);

// MARK: - Реализация

/// Конструктор.
///
/// \param x X-координата.
/// \param y Y-координата.
/// \param z Z-координата.
Point::Point(CalcNumber x, CalcNumber y, CalcNumber z): x(x), y(y), z(z) {}

/// Конструктор по умолчанию. Создается точка (0, 0, 0).
Point::Point(): Point(0, 0, 0) {}

/// Оператор сравнения.
///
/// \param anotherPoint Вторая точка.
///
/// \return true, если координаты точек совпадают, иначе false.
bool Point::operator==(const Point & anotherPoint) const {
    
    return (this->x == anotherPoint.x && this->y == anotherPoint.y && this->z == anotherPoint.z);
    
}

/// Оператор сравнения.
///
/// \param anotherPoint Вторая точка.
///
/// \return true, если координаты точек  не совпадают, иначе true.
bool Point::operator!=(const Point & anotherPoint) const {
    
    return ((*this == anotherPoint) == false);
    
}

/// Вернуть модуль максимальной по модулю координаты.
///
/// \return Модуль максимальной по модулю координаты.
CalcNumber Point::maxAbs() const {
    
    CalcNumber maxAbs = abs(x);
    
    if (abs(y) > maxAbs) {
        maxAbs = abs(y);
    }
    
    if (abs(z) > maxAbs) {
        maxAbs = abs(z);
    }
    
    return maxAbs;
    
}

/// Оператор сложения. Выполняет покоординатное сложение.
///
/// \param anotherPoint Вторая точка.
///
/// \return Точка, равная сумм.е данной точки и anotherPoint.
Point Point::operator+ (const Point & anotherPoint) const {
    
    return Point(
        this->x + anotherPoint.x,
        this->y + anotherPoint.y,
        this->z + anotherPoint.z
    );
    
}

/// Присваивающий оператор сложения. Выполняет покоординатное сложение.
///
/// \param anotherPoint Вторая точка.
///
/// \return Ссылка на себя.
Point & Point::operator+= (const Point & anotherPoint) {
    
    this->x += anotherPoint.x;
    this->y += anotherPoint.y;
    this->z += anotherPoint.z;
    
    return *this;
    
}

/// Оператор сложения с числом. Прибавляет к каждой координате число number.
///
/// \param number Число.
///
/// \return Точка, равная сумм.е данной точки и числа number.
Point Point::operator+ (CalcNumber number) const {
    
    return Point(
        this->x + number,
        this->y + number,
        this->z + number
    );
    
}

/// Присваивающий оператор сложения с числом. Прибавляет к каждой координате число number.
///
/// \param number Число.
///
/// \return Ссылка на себя.
Point & Point::operator+= (CalcNumber number) {
    
    this->x += number;
    this->y += number;
    this->z += number;
    
    return *this;
    
}

/// Оператор вычитания. Выполняет покоординатное вычитание.
///
/// \param anotherPoint Вторая точка.
///
/// \return Точка, равная разности данной точки и anotherPoint.
Point Point::operator- (const Point & anotherPoint) const {
    
    return Point(
        this->x - anotherPoint.x,
        this->y - anotherPoint.y,
        this->z - anotherPoint.z
    );
    
}

/// Присваивающий оператор вычитания. Выполняет покоординатное вычитание.
///
/// \param anotherPoint Вторая точка.
///
/// \return Ссылка на себя.
Point & Point::operator-= (const Point & anotherPoint) {
    
    this->x -= anotherPoint.x;
    this->y -= anotherPoint.y;
    this->z -= anotherPoint.z;
    
    return *this;
    
}

/// Оператор вычитания числа. Вычитает из каждой координаты число number.
///
/// \param number Число.
///
/// \return Точка, равная разности данной точки и числа number.
Point Point::operator- (CalcNumber number) const {
    
    return Point(
        this->x - number,
        this->y - number,
        this->z - number
    );
    
}

/// Присваивающий оператор вычитания числа. Вычитает из каждой координаты число number.
///
/// \param number Число.
///
/// \return Ссылка на себя.
Point & Point::operator-= (CalcNumber number) {
    
    this->x -= number;
    this->y -= number;
    this->z -= number;
    
    return *this;
    
}

/// Оператор умножения на число. Выполняет покоординатное умножение.
///
/// \param number Число.
///
/// \return Точка, равная произведения данной точки и числа number.
Point Point::operator* (CalcNumber number) const {
    
    return Point(
        this->x * number,
        this->y * number,
        this->z * number
    );
    
}

/// Присваивающий оператор умножения на число. Выполняет покоординатное умножение.
///
/// \param number Число.
///
/// \return Ссылка на себя.
Point & Point::operator*= (CalcNumber number) {
    
    this->x *= number;
    this->y *= number;
    this->z *= number;
    
    return *this;
    
}

/// Оператор деления на число. Выполняет покоординатное деление.
///
/// \param number Число.
///
/// \return Точка, равная частному данной точки и числа number.
Point Point::operator/ (CalcNumber number) const {
    
    return Point(
        this->x / number,
        this->y / number,
        this->z / number
    );
    
}

/// Присваивающий оператор деления на число. Выполняет покоординатное деление.
///
/// \param number Число.
///
/// \return Ссылка на себя.
Point & Point::operator/= (CalcNumber number) {
    
    this->x /= number;
    this->y /= number;
    this->z /= number;
    
    return *this;
    
}

/// Вернуть скалярное произведение двух векторов. Первый вектор определяется данной точкой, второй - точкой secondPoint.
///
/// \param secondPoint Точка, определяющая второй вектор.
///
/// \return Скалярное произведение.
CalcNumber Point::scalarProdWith(const Point & secondPoint) const {
    
    return (this->x * secondPoint.x + this->y * secondPoint.y + this->z * secondPoint.z);
    
}

/// Вернуть векторное произведение двух векторов. Первый вектор определяется данной точкой, второй - точкой secondPoint.
///
/// \param secondPoint Точка, определяющая второй вектор.
///
/// \return Векторное произведение.
Point Point::vectorProdWith(const Point & secondPoint) const {
    
    return Point(
            this->y * secondPoint.z - this->z * secondPoint.y,
            this->z * secondPoint.x - this->x * secondPoint.z,
            this->x * secondPoint.y - this->y * secondPoint.x
    );
    
}

/// Вернуть длину вектора, определяемого данной точкой.
///
/// \return Длина вектора.
CalcNumber Point::length() const {
    
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    
}

/// Вернуть расстояние от точки point до данной точки.
///
/// \param point Точка.
///
/// \returns Расстояние от точки point до данной точки.
CalcNumber Point::distanceToPoint(const Point & point) {
    
    CalcNumber dx = point.x - this->x;
    CalcNumber dy = point.y - this->y;
    CalcNumber dz = point.z - this->z;
    
    return sqrt(dx * dx + dy * dy + dz * dz);
    
}

/// Проверить, принадлежит ли точка point данной точке.
///
/// При проверке учитывается статический параметр lengthEpsilon. Если расстоние от точки до данной точки не превосходит lengthEpsilon, то точка считается принадлежащей данной точке. Иначе точка считается не принадлежащей данной точке.
///
/// \param point Точка.
///
/// \returns true, если точка point принадлежит данной точке, иначе false.
bool Point::contains(const Point & point) {
    
    return (distanceToPoint(point) <= lengthEpsilon);
    
}

/// Оператор умножения числа на точку. Выполняет покоординатное умножение.
///
/// \param number Число.
/// \param point Точка.
///
/// \return Точка, равная произведения точки point и числа number.
Point operator* (CalcNumber number, const Point & point) {
    
    return Point(
            point.x * number,
            point.y * number,
            point.z * number
    );
    
}

#endif /* Point_hpp */

