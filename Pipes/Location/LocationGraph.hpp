#ifndef LocationGraph_hpp
#define LocationGraph_hpp

// Подключение стандартных библиотек
#include <vector>
#include <map>
#include <set>
#include <algorithm>

// Подключение внутренних типов
#include "LocationGraphNode.hpp"
#include "WaterConnectionObjects.hpp"
#include "PipeObjectsBag.hpp"
#include "OptimizationParameters.hpp"

/// Граф локации, состоящий из узлов и ребер. Каждый узел графа представляет прямоугольную область, в которой могут проходить трубы трассы системы водоотведения. Ребра соединяют граничащие узлы. Узлы могут пересекаться только границами.
struct LocationGraph {
    
    // MARK: - Вспомогательные типы
    
    /// Результат поиска точки, принадлежащей локации.
    struct FindPointResult {
        
        /// Найденная точка (единица измерения - мм.).
        Point point;
        
        /// Узел, содержащий точку.
        LocationGraphNode * nodeP;
        
    };
    
private:
    
    // MARK: - Скрытые объекты
    
    /// Последний сгенерированный уникальный идентификатор узла.
    unsigned int lastGeneratedId = 0;
    
public:
    
    // MARK: - Открытые объекты
    
    /// Указатель на хранилище, содержащее доступные к использованию объекты системы водоотведения.
    const PipeObjectsBag * pipeObjectsBagP;
    
    /// Указатель на параметры алгоритма оптимизации.
    const OptimizationParameters * optimizationParametersP;
    
    /// Указатели на узлы графа.
    std::vector<LocationGraphNode*> nodePs;
    
    /// Указатели на узлы по идентификатору.
    std::map<unsigned int, LocationGraphNode*> nodePForId;
    
    /// Указатель на узел графа локации, содержащий сток.
    const LocationGraphNode * waterDestinationNodeP;
    
    // MARK: - Конструкторы
    
    /// Конструктор. Создается пустой граф.
    ///
    /// \param pipeObjectsBagP Указатель на хранилище, содержащее доступные к использованию объекты системы водоотведения.
    /// \param optimizationParametersP Указатель на параметры алгоритма оптимизации.
    explicit LocationGraph(const PipeObjectsBag * pipeObjectsBagP, const OptimizationParameters * optimizationParametersP);
    
    /// Конструктор копирования.
    ///
    /// \param anotherLocationGraph Копируемый граф локации.
    LocationGraph(const LocationGraph & anotherLocationGraph);
    
    /// Деструктор.
    ~LocationGraph();
    
    // MARK: - Открытые методы
    
    /// Очистить граф локации. При очищении удаляются существующие узлы.
    void clear();
    
    /// Оператор копирования.
    ///
    /// \param anotherLocationGraph Копируемый граф локации.
    LocationGraph & operator=(const LocationGraph & anotherLocationGraph);
    
    /// Сгенерировать уникальный идентификатор узла.
    ///
    /// \return Уникальный идентификатор узла.
    unsigned int generateNewNodeId();
    
    /// Добавить новый узел в граф локации. Метод бросает Exception-исключение, если координаты узла некорректны или добавляемый узел имеет пересечение положительной площади с существующим узлом графа.
    ///
    /// \param left X-координата левого края узла (единица измерения - мм.).
    /// \param right X-координата правого края узла (единица измерения - мм.).
    /// \param bottom Y-координата нижнего края узла (единица измерения - мм.).
    /// \param top Y-координата верхнего края узла(единица измерения - мм.).
    ///
    /// \return Уникальный идентификатор нового узла.
    unsigned int addNodeAndReturnId(CalcNumber left, CalcNumber right, CalcNumber bottom, CalcNumber top);
    
    /// Загрузить граф локации из файла. Метод бросает Exception-исключение в случае некорректных данных.
    ///
    /// \param fileName Имя файла в формате CSV, в котором хранится локация в виде прямоугольных областей, в которой могут проходить трубы трассы системы водоотведения. Области не должны пересекаться.
    void loadFromFile(const std::string & fileName);
    
    /// Соединить два узла связью типа левый-правый. Метод бросает Exception-исключение, если узлов с данными идентификаторами нет в графе или узлы не обладают данной связью или если данная связь уже зафиксирована.
    ///
    /// \param leftNodeId Идентификатор левого узла.
    /// \param rightNodeId Идентификатор правого узла.
    void connectLeftAndRightNodes(unsigned int leftNodeId, unsigned int rightNodeId);
    
