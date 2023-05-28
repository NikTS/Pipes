#ifndef SimplePipeTrack_hpp
#define SimplePipeTrack_hpp

// Подключение стандартных библиотек
#include <math.h>
#include <set>
#include <map>

// Подключение внутренних типов
#include "CalcNumber.hpp"

/// Трасса системы водоотведения.
///
/// Представляется в виде дерева с корнем в точке стока и листьями в точках-источниках (таким образом, направление дерева (от корня к листьям) противоположно направлению течения воды по трубам трассы).
///
/// Каждый узел дерева включает 1) точку пересечения смежных прямолинейных участков труб (вершина трассы), 2) диаметр трубы, идущей до вершины, 3) массив указателей на следующие (находящиеся выше по уровню) узлы трассы.
struct SimplePipeTrack {
    
private:
    
    // MARK: - Скрытые объекты
    
    /// Словарь пар вида (идентификатор узла, указатель на узел).
    std::map<int, SimplePipeTrackNode*> nodePsForId;
    
public:
    
    // MARK: - Открытые объекты
    
    /// Указатель на корневой узел трассы.
    SimplePipeTrackNode * rootNodeP;
    
    // MARK: - Конструкторы
    
    /// Конструктор. Создается пустая трасса.
    explicit SimplePipeTrack();
    
    /// Конструктор копирования.
    ///
    /// \param anotherSimplePipeTrack Копируемая трасса.
    SimplePipeTrack(const SimplePipeTrack & anotherSimplePipeTrack);
    
    // MARK: - Деструктор
    
    /// Деструктор.
    ~SimplePipeTrack();
    
    // MARK: - Открытые методы
    
    /// Оператор копирования.
    ///
    /// \param anotherSimplePipeTrack Копируемая трасса.
    SimplePipeTrack & operator=(const SimplePipeTrack & anotherSimplePipeTrack);
    
    /// Добавить новый корневой узел в дерево трассы. При этом старый корневой узел (в случае его наличия) становится дочерним узлом добавляемого. При добавлении нового корневого узла пересчитывается вектор трубы, идущей к вершине старого корневого узла, а также ее диаметр.
    ///
    /// \param id Идентификатор узла. Должен быть уникальным.
    /// \param point Вершина узла (единица измерения - мм.).
    /// \param diameter Диаметр трубы, идущей от вершины добавляемого узла к вершине старого узла (единица измерения - мм.). Должен быть положительным. Если до добавления в дереве не было корневого узла, данное значение не используется.
    void addNewRootNode(int id, const Point & point, unsigned int diameter);
    
    /// Добавить новый узел в дерево трассы. Узел присоединяется к существующему узлу (становится его дочерним узлом).
    ///
    /// \param newNodeId Идентификатор добавляемого узла.
    /// \param newNodePoint Вершина добавляемого узла (единица измерения - мм.).
    /// \param newNodeDiameter Диаметр трубы, идущей к вершине добавляемого узла (единица измерения - мм.). Должен быть положительным.
    /// \param existingNodeId Идентификатор узла, к которому присоединяется новый узел. Узел с данным идентификатором должен существовать в дереве.
    void addNewNodeToExisting(int newNodeId, const Point & newNodePoint, CalcNumber newNodeDiameter, int existingNodeId);
    
    /// Вернуть указатель на узел дерева трассы по его идентификатору.
    ///
    /// \param nodeId Идентификатор узла.
    ///
    /// \returns Указатель на узел дерева с идентификатором nodeId или nullptr, если узла с данным идентификатором нет в дереве.
    SimplePipeTrackNode* getNodePForId(int nodeId) const;
    
    /// Рассчитать синус минимального угла наклона труб. Под углом трубы понимается угол между осью трубы и плоскостью Oxy. Для трубы с вершинами A (ближе к источнику) и B (ближе к стоку) угол считается положительным, если z-координата вершины B меньше, чем вершины A.
    ///
    /// \returns Синус минимального угла наклона труб. Если схема не содержит труб, возвращается 1.
    CalcNumber calculateMinSlopeAngleSin() const;
    
private:
    
    // MARK: - Скрытые методы
    
    /// Создать копию поддерева трассы.
    ///
    /// \param rootNodeP Указатель на корневой узел копируемого поддерева.
    ///
    /// \return Указатель на корневой узел созданной копии поддерева.
    SimplePipeTrackNode * createSubTreeCopy(const SimplePipeTrackNode * rootNodeP) const;
    
