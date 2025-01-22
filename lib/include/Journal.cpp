#include "../header/Journal.h"
#include <string.h>
#include <fstream>




Journal::Journal(std::string name, std::string defaultLevel) {
    this->name = name;
    this->defaultLevel = defaultLevel;
}



std::string Journal::getInfo() {
    return name + "\n" + defaultLevel;
}

std::string Journal::getDefaultLevel() {
    return defaultLevel;
}

void Journal::PushMessage(Message &message) {
    // Основной поток добавляет сообщение в очередь и 
    // уведомляет логирующий поток о наличии нового сообщения
    std::lock_guard<std::mutex> lock(mtx);
    messages.push_back(message);
    cv.notify_one();
}


void Journal::Write(std::string filename) {

    std::fstream out(filename + ".txt", std::fstream::out | std::fstream::app);

    if (out.is_open()) {
        out << "Name: " + name + "\nDefault level: " + defaultLevel + "\n";

        while (true) { 

            std::unique_lock<std::mutex> lock(mtx); // Блокируем поток
             // Ожидание сообщений в логирующем потоке
            cv.wait(lock, [&]{ return !(this->messages.empty()) || this->stop; }); 
           
            if (stop && messages.empty()) break;

            // Извлекаем сообщения
            Message message = messages.front();
            messages.erase(messages.begin());

            // Запись
            out << "\n\tText: " + message.getMessage() + "\n";
            out << "\tLevel: " + message.getLevel() + "\n";
            out << "\tTime: " + message.getTime() + "\n";
        }
    } else {
        throw "File " + filename + " err open.";
    }

    out.close();
}


void Journal::Stop() {
    {
        std::lock_guard<std::mutex> lock(mtx);  // Блокировка мьютекса
        stop = true;
    }
    cv.notify_one(); // Уведомление ожидающего потока
}