    /// Соединить два узла связью типа нижний-верхний. Метод бросает Exception-исключение, если узлов с данными идентификаторами нет в графе или узлы не обладают данной связью или если данная связь уже зафиксирована.
    ///
    /// \param bottomNodeId Идентификатор нижнего узла.
    /// \param topNodeId Идентификатор верхнего узла.
    void connectBottomAndTopNodes(unsigned int bottomNodeId, unsigned int topNodeId);
    
    /// Соединить все имеющиеся в графе узлы связями. Связи находятся автоматически. При вызове метода связи в узлах не должны быть установлены. Метод бросает Exception-исключение, если при вызове метода некоторые связи уже установлены в графе локации.
    void connectAllNodes();
    
    /// Найти ближайшую к точке point точку, принадлежащую локации.
    ///
    /// \param point Исходная точка (единица измерения - мм.).
    ///
    /// \return Ближайшая к точке point точка, принадлежащая локации (единица измерения - мм.).
    FindPointResult findClosestPoint(const Point & point);
    
    /// Добавить в граф локации объекты подключения воды. Метод бросает Exception-исключение, если среди объектов подключения отсутствуют источники или сток или если сток не принадлежит полностью (с учетом внешнего диаметра) некоторому узлу локации.
    ///
    /// \param waterConnectionObjects Объекты подключения воды.
    void addWaterConnectionObjects(const WaterConnectionObjects & waterConnectionObjects);
    
    /// Разделить узлы, содержащие точки входа нескольких источников. Узел, содержащий несколько точек входа, разделяется при условии, что 1) разделяющее узел сечение проходит посередине между разделяемыми точками входа, 2) расстояние между разделяемыми точками входа не меньше параметра minSourceDistanceToSeparate, 3) ширина сечения не превосходит параметр maxNodeWidthToSeparate, 4) образуемое сечение не пересекает точки входа источников в узел, 5) образуемое сечение не пересекает сток (с учетом его внешнего диаметра), 6) между разделяемыми точками входа нет других точек входа.
    void separateWaterSources();
    
    /// Найти для каждого узла списка узлов, ведущих в сторону стока, а также минимального расстояния до стока для каждого возможного пути.
    void findPathsDoDestination();
    
private:
    
    // MARK: - Скрытые методы
    
    /// Разделить узел node на два вдоль прямой x = separationX.
    ///
    /// \param node Разделяемый узел.
    /// \param separationX X-координата сечения (единица измерения - мм.).
    void separateNodeX(LocationGraphNode & node, CalcNumber separationX);
    
    /// Разделить узел node на два вдоль прямой y = separationY.
    ///
    /// \param node Разделяемый узел.
    /// \param separationY Y-координата сечения (единица измерения - мм.).
    void separateNodeY(LocationGraphNode & node, CalcNumber separationY);
    
    /// Пересчитать указатель на узел графа локации, содержащий сток.
    void recalculateWaterDestinationNodeP();
    
};

// MARK: - Реализация

/// Конструктор. Создается пустой граф.
///
/// \param pipeObjectsBagP Указатель на хранилище, содержащее доступные к использованию объекты системы водоотведения.
/// \param optimizationParametersP Указатель на параметры алгоритма оптимизации.
LocationGraph::LocationGraph(const PipeObjectsBag * pipeObjectsBagP, const OptimizationParameters * optimizationParametersP): pipeObjectsBagP(pipeObjectsBagP), optimizationParametersP(optimizationParametersP), waterDestinationNodeP(nullptr) {}
    
/// Конструктор копирования.
///
/// \param anotherLocationGraph Копируемый граф локации.
LocationGraph::LocationGraph(const LocationGraph & anotherLocationGraph) {
    
    *this = anotherLocationGraph;
    
}

