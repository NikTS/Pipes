#ifndef PipeObjectsBag_hpp
#define PipeObjectsBag_hpp

// Подключение стандартных библиотек
#include <map>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>

// Подключение внутренних типов
#include "Exception.hpp"
#include "PipeObjectType.hpp"
#include "DirectPipe.hpp"
#include "FanPipe.hpp"
#include "ReductionPipe.hpp"
#include "AnglePipe.hpp"
#include "TeePipe.hpp"
#include "CrossPipe.hpp"

/// Хранилище, содержащее доступные к использованию объекты системы водоотведения.
struct PipeObjectsBag {
    
private:
    
    // MARK: - Скрытые объекты
    
    /// Доступные диаметры объектов в порядке возрастания (единица измерения - мм.).
    std::vector<unsigned int> diameters;
    
    /// Внешние диаметры соединений объектов (единица измерения - мм.).
    std::map<unsigned int, unsigned int> externalDiameterForDiameter;
    
    /// Прямые трубы.
    std::map<unsigned int, DirectPipe> directPipeForDiameter;
    
    /// Фановые трубы.
    std::map<unsigned int, FanPipe> fanPipeForDiameter;
    
    /// Редукции. Для каждого п-диаметра редукции упорядочены по возрастанию м-диаметров.
    std::map<unsigned int, std::vector<ReductionPipe>> reductionPipesForFDiameter;
    
    /// Отводы (отвод - изогнутая труба с одним входом и одним выходом). Для каждого диаметра отводы упорядочены по возрастанию углов.
    std::map<unsigned int, std::vector<AnglePipe>> anglePipesForDiameter;
    
    /// Тройники (тройник - прямая труба со вставкой третьего входа). Для каждого основного диаметра тройники упорядочены по возрастанию диаметров вставки.
    std::map<unsigned int, std::vector<TeePipe>> teePipesForBaseDiameter;
    
    /// Крестовины (крестовина - прямая труба со вставкой второго и третьего входов). Для каждого основного диаметра крестовины упорядочены по возрастанию вторых диаметров.
    std::map<unsigned int, std::vector<CrossPipe>> crossPipesForBaseDiameter;
    
    /// Параметры модели.
    const Config & config;
    
public:
    
    // MARK: - Конструкторы
    
    /// Конструктор. Создается хранилище без объектов.
    ///
    /// \param config Параметры модели.
    explicit PipeObjectsBag(const Config & config);
    
    // MARK: - Открытые методы
    
    /// Загрузить внешние диаметры соединений объектов и сами объекты из файлов. Метод бросает Exception-исключение в случае некорректных данных. Также метод проверяет наличие внешнего диаметра для каждого диаметра, в случае неуспеха бросается Exception-исключение. В случае вызова исключения состояние объекта остается неопределенным.
    ///
    /// \param externalDiametersFileName Имя файла в формате CSV, в котором хранятся внешние диаметры.
    /// \param materialsFileName Имя файла в формате CSV, в котором хранятся доступные к использованию объекты.
    void loadFromFile(const std::string & externalDiametersFileName, const std::string & materialsFileName);
    
    /// Вернуть указатель на массив доступных диаметров объектов. Диаметры в массиве упорядочены по возрастанию.
    ///
    /// \returns Массив доступных диаметров объектов (единица измерения - мм.).
    const std::vector<unsigned int> * getDiametersP() const;
    
    /// Вернуть внешний диаметр соединения для его диаметра.
    ///
    /// \param diameter Диаметр (единица измерения - мм.). Должен являться доступным.
    ///
    /// \returns Внешний диаметр соединения, соответствующий диаметру diameter (единица измерения - мм.).
    const unsigned int getExternalDiameter(unsigned int diameter) const;
    
    /// Вернуть указатель на прямую трубу заданного диаметра.
    ///
    /// \param diameter Диаметр трубы (единица измерения - мм.).
    ///
    /// \returns Указатель на прямую трубу, если она доступна, иначе nullptr.
    const DirectPipe* getDirectPipeP(unsigned int diameter) const;
    
