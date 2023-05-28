#ifndef OptimalPipeTrackFinder_hpp
#define OptimalPipeTrackFinder_hpp

// Подключение стандартных библиотек
#include <vector>
#include <map>
#include <set>

// Подключение внутренних типов
#include "Exception.hpp"
#include "Config.hpp"
#include "WaterConnectionObjects.hpp"
#include "PipeObjectsBag.hpp"
#include "OptimizationParameters.hpp"
#include "View.hpp"
#include "DecisionMaker.hpp"
#include "LocationGraph.hpp"
#include "PipeTrack.hpp"

/// Вычислитель оптимальной трассы системы водоотведения.
class OptimalPipeTrackFinder {
    
    // MARK: - Скрытые объекты
    
    /// Параметры модели.
    const Config & config;
    
    /// Объекты подключения воды.
    const WaterConnectionObjects & waterConnectionObjects;
    
    /// Хранилище, содержащее доступные к использованию объекты системы водоотведения.
    const PipeObjectsBag & pipeObjectsBag;
    
    /// Граф локации, описывающий области, по которым могут проходить трубы трассы системы водоотведения.
    LocationGraph locationGraph;
    
    /// Параметры алгоритма оптимизации.
    const OptimizationParameters & optimizationParameters;
    
    /// Объект, отвечающий за вывод сообщений и ошибок.
    View & view;
    
    /// Объект, отвечающий за принятие неоднозначных решений при нахождении оптимальной трассы системы водоотведения.
    DecisionMaker & decisionMaker;
    
public:
    
    // MARK: - Конструкторы
    
    /// Конструктор.
    ///
    /// \param config Параметры модели.
    /// \param waterConnectionObjects Объекты подключения воды.
    /// \param pipeObjectsBag Хранилище, содержащее доступные к использованию объекты системы водоотведения.
    /// \param locationGraph Граф локации, описывающий области, по которым могут проходить трубы трассы системы водоотведения.
    /// \param optimizationParameters Параметры алгоритма оптимизации.
    /// \param view Объект, отвечающий за вывод сообщений и ошибок.
    /// \param decisionMaker Объект, отвечающий за принятие неоднозначных решений при нахождении оптимальной трассы системы водоотведения.
    explicit OptimalPipeTrackFinder(const Config & config, const WaterConnectionObjects & waterConnectionObjects, const PipeObjectsBag & pipeObjectsBag, LocationGraph locationGraph, const OptimizationParameters & optimizationParameters, View & view, DecisionMaker & decisionMaker);
    
    // MARK: - Открытые методы
    
    /// Вычислить оптимальную трассу системы водоотведения. Метод может бросать Exception-исключение.
    ///
    /// \returns Найденная оптимальная трасса системы водоотведения.
    PipeTrack calculateOptimalPipeTrack();
    
private:
    
    // MARK: - Скрытые методы
    
    /// Подключить к имеющейся трассе pipeTrack источник waterSource. Если трасса пустая, то источник добавляется к стоку. Метод может бросать Exception-исключение.
    ///
    /// \param pipeTrack Текущая трасса.
    /// \param waterSource Подключаемой к трассе источник.
    void connectSourceToPipeTrack(PipeTrack & pipeTrack, const WaterSource & waterSource);
    
    /// Достроить текущий строящийся путь в графе локации до трассы. Если путь не однозначен, построить всевозможные варианты. Если трасса пустая, путь строится до стока.
    ///
    /// \param builtPaths Массив уже построенных путей. В данный массив сохраняются достроенные пути.
    /// \param buildingPath Текущий строящийся путь. Последний элемент данного массива - последний пройденный узел, от которого необходимо продолжить строительство. Массив должен быть непустым.
    /// \param passedNodes Множество уже пройденных узлов в текущем пути.
    /// \param pipeTrackNodesForLocationNode Словарь, в котором для каждого узла графа локации содержится массив содержащихся в нем узлов трассы.
    void findAllPathsFromSourceToPipeTrack(std::vector<std::vector<const LocationGraphNode*>> & builtPaths, std::vector<const LocationGraphNode*> & buildingPath, std::set<const LocationGraphNode*> & passedNodes, std::map<const LocationGraphNode*, std::vector<const PipeTrackNode*>> & pipeTrackNodesForLocationNode);
    
