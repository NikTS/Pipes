#ifndef PipeTrack_hpp
#define PipeTrack_hpp

// Подключение стандартных библиотек
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <fstream>

// Подключение внутренних типов
#include "Exception.hpp"
#include "PipeTrackNode.hpp"
#include "View.hpp"

/// Трасса системы водоотведения. Состоит из расположенных в пространстве объектов системы водоотведения (прямых труб, фановых труб, редукций, отводов, тройников, крестовин). Имеет вид дерева.
struct PipeTrack {
    
private:
    
    // MARK: - Скрытые объекты
    
    /// Указатель на объект, отвечающий за вывод сообщений и ошибок.
    View * viewP;
    
public:
    
    // MARK: - Открытые объекты
    
    /// Указатели на узлы трассы.
    std::vector<PipeTrackNode*> nodePs;
    
    /// Указатель на корневой узел трассы или nullptr. Данный узел соответствует стоку (стояку) трассы.
    PipeTrackNode * rootNodeP;
    
    // MARK: - Конструкторы
    
    /// Конструктор. Создается пустая трасса.
    ///
    /// \param viewP Указатель на объект, отвечающий за вывод сообщений и ошибок.
    explicit PipeTrack(View * viewP);
    
    /// Конструктор копирования.
    ///
    /// \param anotherPipeTrack Копируемая трасса системы водоотведения.
    PipeTrack(const PipeTrack & anotherPipeTrack);
    
    /// Деструктор.
    ~PipeTrack();
    
    // MARK: - Открытые методы
    
    /// Оператор копирования.
    ///
    /// \param anotherPipeTrack Копируемая трасса системы водоотведения.
    PipeTrack & operator=(const PipeTrack & anotherPipeTrack);
    
    /// Создать новый узел трассы и вернуть указатель на него.
    ///
    /// \param type Тип объекта системы водоотведения.
    /// \param pipeObjectP Указатель на объект системы водоотведения.
    /// \param centerPoint Центр объекта (для типов "отвод", "тройник", "крестовина"; единица измерения - мм.). Под центром объекта понимается точка пересечения осей труб.
    /// \param startPoint Начало объекта (для типов "прямая труба", "фановая труба", "редукция"; единица измерения - мм.). Под началом объекта понимается центр его м-входа.
    /// \param endPoint Конец объекта (для типов "прямая труба", "фановая труба", "редукция"; единица измерения - мм.). Под концом объекта понимается центр м-входа соединенного с его п-выходом объекта.
    /// \param baseDirection Основное направление объекта (для типов "отвод", "тройник", "крестовина"). Вектор, задающий направление оси основной (прямой) трубы объекта в сторону стока (к п-выходу).
    /// \param secondDirection Второе направление объекта (для типов "тройник", "крестовина"). Вектор, задающий направление второго м-входа объекта от центра данного м-входа в сторону центра объекта.
    /// \param thirdDirection Третье направление объекта (для типа "крестовина"). Вектор, задающий направление третьего м-входа объекта от центра данного м-входа в сторону центра объекта.
    ///
    /// \return Указатель на созданный узел трассы.
    PipeTrackNode * createNodeAndReturnP(PipeObjectType type, const PipeObject * pipeObjectP, const Point & centerPoint, const Point & startPoint, const Point & endPoint, const Point & baseDirection, const Point & secondDirection, const Point & thirdDirection);
    
    /// Удалить узел из трассы. При удалении узла устраняются связи данного узла со смежными.
    ///
    /// \param pipeTrackNodeP Указатель на удаляемый узел или nullptr.
    void removeNode(PipeTrackNode * pipeTrackNodeP);
    
    /// Вычислить стоимость трассы как сумму стоимостей входящих в нее объектов.
    ///
    /// \return Стоимость трассы (единица измерения - руб.).
    CalcNumber calculateCost();
    
    /// Вывести информацию о 2D-виде трассе.
    void print2D();
    
    /// Вывести данные для отображения 2D-схемы трассы в файл. Метод может бросать Exception-исключение.
    ///
    /// \param fileName Имя файла.
    void print2DDataToFile(const std::string & fileName);
    
private:
    
    // MARK: - Скрытые методы
    
    /// Вернуть число в виде форматированной строки.
    ///
    /// \param number Число.
    /// \param count Число цифр в строке.
    ///
    /// \return Форматированная строка, представляющая число number.
    std::string getFormattedNumber(CalcNumber number, unsigned int count);
    
};

// MARK: - Реализация

/// Конструктор. Создается пустая трасса.
///
/// \param viewP Указатель на объект, отвечающий за вывод сообщений и ошибок.
PipeTrack::PipeTrack(View * viewP): viewP(viewP), rootNodeP(nullptr) {}

