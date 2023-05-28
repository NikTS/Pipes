#ifndef LocationGraphNode_hpp
#define LocationGraphNode_hpp

// Подключение стандартных библиотек
#include <vector>
#include <string>

// Подключение внутренних типов
#include "CalcNumber.hpp"
#include "Point.hpp"
#include "WaterSource.hpp"
#include "WaterDestination.hpp"

/// Узел графа локации. Представляет прямоугольную область, в которой могут проходить трубы трассы системы водоотведения.
struct LocationGraphNode {
    
    // MARK: - Открытые объекты
    
    /// Уникальный идентификатор узла.
    unsigned int id;
    
    /// X-координата левого края узла (единица измерения - мм.).
    CalcNumber left;
    
    /// X-координата правого края узла (единица измерения - мм.).
    CalcNumber right;
    
    /// Y-координата нижнего края узла (единица измерения - мм.).
    CalcNumber bottom;
    
    /// Y-координата верхнего края узла (единица измерения - мм.).
    CalcNumber top;
    
    /// Указатели на левые узлы.
    std::vector<LocationGraphNode*> leftNodesPs;
    
    /// Указатели на правые узлы.
    std::vector<LocationGraphNode*> rightNodesPs;
    
    /// Указатели на нижние узлы.
    std::vector<LocationGraphNode*> bottomNodesPs;
    
    /// Указатели на верхние узлы.
    std::vector<LocationGraphNode*> topNodesPs;
    
    /// Указатели на принадлежащие узлу источники воды.
    std::vector<const WaterSource*> waterSourcesPs;
    
    /// Точки входа источников воды в узел на глубину половины внешнего диаметра.
    std::vector<Point> waterSourcesConnectionPoints;
    
    /// Указатель на принадлежащий узлу сток воды или nullptr.
    const WaterDestination * waterDestinationP;
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param id Уникальный идентификатор узла.
    /// \param left X-координата левого края узла (единица измерения - мм.).
    /// \param right X-координата правого края узла (единица измерения - мм.).
    /// \param bottom Y-координата нижнего края узла (единица измерения - мм.).
    /// \param top Y-координата верхнего края узла(единица измерения - мм.).
    explicit LocationGraphNode(unsigned int id, CalcNumber left, CalcNumber right, CalcNumber bottom, CalcNumber top);
    
    // MARK: - Открытые методы
    
    /// Вернуть толщину узла вдоль оси Ox.
    ///
    /// \return Толщина узла вдоль оси Ox (единица измерения - мм.).
    CalcNumber sizeX() const;
    
    /// Вернуть толщину узла вдоль оси Oy.
    ///
    /// \return Толщина узла вдоль оси Oy (единица измерения - мм.).
    CalcNumber sizeY() const;
    
    /// Вернуть массив указателей на все смежные узлы.
    ///
    /// \return Массив указателей на смежные узлы.
    std::vector<LocationGraphNode*> adjacentNodes() const;
    
    /// Вернуть строковое представление позиции узла на плоскости Oxy.
    ///
    /// \return Строковое представление позиции узла на плоскости Oxy.
    std::string positionStr() const;
    
    /// Найти ближайшую к точке point точку, принадлежащую данному узлу.
    ///
    /// \param point Исходная точка (единица измерения - мм.).
    ///
    /// \return Ближайшая к точке point точка, принадлежащая данному узлу (единица измерения - мм.).
    Point findClosestPoint(const Point & point) const;
    
    /// Проверить, содержит ли узел точку point.
    ///
    /// \param point Точка (единица измерения - мм.).
    ///
    /// \return true, если узел содержит точку point, иначе false.
    bool contains(const Point & point) const;
    
    /// Проверить, содержит ли данный узел внутри себя узел anotherNode. Узел называется содержащимся внутри другого узла, если множество точек узла является подмножеством множества точек второго узла.
    ///
    /// \param anotherNode Другой узел.
    ///
    /// \return true, если данный узел содержит внутри себя узел anotherNode, иначе false.
    bool contains(const LocationGraphNode & anotherNode) const;
    
    /// Проверить, пересекается ли данный узел с узлом anotherNode. Узлы считаются пересекающимися, если множество точек их пересечения непусто.
    ///
    /// \param anotherNode Другой узел.
    ///
    /// \return true, если узлы пересекаются, иначе false.
    bool intersectWith(const LocationGraphNode & anotherNode) const;
    
    /// Проверить, имеет ли данный узел ненулевую площадь пересечения с узлом anotherNode (пересекаются ли данные узлы внутренне).
    ///
    /// \param anotherNode Другой узел.
    ///
    /// \return true, если узлы имеют ненулевую площадь пересечения, иначе false.
    bool hasNonZeroIntersectionAreaWith(const LocationGraphNode & anotherNode) const;
    
};

