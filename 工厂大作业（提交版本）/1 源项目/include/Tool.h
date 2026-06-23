#ifndef FACTORY_TOOL_SYSTEM_TOOL_H
#define FACTORY_TOOL_SYSTEM_TOOL_H

#include <string>

class Tool {
private:
    std::string id;
    std::string name;
    std::string type;
    int stock;
    std::string status;
    int borrowed;
    std::string location;
    double price;

public:
    Tool();
    Tool(std::string id, std::string name, std::string type, int stock,
         std::string status, int borrowed, std::string location, double price);

    const std::string &getId() const;
    const std::string &getName() const;
    const std::string &getType() const;
    int getStock() const;
    const std::string &getStatus() const;
    int getBorrowed() const;
    const std::string &getLocation() const;
    double getPrice() const;
    int getTotalCount() const;
    double getTotalValue() const;

    void modifyInfo(const std::string &newName, const std::string &newType,
                    int newStock, const std::string &newStatus,
                    int newBorrowed, const std::string &newLocation,
                    double newPrice);
    bool borrowTool(int quantity);
    void returnTool(int quantity);

    std::string serialize() const;
    static bool deserialize(const std::string &line, Tool &tool);
    void print() const;
};

#endif
