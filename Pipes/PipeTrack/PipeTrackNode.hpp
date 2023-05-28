#ifndef PipeTrackNode_hpp
#define PipeTrackNode_hpp

// Подключение внутренних типов
#include "Point.hpp"
#include "SoLESolver.hpp"
#include "Line.hpp"
#include "PipeObjectType.hpp"
#include "PipeObject.hpp"

/// Узел трассы системы водоотведения. Представляет собой расположенный в пространстве объект системы водоотведения (прямая труба, фановая труба, редукция, отвод, тройник или крестовина).
struct PipeTrackNode {
    
    // MARK: - Открытые объекты
    
    /// Тип объекта системы водоотведения.
    PipeObjectType type;
    
    /// Указатель на объект системы водоотведения.
    const PipeObject * pipeObjectP;
    
    /// Центр объекта (для типов "отвод", "тройник", "крестовина"; единица измерения - мм.). Под центром объекта понимается точка пересечения осей труб.
    Point centerPoint;
    
    /// Начало объекта (для типов "прямая труба", "фановая труба", "редукция"; единица измерения - мм.). Под началом объекта понимается центр его м-входа.
    Point startPoint;
    
    /// Конец объекта (для типов "прямая труба", "фановая труба", "редукция"; единица измерения - мм.). Под концом объекта понимается центр м-входа соединенного с его п-выходом объекта.
    Point endPoint;
    
    /// Основное направление объекта (для типов "отвод", "тройник", "крестовина"). Вектор единичной длины, задающий направление от центра объекта в сторону центра его п-выхода.
    Point baseDirection;
    
    /// Второе направление объекта (для типов "отвод", "тройник", "крестовина"). Вектор единичной длины, задающий направление второго м-входа объекта (или просто м-входа для типа "отвод") от центра данного м-входа в сторону центра объекта.
    Point secondDirection;
    
    /// Третье направление объекта (для типа "крестовина"). Вектор единичной длины, задающий направление третьего м-входа объекта от центра данного м-входа в сторону центра объекта.
    Point thirdDirection;
    
    /// Указатель на следующий узел трассы или nullptr. Под следующим узлом понимается узел, соединенный с п-входом данного объекта.
    PipeTrackNode * nextNodeP;
    
    /// Указатель на основной предшествующий узел трассы или nullptr. Под основным предшествующим узлом понимается узел, соединенный с основным м-входом данного объекта.
    PipeTrackNode * basePrevNodeP;
    
    /// Указатель на второй предшествующий узел трассы или nullptr. Под вторым предшествующим узлом понимается узел, соединенный с вторым м-входом данного объекта (используется для типов "тройник", "крестовина").
    PipeTrackNode * secondPrevNodeP;
    
    /// Указатель на третий предшествующий узел трассы или nullptr. Под третьим предшествующим узлом понимается узел, соединенный с третьим м-входом данного объекта (используется для типа "крестовина").
    PipeTrackNode * thirdPrevNodeP;
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param type Тип объекта системы водоотведения.
    /// \param pipeObjectP Указатель на объект системы водоотведения.
    /// \param centerPoint Центр объекта (для типов "отвод", "тройник", "крестовина"; единица измерения - мм.). Под центром объекта понимается точка пересечения осей труб.
    /// \param startPoint Начало объекта (для типов "прямая труба", "фановая труба", "редукция"; единица измерения - мм.). Под началом объекта понимается центр его м-входа.
    /// \param endPoint Конец объекта (для типов "прямая труба", "фановая труба", "редукция"; единица измерения - мм.). Под концом объекта понимается центр м-входа соединенного с его п-выходом объекта.
    /// \param baseDirection Основное направление объекта (для типов "отвод", "тройник", "крестовина"). Вектор, задающий направление от центра объекта в сторону центра его п-выхода.
    /// \param secondDirection Второе направление объекта (для типов "отвод", "тройник", "крестовина"). Вектор, задающий направление второго м-входа объекта (или просто м-входа для типа "отвод") от центра данного м-входа в сторону центра объекта.Второе направление объекта (для типов "отвод", "тройник", "крестовина"). Вектор, задающий направление второго м-входа объекта (или просто м-входа для типа "отвод") от центра данного м-входа в сторону центра объекта.
    /// \param thirdDirection Третье направление объекта (для типа "крестовина"). Вектор, задающий направление третьего м-входа объекта от центра данного м-входа в сторону центра объекта.
    explicit PipeTrackNode(PipeObjectType type, const PipeObject * pipeObjectP, const Point & centerPoint, const Point & startPoint, const Point & endPoint, const Point & baseDirection, const Point & secondDirection, const Point & thirdDirection);
    
