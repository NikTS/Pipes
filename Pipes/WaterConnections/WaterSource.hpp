#ifndef WaterSource_hpp
#define WaterSource_hpp

// Подключение стандартных библиотек
#include <cassert>
#include <string>

// Подключение внутренних типов
#include "CalcNumber.hpp"
#include "Point.hpp"

/// Источник воды. Характеризуется 1) именем, 2) точкой подключения, 3) диаметром трубы подключения, 4) направлением трубы подключения (опциональный параметр).
struct WaterSource {
    
private:
    
    // MARK: - Скрытые объекты
    
    /// Имя.
    std::string _name;
    
    /// Точка подключения (единица измерения - мм.).
    Point _point;
    
    /// Диаметр трубы подключения (единица измерения - мм.).
    CalcNumber _diameter;
    
    /// Синус угла наклона трубы к горизонтальной поверхности (плоскости Oxy). Для трубы с вершинами A (ближе к источнику) и B (ближе к стоку) угол считается положительным, если z-координата вершины B меньше, чем вершины A. Данный параметр должен принадлежать множеству [0,1).
    /// \todo может следует убрать данный объект
    CalcNumber _slopeSin;
    
public:
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param name Имя.
    /// \param point Точка подключения (единица измерения - мм.).
    /// \param diameter Диаметр трубы подключения (единица измерения - мм.). Должен быть положительным.
    /// \param slopeSin Синус угла наклона трубы к горизонтальной поверхности (плоскости Oxy). Для трубы с вершинами A (ближе к источнику) и B (ближе к стоку) угол считается положительным, если z-координата вершины B меньше, чем вершины A. Данный параметр должен принадлежать множеству [0,1).
    explicit WaterSource(std::string name, const Point & point, unsigned int diameter, CalcNumber slopeSin);
    
    // MARK: - Открытые методы
    
    /// Вернуть имя точки подключения.
    ///
    /// \return Имя точка подключения.
    std::string name() const;
    
    /// Вернуть точку подключения.
    ///
    /// \return Точка подключения (единица измерения - мм.).
    Point point() const;
    
    /// Вернуть диаметр трубы подключения.
    ///
    /// \return Диаметр трубы подключения (единица измерения - мм.).
    unsigned int diameter() const;
    
    /// Вернуть синус угла наклона трубы к горизонтальной поверхности (плоскости Oxy). Для трубы с вершинами A (ближе к источнику) и B (ближе к стоку) угол считается положительным, если z-координата вершины B меньше, чем вершины A.
    ///
    /// \return Синус угла наклона трубы.
    CalcNumber slopeSin() const;
    
};

// MARK: - Реализация

/// Конструктор.
///
/// \param name Имя.
/// \param point Точка подключения (единица измерения - мм.).
/// \param diameter Диаметр трубы подключения (единица измерения - мм.). Должен быть положительным.
/// \param slopeSin Синус угла наклона трубы к горизонтальной поверхности (плоскости Oxy). Для трубы с вершинами A (ближе к источнику) и B (ближе к стоку) угол считается положительным, если z-координата вершины B меньше, чем вершины A. Данный параметр должен принадлежать множеству [0,1).
WaterSource::WaterSource(std::string name, const Point & point, unsigned int diameter, CalcNumber slopeSin): _name(name), _point(point), _diameter(diameter), _slopeSin(slopeSin) {
    
    assert(diameter > 0);
    assert(0 <= slopeSin && slopeSin < 1);
    
}

/// Вернуть имя точки подключения.
///
/// \return Имя точка подключения.
std::string WaterSource::name() const {
    
    return _name;
    
}

/// Вернуть точку подключения.
///
/// \return Точка подключения (единица измерения - мм.).
Point WaterSource::point() const {
    
    return _point;
    
}

/// Вернуть диаметр трубы подключения.
///
/// \return Диаметр трубы подключения (единица измерения - мм.).
unsigned int WaterSource::diameter() const {
    
    return _diameter;
    
}

/// Вернуть синус угла наклона трубы к горизонтальной поверхности (плоскости Oxy). Для трубы с вершинами A (ближе к источнику) и B (ближе к стоку) угол считается положительным, если z-координата вершины B меньше, чем вершины A.
///
/// \return Синус угла наклона трубы.
CalcNumber WaterSource::slopeSin() const {
    
    return _slopeSin;
    
}

#endif /* WaterSource_hpp */
