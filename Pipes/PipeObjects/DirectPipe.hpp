#ifndef DirectPipe_hpp
#define DirectPipe_hpp

// Подключение стандартных библиотек
#include <cassert>
#include <string>

// Подключение внутренних типов
#include "PipeObject.hpp"

/// Прямая труба с одним входом и одним выходом. Имеет заданные диаметр, идентификатор, имя и стоимость за единицу длины.
struct DirectPipe: public PipeObject {
    
    // MARK: - Открытые объекты
    
    /// Диаметр (единица измерения - мм.).
   unsigned int diameter;
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param diameter Диаметр (единица измерения - мм.). Должен быть положительным.
    /// \param id Идентификатор.
    /// \param name Имя.
    /// \param cost Стоимость за единицу длины (единица измерения - руб./мм.).
    /// \param externalDiameterForDiameterP Указатель на внешние диаметры соединений объектов (единица измерения - мм.).
    explicit DirectPipe(unsigned int diameter, int id, std::string name, CalcNumber cost, const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP);
    
    /// Конструктор по умолчанию.
    DirectPipe();
    
};

// MARK: - Реализация

/// Конструктор.
///
/// \param diameter Диаметр (единица измерения - мм.). Должен быть положительным.
/// \param id Идентификатор.
/// \param name Имя.
/// \param cost Стоимость за единицу длины (единица измерения - руб./мм.).
/// \param externalDiameterForDiameterP Указатель на внешние диаметры соединений объектов (единица измерения - мм.).
DirectPipe::DirectPipe(unsigned int diameter, int id, std::string name, CalcNumber cost, const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP): PipeObject(id, name, cost, externalDiameterForDiameterP), diameter(diameter) {
    
    assert(diameter > 0);
    
}

/// Конструктор по умолчанию.
DirectPipe::DirectPipe(): PipeObject(0, "", 0, nullptr), diameter(1) {}

#endif /* DirectPipe_hpp */