/// Конструктор копирования.
///
/// \param anotherPipeTrack Копируемая трасса системы водоотведения.
PipeTrack::PipeTrack(const PipeTrack & anotherPipeTrack) {
    
    *this = anotherPipeTrack;
    
}

/// Деструктор.
PipeTrack::~PipeTrack() {
    
    for (PipeTrackNode * nodeP : nodePs) {
        delete nodeP;
    }
    nodePs.clear();
    
}

/// Оператор копирования.
///
/// \param anotherPipeTrack Копируемая трасса системы водоотведения.
PipeTrack & PipeTrack::operator=(const PipeTrack & anotherPipeTrack) {
    
    viewP = anotherPipeTrack.viewP;
    
    std::map<const PipeTrackNode*, int> indexForAnotherPipeNodeP;
    
    for (int i = 0; i < anotherPipeTrack.nodePs.size(); i++) {
        const PipeTrackNode * anotherPipeTrackNodeP = anotherPipeTrack.nodePs[i];
        indexForAnotherPipeNodeP[anotherPipeTrackNodeP] = i;
        nodePs.push_back(new PipeTrackNode(*anotherPipeTrackNodeP));
    }
    
    for (int i = 0; i < anotherPipeTrack.nodePs.size(); i++) {
        const PipeTrackNode * anotherPipeTrackNodeP = anotherPipeTrack.nodePs[i];
        PipeTrackNode * nodeP = nodePs[i];
        nodeP->nextNodeP = (anotherPipeTrackNodeP->nextNodeP == nullptr) ? nullptr : nodePs[indexForAnotherPipeNodeP[anotherPipeTrackNodeP->nextNodeP]];
        nodeP->basePrevNodeP = (anotherPipeTrackNodeP->basePrevNodeP == nullptr) ? nullptr : nodePs[indexForAnotherPipeNodeP[anotherPipeTrackNodeP->basePrevNodeP]];
        nodeP->secondPrevNodeP = (anotherPipeTrackNodeP->secondPrevNodeP == nullptr) ? nullptr : nodePs[indexForAnotherPipeNodeP[anotherPipeTrackNodeP->secondPrevNodeP]];
        nodeP->thirdPrevNodeP = (anotherPipeTrackNodeP->thirdPrevNodeP == nullptr) ? nullptr : nodePs[indexForAnotherPipeNodeP[anotherPipeTrackNodeP->thirdPrevNodeP]];
    }
    
    return *this;
    
}

/// Создать новый узел трассы и вернуть указатель на него.
///
/// \param type Тип объекта системы водоотведения.
/// \param pipeObjectP Указатель на объект системы водоотведения.
/// \param centerPoint Центр объекта (для типов "отвод", "тройник", "крестовина"; единица измерения - мм.). Под центром объекта понимается точка пересечения осей труб.
/// \param startPoint Начало объекта (для типов "прямая труба", "фановая труба", "редукция"; единица измерения - мм.). Под началом объекта понимается центр его м-входа.
/// \param endPoint Конец объекта (для типов "прямая труба", "фановая труба", "редукция"; единица измерения - мм.). Под концом объекта понимается центр м-входа соединенного с его п-выходом объекта.
/// \param baseDirection Основное направление объекта (для типов "отвод", "тройник", "крестовина"). Вектор, задающий направление оси основной (прямой) трубы объекта в сторону стока (к п-выходу).
/// \param secondDirection Второе направление объекта (для типов "тройник", "крестовина"). Вектор, задающий направление второго м-входа объекта от центра данного м-входа в сторону центра объекта.
/// \param thirdDirection Третье направление объекта (для типа "крестовина"). Вектор, задающий направление третьего м-входа объекта от центра данного м-входа в сторону центра объекта.
///
/// \return Указатель на созданный узел трассы.
PipeTrackNode * PipeTrack::createNodeAndReturnP(PipeObjectType type, const PipeObject * pipeObjectP, const Point & centerPoint, const Point & startPoint, const Point & endPoint, const Point & baseDirection, const Point & secondDirection, const Point & thirdDirection) {
    
    PipeTrackNode * newNodeP = new PipeTrackNode(type, pipeObjectP, centerPoint, startPoint, endPoint, baseDirection, secondDirection, thirdDirection);
    nodePs.push_back(newNodeP);
    
    return newNodeP;
    
}