    /// Удалить поддерево трассы.
    ///
    /// \param rootNodeP Указатель на корневой узел удаляемого поддерева.
    void deleteSubTree(SimplePipeTrackNode * rootNodeP);
    
    /// Рассчитать синус минимального угла наклона труб для поддерева трассы (без учета трубы, идущей к корневой вершине). Под углом трубы понимается угол между осью трубы и плоскостью Oxy. Для трубы с вершинами A (ближе к источнику) и B (ближе к стоку) угол считается положительным, если z-координата вершины B меньше, чем вершины A.
    ///
    /// \param rootNodeP Указатель на корневой узел поддерева.
    ///
    /// \returns Синус минимального угла наклона труб для поддерева трассы. Если схема не содержит труб, возвращается 1.
    CalcNumber calculateMinSlopeAngleSin(const SimplePipeTrackNode * rootNodeP) const;
    
};

// MARK: - Реализация

/// Конструктор. Создается пустая трасса.
SimplePipeTrack::SimplePipeTrack(): rootNodeP(nullptr) {}
    
/// Конструктор копирования.
///
/// \param anotherSimplePipeTrack Копируемая трасса.
SimplePipeTrack::SimplePipeTrack(const SimplePipeTrack & anotherSimplePipeTrack) {
    
    this->nodePsForId = anotherSimplePipeTrack.nodePsForId;
    *this = anotherSimplePipeTrack;
    
}

/// Деструктор.
SimplePipeTrack::~SimplePipeTrack() {
    
    deleteSubTree(rootNodeP);
    rootNodeP = nullptr;
    
}

/// Оператор копирования.
///
/// \param anotherSimplePipeTrack Копируемая трасса.
SimplePipeTrack & SimplePipeTrack::operator=(const SimplePipeTrack & anotherSimplePipeTrack) {
    
    this->nodePsForId = anotherSimplePipeTrack.nodePsForId;
    this->rootNodeP = createSubTreeCopy(anotherSimplePipeTrack.rootNodeP);
    
    return *this;
    
}

/// Добавить новый корневой узел в дерево трассы. При этом старый корневой узел (в случае его наличия) становится дочерним узлом добавляемого. При добавлении нового корневого узла пересчитывается вектор трубы, идущей к вершине старого корневого узла, а также ее диаметр.
///
/// \param id Идентификатор узла. Должен быть уникальным.
/// \param point Вершина узла (единица измерения - мм.).
/// \param diameter Диаметр трубы, идущей от вершины добавляемого узла к вершине старого узла (единица измерения - мм.). Должен быть положительным. Если до добавления в дереве не было корневого узла, данное значение не используется.
void SimplePipeTrack::addNewRootNode(int id, const Point & point, unsigned int diameter) {
    
    assert(nodePsForId.find(id) == nodePsForId.end());
    
    SimplePipeTrackNode* nodeP = new SimplePipeTrackNode(id, point, Point(0, 0, 0), 1, std::vector<SimplePipeTrackNode*>());
    
    if (rootNodeP != nullptr) {
        rootNodeP->pipeDirection = (rootNodeP->point - point);
        rootNodeP->diameter = diameter;
        nodeP->nextNodesPs.push_back(rootNodeP);
    }
    
    rootNodeP = nodeP;
    nodePsForId[id] = nodeP;
    
}

/// Добавить новый узел в дерево трассы. Узел присоединяется к существующему узлу (становится его дочерним узлом).
///
/// \param newNodeId Идентификатор добавляемого узла.
/// \param newNodePoint Вершина добавляемого узла (единица измерения - мм.).
/// \param newNodeDiameter Диаметр трубы, идущей к вершине добавляемого узла (единица измерения - мм.). Должен быть положительным.
/// \param existingNodeId Идентификатор узла, к которому присоединяется новый узел. Узел с данным идентификатором должен существовать в дереве.
void SimplePipeTrack::addNewNodeToExisting(int newNodeId, const Point & newNodePoint, CalcNumber newNodeDiameter, int existingNodeId) {
    
    assert(nodePsForId.find(newNodeId) == nodePsForId.end());
    auto existingNodePIter = nodePsForId.find(existingNodeId);
    assert(existingNodePIter != nodePsForId.end());
    
    SimplePipeTrackNode* existingNodeP = existingNodePIter->second;
    
    SimplePipeTrackNode* newNodeP = new SimplePipeTrackNode(newNodeId, newNodePoint, newNodePoint - existingNodeP->point, newNodeDiameter, std::vector<SimplePipeTrackNode*>());
    existingNodeP->nextNodesPs.push_back(newNodeP);
    
    nodePsForId[newNodeId] = newNodeP;
    
}

