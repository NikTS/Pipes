#ifndef ReductionPipe_hpp
#define ReductionPipe_hpp

// Подключение стандартных библиотек
#include <cassert>
#include <string>

// Подключение внутренних типов
#include "PipeObject.hpp"

/// Фитинг-редукция (с одним входом меньшего диаметра и одним выходом большего диаметра). Имеет заданные п-диаметр (больший), м-диаметр (меньший), длину, тип выравнивания, идентификатор, имя и стоимость за штуку.
struct ReductionPipe: public PipeObject {
    
    // MARK: - Вспомогательные типы
    
    /// Тип выравнивания.
    enum AlignmentType {
        
        /// Выравнивание во центру трубы.
        center,
        
        /// Выравнивание по краю трубы.
        edge
        
    };
    
    // MARK: - Открытые объекты
    
    /// П-диаметр (больший, единица измерения - мм.).
    unsigned int fDiameter;
    
    /// М-диаметр (меньший, единица измерения - мм.).
    unsigned int mDiameter;
    
    /// Длина (в соединенном состоянии, т.е. расстояние между м-входом данной редукции и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.).
    CalcNumber length;
    
    /// Тип выравнивания.
    AlignmentType alignmentType;
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param fDiameter П-диаметр (больший, единица измерения - мм.). Должен быть положительным.
    /// \param mDiameter М-диаметр (меньший, единица измерения - мм.). Должен быть положительным. Должно выполняться неравенство mDiameter < fDiameter.
    /// \param length Длина (в соединенном состоянии, т.е. расстояние между м-входом данной редукции и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.). Должна быть положительной.
    /// \param alignmentType Тип выравнивания.
    /// \param id Идентификатор.
    /// \param name Имя.
    /// \param cost Стоимость за штуку (единица измерения - руб.).
    /// \param externalDiameterForDiameterP Указатель на внешние диаметры соединений объектов (единица измерения - мм.).
    explicit ReductionPipe(unsigned int fDiameter, unsigned int mDiameter, CalcNumber length, AlignmentType alignmentType, int id, std::string name, CalcNumber cost, const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP);
    
    /// Конструктор по умолчанию.
    ReductionPipe();
    
    // MARK: - Открытые методы
    
    /// Оператор "меньше".
    ///
    /// \param anotherReductionPipe Второй объект данного типа.
    ///
    /// \return true, если *this < anotherReductionPipe, иначе false.
    bool operator<(const ReductionPipe & anotherReductionPipe) const;
    
};

// MARK: - Реализация

// Конструктор.
///
/// \param fDiameter П-диаметр (больший, единица измерения - мм.). Должен быть положительным.
/// \param mDiameter М-диаметр (меньший, единица измерения - мм.). Должен быть положительным. Должно выполняться неравенство mDiameter < fDiameter.
/// \param length Длина (в соединенном состоянии, т.е. расстояние между м-входом данной редукции и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.). Должна быть положительной.
/// \param alignmentType Тип выравнивания.
/// \param id Идентификатор объекта.
/// \param name Имя объекта.
/// \param cost Стоимость за штуку (единица измерения - руб.).
/// \param externalDiameterForDiameterP Указатель на внешние диаметры соединений объектов (единица измерения - мм.).
ReductionPipe::ReductionPipe(unsigned int fDiameter, unsigned int mDiameter, CalcNumber length, AlignmentType alignmentType, int id, std::string name, CalcNumber cost, const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP): PipeObject(id, name, cost, externalDiameterForDiameterP), fDiameter(fDiameter), mDiameter(mDiameter), length(length), alignmentType(alignmentType) {
    
    assert(fDiameter > 0);
    assert(mDiameter > 0);
    assert(mDiameter < fDiameter);
    assert(length > 0);
    
}

/// Конструктор по умолчанию.
ReductionPipe::ReductionPipe(): PipeObject(0, "", 0, nullptr), fDiameter(1), mDiameter(1), length(1), alignmentType(center) {}

/// Оператор "меньше".
///
/// \param anotherReductionPipe Второй объект данного типа.
///
/// \return true, если *this < anotherReductionPipe, иначе false.
bool ReductionPipe::operator<(const ReductionPipe & anotherReductionPipe) const {
    
    if (fDiameter < anotherReductionPipe.fDiameter) {
        return true;
    } else if (fDiameter > anotherReductionPipe.fDiameter) {
        return false;
    } else {
        return (mDiameter < anotherReductionPipe.mDiameter);
    }
    
}

#endif /* ReductionPipe_hpp */
