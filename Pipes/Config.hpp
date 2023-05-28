#ifndef Config_hpp
#define Config_hpp

// Подключение стандартных библиотек
#include <string>
#include <fstream>
#include <sstream>

// Подключение внутренних типов
#include "CalcNumber.hpp"
#include "Exception.hpp"

/// Параметры модели.
struct Config {
    
    // MARK: - Открытые объекты
    
    /// Синус минимально допустимого угла наклона труб. Под углом трубы понимается угол между осью трубы и плоскостью Oxy. Для трубы с вершинами A (ближе к источнику) и B (ближе к стоку) угол считается положительным, если z-координата вершины B меньше, чем вершины A.
    CalcNumber minSlopeAngleSin;
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param minSlopeAngleSin Синус минимально допустимого угла наклона труб. Должен принадлежать отрезку [0,1].
    explicit Config(CalcNumber minSlopeAngleSin);
    
    /// Конструктор по умолчанию.
    explicit Config();
    
    // MARK: - Открытые методы
    
    /// Загрузить параметры модели из файла. Метод бросает Exception-исключение в случае некорректных данных.
    ///
    /// \param fileName Имя файла в формате CSV.
    void loadFromFile(const std::string & fileName);
    
};

// MARK: - Реализация

/// Конструктор.
///
/// \param minSlopeAngleSin Синус минимально допустимого угла наклона труб. Должен принадлежать отрезку [0,1].
Config::Config(CalcNumber minSlopeAngleSin): minSlopeAngleSin(minSlopeAngleSin) {
    
    assert (0 <= minSlopeAngleSin && minSlopeAngleSin <= 1);
    
}

/// Конструктор по умолчанию.
Config::Config() {}

/// Загрузить параметры модели из файла. Метод бросает Exception-исключение в случае некорректных данных.
///
/// \param fileName Имя файла в формате CSV.
void Config::loadFromFile(const std::string & fileName) {
    
    try {
        
        std::ifstream stream(fileName);
        if (stream.fail()) {
            throw Exception("Ошибка при открытии CSV-файла с параметрами модели.");
        }
        std::string line;
        
        /// Разделитель, использующийся в файле.
        const char delimeter = ';';
        
        // считывание заголовка файла
        line = "";
        std::getline(stream, line);
        
        line = "";
        std::getline(stream, line);
        
        std::string lineErrorMessagePrefix = "Ошибка при чтении CSV-файла с параметрами модели";
        
        std::istringstream lineStream(line);
        
        std::string extraStr;
        CalcNumber minDeltaZ;
        
        std::string readingColumnName;
        
        try {
            
            // чтение поля minDeltaZ
            readingColumnName = "Минимальное изменение Z-координаты на метр трубы (мм.)";
            extraStr = "";
            std::getline(lineStream, extraStr, delimeter);
            minDeltaZ = std::stod(extraStr);
            if (minDeltaZ <= 0) {
                throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Данный параметр должен быть положительным.");
            } else if (minDeltaZ > 100) {
                throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Данный параметр не должен превосходить 100.");
            }
            
        }
        catch (const Exception & exception) {
            throw exception;
        }
        catch (...) {
            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\".  Некорректный формат поля.");
        }
        
        stream.close();
        
        this->minSlopeAngleSin = minDeltaZ / 1000;
        
    }
    catch (const Exception & exception) {
        throw exception;
    }
    catch (...) {
        throw Exception("Ошибка при чтении CSV-файла с параметрами модели.");
    }
    
}

#endif /* Config_hpp */
