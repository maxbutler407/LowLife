#ifndef UTILITY_H
#define UTILITY_H

#include <string>

// ----------Stylistic Functions----------
void Stagger(const std::string& string, int delay_ms);
void StaggerInt(const int& integer, int delay_ms);
void Sleep_1s();
void Sleep_5s();
void DisplayASCIIArtFromFile(const std::string& filePath);

#endif // UTILITY_H