    /// Вернуть указатель на фановую трубу заданного диаметра.
    ///
    /// \param diameter Диаметр трубы (единица измерения - мм.).
    ///
    /// \returns Указатель на фановую трубу, если она доступна, иначе nullptr.
    const FanPipe* getFanPipeP(unsigned int diameter) const;
    
    /// Вернуть указатель на массив доступных редукций заданного П-диаметра. Редукции в массиве упорядочены по возрастанию м-диаметров.
    ///
    /// \param fDiameter П-диаметр редукции (единица измерения - мм.).
    ///
    /// \return Указатель на массив редукций П-диаметра diameter. Если редукции данного диаметра не доступны, возвращается nullptr.
    const std::vector<ReductionPipe> * getReductionPipePs(unsigned int fDiameter) const;
    
    /// Вернуть указатель на массив доступных отводов заданного диаметра. Отвод - изогнутая труба с одним входом и одним выходом. Отводы в массиве упорядочены по возрастанию углов.
    ///
    /// \param diameter Диаметр отвода (единица измерения - мм.).
    ///
    /// \returns Указатель на массив доступных отводов диаметра diameter. Если отводы данного диаметра не доступны, возвращается nullptr.
    const std::vector<AnglePipe> * getAnglePipePs(unsigned int diameter) const;
    
    /// Вернуть указатель на массив доступных тройников заданного основного диаметра. Тройник - прямая труба со вставкой третьего входа. Тройники в массиве упорядочены по возрастанию диаметров вставки.
    ///
    /// \param baseDiameter Основной диаметр тройника (единица измерения - мм.).
    ///
    /// \returns Указатель на массив доступных тройников основного диаметра baseDiameter. Если тройники данного диаметра не доступны, возвращается nullptr.
    const std::vector<TeePipe> * getTeePipePs(unsigned int baseDiameter) const;
    
    /// Вернуть указатель на массив доступных крестовин заданного основного диаметра. Крестовина - крестовина - прямая труба со вставкой второго и третьего входов. Крестовины в массиве упорядочены по возрастанию вторых диаметров.
    ///
    /// \param baseDiameter Основной диаметр крестовины (единица измерения - мм.).
    ///
    /// \returns Указатель на массив доступных крестовин основного диаметра baseDiameter. Если крестовины данного диаметра не доступны, возвращается nullptr.
    const std::vector<CrossPipe> * getCrossPipePs(unsigned int baseDiameter) const;
    
private:
    
    // MARK: - Скрытые методы
    
    /// Загрузить внешние диаметры соединений объектов из файла. Метод бросает Exception-исключение в случае некорректных данных. В случае вызова исключения состояние объекта остается неопределенным.
    ///
    /// \param fileName Имя файла в формате CSV.
    void loadExternalDiametersFromFile(const std::string & fileName);
    
    /// Загрузить доступные к использованию объекты из файла. Метод бросает Exception-исключение в случае некорректных данных. В случае вызова исключения состояние объекта остается неопределенным.
    ///
    /// \param fileName Имя файла в формате CSV.
    void loadObjectsFromFile(const std::string & fileName);
    
    /// Проверить наличие внешнего диаметра для каждого диаметра. Метод бросает Exception-исключение в случае неуспеха.
    void checkExternalDiameters();
    
};

// MARK: - Реализация

/// Конструктор. Создается хранилище без объектов.
///
/// \param config Параметры модели.
PipeObjectsBag::PipeObjectsBag(const Config & config): config(config) {}