/// Оператор копирования.
///
/// \param anotherLocationGraph Копируемый граф локации.
LocationGraph & LocationGraph::operator=(const LocationGraph & anotherLocationGraph) {
    
    lastGeneratedId = anotherLocationGraph.lastGeneratedId;
    pipeObjectsBagP = anotherLocationGraph.pipeObjectsBagP;
    optimizationParametersP = anotherLocationGraph.optimizationParametersP;
    nodePs.clear();
    nodePForId.clear();
    
    for (LocationGraphNode * nodeP : anotherLocationGraph.nodePs) {
        LocationGraphNode * newNodeP = new LocationGraphNode(*nodeP);
        nodePs.push_back(newNodeP);
        nodePForId[nodeP->id] = newNodeP;
    }
    
    for (int i = 0; i < nodePs.size(); i++) {
        const LocationGraphNode * anotherGraphNodeP = anotherLocationGraph.nodePs[i];
        for (int j = 0; j < anotherGraphNodeP->leftNodesPs.size(); j++) {
            nodePs[i]->leftNodesPs[j] = nodePForId[anotherGraphNodeP->leftNodesPs[j]->id];
        }
        for (int j = 0; j < anotherGraphNodeP->rightNodesPs.size(); j++) {
            nodePs[i]->rightNodesPs[j] = nodePForId[anotherGraphNodeP->rightNodesPs[j]->id];
        }
        for (int j = 0; j < anotherGraphNodeP->bottomNodesPs.size(); j++) {
            nodePs[i]->bottomNodesPs[j] = nodePForId[anotherGraphNodeP->bottomNodesPs[j]->id];
        }
        for (int j = 0; j < anotherGraphNodeP->topNodesPs.size(); j++) {
            nodePs[i]->topNodesPs[j] = nodePForId[anotherGraphNodeP->topNodesPs[j]->id];
        }
    }
    waterDestinationNodeP = (anotherLocationGraph.waterDestinationNodeP == nullptr) ? nullptr : nodePForId[anotherLocationGraph.waterDestinationNodeP->id];
    
    return *this;
    
}

/// Деструктор.
LocationGraph::~LocationGraph() {
    
    for (LocationGraphNode * nodeP : nodePs) {
        delete nodeP;
    }
    
}

/// Очистить граф локации. При очищении удаляются существующие узлы.
void LocationGraph::clear() {
    
    for (LocationGraphNode * nodeP : nodePs) {
        delete nodeP;
    }
    
    lastGeneratedId = 0;
    nodePs.clear();
    nodePForId.clear();
    waterDestinationNodeP = nullptr;
    
}

/// Сгенерировать уникальный идентификатор узла.
///
/// \return Уникальный идентификатор узла.
unsigned int LocationGraph::generateNewNodeId() {
    
    return ++lastGeneratedId;
    
}

/// Добавить новый узел в граф локации. Метод бросает Exception-исключение, если если координаты узла некорректны или добавляемый узел имеет пересечение положительной площади с существующим узлом графа.
///
/// \param left X-координата левого края узла (единица измерения - мм.).
/// \param right X-координата правого края узла (единица измерения - мм.).
/// \param bottom Y-координата нижнего края узла (единица измерения - мм.).
/// \param top Y-координата верхнего края узла(единица измерения - мм.).
///
/// \return Уникальный идентификатор нового узла.
unsigned int LocationGraph::addNodeAndReturnId(CalcNumber left, CalcNumber right, CalcNumber bottom, CalcNumber top) {
    
    if ((left < right && bottom < top) == false) {
        throw Exception("Ошибка при добавлении нового узла в граф локации. Добавляемый узел имеет некорректные границы. Добавляемый узел: " + LocationGraphNode(0, left, right, bottom, top).positionStr() + ".");
    }
    
    for (const LocationGraphNode * nodeP: nodePs) {
        if ((left >= nodeP->right || right <= nodeP->left || bottom >= nodeP->top || top <= nodeP->bottom) == false) {
            throw Exception("Ошибка при добавлении нового узла в граф локации. Добавляемый узел имеет пересечение положительной площади с существующим узлом графа. Добавляемый узел: " + LocationGraphNode(0, left, right, bottom, top).positionStr() + "; существующий узел: " + nodeP->positionStr() + ".");
        }
    }
    
    unsigned int newId = generateNewNodeId();
    LocationGraphNode * newNodeP = new LocationGraphNode(newId, left, right, bottom, top);
    nodePs.push_back(newNodeP);
    nodePForId[newId] = newNodeP;
    return newId;
    
}