// MARK: - Реализация

/// Конструктор.
///
/// \param id Уникальный идентификатор узла.
/// \param left X-координата левого края узла (единица измерения - мм.).
/// \param right X-координата правого края узла (единица измерения - мм.).
/// \param bottom Y-координата нижнего края узла (единица измерения - мм.).
/// \param top Y-координата верхнего края узла (единица измерения - мм.).
LocationGraphNode::LocationGraphNode(unsigned int id, CalcNumber left, CalcNumber right, CalcNumber bottom, CalcNumber top): id(id), left(left), right(right), bottom(bottom), top(top), waterDestinationP(nullptr) {}

/// Вернуть толщину узла вдоль оси Ox.
///
/// \return Толщина узла вдоль оси Ox (единица измерения - мм.).
CalcNumber LocationGraphNode::sizeX() const {
    
    return right - left;
    
}

/// Вернуть толщину узла вдоль оси Oy.
///
/// \return Толщина узла вдоль оси Oy (единица измерения - мм.).
CalcNumber LocationGraphNode::sizeY() const {
    
    return top - bottom;
    
}

/// Вернуть массив указателей на все смежные узлы.
///
/// \return Массив указателей на смежные узлы.
std::vector<LocationGraphNode*> LocationGraphNode::adjacentNodes() const {
    
    std::vector<LocationGraphNode*> result;
    
    result.insert(result.end(), leftNodesPs.begin(), leftNodesPs.end());
    result.insert(result.end(), rightNodesPs.begin(), rightNodesPs.end());
    result.insert(result.end(), bottomNodesPs.begin(), bottomNodesPs.end());
    result.insert(result.end(), topNodesPs.begin(), topNodesPs.end());
    
    return result;
    
}

/// Вернуть строковое представление позиции узла на плоскости Oxy.
///
/// \return Строковое представление позиции узла на плоскости Oxy.
std::string LocationGraphNode::positionStr() const {
    
    return "(xLeft: " + std::to_string(left) + ", xRight: " + std::to_string(right) + ", yBottom: " + std::to_string(bottom) + ", yTop: " + std::to_string(top) + ")";
    
}

/// Найти ближайшую к точке point точку, принадлежащую данному узлу.
///
/// \param point Исходная точка (единица измерения - мм.).
///
/// \return Ближайшая к точке point точка, принадлежащая данному узлу (единица измерения - мм.).
Point LocationGraphNode::findClosestPoint(const Point & point) const {
    
    CalcNumber x = (point.x < left) ? left : (point.x > right) ? right : point.x;
    CalcNumber y = (point.y < bottom) ? bottom : (point.y > top) ? top : point.y;
    return Point(x, y, 0);
    
}

/// Проверить, содержит ли узел точку point.
///
/// \param point Точка (единица измерения - мм.).
///
/// \return true, если узел содержит точку point, иначе false.
bool LocationGraphNode::contains(const Point & point) const {
    
    return (left <= point.x && point.x <= right && bottom <= point.y && point.y <= top);
    
}

/// Проверить, содержит ли данный узел внутри себя узел anotherNode. Узел называется содержащимся внутри другого узла, если множество точек узла является подмножеством множества точек второго узла.
///
/// \param anotherNode Другой узел.
///
/// \return true, если данный узел содержит внутри себя узел anotherNode, иначе false.
bool LocationGraphNode::contains(const LocationGraphNode & anotherNode) const {
    
    return (left <= anotherNode.left && right >= anotherNode.right && bottom <= anotherNode.bottom && top >= anotherNode.top);
    
}

/// Проверить, пересекается ли данный узел с узлом anotherNode. Узлы считаются пересекающимися, если множество точек их пересечения непусто.
///
/// \param anotherNode Другой узел.
///
/// \return true, если узлы пересекаются, иначе false.
bool LocationGraphNode::intersectWith(const LocationGraphNode & anotherNode) const {
    
    return ((left > anotherNode.right || right < anotherNode.left || bottom > anotherNode.top || top < anotherNode.bottom) == false);
    
}

/// Проверить, имеет ли данный узел ненулевую площадь пересечения с узлом anotherNode (пересекаются ли данные узлы внутренне).
///
/// \param anotherNode Другой узел.
///
/// \return true, если узлы имеют ненулевую площадь пересечения, иначе false.
bool LocationGraphNode::hasNonZeroIntersectionAreaWith(const LocationGraphNode & anotherNode) const {
    
    return ((left >= anotherNode.right || right <= anotherNode.left || bottom >= anotherNode.top || top <= anotherNode.bottom) == false);
    
}

#endif /* LocationGraphNode_hpp */