/// Загрузить внешние диаметры соединений объектов и сами объекты из файлов. Метод бросает Exception-исключение в случае некорректных данных. Также метод проверяет наличие внешнего диаметра для каждого диаметра, в случае неуспеха бросается Exception-исключение. В случае вызова исключения состояние объекта остается неопределенным.
///
/// \param externalDiametersFileName Имя файла в формате CSV, в котором хранятся внешние диаметры.
/// \param materialsFileName Имя файла в формате CSV, в котором хранятся доступные к использованию объекты.
void PipeObjectsBag::loadFromFile(const std::string & externalDiametersFileName, const std::string & materialsFileName) {
    
    loadExternalDiametersFromFile(externalDiametersFileName);
    loadObjectsFromFile(materialsFileName);
    checkExternalDiameters();
    
}

/// Вернуть указатель на массив доступных диаметров объектов. Диаметры в массиве упорядочены по возрастанию.
///
/// \returns Массив доступных диаметров объектов (единица измерения - мм.).
const std::vector<unsigned int> * PipeObjectsBag::getDiametersP() const {
    
    return &diameters;
    
}

/// Вернуть внешний диаметр соединения для его диаметра.
///
/// \param diameter Диаметр (единица измерения - мм.). Должен являться доступным.
///
/// \returns Внешний диаметр соединения, соответствующий диаметру diameter (единица измерения - мм.).
const unsigned int PipeObjectsBag::getExternalDiameter(unsigned int diameter) const {
    
    auto externalDiameterIter = externalDiameterForDiameter.find(diameter);
    assert(externalDiameterIter != externalDiameterForDiameter.end());
    
    return externalDiameterIter->second;
    
}

/// Вернуть указатель на прямую трубу заданного диаметра.
///
/// \param diameter Диаметр трубы (единица измерения - мм.).
///
/// \returns Указатель на прямую трубу, если она доступна, иначе nullptr.
const DirectPipe* PipeObjectsBag::getDirectPipeP(unsigned int diameter) const {
    
    auto directPipeIter = directPipeForDiameter.find(diameter);
    
    return (directPipeIter == directPipeForDiameter.end()) ? nullptr : &(directPipeIter->second);
    
}

/// Вернуть указатель на фановую трубу заданного диаметра.
///
/// \param diameter Диаметр трубы (единица измерения - мм.).
///
/// \returns Указатель на фановую трубу, если она доступна, иначе nullptr.
const FanPipe* PipeObjectsBag::getFanPipeP(unsigned int diameter) const {
    
    auto fanPipeIter = fanPipeForDiameter.find(diameter);
    
    return (fanPipeIter == fanPipeForDiameter.end()) ? nullptr : &(fanPipeIter->second);
    
}

/// Вернуть указатель на массив доступных редукций заданного П-диаметра. Редукции в массиве упорядочены по возрастанию м-диаметров.
///
/// \param fDiameter П-диаметр редукции (единица измерения - мм.).
///
/// \return Указатель на массив редукций П-диаметра diameter. Если редукции данного диаметра не доступны, возвращается nullptr.
const std::vector<ReductionPipe> * PipeObjectsBag::getReductionPipePs(unsigned int fDiameter) const {
    
    auto reductionPipesIter = reductionPipesForFDiameter.find(fDiameter);
    
    return (reductionPipesIter != reductionPipesForFDiameter.end()) ? &(reductionPipesIter->second) : nullptr;
    
}

/// Вернуть указатель на массив доступных отводов заданного диаметра. Отвод - изогнутая труба с одним входом и одним выходом. Отводы в массиве упорядочены по возрастанию углов.
///
/// \param diameter Диаметр отвода (единица измерения - мм.).
///
/// \returns Указатель на массив доступных отводов диаметра diameter. Если отводы данного диаметра не доступны, возвращается nullptr.
const std::vector<AnglePipe> * PipeObjectsBag::getAnglePipePs(unsigned int diameter) const {
    
    auto anglePipesIter = anglePipesForDiameter.find(diameter);
    
    return (anglePipesIter != anglePipesForDiameter.end()) ? &(anglePipesIter->second) : nullptr;
    
}