/// Загрузить граф локации из файла. Метод бросает Exception-исключение в случае некорректных данных.
///
/// \param fileName Имя файла в формате CSV, в котором хранится локация в виде прямоугольных областей, в которой могут проходить трубы трассы системы водоотведения. Области не должны пересекаться.
void LocationGraph::loadFromFile(const std::string & fileName) {
    
    // 1. Удаление существующих узлов локации.

    clear();
    
    // 2. Загрузка узлов локации из файла.
    
    try {
        
        std::ifstream stream(fileName);
        if (stream.fail()) {
            throw Exception("Ошибка при открытии CSV-файла с локацией.");
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
            
            std::string lineErrorMessagePrefix = "Ошибка при чтении CSV-файла с локацией в строке " + std::to_string(lineNumber);
            
            if (line.empty()) {
                lineNumber++;
                continue;
            }
            
            std::istringstream lineStream(line);
            
            std::string readingColumnName, extraStr;
            CalcNumber left, right, bottom, top;
            
            try {
                
                // чтение поля left
                readingColumnName = "Левый край п/у (мм.)";
                extraStr = "";
                std::getline(lineStream, extraStr, delimeter);
                left = std::stoi(extraStr);
                
                // чтение поля right
                readingColumnName = "Правый край п/у (мм.)";
                extraStr = "";
                std::getline(lineStream, extraStr, delimeter);
                right = std::stoi(extraStr);
                
                // чтение поля bottom
                readingColumnName = "Нижний край п/у (мм.)";
                extraStr = "";
                std::getline(lineStream, extraStr, delimeter);
                bottom = std::stoi(extraStr);
                
                // чтение поля top
                readingColumnName = "Верхний край п/у (мм.)";
                extraStr = "";
                std::getline(lineStream, extraStr, delimeter);
                top = std::stoi(extraStr);
                
                // добавление нового узла в граф локации
                addNodeAndReturnId(left, right, bottom, top);
                
            }
            catch (const Exception & exception) {
                throw exception;
            }
            catch (...) {
                throw Exception(lineErrorMessagePrefix + " в поле \"" + readingColumnName + "\". Некорректный формат поля.");
            }
           
            lineNumber++;
            line = "";
            
        }
        
        stream.close();
        
    }
    catch (const Exception & exception) {
        throw exception;
    }
    catch (...) {
        throw Exception("Ошибка при чтении CSV-файла с локацией.");
    }
    
}

/// Соединить два узла связью типа левый-правый. Метод бросает Exception-исключение, если узлов с данными идентификаторами нет в графе или узлы не обладают данной связью или если данная связь уже зафиксирована.
///
/// \param leftNodeId Идентификатор левого узла.
/// \param rightNodeId Идентификатор правого узла.
void LocationGraph::connectLeftAndRightNodes(unsigned int leftNodeId, unsigned int rightNodeId) {
    
    std::string exceptionPrefix = "Ошибка при соединении двух узлов связью типа \"левый-правый\".";// в графе локации с узлами идентификаторов " + std::to_string(leftNodeId) + " и " + std::to_string(rightNodeId) + ".";
    
    if (nodePForId.find(leftNodeId) == nodePForId.end()) {
        throw Exception(exceptionPrefix + " Узел с идентификатором " + std::to_string(leftNodeId) + " отсутствует в графе локации.");
    }
    
    if (nodePForId.find(rightNodeId) == nodePForId.end()) {
        throw Exception(exceptionPrefix + " Узел с идентификатором " + std::to_string(rightNodeId) + " отсутствует в графе локации.");
    }
    
    LocationGraphNode * leftNodeP = nodePForId[leftNodeId];
    LocationGraphNode * rightNodeP = nodePForId[rightNodeId];
    
    exceptionPrefix = "Ошибка при соединении двух узлов связью типа \"левый-правый\".";// в графе локации с узлами идентификаторов " + std::to_string(leftNodeId) + " и " + std::to_string(rightNodeId) + " (" + leftNodeP->positionStr() + " и " + rightNodeP->positionStr() + ").";
    
    if (std::find(leftNodeP->rightNodesPs.begin(), leftNodeP->rightNodesPs.end(), rightNodeP) != leftNodeP->rightNodesPs.end()) {
        throw Exception(exceptionPrefix + " Данная связь уже установлена в графе локации.");
    }
    
    if (std::find(rightNodeP->leftNodesPs.begin(), rightNodeP->leftNodesPs.end(), leftNodeP) != rightNodeP->leftNodesPs.end()) {
        throw Exception(exceptionPrefix + " Данная связь уже установлена в графе локации.");
    }
    
    if (leftNodeP->right != rightNodeP->left || leftNodeP->bottom >= rightNodeP->top || leftNodeP->top <= rightNodeP->bottom) {
        throw Exception(exceptionPrefix + " Узлы не обладают данной связью.");
    }
    
    leftNodeP->rightNodesPs.push_back(rightNodeP);
    rightNodeP->leftNodesPs.push_back(leftNodeP);
    
}

