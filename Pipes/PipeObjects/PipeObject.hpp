#ifndef PipeObject_hpp
#define PipeObject_hpp

// Подключение стандартных библиотек
#include <string>

// Подключение внутренних типов
#include "CalcNumber.hpp"

/// Объект системы водоотведения. Имеет идентификатор, имя и стоимость.
struct PipeObject {
    
    // MARK: - Открытые объекты
    
    /// Идентификатор объекта.
    int id;
    
    /// Имя объекта.
    std::string name;
    
    /// Стоимость объекта (за штуку или единицу длины, в зависимости от типа, единица измерения - руб.).
    CalcNumber cost;
    
    /// Указатель на внешние диаметры соединений объектов (единица измерения - мм.).
    const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP;
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param id Идентификатор объекта.
    /// \param name Имя объекта.
    /// \param cost Стоимость объекта (за штуку или единицу длины, в зависимости от типа, единица измерения - руб.).
    /// \param externalDiameterForDiameterP Указатель на внешние диаметры соединений объектов (единица измерения - мм.).
    explicit PipeObject(int id, std::string name, CalcNumber cost, const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP);
    
};

// MARK: - Реализация

/// Конструктор.
///
/// \param id Идентификатор объекта.
/// \param name Имя объекта.
/// \param cost Стоимость объекта (за штуку или единицу длины, в зависимости от типа, единица измерения - руб.).
PipeObject::PipeObject(int id, std::string name, CalcNumber cost, const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP): id(id), name(name), cost(cost), externalDiameterForDiameterP(externalDiameterForDiameterP) {}

#endif /* PipeObject_hpp */
