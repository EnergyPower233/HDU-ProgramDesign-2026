# Factory Tool Management System

一个基于 C++17 的工厂工具管理信息系统，支持工具信息维护、工具借还管理、统计分析和本地文件持久化。

## 功能特性

- 系统登录验证，默认账号 `root`，密码 `123456`
- 工具信息添加、修改、精准查询、删除和分页展示
- 使用 `std::map<std::string, Tool*>` 维护工具编号和工具对象地址
- 借用工具、归还工具、历史借还记录分页展示
- 使用 `std::set<int>` 维护未归还借还记录编号
- 库存整体统计、低库存红色预警、借用次数排行
- 启动自动加载数据，退出自动保存数据
- 对空输入、非法数字、非法日期、重复编号等情况进行校验

## 项目结构

```text
.
├── include/                 # 头文件
│   ├── BorrowRecord.h
│   ├── Constants.h
│   ├── FactoryToolSystem.h
│   ├── Tool.h
│   └── Utils.h
├── src/                     # 源文件
│   ├── BorrowRecord.cpp
│   ├── FactoryToolSystem.cpp
│   ├── Tool.cpp
│   ├── Utils.cpp
│   └── main.cpp
├── docs/                    # 项目文档
│   ├── DESIGN.md
│   └── USAGE.md
├── Makefile
├── README.md
└── .gitignore
```

## 构建与运行

```bash
make
make run
```

也可以手动编译：

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o factory_tool_system
./factory_tool_system
```

## 数据文件

程序会在运行目录下自动读写以下文件：

- `tools.dat`：工具信息
- `borrow_records.dat`：借还记录
- `statistics.txt`：统计结果

这些文件属于运行期数据，已在 `.gitignore` 中忽略。

## 文档

- [使用说明](docs/USAGE.md)
- [设计说明](docs/DESIGN.md)
- [实验报告](docs/REPORT.md)