/// Соединить два узла связью типа нижний-верхний. Метод бросает Exception-исключение, если узлов с данными идентификаторами нет в графе или узлы не обладают данной связью или если данная связь уже зафиксирована.
///
/// \param bottomNodeId Идентификатор нижнего узла.
/// \param topNodeId Идентификатор верхнего узла.
void LocationGraph::connectBottomAndTopNodes(unsigned int bottomNodeId, unsigned int topNodeId) {
    
    std::string exceptionPrefix = "Ошибка при соединении двух узлов связью типа \"нижний-верхний\".";// в графе локации с узлами идентификаторов " + std::to_string(bottomNodeId) + " и " + std::to_string(topNodeId) + ".";
    
    if (nodePForId.find(bottomNodeId) == nodePForId.end()) {
        throw Exception(exceptionPrefix + " Узел с идентификатором " + std::to_string(bottomNodeId) + " отсутствует в графе локации.");
    }
    
    if (nodePForId.find(topNodeId) == nodePForId.end()) {
        throw Exception(exceptionPrefix + " Узел с идентификатором " + std::to_string(topNodeId) + " отсутствует в графе локации.");
    }
    
    LocationGraphNode * bottomNodeP = nodePForId[bottomNodeId];
    LocationGraphNode * topNodeP = nodePForId[topNodeId];
    
    exceptionPrefix = "Ошибка при соединении двух узлов связью типа \"нижний-верхний\".";// в графе локации с узлами идентификаторов " + std::to_string(bottomNodeId) + " и " + std::to_string(topNodeId) + " (" + bottomNodeP->positionStr() + " и " + topNodeP->positionStr() + ").";
    
    if (std::find(bottomNodeP->topNodesPs.begin(), bottomNodeP->topNodesPs.end(), topNodeP) != bottomNodeP->topNodesPs.end()) {
        throw Exception(exceptionPrefix + " Данная связь уже установлена в графе локации.");
    }
    
    if (std::find(topNodeP->bottomNodesPs.begin(), topNodeP->bottomNodesPs.end(), bottomNodeP) != topNodeP->bottomNodesPs.end()) {
        throw Exception(exceptionPrefix + " Данная связь уже установлена в графе локации.");
    }
    
    if (bottomNodeP->top != topNodeP->bottom || bottomNodeP->left >= topNodeP->right || bottomNodeP->right <= topNodeP->left) {
        throw Exception(exceptionPrefix + " Узлы не обладают данной связью.");
    }
    
    bottomNodeP->topNodesPs.push_back(topNodeP);
    topNodeP->bottomNodesPs.push_back(bottomNodeP);
    
}

/// Соединить все имеющиеся в графе узлы связями. Связи находятся автоматически. При вызове метода связи в узлах не должны быть установлены. Метод бросает Exception-исключение, если при вызове метода некоторые связи уже установлены в графе локации.
void LocationGraph::connectAllNodes() {
    
    for (int i = 0; i < nodePs.size() - 1; i++) {
        for (int j = i + 1; j < nodePs.size(); j++) {
            if (nodePs[i]->intersectWith(*(nodePs[j]))) {
                LocationGraphNode * node1P = nodePs[i];
                LocationGraphNode * node2P = nodePs[j];
                if (node1P->left == node2P->right) {
                    connectLeftAndRightNodes(node2P->id, node1P->id);
                } else if (node1P->right == node2P->left) {
                    connectLeftAndRightNodes(node1P->id, node2P->id);
                } else if (node1P->bottom == node2P->top) {
                    connectBottomAndTopNodes(node2P->id, node1P->id);
                } else {
                    connectBottomAndTopNodes(node1P->id, node2P->id);
                }
            }
        }
    }
    
}

/// Найти ближайшую к точке point точку, принадлежащую локации.
///
/// \param point Исходная точка (единица измерения - мм.).
///
/// \return Ближайшая к точке point точка, принадлежащая локации (единица измерения - мм.).
LocationGraph::FindPointResult LocationGraph::findClosestPoint(const Point & point) {
    
    FindPointResult result;
    CalcNumber minDistance = 999999999.0;
    
    for (LocationGraphNode * nodeP : nodePs) {
        Point closestPoint = nodeP->findClosestPoint(point);
        CalcNumber distance = closestPoint.distanceToPoint(point);
        if (distance < minDistance) {
            minDistance = distance;
            result.point = closestPoint;
            result.nodeP = nodeP;
        }
    }
    
    return result;
    
}

