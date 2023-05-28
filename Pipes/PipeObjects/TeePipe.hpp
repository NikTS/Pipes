#ifndef TeePipe_hpp
#define TeePipe_hpp

// Подключение стандартных библиотек
#include <cassert>
#include <string>

// Подключение внутренних типов
#include "PipeObject.hpp"

/// Фитинг-тройник (прямая труба со вставкой второго входа). Имеет заданные основной диаметр, диаметр вставки, угол, п-длину, основную м-длину, м-длину вставки, идентификатор, имя и стоимость за штуку.
struct TeePipe: public PipeObject {
    
    // MARK: - Открытые объекты
    
    /// Основной диаметр (единица измерения - мм.).
    unsigned int baseDiameter;
    
    /// Диаметр вставки (единица измерения - мм.).
    unsigned int extraDiameter;
    
    /// Угол  (единица измерения - градус).
    unsigned int angle;
    
    /// П-длина (в соединенном состоянии, т.е. расстояние между центром данного тройника и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.).
    CalcNumber fLength;
    
    /// Основная м-длина (расстояние между центром данного тройника и ее основным м-входом, единица измерения - мм.).
    CalcNumber baseMLength;
    
    /// М-длина вставки (расстояние между центром данного тройника и м-входом вставки, единица измерения - мм.).
    CalcNumber extraMLength;
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param baseDiameter Основной диаметр (единица измерения - мм.). Должен быть положительным.
    /// \param extraDiameter Диаметр вставки (единица измерения - мм.). Должен быть положительным. Должно выполняться неравенство extraDiameter <= baseDiameter.
    /// \param angle Угол (единица измерения - градус). Должен принадлежать отрезку [1,90].
    /// \param fLength П-длина (в соединенном состоянии, т.е. расстояние между центром данного тройника и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.). Должна быть положительной.
    /// \param baseMLength Основная м-длина (расстояние между центром данного тройника и ее основным м-входом, единица измерения - мм.). Должна быть положительной.
    /// \param extraMLength М-длина вставки (расстояние между центром данного тройника и м-входом вставки, (единица измерения - м). Должна быть положительной.
    /// \param id Идентификатор.
    /// \param name Имя.
    /// \param cost Стоимость за штуку (единица измерения - руб.).
    /// \param externalDiameterForDiameterP Указатель на внешние диаметры соединений объектов (единица измерения - мм.).
    explicit TeePipe(unsigned int baseDiameter, unsigned int extraDiameter, unsigned int angle, CalcNumber fLength, CalcNumber baseMLength, CalcNumber extraMLength, int id, std::string name, CalcNumber cost, const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP);
    
    /// Конструктор по умолчанию.
    TeePipe();
    
    // MARK: - Открытые методы
    
    /// Оператор "меньше".
    ///
    /// \param anotherTeePipe Второй объект данного типа.
    ///
    /// \return true, если *this < anotherTeePipe, иначе false.
    bool operator<(const TeePipe & anotherTeePipe) const;
    
};

// MARK: - Реализация

/// Конструктор.
///
/// \param baseDiameter Основной диаметр (единица измерения - мм.). Должен быть положительным.
/// \param extraDiameter Диаметр вставки (единица измерения - мм.). Должен быть положительным. Должно выполняться неравенство extraDiameter <= baseDiameter.
/// \param angle Угол (единица измерения - градус). Должен принадлежать отрезку [1,90].
/// \param fLength П-длина (в соединенном состоянии, т.е. расстояние между центром данного тройника и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.). Должна быть положительной.
/// \param baseMLength Основная м-длина (расстояние между центром данного тройника и ее основным м-входом, единица измерения - мм.). Должна быть положительной.
/// \param extraMLength М-длина вставки (расстояние между центром данного тройника и м-входом вставки, единица измерения - мм.). Должна быть положительной.
/// \param id Идентификатор.
/// \param name Имя.
/// \param cost Стоимость за штуку (единица измерения - руб.).
/// \param externalDiameterForDiameterP Указатель на внешние диаметры соединений объектов (единица измерения - мм.).
TeePipe::TeePipe(unsigned int baseDiameter, unsigned int extraDiameter, unsigned int angle, CalcNumber fLength, CalcNumber baseMLength, CalcNumber extraMLength, int id, std::string name, CalcNumber cost, const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP): PipeObject(id, name, cost, externalDiameterForDiameterP), baseDiameter(baseDiameter), extraDiameter(extraDiameter), angle(angle), fLength(fLength), baseMLength(baseMLength), extraMLength(extraMLength) {
    
    assert(baseDiameter > 0);
    assert(extraDiameter > 0);
    assert(extraDiameter <= baseDiameter);
    assert(angle >= 1 && angle <= 90);
    assert(fLength > 0);
    assert(baseMLength > 0);
    assert(extraMLength > 0);
    
}

/// Конструктор по умолчанию.
TeePipe::TeePipe(): PipeObject(0, "", 0, nullptr), baseDiameter(1), extraDiameter(1), angle(1), fLength(1), baseMLength(1), extraMLength(1) {}

/// Оператор "меньше".
///
/// \param anotherTeePipe Второй объект данного типа.
///
/// \return true, если *this < anotherTeePipe, иначе false.
bool TeePipe::operator<(const TeePipe & anotherTeePipe) const {
    
    if (baseDiameter < anotherTeePipe.baseDiameter) {
        return true;
    } else if (baseDiameter > anotherTeePipe.baseDiameter) {
        return false;
    } else {
        return (extraDiameter < anotherTeePipe.extraDiameter);
    }
    
}

#endif /* TeePipe_hpp */