    // MARK: - Открытые методы
    
    /// Проверить, пересекает ли проекция данного узла на плоскость Oxy прямоугольник данной плоскости. Касание границами пересечением не считается.
    ///
    /// \param left X-координата левой границы прямоугольника (единица измерения - мм.).
    /// \param right X-координата правой границы прямоугольника (единица измерения - мм.).
    /// \param bottom Y-координата нижней границы прямоугольника (единица измерения - мм.).
    /// \param top Y-координата верхней границы прямоугольника (единица измерения - мм.).
    ///
    /// \return true, если пересечение есть, иначе false.
    bool isIntersectedWithRectangle(CalcNumber left, CalcNumber right, CalcNumber bottom, CalcNumber top) const;
    
    /// Вычислить стоимость узла трассы.
    ///
    /// \return Стоимость узла трассы (единица измерения - руб.).
    CalcNumber calculateCost() const;
    
    /// Вычислить точку, принадлежащую отрезку, соединяющему начало и конец объекта (для типов "прямая труба", "фановая труба", "редукция"), ближайшую к точке point. Для типов "отвод", "тройник", "крестовина" возвращается центр объекта. Z-координаты объекта и точки point не учитываются (полагаются равными нулю).
    ///
    /// \param point Точка (единица измерения - мм.).
    ///
    /// \return Вычисленная точка с нулевой Z-координатой (единица измерения - мм.).
    Point calculateNearestCenterPoint2D(const Point & point) const;
    
    // MARK: - Скрытые методы
    
    /// Найти нормаль единичной длины к вектору vector в двумерном пространстве.
    ///
    /// vector Вектор в двумерном пространстве (Z-координата не учитывается). Должен быть ненулевым.
    ///
    /// \return Номальный вектор единичной длины к вектору vector. Z-координата возвращается равной 0.
    Point calculateNormal2D(const Point & vector) const;
    
    /// Проверить, пересекаются ли два прямоугольника в двумерном пространстве. Первый прямоугольник задается концами его главной оси startPoint1 и endPoint1 и шириной width1. Второй прямоугольник содержит параллельные осям Ox и Oy ребра и задается осевыми границами left2, right2, bottom2, top2. Касание границами пересечением не считается.
    ///
    /// \param startPoint1 Первый конец главной оси первого прямоугольника.
    /// \param endPoint1 Второй конец главной оси первого прямоугольника.
    /// \param width1 Ширина первого прямоугольника.
    /// \param left2 X-координата левой границы второго прямоугольника (единица измерения - мм.).
    /// \param right2 X-координата правой границы второго прямоугольника (единица измерения - мм.).
    /// \param bottom2 Y-координата нижней границы второго прямоугольника (единица измерения - мм.).
    /// \param top2 Y-координата верхней границы второго прямоугольника (единица измерения - мм.).
    ///
    /// \return true, если пересечение есть, иначе false.
    bool rectanglesAreIntersected(const Point & startPoint1, const Point & endPoint1, CalcNumber width1, CalcNumber left2, CalcNumber right2, CalcNumber bottom2, CalcNumber top2) const;
    
};

// MARK: - Реализация