/// Добавить в граф локации объекты подключения воды. Метод бросает Exception-исключение, если среди объектов подключения отсутствуют источники или сток или если сток не принадлежит полностью (с учетом внешнего диаметра) некоторому узлу локации.
///
/// \param waterConnectionObjects Объекты подключения воды.
void LocationGraph::addWaterConnectionObjects(const WaterConnectionObjects & waterConnectionObjects) {
    
    if (waterConnectionObjects.waterSources.size() == 0) {
        throw Exception("Ошибка при добавлении в граф локации объектов подключения воды. Среди объектов подключения отсутствуют источники.");
    }
    
    if (waterConnectionObjects.waterDestinationIsSet == false) {
        throw Exception("Ошибка при добавлении в граф локации объектов подключения воды. Среди объектов подключеня отсутствует сток.");
    }
    
    for (const WaterSource & waterSource : waterConnectionObjects.waterSources) {
        FindPointResult findPointResult = findClosestPoint(waterSource.point());
        LocationGraphNode * node = findPointResult.nodeP;
        CalcNumber externalDiameterHalfed = pipeObjectsBagP->getExternalDiameter(waterSource.diameter()) / 2;
        Point connectionPoint = findPointResult.point;
        if (connectionPoint.x == node->left) {
            connectionPoint.x += externalDiameterHalfed;
        } else if (connectionPoint.x == node->right) {
            connectionPoint.x -= externalDiameterHalfed;
        }
        if (connectionPoint.y == node->bottom) {
            connectionPoint.y += externalDiameterHalfed;
        } else if (connectionPoint.y == node->top) {
            connectionPoint.y -= externalDiameterHalfed;
        }
        node->waterSourcesPs.push_back(&waterSource);
        node->waterSourcesConnectionPoints.push_back(connectionPoint);
    }
    
    const WaterDestination * waterDestinationP = &(waterConnectionObjects.waterDestination);
    const Point waterDestinationPoint = waterDestinationP->point();
    FindPointResult findPointResult = findClosestPoint(waterDestinationPoint);
    LocationGraphNode * nodeP = findPointResult.nodeP;
    nodeP->waterDestinationP = waterDestinationP;
    waterDestinationNodeP = nodeP;
    CalcNumber waterDestinationExternalRadius = pipeObjectsBagP->getExternalDiameter(waterDestinationP->diameter()) / 2;
    if (nodeP->contains(LocationGraphNode(0,
        waterDestinationPoint.x - waterDestinationExternalRadius,
        waterDestinationPoint.x + waterDestinationExternalRadius,
        waterDestinationPoint.y - waterDestinationExternalRadius,
        waterDestinationPoint.y + waterDestinationExternalRadius
    )) == false) {
        throw Exception("Ошибка при добавлении в граф локации объектов подключения воды. Для подключаемого стока не существует узла графа локации, полностью его содержащего.");
    }
    
}

/// Разделить узлы, содержащие точки входа нескольких источников. Узел, содержащий несколько точек входа, разделяется при условии, что 1) разделяющее узел сечение проходит посередине между разделяемыми точками входа, 2) расстояние между разделяемыми точками входа не меньше параметра minSourceDistanceToSeparate, 3) ширина сечения не превосходит параметр maxNodeWidthToSeparate, 4) образуемое сечение не пересекает точки входа источников в узел, 5) образуемое сечение не пересекает сток (с учетом его внешнего диаметра), 6) между разделяемыми точками входа нет других точек входа.
void LocationGraph::separateWaterSources() {
    
    bool successSeparation = true;
    
    while (successSeparation) {
        
        successSeparation = false;
        
        for (LocationGraphNode * nodeP : nodePs) {
            
            if (nodeP->waterSourcesPs.size() > 1) {
                
                std::set<CalcNumber> xsSet, ysSet;
                for (const Point & connectionPoint : nodeP->waterSourcesConnectionPoints) {
                    xsSet.insert(connectionPoint.x);
                    ysSet.insert(connectionPoint.y);
                }
                
                std::vector<CalcNumber> xsArr, ysArr;
                std::copy(xsSet.begin(), xsSet.end(), std::back_inserter(xsArr));
                std::copy(ysSet.begin(), ysSet.end(), std::back_inserter(ysArr));
                std::sort(xsArr.begin(), xsArr.end());
                std::sort(ysArr.begin(), ysArr.end());
                
                // проверка возможности разделения вдоль прямой x = ...
                if (xsArr.size() > 1 && nodeP->sizeY() <= optimizationParametersP->maxNodeWidthToSeparate) {
                    bool needToSeparate = false;
                    CalcNumber separationX = 0;
                    for (int i = 1; i < xsArr.size(); i++) {
                        if (xsArr[i] - xsArr[i-1] >= optimizationParametersP->minSourceDistanceToSeparate) {
                            separationX = (xsArr[i-1] + xsArr[i]) / 2;
                            if (nodeP->waterDestinationP == nullptr) {
                                needToSeparate = true;
                                break;
                            } else {
                                const WaterDestination * waterDestinationP = nodeP->waterDestinationP;
                                Point waterDestinationPoint = waterDestinationP->point();
                                CalcNumber waterDestinationExternalRadius = pipeObjectsBagP->getExternalDiameter(waterDestinationP->diameter()) / 2;
                                if (separationX < waterDestinationPoint.x - waterDestinationExternalRadius || separationX > waterDestinationPoint.x + waterDestinationExternalRadius) {
                                    needToSeparate = true;
                                    break;
                                }
                            }
                        }
                    }
                    if (needToSeparate) {
                        separateNodeX(*nodeP, separationX);
                        successSeparation = true;
                        break;
                    }
                }
                
                // проверка возможности разделения вдоль прямой y = ...
                if (ysArr.size() > 1 && nodeP->sizeX() <= optimizationParametersP->maxNodeWidthToSeparate) {
                    bool needToSeparate = false;
                    CalcNumber separationY = 0;
                    for (int i = 1; i < ysArr.size(); i++) {
                        if (ysArr[i] - ysArr[i-1] >= optimizationParametersP->minSourceDistanceToSeparate) {
                            separationY = (ysArr[i-1] + ysArr[i]) / 2;
                            if (nodeP->waterDestinationP == nullptr) {
                                needToSeparate = true;
                                break;
                            } else {
                                const WaterDestination * waterDestinationP = nodeP->waterDestinationP;
                                Point waterDestinationPoint = waterDestinationP->point();
                                CalcNumber waterDestinationExternalRadius = pipeObjectsBagP->getExternalDiameter(waterDestinationP->diameter()) / 2;
                                if (separationY < waterDestinationPoint.y - waterDestinationExternalRadius || separationY > waterDestinationPoint.y + waterDestinationExternalRadius) {
                                    needToSeparate = true;
                                    break;
                                }
                            }
                        }
                    }
                    if (needToSeparate) {
                        separateNodeY(*nodeP, separationY);
                        successSeparation = true;
                        break;
                    }
                }
                
            }
            
        }
        
    }
    
    recalculateWaterDestinationNodeP();
    
}

