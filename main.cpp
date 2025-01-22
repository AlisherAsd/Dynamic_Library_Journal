#include <iostream>
#include "./lib/header/app.h"


int main() {
    try {
        // Запуск основного консольного приложения
        app(); 
    }
    catch(const char* ex) {
        std::cout << ex;
    }
    catch(const std::exception& e) 
    {
        std::cout << e.what() << '\n';
    }
    catch(...) { // ловит все подряд
        std::cout << "ERROR Catch (...)";
    }
    std::cout << "\nProgram end.";
}