    /// Найти для пути pathFromSourceToPipeTrack ломаную минимальной псевдодлины, соединяющую точку входа подключаемого источника waterSource с трассой pipeTrack. При поиске учитывается внешний диаметр источника. Если трасса пустая, то источник соединяется со стоком.
    ///
    /// \param pathFromSourceToPipeTrack Путь от источника до трассы в виде узлов графа локации.
    /// \param pipeTrack Трасса системы водоотведения.
    /// \param waterSource Подключаемый источник.
    /// \param pipeTrackNodesForLocationNode Словарь, в котором для каждого узла графа локации содержится массив содержащихся в нем узлов трассы.
    ///
    /// \return Пара типа (ломаная, указатель на соединяемый узел трассы). Ломаная - ломаная минимальной псевдодлины, проходящая через узлы пути pathFromSourceToPipeTrack, соединяющая источник waterSource с трассой pipeTrack. Если последней точкой ломаной является центр стока, то указатель на соединяемый узел трассы равен nullptr. Если поиск неуспешен, возвращается пустая ломаная.
    std::pair<std::vector<Point>, const PipeTrackNode*> findMinPseudoLengthZigzagFromSourceToPipeTrackAndPipeTrackNodeP(const std::vector<const LocationGraphNode*> & pathFromSourceToPipeTrack, const PipeTrack & pipeTrack, const WaterSource & waterSource, std::map<const LocationGraphNode*, std::vector<const PipeTrackNode*>> & pipeTrackNodesForLocationNode);
    
};

// MARK: - Реализация

/// Конструктор.
///
/// \param config Параметры модели.
/// \param waterConnectionObjects Объекты подключения воды.
/// \param pipeObjectsBag Хранилище, содержащее доступные к использованию объекты системы водоотведения.
/// \param locationGraph Граф локации, описывающий области, по которым могут проходить трубы трассы системы водоотведения.
/// \param optimizationParameters Параметры алгоритма оптимизации.
/// \param view Объект, отвечающий за вывод сообщений и ошибок.
/// \param decisionMaker Объект, отвечающий за принятие неоднозначных решений при нахождении оптимальной трассы системы водоотведения.
OptimalPipeTrackFinder::OptimalPipeTrackFinder(const Config & config, const WaterConnectionObjects & waterConnectionObjects, const PipeObjectsBag & pipeObjectsBag, LocationGraph locationGraph, const OptimizationParameters & optimizationParameters, View & view, DecisionMaker & decisionMaker): config(config), waterConnectionObjects(waterConnectionObjects), pipeObjectsBag(pipeObjectsBag), locationGraph(locationGraph), optimizationParameters(optimizationParameters), view(view), decisionMaker(decisionMaker) {}
    