/// Разделить узел node на два вдоль прямой x = separationX.
///
/// \param node Разделяемый узел.
/// \param separationX X-координата сечения (единица измерения - мм.).
void LocationGraph::separateNodeX(LocationGraphNode & node, CalcNumber separationX) {
    
    // создается новый узел (правый)
    unsigned int newId = generateNewNodeId();
    LocationGraphNode * newNodeP = new LocationGraphNode(newId, separationX, node.right, node.bottom, node.top);
    nodePs.push_back(newNodeP);
    nodePForId[newId] = newNodeP;
    newNodeP->leftNodesPs.push_back(&node);
    newNodeP->rightNodesPs = node.rightNodesPs;
    for (LocationGraphNode * rightNodeP : node.rightNodesPs) {
        auto iter = std::find(rightNodeP->leftNodesPs.begin(), rightNodeP->leftNodesPs.end(), &node);
        *iter = newNodeP;
    }
    for (LocationGraphNode * bottomNodeP : node.bottomNodesPs) {
        if (bottomNodeP->right > separationX) {
            newNodeP->bottomNodesPs.push_back(bottomNodeP);
            auto iter = std::find(bottomNodeP->topNodesPs.begin(), bottomNodeP->topNodesPs.end(), &node);
            *iter = newNodeP;
        }
    }
    for (LocationGraphNode * topNodeP : node.topNodesPs) {
        if (topNodeP->right > separationX) {
            newNodeP->topNodesPs.push_back(topNodeP);
            auto iter = std::find(topNodeP->bottomNodesPs.begin(), topNodeP->bottomNodesPs.end(), &node);
            *iter = newNodeP;
        }
    }
    for (int i = 0; i < node.waterSourcesPs.size(); i++) {
        if (node.waterSourcesConnectionPoints[i].x > separationX) {
            newNodeP->waterSourcesPs.push_back(node.waterSourcesPs[i]);
            newNodeP->waterSourcesConnectionPoints.push_back(node.waterSourcesConnectionPoints[i]);
        }
    }
    if (node.waterDestinationP != nullptr && node.waterDestinationP->point().x > separationX) {
        newNodeP->waterDestinationP = node.waterDestinationP;
    }
    
    // корректируется имеющийся узел (левый)
    node.right = separationX;
    node.rightNodesPs.clear();
    node.rightNodesPs.push_back(newNodeP);
    for (int i = static_cast<int>(node.bottomNodesPs.size()) - 1; i >= 0; i--) {
        if (node.bottomNodesPs[i]->left > separationX) {
            node.bottomNodesPs.erase(node.bottomNodesPs.begin() + i);
        }
    }
    for (int i = static_cast<int>(node.topNodesPs.size()) - 1; i >= 0; i--) {
        if (node.topNodesPs[i]->left > separationX) {
            node.topNodesPs.erase(node.topNodesPs.begin() + i);
        }
    }
    for (int i = static_cast<int>(node.waterSourcesPs.size()) - 1; i >= 0 ; i--) {
        if (node.waterSourcesConnectionPoints[i].x > separationX) {
            node.waterSourcesPs.erase(node.waterSourcesPs.begin() + i);
            node.waterSourcesConnectionPoints.erase(node.waterSourcesConnectionPoints.begin() + i);
        }
    }
    if (node.waterDestinationP != nullptr && node.waterDestinationP->point().x > separationX) {
        node.waterDestinationP = nullptr;
    }
    
}