/// Вернуть указатель на массив доступных тройников заданного основного диаметра. Тройник - прямая труба со вставкой третьего входа. Тройники в массиве упорядочены по возрастанию диаметров вставки.
///
/// \param baseDiameter Основной диаметр тройника (единица измерения - мм.).
///
/// \returns Указатель на массив доступных тройников основного диаметра baseDiameter. Если тройники данного диаметра не доступны, возвращается nullptr.
const std::vector<TeePipe> * PipeObjectsBag::getTeePipePs(unsigned int baseDiameter) const {
    
    auto teePipesIter = teePipesForBaseDiameter.find(baseDiameter);
    
    return (teePipesIter != teePipesForBaseDiameter.end()) ? &(teePipesIter->second) : nullptr;
    
}

/// Вернуть указатель на массив доступных крестовин заданного основного диаметра. Крестовина - крестовина - прямая труба со вставкой второго и третьего входов. Крестовины в массиве упорядочены по возрастанию вторых диаметров.
///
/// \param baseDiameter Основной диаметр крестовины (единица измерения - мм.).
///
/// \returns Указатель на массив доступных крестовин основного диаметра baseDiameter. Если крестовины данного диаметра не доступны, возвращается nullptr.
const std::vector<CrossPipe> * PipeObjectsBag::getCrossPipePs(unsigned int baseDiameter) const {
    
    auto crossPipesIter = crossPipesForBaseDiameter.find(baseDiameter);
    
    return (crossPipesIter != crossPipesForBaseDiameter.end()) ? &(crossPipesIter->second) : nullptr;
    
}

/// Загрузить внешние диаметры соединений объектов из файла. Метод бросает Exception-исключение в случае некорректных данных. В случае вызова исключения состояние объекта остается неопределенным.
///
/// \param fileName Имя файла в формате CSV.
void PipeObjectsBag::loadExternalDiametersFromFile(const std::string & fileName) {
    
    externalDiameterForDiameter.clear();
    
    try {
        
        std::ifstream stream(fileName);
        if (stream.fail()) {
            throw Exception("Ошибка при открытии CSV-файла с внешними диаметрами.");
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
            
            std::string lineErrorMessagePrefix = "Ошибка при чтении CSV-файла с внешними диаметрами в строке " + std::to_string(lineNumber);
            
            if (line.empty()) {
                lineNumber++;
                continue;
            }
            
            std::istringstream lineStream(line);
            
            std::string extraStr;
            unsigned int diameter, externalDiameter;
            
            std::string readingColumnName;
            
            try {
                
                // чтение поля diameter
                readingColumnName = "Диаметр (мм.)";
                extraStr = "";
                std::getline(lineStream, extraStr, delimeter);
                diameter = std::stoi(extraStr);
                
                // чтение поля externalDiameter
                readingColumnName = "Внешний диаметр (мм.)";
                extraStr = "";
                std::getline(lineStream, extraStr, delimeter);
                externalDiameter = std::stoi(extraStr);
                
                if (externalDiameter < diameter) {
                    throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Внешний диаметр не может быть меньше обычного диаметра.");
                }
                
            }
            catch (const Exception & exception) {
                throw exception;
            }
            catch (...) {
                throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Некорректный формат поля.");
            }
            
            externalDiameterForDiameter[diameter] = externalDiameter;
            
            lineNumber++;
            line = "";
            
        }
        
        stream.close();
        
    }
    catch (const Exception & exception) {
        throw exception;
    }
    catch (...) {
        throw Exception("Ошибка при чтении CSV-файла с внешними диаметрами.");
    }
    
}