/// Вычислить оптимальную трассу системы водоотведения. Метод может бросать Exception-исключение.
///
/// \returns Найденная оптимальная трасса системы водоотведения.
PipeTrack OptimalPipeTrackFinder::calculateOptimalPipeTrack() {
    
    view.printMessage("\nЗапуск алгоритма вычисления оптимальной трассы системы водоотведения.");
    
    // Шаг 1. Добавление в граф локации объектов подключения воды.
    view.printMessage("\nШаг 1. Добавление в граф локации объектов подключения воды.");
    locationGraph.addWaterConnectionObjects(waterConnectionObjects);
    view.printMessage("Шаг 1 завершен.");
    
    // Шаг 2. Разделение узлов графа локации, содержащих точки входа нескольких источников.
    view.printMessage("\nШаг 2. Разделение узлов графа локации, содержащих точки входа нескольких источников.");
    locationGraph.separateWaterSources();
    view.printMessage("Шаг 2 завершен.");
    
    // Шаг 3. Построение оптимальной трассы, в ходе которого источники последовательно подключаются к стоку в порядке уменьшения их диаметров.
    view.printMessage("\nШаг 3. Построение оптимальной трассы, в ходе которого источники последовательно подключаются к стоку в порядке уменьшения их диаметров.");
    PipeTrack pipeTrack { &view };
    for (const WaterSource & waterSource : waterConnectionObjects.waterSources) {
        view.printMessage("Подключение источника \"" + waterSource.name() + "\".");
        connectSourceToPipeTrack(pipeTrack, waterSource);
        view.printMessage("Источник \"" + waterSource.name() + "\" подключен.");
    }
    view.printMessage("Шаг 3 завершен.");
    
    // Шаг 4. Вычисление стоимости трассы.
    view.printMessage("\nШаг 4. Вычисление стоимости трассы.");
    CalcNumber cost = pipeTrack.calculateCost();
    view.printMessage("Стоимость трассы равна " + std::to_string(static_cast<int>(cost)) + " руб.");
    view.printMessage("Шаг 4 завершен.");
    
    return pipeTrack;
    
}