/// Разделить узел node на два вдоль прямой y = separationY.
///
/// \param node Разделяемый узел.
/// \param separationY Y-координата сечения (единица измерения - мм.).
void LocationGraph::separateNodeY(LocationGraphNode & node, CalcNumber separationY) {
    
    // создается новый узел (верхний)
    unsigned int newId = generateNewNodeId();
    LocationGraphNode * newNodeP = new LocationGraphNode(newId, node.left, node.right, separationY, node.top);
    nodePs.push_back(newNodeP);
    nodePForId[newId] = newNodeP;
    for (LocationGraphNode * leftNodeP : node.leftNodesPs) {
        if (leftNodeP->top > separationY) {
            newNodeP->leftNodesPs.push_back(leftNodeP);
            auto iter = std::find(leftNodeP->rightNodesPs.begin(), leftNodeP->rightNodesPs.end(), &node);
            *iter = newNodeP;
        }
    }
    for (LocationGraphNode * rightNodeP : node.rightNodesPs) {
        if (rightNodeP->top > separationY) {
            newNodeP->rightNodesPs.push_back(rightNodeP);
            auto iter = std::find(rightNodeP->leftNodesPs.begin(), rightNodeP->leftNodesPs.end(), &node);
            *iter = newNodeP;
        }
    }
    newNodeP->bottomNodesPs.push_back(&node);
    newNodeP->topNodesPs = node.topNodesPs;
    for (LocationGraphNode * topNodeP : node.topNodesPs) {
        auto iter = std::find(topNodeP->bottomNodesPs.begin(), topNodeP->bottomNodesPs.end(), &node);
        *iter = newNodeP;
    }
    for (int i = 0; i < node.waterSourcesPs.size(); i++) {
        if (node.waterSourcesConnectionPoints[i].y > separationY) {
            newNodeP->waterSourcesPs.push_back(node.waterSourcesPs[i]);
            newNodeP->waterSourcesConnectionPoints.push_back(node.waterSourcesConnectionPoints[i]);
        }
    }
    if (node.waterDestinationP != nullptr && node.waterDestinationP->point().y > separationY) {
        newNodeP->waterDestinationP = node.waterDestinationP;
    }
    
    // корректируется имеющийся узел (нижний)
    node.top = separationY;
    for (int i = static_cast<int>(node.leftNodesPs.size()) - 1; i >= 0; i--) {
        if (node.leftNodesPs[i]->bottom > separationY) {
            node.leftNodesPs.erase(node.leftNodesPs.begin() + i);
        }
    }
    for (int i = static_cast<int>(node.rightNodesPs.size()) - 1; i >= 0; i--) {
        if (node.rightNodesPs[i]->bottom > separationY) {
            node.rightNodesPs.erase(node.rightNodesPs.begin() + i);
        }
    }
    node.topNodesPs.clear();
    node.topNodesPs.push_back(newNodeP);
    for (int i = static_cast<int>(node.waterSourcesPs.size()) - 1; i >= 0 ; i--) {
        if (node.waterSourcesConnectionPoints[i].y > separationY) {
            node.waterSourcesPs.erase(node.waterSourcesPs.begin() + i);
            node.waterSourcesConnectionPoints.erase(node.waterSourcesConnectionPoints.begin() + i);
        }
    }
    if (node.waterDestinationP != nullptr && node.waterDestinationP->point().y > separationY) {
        node.waterDestinationP = nullptr;
    }
    
}

/// Пересчитать указатель на узел графа локации, содержащий сток.
void LocationGraph::recalculateWaterDestinationNodeP() {
    
    for (const LocationGraphNode * locationNodeP : nodePs) {
        if (locationNodeP->waterDestinationP != nullptr) {
            waterDestinationNodeP = locationNodeP;
        }
    }
    
}

#endif /* LocationGraph_hpp */
