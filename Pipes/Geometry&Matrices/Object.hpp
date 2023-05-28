#ifndef Object_hpp
#define Object_hpp

// Подключение внутренних типов
#include "CalcNumber.hpp"

/// \brief Точка.
class Point;

/// \brief Объект, имеющий определенную форму и расположение.
class Object {
    
public:
    
    // MARK: - Статические открытые объекты
    
    /// \brief Значение по умолчанию для параметра lengthEpsilon.
    constexpr static CalcNumber epsilon_default = 1e-2;
    
    /// \brief Параметр, использующийся при определении принадлежности точки объекту или его границе.
    ///
    /// Если расстоние от точки до объекта не превосходит lengthEpsilon, то точка считается принадлежащей объекту. Иначе точка считается не принадлежащей объекту.
    ///
    /// Если расстоние от точки до границы объекта не превосходит lengthEpsilon, то точка считается принадлежащей границе объекта. Иначе точка считается не принадлежащей границе объекта.
    static CalcNumber lengthEpsilon;
    
};

// MARK: - Инициализация статических переменных значениями по умолчанию

CalcNumber Object::lengthEpsilon = epsilon_default;

#endif /* Object_hpp */
