#pragma once
#include <iostream>
#include <string.h>
#include <vector>


class Message
{
private:

    std::string message;
    std::string level;
    std::string time;
    std::string getCurrentTime(); // Функция для получения текущего времени

public:
    Message(std::string, std::string);
    Message();

    std::string getMessage();
    std::string getLevel();
    std::string getTime() ;
    std::string getInfo() ;
    void setText(std::string);
    void setTime();
    void setLevel(std::string);
};


