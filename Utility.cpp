#include "Utility.h"
#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <irrKlang.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;

// Global sound engine pointer
ISoundEngine* engine = nullptr;

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

// Function to display the image in a new window with a specific size
int DisplayPhotoInNewWindow(const std::string& imagePath, const std::string& windowName, int width, int height, int x, int y) {
    // Set OpenCV logging level to error only -- hides unwanted text
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);

    // Load the image
    cv::Mat image = cv::imread(imagePath);

    // Check if the image is loaded successfully
    if (image.empty()) {
        std::cerr << "Could not open or find the image at: " << imagePath << "\n";
        return -1;
    }

    // Resize the image to the specified width and height
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(width, height));

    // Create the window with the specified name
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::resizeWindow(windowName, width, height);

    // Display the image
    cv::imshow(windowName, resizedImage);

    // Wait for a keystroke in the window
    cv::waitKey(0);

    return 0; // Return 0 to indicate success
}

void startMusic(const std::string& filePath) {
    // Initialize the sound engine if it is not already initialized
    if (!engine) {
        engine = createIrrKlangDevice();
        if (!engine) {
            std::cerr << "Could not initialize sound engine" << std::endl;
            return;
        }
    }

    // Play the sound file
    ISound* sound = engine->play2D(filePath.c_str(), true, false, true);

    if (!sound) {
        std::cerr << "Could not play the sound file: " << filePath << std::endl;
        return;
    }
}

void stopMusic() {
    if (engine) {
        // Stop all sounds
        engine->stopAllSounds();

        // Drop the sound engine to release resources
        engine->drop();
        engine = nullptr; // Set to nullptr to indicate the engine has been released
    }
}