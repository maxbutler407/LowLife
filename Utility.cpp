#include "Utility.h"
#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

// miniaudio import
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#ifdef _WIN32
#include <Windows.h>
#endif

void Stagger(const std::string& string, int delay_ms) {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, 0); // Disable input

    for (char c : string) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }

    // clears any player input whilst staggering text
    FlushConsoleInputBuffer(hInput);

    // re-enables input
    SetConsoleMode(hInput, prev_mode);
}

void StaggerInt(const int& integer, int delay_ms) {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, 0);

    std::string intStr = std::to_string(integer);
    for (char c : intStr) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }

    // clears any player input whilst staggering text
    FlushConsoleInputBuffer(hInput);

    // re-enables input
    SetConsoleMode(hInput, prev_mode);
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

// for any ASCII art imported from a file
void DisplayASCIIArtFromFile(const std::string& filePath) {
    std::ifstream file(filePath);

    // checks if file path is correct
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

// displays character and location images in a new size-specified window
int DisplayPhotoInNewWindow(const std::string& imagePath, const std::string& windowName, int width, int height, int x, int y) {

    // sets OpenCV logging level to error only -- hides unwanted text
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);

    // loads the image
    cv::Mat image = cv::imread(imagePath);

    // checks if the image is loaded successfully
    if (image.empty()) {
        std::cerr << "Could not open or find the image at: " << imagePath << "\n";
        return -1;
    }

    // resizes image to the specified width and height
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(width, height));

    // creates the window with the specified name
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::resizeWindow(windowName, width, height);

    // displays the image
    cv::imshow(windowName, resizedImage);

    // waits for a keystroke in the window
    cv::waitKey(0);

    return 0;
}

ma_engine engine;
bool engineInitialized = false;
ma_sound currentSound;

void startMusic(const std::string& filePath) {
    if (!engineInitialized) {
        ma_engine_init(NULL, &engine);
        engineInitialized = true;
    }
    ma_sound_init_from_file(&engine, filePath.c_str(), 0, NULL, NULL, &currentSound);
    ma_sound_set_looping(&currentSound, MA_TRUE);
    ma_sound_start(&currentSound);
}

void stopMusic() {
    if (engineInitialized) {
        ma_sound_stop(&currentSound);
        ma_sound_uninit(&currentSound);
    }
}