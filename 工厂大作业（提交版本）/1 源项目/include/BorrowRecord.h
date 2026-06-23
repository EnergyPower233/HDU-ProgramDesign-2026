#ifndef FACTORY_TOOL_SYSTEM_BORROW_RECORD_H
#define FACTORY_TOOL_SYSTEM_BORROW_RECORD_H

#include <string>

class BorrowRecord {
private:
    int recordId;
    std::string toolId;
    std::string borrower;
    std::string borrowDate;
    std::string dueDate;
    int quantity;
    std::string status;

public:
    BorrowRecord();
    BorrowRecord(int recordId, std::string toolId, std::string borrower,
                 std::string borrowDate, std::string dueDate, int quantity,
                 std::string status);

    int getRecordId() const;
    const std::string &getToolId() const;
    const std::string &getBorrower() const;
    const std::string &getBorrowDate() const;
    const std::string &getDueDate() const;
    int getQuantity() const;
    const std::string &getStatus() const;
    bool isBorrowed() const;

    void markReturned();

    std::string serialize() const;
    static bool deserialize(const std::string &line, BorrowRecord &record);
    void print() const;
};

#endif
