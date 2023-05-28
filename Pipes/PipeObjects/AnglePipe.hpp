#ifndef AnglePipe_hpp
#define AnglePipe_hpp

// Подключение стандартных библиотек
#include <cassert>
#include <string>
#include <math.h>

// Подключение внутренних типов
#include "PipeObject.hpp"

/// Фитинг-отвод (изогнутая труба с одним входом и одним выходом). Имеет заданные диаметр, угол, п-длину, м-длину, идентификатор, имя и стоимость за штуку.
struct AnglePipe: PipeObject {
    
private:
    
    // MARK: - Скрытые объекты
    
    /// Диаметр (единица измерения - мм.).
    unsigned int _diameter;
    
    /// Угол (единица измерения - градус).
    unsigned int _angle;
    
    /// П-длина (в соединенном состоянии, т.е. расстояние между центром данного отвода и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.).
    CalcNumber _fLength;
    
    /// М-длина (расстояние между центром данного отвода и ее м-входом; единица измерения - мм.).
    CalcNumber _mLength;
    
    /// Угол на 2D схеме при учете минимально допустимого угла наклона труб (единица измерения - градус).
    CalcNumber _projectedAngle;
    
    /// Синус угла на 2D схеме при учете минимально допустимого угла наклона труб.
    CalcNumber _projectedAngleSin;
    
    /// Косинус угла на 2D схеме при учете минимально допустимого угла наклона труб.
    CalcNumber _projectedAngleCos;
    
public:
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param diameter Диаметр (единица измерения - мм.). Должен быть положительным.
    /// \param angle Угол (единица измерения - градус). Должен принадлежать отрезку [1,90].
    /// \param fLength П-длина (в соединенном состоянии, т.е. расстояние между центром данного отвода и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.). Должна быть положительной.
    /// \param mLength М-длина (расстояние между центром данного отвода и ее м-входом, единица измерения - мм.). Должна быть положительной.
    /// \param id Идентификатор.
    /// \param name Имя.
    /// \param cost Стоимость за штуку (единица измерения - руб.).
    /// \param externalDiameterForDiameterP Указатель на внешние диаметры соединений объектов (единица измерения - мм.).
    /// \param config Параметры модели.
    explicit AnglePipe(unsigned int diameter, unsigned int angle, CalcNumber fLength, CalcNumber mLength, int id, std::string name, CalcNumber cost, const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP, const Config & config);
    
    /// Конструктор по умолчанию.
    AnglePipe();
    
    // MARK: - Открытые методы
    
    /// Оператор "меньше".
    ///
    /// \param anotherAnglePipe Второй объект данного типа.
    ///
    /// \return true, если *this < anotherAnglePipe, иначе false.
    bool operator<(const AnglePipe & anotherAnglePipe) const;
    
    /// Вернуть диаметр (единица измерения - мм.).
    ///
    /// \return Диаметр (единица измерения - мм.).
    unsigned int diameter() const;
    
    /// Вернуть угол (единица измерения - градус).
    ///
    /// \return Угол (единица измерения - градус).
    unsigned int angle() const;
    
    /// Вернуть П-длину (в соединенном состоянии, т.е. расстояние между центром данного отвода и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.).
    ///
    /// \return П-длина (единица измерения - мм.).
    CalcNumber fLength() const;
    
    /// Вернусть М-длину (расстояние между центром данного отвода и ее м-входом; единица измерения - мм.).
    ///
    /// \return М-длина (единица измерения - мм.).
    CalcNumber mLength() const;
    
    /// Вернуть угол на 2D схеме при учете минимально допустимого угла наклона труб (единица измерения - градус).
    ///
    /// \return Угол на 2D схеме (единица измерения - градус).
    CalcNumber projectedAngle() const;
    
    /// Вернуть синус угла на 2D схеме при учете минимально допустимого угла наклона труб.
    ///
    /// \return Синус угла на 2D схеме.
    CalcNumber projectedAngleSin() const;
    
    /// Вернуть косинус угла на 2D схеме при учете минимально допустимого угла наклона труб.
    ///
    /// \return Косинус угла на 2D схеме.
    CalcNumber projectedAngleCos() const;
    
};

// MARK: - Реализация

