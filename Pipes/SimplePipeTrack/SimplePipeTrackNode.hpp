#ifndef SimplePipeTrackNode_hpp
#define SimplePipeTrackNode_hpp

// Подключение стандартных библиотек
#include <vector>
#include <cassert>

// Подключение внутренних типов
#include "CalcNumber.hpp"
#include "WaterSource.hpp"

/// Узел трассы системы водоотведения. Включает 1) точку пересечения смежных прямолинейных участков труб (вершина трассы), 2) диаметр трубы, идущей до вершины, 3) массив указателей на следующие (находящиеся выше по уровню) узлы трассы.
struct SimplePipeTrackNode {
    
    // MARK: - Открытые объекты
    
    /// Идентификатор узла.
    int id;
    
    /// Вершина узла (единица измерения - мм.).
    Point point;
    
    /// Вектор, задающий направление и длину трубы, идущей к вершине point (единица измерения - мм.).
    Point pipeDirection;
    
    /// Диаметр трубы, идущей к вершине point (единица измерения - мм.).
    unsigned int diameter;
    
    /// Массив указателей на следующие (находящиеся выше по уровню) узлы трассы.
    std::vector<SimplePipeTrackNode*> nextNodesPs;
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param id Идентификатор узла.
    /// \param point Вершина узла (единица измерения - мм.).
    /// \param pipeDirection Вектор, задающий направление и длину трубы, идущей к вершине point (единица измерения - мм.).
    /// \param diameter Диаметр трубы, идущей к вершине point (единица измерения - мм.). Должен быть положительным.
    /// \param nextNodesPs Массив указателей на следующие (находящиеся выше по уровню) узлы трассы.
    explicit SimplePipeTrackNode(int id, const Point & point, const Point & pipeDirection, unsigned int diameter, const std::vector<SimplePipeTrackNode*> & nextNodesPs);
    
};

// MARK: - Реализация

/// Конструктор.
///
/// \param id Идентификатор узла.
/// \param point Вершина узла (единица измерения - мм.).
/// \param pipeDirection Вектор, задающий направление и длину трубы, идущей к вершине point (единица измерения - мм.).
/// \param diameter Диаметр трубы, идущей к вершине point (единица измерения - мм.). Должен быть положительным.
/// \param nextNodesPs Массив указателей на следующие (находящиеся выше по уровню) узлы трассы.
SimplePipeTrackNode::SimplePipeTrackNode(int id, const Point & point, const Point & pipeDirection, unsigned int diameter, const std::vector<SimplePipeTrackNode*> & nextNodesPs): id(id), point(point), pipeDirection(pipeDirection), diameter(diameter), nextNodesPs(nextNodesPs) {
    
    assert(diameter > 0);
    
}

#endif /* SimplePipeTrackNode_hpp */
