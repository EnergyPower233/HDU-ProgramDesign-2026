#include "Tool.h"

#include "Utils.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

Tool::Tool() : stock(0), status("正常"), borrowed(0), price(0.0) {}

Tool::Tool(std::string id, std::string name, std::string type, int stock,
           std::string status, int borrowed, std::string location, double price)
    : id(std::move(id)), name(std::move(name)), type(std::move(type)),
      stock(stock), status(std::move(status)), borrowed(borrowed),
      location(std::move(location)), price(price) {}

const std::string &Tool::getId() const { return id; }
const std::string &Tool::getName() const { return name; }
const std::string &Tool::getType() const { return type; }
int Tool::getStock() const { return stock; }
const std::string &Tool::getStatus() const { return status; }
int Tool::getBorrowed() const { return borrowed; }
const std::string &Tool::getLocation() const { return location; }
double Tool::getPrice() const { return price; }
int Tool::getTotalCount() const { return stock + borrowed; }
double Tool::getTotalValue() const { return getTotalCount() * price; }

void Tool::modifyInfo(const std::string &newName, const std::string &newType,
                      int newStock, const std::string &newStatus,
                      int newBorrowed, const std::string &newLocation,
                      double newPrice) {
    name = newName;
    type = newType;
    stock = newStock;
    status = newStatus;
    borrowed = newBorrowed;
    location = newLocation;
    price = newPrice;
}

bool Tool::borrowTool(int quantity) {
    if (quantity <= 0 || stock < quantity || status == "损坏") return false;
    stock -= quantity;
    borrowed += quantity;
    return true;
}

void Tool::returnTool(int quantity) {
    if (quantity <= 0) return;
    stock += quantity;
    borrowed = std::max(0, borrowed - quantity);
}

std::string Tool::serialize() const {
    std::ostringstream oss;
    oss << id << '|' << name << '|' << type << '|' << stock << '|'
        << status << '|' << borrowed << '|' << location << '|'
        << std::fixed << std::setprecision(2) << price;
    return oss.str();
}

bool Tool::deserialize(const std::string &line, Tool &tool) {
    std::vector<std::string> fields = split(line, '|');
    if (fields.size() != 8) return false;
    if (!isInteger(fields[3]) || !isInteger(fields[5]) || !isMoney(fields[7])) return false;
    tool = Tool(fields[0], fields[1], fields[2], std::stoi(fields[3]), fields[4],
                std::stoi(fields[5]), fields[6], std::stod(fields[7]));
    return true;
}

void Tool::print() const {
    std::cout << std::left << std::setw(12) << id
              << std::setw(16) << name
              << std::setw(14) << type
              << std::setw(10) << stock
              << std::setw(10) << status
              << std::setw(12) << borrowed
              << std::setw(16) << location
              << std::fixed << std::setprecision(2) << std::setw(10) << price << '\n';
}
