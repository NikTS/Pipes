#ifndef SimplePipeTrackTester_hpp
#define SimplePipeTrackTester_hpp

// Подключение стандартных библиотек
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

// Подключение внутренних типов
#include "SimplePipeTrack.hpp"

/// Тестер для класса SimplePipeTrack.
class SimplePipeTrackTester {
    
public:
    
    // MARK: - Открытые методы
    
    /// Тестировать класс SimplePipeTrack.
    void test();
    
};

// MARK: - Реализация

/// Тестировать класс SimplePipeTrack.
void SimplePipeTrackTester::test() {
    
    SimplePipeTrack pipeTrack;
    
    assert(pipeTrack.rootNodeP == nullptr);
    assert(pipeTrack.getNodePForId(0) == nullptr);
    assert(pipeTrack.calculateMinSlopeAngleSin() == 1);
    
    pipeTrack.addNewRootNode(5, Point(4, 7, 11), -1);
    
    assert(pipeTrack.rootNodeP != nullptr);
    assert(pipeTrack.rootNodeP->id == 5);
    assert(pipeTrack.rootNodeP->point == Point(4, 7, 11));
    assert(pipeTrack.rootNodeP->nextNodesPs.size() == 0);
    assert(pipeTrack.getNodePForId(0) == nullptr);
    assert(pipeTrack.getNodePForId(5) == pipeTrack.rootNodeP);
    assert(pipeTrack.calculateMinSlopeAngleSin() == 1);
    
    pipeTrack.addNewRootNode(4, Point(4, 7, 10), 3);
    
    // 4 -> 5
    
    assert(pipeTrack.rootNodeP != nullptr);
    assert(pipeTrack.rootNodeP->id == 4);
    assert(pipeTrack.rootNodeP->point == Point(4, 7, 10));
    assert(pipeTrack.rootNodeP->nextNodesPs.size() == 1);
    assert(pipeTrack.rootNodeP->nextNodesPs[0]->id == 5);
    assert(pipeTrack.getNodePForId(0) == nullptr);
    assert(pipeTrack.getNodePForId(5) == pipeTrack.rootNodeP->nextNodesPs[0]);
    assert(pipeTrack.getNodePForId(4) == pipeTrack.rootNodeP);
    assert(pipeTrack.getNodePForId(5)->pipeDirection == Point(0, 0, 1));
    assert(pipeTrack.getNodePForId(5)->diameter == 3);
    assert(pipeTrack.calculateMinSlopeAngleSin() == 1);
    
    pipeTrack.addNewNodeToExisting(6, Point(5, 4, 12), 5, 5);
    
    // 4 -> 5, 5 -> 6
    
    assert(pipeTrack.rootNodeP != nullptr);
    assert(pipeTrack.rootNodeP->id == 4);
    assert(pipeTrack.rootNodeP->point == Point(4, 7, 10));
    assert(pipeTrack.rootNodeP->nextNodesPs.size() == 1);
    assert(pipeTrack.rootNodeP->nextNodesPs[0]->id == 5);
    assert(pipeTrack.getNodePForId(0) == nullptr);
    assert(pipeTrack.getNodePForId(5) == pipeTrack.rootNodeP->nextNodesPs[0]);
    assert(pipeTrack.getNodePForId(5)->id == 5);
    assert(pipeTrack.getNodePForId(5)->pipeDirection == Point(0, 0, 1));
    assert(pipeTrack.getNodePForId(5)->diameter == 3);
    assert(pipeTrack.getNodePForId(5)->nextNodesPs.size() == 1);
    assert(pipeTrack.getNodePForId(4) == pipeTrack.rootNodeP);
    assert(pipeTrack.getNodePForId(6) == pipeTrack.getNodePForId(5)->nextNodesPs[0]);
    assert(pipeTrack.getNodePForId(6)->id == 6);
    assert(pipeTrack.getNodePForId(6)->point == Point(5, 4, 12));
    assert(pipeTrack.getNodePForId(6)->pipeDirection == Point(1, -3, 1));
    assert(pipeTrack.getNodePForId(6)->diameter == 5);
    assert(pipeTrack.getNodePForId(6)->nextNodesPs.size() == 0);
    assert(abs(pipeTrack.calculateMinSlopeAngleSin() - (1.0 / sqrt(11))) < 1e-6);
    
    SimplePipeTrack pipeTrack2 = pipeTrack;
    
    assert(pipeTrack2.rootNodeP != nullptr);
    assert(pipeTrack2.rootNodeP->id == 4);
    assert(pipeTrack2.rootNodeP->point == Point(4, 7, 10));
    assert(pipeTrack2.rootNodeP->nextNodesPs.size() == 1);
    assert(pipeTrack2.rootNodeP->nextNodesPs[0]->id == 5);
    assert(pipeTrack2.getNodePForId(0) == nullptr);
    assert(pipeTrack2.getNodePForId(5) == pipeTrack.rootNodeP->nextNodesPs[0]);
    assert(pipeTrack2.getNodePForId(5)->id == 5);
    assert(pipeTrack2.getNodePForId(5)->pipeDirection == Point(0, 0, 1));
    assert(pipeTrack2.getNodePForId(5)->diameter == 3);
    assert(pipeTrack2.getNodePForId(5)->nextNodesPs.size() == 1);
    assert(pipeTrack2.getNodePForId(4) == pipeTrack.rootNodeP);
    assert(pipeTrack2.getNodePForId(6) == pipeTrack.getNodePForId(5)->nextNodesPs[0]);
    assert(pipeTrack2.getNodePForId(6)->id == 6);
    assert(pipeTrack2.getNodePForId(6)->point == Point(5, 4, 12));
    assert(pipeTrack2.getNodePForId(6)->pipeDirection == Point(1, -3, 1));
    assert(pipeTrack2.getNodePForId(6)->diameter == 5);
    assert(pipeTrack2.getNodePForId(6)->nextNodesPs.size() == 0);
    assert(abs(pipeTrack2.calculateMinSlopeAngleSin() - (1.0 / sqrt(11))) < 1e-6);
    
    SimplePipeTrack pipeTrack3;
    pipeTrack3 = pipeTrack;
    
    assert(pipeTrack3.rootNodeP != nullptr);
    assert(pipeTrack3.rootNodeP->id == 4);
    assert(pipeTrack3.rootNodeP->point == Point(4, 7, 10));
    assert(pipeTrack3.rootNodeP->nextNodesPs.size() == 1);
    assert(pipeTrack3.rootNodeP->nextNodesPs[0]->id == 5);
    assert(pipeTrack3.getNodePForId(0) == nullptr);
    assert(pipeTrack3.getNodePForId(5) == pipeTrack.rootNodeP->nextNodesPs[0]);
    assert(pipeTrack3.getNodePForId(5)->id == 5);
    assert(pipeTrack3.getNodePForId(5)->pipeDirection == Point(0, 0, 1));
    assert(pipeTrack3.getNodePForId(5)->diameter == 3);
    assert(pipeTrack3.getNodePForId(5)->nextNodesPs.size() == 1);
    assert(pipeTrack3.getNodePForId(4) == pipeTrack.rootNodeP);
    assert(pipeTrack3.getNodePForId(6) == pipeTrack.getNodePForId(5)->nextNodesPs[0]);
    assert(pipeTrack3.getNodePForId(6)->id == 6);
    assert(pipeTrack3.getNodePForId(6)->point == Point(5, 4, 12));
    assert(pipeTrack3.getNodePForId(6)->pipeDirection == Point(1, -3, 1));
    assert(pipeTrack3.getNodePForId(6)->diameter == 5);
    assert(pipeTrack3.getNodePForId(6)->nextNodesPs.size() == 0);
    assert(abs(pipeTrack3.calculateMinSlopeAngleSin() - (1.0 / sqrt(11))) < 1e-6);
    
    std::cout << "Тестирование класса SimplePipeTrack завершилось успешно.\n";
    
}

#endif /* SimplePipeTrackTester_hpp */
