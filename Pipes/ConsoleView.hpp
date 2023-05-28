#ifndef ConsoleView_hpp
#define ConsoleView_hpp

// Подключение стандартных библиотек
#include <string>
#include <iostream>

// Подключение внутренних типов
#include "View.hpp"

/// Объект, выводящий сообщения в консоль.
class ConsoleView: public View {
    
public:
    
    // MARK: - Открытые методы
    
    /// Вывести сообщение.
    ///
    /// \param message Выводимое соощение.
    virtual void printMessage(std::string message);
    
    /// Вывести сообщение об ошибке.
    ///
    /// \param error Выводимое соощение об ошибке.
    virtual void printError(std::string error);
    
};

// MARK: - Реализация

/// Вывести сообщение.
///
/// \param message Выводимое соощение.
void ConsoleView::printMessage(std::string message) {
    
    std::cout << message << "\n";
    
}

/// Вывести сообщение об ошибке.
///
/// \param error Выводимое соощение об ошибке.
void ConsoleView::printError(std::string error) {
    
    std::cout << error << "\n";
    
}

#endif /* ConsoleView_hpp */
