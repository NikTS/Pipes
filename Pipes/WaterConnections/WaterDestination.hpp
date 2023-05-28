#ifndef WaterDestination_hpp
#define WaterDestination_hpp

// Подключение стандартных библиотек
#include <cassert>
#include <string>

// Подключение внутренних типов
#include "CalcNumber.hpp"
#include "Point.hpp"

/// Сток (стояк) воды. Характеризуется 1) именем, 2) точкой подключения, 3) диаметром трубы подключения.
struct WaterDestination {
    
private:
    
    // MARK: - Скрытые объекты
    
    /// Имя.
    std::string _name;
    
    /// Точка подключения (единица измерения - мм.). Z-координата данной точки задает минимальное значение Z-координаты для центра фитинга, соединяющего данный сток (стояк) с трассой системы водоотведения.
    Point _point;
    
    /// Диаметр трубы подключения (единица измерения - мм.).
    CalcNumber _diameter;
    
public:
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param name Имя.
    /// \param point Точка подключения (единица измерения - мм.). Z-координата данной точки задает минимальное значение Z-координаты для центра фитинга, соединяющего данный сток (стояк) с трассой системы водоотведения.
    /// \param diameter Диаметр трубы подключения (единица измерения - мм.). Должен быть положительным.
    explicit WaterDestination(std::string name, const Point & point, unsigned int diameter);
    
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
    
};

// MARK: - Реализация

/// Конструктор.
/// \param name Имя.
/// \param point Точка подключения (единица измерения - мм.). Z-координата данной точки задает минимальное значение Z-координаты для центра фитинга, соединяющего данный сток (стояк) с трассой системы водоотведения.
/// \param diameter Диаметр трубы подключения (единица измерения - мм.). Должен быть положительным.
WaterDestination::WaterDestination(std::string name, const Point & point, unsigned int diameter): _name(name), _point(point), _diameter(diameter) {
    
    assert(diameter > 0);
    
}

/// Вернуть имя точки подключения.
///
/// \return Имя точка подключения.
std::string WaterDestination::name() const {
    
    return _name;
    
}

/// Вернуть точку подключения.
///
/// \return Точка подключения (единица измерения - мм.).
Point WaterDestination::point() const {
    
    return _point;
    
}

/// Вернуть диаметр трубы подключения.
///
/// \return Диаметр трубы подключения (единица измерения - мм.).
unsigned int WaterDestination::diameter() const {
    
    return _diameter;
    
}

#endif /* WaterDestination_hpp */
