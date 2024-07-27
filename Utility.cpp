#include "Utility.h"
#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <chrono>  

void Stagger(const std::string& string, int delay_ms) {
    for (char c : string) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

void StaggerInt(const int& integer, int delay_ms) {
    std::string intStr = std::to_string(integer);
    for (char c : intStr) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

// Sleep_xs() methods delays the execution of the programme when called.
void Sleep_1s() {
    using namespace std::this_thread;
    using namespace std::chrono;

    sleep_until(system_clock::now() + seconds(1));
}

void Sleep_5s() {
    using namespace std::this_thread;
    using namespace std::chrono;

    sleep_until(system_clock::now() + seconds(5));
}

void DisplayASCIIArtFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "\nCould not open the file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}