/// Подключить к имеющейся трассе pipeTrack источник waterSource. Если трасса пустая, то источник добавляется к стоку. Метод может бросать Exception-исключение.
///
/// \param pipeTrack Текущая трасса.
/// \param waterSource Подключаемой к трассе источник.
void OptimalPipeTrackFinder::connectSourceToPipeTrack(PipeTrack & pipeTrack, const WaterSource & waterSource) {
    
    // Шаг 1. Нахождение для каждого узла трассы узлов локации, через которые данный узел проходит. Нахождение для каждого узла локации узлов трассы, проходящих через данный узел локации.
    
    std::map<const PipeTrackNode*, std::vector<const LocationGraphNode*>> locationNodesForPipeTrackNode;
    std::map<const LocationGraphNode*, std::vector<const PipeTrackNode*>> pipeTrackNodesForLocationNode;
    for (const PipeTrackNode * pipeTrackNodeP : pipeTrack.nodePs) {
        locationNodesForPipeTrackNode[pipeTrackNodeP] = std::vector<const LocationGraphNode*>();
    }
    for (const LocationGraphNode * locationNodeP : locationGraph.nodePs) {
        pipeTrackNodesForLocationNode[locationNodeP] = std::vector<const PipeTrackNode*>();
    }
    
    for (const PipeTrackNode * pipeTrackNodeP : pipeTrack.nodePs) {
        for (const LocationGraphNode * locationNodeP : locationGraph.nodePs) {
            if (pipeTrackNodeP->isIntersectedWithRectangle(locationNodeP->left, locationNodeP->right, locationNodeP->bottom, locationNodeP->top)) {
                locationNodesForPipeTrackNode[pipeTrackNodeP].push_back(locationNodeP);
                pipeTrackNodesForLocationNode[locationNodeP].push_back(pipeTrackNodeP);
            }
        }
    }
    
    // Шаг 2. Нахождение узла локации, содержащего подключаемый источник.
    const LocationGraphNode * sourceLocationNodeP = nullptr;
    for (const LocationGraphNode * locationNodeP : locationGraph.nodePs) {
        if (find(locationNodeP->waterSourcesPs.begin(), locationNodeP->waterSourcesPs.end(), &waterSource) != locationNodeP->waterSourcesPs.end()) {
            sourceLocationNodeP = locationNodeP;
        }
    }
    
    // Шаг 3. Нахождение подходящих путей в графе локации от подключаемого источника к трассе.
    std::vector<std::vector<const LocationGraphNode*>> pathsFromSourceToPipeTrack;
    std::vector<const LocationGraphNode*> buildingPath;
    std::set<const LocationGraphNode*> passedNodes;
    buildingPath.push_back(sourceLocationNodeP);
    passedNodes.insert(sourceLocationNodeP);
    findAllPathsFromSourceToPipeTrack(pathsFromSourceToPipeTrack, buildingPath, passedNodes, pipeTrackNodesForLocationNode);
    
    // Шаг 4. Нахождение для каждого найденного пути ломаной минимальной псевдодлины, соединяющей точку входа подключаемого источника с трассой с учетом внешнего диаметра источника.
    std::vector<std::pair<std::vector<Point>, const PipeTrackNode*>> zigzagForPathsFromSourceToPipeTrack;
    for (const std::vector<const LocationGraphNode*> & pathFromSourceToPipeTrack : pathsFromSourceToPipeTrack) {
        std::pair<std::vector<Point>, const PipeTrackNode*> findResult = findMinPseudoLengthZigzagFromSourceToPipeTrackAndPipeTrackNodeP(pathFromSourceToPipeTrack, pipeTrack, waterSource, pipeTrackNodesForLocationNode);
        zigzagForPathsFromSourceToPipeTrack.push_back(findResult);
    }
    
    // Шаг 5. Сортировка найденных путей и соответствующих ломаных по возрастанию псевдодлины ломаной.
    for (int i = 0; i < pathsFromSourceToPipeTrack.size() - 1; i++) {
        for (int j = i + 1; j < pathsFromSourceToPipeTrack.size(); j++) {
            // нахождение первой длины ломаной
            CalcNumber zigzagLength1 = 0;
            if (zigzagForPathsFromSourceToPipeTrack[i].first.size() == 0) {
                zigzagLength1 = 999999;
            } else {
                for (int l = 1; l < zigzagForPathsFromSourceToPipeTrack[i].first.size(); l++) {
                    zigzagLength1 += (zigzagForPathsFromSourceToPipeTrack[i].first[l] - zigzagForPathsFromSourceToPipeTrack[i].first[l - 1]).length();
                }
            }
            // нахождение второй длины ломаной
            CalcNumber zigzagLength2 = 0;
            if (zigzagForPathsFromSourceToPipeTrack[j].first.size() == 0) {
                zigzagLength2 = 999999;
            } else {
                for (int l = 1; l < zigzagForPathsFromSourceToPipeTrack[j].first.size(); l++) {
                    zigzagLength2 += (zigzagForPathsFromSourceToPipeTrack[j].first[l] - zigzagForPathsFromSourceToPipeTrack[j].first[l - 1]).length();
                }
            }
            // сравнение длин ломаных
            if (zigzagLength2 < zigzagLength1) {
                // перстановка i-го и j-го элементов местами
                std::vector<const LocationGraphNode*> path = pathsFromSourceToPipeTrack[i];
                pathsFromSourceToPipeTrack[i] = pathsFromSourceToPipeTrack[j];
                pathsFromSourceToPipeTrack[j] = path;
                std::pair<std::vector<Point>, const PipeTrackNode*> zigzag = zigzagForPathsFromSourceToPipeTrack[i];
                zigzagForPathsFromSourceToPipeTrack[i] = zigzagForPathsFromSourceToPipeTrack[j];
                zigzagForPathsFromSourceToPipeTrack[j] = zigzag;
            }
        }
    }
    
    // Шаг 6. Устранение найденных путей и соответствующих ломаных для неудачных поисков ломаных.
    for (int i = static_cast<int>(pathsFromSourceToPipeTrack.size()) - 1; i >= 0; i--) {
        if (zigzagForPathsFromSourceToPipeTrack[i].first.size() == 0) {
            pathsFromSourceToPipeTrack.pop_back();
            zigzagForPathsFromSourceToPipeTrack.pop_back();
        }
    }
    
    if (pathsFromSourceToPipeTrack.size() == 0) {
        throw Exception("Ошибка при поиске ломаной минимальной псевдодлины от источника \"" + waterSource.name() + "\" до трассы или стока. Ломаная не найдена.");
    }
    
    // Шаг 7. Для дальнейшего использования оставляется пара (путь, ломаная) с ломаной наименьшей псевдодлины.
    /// Используемый путь для подключения источника.
    std::vector<const LocationGraphNode*> pathFromSourceToPipeTrack = pathsFromSourceToPipeTrack[0];
    /// Соответствующая данному пути ломаная от точки входа источника до центра стока или ближайшей точки центрального отрезка трубы.
    std::vector<Point> zigzagFromSourceToPipeTrack = zigzagForPathsFromSourceToPipeTrack[0].first;
    /// Узел трассы системы водоотведения для подключения или сток (в случае nullptr).
    const PipeTrackNode* endPipeTrackNodeToConnect = zigzagForPathsFromSourceToPipeTrack[0].second;
    
    // Шаг 8 (временный для демонстрации 2D вида схемы). \todo заменить
    // Добавить к имеющейся трассе трубы в соответствии с ломаной zigzagFromSourceToPipeTrack
    unsigned int diameter = waterSource.diameter();
    Point sourcePoint = Point(waterSource.point().x, waterSource.point().y, 0);
    PipeTrackNode * sourceToConnectionNodeP = pipeTrack.createNodeAndReturnP(direct, pipeObjectsBag.getDirectPipeP(diameter), Point(), sourcePoint, zigzagFromSourceToPipeTrack[0], Point(), Point(), Point());
    PipeTrackNode * previousNodeP = sourceToConnectionNodeP;
    for (int i = 1; i < zigzagFromSourceToPipeTrack.size(); i++) {
        PipeTrackNode * currentNodeP = pipeTrack.createNodeAndReturnP(direct, pipeObjectsBag.getDirectPipeP(diameter), Point(), previousNodeP->endPoint, zigzagFromSourceToPipeTrack[i], Point(), Point(), Point());
        previousNodeP = currentNodeP;
    }
   
}

