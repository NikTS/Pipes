#ifndef DecisionMaker_hpp
#define DecisionMaker_hpp

// Подключение стандартных библиотек
#include <map>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>

// Подключение внутренних типов
#include "Exception.hpp"
#include "View.hpp"

/// Объект, отвечающий за принятие неоднозначных решений при нахождении оптимальной трассы системы водоотведения.
class DecisionMaker {
    
public:
    
    // MARK: - Вспомогательные типы
    
    /// Альтернатива при принятии решения.
    struct Alternative {
        
        /// Номер альтернативы.
        unsigned int number;
        
        /// Описание альтернативы.
        std::string description;
        
        /// Конструктор.
        ///
        /// \param number Номер альтернативы.
        /// \param description Описание альтернативы.
        Alternative(unsigned int number, const std::string & description): number(number), description(description) {}
        
    };
    
private:
    
    // MARK: - Скрытые объекты
    
    /// Объект, отвечающий за вывод сообщений и ошибок.
    View & view;
    
    /// Последний сгенерированный уникальный идентификатор решения.
    unsigned int lastGeneratedId = 0;
    
    /// Принятые решения. Словарь состоит из пар вида (номер решения, номер альтернативы).
    std::map<unsigned int, unsigned int> decisions;
    
public:
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param view Объект, отвечающий за вывод сообщений и ошибок.
    explicit DecisionMaker(View & view);
    
    // MARK: - Открытые методы
    
    /// Загрузить принятые решения из файла. Метод бросает Exception-исключение в случае некорректных данных.
    ///
    /// \param fileName Имя файла в формате CSV.
    void loadDecisionsFromFile(const std::string & fileName);
    
    /// Помочь с выбором альтернативы при принятии решения. Данный метод возвращает номер нужной альтернативы или номер альтернативы по умолчанию, если для данного решения альтернатива не выбрана. Альтернативой по умолчанию является первая альтернатива из вектора alternatives.
    ///
    /// \param decisionDescription Описание принимаемого решения.
    /// \param alternatives Альтернативы при принятии данного решения. Должна быть хотя бы одна альтернатива.
    ///
    /// \return Номер принятой альтернативы.
    unsigned int helpWithDecision(const std::string & decisionDescription, const std::vector<Alternative> & alternatives);
    
private:
    
    // MARK: - Скрытые методы
    
    /// Сгенерировать уникальный идентификатор решения.
    ///
    /// \return Уникальный идентификатор решения.
    unsigned int generateNewId();
    
};

// MARK: - Реализация

/// Конструктор.
///
/// \param view Объект, отвечающий за вывод сообщений и ошибок.
DecisionMaker::DecisionMaker(View & view): view(view) {}

/// Загрузить принятые решения из файла. Метод бросает Exception-исключение в случае некорректных данных.
///
/// \param fileName Имя файла в формате CSV.
void DecisionMaker::loadDecisionsFromFile(const std::string & fileName) {
    
    decisions.clear();
    
    try {
        
        std::ifstream stream(fileName);
        if (stream.fail()) {
            throw Exception("Ошибка при открытии CSV-файла с принятыми решениями.");
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
            
            std::string lineErrorMessagePrefix = "Ошибка при чтении CSV-файла с принятыми решениями в строке " + std::to_string(lineNumber);
            
            if (line.empty()) {
                lineNumber++;
                continue;
            }
            
            std::istringstream lineStream(line);
            
            std::string extraStr, readingColumnName;
            int decisionNumber, decisionAlternativeNumber;
            
            // чтения поля decisionNumber
            readingColumnName = "Номер решения";
            extraStr = "";
            std::getline(lineStream, extraStr, delimeter);
            decisionNumber = std::stoi(extraStr);
            if (decisionNumber < 0) {
                throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Данный параметр должен быть неотрицательным.");
            }
            
            // чтения поля decisionResult
            readingColumnName = "Принимаемая альтернатива";
            extraStr = "";
            std::getline(lineStream, extraStr, delimeter);
            decisionAlternativeNumber = std::stoi(extraStr);
            if (decisionAlternativeNumber < 0) {
                throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Данный параметр должен быть неотрицательным.");
            }
            
            decisions[decisionNumber] = decisionAlternativeNumber;
            
            lineNumber++;
            line = "";
            
        }
        
        stream.close();
        
    }
    catch (const Exception & exception) {
        throw exception;
    }
    catch (...) {
        throw Exception("Ошибка при чтении CSV-файла с принятыми решениями.");
    }
    
}

/// Помочь с выбором альтернативы при принятии решения. Данный метод возвращает номер нужной альтернативы или номер альтернативы по умолчанию, если для данного решения альтернатива не выбрана. Альтернативой по умолчанию является первая альтернатива из вектора alternatives.
///
/// \param decisionDescription Описание принимаемого решения.
/// \param alternatives Альтернативы при принятии данного решения. Должна быть хотя бы одна альтернатива.
///
/// \return Номер принятой альтернативы.
unsigned int DecisionMaker::helpWithDecision(const std::string & decisionDescription, const std::vector<Alternative> & alternatives) {
    
    assert(alternatives.size() >= 1);
    
    std::set<unsigned int> alternativeNumbers;
    std::map<unsigned int, std::string> descriptionForAlternativeNumber;
    
    unsigned int decisionId = generateNewId();
    
    view.printMessage("\n**********************************************************************************");
    view.printMessage("Принятие решения №" + std::to_string(decisionId) + ".");
    view.printMessage("\"" + decisionDescription + "\"");
    view.printMessage("\nАльтернативы:");
    
    for (int i = 0; i < alternatives.size(); i++) {
        alternativeNumbers.insert(alternatives[i].number);
        descriptionForAlternativeNumber[alternatives[i].number] = alternatives[i].description;
        view.printMessage(std::to_string(alternatives[i].number) + ((i == 0) ? " (по умолчанию) - \"" : " - \"") + alternatives[i].description + ((i < alternatives.size() - 1) ? "\";" : "\"."));
    }
    
    std::string helpText = "Для изменения номера принимаемой альтернативы добавьте в CSV-файл с принятыми решениями строку вида \"" + std::to_string(decisionId) + ";<номер альтернативы>\".";
    
    auto decisionP = decisions.find(decisionId);
    if (decisionP != decisions.end() && alternativeNumbers.find(decisionP->second) != alternativeNumbers.end()) {
        unsigned int alternativeNumber = decisionP->second;
        view.printMessage("\nПринята альтернатива " + std::to_string(alternativeNumber) + " (\"" + descriptionForAlternativeNumber[alternativeNumber] + "\") согласно команде из файла.");
        view.printMessage("Для изменения номера принимаемой альтернативы измените в CSV-файле с принятыми решениями строку вида \"" + std::to_string(decisionId) + ";<номер альтернативы>\".");
        view.printMessage("**********************************************************************************");
        return alternativeNumber;
    } else {
        view.printMessage("\nПринята альтернатива по умолчанию " + std::to_string(alternatives[0].number) + " (\"" + alternatives[0].description + "\").");
        view.printMessage("Для изменения номера принимаемой альтернативы добавьте в CSV-файл с принятыми решениями строку вида \"" + std::to_string(decisionId) + ";<номер альтернативы>\".");
        view.printMessage("**********************************************************************************");
        return alternatives[0].number;
    }
    
}

/// Сгенерировать уникальный идентификатор решения.
///
/// \return Уникальный идентификатор решения.
unsigned int DecisionMaker::generateNewId() {
    
    return ++lastGeneratedId;
    
}

#endif /* DecisionMaker_hpp */
