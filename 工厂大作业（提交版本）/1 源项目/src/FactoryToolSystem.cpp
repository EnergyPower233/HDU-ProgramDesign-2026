#include "FactoryToolSystem.h"

#include "Constants.h"
#include "Utils.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <utility>

using namespace constants;

void FactoryToolSystem::rebuildToolIndex() {
    toolIndex.clear();
    for (auto &tool : tools) toolIndex[tool->getId()] = tool.get();
}

BorrowRecord *FactoryToolSystem::findRecord(int recordId) {
    for (auto &record : records) {
        if (record.getRecordId() == recordId) return &record;
    }
    return nullptr;
}

void FactoryToolSystem::printToolHeader() const {
    std::cout << std::left << std::setw(12) << "编号"
              << std::setw(16) << "名称"
              << std::setw(14) << "类型"
              << std::setw(10) << "库存"
              << std::setw(10) << "状态"
              << std::setw(12) << "已借出"
              << std::setw(16) << "位置"
              << std::setw(10) << "单价" << '\n';
    std::cout << std::string(100, '-') << '\n';
}

void FactoryToolSystem::printRecordHeader() const {
    std::cout << std::left << std::setw(10) << "记录号"
              << std::setw(12) << "工具编号"
              << std::setw(14) << "借用人"
              << std::setw(14) << "借用日期"
              << std::setw(14) << "应还日期"
              << std::setw(10) << "数量"
              << std::setw(10) << "状态" << '\n';
    std::cout << std::string(84, '-') << '\n';
}

std::string FactoryToolSystem::readToolStatus() const {
    while (true) {
        std::cout << "工具状态(1.正常 2.损坏)：";
        std::string choice;
        std::getline(std::cin, choice);
        choice = trim(choice);
        if (choice == "1") return "正常";
        if (choice == "2") return "损坏";
        std::cout << "请选择 1 或 2。\n";
    }
}

void FactoryToolSystem::loadData() {
    tools.clear();
    records.clear();
    toolIndex.clear();
    unreturnedRecordIds.clear();
    nextRecordId = 1;

    std::ifstream toolIn(TOOL_FILE);
    std::string line;
    while (std::getline(toolIn, line)) {
        Tool tool;
        if (Tool::deserialize(line, tool) && toolIndex.count(tool.getId()) == 0) {
            tools.push_back(std::make_unique<Tool>(tool));
            toolIndex[tool.getId()] = tools.back().get();
        }
    }
    rebuildToolIndex();

    std::ifstream recordIn(RECORD_FILE);
    while (std::getline(recordIn, line)) {
        BorrowRecord record;
        if (BorrowRecord::deserialize(line, record)) {
            records.push_back(record);
            nextRecordId = std::max(nextRecordId, record.getRecordId() + 1);
            if (record.isBorrowed()) unreturnedRecordIds.insert(record.getRecordId());
        }
    }
}

void FactoryToolSystem::saveData() const {
    std::ofstream toolOut(TOOL_FILE);
    for (const auto &tool : tools) toolOut << tool->serialize() << '\n';

    std::ofstream recordOut(RECORD_FILE);
    for (const auto &record : records) recordOut << record.serialize() << '\n';

    saveStatistics();
}

