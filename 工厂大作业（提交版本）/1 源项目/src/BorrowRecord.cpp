#include "BorrowRecord.h"

#include "Utils.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

BorrowRecord::BorrowRecord() : recordId(0), quantity(0), status("已借") {}

BorrowRecord::BorrowRecord(int recordId, std::string toolId, std::string borrower,
                           std::string borrowDate, std::string dueDate, int quantity,
                           std::string status)
    : recordId(recordId), toolId(std::move(toolId)), borrower(std::move(borrower)),
      borrowDate(std::move(borrowDate)), dueDate(std::move(dueDate)),
      quantity(quantity), status(std::move(status)) {}

int BorrowRecord::getRecordId() const { return recordId; }
const std::string &BorrowRecord::getToolId() const { return toolId; }
const std::string &BorrowRecord::getBorrower() const { return borrower; }
const std::string &BorrowRecord::getBorrowDate() const { return borrowDate; }
const std::string &BorrowRecord::getDueDate() const { return dueDate; }
int BorrowRecord::getQuantity() const { return quantity; }
const std::string &BorrowRecord::getStatus() const { return status; }
bool BorrowRecord::isBorrowed() const { return status == "已借"; }

void BorrowRecord::markReturned() { status = "已还"; }

std::string BorrowRecord::serialize() const {
    std::ostringstream oss;
    oss << recordId << '|' << toolId << '|' << borrower << '|' << borrowDate
        << '|' << dueDate << '|' << quantity << '|' << status;
    return oss.str();
}

bool BorrowRecord::deserialize(const std::string &line, BorrowRecord &record) {
    std::vector<std::string> fields = split(line, '|');
    if (fields.size() != 7) return false;
    if (!isInteger(fields[0]) || !isInteger(fields[5])) return false;
    record = BorrowRecord(std::stoi(fields[0]), fields[1], fields[2], fields[3],
                          fields[4], std::stoi(fields[5]), fields[6]);
    return true;
}

void BorrowRecord::print() const {
    std::cout << std::left << std::setw(10) << recordId
              << std::setw(12) << toolId
              << std::setw(14) << borrower
              << std::setw(14) << borrowDate
              << std::setw(14) << dueDate
              << std::setw(10) << quantity
              << std::setw(10) << status << '\n';
}
