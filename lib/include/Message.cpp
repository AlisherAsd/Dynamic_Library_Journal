#include "../header/Message.h"
#include <string.h>
#include <ctime>
#include <sstream>



Message::Message(std::string message, std::string level) {
    this->message = message;
    this->level = level;
    this->time = this->getCurrentTime();
}


Message::Message() {
    this->message = "";
    this->level = "";
    this->time = this->getCurrentTime();
}

std::string Message::getMessage() {
    return message;
}

std::string Message::getLevel() {
    return level;
}

std::string Message::getTime() {
    return time;
}


std::string Message::getInfo() {
    return message + " " + level + " " + time;
}

void Message::setText(std::string text) {
    this->message = text;
}

void Message::setLevel(std::string level) {
    this->level = level;
}

void Message::setTime() {
    this->getCurrentTime();
}

std::string Message::getCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::stringstream ss;
    ss << std::ctime(&now);
    return ss.str();
}
