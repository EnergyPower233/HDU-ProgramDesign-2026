#include "Utils.h"

#include <cctype>
#include <iostream>
#include <limits>
#include <sstream>

std::string trim(const std::string &s) {
    size_t first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, last - first + 1);
}

std::vector<std::string> split(const std::string &line, char delimiter) {
    std::vector<std::string> result;
    std::string item;
    std::stringstream ss(line);
    while (std::getline(ss, item, delimiter)) result.push_back(item);
    return result;
}

bool isInteger(const std::string &s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

bool isMoney(const std::string &s) {
    if (s.empty()) return false;
    bool dot = false;
    bool digit = false;
    for (char c : s) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digit = true;
        } else if (c == '.' && !dot) {
            dot = true;
        } else {
            return false;
        }
    }
    return digit;
}

bool isValidDate(const std::string &date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
    std::string y = date.substr(0, 4), m = date.substr(5, 2), d = date.substr(8, 2);
    if (!isInteger(y) || !isInteger(m) || !isInteger(d)) return false;
    int year = std::stoi(y), month = std::stoi(m), day = std::stoi(d);
    if (year < 1900 || year > 2100 || month < 1 || month > 12) return false;
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if (leap) days[2] = 29;
    return day >= 1 && day <= days[month];
}

std::string readNonEmpty(const std::string &prompt) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);
        if (!input.empty() && input.find('|') == std::string::npos) return input;
        std::cout << "输入不能为空，且不能包含字符 | ，请重新输入。\n";
    }
}

int readInt(const std::string &prompt, int minValue, int maxValue) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);
        if (isInteger(input)) {
            long long value = std::stoll(input);
            if (value >= minValue && value <= maxValue) return static_cast<int>(value);
        }
        std::cout << "请输入范围内的整数 [" << minValue << ", " << maxValue << "]。\n";
    }
}

double readDouble(const std::string &prompt, double minValue) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);
        if (isMoney(input)) {
            double value = std::stod(input);
            if (value >= minValue) return value;
        }
        std::cout << "请输入不小于 " << minValue << " 的合法数字。\n";
    }
}

std::string readDate(const std::string &prompt) {
    while (true) {
        std::string date = readNonEmpty(prompt);
        if (isValidDate(date)) return date;
        std::cout << "日期格式错误，请使用 YYYY-MM-DD，例如 2026-06-09。\n";
    }
}

void pressEnter() {
    std::cout << "\n按回车键继续...";
    std::string dummy;
    std::getline(std::cin, dummy);
}
