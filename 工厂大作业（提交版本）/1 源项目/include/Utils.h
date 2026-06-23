#ifndef FACTORY_TOOL_SYSTEM_UTILS_H
#define FACTORY_TOOL_SYSTEM_UTILS_H

#include <string>
#include <vector>

std::string trim(const std::string &s);
std::vector<std::string> split(const std::string &line, char delimiter);
bool isInteger(const std::string &s);
bool isMoney(const std::string &s);
bool isValidDate(const std::string &date);

std::string readNonEmpty(const std::string &prompt);
int readInt(const std::string &prompt, int minValue = 0, int maxValue = 2147483647);
double readDouble(const std::string &prompt, double minValue = 0.0);
std::string readDate(const std::string &prompt);
void pressEnter();

#endif
