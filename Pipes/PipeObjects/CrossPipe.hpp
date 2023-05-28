#ifndef CrossPipe_hpp
#define CrossPipe_hpp

// Подключение стандартных библиотек
#include <cassert>
#include <string>

// Подключение внутренних типов
#include "PipeObject.hpp"

/// Фитинг-крестовина (прямая труба со вставкой второго и третьего входов). Имеет заданные основной диаметр, второй диаметр, третий диаметр, тип, угол, п-длину, основную м-длину, вторую м-длину, третью м-длину, идентификатор, имя и стоимость за штуку.
struct CrossPipe: public PipeObject {
    
    // MARK: - Вспомогательные типы
    
    /// Тип.
    enum Type {
        
        /// Обычная крестовина.
        usual,
        
        /// Левая крестовина.
        left,
        
        /// Правая крестовина.
        right
        
    };
    
    // MARK: - Открытые объекты
    
    /// Основной диаметр (единица измерения - мм.).
    unsigned int baseDiameter;
    
    /// Второй диаметр (единица измерения - мм.).
    unsigned int secondDiameter;
    
    /// Третий диаметр (единица измерения - мм.).
    unsigned int thirdDiameter;
    
    /// Тип.
    Type type;
    
    /// Угол  (единица измерения - градус).
    unsigned int angle;
    
    /// П-длина (в соединенном состоянии, т.е. расстояние между центром данной крестовины и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.).
    CalcNumber fLength;
    
    /// Основная м-длина (расстояние между центром данной крестовины и ее основным м-входом, единица измерения - мм.).
    CalcNumber baseMLength;
    
    /// Вторая м-длина (расстояние между центром данного тройника и вторым м-входом, единица измерения - мм.).
    CalcNumber secondMLength;
    
    /// Третья м-длина (расстояние между центром данного тройника и третьим м-входом, единица измерения - мм.).
    CalcNumber thirdMLength;
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param baseDiameter Основной диаметр (единица измерения - мм.). Должен быть положительным.
    /// \param secondDiameter Второй диаметр (единица измерения - мм.). Должен быть положительным.
    /// \param thirdDiameter Третий диаметр (единица измерения - мм.). Должен быть положительным. Должны выполняться неравенства thirdDiameter <= secondDiameter <= baseDiameter.
    /// \param type Тип.
    /// \param angle Угол (единица измерения - градус). Должен принадлежать отрезку [1,90].
    /// \param fLength П-длина (в соединенном состоянии, т.е. расстояние между центром данной крестовины и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.). Должна быть положительной.
    /// \param baseMLength Основная м-длина (расстояние между центром данной крестовины и ее основным м-входом, единица измерения - мм.). Должна быть положительной.
    /// \param secondMLength Вторая м-длина (расстояние между центром данного тройника и вторым м-входом, единица измерения - мм.). Должна быть положительной.
    /// \param thirdMLength Третья м-длина (расстояние между центром данного тройника и вторым м-входом, единица измерения - мм.). Должна быть положительной.
    /// \param id Идентификатор.
    /// \param name Имя.
    /// \param cost Стоимость за штуку (единица измерения - руб.).
    /// \param externalDiameterForDiameterP Указатель на внешние диаметры соединений объектов (единица измерения - мм.).
    explicit CrossPipe(unsigned int baseDiameter, unsigned int secondDiameter, unsigned int thirdDiameter, Type type, unsigned int angle, CalcNumber fLength, CalcNumber baseMLength, CalcNumber secondMLength, CalcNumber thirdMLength, int id, std::string name, CalcNumber cost, const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP);
    
    /// Конструктор по умолчанию.
    CrossPipe();
    
    // MARK: - Открытые методы
    
    /// Оператор "меньше".
    ///
    /// \param anotherCrossPipe Второй объект данного типа.
    ///
    /// \return true, если *this < anotherCrossPipe, иначе false.
    bool operator<(const CrossPipe & anotherCrossPipe) const;
    
};

// MARK: - Реализация

/// Конструктор.
///
/// \param baseDiameter Основной диаметр (единица измерения - мм.). Должен быть положительным.
/// \param secondDiameter Второй диаметр (единица измерения - мм.). Должен быть положительным.
/// \param thirdDiameter Третий диаметр (единица измерения - мм.). Должен быть положительным. Должны выполняться неравенства thirdDiameter <= secondDiameter <= baseDiameter.
/// \param type Тип.
/// \param angle Угол (единица измерения - градус). Должен принадлежать отрезку [1,90].
/// \param fLength П-длина (в соединенном состоянии, т.е. расстояние между центром данной крестовины и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.). Должна быть положительной.
/// \param baseMLength Основная м-длина (расстояние между центром данной крестовины и ее основным м-входом, единица измерения - мм.). Должна быть положительной.
/// \param secondMLength Вторая м-длина (расстояние между центром данного тройника и вторым м-входом, единица измерения - мм.). Должна быть положительной.
/// \param thirdMLength Третья м-длина (расстояние между центром данного тройника и вторым м-входом, единица измерения - мм.). Должна быть положительной.
/// \param id Идентификатор.
/// \param name Имя.
/// \param cost Стоимость за штуку (единица измерения - руб.).
/// \param externalDiameterForDiameterP Указатель на внешние диаметры соединений объектов (единица измерения - мм.).
CrossPipe::CrossPipe(unsigned int baseDiameter, unsigned int secondDiameter, unsigned int thirdDiameter, Type type, unsigned int angle, CalcNumber fLength, CalcNumber baseMLength, CalcNumber secondMLength, CalcNumber thirdMLength, int id, std::string name, CalcNumber cost, const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP): PipeObject(id, name, cost, externalDiameterForDiameterP), baseDiameter(baseDiameter), secondDiameter(secondDiameter), thirdDiameter(thirdDiameter), type(type), angle(angle), fLength(fLength), baseMLength(baseMLength), secondMLength(secondMLength), thirdMLength(thirdMLength) {
    
    assert(baseDiameter > 0);
    assert(secondDiameter > 0);
    assert(thirdDiameter > 0);
    assert(thirdDiameter <= secondDiameter && secondDiameter <= baseDiameter);
    assert(angle >= 1 && angle <= 90);
    assert(fLength > 0);
    assert(baseMLength > 0);
    assert(secondMLength > 0);
    assert(thirdMLength > 0);
    
}

/// Конструктор по умолчанию.
CrossPipe::CrossPipe(): PipeObject(0, "", 0, nullptr), baseDiameter(1), secondDiameter(1), thirdDiameter(1), type(usual), angle(1), fLength(1), baseMLength(1), secondMLength(1), thirdMLength(1) {}

/// Оператор "меньше".
///
/// \param anotherCrossPipe Второй объект данного типа.
///
/// \return true, если *this < anotherCrossPipe, иначе false.
bool CrossPipe::operator<(const CrossPipe & anotherCrossPipe) const {
    
    if (baseDiameter < anotherCrossPipe.baseDiameter) {
        return true;
    } else if (baseDiameter > anotherCrossPipe.baseDiameter) {
        return false;
    } else {
        return (secondDiameter < anotherCrossPipe.secondDiameter);
    }
    
}

#endif /* CrossPipe_hpp */