void FactoryToolSystem::saveStatistics() const {
    std::ofstream out(STATS_FILE);
    int totalCount = 0;
    double totalValue = 0.0;
    for (const auto &tool : tools) {
        totalCount += tool->getTotalCount();
        totalValue += tool->getTotalValue();
    }

    out << "库存整体统计\n";
    out << "工具总数量：" << totalCount << '\n';
    out << "工具总价值：" << std::fixed << std::setprecision(2) << totalValue << '\n';
    out << "\n低库存工具（安全库存阈值：" << SAFE_STOCK << "）\n";
    for (const auto &tool : tools) {
        if (tool->getStock() < SAFE_STOCK) {
            out << tool->getId() << " " << tool->getName()
                << " 当前库存：" << tool->getStock() << '\n';
        }
    }
    out << "\n借用次数排行\n";
    std::map<std::string, int> counts;
    for (const auto &record : records) counts[record.getToolId()]++;
    std::vector<std::pair<std::string, int>> ranking(counts.begin(), counts.end());
    std::sort(ranking.begin(), ranking.end(), [](const auto &a, const auto &b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    for (const auto &item : ranking) {
        auto it = toolIndex.find(item.first);
        out << item.first << " "
            << (it == toolIndex.end() ? "未知工具" : it->second->getName())
            << " 借用次数：" << item.second << '\n';
    }
}

bool FactoryToolSystem::login() const {
    for (int attempt = 1; attempt <= 3; ++attempt) {
        std::string account = readNonEmpty("账号：");
        std::string password = readNonEmpty("密码：");
        if (account == "root" && password == "123456") {
            std::cout << "登录成功。\n";
            return true;
        }
        std::cout << "账号或密码错误，剩余尝试次数：" << (3 - attempt) << '\n';
    }
    return false;
}

void FactoryToolSystem::addTool() {
    std::cout << "\n【添加工具信息】\n";
    std::string id;
    while (true) {
        id = readNonEmpty("工具编号：");
        if (toolIndex.count(id) == 0) break;
        std::cout << "该编号已存在，请重新输入编号。\n";
    }
    std::string name = readNonEmpty("工具名称：");
    std::string type = readNonEmpty("工具类型：");
    int stock = readInt("当前库存数量：", 0);
    std::string status = readToolStatus();
    std::string location = readNonEmpty("仓库存放位置：");
    double price = readDouble("工具单价：", 0.0);

    tools.push_back(std::make_unique<Tool>(id, name, type, stock, status, 0, location, price));
    toolIndex[id] = tools.back().get();
    std::cout << "添加成功。\n";
}

void FactoryToolSystem::modifyTool() {
    std::cout << "\n【修改工具信息】\n";
    std::string id = readNonEmpty("请输入要修改的工具编号：");
    auto it = toolIndex.find(id);
    if (it == toolIndex.end()) {
        std::cout << "未找到该工具。\n";
        return;
    }

    Tool *tool = it->second;
    std::cout << "当前信息：\n";
    printToolHeader();
    tool->print();

    std::cout << "请重新输入该工具除编号外的全部信息。\n";
    std::string name = readNonEmpty("工具名称：");
    std::string type = readNonEmpty("工具类型：");
    int stock = readInt("当前库存数量：", 0);
    std::string status = readToolStatus();
    int borrowed = readInt("已借出数量：", 0);
    std::string location = readNonEmpty("仓库存放位置：");
    double price = readDouble("工具单价：", 0.0);

    tool->modifyInfo(name, type, stock, status, borrowed, location, price);
    std::cout << "修改成功。\n";
}

void FactoryToolSystem::queryTool() const {
    std::cout << "\n【查询工具信息】\n";
    std::cout << "1. 按工具编号查询\n2. 按工具名称查询\n3. 按工具类型查询\n";
    int choice = readInt("请选择查询关键字：", 1, 3);
    std::string keyword = readNonEmpty("请输入精准查询内容：");
    std::vector<Tool *> matched;
    for (const auto &tool : tools) {
        if ((choice == 1 && tool->getId() == keyword) ||
            (choice == 2 && tool->getName() == keyword) ||
            (choice == 3 && tool->getType() == keyword)) {
            matched.push_back(tool.get());
        }
    }

    printToolHeader();
    paginate<Tool *>(matched, [](Tool *tool) { tool->print(); });
}

void FactoryToolSystem::deleteTool() {
    std::cout << "\n【删除工具信息】\n";
    std::string id = readNonEmpty("请输入要删除的工具编号：");
    auto it = toolIndex.find(id);
    if (it == toolIndex.end()) {
        std::cout << "未找到该工具。\n";
        return;
    }
    if (it->second->getBorrowed() > 0) {
        std::cout << "该工具仍有借出数量，不能删除。\n";
        return;
    }
    std::cout << "即将删除工具：" << it->second->getName() << "，确认删除？(Y/N)：";
    std::string confirm;
    std::getline(std::cin, confirm);
    confirm = trim(confirm);
    if (confirm != "Y" && confirm != "y") {
        std::cout << "已取消删除。\n";
        return;
    }
    tools.erase(std::remove_if(tools.begin(), tools.end(), [&](const std::unique_ptr<Tool> &tool) {
        return tool->getId() == id;
    }), tools.end());
    rebuildToolIndex();
    std::cout << "删除成功，其他工具编号保持不变。\n";
}

void FactoryToolSystem::showAllTools() const {
    std::cout << "\n【显示所有工具信息】\n";
    printToolHeader();
    std::vector<Tool *> view;
    for (const auto &tool : tools) view.push_back(tool.get());
    paginate<Tool *>(view, [](Tool *tool) { tool->print(); });
}

void FactoryToolSystem::borrowTool() {
    std::cout << "\n【借用工具】\n";
    std::string id = readNonEmpty("工具编号：");
    auto it = toolIndex.find(id);
    if (it == toolIndex.end()) {
        std::cout << "工具不存在。\n";
        return;
    }
    Tool *tool = it->second;
    if (tool->getStock() <= 0 || tool->getStatus() == "损坏") {
        std::cout << "该工具库存不足或状态为损坏，不能借用。\n";
        return;
    }

    std::string borrower = readNonEmpty("借用人姓名：");
    int quantity = readInt("借用数量：", 1);
    if (quantity > tool->getStock()) {
        std::cout << "数量不足，当前可借库存为：" << tool->getStock() << '\n';
        return;
    }
    std::string borrowDate = readDate("借用日期(YYYY-MM-DD)：");
    std::string dueDate = readDate("应还日期(YYYY-MM-DD)：");
    if (dueDate < borrowDate) {
        std::cout << "应还日期不能早于借用日期，本次借用已取消。\n";
        return;
    }

    if (!tool->borrowTool(quantity)) {
        std::cout << "借用失败，请检查库存和工具状态。\n";
        return;
    }
    BorrowRecord record(nextRecordId++, id, borrower, borrowDate, dueDate, quantity, "已借");
    records.push_back(record);
    unreturnedRecordIds.insert(record.getRecordId());
    std::cout << "借用成功，借还记录编号为：" << record.getRecordId() << '\n';
}

void FactoryToolSystem::returnTool() {
    std::cout << "\n【归还工具】\n";
    int recordId = readInt("请输入借还记录编号：", 1);
    if (unreturnedRecordIds.count(recordId) == 0) {
        std::cout << "该记录不存在或已经归还。\n";
        return;
    }
    BorrowRecord *record = findRecord(recordId);
    if (record == nullptr) {
        std::cout << "记录数据异常。\n";
        return;
    }
    auto it = toolIndex.find(record->getToolId());
    if (it != toolIndex.end()) it->second->returnTool(record->getQuantity());
    record->markReturned();
    unreturnedRecordIds.erase(recordId);
    std::cout << "归还成功。\n";
}

void FactoryToolSystem::showBorrowRecords() const {
    std::cout << "\n【查看借还记录】\n";
    std::vector<const BorrowRecord *> view;
    for (const auto &record : records) view.push_back(&record);
    std::sort(view.begin(), view.end(), [](const BorrowRecord *a, const BorrowRecord *b) {
        if (a->getBorrowDate() != b->getBorrowDate()) return a->getBorrowDate() > b->getBorrowDate();
        return a->getRecordId() > b->getRecordId();
    });
    printRecordHeader();
    paginate<const BorrowRecord *>(view, [](const BorrowRecord *record) { record->print(); });
}

void FactoryToolSystem::overallStatistics() const {
    std::cout << "\n【库存整体统计】\n";
    int totalCount = 0;
    double totalValue = 0.0;
    for (const auto &tool : tools) {
        totalCount += tool->getTotalCount();
        totalValue += tool->getTotalValue();
    }
    std::cout << "工厂所有工具总数量：" << totalCount << '\n';
    std::cout << "工具总价值：" << std::fixed << std::setprecision(2) << totalValue << '\n';
}

void FactoryToolSystem::lowStockWarning() const {
    std::cout << "\n【低库存预警】安全库存阈值：" << SAFE_STOCK << '\n';
    bool found = false;
    printToolHeader();
    for (const auto &tool : tools) {
        if (tool->getStock() < SAFE_STOCK) {
            found = true;
            std::cout << "\033[31m";
            tool->print();
            std::cout << "\033[0m";
        }
    }
    if (!found) std::cout << "暂无低库存工具。\n";
}

void FactoryToolSystem::borrowRanking() const {
    std::cout << "\n【借用次数排行】\n";
    std::map<std::string, int> counts;
    for (const auto &record : records) counts[record.getToolId()]++;
    std::vector<std::pair<std::string, int>> ranking(counts.begin(), counts.end());
    std::sort(ranking.begin(), ranking.end(), [](const auto &a, const auto &b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    if (ranking.empty()) {
        std::cout << "暂无借用记录。\n";
        return;
    }

    struct RankItem {
        int rank;
        std::string toolId;
        int count;
    };
    std::vector<RankItem> rankView;
    for (size_t i = 0; i < ranking.size(); ++i) {
        rankView.push_back({static_cast<int>(i + 1), ranking[i].first, ranking[i].second});
    }

    std::cout << std::left << std::setw(8) << "排名"
              << std::setw(12) << "工具编号"
              << std::setw(16) << "工具名称"
              << std::setw(12) << "借用次数" << '\n';
    std::cout << std::string(48, '-') << '\n';
    paginate<RankItem>(rankView, [&](const RankItem &item) {
        auto found = toolIndex.find(item.toolId);
        std::cout << std::left << std::setw(8) << item.rank
                  << std::setw(12) << item.toolId
                  << std::setw(16) << (found == toolIndex.end() ? "未知工具" : found->second->getName())
                  << std::setw(12) << item.count << '\n';
    });
}

void FactoryToolSystem::saveAllFiles() const {
    saveData();
    std::cout << "工具信息、借还记录和统计结果已保存至本地文件。\n";
}

void FactoryToolSystem::toolMenu() {
    while (true) {
        std::cout << "\n========== 工具信息管理 ==========\n";
        std::cout << "1. 添加工具信息\n";
        std::cout << "2. 修改工具信息\n";
        std::cout << "3. 查询工具信息\n";
        std::cout << "4. 删除工具信息\n";
        std::cout << "5. 显示所有工具信息\n";
        std::cout << "0. 返回主菜单\n";
        int choice = readInt("请选择：", 0, 5);
        if (choice == 0) return;
        if (choice == 1) addTool();
        else if (choice == 2) modifyTool();
        else if (choice == 3) queryTool();
        else if (choice == 4) deleteTool();
        else if (choice == 5) showAllTools();
        pressEnter();
    }
}

void FactoryToolSystem::borrowMenu() {
    while (true) {
        std::cout << "\n========== 工具借还管理 ==========\n";
        std::cout << "1. 借用工具\n";
        std::cout << "2. 归还工具\n";
        std::cout << "3. 查看借还记录\n";
        std::cout << "0. 返回主菜单\n";
        int choice = readInt("请选择：", 0, 3);
        if (choice == 0) return;
        if (choice == 1) borrowTool();
        else if (choice == 2) returnTool();
        else if (choice == 3) showBorrowRecords();
        pressEnter();
    }
}

void FactoryToolSystem::statisticsMenu() {
    while (true) {
        std::cout << "\n========== 统计分析 ==========\n";
        std::cout << "1. 库存整体统计\n";
        std::cout << "2. 低库存预警\n";
        std::cout << "3. 借用次数排行\n";
        std::cout << "4. 保存统计结果到文件\n";
        std::cout << "0. 返回主菜单\n";
        int choice = readInt("请选择：", 0, 4);
        if (choice == 0) return;
        if (choice == 1) overallStatistics();
        else if (choice == 2) lowStockWarning();
        else if (choice == 3) borrowRanking();
        else if (choice == 4) {
            saveStatistics();
            std::cout << "统计结果已保存至 " << STATS_FILE << "。\n";
        }
        pressEnter();
    }
}

void FactoryToolSystem::run() {
    loadData();
    std::cout << "========== 工厂工具管理信息系统 ==========\n";
    if (!login()) {
        std::cout << "登录失败，系统退出。\n";
        return;
    }
    while (true) {
        std::cout << "\n============== 主菜单 ==============\n";
        std::cout << "1. 工具信息管理\n";
        std::cout << "2. 工具借还管理\n";
        std::cout << "3. 统计分析\n";
        std::cout << "4. 数据文件保存\n";
        std::cout << "0. 退出系统\n";
        int choice = readInt("请选择：", 0, 4);
        if (choice == 0) {
            saveData();
            std::cout << "数据已自动保存，安全退出系统。\n";
            break;
        }
        if (choice == 1) toolMenu();
        else if (choice == 2) borrowMenu();
        else if (choice == 3) statisticsMenu();
        else if (choice == 4) saveAllFiles();
    }
}
