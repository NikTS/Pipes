#ifndef WaterConnectionObjects_hpp
#define WaterConnectionObjects_hpp

// Подключение стандартных библиотек
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Подключение внутренних типов
#include "WaterSource.hpp"
#include "WaterDestination.hpp"

/// Объекты подключения воды. Состоят из одного стока и одного или более источника.
struct WaterConnectionObjects {
    
    // MARK: - Открытые объекты
    
    /// Источники воды, отсортированные по уменьшению диаметров.
    std::vector<WaterSource> waterSources;
    
    /// Сток воды.
    WaterDestination waterDestination;
    
    /// Флаг установки стока.
    bool waterDestinationIsSet;
    
    // MARK: - Конструкторы
    
    /// Конструктор. Создается пустое множество объектов.
    explicit WaterConnectionObjects();
    
    // MARK: - Открытые методы
    
    /// Загрузить объекты подключения воды из файла. Метод бросает Exception-исключение в случае некорректных данных. В случае вызова исключения состояние объекта остается неопределенным.
    ///
    /// \param fileName Имя файла в формате CSV.
    void loadObjectsFromFile(const std::string & fileName);
    
};

// MARK: - Реализация

/// Конструктор. Создается пустое множество объектов.
WaterConnectionObjects::WaterConnectionObjects(): waterDestination(WaterDestination("", Point(0, 0, 0), 1)), waterDestinationIsSet(false) {}

/// Загрузить объекты подключения воды из файла. Метод бросает Exception-исключение в случае некорректных данных. В случае вызова исключения состояние объекта остается неопределенным.
///
/// \param fileName Имя файла в формате CSV.
void WaterConnectionObjects::loadObjectsFromFile(const std::string & fileName) {
    
    waterSources.clear();
    waterDestinationIsSet = false;
    
    // Шаг 1. Загрузка объектов из файла.
    
    try {
        
        std::ifstream stream(fileName);
        if (stream.fail()) {
            throw Exception("Ошибка при открытии CSV-файла с точками подключения.");
        }
        std::string line;
        
        /// Разделитель, использующийся в файле.
        const char delimeter = ';';
        
        // считывание заголовка файла
        line = "";
        std::getline(stream, line);
        
        int lineNumber = 2;
        line = "";
        while (std::getline(stream, line)) {
            
            std::string lineErrorMessagePrefix = "Ошибка при чтении CSV-файла с точками подключения в строке " + std::to_string(lineNumber);
            
            if (line.empty()) {
                lineNumber++;
                continue;
            }
            
            std::istringstream lineStream(line);
            
            std::string objectTypeStr, name, extraStr;
            int diameter;
            CalcNumber pointX, pointY, pointZ, slopeSin = 0;
            
            // чтения поля objectType
            objectTypeStr = "";
            std::getline(lineStream, objectTypeStr, delimeter);
            
            if (objectTypeStr == "источник" || objectTypeStr == "стояк" || objectTypeStr == "Источник" || objectTypeStr == "Стояк") {
                
                std::string readingColumnName;
                
                try {
                    
                    // чтение поля name
                    readingColumnName = "Наименование";
                    name = "";
                    std::getline(lineStream, name, delimeter);
                    
                    // чтение поля pointX
                    readingColumnName = "X (мм.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    pointX = std::stod(extraStr);
                    
                    // чтение поля pointY
                    readingColumnName = "Y (мм.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    pointY = std::stod(extraStr);
                    
                    // чтение поля pointZ
                    readingColumnName = "Z (мм.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    pointZ = std::stod(extraStr);
                    
                    // чтение поля diameter
                    readingColumnName = "Диаметр (мм.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    diameter = std::stoi(extraStr);
                    if (diameter < 1) {
                        throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Диаметр должен быть положительным.");
                    }
                    
                    // чтение поля directionX
                    readingColumnName = "Синус угла наклона трубы";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    if (objectTypeStr == "стояк" || objectTypeStr == "Стояк") {
                        if (extraStr != "") {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Для стояка направление не должно задаваться.");
                        }
                    } else if (extraStr == "") {
                        slopeSin = 0;
                    } else {
                        slopeSin = std::stod(extraStr);
                        if (slopeSin < 0 || slopeSin >= 1) {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Синус угла наклона трубы должен принадлежать множеству [0,1).");
                        }
                    }
                    
                }
                catch (const Exception & exception) {
                    throw exception;
                }
                catch (...) {
                    throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Некорректный формат поля.");
                }
                
                if (objectTypeStr == "источник" || objectTypeStr == "Источник") {
                    
                    waterSources.push_back(WaterSource(name, Point(pointX, pointY, pointZ), diameter, slopeSin));
                    
                } else {
                    
                    if (waterDestinationIsSet) {
                        throw Exception("Ошибка при чтении CSV-файла с точками подключения. В файле присутствуют несколько стояков.");
                    }
                    
                    waterDestination = WaterDestination(name, Point(pointX, pointY, pointZ), diameter);
                    waterDestinationIsSet = true;
                    
                }
                
            } else {
                throw Exception(lineErrorMessagePrefix + ". Неверный тип.");
            }
            
            lineNumber++;
            line = "";
            
        }
        
        stream.close();
        
    }
    catch (const Exception & exception) {
        throw exception;
    }
    catch (...) {
        throw Exception("Ошибка при чтении CSV-файла с точками подключения.");
    }
    
    if (waterSources.empty()) {
        throw Exception("Ошибка при чтении CSV-файла с точками подключения. В файле отсутствуют источники.");
    }
    
    if (waterDestinationIsSet == false) {
        throw Exception("Ошибка при чтении CSV-файла с точками подключения. В файле отсутствуют стояки.");
    }
    
    // Шаг 2. Сортировка источников по уменьшению диаметров.
    
    for (int i = 0; i < waterSources.size() - 1; i++) {
        for (int j = 1; j < waterSources.size(); j++) {
            if (waterSources[i].diameter() < waterSources[j].diameter()) {
                WaterSource tempSource = waterSources[i];
                waterSources[i] = waterSources[j];
                waterSources[j] = tempSource;
            }
        }
    }
    
}

#endif /* WaterConnectionObjects_hpp */
