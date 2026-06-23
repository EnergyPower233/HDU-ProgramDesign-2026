#ifndef FACTORY_TOOL_SYSTEM_FACTORY_TOOL_SYSTEM_H
#define FACTORY_TOOL_SYSTEM_FACTORY_TOOL_SYSTEM_H

#include "BorrowRecord.h"
#include "Constants.h"
#include "Tool.h"
#include "Utils.h"

#include <map>
#include <memory>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>

class FactoryToolSystem {
private:
    std::vector<std::unique_ptr<Tool>> tools;
    std::vector<BorrowRecord> records;
    std::map<std::string, Tool *> toolIndex;
    std::set<int> unreturnedRecordIds;
    int nextRecordId = 1;

    void rebuildToolIndex();
    BorrowRecord *findRecord(int recordId);
    void printToolHeader() const;
    void printRecordHeader() const;
    std::string readToolStatus() const;

    template <typename T, typename Printer>
    void paginate(const std::vector<T> &items, Printer printer) const;

public:
    void loadData();
    void saveData() const;
    void saveStatistics() const;
    bool login() const;

    void addTool();
    void modifyTool();
    void queryTool() const;
    void deleteTool();
    void showAllTools() const;

    void borrowTool();
    void returnTool();
    void showBorrowRecords() const;

    void overallStatistics() const;
    void lowStockWarning() const;
    void borrowRanking() const;

    void saveAllFiles() const;
    void toolMenu();
    void borrowMenu();
    void statisticsMenu();
    void run();
};

template <typename T, typename Printer>
void FactoryToolSystem::paginate(const std::vector<T> &items, Printer printer) const {
    if (items.empty()) {
        std::cout << "暂无数据。\n";
        return;
    }
    int totalPages = static_cast<int>((items.size() + constants::PAGE_SIZE - 1) / constants::PAGE_SIZE);
    int page = 1;
    while (true) {
        std::cout << "\n第 " << page << " / " << totalPages << " 页\n";
        int begin = (page - 1) * constants::PAGE_SIZE;
        int end = std::min(begin + constants::PAGE_SIZE, static_cast<int>(items.size()));
        for (int i = begin; i < end; ++i) printer(items[i]);
        if (totalPages == 1) break;
        std::cout << "\n[n]下一页 [p]上一页 [q]退出分页：";
        std::string op;
        std::getline(std::cin, op);
        op = trim(op);
        if (op == "n" || op == "N") {
            if (page < totalPages) ++page;
        } else if (op == "p" || op == "P") {
            if (page > 1) --page;
        } else if (op == "q" || op == "Q") {
            break;
        } else {
            std::cout << "无效操作。\n";
        }
    }
}

#endif