/// Загрузить доступные к использованию объекты из файла. Метод бросает Exception-исключение в случае некорректных данных. В случае вызова исключения состояние объекта остается неопределенным.
///
/// \param fileName Имя файла в формате CSV.
void PipeObjectsBag::loadObjectsFromFile(const std::string & fileName) {
    
    std::set<unsigned int> diameters;
    
    // 1. Очищение объектов.
    
    this->diameters.clear();
    this->directPipeForDiameter.clear();
    this->fanPipeForDiameter.clear();
    this->reductionPipesForFDiameter.clear();
    this->anglePipesForDiameter.clear();
    this->teePipesForBaseDiameter.clear();
    this->crossPipesForBaseDiameter.clear();
    
    // 2. загрузка доступных объектов из файла
    
    try {
        
        std::ifstream stream(fileName);
        if (stream.fail()) {
            throw Exception("Ошибка при открытии CSV-файла с доступными материалами.");
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
            
            std::string lineErrorMessagePrefix = "Ошибка при чтении CSV-файла с доступными материалами в строке " + std::to_string(lineNumber);
            
            if (line.empty()) {
                lineNumber++;
                continue;
            }
            
            std::istringstream lineStream(line);
            
            std::string objectTypeStr, name, extraStr;
            int diameter1 = 0, diameter2 = 0, diameter3 = 0, angle = 0, length1 = 0, length2 = 0, length3 = 0, length4 = 0;
            int id = 0;
            CalcNumber cost = 0;
            ReductionPipe::AlignmentType reductionAlignmentType = ReductionPipe::center;
            CrossPipe::Type crossType = CrossPipe::usual;
            PipeObjectType objectType;
            
            // чтение поля objectType
            objectTypeStr = "";
            std::getline(lineStream, objectTypeStr, delimeter);
            
            if (objectTypeStr == "труба" || objectTypeStr == "труба фановая" || objectTypeStr == "редукция" || objectTypeStr == "отвод" || objectTypeStr == "тройник" || objectTypeStr == "крестовина" || objectTypeStr == "Труба" || objectTypeStr == "Труба фановая" || objectTypeStr == "Редукция" || objectTypeStr == "Отвод" || objectTypeStr == "Тройник" || objectTypeStr == "Крестовина") {
                
                objectType = (objectTypeStr == "труба" || objectTypeStr == "Труба") ? PipeObjectType::direct : (objectTypeStr == "труба фановая" || objectTypeStr == "Труба фановая") ? PipeObjectType::fan : (objectTypeStr == "редукция" || objectTypeStr == "Редукция") ? PipeObjectType::reduction : (objectTypeStr == "отвод" || objectTypeStr == "Отвод") ? PipeObjectType::angle : (objectTypeStr == "тройник" || objectTypeStr == "Тройник") ? PipeObjectType::tee : PipeObjectType::cross;
                
                std::string readingColumnName;
                
                try {
                    
                    // чтение поля id
                    readingColumnName = "ИД";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    id = std::stoi(extraStr);
                    
                    // чтение поля name
                    readingColumnName = "Наименование";
                    name = "";
                    std::getline(lineStream, name, delimeter);
                    
                    // чтение поля diameter1
                    readingColumnName = "Диаметр 1 (мм.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    diameter1 = std::stoi(extraStr);
                    if (diameter1 < 1) {
                        throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Диаметр 1 должен быть положительным.");
                    }
                    
                    // чтение поля diameter2
                    readingColumnName = "Диаметр 2 (мм.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    if (objectType == PipeObjectType::reduction || objectType == PipeObjectType::tee || objectType == PipeObjectType::cross) {
                        diameter2 = std::stoi(extraStr);
                        if (diameter2 < 1) {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Диаметр 2 должен быть положительным.");
                        }
                        if (objectType == PipeObjectType::reduction && diameter2 >= diameter1) {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Для редукции диаметр 2 должен быть меньше, чем диаметр 1.");
                        } else if (diameter2 > diameter1) {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Для тройника и крестовины диаметр 2 не должен превосходить диаметра 1.");
                        }
                    }
                    
                    // чтение поля diameter3
                    readingColumnName = "Диаметр 3 (мм.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    if (objectType == PipeObjectType::cross) {
                        diameter3 = std::stoi(extraStr);
                        if (diameter3 < 1) {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Диаметр 3 должен быть положительным.");
                        }
                    }
                    
                    // чтение поля angle
                    readingColumnName = "Угол (гр.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    if (objectType == PipeObjectType::angle || objectType == PipeObjectType::tee || objectType == PipeObjectType::cross) {
                        angle = std::stoi(extraStr);
                        if (angle < 1 || angle > 90) {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Величина угла должна принадлежать отрезку [1, 90].");
                        }
                    }
                    
                    // чтение поля length1
                    readingColumnName = "Длина 1 (мм.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    if (objectType != PipeObjectType::direct && objectType != PipeObjectType::fan) {
                        length1 = std::stoi(extraStr);
                        if (length1 < 1) {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Длина 1 должна быть положительным.");
                        }
                    }
                    
                    // чтение поля length2
                    readingColumnName = "Длина 2 (мм.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    if (objectType == PipeObjectType::angle || objectType == PipeObjectType::tee || objectType == PipeObjectType::cross) {
                        length2 = std::stoi(extraStr);
                        if (length2 < 1) {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Длина 2 должна быть положительным.");
                        }
                    }
                    
                    // чтение поля length3
                    readingColumnName = "Длина 3 (мм.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    if (objectType == PipeObjectType::tee || objectType == PipeObjectType::cross) {
                        length3 = std::stoi(extraStr);
                        if (length3 < 1) {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Длина 3 должна быть положительным.");
                        }
                    }
                    
                    // чтение поля length4
                    readingColumnName = "Длина 4 (мм.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    if (objectType == PipeObjectType::cross) {
                        length4 = std::stoi(extraStr);
                        if (length4 < 1) {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Длина 4 должна быть положительным.");
                        }
                    }
                    
                    // чтение поля crossType
                    readingColumnName = "Тип крестовины";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    if (objectType == PipeObjectType::cross) {
                        if ((extraStr == "левая" || extraStr == "правая" || extraStr == "" || extraStr == "Левая" || extraStr == "Правая") == false) {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Неверный тип крестовины.");
                        }
                        crossType = (extraStr == "левая" || extraStr == "Левая") ? CrossPipe::left : (extraStr == "правая" || extraStr == "Правая") ? CrossPipe::right : CrossPipe::usual;
                    }
                    
                    // чтение поля reductionAlignmentType
                    readingColumnName = "Тип выравнивания редукции";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    if (objectType == PipeObjectType::reduction) {
                        if ((extraStr == "по центру" || extraStr == "по краю" || extraStr == "По центру" || extraStr == "По краю") == false) {
                            throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Неверный тип выравнивания редукции.");
                        }
                        reductionAlignmentType = (extraStr == "по центру" || extraStr == "По центру") ? ReductionPipe::center : ReductionPipe::edge;
                    }
                    
                    // чтение поля cost
                    readingColumnName = "Стоимость (руб./шт. или руб./мм.)";
                    extraStr = "";
                    std::getline(lineStream, extraStr, delimeter);
                    cost = std::stod(extraStr);
                    
                }
                catch (const Exception & exception) {
                    throw exception;
                }
                catch (...) {
                    throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Некорректный формат поля.");
                }
                
                if (objectType == PipeObjectType::direct) {
                    
                    diameters.insert(diameter1);
                    directPipeForDiameter[diameter1] = DirectPipe(diameter1, id, name, cost, &externalDiameterForDiameter);
                    
                } else if (objectType == PipeObjectType::fan) {
                    
                    diameters.insert(diameter1);
                    fanPipeForDiameter[diameter1] = FanPipe(diameter1, id, name, cost, &externalDiameterForDiameter);
                    
                } else if (objectType == PipeObjectType::reduction) {
                    
                    diameters.insert(diameter1);
                    diameters.insert(diameter2);
                    
                    if (reductionPipesForFDiameter.find(diameter1) == reductionPipesForFDiameter.end()) {
                        reductionPipesForFDiameter[diameter1] = std::vector<ReductionPipe>();
                    }
                    reductionPipesForFDiameter[diameter1].push_back(ReductionPipe(diameter1, diameter2, length1, reductionAlignmentType, id, name, cost, &externalDiameterForDiameter));
                    
                } else if (objectType == PipeObjectType::angle) {
                    
                    diameters.insert(diameter1);
                    
                    if (anglePipesForDiameter.find(diameter1) == anglePipesForDiameter.end()) {
                        anglePipesForDiameter[diameter1] = std::vector<AnglePipe>();
                    }
                    anglePipesForDiameter[diameter1].push_back(AnglePipe(diameter1, angle, length1, length2, id, name, cost, &externalDiameterForDiameter, config));
                    
                } else if (objectType == PipeObjectType::tee) {
                    
                    diameters.insert(diameter1);
                    diameters.insert(diameter2);
                    
                    if (teePipesForBaseDiameter.find(diameter1) == teePipesForBaseDiameter.end()) {
                        teePipesForBaseDiameter[diameter1] = std::vector<TeePipe>();
                    }
                    teePipesForBaseDiameter[diameter1].push_back(TeePipe(diameter1, diameter2, angle, length1, length2, length3, id, name, cost, &externalDiameterForDiameter));
                    
                } else {
                    
                    diameters.insert(diameter1);
                    diameters.insert(diameter2);
                    diameters.insert(diameter3);
                    
                    if (crossPipesForBaseDiameter.find(diameter1) == crossPipesForBaseDiameter.end()) {
                        crossPipesForBaseDiameter[diameter1] = std::vector<CrossPipe>();
                    }
                    crossPipesForBaseDiameter[diameter1].push_back(CrossPipe(diameter1, diameter2, diameter3, crossType, angle, length1, length2, length3, length4, id, name, cost, &externalDiameterForDiameter));
                    
                }
                
            } else {
                throw Exception(lineErrorMessagePrefix + ". Неверный тип.");
            }
            
            lineNumber++;
            line = "";
            
        }
        
        stream.close();
        
        for (unsigned int diameter : diameters) {
            this->diameters.push_back(diameter);
        }
        
    }
    catch (const Exception & exception) {
        throw exception;
    }
    catch (...) {
        throw Exception("Ошибка при чтении CSV-файла с доступными материалами.");
    }
    
    // 3. сортировка загруженных объектов
    
    std::sort(this->diameters.begin(), this->diameters.end());
    
    for (auto & reductions : reductionPipesForFDiameter) {
        unsigned int fDiameter = reductions.first;
        std::sort(reductionPipesForFDiameter[fDiameter].begin(), reductionPipesForFDiameter[fDiameter].end());
    }
    
    for (auto & anglePipes : anglePipesForDiameter) {
        unsigned int diameter = anglePipes.first;
        std::sort(anglePipesForDiameter[diameter].begin(), anglePipesForDiameter[diameter].end());
    }
    
    for (auto & teePipes : teePipesForBaseDiameter) {
        unsigned int baseDiameter = teePipes.first;
        std::sort(teePipesForBaseDiameter[baseDiameter].begin(), teePipesForBaseDiameter[baseDiameter].end());
    }
    
    for (auto & crossPipes : crossPipesForBaseDiameter) {
        unsigned int baseDiameter = crossPipes.first;
        std::sort(crossPipesForBaseDiameter[baseDiameter].begin(), crossPipesForBaseDiameter[baseDiameter].end());
    }
    
}

/// Проверить наличие внешнего диаметра для каждого диаметра. Метод бросает Exception-исключение в случае неуспеха.
void PipeObjectsBag::checkExternalDiameters() {
    
    for (unsigned int diameter : diameters) {
        
        if (externalDiameterForDiameter.find(diameter) == externalDiameterForDiameter.end()) {
            
            throw Exception("В CSV-файле с внешними диаметрами отсутствует внешний диаметр для диаметра " + std::to_string(diameter) + ", который присутствует в CSV-файле с доступными материалами.");
            
        }
        
    }
    
}

#endif /* PipeObjectsBag_hpp */