/// Достроить текущий строящийся путь в графе локации до трассы. Если путь не однозначен, построить всевозможные варианты. Если трасса пустая, путь строится до стока.
///
/// \param builtPaths Массив уже построенных путей. В данный массив сохраняются достроенные пути.
/// \param buildingPath Текущий строящийся путь. Последний элемент данного массива - последний пройденный узел, от которого необходимо продолжить строительство. Массив должен быть непустым.
/// \param passedNodes Множество уже пройденных узлов в текущем пути.
/// \param pipeTrackNodesForLocationNode Словарь, в котором для каждого узла графа локации содержится массив содержащихся в нем узлов трассы.
void OptimalPipeTrackFinder::findAllPathsFromSourceToPipeTrack(std::vector<std::vector<const LocationGraphNode*>> & builtPaths, std::vector<const LocationGraphNode*> & buildingPath, std::set<const LocationGraphNode*> & passedNodes, std::map<const LocationGraphNode*, std::vector<const PipeTrackNode*>> & pipeTrackNodesForLocationNode) {
    
    const LocationGraphNode * lastPassedNode = buildingPath[buildingPath.size() - 1];
    if (pipeTrackNodesForLocationNode[lastPassedNode].size() > 0 || lastPassedNode == locationGraph.waterDestinationNodeP) {
        // текущий путь добавляется в массив построенных путей
        builtPaths.push_back(buildingPath);
    }
    for (LocationGraphNode * adjacentNodeP : lastPassedNode->adjacentNodes()) {
        if (passedNodes.find(adjacentNodeP) == passedNodes.end()) {
            buildingPath.push_back(adjacentNodeP);
            passedNodes.insert(adjacentNodeP);
            findAllPathsFromSourceToPipeTrack(builtPaths, buildingPath, passedNodes, pipeTrackNodesForLocationNode);
            buildingPath.pop_back();
            passedNodes.erase(adjacentNodeP);
        }
    }
    
}

