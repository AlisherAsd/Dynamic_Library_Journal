#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include "Message.h"
#include "./Journal.h"
#include <mutex>
#include <condition_variable>
#include <thread>

class Journal
{

private:

    std::string name;
    std::string defaultLevel;
    std::vector<Message> messages;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;

public:

    Journal(std::string, std::string);

    std::string getInfo();
    std::string getDefaultLevel();
    void PushMessage(Message &); // Пушим в вектор сообщение в виде объекта
    void Write(std::string); // Запись из вектора в файл
    void Stop(); // Сообщает потоку записи о завершении работы

};