/// Конструктор.
///
/// \param type Тип объекта системы водоотведения.
/// \param pipeObjectP Указатель на объект системы водоотведения.
/// \param centerPoint Центр объекта (для типов "отвод", "тройник", "крестовина"; единица измерения - мм.). Под центром объекта понимается точка пересечения осей труб.
/// \param startPoint Начало объекта (для типов "прямая труба", "фановая труба", "редукция"; единица измерения - мм.). Под началом объекта понимается центр его м-входа.
/// \param endPoint Конец объекта (для типов "прямая труба", "фановая труба", "редукция"; единица измерения - мм.). Под концом объекта понимается центр м-входа соединенного с его п-выходом объекта.
/// \param baseDirection Основное направление объекта (для типов "отвод", "тройник", "крестовина"). Вектор, задающий направление от центра объекта в сторону центра его п-выхода.
/// \param secondDirection Второе направление объекта (для типов "отвод", "тройник", "крестовина"). Вектор, задающий направление второго м-входа объекта (или просто м-входа для типа "отвод") от центра данного м-входа в сторону центра объекта.
/// \param thirdDirection Третье направление объекта (для типа "крестовина"). Вектор, задающий направление третьего м-входа объекта от центра данного м-входа в сторону центра объекта.
PipeTrackNode::PipeTrackNode(PipeObjectType type, const PipeObject * pipeObjectP, const Point & centerPoint, const Point & startPoint, const Point & endPoint, const Point & baseDirection, const Point & secondDirection, const Point & thirdDirection): type(type), pipeObjectP(pipeObjectP), centerPoint(centerPoint), startPoint(startPoint), endPoint(endPoint), nextNodeP(nullptr), basePrevNodeP(nullptr), secondPrevNodeP(nullptr), thirdPrevNodeP(nullptr) {
    
    this->baseDirection = baseDirection/baseDirection.length();
    this->secondDirection = secondDirection/secondDirection.length();
    this->thirdDirection = thirdDirection/thirdDirection.length();
    
}

/// Проверить, пересекает ли проекция данного узла на плоскость Oxy прямоугольник данной плоскости. Касание границами пересечением не считается.
///
/// \param left X-координата левой границы прямоугольника (единица измерения - мм.).
/// \param right X-координата правой границы прямоугольника (единица измерения - мм.).
/// \param bottom Y-координата нижней границы прямоугольника (единица измерения - мм.).
/// \param top Y-координата верхней границы прямоугольника (единица измерения - мм.).
///
/// \return true, если пересечение есть, иначе false.
bool PipeTrackNode::isIntersectedWithRectangle(CalcNumber left, CalcNumber right, CalcNumber bottom, CalcNumber top) const {
    
    unsigned int diameter, externalDiameter, baseDiameter, baseExternalDiameter, extraDiameter, extraExternalDiameter, secondDiameter, secondExternalDiameter, thirdDiameter, thirdExternalDiameter;
    
    switch (type) {
            
        case direct:
        case fan:
        case reduction:
            diameter = (type == direct) ? static_cast<const DirectPipe*>(pipeObjectP)->diameter : (type == fan) ? static_cast<const FanPipe*>(pipeObjectP)->diameter : static_cast<const ReductionPipe*>(pipeObjectP)->fDiameter;
            externalDiameter = pipeObjectP->externalDiameterForDiameterP->find(diameter)->second;
            return rectanglesAreIntersected(startPoint, endPoint, externalDiameter, left, right, bottom, top);
        case angle:
            diameter = static_cast<const AnglePipe*>(pipeObjectP)->diameter();
            externalDiameter = pipeObjectP->externalDiameterForDiameterP->find(diameter)->second;
            return rectanglesAreIntersected(centerPoint, centerPoint + baseDirection * static_cast<const AnglePipe*>(pipeObjectP)->fLength(), externalDiameter, left, right, bottom, top)
            || rectanglesAreIntersected(centerPoint, centerPoint - secondDirection * static_cast<const AnglePipe*>(pipeObjectP)->mLength(), externalDiameter, left, right, bottom, top);
        case tee:
            baseDiameter = static_cast<const TeePipe*>(pipeObjectP)->baseDiameter;
            baseExternalDiameter = pipeObjectP->externalDiameterForDiameterP->find(baseDiameter)->second;
            extraDiameter = static_cast<const TeePipe*>(pipeObjectP)->extraDiameter;
            extraExternalDiameter = pipeObjectP->externalDiameterForDiameterP->find(extraDiameter)->second;
            return rectanglesAreIntersected(centerPoint + baseDirection * static_cast<const TeePipe*>(pipeObjectP)->fLength, centerPoint - baseDirection * static_cast<const TeePipe*>(pipeObjectP)->baseMLength, baseExternalDiameter, left, right, bottom, top)
            || rectanglesAreIntersected(centerPoint, centerPoint - secondDirection * static_cast<const TeePipe*>(pipeObjectP)->extraMLength, extraExternalDiameter, left, right, bottom, top);
        case cross:
            baseDiameter = static_cast<const CrossPipe*>(pipeObjectP)->baseDiameter;
            baseExternalDiameter = pipeObjectP->externalDiameterForDiameterP->find(baseDiameter)->second;
            secondDiameter = static_cast<const CrossPipe*>(pipeObjectP)->secondDiameter;
            secondExternalDiameter = pipeObjectP->externalDiameterForDiameterP->find(secondDiameter)->second;
            thirdDiameter = static_cast<const CrossPipe*>(pipeObjectP)->thirdDiameter;
            thirdExternalDiameter = pipeObjectP->externalDiameterForDiameterP->find(thirdDiameter)->second;
            return rectanglesAreIntersected(centerPoint + baseDirection * static_cast<const CrossPipe*>(pipeObjectP)->fLength, centerPoint - baseDirection * static_cast<const CrossPipe*>(pipeObjectP)->baseMLength, baseExternalDiameter, left, right, bottom, top)
            || rectanglesAreIntersected(centerPoint, centerPoint - secondDirection * static_cast<const CrossPipe*>(pipeObjectP)->secondMLength, secondExternalDiameter, left, right, bottom, top)
            || rectanglesAreIntersected(centerPoint, centerPoint - thirdDirection * static_cast<const CrossPipe*>(pipeObjectP)->thirdMLength, thirdExternalDiameter, left, right, bottom, top);
            
    }
    
    assert(false);
    
}

