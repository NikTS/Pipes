#ifndef Exception_hpp
#define Exception_hpp

// Подключение стандартных библиотек
#include <string>

/// \brief Исключение. Содержит строку, которую необходимо вывести пользователю приложения.
struct Exception {
    
    // MARK: - Открытые объекты
    
    /// \brief Строка, которую необходимо вывести пользователю приложения.
    std::string errorMessage;
    
    // MARK: - Конструкторы
    
    /// \brief Конструктор.
    ///
    /// \param errorMessage Строка, которую необходимо вывести пользователю приложения.
    explicit Exception(std::string errorMessage);
    
};

// MARK: - Реализация

/// \brief Конструктор.
///
/// \param errorMessage Строка, которую необходимо вывести пользователю приложения.
Exception::Exception(std::string errorMessage): errorMessage(errorMessage) {}

#endif /* Exception_hpp */
