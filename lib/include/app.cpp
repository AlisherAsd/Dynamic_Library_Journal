#include <iostream>
#include <vector>
#include "../header/Journal.h"
#include "../header/Message.h"
#include "../header/Level.h"
#include "../header/app.h"


// Присваиваем значения int из класса для сравнения 
int SetLevelMessageInt(std::string level) {
    if (level == "HIGH") return static_cast<int>(MessageLevel::HIGH);
    if (level == "LOW") return static_cast<int>(MessageLevel::LOW);
    if (level == "MEDIUM") return static_cast<int>(MessageLevel::MEDIUM);
    else {
        throw "ERROR ENTER LEVEL NOT ( LOW || MEDIUM || HIGH )";
    }
}

void app() 
{

    std::string name;
    std::string dLevel;
    std::cout << "Enter name and default level (HIGH or MEDIUM or LOW) of journal." << std::endl;
    std::cout << "Name: "; 
    std::getline(std::cin, name);
    std::cout << "Default level: "; 
    std::cin >> dLevel; // Уровень важности журнала
    std::cin.ignore(); // очистка буффера
    
    int DefaultLevel, MessageLevel; // Переменные для сравнения

    if (dLevel != "") { // Если левел пропущен, выкидываем исключение
        DefaultLevel = SetLevelMessageInt(dLevel);
    } else {
        throw "ERROR NOT DEFAULT LEVEL FOR JOURNAL";
    }


    Journal j(name, dLevel); // Создаем журнал

    std::string text = "";
    std::string level = "";
    std::string time = "";
    std::cout << std::endl;
    std::cout << "If you want exit, enter q." << std::endl;
    std::cout << std::endl;

    Message message;
    // Запуск логирующего потока для записи в файл
    std::thread loggerThread(&Journal::Write, &j, name);

    for (int i = 1; 300; i++) {
        std::cout << "Message " << i << std::endl;
        
        std::cout << "text: ";
        getline(std::cin, text);
        if (text == "q") break;

        std::cout << "level HIGH or MEDIUM or LOW (press Enter for default level): ";
        getline(std::cin, level);

        if (level == "") { // Если левел пропущен, берем значение по умолчанию из класса
            level = j.getDefaultLevel();
        }
            
        MessageLevel = SetLevelMessageInt(level);

        if (level == "q") break;
        
        std::cout << std::endl; 
        message.setText(text);
        message.setLevel(level);
        message.setTime();
        if (MessageLevel >= DefaultLevel) { // Сравниваем уровень важности
            j.PushMessage(message);   
        } else {
            std::cout << "Message skip \nLevel message < default level.\n" << std::endl;
        }
    }

    
    
    j.Stop();
    loggerThread.join();

}