/// Вычислить точку, принадлежащую отрезку, соединяющему начало и конец объекта (для типов "прямая труба", "фановая труба", "редукция"), ближайшую к точке point. Для типов "отвод", "тройник", "крестовина" возвращается центр объекта. Z-координаты объекта и точки point не учитываются (полагаются равными нулю).
///
/// \param point Точка (единица измерения - мм.).
///
/// \return Вычисленная точка с нулевой Z-координатой (единица измерения - мм.).
Point PipeTrackNode::calculateNearestCenterPoint2D(const Point & point) const {
    
    switch (type) {
            
        case direct:
        case fan:
        case reduction: {
            Point startPoint = Point(this->startPoint.x, this->startPoint.y, 0);
            Point endPoint = Point(this->endPoint.x, this->endPoint.y, 0);
            Line line { startPoint, endPoint };
            // \todo исправить поиск проекции точки на прямую
            Point lineDirection = line.directionVector();
            Point lineProj;
            if (lineDirection.x == 0) {
                lineProj.x = startPoint.x;
                lineProj.y = point.y;
            } else if (lineDirection.y == 0) {
                lineProj.x = point.x;
                lineProj.y = startPoint.y;
            } else {
                CalcNumber ldx = lineDirection.x, ldy = lineDirection.y, ldz = lineDirection.z;
                lineProj = SoLESolver::solveSoLE3x3WithNonZeroDeterminant(
                                    ldy, -ldx, 0, ldy * startPoint.x - ldx * startPoint.y,
                                    0, 0, 1, 0,
                                    ldx, ldy, ldz, lineDirection.scalarProdWith(point)
                );
            }
            //
            //Point lineProj = line.projectionForPoint(Point(point.x, point.y, 0));
            CalcNumber startEndLength = (endPoint - startPoint).length();
            CalcNumber startProjLength = (lineProj - startPoint).length();
            CalcNumber projEndLength = (endPoint - lineProj).length();
            if (std::max(startProjLength, projEndLength) <= startEndLength) {
                return lineProj;
            } else if (std::max(startEndLength, projEndLength) <= startProjLength) {
                return endPoint;
            } else {
                return startPoint;
            }
        }
        case angle:
        case tee:
        case cross:
            return centerPoint;
            
    }
    
    assert(false);
    
}