/// Конструктор.
///
/// \param diameter Диаметр (единица измерения - мм.). Должен быть положительным.
/// \param angle Угол (единица измерения - градус). Должен принадлежать отрезку [1,90].
/// \param fLength П-длина (в соединенном состоянии, т.е. расстояние между центром данного отвода и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.). Должна быть положительной.
/// \param mLength М-длина (расстояние между центром данного отвода и ее м-входом, единица измерения - мм.). Должна быть положительной.
/// \param id Идентификатор.
/// \param name Имя.
/// \param cost Стоимость за штуку (единица измерения - руб.).
/// \param externalDiameterForDiameterP Указатель на внешние диаметры соединений объектов (единица измерения - мм.).
/// \param config Параметры модели.
AnglePipe::AnglePipe(unsigned int diameter, unsigned int angle, CalcNumber fLength, CalcNumber mLength, int id, std::string name, CalcNumber cost, const std::map<unsigned int, unsigned int> * externalDiameterForDiameterP, const Config & config): PipeObject(id, name, cost, externalDiameterForDiameterP), _diameter(diameter), _angle(angle), _fLength(fLength), _mLength(mLength) {
    
    assert(diameter > 0);
    assert(angle >= 1 && angle <= 90);
    assert(fLength > 0);
    assert(mLength > 0);
    
    CalcNumber minSlopeAngleSin = config.minSlopeAngleSin;
    CalcNumber minSlopeAngleSinSquared = minSlopeAngleSin * minSlopeAngleSin;
    CalcNumber minSlopeAngleCosSquared = 1 - minSlopeAngleSinSquared;
    CalcNumber alfa = (180.0 - _angle) / 2;
    CalcNumber alfaSin = sin(alfa * M_PI / 180);
    _projectedAngle = 180.0 - 2 * asin(sqrt((alfaSin * alfaSin - minSlopeAngleSinSquared) / minSlopeAngleCosSquared)) * 180.0 / M_PI;
    _projectedAngleSin = sin(_projectedAngle * M_PI / 180);
    _projectedAngleCos = cos(_projectedAngle * M_PI / 180);
    
}

/// Конструктор по умолчанию.
AnglePipe::AnglePipe(): PipeObject(0, "", 0, nullptr), _diameter(1), _angle(1), _fLength(1), _mLength(1) {}

/// Оператор "меньше".
///
/// \param anotherAnglePipe Второй объект данного типа.
///
/// \return true, если *this < anotherAnglePipe, иначе false.
bool AnglePipe::operator<(const AnglePipe & anotherAnglePipe) const {
    
    if (_diameter < anotherAnglePipe._diameter) {
        return true;
    } else if (_diameter > anotherAnglePipe._diameter) {
        return false;
    } else {
        return (_angle < anotherAnglePipe._angle);
    }
    
}

/// Вернуть диаметр (единица измерения - мм.).
///
/// \return Диаметр (единица измерения - мм.).
unsigned int AnglePipe::diameter() const {
    
    return _diameter;
    
}

/// Вернуть угол (единица измерения - градус).
///
/// \return Угол (единица измерения - градус).
unsigned int AnglePipe::angle() const {
    
    return _angle;
    
}

/// Вернуть П-длину (в соединенном состоянии, т.е. расстояние между центром данного отвода и м-входом соединенного с ее п-выходом объекта; единица измерения - мм.).
///
/// \return П-длина (единица измерения - мм.).
CalcNumber AnglePipe::fLength() const {
    
    return _fLength;
    
}

/// Вернусть М-длину (расстояние между центром данного отвода и ее м-входом; единица измерения - мм.).
///
/// \return М-длина (единица измерения - мм.).
CalcNumber AnglePipe::mLength() const {
    
    return _mLength;
    
}

/// Вернуть угол на 2D схеме при учете минимально допустимого угла наклона труб (единица измерения - градус).
///
/// \return Угол на 2D схеме (единица измерения - градус).
CalcNumber AnglePipe::projectedAngle() const {
    
    return _projectedAngle;
    
}

/// Вернуть синус угла на 2D схеме при учете минимально допустимого угла наклона труб.
///
/// \return Синус угла на 2D схеме.
CalcNumber AnglePipe::projectedAngleSin() const {
    
    return _projectedAngleSin;
    
}

/// Вернуть косинус угла на 2D схеме при учете минимально допустимого угла наклона труб.
///
/// \return Косинус угла на 2D схеме.
CalcNumber AnglePipe::projectedAngleCos() const {
    
    return _projectedAngleCos;
    
}

#endif /* AnglePipe_hpp */
