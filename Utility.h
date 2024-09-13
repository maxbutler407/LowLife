#ifndef UTILITY_H
#define UTILITY_H

#include <string>

// ----------Stylistic Functions----------
void Stagger(const std::string& string, int delay_ms);
void StaggerInt(const int& integer, int delay_ms);
void Sleep_1s();
void Sleep_5s();
void DisplayASCIIArtFromFile(const std::string& filePath);
int DisplayPhotoInNewWindow(const std::string& imagePath, const std::string& windowName, int width = 800, int height = 900, int x = 100, int y = 100);
void startMusic(const std::string& filePath);
void stopMusic();

#endif // UTILITY_H