/// Вычислить стоимость узла трассы.
///
/// \return Стоимость узла трассы (единица измерения - руб.).
CalcNumber PipeTrackNode::calculateCost() const {
    
    switch (type) {
            
        case direct:
        case fan:
            return pipeObjectP->cost * (endPoint - startPoint).length();
        case reduction:
        case angle:
        case tee:
        case cross:
            return pipeObjectP->cost;
            
    }
    
    assert(false);
    
}

/// Найти нормаль единичной длины к вектору vector в двумерном пространстве.
///
/// vector Вектор в двумерном пространстве (Z-координата не учитывается). Должен быть ненулевым.
///
/// \return Номальный вектор единичной длины к вектору vector. Z-координата возвращается равной 0.
Point PipeTrackNode::calculateNormal2D(const Point & vector) const {
    
    CalcNumber x = vector.x, y = vector.y;
    Point resultVector = Point(0, 0, 0);
    
    assert(x != 0 || y != 0);
    
    if (x != 0) {
        resultVector.x = -y/x;
        resultVector.y = 1;
    } else {
        resultVector.x = 1;
        resultVector.y = -x/y;
    }
    
    return resultVector/resultVector.length();
    
}

/// Проверить, пересекаются ли два прямоугольника в двумерном пространстве. Первый прямоугольник задается концами его главной оси startPoint1 и endPoint1 и шириной width1. Второй прямоугольник содержит параллельные осям Ox и Oy ребра и задается осевыми границами left2, right2, bottom2, top2. Касание границами пересечением не считается.
///
/// \param startPoint1 Первый конец главной оси первого прямоугольника.
/// \param endPoint1 Второй конец главной оси первого прямоугольника.
/// \param width1 Ширина первого прямоугольника.
/// \param left2 X-координата левой границы второго прямоугольника (единица измерения - мм.).
/// \param right2 X-координата правой границы второго прямоугольника (единица измерения - мм.).
/// \param bottom2 Y-координата нижней границы второго прямоугольника (единица измерения - мм.).
/// \param top2 Y-координата верхней границы второго прямоугольника (единица измерения - мм.).
///
/// \return true, если пересечение есть, иначе false.
bool PipeTrackNode::rectanglesAreIntersected(const Point & startPoint1, const Point & endPoint1, CalcNumber width1, CalcNumber left2, CalcNumber right2, CalcNumber bottom2, CalcNumber top2) const {
    
    // направляющий вектор главной оси первого прямоугольника
    Point direction = endPoint - startPoint;
    
    // Рассматриваются два случая. Первый случай - ребра первого прямоугольника параллельны осям Ox и Oy. Второй случай - обратный.
    
    if (direction.x == 0 || direction.y == 0) {
        
        // первый случай (у первого прямоугольника прямые ребра)
        
        // Шаг 1. Для первого прямоугольника находятся осевые границы left1, right1, bottom1, top1.
        CalcNumber left1, right1, bottom1, top1;
        if (direction.x == 0) {
            left1 = startPoint.x - width1 / 2;
            right1 = startPoint.x + width1 / 2;
            bottom1 = std::min(startPoint.y, endPoint.y);
            top1 = std::max(startPoint.y, endPoint.y);
        } else {
            left1 = std::min(startPoint.x, endPoint.x);
            right1 = std::max(startPoint.x, endPoint.x);
            bottom1 = startPoint.y - width1 / 2;
            top1 = startPoint.y + width1 / 2;
        }
        
        // Шаг 2. Попытка определить отсутствие пересечения.
        if (left1 >= right2 || right1 <= left2 || bottom1 >= top2 || top1 <= bottom2) {
            return false;
        }
        
        // Шаг 3. Проверяются условия пересечения прямоугольников.
        if (left1 == left2 || right1 == right2) {
            if (bottom1 == bottom2 || top1 == top2) {
                return true;
            }
            if (bottom1 < bottom2) {
                return (top1 > bottom2);
            } else {
                // bottom1 > bottom2
                return (bottom1 < top2);
            }
        } else if (top1 == top2 || bottom1 == bottom2) {
            if (left1 == left2 || right1 == right2) {
                return true;
            }
            if (left1 < left2) {
                return (right1 > left2);
            } else {
                // left1 > left2
                return (left1 < right2);
            }
        } else {
            if (left1 < left2 && left2 < right1 && bottom1 < bottom2 && bottom2 < top1) {
                return true;
            }
            if (left1 < left2 && left2 < right1 && bottom1 < top2 && top2 < top1) {
                return true;
            }
            if (left1 < right2 && right2 < right1 && bottom1 < bottom2 && bottom2 < top1) {
                return true;
            }
            if (left1 < right2 && right2 < right1 && bottom1 < top2 && top2 < top1) {
                return true;
            }
            if (left2 < left1 && left1 < right2 && bottom2 < bottom1 && bottom1 < top2) {
                return true;
            }
            if (left2 < left1 && left1 < right2 && bottom2 < top1 && top1 < top2) {
                return true;
            }
            if (left2 < right1 && right1 < right2 && bottom2 < bottom1 && bottom1 < top2) {
                return true;
            }
            if (left2 < right1 && right1 < right2 && bottom2 < top1 && top1 < top2) {
                return true;
            }
            return false;
        }
        
    } else {
        
        // второй случай (у первого прямоугольника косые ребра)
        
        // Для этого случая прямоугольники пересекаются тогда и только тогда, когда пересекается (не касается) некоторая пара ребер этих прямоугольников.
        
        // Шаг 1. Попытка определить отсутствие пересечения.
        CalcNumber left1WithReserve = std::min(startPoint1.x, endPoint1.x) - width1;
        CalcNumber right1WithReserve = std::max(startPoint1.x, endPoint1.x) + width1;
        CalcNumber bottom1WithReserve = std::min(startPoint1.y, endPoint1.y) - width1;
        CalcNumber top1WithReserve = std::max(startPoint1.y, endPoint1.y) + width1;
        if (left1WithReserve >= right2 || right1WithReserve <= left2 || bottom1WithReserve >= top2 || top1WithReserve <= bottom2) {
            return false;
        }
        
        // Шаг 2. Для каждой пары ребер проверяется, пересекаются ли они.
        Point direction1 = endPoint1 - startPoint1;
        Point normal1 = calculateNormal2D(direction1) * (CalcNumber(width1) / 2);
        std::vector<std::pair<Point, Point>> edges1 = {
            std::pair(startPoint1 + normal1, startPoint1 - normal1),
            std::pair(endPoint1 + normal1, endPoint1 - normal1),
            std::pair(startPoint1 + normal1, endPoint1 + normal1),
            std::pair(startPoint1 - normal1, endPoint1 - normal1)
        };
        std::vector<std::pair<Point, Point>> edges2 = {
            std::pair(Point(left2, bottom2, 0), Point(left2, top2, 0)),
            std::pair(Point(right2, bottom2, 0), Point(right2, top2, 0)),
            std::pair(Point(left2, bottom2, 0), Point(right2, bottom2, 0)),
            std::pair(Point(left2, top2, 0), Point(right2, top2, 0))
        };
        for (const std::pair<Point, Point> & edge1 : edges1) {
            for (const std::pair<Point, Point> & edge2 : edges2) {
                // проверка пересечения ребер edge1 и edge2
                CalcNumber a11 = edge1.first.x - edge1.second.x;
                CalcNumber a12 = edge2.second.x - edge2.first.x;
                CalcNumber a21 = edge1.first.y - edge1.second.y;
                CalcNumber a22 = edge2.second.y - edge2.first.y;
                CalcNumber b1 = edge2.second.x - edge1.second.x;
                CalcNumber b2 = edge2.second.y - edge1.second.y;
                CalcNumber betta = (a11 * a22 - a21 * a12) / (a11 * b2 - a21 * b1);
                CalcNumber alfa = (b1 - a12 * betta) / a11;
                if (0 <= alfa && alfa <= 1 && 0 <= betta && betta <= 1) {
                    // касание ребер есть
                    // возможны выожденные случаи, когда метод вернет true в случае касания прямоугольников границами, что не соответствует описанию метода
                    // \todo исправить данный недочет
                    return true;
                }
            }
        }
        return false;
        
    }
    
}

#endif /* PipeTrackNode_hpp */