/// Удалить узел из трассы. При удалении узла устраняются связи данного узла со смежными.
///
/// \param pipeTrackNodeP Указатель на удаляемый узел или nullptr.
void PipeTrack::removeNode(PipeTrackNode * pipeTrackNodeP) {
    
    if (pipeTrackNodeP == nullptr) {
        return;
    }
    
    if (pipeTrackNodeP->nextNodeP != nullptr) {
        if (pipeTrackNodeP->nextNodeP->basePrevNodeP == pipeTrackNodeP) {
            pipeTrackNodeP->nextNodeP->basePrevNodeP = nullptr;
        }
        if (pipeTrackNodeP->nextNodeP->secondPrevNodeP == pipeTrackNodeP) {
            pipeTrackNodeP->nextNodeP->secondPrevNodeP = nullptr;
        }
        if (pipeTrackNodeP->nextNodeP->thirdPrevNodeP == pipeTrackNodeP) {
            pipeTrackNodeP->nextNodeP->thirdPrevNodeP = nullptr;
        }
    }
    
    if (pipeTrackNodeP->basePrevNodeP != nullptr) {
        pipeTrackNodeP->basePrevNodeP->nextNodeP = nullptr;
    }
    if (pipeTrackNodeP->secondPrevNodeP != nullptr) {
        pipeTrackNodeP->secondPrevNodeP->nextNodeP = nullptr;
    }
    if (pipeTrackNodeP->thirdPrevNodeP != nullptr) {
        pipeTrackNodeP->thirdPrevNodeP->nextNodeP = nullptr;
    }
    
    for (int i = 0; i < nodePs.size(); i++) {
        if (nodePs[i] == pipeTrackNodeP) {
            nodePs.erase(nodePs.begin() + i);
            break;
        }
    }
    
    if (rootNodeP == pipeTrackNodeP) {
        rootNodeP = nullptr;
    }
    
    delete pipeTrackNodeP;
    
}

/// Вычислить стоимость трассы как сумму стоимостей входящих в нее объектов.
///
/// \return Стоимость трассы (единица измерения - руб.).
CalcNumber PipeTrack::calculateCost() {
    
    CalcNumber resultCost = 0;
    
    for (const PipeTrackNode * pipeTrackNodeP : nodePs) {
        resultCost += pipeTrackNodeP->calculateCost();
    }
    
    return resultCost;
    
}

/// Вывести информацию о 2D-виде трассе.
void PipeTrack::print2D() {
    
    viewP->printMessage("\nТрасса системы водоотведения в 2D-виде:");
    viewP->printMessage("Начальный узел  | Конечный узел  | Длина | Диаметр трубы");
    viewP->printMessage("----------------|----------------|-------|---------------");
    for (const PipeTrackNode * pipeTrackNodeP : nodePs) {
        std::string startNodeStr = "(" + getFormattedNumber(pipeTrackNodeP->startPoint.x, 6) + ", " + getFormattedNumber(pipeTrackNodeP->startPoint.y, 6) + ")";
        std::string endNodeStr = "(" + getFormattedNumber(pipeTrackNodeP->endPoint.x, 6) + ", " + getFormattedNumber(pipeTrackNodeP->endPoint.y, 6) + ")";
        std::string lengthStr = getFormattedNumber(static_cast<int>((pipeTrackNodeP->endPoint - pipeTrackNodeP->startPoint).length()), 7);
        unsigned int diameter = (pipeTrackNodeP->type == direct) ? static_cast<const FanPipe*>(pipeTrackNodeP->pipeObjectP)->diameter : 0; // \todo случаи других объектов учесть
        std::string diameterStr = getFormattedNumber(diameter, 14);
        viewP->printMessage(startNodeStr + "|" + endNodeStr + "|" + lengthStr + "|" + diameterStr);
    }
    viewP->printMessage("----------------|----------------|-------|---------------");
    
}

/// Вывести данные для отображения 2D-схемы трассы в файл. Метод может бросать Exception-исключение.
///
/// \param fileName Имя файла.
void PipeTrack::print2DDataToFile(const std::string & fileName) {
    
    try {
        std::ofstream oStream;
        oStream.open(fileName);
        
        oStream << nodePs.size() << " 0\n";
        for (const PipeTrackNode * pipeTrackNodeP : nodePs) {
            unsigned int diameter = (pipeTrackNodeP->type == direct) ? static_cast<const DirectPipe*>(pipeTrackNodeP->pipeObjectP)->diameter : 1; // \todo для других типов добавить
            oStream << pipeTrackNodeP->startPoint.x << " " << pipeTrackNodeP->startPoint.y << " " << pipeTrackNodeP->endPoint.x << " " << pipeTrackNodeP->endPoint.y << " " << std::to_string(diameter) << "\n";
        }
        
        oStream.close();
    }
    catch(...) {
        throw Exception("Ошибка при выводе данных для отображения 2D-схемы трассы в файл \"" + fileName + "\".");
    }
    
}

/// Вернуть число в виде форматированной строки.
///
/// \param number Число.
/// \param count Число цифр в строке.
///
/// \return Форматированная строка, представляющая число number.
std::string PipeTrack::getFormattedNumber(CalcNumber number, unsigned int count) {
    
    std::ostringstream oStream;
    oStream << std::setw(count) << number;
    return oStream.str();
    
}

#endif /* PipeTrack_hpp */
