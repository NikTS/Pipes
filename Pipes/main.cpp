// Подключение стандартных библиотек
#include <string>

// Подключение внутренних типов
#include "DecisionMaker.hpp"
#include "ConsoleView.hpp"
#include "Config.hpp"
#include "PipeObjectsBag.hpp"
#include "OptimizationParameters.hpp"
#include "LocationGraph.hpp"
#include "WaterConnectionObjects.hpp"
#include "OptimalPipeTrackFinder.hpp"

/// Вернуть абсолютный путь папки, содержащей данный файл.
///
/// \return Абсолютный путь папки, содержащей данный файл.
static std::string get_current_folder_path() {
    
    std::string current_file_path = __FILE__;
    size_t last_delimeter_pos = current_file_path.find_last_of("/");
    return current_file_path.substr(0, last_delimeter_pos);
    
}

int main(int argc, const char * argv[]) {
    
    /*
    // модульное тестирование
    PointTester().test();
    SoLESolverTester().test();
    Matrix4x4Tester().test();
    LineTester().test();
    PlaneTester().test();
    SimplePipeTrackTester().test();
    */
    
    /// Объект, отвечающий за вывод сообщений и ошибок.
    ConsoleView view;
    
    try {
        
        // 1. Создание объекта, отвечающего за принятие неоднозначных решений при нахождении оптимальной трассы системы водоотведения.
        
        /// Объект, отвечающий за принятие неоднозначных решений при нахождении оптимальной трассы системы водоотведения.
        DecisionMaker decisionMaker { view };
        view.printMessage("\nЗагрузка принятых решений из файла \"/InputData/decisions.csv\".");
        decisionMaker.loadDecisionsFromFile(get_current_folder_path() + "/InputData/decisions.csv");
        
        // 2. Представление объекта, отвечающего з апринятие решений.
        
        unsigned int startAlternativeNumber = decisionMaker.helpWithDecision("Рассказать про объект, отвечающий за принятие решений при построении трассы системы водоотведения, или запустить алгоритм?", {
            DecisionMaker::Alternative(1, "рассказать про объект"),
            DecisionMaker::Alternative(2, "запустить алгоритм")
        });
        
        if (startAlternativeNumber == 1) {
            view.printMessage("\nЗдравствуйте! Рады Вас приветствовать в приложении, помогающей проектировать трассы системы водоотведения.\n\nВ ходе выполнения алгоритма построения трассы приложению часто требуется принимать неоднозначные решения. В случае принятия таких решений приложение делает выбор по умолчанию на основе внутренних правил, однако пользователю приложения предоставляется возможность помогать приложению в принятии таких решений. Для этого используется файл \"decisions.csv\". В этом файле можно явно задать нужную альтернативу, если выбранной алгоритмом вариант пользователя не устраивает.\n\nТеперь добавьте в данный файл строку \"1;2\", сохраните его и перезапустите программу.\n");
            return 0;
        }
        
        // 3. Создание и загрузка объектов.
        
        /// Параметры модели.
        Config config;
        view.printMessage("\nЗагрузка параметров модели из файла \"/InputData/config.csv\".");
        config.loadFromFile(get_current_folder_path() + "/InputData/config.csv");
        
        /// Хранилище, содержащее доступные к использованию объекты системы водоотведения.
        PipeObjectsBag bag { config };
        view.printMessage("\nЗагрузка внешних диаметров труб и доступных к использованию объектов системы водоснабжения из файлов \"/InputData/externalDiameters.csv\" и \"/InputData/materials.csv\" соответственно.");
        bag.loadFromFile(get_current_folder_path() + "/InputData/externalDiameters.csv", get_current_folder_path() + "/InputData/materials.csv");
        
        /// Параметры алгоритма оптимизации.
        OptimizationParameters optimizationParameters;
        
        /// Граф локации, состоящий из прямоугольных областей, в которой могут проходить трубы трассы системы водоотведения.
        LocationGraph locationGraph = LocationGraph(&bag, &optimizationParameters);
        view.printMessage("\nЗагрузка графа локации из файла \"/InputData/location.csv\".");
        locationGraph.loadFromFile(get_current_folder_path() + "/InputData/location.csv");
        locationGraph.connectAllNodes();
        
        /// Объекты подключения воды. Состоят из одного стока и одного или более источника.
        WaterConnectionObjects waterConnectionObjects;
        view.printMessage("\nЗагрузка объектов подключения воды из файла \"/InputData/connections.csv\".");
        waterConnectionObjects.loadObjectsFromFile(get_current_folder_path() + "/InputData/connections.csv");
        
        /// Вычислитель оптимальной трассы системы водоотведения.
        OptimalPipeTrackFinder optimalPipeTrackFinder { config, waterConnectionObjects, bag, locationGraph, optimizationParameters, view, decisionMaker };
        
        // 4. Начало вычислений.
        
        view.printMessage("\n----------------------------------------------------------------------------------------------------------");
        
        // Вычисление оптимальной трассы системы водоотведения.
        PipeTrack optimalPipeTrack = optimalPipeTrackFinder.calculateOptimalPipeTrack();
        
        // Вывод найденной трассы.
        optimalPipeTrack.print2D();
        
        // Вывод данных для отображения 2D-схемы трассы в файл.
        view.printMessage("\nВывод данных для отображения 2D-схемы трассы в файл \"/OutputData/pipeTrack2D.txt\".");
        optimalPipeTrack.print2DDataToFile(get_current_folder_path() + "/OutputData/pipeTrack2D.txt");
        
        view.printMessage("\n----------------------------------------------------------------------------------------------------------");
        
        view.printMessage("\nВ данной версии приложения продемонстрирован базовый алгоритм для построения 2D-схемы трассы системы водоотведения. 3D-версия находится в процессе доработки, поэтому исключена из текущей версии приложения, как и использование техники принятия решений алгоритмом. Данная функциональность, а также другие улучшения, будут добавлены в финальную версию.\n");
        
    }
    catch (const Exception & exception) {
        view.printError(exception.errorMessage);
    }

    return 0;
    
}

