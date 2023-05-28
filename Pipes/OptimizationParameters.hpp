#ifndef OptimizationParameters_hpp
#define OptimizationParameters_hpp

// Подключение внутренних типов
#include "CalcNumber.hpp"

/// Параметры алгоритма оптимизации.
struct OptimizationParameters {
    
    // MARK: - Открытые объекты
    
    /// Минимально расстояние между точками входа разделяемых источников (единица измерения - мм.).
    CalcNumber minSourceDistanceToSeparate = 150;
    
    /// Максимальная ширина сечения при разделении узлов (единица измерения - мм.).
    CalcNumber maxNodeWidthToSeparate = 150;
    
    // MARK: - Конструкторы
    
    /// Конструктор по умолчанию. Параметры инициализируются значениями по умолчанию.
    explicit OptimizationParameters();
    
};

// MARK: - Реализация

/// Конструктор по умолчанию. Параметры инициализируются значениями по умолчанию.
OptimizationParameters::OptimizationParameters() {}

#endif /* OptimizationParameters_hpp */