/// Найти для пути pathFromSourceToPipeTrack ломаную минимальной псевдодлины, соединяющую точку входа подключаемого источника waterSource с трассой pipeTrack. При поиске учитывается внешний диаметр источника. Если трасса пустая, то источник соединяется со стоком.
///
/// \param pathFromSourceToPipeTrack Путь от источника до трассы в виде узлов графа локации.
/// \param pipeTrack Трасса системы водоотведения.
/// \param waterSource Подключаемый источник.
/// \param pipeTrackNodesForLocationNode Словарь, в котором для каждого узла графа локации содержится массив содержащихся в нем узлов трассы.
///
/// \return Пара типа (ломаная, указатель на соединяемый узел трассы). Ломаная - ломаная минимальной псевдодлины, проходящая через узлы пути pathFromSourceToPipeTrack, соединяющая источник waterSource с трассой pipeTrack. Если последней точкой ломаной является центр стока, то указатель на соединяемый узел трассы равен nullptr. Если поиск неуспешен, возвращается пустая ломаная.
std::pair<std::vector<Point>, const PipeTrackNode*> OptimalPipeTrackFinder::findMinPseudoLengthZigzagFromSourceToPipeTrackAndPipeTrackNodeP(const std::vector<const LocationGraphNode*> & pathFromSourceToPipeTrack, const PipeTrack & pipeTrack, const WaterSource & waterSource, std::map<const LocationGraphNode*, std::vector<const PipeTrackNode*>> & pipeTrackNodesForLocationNode) {
    
    // половина внешнего диаметра источника
    CalcNumber externalDiameterHalfed = pipeObjectsBag.getExternalDiameter(waterSource.diameter()) / 2;
    
    // результирующая ломаная
    std::vector<Point> zigzag;
    
    // добавление в ломаную точку входа подключаемого источника
    const LocationGraphNode * sourceLocationNodeP = pathFromSourceToPipeTrack[0];
    for (int i = 0; i < sourceLocationNodeP->waterSourcesPs.size(); i++) {
        if (&waterSource == sourceLocationNodeP->waterSourcesPs[i]) {
            zigzag.push_back(sourceLocationNodeP->waterSourcesConnectionPoints[i]);
        }
    }
    
    for (int i = 0; i < pathFromSourceToPipeTrack.size() - 1; i++) {
        
        // добавление в ломаную точки на границе между текущим и следующим узлами пути
        
        // указатель на текущий узел пути
        const LocationGraphNode* currentNodeP = pathFromSourceToPipeTrack[i];
        // указатель на следующий узел пути
        const LocationGraphNode* nextNodeP = pathFromSourceToPipeTrack[i + 1];
        
        // определение взаимного отношения текущего и следующего узлов
        bool isBottomTop = false, isTopBottom = false, isLeftRight = false, isRightLeft = false;
        if (std::find(currentNodeP->leftNodesPs.begin(), currentNodeP->leftNodesPs.end(), nextNodeP) != currentNodeP->leftNodesPs.end()) {
            isRightLeft = true;
        }
        if (std::find(currentNodeP->rightNodesPs.begin(), currentNodeP->rightNodesPs.end(), nextNodeP) != currentNodeP->rightNodesPs.end()) {
            isLeftRight = true;
        }
        if (std::find(currentNodeP->bottomNodesPs.begin(), currentNodeP->bottomNodesPs.end(), nextNodeP) != currentNodeP->bottomNodesPs.end()) {
            isTopBottom = true;
        }
        if (std::find(currentNodeP->topNodesPs.begin(), currentNodeP->topNodesPs.end(), nextNodeP) != currentNodeP->topNodesPs.end()) {
            isBottomTop = true;
        }
        
        // последняя добавленная в ломаную точка
        Point lastAddedPoint = zigzag[zigzag.size() - 1];
        
        // определение новой добавляемой в ломаную точки
        Point newPoint;
        if (isBottomTop || isTopBottom) {
            CalcNumber left = std::max(currentNodeP->left, nextNodeP->left);
            CalcNumber right = std::min(currentNodeP->right, nextNodeP->right);
            if (right - left < 2 * externalDiameterHalfed) {
                // данного прохода не достаточно для прокладки трубы
                return std::pair<std::vector<Point>, const PipeTrackNode*>(std::vector<Point>(), nullptr);
            }
            if (lastAddedPoint.x < left + externalDiameterHalfed) {
                newPoint.x = left + externalDiameterHalfed;
            } else if (lastAddedPoint.x > right - externalDiameterHalfed) {
                newPoint.x = right - externalDiameterHalfed;
            } else {
                newPoint.x = lastAddedPoint.x;
            }
            newPoint.y = (isBottomTop) ? currentNodeP->top + externalDiameterHalfed : currentNodeP->bottom - externalDiameterHalfed;
        } else {
            CalcNumber bottom = std::max(currentNodeP->bottom, nextNodeP->bottom);
            CalcNumber top = std::min(currentNodeP->top, nextNodeP->top);
            if (top - bottom < 2 * externalDiameterHalfed) {
                // данного прохода не достаточно для прокладки трубы
                return std::pair<std::vector<Point>, const PipeTrackNode*>(std::vector<Point>(), nullptr);
            }
            if (lastAddedPoint.y < bottom + externalDiameterHalfed) {
                newPoint.y = bottom + externalDiameterHalfed;
            } else if (lastAddedPoint.y > top - externalDiameterHalfed) {
                newPoint.y = top - externalDiameterHalfed;
            } else {
                newPoint.y = lastAddedPoint.y;
            }
            newPoint.x = (isLeftRight) ? currentNodeP->right + externalDiameterHalfed : currentNodeP->left - externalDiameterHalfed;
        }
        
        // добавление новой точки в ломаную
        zigzag.push_back(newPoint);
        
    }
    
    // определение последней добавляемой точки в ломаную
    const LocationGraphNode* endNodeP = pathFromSourceToPipeTrack[pathFromSourceToPipeTrack.size() - 1];
    Point lastAddedPoint = zigzag[zigzag.size() - 1];
    bool somePointIsFound = false;
    Point endPoint;
    const PipeTrackNode * resultPipeTrackNodeP = nullptr;
    CalcNumber minDistance = 999999;
    // проверка существующих узлов схемы
    for (const PipeTrackNode * pipeTrackNodeP : pipeTrackNodesForLocationNode[endNodeP]) {
        if (pipeTrackNodeP->type == direct || pipeTrackNodeP->type == fan) {
            Point nearestCenterPoint = pipeTrackNodeP->calculateNearestCenterPoint2D(lastAddedPoint); // \todo проверить логику для случая, когда источник внутри доступной области уже находится!
            if (endNodeP->left <= nearestCenterPoint.x
                && nearestCenterPoint.x <= endNodeP->right
                && endNodeP->bottom <= nearestCenterPoint.y
                && nearestCenterPoint.y <= endNodeP->top) {
                CalcNumber distance = (lastAddedPoint - nearestCenterPoint).length();
                if (distance < minDistance) {
                    minDistance = distance;
                    endPoint = nearestCenterPoint;
                    resultPipeTrackNodeP = pipeTrackNodeP;
                    somePointIsFound = true;
                }
            }
        }
    }
    // проверка стока
    if (endNodeP->waterDestinationP != nullptr) {
        Point waterDestinationPoint = Point(endNodeP->waterDestinationP->point().x, endNodeP->waterDestinationP->point().y, 0);
        CalcNumber distanceToDestination = (waterDestinationPoint - lastAddedPoint).length();
        if (distanceToDestination < minDistance) {
            minDistance = distanceToDestination;
            endPoint = waterDestinationPoint;
            resultPipeTrackNodeP = nullptr;
            somePointIsFound = true;
        }
    }
    
    if (somePointIsFound) {
        zigzag.push_back(endPoint);
    } else {
        zigzag.clear();
    }
    
    return std::pair<std::vector<Point>, const PipeTrackNode*>(zigzag, resultPipeTrackNodeP);
    
}

#endif /* OptimalPipeTrackFinder_hpp */
