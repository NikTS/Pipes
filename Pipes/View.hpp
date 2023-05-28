#ifndef View_hpp
#define View_hpp

// Подключение стандартных библиотек
#include <string>

/// Объект, отвечающий за вывод сообщений и ошибок.
class View {
    
public:
    
    // MARK: - Открытые методы
    
    /// Вывести сообщение.
    ///
    /// \param message Выводимое соощение.
    virtual void printMessage(std::string message) = 0;
    
    /// Вывести сообщение об ошибке.
    ///
    /// \param error Выводимое соощение об ошибке.
    virtual void printError(std::string error) = 0;
    
};

#endif /* View_hpp */