/// Вернуть указатель на узел дерева трассы по его идентификатору.
///
/// \param nodeId Идентификатор узла.
///
/// \returns Указатель на узел дерева с идентификатором nodeId или nullptr, если узла с данным идентификатором нет в дереве.
SimplePipeTrackNode* SimplePipeTrack::getNodePForId(int nodeId) const {
    
    auto iter = nodePsForId.find(nodeId);
    if (iter == nodePsForId.end()) {
        return nullptr;
    }
    return iter->second;
    
}
    
/// Рассчитать синус минимального угла наклона труб. Под углом трубы понимается угол между осью трубы и плоскостью Oxy. Для трубы с вершинами A (ближе к источнику) и B (ближе к стоку) угол считается положительным, если z-координата вершины B меньше, чем вершины A.
///
/// \returns Синус минимального угла наклона труб. Если схема не содержит труб, возвращается 1.
CalcNumber SimplePipeTrack::calculateMinSlopeAngleSin() const {
    
    return calculateMinSlopeAngleSin(rootNodeP);
    
}
    
/// Создать копию поддерева трассы.
///
/// \param rootNodeP Указатель на корневой узел копируемого поддерева.
///
/// \return Указатель на корневой узел созданной копии поддерева.
SimplePipeTrackNode * SimplePipeTrack::createSubTreeCopy(const SimplePipeTrackNode * rootNodeP) const {
    
    if (rootNodeP == nullptr) {
        return nullptr;
    }
    
    SimplePipeTrackNode * newRootNodeP = new SimplePipeTrackNode(rootNodeP->id, rootNodeP->point, rootNodeP->pipeDirection, rootNodeP->diameter, std::vector<SimplePipeTrackNode*>());
    for (const SimplePipeTrackNode * nodeP: rootNodeP->nextNodesPs) {
        newRootNodeP->nextNodesPs.push_back(createSubTreeCopy(nodeP));
    }
    
    return newRootNodeP;
    
}

/// Удалить поддерево трассы.
///
/// \param rootNodeP Указатель на корневой узел удаляемого поддерева.
void SimplePipeTrack::deleteSubTree(SimplePipeTrackNode * rootNodeP) {
    
    if (rootNodeP != nullptr) {
        
        for (SimplePipeTrackNode * nodeP: rootNodeP->nextNodesPs) {
            deleteSubTree(nodeP);
        }
        rootNodeP->nextNodesPs.clear();
        nodePsForId.erase(rootNodeP->id);
        
        delete rootNodeP;
        
    }
    
}

/// Рассчитать синус минимального угла наклона труб для поддерева трассы (без учета трубы, идущей к корневой вершине). Под углом трубы понимается угол между осью трубы и плоскостью Oxy. Для трубы с вершинами A (ближе к источнику) и B (ближе к стоку) угол считается положительным, если z-координата вершины B меньше, чем вершины A.
///
/// \param rootNodeP Указатель на корневой узел поддерева.
///
/// \returns Синус минимального угла наклона труб для поддерева трассы. Если схема не содержит труб, возвращается 1.
CalcNumber SimplePipeTrack::calculateMinSlopeAngleSin(const SimplePipeTrackNode * rootNodeP) const {
    
    CalcNumber minSlopeAngleSin = 1;
    
    if (rootNodeP != nullptr) {
        
        for (SimplePipeTrackNode * nodeP: rootNodeP->nextNodesPs) {
            
            // Учесть поддерево с корнем *nodeP
            minSlopeAngleSin = std::min(minSlopeAngleSin, calculateMinSlopeAngleSin(nodeP));
            
            // Учесть трубу к вершине узла *nodeP
            Point pipeDirection = nodeP->pipeDirection;
            CalcNumber slopeAngleSin = pipeDirection.z / pipeDirection.length();
            minSlopeAngleSin = std::min(minSlopeAngleSin, slopeAngleSin);
            
        }
        
    }
    
    return minSlopeAngleSin;
    
}

#endif /* SimplePipeTrack_hpp */
